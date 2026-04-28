/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jun 25 15:16:20 2011
 */
/* Compiler settings for ..\common\include\EMSORBIT.IDL:
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

#ifndef __EMSORBIT_h__
#define __EMSORBIT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSOrbit_FWD_DEFINED__
#define __IEMSOrbit_FWD_DEFINED__
typedef interface IEMSOrbit IEMSOrbit;
#endif 	/* __IEMSOrbit_FWD_DEFINED__ */


#ifndef __IEMSOrbit2_FWD_DEFINED__
#define __IEMSOrbit2_FWD_DEFINED__
typedef interface IEMSOrbit2 IEMSOrbit2;
#endif 	/* __IEMSOrbit2_FWD_DEFINED__ */


#ifndef __IEMSOrbit3_FWD_DEFINED__
#define __IEMSOrbit3_FWD_DEFINED__
typedef interface IEMSOrbit3 IEMSOrbit3;
#endif 	/* __IEMSOrbit3_FWD_DEFINED__ */


#ifndef __IEMSOrbit4_FWD_DEFINED__
#define __IEMSOrbit4_FWD_DEFINED__
typedef interface IEMSOrbit4 IEMSOrbit4;
#endif 	/* __IEMSOrbit4_FWD_DEFINED__ */


#ifndef __IEMSOrbit5_FWD_DEFINED__
#define __IEMSOrbit5_FWD_DEFINED__
typedef interface IEMSOrbit5 IEMSOrbit5;
#endif 	/* __IEMSOrbit5_FWD_DEFINED__ */


#ifndef __IEMSOrbitInit_FWD_DEFINED__
#define __IEMSOrbitInit_FWD_DEFINED__
typedef interface IEMSOrbitInit IEMSOrbitInit;
#endif 	/* __IEMSOrbitInit_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSORBIT_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {E8F04C91-4552-11d5-8B95-009027912866} 
DEFINE_GUID( CLSID_EMSOrbit, 0xe8f04c91, 0x4552, 0x11d5, 0x8b, 0x95, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66); 
 
// {E8F04C92-4552-11d5-8B95-009027912866} 
DEFINE_GUID( IID_IEMSOrbit, 0xe8f04c92, 0x4552, 0x11d5, 0x8b, 0x95, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66); 
 
// {90EFA3C3-CFD8-4a39-9321-AC2C7C18D5AA}
DEFINE_GUID( IID_IEMSOrbit2, 0x90efa3c3, 0xcfd8, 0x4a39, 0x93, 0x21, 0xac, 0x2c, 0x7c, 0x18, 0xd5, 0xaa);
 
// {31D9B372-71A0-4298-9122-F7DFFB067439}
DEFINE_GUID( IID_IEMSOrbit3, 0x31d9b372, 0x71a0, 0x4298, 0x91, 0x22, 0xf7, 0xdf, 0xfb, 0x6, 0x74, 0x39);
 
// {738265B6-9E40-44ff-B8A7-E5F681AFBA18}
DEFINE_GUID( IID_IEMSOrbit4, 0x738265b6, 0x9e40, 0x44ff, 0xb8, 0xa7, 0xe5, 0xf6, 0x81, 0xaf, 0xba, 0x18);
 
// {DEDFE2BA-F2FB-4bee-9744-207931959F40}
DEFINE_GUID( IID_IEMSOrbit5, 0xdedfe2ba, 0xf2fb, 0x4bee, 0x97, 0x44, 0x20, 0x79, 0x31, 0x95, 0x9f, 0x40);
 
// {CE4EC876-A5CF-4f82-9B7A-5362D6D363F1}
DEFINE_GUID(IID_IEMSOrbitInit, 0xce4ec876, 0xa5cf, 0x4f82, 0x9b, 0x7a, 0x53, 0x62, 0xd6, 0xd3, 0x63, 0xf1);
// Flags for SetSatelliteTLE3 
#define EMS_ORBIT_OVERRIDE_MORE_RECENT	(0x0001)
#define EMS_ORBIT_OVERRIDE_ALL			(0x0002)
#define EMS_ORBIT_POST_MANOEUVRE			(0x0004)
 


extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0000_v0_0_s_ifspec;

#pragma pack(push, 4)

#ifndef __IEMSOrbit_INTERFACE_DEFINED__
#define __IEMSOrbit_INTERFACE_DEFINED__

/* interface IEMSOrbit */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSTLEDATA
    {
    EMSTIME timeEpoch;
    double fXndt2o;
    double fXndd6o;
    double fBStar;
    int nOrbitNumber;
    double fCoVarMatrix[ 21 ];
    /* [switch_is][switch_type] */ union 
        {
        /* [default] */ struct  
            {
            double fInclination;
            double fRightAscNode;
            double fEccentricity;
            double fArgPerigee;
            double fMeanAnomaly;
            double fMeanMotion;
            }	var;
        /* [case()] */ double vect[ 6 ];
        }	elem;
    }	EMSTLEDATA;

