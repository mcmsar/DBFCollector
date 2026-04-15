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

#ifndef __CONFIGURATION_ACCESSOR_H__
#define __CONFIGURATION_ACCESSOR_H__

#include "aobjbase.h"
#include <string>
#include "objectlist.h"

#ifdef USE_APACHE_XERCES
#include <xercesc/util/XercesDefs.hpp>
namespace XERCES_CPP_NAMESPACE 
{
	class DOMElement;
	class DOMNode;
	class DOMAttr;
};
#include <xalanc/xalandom/xalandomdefinitions.hpp>
namespace XALAN_CPP_NAMESPACE
{
	class XalanNode;
	class XercesDocumentWrapper;
	class NodeRefList;
};
#else
class CEMSDOMNode;
class CEMSDOMNodeList;
#endif

//! @class CEMSConfigurationAccessor
//! Manages access to an underlying XML DOM Node.
class CEMSConfigurationAccessor : public CApiObjBase
{
	public:
		CEMSConfigurationAccessor();
		CEMSConfigurationAccessor( const CEMSConfigurationAccessor& x );
		virtual ~CEMSConfigurationAccessor();

		//! @fn virtual std::wstring Serialize();
		//! Return the contents of the configuration node in string format.
		virtual std::wstring Serialize();

#ifdef USE_APACHE_XERCES
		//! Assign the source configuration node.
		void SetSource( XERCES_CPP_NAMESPACE::DOMNode* pNode );
#else
		//! @fn void SetSource( CEMSDOMNode* pNode )
		//! Assign the source configuration node.
		void SetSource( CEMSDOMNode* pNode );

		void SetSource( const wchar_t* cwszXMLString, const wchar_t* cwszNSString );
#endif

		//! @fn void SetSource( const wchar_t* cwszXMLString )
		//! Loads the given XML string into a DOM and sets the root
		//! node to the member pointer m_pNode.
		void SetSource( const wchar_t* cwszXMLString );

		
		//! Loads XML form the given file into a DOM and sets the root
		//! node to the member pointer m_pNode.
		void SetSourceFile( const wchar_t* cwszXMLFile );

		//! Save the document to file.  If a NULL file name parameter is specified, it will
		//! use the name of the file previously loaded (if loaded from file).
		void Save( const wchar_t* cwszXMLFile = 0 );

#ifndef USE_APACHE_XERCES
		//! @fn CEMSDOMNode* GetNode()
		//! Retrieve the source configuration node.
		CEMSDOMNode* GetNode();

		CEMSDOMNode* GetElement( const wchar_t* cwszPath );
#endif

