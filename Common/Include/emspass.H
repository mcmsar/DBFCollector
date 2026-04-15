/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jan 22 18:30:40 2007
 */
/* Compiler settings for ..\Common\Include\EMSPASS.IDL:
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

#ifndef __EMSPASS_h__
#define __EMSPASS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSPassSchedule_FWD_DEFINED__
#define __IEMSPassSchedule_FWD_DEFINED__
typedef interface IEMSPassSchedule IEMSPassSchedule;
#endif 	/* __IEMSPassSchedule_FWD_DEFINED__ */


#ifndef __IEMSPassSchedule2_FWD_DEFINED__
#define __IEMSPassSchedule2_FWD_DEFINED__
typedef interface IEMSPassSchedule2 IEMSPassSchedule2;
#endif 	/* __IEMSPassSchedule2_FWD_DEFINED__ */


#ifndef __IEMSPassSchedule3_FWD_DEFINED__
#define __IEMSPassSchedule3_FWD_DEFINED__
typedef interface IEMSPassSchedule3 IEMSPassSchedule3;
#endif 	/* __IEMSPassSchedule3_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSPASS_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {999808E2-4C47-11d5-8BB5-009027912866} 
DEFINE_GUID( CLSID_EMSPassSchedule, 0x999808e2, 0x4c47, 0x11d5, 0x8b, 0xb5, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66); 
 
// {999808E3-4C47-11d5-8BB5-009027912866} 
DEFINE_GUID( IID_IEMSPassSchedule, 0x999808e3, 0x4c47, 0x11d5, 0x8b, 0xb5, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66); 
 
// {1D81BE81-3B9F-11d7-9D3F-000021FAA228}
DEFINE_GUID( IID_IEMSPassSchedule2, 0x1d81be81, 0x3b9f, 0x11d7, 0x9d, 0x3f, 0x0, 0x0, 0x21, 0xfa, 0xa2, 0x28);
 
// {A5E4261A-D9B8-4ff0-A1B1-E45DB22070C9}
DEFINE_GUID( IID_IEMSPassSchedule3, 0xa5e4261a, 0xd9b8, 0x4ff0, 0xa1, 0xb1, 0xe4, 0x5d, 0xb2, 0x20, 0x70, 0xc9);
 
//
//Definitions for Flags
//
// mask & 0x00F = status
//
#define EMS_PASSFLAG_STATUS_MASK	(0x00F)
#define EMS_PASSFLAG_SUPPRESS		(0x001)
#define EMS_PASSFLAG_SKIP 			EMS_PASSFLAG_SUPPRESS
#define EMS_PASSFLAG_PROCESS		(0x002)
#define EMS_PASSFLAG_REDUNDANT	(0x004)
//
// mask & 0x0F0 = origin
//
#define EMS_PASSFLAG_ORIGIN_MASK	(0x0F0)
#define EMS_PASSFLAG_LUT			(0x010)
#define EMS_PASSFLAG_MCC			(0x020)
#define EMS_PASSFLAG_RCC			(0x040)
#define EMS_PASSFLAG_OPERATOR		(0x080)
//
// mask & 0xF00 = disposition
//
#define EMS_PASSFLAG_RESULT_MASK	(0xF00)
#define EMS_PASSFLAG_SUCCESS		(0x100)
#define EMS_PASSFLAG_ABORT			(0x200)
#define EMS_PASSFLAG_ERROR			(0x400)
// Process Flags 
#define EMS_PASSFLAG_EXTPROCESSING	(0x0001) 
 


extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0000_v0_0_s_ifspec;

#ifndef __IEMSPassSchedule_INTERFACE_DEFINED__
#define __IEMSPassSchedule_INTERFACE_DEFINED__

/* interface IEMSPassSchedule */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSSATELLITEPASS
    {
    ULONG ulSatelliteID;
    ULONG ulFlags;
    ULONG ulOrbitNumber;
    EMSTIME timeAOS;
    EMSTIME timeLOS;
    EMSTIME timePeak;
    EMSDEGREES degMaxElevation;
    EMSDEGREES degMinElevation;
    EMSDEGREES degAzimuthAOS;
    EMSDEGREES degAzimuthLOS;
    }	EMSSATELLITEPASS;

typedef struct _tagEMSSATELLITEPASS __RPC_FAR *LPEMSSATELLITEPASS;


#pragma pack()

