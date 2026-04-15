/********************************************************************
*       Module:                 EMSExcpt.cpp
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Implementation of the CEMSException class
*
*       Usage:
*       Entry Point:
*       Input Files: 
*       Output Files:
*       Comments:
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

        Rev     Date                    Auth    Changes
        ===     ====                    ====    =======

        0.0     2001 Apr 10     rvw     start
		1.0		2002 Aug 16				JB		modified for ANSI C++

********************************************************************/
#include <string.h>
#include "emstypes.h"
#include <tchar.h>

#include "emserror.h"
#include "aobjbase.h"
#include "logmsgparam.h"
#include "emsexcpt.h"

CEMSException::CEMSException( const CEMSException &rEx )
{
   m_nLine = rEx.m_nLine;
   m_hr = rEx.m_hr;
   m_hrSub = rEx.m_hrSub;
   m_bHasMessage = rEx.m_bHasMessage;
   m_bAlarmLogged = rEx.m_bAlarmLogged;
   m_bLogDisabled = rEx.m_bLogDisabled;
   m_param = rEx.m_param;
   m_bAsWarningOnly = rEx.m_bAsWarningOnly;

   m_lpszFile = 0;
   m_lpszComment = 0;

	SetComment( rEx.m_lpszComment );

   SetFileName( rEx.m_lpszFile );
}

CEMSException::CEMSException( int nLine, LPCTSTR lpcszFile )
{
   m_nLine = nLine;
   m_lpszFile = 0;
   m_hr = EMS_EXCEPTION;
   m_hrSub = 0;
   m_lpszComment = 0;
   m_bHasMessage = FALSE;
   m_bAlarmLogged = FALSE;
   m_bLogDisabled = FALSE;
   m_bAsWarningOnly = FALSE;

   SetFileName( lpcszFile );
}

CEMSException::CEMSException(	int			nLine, 
								LPCTSTR		lpcszFile,
								EMS_RESULT	errCode, 
								CEMSLogMsgParam& param,
								EMS_RESULT subErrCode ) // = 0
{
	m_nLine			= nLine;
	m_lpszFile		= 0;
	SetFileName( lpcszFile );

	m_hr = errCode;
	m_hrSub	= subErrCode;
	m_lpszFile = 0;
	m_lpszComment = 0;
	m_nLine = 0;
	m_param = param;
	m_bHasMessage = TRUE;
	m_bAlarmLogged = FALSE;
	m_bLogDisabled = FALSE;
	m_bAsWarningOnly = FALSE;
}

CEMSException::CEMSException( EMS_RESULT errCode, EMS_RESULT subErrCode )
{
   m_hr = errCode;
   m_hrSub = subErrCode;
   m_lpszFile = 0;
   m_lpszComment = 0;
   m_nLine = -1;
   m_bHasMessage = FALSE;
   m_bAlarmLogged = FALSE;
   m_bLogDisabled = FALSE;
   m_bAsWarningOnly = FALSE;
}

CEMSException::CEMSException( EMS_RESULT errCode, CEMSLogMsgParam& param )
{
	m_hr = errCode;
	m_hrSub = 0;
	m_lpszFile = 0;
	m_lpszComment = 0;
	m_nLine = 0;
	m_param = param;
	m_bHasMessage = TRUE;
	m_bAlarmLogged = FALSE;
	m_bLogDisabled = FALSE;
	m_bAsWarningOnly = FALSE;
}

CEMSException::CEMSException( EMS_RESULT errCode, const BOOL cbHasMessage )
{
	m_hr = errCode;
	m_hrSub = 0;
	m_lpszFile = 0;
	m_lpszComment = 0;
	m_nLine = 0;
	m_bHasMessage = cbHasMessage;
	m_bAlarmLogged = FALSE;
	m_bLogDisabled = FALSE;
	m_bAsWarningOnly = FALSE;

}

CEMSException::CEMSException(	int nLine, 
								LPCTSTR lpcszFile, 
								EMS_RESULT errCode, 
								EMS_RESULT subErrCode )
{
	m_nLine = nLine;
	m_lpszFile = 0;
	m_lpszComment = 0;
	SetFileName( lpcszFile );
	m_hr = errCode;
	m_hrSub = subErrCode;
	m_bHasMessage = FALSE;
	m_bAlarmLogged = FALSE;
	m_bLogDisabled = FALSE;
	m_bAsWarningOnly = FALSE;

}

