/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 29 16:20:58 2011
 */
/* Compiler settings for ..\..\common\include\DAL.idl:
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

#ifndef __DAL_h__
#define __DAL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDALVariable_FWD_DEFINED__
#define __IEMSDALVariable_FWD_DEFINED__
typedef interface IEMSDALVariable IEMSDALVariable;
#endif 	/* __IEMSDALVariable_FWD_DEFINED__ */


#ifndef __IEMSDALFixed_FWD_DEFINED__
#define __IEMSDALFixed_FWD_DEFINED__
typedef interface IEMSDALFixed IEMSDALFixed;
#endif 	/* __IEMSDALFixed_FWD_DEFINED__ */


#ifndef __IEMSDALFixed2_FWD_DEFINED__
#define __IEMSDALFixed2_FWD_DEFINED__
typedef interface IEMSDALFixed2 IEMSDALFixed2;
#endif 	/* __IEMSDALFixed2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "leostats.h"
#include "sittypes.h"
#include "calib406.h"
#include "cbcdata.h"
#include "cbcout.h"
#include "combine406.h"
#include "emsicfg.h"
#include "locate.h"
#include "emslog.h"
#include "emstle.h"
#include "residual.h"
#include "sarpcalib.h"
#include "sarpdata.h"
#include "sarrcalib.h"
#include "sarrdata.h"
#include "spectrum.h"
#include "emsaudio.h"
#include "emsalarm.h"
#include "sarrplugin.h"
#include "calib406ext.h"
#include "abldata.h"
#include "healthstatustypes.h"
#include "beaconadvisorytypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_DAL_0000 */
/* [local] */ 

// {F66FA79A-593B-414b-B024-934B3E91FA71}
DEFINE_GUID(IID_IEMSDALVariable, 0xf66fa79a, 0x593b, 0x414b, 0xb0, 0x24, 0x93, 0x4b, 0x3e, 0x91, 0xfa, 0x71);
// {3A891797-49A7-4070-B6B9-9A12437021C2}
DEFINE_GUID(CLSID_EMSDAL, 0x3a891797, 0x49a7, 0x4070, 0xb6, 0xb9, 0x9a, 0x12, 0x43, 0x70, 0x21, 0xc2);
// {803BA197-4A48-4d01-B545-C56F660FDF1F}
DEFINE_GUID(IID_IEMSDALFixed, 0x803ba197, 0x4a48, 0x4d01, 0xb5, 0x45, 0xc5, 0x6f, 0x66, 0xf, 0xdf, 0x1f);
// {228E8452-9AB1-4fb7-AC71-5212CC4ED9AA}
DEFINE_GUID(IID_IEMSDALFixed2, 0x228e8452, 0x9ab1, 0x4fb7, 0xac, 0x71, 0x52, 0x12, 0xcc, 0x4e, 0xd9, 0xaa);
typedef 
enum tagEMSDBFieldType
    {	DBFLDTYPE_UNKNOWN	= 0,
	DBFLDTYPE_SHORT	= 1,
	DBFLDTYPE_USHORT	= 2,
	DBFLDTYPE_LONG	= 3,
	DBFLDTYPE_ULONG	= 4,
	DBFLDTYPE_BIGINT	= 5,
	DBFLDTYPE_UBIGINT	= 6,
	DBFLDTYPE_WSTRING	= 7,
	DBFLDTYPE_STRING	= 8,
	DBFLDTYPE_BINARY	= 9,
	DBFLDTYPE_LONG_BINARY	= 10,
	DBFLDTYPE_FLOAT	= 11,
	DBFLDTYPE_DOUBLE	= 12,
	DBFLDTYPE_TINYINT	= 13,
	DBFLDTYPE_UTINYINT	= 14,
	DBFLDTYPE_BOOLEAN	= 15,
	DBFLDTYPE_DATETIME	= 16,
	DBFLDTYPE_VARCHAR	= 17,
	DBFLDTYPE_CHAR	= 18,
	DBFLDTYPE_LAST	= DBFLDTYPE_CHAR + 1
    }	EMSDBFLDTYPE;

typedef long EMSDALCACHEID;

#define	INITIALDALCACHEID	( 0 )

#define	NULLDALCACHEID	( 0 )

#define	DONTCACHE	( -1 )

typedef struct  tagEMSRetrievalProperties
    {
    unsigned long ulCacheID;
    unsigned long ulMaxRecords;
    unsigned long ulTotalRecords;
    boolean bReturnDescriptor;
    unsigned long ulRecordSize;
    }	EMSRETRIEVALPROPS;

