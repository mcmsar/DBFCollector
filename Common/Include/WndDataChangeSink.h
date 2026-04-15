/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef _WNDDATACHANGESINK_H
#define _WNDDATACHANGESINK_H

#include "aobjbase.h"
#include "ChangeMonitor.h"

//! @class CEMSWndDataChangeSink 
//! Generic implementation of an IEMSDataChangeSink that will
//! simply post a windows message on data change
class CEMSWndDataChangeSink : public IEMSDataChangeSink, public CApiObjBase
{
public:
	CEMSWndDataChangeSink( const HWND chWndNotify, const UINT cuiMessageID );
	CEMSWndDataChangeSink( const CEMSWndDataChangeSink& x );
	~CEMSWndDataChangeSink();

	/*********************************************************************
	*	IEMSDataChangeSink Methods
	*********************************************************************/
	//! @fn void OnChange()
	//! IEMSDataChangeSink method.  
	//! Ripple event to all subscribed sinks.
	HRESULT STDMETHODCALLTYPE 
			OnChange(	const ULONG			culLutID,
						const EMSDATACHANGE ceDataChange,
						const ULONG			culUserDataSize,
						const BYTE*			cabyUserData );

	/*********************************************************************
	*	IUnknown Methods
	*********************************************************************/
	STDMETHOD(QueryInterface)		(THIS_ REFIID, LPVOID FAR *);
	STDMETHOD_(ULONG, AddRef)		(THIS);
	STDMETHOD_(ULONG, Release)		(THIS);

private:
	HWND	m_hWndNotify;
	UINT	m_uiMessageID;
};

#endif //_WNDDATACHANGESINK_H
