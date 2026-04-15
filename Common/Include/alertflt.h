/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 03 17:56:51 2010
 */
/* Compiler settings for C:\dev\LUT600\Common\Include\ALERTFLT.IDL:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef __ALERTFLT_h__
#define __ALERTFLT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAlertFilter_FWD_DEFINED__
#define __IEMSAlertFilter_FWD_DEFINED__
typedef interface IEMSAlertFilter IEMSAlertFilter;
#endif 	/* __IEMSAlertFilter_FWD_DEFINED__ */


#ifndef __IEMSAlertFilter2_FWD_DEFINED__
#define __IEMSAlertFilter2_FWD_DEFINED__
typedef interface IEMSAlertFilter2 IEMSAlertFilter2;
#endif 	/* __IEMSAlertFilter2_FWD_DEFINED__ */


#ifndef __IEMSAlertFilter3_FWD_DEFINED__
#define __IEMSAlertFilter3_FWD_DEFINED__
typedef interface IEMSAlertFilter3 IEMSAlertFilter3;
#endif 	/* __IEMSAlertFilter3_FWD_DEFINED__ */


#ifndef __IEMSAlertFilter4_FWD_DEFINED__
#define __IEMSAlertFilter4_FWD_DEFINED__
typedef interface IEMSAlertFilter4 IEMSAlertFilter4;
#endif 	/* __IEMSAlertFilter4_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "locate.h"
#include "abldata.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ALERTFLT_0000 */
/* [local] */ 

/********************************************************************
*	Module:			alertflt.h
*	Description: 	Alert Filtering Interface
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

#ifndef INC_ALERTFLT
#define INC_ALERTFLT

 
#include "emserror.h"
 
// {6177BD13-EA0F-4655-8CAC-EBE760C11160}
DEFINE_GUID( CLSID_EMSAlertFilter, 0x6177bd13, 0xea0f, 0x4655, 0x8c, 0xac, 0xeb, 0xe7, 0x60, 0xc1, 0x11, 0x60);
// {AAC69CB3-2A4D-4fc6-BF96-DBFB8048B8CC}
DEFINE_GUID( IID_IEMSAlertFilter, 0xaac69cb3, 0x2a4d, 0x4fc6, 0xbf, 0x96, 0xdb, 0xfb, 0x80, 0x48, 0xb8, 0xcc);
 
// {AD9F839C-274A-4966-90EC-553CE05AAD29}
DEFINE_GUID( IID_IEMSAlertFilter2, 0xad9f839c, 0x274a, 0x4966, 0x90, 0xec, 0x55, 0x3c, 0xe0, 0x5a, 0xad, 0x29);
// {1ECAFE5E-E5C1-41a6-B4F1-9BFFF5404A11}
DEFINE_GUID( IID_IEMSAlertFilter3, 0x1ecafe5e, 0xe5c1, 0x41a6, 0xb4, 0xf1, 0x9b, 0xff, 0xf5, 0x40, 0x4a, 0x11);
// {1415F6F0-9147-4d94-8A6D-2D82AD8F4931}
DEFINE_GUID( IID_IEMSAlertFilter4, 0x1415f6f0, 0x9147, 0x4d94, 0x8a, 0x6d, 0x2d, 0x82, 0xad, 0x8f, 0x49, 0x31);
 
#ifdef UNICODE
#define CheckAlertFilter     CheckAlertFilterW
#else
#define CheckAlertFilter     CheckAlertFilterA
#endif // UNICODE
 


extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0000_v0_0_s_ifspec;

#ifndef __IEMSAlertFilter_INTERFACE_DEFINED__
#define __IEMSAlertFilter_INTERFACE_DEFINED__

/* interface IEMSAlertFilter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertFilter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AAC69CB3-2A4D-4fc6-BF96-DBFB8048B8CC")
    IEMSAlertFilter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckAlertFilterA( 
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CheckAlertFilterW( 
            EMSLOCATE __RPC_FAR *lpLocate,
            WCHAR __RPC_FAR *lpcszDest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertFilterVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertFilter __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertFilter __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSAlertFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSAlertFilter __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterA )( 
            IEMSAlertFilter __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterW )( 
            IEMSAlertFilter __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            WCHAR __RPC_FAR *lpcszDest);
        
        END_INTERFACE
    } IEMSAlertFilterVtbl;

    interface IEMSAlertFilter
    {
        CONST_VTBL struct IEMSAlertFilterVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertFilter_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertFilter_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertFilter_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertFilter_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IEMSAlertFilter_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSAlertFilter_CheckAlertFilterA(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterA(This,lpLocate,lpcszDest)

#define IEMSAlertFilter_CheckAlertFilterW(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterW(This,lpLocate,lpcszDest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertFilter_Initialize_Proxy( 
    IEMSAlertFilter __RPC_FAR * This);


void __RPC_STUB IEMSAlertFilter_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlertFilter_Reset_Proxy( 
    IEMSAlertFilter __RPC_FAR * This);


void __RPC_STUB IEMSAlertFilter_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlertFilter_CheckAlertFilterA_Proxy( 
    IEMSAlertFilter __RPC_FAR * This,
    EMSLOCATE __RPC_FAR *lpLocate,
    unsigned char __RPC_FAR *lpcszDest);


void __RPC_STUB IEMSAlertFilter_CheckAlertFilterA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlertFilter_CheckAlertFilterW_Proxy( 
    IEMSAlertFilter __RPC_FAR * This,
    EMSLOCATE __RPC_FAR *lpLocate,
    WCHAR __RPC_FAR *lpcszDest);


void __RPC_STUB IEMSAlertFilter_CheckAlertFilterW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertFilter_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ALERTFLT_0019 */
/* [local] */ 

