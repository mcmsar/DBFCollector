/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/
#ifndef __QUEUE_MEM_STREAM_H__
#define __QUEUE_MEM_STREAM_H__

#include "aobjbase.h"
#include "emspipe.h"
#include "criticalsection.h"
#include "objectqueue.h"

//! @class CEMSQueueMemoryStream
//! This is a memory stream class that acts like a queue of bytes.
class CEMSQueueMemoryStream : public IEMSSeqStream, public CApiObjBase
{
public:
	CEMSQueueMemoryStream( );

/*********************************************************************
*	Public Methods
*********************************************************************/
	EMS_RESULT	SetMaxSize( const ULONG culBytes );

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

/*********************************************************************
*	Other Methods
*********************************************************************/
	ULONG GetCurrentSize() { return m_oQueue.Count(); }

protected: // methods
	virtual ~CEMSQueueMemoryStream();

protected: // data
	CEMSObjectQueue<BYTE>	m_oQueue;
	CEMSCriticalSection		m_csBuffer;
};

#endif // INC_EMSMSTRM
