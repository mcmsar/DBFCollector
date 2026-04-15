
#ifndef __EMSDOMDOC_H__
#define __EMSDOMDOC_H__

#ifdef USE_APACHE_XERCES
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/domdocument.hpp>
#else
#ifdef _64BITS
#import <msxml6.dll>
using namespace MSXML2;
#else
#import <msxml4.dll> named_guids
#endif
#endif

// forward declaration classes
class CEMSDOMDocument;

// standard includes


// EMS includes
#include <emsbase.h>                // base class for some EMS objects
#include <emsdomnodelist.h>         // wrapper for MS DOM node list class
#include <emsdomnode.h>             // warapper for MS DOM node class
  

class CEMSDOMDocument : public CEMSBase
{
public:
	CEMSDOMDocument();
	CEMSDOMDocument( CEMSDOMDocument& oDoc );
#ifdef USE_APACHE_XERCES
	CEMSDOMDocument( XERCES_CPP_NAMESPACE::DOMDocument* pDoc );
#else
	CEMSDOMDocument( MSXML2::IXMLDOMDocumentPtr spDoc );
	CEMSDOMDocument( MSXML2::IXMLDOMDocument2Ptr spDoc );
#endif
	virtual ~CEMSDOMDocument();

	void Initialize( const wchar_t* cwszRootName );

	void Clear();
	
	bool Load( const wchar_t* cwszFileName, bool bAsync = false, bool bValidateOnParse = false );
	bool LoadXML( const wchar_t* cwszXML );
	bool Save( const wchar_t* cwszFileName );

	CEMSDOMNodeList* SelectNodes( const wchar_t* cwszXPATH );
	CEMSDOMNode* SelectSingleNode( const wchar_t* cwszXPATH );
	wchar_t* GetXML();
	CEMSDOMNode*   RemoveChild( CEMSDOMNode* pChild );
	CEMSDOMNode*   AppendChild( CEMSDOMNode* pNode );
	CEMSDOMNode*   CreateNode( const wchar_t* cwszNodeName );
	CEMSDOMNode*   CreateNode( const wchar_t* cwszNodeName, const wchar_t* cwszNS );
	CEMSDOMNode*   CreateCDATA( const wchar_t* cwszNodeName );
	CEMSDOMNode*   AddChildNode( const wchar_t* cwszElementName, const wchar_t* cwszValue );
   CEMSDOMNode*   CreateTextNode(const wchar_t* cwszValue);

   // gets the root element, NULL if none exists
   CEMSDOMNode*   GetRoot();
 
   bool	IsLoaded() { return m_bLoaded; }
   bool IsValid();

   void SetNamespace( const wchar_t* cwszNamespace );
   std::wstring GetNamespace();

   std::wstring GetNamespaceURI();

#ifdef USE_APACHE_XERCES
   //! Import a node into the document.
   CEMSDOMNode* ImportNode( CEMSDOMNode* pNode, bool bDeep );
#endif

protected:
	void _Init();

protected:
#ifdef USE_APACHE_XERCES
	XERCES_CPP_NAMESPACE::DOMDocument*	m_pDoc;
	XERCES_CPP_NAMESPACE::DOMNode*		m_pRootNode;
#else
	MSXML2::IXMLDOMDocument2Ptr m_spDoc;
	MSXML2::IXMLDOMNodePtr m_spRootNode;
#endif

	bool	m_bLoaded;
};



#endif // __EMSDOMDOC_H__