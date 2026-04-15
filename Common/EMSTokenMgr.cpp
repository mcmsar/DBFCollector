///////////////////////////////////////////////////////////////////////////////
///  EMSTokenMgr.cpp
///
///  PATH: C:\dev\Common
///
///  CREATED: 11/11/2003 3:12:44 PM by Christiaan Burchell
///
///  PURPOSE:  The Token Manager
///
///  COPYRIGHT NOTICE: Copyright (c) 2003-2005 by EMS Technologies, Inc., All rights reserved
///
///  LAST CHANGED: $Date$
///
///  REVISION HISTORY:
///  $Log$


/// 

// EMSTokenMgr.cpp: implementation of the CEMSTokenMgr class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length
#pragma warning(disable:4503)

#include <stdio.h>
#include "EMSTokenMgr.h"
#include <string>
#include "convutility.h"
#include "emsoitypes.h"
#include "mtlconfiguration.h"
#include "routeconfig.h"

#include <string>
#include "emsexcpt.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////
///
/// NAME: CEMSTokenMgr
///
/// CLASS: CEMSTokenMgr
///
/// DESCRIPTION: Class Constructor
///
/// CREATED:     11/11/2003 3:03:44 PM
///
/// SIDE EFFECTS: 
///
/////////////////////////////////////////////////
CEMSTokenMgr::CEMSTokenMgr()
{
    m_pEMSAuthentication = NULL;
}



/////////////////////////////////////////////////
///
/// NAME: ~CEMSTokenMgr
///
/// CLASS: CEMSTokenMgr
///
/// DESCRIPTION: Class Destructor
///
/// CREATED:     11/11/2003 3:03:43 PM
///
/// SIDE EFFECTS: 
///
/////////////////////////////////////////////////
CEMSTokenMgr::~CEMSTokenMgr()
{
    if(m_pEMSAuthentication)
        m_pEMSAuthentication->Release();
}

/////////////////////////////////////////////////
///
/// NAME: _Init
///
/// CLASS: CEMSTokenMgr
///
/// DESCRIPTION: 
///
/// CREATED:     10/31/2003 11:33:05 AM
///
/// RETURN: HRESULT 
///
/// SIDE EFFECTS: 
///
/////////////////////////////////////////////////
HRESULT CEMSTokenMgr::_Init()
{
    HRESULT hr;
    hr = CoCreateInstance( CLSID_EMSAuthentication, 0, CLSCTX_ALL, 
							IID_IEMSAuthentication, (LPVOID*)&m_pEMSAuthentication );
    return hr;
}