#define MAX_FIELD_NAME 64
typedef struct  tagEMSFieldDescriptor
    {
    EMSDBFLDTYPE eType;
    long lSize;
    wchar_t wszName[ 65 ];
    }	EMSFIELDDESCRIPTOR;

typedef 
enum eEMSRecordType
    {	EMSRT_UNKNOWN	= 0,
	EMSRT_ANTENNA	= 1,
	EMSRT_CALIB406	= 2,
	EMSRT_CALIBCBC	= 3,
	EMSRT_CALIBCBC_STATS	= 4,
	EMSRT_CBC	= 5,
	EMSRT_COLLECTOR	= 6,
	EMSRT_COMB406	= 7,
	EMSRT_COMB406_STATS	= 8,
	EMSRT_COMMS_STATS	= 9,
	EMSRT_CONFIG	= 10,
	EMSRT_GEO_CALIB406_STATS	= 11,
	EMSRT_GEO_STATS	= 12,
	EMSRT_LEO_CALIB406_STATS	= 13,
	EMSRT_LOCATE	= 14,
	EMSRT_LOCATE_STATS	= 15,
	EMSRT_LOG	= 16,
	EMSRT_ORBIT	= 17,
	EMSRT_ORBIT_STATS	= 18,
	EMSRT_PASS_STATS	= 19,
	EMSRT_RESIDUAL	= 20,
	EMSRT_SARP_CALIB	= 21,
	EMSRT_SARP_CALIB_STATS	= 22,
	EMSRT_SARP	= 23,
	EMSRT_SARR_CALIB	= 24,
	EMSRT_SARR_CALIB_STATS	= 25,
	EMSRT_SARR	= 26,
	EMSRT_SAT_TRACK	= 27,
	EMSRT_SENSOR	= 28,
	EMSRT_SPECTRUM	= 29,
	EMSRT_STAT_SUMMARY	= 30,
	EMSRT_WIDEBAND_STATS	= 31,
	EMSRT_AUDIO	= 32,
	EMSRT_MANOEUVRE	= 33,
	EMSRT_SARP_CALIB_124	= 34,
	EMSRT_SARP_CALIB_STATS_124	= 35,
	EMSRT_SARR_124	= 36,
	EMSRT_LOCATE_124	= 37,
	EMSRT_SARR_EXT	= 38,
	EMSRT_CALIB406_EXT	= 39,
	EMSRT_CALIB406_2	= 40,
	EMSRT_LUT_STATUS	= 41,
	EMSRT_ABL_DATA	= 42,
	EMSRT_HEALTH_STATUS	= 43,
	EMSRT_HEALTH_DETECTIONS	= 44,
	EMSRT_BEACON_ADVISORY	= 45,
	EMSRT_LP_STATUS	= 46,
	EMSRT_LAST	= EMSRT_LP_STATUS
    }	EMSRECORDTYPE;

typedef struct  tagEMSVariantRecord
    {
    EMSRECORDTYPE eType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSLEOSTATUSUPDATE status;
        /* [case()] */ EMSCALIB406DATA calib406;
        /* [case()] */ EMSCBCOUTPUTDATA calibCBC;
        /* [case()] */ EMSCBCDATA rawCBC;
        /* [case()] */ EMSCOMBINE406DATA combine406;
        /* [case()] */ EMSCONFIGPACKET config;
        /* [case()] */ EMSLOCATE locate;
        /* [case()] */ EMSLOGDATA log;
        /* [case()] */ EMSTLERECORD tle;
        /* [case()] */ EMSRESIDUALDATA residual;
        /* [case()] */ EMSSARPCALIBDATA sarpcalib;
        /* [case()] */ EMSSARPDATA sarp;
        /* [case()] */ EMSSARRCALIBDATA sarrcalib;
        /* [case()] */ EMSSARRDATA sarr;
        /* [case()] */ EMSSATTRACKRECORD satTrack;
        /* [case()] */ EMSSPECTRUM spectrum;
        /* [case()] */ EMSMANOEUVREDATA manoeuvre;
        /* [case()] */ EMSAUDIODATARECORD_RIFF audio;
        /* [case()] */ EMSALARMDATA statsummary;
        /* [default] */  /* Empty union arm */ 
        }	data;
    }	EMSVARIANTRECORD;

