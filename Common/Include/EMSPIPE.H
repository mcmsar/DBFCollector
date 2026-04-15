/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 22 15:27:40 2007
 */
/* Compiler settings for ..\common\include\EMSPIPE.IDL:
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

#ifndef __EMSPIPE_h__
#define __EMSPIPE_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSeqStream_FWD_DEFINED__
#define __IEMSSeqStream_FWD_DEFINED__
typedef interface IEMSSeqStream IEMSSeqStream;
#endif 	/* __IEMSSeqStream_FWD_DEFINED__ */


#ifndef __IEMSPacketStream_FWD_DEFINED__
#define __IEMSPacketStream_FWD_DEFINED__
typedef interface IEMSPacketStream IEMSPacketStream;
#endif 	/* __IEMSPacketStream_FWD_DEFINED__ */


#ifndef __IEMSRandomStream_FWD_DEFINED__
#define __IEMSRandomStream_FWD_DEFINED__
typedef interface IEMSRandomStream IEMSRandomStream;
#endif 	/* __IEMSRandomStream_FWD_DEFINED__ */


#ifndef __IEMSTextSeqStream_FWD_DEFINED__
#define __IEMSTextSeqStream_FWD_DEFINED__
typedef interface IEMSTextSeqStream IEMSTextSeqStream;
#endif 	/* __IEMSTextSeqStream_FWD_DEFINED__ */


#ifndef __IEMSDataSource_FWD_DEFINED__
#define __IEMSDataSource_FWD_DEFINED__
typedef interface IEMSDataSource IEMSDataSource;
#endif 	/* __IEMSDataSource_FWD_DEFINED__ */


#ifndef __IEMSDataSink_FWD_DEFINED__
#define __IEMSDataSink_FWD_DEFINED__
typedef interface IEMSDataSink IEMSDataSink;
#endif 	/* __IEMSDataSink_FWD_DEFINED__ */


#ifndef __IEMSDataSink2_FWD_DEFINED__
#define __IEMSDataSink2_FWD_DEFINED__
typedef interface IEMSDataSink2 IEMSDataSink2;
#endif 	/* __IEMSDataSink2_FWD_DEFINED__ */


#ifndef __IEMSDataPipeline_FWD_DEFINED__
#define __IEMSDataPipeline_FWD_DEFINED__
typedef interface IEMSDataPipeline IEMSDataPipeline;
#endif 	/* __IEMSDataPipeline_FWD_DEFINED__ */


#ifndef __IEMSDataPipeline2_FWD_DEFINED__
#define __IEMSDataPipeline2_FWD_DEFINED__
typedef interface IEMSDataPipeline2 IEMSDataPipeline2;
#endif 	/* __IEMSDataPipeline2_FWD_DEFINED__ */


#ifndef __IEMSCommandSource_FWD_DEFINED__
#define __IEMSCommandSource_FWD_DEFINED__
typedef interface IEMSCommandSource IEMSCommandSource;
#endif 	/* __IEMSCommandSource_FWD_DEFINED__ */


#ifndef __IEMSCommandSink_FWD_DEFINED__
#define __IEMSCommandSink_FWD_DEFINED__
typedef interface IEMSCommandSink IEMSCommandSink;
#endif 	/* __IEMSCommandSink_FWD_DEFINED__ */


#ifndef __IEMSCommandChannel_FWD_DEFINED__
#define __IEMSCommandChannel_FWD_DEFINED__
typedef interface IEMSCommandChannel IEMSCommandChannel;
#endif 	/* __IEMSCommandChannel_FWD_DEFINED__ */


#ifndef __IEMSCommandChannel2_FWD_DEFINED__
#define __IEMSCommandChannel2_FWD_DEFINED__
typedef interface IEMSCommandChannel2 IEMSCommandChannel2;
#endif 	/* __IEMSCommandChannel2_FWD_DEFINED__ */


#ifndef __EMSDataPipeline_FWD_DEFINED__
#define __EMSDataPipeline_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSDataPipeline EMSDataPipeline;
#else
typedef struct EMSDataPipeline EMSDataPipeline;
#endif /* __cplusplus */

#endif 	/* __EMSDataPipeline_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSPIPE_0000 */
/* [local] */ 

#include "emserror.h"
#include "emscom.h"
#include "pipemsgs.h"


/*********************************************************************
*	GUIDs
*********************************************************************/

// {488E3131-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( CLSID_EMSDataPipeline, 0x488e3131, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {488E3132-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSCommandChannel, 0x488e3132, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {488E3133-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSDataPipeline, 0x488e3133, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {5F414595-AB0A-4880-9351-3D9700A9B1DD}
DEFINE_GUID( IID_IEMSDataPipeline2, 0x5f414595, 0xab0a, 0x4880, 0x93, 0x51, 0x3d, 0x97, 0x0, 0xa9, 0xb1, 0xdd);

// {488E3134-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSCommandSource, 0x488e3134, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {488E3135-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSCommandSink, 0x488e3135, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {488E3136-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSDataSource, 0x488e3136, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {488E3137-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSDataSink, 0x488e3137, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {6FBD1F04-C2D6-4830-A446-4C28E507FE8C}
DEFINE_GUID(IID_IEMSDataSink2, 0x6fbd1f04, 0xc2d6, 0x4830, 0xa4, 0x46, 0x4c, 0x28, 0xe5, 0x7, 0xfe, 0x8c);

// {488E3138-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSSeqStream, 0x488e3138, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {7EC8F653-2B16-4cd2-8EFD-AD03B1FC250B}
DEFINE_GUID(IID_IEMSTextSeqStream, 0x7ec8f653, 0x2b16, 0x4cd2, 0x8e, 0xfd, 0xad, 0x3, 0xb1, 0xfc, 0x25, 0xb);

