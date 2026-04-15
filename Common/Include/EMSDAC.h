/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 08 12:39:53 2005
 */
/* Compiler settings for ..\common\include\EMSDAC.idl:
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

#ifndef __EMSDAC_h__
#define __EMSDAC_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDACRecv_FWD_DEFINED__
#define __IEMSDACRecv_FWD_DEFINED__
typedef interface IEMSDACRecv IEMSDACRecv;
#endif 	/* __IEMSDACRecv_FWD_DEFINED__ */


#ifndef __IEMSDACRecv2_FWD_DEFINED__
#define __IEMSDACRecv2_FWD_DEFINED__
typedef interface IEMSDACRecv2 IEMSDACRecv2;
#endif 	/* __IEMSDACRecv2_FWD_DEFINED__ */


#ifndef __IEMSDACManager_FWD_DEFINED__
#define __IEMSDACManager_FWD_DEFINED__
typedef interface IEMSDACManager IEMSDACManager;
#endif 	/* __IEMSDACManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "EMSTYPEX.h"
#include "IGATEWAY.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSDAC_0000 */
/* [local] */ 

// {D631FF4D-42AE-4221-98CF-A3FCE380ADE8}
DEFINE_GUID( CLSID_EMSDAC, 0xd631ff4d, 0x42ae, 0x4221, 0x98, 0xcf, 0xa3, 0xfc, 0xe3, 0x80, 0xad, 0xe8 );
// {62774C8B-CF8B-482b-B7E8-C329FFD1F1CA}
DEFINE_GUID( IID_IEMSDACRecv, 0x62774c8b, 0xcf8b, 0x482b, 0xb7, 0xe8, 0xc3, 0x29, 0xff, 0xd1, 0xf1, 0xca );
// {7A61A4BA-B02F-4a1e-A6B2-55ACA368FA53}
DEFINE_GUID( IID_IEMSDACManager, 0x7a61a4ba, 0xb02f, 0x4a1e, 0xa6, 0xb2, 0x55, 0xac, 0xa3, 0x68, 0xfa, 0x53 );
// {6BAF9AAA-2C00-4d4e-843A-4683C317A630}
DEFINE_GUID( IID_IEMSDACRecv2, 0x6baf9aaa, 0x2c00, 0x4d4e, 0x84, 0x3a, 0x46, 0x83, 0xc3, 0x17, 0xa6, 0x30);


extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0000_v0_0_s_ifspec;

#ifndef __IEMSDACRecv_INTERFACE_DEFINED__
#define __IEMSDACRecv_INTERFACE_DEFINED__

