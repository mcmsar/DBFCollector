/********************************************************************
*	Module:			EMSCharMapFStrm.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*			A standard file stream that will, optionally, remap
*			characters before writing.
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
*					All rights reserved
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
********************************************************************/
#include <stdio.h>
#include <tchar.h>

#include "emscharmapfstrm.h"
#include "emserror.h"

EMS_RESULT
CEMSCharMapFileStream::Init( LPCTSTR szCharMapFilename )
{
	EMS_RESULT	hr = EMS_OK;
	if ( szCharMapFilename && _tcslen( szCharMapFilename ) )
	{
		hr = m_CharMap.LoadMap( szCharMapFilename );
		if ( SUCCEEDED(hr) )
		{
			m_bHasMap = true;
		}
	}
	return hr;
}

// 
STDMETHODIMP CEMSCharMapFileStream::Write( const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT	hr = EMS_OK;

	if ( m_bHasMap )
	{
		BYTE*	aby = new BYTE[cb];
		memcpy( aby, pv, cb );

#ifdef UNICODE
		m_CharMap.RemapString( (wchar_t*)aby, cb );
#else
		m_CharMap.RemapString( (char*)aby, cb );
#endif

		hr = CEMSFileStream::Write( aby, cb, pcbWritten );
	}
	else
	{
		hr = CEMSFileStream::Write( pv, cb, pcbWritten );
	}
	return hr;
}
