#ifndef __EMSVARITYPE_H__
#define __EMSVARITYPE_H__

#include <iconfigmanager.h>

class _com_error;

class _emsvaritype_t : public _tagEMSVARITYPE
{
public:

#pragma message("!!!!!!!!!!!!!!!!!!!!!!!find a way to block the automatic memberwise struct copy!!!!!!!!!!!!!!")

   // Constructors
   //
   _emsvaritype_t();

   _emsvaritype_t(const EMSVARITYPE&      varSrc);
   _emsvaritype_t(const EMSVARITYPE*      pSrc);
   _emsvaritype_t(const _emsvaritype_t&   varSrc);

   _emsvaritype_t(EMSVARITYPE& varSrc, bool fCopy);   // Attach EMSVARITYPE if !fCopy

   _emsvaritype_t( bool bSrc );              // Creates an EMSVARITYPE_DATATYPE_BOOL
   _emsvaritype_t( const wchar_t *pSrc );    // Creates an EMSVARITYPE_DATATYPE_STRING
   _emsvaritype_t( const char* pSrc );       // Creates an EMSVARITYPE_DATATYPE_STRING
   _emsvaritype_t( const EMSTIME &tmSrc );   // Creates an EMSVARITYPE_DATATYPE_TIME
   _emsvaritype_t( const INT64 &i64Src );    // Creates an EMSVARITYPE_DATATYPE_BIGINT
   _emsvaritype_t( int iSrc,              EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_INT );    // Creates an EMSVARITYPE_DATATYPE_INT or others*
   _emsvaritype_t( unsigned int uiSrc,    EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_UINT );   // Creates an EMSVARITYPE_DATATYPE_UINT or others*
   _emsvaritype_t( double dblSrc );	         // Creates an EMSVARITYPE_DATATYPE_DOUBLE
   _emsvaritype_t( float fltSrc );           // Creates an EMSVARITYPE_DATATYPE_FLOAT
	_emsvaritype_t( short sSrc,            EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_INT );    // Creates an EMSVARITYPE_DATATYPE_INT or others*
	_emsvaritype_t( unsigned short sSrc,   EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_UINT );   // Creates an EMSVARITYPE_DATATYPE_INT or others*
	_emsvaritype_t( long lSrc,             EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_INT );    // Creates an EMSVARITYPE_DATATYPE_INT or others*
	_emsvaritype_t( unsigned long lSrc,    EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_UINT );   // Creates an EMSVARITYPE_DATATYPE_UINT or others*
	_emsvaritype_t( BYTE bSrc,             EMSVARITYPE_DATATYPE vtSrc = EMSVARITYPE_DATATYPE_BOOL );   // Creates an EMSVARITYPE_DATATYPE_INT or others*
   // others*: generally speaking, only EMSVARITYPE_DATATYPE_BOOL is acceptable

   // Destructor
   //
   ~_emsvaritype_t();

   // Extractors
   //
   operator EMSTIME()         const;
   operator INT64()           const;
   operator int()             const;
   operator unsigned int()    const;
   operator float()           const;
   operator double()          const;
   operator const char*()     const;
   operator const wchar_t*()  const;
   operator wchar_t*()        const;
   operator bool()            const;
	operator short()           const;
	operator unsigned short()  const;
	operator long()            const;
	operator unsigned long()   const;
	operator BYTE()            const;

	// Assignment operations
	//
	_emsvaritype_t& operator=(const EMSVARITYPE& varSrc);
	_emsvaritype_t& operator=(const EMSVARITYPE* pSrc);
	_emsvaritype_t& operator=(const _emsvaritype_t& varSrc);

	_emsvaritype_t& operator=(EMSTIME tmSrc);
	_emsvaritype_t& operator=(INT64 i64Src);
	_emsvaritype_t& operator=(int iSrc);
	_emsvaritype_t& operator=(unsigned int uiSrc);
	_emsvaritype_t& operator=(short sSrc);
	_emsvaritype_t& operator=(unsigned short sSrc);
	_emsvaritype_t& operator=(long lSrc);
	_emsvaritype_t& operator=(unsigned long lSrc);
	_emsvaritype_t& operator=(float fltSrc);
	_emsvaritype_t& operator=(double dblSrc);
	_emsvaritype_t& operator=(const wchar_t* pSrc);
	_emsvaritype_t& operator=(const char* pSrc);
 	_emsvaritype_t& operator=(bool bSrc);
	_emsvaritype_t& operator=(BYTE bSrc);

	// Comparison operations
	//
	bool operator==(const EMSVARITYPE& varSrc)   const;
	bool operator==(const EMSVARITYPE* pSrc)     const;

	bool operator!=(const EMSVARITYPE& varSrc)   const;
	bool operator!=(const EMSVARITYPE* pSrc)     const;

	// Low-level operations
	//
	void Clear();

	void Attach(EMSVARITYPE& varSrc);
	EMSVARITYPE Detach();

	void ChangeType(EMSVARITYPE_DATATYPE vartype, const _emsvaritype_t* pSrc = NULL);

	void SetString(const char* pSrc);
	void SetString(const wchar_t* pSrc);
};

#endif // __EMSVARITYPE_H__

