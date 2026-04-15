/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 30 16:34:07 2004
 */
/* Compiler settings for emstleserver.idl:
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

#ifndef __emstleserver_h__
#define __emstleserver_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSTLEServer_FWD_DEFINED__
#define __IEMSTLEServer_FWD_DEFINED__
typedef interface IEMSTLEServer IEMSTLEServer;
#endif 	/* __IEMSTLEServer_FWD_DEFINED__ */


#ifndef __IEMSTLEServer2_FWD_DEFINED__
#define __IEMSTLEServer2_FWD_DEFINED__
typedef interface IEMSTLEServer2 IEMSTLEServer2;
#endif 	/* __IEMSTLEServer2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emsorbit.h"
#include "dal.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emstleserver_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {39CF31B4-C4FB-40bf-BBD5-29511D007E3C} 
DEFINE_GUID( CLSID_EMSTLEServer, 0x39cf31b4, 0xc4fb, 0x40bf, 0xbb, 0xd5, 0x29, 0x51, 0x1d, 0x0, 0x7e, 0x3c); 
 
// {BAD6DDEA-88AB-4899-88E9-9B7BABB726C0} 
DEFINE_GUID( IID_IEMSTLEServer, 0xbad6ddea, 0x88ab, 0x4899, 0x88, 0xe9, 0x9b, 0x7b, 0xab, 0xb7, 0x26, 0xc0); 
 