typedef struct _tagEMSTLEDATA __RPC_FAR *LPEMSTLEDATA;


EXTERN_C const IID IID_IEMSOrbit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E8F04C92-4552-11d5-8B95-009027912866")
    IEMSOrbit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EarthFixedOrbit( 
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InertialOrbit( 
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EarthFixedOrbitTLE( 
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InertialOrbitTLE( 
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatelliteTLE( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteTLE( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PropogateTLE( 
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrbitNumber( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reload( 
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbit )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbit )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLE )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLE )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropogateTLE )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitNumber )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reload )( 
            IEMSOrbit __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEMSOrbitVtbl;

    interface IEMSOrbit
    {
        CONST_VTBL struct IEMSOrbitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbit_EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit_InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit_EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit_InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit_SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)

#define IEMSOrbit_GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit_PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)	\
    (This)->lpVtbl -> PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)

#define IEMSOrbit_GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)	\
    (This)->lpVtbl -> GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)

#define IEMSOrbit_Reload(This,dwFlags)	\
    (This)->lpVtbl -> Reload(This,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbit_EarthFixedOrbit_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit_EarthFixedOrbit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_InertialOrbit_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit_InertialOrbit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_EarthFixedOrbitTLE_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit_EarthFixedOrbitTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_InertialOrbitTLE_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit_InertialOrbitTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_SetSatelliteTLE_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTIME eTime,
    /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);


void __RPC_STUB IEMSOrbit_SetSatelliteTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_GetSatelliteTLE_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTIME eTime,
    /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);


void __RPC_STUB IEMSOrbit_GetSatelliteTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_PropogateTLE_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
    /* [in] */ const EMSTIME eTime,
    /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);


void __RPC_STUB IEMSOrbit_PropogateTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_GetOrbitNumber_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTIME eTime,
    /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);


void __RPC_STUB IEMSOrbit_GetOrbitNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit_Reload_Proxy( 
    IEMSOrbit __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSOrbit_Reload_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbit_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbit __RPC_FAR *LPEMSORBIT;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0008_v0_0_s_ifspec;

#ifndef __IEMSOrbit2_INTERFACE_DEFINED__
#define __IEMSOrbit2_INTERFACE_DEFINED__

/* interface IEMSOrbit2 */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSTLEDATA2
    {
    EMSTLEDATA tle;
    EMSTIME timeEffective;
    EMSTIME timeModified;
    }	EMSTLEDATA2;

typedef struct _tagEMSTLEDATA2 __RPC_FAR *LPEMSTLEDATA2;


EXTERN_C const IID IID_IEMSOrbit2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90EFA3C3-CFD8-4a39-9321-AC2C7C18D5AA")
    IEMSOrbit2 : public IEMSOrbit
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSatelliteTLE2( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteTLE2( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertOrbitVectorToTLE( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbit2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbit2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbit2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbit )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbit )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropogateTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitNumber )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reload )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE2 )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE2 )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLE )( 
            IEMSOrbit2 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        END_INTERFACE
    } IEMSOrbit2Vtbl;

    interface IEMSOrbit2
    {
        CONST_VTBL struct IEMSOrbit2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbit2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbit2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbit2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbit2_EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit2_InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit2_EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit2_InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit2_SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)

#define IEMSOrbit2_GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit2_PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)	\
    (This)->lpVtbl -> PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)

#define IEMSOrbit2_GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)	\
    (This)->lpVtbl -> GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)

#define IEMSOrbit2_Reload(This,dwFlags)	\
    (This)->lpVtbl -> Reload(This,dwFlags)


#define IEMSOrbit2_SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)

#define IEMSOrbit2_GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit2_ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbit2_SetSatelliteTLE2_Proxy( 
    IEMSOrbit2 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData);


void __RPC_STUB IEMSOrbit2_SetSatelliteTLE2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit2_GetSatelliteTLE2_Proxy( 
    IEMSOrbit2 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTIME eTime,
    /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData);


void __RPC_STUB IEMSOrbit2_GetSatelliteTLE2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit2_ConvertOrbitVectorToTLE_Proxy( 
    IEMSOrbit2 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ EMSTIMECOORD timeCoord,
    /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);


void __RPC_STUB IEMSOrbit2_ConvertOrbitVectorToTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbit2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0009 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbit2 __RPC_FAR *LPEMSORBIT2;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0009_v0_0_s_ifspec;

#ifndef __IEMSOrbit3_INTERFACE_DEFINED__
#define __IEMSOrbit3_INTERFACE_DEFINED__

