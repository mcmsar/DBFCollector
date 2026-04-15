/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Feb 11 16:01:32 2008
 */
/* Compiler settings for emstrack.idl:
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

#ifndef __emstrack_h__
#define __emstrack_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSTrackSchedule_FWD_DEFINED__
#define __IEMSTrackSchedule_FWD_DEFINED__
typedef interface IEMSTrackSchedule IEMSTrackSchedule;
#endif 	/* __IEMSTrackSchedule_FWD_DEFINED__ */


#ifndef __IEMSTrackSchedule2_FWD_DEFINED__
#define __IEMSTrackSchedule2_FWD_DEFINED__
typedef interface IEMSTrackSchedule2 IEMSTrackSchedule2;
#endif 	/* __IEMSTrackSchedule2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emspass.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emstrack_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {91B43291-D5F2-11d5-8CD6-009027912866}
DEFINE_GUID( CLSID_EMSTrackSchedule, 0x91b43291, 0xd5f2, 0x11d5, 0x8c, 0xd6, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {91B43292-D5F2-11d5-8CD6-009027912866}
DEFINE_GUID( IID_IEMSTrackSchedule, 0x91b43292, 0xd5f2, 0x11d5, 0x8c, 0xd6, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {CE7DA97A-E3C4-41e7-806A-E7B01C7B5118}
DEFINE_GUID( IID_IEMSTrackSchedule2, 0xce7da97a, 0xe3c4, 0x41e7, 0x80, 0x6a, 0xe7, 0xb0, 0x1c, 0x7b, 0x51, 0x18);
 
// Maximum Number of Optimized Satellite Passes
#define EMS_MAX_NUM_OPT_SAT_PASSES (8192)
 


extern RPC_IF_HANDLE __MIDL_itf_emstrack_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstrack_0000_v0_0_s_ifspec;

#ifndef __IEMSTrackSchedule_INTERFACE_DEFINED__
#define __IEMSTrackSchedule_INTERFACE_DEFINED__

/* interface IEMSTrackSchedule */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSSATELLITETRACK
    {
    ULONG ulLutID;
    EMSSATELLITEPASS PassInfo;
    EMSTIME actualStartTime;
    EMSTIME actualEndTime;
    double dWeight;
    }	EMSSATELLITETRACK;

typedef struct _tagEMSSATELLITETRACK __RPC_FAR *LPEMSSATELLITETRACK;

typedef struct  _tagEMSSATTRACKRECORD
    {
    EMSTIME timeSched;
    WORD wSeq;
    WORD wCount;
    EMSSATELLITETRACK track;
    }	EMSSATTRACKRECORD;

typedef struct _tagEMSSATTRACKRECORD __RPC_FAR *LPEMSSATTRACKRECORD;


#pragma pack()

EXTERN_C const IID IID_IEMSTrackSchedule;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("253F24D7-11F4-4aee-BF13-89836E28598C")
    IEMSTrackSchedule : public IEMSPassSchedule
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetLuts( 
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulLutID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOptSchedule( 
            /* [in] */ ULONG cbCount,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSSATELLITETRACK __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassProcessingTime( 
            /* [in] */ ULONG ulPrePass,
            /* [in] */ ULONG ulPostPass) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTrackScheduleVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTrackSchedule __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTrackSchedule __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatellites )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPrimaryLut )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ const ULONG ulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSchedule )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSchedule )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchedule )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLuts )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptSchedule )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSSATELLITETRACK __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassProcessingTime )( 
            IEMSTrackSchedule __RPC_FAR * This,
            /* [in] */ ULONG ulPrePass,
            /* [in] */ ULONG ulPostPass);
        
        END_INTERFACE
    } IEMSTrackScheduleVtbl;

    interface IEMSTrackSchedule
    {
        CONST_VTBL struct IEMSTrackScheduleVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTrackSchedule_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTrackSchedule_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTrackSchedule_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTrackSchedule_SetSatellites(This,cbCount,pulSatID)	\
    (This)->lpVtbl -> SetSatellites(This,cbCount,pulSatID)

#define IEMSTrackSchedule_SetPrimaryLut(This,ulLutID)	\
    (This)->lpVtbl -> SetPrimaryLut(This,ulLutID)

#define IEMSTrackSchedule_GenerateSchedule(This,startTime,stopTime)	\
    (This)->lpVtbl -> GenerateSchedule(This,startTime,stopTime)

#define IEMSTrackSchedule_SetSchedule(This,startTime,stopTime,pvPass,cbCount)	\
    (This)->lpVtbl -> SetSchedule(This,startTime,stopTime,pvPass,cbCount)

#define IEMSTrackSchedule_GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)


#define IEMSTrackSchedule_SetLuts(This,cbCount,pulLutID)	\
    (This)->lpVtbl -> SetLuts(This,cbCount,pulLutID)

#define IEMSTrackSchedule_GetOptSchedule(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetOptSchedule(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)

#define IEMSTrackSchedule_SetPassProcessingTime(This,ulPrePass,ulPostPass)	\
    (This)->lpVtbl -> SetPassProcessingTime(This,ulPrePass,ulPostPass)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTrackSchedule_SetLuts_Proxy( 
    IEMSTrackSchedule __RPC_FAR * This,
    /* [in] */ ULONG cbCount,
    /* [size_is][in] */ const ULONG __RPC_FAR *pulLutID);


void __RPC_STUB IEMSTrackSchedule_SetLuts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule_GetOptSchedule_Proxy( 
    IEMSTrackSchedule __RPC_FAR * This,
    /* [in] */ ULONG cbCount,
    /* [in] */ ULONG ulLutID,
    /* [length_is][size_is][out] */ EMSSATELLITETRACK __RPC_FAR *pvPass,
    /* [out] */ ULONG __RPC_FAR *pcbResult,
    /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
    /* [out] */ EMSTIME __RPC_FAR *lpStopTime);


void __RPC_STUB IEMSTrackSchedule_GetOptSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule_SetPassProcessingTime_Proxy( 
    IEMSTrackSchedule __RPC_FAR * This,
    /* [in] */ ULONG ulPrePass,
    /* [in] */ ULONG ulPostPass);


void __RPC_STUB IEMSTrackSchedule_SetPassProcessingTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTrackSchedule_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emstrack_0014 */
/* [local] */ 

typedef /* [unique] */ IEMSTrackSchedule __RPC_FAR *LPEMSTRACKSCHEDULE;



extern RPC_IF_HANDLE __MIDL_itf_emstrack_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstrack_0014_v0_0_s_ifspec;

#ifndef __IEMSTrackSchedule2_INTERFACE_DEFINED__
#define __IEMSTrackSchedule2_INTERFACE_DEFINED__

/* interface IEMSTrackSchedule2 */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSSATELLITETRACK2
    {
    ULONG ulLutID;
    ULONG ulAntennaID;
    EMSSATELLITEPASS PassInfo;
    EMSTIME actualStartTime;
    EMSTIME actualEndTime;
    double dWeight;
    }	EMSSATELLITETRACK2;

typedef struct _tagEMSSATELLITETRACK2 __RPC_FAR *LPEMSSATELLITETRACK2;

typedef struct  _tagEMSSATTRACKRECORD2
    {
    EMSTIME timeSched;
    WORD wSeq;
    WORD wCount;
    EMSSATELLITETRACK2 track;
    }	EMSSATTRACKRECORD2;

typedef struct _tagEMSSATTRACKRECORD2 __RPC_FAR *LPEMSSATTRACKRECORD2;


#pragma pack()

EXTERN_C const IID IID_IEMSTrackSchedule2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE7DA97A-E3C4-41e7-806A-E7B01C7B5118")
    IEMSTrackSchedule2 : public IEMSTrackSchedule
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
        
        virtual HRESULT STDMETHODCALLTYPE SetTrackingLimits( 
            DWORD dwCount,
            EMSSATPASSLIMITS __RPC_FAR *lpLimits) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTrackingLimit( 
            DWORD dwMinSatID,
            DWORD dwMaxSatID,
            double dMinutes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOptSchedule2( 
            /* [in] */ ULONG cbCount,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSSATELLITETRACK2 __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTrackSchedule2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTrackSchedule2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTrackSchedule2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatellites )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulSatID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPrimaryLut )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ const ULONG ulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSchedule )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSchedule )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ const EMSTIME startTime,
            /* [in] */ const EMSTIME stopTime,
            /* [size_is][in] */ const EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [in] */ ULONG cbCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSchedule )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSSATELLITEPASS __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLuts )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [size_is][in] */ const ULONG __RPC_FAR *pulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptSchedule )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSSATELLITETRACK __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassProcessingTime )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG ulPrePass,
            /* [in] */ ULONG ulPostPass);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFlags )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassLimits )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD dwCount,
            EMSSATPASSLIMITS __RPC_FAR *lpLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassLimit )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD dwMinSatID,
            DWORD dwMaxSatID,
            double dMinutes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTrackingLimits )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD dwCount,
            EMSSATPASSLIMITS __RPC_FAR *lpLimits);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTrackingLimit )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            DWORD dwMinSatID,
            DWORD dwMaxSatID,
            double dMinutes);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOptSchedule2 )( 
            IEMSTrackSchedule2 __RPC_FAR * This,
            /* [in] */ ULONG cbCount,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSSATELLITETRACK2 __RPC_FAR *pvPass,
            /* [out] */ ULONG __RPC_FAR *pcbResult,
            /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
            /* [out] */ EMSTIME __RPC_FAR *lpStopTime);
        
        END_INTERFACE
    } IEMSTrackSchedule2Vtbl;

    interface IEMSTrackSchedule2
    {
        CONST_VTBL struct IEMSTrackSchedule2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTrackSchedule2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTrackSchedule2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTrackSchedule2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTrackSchedule2_SetSatellites(This,cbCount,pulSatID)	\
    (This)->lpVtbl -> SetSatellites(This,cbCount,pulSatID)

#define IEMSTrackSchedule2_SetPrimaryLut(This,ulLutID)	\
    (This)->lpVtbl -> SetPrimaryLut(This,ulLutID)

#define IEMSTrackSchedule2_GenerateSchedule(This,startTime,stopTime)	\
    (This)->lpVtbl -> GenerateSchedule(This,startTime,stopTime)

#define IEMSTrackSchedule2_SetSchedule(This,startTime,stopTime,pvPass,cbCount)	\
    (This)->lpVtbl -> SetSchedule(This,startTime,stopTime,pvPass,cbCount)

#define IEMSTrackSchedule2_GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetSchedule(This,cbCount,pvPass,pcbResult,lpStartTime,lpStopTime)


#define IEMSTrackSchedule2_SetLuts(This,cbCount,pulLutID)	\
    (This)->lpVtbl -> SetLuts(This,cbCount,pulLutID)

#define IEMSTrackSchedule2_GetOptSchedule(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetOptSchedule(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)

#define IEMSTrackSchedule2_SetPassProcessingTime(This,ulPrePass,ulPostPass)	\
    (This)->lpVtbl -> SetPassProcessingTime(This,ulPrePass,ulPostPass)


#define IEMSTrackSchedule2_SetFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,dwFlags)

#define IEMSTrackSchedule2_GetFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,lpdwFlags)

#define IEMSTrackSchedule2_SetPassLimits(This,dwCount,lpLimits)	\
    (This)->lpVtbl -> SetPassLimits(This,dwCount,lpLimits)

#define IEMSTrackSchedule2_SetPassLimit(This,dwMinSatID,dwMaxSatID,dMinutes)	\
    (This)->lpVtbl -> SetPassLimit(This,dwMinSatID,dwMaxSatID,dMinutes)

#define IEMSTrackSchedule2_SetTrackingLimits(This,dwCount,lpLimits)	\
    (This)->lpVtbl -> SetTrackingLimits(This,dwCount,lpLimits)

#define IEMSTrackSchedule2_SetTrackingLimit(This,dwMinSatID,dwMaxSatID,dMinutes)	\
    (This)->lpVtbl -> SetTrackingLimit(This,dwMinSatID,dwMaxSatID,dMinutes)

#define IEMSTrackSchedule2_GetOptSchedule2(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)	\
    (This)->lpVtbl -> GetOptSchedule2(This,cbCount,ulLutID,pvPass,pcbResult,lpStartTime,lpStopTime)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_SetFlags_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD dwFlags);


