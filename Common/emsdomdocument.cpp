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
#pragma warning(disable:4786)	// disable compiler warning for debug symbol length

#include <string>
using std::string;
using std::wstring;

#include <emsbase.h>
#include <emsdomdocument.h>

#include <emsdomnodelist.h>
#include <emsdomnode.h>

#include <emserror.h>
#include <emsexcpt.h>

#include "generalmsgs.h"

const wchar_t* cwszNamespaceProperty = L"SelectionNamespaces";

#ifdef USE_APACHE_XERCES
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/domexception.hpp>
#include <xercesc/dom/domimplementation.hpp>
#include <xercesc/framework/membufinputsource.hpp>
#include <xercesc/framework/localfileinputsource.hpp>
#include <xercesc/dom/impl/domwriterimpl.hpp>
#include "xstr.h"

CEMSDOMDocument::CEMSDOMDocument() : CEMSBase("CEMSDOMDocument"), m_pDoc(NULL), 
								m_pRootNode(NULL), m_bLoaded(false)
{
}
 
CEMSDOMDocument::CEMSDOMDocument( CEMSDOMDocument& oDoc ) : CEMSBase("CEMSDOMDocument"),
													m_pDoc(NULL), m_pRootNode(NULL),
													m_bLoaded(oDoc.m_bLoaded)
{
	try
	{
		if( oDoc.m_pDoc )
		{
//			_Init();

//			if( !m_pDoc )
//			{
//				THROW_NULL_POINTER_EXCEPTION();
//			}

			m_pDoc = (XERCES_CPP_NAMESPACE::DOMDocument*) (oDoc.m_pDoc->cloneNode(true));

	//		m_pRootNode = m_pDoc->importNode( oDoc.m_pDoc, true );// = dynamic_cast<XERCES_CPP_NAMESPACE::DOMDocument*>(pDoc->cloneNode (true ) );
			m_pRootNode = m_pDoc->getDocumentElement();
			m_bLoaded = true;
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
}

CEMSDOMDocument::CEMSDOMDocument( XERCES_CPP_NAMESPACE::DOMDocument* pDoc ) : 
										CEMSBase("CEMSDOMDocument"), m_pDoc( NULL ),
										m_pRootNode(NULL), m_bLoaded(false)
{
	try
	{
		if( pDoc )
		{
//			_Init();

//			if( !m_pDoc )
//			{
//				THROW_NULL_POINTER_EXCEPTION();
//			}

			m_pDoc = (XERCES_CPP_NAMESPACE::DOMDocument*) (pDoc->cloneNode(true));

	//		m_pRootNode = m_pDoc->importNode( pDoc, true );// = dynamic_cast<XERCES_CPP_NAMESPACE::DOMDocument*>(pDoc->cloneNode (true ) );
			m_pRootNode = m_pDoc->getDocumentElement();
			m_bLoaded = true;
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
}

CEMSDOMDocument::~CEMSDOMDocument()
{
	Clear();
}
 
void
CEMSDOMDocument::Initialize( const wchar_t* cwszRootName )
{
	if( NULL != m_pRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_ALREADY_INITIALIZED );
	}

	_Init();

	try
	{
		// Create a root node.
		m_pRootNode = (XERCES_CPP_NAMESPACE::DOMNode*) m_pDoc->createElement( X( cwszRootName ) );

		// Now append it to the document to make it the root.
		if( NULL != m_pRootNode )
		{
			m_pDoc->appendChild( m_pRootNode );
		}

		m_bLoaded = true;

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

void 
CEMSDOMDocument::Clear()
{
	if( m_pDoc )
	{
		m_pDoc->release();
		m_pDoc = NULL;
	}

	m_pRootNode = NULL;
}

bool 
CEMSDOMDocument::Load(  const wchar_t* cwszFileName, 
                        bool bAsync, 
                        bool bValidateOnParse)
{
	bool bRet = false;

	_Init();

	XERCES_CPP_NAMESPACE::XercesDOMParser* pParser = NULL;

	try
	{  
		if(bAsync)
		{
			assert( false );
			THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
		}

		if(bValidateOnParse)
		{
		  assert( false );
		  THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
		}

		pParser = new XERCES_CPP_NAMESPACE::XercesDOMParser();

		if( !pParser )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		XERCES_CPP_NAMESPACE::LocalFileInputSource oLocalFile( cwszFileName );

		pParser->parse( oLocalFile );

		if( m_pDoc )
		{
			m_pDoc->release();
			m_pDoc = NULL;
		}

		m_pDoc = pParser->adoptDocument();

		// Set the root node.
		if( m_pRootNode )
		{
			m_pRootNode->release();
			m_pRootNode = NULL;
		}

		m_pRootNode = (XERCES_CPP_NAMESPACE::DOMNode*) m_pDoc->getDocumentElement();

		m_bLoaded = true;

		bRet = true;

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
		delete[] szMessage;
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
		delete[] szMessage;
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

	return bRet;
}

bool
CEMSDOMDocument::LoadXML( const wchar_t* cwszXML )
{
	bool bRet = false;

	_Init();

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

		if( m_pDoc )
		{
			m_pDoc->release();
			m_pDoc = NULL;
		}

		m_pDoc = pParser->adoptDocument();


		// Set the root node.
		if( m_pRootNode )
		{
			m_pRootNode->release();
			m_pRootNode = NULL;
		}

        m_pRootNode = (XERCES_CPP_NAMESPACE::DOMNode*) m_pDoc->getDocumentElement();

		m_bLoaded = true;

		bRet = true;

	
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
		delete[] szMessage;
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
		delete[] szMessage;
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

	return bRet;
}

bool
CEMSDOMDocument::Save( const wchar_t* cwszFileName )
{
	bool bRet = false;

	if( NULL == m_pDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	FILE* fpOut = NULL;

	try
	{
		FILE* fpOut = _wfopen( cwszFileName, L"w+" );

		if( !fpOut )
		{
			THROW_RUNTIME_EXCEPTION( EMS_NO_FILE );
		}

		XERCES_CPP_NAMESPACE::DOMWriterImpl oDOMWriter;
		const XMLCh* cwszValue = X( oDOMWriter.writeToString( *m_pDoc ) );

		fwprintf( fpOut, L"%s", cwszValue );

		fclose( fpOut );
		fpOut = NULL;

		bRet = true;
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
		delete[] szMessage;
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
		delete[] szMessage;
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

	return bRet;
}

CEMSDOMNodeList*
CEMSDOMDocument::SelectNodes( const wchar_t* cwszXPath )
{
	if( NULL == m_pRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNodeList* pNodeList = NULL;

	try
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pRootNode->getNodeType() )
		{
			XERCES_CPP_NAMESPACE::DOMNodeList* pNodeListTemp = ( (XERCES_CPP_NAMESPACE::DOMElement*) m_pRootNode)->getElementsByTagName( cwszXPath );

			if( NULL != pNodeListTemp )
			{
				pNodeList = new CEMSDOMNodeList( pNodeListTemp );

				if( !pNodeList )
				{
					THROW_NOMEMORY_EXCEPTION();
				}
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch( ... )
	{
		if( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}

		throw;
	}

	return pNodeList;
}

CEMSDOMNode*
CEMSDOMDocument::SelectSingleNode( const wchar_t* cwszXPath )
{
	CEMSDOMNode* pRet = NULL;
	CEMSDOMNodeList* pNodeList = NULL;

	try
	{
		pNodeList = SelectNodes( cwszXPath );
		
		if( pNodeList )
		{
			pRet = pNodeList->NextNode();

			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}

		throw;
	}


	return pRet;
}

wchar_t*
CEMSDOMDocument::GetXML()
{
	if( NULL == m_pDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszXML = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMWriterImpl oDOMWriter;
		const XMLCh* cwszValue = X( oDOMWriter.writeToString( *m_pDoc ) );

		size_t iLen = 0;
		if( cwszValue && 
			( (iLen = wcslen(cwszValue)) > 0 ) )
		{
			wszXML = new wchar_t[ iLen + 1 ];
			if( !wszXML )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszXML, 0, sizeof(wchar_t)*(iLen + 1) );
			wcsncpy( wszXML, cwszValue, iLen );

		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( wszXML )
		{
			delete[] wszXML;
			wszXML = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( wszXML )
		{
			delete[] wszXML;
			wszXML = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch( ... )
	{
		if( wszXML )
		{
			delete[] wszXML;
			wszXML = NULL;
		}

		throw;
	}

	return wszXML;
}

CEMSDOMNode*
CEMSDOMDocument::RemoveChild( CEMSDOMNode* pChild )
{
	if( !pChild )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( NULL == m_pRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pRemoveChild = m_pRootNode->removeChild( pChild->GetRaw() );

		if( NULL != pRemoveChild )
		{
			pRetNode = new CEMSDOMNode( pRemoveChild );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
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

CEMSDOMNode*
CEMSDOMDocument::AppendChild( CEMSDOMNode* pNewNode )
{
	if( !pNewNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( NULL == m_pRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pAppendChild = m_pRootNode->appendChild( pNewNode->GetRaw() );

		if( 0 != pAppendChild )
		{
			pRetNode = new CEMSDOMNode( pAppendChild );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
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


CEMSDOMNode*
CEMSDOMDocument::CreateNode( const wchar_t* cwszNodeName )
{
	if( !cwszNodeName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( NULL == m_pDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNewNode = m_pDoc->createElement( X( cwszNodeName ) );

		if( NULL != pNewNode )
		{
			pRetNode = new CEMSDOMNode( pNewNode );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
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

CEMSDOMNode*
CEMSDOMDocument::CreateTextNode( const wchar_t* cwszValue )
{
	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( NULL == m_pDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = NULL;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNewNode = m_pDoc->createTextNode( X( cwszValue ) );

		if( NULL != pNewNode )
		{
			pRetNode = new CEMSDOMNode( pNewNode );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
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


CEMSDOMNode*
CEMSDOMDocument::AddChildNode( const wchar_t* cwszElementName, const wchar_t* cwszValue )
{
	CEMSDOMNode* pRet = 0;

	// First, check if the node exists.
	CEMSDOMNode* pNameNode = SelectSingleNode( cwszElementName );

	if( !pNameNode )
	{
		// Create it.
		pNameNode = CreateNode( cwszElementName );
	}

	if( pNameNode )
	{
		if( wcslen( cwszValue ) > 0 )
			pNameNode->SetElementText( cwszValue );

		// Append it.
		CEMSDOMNode* pAppended = AppendChild( pNameNode );

		if( pAppended )
		{
			pRet = pAppended;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	return pRet;
}

CEMSDOMNode*
CEMSDOMDocument::GetRoot()
{ 
	assert( m_pDoc );

	if( !m_pDoc )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( NULL == m_pRootNode )
	{
		m_pRootNode = m_pDoc->getDocumentElement();
	}

	if( NULL == m_pRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

   return new CEMSDOMNode(m_pRootNode);
}

bool 
CEMSDOMDocument::IsValid()
{
	bool bRet = false;

	// If we have a document then it's valid.  Otherwise, parsing would have failed?
	if( NULL != m_pDoc )
		bRet = true;

	return bRet;
}

void 
CEMSDOMDocument::SetNamespace( const wchar_t* cwszNamespace )
{
	assert( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

std::wstring 
CEMSDOMDocument::GetNamespace()
{
	std::wstring wszRet;

	assert( false );
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );

	return wszRet;
}

CEMSDOMNode* 
CEMSDOMDocument::ImportNode( CEMSDOMNode* pNode, bool bDeep  )
{
	CEMSDOMNode* pRetNode = NULL;

	try
	{
		if( m_pDoc )
		{
			m_pDoc->release();
			m_pDoc = NULL;
		}

		pRetNode = pNode->CloneNode( bDeep );

		XERCES_CPP_NAMESPACE::DOMNode* pNodeTemp = pRetNode->GetRaw();

		if( pRetNode )
		{
			m_pDoc = pNodeTemp->getOwnerDocument();
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRetNode )
		{
			pRetNode->Release();
			pRetNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMDocumentException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		XERCES_CPP_NAMESPACE::XMLString::release( &szMessage );
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
      

void
CEMSDOMDocument::_Init()
{
	if( !m_pDoc )
	{
		XERCES_CPP_NAMESPACE::DOMImplementation *pImpl = XERCES_CPP_NAMESPACE::DOMImplementation::getImplementation();
		m_pDoc = pImpl->createDocument();
	}
}

#else	// MSXML

CEMSDOMDocument::CEMSDOMDocument() : CEMSBase("CEMSDOMDocument"), m_bLoaded(false)
{
}
 
CEMSDOMDocument::CEMSDOMDocument( CEMSDOMDocument& oDoc ) : CEMSBase("CEMSDOMDocument")
{
	if(  0 != m_spDoc )
	{
		m_spDoc.Release();
	}

	if( 0 != m_spRootNode )
	{
		m_spRootNode.Release();
	}

	if( oDoc.m_spDoc != NULL )
   {
		m_spDoc = oDoc.m_spDoc;
   }
   else
   {
      
   }

	if( oDoc.m_spRootNode != NULL)
   {
		m_spRootNode = oDoc.m_spRootNode;
   }

	m_bLoaded = oDoc.m_bLoaded;
}

CEMSDOMDocument::CEMSDOMDocument( MSXML2::IXMLDOMDocumentPtr spDoc ) : CEMSBase("CEMSDOMDocument"), m_spDoc( spDoc )
{
	m_bLoaded = false;

	if( m_spDoc )
	{
		if( m_spDoc->GetdocumentElement() )
			m_bLoaded = true;
	}
}

CEMSDOMDocument::CEMSDOMDocument( MSXML2::IXMLDOMDocument2Ptr spDoc ) : CEMSBase("CEMSDOMDocument"), m_spDoc( spDoc )
{
	m_bLoaded = false;

	if( m_spDoc )
	{
		if( m_spDoc->GetdocumentElement() )
			m_bLoaded = true;
	}
}

CEMSDOMDocument::~CEMSDOMDocument()
{
}
 
void
CEMSDOMDocument::Initialize( const wchar_t* cwszRootName )
{
	if( 0 != m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_ALREADY_INITIALIZED );
	}

	_Init();

	try
	{
		// Create a root node.
		m_spRootNode = m_spDoc->createNode( _variant_t( (long) MSXML2::NODE_ELEMENT ), _bstr_t( cwszRootName ), _bstr_t(L"") );

		// Now append it to the document to make it the root.
		if( 0 != m_spRootNode )
		{
			m_spDoc->appendChild( m_spRootNode );
		}

		m_bLoaded = true;

	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
}

void 
CEMSDOMDocument::Clear()
{
	if( m_spDoc )
	{
		m_spDoc.Release();
		m_spDoc = 0;
	}

	if( m_spRootNode )
	{
		m_spRootNode.Release();
		m_spRootNode = 0;
	}
}

bool 
CEMSDOMDocument::Load(  const wchar_t* cwszFileName, 
                        bool bAsync, 
                        bool bValidateOnParse)
{
	_Init();

	try
	{  
      if(bAsync)
         m_spDoc->async = VARIANT_TRUE;
      else
         m_spDoc->async = VARIANT_FALSE;

     if(bValidateOnParse)
	      m_spDoc->validateOnParse = VARIANT_TRUE;
     else
         m_spDoc->validateOnParse = VARIANT_FALSE;

		BOOL bRet = m_spDoc->load( _bstr_t( cwszFileName ) );

		if( bRet )
		{
			// Set the root node.
			if( m_spRootNode )
			{
				m_spRootNode.Release();
				m_spRootNode = 0;
			}
         m_spRootNode = m_spDoc->GetdocumentElement();

			 m_bLoaded = true;

			return true;
		}
		else
		{
			// Check for parse errors.
			MSXML2::IXMLDOMParseErrorPtr spParseError = m_spDoc->GetparseError();
			if( 0 != spParseError )
			{
				CEMSLogMsgParam oParam;
				oParam.AddString( cwszFileName );
				oParam.AddX( spParseError->GeterrorCode() );
				oParam.AddString( spParseError->Getreason() );
				oParam.AddString( spParseError->GetsrcText() );

				throw CEMSException( EMS_GENERAL_XML_FILE_LOAD_FAIL, oParam  );

			}
			return false;
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}


}

bool
CEMSDOMDocument::LoadXML( const wchar_t* cwszXML )
{
	_Init();

	try
	{
		BOOL bRet = m_spDoc->loadXML( cwszXML );

		if( bRet )
		{
			// Set the root node.
			if( m_spRootNode )
			{
				m_spRootNode.Release();
				m_spRootNode = 0;
			}

			
			m_spRootNode = m_spDoc->GetfirstChild();

			// Make sure that the first child is not a processing instruction.
			while( MSXML2::NODE_ELEMENT != m_spRootNode->GetnodeType() )
			{
				m_spRootNode = m_spRootNode->GetnextSibling();
			}


			m_bLoaded = true;

			return true;
		}
		else
		{
			// Check for parse errors.
			MSXML2::IXMLDOMParseErrorPtr spParseError = m_spDoc->GetparseError();
			if( 0 != spParseError )
			{
				CEMSLogMsgParam oParam;
				oParam.AddX( spParseError->GeterrorCode() );
				oParam.AddString( spParseError->Getreason() );
				oParam.AddString( spParseError->GetsrcText() );

				throw CEMSException( EMS_GENERAL_XML_LOAD_FAIL, oParam  );

			}
			return false;
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
}

bool
CEMSDOMDocument::Save( const wchar_t* cwszFileName )
{
	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		BOOL bRet = m_spDoc->save( _bstr_t( cwszFileName ) );

		if( bRet )
			return true;
		else
			return false;
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
}

CEMSDOMNodeList*
CEMSDOMDocument::SelectNodes( const wchar_t* cwszXPath )
{
	if( 0 == m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNodeList* pNodeList = 0;

	try
	{
		MSXML2::IXMLDOMNodeListPtr spNodeList = m_spRootNode->selectNodes( _bstr_t( cwszXPath ) );

		if( 0 != spNodeList )
		{
			pNodeList = new CEMSDOMNodeList( spNodeList );

			if( !pNodeList )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNodeList;
}

CEMSDOMNode*
CEMSDOMDocument::SelectSingleNode( const wchar_t* cwszXPath )
{
	if( 0 == m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spRootNode->selectSingleNode( _bstr_t( cwszXPath ) );

		if( 0 != spNode )
		{
			pNode = new CEMSDOMNode( spNode );

			if( !pNode )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNode;
}

wchar_t*
CEMSDOMDocument::GetXML()
{
	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszXML = 0;

	try
	{
		_bstr_t bszXML = m_spDoc->Getxml();

		if( bszXML.length() )
		{
			wszXML = new wchar_t[ bszXML.length() + 1 ];
			if( !wszXML )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszXML, 0, sizeof(wchar_t)*(bszXML.length() + 1) );
			wcsncpy( wszXML, bszXML, bszXML.length() );

		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return wszXML;
}

CEMSDOMNode*
CEMSDOMDocument::RemoveChild( CEMSDOMNode* pChild )
{
	if( !pChild )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spRemoveChild = m_spRootNode->removeChild( (MSXML2::IXMLDOMNode*) *pChild );

		if( 0 != spRemoveChild )
		{
			pRetNode = new CEMSDOMNode( spRemoveChild );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
}

CEMSDOMNode*
CEMSDOMDocument::AppendChild( CEMSDOMNode* pNewNode )
{
	if( !pNewNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spAppendChild = m_spRootNode->appendChild( (MSXML2::IXMLDOMNode*) *pNewNode );

		if( 0 != spAppendChild )
		{
			pRetNode = new CEMSDOMNode( spAppendChild );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
}


CEMSDOMNode*
CEMSDOMDocument::CreateNode( const wchar_t* cwszNodeName )
{
	if( !cwszNodeName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		// By default, use the document's namespace.
		std::wstring wszNS = GetNamespaceURI();

		MSXML2::IXMLDOMNodePtr spNewNode = m_spDoc->createNode( _variant_t( (long) MSXML2::NODE_ELEMENT) , 
								_bstr_t( cwszNodeName ), wszNS.empty() ? _bstr_t(L"") : wszNS.c_str() );

		if( 0 != spNewNode )
		{
			pRetNode = new CEMSDOMNode( spNewNode );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
	
}

CEMSDOMNode*
CEMSDOMDocument::CreateNode( const wchar_t* cwszNodeName, const wchar_t* cwszNS )
{
	if( !cwszNodeName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		std::wstring wszNS = cwszNS;

		MSXML2::IXMLDOMNodePtr spNewNode = m_spDoc->createNode( _variant_t( (long) MSXML2::NODE_ELEMENT) , 
								_bstr_t( cwszNodeName ), wszNS.empty() ? _bstr_t(L"") : wszNS.c_str() );

		if( 0 != spNewNode )
		{
			pRetNode = new CEMSDOMNode( spNewNode );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
	
}

CEMSDOMNode*
CEMSDOMDocument::CreateCDATA( const wchar_t* cwszNodeName )
{
	if( !cwszNodeName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		// By default, use the document's namespace.
		std::wstring wszNS = GetNamespace();

		MSXML2::IXMLDOMNodePtr spNewNode = m_spDoc->createNode( _variant_t( (long) MSXML2::NODE_CDATA_SECTION) , 
								_bstr_t( cwszNodeName ), wszNS.empty() ? _bstr_t(L"") : wszNS.c_str() );

		if( 0 != spNewNode )
		{
			pRetNode = new CEMSDOMNode( spNewNode );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
	
}

CEMSDOMNode*
CEMSDOMDocument::CreateTextNode( const wchar_t* cwszValue )
{
	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNewNode = m_spDoc->createTextNode(_bstr_t( cwszValue));

		if( 0 != spNewNode )
		{
			pRetNode = new CEMSDOMNode( spNewNode );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMDocumentException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
	
}


CEMSDOMNode*
CEMSDOMDocument::AddChildNode( const wchar_t* cwszElementName, const wchar_t* cwszValue )
{
	CEMSDOMNode* pRet = 0;

	// First, check if the node exists.
	CEMSDOMNode* pNameNode = SelectSingleNode( cwszElementName );

	if( !pNameNode )
	{
		// Create it.
		pNameNode = CreateNode( cwszElementName );
	}

	if( pNameNode )
	{
		if( wcslen( cwszValue ) > 0 )
			pNameNode->SetElementText( cwszValue );

		// Append it.
		CEMSDOMNode* pAppended = AppendChild( pNameNode );

		if( pAppended )
		{
			pRet = pAppended;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	return pRet;
}

CEMSDOMNode*
CEMSDOMDocument::GetRoot()
{ 
	if( 0 == m_spRootNode )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   return new CEMSDOMNode(m_spRootNode);
}

bool 
CEMSDOMDocument::IsValid()
{
	bool bRet = false;

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	MSXML2::IXMLDOMParseErrorPtr spParseError = m_spDoc->validate();

	if( S_OK == spParseError->errorCode )
		bRet = true;
	else
	{
		OutputDebugStringW( spParseError->Getreason() );
		OutputDebugStringW( spParseError->GetsrcText() );
	}

	return bRet;

}

void 
CEMSDOMDocument::SetNamespace( const wchar_t* cwszNamespace )
{
	if( !cwszNamespace )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	_bstr_t bszProperty( cwszNamespaceProperty );
	_bstr_t bszNamespace( cwszNamespace );
	HRESULT hr = m_spDoc->setProperty( bszProperty, _variant_t( bszNamespace ) );

	if( FAILED(hr) )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( hr );
	}
}

std::wstring 
CEMSDOMDocument::GetNamespace()
{
	std::wstring wszRet;

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	_bstr_t bszProperty( cwszNamespaceProperty );
	_variant_t vNamespace = m_spDoc->getProperty( bszProperty );

	if( vNamespace.vt == VT_BSTR && vNamespace.bstrVal )
	{
		wszRet = vNamespace.bstrVal;
	}

	return wszRet;
}

std::wstring 
CEMSDOMDocument::GetNamespaceURI()
{
	std::wstring wszRet;

	if( 0 == m_spDoc )
	{
		THROW_DOM_DOCUMENT_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	BSTR bszProperty = NULL;
	//_variant_t vNamespace = m_spDoc->get_namespaceURI( bszProperty );
	EMS_RESULT hr = m_spDoc->get_namespaceURI( &bszProperty );

	//if( vNamespace.vt == VT_BSTR && vNamespace.bstrVal )
	//{
	//	wszRet = vNamespace.bstrVal;
	//}

	if( bszProperty )
	{
		wszRet = bszProperty;
		SysFreeString(bszProperty);
	}

	

	return wszRet;
}
      

void
CEMSDOMDocument::_Init()
{
	if( 0 == m_spDoc )
	{
#ifdef _64BITS
		HRESULT hr = m_spDoc.CreateInstance(__uuidof(MSXML2::FreeThreadedDOMDocument60));
#else
		HRESULT hr = m_spDoc.CreateInstance(__uuidof(MSXML2::FreeThreadedDOMDocument40));
#endif

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}
}

#endif