EXTERN_C const IID IID_IEMSPassSchedule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("999808E3-4C47-11d5-8BB5-009027912866")
    IEMSPassSchedule : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSatellites( 
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPrimaryLut( 
            /* [in] */ const ULONG ulLutID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GenerateSchedule( 
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSchedule( 
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSchedule( 
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassScheduleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSchedule __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSchedule __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatellites )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPrimaryLut )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ const ULONG ulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSchedule )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSchedule )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchedule )( 
            IEMSPassSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        END_INTERFACE
    } IEMSPassScheduleVtbl;

    interface IEMSPassSchedule
    {
        CONST_VTBL struct IEMSPassScheduleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSchedule_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSchedule_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSchedule_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassSchedule_SetSatellites(This,cbCount,pulSatID)	\
    (This)->lpVtbl -> SetSatellites(This,cbCount,pulSatID)

#define IEMSPassSchedule_SetPrimaryLut(This,ulLutID)	\
    (This)->lpVtbl -> SetPrimaryLut(This,ulLutID)

#define IEMSPassSchedule_GenerateSchedule(This,startTime,stopTime)	\
    (This)->lpVtbl -> GenerateSchedule(This,startTime,stopTime)

#define IEMSPassSchedule_SetSchedule(This,startTime,stopTime,pvPass,cbCount)	\
    (This)->lpVtbl -> SetSchedule(This,startTime,stopTime,pvPass,cbCount)

#define IEMSPassSchedule_GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSchedule_SetSatellites_Proxy( 
    IEMSPassSchedule __RPC_FAR * This,
    /* [in] */ ULONG cbCount,
    /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);


void __RPC_STUB IEMSPassSchedule_SetSatellites_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule_SetPrimaryLut_Proxy( 
    IEMSPassSchedule __RPC_FAR * This,
    /* [in] */ const ULONG ulLutID);


void __RPC_STUB IEMSPassSchedule_SetPrimaryLut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule_GenerateSchedule_Proxy( 
    IEMSPassSchedule __RPC_FAR * This,
    /* [in] */ const EMSTIME startTime,
    /* [in] */ const EMSTIME stopTime);


void __RPC_STUB IEMSPassSchedule_GenerateSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule_SetSchedule_Proxy( 
    IEMSPassSchedule __RPC_FAR * This,
    /* [in] */ const EMSTIME startTime,
    /* [in] */ const EMSTIME stopTime,
    /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
    /* [in] */ ULONG cbCount);


void __RPC_STUB IEMSPassSchedule_SetSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule_GetSchedule_Proxy( 
    IEMSPassSchedule __RPC_FAR * This,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
    /* [out] */ ULONG __RPC_FAR *pcbResult,
    /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
    /* [out] */ EMSTIME __RPC_FAR *lpStopTime);


void __RPC_STUB IEMSPassSchedule_GetSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSchedule_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSPASS_0011 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSchedule __RPC_FAR *LPEMSPASSSCHEDULE;



extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0011_v0_0_s_ifspec;

#ifndef __IEMSPassSchedule2_INTERFACE_DEFINED__
#define __IEMSPassSchedule2_INTERFACE_DEFINED__

