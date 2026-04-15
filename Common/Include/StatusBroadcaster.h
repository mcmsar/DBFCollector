

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon Jun 18 12:19:18 2012
 */
/* Compiler settings for C:\SAR\Common\Include\StatusBroadcaster.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __StatusBroadcaster_h__
#define __StatusBroadcaster_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSStatusBroadcaster_FWD_DEFINED__
#define __IEMSStatusBroadcaster_FWD_DEFINED__
typedef interface IEMSStatusBroadcaster IEMSStatusBroadcaster;
#endif 	/* __IEMSStatusBroadcaster_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_StatusBroadcaster_0000_0000 */
/* [local] */ 

/********************************************************************
*	Module:			StatusBroadcaster.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structure for Active Beacon Data Record; 
*					Defines methods to be implemented in the StatusBroadcaster class )
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date		Auth	Changes
	===	====		====	=======


********************************************************************/
#ifndef INC_STATUS_BROADCASTER
#define INC_STATUS_BROADCASTER

// {99FAB986-B46D-4779-A28C-655F71F68685}
DEFINE_GUID(CLSID_EMSStatusBroadcaster, 0x99fab986, 0xb46d, 0x4779, 0xa2, 0x8c, 0x65, 0x5f, 0x71, 0xf6, 0x86, 0x85);
 
// {C2F97501-1617-460d-8B15-DC911D2C64F7}
DEFINE_GUID( IID_IEMSStatusBroadcaster, 0xc2f97501, 0x1617, 0x460d, 0x8b, 0x15, 0xdc, 0x91, 0x1d, 0x2c, 0x64, 0xf7);
 


extern RPC_IF_HANDLE __MIDL_itf_StatusBroadcaster_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatusBroadcaster_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSStatusBroadcaster_INTERFACE_DEFINED__
#define __IEMSStatusBroadcaster_INTERFACE_DEFINED__

/* interface IEMSStatusBroadcaster */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef 
enum _tagEMSCOMPONENTSTATUS
    {	EMS_STATUS_OK	= 0,
	EMS_STATUS_WARNING	= 1,
	EMS_STATUS_ERROR	= 2,
	EMS_STATUS_UNKNOWN	= 3
    } 	EMSCOMPONENTSTATUS;

typedef enum _tagEMSCOMPONENTSTATUS *LPEMSCOMPONENTSTATUS;

typedef 
enum tagEMSAntenna_State
    {	EMS_ANTENNA_STATE_IDLE	= 0,
	EMS_ANTENNA_STATE__TRACKING	= 1,
	EMS_ANTENNA_STATE_TRACKING_ACQUISTION	= 2,
	EMS_ANTENNA_STATE_STOW	= 3,
	EMS_ANTENNA_STATE_FAILED	= 4,
	EMS_ANTENNA_STATE_OUTAGE	= 5
    } 	EMSANTENNA_STATE;


#pragma pack()

EXTERN_C const IID IID_IEMSStatusBroadcaster;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2F97501-1617-460d-8B15-DC911D2C64F7")
    IEMSStatusBroadcaster : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BroadcastStatus( 
            /* [in] */ const ULONG culLutID,
            /* [in] */ const ULONG culServiceID,
            /* [in] */ const EMSTIME ctmTimeStamp,
            /* [in] */ const EMSCOMPONENTSTATUS eStatus,
            /* [string][in] */ const wchar_t *cwszServiceDescr,
            /* [string][in] */ const wchar_t *cwszError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BroadcastAntennaDetails( 
            /* [in] */ const ULONG culAntennaID,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const EMSTIME ctmTimeStamp,
            /* [in] */ const EMSANTENNA_STATE ceState,
            /* [in] */ const float cfAzimuth,
            /* [in] */ const float cfElevation) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSStatusBroadcasterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSStatusBroadcaster * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSStatusBroadcaster * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSStatusBroadcaster * This);
        
        HRESULT ( STDMETHODCALLTYPE *BroadcastStatus )( 
            IEMSStatusBroadcaster * This,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const ULONG culServiceID,
            /* [in] */ const EMSTIME ctmTimeStamp,
            /* [in] */ const EMSCOMPONENTSTATUS eStatus,
            /* [string][in] */ const wchar_t *cwszServiceDescr,
            /* [string][in] */ const wchar_t *cwszError);
        
        HRESULT ( STDMETHODCALLTYPE *BroadcastAntennaDetails )( 
            IEMSStatusBroadcaster * This,
            /* [in] */ const ULONG culAntennaID,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const EMSTIME ctmTimeStamp,
            /* [in] */ const EMSANTENNA_STATE ceState,
            /* [in] */ const float cfAzimuth,
            /* [in] */ const float cfElevation);
        
        END_INTERFACE
    } IEMSStatusBroadcasterVtbl;

    interface IEMSStatusBroadcaster
    {
        CONST_VTBL struct IEMSStatusBroadcasterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSStatusBroadcaster_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSStatusBroadcaster_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSStatusBroadcaster_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSStatusBroadcaster_BroadcastStatus(This,culLutID,culServiceID,ctmTimeStamp,eStatus,cwszServiceDescr,cwszError)	\
    ( (This)->lpVtbl -> BroadcastStatus(This,culLutID,culServiceID,ctmTimeStamp,eStatus,cwszServiceDescr,cwszError) ) 

#define IEMSStatusBroadcaster_BroadcastAntennaDetails(This,culAntennaID,culSatID,ctmTimeStamp,ceState,cfAzimuth,cfElevation)	\
    ( (This)->lpVtbl -> BroadcastAntennaDetails(This,culAntennaID,culSatID,ctmTimeStamp,ceState,cfAzimuth,cfElevation) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSStatusBroadcaster_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_StatusBroadcaster_0000_0001 */
/* [local] */ 

#endif //INC_STATUS_BROADCASTER


extern RPC_IF_HANDLE __MIDL_itf_StatusBroadcaster_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_StatusBroadcaster_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


