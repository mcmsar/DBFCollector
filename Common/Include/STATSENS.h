
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 5.03.0280 */
/* at Sat Jan 04 13:48:28 2003
 */
/* Compiler settings for D:\Devsar\leo600\status\STATSENS.IDL:
    Os (OptLev=s), W1, Zp8, env=Win32 (32b run), ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __STATSENS_h__
#define __STATSENS_h__

/* Forward Declarations */ 

#ifndef __IEMSSensorStatus_FWD_DEFINED__
#define __IEMSSensorStatus_FWD_DEFINED__
typedef interface IEMSSensorStatus IEMSSensorStatus;
#endif 	/* __IEMSSensorStatus_FWD_DEFINED__ */


#ifndef __IEMSSensorStatusEx_FWD_DEFINED__
#define __IEMSSensorStatusEx_FWD_DEFINED__
typedef interface IEMSSensorStatusEx IEMSSensorStatusEx;
#endif 	/* __IEMSSensorStatusEx_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

#ifdef __cplusplus
extern "C"{
#endif 

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATSENS_0000 */
/* [local] */ 

// {B88A5C0C-96AD-4db4-9210-11657A1E1266}
DEFINE_GUID( IID_IEMSSensorStatus, 0xb88a5c0c, 0x96ad, 0x4db4, 0x92, 0x10, 0x11, 0x65, 0x7a, 0x1e, 0x12, 0x66);
 
 // {D9F292BA-0083-4d1e-9AB3-DDD1EDCB8FFC}
DEFINE_GUID( IID_IEMSSensorStatusEx, 0xd9f292ba, 0x83, 0x4d1e, 0x9a, 0xb3, 0xdd, 0xd1, 0xed, 0xcb, 0x8f, 0xfc);
 


extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0000_v0_0_s_ifspec;

#ifndef __IEMSSensorStatus_INTERFACE_DEFINED__
#define __IEMSSensorStatus_INTERFACE_DEFINED__

/* interface IEMSSensorStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct _tagEMSSENSORINFO
    {
    double dTempA;
    double dTempB;
    double dTempC;
    double dTempD;
    double dTempE;
    double dTempF;
    double dTempG;
    double dTempH;
    double dTempI;
    double dTempJ;
    double dHumidityA;
    double dHumidityB;
    double dVoltageA;
    double dVoltageB;
    double dVoltageC;
    double dVoltageD;
    DWORD dwDoorA;
    DWORD dwDoorB;
    DWORD dwDoorC;
    DWORD dwDoorD;
    }	EMSSENSORINFO;

typedef struct _tagEMSSENSORINFO __RPC_FAR *LPEMSSENSORINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSSensorStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B88A5C0C-96AD-4db4-9210-11657A1E1266")
    IEMSSensorStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetSensorInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSensorInfo( 
            /* [in] */ EMSSENSORINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSensorInfo( 
            /* [out] */ EMSSENSORINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSensorStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSensorStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSensorStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSensorStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetSensorInfo )( 
            IEMSSensorStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensorInfo )( 
            IEMSSensorStatus __RPC_FAR * This,
            /* [in] */ EMSSENSORINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorInfo )( 
            IEMSSensorStatus __RPC_FAR * This,
            /* [out] */ EMSSENSORINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSSensorStatusVtbl;

    interface IEMSSensorStatus
    {
        CONST_VTBL struct IEMSSensorStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSensorStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSensorStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSensorStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSSensorStatus_ResetSensorInfo(This)	\
    (This)->lpVtbl -> ResetSensorInfo(This)

#define IEMSSensorStatus_SetSensorInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetSensorInfo(This,lpInfo)

#define IEMSSensorStatus_GetSensorInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetSensorInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSensorStatus_ResetSensorInfo_Proxy( 
    IEMSSensorStatus __RPC_FAR * This);


void __RPC_STUB IEMSSensorStatus_ResetSensorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSensorStatus_SetSensorInfo_Proxy( 
    IEMSSensorStatus __RPC_FAR * This,
    /* [in] */ EMSSENSORINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSensorStatus_SetSensorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSensorStatus_GetSensorInfo_Proxy( 
    IEMSSensorStatus __RPC_FAR * This,
    /* [out] */ EMSSENSORINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSensorStatus_GetSensorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSensorStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATSENS_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSSensorStatus __RPC_FAR *LPEMSSENSORSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0012_v0_0_s_ifspec;

#ifndef __IEMSSensorStatusEx_INTERFACE_DEFINED__
#define __IEMSSensorStatusEx_INTERFACE_DEFINED__

/* interface IEMSSensorStatusEx */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct _tagEMSSENSORINFOEX
    {
    WORD wDoorStatus;
    float fACUTemp;
    float fAUXTemp;
    float fServoTemp;
    float fLNCTemp;
    float fRadomeTemp;
    float fRackTemp;
    float fRackAmbientTemp;
    float fRadomeHumidity;
    float fACUHumidity;
    float fAGCVoltage;
    WORD wWindSpeed;
    WORD wWindDirection;
    WORD wPowerAlarm;
    WORD wSpare;
    }	EMSSENSORINFOEX;

typedef struct _tagEMSSENSORINFOEX __RPC_FAR *LPEMSSENSORINFOEX;


#pragma pack()

EXTERN_C const IID IID_IEMSSensorStatusEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D9F292BA-0083-4d1e-9AB3-DDD1EDCB8FFC")
    IEMSSensorStatusEx : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetSensorInfoEx( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSensorInfoEx( 
            /* [in] */ EMSSENSORINFOEX __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSensorInfoEx( 
            /* [out] */ EMSSENSORINFOEX __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSensorStatusExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSensorStatusEx __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSensorStatusEx __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSensorStatusEx __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetSensorInfoEx )( 
            IEMSSensorStatusEx __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSensorInfoEx )( 
            IEMSSensorStatusEx __RPC_FAR * This,
            /* [in] */ EMSSENSORINFOEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSensorInfoEx )( 
            IEMSSensorStatusEx __RPC_FAR * This,
            /* [out] */ EMSSENSORINFOEX __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSSensorStatusExVtbl;

    interface IEMSSensorStatusEx
    {
        CONST_VTBL struct IEMSSensorStatusExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSensorStatusEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSensorStatusEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSensorStatusEx_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSSensorStatusEx_ResetSensorInfoEx(This)	\
    (This)->lpVtbl -> ResetSensorInfoEx(This)

#define IEMSSensorStatusEx_SetSensorInfoEx(This,lpInfo)	\
    (This)->lpVtbl -> SetSensorInfoEx(This,lpInfo)

#define IEMSSensorStatusEx_GetSensorInfoEx(This,lpInfo)	\
    (This)->lpVtbl -> GetSensorInfoEx(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSensorStatusEx_ResetSensorInfoEx_Proxy( 
    IEMSSensorStatusEx __RPC_FAR * This);


void __RPC_STUB IEMSSensorStatusEx_ResetSensorInfoEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSensorStatusEx_SetSensorInfoEx_Proxy( 
    IEMSSensorStatusEx __RPC_FAR * This,
    /* [in] */ EMSSENSORINFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSensorStatusEx_SetSensorInfoEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSensorStatusEx_GetSensorInfoEx_Proxy( 
    IEMSSensorStatusEx __RPC_FAR * This,
    /* [out] */ EMSSENSORINFOEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSensorStatusEx_GetSensorInfoEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSensorStatusEx_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATSENS_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSSensorStatusEx __RPC_FAR *LPEMSSENSORSTATUSEX;



extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATSENS_0013_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