void __RPC_STUB IEMSTrackSchedule2_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_GetFlags_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSTrackSchedule2_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_SetPassLimits_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD dwCount,
    EMSSATPASSLIMITS __RPC_FAR *lpLimits);


void __RPC_STUB IEMSTrackSchedule2_SetPassLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_SetPassLimit_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD dwMinSatID,
    DWORD dwMaxSatID,
    double dMinutes);


void __RPC_STUB IEMSTrackSchedule2_SetPassLimit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_SetTrackingLimits_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD dwCount,
    EMSSATPASSLIMITS __RPC_FAR *lpLimits);


void __RPC_STUB IEMSTrackSchedule2_SetTrackingLimits_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_SetTrackingLimit_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    DWORD dwMinSatID,
    DWORD dwMaxSatID,
    double dMinutes);


void __RPC_STUB IEMSTrackSchedule2_SetTrackingLimit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTrackSchedule2_GetOptSchedule2_Proxy( 
    IEMSTrackSchedule2 __RPC_FAR * This,
    /* [in] */ ULONG cbCount,
    /* [in] */ ULONG ulLutID,
    /* [length_is][size_is][out] */ EMSSATELLITETRACK2 __RPC_FAR *pvPass,
    /* [out] */ ULONG __RPC_FAR *pcbResult,
    /* [out] */ EMSTIME __RPC_FAR *lpStartTime,
    /* [out] */ EMSTIME __RPC_FAR *lpStopTime);


void __RPC_STUB IEMSTrackSchedule2_GetOptSchedule2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTrackSchedule2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emstrack_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSTrackSchedule2 __RPC_FAR *LPEMSTRACKSCHEDULE2;



extern RPC_IF_HANDLE __MIDL_itf_emstrack_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstrack_0015_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
