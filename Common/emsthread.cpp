#include "emsthread.h"
#ifdef WIN32
#include <process.h>
#endif
#include <exception>

#ifdef _POSIX_THREADS
#include <assert.h>
#endif

const unsigned long culMaxShutdownWaitTimeout = 3000;

CEMSThread::CEMSThread() :	m_id(0), 
#ifdef WIN32
							m_h(0), m_hStopEvent(0),
#elif defined(_POSIX_THREADS)
							m_bStopRequested(false),
#endif
							m_ulStackSize(0)
{
}

CEMSThread::~CEMSThread()
{
#ifdef WIN32
    if (m_h != 0)
#elif defined(_POSIX_THREADS)
	if( 0 != m_id )
#endif
    {
        if( !wait( culMaxShutdownWaitTimeout ) )
		{
			stop();
		}
		else
		{
#ifdef WIN32
			CloseHandle(m_h);
			m_id = 0;
			m_h = 0;
#elif defined(_POSIX_THREADS)
			pthread_detach( m_id );
			m_id = 0;
#endif
		}
    }

#ifdef WIN32
	if( m_hStopEvent )
	{
		CloseHandle( m_hStopEvent );
		m_hStopEvent = 0;
	}
#elif defined(_POSIX_THREADS)
#endif
}

void CEMSThread::start()
{
#ifdef WIN32
	if( 0 == m_hStopEvent )
	{
		m_hStopEvent = CreateEvent( 0, FALSE, FALSE, 0 );
	}

    if (m_h != 0)
    {
        wait();
        CloseHandle(m_h);
        m_id = 0;
        m_h = 0;
    }
    unsigned id;
    unsigned long h = _beginthreadex(0, m_ulStackSize, entryPoint, this,
        CREATE_SUSPENDED, &id);
    if (h == 0)
    {
        //throw Exception(Exception::k_threadCreationFailure);
    }
	else
	{
		m_id = id;
		m_h = reinterpret_cast<HANDLE>(h);
		if (ResumeThread(m_h) == static_cast<DWORD>(-1))
		{
			//throw Exception(Exception::k_threadResumeFailure, GetLastError());
		}
	}
#elif defined(_POSIX_THREADS)
	m_bStopRequested = false;
	pthread_attr_t attrThread;
	int iRet = pthread_attr_init( &attrThread );

	if( 0 == iRet )
	{
		if( 0 != m_ulStackSize )
		{
			iRet = pthread_attr_setstacksize( &attrThread, m_ulStackSize );
		}
	}

	if( 0 == iRet )
	{
		pthread_t idThread;
		iRet = pthread_create( &idThread, &attrThread, entryPoint, NULL );

		if( 0 == iRet )
		{
			m_id = idThread;
		}

	}
	
#endif
}

void CEMSThread::stop()
{
#ifdef WIN32
	if( 0 != m_h )
	{
		TerminateThread( m_h, 0);
		CloseHandle( m_h );
		m_h = 0;
		m_id = 0;
	}
#elif defined(_POSIX_THREADS)
	// This is a hard stop.
	if( 0 != m_id )
	{
		if( PTHREAD_CANCELLED != m_id )
		{
			int iRet = pthread_cancel( m_id );
		}

	}
#endif
}

#ifdef WIN32
unsigned __stdcall CEMSThread::entryPoint(void* pArg)
#elif defined(_POSIX_THREADS)
void* CEMSThread::entryPoint(void* pArg);
#endif
{
    try
    {
        CEMSThread* pThis = static_cast<CEMSThread*>(pArg);
        pThis->run();
    }
    //catch (const exception& )
    catch (...)
    {
//        cout << "std::exception in thread:  " << e.what() << endl << endl;
    }
    return 0;
}

bool CEMSThread::wait(unsigned long timeout)
{
    bool result = true;

#ifdef WIN32
    if (m_h != 0)
    {
        switch (WaitForSingleObject(m_h, timeout))
        {
        case WAIT_OBJECT_0:
            break;

        case WAIT_TIMEOUT:
            result = false;
            break;

        default:
//            throw Exception(Exception::k_threadWaitFailure,
//                GetLastError());
            break;
        }
    }
#elif defined(_POSIX_THREADS)
	// We're waiting for the thread to stop here.
#endif

    return result;
}

bool 
CEMSThread::WaitForStop( unsigned long timeout )
{
	bool bRet = false;

#ifdef WIN32
	if( m_hStopEvent )
	{
		switch( WaitForSingleObject( m_hStopEvent, timeout ) )
		{
			case WAIT_OBJECT_0:
				bRet = true;
				break;
			case WAIT_TIMEOUT:
				break;
		}
	}
#elif defined(__VMS)
	// For this to work, event handling implementation is needed.
	assert( false );
#endif

	return bRet;
}

void
CEMSThread::SignalStop()
{
#ifdef WIN32
	if( m_hStopEvent )
	{
		SetEvent( m_hStopEvent );
	}
#elif defined(_VMS)
	// For this to work, event handling implementation is needed.
	assert( false );
#endif
}