		//! @fn void SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
		//! Set the text of the given element node.
		void SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue );
		void SetElementValue( const wchar_t* cwszPath, const wchar_t* cwszValue, const wchar_t* cwszNS );
		void SetElementValueCDATA( const wchar_t* cwszPath, const wchar_t* cwszValue );

		//! @fn std::wstring GetElementValue( const wchar_t* cwszPath )
		//! Get the text of the given element node.
		std::wstring GetElementValue( const wchar_t* cwszPath );
		

		//! @fn void SetAttributeValue( const wchar_t* cwszPath, const wchar_t* cwszValue )
		//! Set the text of the given attribute node with a string value.
		void SetAttributeValue( const wchar_t* cwszPath, const wchar_t* cwszValue );
		
		//! @fn std::wstring GetAttributeValue( const wchar_t* cwszPath )
		//! Get the text of the given attribute.
		std::wstring GetAttributeValue( const wchar_t* cwszPath );

		//! @fn void SetElementValue( const wchar_t* cwszPath, const double cdValue )
		//! Set the text of the given element node with a double value.
		void SetElementValue( const wchar_t* cwszPath, const double cdValue );
		
		//! @fn double GetElementValueDouble( const wchar_t* cwszPath )
		//! Retrieve an element value as a double.
		double GetElementValueDouble( const wchar_t* cwszPath );

		//! @fn void SetElementValue( const wchar_t* cwszPath, const bool cbValue )
		//! Set the text of the given element node with a bool value.
		void SetElementValue( const wchar_t* cwszPath, const bool cbValue );
		
		//! @fn bool GetElementValueBoolean( const wchar_t* cwszPath )
		//! Retrieve an element value as a bool.
		bool GetElementValueBoolean( const wchar_t* cwszPath );

		//! @fn void SetElementValue( const wchar_t* cwszPath, const ULONG culValue )
		//! Set the text of the given element node with a ULONG value.
		void SetElementValue( const wchar_t* cwszPath, const ULONG culValue );
		void SetElementValue( const wchar_t* cwszPath, const ULONG culValue, const wchar_t* cwszNS );

		//! @fn ULONG GetElementValueULong( const wchar_t* cwszPath )
		//! Get an element value as a ULONG.
		ULONG GetElementValueULong( const wchar_t* cwszPath );

		//! @fn void SetElementValue( const wchar_t* cwszPath, const EMSTIME ctimeValue )
		//! Set the text of the given element node with an EMSTIME value.
		void SetElementValue( const wchar_t* cwszPath, const EMSTIME ctimeValue );

		//! @fn EMSTIME GetElementValueTime( const wchar_t* cwszPath )
		//! Get an element value as an EMSTIME.
		EMSTIME GetElementValueTime( const wchar_t* cwszPath );

		//! Set the text of a given element node with an unsigned short value.
		void SetElementValue( const wchar_t* cwszPath, const unsigned short cusValue );

		//! Get an element value as an unsigned short.
		unsigned short GetElementValueUShort( const wchar_t* cwszPath );
		
		//! @fn short GetElementValueShort( const wchar_t* cwszPath )
		//! Get an element value as a short.
		short GetElementValueShort( const wchar_t* cwszPath );

		//! Get an element value as an UINT64.  The value is assumed to be stored in Hex format.
		unsigned __int64 GetElementValueUI64( const wchar_t* cwszPath );

		//! Set an element value as an UINT64.
		void SetElementValue( const wchar_t* cwszPath, const unsigned __int64 cui64Value );

		//! Set the text of the given element node with a float value.
		void SetElementValue( const wchar_t* cwszPath, const float cfValue );
		
		//! Retrieve an element value as a float.
		float GetElementValueFloat( const wchar_t* cwszPath );

		//! Retrieve an element value as an int.
		int GetElementValueInt( const wchar_t* cwszPath );

		void SetElementValue( const wchar_t* cwszPath, const BYTE cbyValue );

		void SetElementValue( const wchar_t* cwszPath, const short csValue );

		void SetElementValue( const wchar_t* cwszPath, const char ccValue );

		//! @fn void SetAttributeValue( const wchar_t* cwszPath, const ULONG culValue )
		//! Set the text of the given attribute node with a ULONG value.
		void SetAttributeValue( const wchar_t* cwszPath, const ULONG culValue );

		//! @fn ULONG GetAttributeValueULong( const wchar_t* cwszPath )
		//! Get an attribute value as a ULONG.
		ULONG GetAttributeValueULong( const wchar_t* cwszPath );

		//! @fn bool GetAttributeValueBoolean( const wchar_t* cwszPath )
		//! Get an attribute value as a bool.
		bool GetAttributeValueBoolean( const wchar_t* cwszPath );

		//! @fn void SetAttributeValue( const wchar_t* cwszPath, const bool cbValue )
		//! Set the text of the given attribute node with a bool value.
		void SetAttributeValue( const wchar_t* cwszPath, const bool cbValue );

		//! @fn void AttachChild( CEMSConfigurationAccessor* pChild )
		//! Attach the given object as a child node.  This method
		//! creates an XML child node in the structure and attaches that node
		//! to the input child object.
		void AttachChild( CEMSConfigurationAccessor* pChild );

		//! @fn void Attach( CEMSConfigurationAccessor* pChild )
		//! Attach the given object as a child node.  This method
		//! assumes that the input child is already connected to an XML node.
		//! It attaches the XML node as a child to the existing structure.
		void Attach( CEMSConfigurationAccessor* pChild );

		//! @fn virtual std::wstring GetElementName()
		//! Retrieve the name of the top-level element node.
		//! This must be overriden in derived classes.
		virtual std::wstring GetElementName() { return std::wstring(); }

		//! @fn void DetachChild()
		//! Detach this child from its parent.
		void DetachChild();

#ifdef USE_APACHE_XERCES
		//! Get a list of nodes matching the given query.
		XALAN_CPP_NAMESPACE::NodeRefList GetNodes( const wchar_t* cwszPath );

		//! Get the node matching the query.
		XALAN_CPP_NAMESPACE::XalanNode*  GetNode( const wchar_t* cwszPath );

#else
		//! @fn CEMSDOMNodeList* GetNodes( const wchar_t* cwszPath )
		//! Get a list of nodes matching the given query.
		CEMSDOMNodeList* GetNodes( const wchar_t* cwszPath );

		//! @fn CEMSDOMNode* GetNode( const wchar_t* cwszPath )
		//! Get the node matching the query.
		CEMSDOMNode* GetNode( const wchar_t* cwszPath );
