/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 31 12:14:49 2006
 */
/* Compiler settings for statsarr.idl:
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

#ifndef __statsarr_h__
#define __statsarr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSarrCalibStatus_FWD_DEFINED__
#define __IEMSSarrCalibStatus_FWD_DEFINED__
typedef interface IEMSSarrCalibStatus IEMSSarrCalibStatus;
#endif 	/* __IEMSSarrCalibStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_statsarr_0000 */
/* [local] */ 

// {C2DA85DC-E6A9-4ae3-881F-E1DA7F90974F}
DEFINE_GUID( IID_IEMSSarrCalibStatus, 0xc2da85dc, 0xe6a9, 0x4ae3, 0x88, 0x1f, 0xe1, 0xda, 0x7f, 0x90, 0x97, 0x4f);


extern RPC_IF_HANDLE __MIDL_itf_statsarr_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statsarr_0000_v0_0_s_ifspec;

#ifndef __IEMSSarrCalibStatus_INTERFACE_DEFINED__
#define __IEMSSarrCalibStatus_INTERFACE_DEFINED__

/* interface IEMSSarrCalibStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef /* [v1_enum] */ 
enum _tagEMSSARRCALIBSTATE
    {	EMS_SARRCALIB_Idle	= 0,
	EMS_SARRCALIB_Initialized	= 1,
	EMS_SARRCALIB_Processing	= 2,
	EMS_SARRCALIB_EndOfPass	= 3,
	EMS_SARRCALIB_WaitingToProcess	= 4
    }	EMSSARRCALIBSTATE;

typedef /* [v1_enum] */ 
enum _tagEMSSARRCALIBUPDATESTATUS
    {	EMS_SARRCALIBUPD_Unknown	= 0,
	EMS_SARRCALIBUPD_Updated	= 1,
	EMS_SARRCALIBUPD_TooFewData	= 2,
	EMS_SARRCALIBUPD_Error	= 3
    }	EMSSARRCALIBUPDATESTATUS;

typedef struct  _tagEMSSARRCALIBINFO
    {
    WORD wStatus;
    ULONG ulSatID;
    ULONG ulSARRCALIBNumber;
    WORD wType;
    float fFreqOffset;
    float fFreqDrift;
    INT64 i64TimeOffset;
    ULONG ulNumMsg;
    ULONG ulNumMsgUsed;
    float fFreqResidualMean;
    float fFreqResidualStdDev;
    float fFreqResidualMax;
    float fTimeResidualMean;
    float fTimeResidualStdDev;
    float fTimeResidualMax;
    }	EMSSARRCALIBINFO;

typedef struct _tagEMSSARRCALIBINFO __RPC_FAR *LPEMSSARRCALIBINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSSarrCalibStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C2DA85DC-E6A9-4ae3-881F-E1DA7F90974F")
    IEMSSarrCalibStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetSarrCalibInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarrCalibInfo( 
            /* [in] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarrCalibInfo( 
            /* [out] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSarrCalibStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSarrCalibStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSarrCalibStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSarrCalibStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetSarrCalibInfo )( 
            IEMSSarrCalibStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSarrCalibInfo )( 
            IEMSSarrCalibStatus __RPC_FAR * This,
            /* [in] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSarrCalibInfo )( 
            IEMSSarrCalibStatus __RPC_FAR * This,
            /* [out] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSSarrCalibStatusVtbl;

    interface IEMSSarrCalibStatus
    {
        CONST_VTBL struct IEMSSarrCalibStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSarrCalibStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSarrCalibStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSarrCalibStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSSarrCalibStatus_ResetSarrCalibInfo(This)	\
    (This)->lpVtbl -> ResetSarrCalibInfo(This)

#define IEMSSarrCalibStatus_SetSarrCalibInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetSarrCalibInfo(This,lpInfo)

#define IEMSSarrCalibStatus_GetSarrCalibInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetSarrCalibInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSarrCalibStatus_ResetSarrCalibInfo_Proxy( 
    IEMSSarrCalibStatus __RPC_FAR * This);


void __RPC_STUB IEMSSarrCalibStatus_ResetSarrCalibInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSarrCalibStatus_SetSarrCalibInfo_Proxy( 
    IEMSSarrCalibStatus __RPC_FAR * This,
    /* [in] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSarrCalibStatus_SetSarrCalibInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSarrCalibStatus_GetSarrCalibInfo_Proxy( 
    IEMSSarrCalibStatus __RPC_FAR * This,
    /* [out] */ EMSSARRCALIBINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSarrCalibStatus_GetSarrCalibInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSarrCalibStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statsarr_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSSarrCalibStatus __RPC_FAR *LPEMSSARRCALIBSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_statsarr_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statsarr_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