/* interface IEMSPassSchedule2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSPassSchedule2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D81BE81-3B9F-11d7-9D3F-000021FAA228")
    IEMSPassSchedule2 : public IEMSPassSchedule
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetLocation( 
            /* [in] */ EMSLOCATION location) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSiteProfile( 
            /* [in] */ ULONG ulCount,
            /* [size_is][in] */ const EMSAZEL __RPC_FAR *lpProfile) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSchedule2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSchedule2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSchedule2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatellites )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPrimaryLut )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ const ULONG ulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSchedule )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSchedule )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchedule )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocation )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ EMSLOCATION location);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSiteProfile )( 
            IEMSPassSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG ulCount,
            /* [size_is][in] */ const EMSAZEL __RPC_FAR *lpProfile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSPassSchedule2 __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSPassSchedule2Vtbl;

    interface IEMSPassSchedule2
    {
        CONST_VTBL struct IEMSPassSchedule2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSchedule2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSchedule2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSchedule2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassSchedule2_SetSatellites(This,cbCount,pulSatID)	\
    (This)->lpVtbl -> SetSatellites(This,cbCount,pulSatID)

#define IEMSPassSchedule2_SetPrimaryLut(This,ulLutID)	\
    (This)->lpVtbl -> SetPrimaryLut(This,ulLutID)

#define IEMSPassSchedule2_GenerateSchedule(This,startTime,stopTime)	\
    (This)->lpVtbl -> GenerateSchedule(This,startTime,stopTime)

#define IEMSPassSchedule2_SetSchedule(This,startTime,stopTime,pvPass,cbCount)	\
    (This)->lpVtbl -> SetSchedule(This,startTime,stopTime,pvPass,cbCount)

#define IEMSPassSchedule2_GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)


#define IEMSPassSchedule2_SetLocation(This,location)	\
    (This)->lpVtbl -> SetLocation(This,location)

#define IEMSPassSchedule2_SetSiteProfile(This,ulCount,lpProfile)	\
    (This)->lpVtbl -> SetSiteProfile(This,ulCount,lpProfile)

#define IEMSPassSchedule2_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSchedule2_SetLocation_Proxy( 
    IEMSPassSchedule2 __RPC_FAR * This,
    /* [in] */ EMSLOCATION location);


void __RPC_STUB IEMSPassSchedule2_SetLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule2_SetSiteProfile_Proxy( 
    IEMSPassSchedule2 __RPC_FAR * This,
    /* [in] */ ULONG ulCount,
    /* [size_is][in] */ const EMSAZEL __RPC_FAR *lpProfile);


void __RPC_STUB IEMSPassSchedule2_SetSiteProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule2_Reset_Proxy( 
    IEMSPassSchedule2 __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedule2_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSchedule2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSPASS_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSchedule2 __RPC_FAR *LPEMSPASSSCHEDULE2;



extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0012_v0_0_s_ifspec;

#ifndef __IEMSPassSchedule3_INTERFACE_DEFINED__
#define __IEMSPassSchedule3_INTERFACE_DEFINED__

/* interface IEMSPassSchedule3 */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSSATPASSLIMITS
    {
    ULONG ulMinSatID;
    ULONG ulMaxSatID;
    double dMaxMinutes;
    }	EMSSATPASSLIMITS;

typedef struct _tagEMSSATPASSLIMITS __RPC_FAR *LPEMSSATPASSLIMITS;


#pragma pack()

EXTERN_C const IID IID_IEMSPassSchedule3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5E4261A-D9B8-4ff0-A1B1-E45DB22070C9")
    IEMSPassSchedule3 : public IEMSPassSchedule2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            DWORD __RPC_FAR *lpdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassLimits( 
            DWORD dwCount,
            EMSSATPASSLIMITS __RPC_FAR *lpLimits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassLimit( 
            DWORD dwMinSatID,
            DWORD dwMaxSatID,
            double dMinutes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSchedule3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSchedule3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSchedule3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatellites )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPrimaryLut )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ const ULONG ulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSchedule )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSchedule )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchedule )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocation )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ EMSLOCATION location);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSiteProfile )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            /* [in] */ ULONG ulCount,
            /* [size_is][in] */ const EMSAZEL __RPC_FAR *lpProfile);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSPassSchedule3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFlags )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassLimits )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            DWORD dwCount,
            EMSSATPASSLIMITS __RPC_FAR *lpLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassLimit )( 
            IEMSPassSchedule3 __RPC_FAR * This,
            DWORD dwMinSatID,
            DWORD dwMaxSatID,
            double dMinutes);
        
        END_INTERFACE
    } IEMSPassSchedule3Vtbl;

    interface IEMSPassSchedule3
    {
        CONST_VTBL struct IEMSPassSchedule3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSchedule3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSchedule3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSchedule3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassSchedule3_SetSatellites(This,cbCount,pulSatID)	\
    (This)->lpVtbl -> SetSatellites(This,cbCount,pulSatID)

#define IEMSPassSchedule3_SetPrimaryLut(This,ulLutID)	\
    (This)->lpVtbl -> SetPrimaryLut(This,ulLutID)

#define IEMSPassSchedule3_GenerateSchedule(This,startTime,stopTime)	\
    (This)->lpVtbl -> GenerateSchedule(This,startTime,stopTime)

#define IEMSPassSchedule3_SetSchedule(This,startTime,stopTime,pvPass,cbCount)	\
    (This)->lpVtbl -> SetSchedule(This,startTime,stopTime,pvPass,cbCount)

#define IEMSPassSchedule3_GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)


#define IEMSPassSchedule3_SetLocation(This,location)	\
    (This)->lpVtbl -> SetLocation(This,location)

#define IEMSPassSchedule3_SetSiteProfile(This,ulCount,lpProfile)	\
    (This)->lpVtbl -> SetSiteProfile(This,ulCount,lpProfile)

#define IEMSPassSchedule3_Reset(This)	\
    (This)->lpVtbl -> Reset(This)


#define IEMSPassSchedule3_SetFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,dwFlags)

#define IEMSPassSchedule3_GetFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,lpdwFlags)

#define IEMSPassSchedule3_SetPassLimits(This,dwCount,lpLimits)	\
    (This)->lpVtbl -> SetPassLimits(This,dwCount,lpLimits)

#define IEMSPassSchedule3_SetPassLimit(This,dwMinSatID,dwMaxSatID,dMinutes)	\
    (This)->lpVtbl -> SetPassLimit(This,dwMinSatID,dwMaxSatID,dMinutes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSchedule3_SetFlags_Proxy( 
    IEMSPassSchedule3 __RPC_FAR * This,
    DWORD dwFlags);


void __RPC_STUB IEMSPassSchedule3_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule3_GetFlags_Proxy( 
    IEMSPassSchedule3 __RPC_FAR * This,
    DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSPassSchedule3_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule3_SetPassLimits_Proxy( 
    IEMSPassSchedule3 __RPC_FAR * This,
    DWORD dwCount,
    EMSSATPASSLIMITS __RPC_FAR *lpLimits);


void __RPC_STUB IEMSPassSchedule3_SetPassLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSchedule3_SetPassLimit_Proxy( 
    IEMSPassSchedule3 __RPC_FAR * This,
    DWORD dwMinSatID,
    DWORD dwMaxSatID,
    double dMinutes);


void __RPC_STUB IEMSPassSchedule3_SetPassLimit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSchedule3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSPASS_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSchedule3 __RPC_FAR *LPEMSPASSSCHEDULE3;



extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSPASS_0013_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
