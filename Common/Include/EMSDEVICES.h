/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 29 15:47:29 2002
 */
/* Compiler settings for D:\devsar\include\EMSDEVICES.IDL:
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

#ifndef __EMSDEVICES_h__
#define __EMSDEVICES_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDevice_FWD_DEFINED__
#define __IEMSDevice_FWD_DEFINED__
typedef interface IEMSDevice IEMSDevice;
#endif 	/* __IEMSDevice_FWD_DEFINED__ */


#ifndef __IEMSSubDevice_FWD_DEFINED__
#define __IEMSSubDevice_FWD_DEFINED__
typedef interface IEMSSubDevice IEMSSubDevice;
#endif 	/* __IEMSSubDevice_FWD_DEFINED__ */


#ifndef __IEMSSubDeviceFactory_FWD_DEFINED__
#define __IEMSSubDeviceFactory_FWD_DEFINED__
typedef interface IEMSSubDeviceFactory IEMSSubDeviceFactory;
#endif 	/* __IEMSSubDeviceFactory_FWD_DEFINED__ */


#ifndef __IEMSEnumDevices_FWD_DEFINED__
#define __IEMSEnumDevices_FWD_DEFINED__
typedef interface IEMSEnumDevices IEMSEnumDevices;
#endif 	/* __IEMSEnumDevices_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSDEVICES_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {AC28AC42-5C2F-491d-BADA-1D1E58926BC9}
DEFINE_GUID(CLSID_EMSDevices, 0xac28ac42, 0x5c2f, 0x491d, 0xba, 0xda, 0x1d, 0x1e, 0x58, 0x92, 0x6b, 0xc9);
// {A1E1BD8D-2531-4afa-98F1-CED75B3243B8}
DEFINE_GUID(IID_IEMSEnumDevices, 0xa1e1bd8d, 0x2531, 0x4afa, 0x98, 0xf1, 0xce, 0xd7, 0x5b, 0x32, 0x43, 0xb8);
// {53EFD1FC-9105-4161-B5EF-C5D764248502}
DEFINE_GUID(IID_IEMSDevice, 0x53efd1fc, 0x9105, 0x4161, 0xb5, 0xef, 0xc5, 0xd7, 0x64, 0x24, 0x85, 0x2);
// {1C8AA1FF-158B-45e4-9623-F9D890855008}
DEFINE_GUID(IID_IEMSSubDeviceFactory, 0x1c8aa1ff, 0x158b, 0x45e4, 0x96, 0x23, 0xf9, 0xd8, 0x90, 0x85, 0x50, 0x8);
// {F76CEB4F-2C18-4ead-B3EB-8E43048BF2FA}
DEFINE_GUID(IID_IEMSSubDevice, 0xf76ceb4f, 0x2c18, 0x4ead, 0xb3, 0xeb, 0x8e, 0x43, 0x4, 0x8b, 0xf2, 0xfa);
#define	DEVDESCLEN	( 200 )

#define	DEVTYPE_ALL	( 0xffffffff )



extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0000_v0_0_s_ifspec;

#ifndef __IEMSDevice_INTERFACE_DEFINED__
#define __IEMSDevice_INTERFACE_DEFINED__

