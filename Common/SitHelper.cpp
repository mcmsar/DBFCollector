///////////////////////////////////////////////////////////////////////////////
//  SitHelper.cpp
//
//  PATH: C:\Dev\LutServer\common
//
//  CREATED: 2/14/2003 1:23:24 PM by Christiaan Burchell
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

// SitHelper.cpp: implementation of the CSitHelper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#define INITGUID
#include <initguid.h>
#include "SitHelper.h"
#include "SitParse.h"
#include "EMSit751.h"
#include "emsoitypes.h"
#include "emsiteif.H"

#include "EMSSourceInfo.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////
//
// NAME: CSitHelper
//
// CLASS: CSitHelper
//
// DESCRIPTION: Class Constructor
//
// CREATED:     2/14/2003 1:23:27 PM
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CSitHelper::CSitHelper()
{

}



////////////////////////////////////////////////
//
// NAME: ~CSitHelper
//
// CLASS: CSitHelper
//
// DESCRIPTION: Class Destructor
//
// CREATED:     2/14/2003 1:23:28 PM
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
CSitHelper::~CSitHelper()
{

}




////////////////////////////////////////////////
//
// NAME: GetMessageThread
//
// CLASS: CSitHelper
//
// DESCRIPTION: the Receve message thread
//
// CREATED:     2/14/2003 1:23:43 PM
//
// PARAMETERS: 
//             LPVOID pParam
//
// RETURN: UINT 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
UINT CSitHelper::GetMessageThread( LPVOID pParam )
{
    EMSTRACE("Thread Created\n");
    CCallbackData* pData = static_cast<CCallbackData*>(pParam);
    if(pData == NULL)
        return -1;


    CSitCallback* pCallBack = NULL;

    CoInitializeEx(NULL,COINIT_MULTITHREADED);


    pCallBack = new CSitCallback();
    pCallBack->m_pData = pData;



    IEMSGatewayConnection* pConn = 0;
	HRESULT hr = CoCreateInstance( CLSID_EMSGateway, 0, CLSCTX_ALL, IID_IEMSGatewayConnection, (void**) &pConn );
    if FAILED(hr)
    {
        pData->m_TheadDead.SetEvent();
        return hr;
    }
	EMSGATEWAYADDRESS addrFrom;
	memset( &addrFrom, 0, sizeof(EMSGATEWAYADDRESS) );

	addrFrom.type = EMSGatewayCSAddress;
	memcpy( addrFrom.cAddress, pData->m_LutID.GetBuffer(pData->m_LutID.GetLength()), min(64,pData->m_LutID.GetLength()) );

	hr = pConn->Connect( &addrFrom, 0 );
    if FAILED(hr)
    {
        pConn->Release();
        pData->m_TheadDead.SetEvent();
        return hr;
    }

	
	IEMSGatewayEventManager* pEventMgr = 0;
	DWORD dwCookie = 0;
	if( SUCCEEDED(hr) )
    {
		if( pCallBack )
		{
			hr = pConn->QueryInterface( IID_IEMSGatewayEventManager, (void**) &pEventMgr );

			if( SUCCEEDED(hr) )
			{
                EMSTRACE("Thread Advise\n");
				hr = pEventMgr->Advise( pCallBack, FALSE, &dwCookie );
			}
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}
	}

    pData->m_ThreadCreated.SetEvent();
    if(FAILED(hr))
        pData->m_EventMessageFound.SetEvent();
    else
    {
        EMSTRACE("Thread WaitForSingleObject\n");
        WaitForSingleObject(pData->m_KillThread,pData->m_Timeout);
    }
    
    EMSTRACE("End WaitForSingleObject\n");

    if( pCallBack )
	{
		if( pEventMgr )
		{
			if( dwCookie )
				pEventMgr->Unadvise( dwCookie );
		}

		pCallBack->Release();
		pCallBack = 0;
	}

	if( pEventMgr )
	{
		pEventMgr->Release();
		pEventMgr = 0;
	}

    if(pConn)
    {
        pConn->Disconnect();
        pConn->Release();
        pConn = NULL;
    }

    pData->m_TheadDead.SetEvent();

    return 42;

}


