#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length

#include "routeendconfig.h"
#include "emserror.h"
#include "emsexcpt.h"

CEMSRouteEndConfig::CEMSRouteEndConfig() : m_wszRouteName(0), m_ulID(0), m_wszName(0),
									m_wszTranslationTable(0), m_bMultiSit(false),
									m_ulMaxSatellites(0), m_ulMaxAlertsPerMsg(0), m_wszAlias(0),
									m_bReportSourceChannel(false), m_bUseSecurityToken(false)
{
	memset( &m_specDirect, 0, sizeof( EMSDIRECTCOPYSPEC ) );
	memset( &m_specFTP, 0, sizeof(EMSFTPSPEC) );
	memset( &m_specSOAP, 0, sizeof(EMSSOAPSPEC) );
}

CEMSRouteEndConfig::CEMSRouteEndConfig( const CEMSRouteEndConfig& x )
{
	CEMSRouteEndConfig();

	if( x.m_wszRouteName )
		SetRouteName( x.m_wszRouteName );

	SetID( x.m_ulID );

	if( x.m_wszName )
		SetName( x.m_wszName );

	if( x.m_wszTranslationTable )
		SetTranslationTable( m_wszTranslationTable );

	m_bMultiSit = x.m_bMultiSit;
	m_bReportSourceChannel = x.m_bReportSourceChannel;
	m_bUseSecurityToken = x.m_bUseSecurityToken;

	SetMaxSatellites( m_ulMaxSatellites );

	m_ulMaxAlertsPerMsg = x.m_ulMaxAlertsPerMsg;

	if( x.m_wszAlias )
		SetAlias( x.m_wszAlias );
}

CEMSRouteEndConfig::~CEMSRouteEndConfig()
{
	if( m_wszRouteName )
		delete[] m_wszRouteName;
	m_wszRouteName = 0;

	if( m_wszName )
		delete[] m_wszName;
	m_wszName = 0;

	if( m_wszTranslationTable )
		delete[] m_wszTranslationTable;
	m_wszTranslationTable = 0;

	if( m_specDirect.wszDir )
		delete[] m_specDirect.wszDir;
	m_specDirect.wszDir = 0;

	if( m_specFTP.wszHost )
		delete[] m_specFTP.wszHost;
	m_specFTP.wszHost = 0;

	if( m_specFTP.wszLogin )
		delete[] m_specFTP.wszLogin;
	m_specFTP.wszLogin = 0;

	if( m_specFTP.wszPwd )
		delete[] m_specFTP.wszPwd;
	m_specFTP.wszPwd = 0;

	if( m_specFTP.wszDir )
		delete[] m_specFTP.wszDir;
	m_specFTP.wszDir = 0;

	if( m_specSOAP.wszEndpoint )
		delete[] m_specSOAP.wszEndpoint;
	m_specSOAP.wszEndpoint = 0;

	if( m_wszAlias )
		delete[] m_wszAlias;
	m_wszAlias = 0;
}

void
CEMSRouteEndConfig::SetAlias( const wchar_t* cwszName )
{
	if( !cwszName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	_SetString( m_wszAlias, cwszName );
}

wchar_t*
CEMSRouteEndConfig::GetAlias() const
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszAlias );

	return wszRet;
}

void
CEMSRouteEndConfig::SetRouteName( const wchar_t* cwszRoute )
{
	if( !cwszRoute )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	_SetString( m_wszRouteName, cwszRoute );
}

wchar_t*
CEMSRouteEndConfig::GetRouteName() const
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszRouteName );

	return wszRet;
}

void
CEMSRouteEndConfig::SetName( const wchar_t* cwszName )
{
	_SetString( m_wszName, cwszName );
}

wchar_t*
CEMSRouteEndConfig::GetName() const
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszName );

	return wszRet;
}

/*void
CEMSRouteConfig::SetToName( const wchar_t* cwszTo )
{
	_SetString( m_wszToName, cwszTo );
}

wchar_t*
CEMSRouteConfig::GetToName() const
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszToName );

	return wszRet;
}*/

