/********************************************************************
*	Module:			sittoken.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of SIT Tokeniser Classe
*
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#ifndef INC_SITTOKEN
#define INC_SITTOKEN

#include "emstypes.h"
#include "emspipe.h"
#include "emserror.h"
#include "emstime.h"
#include "emssit.h"
#include "lineterminator.h"
#include <string>

#define EMS_MAX_SIT_FIELDS_UNREAD ( 16 )		

class CEMSSitTokenizer
{
public:
	CEMSSitTokenizer( IEMSSeqStream *lpStream = 0 );
	virtual ~CEMSSitTokenizer();

	void SetStream( IEMSSeqStream *lpStream );

	EMS_RESULT ReadLine( LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount ); 
	EMS_RESULT ReadField( LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount );
	EMS_RESULT ReadChar( TCHAR *lpcValue );
	EMS_RESULT UnReadChar( TCHAR cValue );
	EMS_RESULT UnReadField( LPTSTR lpszBuffer, ULONG ulLen );
	void ResetUnReadFields( void );
	EMS_RESULT ReadAllText( std::string& roszAll );

private: // methods		
	EMS_RESULT _FlushEOL( void );
	EMS_RESULT _AppendChar( int nByte, LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount );

private: // data
	int		m_nUnreadValue;
//	int		m_nUnreadFieldLen;
//	TCHAR		m_szUnreadFieldValue[ EMS_MAX_SIT_LINE_LENGTH + 2 ];
	IEMSSeqStream *m_lpStream;
	int		m_nUnreadCount;
	EMSSITFIELD m_unreadFld[ EMS_MAX_SIT_FIELDS_UNREAD ];
	CEMSLineTerminator m_LT;
};

#endif // INC_SITTOKEN

