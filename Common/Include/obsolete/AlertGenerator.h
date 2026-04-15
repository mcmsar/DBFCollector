
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Oct 08 13:20:51 2003
 */
/* Compiler settings for ..\..\common\include\AlertGenerator.idl:
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

#ifndef __AlertGenerator_h__
#define __AlertGenerator_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSAlertGenerator_FWD_DEFINED__
#define __IEMSAlertGenerator_FWD_DEFINED__
typedef interface IEMSAlertGenerator IEMSAlertGenerator;
#endif 	/* __IEMSAlertGenerator_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_AlertGenerator_0000 */
/* [local] */ 

// {B87AF813-7459-43ea-819A-CE378F03F19A}
DEFINE_GUID(IID_IEMSAlertGenerator, 0xb87af813, 0x7459, 0x43ea, 0x81, 0x9a, 0xce, 0x37, 0x8f, 0x3, 0xf1, 0x9a);
// {5B2BA125-4D13-4f21-BD85-F5547326B251}
DEFINE_GUID(CLSID_EMSAlertGenerator, 0x5b2ba125, 0x4d13, 0x4f21, 0xbd, 0x85, 0xf5, 0x54, 0x73, 0x26, 0xb2, 0x51);
typedef struct tagEMSLocationKey
    {
    EMSTIME timestamp;
    unsigned short usType;
    } 	EMSLOCATIONKEY;



extern RPC_IF_HANDLE __MIDL_itf_AlertGenerator_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AlertGenerator_0000_v0_0_s_ifspec;

#ifndef __IEMSAlertGenerator_INTERFACE_DEFINED__
#define __IEMSAlertGenerator_INTERFACE_DEFINED__

/* interface IEMSAlertGenerator */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSAlertGenerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B87AF813-7459-43ea-819A-CE378F03F19A")
    IEMSAlertGenerator : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GenerateAlerts( 
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY *aLocations) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertGeneratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSAlertGenerator * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSAlertGenerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSAlertGenerator * This);
        
        HRESULT ( STDMETHODCALLTYPE *GenerateAlerts )( 
            IEMSAlertGenerator * This,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY *aLocations);
        
        END_INTERFACE
    } IEMSAlertGeneratorVtbl;

    interface IEMSAlertGenerator
    {
        CONST_VTBL struct IEMSAlertGeneratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertGenerator_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertGenerator_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertGenerator_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertGenerator_GenerateAlerts(This,ulLocations,aLocations)	\
    (This)->lpVtbl -> GenerateAlerts(This,ulLocations,aLocations)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertGenerator_GenerateAlerts_Proxy( 
    IEMSAlertGenerator * This,
    /* [in] */ unsigned long ulLocations,
    /* [size_is][in] */ EMSLOCATIONKEY *aLocations);


void __RPC_STUB IEMSAlertGenerator_GenerateAlerts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertGenerator_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


