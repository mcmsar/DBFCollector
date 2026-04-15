/********************************************************************
*	Module:			EMSFList.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface description for CEMSFileList class
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
#ifndef INC_EMSFLIST
#define INC_EMSFLIST

#include "emstypes.h"
#include "emserror.h"

class CEMSFileList 
{
public:
	CEMSFileList( LPCTSTR lpcszSearch=0, BOOL bSort = TRUE );
	virtual ~CEMSFileList();

	EMS_RESULT Initialize( LPCTSTR lpcszSearch=0, BOOL bSort = TRUE );
	EMS_RESULT InitializeEx( LPCTSTR lpcszSearch=0, BOOL bSort = TRUE );

	EMS_RESULT Reset( void );
	EMS_RESULT Sort( void );
	EMS_RESULT SortEx( void );
	inline int Count( void ) { return m_nCount; }

	LPCTSTR GetFileName( int nIndex );
 	DWORD GetFileSize( int nIndex );
 	EMSTIME GetFileLastWriteTime( int nIndex );

private:
	long _extractSequenceNumber( LPCTSTR lpszFileName );

private: // data
	int		m_nCount;
	LPVOID	m_lpLinkedList;
	LPVOID	m_lpIndex;
};

#endif	// INC_EMSFLIST