typedef struct  tagEMSVariantRecord2
    {
    EMSRECORDTYPE eType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSLEOSTATUSUPDATE status;
        /* [case()] */ EMSCALIB406DATA calib406;
        /* [case()] */ EMSCBCOUTPUTDATA calibCBC;
        /* [case()] */ EMSCBCDATA rawCBC;
        /* [case()] */ EMSCOMBINE406DATA combine406;
        /* [case()] */ EMSCONFIGPACKET config;
        /* [case()] */ EMSLOCATE locate;
        /* [case()] */ EMSLOGDATA log;
        /* [case()] */ EMSTLERECORD tle;
        /* [case()] */ EMSRESIDUALDATA residual;
        /* [case()] */ EMSSARPCALIBDATA sarpcalib;
        /* [case()] */ EMSSARPDATA sarp;
        /* [case()] */ EMSSARRCALIBDATA sarrcalib;
        /* [case()] */ EMSSARRDATA sarr;
        /* [case()] */ EMSSATTRACKRECORD satTrack;
        /* [case()] */ EMSSPECTRUM spectrum;
        /* [case()] */ EMSMANOEUVREDATA manoeuvre;
        /* [case()] */ EMSAUDIODATARECORD_RIFF audio;
        /* [case()] */ EMSALARMDATA statsummary;
        /* [case()] */ EMSSARRDATAEX sarrext;
        /* [case()] */ EMSCALIB406DATAEXT calib406ext;
        /* [case()] */ EMSCALIB406DATA2 calib406_2;
        /* [default] */  /* Empty union arm */ 
        }	data;
    }	EMSVARIANTRECORD2;

typedef struct  tagEMSVariantRecord3
    {
    EMSRECORDTYPE eType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSLEOSTATUSUPDATE status;
        /* [case()] */ EMSCALIB406DATA calib406;
        /* [case()] */ EMSCBCOUTPUTDATA calibCBC;
        /* [case()] */ EMSCBCDATA rawCBC;
        /* [case()] */ EMSCOMBINE406DATA combine406;
        /* [case()] */ EMSCONFIGPACKET config;
        /* [case()] */ EMSLOCATE locate;
        /* [case()] */ EMSLOGDATA log;
        /* [case()] */ EMSTLERECORD tle;
        /* [case()] */ EMSRESIDUALDATA residual;
        /* [case()] */ EMSSARPCALIBDATA sarpcalib;
        /* [case()] */ EMSSARPDATA sarp;
        /* [case()] */ EMSSARRCALIBDATA sarrcalib;
        /* [case()] */ EMSSARRDATA sarr;
        /* [case()] */ EMSSATTRACKRECORD satTrack;
        /* [case()] */ EMSSPECTRUM spectrum;
        /* [case()] */ EMSMANOEUVREDATA manoeuvre;
        /* [case()] */ EMSAUDIODATARECORD_RIFF audio;
        /* [case()] */ EMSALARMDATA statsummary;
        /* [case()] */ EMSSARRDATAEX sarrext;
        /* [case()] */ EMSCALIB406DATAEXT calib406ext;
        /* [case()] */ EMSCALIB406DATA2 calib406_2;
        /* [case()] */ EMSABLData abl;
        /* [case()] */ EMSHEALTHSTATUS healthstatus;
        /* [case()] */ EMSHEALTHDETECTIONS healthdetections;
        /* [case()] */ EMS_BEACON_ADVISORY beaconadvisory;
        /* [default] */  /* Empty union arm */ 
        }	data;
    }	EMSVARIANTRECORD3;



extern RPC_IF_HANDLE __MIDL_itf_DAL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DAL_0000_v0_0_s_ifspec;

#ifndef __IEMSDALVariable_INTERFACE_DEFINED__
#define __IEMSDALVariable_INTERFACE_DEFINED__

