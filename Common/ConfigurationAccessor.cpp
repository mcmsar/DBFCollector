/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$


********************************************************************/
#ifdef WIN32
#pragma warning(disable:4786)
#endif

#include "configurationaccessor.h"

#ifdef WIN32
#include "emsdomnode.h"
#include "emsdomnodelist.h"
#endif

#include "emsexcpt.h"
#include "convutility.h"
#include "messages.h"

#ifdef WIN32
#include <crtdbg.h>
#elif defined(__VMS)
#include <assert.h>
#endif

const wchar_t* CEMSConfigurationAccessor::ms_cwszFlagValueTrue = L"true";
const wchar_t* CEMSConfigurationAccessor::ms_cwszFlagValueFalse = L"false";

const wchar_t* CEMSConfigurationAccessor::ms_cwszElementLevel = L"/";
const wchar_t* CEMSConfigurationAccessor::ms_cwszAttributeIndicator = L"@";

const ULONG CEMSConfigurationAccessor::ms_culMaxXPathQuerySize = 255;

#ifdef USE_APACHE_XERCES
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/domnode.hpp>
#include <xercesc/dom/domexception.hpp>
#include <xercesc/dom/domxpathresult.hpp>
#include <xercesc/dom/domimplementation.hpp>
#include <xercesc/framework/membufinputsource.hpp>
#include <xercesc/framework/localfileinputsource.hpp>
#include <xercesc/dom/impl/domwriterimpl.hpp>

#include <xalanc/PlatformSupport/XSLException.hpp>
#include <xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp>
#include <xalanc/XPath/XObject.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeInit.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeParserLiaison.hpp>
#include <xalanc/XalanTransformer/XercesDOMWrapperParsedSource.hpp>
#include <xalanc/xercesparserliaison/xerceselementwrapper.hpp>
#include <xalanc/xercesparserliaison/xercesparserliaison.hpp>
#include <xalanc/xercesparserliaison/xercesdomsupport.hpp>
#include <xalanc/xercesparserliaison/xerceswrappernavigator.hpp>

#include <xalanc/xercesparserliaison/xercesdocumentwrapper.hpp>
#include <xalanc/Include/XalanMemoryManagement.hpp>
#include <xalanc/xpath/NodeRefList.hpp>

CEMSConfigurationAccessor::CEMSConfigurationAccessor() : m_pNode(NULL), m_pXalanDoc(NULL)
{
}

CEMSConfigurationAccessor::CEMSConfigurationAccessor( const CEMSConfigurationAccessor& x ) : 
								m_pNode(x.m_pNode), m_pXalanDoc(NULL), m_owszFile( x.m_owszFile )
{
	// True copy.
	if( x.m_pNode )
	{
		m_pNode = x.m_pNode->cloneNode(true);
	}
}

CEMSConfigurationAccessor::~CEMSConfigurationAccessor()
{
	_ReleaseData();
}

std::wstring 
CEMSConfigurationAccessor::Serialize()
{
	std::wstring owszRet;

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		XERCES_CPP_NAMESPACE::DOMWriterImpl oDOMWriter;
		owszRet= oDOMWriter.writeToString( *m_pNode );
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}

	return owszRet;
}

void 
CEMSConfigurationAccessor::SetSource( XERCES_CPP_NAMESPACE::DOMNode* pNode )
{
	try
	{
		_ReleaseData();
		m_pNode = pNode->cloneNode(true);
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
}

void 
CEMSConfigurationAccessor::SetSource( const wchar_t* cwszXML )
{
	_ReleaseData();

	XERCES_CPP_NAMESPACE::XercesDOMParser*  pParser = NULL;

	try
	{  
		if( !cwszXML )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pParser = new XERCES_CPP_NAMESPACE::XercesDOMParser();

		if( !pParser )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		// Does the XML string contain a processing instruction with the xml version.
		// The Xerces parser requires it.
		std::wstring owszXML( cwszXML );
		std::wstring::size_type iPos = owszXML.find( L"xml version=" );
		if( std::wstring::npos == iPos )
		{
			owszXML = L"<?xml version=\"1.0\" standalone=\"no\"?>\n";
			owszXML.append( cwszXML );
		}


		XERCES_CPP_NAMESPACE::MemBufInputSource oMem(	(const XMLByte*) owszXML.c_str(), 
														sizeof(wchar_t)*owszXML.length(), 
														(const XMLCh*) L"" );
		pParser->parse( oMem );

		m_pNode = pParser->adoptDocument();

		delete pParser;
		pParser = NULL;
	
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetSourceFile( const wchar_t* cwszXMLFile )
{
	_ReleaseData();

	XERCES_CPP_NAMESPACE::XercesDOMParser* pParser = NULL;

	try
	{  
		pParser = new XERCES_CPP_NAMESPACE::XercesDOMParser();

		if( !pParser )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		XERCES_CPP_NAMESPACE::LocalFileInputSource oLocalFile( cwszXMLFile );

		pParser->parse( oLocalFile );


		m_pNode = pParser->adoptDocument();

		delete pParser;
		pParser = NULL;
		
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::Save( const wchar_t* cwszXMLFile )
{
	FILE* fpOut = NULL;

	try
	{
		FILE* fpOut = _wfopen( cwszXMLFile, L"w+" );

		if( !fpOut )
		{
			THROW_RUNTIME_EXCEPTION( EMS_NO_FILE );
		}

		std::wstring owszSerial = Serialize();

		fwprintf( fpOut, L"%s", owszSerial.c_str() );

		fclose( fpOut );
		fpOut = NULL;
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( fpOut )
		{
			fclose( fpOut );
			fpOut = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( fpOut )
		{
			fclose( fpOut );
			fpOut = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		if( fpOut )
		{
			fclose( fpOut );
			fpOut = NULL;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
{
	_ASSERTE( cwszValue );

	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	XERCES_CPP_NAMESPACE::DOMElement* pElement = NULL;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->setNodeValue( cwszValue );
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{

		throw;
	}
}


std::wstring 
CEMSConfigurationAccessor::GetElementValue( const wchar_t* cwszPath )
{
	std::wstring owszRet;

	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		XALAN_CPP_NAMESPACE::XalanNode* pNode = GetNode( cwszPath );

		if( pNode )
		{
			if( XALAN_CPP_NAMESPACE::XalanNode::ELEMENT_NODE == pNode->getNodeType() )
			{
				owszRet = pNode->getNodeValue().c_str();
			}
		}

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{

		throw;
	}

	return owszRet;
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
{
	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );
	_ASSERTE( cwszValue );

	if( !m_pNode || !cwszPath || !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// For now, keep it simple.  The Path can only be the attribute name.  That is, it is not
		// really the path to the attribute, but assumes that attribute is a child of the current
		// node.

		// So, the node must be of element type.
		if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
		{

			// Strip off any leading attribute signifier.
			std::wstring wszAttributeName;
			std::wstring wszPath( cwszPath );
			std::wstring::size_type nAtPos = wszPath.find( ms_cwszAttributeIndicator );

			if( std::wstring::npos != nAtPos )
			{
				_ASSERTE( wszPath.length() > 1 );

				if( wszPath.length() > 1 )
					wszAttributeName = wszPath.substr( nAtPos + 1 );
			}
			else
			{
				wszAttributeName = wszPath;
			}

			XERCES_CPP_NAMESPACE::DOMAttr* pAttr = m_pNode->getOwnerDocument()->createAttribute( wszAttributeName.c_str() );

			if( !pAttr )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pAttr->setValue( cwszValue );

			((XERCES_CPP_NAMESPACE::DOMElement*) m_pNode)->setAttributeNode( pAttr );

		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}
}

std::wstring 
CEMSConfigurationAccessor::GetAttributeValue( const wchar_t* cwszPath )
{
	_ASSERTE( cwszPath );

	std::wstring owszRet;

	if( !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	//XERCES_CPP_NAMESPACE::DOMElement* pElement = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMAttr* pAttribute = _GetAttribute( cwszPath );

		//pElement = _GetTextElement( cwszPath );

		//if( !pElement )
		//{
		//	THROW_NULL_POINTER_EXCEPTION();
		//}

		if( pAttribute )
			owszRet = pAttribute->getNodeValue( );
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}

	return owszRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const double cdValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( cdValue ).c_str() );
}
		
double 
CEMSConfigurationAccessor::GetElementValueDouble( const wchar_t* cwszPath )
{
	double dRet = 0.0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		dRet = CEMSConversionUtil::ConvertToDouble( wszValue.c_str() );
	}

	return dRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const bool cbValue )
{
	SetElementValue( cwszPath, cbValue ? ms_cwszFlagValueTrue : ms_cwszFlagValueFalse );
}

bool 
CEMSConfigurationAccessor::GetElementValueBoolean( const wchar_t* cwszPath )
{
	bool bRet = false;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( wszValue == ms_cwszFlagValueTrue )
	{
		bRet = true;
	}
	else if( wszValue == ms_cwszFlagValueFalse )
	{
		bRet = false;
	}

	return bRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const ULONG culValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( culValue ).c_str() );
}

ULONG 
CEMSConfigurationAccessor::GetElementValueULong( const wchar_t* cwszPath )
{
	ULONG ulRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		ulRet = CEMSConversionUtil::ConvertToULong( wszValue.c_str() );
	}

	return ulRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const EMSTIME ctimeValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString(ctimeValue.intTime).c_str() );
}

EMSTIME
CEMSConfigurationAccessor::GetElementValueTime( const wchar_t* cwszPath )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		timeRet = CEMSConversionUtil::ConvertToTime( wszValue.c_str() );
	}

	return timeRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const USHORT cusValue )
{
	SetElementValue( cwszPath, (const ULONG) cusValue );
}

//! Get an element value as an unsigned short.
unsigned short 
CEMSConfigurationAccessor::GetElementValueUShort( const wchar_t* cwszPath )
{
	unsigned short usRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		usRet = CEMSConversionUtil::ConvertToUShort( wszValue.c_str() );
	}

	return usRet;
}

short 
CEMSConfigurationAccessor::GetElementValueShort( const wchar_t* cwszPath )
{
	short sRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		sRet = CEMSConversionUtil::ConvertToShort( wszValue.c_str() );
	}

	return sRet;
}

unsigned __int64 
CEMSConfigurationAccessor::GetElementValueUI64( const wchar_t* cwszPath )
{
	unsigned __int64 ui64Ret = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		ui64Ret = CEMSConversionUtil::ConvertHexStringToUInt64( wszValue.c_str() );
	}

	return ui64Ret;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const unsigned __int64 cui64Value )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString(cui64Value).c_str() );
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const float cfValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( cfValue ).c_str() );
}
		
