#ifndef __EMSDOMNODE_H__
#define __EMSDOMNODE_H__

#ifdef USE_APACHE_XERCES
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/domnode.hpp>
#else
#ifdef _64BITS
#import <msxml6.dll>  
using namespace MSXML2;
#else
#import <msxml4.dll> named_guids
#endif
#endif

// forward declaration classes
class CEMSDOMNode;


// standard includes
#include <string>

// EMS includes
#include <emsbase.h>                // base class for some EMS objects
#include <emsdomnodelist.h>         // wrapper for MS DOM node list class
#include <emsdomdocument.h>         // wrapper for MS DOM document class

class CEMSDOMNode : public CEMSBase
{
public:
#ifdef USE_APACHE_XERCES
	CEMSDOMNode( XERCES_CPP_NAMESPACE::DOMNode* pNode );
#else
	CEMSDOMNode( MSXML2::IXMLDOMNodePtr spNode );
#endif
	CEMSDOMNode( CEMSDOMNode& oNode );
	virtual ~CEMSDOMNode();

	CEMSDOMNode* AppendChild( CEMSDOMNode* pNode );
	CEMSDOMNode* CloneNode( bool bDeep = true );
	CEMSDOMNodeList* SelectNodes( const wchar_t* cwszXPATH );
	CEMSDOMNode* SelectSingleNode( const wchar_t* cwszXPATH );
	wchar_t* GetElementText();
	std::wstring GetElementTextEx();
	void SetElementText( const wchar_t* cwszText );
	void SetAttributeText( const wchar_t* cwszAttributeName, const wchar_t* cwszText );

	std::wstring GetAttributeText( const wchar_t* cwszAttributeName );
	double GetAttributeValueDouble( const wchar_t* cwszAttributeName );
	float GetAttributeValueFloat( const wchar_t* cwszAttributeName );
	bool GetAttributeValueBoolean( const wchar_t* cwszAttributeName );
	short GetAttributeValueShort( const wchar_t* cwszAttributeName );
	int GetAttributeValueInt( const wchar_t* cwszAttributeName );
	__int64 GetAttributeValueInt64( const wchar_t* cwszAttributeName );

	wchar_t* GetXML();
	CEMSDOMDocument* GetOwnerDocument();
	CEMSDOMNode* AddChildNode( const wchar_t* cwszElementName,     // element name
                              const wchar_t* cwszValue,           // value
                              bool  bForceAdd=false);             // true=will allow duplicates
	CEMSDOMNode* AddChildNode( const wchar_t* cwszElementName, 
                           const wchar_t* cwszValue,
						   const wchar_t* cwszNS,
                           bool  bForceAdd=false);
	CEMSDOMNode* AddChildCDATA( const wchar_t* cwszElementName,     // element name
                              const wchar_t* cwszValue,           // value
                              bool  bForceAdd=false);             // true=will allow duplicates

   // inserts an element at its prescribed address (if already in XML file)
   // otherwise it is appended to the end of the parent element
   CEMSDOMNode* InsertChildNode( const wchar_t* pwcsName, const wchar_t* pwcsValue );

   // gets the current node name
   wchar_t* GetNodeName() const;

   std::wstring GetNodeNameEx() const;
   void SetAttributeText( const wchar_t* cwszValue );

#ifdef USE_APACHE_XERCES
   XERCES_CPP_NAMESPACE::DOMNode* GetRaw();
#else
	operator MSXML2::IXMLDOMNodePtr();
	operator MSXML2::IXMLDOMNode*();  
#endif

	CEMSDOMNode* GetParentNode();
	void RemoveChild( CEMSDOMNode* pNode );

	// These methods will set the value of a TEXT type element.
	void SetValue( const double cdValue );
	void SetValue( const ULONG culValue );
	void SetValue( const wchar_t* cwszValue );
	void SetValueCDATA( const wchar_t* cwszValue );
	void SetValue( const INT64 ci64Value );
	void SetValue( const short csValue );
	void SetValue( const BYTE cbyValue );
	void SetValue( const char ccValue );


protected:
   // get the count of Child nodes
   int ChildCount( const wchar_t* pwcsNodeName );

   // gets a child element at a specific index
   CEMSDOMNode* GetChildAt( const wchar_t* pwcsName, int iIndex );

   // removes a child at a specific index
   CEMSDOMNode*  RemoveChildAt( const wchar_t* pwcsName, int iIndex);

   // removes a child node using child node name
   CEMSDOMNode*  RemoveChildNode( const wchar_t* pwcsName );

   // compares the elements name 
#ifdef USE_APACHE_XERCES
   bool CompareChildName( XERCES_CPP_NAMESPACE::DOMNode* pChild, const wchar_t* pwcsName );
#else
   bool CompareChildName( MSXML2::IXMLDOMNodePtr spChild, const wchar_t* pwcsName );
#endif

   // get a child element text, pointer must be freed by caller
   wchar_t* GetChildText( const wchar_t* pwcsName );

private:
#ifndef USE_APACHE_XERCES
	void _SetValue( const _variant_t& vValue );
	void _SetValueCDATA( const _variant_t& vValue );
#endif

#ifdef USE_APACHE_XERCES
	XERCES_CPP_NAMESPACE::DOMNode*	m_pNode;
#else
  	MSXML2::IXMLDOMNodePtr m_spNode;
#endif
   

};

#endif // __EMSDOMNODE_H__