////////////////////////////////////////////////
//
// NAME: SendReciveSitMessage
//
// DESCRIPTION: Semds and Receves a sit message
//
// CREATED:     2/11/2003 1:50:08 PM
//
// PARAMETERS: 
//             CEMSSitMessageBase* pSendMessage
//             const char* szFrom
//             const char* szTo
//             ULONG sitnumber
//             CEMSSitMessageBase** pResponceMessage
//             ULONG TimeOut = 0
//
// RETURN: static EMS_RESULT 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
EMS_RESULT CSitHelper::SendReciveSitMessage(CEMSSitMessageBase* pSendMessage, // the message to send
                                       const TCHAR* szLutID, // were the messag is to be sent from
                                       ULONG SitCode,  // the sit message to receive
                                       CEMSSitMessageBase** pResponceMessage, // the receved message
                                       DWORD TimeOut,  // time in miliseconds to wait
                                       HANDLE hKillEvent
                                       ) 
{


    EMSTRACE1("SendReciveSitMessage Looking for Message 0x%x\n",SitCode);
    CEMSSourceInfo Si;
    Si.Init();
    CCallbackData* pData;
    pData = new CCallbackData();

    pData->m_OIID.Format(_T("%d"),Si.GetOIID());


    pData->m_LutID = szLutID;
    pData->m_SitCode = SitCode;
    pData->m_Timeout = TimeOut;


    EMSTRACE("CreateThread\n");
    AfxBeginThread(CSitHelper::GetMessageThread,(LPVOID)pData);

    DWORD NumbEvents = 2;
    HANDLE Events[3];
    Events[0] = pData->m_ThreadCreated;
    Events[1] = pData->m_TheadDead;
    if(hKillEvent)
    {
        NumbEvents = 3;
        Events[2] = hKillEvent;
    }


    
    if(WaitForMultipleObjects(NumbEvents,Events,FALSE,INFINITE) != WAIT_OBJECT_0)
    {
        EMSTRACE("Thread has Died\n");
        return EMS_WAIT_ABANDONDED;
    }


    EMSTRACE("SendMessage\n");
    pData->m_MessageNumb = 0;
    HRESULT hr = SendSitMessage(pSendMessage,szLutID,&pData->m_MessageNumb);
    if(SUCCEEDED(hr))
    {

        Events[0] = pData->m_EventMessageFound;
        if(WaitForMultipleObjects(NumbEvents,Events,FALSE,TimeOut) == WAIT_OBJECT_0)
        {
            EMSTRACE("Got Message\n");
            if(pData->m_pMessage == NULL)
            {
                EMSTRACE("m_pMessage NULL\n");
                hr = EMS_WAIT_ABANDONDED;
            }
            *pResponceMessage = pData->m_pMessage;
        }
        else
        {
            EMSTRACE("Timeout\n");
            *pResponceMessage = NULL;
            hr = EMS_WAIT_TIMEOUT;
        }
    }
    else
    {
        EMSTRACE("SendSitMessage Failed\n");
    }

    
    return hr;
}





