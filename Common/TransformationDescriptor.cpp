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

#include "transformationdescriptor.h"
#include "emsdomdocument.h"
#include "emsdomnode.h"
#include "emsexcpt.h"
#include "dataiomsgs.h"


const wchar_t* CEMSTransformationDescriptor::ms_cwszClassIDPath = L"ClassID";
const wchar_t* CEMSTransformationDescriptor::ms_cwszMethodPath = L"Method";
const wchar_t* CEMSTransformationDescriptor::ms_cwszStartOffset = L"StartOffset";
const wchar_t* CEMSTransformationDescriptor::ms_cwszRoot = L"Translation";

CEMSTransformationDescriptor::CEMSTransformationDescriptor() : m_ulOutputSize(0), m_ulInputSize(0)
{
}

CEMSTransformationDescriptor::CEMSTransformationDescriptor( const wchar_t* cwszClsid,
															const wchar_t* cwszMethod, 
															const ULONG culOutputSize,
															const ULONG culInputSize ) :
																m_owszClsid( cwszClsid ),
																m_owszMethod( cwszMethod), 
																m_ulOutputSize( culOutputSize ),
																m_ulInputSize( culInputSize )
{
}

CEMSTransformationDescriptor::CEMSTransformationDescriptor( const CEMSTransformationDescriptor& x ) :
																			m_owszClsid( x.m_owszClsid ),
																			m_owszMethod( x.m_owszMethod ),
																			m_ulOutputSize( x.m_ulOutputSize ),
																			m_ulInputSize( x.m_ulInputSize )
{
}

CEMSTransformationDescriptor::~CEMSTransformationDescriptor()
{
}

void 
CEMSTransformationDescriptor::Deserialize( const wchar_t* cwszFmtInstruction )
{
	CEMSDOMNode* pClassNode = 0;
	CEMSDOMNode* pMethodNode = 0;
	CEMSDOMNode* pOffsetNode = 0;

	try
	{
		if( cwszFmtInstruction )
		{
			CEMSDOMDocument oDoc;

			if( oDoc.LoadXML( cwszFmtInstruction ) )
			{
				// Get the class ID from the instruction set.
				pClassNode = oDoc.SelectSingleNode( ms_cwszClassIDPath );

				if( !pClassNode )
				{
					throw CEMSException( EMS_DATAIO_FORMAT_NO_CLASSID );
				}

				m_owszClsid = pClassNode->GetElementTextEx();

				if( m_owszClsid.empty() )
				{
					throw CEMSException( EMS_DATAIO_FORMAT_NO_CLASSID_STRING );
				}

				pClassNode->Release();
				pClassNode = 0;

				pMethodNode = oDoc.SelectSingleNode( ms_cwszMethodPath );

				if( !pMethodNode )
				{
					throw CEMSException( EMS_DATAIO_FORMAT_NO_METHOD );
				}

				m_owszMethod = pMethodNode->GetElementTextEx();

				if( m_owszMethod.empty() )
				{
					throw CEMSException( EMS_DATAIO_FORMAT_NO_METHOD_STRING );
				}

				pMethodNode->Release();
				pMethodNode = 0;

/*				pOffsetNode = oDoc.SelectSingleNode( ms_cwszStartOffset );

				if( pOffsetNode )
				{
					// Optional
					std::wstring wszOffset = pOffsetNode->GetElementTextEx();
					
					pOffsetNode->Release();
					pOffsetNode = 0;
				}
*/
			}
		}
	}
	catch( ... )
	{
		if( pClassNode )
		{
			pClassNode->Release();
			pClassNode = 0;
		}

		if( pMethodNode )
		{
			pMethodNode->Release();
			pMethodNode = 0;
		}

		if( pOffsetNode )
		{
			pOffsetNode->Release();
			pOffsetNode = 0;
		}

		throw;
	}
}

std::wstring 
CEMSTransformationDescriptor::Serialize()
{
	std::wstring wszRet;

	CEMSDOMNode* pNode = 0;
	wchar_t* wszXML = 0;

	try
	{
		CEMSDOMDocument oDoc;
		oDoc.Initialize( ms_cwszRoot );

		pNode = oDoc.AddChildNode( ms_cwszClassIDPath, m_owszClsid.c_str() );

		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		pNode = oDoc.AddChildNode( ms_cwszMethodPath, m_owszMethod.c_str() );

		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		wszXML = oDoc.GetXML();

		if( wszXML )
		{
			wszRet = wszXML;

			delete[] wszXML;
			wszXML = 0;
		}
	}
	catch( ... )
	{
		if( wszXML )
		{
			wszRet = wszXML;

			delete[] wszXML;
			wszXML = 0;
		}

		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		throw;
	}

	return wszRet;
}

void 
CEMSTransformationDescriptor::SetMethod( const wchar_t* cwszMethod )
{
	if( cwszMethod )
	{
		m_owszMethod = cwszMethod;
	}
}

void 
CEMSTransformationDescriptor::SetClassID( const wchar_t* cwszID )
{
	if( cwszID )
	{
		m_owszClsid = cwszID;
	}
}