/* interface IEMSDACRecv */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDACRecv;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("62774C8B-CF8B-482b-B7E8-C329FFD1F1CA")
    IEMSDACRecv : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnData( 
            /* [string][in] */ wchar_t __RPC_FAR *szFilePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnData2( 
            ULONG ulSourceID,
            /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR data[  ],
            ULONG ulNumRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDACRecvVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDACRecv __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDACRecv __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDACRecv __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnData )( 
            IEMSDACRecv __RPC_FAR * This,
            /* [string][in] */ wchar_t __RPC_FAR *szFilePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnData2 )( 
            IEMSDACRecv __RPC_FAR * This,
            ULONG ulSourceID,
            /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR data[  ],
            ULONG ulNumRecords);
        
        END_INTERFACE
    } IEMSDACRecvVtbl;

    interface IEMSDACRecv
    {
        CONST_VTBL struct IEMSDACRecvVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDACRecv_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDACRecv_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDACRecv_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDACRecv_OnData(This,szFilePath)	\
    (This)->lpVtbl -> OnData(This,szFilePath)

#define IEMSDACRecv_OnData2(This,ulSourceID,data,ulNumRecords)	\
    (This)->lpVtbl -> OnData2(This,ulSourceID,data,ulNumRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDACRecv_OnData_Proxy( 
    IEMSDACRecv __RPC_FAR * This,
    /* [string][in] */ wchar_t __RPC_FAR *szFilePath);


void __RPC_STUB IEMSDACRecv_OnData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDACRecv_OnData2_Proxy( 
    IEMSDACRecv __RPC_FAR * This,
    ULONG ulSourceID,
    /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR data[  ],
    ULONG ulNumRecords);


void __RPC_STUB IEMSDACRecv_OnData2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDACRecv_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDAC_0354 */
/* [local] */ 

typedef IEMSDACRecv __RPC_FAR *LPEMSDACRECV;



extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0354_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0354_v0_0_s_ifspec;

#ifndef __IEMSDACRecv2_INTERFACE_DEFINED__
#define __IEMSDACRecv2_INTERFACE_DEFINED__

/* interface IEMSDACRecv2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDACRecv2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6BAF9AAA-2C00-4d4e-843A-4683C317A630")
    IEMSDACRecv2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnData3( 
            ULONG ulSourceID,
            /* [size_is][in] */ EMSVARIANTRECORD2 __RPC_FAR data[  ],
            ULONG ulNumRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDACRecv2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDACRecv2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDACRecv2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDACRecv2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnData3 )( 
            IEMSDACRecv2 __RPC_FAR * This,
            ULONG ulSourceID,
            /* [size_is][in] */ EMSVARIANTRECORD2 __RPC_FAR data[  ],
            ULONG ulNumRecords);
        
        END_INTERFACE
    } IEMSDACRecv2Vtbl;

    interface IEMSDACRecv2
    {
        CONST_VTBL struct IEMSDACRecv2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDACRecv2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDACRecv2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDACRecv2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDACRecv2_OnData3(This,ulSourceID,data,ulNumRecords)	\
    (This)->lpVtbl -> OnData3(This,ulSourceID,data,ulNumRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDACRecv2_OnData3_Proxy( 
    IEMSDACRecv2 __RPC_FAR * This,
    ULONG ulSourceID,
    /* [size_is][in] */ EMSVARIANTRECORD2 __RPC_FAR data[  ],
    ULONG ulNumRecords);


void __RPC_STUB IEMSDACRecv2_OnData3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDACRecv2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDAC_0355 */
/* [local] */ 

typedef IEMSDACRecv2 __RPC_FAR *LPEMSDACRECV2;



extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0355_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0355_v0_0_s_ifspec;

#ifndef __IEMSDACManager_INTERFACE_DEFINED__
#define __IEMSDACManager_INTERFACE_DEFINED__

/* interface IEMSDACManager */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDACManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A61A4BA-B02F-4a1e-A6B2-55ACA368FA53")
    IEMSDACManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [size_is][in] */ ULONG __RPC_FAR ulLutIDs[  ],
            ULONG ulNumLuts,
            /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR ulDataSources[  ],
            ULONG ulNumSources,
            EMSTIME starttime,
            EMSTIME endtime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudio( 
            ULONG ulLutID,
            float fMinFreq,
            float fMaxFreq,
            EMSTIME starttime,
            EMSTIME endtime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDACManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDACManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDACManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDACManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSDACManager __RPC_FAR * This,
            /* [size_is][in] */ ULONG __RPC_FAR ulLutIDs[  ],
            ULONG ulNumLuts,
            /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR ulDataSources[  ],
            ULONG ulNumSources,
            EMSTIME starttime,
            EMSTIME endtime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudio )( 
            IEMSDACManager __RPC_FAR * This,
            ULONG ulLutID,
            float fMinFreq,
            float fMaxFreq,
            EMSTIME starttime,
            EMSTIME endtime);
        
        END_INTERFACE
    } IEMSDACManagerVtbl;

    interface IEMSDACManager
    {
        CONST_VTBL struct IEMSDACManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDACManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDACManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDACManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDACManager_GetData(This,ulLutIDs,ulNumLuts,ulDataSources,ulNumSources,starttime,endtime)	\
    (This)->lpVtbl -> GetData(This,ulLutIDs,ulNumLuts,ulDataSources,ulNumSources,starttime,endtime)

#define IEMSDACManager_GetAudio(This,ulLutID,fMinFreq,fMaxFreq,starttime,endtime)	\
    (This)->lpVtbl -> GetAudio(This,ulLutID,fMinFreq,fMaxFreq,starttime,endtime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDACManager_GetData_Proxy( 
    IEMSDACManager __RPC_FAR * This,
    /* [size_is][in] */ ULONG __RPC_FAR ulLutIDs[  ],
    ULONG ulNumLuts,
    /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR ulDataSources[  ],
    ULONG ulNumSources,
    EMSTIME starttime,
    EMSTIME endtime);


void __RPC_STUB IEMSDACManager_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDACManager_GetAudio_Proxy( 
    IEMSDACManager __RPC_FAR * This,
    ULONG ulLutID,
    float fMinFreq,
    float fMaxFreq,
    EMSTIME starttime,
    EMSTIME endtime);


void __RPC_STUB IEMSDACManager_GetAudio_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDACManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDAC_0356 */
/* [local] */ 

typedef IEMSDACManager __RPC_FAR *LPEMSDACMANAGER;



extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0356_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDAC_0356_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
