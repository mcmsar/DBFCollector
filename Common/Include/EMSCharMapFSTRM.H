/********************************************************************
*	Module:			EMSCharMapFStrm.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*			File stream that supports the remapping of characters
*			based on a specified character map (ie lookup table)
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2004/02/06		CH		written

********************************************************************/
#ifndef INC_CHARMAPEMSFSTRM
#define INC_CHARMAPEMSFSTRM

#include "EMSFSTRM.h"
#include "CharMap.h"

class CEMSCharMapFileStream : public CEMSFileStream
{
public:
	CEMSCharMapFileStream():m_bHasMap(false) {}

	EMS_RESULT	Init( LPCTSTR szCharMapFilename );

	// The implementation assumes that the supplied BYTE buffer contains
	// an array of TCHAR
	virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);

private: // methods
	~CEMSCharMapFileStream() {}

private: // data
	CEMSCharMap m_CharMap;
	bool		m_bHasMap;
};

#endif // INC_CHARMAPEMSFSTRM
