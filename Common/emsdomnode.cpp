#pragma warning(disable:4786)

#include <string>
using std::string;
using std::wstring;

#include <criticalsection.h>
#include <emsbase.h>

#include <emsdomnode.h>

#include <emsdomnodelist.h>
#include <emsdomdocument.h>

#include "convutility.h"

#include <emserror.h>
#include <emsexcpt.h>

#ifdef USE_APACHE_XERCES
#include <xercesc/dom/domexception.hpp>
#include <xercesc/dom/domdocument.hpp>
#include <xercesc/dom/domelement.hpp>
#include <xercesc/dom/domtext.hpp>
#include <xercesc/dom/impl/domwriterimpl.hpp>
#include "xstr.h"
#include "convutility.h"

CEMSDOMNode::CEMSDOMNode( XERCES_CPP_NAMESPACE::DOMNode* pNode ) : CEMSBase("CEMSDOMNode"), m_pNode( pNode )
{
}

CEMSDOMNode::CEMSDOMNode( CEMSDOMNode& oNode ) : CEMSBase("CEMSDOMNode"), m_pNode( oNode.m_pNode )
{
}

CEMSDOMNode::~CEMSDOMNode()
{
}

CEMSDOMNode*
CEMSDOMNode::AppendChild( CEMSDOMNode* pChild )
{
	if( !pChild )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pAppendChild = m_pNode->appendChild( (XERCES_CPP_NAMESPACE::DOMNode*) pChild );

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
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
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
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pRetNode;
}

