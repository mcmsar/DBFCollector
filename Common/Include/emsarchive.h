/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Jan 04 18:11:12 2003
 */
/* Compiler settings for emsarchive.idl:
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

#ifndef __emsarchive_h__
#define __emsarchive_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMS600ArchiveInfo_FWD_DEFINED__
#define __IEMS600ArchiveInfo_FWD_DEFINED__
typedef interface IEMS600ArchiveInfo IEMS600ArchiveInfo;
#endif 	/* __IEMS600ArchiveInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsarchive_0000 */
/* [local] */ 

// {460AE48B-3652-44ca-9C17-C69ECDF4F84E}
DEFINE_GUID( IID_IEMS600ArchiveInfo, 0x460ae48b, 0x3652, 0x44ca, 0x9c, 0x17, 0xc6, 0x9e, 0xcd, 0xf4, 0xf8, 0x4e);
typedef struct  _tagEMSARCHIVEINFO
    {
    double dRawCBCDataDays;
    double dRaw406DataDays;
    double dSpectrumDataDays;
    double dCalibCBCDataDays;
    double dCalib406DataDays;
    double dStatsDataDays;
    double dAlarmDataDays;
    double dTLEDataDays;
    double dLocationDataDays;
    double dPassDataDays;
    double dPassSchedDays;
    double dCommsDataDays;
    double dLogDataDays;
    double dSensorDataDays;
    double dEnvironDataDays;
    double dCombined406DataDays;
    double dResidualDataDays;
    double dConfigDataDays;
    double dSarpCalibDataDays;
    double dSarrCalibDataDays;
    double dGeoStatsDataDays;
    }	EMSARCHIVEINFO;

typedef struct _tagEMSARCHIVEINFO __RPC_FAR *LPEMSARCHIVEINFO;



extern RPC_IF_HANDLE __MIDL_itf_emsarchive_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsarchive_0000_v0_0_s_ifspec;

#ifndef __IEMS600ArchiveInfo_INTERFACE_DEFINED__
#define __IEMS600ArchiveInfo_INTERFACE_DEFINED__

/* interface IEMS600ArchiveInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMS600ArchiveInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("460AE48B-3652-44ca-9C17-C69ECDF4F84E")
    IEMS600ArchiveInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetArchiveInfo( 
            /* [out] */ EMSARCHIVEINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMS600ArchiveInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMS600ArchiveInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMS600ArchiveInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMS600ArchiveInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetArchiveInfo )( 
            IEMS600ArchiveInfo __RPC_FAR * This,
            /* [out] */ EMSARCHIVEINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMS600ArchiveInfoVtbl;

    interface IEMS600ArchiveInfo
    {
        CONST_VTBL struct IEMS600ArchiveInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMS600ArchiveInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMS600ArchiveInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMS600ArchiveInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMS600ArchiveInfo_GetArchiveInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetArchiveInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMS600ArchiveInfo_GetArchiveInfo_Proxy( 
    IEMS600ArchiveInfo __RPC_FAR * This,
    /* [out] */ EMSARCHIVEINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMS600ArchiveInfo_GetArchiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMS600ArchiveInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsarchive_0008 */
/* [local] */ 

typedef /* [unique] */ IEMS600ArchiveInfo __RPC_FAR *LPEMS600ARCHIVEINFO;



extern RPC_IF_HANDLE __MIDL_itf_emsarchive_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsarchive_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
