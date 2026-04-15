/********************************************************************
*	Module:			pkstream.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/03/22		rvw	start

********************************************************************/
#ifndef INC_PKSTREAM
#define INC_PKSTREAM

#include "emspipe.h"

class CEMSPacketStream : public IEMSPacketStream
{
public:
	CEMSPacketStream( BYTE cType=0, int nMaxLength=0, DWORD dwFlags = EMS_PIPE_FIXED_LENGTH | EMS_PIPE_WAIT_WRITE);

	EMS_RESULT Initialize( int nQueueSize = 32 );

	/*********************************************************************
	*	IUnknown Methods
	*********************************************************************/
	STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef(void); 
	STDMETHODIMP_(ULONG) Release(void); 

	/*********************************************************************
	*	IEMSSeqStream Methods
	*********************************************************************/
	STDMETHODIMP Read( BYTE __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbRead );
	STDMETHODIMP Write( const BYTE __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbWritten );

	/*********************************************************************
	*	IEMSPacketStream Methods
	*********************************************************************/
	STDMETHODIMP SetType( BYTE cDataType );
	STDMETHODIMP GetType( BYTE __RPC_FAR *lpcDataType );
	STDMETHODIMP SetMaxLength( INT nMaxLength );
	STDMETHODIMP GetMaxLength( INT __RPC_FAR *lpnMaxLength );
	STDMETHODIMP SetFlags( DWORD dwFlags );
	STDMETHODIMP GetFlags( DWORD __RPC_FAR *lpdwFlags );

/*********************************************************************
*	other public methods
*********************************************************************/
	int GetQueueCount( void );
	inline WORD GetQueueSize( void ) { return ( WORD )m_nQueueSize; };

/*********************************************************************
*	Private Methods
*********************************************************************/
private:
	virtual ~CEMSPacketStream();

	BOOL _Lock( BOOL bWait=TRUE, DWORD dwTimeout=0xFFFFFFFF );
	void _Unlock( void );
	LPBYTE _GetDataPointer( int nIndex );
	EMS_RESULT _InitDataQueue( void );
	EMS_RESULT _ResetDataQueue( void );
	EMS_RESULT _PushDataQueue( BYTE const *lpBuffer, ULONG ulLength, ULONG *lpulCount );
	EMS_RESULT _PopDataQueue( BYTE const *lpBuffer, ULONG ulLength, ULONG *lpulCount );
	void _SetDataLength( int nIndex, int nLength );
	int _GetDataLength( int nIndex );
	BOOL _IsOverflow( void );

	inline BOOL _VariableLength( void ) 
 		{ return ( m_dwFlags & EMS_PIPE_VARIABLE_LENGTH ) == EMS_PIPE_VARIABLE_LENGTH; }

	inline INT _MaxDataLength( void ) 
		{ return ( _VariableLength() ) ? m_nMaxRecLen - sizeof(INT) : m_nMaxRecLen; }

private: // data
	volatile LONG	m_lRefCount;
	int 		m_nMaxRecLen;
	int		m_nQueueSize;
//	int		m_nQueueDefaultSize;
	int		m_nQueueHead;
	int		m_nQueueTail;
	LPBYTE	m_lpQueue;
	INT64		m_i64Sequence;
	BOOL		m_bNewData;
	HANDLE	m_hEventNewData;
	HANDLE	m_hMutex;
	DWORD		m_dwFlags;
	DWORD		m_dwTimeout;
	BYTE		m_cType;
};

#endif // INC_PKSTREAM

