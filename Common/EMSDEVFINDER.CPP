#include "EMSDEVFINDER.h"
#include <string.h>

#ifdef _DEBUG
#include "debugwin.h"
#include <stdio.h>
CDebugWin DevFDBG;
char szDevFDBG[256];

HRESULT CLSIDToStr( LPSTR lpszStr, GUID guid )
{
	EMS_RESULT hr = EMS_OK;
	LPWSTR lpwStr;
	LPWSTR pswStr;
	LPSTR lpsz;

	if( !lpszStr )
	{
		return E_INVALIDARG;
	}

	hr = StringFromCLSID( guid, &lpwStr );

	if( hr != S_OK )
		return hr;

	//convert back from UNICODE to ANSI
	pswStr = lpwStr;
	lpsz = lpszStr;

	while( *pswStr )
	{
		*lpsz++ = (CHAR)*pswStr++;
	}

	*lpsz = '\0';

	CoTaskMemFree( (LPVOID)lpwStr );

	return hr;
}

#endif

EMS_RESULT CSubDeviceFinder::GetSubDevices( DWORD dwNumSubDevs, LPSUBDEVS lpSubDevs, DWORD dwClsCtx )
{
	DWORD dwNumDevs;
	EMS_RESULT hr;
	EMS_RESULT local_hr;
	EMSDEVICEINFO Devs[50];
	IID iid[1];
	LPEMSSUBDEVICEFACTORY lpDevFac = NULL;
	LPEMSENUMDEVICES lpEnum = NULL;

	memcpy( iid, &IID_IEMSSubDeviceFactory, sizeof(IID) );

	//initialize list
	for( DWORD k = 0; k < dwNumSubDevs; k++ )
	{
		lpSubDevs[k].hr = EMS_NOINTERFACE;
		lpSubDevs[k].lpSubDev = NULL;
	}

#ifdef _DEBUG
	DevFDBG.OutputMsg((LPVOID)"creating EMSDEVICES object");
#endif

	hr = ::CoCreateInstance( CLSID_EMSDevices, NULL, CLSCTX_ALL, IID_IEMSEnumDevices, (LPVOID*)&lpEnum );
	if( SUCCEEDED(hr) )
	{
		hr = lpEnum->Initialize();
		if( SUCCEEDED(hr) )
		{

			dwNumDevs = 50;
			hr = lpEnum->EnumDevices( &dwNumDevs, Devs, 1, iid );

			if( SUCCEEDED(hr) )
			{
				for( DWORD i = 0; i < dwNumDevs; i++ )
				{

#ifdef _DEBUG
					CLSIDToStr(szDevFDBG, Devs[i].guid);
					DevFDBG.OutputMsg((LPVOID)szDevFDBG);
#endif
					local_hr = ::CoCreateInstance( Devs[i].guid, NULL, dwClsCtx, IID_IEMSSubDeviceFactory, (LPVOID*)&lpDevFac );

#ifdef _DEBUG
					sprintf(szDevFDBG, "local_hr = 0x%x", local_hr);
					DevFDBG.OutputMsg((LPVOID)szDevFDBG);
#endif

					if(SUCCEEDED(local_hr))
					{
						for( DWORD j = 0; j < dwNumSubDevs; j++ )
						{
							if( FAILED(lpSubDevs[j].hr) )
							{

#ifdef _DEBUG
								DevFDBG.OutputMsg((LPVOID)"Calling create subdevice.");
#endif

								lpSubDevs[j].hr = lpDevFac->CreateSubDevice( lpSubDevs[j].iid, lpSubDevs[j].dwVirtID, &lpSubDevs[j].lpSubDev );

#ifdef _DEBUG
								DevFDBG.OutputMsg((LPVOID)"Called create device.");
#endif
							}
						}
						lpDevFac->Release();
						lpDevFac = NULL;
					}
				}
			}
		
		}

		lpEnum->Release();
		lpEnum = NULL;
	}

	return hr;
}