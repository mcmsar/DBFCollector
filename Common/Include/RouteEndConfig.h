/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __ROUTE_END_CONFIG_H__
#define __ROUTE_END_CONFIG_H__

#include "cacheconfig.h"
#include "igateway.h"
#include <map>
#include <set>

typedef enum eMsgType
{
	MSGTYPE_UNKNOWN = 0,
	MSGTYPE_BINARY = 1,
	MSGTYPE_SIT = 2,
	MSGTYPE_SOAP = 3,
	MSGTYPE_UDP = 4
} EMSMSGTYPE;

typedef struct tagDirectCopy
{
	wchar_t* wszDir;
} EMSDIRECTCOPYSPEC;

typedef struct tagFTP
{
	wchar_t*	wszHost;
	long		lPort;
	wchar_t*	wszLogin;
	wchar_t*	wszPwd;
	wchar_t*	wszDir;
} EMSFTPSPEC;

typedef struct tagSOAP
{
	wchar_t*	wszEndpoint;
} EMSSOAPSPEC;


//! @class CEMSRouteEndConfig
//! Stores configuration information for one end of a route.
class CEMSRouteEndConfig : public CEMSCacheConfig
{
	public:
		CEMSRouteEndConfig();
		CEMSRouteEndConfig( const CEMSRouteEndConfig& x );
		~CEMSRouteEndConfig();

		void SetRouteName( const wchar_t* cwszRoute );
		wchar_t* GetRouteName() const;

		void SetAlias( const wchar_t* cwszAlias );
		wchar_t* GetAlias() const;

		inline void SetID( const unsigned long culID ) { m_ulID = culID; }
		inline unsigned long GetID() const { return m_ulID; }

		void SetName( const wchar_t* cwszName );
		wchar_t* GetName() const;

		void SetTranslationTable( const wchar_t* cwszTable );
		wchar_t* GetTranslationTable() const;

		void SetMsgType( const EMSRESOURCEIDENTIFIER ceResource, const EMSMSGTYPE ceMsgType );
		EMSMSGTYPE GetMsgType( const EMSRESOURCEIDENTIFIER ceResource ) const;

		inline void SetMultiSit( const bool cbMulti ) { m_bMultiSit = cbMulti; }
		inline bool GetMultiSit() const { return m_bMultiSit; }

		inline void SetMaxSatellites( const unsigned long culMax ) { m_ulMaxSatellites = culMax; }
		inline unsigned long GetMaxSatellites() const { return m_ulMaxSatellites; }

		void SetSitSID( const long clSID );
		bool IsSitSID( const long clSID);

		void SetInSitSID( const long clSID );
		bool IsInSitSID( const long clSID );

		void SetSitInternal( const long clSit );
		bool IsSitInternal( const long clSit );

		void SetInSitInternal( const long clSit );
		bool IsInSitInternal( const long clSit );

		void SetAutoSitSID( const long clSID );
		bool IsAutoSitSID( const long clSID );
		
		void SetAutoSitInternal( const long clSit );
		bool IsAutoSitInternal( const long clSit );

		void SetBinarySend( const EMSRECORDTYPE ceRT, const bool cbSendBinary );
		bool GetBinarySend( const EMSRECORDTYPE ceRT) const;

		void SetBinaryReceive( const EMSRECORDTYPE ceRT, const bool cbReceiveBinary );
		bool GetBinaryReceive( const EMSRECORDTYPE ceRT );

		void SetDirectCopy( const EMSDIRECTCOPYSPEC cspecDirect );
		void SetDirectDir( const wchar_t* cwszDir );
		EMSDIRECTCOPYSPEC GetDirectCopy() const;

		void SetFTP( const EMSFTPSPEC cspecFTP );
		void SetFTPHost( const wchar_t* cwszHost );
		void SetFTPPort( const long clPort );
		void SetFTPLogin( const wchar_t* cwszLogin );
		void SetFTPPwd( const wchar_t* cwszPwd );
		void SetFTPDir( const wchar_t* cwszDir );
		EMSFTPSPEC GetFTP() const;

		void SetSOAP( const EMSSOAPSPEC cspecSOAP );
		void SetSOAPEndpoint( const wchar_t* cwszEndPoint );
		EMSSOAPSPEC GetSOAP() const;

		inline void SetUseSecurityToken( const bool cbUse ) { m_bUseSecurityToken = cbUse; }
		inline bool GetUseSecurityToken() { return m_bUseSecurityToken; }

		void GetAlerts( unsigned long& ulAlerts, long*& alAlerts ) const;
		void GetAutoAlerts( unsigned long& ulAlerts, long*& alAlerts ) const;

		inline void SetMaxAlertsPerMessage( const unsigned long culMax ) { m_ulMaxAlertsPerMsg = culMax; }
		inline unsigned long GetMaxAlertsPerMessage() { return m_ulMaxAlertsPerMsg; }

		bool FilterOnAlertChannel();
		void SetAlertChannel( const unsigned long culChannelID );
		bool IsAlertChannel( const unsigned long culChannelID );

		inline void SetReportSourceChannel( const bool cbReportSourceChannel ) { m_bReportSourceChannel = cbReportSourceChannel; }
		inline bool GetReportSourceChannel() const { return m_bReportSourceChannel; }

	private:	// methods

	private:	// data
		wchar_t*									m_wszRouteName;
		unsigned long								m_ulID;
		wchar_t*									m_wszName;
		wchar_t*									m_wszTranslationTable;
		std::map<EMSRESOURCEIDENTIFIER, EMSMSGTYPE>	m_mapResourceMsgTypeTable;
		bool										m_bMultiSit;
		unsigned long								m_ulMaxSatellites;
		std::map<EMSRECORDTYPE, bool>				m_mapBinaryTable;
		std::map<EMSRECORDTYPE, bool>				m_mapBinaryRecvTable;
		std::set<long>								m_setSID;
		std::set<long>								m_setSITInternal;
		std::set<long>								m_setAutoSID;
		std::set<long>								m_setAutoSITInternal;
		std::set<long>								m_setInSID;
		std::set<long>								m_setInSITInternal;
		EMSDIRECTCOPYSPEC							m_specDirect;
		EMSFTPSPEC									m_specFTP;
		EMSSOAPSPEC									m_specSOAP;
		bool										m_bUseSecurityToken;
		unsigned long								m_ulMaxAlertsPerMsg;
		wchar_t*									m_wszAlias;
		bool										m_bReportSourceChannel;
		std::set<unsigned long>						m_setAlertChannel;
};

#endif // __ROUTE_END_CONFIG_H__

	