CEMSException::~CEMSException()
{
   if ( m_lpszFile )
   {
		delete [ ] m_lpszFile;
		m_lpszFile = 0;
   }

   if ( m_lpszComment )
   {
		delete [ ] m_lpszComment;
		m_lpszComment = 0;
   }
}

BOOL
CEMSException::SetFileName( LPCTSTR lpcszFile )
{
   if ( m_lpszFile && lpcszFile && ( _tcscmp( lpcszFile, m_lpszFile) == 0 ) )
   {
      ;  // file name is the same : so nothing to do
   }
   else
   {
      if ( m_lpszFile )
      {
         delete [ ] m_lpszFile;
         m_lpszFile = 0;
      }
      if ( lpcszFile && *lpcszFile )
      {
         m_lpszFile = new TCHAR[ _tcslen( lpcszFile ) + 1 ];
         if ( m_lpszFile )
            _tcscpy( m_lpszFile, lpcszFile );
      }
   }
   return ( m_lpszFile != 0 );
}

// *** THE FOLLOWING FUNCTIONS ARE DEPRECATED ***
// All "comments" should be translatable strings or should be a message parameter
// The only valid string parameters are non-translatable strings.  
// E.g. names, supplied data, or formatted numeric data.

CEMSException::CEMSException(	int nLine, 
								LPCTSTR lpcszFile, 
								EMS_RESULT errCode, 
								EMS_RESULT subErrCode, 
								LPCTSTR szComment )
{
	m_nLine = nLine;
	m_lpszFile = 0;
	m_lpszComment = 0;
	SetFileName( lpcszFile );
	m_hr = errCode;
	m_hrSub = subErrCode;
	m_bHasMessage = FALSE;
	m_bAlarmLogged = FALSE;
	m_bLogDisabled = FALSE;
	m_bAsWarningOnly = FALSE;
	
	SetComment( szComment );
}

CEMSException::CEMSException( LPCTSTR lpcszComment , EMS_RESULT errCode, EMS_RESULT subErrCode )
{
   m_hr = errCode;
   m_hrSub = subErrCode;
   m_lpszFile = 0;
   m_lpszComment = 0;
   m_nLine = -1;
   m_bHasMessage = FALSE;
   m_bAlarmLogged = FALSE;
   m_bLogDisabled = FALSE;
   m_bAsWarningOnly = FALSE;

   SetComment( lpcszComment );
}
BOOL
CEMSException::SetComment( LPCTSTR lpcszComment )
{
   if ( m_lpszComment && lpcszComment && ( _tcscmp( lpcszComment, m_lpszComment) == 0 ) )
   {
      ;     // comment is the same : so nothing to do
   }
   else
   {
      if ( m_lpszComment )
      {
         delete [ ] m_lpszComment;
         m_lpszComment = 0;
      }
      if ( lpcszComment && *lpcszComment )
      {
         m_lpszComment = new TCHAR[ _tcslen( lpcszComment ) + 1 ];
         if ( m_lpszComment )
            _tcscpy( m_lpszComment, lpcszComment );
      }
   }
   return ( m_lpszComment != 0 );
}

CEMSException& 
CEMSException::operator=( const CEMSException& croRHS )
{
	m_nLine = croRHS.m_nLine;
	m_hr = croRHS.m_hr;
	m_hrSub = croRHS.m_hrSub;
	m_bHasMessage = croRHS.m_bHasMessage;
	m_bAlarmLogged = croRHS.m_bAlarmLogged;
	m_bLogDisabled = croRHS.m_bLogDisabled;
	m_param = croRHS.m_param;
	m_bAsWarningOnly = croRHS.m_bAsWarningOnly;

	m_lpszFile = 0;
	m_lpszComment = 0;

	SetComment( croRHS.m_lpszComment );

	SetFileName( croRHS.m_lpszFile );

	return *this;
}

void 
CEMSException::Clear()
{
	m_nLine = 0;
	m_hr = EMS_OK;
	m_hrSub = EMS_OK;
	m_bHasMessage = false;
	m_bAlarmLogged = false;
	m_bLogDisabled = false;
	m_param.Clear();
	m_bAsWarningOnly = false;

	if( m_lpszFile )
	{
		delete[] m_lpszFile;
		m_lpszFile = 0;
	}

	if( m_lpszComment )
	{
		delete[] m_lpszComment;
		m_lpszComment = 0;
	}
}