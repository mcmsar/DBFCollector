
#ifndef INC_NOTIFYMGR
#define INC_NOTIFYMGR

#pragma warning(disable:4786)	// Disable warning messages for stl debug symbol size.
#include "criticalsection.h"
#include <map>
using std::map;

typedef map<unsigned long, IUnknown*> MAPCALLBACKS;

class CEMSMsgNotificationMgr
{
public:
	CEMSMsgNotificationMgr();
	~CEMSMsgNotificationMgr();

	unsigned long Register( IUnknown* pCallBack );
	void Unregister( const unsigned long culCookie );
	unsigned long GetCount();
	IUnknown* GetAt( const unsigned long culIndex );
	void RemoveAt( const unsigned long culIndex );

private:	// methods
	void _ReleaseCallbacks();
	unsigned long _Cookie();

private:	// data
	MAPCALLBACKS m_mapCallBacks;
	static unsigned long ms_ulCurrentCookie;

	CEMSCriticalSection m_csCookie;
	CEMSCriticalSection m_csMap;
};
#endif // INC_NOTIFYMGR
