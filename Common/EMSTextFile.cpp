/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/


#ifdef __EMS_USING_MFC__
#include <afxdisp.h>
#else
#include <windows.h>
#endif

#include "EMSTextFile.h"


CEMSTextFile::CEMSTextFile(): m_lpFile(NULL)
{
}

CEMSTextFile::~CEMSTextFile()
{
	Close();
}

bool 
CEMSTextFile::OpenTextFile( const char* szFileName, const char* szMode )
{
	bool bRet = false;

	if( szFileName && strlen( szFileName ) > 0 )
	{
		m_szFileName = szFileName;
		if( m_lpFile )
		{
			fclose( (FILE*)m_lpFile );
			m_lpFile = 0;
		}

		m_lpFile = fopen( szFileName, szMode );
			

		if( m_lpFile )
		{
			bRet = true;
		}
	}

	return bRet;
}

void
CEMSTextFile::Close()
{
	if ( m_lpFile )
	{
		fclose( (FILE*)m_lpFile );
		m_lpFile = 0;
	}
}

bool
CEMSTextFile::WriteText( const char* szText )
{
	bool bRet = false;

	if( !m_lpFile )
	{
		std::string szFile = m_szFileName;
		OpenTextFile( szFile.c_str(), "w" );
	}

	if( m_lpFile )
	{
		if( fwrite( szText, 1, strlen(szText), m_lpFile ) == strlen(szText) )
		{
			bRet = true;
		}
	}
	
	return bRet;
}
