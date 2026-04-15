/********************************************************************
*	Module:			EMSFList.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSFileList class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
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

	0.0	2002/11/2	rvw	start

********************************************************************/
#include <windows.h>
#include <tchar.h>

#include "emsflist.h"
#include "emstime.h"
#include "RouteConfigConstants.h"

typedef struct _tagEMSFILELISTLINK
{
	long lSortIndex;
	WIN32_FIND_DATA findData;
	_tagEMSFILELISTLINK *lpNext;
	_tagEMSFILELISTLINK *lpPrev;
} EMSFILELISTLINK, *LPEMSFILELISTLINK;

CEMSFileList::CEMSFileList( LPCTSTR lpcszSearch, BOOL bSort )
{
	m_nCount = 0;
	m_lpLinkedList = 0;
	m_lpIndex = 0;

	if ( lpcszSearch && *lpcszSearch )
		Initialize( lpcszSearch, bSort );
}

CEMSFileList::~CEMSFileList()
{
	Reset();
}

EMS_RESULT CEMSFileList::Reset( void )
{
	if ( m_lpLinkedList )
	{
		LPEMSFILELISTLINK lpLink = (LPEMSFILELISTLINK)m_lpLinkedList, lpDelete=0;

		while ( lpLink )
		{
			lpDelete = lpLink;

			lpLink = lpLink->lpNext;

			delete lpDelete;
		}
		m_lpLinkedList = 0;
	}

	if ( m_lpIndex )
	{
		delete [ ] ((LPEMSFILELISTLINK*)m_lpIndex);
		m_lpIndex = 0;
	}

	m_nCount = 0;

	return EMS_OK;
}

EMS_RESULT CEMSFileList::Initialize( LPCTSTR lpcszSearch, BOOL bSort )
{
	EMS_RESULT hr = EMS_OK;
	LPEMSFILELISTLINK lpRoot = 0, lpLink = 0, lpPrev=0;
	HANDLE hFindFile;
	WIN32_FIND_DATA findData;

	Reset();

	hFindFile = FindFirstFile( lpcszSearch, &findData );

	while ( hFindFile != INVALID_HANDLE_VALUE )
	{
		if ( ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
		{
			lpLink = new EMSFILELISTLINK;

			if ( lpLink )
			{
				memset( lpLink, 0, sizeof( EMSFILELISTLINK ) );

				lpLink->findData = findData; 

				lpLink->lpPrev = lpPrev;

				if ( !lpRoot )
					lpRoot = lpLink;

				if ( lpPrev )
					lpPrev->lpNext = lpLink;

				lpPrev = lpLink;
			}

			m_nCount++;
		}

		if ( !FindNextFile( hFindFile, &findData ))
		{
			FindClose( hFindFile );

			hFindFile = INVALID_HANDLE_VALUE;
		}
	}

	m_lpLinkedList = lpRoot;

	if ( lpRoot && m_nCount )
	{
		LPEMSFILELISTLINK *lpIndex = new LPEMSFILELISTLINK[ m_nCount ], lpThis=(LPEMSFILELISTLINK)lpRoot;

		if ( lpIndex )
		{
			int i = 0;

			memset( lpIndex, 0, sizeof( LPEMSFILELISTLINK ) * m_nCount );

			while ( lpThis )
			{
				lpIndex[ i++ ] = lpThis;
				lpThis = lpThis->lpNext;
			}
		}
		m_lpIndex = lpIndex;
	}

	if ( bSort && m_nCount ) 
		hr = Sort();

	return hr;
}

EMS_RESULT CEMSFileList::InitializeEx( LPCTSTR lpcszSearch, BOOL bSort )
{
	EMS_RESULT hr = EMS_OK;
	LPEMSFILELISTLINK lpRoot = 0, lpLink = 0, lpPrev=0;
	HANDLE hFindFile;
	WIN32_FIND_DATA findData;

	Reset();

	hFindFile = FindFirstFile( lpcszSearch, &findData );

	while ( hFindFile != INVALID_HANDLE_VALUE )
	{
		if ( ( findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) == 0 )
		{
			lpLink = new EMSFILELISTLINK;

			if ( lpLink )
			{
				memset( lpLink, 0, sizeof( EMSFILELISTLINK ) );

				lpLink->findData = findData; 

				lpLink->lpPrev = lpPrev;

				lpLink->lSortIndex = _extractSequenceNumber(findData.cFileName);

				if ( !lpRoot )
					lpRoot = lpLink;

				if ( lpPrev )
					lpPrev->lpNext = lpLink;

				lpPrev = lpLink;
			}

			m_nCount++;
		}

		if ( !FindNextFile( hFindFile, &findData ))
		{
			FindClose( hFindFile );

			hFindFile = INVALID_HANDLE_VALUE;
		}
	}

	m_lpLinkedList = lpRoot;

	if ( lpRoot && m_nCount )
	{
		LPEMSFILELISTLINK *lpIndex = new LPEMSFILELISTLINK[ m_nCount ], lpThis=(LPEMSFILELISTLINK)lpRoot;

		if ( lpIndex )
		{
			int i = 0;

			memset( lpIndex, 0, sizeof( LPEMSFILELISTLINK ) * m_nCount );

			while ( lpThis )
			{
				lpIndex[ i++ ] = lpThis;
				lpThis = lpThis->lpNext;
			}
		}
		m_lpIndex = lpIndex;
	}

	if ( bSort && m_nCount ) 
		hr = SortEx();

	return hr;
}

EMS_RESULT CEMSFileList::Sort( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nCount && m_lpLinkedList && m_lpIndex )
	{
		BOOL bChanged = TRUE;
		LPEMSFILELISTLINK *lpIndex = (LPEMSFILELISTLINK*)m_lpIndex, lpLink=0;

		while ( bChanged )
		{
			bChanged = FALSE;

			for ( int i = 0; i < m_nCount - 1; i++ )
			{
				if ( lstrcmpi( GetFileName( i ) , GetFileName( i + 1 ) ) > 0 ) 
				{
					lpLink = lpIndex[i];

					lpIndex[ i ] = lpIndex[ i + 1 ];

					lpIndex[ i + 1 ] = lpLink;
					
					bChanged = TRUE;
				}
			}
		}
	}

	return hr;
}
 