/* interface IEMSDALVariable */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDALVariable;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F66FA79A-593B-414b-B024-934B3E91FA71")
    IEMSDALVariable : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ const boolean cbReturnDescriptor,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
            /* [out][in] */ unsigned long __RPC_FAR *pulFields,
            /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
            /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
            /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cancel( 
            /* [in] */ const EMSDALCACHEID cCacheID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDALVariableVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDALVariable __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDALVariable __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDALVariable __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSDALVariable __RPC_FAR * This,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ const boolean cbReturnDescriptor,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
            /* [out][in] */ unsigned long __RPC_FAR *pulFields,
            /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
            /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
            /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IEMSDALVariable __RPC_FAR * This,
            /* [in] */ const EMSDALCACHEID cCacheID);
        
        END_INTERFACE
    } IEMSDALVariableVtbl;

    interface IEMSDALVariable
    {
        CONST_VTBL struct IEMSDALVariableVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDALVariable_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDALVariable_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDALVariable_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDALVariable_GetData(This,pCacheID,culMaxRecords,cbReturnDescriptor,cwszOutputFileSpec,pulTotalRecords,pulRecordSize,pbCacheOverflow,cwszConnection,cwszSQLQuery,pulFields,paFields,pulDataSize,paData)	\
    (This)->lpVtbl -> GetData(This,pCacheID,culMaxRecords,cbReturnDescriptor,cwszOutputFileSpec,pulTotalRecords,pulRecordSize,pbCacheOverflow,cwszConnection,cwszSQLQuery,pulFields,paFields,pulDataSize,paData)

#define IEMSDALVariable_Cancel(This,cCacheID)	\
    (This)->lpVtbl -> Cancel(This,cCacheID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDALVariable_GetData_Proxy( 
    IEMSDALVariable __RPC_FAR * This,
    /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
    /* [in] */ const unsigned long culMaxRecords,
    /* [in] */ const boolean cbReturnDescriptor,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
    /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
    /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
    /* [out][in] */ unsigned long __RPC_FAR *pulFields,
    /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
    /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
    /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData);


void __RPC_STUB IEMSDALVariable_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDALVariable_Cancel_Proxy( 
    IEMSDALVariable __RPC_FAR * This,
    /* [in] */ const EMSDALCACHEID cCacheID);


void __RPC_STUB IEMSDALVariable_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDALVariable_INTERFACE_DEFINED__ */


#ifndef __IEMSDALFixed_INTERFACE_DEFINED__
#define __IEMSDALFixed_INTERFACE_DEFINED__

/* interface IEMSDALFixed */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDALFixed;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("803BA197-4A48-4d01-B545-C56F660FDF1F")
    IEMSDALFixed : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ const EMSRECORDTYPE ceRecordType,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Delete( 
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const EMSRECORDTYPE ceType,
            /* [in] */ const EMSTIME ctimeStart,
            /* [in] */ const EMSTIME ctimeEnd,
            /* [out][in] */ unsigned long __RPC_FAR *pulDeleted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Insert( 
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const unsigned long culRecords,
            /* [size_is][in] */ const EMSVARIANTRECORD __RPC_FAR *caRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Cancel( 
            /* [in] */ const EMSDALCACHEID cCacheID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDALFixedVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDALFixed __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDALFixed __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDALFixed __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSDALFixed __RPC_FAR * This,
            /* [in] */ const EMSRECORDTYPE ceRecordType,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IEMSDALFixed __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const EMSRECORDTYPE ceType,
            /* [in] */ const EMSTIME ctimeStart,
            /* [in] */ const EMSTIME ctimeEnd,
            /* [out][in] */ unsigned long __RPC_FAR *pulDeleted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IEMSDALFixed __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const unsigned long culRecords,
            /* [size_is][in] */ const EMSVARIANTRECORD __RPC_FAR *caRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IEMSDALFixed __RPC_FAR * This,
            /* [in] */ const EMSDALCACHEID cCacheID);
        
        END_INTERFACE
    } IEMSDALFixedVtbl;

    interface IEMSDALFixed
    {
        CONST_VTBL struct IEMSDALFixedVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDALFixed_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDALFixed_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDALFixed_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDALFixed_GetData(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)	\
    (This)->lpVtbl -> GetData(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)

#define IEMSDALFixed_Delete(This,cwszConnection,ceType,ctimeStart,ctimeEnd,pulDeleted)	\
    (This)->lpVtbl -> Delete(This,cwszConnection,ceType,ctimeStart,ctimeEnd,pulDeleted)

#define IEMSDALFixed_Insert(This,cwszConnection,culRecords,caRecords)	\
    (This)->lpVtbl -> Insert(This,cwszConnection,culRecords,caRecords)

#define IEMSDALFixed_Cancel(This,cCacheID)	\
    (This)->lpVtbl -> Cancel(This,cCacheID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDALFixed_GetData_Proxy( 
    IEMSDALFixed __RPC_FAR * This,
    /* [in] */ const EMSRECORDTYPE ceRecordType,
    /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
    /* [in] */ const unsigned long culMaxRecords,
    /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
    /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
    /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paRecords);


void __RPC_STUB IEMSDALFixed_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDALFixed_Delete_Proxy( 
    IEMSDALFixed __RPC_FAR * This,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [in] */ const EMSRECORDTYPE ceType,
    /* [in] */ const EMSTIME ctimeStart,
    /* [in] */ const EMSTIME ctimeEnd,
    /* [out][in] */ unsigned long __RPC_FAR *pulDeleted);


void __RPC_STUB IEMSDALFixed_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDALFixed_Insert_Proxy( 
    IEMSDALFixed __RPC_FAR * This,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [in] */ const unsigned long culRecords,
    /* [size_is][in] */ const EMSVARIANTRECORD __RPC_FAR *caRecords);


void __RPC_STUB IEMSDALFixed_Insert_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDALFixed_Cancel_Proxy( 
    IEMSDALFixed __RPC_FAR * This,
    /* [in] */ const EMSDALCACHEID cCacheID);


void __RPC_STUB IEMSDALFixed_Cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDALFixed_INTERFACE_DEFINED__ */


#ifndef __IEMSDALFixed2_INTERFACE_DEFINED__
#define __IEMSDALFixed2_INTERFACE_DEFINED__

/* interface IEMSDALFixed2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDALFixed2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("228E8452-9AB1-4fb7-AC71-5212CC4ED9AA")
    IEMSDALFixed2 : public IEMSDALFixed
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData2( 
            /* [in] */ const EMSRECORDTYPE ceRecordType,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD2 __RPC_FAR *__RPC_FAR *paRecords) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Insert2( 
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const unsigned long culRecords,
            /* [size_is][in] */ const EMSVARIANTRECORD2 __RPC_FAR *caRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDALFixed2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDALFixed2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDALFixed2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [in] */ const EMSRECORDTYPE ceRecordType,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const EMSRECORDTYPE ceType,
            /* [in] */ const EMSTIME ctimeStart,
            /* [in] */ const EMSTIME ctimeEnd,
            /* [out][in] */ unsigned long __RPC_FAR *pulDeleted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const unsigned long culRecords,
            /* [size_is][in] */ const EMSVARIANTRECORD __RPC_FAR *caRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Cancel )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [in] */ const EMSDALCACHEID cCacheID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData2 )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [in] */ const EMSRECORDTYPE ceRecordType,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD2 __RPC_FAR *__RPC_FAR *paRecords);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Insert2 )( 
            IEMSDALFixed2 __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [in] */ const unsigned long culRecords,
            /* [size_is][in] */ const EMSVARIANTRECORD2 __RPC_FAR *caRecords);
        
        END_INTERFACE
    } IEMSDALFixed2Vtbl;

    interface IEMSDALFixed2
    {
        CONST_VTBL struct IEMSDALFixed2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDALFixed2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDALFixed2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDALFixed2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDALFixed2_GetData(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)	\
    (This)->lpVtbl -> GetData(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)

#define IEMSDALFixed2_Delete(This,cwszConnection,ceType,ctimeStart,ctimeEnd,pulDeleted)	\
    (This)->lpVtbl -> Delete(This,cwszConnection,ceType,ctimeStart,ctimeEnd,pulDeleted)

#define IEMSDALFixed2_Insert(This,cwszConnection,culRecords,caRecords)	\
    (This)->lpVtbl -> Insert(This,cwszConnection,culRecords,caRecords)

#define IEMSDALFixed2_Cancel(This,cCacheID)	\
    (This)->lpVtbl -> Cancel(This,cCacheID)


#define IEMSDALFixed2_GetData2(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)	\
    (This)->lpVtbl -> GetData2(This,ceRecordType,pCacheID,culMaxRecords,pulTotalRecords,pbCacheOverflow,cwszConnection,cwszSQLWhere,pulRecords,paRecords)

#define IEMSDALFixed2_Insert2(This,cwszConnection,culRecords,caRecords)	\
    (This)->lpVtbl -> Insert2(This,cwszConnection,culRecords,caRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDALFixed2_GetData2_Proxy( 
    IEMSDALFixed2 __RPC_FAR * This,
    /* [in] */ const EMSRECORDTYPE ceRecordType,
    /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
    /* [in] */ const unsigned long culMaxRecords,
    /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
    /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLWhere,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
    /* [size_is][size_is][out] */ EMSVARIANTRECORD2 __RPC_FAR *__RPC_FAR *paRecords);


void __RPC_STUB IEMSDALFixed2_GetData2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDALFixed2_Insert2_Proxy( 
    IEMSDALFixed2 __RPC_FAR * This,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [in] */ const unsigned long culRecords,
    /* [size_is][in] */ const EMSVARIANTRECORD2 __RPC_FAR *caRecords);


void __RPC_STUB IEMSDALFixed2_Insert2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDALFixed2_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
