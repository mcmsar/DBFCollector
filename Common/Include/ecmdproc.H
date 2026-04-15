/********************************************************************
*	Module:			ecmdproc.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 CEMSCommandProcessor class
*						
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

	0.0	01/03/22		rvw	start

********************************************************************/
#ifndef INC_CMDPROC
#define INC_CMDPROC

#include "cmdsink.h"

#define EMS_MAX_COMMAND_PARAMS	( 16 )

class CEMSCommandProcessor : public CEMSCommandSink
{
public:
	CEMSCommandProcessor( BYTE cCmdType = 0, INT nMaxLength = 0 );

	EMS_RESULT ParseCommand( void );
	EMS_RESULT EndCommand( void );

	BOOL IsCommand( LPCTSTR lpcszCmd );
	LONG LongParam( LPCTSTR lpcszParam, LONG lDefault=0 );
	LONG TextParam( LPCTSTR lpcszParam, LPTSTR lpszValue, INT nMaxLen, LPCTSTR lpcszDefault="" );
	INT IntParam( LPCTSTR lpcszParam, INT nDefault = 0 );

	LPCTSTR GetCommand( void ) { return (LPCTSTR)m_lpszCmd; }
	LPCSTR GetCmdLine( void );
	int GetParamCount( void ) { return m_nParamCount; }
	LPCTSTR GetParamName( int nIndex );
	LPCTSTR GetParamValue( int nIndex );

protected: // methods
	virtual ~CEMSCommandProcessor();

private: // methods
	BOOL _ProcessParam( LPSTR lpszParam );
	BOOL _ProcessCommand( LPSTR lpszCmd );

private: // data
	BYTE		m_cCmdType;
	LPBYTE	m_lpBuffer;
	LPTSTR 	m_lpszCmd;
	LPTSTR	m_lpszParam[ EMS_MAX_COMMAND_PARAMS ];
	LPTSTR	m_lpszValue[ EMS_MAX_COMMAND_PARAMS ];
	ULONG 	m_ulCmdLength;
	int		m_nParamCount;
	BOOL		m_bSyntaxError;
};

#endif // INC_CMDPROC

