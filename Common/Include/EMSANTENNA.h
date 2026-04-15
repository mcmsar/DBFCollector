/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 21 16:43:31 2002
 */
/* Compiler settings for C:\Dev\Devices\AntennaDevice\EMSANTENNA.IDL:
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

#ifndef __EMSANTENNA_h__
#define __EMSANTENNA_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAntennaDevice_FWD_DEFINED__
#define __IEMSAntennaDevice_FWD_DEFINED__
typedef interface IEMSAntennaDevice IEMSAntennaDevice;
#endif 	/* __IEMSAntennaDevice_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSANTENNA_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {A2DC47CC-7156-4bd7-BBCF-01A059ADE33C}
DEFINE_GUID(IID_IEMSAntennaDevice, 0xa2dc47cc, 0x7156, 0x4bd7, 0xbb, 0xcf, 0x1, 0xa0, 0x59, 0xad, 0xe3, 0x3c);
 
// {53374D01-3488-4282-9F2C-4B02825BE9DC}
DEFINE_GUID(CLSID_CEMSAntennaDevice, 0x53374d01, 0x3488, 0x4282, 0x9f, 0x2c, 0x4b, 0x2, 0x82, 0x5b, 0xe9, 0xdc);
 
const int ELOFFSET = 8;	//EL status codes are AZ status code just bit-shifted by this amount

//status flags
const int EMS_ANTENNA_AZ_MOVING		= 0x00000001;
const int EMS_ANTENNA_AZ_CWFROMHOME	= 0x00000002;	//Set means the antenna is on the clock-wise side of the home position,
												//Reset means the antenna is on the counter clock-wise side of the home position.
const int EMS_ANTENNA_AZ_LIMPVE		= 0x00000004;	//+ve limit reached
const int EMS_ANTENNA_AZ_LIMNVE		= 0x00000008;	//-ve limit reached
const int EMS_ANTENNA_AZ_HOME		= 0x00000010;	//device at home position
const int EMS_ANTENNA_AZ_ERROR		= 0x00000080;
const int EMS_ANTENNA_EL_MOVING		= 0x00000100;	//EMS_ANTENNA_AZ_MOVING << ELOFFSET
const int EMS_ANTENNA_EL_CWFROMHOME	= 0x00000200;	//EMS_ANTENNA_AZ_CWFROMHOME << ELOFFSET
const int EMS_ANTENNA_EL_LIMPVE		= 0x00000400;	//EMS_ANTENNA_AZ_LIMPVE << ELOFFSET
const int EMS_ANTENNA_EL_LIMNVE		= 0x00000800;	//EMS_ANTENNA_AZ_LIMNVE << ELOFFSET
const int EMS_ANTENNA_EL_HOME		= 0x00001000;	//EMS_ANTENNA_AZ_HOME << ELOFFSET
const int EMS_ANTENNA_EL_ERROR		= 0x00008000;	//EMS_ANTENNA_AZ_ERROR << ELOFFSET

const int EMS_ANTENNA_HOME			= 0x00010000;
const int EMS_ANTENNA_ERROR			= 0x80000000;
 
const int EMS_ANTENNA_INIT_NORESET	= 0x00000001;
const int EMS_ANTENNA_INIT_REFRESH	= 0x00000002;
const int EMS_ANTENNA_INIT_REINIT	= 0x00000003;


extern RPC_IF_HANDLE __MIDL_itf_EMSANTENNA_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSANTENNA_0000_v0_0_s_ifspec;

#ifndef __IEMSAntennaDevice_INTERFACE_DEFINED__
#define __IEMSAntennaDevice_INTERFACE_DEFINED__

/* interface IEMSAntennaDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAntennaDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2DC47CC-7156-4bd7-BBCF-01A059ADE33C")
    IEMSAntennaDevice : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ ULONG __RPC_FAR *lpulFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ LPEMSAZEL lpPosition,
            /* [out] */ LPEMSTIME lpAZTime,
            /* [out] */ LPEMSTIME lpELTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRate( 
            /* [out] */ LPEMSAZEL lpRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxSpeed( 
            /* [in] */ EMSAZEL Speed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSpeed( 
            /* [out] */ EMSAZEL __RPC_FAR *lpMaxSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHomeTime( 
            /* [out] */ ULONG __RPC_FAR *lpulMilliSecs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHomePosition( 
            /* [out] */ EMSAZEL __RPC_FAR *lpPosition) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBeamWidth( 
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMinElevation( 
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxElevation( 
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxAzimuth( 
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetHandle( 
            /* [in] */ DWORD dwStrLen,
            /* [size_is][in] */ LPTSTR lpszHandleID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetAndHome( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Home( 
            /* [in] */ ULONG ulResetCounter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetCounter( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveToPosition( 
            /* [in] */ EMSAZEL Position,
            /* [in] */ EMSAZEL Rate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveAtRate( 
            /* [in] */ EMSAZEL Rate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAntennaDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAntennaDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAntennaDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStatus )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ LPEMSAZEL lpPosition,
            /* [out] */ LPEMSTIME lpAZTime,
            /* [out] */ LPEMSTIME lpELTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRate )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ LPEMSAZEL lpRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxSpeed )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ EMSAZEL Speed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSpeed )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSAZEL __RPC_FAR *lpMaxSpeed);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHomeTime )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulMilliSecs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetHomePosition )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSAZEL __RPC_FAR *lpPosition);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBeamWidth )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMinElevation )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxElevation )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxAzimuth )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetHandle )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ DWORD dwStrLen,
            /* [size_is][in] */ LPTSTR lpszHandleID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetAndHome )( 
            IEMSAntennaDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Home )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ ULONG ulResetCounter);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCounter )( 
            IEMSAntennaDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveToPosition )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ EMSAZEL Position,
            /* [in] */ EMSAZEL Rate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveAtRate )( 
            IEMSAntennaDevice __RPC_FAR * This,
            /* [in] */ EMSAZEL Rate);
        
        END_INTERFACE
    } IEMSAntennaDeviceVtbl;

    interface IEMSAntennaDevice
    {
        CONST_VTBL struct IEMSAntennaDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAntennaDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAntennaDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAntennaDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAntennaDevice_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSAntennaDevice_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSAntennaDevice_GetStatus(This,lpulFlags)	\
    (This)->lpVtbl -> GetStatus(This,lpulFlags)

#define IEMSAntennaDevice_GetPosition(This,lpPosition,lpAZTime,lpELTime)	\
    (This)->lpVtbl -> GetPosition(This,lpPosition,lpAZTime,lpELTime)

#define IEMSAntennaDevice_GetRate(This,lpRate)	\
    (This)->lpVtbl -> GetRate(This,lpRate)

#define IEMSAntennaDevice_SetMaxSpeed(This,Speed)	\
    (This)->lpVtbl -> SetMaxSpeed(This,Speed)

#define IEMSAntennaDevice_GetMaxSpeed(This,lpMaxSpeed)	\
    (This)->lpVtbl -> GetMaxSpeed(This,lpMaxSpeed)

#define IEMSAntennaDevice_GetHomeTime(This,lpulMilliSecs)	\
    (This)->lpVtbl -> GetHomeTime(This,lpulMilliSecs)

#define IEMSAntennaDevice_GetHomePosition(This,lpPosition)	\
    (This)->lpVtbl -> GetHomePosition(This,lpPosition)

#define IEMSAntennaDevice_GetBeamWidth(This,lpDegrees)	\
    (This)->lpVtbl -> GetBeamWidth(This,lpDegrees)

#define IEMSAntennaDevice_GetMinElevation(This,lpDegrees)	\
    (This)->lpVtbl -> GetMinElevation(This,lpDegrees)

#define IEMSAntennaDevice_GetMaxElevation(This,lpDegrees)	\
    (This)->lpVtbl -> GetMaxElevation(This,lpDegrees)

#define IEMSAntennaDevice_GetMaxAzimuth(This,lpDegrees)	\
    (This)->lpVtbl -> GetMaxAzimuth(This,lpDegrees)

#define IEMSAntennaDevice_SetHandle(This,dwStrLen,lpszHandleID)	\
    (This)->lpVtbl -> SetHandle(This,dwStrLen,lpszHandleID)

#define IEMSAntennaDevice_ResetAndHome(This)	\
    (This)->lpVtbl -> ResetAndHome(This)

#define IEMSAntennaDevice_Home(This,ulResetCounter)	\
    (This)->lpVtbl -> Home(This,ulResetCounter)

#define IEMSAntennaDevice_ResetCounter(This)	\
    (This)->lpVtbl -> ResetCounter(This)

#define IEMSAntennaDevice_MoveToPosition(This,Position,Rate)	\
    (This)->lpVtbl -> MoveToPosition(This,Position,Rate)

#define IEMSAntennaDevice_MoveAtRate(This,Rate)	\
    (This)->lpVtbl -> MoveAtRate(This,Rate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetStatus_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulFlags);


void __RPC_STUB IEMSAntennaDevice_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetPosition_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ LPEMSAZEL lpPosition,
    /* [out] */ LPEMSTIME lpAZTime,
    /* [out] */ LPEMSTIME lpELTime);