/* interface IEMSOrbit3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSOrbit3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31D9B372-71A0-4298-9122-F7DFFB067439")
    IEMSOrbit3 : public IEMSOrbit2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSatelliteTLE3( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbit3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbit3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbit3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbit )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbit )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropogateTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitNumber )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reload )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE2 )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE2 )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLE )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE3 )( 
            IEMSOrbit3 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEMSOrbit3Vtbl;

    interface IEMSOrbit3
    {
        CONST_VTBL struct IEMSOrbit3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbit3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbit3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbit3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbit3_EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit3_InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit3_EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit3_InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit3_SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)

#define IEMSOrbit3_GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit3_PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)	\
    (This)->lpVtbl -> PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)

#define IEMSOrbit3_GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)	\
    (This)->lpVtbl -> GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)

#define IEMSOrbit3_Reload(This,dwFlags)	\
    (This)->lpVtbl -> Reload(This,dwFlags)


#define IEMSOrbit3_SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)

#define IEMSOrbit3_GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit3_ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)


#define IEMSOrbit3_SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)	\
    (This)->lpVtbl -> SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbit3_SetSatelliteTLE3_Proxy( 
    IEMSOrbit3 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSOrbit3_SetSatelliteTLE3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbit3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0010 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbit3 __RPC_FAR *LPEMSORBIT3;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0010_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0010_v0_0_s_ifspec;

#ifndef __IEMSOrbit4_INTERFACE_DEFINED__
#define __IEMSOrbit4_INTERFACE_DEFINED__

/* interface IEMSOrbit4 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSOrbit4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("738265B6-9E40-44ff-B8A7-E5F681AFBA18")
    IEMSOrbit4 : public IEMSOrbit3
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE EarthFixedOrbitDouble( 
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InertialOrbitDouble( 
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EarthFixedOrbitTLEDouble( 
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InertialOrbitTLEDouble( 
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConvertOrbitVectorToTLEDouble( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORDD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbit4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbit4 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbit4 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbit )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbit )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropogateTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitNumber )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reload )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE2 )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE2 )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLE )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE3 )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitDouble )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitDouble )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLEDouble )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLEDouble )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLEDouble )( 
            IEMSOrbit4 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORDD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        END_INTERFACE
    } IEMSOrbit4Vtbl;

    interface IEMSOrbit4
    {
        CONST_VTBL struct IEMSOrbit4Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbit4_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbit4_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbit4_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbit4_EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)

#define IEMSOrbit4_GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit4_PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)	\
    (This)->lpVtbl -> PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)

#define IEMSOrbit4_GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)	\
    (This)->lpVtbl -> GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)

#define IEMSOrbit4_Reload(This,dwFlags)	\
    (This)->lpVtbl -> Reload(This,dwFlags)


#define IEMSOrbit4_SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)

#define IEMSOrbit4_GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit4_ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)


#define IEMSOrbit4_SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)	\
    (This)->lpVtbl -> SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)


#define IEMSOrbit4_EarthFixedOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_InertialOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_EarthFixedOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_InertialOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit4_ConvertOrbitVectorToTLEDouble(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLEDouble(This,ulSatelliteID,timeCoord,lpTLEData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbit4_EarthFixedOrbitDouble_Proxy( 
    IEMSOrbit4 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit4_EarthFixedOrbitDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit4_InertialOrbitDouble_Proxy( 
    IEMSOrbit4 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit4_InertialOrbitDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit4_EarthFixedOrbitTLEDouble_Proxy( 
    IEMSOrbit4 __RPC_FAR * This,
    /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit4_EarthFixedOrbitTLEDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit4_InertialOrbitTLEDouble_Proxy( 
    IEMSOrbit4 __RPC_FAR * This,
    /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
    /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
    /* [in] */ ULONG cbCount,
    /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
    /* [out] */ ULONG __RPC_FAR *pcbResult);


void __RPC_STUB IEMSOrbit4_InertialOrbitTLEDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOrbit4_ConvertOrbitVectorToTLEDouble_Proxy( 
    IEMSOrbit4 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ EMSTIMECOORDD timeCoord,
    /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);


void __RPC_STUB IEMSOrbit4_ConvertOrbitVectorToTLEDouble_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbit4_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0011 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbit4 __RPC_FAR *LPEMSORBIT4;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0011_v0_0_s_ifspec;

#ifndef __IEMSOrbit5_INTERFACE_DEFINED__
#define __IEMSOrbit5_INTERFACE_DEFINED__

