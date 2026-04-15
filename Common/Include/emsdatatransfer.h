/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Oct 31 16:03:46 2003
 */
/* Compiler settings for C:\dev\common\Include\emsdatatransfer.idl:
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

#ifndef __emsdatatransfer_h__
#define __emsdatatransfer_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDataTransfer_FWD_DEFINED__
#define __IEMSDataTransfer_FWD_DEFINED__
typedef interface IEMSDataTransfer IEMSDataTransfer;
#endif 	/* __IEMSDataTransfer_FWD_DEFINED__ */


#ifndef __EMSDataTransfer_FWD_DEFINED__
#define __EMSDataTransfer_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSDataTransfer EMSDataTransfer;
#else
typedef struct EMSDataTransfer EMSDataTransfer;
#endif /* __cplusplus */

#endif 	/* __EMSDataTransfer_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "igateway.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsdatatransfer_0000 */
/* [local] */ 


// {A2167182-71C9-4046-BC1C-15989BC9BA66}
DEFINE_GUID( CLSID_EMSDataTransfer, 0xa2167182, 0x71c9, 0x4046, 0xbc, 0x1c, 0x15, 0x98, 0x9b, 0xc9, 0xba, 0x66);

// {01FAC86F-C73D-4284-AB74-9A6EE1DBC35B}
DEFINE_GUID( IID_IEMSDataTransfer, 0x1fac86f, 0xc73d, 0x4284, 0xab, 0x74, 0x9a, 0x6e, 0xe1, 0xdb, 0xc3, 0x5b);



extern RPC_IF_HANDLE __MIDL_itf_emsdatatransfer_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsdatatransfer_0000_v0_0_s_ifspec;

#ifndef __IEMSDataTransfer_INTERFACE_DEFINED__
#define __IEMSDataTransfer_INTERFACE_DEFINED__

/* interface IEMSDataTransfer */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataTransfer __RPC_FAR *LPEMSDATATRANSFER;


EXTERN_C const IID IID_IEMSDataTransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("01FAC86F-C73D-4284-AB74-9A6EE1DBC35B")
    IEMSDataTransfer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UploadData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ unsigned long ulUploadTarget,
            /* [in] */ EMSRECORDTYPE eRecordType,
            /* [in] */ unsigned long ulMaxPackageSize,
            /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataTransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataTransfer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataTransfer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataTransfer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UploadData )( 
            IEMSDataTransfer __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ unsigned long ulUploadTarget,
            /* [in] */ EMSRECORDTYPE eRecordType,
            /* [in] */ unsigned long ulMaxPackageSize,
            /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere);
        
        END_INTERFACE
    } IEMSDataTransferVtbl;

    interface IEMSDataTransfer
    {
        CONST_VTBL struct IEMSDataTransferVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataTransfer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataTransfer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataTransfer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataTransfer_UploadData(This,ulDestID,ulUploadTarget,eRecordType,ulMaxPackageSize,wszSQLWhere)	\
    (This)->lpVtbl -> UploadData(This,ulDestID,ulUploadTarget,eRecordType,ulMaxPackageSize,wszSQLWhere)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataTransfer_UploadData_Proxy( 
    IEMSDataTransfer __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ unsigned long ulUploadTarget,
    /* [in] */ EMSRECORDTYPE eRecordType,
    /* [in] */ unsigned long ulMaxPackageSize,
    /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere);


void __RPC_STUB IEMSDataTransfer_UploadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataTransfer_INTERFACE_DEFINED__ */



#ifndef __EMSDataTransferLib_LIBRARY_DEFINED__
#define __EMSDataTransferLib_LIBRARY_DEFINED__

/* library EMSDataTransferLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSDataTransferLib;

EXTERN_C const CLSID CLSID_EMSDataTransfer;

#ifdef __cplusplus

class DECLSPEC_UUID("A2167182-71C9-4046-BC1C-15989BC9BA66")
EMSDataTransfer;
#endif
#endif /* __EMSDataTransferLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
