/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jan 26 10:33:59 2004
 */
/* Compiler settings for C:\dev\Common\Include\EMSAUDIO.IDL:
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

#ifndef __EMSAUDIO_h__
#define __EMSAUDIO_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "sigdata.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSAUDIO_0000 */
/* [local] */ 

 
#include "emserror.h"
 
//  
//  
#define EMS_AUDIO_REQUEST (0x1) 
#define EMS_AUDIO_REPLY (0x2) 
//  
#define EMS_AUDIO_WAVE_FMT (0x1) 
#define MAX_AUDIO_BLOCK_SIZE 4096
#define EMS_AUDIO_REQUEST_FLAG_FILE (0x0001)
#define EMS_AUDIO_REQUEST_FLAG_DB	(0x0002)
#define EMS_AUDIO_REQUEST_FLAG_STREAM  (0x0004)


extern RPC_IF_HANDLE __MIDL_itf_EMSAUDIO_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAUDIO_0000_v0_0_s_ifspec;

#ifndef __IEMSAUDIOdata_INTERFACE_DEFINED__
#define __IEMSAUDIOdata_INTERFACE_DEFINED__

/* interface IEMSAUDIOdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSAUDIOSPEC
    {
    EMSTIME timeStart;
    WORD wSatID;
    WORD wLutID;
    WORD wFileFmt;
    double dDuration;
    double dCentreFreq;
    double dBandwidth;
    WORD wNumFreqCoeff;
    double dFreqCoeff[ 16 ];
    WORD wNumChannels;
    BYTE szFilespec[ 256 ];
    }	EMSAUDIOSPEC;

typedef struct _tagEMSAUDIOSPEC __RPC_FAR *LPEMSAUDIOSPEC;

typedef struct  _tagEMSAUDIOREQUEST
    {
    WORD wFlags;
    INT nDestID;
    INT nRequestID;
    BYTE szUserID[ 65 ];
    DWORD dwUserRights;
    EMSAUDIOSPEC spec;
    HRESULT hrResult;
    DWORD dwFilesize;
    }	EMSAUDIOREQUEST;

typedef struct _tagEMSAUDIOREQUEST __RPC_FAR *LPEMSAUDIOREQUEST;

typedef struct  _tagEMSAUDIORECORDHEADER
    {
    INT64 ID;
    EMSSIGDATAIDTYPE dataID;
    float fCenterFreq;
    float fBandWidth;
    }	EMSAUDIORECORDHEADER;

typedef struct _tagEMSAUDIORECORDHEADER __RPC_FAR *LPEMSAUDIORECORDHEADER;

typedef struct  _tagEMSAUDIORECORDHEADER_RIFF
    {
    EMSAUDIORECORDHEADER audioHdr;
    WORD dwBitsPerSample;
    DWORD dwSamplesPerSec;
    int iChans;
    }	EMSAUDIORECORDHEADER_RIFF;

typedef struct _tagEMSAUDIORECORDHEADER_RIFF __RPC_FAR *LPEMSAUDIORECORDHEADER_RIFF;

typedef struct  _tagEMSAUDIODATARECORD_RIFF
    {
    EMSAUDIORECORDHEADER_RIFF riffHdr;
    UINT uiSequence;
    UINT uiDataSize;
    BYTE data[ 4096 ];
    }	EMSAUDIODATARECORD_RIFF;

typedef struct _tagEMSAUDIODATARECORD_RIFF __RPC_FAR *LPEMSAUDIODATARECORD_RIFF;

typedef struct  _tagEMSAUDIOSELECTCRITERIA
    {
    INT64 i64ID;
    ULONG ulSatID;
    ULONG ulLutID;
    EMSTIME timeStart;
    EMSTIME timeEnd;
    double dCentreFreq;
    double dBandwidth;
    }	EMSAUDIOSELECTCRITERIA;

typedef struct _tagEMSAUDIOSELECTCRITERIA __RPC_FAR *LPEMSAUDIOSELECTCRITERIA;


#pragma pack()


extern RPC_IF_HANDLE IEMSAUDIOdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSAUDIOdata_v0_0_s_ifspec;
#endif /* __IEMSAUDIOdata_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
