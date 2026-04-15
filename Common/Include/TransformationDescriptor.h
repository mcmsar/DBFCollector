/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#ifndef __TRANSFORMATION_DESCRIPTOR_H__
#define __TRANSFORMATION_DESCRIPTOR_H__

#include "aobjbase.h"
#include <string>

//! @class CEMSTransformationDescriptor
//! Contains information describing a data format transformation.
class CEMSTransformationDescriptor : public CApiObjBase
{
	public:
		CEMSTransformationDescriptor();
		CEMSTransformationDescriptor( const wchar_t* cwszClsid, const wchar_t* cwszMethod, const ULONG culOutputSize, const ULONG culInputSize );
		CEMSTransformationDescriptor( const CEMSTransformationDescriptor& x );
		~CEMSTransformationDescriptor();

		//! @fn void Deserialize( const wchar_t* cwszDesc )
		//! Load the object from its serial XML form.
		void Deserialize( const wchar_t* cwszDesc );

		//! @fn std::wstring Serialize()
		//! Convert the object to its serial XML form.
		std::wstring Serialize();

		//! @fn void SetClassID( const wchar_t* cwszID )
		//! Set the class ID of the plug-in that performs the translation.
		void SetClassID( const wchar_t* cwszID );

		//! @fn std::wstring GetClassID()
		//! Retrieve the class ID of the plug-in that performs the translation.
		std::wstring GetClassID() { return m_owszClsid; }

		//! @fn void SetMethod( const wchar_t* cwszMethod )
		//! Set the transformation method name.
		void SetMethod( const wchar_t* cwszMethod );

		//! @fn std::wstring GetMethod() const
		//! Get the transformation method.
		std::wstring GetMethod() const { return m_owszMethod; }

		//! @fn void SetOutputSize( const ULONG culSize )
		//! Set the output record size.
		void SetOutputSize( const ULONG culSize ) { m_ulOutputSize = culSize; }

		//! @fn ULONG GetOutputSize() const
		//! Get the output record size.
		ULONG GetOutputSize() const { return m_ulOutputSize; }

		//! @fn void SetInputSize( const ULONG culSize )
		//! Set the size of the input record.
		void SetInputSize( const ULONG culSize ) { m_ulInputSize = culSize; }

		//! @fn ULONG GetInputSize() const
		//! Get the size of the input record.
		ULONG GetInputSize() const { return m_ulInputSize; }

	private:
		std::wstring m_owszClsid;
		std::wstring m_owszMethod;
		ULONG m_ulOutputSize;
		ULONG m_ulInputSize;

	public:
		static const wchar_t* ms_cwszClassIDPath;
		static const wchar_t* ms_cwszMethodPath;
		static const wchar_t* ms_cwszStartOffset;
		static const wchar_t* ms_cwszRoot;


};

#endif