typedef /* [unique] */ IEMSAlertFilter __RPC_FAR *LPEMSALERTFILTER;



extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0019_v0_0_s_ifspec;

#ifndef __IEMSAlertFilter2_INTERFACE_DEFINED__
#define __IEMSAlertFilter2_INTERFACE_DEFINED__

/* interface IEMSAlertFilter2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertFilter2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("AD9F839C-274A-4966-90EC-553CE05AAD29")
    IEMSAlertFilter2 : public IEMSAlertFilter
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAlertFilterResult( 
            HRESULT __RPC_FAR *lphrReason) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertFilter2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertFilter2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertFilter2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertFilter2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSAlertFilter2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSAlertFilter2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterA )( 
            IEMSAlertFilter2 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterW )( 
            IEMSAlertFilter2 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            WCHAR __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlertFilterResult )( 
            IEMSAlertFilter2 __RPC_FAR * This,
            HRESULT __RPC_FAR *lphrReason);
        
        END_INTERFACE
    } IEMSAlertFilter2Vtbl;

    interface IEMSAlertFilter2
    {
        CONST_VTBL struct IEMSAlertFilter2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertFilter2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertFilter2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertFilter2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertFilter2_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IEMSAlertFilter2_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSAlertFilter2_CheckAlertFilterA(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterA(This,lpLocate,lpcszDest)

#define IEMSAlertFilter2_CheckAlertFilterW(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterW(This,lpLocate,lpcszDest)


#define IEMSAlertFilter2_GetAlertFilterResult(This,lphrReason)	\
    (This)->lpVtbl -> GetAlertFilterResult(This,lphrReason)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertFilter2_GetAlertFilterResult_Proxy( 
    IEMSAlertFilter2 __RPC_FAR * This,
    HRESULT __RPC_FAR *lphrReason);


void __RPC_STUB IEMSAlertFilter2_GetAlertFilterResult_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertFilter2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ALERTFLT_0020 */
/* [local] */ 

typedef /* [unique] */ IEMSAlertFilter2 __RPC_FAR *LPEMSALERTFILTER2;



extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0020_v0_0_s_ifspec;

#ifndef __IEMSAlertFilter3_INTERFACE_DEFINED__
#define __IEMSAlertFilter3_INTERFACE_DEFINED__