void __RPC_STUB IEMSAntennaDevice_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetRate_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ LPEMSAZEL lpRate);


void __RPC_STUB IEMSAntennaDevice_GetRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_SetMaxSpeed_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [in] */ EMSAZEL Speed);


void __RPC_STUB IEMSAntennaDevice_SetMaxSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetMaxSpeed_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSAZEL __RPC_FAR *lpMaxSpeed);


void __RPC_STUB IEMSAntennaDevice_GetMaxSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetHomeTime_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulMilliSecs);


void __RPC_STUB IEMSAntennaDevice_GetHomeTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetHomePosition_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSAZEL __RPC_FAR *lpPosition);


void __RPC_STUB IEMSAntennaDevice_GetHomePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetBeamWidth_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);


void __RPC_STUB IEMSAntennaDevice_GetBeamWidth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetMinElevation_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);


void __RPC_STUB IEMSAntennaDevice_GetMinElevation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetMaxElevation_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);


void __RPC_STUB IEMSAntennaDevice_GetMaxElevation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_GetMaxAzimuth_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [out] */ EMSDEGREES __RPC_FAR *lpDegrees);


void __RPC_STUB IEMSAntennaDevice_GetMaxAzimuth_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_SetHandle_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [in] */ DWORD dwStrLen,
    /* [size_is][in] */ LPTSTR lpszHandleID);


void __RPC_STUB IEMSAntennaDevice_SetHandle_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_ResetAndHome_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This);


void __RPC_STUB IEMSAntennaDevice_ResetAndHome_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_Home_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [in] */ ULONG ulResetCounter);


void __RPC_STUB IEMSAntennaDevice_Home_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_ResetCounter_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This);


void __RPC_STUB IEMSAntennaDevice_ResetCounter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_MoveToPosition_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [in] */ EMSAZEL Position,
    /* [in] */ EMSAZEL Rate);


void __RPC_STUB IEMSAntennaDevice_MoveToPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaDevice_MoveAtRate_Proxy( 
    IEMSAntennaDevice __RPC_FAR * This,
    /* [in] */ EMSAZEL Rate);


void __RPC_STUB IEMSAntennaDevice_MoveAtRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAntennaDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSANTENNA_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSAntennaDevice __RPC_FAR *LPEMSANTENNADEVICE;



extern RPC_IF_HANDLE __MIDL_itf_EMSANTENNA_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSANTENNA_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
