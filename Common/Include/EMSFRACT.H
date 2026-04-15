/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 13 17:06:14 2004
 */
/* Compiler settings for C:\Dev\Common\Include\EMSFRACT.IDL:
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

#ifndef __emsfract_h__
#define __emsfract_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSFract_FWD_DEFINED__
#define __IEMSFract_FWD_DEFINED__
typedef interface IEMSFract IEMSFract;
#endif 	/* __IEMSFract_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSFRACT_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {68CD0786-9FF4-4700-A32E-A6620D847D3A} 
DEFINE_GUID( CLSID_EMSFract, 0x68cd0786, 0x9ff4, 0x4700, 0xa3, 0x2e, 0xa6, 0x62, 0xd, 0x84, 0x7d, 0x3a); 
 
// {177EA9A8-CEB8-4dbb-B1C9-23197F4E0625} 
DEFINE_GUID( IID_IEMSFract, 0x177ea9a8, 0xceb8, 0x4dbb, 0xb1, 0xc9, 0x23, 0x19, 0x7f, 0x4e, 0x6, 0x25); 
 

extern RPC_IF_HANDLE __MIDL_itf_EMSFRACT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSFRACT_0000_v0_0_s_ifspec;

#ifndef __IEMSFract_INTERFACE_DEFINED__
#define __IEMSFract_INTERFACE_DEFINED__

/* interface IEMSFract */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSREFRACTION
    {
    __int64 time;
    double dFreq;
    EMSCOORDD satCoord;
    double dRange;
    double dRangeAdj;
    double dRangeRate;
    double dRangeRateAdj;
    EMSAZEL azEl;
    }	EMSREFRACTION;

typedef struct _tagEMSREFRACTION __RPC_FAR *LPEMSREFRACTION;


EXTERN_C const IID IID_IEMSFract;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("177EA9A8-CEB8-4dbb-B1C9-23197F4E0625")
    IEMSFract : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadIonosphericConstants( 
            /* [in] */ EMSTIME ionoTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CalcRRateWithRefractionAdjustments( 
            /* [in] */ const LPEMSLOCATION lpLocation,
            /* [in] */ EMSCOORDSYSTEM satCoordSystem,
            /* [size_is][out][in] */ LPEMSREFRACTION lpRefraction,
            /* [in] */ ULONG ulCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Calculate( 
            /* [in] */ const LPEMSLOCATION lpLocation,
            /* [in] */ double dFrequency,
            /* [size_is][in] */ const LPEMSTIMECOORDD lpSatPV,
            /* [size_is][out] */ LPEMSRANGERATED lpRangeRate,
            /* [in] */ ULONG ulCount,
            /* [in] */ BOOLEAN bAddIonos) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSFractVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSFract __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSFract __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSFract __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadIonosphericConstants )( 
            IEMSFract __RPC_FAR * This,
            /* [in] */ EMSTIME ionoTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CalcRRateWithRefractionAdjustments )( 
            IEMSFract __RPC_FAR * This,
            /* [in] */ const LPEMSLOCATION lpLocation,
            /* [in] */ EMSCOORDSYSTEM satCoordSystem,
            /* [size_is][out][in] */ LPEMSREFRACTION lpRefraction,
            /* [in] */ ULONG ulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Calculate )( 
            IEMSFract __RPC_FAR * This,
            /* [in] */ const LPEMSLOCATION lpLocation,
            /* [in] */ double dFrequency,
            /* [size_is][in] */ const LPEMSTIMECOORDD lpSatPV,
            /* [size_is][out] */ LPEMSRANGERATED lpRangeRate,
            /* [in] */ ULONG ulCount,
            /* [in] */ BOOLEAN bAddIonos);
        
        END_INTERFACE
    } IEMSFractVtbl;

    interface IEMSFract
    {
        CONST_VTBL struct IEMSFractVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSFract_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSFract_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSFract_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSFract_LoadIonosphericConstants(This,ionoTime)	\
    (This)->lpVtbl -> LoadIonosphericConstants(This,ionoTime)

#define IEMSFract_CalcRRateWithRefractionAdjustments(This,lpLocation,satCoordSystem,lpRefraction,ulCount)	\
    (This)->lpVtbl -> CalcRRateWithRefractionAdjustments(This,lpLocation,satCoordSystem,lpRefraction,ulCount)

#define IEMSFract_Calculate(This,lpLocation,dFrequency,lpSatPV,lpRangeRate,ulCount,bAddIonos)	\
    (This)->lpVtbl -> Calculate(This,lpLocation,dFrequency,lpSatPV,lpRangeRate,ulCount,bAddIonos)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSFract_LoadIonosphericConstants_Proxy( 
    IEMSFract __RPC_FAR * This,
    /* [in] */ EMSTIME ionoTime);


void __RPC_STUB IEMSFract_LoadIonosphericConstants_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSFract_CalcRRateWithRefractionAdjustments_Proxy( 
    IEMSFract __RPC_FAR * This,
    /* [in] */ const LPEMSLOCATION lpLocation,
    /* [in] */ EMSCOORDSYSTEM satCoordSystem,
    /* [size_is][out][in] */ LPEMSREFRACTION lpRefraction,
    /* [in] */ ULONG ulCount);


void __RPC_STUB IEMSFract_CalcRRateWithRefractionAdjustments_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSFract_Calculate_Proxy( 
    IEMSFract __RPC_FAR * This,
    /* [in] */ const LPEMSLOCATION lpLocation,
    /* [in] */ double dFrequency,
    /* [size_is][in] */ const LPEMSTIMECOORDD lpSatPV,
    /* [size_is][out] */ LPEMSRANGERATED lpRangeRate,
    /* [in] */ ULONG ulCount,
    /* [in] */ BOOLEAN bAddIonos);


void __RPC_STUB IEMSFract_Calculate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSFract_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSFRACT_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSFract __RPC_FAR *LPEMSFract;



extern RPC_IF_HANDLE __MIDL_itf_EMSFRACT_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSFRACT_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
