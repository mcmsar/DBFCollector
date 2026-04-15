/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_CMDSRCRETRY
#define INC_CMDSRCRETRY

#include "cmdsrc.h"

class CEMSCommandSourceRetry : public CEMSCommandSource
{
public:
	CEMSCommandSourceRetry( BYTE cCmdType = 0, INT nMaxLength = 0 );

	/*********************************************************************
	*	IUnknown Methods
	*********************************************************************/
	STDMETHODIMP    QueryInterface (REFIID iid, void **ppv);

	/*********************************************************************
	*	
	*********************************************************************/
	STDMETHODIMP Write( BYTE cTo, const BYTE __RPC_FAR *pv, ULONG cb, ULONG __RPC_FAR *pcbWritten );

protected: // methods
	virtual ~CEMSCommandSourceRetry();

private: // data
    ULONG               m_ulRetryTime;      // in milliseconds

#ifdef TRACE
    BYTE                m_byType;
    LPEMSLOGGER         m_pLogger;
#endif

};

#endif // INC_CMDSRCRETRY