/////////////////////////////////////////////////
///
/// NAME: GetToken
///
/// CLASS: CEMSTokenMgr
///
/// DESCRIPTION: 
///
/// CREATED:     10/31/2003 11:33:08 AM
///
/// PARAMETERS: 
///             DWORD dwDestLUTID
///             DWORD dwSrcLUTID
///             LPEMSGATEWAYTOKEN lpSecurityToken
///
/// RETURN: HRESULT 
///
/// SIDE EFFECTS: 
///
/////////////////////////////////////////////////
HRESULT CEMSTokenMgr::GetToken(DWORD dwDestLUTID,DWORD dwSrcLUTID,LPEMSGATEWAYTOKEN lpSecurityToken)
{
    HRESULT hr = S_OK;
    if(m_pEMSAuthentication == NULL)
        hr = _Init();

    if (SUCCEEDED(hr))
    {
        BOOL bAuthenticate = TRUE;
		std::wstring wszRouteName;

		CEMSMTLConfiguration* pConfig = CEMSMTLConfiguration::GetMTLConfigInstance();

		if( !pConfig )
		{
			hr = EMS_INVALID_PTR;
		}

		if( SUCCEEDED(hr) )
		{
			CEMSRouteConfig** apRoutes = 0;
			unsigned long ulRoutes = 0;

			try
			{
				pConfig->GetRouteConfigs( dwSrcLUTID, dwDestLUTID, ulRoutes, apRoutes );

				if( ulRoutes > 0 && apRoutes )
				{
					// Use the first one found.  The OI is the caller of this method and it does not
					// want to broadcast on multiple routes.
					if( apRoutes[0] )
					{
						wszRouteName = apRoutes[0]->GetRouteName();
					}

					for( unsigned long l = 0; l < ulRoutes; l++ )
					{
						if( apRoutes[l] )
						{
							apRoutes[l]->Release();
							apRoutes[l] = 0;
						}
					}

					delete[] apRoutes;
					apRoutes = 0;
				}
			}
			catch( CEMSException& e  )
			{
				if( apRoutes )
				{
					for( unsigned long l = 0; l < ulRoutes; l++ )
					{
						if( apRoutes[l] )
						{
							apRoutes[l]->Release();
							apRoutes[l] = 0;
						}
					}

					delete[] apRoutes;
					apRoutes = 0;
				}

				hr = e.GetErrCode();
			}
			catch( ...  )
			{
				if( apRoutes )
				{
					for( unsigned long l = 0; l < ulRoutes; l++ )
					{
						if( apRoutes[l] )
						{
							apRoutes[l]->Release();
							apRoutes[l] = 0;
						}
					}

					delete[] apRoutes;
					apRoutes = 0;
				}

				hr = EMS_EXCEPTION;
			}
		}

		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( SUCCEEDED(hr) )
		{
			IEMSConfigurationManager* pEMSConfigurationManager = NULL;
			hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL,
										IID_IEMSConfigurationManager, (LPVOID*)&pEMSConfigurationManager );
			if( SUCCEEDED(hr) && pEMSConfigurationManager != NULL)
			{
           
				//::swprintf(wstrGroupID,L"%04d_%04d",min(dwDestLUTID,dwSrcLUTID),max(dwDestLUTID,dwSrcLUTID));

				EMSVARITYPE Value;
				hr = pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End1.Identifier",&Value);
				if (SUCCEEDED(hr))
				{
					if(Value.uiVal == dwSrcLUTID)
					{
						if (SUCCEEDED(pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End1.Out.SecurityToken",&Value))  && Value.dataType == EMSVARITYPE_DATATYPE_STRING)
						{
							std::string str = CEMSConversionUtil::ConvertToString( Value.pwcsVal );
							memcpy(lpSecurityToken->cToken,str.data(),64);
							::CoTaskMemFree(Value.pwcsVal);
							bAuthenticate = FALSE;
						}
					}
					else
					{
						if (SUCCEEDED(pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End2.Out.SecurityToken",&Value))  && Value.dataType == EMSVARITYPE_DATATYPE_STRING)
						{
							std::string str = CEMSConversionUtil::ConvertToString(Value.pwcsVal);
							memcpy(lpSecurityToken->cToken,str.data(),64);
							::CoTaskMemFree(Value.pwcsVal);
							bAuthenticate = FALSE;
						}
					}
				}
				else
				{
					EMSTRACE2(TEXT("Call to %S Failed End1.Identifier hr = %x\n"),wszRouteName.c_str(),hr);
				}

				pEMSConfigurationManager->Release();
			}
			else
			{
				EMSTRACE1(TEXT("IEMSConfigurationManager Failed hr = %x\n"),hr);
			}
		}
		else
		{
			EMSTRACE(TEXT("Failed to retrieve route configuration information need to determine whether a security token has been configured."));
		}
        
        if(bAuthenticate)
        {
            if(m_pEMSAuthentication !=NULL)
            {
                hr = m_pEMSAuthentication->Authenticate(0,dwDestLUTID,lpSecurityToken);
            }
            else
                hr = E_POINTER;
        }
        
    }
    return hr;
}

HRESULT 
CEMSTokenMgr::GetToken(const wchar_t* cwszDestAlias, const wchar_t* cwszSrcAlias, LPEMSGATEWAYTOKEN lpSecurityToken)
{
	HRESULT hr = S_OK;
    if(m_pEMSAuthentication == NULL)
        hr = _Init();

    if (SUCCEEDED(hr))
    {
        BOOL bAuthenticate = TRUE;
		std::wstring wszRouteName;
		DWORD dwDestLUTID = 0;

		CEMSMTLConfiguration* pConfig = CEMSMTLConfiguration::GetMTLConfigInstance();

		if( !pConfig )
		{
			hr = EMS_INVALID_PTR;
		}

		if( SUCCEEDED(hr) )
		{
			CEMSRouteConfig* pRoute = 0;
			CEMSRouteEndConfig* pDestEnd = 0;

			try
			{
				pRoute = pConfig->GetRouteConfig( cwszSrcAlias, cwszDestAlias );

				if( !pRoute )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				wszRouteName = pRoute->GetRouteName();

				pDestEnd = pRoute->GetEnd( cwszDestAlias );

				if( !pDestEnd )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				dwDestLUTID = pDestEnd->GetID();

				pRoute->Release();
				pRoute = 0;

				pDestEnd->Release();
				pDestEnd = 0;
			}
			catch( CEMSException& e  )
			{
				if( pRoute )
				{
					pRoute->Release();
					pRoute = 0;
				}

				if( pDestEnd )
				{
					pDestEnd->Release();
					pDestEnd = 0;
				}

				hr = e.GetErrCode();
			}
			catch( ... )
			{
				if( pRoute )
				{
					pRoute->Release();
					pRoute = 0;
				}

				if( pDestEnd )
				{
					pDestEnd->Release();
					pDestEnd = 0;
				}

				hr = EMS_EXCEPTION;
			}
		}

		if( pConfig )
		{
			pConfig->Release();
			pConfig = 0;
		}

		if( SUCCEEDED(hr) )
		{
			IEMSConfigurationManager* pEMSConfigurationManager = NULL;
			hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL,
										IID_IEMSConfigurationManager, (LPVOID*)&pEMSConfigurationManager );
			if( SUCCEEDED(hr) && pEMSConfigurationManager != NULL)
			{
           
				EMSVARITYPE Value;
				hr = pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End1.Alias",&Value);
				if (SUCCEEDED(hr))
				{
					if( wcsicmp( Value.pwcsVal, cwszSrcAlias) == 0 )
					{
						if (SUCCEEDED(pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End1.Out.SecurityToken",&Value))  && Value.dataType == EMSVARITYPE_DATATYPE_STRING)
						{
							std::string str = CEMSConversionUtil::ConvertToString( Value.pwcsVal );
							memcpy(lpSecurityToken->cToken,str.data(),64);
							::CoTaskMemFree(Value.pwcsVal);
							bAuthenticate = FALSE;
						}
					}
					else
					{
						if (SUCCEEDED(pEMSConfigurationManager->Get(L"RTE",wszRouteName.c_str(),L"End2.Out.SecurityToken",&Value))  && Value.dataType == EMSVARITYPE_DATATYPE_STRING)
						{
							std::string str = CEMSConversionUtil::ConvertToString(Value.pwcsVal);
							memcpy(lpSecurityToken->cToken,str.data(),64);
							::CoTaskMemFree(Value.pwcsVal);
							bAuthenticate = FALSE;
						}
					}
				}
				else
				{
					EMSTRACE2(TEXT("Call to %S Failed End1.Identifier hr = %x\n"),wszRouteName.c_str(),hr);
				}

				pEMSConfigurationManager->Release();
			}
			else
			{
				EMSTRACE1(TEXT("IEMSConfigurationManager Failed hr = %x\n"),hr);
			}
		}
		else
		{
			EMSTRACE(TEXT("Failed to retrieve route configuration information need to determine whether a security token has been configured."));
		}
        
        if(bAuthenticate)
        {
            if(m_pEMSAuthentication !=NULL)
            {
                hr = m_pEMSAuthentication->Authenticate(0,dwDestLUTID,lpSecurityToken);
            }
            else
                hr = E_POINTER;
        }
        
    }
    return hr;
}