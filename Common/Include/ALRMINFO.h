
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Tue Nov 26 23:06:43 2002
 */
/* Compiler settings for D:\Devsar\leo600\siteinfo\ALRMINFO.IDL:
    Os (OptLev=s), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
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

#ifndef __ALRMINFO_h__
#define __ALRMINFO_h__

/* Forward Declarations */ 

#ifndef __IEMSAlarmSuppressionInfo_FWD_DEFINED__
#define __IEMSAlarmSuppressionInfo_FWD_DEFINED__
typedef interface IEMSAlarmSuppressionInfo IEMSAlarmSuppressionInfo;
#endif 	/* __IEMSAlarmSuppressionInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ALRMINFO_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {B0292FF7-F151-48a0-AD23-40ABBDD2652A}
DEFINE_GUID( IID_IEMSAlarmSuppressionInfo, 0xb0292ff7, 0xf151, 0x48a0, 0xad, 0x23, 0x40, 0xab, 0xbd, 0xd2, 0x65, 0x2a);


extern RPC_IF_HANDLE __MIDL_itf_ALRMINFO_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALRMINFO_0000_v0_0_s_ifspec;

#ifndef __IEMSAlarmSuppressionInfo_INTERFACE_DEFINED__
#define __IEMSAlarmSuppressionInfo_INTERFACE_DEFINED__

/* interface IEMSAlarmSuppressionInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlarmSuppressionInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B0292FF7-F151-48a0-AD23-40ABBDD2652A")
    IEMSAlarmSuppressionInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAlarmCodesForDestination( 
            /* [in] */ int nDest,
            /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrAlarmCodes,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWarningCodesForDestination( 
            /* [in] */ int nDest,
            /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrWarningCodes,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlarmSuppressionInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlarmSuppressionInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlarmSuppressionInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlarmSuppressionInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlarmCodesForDestination )( 
            IEMSAlarmSuppressionInfo __RPC_FAR * This,
            /* [in] */ int nDest,
            /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrAlarmCodes,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWarningCodesForDestination )( 
            IEMSAlarmSuppressionInfo __RPC_FAR * This,
            /* [in] */ int nDest,
            /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrWarningCodes,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        END_INTERFACE
    } IEMSAlarmSuppressionInfoVtbl;

    interface IEMSAlarmSuppressionInfo
    {
        CONST_VTBL struct IEMSAlarmSuppressionInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlarmSuppressionInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlarmSuppressionInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlarmSuppressionInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlarmSuppressionInfo_GetAlarmCodesForDestination(This,nDest,lphrAlarmCodes,ulMax,ulActual)	\
    (This)->lpVtbl -> GetAlarmCodesForDestination(This,nDest,lphrAlarmCodes,ulMax,ulActual)

#define IEMSAlarmSuppressionInfo_GetWarningCodesForDestination(This,nDest,lphrWarningCodes,ulMax,ulActual)	\
    (This)->lpVtbl -> GetWarningCodesForDestination(This,nDest,lphrWarningCodes,ulMax,ulActual)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlarmSuppressionInfo_GetAlarmCodesForDestination_Proxy( 
    IEMSAlarmSuppressionInfo __RPC_FAR * This,
    /* [in] */ int nDest,
    /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrAlarmCodes,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSAlarmSuppressionInfo_GetAlarmCodesForDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlarmSuppressionInfo_GetWarningCodesForDestination_Proxy( 
    IEMSAlarmSuppressionInfo __RPC_FAR * This,
    /* [in] */ int nDest,
    /* [length_is][size_is][out] */ HRESULT __RPC_FAR *lphrWarningCodes,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSAlarmSuppressionInfo_GetWarningCodesForDestination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlarmSuppressionInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ALRMINFO_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSAlarmSuppressionInfo __RPC_FAR *LPEMSALARMSUPPRESSIONINFO;



extern RPC_IF_HANDLE __MIDL_itf_ALRMINFO_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ALRMINFO_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


