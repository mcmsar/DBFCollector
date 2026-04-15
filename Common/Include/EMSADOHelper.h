/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMS_ADO_HELPER_H__
#define __EMS_ADO_HELPER_H__

#define _USEADO
#ifdef _USEADO
#pragma warning(push)
#pragma warning(disable:4146)
#import <msado15.dll> named_guids, rename("EOF", "EndOfFile" )
#pragma warning(pop)
using namespace ADODB;
#endif

#include "daltypes.h"
#include <map>

class CEMSADOHelper
{
	public:
		CEMSADOHelper();
		CEMSADOHelper( const CEMSADOHelper& x );
		~CEMSADOHelper();

		DataTypeEnum			GetADODataType( const EMSDBFLDTYPE ceDataType );

		ParameterDirectionEnum	GetADODirectionType( const EMSDBCMDDIRECTIONTYPE ceParamType ) const;

		void					ConvertToSafeArray( const unsigned long culBytes, 
													const unsigned char* cabyValue,
													_variant_t& vValue ) const;

		EMSDBFLDTYPE			GetEMSDataType( const DataTypeEnum ceType );

		long					GetEMSDataSize( const EMSDBFLDTYPE ceType );

		EMSDBOBJECTSTATE		GetEMSObjectState( const ObjectStateEnum ceState );

		bool FilterAlarm( const HRESULT chrErrorCode );

		bool IsWarning( const HRESULT chrErrorCode );

		//! Convert an EMSTIME to the DATE type that is a member of the VARIANT union.
		DATE					GetDate( const EMSTIME ctimeValue );

		//! Convert a variant DATE to EMSTIME.
		EMSTIME					GetEMSTime( const VARIANT cvValue );

		static AffectEnum		GetADOAffectType( const EMSDBAFFECTS ceAffect ); 

	private:
		void _LoadAdoToEmsFldTypeTable();
		void _LoadEmsToAdoFldTypeTable();
		void _LoadEMSDataSizes();
		void _LoadAdoToEmsObjectStateTable();

	private:
		std::map<DataTypeEnum,EMSDBFLDTYPE>		m_mapAdoToEmsFldType;
		std::map<EMSDBFLDTYPE,DataTypeEnum>		m_mapEmsToAdoFldType;
		std::map<EMSDBFLDTYPE,long>				m_mapEmsDataSizes;
		std::map<ObjectStateEnum,EMSDBOBJECTSTATE>	m_mapAdoToEmsObjState;

};

#endif // __EMS_ADO_HELPER_H__