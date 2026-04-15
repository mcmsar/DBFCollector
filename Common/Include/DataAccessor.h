
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Feb 26 13:49:44 2003
 */
/* Compiler settings for F:\dev\LEOLUT600\INCLUDE\dataaccessor.IDL:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
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

#ifndef __DataAccessor_h__
#define __DataAccessor_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSDBConnection_FWD_DEFINED__
#define __IEMSDBConnection_FWD_DEFINED__
typedef interface IEMSDBConnection IEMSDBConnection;
#endif 	/* __IEMSDBConnection_FWD_DEFINED__ */


#ifndef __IEMSAccessor_FWD_DEFINED__
#define __IEMSAccessor_FWD_DEFINED__
typedef interface IEMSAccessor IEMSAccessor;
#endif 	/* __IEMSAccessor_FWD_DEFINED__ */


/* header files for imported files */
#include "leolut600dbs.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_dataaccessor_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {3CF00255-D829-42cf-80BF-08B3E8C46053}
DEFINE_GUID(CLSID_EMSAccessor, 0x3cf00255, 0xd829, 0x42cf, 0x80, 0xbf, 0x8, 0xb3, 0xe8, 0xc4, 0x60, 0x53);
// {F2496C3B-CA31-4e14-87DA-8E8B6B9310A2}
DEFINE_GUID(IID_IEMSDBConnection, 0xf2496c3b, 0xca31, 0x4e14, 0x87, 0xda, 0x8e, 0x8b, 0x6b, 0x93, 0x10, 0xa2);
// {A4256E86-AC4D-4082-BB76-6EA71A7BF6FE}
DEFINE_GUID(IID_IEMSAccessor, 0xa4256e86, 0xac4d, 0x4082, 0xbb, 0x76, 0x6e, 0xa7, 0x1a, 0x7b, 0xf6, 0xfe);


extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0000_v0_0_s_ifspec;

#ifndef __IEMSDBConnection_INTERFACE_DEFINED__
#define __IEMSDBConnection_INTERFACE_DEFINED__

/* interface IEMSDBConnection */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDBConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F2496C3B-CA31-4e14-87DA-8E8B6B9310A2")
    IEMSDBConnection : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [string][in] */ LPCWSTR szConnection) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDBConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSDBConnection * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSDBConnection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSDBConnection * This);
        
        HRESULT ( STDMETHODCALLTYPE *Connect )( 
            IEMSDBConnection * This,
            /* [string][in] */ LPCWSTR szConnection);
        
        HRESULT ( STDMETHODCALLTYPE *Disconnect )( 
            IEMSDBConnection * This);
        
        END_INTERFACE
    } IEMSDBConnectionVtbl;

    interface IEMSDBConnection
    {
        CONST_VTBL struct IEMSDBConnectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDBConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDBConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDBConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDBConnection_Connect(This,szConnection)	\
    (This)->lpVtbl -> Connect(This,szConnection)

#define IEMSDBConnection_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDBConnection_Connect_Proxy( 
    IEMSDBConnection * This,
    /* [string][in] */ LPCWSTR szConnection);


void __RPC_STUB IEMSDBConnection_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDBConnection_Disconnect_Proxy( 
    IEMSDBConnection * This);


void __RPC_STUB IEMSDBConnection_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDBConnection_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dataaccessor_0398 */
/* [local] */ 

typedef /* [unique] */ IEMSDBConnection *LPEMSDBCONNECTION;



extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0398_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0398_v0_0_s_ifspec;

#ifndef __IEMSAccessor_INTERFACE_DEFINED__
#define __IEMSAccessor_INTERFACE_DEFINED__

/* interface IEMSAccessor */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAccessor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A4256E86-AC4D-4082-BB76-6EA71A7BF6FE")
    IEMSAccessor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE get_spectrumDataSet( 
            /* [in] */ EMSSELECTCRITERIA *pCriteria,
            /* [out][in] */ long *plCount,
            /* [size_is][size_is][out] */ LPEMSSPECTRUM **papData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE get_cbcDataSet( 
            /* [in] */ EMSSELECTCRITERIA *pCriteria,
            /* [out][in] */ long *plCount,
            /* [size_is][size_is][out] */ LPEMSCBCDATA **papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAccessorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSAccessor * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSAccessor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSAccessor * This);
        
        HRESULT ( STDMETHODCALLTYPE *get_spectrumDataSet )( 
            IEMSAccessor * This,
            /* [in] */ EMSSELECTCRITERIA *pCriteria,
            /* [out][in] */ long *plCount,
            /* [size_is][size_is][out] */ LPEMSSPECTRUM **papData);
        
        HRESULT ( STDMETHODCALLTYPE *get_cbcDataSet )( 
            IEMSAccessor * This,
            /* [in] */ EMSSELECTCRITERIA *pCriteria,
            /* [out][in] */ long *plCount,
            /* [size_is][size_is][out] */ LPEMSCBCDATA **papData);
        
        END_INTERFACE
    } IEMSAccessorVtbl;

    interface IEMSAccessor
    {
        CONST_VTBL struct IEMSAccessorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAccessor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAccessor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAccessor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAccessor_get_spectrumDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_spectrumDataSet(This,pCriteria,plCount,papData)

#define IEMSAccessor_get_cbcDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_cbcDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAccessor_get_spectrumDataSet_Proxy( 
    IEMSAccessor * This,
    /* [in] */ EMSSELECTCRITERIA *pCriteria,
    /* [out][in] */ long *plCount,
    /* [size_is][size_is][out] */ LPEMSSPECTRUM **papData);


void __RPC_STUB IEMSAccessor_get_spectrumDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAccessor_get_cbcDataSet_Proxy( 
    IEMSAccessor * This,
    /* [in] */ EMSSELECTCRITERIA *pCriteria,
    /* [out][in] */ long *plCount,
    /* [size_is][size_is][out] */ LPEMSCBCDATA **papData);


void __RPC_STUB IEMSAccessor_get_cbcDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAccessor_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_dataaccessor_0399 */
/* [local] */ 

typedef /* [unique] */ IEMSAccessor *LPEMSACCESSOR;



extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0399_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dataaccessor_0399_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


