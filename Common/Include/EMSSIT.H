/********************************************************************
*	Module:			emssit.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of SIT Message Classes
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
* Copyright (c) 2001-2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5		rvw		start
		2005Jan07		CH		Moved error codes to EMSErrorMsgs.mc
								These can now be accessed via messages.h

********************************************************************/
#ifndef INC_EMSSIT
#define INC_EMSSIT

#include "emstypes.h"
#include "emspipe.h"
#include "emserror.h"
#include "emstime.h"
#include "sittypes.h"
#include "lineterminator.h"
#include "sitformatclass.h"

#define EMS_MAX_SIT_LINE_LENGTH ( 69 )		// bytes
#define EMS_MAX_SIT_MSG_LENGTH ( 32000 )		// bytes

#define EMS_DEFAULT_SIT_LINE_SIZE ( 72 )	// Number of bytes in a msg line including carriage return and line feed.
#define EMS_DEFAULT_SIT_HEADER_LINES ( 2 )	// Number of lines in an alert message header.
#define EMS_DEFAULT_SIT_TRAILER_LINES ( 2 )	// Number of lines in an alert message trailer.
#define EMS_DEFAULT_SIT_LINES_RECORD ( 1 )	// Number of lines per record.

#define EMS_DEFAULT_MAX_LINES_PER_ALERT ( 7 )


typedef ULONG EMSSITCODE;

typedef struct tagEMSSITFIELD
{
	int nLength;
	TCHAR szText[ EMS_MAX_SIT_LINE_LENGTH + 3 ];
} EMSSITFIELD, *LPEMSSITFIELD;

class CEMSSitTokenizer;

class CEMSSitMessageBase
{
public:
	CEMSSitMessageBase();
	virtual ~CEMSSitMessageBase();

	EMS_RESULT Generate( IEMSSeqStream *lpStream );
	EMS_RESULT GenerateSit( IEMSSeqStream *lpStream );

	inline void SetCurrentMsgNumber( int nMsgNumber ) { m_nCurrMsgNumber = nMsgNumber; }		
	inline int GetCurrentMsgNumber( void ) { return m_nCurrMsgNumber; }
	inline void SetLastMsgNumber( int nMsgNumber ) { m_nLastMsgNumber = nMsgNumber; }		
	inline int GetLastMsgNumber( void ) { return m_nLastMsgNumber; }
	inline void SetReportingMCC( int nMCC ) { m_nReportingMCC = nMCC; }		
	inline int GetReportingMCC( void ) { return m_nReportingMCC; }
	inline void SetSitNumber( int nNumber ) { if ( nNumber) m_nSitNumber = nNumber; }
	inline int GetSitNumber( void ) { return m_nSitNumber; }
	inline void SetSitCode( EMSSITCODE sitCode ) { m_sitCode = sitCode; }
	inline EMSSITCODE GetSitCode( void ) { return m_sitCode; }
	LPCTSTR GetSitCodeStr( void );
	inline void SetSitDestination( int nNumber ) { m_nSitDestination = nNumber; }
	inline int GetSitDestination( void ) { return m_nSitDestination; }

	inline void SetHiResTime( BOOL bHiRes=TRUE ) { m_bUseHiResTime = bHiRes; }

	EMSTIME GetTransmitTime( void ) { return m_timeTransmit; }
	void SetTransmitTime( EMSTIME timeTransmit ) { m_timeTransmit = timeTransmit; }

