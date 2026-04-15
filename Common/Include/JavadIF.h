

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 20 15:56:13 2013
 */
/* Compiler settings for ..\Common\Include\JavadIF.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __JavadIF_h__
#define __JavadIF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSJavadInterface_FWD_DEFINED__
#define __IEMSJavadInterface_FWD_DEFINED__
typedef interface IEMSJavadInterface IEMSJavadInterface;
#endif 	/* __IEMSJavadInterface_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "gpsephem.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_JavadIF_0000_0000 */
/* [local] */ 

// {28a9f519-8519-497f-884b-64980ba3cf92}
DEFINE_GUID( CLSID_EMSJavadInterface, 0x28a9f519, 0x8519, 0x497f, 0x88, 0x4b, 0x64, 0x98, 0x0b, 0xa3, 0xcf, 0x92);
 
// {28a9f51a-8519-497f-884b-64980ba3cf92}
DEFINE_GUID( IID_IEMSJavadInterface, 0x28a9f51a, 0x8519, 0x497f, 0x88, 0x4b, 0x64, 0x98, 0x0b, 0xa3, 0xcf, 0x92);
 

#pragma pack(1)
typedef struct _tagEMSGLOEPHEMERIS
    {
    BYTE cSv;
    BYTE cFrqNum;
    short siDne;
    int iTk;
    int iTb;
    BYTE cHealth;
    BYTE cAge;
    BYTE cFlags;
    double dR[ 3 ];
    float fV[ 3 ];
    float fW[ 3 ];
    double dTauSys;
    float fTau;
    float fGamma;
    float fDelTauN;
    BYTE cNFt;
    BYTE cNN4;
    WORD wFlags2;
    } 	EMSGLOEPHEMERIS;

typedef struct _tagEMSGLOEPHEMERIS *LPEMSGLOEPHEMERIS;

typedef struct _tagEMSGLOEPHEMERIS2
    {
    ULONG ulSatID;
    EMSGLOEPHEMERIS baseData;
    } 	EMSGLOEPHEMERIS2;

typedef struct _tagEMSGLOEPHEMERIS2 *LPEMSGLOEPHEMERIS2;

typedef struct _tagEMSGALEPHEMERIS
    {
    EMSEPHEMERISDATA gps;
    float fBgdE1E5a;
    float fBgdE1E5b;
    float fAi[ 3 ];
    BYTE cSfi;
    BYTE cNavType;
    } 	EMSGALEPHEMERIS;

typedef struct _tagEMSGALEPHEMERIS *LPEMSGALEPHEMERIS;


#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_JavadIF_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_JavadIF_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSJavadInterface_INTERFACE_DEFINED__
#define __IEMSJavadInterface_INTERFACE_DEFINED__