float 
CEMSConfigurationAccessor::GetElementValueFloat( const wchar_t* cwszPath )
{
	float fRet = 0.0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		fRet = CEMSConversionUtil::ConvertToFloat( wszValue.c_str() );
	}

	return fRet;
}

int
CEMSConfigurationAccessor::GetElementValueInt( const wchar_t* cwszPath )
{
	int iRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		iRet = _wtoi( wszValue.c_str() );
	}

	return iRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const BYTE cbyValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( cbyValue ).c_str() );
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const short csValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( csValue ).c_str() );
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const char ccValue )
{
	SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( ccValue ).c_str() );
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const ULONG culValue )
{
	SetAttributeValue( cwszPath, CEMSConversionUtil::ConvertToString( culValue ).c_str() );
}

ULONG 
CEMSConfigurationAccessor::GetAttributeValueULong( const wchar_t* cwszPath )
{
	ULONG ulRet = 0;

	std::wstring owszValue = GetAttributeValue( cwszPath );

	if( !owszValue.empty() )
	{
		ulRet = CEMSConversionUtil::ConvertToULong( owszValue.c_str() );
	}

	return ulRet;
}

bool 
CEMSConfigurationAccessor::GetAttributeValueBoolean( const wchar_t* cwszPath )
{
	bool bRet = false;

	std::wstring owszValue = GetAttributeValue( cwszPath );

	if( !owszValue.empty() )
	{
		if( 0 == wcsicmp( owszValue.c_str(), ms_cwszFlagValueTrue ) )
		{
			bRet = true;
		}
		else if( 0 == wcsicmp( owszValue.c_str(), ms_cwszFlagValueFalse ) )
		{
			bRet = false;
		}
	}

	return bRet;;
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const bool cbValue )
{
	SetAttributeValue( cwszPath, cbValue ? ms_cwszFlagValueTrue : ms_cwszFlagValueFalse );
}

