/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Dec 05 11:20:27 2003
 */
/* Compiler settings for emsdm.idl:
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

#ifndef __emsdm_h__
#define __emsdm_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDataManager_FWD_DEFINED__
#define __IEMSDataManager_FWD_DEFINED__
typedef interface IEMSDataManager IEMSDataManager;
#endif 	/* __IEMSDataManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "EMSTYPEX.h"
#include "DAL.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsdm_0000 */
/* [local] */ 

// {0837EEDF-9AB4-4ae6-B7C0-49CBE5F0F485}
DEFINE_GUID(CLSID_CEMSDataManager, 0x837eedf, 0x9ab4, 0x4ae6, 0xb7, 0xc0, 0x49, 0xcb, 0xe5, 0xf0, 0xf4, 0x85);

// {94D155A6-3D58-4869-B15A-8E6ECAD2AC9A}
DEFINE_GUID(IID_IEMSDataManager, 0x94d155a6, 0x3d58, 0x4869, 0xb1, 0x5a, 0x8e, 0x6e, 0xca, 0xd2, 0xac, 0x9a);

#define	c_ulMAX_SOURCE_PATH_LEN	( 512 )

typedef struct  _tagEMSSourcesTimeOut
    {
    double dOlderThan;
    EMSRECORDTYPE rt;
    }	EMSSOURCESTIMEOUT;

typedef struct  _tagEMSPathTimeOut
    {
    wchar_t wszPath[ 512 ];
    double dOlderThan;
    }	EMSSOURCEPATHTIMEOUT;



extern RPC_IF_HANDLE __MIDL_itf_emsdm_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsdm_0000_v0_0_s_ifspec;

#ifndef __IEMSDataManager_INTERFACE_DEFINED__
#define __IEMSDataManager_INTERFACE_DEFINED__

/* interface IEMSDataManager */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDataManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("94D155A6-3D58-4869-B15A-8E6ECAD2AC9A")
    IEMSDataManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ArchiveDB( 
            /* [in] */ ULONG ulNumSources,
            /* [size_is][in] */ EMSSOURCESTIMEOUT __RPC_FAR aSources[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ArchivePath( 
            /* [in] */ ULONG ulNumSources,
            /* [size_is][in] */ EMSSOURCEPATHTIMEOUT __RPC_FAR aSourcePaths[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArchiveDB )( 
            IEMSDataManager __RPC_FAR * This,
            /* [in] */ ULONG ulNumSources,
            /* [size_is][in] */ EMSSOURCESTIMEOUT __RPC_FAR aSources[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ArchivePath )( 
            IEMSDataManager __RPC_FAR * This,
            /* [in] */ ULONG ulNumSources,
            /* [size_is][in] */ EMSSOURCEPATHTIMEOUT __RPC_FAR aSourcePaths[  ]);
        
        END_INTERFACE
    } IEMSDataManagerVtbl;

    interface IEMSDataManager
    {
        CONST_VTBL struct IEMSDataManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataManager_ArchiveDB(This,ulNumSources,aSources)	\
    (This)->lpVtbl -> ArchiveDB(This,ulNumSources,aSources)

#define IEMSDataManager_ArchivePath(This,ulNumSources,aSourcePaths)	\
    (This)->lpVtbl -> ArchivePath(This,ulNumSources,aSourcePaths)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataManager_ArchiveDB_Proxy( 
    IEMSDataManager __RPC_FAR * This,
    /* [in] */ ULONG ulNumSources,
    /* [size_is][in] */ EMSSOURCESTIMEOUT __RPC_FAR aSources[  ]);


void __RPC_STUB IEMSDataManager_ArchiveDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataManager_ArchivePath_Proxy( 
    IEMSDataManager __RPC_FAR * This,
    /* [in] */ ULONG ulNumSources,
    /* [size_is][in] */ EMSSOURCEPATHTIMEOUT __RPC_FAR aSourcePaths[  ]);


void __RPC_STUB IEMSDataManager_ArchivePath_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsdm_0193 */
/* [local] */ 

typedef IEMSDataManager __RPC_FAR *LPEMSDATAMANAGER;



extern RPC_IF_HANDLE __MIDL_itf_emsdm_0193_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsdm_0193_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
