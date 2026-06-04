#ifndef INC_TRANSMITQUEUE_H
#define INC_TRANSMITQUEUE_H

#include <windows.h>
#include <mutex>
#include <condition_variable>
#include <queue>

// Move-only packet that owns its serialized payload buffer.
struct TransmitPacket
{
	BYTE*  pData   = nullptr;
	DWORD  dwBytes = 0;

	TransmitPacket() = default;
	TransmitPacket(BYTE* p, DWORD n) : pData(p), dwBytes(n) {}
	~TransmitPacket() { delete[] pData; }

	TransmitPacket(TransmitPacket&& o) noexcept
		: pData(o.pData), dwBytes(o.dwBytes)
	{ o.pData = nullptr; o.dwBytes = 0; }

	TransmitPacket& operator=(TransmitPacket&& o) noexcept
	{
		if (this != &o) {
			delete[] pData;
			pData = o.pData;   dwBytes = o.dwBytes;
			o.pData = nullptr; o.dwBytes = 0;
		}
		return *this;
	}

	TransmitPacket(const TransmitPacket&)            = delete;
	TransmitPacket& operator=(const TransmitPacket&) = delete;
};

// Bounded, thread-safe queue used to hand serialized packets to a
// background transmit thread without blocking the processing thread.
class CTransmitQueue
{
public:
	explicit CTransmitQueue(int nMaxDepth = 4)
		: m_nMaxDepth(nMaxDepth), m_bStop(false) {}

	void Push(TransmitPacket pkt)
	{
		std::lock_guard<std::mutex> lk(m_mtx);
		if ((int)m_q.size() >= m_nMaxDepth)
		{
			printf("[TransmitQueue] full -- dropping oldest packet\n");
			m_q.pop();
		}
		m_q.push(std::move(pkt));
		m_cv.notify_one();
	}

	// Returns false when stopped and queue is drained.
	bool Pop(TransmitPacket& out)
	{
		std::unique_lock<std::mutex> lk(m_mtx);
		m_cv.wait(lk, [this]{ return !m_q.empty() || m_bStop; });
		if (m_q.empty()) return false;
		out = std::move(m_q.front());
		m_q.pop();
		return true;
	}

	void Stop()
	{
		std::lock_guard<std::mutex> lk(m_mtx);
		m_bStop = true;
		m_cv.notify_all();
	}

	// Reset stop flag and drain stale packets before restarting a thread.
	void Restart()
	{
		std::lock_guard<std::mutex> lk(m_mtx);
		m_bStop = false;
		while (!m_q.empty()) m_q.pop();
	}

private:
	std::queue<TransmitPacket> m_q;
	std::mutex                 m_mtx;
	std::condition_variable    m_cv;
	int                        m_nMaxDepth;
	bool                       m_bStop;
};

#endif // INC_TRANSMITQUEUE_H