/* interface IEMSDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("53EFD1FC-9105-4161-B5EF-C5D764248502")
    IEMSDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ DWORD dwParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceInfo( 
            /* [in] */ DWORD dwStrLen,
            /* [size_is][out] */ LPTSTR lpszInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSDevice __RPC_FAR * This,
            /* [in] */ DWORD dwParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceInfo )( 
            IEMSDevice __RPC_FAR * This,
            /* [in] */ DWORD dwStrLen,
            /* [size_is][out] */ LPTSTR lpszInfo);
        
        END_INTERFACE
    } IEMSDeviceVtbl;

    interface IEMSDevice
    {
        CONST_VTBL struct IEMSDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDevice_Initialize(This,dwParam)	\
    (This)->lpVtbl -> Initialize(This,dwParam)

#define IEMSDevice_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSDevice_GetDeviceInfo(This,dwStrLen,lpszInfo)	\
    (This)->lpVtbl -> GetDeviceInfo(This,dwStrLen,lpszInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDevice_Initialize_Proxy( 
    IEMSDevice __RPC_FAR * This,
    /* [in] */ DWORD dwParam);


void __RPC_STUB IEMSDevice_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDevice_Reset_Proxy( 
    IEMSDevice __RPC_FAR * This);


void __RPC_STUB IEMSDevice_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDevice_GetDeviceInfo_Proxy( 
    IEMSDevice __RPC_FAR * This,
    /* [in] */ DWORD dwStrLen,
    /* [size_is][out] */ LPTSTR lpszInfo);


void __RPC_STUB IEMSDevice_GetDeviceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDEVICES_0077 */
/* [local] */ 

typedef /* [unique] */ IEMSDevice __RPC_FAR *LPEMSDEVICE;



extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0077_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0077_v0_0_s_ifspec;

#ifndef __IEMSSubDevice_INTERFACE_DEFINED__
#define __IEMSSubDevice_INTERFACE_DEFINED__

/* interface IEMSSubDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSubDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F76CEB4F-2C18-4ead-B3EB-8E43048BF2FA")
    IEMSSubDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetParentDevice( 
            /* [out][in] */ LPEMSDEVICE __RPC_FAR *lpDev) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDeviceID( 
            /* [out][in] */ LPDWORD lpDevID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSubDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSubDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSubDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSubDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSSubDevice __RPC_FAR * This,
            /* [out][in] */ LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSSubDevice __RPC_FAR * This,
            /* [out][in] */ LPDWORD lpDevID);
        
        END_INTERFACE
    } IEMSSubDeviceVtbl;

    interface IEMSSubDevice
    {
        CONST_VTBL struct IEMSSubDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSubDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSubDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSubDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSubDevice_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSSubDevice_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSubDevice_GetParentDevice_Proxy( 
    IEMSSubDevice __RPC_FAR * This,
    /* [out][in] */ LPEMSDEVICE __RPC_FAR *lpDev);


void __RPC_STUB IEMSSubDevice_GetParentDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSubDevice_GetDeviceID_Proxy( 
    IEMSSubDevice __RPC_FAR * This,
    /* [out][in] */ LPDWORD lpDevID);


void __RPC_STUB IEMSSubDevice_GetDeviceID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSubDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDEVICES_0078 */
/* [local] */ 

typedef /* [unique] */ IEMSSubDevice __RPC_FAR *LPEMSSUBDEVICE;



extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0078_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0078_v0_0_s_ifspec;

#ifndef __IEMSSubDeviceFactory_INTERFACE_DEFINED__
#define __IEMSSubDeviceFactory_INTERFACE_DEFINED__

/* interface IEMSSubDeviceFactory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSubDeviceFactory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1C8AA1FF-158B-45e4-9623-F9D890855008")
    IEMSSubDeviceFactory : public IEMSDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CreateSubDevice( 
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwDeviceID,
            /* [out] */ LPEMSSUBDEVICE __RPC_FAR *lppSubDev) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSubDeviceFactoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSubDeviceFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSubDeviceFactory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSubDeviceFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSSubDeviceFactory __RPC_FAR * This,
            /* [in] */ DWORD dwParam);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSSubDeviceFactory __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceInfo )( 
            IEMSSubDeviceFactory __RPC_FAR * This,
            /* [in] */ DWORD dwStrLen,
            /* [size_is][out] */ LPTSTR lpszInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CreateSubDevice )( 
            IEMSSubDeviceFactory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [in] */ DWORD dwDeviceID,
            /* [out] */ LPEMSSUBDEVICE __RPC_FAR *lppSubDev);
        
        END_INTERFACE
    } IEMSSubDeviceFactoryVtbl;

    interface IEMSSubDeviceFactory
    {
        CONST_VTBL struct IEMSSubDeviceFactoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSubDeviceFactory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSubDeviceFactory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSubDeviceFactory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSubDeviceFactory_Initialize(This,dwParam)	\
    (This)->lpVtbl -> Initialize(This,dwParam)

#define IEMSSubDeviceFactory_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSSubDeviceFactory_GetDeviceInfo(This,dwStrLen,lpszInfo)	\
    (This)->lpVtbl -> GetDeviceInfo(This,dwStrLen,lpszInfo)


#define IEMSSubDeviceFactory_CreateSubDevice(This,riid,dwDeviceID,lppSubDev)	\
    (This)->lpVtbl -> CreateSubDevice(This,riid,dwDeviceID,lppSubDev)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSubDeviceFactory_CreateSubDevice_Proxy( 
    IEMSSubDeviceFactory __RPC_FAR * This,
    /* [in] */ REFIID riid,
    /* [in] */ DWORD dwDeviceID,
    /* [out] */ LPEMSSUBDEVICE __RPC_FAR *lppSubDev);


void __RPC_STUB IEMSSubDeviceFactory_CreateSubDevice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSubDeviceFactory_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDEVICES_0079 */
/* [local] */ 

typedef /* [unique] */ IEMSSubDeviceFactory __RPC_FAR *LPEMSSUBDEVICEFACTORY;



extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0079_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0079_v0_0_s_ifspec;

#ifndef __IEMSEnumDevices_INTERFACE_DEFINED__
#define __IEMSEnumDevices_INTERFACE_DEFINED__

/* interface IEMSEnumDevices */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagDEVICEINFO
    {
    IID iid;
    GUID guid;
    DWORD dwDevType;
    CHAR szDevDesc[ 200 ];
    }	EMSDEVICEINFO;

typedef struct _tagDEVICEINFO __RPC_FAR *LPEMSDEVICEINFO;


EXTERN_C const IID IID_IEMSEnumDevices;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1E1BD8D-2531-4afa-98F1-CED75B3243B8")
    IEMSEnumDevices : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EnumDevices( 
            /* [out][in] */ LPDWORD lpdwnumDeviceEntries,
            /* [out] */ LPEMSDEVICEINFO lpDevInfo,
            /* [in] */ DWORD dwNumCATIDs,
            /* [size_is][in] */ GUID __RPC_FAR catid[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSEnumDevicesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSEnumDevices __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSEnumDevices __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSEnumDevices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IEMSEnumDevices __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnumDevices )( 
            IEMSEnumDevices __RPC_FAR * This,
            /* [out][in] */ LPDWORD lpdwnumDeviceEntries,
            /* [out] */ LPEMSDEVICEINFO lpDevInfo,
            /* [in] */ DWORD dwNumCATIDs,
            /* [size_is][in] */ GUID __RPC_FAR catid[  ]);
        
        END_INTERFACE
    } IEMSEnumDevicesVtbl;

    interface IEMSEnumDevices
    {
        CONST_VTBL struct IEMSEnumDevicesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSEnumDevices_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSEnumDevices_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSEnumDevices_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSEnumDevices_Initialize(This)	\
    (This)->lpVtbl -> Initialize(This)

#define IEMSEnumDevices_EnumDevices(This,lpdwnumDeviceEntries,lpDevInfo,dwNumCATIDs,catid)	\
    (This)->lpVtbl -> EnumDevices(This,lpdwnumDeviceEntries,lpDevInfo,dwNumCATIDs,catid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSEnumDevices_Initialize_Proxy( 
    IEMSEnumDevices __RPC_FAR * This);


void __RPC_STUB IEMSEnumDevices_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSEnumDevices_EnumDevices_Proxy( 
    IEMSEnumDevices __RPC_FAR * This,
    /* [out][in] */ LPDWORD lpdwnumDeviceEntries,
    /* [out] */ LPEMSDEVICEINFO lpDevInfo,
    /* [in] */ DWORD dwNumCATIDs,
    /* [size_is][in] */ GUID __RPC_FAR catid[  ]);


void __RPC_STUB IEMSEnumDevices_EnumDevices_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSEnumDevices_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSDEVICES_0080 */
/* [local] */ 

typedef /* [unique] */ IEMSEnumDevices __RPC_FAR *LPEMSENUMDEVICES;



extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0080_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSDEVICES_0080_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
