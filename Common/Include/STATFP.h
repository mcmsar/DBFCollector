

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Jun 14 17:15:59 2012
 */
/* Compiler settings for C:\SAR\Common\Include\STATFP.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __STATFP_h__
#define __STATFP_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSFPStatus_FWD_DEFINED__
#define __IEMSFPStatus_FWD_DEFINED__
typedef interface IEMSFPStatus IEMSFPStatus;
#endif 	/* __IEMSFPStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_STATFP_0000_0000 */
/* [local] */ 

// {11041DE8-2118-4b0d-BA3D-DFB2BDFACEAC}
DEFINE_GUID( IID_IEMSFPStatus, 0x11041de8, 0x2118, 0x4b0d, 0xba, 0x3d, 0xdf, 0xb2, 0xbd, 0xfa, 0xce, 0xac);
 


extern RPC_IF_HANDLE __MIDL_itf_STATFP_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATFP_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSFPStatus_INTERFACE_DEFINED__
#define __IEMSFPStatus_INTERFACE_DEFINED__

/* interface IEMSFPStatus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSFPStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11041DE8-2118-4b0d-BA3D-DFB2BDFACEAC")
    IEMSFPStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetAntennaID( 
            /* [in] */ const ULONG ulAntennaID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSFPStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSFPStatus * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSFPStatus * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSFPStatus * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetAntennaID )( 
            IEMSFPStatus * This,
            /* [in] */ const ULONG ulAntennaID);
        
        END_INTERFACE
    } IEMSFPStatusVtbl;

    interface IEMSFPStatus
    {
        CONST_VTBL struct IEMSFPStatusVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSFPStatus_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSFPStatus_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSFPStatus_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 



#define IEMSFPStatus_SetAntennaID(This,ulAntennaID)	\
    ( (This)->lpVtbl -> SetAntennaID(This,ulAntennaID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSFPStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATFP_0000_0001 */
/* [local] */ 

typedef /* [unique] */ IEMSFPStatus *LPEMSFPStatus;



extern RPC_IF_HANDLE __MIDL_itf_STATFP_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATFP_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


