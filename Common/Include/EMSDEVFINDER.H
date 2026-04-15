#ifndef INC_EMSDEVFINDER
#define INC_EMSDEVFINDER

#include "EMSDEVICES.h"

class CSubDeviceFinder
{
public:
	typedef struct _tagSubDevice
	{
		DWORD dwVirtID;				//in
		IID iid;					//in
		EMS_RESULT hr;				//out
		LPEMSSUBDEVICE lpSubDev;	//out
	} SUBDEV, *LPSUBDEVS;

	static EMS_RESULT GetSubDevices( DWORD dwNumSubDevs, LPSUBDEVS lpSubDevs, DWORD dwClsCtx = CLSCTX_ALL );
};

#endif