

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0628 */
/* at Mon Jan 18 22:14:07 2038
 */
/* Compiler settings for ..\Common\Include\DataTransmitter.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0628 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __DataTransmitter_h__
#define __DataTransmitter_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#ifndef DECLSPEC_XFGVIRT
#if defined(_CONTROL_FLOW_GUARD_XFG)
#define DECLSPEC_XFGVIRT(base, func) __declspec(xfg_virtual(base, func))
#else
#define DECLSPEC_XFGVIRT(base, func)
#endif
#endif

/* Forward Declarations */ 

#ifndef __IEMSDataTransmitter_FWD_DEFINED__
#define __IEMSDataTransmitter_FWD_DEFINED__
typedef interface IEMSDataTransmitter IEMSDataTransmitter;

#endif 	/* __IEMSDataTransmitter_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_DataTransmitter_0000_0000 */
/* [local] */ 

// {3F29435D-64E3-4ef3-A759-138F984B85F1}
DEFINE_GUID(IID_IEMSDataTransmitter, 0x3f29435d, 0x64e3, 0x4ef3, 0xa7, 0x59, 0x13, 0x8f, 0x98, 0x4b, 0x85, 0xf1);


extern RPC_IF_HANDLE __MIDL_itf_DataTransmitter_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DataTransmitter_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSDataTransmitter_INTERFACE_DEFINED__
#define __IEMSDataTransmitter_INTERFACE_DEFINED__

/* interface IEMSDataTransmitter */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDataTransmitter;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3F29435D-64E3-4ef3-A759-138F984B85F1")
    IEMSDataTransmitter : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [string][in] */ const wchar_t *cwszConnectInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ const int ciLen,
            /* [size_is][in] */ const BYTE *cabyData,
            /* [out][in] */ int *piSent) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEMSDataTransmitterVtbl
    {
        BEGIN_INTERFACE
        
        DECLSPEC_XFGVIRT(IUnknown, QueryInterface)
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSDataTransmitter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        DECLSPEC_XFGVIRT(IUnknown, AddRef)
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSDataTransmitter * This);
        
        DECLSPEC_XFGVIRT(IUnknown, Release)
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSDataTransmitter * This);
        
        DECLSPEC_XFGVIRT(IEMSDataTransmitter, Connect)
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IEMSDataTransmitter * This,
            /* [string][in] */ const wchar_t *cwszConnectInfo);
        
        DECLSPEC_XFGVIRT(IEMSDataTransmitter, Disconnect)
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IEMSDataTransmitter * This);
        
        DECLSPEC_XFGVIRT(IEMSDataTransmitter, Send)
        HRESULT ( STDMETHODCALLTYPE *Send )( 
            IEMSDataTransmitter * This,
            /* [in] */ const int ciLen,
            /* [size_is][in] */ const BYTE *cabyData,
            /* [out][in] */ int *piSent);
        
        END_INTERFACE
    } IEMSDataTransmitterVtbl;

    interface IEMSDataTransmitter
    {
        CONST_VTBL struct IEMSDataTransmitterVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataTransmitter_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSDataTransmitter_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSDataTransmitter_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSDataTransmitter_Connect(This,cwszConnectInfo)	\
    ( (This)->lpVtbl -> Connect(This,cwszConnectInfo) ) 

#define IEMSDataTransmitter_Disconnect(This)	\
    ( (This)->lpVtbl -> Disconnect(This) ) 

#define IEMSDataTransmitter_Send(This,ciLen,cabyData,piSent)	\
    ( (This)->lpVtbl -> Send(This,ciLen,cabyData,piSent) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSDataTransmitter_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