	virtual void SetMsgHeader( CEMSSitMessageBase *lpSitMsg );
	virtual EMS_RESULT GenerateMsgHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateNewSit( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitTrailer( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateMsgTrailer( IEMSSeqStream *lpStream );

	EMS_RESULT ParseMsgStart( CEMSSitTokenizer *lpTokenizer );

	virtual EMS_RESULT ParseMsgHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitTrailer( CEMSSitTokenizer *lpTokenizer, BOOL *lpbLastSit=0 );
	virtual EMS_RESULT ParseMsgTrailer( CEMSSitTokenizer *lpTokenizer );

	virtual void Reset( void );

	inline void SetMaxLineSize( int nMaxLineSize ) { m_nMaxLineSize = nMaxLineSize; }
	inline int GetMaxLineSize( void ) { return m_nMaxLineSize; }
	inline void SetHeaderLines( int nHeaderLines ) { m_nHeaderLines = nHeaderLines; }
	inline int GetHeaderLines( void ) { return m_nHeaderLines; }
	inline void SetTrailerLines( int nTrailerLines ) { m_nTrailerLines = nTrailerLines; }
	inline int GetTrailerLines( void ) { return m_nTrailerLines; }
	inline void SetMaxMsgSize( int nMaxMsgSize ) { m_nMaxMsgSize = nMaxMsgSize; }
	inline int GetMaxMsgSize( void ) { return m_nMaxMsgSize; }
	inline void SetMaxLinesPerRecord( int nMaxLPR ) { m_nMaxLinesPerRecord = nMaxLPR; }
	inline int GetMaxLinesPerRecord( void ) { return m_nMaxLinesPerRecord; }

	int GetMaxRecordCount( void );

	inline void SetAutoSend( BOOL bAutoSend ) { m_bAutoSend = bAutoSend; }
	inline BOOL GetAutoSend( void ) { return m_bAutoSend; }

	virtual EMSSITFORMATCLASS GetFormatClass() { return SIT_FMT_CLASS_SIT; }

protected:	// methods 
	EMS_RESULT WriteLine( IEMSSeqStream *lpStream, LPCTSTR lpcszLine );
	EMS_RESULT ReadSitLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITFIELD lpFld, int nMax, int *lpnCount );
	EMS_RESULT ReadSitLine( CEMSSitTokenizer *lpTokenizer,  LPTSTR lpszBuffer, int nMax, int *lpnLength );
	EMS_RESULT UnReadSitLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITFIELD lpFld, int nCount );

	virtual int _GetMaxSitLineLength() { return EMS_MAX_SIT_LINE_LENGTH; }

private: // methods
	void _Reset( void );

protected:	// data
	int			m_nMaxLineSize;
	int			m_nHeaderLines;
	int			m_nTrailerLines;
	int			m_nMaxMsgSize;
	int			m_nMaxLinesPerRecord;

private: // data
	int 		m_nCurrMsgNumber;
	int 		m_nLastMsgNumber;
	int		m_nReportingMCC;
	CEMSTime	m_timeTransmit;
	int		m_nSitNumber;
	EMSSITCODE	m_sitCode;
	TCHAR		m_szSitCodeStr[16];
	int 		m_nSitDestination;
	int		m_nUnreadValue;
	BOOL		m_bUseHiResTime;
	BOOL		m_bAutoSend;

	CEMSLineTerminator m_LT;
};

class CEMSSitAlertMessageBase : public CEMSSitMessageBase
{
public:
	CEMSSitAlertMessageBase();
	virtual ~CEMSSitAlertMessageBase();

	virtual void Reset( void );

	virtual EMS_RESULT AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln );

	inline void SetAlertCount( int nCount ) { m_nAlertCount = nCount; }
	inline int GetAlertCount( void ) { return m_nAlertCount; }
	inline int IncrAlertCount( void ) { return ++m_nAlertCount; }
	inline void SetMaxAlertCount( int nCount ) { m_nMaxAlertCount = nCount; }	// This is obsolete.
	int GetMaxAlertCount( void );

	inline int GetSatelliteID( void ) { return m_nSatID; }
	inline void SetSatelliteID( int nNumber ) { m_nSatID = nNumber; }
	inline int GetPassID( void ) { return m_nPass; }
	inline void  SetPassID( int nNumber ) { m_nPass = nNumber; }

	EMS_RESULT GetSolution( LPEMSSITLOCALERTSOLUTION lpSoln, int nIndex );

protected: // methods
	LPEMSSITLOCALERTSOLUTION _GetSolutionPtr( int nIndex );
	int _AllocSolutions( int nCount );
	unsigned long _GetReportingMCC();

private: // data
	int 		m_nAlertCount;
	int 		m_nMaxAlertCount;
	int		m_nSatID;
	int		m_nPass;
	LPEMSSITLOCALERTSOLUTION	m_lpSoln;
	int							m_nAllocCount;
};

#endif // INC_EMSSIT
