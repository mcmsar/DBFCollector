/******************************************************************** 
*	Module:			emslocal.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSLocale - Localization Support Object Definition(s)
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
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

	0.0	2001/06/01	rvw	start

********************************************************************/

#ifndef INC_EMSLOCAL
#define INC_EMSLOCAL

#include "emstypes.h"
#include "emserror.h"

class CEMSLocale
{
public:
	CEMSLocale( LPCTSTR lpcszFilespec=0, WORD wLangID = 0x0 );
	~CEMSLocale();

	EMS_RESULT Initialize( LPCTSTR lpcszFilespec=0, WORD wLangID = 0x0 );
	void UnInitialize( void );

	int SetFilespec( LPCTSTR lpcszFilespec );
	int LoadString( UINT unID, LPTSTR lpszBuffer, int nBufferMax, WORD wLangID = 0x0 );

	inline EMS_RESULT GetLastError( void ) { return m_lastError; }

	BOOL IsValid( void );

private: // methods
	BOOL _LanguageSuffix( LPTSTR lpszExt, int nMaxLength, WORD wLanguageID );
	BOOL _SelectLanguageSuffix( LPTSTR lpszExt, int nMaxLength, LPWORD lpwLanguageID );
	HANDLE _LoadLibrary( LPWORD lpwLanguageID );

private : // data
	HANDLE 	m_hResHandle;
	LPTSTR	m_lpszResFilespec;
	WORD		m_wDesiredLanguageID;
	WORD		m_wCurrentLanguageID;
	BOOL		m_bInitialized;
	EMS_RESULT	m_lastError;
};

#endif // INC_EMSLOCAL
