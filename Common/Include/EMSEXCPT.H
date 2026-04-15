/********************************************************************
*	Module:			EMSExcpt.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface to CEMSException class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001 Apr 10	rvw	start

********************************************************************/
#ifndef INC_EMSEXCPT
#define INC_EMSEXCPT

#include "emstypes.h"
#include "emserror.h"

#include "logmsgparam.h"

class CEMSException
{
public:
	// *** THE FOLLOWING FUNCTIONS ARE DEPRECATED ***
	// All "comments" should be translatable strings or should be a message parameter
	// The only valid string parameters are non-translatable strings.  
	// E.g. names, supplied data, or formatted numeric data.
	CEMSException( int nLine, LPCTSTR lpcszFile, EMS_RESULT errCode, EMS_RESULT subErrCode, LPCTSTR szComment );
	CEMSException( LPCTSTR lpcszComment , EMS_RESULT errCode=0, EMS_RESULT subErrCode=0 );

	BOOL SetComment( LPCTSTR lpcszComment=0 );
	LPCTSTR GetComment( void ) { return (LPCTSTR)m_lpszComment; }
	// *** END OF DEPRECATED FUNCTIONS ***

	CEMSException( const CEMSException &ex );
	CEMSException( int nLine, LPCTSTR lpcszFile, EMS_RESULT errCode, EMS_RESULT subErrCode = 0 );
	CEMSException( int nLine, LPCTSTR lpcszFile, EMS_RESULT errCode, CEMSLogMsgParam& param, EMS_RESULT subErrCode = 0 );
	CEMSException( int nLine= 0, LPCTSTR lpcszFile = 0 );
	CEMSException( EMS_RESULT errCode, EMS_RESULT subErrCode=0 );
	CEMSException( EMS_RESULT errCode, CEMSLogMsgParam& param );
	CEMSException( EMS_RESULT errCode, const BOOL cbHasMessage );
	virtual ~CEMSException();

	void SetLineNumber( int nLine = 0 ) { m_nLine = nLine; }
	int GetLineNumber( void ) { return m_nLine; }

	EMS_RESULT GetErrCode( void ) { return m_hr; }
	EMS_RESULT GetSubErrCode( void ) { return m_hrSub; }

	void SetMark( int nLine = 0, LPCTSTR lpcszFile = 0 )
		{
			m_nLine = nLine; SetFileName( lpcszFile );
		}

	BOOL SetFileName( LPCTSTR lpcszFile = 0 );
	LPCTSTR GetFileName( void ) { return (LPCTSTR)m_lpszFile; }
	CEMSLogMsgParam& GetParam() { return m_param; }
	BOOL HasMessage() { return m_bHasMessage; }
	BOOL HasBeenAlarmed() { return m_bAlarmLogged; }
	void SetAlarmLogged() { m_bAlarmLogged = TRUE; }
	void DisableLog() { m_bLogDisabled = TRUE; }
	BOOL LogDisabled() { return m_bLogDisabled; }
	void SetLogAsWarning() { m_bAsWarningOnly = TRUE; }
	BOOL IsWarning() { return m_bAsWarningOnly; }

	void SetErrCode( const EMS_RESULT chrValue ) { m_hr = chrValue; }
	CEMSException& operator=( const CEMSException& croRHS );
	void Clear(); 

private: // data
	int m_nLine;
	TCHAR *m_lpszFile;
	TCHAR *m_lpszComment;
	EMS_RESULT m_hr;
	EMS_RESULT m_hrSub;
	CEMSLogMsgParam m_param;
	BOOL	m_bHasMessage;
	BOOL	m_bAlarmLogged;
	BOOL	m_bLogDisabled;
	BOOL	m_bAsWarningOnly;
};


// macros to define specialized child exception classes
#define EMSException(className)                 \
   class className : public CEMSException       \
   {                                            \
      public:                                   \
      className(     int nLine,                 \
                     TCHAR* lpcszFile,          \
                     long errCode,              \
                     long subErrCode=0,         \
					 TCHAR* szComment = 0):     \
                     CEMSException(nLine, lpcszFile, errCode, subErrCode, szComment)\
      {                                         \
                                                \
      }                                         \
                                                \
      className(CEMSException& r):              \
         CEMSException(r)                       \
      {                                         \
                                                \
      }                                         \
                                                \
      className(	int	nLine,					\
					LPCTSTR lpcszFile,			\
					EMS_RESULT errCode,			\
					CEMSLogMsgParam& param ):	\
			CEMSException( nLine, lpcszFile, errCode, param ) \
      {                                         \
                                                \
      }                                         \
                                                \
   };                                           


// macros for raising EMS exceptions