////////////////////////////////////////////////
//
// NAME: endSitMessage
//
// DESCRIPTION: test
//
// PARAMETERS: 
//             CEMSSitMessageBase* pMessage
//
// RETURN: static EMS_RESULT 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
EMS_RESULT CSitHelper::SendSitMessage(CEMSSitMessageBase* pMessage,
                                      const TCHAR* szLutID, 
                                      DWORD* pMessageNumber)
{
    CEMSSourceInfo Si;
    Si.Init();
    EMS_RESULT hr = EMS_OK;
    if (pMessage)
	{
        CString strOIID;
        strOIID.Format(_T("%d"),Si.GetOIID());
        EMSTRACE1("OIID = %s\n",strOIID);

        IEMSGatewayConnection* pConn = 0;
		hr = CoCreateInstance( CLSID_EMSGateway, 0, CLSCTX_ALL, IID_IEMSGatewayConnection, (void**) &pConn );

		if( SUCCEEDED(hr) )
		{
			EMSGATEWAYADDRESS addrFrom;
			memset( &addrFrom, 0, sizeof(EMSGATEWAYADDRESS) );

			addrFrom.type = EMSGatewayCSAddress;

            char tempOIID[10];

#ifdef _UNICODE
            USES_CONVERSION;
            _snprintf(tempOIID,10,W2A((LPCTSTR)strOIID));
#else
			_snprintf(tempOIID,10,(LPCTSTR)strOIID);
#endif
            memcpy( addrFrom.cAddress, tempOIID, strlen(tempOIID) );

			hr = pConn->Connect( &addrFrom, 0 );
		}
        else
        {
            EMSTRACE("CoCreateInstance IEMSGatewayConnection Failed\n");
        }

        if( SUCCEEDED(hr) )
		{
            *pMessageNumber = Si.GetNextMsgNumber(_ttoi(szLutID));

            pMessage->SetReportingMCC(_ttoi(strOIID)); // me
            pMessage->SetSitDestination(_ttoi(szLutID)); // the lut
            pMessage->SetCurrentMsgNumber(*pMessageNumber);

			EMSGATEWAYDATATYPE eType = EMSGatewaySitMsg;
			
			EMSGATEWAYTOKEN secToken;
			memset( &secToken, 0, sizeof( EMSGATEWAYTOKEN ) );
			EMSGATEWAYADDRESS addrTo;
			memset( &addrTo, 0, sizeof( EMSGATEWAYADDRESS ) );
			

            char tempLUTID[10];

            addrTo.type = EMSGatewayCSAddress;

#ifdef _UNICODE
            USES_CONVERSION;
            _snprintf(tempLUTID,10,W2A((LPCTSTR)szLutID));
#else
			_snprintf(tempLUTID,10,(LPCTSTR)szLutID);
#endif
            memcpy( addrTo.cAddress, tempLUTID, strlen(tempLUTID) );

			BYTE* cMsg = 0;
			long lMsgSize = 0; 

            hr = CEMSSitStream::GetByteArray( pMessage, cMsg, lMsgSize );

			if( SUCCEEDED(hr) )
			{
                EMSTRACE("Sending Sit Message\n");
				hr = pConn->Send( eType, cMsg, lMsgSize, &secToken, &addrTo );
			}
            else
            {
                EMSTRACE("GetByteArray Failed\n");
            }

			if( cMsg )
			{
				delete[] cMsg;
				cMsg = 0;
			}

		}
        else
        {
            EMSTRACE("IEMSGatewayConnection->Connect Failed\n");
        }

        if(pConn)
        {
            pConn->Disconnect();
            EMSTRACE("IEMSGateway->Release()");
            pConn->Release();
		    pConn = 0;
        }
	}
    else
    {
        EMSTRACE("Bad Param\n");
        hr = EMS_BAD_PARAM;
    }
    return hr;
}


 //IEMSGatewayNotification
