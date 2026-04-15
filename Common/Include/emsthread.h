#ifndef __EMSTHREAD_H__
#define __EMSTHREAD_H__

#ifdef WIN32
// Can't include both afxdisp.h and windows.h simultaneously without getting a compiler error.
// So, projects including MFC and using this class should define __EMS_USING_MFC__
#ifdef __EMS_USING_MFC__
#include <afxdisp.h>
#else
#include <windows.h>
#endif
#elif defined(_POSIX_THREADS)
#include <pthread.h>
#define INFINITE 0
#endif

class CEMSThread
{
public:
    CEMSThread();
    virtual ~CEMSThread();

    virtual void start();
    virtual bool wait(unsigned long timeout = INFINITE);
	virtual void stop();

#ifdef WIN32
    unsigned long getId() const
        { return m_id; }
    HANDLE getHandle() const
        { return m_h; }
#elif defined( _POSIX_THREADS)
	pthread_t getId() const { return m_id; }
#endif

	bool WaitForStop( unsigned long timeout = INFINITE );
	void SignalStop();
	void SetStackSize( const unsigned long culStackBytes ) { m_ulStackSize = culStackBytes; }

protected:
    virtual void run() = 0;

#ifdef WIN32
	// Protected so that the derived class
	// can do a WaitForMultipleObjects() that 
	// includes this event
	HANDLE			m_hStopEvent;
#endif


private:
#ifdef WIN32
    static unsigned __stdcall entryPoint(void* pArg);
#elif defined(_POSIX_THREADS)
	static void* entryPoint(void* pArg);
#endif

#ifdef WIN32
    unsigned long   m_id;
    HANDLE          m_h;
#elif defined(_POSIX_THREADS)
	pthread_t		m_id;
	bool			m_bStopRequested;
#endif
	unsigned long	m_ulStackSize;
};

#endif