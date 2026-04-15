/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 28 10:53:06 2008
 */
/* Compiler settings for ..\common\include\STATC406.IDL:
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

#ifndef __STATC406_h__
#define __STATC406_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCalibrate406Status_FWD_DEFINED__
#define __IEMSCalibrate406Status_FWD_DEFINED__
typedef interface IEMSCalibrate406Status IEMSCalibrate406Status;
#endif 	/* __IEMSCalibrate406Status_FWD_DEFINED__ */


#ifndef __IEMSCalibrate406Status2_FWD_DEFINED__
#define __IEMSCalibrate406Status2_FWD_DEFINED__
typedef interface IEMSCalibrate406Status2 IEMSCalibrate406Status2;
#endif 	/* __IEMSCalibrate406Status2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATC406_0000 */
/* [local] */ 

#ifndef INC_STATC406
#define INC_STATC406

// {ACB9B761-F181-11d5-8D38-009027912866}
DEFINE_GUID( IID_IEMSCalibrate406Status, 0xacb9b761, 0xf181, 0x11d5, 0x8d, 0x38, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {24EC971E-12F4-4abc-9BB7-744434D4478F}
DEFINE_GUID( IID_IEMSCalibrate406Status2, 0x24ec971e, 0x12f4, 0x4abc, 0x9b, 0xb7, 0x74, 0x44, 0x34, 0xd4, 0x47, 0x8f);
 


extern RPC_IF_HANDLE __MIDL_itf_STATC406_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATC406_0000_v0_0_s_ifspec;

#ifndef __IEMSCalibrate406Status_INTERFACE_DEFINED__
#define __IEMSCalibrate406Status_INTERFACE_DEFINED__

/* interface IEMSCalibrate406Status */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSCALIB406STATE
    {	EMS_C406S_Idle	= 0,
	EMS_C406S_Initialized	= 1,
	EMS_C406S_Processing	= 2
    }	EMSCALIB406STATE;


#pragma pack(1)
typedef struct  _tagEMSCALIBRATE406INFO
    {
    WORD wStatus;
    EMSCALIB406STATE state;
    ULONG ulSatID;
    ULONG ulBufferedRecords;
    ULONG ulHistoryRecords;
    ULONG ulCalibratedRecords;
    }	EMSCALIBRATE406INFO;

typedef struct _tagEMSCALIBRATE406INFO __RPC_FAR *LPEMSCALIBRATE406INFO;

typedef struct  _tagEMSCALIBRATE406INFOEX
    {
    WORD wStatus;
    ULONG ulBufferedRecords;
    ULONG ulHistoryRecords;
    ULONG ulCalibratedRecords;
    ULONG ulNumBeacons;
    ULONG ulNumRefBeaconRecords;
    ULONG ulSarrRecords;
    ULONG ulSarpRecords;
    }	EMSCALIBRATE406INFOEX;

typedef struct _tagEMSCALIBRATE406INFOEX __RPC_FAR *LPEMSCALIBRATE406INFOEX;


#pragma pack()

EXTERN_C const IID IID_IEMSCalibrate406Status;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACB9B761-F181-11d5-8D38-009027912866")
    IEMSCalibrate406Status : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetCalibrate406Info( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCalibrate406Info( 
            /* [in] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCalibrate406Info( 
            /* [out] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCalibrate406StatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCalibrate406Status __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCalibrate406Status __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCalibrate406Status __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCalibrate406Info )( 
            IEMSCalibrate406Status __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCalibrate406Info )( 
            IEMSCalibrate406Status __RPC_FAR * This,
            /* [in] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalibrate406Info )( 
            IEMSCalibrate406Status __RPC_FAR * This,
            /* [out] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCalibrate406StatusVtbl;

    interface IEMSCalibrate406Status
    {
        CONST_VTBL struct IEMSCalibrate406StatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCalibrate406Status_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCalibrate406Status_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCalibrate406Status_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCalibrate406Status_ResetCalibrate406Info(This)	\
    (This)->lpVtbl -> ResetCalibrate406Info(This)

#define IEMSCalibrate406Status_SetCalibrate406Info(This,lpInfo)	\
    (This)->lpVtbl -> SetCalibrate406Info(This,lpInfo)

#define IEMSCalibrate406Status_GetCalibrate406Info(This,lpInfo)	\
    (This)->lpVtbl -> GetCalibrate406Info(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCalibrate406Status_ResetCalibrate406Info_Proxy( 
    IEMSCalibrate406Status __RPC_FAR * This);


void __RPC_STUB IEMSCalibrate406Status_ResetCalibrate406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCalibrate406Status_SetCalibrate406Info_Proxy( 
    IEMSCalibrate406Status __RPC_FAR * This,
    /* [in] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrate406Status_SetCalibrate406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCalibrate406Status_GetCalibrate406Info_Proxy( 
    IEMSCalibrate406Status __RPC_FAR * This,
    /* [out] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrate406Status_GetCalibrate406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCalibrate406Status_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATC406_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSCalibrate406Status __RPC_FAR *LPEMSCALIBRATE406STATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATC406_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATC406_0015_v0_0_s_ifspec;

#ifndef __IEMSCalibrate406Status2_INTERFACE_DEFINED__
#define __IEMSCalibrate406Status2_INTERFACE_DEFINED__

/* interface IEMSCalibrate406Status2 */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSCALIBRATE406INFOEX2
    {
    EMSCALIBRATE406INFOEX infoEx;
    EMSTIME timeMsgSARPCalibNewest;
    EMSTIME timeMsgSARPCalibOldest;
    }	EMSCALIBRATE406INFOEX2;

typedef struct _tagEMSCALIBRATE406INFOEX2 __RPC_FAR *LPEMSCALIBRATE406INFOEX2;


#pragma pack()

EXTERN_C const IID IID_IEMSCalibrate406Status2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("24EC971E-12F4-4abc-9BB7-744434D4478F")
    IEMSCalibrate406Status2 : public IEMSCalibrate406Status
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCalibrate406Info2( 
            /* [in] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCalibrate406Info2( 
            /* [out] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCalibrate406Status2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCalibrate406Status2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCalibrate406Status2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCalibrate406Status2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCalibrate406Info )( 
            IEMSCalibrate406Status2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCalibrate406Info )( 
            IEMSCalibrate406Status2 __RPC_FAR * This,
            /* [in] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalibrate406Info )( 
            IEMSCalibrate406Status2 __RPC_FAR * This,
            /* [out] */ EMSCALIBRATE406INFOEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCalibrate406Info2 )( 
            IEMSCalibrate406Status2 __RPC_FAR * This,
            /* [in] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalibrate406Info2 )( 
            IEMSCalibrate406Status2 __RPC_FAR * This,
            /* [out] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCalibrate406Status2Vtbl;

    interface IEMSCalibrate406Status2
    {
        CONST_VTBL struct IEMSCalibrate406Status2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCalibrate406Status2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCalibrate406Status2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCalibrate406Status2_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCalibrate406Status2_ResetCalibrate406Info(This)	\
    (This)->lpVtbl -> ResetCalibrate406Info(This)

#define IEMSCalibrate406Status2_SetCalibrate406Info(This,lpInfo)	\
    (This)->lpVtbl -> SetCalibrate406Info(This,lpInfo)

#define IEMSCalibrate406Status2_GetCalibrate406Info(This,lpInfo)	\
    (This)->lpVtbl -> GetCalibrate406Info(This,lpInfo)


#define IEMSCalibrate406Status2_SetCalibrate406Info2(This,lpInfo)	\
    (This)->lpVtbl -> SetCalibrate406Info2(This,lpInfo)

#define IEMSCalibrate406Status2_GetCalibrate406Info2(This,lpInfo)	\
    (This)->lpVtbl -> GetCalibrate406Info2(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCalibrate406Status2_SetCalibrate406Info2_Proxy( 
    IEMSCalibrate406Status2 __RPC_FAR * This,
    /* [in] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrate406Status2_SetCalibrate406Info2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCalibrate406Status2_GetCalibrate406Info2_Proxy( 
    IEMSCalibrate406Status2 __RPC_FAR * This,
    /* [out] */ EMSCALIBRATE406INFOEX2 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrate406Status2_GetCalibrate406Info2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCalibrate406Status2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATC406_0016 */
/* [local] */ 

typedef /* [unique] */ IEMSCalibrate406Status2 __RPC_FAR *LPEMSCALIBRATE406STATUS2;


#endif


extern RPC_IF_HANDLE __MIDL_itf_STATC406_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATC406_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
