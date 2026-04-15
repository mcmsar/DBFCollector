
#ifndef __EMSDOMNODELIST_H__
#define __EMSDOMNODELIST_H__

#ifdef USE_APACHE_XERCES
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/dom/domnodelist.hpp>
#else
#ifdef _64BITS
#import <msxml6.dll>
using namespace MSXML2;
#else
#import <msxml4.dll> named_guids
#endif
#endif


// forward declaration classes
class CEMSDOMNodeList;


// standard includes


// EMS includes
#include <emsbase.h>             // base class for some EMS objects
#include <emsdomnode.h>           // wrapper for MS DOM node  class


class CEMSDOMNodeList : public CEMSBase
{
public:
#ifdef USE_APACHE_XERCES
	CEMSDOMNodeList( XERCES_CPP_NAMESPACE::DOMNodeList* pNodeList );
#else
	CEMSDOMNodeList( MSXML2::IXMLDOMNodeListPtr spNodeList );
#endif
	virtual ~CEMSDOMNodeList();

	long GetLength();
	CEMSDOMNode* GetNode( const long clIndex );
	CEMSDOMNode* NextNode();
	void Reset();

protected:

#ifdef USE_APACHE_XERCES
	XERCES_CPP_NAMESPACE::DOMNodeList*	m_pNodeList;
	ULONG	m_ulCurrentIdx;
#else
	MSXML2::IXMLDOMNodeListPtr m_spNodeList;
#endif

};

#endif // __EMSDOMNODELIST_H__