#ifndef __GATEWAY_CMD_H__
#define __GATEWAY_CMD_H__

#include "igateway.h"
#include "commandformats.h"

class CEMSCommandProcessor;
class CEMSCommandSource;
interface IEMSCommandChannel;

typedef enum tagGtwyCmdResponses
{
	GTWY_RESP_UKNOWN = 0,
	GTWY_RESP_LPC_INIT_DATA_DONE = 1,
	GTWY_RESP_LPC_PROCESS406_DATA_DONE = 2,
	GTWY_RESP_LPC_GET_FILENAMES_DONE = 3,
	GTWY_RESP_GENERIC = 4,
	GTWY_RESP_DAL_GET = 5
} EMSGTWYRESPONSE;

//! @class CEMSGatewayCmd
//! This class is used for creating and reading commands sent by and to the Gateway over the 
//! EMSPipeline.
class CEMSGatewayCmd
{
	public:
		CEMSGatewayCmd();
		CEMSGatewayCmd( const CEMSGatewayCmd& x );
		~CEMSGatewayCmd();

		inline void SetResponseType( const EMSGTWYRESPONSE ceResponse ) { m_eRespType = ceResponse; }
		inline EMSGTWYRESPONSE GetResponseType() const { return m_eRespType; }

		inline void SetSessionID( const unsigned long culSessionID ) { m_ulSessionID = culSessionID; }
		inline unsigned long GetSessionID( ) const { return m_ulSessionID; }

		inline void SetReturnStatus( const EMS_RESULT chrStatus ) { m_hrStatus = chrStatus; }
		inline EMS_RESULT GetReturnStatus() const { return m_hrStatus; }

		inline void SetTotalRecords( const unsigned long culTotalRecs ) { m_ulTotalRecords = culTotalRecs; }
		inline unsigned long GetTotalRecords() const { return m_ulTotalRecords; }

		inline void SetRecordSize( const unsigned long culRecordSize ) { m_ulRecordSize = culRecordSize; }
		inline unsigned long GetRecordSize() const { return m_ulRecordSize; }

		inline void SetCacheOverflow( const bool cbOverflow ) { m_bOverflow = cbOverflow; }
		inline bool GetCacheOverflow() const { return m_bOverflow; }

		inline void SetCacheID( const EMSDALCACHEID cCacheID ) { m_cacheID = cCacheID; }
		inline EMSDALCACHEID GetCacheID() const { return m_cacheID; }
		
		TCHAR* SerializeResponse() const;
		void SendResponse();
		void DeserializeResponse( CEMSCommandProcessor* pCmdProcessor );

	private:	// methods
		CEMSCommandSource*	_GetCommandSource();
		IEMSCommandChannel*	_GetCommandChannel();

	private:	// data
		EMSGTWYRESPONSE m_eRespType;
		EMS_RESULT		m_hrStatus;

		CEMSCommandSource*	m_pCmdSrc;
		IEMSCommandChannel*	m_pCmdChannel;

		// For LPC
		unsigned long m_ulSessionID;

		// For DAL
		unsigned long m_ulTotalRecords;
		unsigned long m_ulRecordSize;
		bool m_bOverflow;
		EMSDALCACHEID m_cacheID;
};


#endif // __GATEWAY_CMD_H__