void 
CEMSConfigurationAccessor::AttachChild( CEMSConfigurationAccessor* pChild )
{
	_ASSERTE( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void 
CEMSConfigurationAccessor::Attach( CEMSConfigurationAccessor* pChild )
{
	_ASSERTE( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void 
CEMSConfigurationAccessor::DetachChild()
{
	_ASSERTE( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

XALAN_CPP_NAMESPACE::NodeRefList 
CEMSConfigurationAccessor::GetNodes( const wchar_t* cwszPath )
{
	XALAN_CPP_NAMESPACE::NodeRefList refRetList;

	try
	{
		XALAN_CPP_NAMESPACE::XPathEvaluator::initialize();

		XALAN_CPP_NAMESPACE::XalanSourceTreeDOMSupport		theDOMSupport;
		XALAN_CPP_NAMESPACE::XalanSourceTreeParserLiaison	theLiaison(theDOMSupport);

		// Hook the two together...
		theDOMSupport.setParserLiaison(&theLiaison);

		XALAN_CPP_NAMESPACE::XalanNode* pContextNode = _GetXalanNode();

		if( !pContextNode )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		XALAN_CPP_NAMESPACE::XalanDocumentPrefixResolver thePrefixResolver( pContextNode->getOwnerDocument() ? pContextNode->getOwnerDocument() : (XALAN_CPP_NAMESPACE::XalanDocument*) pContextNode );

		XALAN_CPP_NAMESPACE::XPathEvaluator	theEvaluator;

		refRetList = theEvaluator.selectNodeList( refRetList, theDOMSupport, 
												pContextNode, 
												(const XALAN_CPP_NAMESPACE::XalanDOMChar*)	( cwszPath ), 
												thePrefixResolver );

		XALAN_CPP_NAMESPACE::XPathEvaluator::terminate();
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}


	return refRetList;
}

XALAN_CPP_NAMESPACE::XalanNode* 
CEMSConfigurationAccessor::GetNode( const wchar_t* cwszPath )
{
	XALAN_CPP_NAMESPACE::XalanNode* pRet = NULL;

	try
	{
		XALAN_CPP_NAMESPACE::XPathEvaluator::initialize();

		XALAN_CPP_NAMESPACE::XalanSourceTreeDOMSupport		theDOMSupport;
		XALAN_CPP_NAMESPACE::XalanSourceTreeParserLiaison	theLiaison(theDOMSupport);

		// Hook the two together...
		theDOMSupport.setParserLiaison(&theLiaison);

		XALAN_CPP_NAMESPACE::XalanNode* pContextNode = _GetXalanNode();

		if( !pContextNode )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		XALAN_CPP_NAMESPACE::XalanDocumentPrefixResolver thePrefixResolver( pContextNode->getOwnerDocument() ? pContextNode->getOwnerDocument() : (XALAN_CPP_NAMESPACE::XalanDocument*) pContextNode );

		XALAN_CPP_NAMESPACE::XPathEvaluator	theEvaluator;

		pRet = theEvaluator.selectSingleNode( theDOMSupport, 
												pContextNode, 
												(const XALAN_CPP_NAMESPACE::XalanDOMChar*)	( cwszPath ), 
												thePrefixResolver );

		XALAN_CPP_NAMESPACE::XPathEvaluator::terminate();
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}

	return pRet;
}

void 
CEMSConfigurationAccessor::DeleteElement( const wchar_t* cwszPath )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// Find the node
		XERCES_CPP_NAMESPACE::DOMXPathEvaluator* pXPath = (XERCES_CPP_NAMESPACE::DOMXPathEvaluator*) m_pNode->getOwnerDocument(); 

		XERCES_CPP_NAMESPACE::DOMXPathResult* pResult = (XERCES_CPP_NAMESPACE::DOMXPathResult *) pXPath->evaluate(cwszPath, 
																							m_pNode->getOwnerDocument(), NULL, 
																							XERCES_CPP_NAMESPACE::DOMXPathResult::ANY_TYPE, 
																							NULL);

		if( pResult )
		{
			if( XERCES_CPP_NAMESPACE::DOMXPathResult::ANY_UNORDERED_NODE_TYPE == pResult->getResultType() )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pNode = pResult->getSingleNodeValue();

				if( pNode )
				{
					m_pNode->removeChild( pNode );
				}
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}

}

void 
CEMSConfigurationAccessor::SetElement( const wchar_t* cwszPath )
{
	_ASSERTE( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void 
CEMSConfigurationAccessor::Insert( const wchar_t* cwszPath, const wchar_t* cwszSerialData )
{
	XERCES_CPP_NAMESPACE::DOMElement* pElement = NULL;
	XERCES_CPP_NAMESPACE::DOMNode* pData = NULL;
	XERCES_CPP_NAMESPACE::DOMNode* pNewChild = NULL;

	try
	{
		if( cwszSerialData )
		{
			if( cwszPath )
			{
				pElement = _GetTextElement( cwszPath );
			}
			else
			{
				if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
				{
					pElement = (XERCES_CPP_NAMESPACE::DOMElement*) m_pNode;

					if( !pElement )
					{
						THROW_NULL_POINTER_EXCEPTION();
					}
				}
			}

			if( !pElement )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			// Load the data into DOM and then append.
			pData = _Load( cwszSerialData );

			if( !pData )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		
			pNewChild = pElement->appendChild( pData );

			if( !pNewChild )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pData->release();
			pData = NULL;
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		
		if( pData )
		{
			pData->release();
			pData = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pData )
		{
			pData->release();
			pData = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		if( pData )
		{
			pData->release();
			pData = NULL;
		}

		throw;
	}
}

CEMSConfigurationAccessor 
CEMSConfigurationAccessor::GetAccessor( const wchar_t* cwszPath )
{
	CEMSConfigurationAccessor oRet;

	try
	{
		if( cwszPath )
		{
			XALAN_CPP_NAMESPACE::XalanNode* pXalanNode = GetNode( cwszPath );

			if( pXalanNode )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pNode = _GetXercesNode( pXalanNode );

				if( pNode )
				{
					oRet.SetSource( pNode );
				}
			}
		}
	}
	catch( ... )
	{
		throw;
	}

	return oRet;
}

CEMSConfigurationAccessor* 
CEMSConfigurationAccessor::GetAccessorEx( const wchar_t* cwszPath )
{
	CEMSConfigurationAccessor* pRet = NULL;

	try
	{
		if( cwszPath )
		{
			XALAN_CPP_NAMESPACE::XalanNode* pXalanNode = GetNode( cwszPath );

			if( pXalanNode )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pNode = _GetXercesNode( pXalanNode );

				if( pNode )
				{
					pRet = new CEMSConfigurationAccessor();

					if( !pRet )
					{
						THROW_NOMEMORY_EXCEPTION();
					}

					pRet->SetSource( pNode );
				}
			}
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		throw;
	}

	return pRet;
}

CEMSObjectList<CEMSConfigurationAccessor> 
CEMSConfigurationAccessor::GetAccessorList( const wchar_t* cwszPath )
{
	CEMSObjectList<CEMSConfigurationAccessor> olstRet;

	try
	{
		if( cwszPath )
		{
			XALAN_CPP_NAMESPACE::NodeRefList olstNodes = GetNodes( cwszPath );

			for( int i = 0; i < olstNodes.getLength(); i++ )
			{
				XALAN_CPP_NAMESPACE::XalanNode* pXalanNode = olstNodes.item( i );

				if( pXalanNode )
				{
					XERCES_CPP_NAMESPACE::DOMNode* pNode = _GetXercesNode( pXalanNode );

					if( pNode )
					{
						CEMSConfigurationAccessor oAccessor;
						oAccessor.SetSource( pNode );

						olstRet.Add( oAccessor );
					}
				}
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}

	return olstRet;

}

CEMSConfigurationAccessor& 
CEMSConfigurationAccessor::operator= ( const CEMSConfigurationAccessor& coRHS ) 
{
	_ReleaseData();

	// This is tricky.  If the source node's document is released then the copied node is gone too.
	// So, clone it to get a complete copy.

	if( coRHS.m_pNode )
	{
		m_pNode = coRHS.m_pNode->cloneNode(true);
	}

	return *this;
}

void
CEMSConfigurationAccessor::Append( const wchar_t* cwszPath, const wchar_t* cwszNewElement, 
								  const wchar_t* cwszValue )
{
	try
	{
		XERCES_CPP_NAMESPACE::DOMElement* pNode = _GetTextElement( cwszPath );

		if( pNode )
		{
			XERCES_CPP_NAMESPACE::DOMElement* pNewNode = pNode->getOwnerDocument()->createElement( cwszNewElement );

			if( !pNewNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pNode->appendChild( pNewNode );

			if( cwszValue )
			{
				pNewNode->setNodeValue( cwszValue );
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}

}

CEMSDOMNode*
CEMSConfigurationAccessor::Append( const wchar_t* cwszPath, const wchar_t* cwszNewElement, 
								  const wchar_t* cwszValue )
{
	CEMSDOMNode* pRetNode = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMElement* pNode = _GetTextElement( cwszPath );

		if( pNode )
		{
			XERCES_CPP_NAMESPACE::DOMElement* pNewNode = pNode->getOwnerDocument()->createElement( cwszNewElement );

			if( !pNewNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pNode->appendChild( pNewNode );

			if( cwszValue )
			{
				pNewNode->setNodeValue( cwszValue );
			}

			pRetNode = new CEMSDOMNode( pNewNode );

			if( !pRetNode )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );

		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		throw e;
	}
	catch( ... )
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		throw;
	}

	return pRetNode;
}


bool 
CEMSConfigurationAccessor::DoesNodeExist( const wchar_t* cwszPath )
{
	bool bRet = false;

	XALAN_CPP_NAMESPACE::XalanNode* pNode = GetNode( cwszPath );

	if( pNode )
	{
		bRet = true;
	}

	return bRet;
}

bool 
CEMSConfigurationAccessor::IsInitialized()
{
	return ( NULL == m_pNode ) ? false : true;
}

INT64 
CEMSConfigurationAccessor::GetAttributeValueHexI64( const wchar_t* cwszPath )
{
	INT64 i64Ret = 0;

	std::wstring owszValue = GetAttributeValue( cwszPath );

	if( !owszValue.empty() )
	{
		i64Ret = CEMSConversionUtil::ConvertHexStringToInt64( owszValue.c_str() );
	}


	return i64Ret;
}

void
CEMSConfigurationAccessor::_ReleaseData()
{
	if( m_pNode )
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::DOCUMENT_NODE == m_pNode->getNodeType() )
		{
			m_pNode->release();
			m_pNode = NULL;
		}
	}

	if( m_pXalanDoc )
	{
		m_pXalanDoc->destroyWrapper();
		m_pXalanDoc = NULL;
	}
}

CEMSObjectList<std::wstring> 
CEMSConfigurationAccessor::_ParseElementPath( const wchar_t* cwszPath )
{
	CEMSObjectList<std::wstring> olstRet;

	if( cwszPath )
	{
		std::wstring wszPath( cwszPath );

		std::wstring::size_type nStartPos = 0;
		
		std::wstring::size_type nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

		if( std::wstring::npos == nEndPos )
		{
			// There's only one level of nesting.
			olstRet.Add( wszPath );
		}
		else
		{
			while( std::wstring::npos !=  nEndPos )
			{
				std::wstring wszToken = wszPath.substr( nStartPos, nEndPos );

				olstRet.Add( wszToken );

				nStartPos = nEndPos + wcslen(ms_cwszElementLevel);

				nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

				if( std::wstring::npos == nEndPos )
				{
					// Grab up to the end of the string.
					if( nStartPos < wszPath.length() )
					{
						wszToken = wszPath.substr( nStartPos );

						olstRet.Add( wszToken );
					}
				}
			}
		}
	}

	return olstRet;
}

CEMSObjectList<std::wstring> 
CEMSConfigurationAccessor::_ParseAttributePath( const wchar_t* cwszPath )
{
	CEMSObjectList<std::wstring> olstRet;

	if( cwszPath )
	{
		// Assuming that the attribute is at the end of the chain.
		// E.g., element/element/@attribute

		std::wstring wszPath( cwszPath );

		std::wstring::size_type nAttributePos = wszPath.find( ms_cwszAttributeIndicator );


		std::wstring::size_type nStartPos = 0;
		
		std::wstring::size_type nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

		while( std::wstring::npos !=  nEndPos && (nEndPos < nAttributePos) )
		{
			std::wstring wszToken = wszPath.substr( nStartPos, nEndPos );

			olstRet.Add( wszToken );

			nStartPos = nEndPos + wcslen(ms_cwszElementLevel);

			nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );
		}

		std::wstring wszAttribute = wszPath.substr( nAttributePos + wcslen(ms_cwszAttributeIndicator) );

		olstRet.Add( wszAttribute );
	}

	return olstRet;
}

XERCES_CPP_NAMESPACE::DOMElement*
CEMSConfigurationAccessor::_GetTextElement( const wchar_t* cwszPath )
{
	//_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	//if( !m_pNode || !cwszPath )
	if( !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	XERCES_CPP_NAMESPACE::DOMElement* pRet = 0;
	XERCES_CPP_NAMESPACE::DOMElement* pNewNode = 0;

	try
	{
		if( m_pNode )
		{
			XALAN_CPP_NAMESPACE::XalanNode* pXalanNode = GetNode( cwszPath );

			if( pXalanNode )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pNode  = _GetXercesNode( pXalanNode );

				if( pNode )
				{
					// Is it an element node?
					if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == pNode->getNodeType() )
					{
						pRet = (XERCES_CPP_NAMESPACE::DOMElement*) pNode;
					}
				}
			}
		}

		if( !pRet )
		{
			// Add it.  Note that cwszPath could be a chain of nodes.  The whole structure needs
			// to be created.
			// Assuming that it is of form:
			//	element1/element2/element3/...
			CEMSObjectList<std::wstring> olstElements = _ParseElementPath( cwszPath );
			olstElements.MoveFirst();
			std::wstring wszElement = olstElements.GetNext();

			// If there is no pre-existing node then the first element in the list becomes it.
			if( !m_pNode )
			{
				if( !wszElement.empty() )
				{
					_CreateRoot( wszElement.c_str() );
				}

				// Move to next.
				wszElement = olstElements.GetNext();
			}

			if( !m_pNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
			{
				pRet = (XERCES_CPP_NAMESPACE::DOMElement*) m_pNode;
			}
			
			if( !pRet )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			while( !wszElement.empty() )
			{
				XERCES_CPP_NAMESPACE::DOMDocument* pDoc = pRet->getOwnerDocument();

				if( !pDoc )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				pNewNode = pDoc->createElement( wszElement.c_str() );

				if( !pNewNode )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}
				
				pNewNode = (XERCES_CPP_NAMESPACE::DOMElement*) pRet->appendChild( pNewNode );

				pRet = pNewNode;

				wszElement = olstElements.GetNext();
			}

			_ASSERTE( pRet );

			if( !pRet )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		}

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		throw;
	}

	return pRet;
}

XERCES_CPP_NAMESPACE::DOMAttr* 
CEMSConfigurationAccessor::_GetAttribute( const wchar_t* cwszPath )
{
	XERCES_CPP_NAMESPACE::DOMAttr* pRet = NULL;

	XALAN_CPP_NAMESPACE::XalanNode* pNode = GetNode( cwszPath );

	if( pNode )
	{
		XERCES_CPP_NAMESPACE::DOMNode* pXercesNode = _GetXercesNode( pNode );

		if( pXercesNode )
		{
			// confirm the type.
			if( XERCES_CPP_NAMESPACE::DOMNode::ATTRIBUTE_NODE == pXercesNode->getNodeType() )
			{
				pRet = (XERCES_CPP_NAMESPACE::DOMAttr*) pXercesNode;
			}
		}
	}

	return pRet;
}

void 
CEMSConfigurationAccessor::_CreateRoot( const wchar_t* cwszRoot )
{
	if( cwszRoot )
	{
		try
		{
			_Init();

			XERCES_CPP_NAMESPACE::DOMElement* pRoot = m_pNode->getOwnerDocument()->createElement( cwszRoot );

			if( pRoot )
			{
				m_pNode->appendChild( pRoot );
			}
		}
		catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
		{
			char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
			CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
			XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
			throw e;
		}
		catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
		{
			char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
			CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
			XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
			throw e;
		}
		catch( ... )
		{
			throw;
		}
	}
}

XERCES_CPP_NAMESPACE::DOMNode*
CEMSConfigurationAccessor::_Load( const wchar_t* cwszXML )
{
	XERCES_CPP_NAMESPACE::DOMNode* pRet = NULL;
	XERCES_CPP_NAMESPACE::XercesDOMParser*  pParser = NULL;

	try
	{  
		if( !cwszXML )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pParser = new XERCES_CPP_NAMESPACE::XercesDOMParser();

		if( !pParser )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		// Does the XML string contain a processing instruction with the xml version.
		// The Xerces parser requires it.
		std::wstring owszXML( cwszXML );
		std::wstring::size_type iPos = owszXML.find( L"xml version=" );
		if( std::wstring::npos == iPos )
		{
			owszXML = L"<?xml version=\"1.0\" standalone=\"no\"?>\n";
			owszXML.append( cwszXML );
		}


		XERCES_CPP_NAMESPACE::MemBufInputSource oMem(	(const XMLByte*) owszXML.c_str(), 
														sizeof(wchar_t)*owszXML.length(), 
														(const XMLCh*) L"" );
		pParser->parse( oMem );

		pRet = pParser->adoptDocument();

		delete pParser;
		pParser = NULL;
	
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch( ... )
	{
		if( pParser )
		{
			delete pParser;
			pParser = NULL;
		}

		throw;
	}

	return pRet;
}

void
CEMSConfigurationAccessor::_Init()
{
	if( !m_pNode )
	{
		XERCES_CPP_NAMESPACE::DOMImplementation *pImpl = XERCES_CPP_NAMESPACE::DOMImplementation::getImplementation();
		m_pNode = pImpl->createDocument();
	}
}

XALAN_CPP_NAMESPACE::XalanNode* 
CEMSConfigurationAccessor::_GetXalanNode()
{
	XALAN_CPP_NAMESPACE::XalanNode* pRet = NULL;

	_InitXalanDoc();

	if( m_pXalanDoc )
	{
		pRet = m_pXalanDoc->mapNode( m_pNode );

		if( !pRet )
		{
			// It could be a doc.
			pRet = m_pXalanDoc;
		}
	}

	return pRet;
}

XERCES_CPP_NAMESPACE::DOMNode* 
CEMSConfigurationAccessor::_GetXercesNode( XALAN_CPP_NAMESPACE::XalanNode* pXalanNode )
{
	XERCES_CPP_NAMESPACE::DOMNode* pRet = NULL;

	if( pXalanNode )
	{
		_InitXalanDoc();

		if( m_pXalanDoc )
		{
			pRet = const_cast<XERCES_CPP_NAMESPACE::DOMNode*>( m_pXalanDoc->mapNode( pXalanNode ) );
		}
	}

	return pRet;
}

void 
CEMSConfigurationAccessor::_InitXalanDoc()
{
	if( m_pNode )
	{
	
		if( !m_pXalanDoc )
		{
			XERCES_CPP_NAMESPACE::DOMDocument* pDoc = NULL;

			if( XERCES_CPP_NAMESPACE::DOMNode::DOCUMENT_NODE == m_pNode->getNodeType() )
			{
				pDoc = (XERCES_CPP_NAMESPACE::DOMDocument*) m_pNode;
			}
			else if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
			{
				pDoc = m_pNode->getOwnerDocument();
			}
			else
			{
				short sType = m_pNode->getNodeType();

				THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
			}

			if( !pDoc )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}


			XALAN_USING_XALAN(XalanMemMgrs)
			XALAN_USING_XALAN(XercesDocumentWrapper)

			m_pXalanDoc = XercesDocumentWrapper::create( XalanMemMgrs::getDefaultXercesMemMgr(), pDoc, 
																		true, true, false );

			if( !m_pXalanDoc )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		}
	}
}


#else // MSXML

CEMSConfigurationAccessor::CEMSConfigurationAccessor() : m_pNode(0)
{
}

CEMSConfigurationAccessor::CEMSConfigurationAccessor( const CEMSConfigurationAccessor& x ) : 
								m_pNode(x.m_pNode), m_owszFile( x.m_owszFile )
{
	// True copy.
	if( x.m_pNode )
	{
		m_pNode = x.m_pNode->CloneNode();
	}
}

CEMSConfigurationAccessor::~CEMSConfigurationAccessor()
{
	_ReleaseData();
}

std::wstring 
CEMSConfigurationAccessor::Serialize()
{
	std::wstring wszRet;

	if( m_pNode )
	{
		wchar_t* wszXML = 0;

		try
		{
			wszXML = m_pNode->GetXML();

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
				delete[] wszXML;
				wszXML = 0;
			}

			throw;
		}
	}

	return wszRet;
}

void 
CEMSConfigurationAccessor::SetSource( CEMSDOMNode* pNode )
{
	_ReleaseData();

	m_pNode = pNode;

	if( m_pNode )
	{
		m_pNode->AddRef();
	}
}

void 
CEMSConfigurationAccessor::SetSource( const wchar_t* cwszXMLString )
{
	_ReleaseData();

	CEMSDOMDocument* pDoc = 0;

	try
	{
		pDoc = new CEMSDOMDocument;

		if( !pDoc )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( pDoc->LoadXML( cwszXMLString ) )
		{
			m_pNode = pDoc->GetRoot();
		}

		pDoc->Release();
		pDoc = 0;

	}
	catch( ... )
	{
		if( pDoc )
		{
			pDoc->Release();
			pDoc = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetSource( const wchar_t* cwszXMLString, const wchar_t* cwszNSString )
{
	_ReleaseData();

	CEMSDOMDocument* pDoc = 0;

	try
	{
		pDoc = new CEMSDOMDocument;

		if( !pDoc )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( pDoc->LoadXML( cwszXMLString ) )
		{
			m_pNode = pDoc->GetRoot();
		}

		pDoc->SetNamespace( cwszNSString );

		pDoc->Release();
		pDoc = 0;

	}
	catch( ... )
	{
		if( pDoc )
		{
			pDoc->Release();
			pDoc = 0;
		}

		throw;
	}
}


void 
CEMSConfigurationAccessor::SetSourceFile( const wchar_t* cwszXMLFile )
{
	_ReleaseData();

	CEMSDOMDocument* pDoc = 0;

	try
	{
		pDoc = new CEMSDOMDocument;

		if( !pDoc )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( pDoc->Load( cwszXMLFile ) )
		{
			m_pNode = pDoc->GetRoot();

			m_owszFile = cwszXMLFile;
		}

		pDoc->Release();
		pDoc = 0;

	}
	catch( ... )
	{
		if( pDoc )
		{
			pDoc->Release();
			pDoc = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::Save( const wchar_t* cwszXMLFile )
{
	CEMSDOMDocument* pDoc = 0;
	wchar_t* wszSerialXML = 0;

	try
	{
		std::wstring owszFile;

		if( !m_pNode )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		if( !cwszXMLFile )
		{
			owszFile = m_owszFile;
		}
		else
		{
			owszFile = cwszXMLFile;
		}

		if( owszFile.empty() )
		{
			THROW_INVALID_ARG_EXCEPTION();
		}

		wszSerialXML = m_pNode->GetXML();
		
		pDoc = new CEMSDOMDocument;

		if( !pDoc )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( pDoc->LoadXML( wszSerialXML ) )
		{
			m_pNode->Release();
			m_pNode = 0;

			m_pNode = pDoc->GetRoot();

			pDoc->Save( owszFile.c_str() );

			m_owszFile = owszFile;
		}

		if( wszSerialXML )
		{
			delete[] wszSerialXML;
			wszSerialXML = 0;
		}

		pDoc->Release();
		pDoc = 0;

	}
	catch( ... )
	{
		if( pDoc )
		{
			pDoc->Release();
			pDoc = 0;
		}

		if( wszSerialXML )
		{
			delete[] wszSerialXML;
			wszSerialXML = 0;
		}

		throw;
	}
}

CEMSDOMNode* 
CEMSConfigurationAccessor::GetNode()
{
	CEMSDOMNode* pRet = m_pNode;

	if( pRet )
	{
		pRet->AddRef();
	}

	return pRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
{
	_ASSERTE( cwszValue );

	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( cwszValue );

		pElement->Release();
		pElement = NULL;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue, const wchar_t* cwszNS )
{
	_ASSERTE( cwszValue );

	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		pElement = _GetTextElement( cwszPath, cwszNS );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( cwszValue );

		pElement->Release();
		pElement = NULL;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValueCDATA( const wchar_t* cwszPath, const wchar_t* cwszValue )
{
	_ASSERTE( cwszValue );

	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		pElement = _GetTextElementCDATA( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValueCDATA( cwszValue );

		pElement->Release();
		pElement = NULL;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

CEMSDOMNode* 
CEMSConfigurationAccessor::GetElement( const wchar_t* cwszPath )
{
	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	
	try
	{
		pElement = m_pNode->SelectSingleNode( cwszPath );
	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	return pElement;
}

std::wstring 
CEMSConfigurationAccessor::GetElementValue( const wchar_t* cwszPath )
{
	std::wstring wszRet;

	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	
	try
	{
		pElement = m_pNode->SelectSingleNode( cwszPath );

		if( pElement )
		{
			wszRet = pElement->GetElementTextEx();

			pElement->Release();
			pElement = 0;
		}

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	return wszRet;
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
{
	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );
	_ASSERTE( cwszValue );

	if( !m_pNode || !cwszPath || !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		// For now, keep it simple.  The Path can only be the attribute name.  That is, it is not
		// really the path to the attribute, but assumes that attribute is a child of the current
		// node.

		// Strip off any leading attribute signifier.
		std::wstring wszAttributeName;
		std::wstring wszPath( cwszPath );
		std::wstring::size_type nAtPos = wszPath.find( ms_cwszAttributeIndicator );

		if( std::wstring::npos != nAtPos )
		{
			_ASSERTE( wszPath.length() > 1 );

			if( wszPath.length() > 1 )
				wszAttributeName = wszPath.substr( nAtPos + 1 );
		}
		else
		{
			wszAttributeName = wszPath;
		}

		m_pNode->SetAttributeText( wszAttributeName.c_str(), cwszValue );
		
/*		if( pElement )
		{
			pElement->SetAttributeText( cwszValue );

			pElement->Release();
			pElement = 0;
		}
		else
		{
			// Add it.  Note that cwszPath could be a chain of nodes.  The whole structure needs
			// to be created.
			// Assuming that it is of form:
			//	element1/element2/element3/@attribute...
			// The attribute is always the last element in the returned list.
			CEMSObjectList<std::wstring> olstElements = _ParseAttributePath( cwszPath );


			// First check if the 
			
			olstElements.MoveFirst();
			std::wstring wszElement = olstElements.GetNext();
			long lProcessed = 0;

			pElement = m_pNode;
			pElement->AddRef();

			while( !wszElement.empty() && lProcessed < (olstElements.Count() - 1) )
			{
				pNewNode = pElement->AddChildNode( wszElement.c_str(), 0 );

				pElement->Release();
				pElement = pNewNode;

				wszElement = olstElements.GetNext();

				lProcessed++;
			}

			_ASSERTE( pElement );

			if( !pElement )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pElement->SetAttributeText( wszElement.c_str(), cwszValue );

			pElement->Release();
			pElement = 0;

		}
*/

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		throw;
	}
}

std::wstring 
CEMSConfigurationAccessor::GetAttributeValue( const wchar_t* cwszPath ) 
{ 
	return GetElementValue( cwszPath ); 
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const double cdValue )
{

	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( cdValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}
		
double 
CEMSConfigurationAccessor::GetElementValueDouble( const wchar_t* cwszPath )
{
	double dRet = 0.0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		dRet = CEMSConversionUtil::ConvertToDouble( wszValue.c_str() );
	}

	return dRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const bool cbValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( cbValue ? ms_cwszFlagValueTrue : ms_cwszFlagValueFalse );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

bool 
CEMSConfigurationAccessor::GetElementValueBoolean( const wchar_t* cwszPath )
{
	bool bRet = false;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( wszValue == ms_cwszFlagValueTrue )
	{
		bRet = true;
	}
	else if( wszValue == ms_cwszFlagValueFalse )
	{
		bRet = false;
	}

	return bRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const ULONG culValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( culValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	//SetElementValue( cwszPath, CEMSConversionUtil::ConvertToString( culValue ).c_str() );
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const ULONG culValue, const wchar_t* cwszNS )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath, cwszNS );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( culValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

}

ULONG 
CEMSConfigurationAccessor::GetElementValueULong( const wchar_t* cwszPath )
{
	ULONG ulRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		ulRet = CEMSConversionUtil::ConvertToULong( wszValue.c_str() );
	}

	return ulRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const EMSTIME ctimeValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		// Convert to string first since CEMSDOMNode does not handle 64 bit integers.
		pElement->SetValue( CEMSConversionUtil::ConvertToString(ctimeValue.intTime).c_str() );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

EMSTIME
CEMSConfigurationAccessor::GetElementValueTime( const wchar_t* cwszPath )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		timeRet = CEMSConversionUtil::ConvertToTime( wszValue.c_str() );
	}

	return timeRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const USHORT cusValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		//pElement->SetValue( CEMSConversionUtil::ConvertToString(cusValue).c_str() );
		pElement->SetValue( (const ULONG) cusValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

//! Get an element value as an unsigned short.
unsigned short 
CEMSConfigurationAccessor::GetElementValueUShort( const wchar_t* cwszPath )
{
	unsigned short usRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		usRet = CEMSConversionUtil::ConvertToUShort( wszValue.c_str() );
	}

	return usRet;
}

short 
CEMSConfigurationAccessor::GetElementValueShort( const wchar_t* cwszPath )
{
	short sRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		sRet = CEMSConversionUtil::ConvertToShort( wszValue.c_str() );
	}

	return sRet;
}

unsigned __int64 
CEMSConfigurationAccessor::GetElementValueUI64( const wchar_t* cwszPath )
{
	unsigned __int64 ui64Ret = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		ui64Ret = CEMSConversionUtil::ConvertHexStringToUInt64( wszValue.c_str() );
	}

	return ui64Ret;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const unsigned __int64 cui64Value )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		// Convert to string first since CEMSDOMNode does not handle 64 bit integers.
		pElement->SetValue( CEMSConversionUtil::ConvertToString(cui64Value).c_str() );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const float cfValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		// Convert to string first since CEMSDOMNode does not handle 64 bit integers.
		pElement->SetValue( cfValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}
		
float 
CEMSConfigurationAccessor::GetElementValueFloat( const wchar_t* cwszPath )
{
	float fRet = 0.0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		fRet = CEMSConversionUtil::ConvertToFloat( wszValue.c_str() );
	}

	return fRet;
}

int
CEMSConfigurationAccessor::GetElementValueInt( const wchar_t* cwszPath )
{
	int iRet = 0;

	std::wstring wszValue = GetElementValue( cwszPath );

	if( !wszValue.empty() )
	{
		iRet = _wtoi( wszValue.c_str() );
	}

	return iRet;
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const BYTE cbyValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( cbyValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const short csValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( csValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetElementValue( const wchar_t* cwszPath, const char ccValue )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->SetValue( ccValue );

		pElement->Release();
		pElement = 0;

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const ULONG culValue )
{
	SetAttributeValue( cwszPath, CEMSConversionUtil::ConvertToString( culValue ).c_str() );
}

ULONG 
CEMSConfigurationAccessor::GetAttributeValueULong( const wchar_t* cwszPath )
{
	ULONG ulRet = 0;

	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	
	try
	{
		pElement = m_pNode->SelectSingleNode( cwszPath );

		if( pElement )
		{
			std::wstring wszValue = pElement->GetElementTextEx();

			pElement->Release();
			pElement = 0;

			if( !wszValue.empty() )
			{
				ulRet = CEMSConversionUtil::ConvertToULong( wszValue.c_str() );
			}
		}

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	return ulRet;
}

bool 
CEMSConfigurationAccessor::GetAttributeValueBoolean( const wchar_t* cwszPath )
{
	bool bRet = false;

	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	
	try
	{
		pElement = m_pNode->SelectSingleNode( cwszPath );

		if( pElement )
		{
			std::wstring wszValue = pElement->GetElementTextEx();

			pElement->Release();
			pElement = 0;

			if( !wszValue.empty() )
			{
				if( wszValue == ms_cwszFlagValueTrue )
				{
					bRet = true;
				}
				else if( wszValue == ms_cwszFlagValueFalse )
				{
					bRet = false;
				}
			}
		}

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	return bRet;;
}

void 
CEMSConfigurationAccessor::SetAttributeValue( const wchar_t* cwszPath, const bool cbValue )
{
	SetAttributeValue( cwszPath, cbValue ? ms_cwszFlagValueTrue : ms_cwszFlagValueFalse );
}

void 
CEMSConfigurationAccessor::AttachChild( CEMSConfigurationAccessor* pChild )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pChildNode = 0;

	try
	{
		if( pChild )
		{
			pChildNode = m_pNode->AddChildNode( pChild->GetElementName().c_str(), L"", true );

			if( !pChildNode )
			{
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( pChild->GetElementName().c_str() );
				oLogParam.AddString( GetElementName().c_str() );

				throw CEMSException( EMS_SOLN_DISP_ADD_CHILD_FAILURE, oLogParam );
			}

			pChild->SetSource( pChildNode );

			pChildNode->Release();
			pChildNode = 0;
		}
	}
	catch( ... )
	{
		if( pChildNode )
		{
			pChildNode->Release();
			pChildNode = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::Attach( CEMSConfigurationAccessor* pChild )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pChildNode = 0;
	CEMSDOMNode* pChildSourceNode = 0;

	try
	{
		if( pChild )
		{
			pChildSourceNode = pChild->GetNode();

			_ASSERTE( pChildSourceNode );

			if( !pChildSourceNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pChildNode = m_pNode->AppendChild( pChildSourceNode );

			if( !pChildNode )
			{
				CEMSLogMsgParam oLogParam;
				oLogParam.AddString( pChild->GetElementName().c_str() );
				oLogParam.AddString( GetElementName().c_str() );

				throw CEMSException( EMS_SOLN_DISP_ADD_CHILD_FAILURE, oLogParam );
			}

			pChild->SetSource( pChildNode );

			pChildSourceNode->Release();
			pChildSourceNode = 0;

			pChildNode->Release();
			pChildNode = 0;
		}
	}
	catch( ... )
	{
		if( pChildNode )
		{
			pChildNode->Release();
			pChildNode = 0;
		}

		if( pChildSourceNode )
		{
			pChildSourceNode->Release();
			pChildSourceNode = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::DetachChild()
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pParentNode = 0;

	try
	{
		// Get its parent
		pParentNode = m_pNode->GetParentNode();

		if( pParentNode )
		{
			// Remove from its parent
			pParentNode->RemoveChild( m_pNode );
		}

		pParentNode->Release();
		pParentNode = 0;
	}
	catch( ... )
	{
		if( pParentNode )
		{
			pParentNode->Release();
			pParentNode = 0;
		}

		throw;
	}
}

CEMSDOMNodeList* 
CEMSConfigurationAccessor::GetNodes( const wchar_t* cwszPath )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNodeList* pList = 0;

	try
	{
		// Get its parent
		pList = m_pNode->SelectNodes( cwszPath );
	}
	catch( ... )
	{
		if( pList )
		{
			pList->Release();
			pList = 0;
		}

		throw;
	}

	return pList;
}

CEMSDOMNode* 
CEMSConfigurationAccessor::GetNode( const wchar_t* cwszPath )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		// Get its parent
		pNode = m_pNode->SelectSingleNode( cwszPath );
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		throw;
	}

	return pNode;
}

void 
CEMSConfigurationAccessor::DeleteElement( const wchar_t* cwszPath )
{
	_ASSERTE( m_pNode );

	if( !m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pNode = 0;
	CEMSDOMNode* pParentNode = 0;

	try
	{
		// Find the node
		pNode = m_pNode->SelectSingleNode( cwszPath );

		if( pNode )
		{
			// Get its parent.
			pParentNode = pNode->GetParentNode();

			if( pParentNode )
			{
				// Remove it from its parent.
				pParentNode->RemoveChild( pNode );

				pParentNode->Release();
				pParentNode = 0;
			}

			pNode->Release();
			pNode = 0;
		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		if( pParentNode )
		{
			pParentNode->Release();
			pParentNode = 0;
		}

		throw;
	}

}

void 
CEMSConfigurationAccessor::SetElement( const wchar_t* cwszPath )
{
	CEMSDOMNode* pElement = 0;

	try
	{
		pElement = _GetTextElement( cwszPath );

		if( !pElement )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		pElement->Release();
		pElement = 0;
	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}
}

void 
CEMSConfigurationAccessor::Insert( const wchar_t* cwszPath, const wchar_t* cwszSerialData )
{
	CEMSDOMNode* pElement = 0;
	CEMSDOMNode* pData = 0;
	CEMSDOMNode* pNewChild = 0;

	try
	{
		if( cwszSerialData )
		{
			if( cwszPath )
			{
				pElement = _GetTextElement( cwszPath );
			}
			else
			{
				pElement = m_pNode;

				if( !pElement )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}


				pElement->AddRef();
			}

			if( !pElement )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			// Load the data into DOM and then append.
			pData = _Load( cwszSerialData );

			if( !pData )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		
			pNewChild = pElement->AppendChild( pData );

			if( !pNewChild )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pNewChild->Release();
			pNewChild = 0;

			pData->Release();
			pData = 0;

			pElement->Release();
			pElement = 0;
		}
	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		if( pData )
		{
			pData->Release();
			pData = 0;
		}

		if( pNewChild )
		{
			pNewChild->Release();
			pNewChild = 0;
		}

		throw;
	}
}

CEMSConfigurationAccessor 
CEMSConfigurationAccessor::GetAccessor( const wchar_t* cwszPath )
{
	CEMSConfigurationAccessor oRet;
	CEMSDOMNode* pNode = 0;

	try
	{
		if( cwszPath )
		{
			pNode = GetNode( cwszPath );

			if( pNode )
			{
				oRet.SetSource( pNode );

				pNode->Release();
				pNode = 0;
			}

		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		throw;
	}

	return oRet;
}

CEMSConfigurationAccessor* 
CEMSConfigurationAccessor::GetAccessorEx( const wchar_t* cwszPath )
{
	CEMSConfigurationAccessor* pRet = NULL;

	CEMSDOMNode* pNode = 0;

	try
	{
		if( cwszPath )
		{
			pNode = GetNode( cwszPath );

			if( pNode )
			{
				pRet = new CEMSConfigurationAccessor();

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pRet->SetSource( pNode );

				pNode->Release();
				pNode = 0;
			}

		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

CEMSObjectList<CEMSConfigurationAccessor> 
CEMSConfigurationAccessor::GetAccessorList( const wchar_t* cwszPath )
{
	CEMSObjectList<CEMSConfigurationAccessor> olstRet;
	CEMSDOMNodeList* pNodeList = 0;
	CEMSDOMNode* pNode = 0;

	try
	{
		if( cwszPath )
		{
			pNodeList = GetNodes( cwszPath );

			if( pNodeList )
			{
				pNode = pNodeList->NextNode();

				while( pNode )
				{
					CEMSConfigurationAccessor oAccessor;
					oAccessor.SetSource( pNode );

					olstRet.Add( oAccessor );

					pNode->Release();
					pNode = 0;

					pNode = pNodeList->NextNode();
				}
			}

			pNodeList->Release();
			pNodeList = 0;
		}
	}
	catch( ... )
	{
		if( pNodeList )
		{
			pNodeList->Release();
			pNodeList = 0;
		}

		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		throw;
	}

	return olstRet;

}

CEMSConfigurationAccessor& 
CEMSConfigurationAccessor::operator= ( const CEMSConfigurationAccessor& coRHS ) 
{
	_ReleaseData();

	m_pNode = coRHS.m_pNode;

	if( m_pNode )
		m_pNode->AddRef();

	return *this;
}

void
CEMSConfigurationAccessor::Append( const wchar_t* cwszPath, const wchar_t* cwszNewElement, 
								  const wchar_t* cwszValue )
{
	CEMSDOMNode* pNode = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		pNode = _GetTextElement( cwszPath );

		if( pNode )
		{
			pNewNode = pNode->AddChildNode( cwszNewElement, cwszValue, true );

			if( pNewNode )
			{
				pNewNode->Release();
				pNewNode = 0;
			}

			pNode->Release();
			pNode = 0;
		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		throw;
	}

}

CEMSConfigurationAccessor*
CEMSConfigurationAccessor::AppendEx( const wchar_t* cwszPath, const wchar_t* cwszNewElement, 
								  const wchar_t* cwszValue )
{
	CEMSConfigurationAccessor* pRet = NULL;

	CEMSDOMNode* pNode = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		pNode = _GetTextElement( cwszPath );

		if( pNode )
		{
			pNewNode = pNode->AddChildNode( cwszNewElement, cwszValue, true );

			if( pNewNode )
			{
				pRet = new CEMSConfigurationAccessor();

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pRet->SetSource( pNewNode );

				pNewNode->Release();
				pNewNode = NULL;
			}

			pNode->Release();
			pNode = NULL;
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = NULL;
		}

		throw;
	}

	return pRet;
}

bool 
CEMSConfigurationAccessor::DoesNodeExist( const wchar_t* cwszPath )
{
	bool bRet = false;

	_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	if( !m_pNode || !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pElement = 0;
	
	try
	{
		pElement = m_pNode->SelectSingleNode( cwszPath );

		if( pElement )
		{
			bRet = true;

			pElement->Release();
			pElement = 0;
		}

	}
	catch( ... )
	{
		if( pElement )
		{
			pElement->Release();
			pElement = 0;
		}

		throw;
	}

	return bRet;
}

bool 
CEMSConfigurationAccessor::IsInitialized()
{
	return ( NULL == m_pNode ) ? false : true;
}

INT64 
CEMSConfigurationAccessor::GetAttributeValueHexI64( const wchar_t* cwszPath )
{
	INT64 i64Ret = 0;

	std::wstring owszValue = GetAttributeValue( cwszPath );

	if( !owszValue.empty() )
	{
		i64Ret = CEMSConversionUtil::ConvertHexStringToInt64( owszValue.c_str() );
	}


	return i64Ret;
}

void
CEMSConfigurationAccessor::_ReleaseData()
{
	if( m_pNode )
	{
		m_pNode->Release();
		m_pNode = 0;
	}
}

CEMSObjectList<std::wstring> 
CEMSConfigurationAccessor::_ParseElementPath( const wchar_t* cwszPath )
{
	CEMSObjectList<std::wstring> olstRet;

	if( cwszPath )
	{
		std::wstring wszPath( cwszPath );

		std::wstring::size_type nStartPos = 0;
		
		std::wstring::size_type nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

		if( std::wstring::npos == nEndPos )
		{
			// There's only one level of nesting.
			olstRet.Add( wszPath );
		}
		else
		{
			while( std::wstring::npos !=  nEndPos )
			{
				std::wstring wszToken = wszPath.substr( nStartPos, nEndPos );

				olstRet.Add( wszToken );

				nStartPos = nEndPos + wcslen(ms_cwszElementLevel);

				nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

				if( std::wstring::npos == nEndPos )
				{
					// Grab up to the end of the string.
					if( nStartPos < wszPath.length() )
					{
						wszToken = wszPath.substr( nStartPos );

						olstRet.Add( wszToken );
					}
				}
			}
		}
	}

	return olstRet;
}

CEMSObjectList<std::wstring> 
CEMSConfigurationAccessor::_ParseAttributePath( const wchar_t* cwszPath )
{
	CEMSObjectList<std::wstring> olstRet;

	if( cwszPath )
	{
		// Assuming that the attribute is at the end of the chain.
		// E.g., element/element/@attribute

		std::wstring wszPath( cwszPath );

		std::wstring::size_type nAttributePos = wszPath.find( ms_cwszAttributeIndicator );


		std::wstring::size_type nStartPos = 0;
		
		std::wstring::size_type nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );

		while( std::wstring::npos !=  nEndPos && (nEndPos < nAttributePos) )
		{
			std::wstring wszToken = wszPath.substr( nStartPos, nEndPos );

			olstRet.Add( wszToken );

			nStartPos = nEndPos + wcslen(ms_cwszElementLevel);

			nEndPos = wszPath.find( ms_cwszElementLevel, nStartPos );
		}

		std::wstring wszAttribute = wszPath.substr( nAttributePos + wcslen(ms_cwszAttributeIndicator) );

		olstRet.Add( wszAttribute );
	}

	return olstRet;
}

CEMSDOMNode* 
CEMSConfigurationAccessor::_GetTextElement( const wchar_t* cwszPath, const wchar_t* cwszNS )
{
	//_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	//if( !m_pNode || !cwszPath )
	if( !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pRet = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		if( m_pNode )
		{
			pRet = m_pNode->SelectSingleNode( cwszPath );
		}

		if( !pRet )
		{
			// Add it.  Note that cwszPath could be a chain of nodes.  The whole structure needs
			// to be created.
			// Assuming that it is of form:
			//	element1/element2/element3/...
			CEMSObjectList<std::wstring> olstElements = _ParseElementPath( cwszPath );
			olstElements.MoveFirst();
			std::wstring wszElement = olstElements.GetNext();

			// If there is no pre-existing node then the first element in the list becomes it.
			if( !m_pNode )
			{
				if( !wszElement.empty() )
				{
					_CreateRoot( wszElement.c_str() );
				}

				// Move to next.
				wszElement = olstElements.GetNext();
			}

			if( !m_pNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet = m_pNode;
			pRet->AddRef();
			
			while( !wszElement.empty() )
			{
				if( !cwszNS )
					pNewNode = pRet->AddChildNode( wszElement.c_str(), 0 );
				else
					pNewNode = pRet->AddChildNode( wszElement.c_str(), 0, cwszNS );

				pRet->Release();
				pRet = pNewNode;

				wszElement = olstElements.GetNext();
			}

			_ASSERTE( pRet );

			if( !pRet )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		}

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		throw;
	}

	return pRet;
}

CEMSDOMNode* 
CEMSConfigurationAccessor::_GetTextElementCDATA( const wchar_t* cwszPath )
{
	//_ASSERTE( m_pNode );
	_ASSERTE( cwszPath );

	//if( !m_pNode || !cwszPath )
	if( !cwszPath )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	CEMSDOMNode* pRet = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		if( m_pNode )
		{
			pRet = m_pNode->SelectSingleNode( cwszPath );
		}

		if( !pRet )
		{
			// Add it.  Note that cwszPath could be a chain of nodes.  The whole structure needs
			// to be created.
			// Assuming that it is of form:
			//	element1/element2/element3/...
			CEMSObjectList<std::wstring> olstElements = _ParseElementPath( cwszPath );
			olstElements.MoveFirst();
			std::wstring wszElement = olstElements.GetNext();

			// If there is no pre-existing node then the first element in the list becomes it.
			if( !m_pNode )
			{
				if( !wszElement.empty() )
				{
					_CreateRoot( wszElement.c_str() );
				}

				// Move to next.
				wszElement = olstElements.GetNext();
			}

			if( !m_pNode )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			pRet = m_pNode;
			pRet->AddRef();
			
			while( !wszElement.empty() )
			{
				pNewNode = pRet->AddChildCDATA( wszElement.c_str(), 0 );

				pRet->Release();
				pRet = pNewNode;

				wszElement = olstElements.GetNext();
			}

			_ASSERTE( pRet );

			if( !pRet )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
		}

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSConfigurationAccessor::_CreateRoot( const wchar_t* cwszRoot )
{
	if( cwszRoot )
	{
		CEMSDOMDocument* pDoc = 0;

		try
		{
			pDoc = new CEMSDOMDocument;

			if( !pDoc )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			pDoc->Initialize( cwszRoot );
			m_pNode = pDoc->GetRoot();

			pDoc->Release();
			pDoc = 0;

		}
		catch( ... )
		{
			if( pDoc )
			{
				pDoc->Release();
				pDoc = 0;
			}

			throw;
		}
	}
}

CEMSDOMNode* 
CEMSConfigurationAccessor::_Load( const wchar_t* cwszXML )
{
	CEMSDOMNode* pRet = 0;
	CEMSDOMDocument* pDoc = 0;

	try
	{
		if( cwszXML )
		{
			pDoc = new CEMSDOMDocument;

			if( !pDoc )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			if( pDoc->LoadXML( cwszXML ) )
			{
				pRet = pDoc->GetRoot();
			}

			pDoc->Release();
			pDoc = 0;
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( pDoc )
		{
			pDoc->Release();
			pDoc = 0;
		}

		throw;
	}

	return pRet;
}

CEMSConfigurationAccessor*
CEMSConfigurationAccessor::AddChildElement( const wchar_t* cwszPath, const wchar_t* cwszElement )
{
	CEMSConfigurationAccessor* pRet = NULL;
	CEMSDOMNode* pNode = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		if( cwszPath )
			pNode = m_pNode->SelectSingleNode( cwszPath );
		else
		{
			pNode = m_pNode;
			pNode->AddRef();
		}

		if( pNode )
		{
			pNewNode = pNode->AddChildNode( cwszElement, NULL, true );

			if( pNewNode )
			{
				pRet = new CEMSConfigurationAccessor();

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pRet->SetSource( pNewNode );

				pNewNode->Release();
				pNewNode = NULL;
			}

			pNode->Release();
			pNode = 0;
		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		throw;
	}

	return pRet;
}

CEMSConfigurationAccessor*
CEMSConfigurationAccessor::AddChildElement( const wchar_t* cwszPath, const wchar_t* cwszElement, const wchar_t* cwszNS )
{
	CEMSConfigurationAccessor* pRet = NULL;
	CEMSDOMNode* pNode = 0;
	CEMSDOMNode* pNewNode = 0;

	try
	{
		if( cwszPath )
			pNode = m_pNode->SelectSingleNode( cwszPath );
		else
		{
			pNode = m_pNode;
			pNode->AddRef();
		}

		if( pNode )
		{
			pNewNode = pNode->AddChildNode( cwszElement, NULL, cwszNS, true );

			if( pNewNode )
			{
				pRet = new CEMSConfigurationAccessor();

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pRet->SetSource( pNewNode );

				pNewNode->Release();
				pNewNode = NULL;
			}

			pNode->Release();
			pNode = 0;
		}
	}
	catch( ... )
	{
		if( pNode )
		{
			pNode->Release();
			pNode = 0;
		}

		if( pNewNode )
		{
			pNewNode->Release();
			pNewNode = 0;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		throw;
	}

	return pRet;
}

#endif