/* interface IEMSOrbit5 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSOrbit5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DEDFE2BA-F2FB-4bee-9744-207931959F40")
    IEMSOrbit5 : public IEMSOrbit4
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteTLE3( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbit5Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbit5 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbit5 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbit )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbit )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [in] */ const EMSTLEDATA __RPC_FAR *pTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PropogateTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLEData,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpPropogatedTLE);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOrbitNumber )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ ULONG __RPC_FAR *lpulOrbitNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reload )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE2 )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE2 )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLE )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSatelliteTLE3 )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitDouble )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitDouble )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EarthFixedOrbitTLEDouble )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InertialOrbitTLEDouble )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ EMSTLEDATA __RPC_FAR *lpTLE,
            /* [size_is][in] */ const EMSTIME __RPC_FAR *pvTime,
            /* [in] */ ULONG cbCount,
            /* [length_is][size_is][out] */ EMSTIMECOORDD __RPC_FAR *pvCoord,
            /* [out] */ ULONG __RPC_FAR *pcbResult);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConvertOrbitVectorToTLEDouble )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIMECOORDD timeCoord,
            /* [out] */ EMSTLEDATA __RPC_FAR *lpTLEData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatelliteTLE3 )( 
            IEMSOrbit5 __RPC_FAR * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ const EMSTIME eTime,
            /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        END_INTERFACE
    } IEMSOrbit5Vtbl;

    interface IEMSOrbit5
    {
        CONST_VTBL struct IEMSOrbit5Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbit5_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbit5_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbit5_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbit5_EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbit(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLE(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE(This,ulSatelliteID,eTime,pTLEData)

#define IEMSOrbit5_GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit5_PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)	\
    (This)->lpVtbl -> PropogateTLE(This,lpTLEData,eTime,lpPropogatedTLE)

#define IEMSOrbit5_GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)	\
    (This)->lpVtbl -> GetOrbitNumber(This,ulSatelliteID,eTime,lpulOrbitNumber)

#define IEMSOrbit5_Reload(This,dwFlags)	\
    (This)->lpVtbl -> Reload(This,dwFlags)


#define IEMSOrbit5_SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)	\
    (This)->lpVtbl -> SetSatelliteTLE2(This,ulSatelliteID,lpTLEData)

#define IEMSOrbit5_GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)	\
    (This)->lpVtbl -> GetSatelliteTLE2(This,ulSatelliteID,eTime,lpTLEData)

#define IEMSOrbit5_ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLE(This,ulSatelliteID,timeCoord,lpTLEData)


#define IEMSOrbit5_SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)	\
    (This)->lpVtbl -> SetSatelliteTLE3(This,ulSatelliteID,lpTLEData,dwFlags)


#define IEMSOrbit5_EarthFixedOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_InertialOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitDouble(This,ulSatelliteID,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_EarthFixedOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> EarthFixedOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_InertialOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)	\
    (This)->lpVtbl -> InertialOrbitTLEDouble(This,lpTLE,pvTime,cbCount,pvCoord,pcbResult)

#define IEMSOrbit5_ConvertOrbitVectorToTLEDouble(This,ulSatelliteID,timeCoord,lpTLEData)	\
    (This)->lpVtbl -> ConvertOrbitVectorToTLEDouble(This,ulSatelliteID,timeCoord,lpTLEData)


#define IEMSOrbit5_GetSatelliteTLE3(This,ulSatelliteID,eTime,lpTLEData,lpdwFlags)	\
    (This)->lpVtbl -> GetSatelliteTLE3(This,ulSatelliteID,eTime,lpTLEData,lpdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbit5_GetSatelliteTLE3_Proxy( 
    IEMSOrbit5 __RPC_FAR * This,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ const EMSTIME eTime,
    /* [out] */ EMSTLEDATA2 __RPC_FAR *lpTLEData,
    /* [out] */ DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSOrbit5_GetSatelliteTLE3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbit5_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbit5 __RPC_FAR *LPEMSORBIT5;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0012_v0_0_s_ifspec;

#ifndef __IEMSOrbitInit_INTERFACE_DEFINED__
#define __IEMSOrbitInit_INTERFACE_DEFINED__

/* interface IEMSOrbitInit */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSOrbitInit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE4EC876-A5CF-4f82-9B7A-5362D6D363F1")
    IEMSOrbitInit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOrbitInitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOrbitInit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOrbitInit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOrbitInit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSOrbitInit __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSOrbitInitVtbl;

    interface IEMSOrbitInit
    {
        CONST_VTBL struct IEMSOrbitInitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOrbitInit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOrbitInit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOrbitInit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOrbitInit_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOrbitInit_Initialize_Proxy( 
    IEMSOrbitInit __RPC_FAR * This);


void __RPC_STUB IEMSOrbitInit_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOrbitInit_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSORBIT_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSOrbitInit __RPC_FAR *LPEMSORBITINIT;



extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSORBIT_0013_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#pragma pack(pop)

#endif