/* interface IEMSAlertFilter3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertFilter3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1ECAFE5E-E5C1-41a6-B4F1-9BFFF5404A11")
    IEMSAlertFilter3 : public IEMSAlertFilter2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckABLAlertFilter( 
            /* [in] */ const EMSABLData cAlert,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszDest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertFilter3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertFilter3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertFilter3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertFilter3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSAlertFilter3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSAlertFilter3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterA )( 
            IEMSAlertFilter3 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterW )( 
            IEMSAlertFilter3 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            WCHAR __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlertFilterResult )( 
            IEMSAlertFilter3 __RPC_FAR * This,
            HRESULT __RPC_FAR *lphrReason);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckABLAlertFilter )( 
            IEMSAlertFilter3 __RPC_FAR * This,
            /* [in] */ const EMSABLData cAlert,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszDest);
        
        END_INTERFACE
    } IEMSAlertFilter3Vtbl;

    interface IEMSAlertFilter3
    {
        CONST_VTBL struct IEMSAlertFilter3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertFilter3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertFilter3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertFilter3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertFilter3_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IEMSAlertFilter3_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSAlertFilter3_CheckAlertFilterA(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterA(This,lpLocate,lpcszDest)

#define IEMSAlertFilter3_CheckAlertFilterW(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterW(This,lpLocate,lpcszDest)


#define IEMSAlertFilter3_GetAlertFilterResult(This,lphrReason)	\
    (This)->lpVtbl -> GetAlertFilterResult(This,lphrReason)


#define IEMSAlertFilter3_CheckABLAlertFilter(This,cAlert,cwszDest)	\
    (This)->lpVtbl -> CheckABLAlertFilter(This,cAlert,cwszDest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertFilter3_CheckABLAlertFilter_Proxy( 
    IEMSAlertFilter3 __RPC_FAR * This,
    /* [in] */ const EMSABLData cAlert,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszDest);


void __RPC_STUB IEMSAlertFilter3_CheckABLAlertFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertFilter3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ALERTFLT_0021 */
/* [local] */ 

typedef /* [unique] */ IEMSAlertFilter3 __RPC_FAR *LPEMSALERTFILTER3;



extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0021_v0_0_s_ifspec;

#ifndef __IEMSAlertFilter4_INTERFACE_DEFINED__
#define __IEMSAlertFilter4_INTERFACE_DEFINED__

/* interface IEMSAlertFilter4 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertFilter4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1415F6F0-9147-4d94-8A6D-2D82AD8F4931")
    IEMSAlertFilter4 : public IEMSAlertFilter3
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckFixedBitsAlertFilter( 
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertFilter4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertFilter4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertFilter4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSAlertFilter4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSAlertFilter4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterA )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckAlertFilterW )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            WCHAR __RPC_FAR *lpcszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlertFilterResult )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            HRESULT __RPC_FAR *lphrReason);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckABLAlertFilter )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            /* [in] */ const EMSABLData cAlert,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszDest);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckFixedBitsAlertFilter )( 
            IEMSAlertFilter4 __RPC_FAR * This,
            EMSLOCATE __RPC_FAR *lpLocate,
            unsigned char __RPC_FAR *lpcszDest);
        
        END_INTERFACE
    } IEMSAlertFilter4Vtbl;

    interface IEMSAlertFilter4
    {
        CONST_VTBL struct IEMSAlertFilter4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertFilter4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertFilter4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertFilter4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertFilter4_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IEMSAlertFilter4_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSAlertFilter4_CheckAlertFilterA(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterA(This,lpLocate,lpcszDest)

#define IEMSAlertFilter4_CheckAlertFilterW(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckAlertFilterW(This,lpLocate,lpcszDest)


#define IEMSAlertFilter4_GetAlertFilterResult(This,lphrReason)	\
    (This)->lpVtbl -> GetAlertFilterResult(This,lphrReason)


#define IEMSAlertFilter4_CheckABLAlertFilter(This,cAlert,cwszDest)	\
    (This)->lpVtbl -> CheckABLAlertFilter(This,cAlert,cwszDest)


#define IEMSAlertFilter4_CheckFixedBitsAlertFilter(This,lpLocate,lpcszDest)	\
    (This)->lpVtbl -> CheckFixedBitsAlertFilter(This,lpLocate,lpcszDest)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertFilter4_CheckFixedBitsAlertFilter_Proxy( 
    IEMSAlertFilter4 __RPC_FAR * This,
    EMSLOCATE __RPC_FAR *lpLocate,
    unsigned char __RPC_FAR *lpcszDest);


void __RPC_STUB IEMSAlertFilter4_CheckFixedBitsAlertFilter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertFilter4_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ALERTFLT_0022 */
/* [local] */ 

typedef /* [unique] */ IEMSAlertFilter4 __RPC_FAR *LPEMSALERTFILTER4;

#endif //INC_ALERTFLT


extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0022_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALERTFLT_0022_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
