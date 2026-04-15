///////////////////////////////////////////////////////////////////////////////
//  SitHelper.h
//
//  PATH: C:\Dev\LutServer\include
//
//  CREATED: 2/14/2003 1:26:33 PM by Christiaan Burchell
//
//  PURPOSE:  Class to send and receve Sit messages using the gateway
//
//  COPYRIGHT NOTICE: Copyright (c) 2003 by EMS Technologies, Inc., All rights reserved
//
//  LAST CHANGED: $Date$
//
//  REVISION HISTORY:
//  $Log$

// 

// SitHelper.h: interface for the CSitHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SITHELPER_H__5AEFDB07_A5DA_4AE3_BEA7_D88777D2956F__INCLUDED_)
#define AFX_SITHELPER_H__5AEFDB07_A5DA_4AE3_BEA7_D88777D2956F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "aobjbase.h"
#include "igateway.h"
#include "sitstream.h"

class CSitHelper  
{
public:
	CSitHelper();
	virtual ~CSitHelper();

private:

    class CCallbackData
    {
    public:
        CEvent m_EventMessageFound;
        CEvent m_KillThread;
        CEvent m_TheadDead;
        CString m_OIID;
        CString m_LutID;
        ULONG m_SitCode;
        CEMSSitMessageBase* m_pMessage;
        DWORD m_Timeout;

        CEvent m_ThreadCreated;
        DWORD m_MessageNumb;
    };

    class CSitCallback : public IEMSGatewayNotification,
						 public CApiObjBase
    {
    public:
        CCallbackData* m_pData;


	    CSitCallback() 
        {
        }
	    ~CSitCallback() {}

	    // IUnknown


////////////////////////////////////////////////
//
// NAME: STDMETHODIMP_
//
// DESCRIPTION: Adds a Refrence to the class
//
// CREATED:     2/14/2003 1:27:08 PM
//
// PARAMETERS: 
//             ULONG
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
        STDMETHODIMP_(ULONG) AddRef()
        {
	        return IncrRefCount();
        }



////////////////////////////////////////////////
//
// NAME: STDMETHODIMP_
//
// DESCRIPTION: Releases a refrence to the class
//
// CREATED:     2/14/2003 1:27:29 PM
//
// PARAMETERS: 
//             ULONG
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
        STDMETHODIMP_(ULONG) Release()
        {
	        if (DecrRefCount() == 0)
	        {
		        delete this;
		        return 0;
	        }
	        return GetRefCount();
        }

        STDMETHODIMP QueryInterface(REFIID riid, LPVOID *lppObj)
        {
	        EMS_RESULT hr = E_NOINTERFACE;

	        if ( lppObj )
	        {
		        LPUNKNOWN lpUnknown = 0;

		        *lppObj = 0;

		        if ( riid == IID_IUnknown || riid == IID_IEMSGatewayNotification )
		        {
  			        lpUnknown = (IUnknown *)(IEMSGatewayNotification*)this;
		        }
		        if ( lpUnknown )
		        {
			        lpUnknown->AddRef();

  		        hr = S_OK;
 		        }
		        *lppObj = lpUnknown;
	        }
	        else
  	        hr = E_INVALIDARG;

	        return hr;
        }


         //IEMSGatewayNotification
        STDMETHODIMP
        OnMsgReceived( /* [in] */ EMSGATEWAYDATATYPE eType,
								        /* [size_is][in] */ BYTE cMsg[  ],
								        /* [in] */ long lMsgSize,
								        /* [in] */ EMSGATEWAYTOKEN *lpSecurityToken,
								        /* [in] */ EMSGATEWAYADDRESS *lpFromAddress);
    };


    static UINT GetMessageThread( LPVOID pParam );

    //static DWORD GetOIID();

public:

    static EMS_RESULT SendReciveSitMessage(CEMSSitMessageBase* pSendMessage, // the message to send
                                       const TCHAR* szLutID, // were the messag is to be sent from
                                       ULONG SitCode,  // the sit message to receive
                                       CEMSSitMessageBase** pResponceMessage, // the receved message
                                       DWORD TimeOut = INFINITE,  // time in miliseconds to wait
                                       HANDLE hKillEvent = NULL
                                       );
    static EMS_RESULT SendSitMessage(CEMSSitMessageBase* pMessage,
                                      const TCHAR* szLutID,
                                      DWORD* pMessageNumber);

    static EMS_RESULT SendRawSitMessage(const TCHAR* szRawSit,const TCHAR* szLutID);

};

#endif // !defined(AFX_SITHELPER_H__5AEFDB07_A5DA_4AE3_BEA7_D88777D2956F__INCLUDED_)