/* interface IEMSJavadInterface */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSJavadInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28a9f51a-8519-497f-884b-64980ba3cf92")
    IEMSJavadInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitEphemerisData( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitGpsEphemeris( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitGalEphemeris( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitGloEphemeris( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGpsEphemerisData( 
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSEPHEMERISDATA **lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGloEphemerisData( 
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSGLOEPHEMERIS **lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGalEphemerisData( 
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSGALEPHEMERIS **lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLeapSeconds( 
            /* [out] */ WORD *wLeapSeconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRcvTimeAcuracy( 
            /* [out] */ float *fAccuracy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Open( 
            /* [in] */ DWORD dwDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReadTime( 
            /* [out] */ LPEMSTIME lpEmsTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTime( 
            /* [in] */ EMSTIME emsTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMode( 
            /* [out] */ LPDWORD lpdwMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMode( 
            /* [in] */ DWORD dwMode) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SyncSystemClock( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [out] */ EMSLOCATION *lpLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetHardwareStatus( 
            /* [out] */ DWORD *lpdwStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSJavadInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSJavadInterface * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSJavadInterface * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitEphemerisData )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitGpsEphemeris )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitGalEphemeris )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitGloEphemeris )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetGpsEphemerisData )( 
            IEMSJavadInterface * This,
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSEPHEMERISDATA **lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetGloEphemerisData )( 
            IEMSJavadInterface * This,
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSGLOEPHEMERIS **lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetGalEphemerisData )( 
            IEMSJavadInterface * This,
            /* [out] */ ULONG *ulCount,
            /* [out] */ EMSGALEPHEMERIS **lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLeapSeconds )( 
            IEMSJavadInterface * This,
            /* [out] */ WORD *wLeapSeconds);
        
        HRESULT ( STDMETHODCALLTYPE *GetRcvTimeAcuracy )( 
            IEMSJavadInterface * This,
            /* [out] */ float *fAccuracy);
        
        HRESULT ( STDMETHODCALLTYPE *Open )( 
            IEMSJavadInterface * This,
            /* [in] */ DWORD dwDevice);
        
        HRESULT ( STDMETHODCALLTYPE *Close )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *ReadTime )( 
            IEMSJavadInterface * This,
            /* [out] */ LPEMSTIME lpEmsTime);
        
        HRESULT ( STDMETHODCALLTYPE *SetTime )( 
            IEMSJavadInterface * This,
            /* [in] */ EMSTIME emsTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetMode )( 
            IEMSJavadInterface * This,
            /* [out] */ LPDWORD lpdwMode);
        
        HRESULT ( STDMETHODCALLTYPE *SetMode )( 
            IEMSJavadInterface * This,
            /* [in] */ DWORD dwMode);
        
        HRESULT ( STDMETHODCALLTYPE *SyncSystemClock )( 
            IEMSJavadInterface * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IEMSJavadInterface * This,
            /* [out] */ EMSLOCATION *lpLocation);
        
        HRESULT ( STDMETHODCALLTYPE *GetHardwareStatus )( 
            IEMSJavadInterface * This,
            /* [out] */ DWORD *lpdwStatus);
        
        END_INTERFACE
    } IEMSJavadInterfaceVtbl;

    interface IEMSJavadInterface
    {
        CONST_VTBL struct IEMSJavadInterfaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSJavadInterface_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSJavadInterface_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSJavadInterface_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSJavadInterface_InitEphemerisData(This)	\
    ( (This)->lpVtbl -> InitEphemerisData(This) ) 

#define IEMSJavadInterface_InitGpsEphemeris(This)	\
    ( (This)->lpVtbl -> InitGpsEphemeris(This) ) 

#define IEMSJavadInterface_InitGalEphemeris(This)	\
    ( (This)->lpVtbl -> InitGalEphemeris(This) ) 

#define IEMSJavadInterface_InitGloEphemeris(This)	\
    ( (This)->lpVtbl -> InitGloEphemeris(This) ) 

#define IEMSJavadInterface_GetGpsEphemerisData(This,ulCount,lpData)	\
    ( (This)->lpVtbl -> GetGpsEphemerisData(This,ulCount,lpData) ) 

#define IEMSJavadInterface_GetGloEphemerisData(This,ulCount,lpData)	\
    ( (This)->lpVtbl -> GetGloEphemerisData(This,ulCount,lpData) ) 

#define IEMSJavadInterface_GetGalEphemerisData(This,ulCount,lpData)	\
    ( (This)->lpVtbl -> GetGalEphemerisData(This,ulCount,lpData) ) 

#define IEMSJavadInterface_GetLeapSeconds(This,wLeapSeconds)	\
    ( (This)->lpVtbl -> GetLeapSeconds(This,wLeapSeconds) ) 

#define IEMSJavadInterface_GetRcvTimeAcuracy(This,fAccuracy)	\
    ( (This)->lpVtbl -> GetRcvTimeAcuracy(This,fAccuracy) ) 

#define IEMSJavadInterface_Open(This,dwDevice)	\
    ( (This)->lpVtbl -> Open(This,dwDevice) ) 

#define IEMSJavadInterface_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define IEMSJavadInterface_ReadTime(This,lpEmsTime)	\
    ( (This)->lpVtbl -> ReadTime(This,lpEmsTime) ) 

#define IEMSJavadInterface_SetTime(This,emsTime)	\
    ( (This)->lpVtbl -> SetTime(This,emsTime) ) 

#define IEMSJavadInterface_GetMode(This,lpdwMode)	\
    ( (This)->lpVtbl -> GetMode(This,lpdwMode) ) 

#define IEMSJavadInterface_SetMode(This,dwMode)	\
    ( (This)->lpVtbl -> SetMode(This,dwMode) ) 

#define IEMSJavadInterface_SyncSystemClock(This)	\
    ( (This)->lpVtbl -> SyncSystemClock(This) ) 

#define IEMSJavadInterface_GetPosition(This,lpLocation)	\
    ( (This)->lpVtbl -> GetPosition(This,lpLocation) ) 

#define IEMSJavadInterface_GetHardwareStatus(This,lpdwStatus)	\
    ( (This)->lpVtbl -> GetHardwareStatus(This,lpdwStatus) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSJavadInterface_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_JavadIF_0000_0001 */
/* [local] */ 

typedef /* [unique] */ IEMSJavadInterface *LPEMSJAVADINTERFACE;



extern RPC_IF_HANDLE __MIDL_itf_JavadIF_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_JavadIF_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


