/********************************************************************
*	Module:		  EMSCmdSk.h
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

	0.0	01/05/24		rvw	start

********************************************************************/
#ifndef INC_EMSCMDSK
#define INC_EMSCMDSK

#include "emspipe.h"

class CEMSCommandSink :	public IEMSCommandSink
{
public:
	CEMSCommandSink( BYTE cProcessType=0 );

/*********************************************************************
*	IUnknown Methods
*********************************************************************/
    STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void); 
    STDMETHODIMP_(ULONG) Release(void); 

/*********************************************************************
*	IEMSCommandSink Methods
*********************************************************************/
	STDMETHODIMP SetType( BYTE cProcessType );
	STDMETHODIMP GetType( BYTE __RPC_FAR *lpcProcessType );
	STDMETHODIMP SetStream( LPEMSSEQSTREAM lpStream );

/*********************************************************************
*	Public Methods
*********************************************************************/
	EMS_RESULT GetCommand( LPBYTE lpBuffer, ULONG ulMaxSize, ULONG *lpulLength );
	EMS_RESULT Register( HANDLE *lphEvent=0 );
	EMS_RESULT UnRegister( void );

private: // methods
	virtual ~CEMSCommandSink();
	void _ReleaseEventHandle( void );

private: // data
	LONG				m_lRefCount;
	BYTE				m_cProcessType;
	HANDLE			m_hEventNewCommand;
	LPEMSSEQSTREAM	m_lpStream;
	LPEMSCOMMANDCHANNEL m_lpCmdChannel;
	BOOL				m_bRegistered;
};

#endif // INC_EMSCMDSK

