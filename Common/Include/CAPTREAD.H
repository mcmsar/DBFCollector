/******************************************************************** 
*	Module:			captread.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSCaptureFileReader
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003 June 18 rvw	start

********************************************************************/
#ifndef INC_CAPTREAD
#define INC_CAPTREAD

#include "emserror.h"
#include "filesign.h"

const int c_nMaxChannelNumber = 255;

class CEMSCaptureRecordProcessor
{
public:
	CEMSCaptureRecordProcessor() { m_dwFileOffset = 0; };
	virtual ~CEMSCaptureRecordProcessor() {};

	virtual EMS_RESULT OnCaptureRecord( int nChannel, WORD wVersion, int nLength, LPBYTE lpRecord )=0;

	inline DWORD GetFileOffset( void ) { return m_dwFileOffset; }
	inline void SetFileOffset( DWORD dwOffset ) { m_dwFileOffset = dwOffset; }

private: // data
	DWORD	m_dwFileOffset;				
};

class CEMSCaptureFileReader
{
public:
	CEMSCaptureFileReader();
	virtual ~CEMSCaptureFileReader();

	inline void SetCurrentVersion( WORD wVersion ) { m_wCurrentVersion = wVersion; }
	inline void SetOverrideVersion( WORD wVersion ) { m_wOverrideVersion = wVersion; }
	inline WORD GetCurrentVersion( void ) { return m_wCurrentVersion; }

	EMS_RESULT ProcessFile( LPCTSTR lpcszFilespec, CEMSCaptureRecordProcessor *lpProcessor );
	EMS_RESULT Initialize( int nMaxRecLen );
	EMS_RESULT Reset( void );

private:	// methods
	EMS_RESULT _Init( void );

private:	// data
	WORD						m_wCurrentVersion;
	WORD						m_wOverrideVersion;
	int						m_nMaxRecLength;
	int						m_nMaxRecLengthRead;
	int						m_nRecordsRead;
	bool						m_bDataPresent[ c_nMaxChannelNumber ];
	LPBYTE				 	m_lpcBuffer;
};

#endif	// INC_CAPTREAD