// {3D9B8751-CA7E-11d8-8E69-009027912866}
DEFINE_GUID( IID_IEMSTLEServer2, 0x3d9b8751, 0xca7e, 0x11d8, 0x8e, 0x69, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// Settings for ulFlags 
//
#define EMSTLEServerFlag_AllowDefault         (0x1)  /* Supply Default TLE */
 
extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0000_v0_0_s_ifspec;

#ifndef __IEMSTLEServer_INTERFACE_DEFINED__
#define __IEMSTLEServer_INTERFACE_DEFINED__

/* interface IEMSTLEServer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSTLEServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BAD6DDEA-88AB-4899-88E9-9B7BABB726C0")
    IEMSTLEServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBestSatTLE( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatID,
            /* [in] */ EMSTIME eTime,
            /* [out] */ LPEMSTLEDATA lpTLEData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCacheTLE( 
            /* [in] */ LPEMSTLERECORD lpTLERecs,
            int nTLERecs) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTLEServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTLEServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTLEServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTLEServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBestSatTLE )( 
            IEMSTLEServer __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatID,
            /* [in] */ EMSTIME eTime,
            /* [out] */ LPEMSTLEDATA lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCacheTLE )( 
            IEMSTLEServer __RPC_FAR * This,
            /* [in] */ LPEMSTLERECORD lpTLERecs,
            int nTLERecs);
        
        END_INTERFACE
    } IEMSTLEServerVtbl;

    interface IEMSTLEServer
    {
        CONST_VTBL struct IEMSTLEServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTLEServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTLEServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTLEServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTLEServer_GetBestSatTLE(This,ulLutID,ulSatID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetBestSatTLE(This,ulLutID,ulSatID,eTime,lpTLEData)

#define IEMSTLEServer_SetCacheTLE(This,lpTLERecs,nTLERecs)	\
    (This)->lpVtbl -> SetCacheTLE(This,lpTLERecs,nTLERecs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTLEServer_GetBestSatTLE_Proxy( 
    IEMSTLEServer __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ ULONG ulSatID,
    /* [in] */ EMSTIME eTime,
    /* [out] */ LPEMSTLEDATA lpTLEData);


void __RPC_STUB IEMSTLEServer_GetBestSatTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer_SetCacheTLE_Proxy( 
    IEMSTLEServer __RPC_FAR * This,
    /* [in] */ LPEMSTLERECORD lpTLERecs,
    int nTLERecs);


void __RPC_STUB IEMSTLEServer_SetCacheTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTLEServer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emstleserver_0196 */
/* [local] */ 

typedef /* [unique] */ IEMSTLEServer __RPC_FAR *LPEMSTLEServer;



extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0196_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0196_v0_0_s_ifspec;

#ifndef __IEMSTLEServer2_INTERFACE_DEFINED__
#define __IEMSTLEServer2_INTERFACE_DEFINED__

/* interface IEMSTLEServer2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSTLEServer2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3D9B8751-CA7E-11d8-8E69-009027912866")
    IEMSTLEServer2 : public IEMSTLEServer
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ ULONG ulMaxTLEs,
            /* [in] */ ULONG ulFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetCacheTLEs( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LoadCacheTLEs( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatID,
            /* [in] */ EMSTIME timeStart,
            /* [in] */ EMSTIME timeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCacheTLECount( 
            /* [out] */ ULONG __RPC_FAR *lpulCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCacheTLERecord( 
            /* [out] */ LPEMSTLERECORD lpTLERecord,
            /* [in] */ ULONG ulIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCacheTLEData( 
            /* [out] */ LPEMSTLEDATA lpTLEData,
            /* [in] */ ULONG ulIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTLEServer2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTLEServer2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTLEServer2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBestSatTLE )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatID,
            /* [in] */ EMSTIME eTime,
            /* [out] */ LPEMSTLEDATA lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCacheTLE )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [in] */ LPEMSTLERECORD lpTLERecs,
            int nTLERecs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [in] */ ULONG ulMaxTLEs,
            /* [in] */ ULONG ulFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSTLEServer2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCacheTLEs )( 
            IEMSTLEServer2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadCacheTLEs )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatID,
            /* [in] */ EMSTIME timeStart,
            /* [in] */ EMSTIME timeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCacheTLECount )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCacheTLERecord )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [out] */ LPEMSTLERECORD lpTLERecord,
            /* [in] */ ULONG ulIndex);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCacheTLEData )( 
            IEMSTLEServer2 __RPC_FAR * This,
            /* [out] */ LPEMSTLEDATA lpTLEData,
            /* [in] */ ULONG ulIndex);
        
        END_INTERFACE
    } IEMSTLEServer2Vtbl;

    interface IEMSTLEServer2
    {
        CONST_VTBL struct IEMSTLEServer2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTLEServer2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTLEServer2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTLEServer2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTLEServer2_GetBestSatTLE(This,ulLutID,ulSatID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetBestSatTLE(This,ulLutID,ulSatID,eTime,lpTLEData)

#define IEMSTLEServer2_SetCacheTLE(This,lpTLERecs,nTLERecs)	\
    (This)->lpVtbl -> SetCacheTLE(This,lpTLERecs,nTLERecs)


#define IEMSTLEServer2_Initialize(This,ulMaxTLEs,ulFlags)	\
    (This)->lpVtbl -> Initialize(This,ulMaxTLEs,ulFlags)

#define IEMSTLEServer2_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSTLEServer2_ResetCacheTLEs(This)	\
    (This)->lpVtbl -> ResetCacheTLEs(This)

#define IEMSTLEServer2_LoadCacheTLEs(This,ulLutID,ulSatID,timeStart,timeEnd)	\
    (This)->lpVtbl -> LoadCacheTLEs(This,ulLutID,ulSatID,timeStart,timeEnd)

#define IEMSTLEServer2_GetCacheTLECount(This,lpulCount)	\
    (This)->lpVtbl -> GetCacheTLECount(This,lpulCount)

#define IEMSTLEServer2_GetCacheTLERecord(This,lpTLERecord,ulIndex)	\
    (This)->lpVtbl -> GetCacheTLERecord(This,lpTLERecord,ulIndex)

#define IEMSTLEServer2_GetCacheTLEData(This,lpTLEData,ulIndex)	\
    (This)->lpVtbl -> GetCacheTLEData(This,lpTLEData,ulIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTLEServer2_Initialize_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This,
    /* [in] */ ULONG ulMaxTLEs,
    /* [in] */ ULONG ulFlags);


void __RPC_STUB IEMSTLEServer2_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_Reset_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This);


void __RPC_STUB IEMSTLEServer2_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_ResetCacheTLEs_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This);


void __RPC_STUB IEMSTLEServer2_ResetCacheTLEs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_LoadCacheTLEs_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ ULONG ulSatID,
    /* [in] */ EMSTIME timeStart,
    /* [in] */ EMSTIME timeEnd);


void __RPC_STUB IEMSTLEServer2_LoadCacheTLEs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_GetCacheTLECount_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulCount);


void __RPC_STUB IEMSTLEServer2_GetCacheTLECount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_GetCacheTLERecord_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This,
    /* [out] */ LPEMSTLERECORD lpTLERecord,
    /* [in] */ ULONG ulIndex);


void __RPC_STUB IEMSTLEServer2_GetCacheTLERecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTLEServer2_GetCacheTLEData_Proxy( 
    IEMSTLEServer2 __RPC_FAR * This,
    /* [out] */ LPEMSTLEDATA lpTLEData,
    /* [in] */ ULONG ulIndex);


void __RPC_STUB IEMSTLEServer2_GetCacheTLEData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTLEServer2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emstleserver_0197 */
/* [local] */ 

typedef /* [unique] */ IEMSTLEServer2 __RPC_FAR *LPEMSTLESERVER2;



extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0197_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstleserver_0197_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
