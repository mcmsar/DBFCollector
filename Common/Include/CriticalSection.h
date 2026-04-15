#ifndef __CRITICALSECTION_H__
#define __CRITICALSECTION_H__

#ifdef WIN32

// Can't include both afxdisp.h and windows.h simultaneously without getting a compiler error.
// So, projects including MFC and using this class should define __EMS_USING_MFC__
#ifdef __EMS_USING_MFC__
#include <afxdisp.h>
#else
#include <windows.h>
#endif

class CEMSCriticalSection
{
public:
	CEMSCriticalSection() { InitializeCriticalSection( &m_CS ); }
	virtual ~CEMSCriticalSection() { DeleteCriticalSection( &m_CS ); }

	void Enter() { EnterCriticalSection( &m_CS ); }
	void Leave() { LeaveCriticalSection( &m_CS ); }

private:
	CRITICAL_SECTION m_CS;
};

#elif defined(_POSIX_THREADS)	// not WIN32
class CEMSCriticalSection
{
public:
	inline CEMSCriticalSection();
	inline virtual ~CEMSCriticalSection();

	void Enter() { pthread_mutex_lock( &m_oMutex ); }
	void Leave() { pthread_mutex_unlock( &m_oMutex ); }

private:
	pthread_mutex_t m_oMutex;
};

CEMSCriticalSection::CEMSCriticalSection()
{
	pthread_mutexattr_t oAttr;

	int iRet = pthread_mutexattr_init( &oAttr );

	bool bAttrInit = false;

	if( 0 == iRet )
	{
		iRet = pthread_mutexattr_settype( &oAttr, PTHREAD_MUTEX_RECURSIVE  );

		bAttrInit = true;
	}

	if( 0 == iRet )
	{
		iRet = pthread_mutex_init( &m_oMutex, &oAttr );
	}

	if( bAttrInit )
	{
		pthread_mutexattr_destroy( &oAttr );
	}
}

CEMSCriticalSection::~CEMSCriticalSection()
{
	int iRet = pthread_mutex_destroy( &m_oMutex );
}

#endif

#endif //__CRITICALSECTION_H__