// general exceptions
EMSException(CEMSLogicException)
EMSException(CEMSRuntimeException)
EMSException(CEMSNullPointerException)
EMSException(CEMSInvalidArgumentException)
EMSException(CEMSValidationException)
EMSException(CEMSObjectCreateException)

#define THROW_LOGIC_EXCEPTION(lErrorCode)\
   throw CEMSLogicException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_RUNTIME_EXCEPTION(lErrorCode)\
   throw CEMSRuntimeException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_NOMEMORY_EXCEPTION()\
	throw CEMSRuntimeException(__LINE__,TEXT(__FILE__), EMS_NO_MEMORY);

#define THROW_NULL_POINTER_EXCEPTION()\
   throw CEMSNullPointerException(__LINE__, TEXT(__FILE__), EMS_INVALID_PTR);

#define THROW_INVALID_ARG_EXCEPTION()\
   throw CEMSInvalidArgumentException(__LINE__, TEXT(__FILE__), EMS_BAD_PARAM);

#define THROW_VALIDATION_EXCEPTION(lErrorCode)\
   throw CEMSValidationException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_RUNTIME_EXCEPTION_WITH_MSG(lErrorCode)\
	throw CEMSException( lErrorCode, true );

#define THROW_OBJECT_CREATE_EXCEPTION( lErrorCode, wszObjName )\
	{\
	CEMSLogMsgParam	param(2);\
	param.AddString( wszObjName );\
	param.AddX( lErrorCode );\
	throw CEMSObjectCreateException(__LINE__, TEXT(__FILE__), EMS_OBJECT_CREATE_FAILED, param );\
	}

#define THROW_QUERYINTERFACE_EXCEPTION( lErrorCode, wszInterface )\
	{\
	CEMSLogMsgParam	param(2);\
	param.AddString( wszInterface );\
	param.AddX( lErrorCode );\
	throw CEMSObjectCreateException(__LINE__, TEXT(__FILE__), EMS_QUERY_INTERFACE_ERROR, param );\
	}

// I/O exceptions
EMSException(CEMSIOException)
EMSException(CEMSFileNotFoundException)

#define THROW_IO_EXCEPTION()\
   throw CEMSIOException(__LINE__, TEXT(__FILE__), EMS_IO_ERROR);

#define THROW_FILE_NOT_FOUND_EXCEPTION()\
   throw CEMSFileNotFoundException(__LINE__, TEXT(__FILE__), EMS_NO_FILE);

// Database Exceptions
EMSException(CEMSDALException)

#define THROW_DAL_EXCEPTION(lErrorCode)\
   throw CEMSDALException(__LINE__, TEXT(__FILE__), lErrorCode);


// EMS DOM Exceptions
EMSException(CEMSDOMException)
EMSException(CEMSDOMDocumentException)
EMSException(CEMSDOMNodeException)
EMSException(CEMSDOMNodeListException)
   
#define THROW_DOM_EXCEPTION(lErrorCode)\
   throw CEMSDOMException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_DOM_DOCUMENT_EXCEPTION(lErrorCode)\
   throw CEMSDOMDocumentException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_DOM_NODE_EXCEPTION(lErrorCode)\
   throw CEMSDOMNodeException(__LINE__, TEXT(__FILE__), lErrorCode);

#define THROW_DOM_NODE_LIST_EXCEPTION(lErrorCode)\
   throw CEMSDOMNodeListException(__LINE__, TEXT(__FILE__), lErrorCode);


// EMS Security Exceptions

// Abreviations used:
// SS = Security Service
// AE = Authentication Engine
// PE = Policy Engine

EMSException(CEMS_SS_Exception)
EMSException(CEMS_AE_Exception)
EMSException(CEMS_PE_Exception)

// AE
#define THROW_AE_EXCEPTION(lErrorCode)\
   throw CEMS_AE_Exception(__LINE__, TEXT(__FILE__), lErrorCode); 

#define THROW_AE_VALIDATION_EXCEPTION()\
   throw CEMS_AE_Exception(__LINE__, TEXT(__FILE__), EMS_BAD_PARAM); 

// PE
#define THROW_PE_EXCEPTION(lErrorCode)\
   throw CEMS_PE_Exception(__LINE__, TEXT(__FILE__), lErrorCode); 

#define THROW_PE_VALIDATION_EXCEPTION()\
   throw CEMS_PE_Exception(__LINE__, TEXT(__FILE__), EMS_BAD_PARAM); 

// SS
#define THROW_SS_EXCEPTION(lErrorCode)\
   throw CEMS_SS_Exception(__LINE__, TEXT(__FILE__), lErrorCode); 

#define THROW_SS_VALIDATION_EXCEPTION()\
   throw CEMS_SS_Exception(__LINE__, TEXT(__FILE__), EMS_BAD_PARAM); 

#endif // INC_EMSEXCPT