#endif

		//! @fn void DeleteElement( const wchar_t* cwszPath )
		//! Remove the element from the document.
		void DeleteElement( const wchar_t* cwszPath );

		//! Creates the specified element(s).
		void SetElement( const wchar_t* cwszPath );

		//! Appends the data as a child of the node at the given path.  If a NULL path is
		//! specified, it is inserted as a child of the top-level node.
		void Insert( const wchar_t* cwszPath, const wchar_t* cwszSerialData );

		//! Get an accessor to the portion of the configuration found at the given path.
		CEMSConfigurationAccessor GetAccessor( const wchar_t* cwszPath );

		//! Get an accessor to the portion of the configuration found at the given path.  Caller must release the returned pointer.
		CEMSConfigurationAccessor* GetAccessorEx( const wchar_t* cwszPath );

		//! Get a list of accessors to the portions of the configuration found at the given path.
		CEMSObjectList<CEMSConfigurationAccessor> GetAccessorList( const wchar_t* cwszPath );

		//! Overloaded assignment operator.
		CEMSConfigurationAccessor& operator= ( const CEMSConfigurationAccessor& coRHS );

		//! Append a configuration element to the element indicated by path.
		void Append( const wchar_t* cwszPath, const wchar_t* cwszNewElement, const wchar_t* cwszValue );

		//! Append a configuration element to the element indicated by the path.
		CEMSConfigurationAccessor* AppendEx( const wchar_t* cwszPath, const wchar_t* cwszNewElement, const wchar_t* cwszValue );

		//! Determine whether the node specified by the given path is in the document.
		bool DoesNodeExist( const wchar_t* cwszPath );

		//! Checks for a root node.
		bool IsInitialized();

		//! Retrieve the given attribute as an INT64.  The attribute is expected to be in Hex format.
		INT64 GetAttributeValueHexI64( const wchar_t* cwszPath );

		//! Add an element of the given name at the path indicated (NULL path is root).
		CEMSConfigurationAccessor* AddChildElement( const wchar_t* cwszPath, const wchar_t* cwszElement );

		CEMSConfigurationAccessor* AddChildElement( const wchar_t* cwszPath, const wchar_t* cwszElement, const wchar_t* cwszNS );

	protected:
		void _ReleaseData();

#ifdef USE_APACHE_XERCES
		void _Init();
#endif

	private:

		CEMSObjectList<std::wstring> _ParseElementPath( const wchar_t* cwszPath );
		CEMSObjectList<std::wstring> _ParseAttributePath( const wchar_t* cwszPath );

#ifdef USE_APACHE_XERCES
		XERCES_CPP_NAMESPACE::DOMElement* _GetTextElement( const wchar_t* cwszPath );
		XERCES_CPP_NAMESPACE::DOMAttr* _GetAttribute( const wchar_t* cwszPath );
#else
		CEMSDOMNode* _GetTextElement( const wchar_t* cwszPath, const wchar_t* cwszNS = NULL );
		CEMSDOMNode* _GetTextElementCDATA( const wchar_t* cwszPath );
#endif

		void _CreateRoot( const wchar_t* cwszRoot );

#ifdef USE_APACHE_XERCES
		//! Load the XML string into a DOM and return the top level node.
		XERCES_CPP_NAMESPACE::DOMNode* _Load( const wchar_t* cwszXML );
#else
		//! Load the XML string into a DOM and return the top level node.
		CEMSDOMNode* _Load( const wchar_t* cwszXML );
#endif

#ifdef USE_APACHE_XERCES
		XALAN_CPP_NAMESPACE::XalanNode* _GetXalanNode();
		XERCES_CPP_NAMESPACE::DOMNode* _GetXercesNode( XALAN_CPP_NAMESPACE::XalanNode* pXalanNode );
		void _InitXalanDoc();
#endif

	protected:
#ifdef USE_APACHE_XERCES
		XERCES_CPP_NAMESPACE::DOMNode* m_pNode;
		XALAN_CPP_NAMESPACE::XercesDocumentWrapper* m_pXalanDoc;
#else
		CEMSDOMNode*	m_pNode;
#endif

		static const ULONG ms_culMaxXPathQuerySize;

		std::wstring	m_owszFile;

	private:
		static const wchar_t* ms_cwszFlagValueTrue;
		static const wchar_t* ms_cwszFlagValueFalse;

		static const wchar_t* ms_cwszElementLevel;
		static const wchar_t* ms_cwszAttributeIndicator;
		
};

#endif