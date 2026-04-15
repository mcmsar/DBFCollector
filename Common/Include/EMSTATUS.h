/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 16 11:15:32 2002
 */
/* Compiler settings for EMSTATUS.IDL:
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

#ifndef __EMSTATUS_h__
#define __EMSTATUS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSStatus_FWD_DEFINED__
#define __IEMSStatus_FWD_DEFINED__
typedef interface IEMSStatus IEMSStatus;
#endif 	/* __IEMSStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSTATUS_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {F83F4B74-EA53-11d5-8D21-009027912866}
DEFINE_GUID(CLSID_EMSStatus, 0xf83f4b74, 0xea53, 0x11d5, 0x8d, 0x21, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {F83F4B75-EA53-11d5-8D21-009027912866}
DEFINE_GUID( IID_IEMSStatus, 0xf83f4b75, 0xea53, 0x11d5, 0x8d, 0x21, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);

extern RPC_IF_HANDLE __MIDL_itf_EMSTATUS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSTATUS_0000_v0_0_s_ifspec;

#ifndef __IEMSStatus_INTERFACE_DEFINED__
#define __IEMSStatus_INTERFACE_DEFINED__

/* interface IEMSStatus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F83F4B75-EA53-11d5-8D21-009027912866")
    IEMSStatus : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IEMSStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSStatus __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSStatusVtbl;

    interface IEMSStatus
    {
        CONST_VTBL struct IEMSStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSTATUS_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSStatus __RPC_FAR *LPEMSSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_EMSTATUS_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSTATUS_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