void
CEMSRouteEndConfig::SetTranslationTable( const wchar_t* cwszTable )
{
	_SetString( m_wszTranslationTable, cwszTable );
}

wchar_t*
CEMSRouteEndConfig::GetTranslationTable() const
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszTranslationTable );

	return wszRet;
}

void 
CEMSRouteEndConfig::SetMsgType( const EMSRESOURCEIDENTIFIER ceResource, const EMSMSGTYPE ceMsgType )
{
	std::map<EMSRESOURCEIDENTIFIER,EMSMSGTYPE>::iterator itFind = m_mapResourceMsgTypeTable.find( ceResource );

	if( itFind == m_mapResourceMsgTypeTable.end() )
	{
		m_mapResourceMsgTypeTable.insert( std::pair<EMSRESOURCEIDENTIFIER, EMSMSGTYPE>( ceResource, ceMsgType ) );
	}
}

EMSMSGTYPE 
CEMSRouteEndConfig::GetMsgType( const EMSRESOURCEIDENTIFIER ceResource ) const
{
	EMSMSGTYPE eType = MSGTYPE_UNKNOWN;

	std::map<EMSRESOURCEIDENTIFIER,EMSMSGTYPE>::const_iterator itFind = m_mapResourceMsgTypeTable.find( ceResource );

	if( itFind != m_mapResourceMsgTypeTable.end() )
	{
		eType = itFind->second;
	}

	return eType;
}

void 
CEMSRouteEndConfig::SetSitSID( const long clSID )
{
	if( 0 != clSID )
	{
		m_setSID.insert( clSID );
	}
}