// {488E3139-7AD3-11d5-8BFD-009027912866}
DEFINE_GUID( IID_IEMSPacketStream, 0x488e3139, 0x7ad3, 0x11d5, 0x8b, 0xfd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

// {0DC244FB-AE01-4c9f-BE6A-B3CC71C26B49}
DEFINE_GUID( IID_IEMSCommandChannel2, 0xdc244fb, 0xae01, 0x4c9f, 0xbe, 0x6a, 0xb3, 0xcc, 0x71, 0xc2, 0x6b, 0x49);

// {138E91E8-2D48-4190-9E63-FA19C90048C4}
DEFINE_GUID(IID_IEMSRandomStream, 0x138e91e8, 0x2d48, 0x4190, 0x9e, 0x63, 0xfa, 0x19, 0xc9, 0x0, 0x48, 0xc4);

/*********************************************************************
*	Defines
*********************************************************************/

/* Flags */
#define EMS_PIPE_FIXED_LENGTH			(0x00000001)
#define EMS_PIPE_VARIABLE_LENGTH		(0x00000002)
#define EMS_PIPE_WAIT_WRITE			(0x00010000)
#define EMS_PIPE_SUB_SINKS				(0x01000000)
#define EMS_PIPE_IS_FULL				(0x02000000)
#define EMS_PIPE_DEFAULT_FLAGS		(0x10000000)
#define EMS_PIPE_DEFAULT_MAXLENGTH	(0x20000000)
#define EMS_PIPE_DEFAULT_MAXSINKS	(0x40000000)
#define EMS_PIPE_DEFAULT_MAXSOURCES	(0x80000000)
#define EMS_PIPE_COMMAND_CHANNEL	(0xFF)
#define EMS_PIPE_DEBUG_CHANNEL	(0xFE)
#define EMS_PIPE_MAX_COMMAND_LENGTH	(256)

/* Info Flags */
#define EMS_PIPE_INFO_LOGGING_ON		(0x00000001)

/* Command Connect Status Flags */
#define EMS_PIPE_STATUS_CONNECTED (0x80000000)
#define EMS_PIPE_STATUS_READY		 (0x00000001)


extern RPC_IF_HANDLE __MIDL_itf_EMSPIPE_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSPIPE_0000_v0_0_s_ifspec;

#ifndef __IEMSSeqStream_INTERFACE_DEFINED__
#define __IEMSSeqStream_INTERFACE_DEFINED__

/* interface IEMSSeqStream */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSSeqStream __RPC_FAR *LPEMSSEQSTREAM;


EXTERN_C const IID IID_IEMSSeqStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3138-7AD3-11d5-8BFD-009027912866")
    IEMSSeqStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Read( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Write( 
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSeqStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSeqStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSeqStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSeqStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IEMSSeqStream __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IEMSSeqStream __RPC_FAR * This,
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        END_INTERFACE
    } IEMSSeqStreamVtbl;

    interface IEMSSeqStream
    {
        CONST_VTBL struct IEMSSeqStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSeqStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSeqStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSeqStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSeqStream_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define IEMSSeqStream_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSeqStream_Read_Proxy( 
    IEMSSeqStream __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSeqStream_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSeqStream_Write_Proxy( 
    IEMSSeqStream __RPC_FAR * This,
    /* [size_is][in] */ const BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbWritten);


void __RPC_STUB IEMSSeqStream_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSeqStream_INTERFACE_DEFINED__ */


#ifndef __IEMSPacketStream_INTERFACE_DEFINED__
#define __IEMSPacketStream_INTERFACE_DEFINED__

/* interface IEMSPacketStream */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSPacketStream __RPC_FAR *LPEMSPACKETSTREAM;


EXTERN_C const IID IID_IEMSPacketStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3139-7AD3-11d5-8BFD-009027912866")
    IEMSPacketStream : public IEMSSeqStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetType( 
            /* [in] */ BYTE cDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [out] */ BYTE __RPC_FAR *lpcDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxLength( 
            /* [in] */ INT nMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxLength( 
            /* [out] */ INT __RPC_FAR *lpnMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [out] */ DWORD __RPC_FAR *lpdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPacketStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPacketStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPacketStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFlags )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IEMSPacketStream __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        END_INTERFACE
    } IEMSPacketStreamVtbl;

    interface IEMSPacketStream
    {
        CONST_VTBL struct IEMSPacketStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPacketStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPacketStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPacketStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPacketStream_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define IEMSPacketStream_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define IEMSPacketStream_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSPacketStream_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSPacketStream_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSPacketStream_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSPacketStream_SetFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,dwFlags)

#define IEMSPacketStream_GetFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,lpdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPacketStream_SetType_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [in] */ BYTE cDataType);


void __RPC_STUB IEMSPacketStream_SetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPacketStream_GetType_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpcDataType);


void __RPC_STUB IEMSPacketStream_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPacketStream_SetMaxLength_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [in] */ INT nMaxLength);


void __RPC_STUB IEMSPacketStream_SetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPacketStream_GetMaxLength_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *lpnMaxLength);


void __RPC_STUB IEMSPacketStream_GetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPacketStream_SetFlags_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSPacketStream_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPacketStream_GetFlags_Proxy( 
    IEMSPacketStream __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSPacketStream_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPacketStream_INTERFACE_DEFINED__ */


#ifndef __IEMSRandomStream_INTERFACE_DEFINED__
#define __IEMSRandomStream_INTERFACE_DEFINED__

/* interface IEMSRandomStream */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSRandomStream __RPC_FAR *LPEMSRANDOMSTREAM;


EXTERN_C const IID IID_IEMSRandomStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("138E91E8-2D48-4190-9E63-FA19C90048C4")
    IEMSRandomStream : public IEMSSeqStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MoveFirst( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MoveLast( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Move( 
            /* [in] */ const long clIndex) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRandomStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRandomStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRandomStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRandomStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IEMSRandomStream __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IEMSRandomStream __RPC_FAR * This,
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveFirst )( 
            IEMSRandomStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MoveLast )( 
            IEMSRandomStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Move )( 
            IEMSRandomStream __RPC_FAR * This,
            /* [in] */ const long clIndex);
        
        END_INTERFACE
    } IEMSRandomStreamVtbl;

    interface IEMSRandomStream
    {
        CONST_VTBL struct IEMSRandomStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRandomStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRandomStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRandomStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRandomStream_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define IEMSRandomStream_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define IEMSRandomStream_MoveFirst(This)	\
    (This)->lpVtbl -> MoveFirst(This)

#define IEMSRandomStream_MoveLast(This)	\
    (This)->lpVtbl -> MoveLast(This)

#define IEMSRandomStream_Move(This,clIndex)	\
    (This)->lpVtbl -> Move(This,clIndex)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRandomStream_MoveFirst_Proxy( 
    IEMSRandomStream __RPC_FAR * This);


void __RPC_STUB IEMSRandomStream_MoveFirst_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSRandomStream_MoveLast_Proxy( 
    IEMSRandomStream __RPC_FAR * This);


void __RPC_STUB IEMSRandomStream_MoveLast_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSRandomStream_Move_Proxy( 
    IEMSRandomStream __RPC_FAR * This,
    /* [in] */ const long clIndex);


void __RPC_STUB IEMSRandomStream_Move_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRandomStream_INTERFACE_DEFINED__ */


#ifndef __IEMSTextSeqStream_INTERFACE_DEFINED__
#define __IEMSTextSeqStream_INTERFACE_DEFINED__

/* interface IEMSTextSeqStream */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSTextSeqStream __RPC_FAR *LPEMSTEXTSEQSTREAM;


EXTERN_C const IID IID_IEMSTextSeqStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7EC8F653-2B16-4cd2-8EFD-AD03B1FC250B")
    IEMSTextSeqStream : public IEMSSeqStream
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ReadLine( 
            /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *ppwszLine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE WriteLine( 
            /* [string][in] */ wchar_t __RPC_FAR *pwszLine) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTextSeqStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTextSeqStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTextSeqStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTextSeqStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IEMSTextSeqStream __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IEMSTextSeqStream __RPC_FAR * This,
            /* [size_is][in] */ const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbWritten);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadLine )( 
            IEMSTextSeqStream __RPC_FAR * This,
            /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *ppwszLine);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *WriteLine )( 
            IEMSTextSeqStream __RPC_FAR * This,
            /* [string][in] */ wchar_t __RPC_FAR *pwszLine);
        
        END_INTERFACE
    } IEMSTextSeqStreamVtbl;

    interface IEMSTextSeqStream
    {
        CONST_VTBL struct IEMSTextSeqStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTextSeqStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTextSeqStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTextSeqStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTextSeqStream_Read(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> Read(This,pv,cb,pcbRead)

#define IEMSTextSeqStream_Write(This,pv,cb,pcbWritten)	\
    (This)->lpVtbl -> Write(This,pv,cb,pcbWritten)


#define IEMSTextSeqStream_ReadLine(This,ppwszLine)	\
    (This)->lpVtbl -> ReadLine(This,ppwszLine)

#define IEMSTextSeqStream_WriteLine(This,pwszLine)	\
    (This)->lpVtbl -> WriteLine(This,pwszLine)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTextSeqStream_ReadLine_Proxy( 
    IEMSTextSeqStream __RPC_FAR * This,
    /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *ppwszLine);


void __RPC_STUB IEMSTextSeqStream_ReadLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTextSeqStream_WriteLine_Proxy( 
    IEMSTextSeqStream __RPC_FAR * This,
    /* [string][in] */ wchar_t __RPC_FAR *pwszLine);


void __RPC_STUB IEMSTextSeqStream_WriteLine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTextSeqStream_INTERFACE_DEFINED__ */


#ifndef __IEMSDataSource_INTERFACE_DEFINED__
#define __IEMSDataSource_INTERFACE_DEFINED__

/* interface IEMSDataSource */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataSource __RPC_FAR *LPEMSDATASOURCE;


EXTERN_C const IID IID_IEMSDataSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3136-7AD3-11d5-8BFD-009027912866")
    IEMSDataSource : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetType( 
            /* [in] */ BYTE cDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [out] */ BYTE __RPC_FAR *lpcDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxLength( 
            /* [out] */ INT __RPC_FAR *lpnMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxLength( 
            /* [in] */ INT nMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStream( 
            /* [in] */ LPEMSPACKETSTREAM lpStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStream( 
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSDataSource __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSDataSource __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSDataSource __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSDataSource __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStream )( 
            IEMSDataSource __RPC_FAR * This,
            /* [in] */ LPEMSPACKETSTREAM lpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStream )( 
            IEMSDataSource __RPC_FAR * This,
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);
        
        END_INTERFACE
    } IEMSDataSourceVtbl;

    interface IEMSDataSource
    {
        CONST_VTBL struct IEMSDataSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataSource_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSDataSource_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSDataSource_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSDataSource_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSDataSource_SetStream(This,lpStream)	\
    (This)->lpVtbl -> SetStream(This,lpStream)

#define IEMSDataSource_GetStream(This,lplpStream)	\
    (This)->lpVtbl -> GetStream(This,lplpStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataSource_SetType_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [in] */ BYTE cDataType);


void __RPC_STUB IEMSDataSource_SetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSource_GetType_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpcDataType);


void __RPC_STUB IEMSDataSource_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSource_GetMaxLength_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *lpnMaxLength);


void __RPC_STUB IEMSDataSource_GetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSource_SetMaxLength_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [in] */ INT nMaxLength);


void __RPC_STUB IEMSDataSource_SetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSource_SetStream_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [in] */ LPEMSPACKETSTREAM lpStream);


void __RPC_STUB IEMSDataSource_SetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSource_GetStream_Proxy( 
    IEMSDataSource __RPC_FAR * This,
    /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);


void __RPC_STUB IEMSDataSource_GetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataSource_INTERFACE_DEFINED__ */


#ifndef __IEMSDataSink_INTERFACE_DEFINED__
#define __IEMSDataSink_INTERFACE_DEFINED__

/* interface IEMSDataSink */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataSink __RPC_FAR *LPEMSDATASINK;


EXTERN_C const IID IID_IEMSDataSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3137-7AD3-11d5-8BFD-009027912866")
    IEMSDataSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetType( 
            /* [in] */ BYTE cDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetType( 
            /* [out] */ BYTE __RPC_FAR *lpcDataType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxLength( 
            /* [in] */ INT nMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxLength( 
            /* [out] */ INT __RPC_FAR *lpnMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetStream( 
            /* [in] */ LPEMSPACKETSTREAM lpStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetStream( 
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE OnDataAvailable( 
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSDataSink __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSDataSink __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSDataSink __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSDataSink __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStream )( 
            IEMSDataSink __RPC_FAR * This,
            /* [in] */ LPEMSPACKETSTREAM lpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStream )( 
            IEMSDataSink __RPC_FAR * This,
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDataAvailable )( 
            IEMSDataSink __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEMSDataSinkVtbl;

    interface IEMSDataSink
    {
        CONST_VTBL struct IEMSDataSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataSink_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSDataSink_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSDataSink_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSDataSink_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSDataSink_SetStream(This,lpStream)	\
    (This)->lpVtbl -> SetStream(This,lpStream)

#define IEMSDataSink_GetStream(This,lplpStream)	\
    (This)->lpVtbl -> GetStream(This,lplpStream)

#define IEMSDataSink_OnDataAvailable(This,dwSize,dwFlags)	\
    (This)->lpVtbl -> OnDataAvailable(This,dwSize,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataSink_SetType_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [in] */ BYTE cDataType);


void __RPC_STUB IEMSDataSink_SetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_GetType_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpcDataType);


void __RPC_STUB IEMSDataSink_GetType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_SetMaxLength_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [in] */ INT nMaxLength);


void __RPC_STUB IEMSDataSink_SetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_GetMaxLength_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [out] */ INT __RPC_FAR *lpnMaxLength);


void __RPC_STUB IEMSDataSink_GetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_SetStream_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [in] */ LPEMSPACKETSTREAM lpStream);


void __RPC_STUB IEMSDataSink_SetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_GetStream_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);


void __RPC_STUB IEMSDataSink_GetStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink_OnDataAvailable_Proxy( 
    IEMSDataSink __RPC_FAR * This,
    /* [in] */ DWORD dwSize,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSDataSink_OnDataAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataSink_INTERFACE_DEFINED__ */


#ifndef __IEMSDataSink2_INTERFACE_DEFINED__
#define __IEMSDataSink2_INTERFACE_DEFINED__

/* interface IEMSDataSink2 */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataSink2 __RPC_FAR *LPEMSDATASINK2;


EXTERN_C const IID IID_IEMSDataSink2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FBD1F04-C2D6-4830-A446-4C28E507FE8C")
    IEMSDataSink2 : public IEMSDataSink
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetReceivingProcessID( 
            /* [in] */ const DWORD cdwProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetReceivingProcessID( 
            /* [out] */ DWORD __RPC_FAR *pdwProcessID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataSink2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataSink2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataSink2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStream )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ LPEMSPACKETSTREAM lpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStream )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDataAvailable )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetReceivingProcessID )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [in] */ const DWORD cdwProcessID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReceivingProcessID )( 
            IEMSDataSink2 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *pdwProcessID);
        
        END_INTERFACE
    } IEMSDataSink2Vtbl;

    interface IEMSDataSink2
    {
        CONST_VTBL struct IEMSDataSink2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataSink2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataSink2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataSink2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataSink2_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSDataSink2_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSDataSink2_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSDataSink2_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSDataSink2_SetStream(This,lpStream)	\
    (This)->lpVtbl -> SetStream(This,lpStream)

#define IEMSDataSink2_GetStream(This,lplpStream)	\
    (This)->lpVtbl -> GetStream(This,lplpStream)

#define IEMSDataSink2_OnDataAvailable(This,dwSize,dwFlags)	\
    (This)->lpVtbl -> OnDataAvailable(This,dwSize,dwFlags)


#define IEMSDataSink2_SetReceivingProcessID(This,cdwProcessID)	\
    (This)->lpVtbl -> SetReceivingProcessID(This,cdwProcessID)

#define IEMSDataSink2_GetReceivingProcessID(This,pdwProcessID)	\
    (This)->lpVtbl -> GetReceivingProcessID(This,pdwProcessID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataSink2_SetReceivingProcessID_Proxy( 
    IEMSDataSink2 __RPC_FAR * This,
    /* [in] */ const DWORD cdwProcessID);


void __RPC_STUB IEMSDataSink2_SetReceivingProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataSink2_GetReceivingProcessID_Proxy( 
    IEMSDataSink2 __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *pdwProcessID);


void __RPC_STUB IEMSDataSink2_GetReceivingProcessID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataSink2_INTERFACE_DEFINED__ */


#ifndef __IEMSDataPipeline_INTERFACE_DEFINED__
#define __IEMSDataPipeline_INTERFACE_DEFINED__

/* interface IEMSDataPipeline */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataPipeline __RPC_FAR *LPEMSDATAPIPELINE;

typedef struct  _tagEMSDATACHANNELINFO
    {
    BOOL bValidChannel;
    WORD wMaxSinks;
    WORD wSinks;
    WORD wMaxSources;
    WORD wSources;
    WORD wMaxBuffers;
    WORD wHighBuffers;
    WORD wLowBuffers;
    DWORD dwMaxLength;
    DWORD dwFlags;
    HRESULT errLatest;
    }	EMSDATACHANNELINFO;

typedef struct _tagEMSDATACHANNELINFO __RPC_FAR *LPEMSDATACHANNELINFO;


EXTERN_C const IID IID_IEMSDataPipeline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3133-7AD3-11d5-8BFD-009027912866")
    IEMSDataPipeline : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetInfo( 
            /* [in] */ DWORD dwInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetInfo( 
            /* [out] */ DWORD __RPC_FAR *lpdwInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetChannelInfo( 
            /* [in] */ BYTE cType,
            /* [out] */ EMSDATACHANNELINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFlags( 
            /* [in] */ BYTE cType,
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFlags( 
            /* [in] */ BYTE cType,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxLength( 
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxLength( 
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxSinks( 
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSinks) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSinks( 
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSinks) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMaxSources( 
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSources) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSources( 
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSources) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterSink( 
            /* [in] */ LPEMSDATASINK lpSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterSink( 
            /* [in] */ LPEMSDATASINK lpSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterSource( 
            /* [in] */ LPEMSDATASOURCE lpSource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterSource( 
            /* [in] */ LPEMSDATASOURCE lpSource) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataPipelineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataPipeline __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataPipeline __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ DWORD dwInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelInfo )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ EMSDATACHANNELINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFlags )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxSinks )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSinks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSinks )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSinks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxSources )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSources )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSink )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ LPEMSDATASINK lpSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSink )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ LPEMSDATASINK lpSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSource )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ LPEMSDATASOURCE lpSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSource )( 
            IEMSDataPipeline __RPC_FAR * This,
            /* [in] */ LPEMSDATASOURCE lpSource);
        
        END_INTERFACE
    } IEMSDataPipelineVtbl;

    interface IEMSDataPipeline
    {
        CONST_VTBL struct IEMSDataPipelineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataPipeline_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataPipeline_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataPipeline_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataPipeline_SetInfo(This,dwInfo)	\
    (This)->lpVtbl -> SetInfo(This,dwInfo)

#define IEMSDataPipeline_GetInfo(This,lpdwInfo)	\
    (This)->lpVtbl -> GetInfo(This,lpdwInfo)

#define IEMSDataPipeline_GetChannelInfo(This,cType,lpInfo)	\
    (This)->lpVtbl -> GetChannelInfo(This,cType,lpInfo)

#define IEMSDataPipeline_SetFlags(This,cType,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,cType,dwFlags)

#define IEMSDataPipeline_GetFlags(This,cType,lpdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,cType,lpdwFlags)

#define IEMSDataPipeline_SetMaxLength(This,cType,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,cType,nMaxLength)

#define IEMSDataPipeline_GetMaxLength(This,cType,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,cType,lpnMaxLength)

#define IEMSDataPipeline_SetMaxSinks(This,cType,nMaxSinks)	\
    (This)->lpVtbl -> SetMaxSinks(This,cType,nMaxSinks)

#define IEMSDataPipeline_GetMaxSinks(This,cType,lpnMaxSinks)	\
    (This)->lpVtbl -> GetMaxSinks(This,cType,lpnMaxSinks)

#define IEMSDataPipeline_SetMaxSources(This,cType,nMaxSources)	\
    (This)->lpVtbl -> SetMaxSources(This,cType,nMaxSources)

#define IEMSDataPipeline_GetMaxSources(This,cType,lpnMaxSources)	\
    (This)->lpVtbl -> GetMaxSources(This,cType,lpnMaxSources)

#define IEMSDataPipeline_RegisterSink(This,lpSink)	\
    (This)->lpVtbl -> RegisterSink(This,lpSink)

#define IEMSDataPipeline_UnRegisterSink(This,lpSink)	\
    (This)->lpVtbl -> UnRegisterSink(This,lpSink)

#define IEMSDataPipeline_RegisterSource(This,lpSource)	\
    (This)->lpVtbl -> RegisterSource(This,lpSource)

#define IEMSDataPipeline_UnRegisterSource(This,lpSource)	\
    (This)->lpVtbl -> UnRegisterSource(This,lpSource)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataPipeline_SetInfo_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ DWORD dwInfo);


void __RPC_STUB IEMSDataPipeline_SetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetInfo_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *lpdwInfo);


void __RPC_STUB IEMSDataPipeline_GetInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetChannelInfo_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [out] */ EMSDATACHANNELINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSDataPipeline_GetChannelInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_SetFlags_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSDataPipeline_SetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetFlags_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [out] */ DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSDataPipeline_GetFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_SetMaxLength_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [in] */ INT nMaxLength);


void __RPC_STUB IEMSDataPipeline_SetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetMaxLength_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [out] */ INT __RPC_FAR *lpnMaxLength);


void __RPC_STUB IEMSDataPipeline_GetMaxLength_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_SetMaxSinks_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [in] */ INT nMaxSinks);


