/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 10 14:13:56 2004
 */
/* Compiler settings for ..\common\include\ialertgen.idl:
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

#ifndef __ialertgen_h__
#define __ialertgen_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAlertGen_FWD_DEFINED__
#define __IEMSAlertGen_FWD_DEFINED__
typedef interface IEMSAlertGen IEMSAlertGen;
#endif 	/* __IEMSAlertGen_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "EMSTYPEX.h"
#include "locate.h"
#include "emsauthorization.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ialertgen_0000 */
/* [local] */ 

// {FCD595EC-2F09-4a49-8DF5-690D06600997}
DEFINE_GUID( CLSID_EMSAlertGen, 0xfcd595ec, 0x2f09, 0x4a49, 0x8d, 0xf5, 0x69, 0xd, 0x6, 0x60, 0x9, 0x97 );

// {81577DE2-6F2A-4a74-99B0-DB9740D6ADED}
DEFINE_GUID( IID_IEMSAlertGen, 0x81577de2, 0x6f2a, 0x4a74, 0x99, 0xb0, 0xdb, 0x97, 0x40, 0xd6, 0xad, 0xed );
#define	MAX_DESTINATIONS	( 32 )

typedef struct  _tagEMSLocateEx
    {
    EMSLOCATE locate;
    DWORD dwFlags;
    ULONG ulNumDestinations;
    ULONG aulDestinations[ 32 ];
    /* [string] */ unsigned char szUserID[ 21 ];
    }	EMSLOCATEEX;

#define	EMSLOCATEEX_FLAG_MORE	( 0x1 )

#define	EMSLOCATEEX_FLAG_FIRST	( 0x2 )

#define	EMSLOCATEEX_FLAG_LAST	( 0x4 )

typedef __RPC_FAR EMSLOCATEEX* LPEMSLOCATEEX;



extern RPC_IF_HANDLE __MIDL_itf_ialertgen_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ialertgen_0000_v0_0_s_ifspec;

#ifndef __IEMSAlertGen_INTERFACE_DEFINED__
#define __IEMSAlertGen_INTERFACE_DEFINED__

/* interface IEMSAlertGen */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSAlertGen;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("81577DE2-6F2A-4a74-99B0-DB9740D6ADED")
    IEMSAlertGen : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GenerateAlerts( 
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulNumDestinations,
            /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations,
            /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GenerateSolutionsResponse( 
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertGenVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertGen __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertGen __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertGen __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateAlerts )( 
            IEMSAlertGen __RPC_FAR * This,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulNumDestinations,
            /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations,
            /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateSolutionsResponse )( 
            IEMSAlertGen __RPC_FAR * This,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations);
        
        END_INTERFACE
    } IEMSAlertGenVtbl;

    interface IEMSAlertGen
    {
        CONST_VTBL struct IEMSAlertGenVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertGen_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertGen_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertGen_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertGen_GenerateAlerts(This,ulSourceID,ulNumDestinations,ulDestinationIDs,ulLocations,pLocations,szUserID)	\
    (This)->lpVtbl -> GenerateAlerts(This,ulSourceID,ulNumDestinations,ulDestinationIDs,ulLocations,pLocations,szUserID)

#define IEMSAlertGen_GenerateSolutionsResponse(This,ulSourceID,ulLocations,pLocations)	\
    (This)->lpVtbl -> GenerateSolutionsResponse(This,ulSourceID,ulLocations,pLocations)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertGen_GenerateAlerts_Proxy( 
    IEMSAlertGen __RPC_FAR * This,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulNumDestinations,
    /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
    /* [in] */ ULONG ulLocations,
    /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations,
    /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]);


void __RPC_STUB IEMSAlertGen_GenerateAlerts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlertGen_GenerateSolutionsResponse_Proxy( 
    IEMSAlertGen __RPC_FAR * This,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulLocations,
    /* [size_is][in] */ EMSLOCATE __RPC_FAR *pLocations);


void __RPC_STUB IEMSAlertGen_GenerateSolutionsResponse_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertGen_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ialertgen_0020 */
/* [local] */ 

typedef IEMSAlertGen __RPC_FAR *LPEMSALERTGEN;



extern RPC_IF_HANDLE __MIDL_itf_ialertgen_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ialertgen_0020_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
