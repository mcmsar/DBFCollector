/********************************************************************
*	Module:			emsit750.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit750A  Class
*						LUT Command
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
#ifndef INC_EMSIT750
#define INC_EMSIT750

#include "emssit.h"

#define EMS_SIT750A_MAX_COMMANDS ( 999 )

class CEMSSit750A : public CEMSSitMessageBase
{
public:
	CEMSSit750A();
	virtual ~CEMSSit750A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

	inline int GetCmdCount( void ) { return m_nCmdCount; }
	inline void SetCmdCount( int nCount ) { m_nCmdCount = nCount; }

	int GetCmdLine( int nIndex, LPTSTR lpszBuffer, int nMaxLength );
	EMS_RESULT SetCmdLine( int nIndex, LPCTSTR lpcszBuffer );
	EMS_RESULT AddCmdLine( LPCTSTR lpcszBuffer );

private: // methods
	EMS_RESULT _ParseCmdLine( CEMSSitTokenizer *lpTokenizer, int nIndex );

private:	// data
	int		m_nCmdCount;	// 3 digits
	LPTSTR	m_lpszCmds[ EMS_SIT750A_MAX_COMMANDS ];
};

#endif // INC_EMSIT750