EMS_RESULT CEMSFileList::SortEx( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nCount && m_lpLinkedList && m_lpIndex )
	{
		BOOL bChanged = TRUE;
		LPEMSFILELISTLINK *lpIndex = (LPEMSFILELISTLINK*)m_lpIndex, lpLink=0;

		while ( bChanged )
		{
			bChanged = FALSE;

			for ( int i = 0; i < m_nCount - 1; i++ )
			{
				if( lpIndex[ i ]->lSortIndex > lpIndex[ i + 1 ]->lSortIndex ) 
				{
					lpLink = lpIndex[i];

					lpIndex[ i ] = lpIndex[ i + 1 ];

					lpIndex[ i + 1 ] = lpLink;
					
					bChanged = TRUE;
				}
			}
		}

		long lSortIndexDelta = lpIndex[ m_nCount - 1 ]->lSortIndex -
				lpIndex[ 0 ]->lSortIndex;
		long lNinetyPercent = ((clMaxBinMsgSequenceNumber / 10)*9);

		if( lSortIndexDelta > lNinetyPercent )
		{
			bChanged = TRUE;

			while ( bChanged )
			{
				bChanged = FALSE;

				for ( int i = 0; i < m_nCount - 1; i++ )
				{
					if( (lpIndex[ i ]->lSortIndex + lNinetyPercent ) <
						lpIndex[ i + 1 ]->lSortIndex ) 
					{
						lpLink = lpIndex[i];

						lpIndex[ i ] = lpIndex[ i + 1 ];

						lpIndex[ i + 1 ] = lpLink;
						
						bChanged = TRUE;
					}
				}
			}


		}
	}

	return hr;
}

long
CEMSFileList::_extractSequenceNumber( LPCTSTR lpszFileName )
{
	long lRetVal = -1;

	TCHAR szNumber[ 32 ]="", szFileName[ 256 ] = "";

	LPTSTR lpszToken = 0;
	int nToken = 0;

	lstrcpy( szFileName, lpszFileName );
	lpszToken = _tcstok( szFileName, TEXT("_") );

	while ( lpszToken )
	{
		switch ( nToken++ )
		{
			case 0:	break;
			case 1:	break;
			case 2:	lstrcpy( szNumber, lpszToken ); break;
		}
		lpszToken = _tcstok( 0, TEXT("_") );
	}

	lRetVal = atol( szNumber );

	return lRetVal;
}

LPCTSTR CEMSFileList::GetFileName( int nIndex )
{
	LPTSTR lpszFileName = 0;

	if ( ( nIndex < m_nCount ) && m_lpLinkedList && m_lpIndex )
	{
		LPEMSFILELISTLINK *lpIndex = ( LPEMSFILELISTLINK *)m_lpIndex;

		lpszFileName = lpIndex[ nIndex ]->findData.cFileName;
	}

	return (LPCTSTR)lpszFileName;
}

DWORD CEMSFileList::GetFileSize( int nIndex )
{
	DWORD dwFileSize=0;

	if ( ( nIndex < m_nCount ) && m_lpLinkedList && m_lpIndex )
	{
		LPEMSFILELISTLINK *lpIndex = ( LPEMSFILELISTLINK *)m_lpIndex;

		dwFileSize = lpIndex[ nIndex ]->findData.nFileSizeLow;
	}

	return dwFileSize;
}

EMSTIME CEMSFileList::GetFileLastWriteTime( int nIndex )
{
	CEMSTime timeLastWritten;

	if ( ( nIndex < m_nCount ) && m_lpLinkedList && m_lpIndex )
	{
		LPEMSFILELISTLINK *lpIndex = ( LPEMSFILELISTLINK *)m_lpIndex;
		FILETIME fileTime = lpIndex[ nIndex ]->findData.ftLastWriteTime;
		SYSTEMTIME sysTime;

		if ( FileTimeToSystemTime( &fileTime, &sysTime ) )
		{
			timeLastWritten.SetTime( sysTime.wYear, sysTime.wMonth, sysTime.wDay,
				sysTime.wHour, sysTime.wMinute, sysTime.wSecond, 
				(LONG)sysTime.wMilliseconds * 1000000 );
		}

	}
	return timeLastWritten;
}
