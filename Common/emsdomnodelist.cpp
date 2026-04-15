#include <string>
using std::string;
using std::wstring;

#include <criticalsection.h>
#include <emsbase.h>
#include <emsdomnodelist.h>

#include <emserror.h>
#include <emsexcpt.h>

#include <emsdomnode.h>

#ifdef USE_APACHE_XERCES
#include <xercesc/dom/domexception.hpp>
#include "xstr.h"

CEMSDOMNodeList::CEMSDOMNodeList( XERCES_CPP_NAMESPACE::DOMNodeList* pNodeList ) : CEMSBase("CEMSDOMNodeList"),
																			m_pNodeList( pNodeList ),
																			m_ulCurrentIdx(0)
{
}

CEMSDOMNodeList::~CEMSDOMNodeList()
{
}

long
CEMSDOMNodeList::GetLength()
{
	if( 0 == m_pNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	return m_pNodeList->getLength();
}

CEMSDOMNode*
CEMSDOMNodeList::GetNode( const long clIndex )
{
	if( 0 == m_pNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pTempNode = m_pNodeList->item( clIndex );

		if( 0 != pTempNode )
		{
			pNode = new CEMSDOMNode( pTempNode );

			if( !pNode )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeListException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeListException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pNode;
}

CEMSDOMNode*
CEMSDOMNodeList::NextNode()
{
	if( 0 == m_pNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		XERCES_CPP_NAMESPACE::DOMNode* pTempNode = m_pNodeList->item( m_ulCurrentIdx++ );

		if( 0 != pTempNode )
		{
			pNode = new CEMSDOMNode( pTempNode );
		}
	}
	catch (const XERCES_CPP_NAMESPACE::XMLException& toCatch) 
	{
		if( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.getMessage());
		CEMSDOMNodeListException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}
	catch (const XERCES_CPP_NAMESPACE::DOMException& toCatch)
	{
		if( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}

		char* szMessage = XERCES_CPP_NAMESPACE::XMLString::transcode(toCatch.msg);
		CEMSDOMNodeListException e( __LINE__, TEXT(__FILE__), 0, 0, szMessage );
		delete[] szMessage;
		throw e;
	}

	return pNode;
}

void
CEMSDOMNodeList::Reset()
{
	if( 0 == m_pNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	m_ulCurrentIdx = 0;
}

#else

CEMSDOMNodeList::CEMSDOMNodeList( MSXML2::IXMLDOMNodeListPtr spNodeList ) : CEMSBase("CEMSDOMNodeList"),
																			m_spNodeList( spNodeList )
{
}

CEMSDOMNodeList::~CEMSDOMNodeList()
{
}

long
CEMSDOMNodeList::GetLength()
{
	if( 0 == m_spNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	return m_spNodeList->length;
}

CEMSDOMNode*
CEMSDOMNodeList::GetNode( const long clIndex )
{
	if( 0 == m_spNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNodeList->item[ clIndex ];

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
		throw CEMSDOMNodeListException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNode;
}

CEMSDOMNode*
CEMSDOMNodeList::NextNode()
{
	if( 0 == m_spNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	CEMSDOMNode* pNode = 0;

	try
	{
		MSXML2::IXMLDOMNodePtr spNode = m_spNodeList->nextNode();

		if( 0 != spNode )
		{
			pNode = new CEMSDOMNode( spNode );
		}
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeListException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

	return pNode;
}

void
CEMSDOMNodeList::Reset()
{
	if( 0 == m_spNodeList )
	{
		THROW_DOM_NODE_LIST_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		m_spNodeList->reset();
	}
	catch( _com_error& e )
	{
		throw CEMSDOMNodeListException( __LINE__, TEXT(__FILE__), e.Error(), 0, e.Description() );
	}

}

#endif
