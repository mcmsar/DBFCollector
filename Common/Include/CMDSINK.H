/********************************************************************
*	Module:			cmdsink.h
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
#ifndef INC_CMDSINK
#define INC_CMDSINK

#include "emspipe.h"

class CEMSCommandSink : public IEMSCommandSink
{
public:
	CEMSCommandSink( BYTE cCmdType = 0, INT nMaxLength = 0 );

	/*********************************************************************
	*	IUnknown Methods
	*********************************************************************/
	STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
	STDMETHODIMP_(ULONG) AddRef(void); 
	STDMETHODIMP_(ULONG) Release(void); 

	/*********************************************************************
	*	IEMSDataSink Methods
	*********************************************************************/

	STDMETHODIMP SetType( BYTE cDataType );
	STDMETHODIMP GetType( BYTE __RPC_FAR *lpcDataType );
	STDMETHODIMP GetMaxLength( INT __RPC_FAR *lpnMaxLength );
	STDMETHODIMP SetMaxLength( INT nMaxLength );
	STDMETHODIMP SetStream( LPEMSPACKETSTREAM lpStream );
	STDMETHODIMP GetStream( LPEMSPACKETSTREAM __RPC_FAR *lplpStream );
	STDMETHODIMP OnDataAvailable( DWORD dwSize, DWORD dwFlags );

	/*********************************************************************
	*	IEMSCommandSink Methods
	*********************************************************************/

	STDMETHODIMP SetCmdType( BYTE cCmdType );
	STDMETHODIMP GetCmdType( BYTE __RPC_FAR *lpcCmdType );

	/*********************************************************************
	*	
	*********************************************************************/

	inline HANDLE GetEventHandle( void ) { return m_hOnDataEvent; }

	EMS_RESULT Read( BYTE *lpBuffer, ULONG ulMaxLength, ULONG *lpulRead );

protected: // methods
	virtual ~CEMSCommandSink();

private: // data
	volatile LONG	m_lRefCount;
	BYTE			m_cType;
	BYTE			m_cCmdType;
	INT				m_nMaxLength;
	LPEMSPACKETSTREAM m_lpStream;
	HANDLE			m_hOnDataEvent;
};

#endif // INC_CMDSINK

