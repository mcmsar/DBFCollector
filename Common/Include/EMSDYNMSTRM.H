/********************************************************************
*	Module:			EMSDynMStrm.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSDynMemoryStream definition.  A verion of the
*					memory stream class, but with dynamic allocation
*					of buffer space while writing.
*
*					Use this class when the size of the buffer needed
*					is not known when writing begins.
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

	0.0	2003/02/10		JB		start

********************************************************************/
#ifndef INC_EMSMSDYNTRM
#define INC_EMSMSDYNTRM

#include "aobjbase.h"
#include "emspipe.h"
#include "emsmstrm.h"

class CEMSDynMemoryStream : public CEMSMemoryStream
{
public:
	CEMSDynMemoryStream( ULONG ulChunkSize );
	~CEMSDynMemoryStream();

/*********************************************************************
*	IEMSSeqStream Methods
*********************************************************************/
	virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);

private:	// methods
	EMS_RESULT	_ReAllocate( ULONG ulBytes );
	ULONG		_GetBytesAvailable();
	ULONG		_GetNumChunks( ULONG ulBytes );
	EMS_RESULT	_AllocateBuffer( ULONG ulChunks, LPBYTE& pBuffer, ULONG& ulBufSize );

private:	// data
	ULONG m_ulChunkSize;


};

#endif // INC_EMSMSTRM
