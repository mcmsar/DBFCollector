

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Apr 24 16:24:20 2026
 */
/* Compiler settings for ..\Common\Include\DataTransmitter.idl:
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

#ifndef __DataTransmitter_h__
#define __DataTransmitter_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSDataTransmitter * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSDataTransmitter * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSDataTransmitter * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IEMSDataTransmitter * This,
            /* [string][in] */ const wchar_t *cwszConnectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IEMSDataTransmitter * This);
        
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


