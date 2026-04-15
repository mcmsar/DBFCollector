/********************************************************************
*	Module:			EMSMStrm.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSMemoryStream definition
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

	0.0	2001/07/30		rvw	start

********************************************************************/
#ifndef INC_EMSMSTRM
#define INC_EMSMSTRM

#include "aobjbase.h"
#include "emspipe.h"

class CEMSMemoryStream : public IEMSSeqStream, public CApiObjBase
{
public:
	CEMSMemoryStream( );

/*********************************************************************
*	Public Methods
*********************************************************************/
	EMS_RESULT Allocate( ULONG ulBytes );
	EMS_RESULT Free( void );
	EMS_RESULT Reset( void );
	LPBYTE	GetPtr( void ) { return m_lpBuffer; }
	ULONG	GetLength( void ) { return m_ulBufferLength; }
	ULONG	GetAllocated( void ) { return m_ulBufferAllocated; }
	ULONG	GetPosition( void ) { return m_ulBufferPosition; }
	ULONG 	SetPosition( ULONG ulOffset );
	void		ResetPosition( void ) { SetPosition( 0 ); }

/*********************************************************************
*	IEMSSeqStream Methods
*********************************************************************/

	virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
	virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);

protected: // methods
	virtual ~CEMSMemoryStream();

protected: // data
	LPBYTE	m_lpBuffer;
	ULONG		m_ulBufferLength;
	ULONG		m_ulBufferAllocated;
	ULONG		m_ulBufferPosition;
};

#endif // INC_EMSMSTRM
