/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 30 17:31:00 2003
 */
/* Compiler settings for stattcal.idl:
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

#ifndef __stattcal_h__
#define __stattcal_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSTCalStatus_FWD_DEFINED__
#define __IEMSTCalStatus_FWD_DEFINED__
typedef interface IEMSTCalStatus IEMSTCalStatus;
#endif 	/* __IEMSTCalStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_stattcal_0000 */
/* [local] */ 

// {378E6C3F-FC1C-4c4e-8687-C057082032F2}
DEFINE_GUID( IID_IEMSTCalStatus, 0x378e6c3f, 0xfc1c, 0x4c4e, 0x86, 0x87, 0xc0, 0x57, 0x8, 0x20, 0x32, 0xf2);


extern RPC_IF_HANDLE __MIDL_itf_stattcal_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_stattcal_0000_v0_0_s_ifspec;

#ifndef __IEMSTCalStatus_INTERFACE_DEFINED__
#define __IEMSTCalStatus_INTERFACE_DEFINED__

/* interface IEMSTCalStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef /* [v1_enum] */ 
enum _tagEMSTCALSTATE
    {	EMS_TCAL_Idle	= 0,
	EMS_TCAL_Initialized	= 1,
	EMS_TCAL_Processing	= 2,
	EMS_TCAL_EndOfPass	= 3,
	EMS_TCAL_WaitingToProcess	= 4
    }	EMSTCALSTATE;

typedef /* [v1_enum] */ 
enum _tagEMSTCALUPDATESTATUS
    {	EMS_TCALUPD_Unknown	= 0,
	EMS_TCALUPD_Updated	= 1,
	EMS_TCALUPD_TooFewData	= 2,
	EMS_TCALUPD_Error	= 3
    }	EMSTCALUPDATESTATUS;

typedef struct  _tagEMSTCALINFO
    {
    WORD wStatus;
    ULONG ulSatID;
    ULONG ulTCALNumber;
    WORD wType;
    EMSTIME timeRollover;
    float fFreqCorrection;
    ULONG ulNumMsg;
    ULONG ulNumMsgUsed;
    float fResidualMean;
    float fResidualStdDev;
    float fResidualMax;
    float fRolloverError;
    float fFreqCorrectionError;
    float fCorrelationCoef;
    double dUSOFrequency;
    double dRolloverPropogationError;
    }	EMSTCALINFO;

typedef struct _tagEMSTCALINFO __RPC_FAR *LPEMSTCALINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSTCalStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("378E6C3F-FC1C-4c4e-8687-C057082032F2")
    IEMSTCalStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetTCalInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTCalInfo( 
            /* [in] */ EMSTCALINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTCalInfo( 
            /* [out] */ EMSTCALINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTCalStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTCalStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTCalStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTCalStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetTCalInfo )( 
            IEMSTCalStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTCalInfo )( 
            IEMSTCalStatus __RPC_FAR * This,
            /* [in] */ EMSTCALINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTCalInfo )( 
            IEMSTCalStatus __RPC_FAR * This,
            /* [out] */ EMSTCALINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSTCalStatusVtbl;

    interface IEMSTCalStatus
    {
        CONST_VTBL struct IEMSTCalStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTCalStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTCalStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTCalStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSTCalStatus_ResetTCalInfo(This)	\
    (This)->lpVtbl -> ResetTCalInfo(This)

#define IEMSTCalStatus_SetTCalInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetTCalInfo(This,lpInfo)

#define IEMSTCalStatus_GetTCalInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetTCalInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTCalStatus_ResetTCalInfo_Proxy( 
    IEMSTCalStatus __RPC_FAR * This);


void __RPC_STUB IEMSTCalStatus_ResetTCalInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTCalStatus_SetTCalInfo_Proxy( 
    IEMSTCalStatus __RPC_FAR * This,
    /* [in] */ EMSTCALINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSTCalStatus_SetTCalInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTCalStatus_GetTCalInfo_Proxy( 
    IEMSTCalStatus __RPC_FAR * This,
    /* [out] */ EMSTCALINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSTCalStatus_GetTCalInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTCalStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_stattcal_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSTCalStatus __RPC_FAR *LPEMSTCALSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_stattcal_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_stattcal_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