bool 
CEMSRouteEndConfig::IsSitSID( const long clSID)
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setSID.find( clSID );

	if( itFind != m_setSID.end() )
	{
		bRet = true;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetInSitSID( const long clSID )
{
	if( 0 != clSID )
	{
		m_setInSID.insert( clSID );
	}
}

bool
CEMSRouteEndConfig::IsInSitSID( const long clSID )
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setInSID.find( clSID );

	if( itFind != m_setInSID.end() )
	{
		bRet = true;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetSitInternal( const long clSit )
{
	if( 0 != clSit )
	{
		m_setSITInternal.insert( clSit );
	}
}

bool
CEMSRouteEndConfig::IsSitInternal( const long clSit )
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setSITInternal.find( clSit );

	if( itFind != m_setSITInternal.end() )
	{
		bRet = true;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetInSitInternal( const long clSit )
{
	if( 0 != clSit )
	{
		m_setInSITInternal.insert( clSit );
	}
}

bool
CEMSRouteEndConfig::IsInSitInternal( const long clSit )
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setInSITInternal.find( clSit );

	if( itFind != m_setInSITInternal.end() )
	{
		bRet = true;
	}

	return bRet;
}


void 
CEMSRouteEndConfig::SetAutoSitSID( const long clSID )
{
	if( 0 != clSID )
	{
		m_setAutoSID.insert( clSID );
	}
}

bool 
CEMSRouteEndConfig::IsAutoSitSID( const long clSID )
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setAutoSID.find( clSID );

	if( itFind != m_setAutoSID.end() )
	{
		bRet = true;
	}

	return bRet;
}
		
void 
CEMSRouteEndConfig::SetAutoSitInternal( const long clSit )
{
	if( 0 != clSit )
	{
		m_setAutoSITInternal.insert( clSit );
	}
}

bool 
CEMSRouteEndConfig::IsAutoSitInternal( const long clSit )
{
	bool bRet = false;

	std::set<long>::iterator itFind = m_setAutoSITInternal.find( clSit );

	if( itFind != m_setAutoSITInternal.end() )
	{
		bRet = true;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetBinarySend( const EMSRECORDTYPE ceRT, const bool cbSendBinary )
{
	std::map<EMSRECORDTYPE,bool>::iterator itFind = m_mapBinaryTable.find( ceRT );

	if( itFind == m_mapBinaryTable.end() )
	{
		m_mapBinaryTable.insert( std::pair<EMSRECORDTYPE, bool>( ceRT, cbSendBinary ) );
	}
}

bool 
CEMSRouteEndConfig::GetBinarySend( const EMSRECORDTYPE ceRT) const
{
	bool bRet = false;

	std::map<EMSRECORDTYPE,bool>::const_iterator itFind = m_mapBinaryTable.find( ceRT );

	if( itFind != m_mapBinaryTable.end() )
	{
		bRet = itFind->second;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetBinaryReceive( const EMSRECORDTYPE ceRT, const bool cbReceiveBinary )
{
	std::map<EMSRECORDTYPE,bool>::iterator itFind = m_mapBinaryRecvTable.find( ceRT );

	if( itFind == m_mapBinaryRecvTable.end() )
	{
		m_mapBinaryRecvTable.insert( std::pair<EMSRECORDTYPE, bool>( ceRT, cbReceiveBinary ) );
	}
}

bool 
CEMSRouteEndConfig::GetBinaryReceive( const EMSRECORDTYPE ceRT )
{
	bool bRet = false;

	std::map<EMSRECORDTYPE,bool>::iterator itFind = m_mapBinaryRecvTable.find( ceRT );

	if( itFind != m_mapBinaryRecvTable.end() )
	{
		bRet = itFind->second;
	}

	return bRet;
}

void 
CEMSRouteEndConfig::SetDirectCopy( const EMSDIRECTCOPYSPEC cspecDirect )
{
	_SetString( m_specDirect.wszDir, cspecDirect.wszDir );
}

void 
CEMSRouteEndConfig::SetDirectDir( const wchar_t* cwszDir )
{
	_SetString( m_specDirect.wszDir, cwszDir );
}



EMSDIRECTCOPYSPEC 
CEMSRouteEndConfig::GetDirectCopy() const
{
	EMSDIRECTCOPYSPEC specDirect;
	specDirect.wszDir = 0;

	_SetString( specDirect.wszDir, m_specDirect.wszDir );

	return specDirect;
}

void 
CEMSRouteEndConfig::SetFTP( const EMSFTPSPEC cspecFTP )
{
	_SetString( m_specFTP.wszHost, cspecFTP.wszHost );
	_SetString( m_specFTP.wszLogin, cspecFTP.wszLogin );
	_SetString( m_specFTP.wszPwd, cspecFTP.wszPwd );
	_SetString( m_specFTP.wszDir, cspecFTP.wszDir );
	m_specFTP.lPort = cspecFTP.lPort;
}

void 
CEMSRouteEndConfig::SetFTPHost( const wchar_t* cwszHost )
{
	_SetString( m_specFTP.wszHost, cwszHost );
}

void 
CEMSRouteEndConfig::SetFTPPort( const long clPort )
{
	m_specFTP.lPort = clPort;
}

void 
CEMSRouteEndConfig::SetFTPLogin( const wchar_t* cwszLogin )
{
	_SetString( m_specFTP.wszLogin, cwszLogin );
}

void 
CEMSRouteEndConfig::SetFTPPwd( const wchar_t* cwszPwd )
{
	_SetString( m_specFTP.wszPwd, cwszPwd );
}

void 
CEMSRouteEndConfig::SetFTPDir( const wchar_t* cwszDir )
{
	_SetString( m_specFTP.wszDir, cwszDir );
}

EMSFTPSPEC 
CEMSRouteEndConfig::GetFTP() const
{
	EMSFTPSPEC ftpSpec;
	memset( &ftpSpec, 0, sizeof(EMSFTPSPEC) );

	_SetString( ftpSpec.wszHost, m_specFTP.wszHost );
	_SetString( ftpSpec.wszLogin, m_specFTP.wszLogin );
	_SetString( ftpSpec.wszPwd, m_specFTP.wszPwd );
	_SetString( ftpSpec.wszDir, m_specFTP.wszDir );
	ftpSpec.lPort = m_specFTP.lPort;

	return ftpSpec;
}

void 
CEMSRouteEndConfig::SetSOAP( const EMSSOAPSPEC cspecSOAP )
{
	_SetString( m_specSOAP.wszEndpoint, cspecSOAP.wszEndpoint );
}

void 
CEMSRouteEndConfig::SetSOAPEndpoint( const wchar_t* cwszEndPoint )
{
	_SetString( m_specSOAP.wszEndpoint, cwszEndPoint );
}

EMSSOAPSPEC 
CEMSRouteEndConfig::GetSOAP() const
{
	EMSSOAPSPEC specSOAP;
	memset( &specSOAP, 0, sizeof(EMSSOAPSPEC) );

	_SetString( specSOAP.wszEndpoint, m_specSOAP.wszEndpoint );

	return specSOAP;
}

void 
CEMSRouteEndConfig::GetAlerts( unsigned long& ulAlerts, long*& alAlerts ) const
{
	ulAlerts = 0;
	alAlerts = 0;

	ulAlerts = m_setSID.size() + m_setSITInternal.size();

    if( ulAlerts > 0 )
    {
	    alAlerts = new long[ ulAlerts ];

	    if( !alAlerts )
	    {
		    THROW_NOMEMORY_EXCEPTION();
	    }

	    try
	    {
		    memset( alAlerts, 0, ulAlerts*sizeof(long) );

		    std::set<long>::const_iterator it = m_setSID.begin();

		    long lIndex = 0;
		    while( it != m_setSID.end() )
		    {
			    alAlerts[lIndex] = *it;
			    lIndex++;
			    it++;
		    }

		    it = m_setSITInternal.begin();
		    while( it != m_setSITInternal.end() )
		    {
			    alAlerts[lIndex] = *it;
			    lIndex++;
			    it++;
		    }
	    }
	    catch( ... )
	    {
		    if( alAlerts )
		    {
			    delete[] alAlerts;
			    alAlerts = 0;
		    }

		    throw;
	    }
    }

}

void 
CEMSRouteEndConfig::GetAutoAlerts( unsigned long& ulAlerts, long*& alAlerts ) const
{
	ulAlerts = 0;
	alAlerts = 0;

	ulAlerts = m_setAutoSID.size() + m_setAutoSITInternal.size();

    if( ulAlerts > 0 )
    {
	    alAlerts = new long[ ulAlerts ];

	    if( !alAlerts )
	    {
		    THROW_NOMEMORY_EXCEPTION();
	    }

	    try
	    {
		    memset( alAlerts, 0, ulAlerts*sizeof(long) );

		    std::set<long>::const_iterator it = m_setAutoSID.begin();

		    long lIndex = 0;
		    while( it != m_setAutoSID.end() )
		    {
			    alAlerts[lIndex] = *it;
			    lIndex++;
                it++;
		    }

		    it = m_setAutoSITInternal.begin();
		    while( it != m_setAutoSITInternal.end() )
		    {
			    alAlerts[lIndex] = *it;
			    lIndex++;
                it++;
		    }
	    }
	    catch( ... )
	    {
		    if( alAlerts )
		    {
			    delete[] alAlerts;
			    alAlerts = 0;
		    }

		    throw;
	    }
    }

}

void 
CEMSRouteEndConfig::SetAlertChannel( const unsigned long culChannelID )
{
	if( 0 != culChannelID )
	{
		m_setAlertChannel.insert( culChannelID );
	}
}

bool
CEMSRouteEndConfig::IsAlertChannel( const unsigned long culChannelID )
{
	bool bRet = false;

	std::set<unsigned long>::iterator itFind = m_setAlertChannel.find( culChannelID );

	if( itFind != m_setAlertChannel.end() )
	{
		bRet = true;
	}

	return bRet;
}

bool
CEMSRouteEndConfig::FilterOnAlertChannel()
{
	return (m_setAlertChannel.size() > 0);
}
