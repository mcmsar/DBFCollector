/********************************************************************
*	Module:			emsit605.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit605,
*						CEMSSit605A, CEMSSit605B, CEMSSit605C, CEMSSit605D
*						LUT Messages
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT605
#define INC_EMSIT605

#include "emssit.h"

#define EMSSIT605A_MAX_MSGS ( 999 )
#define EMSSIT605_TYPE_LEN	( 2 )
#define EMSSIT605_SOURCE_LEN ( 16 )
#define EMSSIT605_STATUS_LEN ( 8 )

typedef struct tagEMSSIT605LINE
{
	TCHAR szText [ EMS_MAX_SIT_LINE_LENGTH + 1 ];
} EMSSIT605LINE, *LPEMSSIT605LINE;

typedef struct tagEMSSIT605ASTATUS
{
	TCHAR szType[ EMSSIT605_TYPE_LEN	+1];
	TCHAR szSource[ EMSSIT605_SOURCE_LEN +1];
	TCHAR szStatus[ EMSSIT605_STATUS_LEN +1];
} EMSSIT605ASTATUS, *LPEMSSIT605ASTATUS;

class CEMSSit605 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit605();
	virtual ~CEMSSit605();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	int GetLineCount( void ) { return m_nLineCount; }

protected: // methods
	EMS_RESULT _GetLine( int nIndex, LPEMSSIT605LINE lpLine, int nLength = sizeof(EMSSIT605LINE) ); 
	EMS_RESULT _AddLine( LPEMSSIT605LINE lpLine, int nLength = sizeof(EMSSIT605LINE) ); 

private:	// data
	int 					m_nLineCount;
	int 					m_nAllocCount;
	LPEMSSIT605LINE	m_lpLine;
};

class CEMSSit605A : public CEMSSitAlertMessageBase
{
public:
	CEMSSit605A();
	virtual ~CEMSSit605A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	inline int  GetLineCount( void ) { return m_nLineCount; }
	void        SetLineCount( int nLineCount ) { m_nLineCount = nLineCount; }

	EMS_RESULT GetStatus( LPEMSSIT605ASTATUS lpStatus, int nIndex );	
	EMS_RESULT AddStatus( LPEMSSIT605ASTATUS lpStatus );

protected:

   virtual EMS_RESULT _ParseSatInfoLine( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParseStatusInfoLine( CEMSSitTokenizer* lpTokenizer, LPEMSSIT605ASTATUS lpLine );

   int _AllocLines( int nCount );
	LPEMSSIT605ASTATUS _GetLinePtr( int nIndex );

private:	// data
	int 						m_nLineCount;
	int 						m_nAllocCount;
	LPEMSSIT605ASTATUS	m_lpLine;
};

class CEMSSit605B : public CEMSSit605A
{
public:
	CEMSSit605B();
	virtual ~CEMSSit605B();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	void SetSource( LPCSTR lpszSource );
	void SetMsg( LPCSTR lpszMsg );

//	inline LPCTSTR GetMsg( void ) { return (LPCTSTR)m_szMsg; }
	inline LPCTSTR GetMsg( void ) { return (LPCTSTR)m_lpszMsg; }
	inline LPCTSTR GetSource( void ) { return (LPCTSTR)m_szSource; }

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

private:

   virtual EMS_RESULT _ParseSourceNameLine( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParseMessageTextLine_s( CEMSSitTokenizer* lpTokenizer );

private:	// data
	TCHAR				m_szSource[ EMSSIT605_SOURCE_LEN + 1 ];
//	TCHAR				m_szMsg[ EMSSIT605_MSG_LEN + 1];
	TCHAR				*m_lpszMsg;
};

class CEMSSit605C : public CEMSSit605B
{
public:
	CEMSSit605C();
	virtual ~CEMSSit605C();

	virtual void Reset( void );
};

class CEMSSit605D : public CEMSSitAlertMessageBase
{
public:
	CEMSSit605D();
	virtual ~CEMSSit605D();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );
};

#define EMSIPADDRESSLENGTH 15

typedef struct tagEMSIPSTATUS
{
	TCHAR szIPAddress[ EMSIPADDRESSLENGTH + 1 ];
	TCHAR cState;
	TCHAR cConnType;
} EMSIPSTATUS, *PEMSIPSTATUS;

//! IP Address status notification message.
class CEMSSit605E : public CEMSSitAlertMessageBase
{
public:
	CEMSSit605E();
	virtual ~CEMSSit605E();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	inline int  GetLineCount( void ) { return m_nLineCount; }
	void        SetLineCount( int nLineCount ) { m_nLineCount = nLineCount; }

	EMS_RESULT GetStatus( PEMSIPSTATUS pStatus, int nIndex );	
	EMS_RESULT AddStatus( PEMSIPSTATUS pStatus );

protected:
	virtual EMS_RESULT _ParseStatusInfoLine( CEMSSitTokenizer* lpTokenizer, PEMSIPSTATUS pLine );

	int _AllocLines( int nCount );
	PEMSIPSTATUS _GetLinePtr( int nIndex );

private:	// data
	int 						m_nLineCount;
	int 						m_nAllocCount;
	PEMSIPSTATUS				m_pLine;
};

#endif // INC_EMSIT605

