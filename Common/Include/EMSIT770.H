/********************************************************************
*	Module:			emsit770.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit770A  Class
*						Data Report Message
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
	0.1 2003 Mar 6   Lguan	add parse code

********************************************************************/

#ifndef INC_EMSIT770
#define INC_EMSIT770

#include "emssit.h"

#define EMSSIT770A_MAX_MSGS ( 999 )
#define EMSSIT770A_MAX_TEXT_LEN ( 69 )

#define EMS_LINES_PER_LOG_RECORD ( 1 )

typedef struct tagEMSSIT770AMSG
{
	TCHAR szText[ EMSSIT770A_MAX_TEXT_LEN  + 1 ];
} EMSSIT770AMSG, *LPEMSSIT770AMSG;

class CEMSSit770A : public CEMSSitMessageBase
{
public:
	CEMSSit770A();
	virtual ~CEMSSit770A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual void Reset( void );

	inline int GetMsgCount( void ) { return m_nMsgCount; }
	inline void GetMsgCount( int nCount ) { m_nMsgCount = nCount; }

	LPCTSTR GetMsg( int nIndex );
	EMS_RESULT AddMsg( LPCTSTR lpcszMsg );

	int	GetMaxAddMsgLen();
private:
	
	EMS_RESULT _ParseMsgLine( CEMSSitTokenizer *lpTokenizer, int nIndex );
	
	// data
	int 					m_nMsgCount;
	int 					m_nAllocCount;
	LPEMSSIT770AMSG		    m_lpMsg;
};

#endif // INC_EMSIT770

