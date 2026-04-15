///////////////////////////////////////////////////////////////////////////////
///  EMSTokenMgr.h
///
///  PATH: C:\dev\GUI Common
///
///  CREATED: 11/11/2003 3:12:56 PM by Christiaan Burchell
///
///  PURPOSE:  The Token Manager
///
///  COPYRIGHT NOTICE: Copyright (c) 2003 by EMS Technologies, Inc., All rights reserved
///
///  LAST CHANGED: $Date$
///
///  REVISION HISTORY:
///  $Log$

/// 

// EMSTokenMgr.h: interface for the CEMSTokenMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMSTOKENMGR_H__AD9F3F03_3FDC_4169_B947_724262F6F973__INCLUDED_)
#define AFX_EMSTOKENMGR_H__AD9F3F03_3FDC_4169_B947_724262F6F973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "emsauthentication.h"

class CEMSTokenMgr
{
public:
    CEMSTokenMgr();
    virtual ~CEMSTokenMgr();
    HRESULT GetToken(DWORD dwDestLUTID,DWORD dwSrcLUTID,LPEMSGATEWAYTOKEN lpSecurityToken);
	HRESULT GetToken(const wchar_t* cwszDestAlias, const wchar_t* cwszSrcAlias, LPEMSGATEWAYTOKEN lpSecurityToken);

private:
    HRESULT _Init();
    IEMSAuthentication* m_pEMSAuthentication;
};

#endif // !defined(AFX_EMSTOKENMGR_H__AD9F3F03_3FDC_4169_B947_724262F6F973__INCLUDED_)