CEMSDOMNode*
CEMSDOMNode::CloneNode( bool bDeep )
{
	CEMSDOMNode* pRet = 0;

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	XERCES_CPP_NAMESPACE::DOMNode* pTempNode = 0;

	try
	{
		pTempNode = m_pNode->cloneNode( bDeep );

		if( 0 != pTempNode )
		{
			pRet = new CEMSDOMNode( pTempNode );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pRet;
}

CEMSDOMNodeList*
CEMSDOMNode::SelectNodes( const wchar_t* cwszXPath )
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNodeList* pRet = 0;
/*
	try
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
		{
			XERCES_CPP_NAMESPACE::DOMXPathEvaluator* pXPath = (XERCES_CPP_NAMESPACE::DOMXPathEvaluator*) m_pNode->getOwnerDocument(); 

			if( pXPath )
			{
				XERCES_CPP_NAMESPACE::DOMXPathResult* pXPres = (XERCES_CPP_NAMESPACE::DOMXPathResult *) pXPath->evaluate(cwszXPath, m_pNode, 
																											NULL, 
																											XERCES_CPP_NAMESPACE::DOMXPathResult::ANY_UNORDERED_NODE_TYPE, NULL); 


				XERCES_CPP_NAMESPACE::DOMElement* pElement = (XERCES_CPP_NAMESPACE::DOMElement*) m_pNode;

				if( !pElement )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				XERCES_CPP_NAMESPACE::DOMNodeList* pNodeList = pElement->getElementsByTagName( cwszXPath );


				if( pXPres )
				{
					if( 0 != pNodeList )
					{
						pRet = new CEMSDOMNodeList( pNodeList );

						if( !pRet )
						{
							THROW_NOMEMORY_EXCEPTION();
						}
					}
				}
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
*/
	return pRet;
}

CEMSDOMNode*
CEMSDOMNode::SelectSingleNode( const wchar_t* cwszXPath )
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRet = 0;

	try
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
		{
			XERCES_CPP_NAMESPACE::DOMElement* pElement = (XERCES_CPP_NAMESPACE::DOMElement*) m_pNode;

			if( !pElement )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}


			if( cwszXPath )
			{
				if( L'@' == cwszXPath[0] )
				{
					XERCES_CPP_NAMESPACE::DOMAttr* pAttr = pElement->getAttributeNode( cwszXPath );

					const XMLCh * sz = pElement->getTextContent();

					if( pAttr )
					{
						pRet = new CEMSDOMNode( pAttr );

						if( !pRet )
						{
							THROW_NOMEMORY_EXCEPTION();
						}
					}
				}
				else
				{
					XERCES_CPP_NAMESPACE::DOMNodeList* pNodeList = pElement->getElementsByTagName( cwszXPath );

					if( 0 != pNodeList &&
						pNodeList->getLength() > 0 )
					{
						// Just get the first element in the list.
						XERCES_CPP_NAMESPACE::DOMNode* pNode = pNodeList->item( 0 );

						if( pNode )
						{
							pRet = new CEMSDOMNode( pNode );

							if( !pRet )
							{
								THROW_NOMEMORY_EXCEPTION();
							}
						}
					}
				}
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pRet;
}

wchar_t*
CEMSDOMNode::GetElementText()
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszText = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNode = m_pNode->getFirstChild();

		if( 0 != pNode )
		{
			// See if the child is a text node.

			if( XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE == pNode->getNodeType() )
			{
				XERCES_CPP_NAMESPACE::DOMText* pText = (XERCES_CPP_NAMESPACE::DOMText*) pNode;

				if( 0 != pText )
				{
					const XMLCh* cwszValue = X( pText->getNodeValue() );

					if( cwszValue )
					{
						size_t iLen = wcslen( cwszValue );

						wszText = new wchar_t[ iLen + 1 ];

						if( !wszText )
						{
							THROW_NOMEMORY_EXCEPTION();
						}
							
						memset( wszText, 0, sizeof(wchar_t)*( iLen + 1 ) );

						wcsncpy( wszText, cwszValue, iLen );
					}
				}
			}

		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( wszText )
		{
			delete[] wszText;
			wszText = 0;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( wszText )
		{
			delete[] wszText;
			wszText = 0;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return wszText;
}

std::wstring
CEMSDOMNode::GetElementTextEx()
{
	std::wstring wszRet;

	wchar_t* wszTemp = GetElementText();

	if( wszTemp && 
		wcslen( wszTemp ) > 0 )
	{
		wszRet = wszTemp;

		delete[] wszTemp;
		wszTemp = NULL;
	}

	return wszRet;
}

void
CEMSDOMNode::SetElementText( const wchar_t* cwszText )
{
	if( !cwszText )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNode = m_pNode->getFirstChild();

		if( 0 != pNode )
		{
			// See if the child is a text node.
			if( XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE == pNode->getNodeType() )
			{
				pNode->setNodeValue( X( cwszText ) );
			}
		}
		else
		{

			XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();

			if( pDoc )
			{
				pNode = pDoc->createTextNode( X( cwszText ) );
			}

			if( pNode )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pAppended = m_pNode->appendChild( pNode  );
			}
		}

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

void 
CEMSDOMNode::SetAttributeText( const wchar_t* cwszAttributeName, const wchar_t* cwszText )
{
	if( !cwszText )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::ELEMENT_NODE == m_pNode->getNodeType() )
		{
			XERCES_CPP_NAMESPACE::DOMElement* pElement = (XERCES_CPP_NAMESPACE::DOMElement*) m_pNode;

			if( 0 != pElement )
			{
				pElement->setAttribute( X(cwszAttributeName), X(cwszText) );
			}
		}

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

void 
CEMSDOMNode::SetAttributeText( const wchar_t* cwszValue )
{
	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_pNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		if( XERCES_CPP_NAMESPACE::DOMNode::ATTRIBUTE_NODE == m_pNode->getNodeType() )
		{
			m_pNode->setNodeValue( X(cwszValue) );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

wchar_t*
CEMSDOMNode::GetXML()
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszXML = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMWriterImpl oDOMWriter;
		const XMLCh* cwszValue = oDOMWriter.writeToString( *m_pNode );
		
		size_t iLen = 0;

		if( cwszValue && 
			(iLen = wcslen(cwszValue)) > 0 )
		{
			wszXML = new wchar_t[ iLen + 1 ];
			
			if( !wszXML )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszXML, 0, (iLen + 1)*sizeof(wchar_t) );

			wcsncpy( wszXML, cwszValue, iLen);

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
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
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
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return wszXML;
}

CEMSDOMDocument*
CEMSDOMNode::GetOwnerDocument()
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMDocument* pRet = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();

		if( 0 != pDoc )
		{
			pRet = new CEMSDOMDocument( pDoc );
		}
		else
		{
			THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pRet;
}


CEMSDOMNode*
CEMSDOMNode::AddChildNode( const wchar_t* cwszElementName, 
                           const wchar_t* cwszValue,
                           bool  bForceAdd)
{
	CEMSDOMNode* pNewNode = NULL;


	
	CEMSDOMNode* pNameNode = NULL;
   // if ForcedAdd is false, then no duplicate are allowed, the existing node will be updated
   if(!bForceAdd)
      pNameNode =  SelectSingleNode( cwszElementName );
   
   CEMSDOMDocument* pDoc = GetOwnerDocument();

   // bForcedAdd was set to true, or the node did not exist, we will try to add it
	if( 0 == pNameNode )
	{
		// Create it.
		if( pDoc )
		{
			pNameNode = pDoc->CreateNode( cwszElementName );
		}
	}

	if( 0 != pNameNode )
	{
		if( cwszValue )
		{
			if( wcslen( cwszValue ) > 0 )
				pNameNode->SetElementText( cwszValue );
		}
         
       
 	   // Append it.
		CEMSDOMNode* pAppendedNode = AppendChild( pNameNode );
     
		if( 0 != pAppendedNode )
		{
			pNewNode = pAppendedNode;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	if( pDoc )
	{
		pDoc->Release();
		pDoc = 0;
	}

	return pNewNode;
}

XERCES_CPP_NAMESPACE::DOMNode*
CEMSDOMNode::GetRaw()
{
	return m_pNode;
}

int 
CEMSDOMNode::ChildCount( const wchar_t* pwcsNodeName )
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

   CEMSDOMNodeList* pNodeList = SelectNodes( pwcsNodeName );       

   if(0 == pNodeList)
      THROW_DOM_NODE_EXCEPTION(EMS_UNKNOWN_ERROR);
   return pNodeList->GetLength();

}



wchar_t*
CEMSDOMNode::GetNodeName() const 
{ 
	wchar_t* wszRet = 0;

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	const XMLCh* szTemp = X( m_pNode->getNodeName() ); 

	if( szTemp )
	{
		size_t iLen = wcslen( szTemp );

		wszRet = new wchar_t[ iLen + 1 ];

		if( !wszRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( wszRet, 0, (iLen+1)*sizeof(wchar_t) );

		wcscpy( wszRet, szTemp );
	}
   
	return wszRet;
}

std::wstring
CEMSDOMNode::GetNodeNameEx() const 
{ 
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
	
	return std::wstring( X(m_pNode->getNodeName()) ); 
}



CEMSDOMNode*
CEMSDOMNode::GetChildAt( const wchar_t* cwszName, int iIndex )
{
	CEMSDOMNode* pRet = NULL;

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	int iCount = 0;

	XERCES_CPP_NAMESPACE::DOMNode* pChild = m_pNode->getFirstChild();

	while(	pChild && 
			!pRet )
	{
		if( CompareChildName( pChild, cwszName ) )
		{
			if( iCount++ == iIndex )
			{
				pRet = new CEMSDOMNode( pChild );

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}
			}
		}

		pChild = m_pNode->getNextSibling();
	}

	return pRet;
}



CEMSDOMNode*
CEMSDOMNode::RemoveChildAt( const wchar_t* cwszName, int iIndex)
{
	CEMSDOMNode* pNodeOut = NULL;
	
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   
	int iCount = 0;
	XERCES_CPP_NAMESPACE::DOMNode* pChild = m_pNode->getFirstChild();

	while( pChild && !pNodeOut )
	{
		if ( CompareChildName( pChild, cwszName ) )
		{
			if (iCount++ == iIndex)
			{
				try
				{
					XERCES_CPP_NAMESPACE::DOMNode* pNodeOutTemp = m_pNode->removeChild( pChild );
					if(0 != pNodeOutTemp)
					{
						pNodeOut = new CEMSDOMNode(pChild);

						if( !pNodeOut )
						{
							THROW_NOMEMORY_EXCEPTION();
						}
					}
				}
				catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
				{
					if( pNodeOut )
					{
						pNodeOut->Release();
						pNodeOut = NULL;
					}

					char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
					CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
					delete[] szMessage;
					throw e;
				}
				catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
				{
					if( pNodeOut )
					{
						pNodeOut->Release();
						pNodeOut = NULL;
					}

					char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
					CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
					delete[] szMessage;
					throw e;
				}
			}
		}
	}
  
	return pNodeOut;
}



bool 
CEMSDOMNode::CompareChildName( XERCES_CPP_NAMESPACE::DOMNode* pChild, const wchar_t* cwszName )
{
   if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
	return( 0 == wcsicmp( X(pChild->getNodeName()), cwszName) );
}

wchar_t*
CEMSDOMNode::GetChildText( const wchar_t* cwszName )
{
   if( 0 == m_pNode )
   {
      THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
   }
                                                            // this will be used to form the XPath
   CEMSDOMNode* pNode = SelectSingleNode( cwszName );       // Build the XPath buffer

   if( 0 != pNode)
   {
      return pNode->GetElementText();
   }
   return 0;
}

CEMSDOMNode*
CEMSDOMNode::RemoveChildNode( const wchar_t* cwszName )
{

   CEMSDOMNode* pNodeOut = NULL;

	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

   CEMSDOMNode* pChild = SelectSingleNode( cwszName ); 

   if( 0 == pChild)
      return pChild;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNodeOutTemp = m_pNode->removeChild( pChild->GetRaw() );
		if( 0 != pNodeOutTemp)
		{
			pNodeOut = new CEMSDOMNode(pNodeOutTemp);

			if( !pNodeOut )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
      
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pNodeOut )
		{
			pNodeOut->Release();
			pNodeOut = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pNodeOut )
		{
			pNodeOut->Release();
			pNodeOut = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
      
   return pNodeOut;
}

CEMSDOMNode*
CEMSDOMNode::InsertChildNode( const wchar_t* pwcsName, 
                              const wchar_t* pwcsValue )
{
   if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   try
   {
      bool bExists = false;
	  XERCES_CPP_NAMESPACE::DOMNode* pChild = m_pNode->getFirstChild();

	  while( pChild )
      //for (MSXML2::IXMLDOMNodePtr spChild = m_spNode->firstChild; spChild; spChild = spChild->nextSibling)
	  { 
		
		if ( CompareChildName( pChild, pwcsName ) )
		{
            bExists = true;

			XERCES_CPP_NAMESPACE::DOMNode* pRefChild = pChild->getNextSibling();
            
		    CEMSDOMDocument* pDoc = GetOwnerDocument();
            CEMSDOMNode* pNameNode = NULL;
            if( 0 != pDoc )   
            {
               pNameNode = pDoc->CreateNode( pwcsName );
               if(0 == pNameNode)
			   {
                  THROW_DOM_NODE_EXCEPTION(EMS_UNKNOWN_ERROR);
			   }

               pNameNode->SetElementText( pwcsValue );

            }
            else
			{
               THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
			}

			pChild->setNodeValue( X( pwcsValue ) );
            //spChild->text = bstr_t(pwcsValue);
            
		      // insert it at the right spot
		    if( 0 != m_pNode->insertBefore(pChild, pRefChild))
            {
               return new CEMSDOMNode(pChild);
            }
            else
            {
               THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
            }
         }
      }
      // no child nodes, so just append it.
      if(!bExists)
      {
         return AddChildNode(pwcsName, pwcsValue);
      }
   }
   catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

   return 0;
}


CEMSDOMNode* 
CEMSDOMNode::GetParentNode()
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRet = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pParent = m_pNode->getParentNode();

		if( 0 != pParent )
		{
			pRet = new CEMSDOMNode( pParent );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pRet;
}
	
void 
CEMSDOMNode::RemoveChild( CEMSDOMNode* pNode )
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		m_pNode->removeChild( pNode->GetRaw() );
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

void 
CEMSDOMNode::SetValue( const double cdValue )
{
	SetValue( CEMSConversionUtil::ConvertToString( cdValue ).c_str() );
}

void 
CEMSDOMNode::SetValue( const ULONG culValue )
{
	SetValue( CEMSConversionUtil::ConvertToString( culValue ).c_str() );
}

void 
CEMSDOMNode::SetValue( const INT64 ci64Value )
{
	SetValue( CEMSConversionUtil::ConvertToString( ci64Value ).c_str() );
}

void 
CEMSDOMNode::SetValue( const short csValue )
{
	SetValue( CEMSConversionUtil::ConvertToString( csValue ).c_str() );
}

void 
CEMSDOMNode::SetValue( const BYTE cbyValue )
{
	SetValue( CEMSConversionUtil::ConvertToString( cbyValue ).c_str() );
}

void 
CEMSDOMNode::SetValue( const char ccValue )
{
	SetValue( CEMSConversionUtil::ConvertToString( ccValue ).c_str() );
}

void 
CEMSDOMNode::SetValue( const wchar_t* cwszValue )
{
	if( 0 == m_pNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pNode = m_pNode->getFirstChild();

		XERCES_CPP_NAMESPACE::DOMText* pText = NULL;

		if( 0 != pNode )
		{
			// See if the child is a text node.
			if( XERCES_CPP_NAMESPACE::DOMNode::TEXT_NODE == pNode->getNodeType() )
			{
				pText = (XERCES_CPP_NAMESPACE::DOMText*) pNode;
			}

		}
		else
		{
			XERCES_CPP_NAMESPACE::DOMDocument* pDoc = m_pNode->getOwnerDocument();
			if( pDoc )
			{
				pNode = pDoc->createTextNode( X(L"") );
			}

			if( pNode )
			{
				XERCES_CPP_NAMESPACE::DOMNode* pAppended = m_pNode->appendChild( pNode );

				pText = (XERCES_CPP_NAMESPACE::DOMText*) pNode;
			}

		}

		if( 0 != pText )
		{
			pText->setNodeValue( X(cwszValue) );
		}

	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
}

#else	// MSXML4 implementation.

CEMSDOMNode::CEMSDOMNode( MSXML2::IXMLDOMNodePtr spNode ) : CEMSBase("CEMSDOMNode"), m_spNode( spNode )
{
}

CEMSDOMNode::CEMSDOMNode( CEMSDOMNode& oNode ) : CEMSBase("CEMSDOMNode"), m_spNode( oNode.m_spNode )
{
}

CEMSDOMNode::~CEMSDOMNode()
{
}

CEMSDOMNode*
CEMSDOMNode::AppendChild( CEMSDOMNode* pChild )
{
	if( !pChild )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRetNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spAppendChild = m_spNode->appendChild( (MSXML2::IXMLDOMNode*) *pChild );

		if( 0 != spAppendChild )
		{
			pRetNode = new CEMSDOMNode( spAppendChild );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRetNode;
}

CEMSDOMNode*
CEMSDOMNode::CloneNode( bool bDeep )
{
	CEMSDOMNode* pRet = 0;

	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->cloneNode( bDeep ? VARIANT_TRUE : VARIANT_FALSE );

		if( 0 != spNode )
		{
			pRet = new CEMSDOMNode( spNode );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRet;
}

CEMSDOMNodeList*
CEMSDOMNode::SelectNodes( const wchar_t* cwszXPath )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNodeList* pNodeList = 0;

	try
	{
		MSXML2::IXMLDOMNodeListPtr spNodeList = m_spNode->selectNodes( _bstr_t( cwszXPath ) );

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
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNodeList;
}

CEMSDOMNode*
CEMSDOMNode::SelectSingleNode( const wchar_t* cwszXPath )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->selectSingleNode( _bstr_t( cwszXPath ) );

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
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNode;
}

wchar_t*
CEMSDOMNode::GetElementText()
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszText = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			MSXML2::IXMLDOMTextPtr spText = spNode;

			if( 0 != spText )
			{
				_bstr_t bszText = spText->Gettext();

				if( bszText.length() > 0 )
				{
#ifdef __COMALLOC
					wszText = (wchar_t*) CoTaskMemAlloc( (bszText.length() + 1)*sizeof(wchar_t) );
#else
					wszText = new wchar_t[ bszText.length() + 1 ];
#endif
					if( !wszText )
					{
						THROW_NOMEMORY_EXCEPTION();
					}
						
					memset( wszText, 0, sizeof(wchar_t)*( bszText.length() + 1 ) );

					wcsncpy( wszText, bszText, bszText.length() );
				}
			}

		}
	}
	catch( _com_error& e ) 
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return wszText;
}

std::wstring
CEMSDOMNode::GetElementTextEx()
{
	std::wstring wszRet;

	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			MSXML2::IXMLDOMTextPtr spText = spNode;

			if( 0 != spText )
			{
				_bstr_t bszText = spText->Gettext();

				if( bszText.length() > 0 )
				{
					wszRet = bszText;
				}
			}
		}
	}
	catch( _com_error& e ) 
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return wszRet;
}

void
CEMSDOMNode::SetElementText( const wchar_t* cwszText )
{
	if( !cwszText )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		MSXML2::IXMLDOMTextPtr spText;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			spText = spNode;

			if( 0 != spText )
			{
				spText->Puttext( _bstr_t( cwszText ) );
			}

		}
		else
		{
			MSXML2::IXMLDOMDocument2Ptr spDoc = m_spNode->GetownerDocument();

			if( spDoc )
			{
				spNode = spDoc->createTextNode( _bstr_t(cwszText) );
			}

			if( spNode )
			{
				MSXML2::IXMLDOMNodePtr spAppended = m_spNode->appendChild( spNode  );
			}
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}


}

void 
CEMSDOMNode::SetAttributeText( const wchar_t* cwszAttributeName, const wchar_t* cwszText )
{
	if( !cwszText )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		MSXML2::IXMLDOMElementPtr spElement = m_spNode;

		if( 0 != spElement )
		{
			spElement->setAttribute( cwszAttributeName, cwszText );
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
}

std::wstring
CEMSDOMNode::GetAttributeText( const wchar_t* cwszAttributeName )
{
	std::wstring wszRet;

	if( 0 == m_spNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		MSXML2::IXMLDOMElementPtr spElement = m_spNode;

		if( 0 != spElement )
		{
			_variant_t vValue = spElement->getAttribute(cwszAttributeName);
			if (vValue.vt != VT_NULL )
			    wszRet = _bstr_t( vValue );
		}
	}
	catch( _com_error& e ) 
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return wszRet;
}

//new method
double 
CEMSDOMNode::GetAttributeValueDouble( const wchar_t* cwszAttributeName )
{
	double dRet = 0.0;

	std::wstring wszValue = GetAttributeText( cwszAttributeName );

	if( !wszValue.empty() )
	{
		dRet = CEMSConversionUtil::ConvertToDouble( wszValue.c_str() );
	}

	return dRet;
}

//New method
float 
CEMSDOMNode::GetAttributeValueFloat( const wchar_t* cwszAttributeName )
{
	float fRet = 0.0;

	std::wstring wszValue = GetAttributeText( cwszAttributeName );

	if( !wszValue.empty() )
	{
		fRet = CEMSConversionUtil::ConvertToFloat( wszValue.c_str() );
	}

	return fRet;
}

//new method
bool 
CEMSDOMNode::GetAttributeValueBoolean( const wchar_t* cwszAttributeName )
{
	bool bRet = false;

	std::wstring wszValue = GetAttributeText( cwszAttributeName );

	if( wszValue == L"true" )
	{
		bRet = true;
	}

	return bRet;
}

//new method
short 
CEMSDOMNode::GetAttributeValueShort( const wchar_t* cwszAttributeName )
{
	short siRet = 0;

	std::wstring wszValue = GetAttributeText( cwszAttributeName );

	if( !wszValue.empty() )
	{
		siRet = CEMSConversionUtil::ConvertToShort( wszValue.c_str() );
	}

	return siRet;
}

//new method
int 
CEMSDOMNode::GetAttributeValueInt( const wchar_t* cwszAttributeName )
{
	int iRet = 0;

	std::wstring wszValue = GetAttributeText( cwszAttributeName );

	if( !wszValue.empty() )
	{
		iRet = CEMSConversionUtil::ConvertToLong( wszValue.c_str() );
	}

	return iRet;
}

//new method
__int64 
CEMSDOMNode::GetAttributeValueInt64( const wchar_t* cwszAttributeName )
{
	__int64 i64Ret = 0;

	if( cwszAttributeName )
	{
#if _MSC_VER < 1300
		swscanf( cwszAttributeName, L"%I64d", &i64Ret );
#else
		i64Ret = _wcstoi64( cwszAttributeName, 0, 10 );
#endif
	}

	return i64Ret;
}

void 
CEMSDOMNode::SetAttributeText( const wchar_t* cwszValue )
{
	if( !cwszValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == m_spNode )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		MSXML2::IXMLDOMAttributePtr spAttribute = m_spNode;

		if( 0 != spAttribute )
		{
			spAttribute->Putvalue( cwszValue );
			//spAttribute->Puttext( cwszValue );
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
}

wchar_t*
CEMSDOMNode::GetXML()
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	wchar_t* wszXML = 0;

	try
	{
		_bstr_t bszXML = m_spNode->Getxml();

		if( bszXML.length() )
		{
			wszXML = new wchar_t[ bszXML.length() + 1 ];
			if( !wszXML )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszXML, 0, (bszXML.length() + 1)*sizeof(wchar_t) );

			wcsncpy( wszXML, bszXML, bszXML.length() );

		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return wszXML;
}

CEMSDOMDocument*
CEMSDOMNode::GetOwnerDocument()
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMDocument* pRet = 0;

	try
	{
		MSXML2::IXMLDOMDocument2Ptr spDoc = m_spNode->GetownerDocument();

		if( 0 != spDoc )
		{
			pRet = new CEMSDOMDocument( spDoc );
		}
		else
		{
			THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pRet;
}


CEMSDOMNode*
CEMSDOMNode::AddChildNode( const wchar_t* cwszElementName, 
                           const wchar_t* cwszValue,
                           bool  bForceAdd)
{
	CEMSDOMNode* pNewNode = NULL;


	
	CEMSDOMNode* pNameNode = NULL;
   // if ForcedAdd is false, then no duplicate are allowed, the existing node will be updated
   if(!bForceAdd)
      pNameNode =  SelectSingleNode( cwszElementName );
   
   CEMSDOMDocument* pDoc = GetOwnerDocument();

   // bForcedAdd was set to true, or the node did not exist, we will try to add it
	if( 0 == pNameNode )
	{
		// Create it.
		if( pDoc )
		{
			pNameNode = pDoc->CreateNode( cwszElementName );
		}
	}

	if( 0 != pNameNode )
	{
		if( cwszValue )
		{
			if( wcslen( cwszValue ) > 0 )
				pNameNode->SetElementText( cwszValue );
		}
         
       
 	   // Append it.
		CEMSDOMNode* pAppendedNode = AppendChild( pNameNode );
     
		if( 0 != pAppendedNode )
		{
			pNewNode = pAppendedNode;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	if( pDoc )
	{
		pDoc->Release();
		pDoc = 0;
	}

	return pNewNode;
}

CEMSDOMNode*
CEMSDOMNode::AddChildNode( const wchar_t* cwszElementName, 
                           const wchar_t* cwszValue,
						   const wchar_t* cwszNS,
                           bool  bForceAdd )
{
	CEMSDOMNode* pNewNode = NULL;


	
	CEMSDOMNode* pNameNode = NULL;
   // if ForcedAdd is false, then no duplicate are allowed, the existing node will be updated
   if(!bForceAdd)
      pNameNode =  SelectSingleNode( cwszElementName );
   
   CEMSDOMDocument* pDoc = GetOwnerDocument();

   // bForcedAdd was set to true, or the node did not exist, we will try to add it
	if( 0 == pNameNode )
	{
		// Create it.
		if( pDoc )
		{
			pNameNode = pDoc->CreateNode( cwszElementName, cwszNS );
		}
	}

	if( 0 != pNameNode )
	{
		if( cwszValue )
		{
			if( wcslen( cwszValue ) > 0 )
				pNameNode->SetElementText( cwszValue );
		}
         
       
 	   // Append it.
		CEMSDOMNode* pAppendedNode = AppendChild( pNameNode );
     
		if( 0 != pAppendedNode )
		{
			pNewNode = pAppendedNode;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	if( pDoc )
	{
		pDoc->Release();
		pDoc = 0;
	}

	return pNewNode;
}

CEMSDOMNode*
CEMSDOMNode::AddChildCDATA( const wchar_t* cwszElementName, 
                           const wchar_t* cwszValue,
                           bool  bForceAdd)
{
	CEMSDOMNode* pNewNode = NULL;


	
	CEMSDOMNode* pNameNode = NULL;
   // if ForcedAdd is false, then no duplicate are allowed, the existing node will be updated
   if(!bForceAdd)
      pNameNode =  SelectSingleNode( cwszElementName );
   
   CEMSDOMDocument* pDoc = GetOwnerDocument();

   // bForcedAdd was set to true, or the node did not exist, we will try to add it
	if( 0 == pNameNode )
	{
		// Create it.
		if( pDoc )
		{
			pNameNode = pDoc->CreateCDATA( cwszElementName );
		}
	}

	if( 0 != pNameNode )
	{
		if( cwszValue )
		{
			if( wcslen( cwszValue ) > 0 )
				pNameNode->SetElementText( cwszValue );
		}
         
       
 	   // Append it.
		CEMSDOMNode* pAppendedNode = AppendChild( pNameNode );
     
		if( 0 != pAppendedNode )
		{
			pNewNode = pAppendedNode;
		}

		pNameNode->Release();
		pNameNode = 0;

	}

	if( pDoc )
	{
		pDoc->Release();
		pDoc = 0;
	}

	return pNewNode;
}

CEMSDOMNode::operator MSXML2::IXMLDOMNodePtr()
{
	return m_spNode;
}

CEMSDOMNode::operator MSXML2::IXMLDOMNode*()
{
	MSXML2::IXMLDOMNode* pRet = 0;

	if( 0 != m_spNode )
	{
		pRet = m_spNode;
	}

	return pRet;
}



int 
CEMSDOMNode::ChildCount( const wchar_t* pwcsNodeName )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

   CEMSDOMNodeList* pNodeList = SelectNodes( pwcsNodeName );       

   if(0 == pNodeList)
      THROW_DOM_NODE_EXCEPTION(EMS_UNKNOWN_ERROR);
   return pNodeList->GetLength();

}



wchar_t*
CEMSDOMNode::GetNodeName() const 
{ 
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   return m_spNode->nodeName; 
}

std::wstring
CEMSDOMNode::GetNodeNameEx() const 
{ 
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
	
	return std::wstring( m_spNode->nodeName ); 
}



CEMSDOMNode*
CEMSDOMNode::GetChildAt(   const wchar_t*    pwcsName,
                                 int         iIndex )
{
   if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	int iCount = 0;
	for (MSXML2::IXMLDOMNodePtr spChild = m_spNode->firstChild; spChild; spChild = spChild->nextSibling)
   {
		if ( CompareChildName( spChild, pwcsName ) )
      {
			if (iCount++ == iIndex)
         {
            CEMSDOMNode* pNode = NULL;
            pNode = new CEMSDOMNode( spChild );
				return pNode;
         }
      }
   }
   return 0;
}



CEMSDOMNode*
CEMSDOMNode::RemoveChildAt( const wchar_t* pwcsName, int iIndex)
{
   CEMSDOMNode* pNodeOut = NULL;
   if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   int iCount = 0;
   for (MSXML2::IXMLDOMNodePtr spChild = m_spNode->firstChild; spChild; spChild = spChild->nextSibling)
   {
	   if ( CompareChildName( spChild, pwcsName ) )
      {
		   if (iCount++ == iIndex)
         {
            try
            {
               
               MSXML2::IXMLDOMNodePtr spNodeOut = m_spNode->removeChild(spChild);
               if(0 != spNodeOut)
                  pNodeOut = new CEMSDOMNode(spChild);
            }
            catch( _com_error& e )
	         {
		         throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	         }
         }
      }
   }
  
   return pNodeOut;
}



bool 
CEMSDOMNode::CompareChildName( MSXML2::IXMLDOMNodePtr spChild, const wchar_t* pwcsName )
{
   if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
	return( spChild->baseName == _bstr_t(pwcsName) );
}

wchar_t*
CEMSDOMNode::GetChildText( const wchar_t* pwcsName )
{
   if( 0 == m_spNode )
   {
      THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
   }
                                                            // this will be used to form the XPath
   CEMSDOMNode* pNode = SelectSingleNode( pwcsName );       // Build the XPath buffer

   if( 0 != pNode)
   {
      return pNode->GetElementText();
   }
   return 0;
}

CEMSDOMNode*
CEMSDOMNode::RemoveChildNode( const wchar_t* pwcsName )
{

   CEMSDOMNode* pNodeOut = NULL;

	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

   CEMSDOMNode* pChild = SelectSingleNode( pwcsName ); 

   if( 0 == pChild)
      return pChild;

   try
   {
      MSXML2::IXMLDOMNodePtr spNodeOut = m_spNode->removeChild(*pChild);
      if( 0 != spNodeOut)
         pNodeOut = new CEMSDOMNode(spNodeOut);
      
   }
   catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
      
   return pNodeOut;
}

CEMSDOMNode*
CEMSDOMNode::InsertChildNode( const wchar_t* pwcsName, 
                              const wchar_t* pwcsValue )
{
   if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}
   try
   {
      bool bExists = false;
      for (MSXML2::IXMLDOMNodePtr spChild = m_spNode->firstChild; spChild; spChild = spChild->nextSibling)
      {  
	      if ( CompareChildName( spChild, pwcsName ) )
         {
            bExists = true;

            _variant_t refChild; //=((IDispatch*)spChild->nextSibling);
            
            if(0 != spChild->nextSibling)
            {
               refChild = (IDispatch*)spChild->nextSibling;
            }
            
		      CEMSDOMDocument* pDoc = GetOwnerDocument();
            CEMSDOMNode* pNameNode = NULL;
            if( 0 != pDoc )   
            {
               pNameNode = pDoc->CreateNode( pwcsName );
               if(0 == pNameNode)
                  THROW_DOM_NODE_EXCEPTION(EMS_UNKNOWN_ERROR);
               pNameNode->SetElementText( pwcsValue );
            }
            else
               THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
            spChild->text = bstr_t(pwcsValue);
            
		      // insert it at the right spot
		      if( 0 != m_spNode->insertBefore(spChild, refChild))
            {
               return new CEMSDOMNode(spChild);
            }
            else
            {
               THROW_DOM_NODE_EXCEPTION( EMS_UNKNOWN_ERROR );
            }
         }
      }
      // no child nodes, so just append it.
      if(!bExists)
      {
         return AddChildNode(pwcsName, pwcsValue);
      }
   }
   catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
   return 0;
}


CEMSDOMNode* 
CEMSDOMNode::GetParentNode()
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pRet = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spParent = m_spNode->GetparentNode();

		if( 0 != spParent )
		{
			pRet = new CEMSDOMNode( spParent );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch( _com_error& e )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}
	
void 
CEMSDOMNode::RemoveChild( CEMSDOMNode* pNode )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		m_spNode->removeChild( *pNode );
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSDOMNode::SetValue( const double cdValue )
{
	_variant_t vValue( cdValue );
	_SetValue( vValue );
}

void 
CEMSDOMNode::SetValue( const ULONG culValue )
{
	_variant_t vValue;
	vValue.vt = VT_UI4;
	vValue.ulVal = culValue;
	_SetValue( vValue );
}

void 
CEMSDOMNode::SetValue( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		_variant_t vValue( cwszValue );
		_SetValue( vValue );
	}
}
	
void 
CEMSDOMNode::SetValueCDATA( const wchar_t* cwszValue )
{
/*	if( cwszValue )
	{
		_variant_t vValue( cwszValue );
		_SetValueCDATA( vValue );
	}
*/
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		MSXML2::IXMLDOMTextPtr spText;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			spText = spNode;

		}
		else
		{
			MSXML2::IXMLDOMDocument2Ptr spDoc = m_spNode->GetownerDocument();

			if( spDoc )
			{
				spNode = spDoc->createCDATASection( _bstr_t(cwszValue) );
			}

			if( spNode )
			{
				MSXML2::IXMLDOMNodePtr spAppended = m_spNode->appendChild( spNode  );

				spText = spNode;
			}

		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
	catch( ... )
	{
		throw;
	}
}
	
void 
CEMSDOMNode::SetValue( const INT64 ci64Value )
{
	// Looks like MSXML4 can't handle 64 bit integers.  Callers should convert to a string and 
	// call SetValue( const wchar_t* cwszValue ) instead.  MSXML simply coerces VARIANTs to
	// schema defined types anyway.
	throw CEMSException( EMS_UNSUPPORTED );
}

void 
CEMSDOMNode::SetValue( const short csValue )
{
	_variant_t vValue( csValue );
	_SetValue( vValue );
}

void 
CEMSDOMNode::SetValue( const BYTE cbyValue )
{
	_variant_t vValue( cbyValue );
	_SetValue( vValue );
}

void 
CEMSDOMNode::SetValue( const char ccValue )
{
	_variant_t vValue;
	vValue.vt = VT_I1;
	vValue.cVal = ccValue;
	_SetValue( vValue );
}

void 
CEMSDOMNode::_SetValue( const _variant_t& vValue )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		MSXML2::IXMLDOMTextPtr spText;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			spText = spNode;

		}
		else
		{
			MSXML2::IXMLDOMDocument2Ptr spDoc = m_spNode->GetownerDocument();

			if( spDoc )
			{
				_variant_t vType;
				vType.vt = VT_I4;
#ifdef _64BITS
				vType.lVal =  MSXML2::NODE_TEXT;
#else
				vType.lVal =  NODE_TEXT;
#endif
				spNode = spDoc->createNode( vType, _bstr_t(L""), _bstr_t(L"")  );
			}

			if( spNode )
			{
				MSXML2::IXMLDOMNodePtr spAppended = m_spNode->appendChild( spNode  );

				spText = spNode;
			}

		}

		if( 0 != spText )
		{
			spText->PutnodeTypedValue( vValue );
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSDOMNode::_SetValueCDATA( const _variant_t& vValue )
{
	if( 0 == m_spNode )
	{
		THROW_DOM_NODE_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNode->firstChild;

		MSXML2::IXMLDOMTextPtr spText;

		if( 0 != spNode )
		{
			// See if the child is a text node.
			spText = spNode;

		}
		else
		{
			MSXML2::IXMLDOMDocument2Ptr spDoc = m_spNode->GetownerDocument();

			if( spDoc )
			{
				_variant_t vType;
				vType.vt = VT_I4;
#ifdef _64BITS
				vType.lVal =  MSXML2::NODE_TEXT;
#else
				vType.lVal =  NODE_TEXT;
#endif
				spNode = spDoc->createCDATASection( _bstr_t(L"") );
			}

			if( spNode )
			{
				MSXML2::IXMLDOMNodePtr spAppended = m_spNode->appendChild( spNode  );

				spText = spNode;
			}

		}

		if( 0 != spText )
		{
			spText->PutnodeTypedValue( vValue );
		}

	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}
	catch( ... )
	{
		throw;
	}
}

#endif