void __RPC_STUB IEMSDataPipeline_SetMaxSinks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetMaxSinks_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [out] */ INT __RPC_FAR *lpnMaxSinks);


void __RPC_STUB IEMSDataPipeline_GetMaxSinks_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_SetMaxSources_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [in] */ INT nMaxSources);


void __RPC_STUB IEMSDataPipeline_SetMaxSources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_GetMaxSources_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ BYTE cType,
    /* [out] */ INT __RPC_FAR *lpnMaxSources);


void __RPC_STUB IEMSDataPipeline_GetMaxSources_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_RegisterSink_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ LPEMSDATASINK lpSink);


void __RPC_STUB IEMSDataPipeline_RegisterSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_UnRegisterSink_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ LPEMSDATASINK lpSink);


void __RPC_STUB IEMSDataPipeline_UnRegisterSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_RegisterSource_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ LPEMSDATASOURCE lpSource);


void __RPC_STUB IEMSDataPipeline_RegisterSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDataPipeline_UnRegisterSource_Proxy( 
    IEMSDataPipeline __RPC_FAR * This,
    /* [in] */ LPEMSDATASOURCE lpSource);


void __RPC_STUB IEMSDataPipeline_UnRegisterSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataPipeline_INTERFACE_DEFINED__ */


#ifndef __IEMSDataPipeline2_INTERFACE_DEFINED__
#define __IEMSDataPipeline2_INTERFACE_DEFINED__