////////////////////////////////////////////////
//
// NAME: OnMsgReceived
//
// CLASS: CSitHelper::CSitCallback
//
// DESCRIPTION: the message recever handler
//
// CREATED:     2/14/2003 1:24:41 PM
//
// PARAMETERS: 
//              EMSGATEWAYDATATYPE eType
//             BYTE cMsg[  ]
//             long lMsgSize
//             EMSGATEWAYTOKEN *lpSecurityToken
//             EMSGATEWAYADDRESS *lpFromAddress
//
// RETURN: STDMETHODIMP 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
STDMETHODIMP CSitHelper::CSitCallback::OnMsgReceived(
                                        /* [in] */ EMSGATEWAYDATATYPE eType,
								        /* [size_is][in] */ BYTE cMsg[  ],
								        /* [in] */ long lMsgSize,
								        /* [in] */ EMSGATEWAYTOKEN *lpSecurityToken,
								        /* [in] */ EMSGATEWAYADDRESS *lpFromAddress)
{
	if( lMsgSize && lpFromAddress)
	{

        CString from = (char*)lpFromAddress->cAddress;
        EMSTRACE1("Receved Message From %s\n",from);
        char tempbuff[2560];
        memset(tempbuff,0,2560);
        memcpy(tempbuff,cMsg,min(2560,lMsgSize));
        EMSTRACE1("%s\n",tempbuff);
        CEMSSitMessageBase* pMessage = NULL;
        CEMSSitParser parser;
        int messages  = 0;

        EMSTRACE0("Parsing Message\n");
        switch(eType)
        {
            case EMSGatewaySitMsg:
                EMSTRACE0("ParseSitByteArray\n");
                if(parser.ParseSitByteArray(cMsg,lMsgSize,&pMessage,1,&messages)!= EMS_OK)
                {
                    EMSTRACE("ParseSitByteArray Failed");
                }
            break;
            case EMSGatewaySITMsgFile:
            {
                EMSTRACE0("ParseSitFile\n");

        #ifdef _UNICODE
                    USES_CONVERSION;
                    if(parser.ParseSitFile(A2W(tempbuff),&pMessage,1,&messages)!= EMS_OK)
                    {
                            EMSTRACE("ParseSitFile Failed");
                    }

        #else
			        if(parser.ParseSitFile(tempbuff,&pMessage,1,&messages)!= EMS_OK)
                    {
                        EMSTRACE("ParseSitFile Failed");
                    }
        #endif
                    break;
            }
            default:
                EMSTRACE1("Unsupported type %d\n",eType);
        }
        if(pMessage)
        {
            EMSTRACE1("From %d\n",pMessage->GetReportingMCC());
            EMSTRACE1("Sit %d\n",pMessage->GetSitNumber());
            EMSTRACE1("Dest %d\n",pMessage->GetSitDestination());
            EMSTRACE1("Code 0x%X\n",pMessage->GetSitCode());

            if(pMessage->GetReportingMCC() == _ttoi(m_pData->m_LutID))
            {

                if(pMessage->GetSitCode() == m_pData->m_SitCode)
                {
                    EMSTRACE("Found Message!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
                    m_pData->m_pMessage = pMessage;
                    m_pData->m_EventMessageFound.SetEvent(); // tell the main thread that we have receved the event
                    m_pData->m_KillThread.SetEvent();
                }
                else if(pMessage->GetSitCode() == 0x751A)
                {
                   EMSTRACE("Found 0x751A\n");
                   CEMSSit751A* pSit751A = (CEMSSit751A*)pMessage;
                   CString strStatus = pSit751A->GetStatus();
                   DWORD MessageNo = pSit751A->GetAckMsgNumber();
                  
                   EMSTRACE2("Status = %s Message No = %d\n",strStatus,MessageNo);
                   
                   if(!strStatus.IsEmpty() && m_pData->m_MessageNumb == MessageNo)
                   {
                        if(strStatus == _T("CPND"))
                        {
                            EMSTRACE("Found CPND Message");
                            m_pData->m_pMessage = NULL;
                            m_pData->m_EventMessageFound.SetEvent(); // tell the main thread that we have receved the event
                            m_pData->m_KillThread.SetEvent();
                        }
                   }

                   delete pMessage;
                }
                else
                {
                    EMSTRACE("Not looking for that type of message\n");
                    delete pMessage;
                }
            }
            else
            {
                EMSTRACE("Message Not for me\n");
            }
        }
        else
        {
            EMSTRACE0("pMessage is NULL\n");
        }
	}
	return EMS_OK;
}



////////////////////////////////////////////////
//
// NAME: SendRawSitMessage
//
// CLASS: CSitHelper
//
// DESCRIPTION: Sends a raw sit message
//
// CREATED:     3/17/2003 3:56:08 PM
//
// PARAMETERS: 
//             const TCHAR* szRawSit
//             const TCHAR* szLutID
//
// RETURN: EMS_RESULT 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
EMS_RESULT CSitHelper::SendRawSitMessage(const TCHAR* szRawSit,const TCHAR* szLutID)
{
    CEMSSourceInfo Si;
    Si.Init();
    EMS_RESULT hr = EMS_OK;
    if (szRawSit)
	{
        CString strOIID;
        strOIID.Format(_T("%d"),Si.GetOIID());
        EMSTRACE1("OIID = %s\n",strOIID);

        IEMSGatewayConnection* pConn = 0;
		hr = CoCreateInstance( CLSID_EMSGateway, 0, CLSCTX_ALL, IID_IEMSGatewayConnection, (void**) &pConn );

		if( SUCCEEDED(hr) )
		{
			EMSGATEWAYADDRESS addrFrom;
			memset( &addrFrom, 0, sizeof(EMSGATEWAYADDRESS) );

			addrFrom.type = EMSGatewayCSAddress;

            char tempOIID[10];

#ifdef _UNICODE
            USES_CONVERSION;
            _snprintf(tempOIID,10,W2A((LPCTSTR)strOIID));
#else
			_snprintf(tempOIID,10,(LPCTSTR)strOIID);
#endif
            memcpy( addrFrom.cAddress, tempOIID, strlen(tempOIID) );

			hr = pConn->Connect( &addrFrom, 0 );
		}
        else
        {
            EMSTRACE("CoCreateInstance IEMSGatewayConnection Failed\n");
        }

        if( SUCCEEDED(hr) )
		{
			EMSGATEWAYDATATYPE eType = EMSGatewaySitMsg;
			
			EMSGATEWAYTOKEN secToken;
			memset( &secToken, 0, sizeof( EMSGATEWAYTOKEN ) );
			EMSGATEWAYADDRESS addrTo;
			memset( &addrTo, 0, sizeof( EMSGATEWAYADDRESS ) );
			

            char tempLUTID[10];

            addrTo.type = EMSGatewayCSAddress;

#ifdef _UNICODE
            USES_CONVERSION;
            _snprintf(tempLUTID,10,W2A((LPCTSTR)szLutID));
#else
			_snprintf(tempLUTID,10,(LPCTSTR)szLutID);
#endif
            memcpy( addrTo.cAddress, tempLUTID, strlen(tempLUTID) );

			
            long lMsgSize = _tcslen(szRawSit);
            BYTE* cMsg = new BYTE[lMsgSize];
            
#ifdef _UNICODE
            memcpy(cMsg,W2A(szRawSit),lMsgSize);
#else
			memcpy(cMsg,szRawSit,lMsgSize);
#endif

			if( SUCCEEDED(hr) )
			{
                EMSTRACE("Sending Sit Message\n");
				hr = pConn->Send( eType, cMsg, lMsgSize, &secToken, &addrTo );
			}
            else
            {
                EMSTRACE("GetByteArray Failed\n");
            }

			if( cMsg )
			{
				delete[] cMsg;
				cMsg = 0;
			}

		}
        else
        {
            EMSTRACE("IEMSGatewayConnection->Connect Failed\n");
        }

        if(pConn)
        {
            pConn->Disconnect();
            EMSTRACE("IEMSGateway->Release()");
            pConn->Release();
		    pConn = 0;
        }
	}
    else
    {
        EMSTRACE("Bad Param\n");
        hr = EMS_BAD_PARAM;
    }
    return hr;
}
