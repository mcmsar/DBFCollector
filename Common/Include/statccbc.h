/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 05 17:17:50 2003
 */
/* Compiler settings for statccbc.idl:
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

#ifndef __statccbc_h__
#define __statccbc_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCalibrateCBCStatus_FWD_DEFINED__
#define __IEMSCalibrateCBCStatus_FWD_DEFINED__
typedef interface IEMSCalibrateCBCStatus IEMSCalibrateCBCStatus;
#endif 	/* __IEMSCalibrateCBCStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_statccbc_0000 */
/* [local] */ 

// {ACB9B762-F181-11d5-8D38-009027912866}
DEFINE_GUID( IID_IEMSCalibrateCBCStatus, 0xacb9b762, 0xf181, 0x11d5, 0x8d, 0x38, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 


extern RPC_IF_HANDLE __MIDL_itf_statccbc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statccbc_0000_v0_0_s_ifspec;

#ifndef __IEMSCalibrateCBCStatus_INTERFACE_DEFINED__
#define __IEMSCalibrateCBCStatus_INTERFACE_DEFINED__

/* interface IEMSCalibrateCBCStatus */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSCALIBCBCSTATE
    {	EMS_CCBCS_Idle	= 0,
	EMS_CCBCS_Initialized	= 1,
	EMS_CCBCS_Processing	= 2
    }	EMSCALIBCBCSTATE;


#pragma pack(1)
typedef struct  _tagEMSCALIBRATECBCINFO
    {
    WORD wStatus;
    ULONG ulBufferedRecords;
    ULONG ulCalibratedRecords;
    ULONG ulNumBeacons;
    }	EMSCALIBRATECBCINFO;

typedef struct _tagEMSCALIBRATECBCINFO __RPC_FAR *LPEMSCALIBRATECBCINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSCalibrateCBCStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACB9B762-F181-11d5-8D38-009027912866")
    IEMSCalibrateCBCStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetCalibrateCBCInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCalibrateCBCInfo( 
            /* [in] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCalibrateCBCInfo( 
            /* [out] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCalibrateCBCStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCalibrateCBCInfo )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCalibrateCBCInfo )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This,
            /* [in] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCalibrateCBCInfo )( 
            IEMSCalibrateCBCStatus __RPC_FAR * This,
            /* [out] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCalibrateCBCStatusVtbl;

    interface IEMSCalibrateCBCStatus
    {
        CONST_VTBL struct IEMSCalibrateCBCStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCalibrateCBCStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCalibrateCBCStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCalibrateCBCStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCalibrateCBCStatus_ResetCalibrateCBCInfo(This)	\
    (This)->lpVtbl -> ResetCalibrateCBCInfo(This)

#define IEMSCalibrateCBCStatus_SetCalibrateCBCInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetCalibrateCBCInfo(This,lpInfo)

#define IEMSCalibrateCBCStatus_GetCalibrateCBCInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetCalibrateCBCInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCalibrateCBCStatus_ResetCalibrateCBCInfo_Proxy( 
    IEMSCalibrateCBCStatus __RPC_FAR * This);


void __RPC_STUB IEMSCalibrateCBCStatus_ResetCalibrateCBCInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCalibrateCBCStatus_SetCalibrateCBCInfo_Proxy( 
    IEMSCalibrateCBCStatus __RPC_FAR * This,
    /* [in] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrateCBCStatus_SetCalibrateCBCInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCalibrateCBCStatus_GetCalibrateCBCInfo_Proxy( 
    IEMSCalibrateCBCStatus __RPC_FAR * This,
    /* [out] */ EMSCALIBRATECBCINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCalibrateCBCStatus_GetCalibrateCBCInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCalibrateCBCStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statccbc_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSCalibrateCBCStatus __RPC_FAR *LPEMSCALIBRATECBCSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_statccbc_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statccbc_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
