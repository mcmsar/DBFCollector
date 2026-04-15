
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Fri Mar 12 10:03:59 2004
 */
/* Compiler settings for C:\dev\common\Include\EMSSATX.IDL:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __EMSSATX_h__
#define __EMSSATX_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSSatelliteInfoEx_FWD_DEFINED__
#define __IEMSSatelliteInfoEx_FWD_DEFINED__
typedef interface IEMSSatelliteInfoEx IEMSSatelliteInfoEx;
#endif 	/* __IEMSSatelliteInfoEx_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_EMSSATX_0000 */
/* [local] */ 

/********************************************************************
*	Module:			emssatx.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	IEMSSatelliteInfoEx
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	02/01/18		rvw	start

********************************************************************/
#ifndef INC_EMSSATX
#define INC_EMSSATX
// {55869DCE-8C75-4c09-AFAB-B5358EACC31F}
DEFINE_GUID( IID_IEMSSatelliteInfoEx, 0x55869dce, 0x8c75, 0x4c09, 0xaf, 0xab, 0xb5, 0x35, 0x8e, 0xac, 0xc3, 0x1f);
 


extern RPC_IF_HANDLE __MIDL_itf_EMSSATX_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSATX_0000_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfoEx_INTERFACE_DEFINED__
#define __IEMSSatelliteInfoEx_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfoEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSatelliteInfoEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("55869DCE-8C75-4c09-AFAB-B5358EACC31F")
    IEMSSatelliteInfoEx : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteOrbitTolerance( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ double *lpdWarnPos,
            /* [out] */ double *lpdWarnVelocity,
            /* [out] */ double *lpdMaxPos,
            /* [out] */ double *lpdMaxVelocity) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteWeightFactor( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ double *lpdWeightFactor) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfoExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfoEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfoEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfoEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteOrbitTolerance )( 
            IEMSSatelliteInfoEx * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ double *lpdWarnPos,
            /* [out] */ double *lpdWarnVelocity,
            /* [out] */ double *lpdMaxPos,
            /* [out] */ double *lpdMaxVelocity);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteWeightFactor )( 
            IEMSSatelliteInfoEx * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ double *lpdWeightFactor);
        
        END_INTERFACE
    } IEMSSatelliteInfoExVtbl;

    interface IEMSSatelliteInfoEx
    {
        CONST_VTBL struct IEMSSatelliteInfoExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfoEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSatelliteInfoEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSatelliteInfoEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSatelliteInfoEx_GetSatelliteOrbitTolerance(This,ulSatID,lpdWarnPos,lpdWarnVelocity,lpdMaxPos,lpdMaxVelocity)	\
    (This)->lpVtbl -> GetSatelliteOrbitTolerance(This,ulSatID,lpdWarnPos,lpdWarnVelocity,lpdMaxPos,lpdMaxVelocity)

#define IEMSSatelliteInfoEx_GetSatelliteWeightFactor(This,ulSatID,lpdWeightFactor)	\
    (This)->lpVtbl -> GetSatelliteWeightFactor(This,ulSatID,lpdWeightFactor)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSatelliteInfoEx_GetSatelliteOrbitTolerance_Proxy( 
    IEMSSatelliteInfoEx * This,
    /* [in] */ ULONG ulSatID,
    /* [out] */ double *lpdWarnPos,
    /* [out] */ double *lpdWarnVelocity,
    /* [out] */ double *lpdMaxPos,
    /* [out] */ double *lpdMaxVelocity);


void __RPC_STUB IEMSSatelliteInfoEx_GetSatelliteOrbitTolerance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSatelliteInfoEx_GetSatelliteWeightFactor_Proxy( 
    IEMSSatelliteInfoEx * This,
    /* [in] */ ULONG ulSatID,
    /* [out] */ double *lpdWeightFactor);


void __RPC_STUB IEMSSatelliteInfoEx_GetSatelliteWeightFactor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSatelliteInfoEx_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSSATX_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfoEx *LPEMSSATELLITEINFOEX;

#endif //INC_EMSSATX


extern RPC_IF_HANDLE __MIDL_itf_EMSSATX_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSATX_0015_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


