/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMS_DBCOMMAND_H__
#define __EMS_DBCOMMAND_H__

#include "aobjbase.h"
#include "dal.h"
#include "daltypes.h"
#include <string>
#include "emsadohelper.h"

#define _USEADO
#ifdef _USEADO
#pragma warning(push)
#pragma warning(disable:4146)
#import <msado15.dll> named_guids, rename("EOF", "EndOfFile" )
#pragma warning(pop)
using namespace ADODB;
#endif

class CEMSDBCommand : public CApiObjBase
{	
	public:
		CEMSDBCommand();
		CEMSDBCommand( const CEMSDBCommand& x );
		~CEMSDBCommand();

		void Execute( const bool cbAsync = false );
		void SetConnection( const wchar_t* cwszCon );
		void SetCommandString( const wchar_t* cwszCmdString );
		EMSDBOBJECTSTATE GetState();
		void Cancel();

		void BindParameter( const wchar_t* cwszName, const EMSDBFLDTYPE ceDataType, 
							const EMSDBCMDDIRECTIONTYPE ceParamType );

		void SetParameterValue( const wchar_t* cwszName, const short csValue );
		void SetParameterValue( const wchar_t* cwszName, const unsigned short cusValue );
		void SetParameterValue( const wchar_t* cwszName, const long clValue );
		void SetParameterValue( const wchar_t* cwszName, const unsigned long culValue );
		void SetParameterValue( const wchar_t* cwszName, const __int64 ci64Value );
		void SetParameterValue( const wchar_t* cwszName, const unsigned __int64 cui64Value );
		void SetParameterValue( const wchar_t* cwszName, const wchar_t* cwszValue );
		void SetParameterValue( const wchar_t* cwszName, const char* cszValue );
		void SetParameterValue( const wchar_t* cwszName, const unsigned long culBytes, 
								const unsigned char* cabyValue );
		void SetParameterValue( const wchar_t* cwszName, const float cfValue );
		void SetParameterValue( const wchar_t* cwszName, const double cdValue );
		void SetParameterValue( const wchar_t* cwszName, const unsigned char cbyValue );


	private:
		_CommandPtr		_GetCommandPtr();
		void			_SetValue( const wchar_t* cwszName, _variant_t vValue );
		_ParameterPtr	_GetParameter( const wchar_t* cwszName );
		
	private:	// data
		_CommandPtr		m_spCmd;

		CEMSADOHelper	m_adoHelper;
};

#endif	// __EMS_DBCOMMAND_H__