/* interface IEMSDataPipeline2 */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSDataPipeline2 __RPC_FAR *LPEMSDATAPIPELINE2;


EXTERN_C const IID IID_IEMSDataPipeline2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5F414595-AB0A-4880-9351-3D9700A9B1DD")
    IEMSDataPipeline2 : public IEMSDataPipeline
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetOverflowOrder( 
            /* [in] */ const BYTE cType,
            /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *pwszOrder) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataPipeline2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataPipeline2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataPipeline2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetInfo )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ DWORD dwInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetInfo )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelInfo )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ EMSDATACHANNELINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFlags )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFlags )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxSinks )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSinks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSinks )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSinks);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxSources )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [in] */ INT nMaxSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSources )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ BYTE cType,
            /* [out] */ INT __RPC_FAR *lpnMaxSources);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSink )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ LPEMSDATASINK lpSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSink )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ LPEMSDATASINK lpSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSource )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ LPEMSDATASOURCE lpSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSource )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ LPEMSDATASOURCE lpSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOverflowOrder )( 
            IEMSDataPipeline2 __RPC_FAR * This,
            /* [in] */ const BYTE cType,
            /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *pwszOrder);
        
        END_INTERFACE
    } IEMSDataPipeline2Vtbl;

    interface IEMSDataPipeline2
    {
        CONST_VTBL struct IEMSDataPipeline2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataPipeline2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataPipeline2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataPipeline2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataPipeline2_SetInfo(This,dwInfo)	\
    (This)->lpVtbl -> SetInfo(This,dwInfo)

#define IEMSDataPipeline2_GetInfo(This,lpdwInfo)	\
    (This)->lpVtbl -> GetInfo(This,lpdwInfo)

#define IEMSDataPipeline2_GetChannelInfo(This,cType,lpInfo)	\
    (This)->lpVtbl -> GetChannelInfo(This,cType,lpInfo)

#define IEMSDataPipeline2_SetFlags(This,cType,dwFlags)	\
    (This)->lpVtbl -> SetFlags(This,cType,dwFlags)

#define IEMSDataPipeline2_GetFlags(This,cType,lpdwFlags)	\
    (This)->lpVtbl -> GetFlags(This,cType,lpdwFlags)

#define IEMSDataPipeline2_SetMaxLength(This,cType,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,cType,nMaxLength)

#define IEMSDataPipeline2_GetMaxLength(This,cType,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,cType,lpnMaxLength)

#define IEMSDataPipeline2_SetMaxSinks(This,cType,nMaxSinks)	\
    (This)->lpVtbl -> SetMaxSinks(This,cType,nMaxSinks)

#define IEMSDataPipeline2_GetMaxSinks(This,cType,lpnMaxSinks)	\
    (This)->lpVtbl -> GetMaxSinks(This,cType,lpnMaxSinks)

#define IEMSDataPipeline2_SetMaxSources(This,cType,nMaxSources)	\
    (This)->lpVtbl -> SetMaxSources(This,cType,nMaxSources)

#define IEMSDataPipeline2_GetMaxSources(This,cType,lpnMaxSources)	\
    (This)->lpVtbl -> GetMaxSources(This,cType,lpnMaxSources)

#define IEMSDataPipeline2_RegisterSink(This,lpSink)	\
    (This)->lpVtbl -> RegisterSink(This,lpSink)

#define IEMSDataPipeline2_UnRegisterSink(This,lpSink)	\
    (This)->lpVtbl -> UnRegisterSink(This,lpSink)

#define IEMSDataPipeline2_RegisterSource(This,lpSource)	\
    (This)->lpVtbl -> RegisterSource(This,lpSource)

#define IEMSDataPipeline2_UnRegisterSource(This,lpSource)	\
    (This)->lpVtbl -> UnRegisterSource(This,lpSource)


#define IEMSDataPipeline2_GetOverflowOrder(This,cType,pwszOrder)	\
    (This)->lpVtbl -> GetOverflowOrder(This,cType,pwszOrder)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataPipeline2_GetOverflowOrder_Proxy( 
    IEMSDataPipeline2 __RPC_FAR * This,
    /* [in] */ const BYTE cType,
    /* [string][out] */ wchar_t __RPC_FAR *__RPC_FAR *pwszOrder);


void __RPC_STUB IEMSDataPipeline2_GetOverflowOrder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataPipeline2_INTERFACE_DEFINED__ */


#ifndef __IEMSCommandSource_INTERFACE_DEFINED__
#define __IEMSCommandSource_INTERFACE_DEFINED__

/* interface IEMSCommandSource */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSCommandSource __RPC_FAR *LPEMSCOMMANDSOURCE;


EXTERN_C const IID IID_IEMSCommandSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3134-7AD3-11d5-8BFD-009027912866")
    IEMSCommandSource : public IEMSDataSource
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCmdType( 
            /* [in] */ BYTE cCmdType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCmdType( 
            /* [out] */ BYTE __RPC_FAR *lpcCmdType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommandSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommandSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommandSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStream )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [in] */ LPEMSPACKETSTREAM lpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStream )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCmdType )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [in] */ BYTE cCmdType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCmdType )( 
            IEMSCommandSource __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcCmdType);
        
        END_INTERFACE
    } IEMSCommandSourceVtbl;

    interface IEMSCommandSource
    {
        CONST_VTBL struct IEMSCommandSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommandSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommandSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommandSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCommandSource_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSCommandSource_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSCommandSource_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSCommandSource_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSCommandSource_SetStream(This,lpStream)	\
    (This)->lpVtbl -> SetStream(This,lpStream)

#define IEMSCommandSource_GetStream(This,lplpStream)	\
    (This)->lpVtbl -> GetStream(This,lplpStream)


#define IEMSCommandSource_SetCmdType(This,cCmdType)	\
    (This)->lpVtbl -> SetCmdType(This,cCmdType)

#define IEMSCommandSource_GetCmdType(This,lpcCmdType)	\
    (This)->lpVtbl -> GetCmdType(This,lpcCmdType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommandSource_SetCmdType_Proxy( 
    IEMSCommandSource __RPC_FAR * This,
    /* [in] */ BYTE cCmdType);


void __RPC_STUB IEMSCommandSource_SetCmdType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandSource_GetCmdType_Proxy( 
    IEMSCommandSource __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpcCmdType);


void __RPC_STUB IEMSCommandSource_GetCmdType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommandSource_INTERFACE_DEFINED__ */


#ifndef __IEMSCommandSink_INTERFACE_DEFINED__
#define __IEMSCommandSink_INTERFACE_DEFINED__

/* interface IEMSCommandSink */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSCommandSink __RPC_FAR *LPEMSCOMMANDSINK;


EXTERN_C const IID IID_IEMSCommandSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3135-7AD3-11d5-8BFD-009027912866")
    IEMSCommandSink : public IEMSDataSink
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetCmdType( 
            /* [in] */ BYTE cCmdType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCmdType( 
            /* [out] */ BYTE __RPC_FAR *lpcCmdType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommandSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommandSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommandSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetType )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ BYTE cDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetType )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcDataType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMaxLength )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ INT nMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxLength )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [out] */ INT __RPC_FAR *lpnMaxLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetStream )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ LPEMSPACKETSTREAM lpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetStream )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [out] */ LPEMSPACKETSTREAM __RPC_FAR *lplpStream);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDataAvailable )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ DWORD dwSize,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCmdType )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [in] */ BYTE cCmdType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCmdType )( 
            IEMSCommandSink __RPC_FAR * This,
            /* [out] */ BYTE __RPC_FAR *lpcCmdType);
        
        END_INTERFACE
    } IEMSCommandSinkVtbl;

    interface IEMSCommandSink
    {
        CONST_VTBL struct IEMSCommandSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommandSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommandSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommandSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCommandSink_SetType(This,cDataType)	\
    (This)->lpVtbl -> SetType(This,cDataType)

#define IEMSCommandSink_GetType(This,lpcDataType)	\
    (This)->lpVtbl -> GetType(This,lpcDataType)

#define IEMSCommandSink_SetMaxLength(This,nMaxLength)	\
    (This)->lpVtbl -> SetMaxLength(This,nMaxLength)

#define IEMSCommandSink_GetMaxLength(This,lpnMaxLength)	\
    (This)->lpVtbl -> GetMaxLength(This,lpnMaxLength)

#define IEMSCommandSink_SetStream(This,lpStream)	\
    (This)->lpVtbl -> SetStream(This,lpStream)

#define IEMSCommandSink_GetStream(This,lplpStream)	\
    (This)->lpVtbl -> GetStream(This,lplpStream)

#define IEMSCommandSink_OnDataAvailable(This,dwSize,dwFlags)	\
    (This)->lpVtbl -> OnDataAvailable(This,dwSize,dwFlags)


#define IEMSCommandSink_SetCmdType(This,cCmdType)	\
    (This)->lpVtbl -> SetCmdType(This,cCmdType)

#define IEMSCommandSink_GetCmdType(This,lpcCmdType)	\
    (This)->lpVtbl -> GetCmdType(This,lpcCmdType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommandSink_SetCmdType_Proxy( 
    IEMSCommandSink __RPC_FAR * This,
    /* [in] */ BYTE cCmdType);


void __RPC_STUB IEMSCommandSink_SetCmdType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandSink_GetCmdType_Proxy( 
    IEMSCommandSink __RPC_FAR * This,
    /* [out] */ BYTE __RPC_FAR *lpcCmdType);


void __RPC_STUB IEMSCommandSink_GetCmdType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommandSink_INTERFACE_DEFINED__ */


#ifndef __IEMSCommandChannel_INTERFACE_DEFINED__
#define __IEMSCommandChannel_INTERFACE_DEFINED__

/* interface IEMSCommandChannel */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSCommandChannel __RPC_FAR *LPEMSCOMMANDCHANNEL;


EXTERN_C const IID IID_IEMSCommandChannel;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("488E3132-7AD3-11d5-8BFD-009027912866")
    IEMSCommandChannel : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RegisterSource( 
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterSource( 
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RegisterSink( 
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnRegisterSink( 
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommandChannelVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommandChannel __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommandChannel __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommandChannel __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSource )( 
            IEMSCommandChannel __RPC_FAR * This,
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSource )( 
            IEMSCommandChannel __RPC_FAR * This,
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSink )( 
            IEMSCommandChannel __RPC_FAR * This,
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSink )( 
            IEMSCommandChannel __RPC_FAR * This,
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);
        
        END_INTERFACE
    } IEMSCommandChannelVtbl;

    interface IEMSCommandChannel
    {
        CONST_VTBL struct IEMSCommandChannelVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommandChannel_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommandChannel_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommandChannel_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCommandChannel_RegisterSource(This,lpCmdSource)	\
    (This)->lpVtbl -> RegisterSource(This,lpCmdSource)

#define IEMSCommandChannel_UnRegisterSource(This,lpCmdSource)	\
    (This)->lpVtbl -> UnRegisterSource(This,lpCmdSource)

#define IEMSCommandChannel_RegisterSink(This,lpCmdSink)	\
    (This)->lpVtbl -> RegisterSink(This,lpCmdSink)

#define IEMSCommandChannel_UnRegisterSink(This,lpCmdSink)	\
    (This)->lpVtbl -> UnRegisterSink(This,lpCmdSink)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommandChannel_RegisterSource_Proxy( 
    IEMSCommandChannel __RPC_FAR * This,
    /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);


void __RPC_STUB IEMSCommandChannel_RegisterSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandChannel_UnRegisterSource_Proxy( 
    IEMSCommandChannel __RPC_FAR * This,
    /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);


void __RPC_STUB IEMSCommandChannel_UnRegisterSource_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandChannel_RegisterSink_Proxy( 
    IEMSCommandChannel __RPC_FAR * This,
    /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);


void __RPC_STUB IEMSCommandChannel_RegisterSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandChannel_UnRegisterSink_Proxy( 
    IEMSCommandChannel __RPC_FAR * This,
    /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);


void __RPC_STUB IEMSCommandChannel_UnRegisterSink_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommandChannel_INTERFACE_DEFINED__ */


#ifndef __IEMSCommandChannel2_INTERFACE_DEFINED__
#define __IEMSCommandChannel2_INTERFACE_DEFINED__

/* interface IEMSCommandChannel2 */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSCommandChannel2 __RPC_FAR *LPEMSCOMMANDCHANNEL2;


EXTERN_C const IID IID_IEMSCommandChannel2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0DC244FB-AE01-4c9f-BE6A-B3CC71C26B49")
    IEMSCommandChannel2 : public IEMSCommandChannel
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetConnectStatus( 
            /* [in] */ BYTE cCmdChannel,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConnectStatus( 
            /* [in] */ BYTE cCmdChannel,
            /* [in] */ DWORD dwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommandChannel2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommandChannel2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommandChannel2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSource )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSource )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ IEMSCommandSource __RPC_FAR *lpCmdSource);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RegisterSink )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnRegisterSink )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ IEMSCommandSink __RPC_FAR *lpCmdSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnectStatus )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ BYTE cCmdChannel,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConnectStatus )( 
            IEMSCommandChannel2 __RPC_FAR * This,
            /* [in] */ BYTE cCmdChannel,
            /* [in] */ DWORD dwFlags);
        
        END_INTERFACE
    } IEMSCommandChannel2Vtbl;

    interface IEMSCommandChannel2
    {
        CONST_VTBL struct IEMSCommandChannel2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommandChannel2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommandChannel2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommandChannel2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCommandChannel2_RegisterSource(This,lpCmdSource)	\
    (This)->lpVtbl -> RegisterSource(This,lpCmdSource)

#define IEMSCommandChannel2_UnRegisterSource(This,lpCmdSource)	\
    (This)->lpVtbl -> UnRegisterSource(This,lpCmdSource)

#define IEMSCommandChannel2_RegisterSink(This,lpCmdSink)	\
    (This)->lpVtbl -> RegisterSink(This,lpCmdSink)

#define IEMSCommandChannel2_UnRegisterSink(This,lpCmdSink)	\
    (This)->lpVtbl -> UnRegisterSink(This,lpCmdSink)


#define IEMSCommandChannel2_GetConnectStatus(This,cCmdChannel,lpdwFlags)	\
    (This)->lpVtbl -> GetConnectStatus(This,cCmdChannel,lpdwFlags)

#define IEMSCommandChannel2_SetConnectStatus(This,cCmdChannel,dwFlags)	\
    (This)->lpVtbl -> SetConnectStatus(This,cCmdChannel,dwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommandChannel2_GetConnectStatus_Proxy( 
    IEMSCommandChannel2 __RPC_FAR * This,
    /* [in] */ BYTE cCmdChannel,
    /* [out] */ DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSCommandChannel2_GetConnectStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommandChannel2_SetConnectStatus_Proxy( 
    IEMSCommandChannel2 __RPC_FAR * This,
    /* [in] */ BYTE cCmdChannel,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSCommandChannel2_SetConnectStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommandChannel2_INTERFACE_DEFINED__ */



#ifndef __EMSDataPipelineLib_LIBRARY_DEFINED__
#define __EMSDataPipelineLib_LIBRARY_DEFINED__

/* library EMSDataPipelineLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSDataPipelineLib;

EXTERN_C const CLSID CLSID_EMSDataPipeline;

#ifdef __cplusplus

class DECLSPEC_UUID("488E3131-7AD3-11d5-8BFD-009027912866")
EMSDataPipeline;
#endif
#endif /* __EMSDataPipelineLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
