#ifndef __SOURCEINFO_H__
#define __SOURCEINFO_H__

#include "emsiteif.h"
#include "emslinfo.h"

class CEMSSourceInfo
{
public:
	CEMSSourceInfo();
	CEMSSourceInfo( CEMSSourceInfo& oInfo );
	~CEMSSourceInfo();

	EMS_RESULT Init();
	ULONG GetSiteID() { return m_ulSiteID; }
	ULONG GetOIID() { return m_ulOIID; }
	ULONG GetNextMsgNumber( ULONG ulDestID );
	char* GetShortName() { return m_szOIName; }
private:
	EMS_RESULT _InitSiteInfo();

private:
	IEMSSiteInfo*	m_pSiteInfo;
	ULONG m_ulSiteID;
	ULONG m_ulOIID;
	char m_szOIName[_MAX_PATH+1];
};

#endif