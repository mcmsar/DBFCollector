/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 05 16:36:33 2003
 */
/* Compiler settings for statodet.idl:
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

#ifndef __statodet_h__
#define __statodet_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSOrbitDetermineStatus_FWD_DEFINED__
#define __IEMSOrbitDetermineStatus_FWD_DEFINED__
typedef interface IEMSOrbitDetermineStatus IEMSOrbitDetermineStatus;
#endif 	/* __IEMSOrbitDetermineStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_statodet_0000 */
/* [local] */ 

// {ABFAD672-F182-11d5-8D38-009027912866}
DEFINE_GUID( IID_IEMSOrbitDetermineStatus, 0xabfad672, 0xf182, 0x11d5, 0x8d, 0x38, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 


extern RPC_IF_HANDLE __MIDL_itf_statodet_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statodet_0000_v0_0_s_ifspec;

#ifndef __IEMSOrbitDetermineStatus_INTERFACE_DEFINED__
#define __IEMSOrbitDetermineStatus_INTERFACE_DEFINED__

/* interface IEMSOrbitDetermineStatus */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSORBITDETERMINESTATE
    {	EMS_ODS_Idle	= 0,
	EMS_ODS_Initialized	= 1,
	EMS_ODS_Processing	= 2,
	EMS_ODS_EndOfPass	= 3,
	EMS_ODS_WaitingToProcess	= 4
    }	EMSORBITDETERMINESTATE;


#pragma pack(1)
typedef struct  _tagEMSORBITDETERMINEINFO
    {
    WORD wStatus;
    EMSORBITDETERMINESTATE state;
    ULONG ulSatID;
    ULONG ulBufferedRecords;
    ULONG ulTrackRecords;
    }	EMSORBITDETERMINEINFO;

typedef struct _tagEMSORBITDETERMINEINFO __RPC_FAR *LPEMSORBITDETERMINEINFO;

typedef /* [v1_enum] */ 
enum _tagEMSORBITUPDATESTATUS
    {	EMS_ORBUPD_Unknown	= 0,
	EMS_ORBUPD_Updated	= 1,
	EMS_ORBUPD_TooFewData	= 2,
	EMS_ORBUPD_Error	= 3
    }	EMSORBITUPDATESTATUS;

typedef struct  _tagEMSORBITDETERMINEINFOEX
    {
    WORD wStatus;
    WORD wNumDownlink;
    WORD wNumDownlinkUsed;
    WORD wNum406;
    WORD wNum406Used;
    float fMeanResidualInput;
    float fMeanResidualOutput;
    float fStdDevResidualInput;
    float fStdDevResidualOutput;
    float fPositionDifference;
    float fVelocityDifference;
    }	EMSORBITDETERMINEINFOEX;

typedef struct _tagEMSORBITDETERMINEINFOEX __RPC_FAR *LPEMSORBITDETERMINEINFOEX;


#pragma pack()

EXTERN_C const IID IID_IEMSOrbitDetermineStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ABFAD672-F182-11d5-8D38-009027912866")
    IEMSOrbitDetermineStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetOrbitDetermineInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOrbitDetermineInfo( 
            /* [in] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrbitDetermineInfo( 
            /* [out] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbitDetermineStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetOrbitDetermineInfo )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetOrbitDetermineInfo )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This,
            /* [in] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitDetermineInfo )( 
            IEMSOrbitDetermineStatus __RPC_FAR * This,
            /* [out] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSOrbitDetermineStatusVtbl;

    interface IEMSOrbitDetermineStatus
    {
        CONST_VTBL struct IEMSOrbitDetermineStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbitDetermineStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbitDetermineStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbitDetermineStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSOrbitDetermineStatus_ResetOrbitDetermineInfo(This)	\
    (This)->lpVtbl -> ResetOrbitDetermineInfo(This)

#define IEMSOrbitDetermineStatus_SetOrbitDetermineInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetOrbitDetermineInfo(This,lpInfo)

#define IEMSOrbitDetermineStatus_GetOrbitDetermineInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetOrbitDetermineInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbitDetermineStatus_ResetOrbitDetermineInfo_Proxy( 
    IEMSOrbitDetermineStatus __RPC_FAR * This);


void __RPC_STUB IEMSOrbitDetermineStatus_ResetOrbitDetermineInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbitDetermineStatus_SetOrbitDetermineInfo_Proxy( 
    IEMSOrbitDetermineStatus __RPC_FAR * This,
    /* [in] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSOrbitDetermineStatus_SetOrbitDetermineInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbitDetermineStatus_GetOrbitDetermineInfo_Proxy( 
    IEMSOrbitDetermineStatus __RPC_FAR * This,
    /* [out] */ EMSORBITDETERMINEINFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSOrbitDetermineStatus_GetOrbitDetermineInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbitDetermineStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statodet_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbitDetermineStatus __RPC_FAR *LPEMSORBITDETERMINESTATUS;



extern RPC_IF_HANDLE __MIDL_itf_statodet_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statodet_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
