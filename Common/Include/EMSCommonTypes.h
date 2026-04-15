

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Oct 18 08:45:07 2004
 */
/* Compiler settings for .\include\EMSCommonTypes.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __EMSCommonTypes_h__
#define __EMSCommonTypes_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emsauthorization.h"
#include "dal.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_EMSCommonTypes_0000 */
/* [local] */ 

typedef 
enum eTrigger
    {	EMSTRG_UNKNOWN	= 0,
	EMSTRG_MANUAL	= 1,
	EMSTRG_AUTO	= 2,
	EMSTRG_LAST	= EMSTRG_AUTO + 1
    } 	EMSTRIGGER;

typedef 
enum eOperatorCmd
    {	OPCMD_UNKNOWN	= 0,
	OPCMD_RESTART_COLD	= 1,
	OPCMD_RESTART_WARM	= 2,
	OPCMD_GENPASS	= 3,
	OPCMD_PROCPASS	= 4,
	OPCMD_SUPPASS	= 5,
	OPCMD_SYSTEST	= 6,
	OPCMD_GETCFG	= 7,
	OPCMD_SETCFG	= 8,
	OPCMD_SEND_DATA	= 9,
	OPCMD_GET_FILE	= 10,
	OPCMD_LAST	= OPCMD_GET_FILE + 1
    } 	EMSOPERATORCMDTYPE;

typedef struct tagPass
    {
    unsigned long ulLutID;
    unsigned long ulSatID;
    unsigned long ulPassID;
    EMSTIME timeAOS;
    } 	EMSPASSDEF;

typedef struct tagConfigSetting
    {
    wchar_t wszConfigID[ 256 ];
    wchar_t wszLHS[ 256 ];
    wchar_t wszRHS[ 1024 ];
    EMSAUTHORIZATIONINFO authInfo;
    } 	EMSCONFIGSETTING;

typedef struct tagPassSchedParams
    {
    EMSTIME timeStartTime;
    double dDuration;
    } 	EMSSCHEDPARAMS;

typedef 
enum tagCriteriaType
    {	CRITERIA_UNKNOWN	= 0,
	CRITERIA_C	= 1,
	CRITERIA_S	= 2,
	CRITERIA_P	= 3,
	CRITERIA_T	= 4,
	CRITERIA_X	= 5,
	CRITERIA_B	= 6,
	CRITERIA_LAST	= CRITERIA_B + 1
    } 	EMSCRITERIATYPE;

typedef 
enum tagLUTType
    {	LUTTYPE_UNKNOWN	= 0,
	LUTTYPE_LEO	= 1,
	LUTTYPE_GEO	= 2,
	LUTTYPE_LAST	= LUTTYPE_GEO + 1
    } 	EMSLUTTYPE;

typedef struct tagSendDataParams
    {
    EMSRECORDTYPE eDataType;
    EMSCRITERIATYPE eCriteriaType;
    unsigned long ulSatID;
    unsigned long ulPassID;
    EMSTIME time1;
    EMSTIME time2;
    double dDuration;
    __int64 i64BeaconID;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSLUTTYPE eLutType;
        /* [case()] */ boolean bLog;
        /* [case()] */ EMSAUDIOSPEC audioSpec;
        /* [default] */  /* Empty union arm */ 
        } 	exData;
    boolean bGeo;
    } 	EMSSENDDATAPARAMS;

typedef struct tagGetFileParams
    {
    wchar_t wszFileName[ 256 ];
    wchar_t wszChildDir[ 256 ];
    boolean bDelete;
    } 	EMSGETFILEPARAMS;

typedef struct tagOperatorCmd
    {
    EMSOPERATORCMDTYPE eCmdType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSPASSDEF pass;
        /* [case()] */ EMSCONFIGSETTING cfg;
        /* [case()] */ EMSSCHEDPARAMS sched;
        /* [case()] */ EMSSENDDATAPARAMS sendData;
        /* [case()] */ EMSGETFILEPARAMS getFile;
        /* [default] */  /* Empty union arm */ 
        } 	cmdData;
    } 	EMSOPERATORCMD;

typedef 
enum tagControlDataValue
    {	EMSCONTROL_UNKNOWN	= 0,
	EMSCONTROL_INFO	= 1,
	EMSCONTROL_VALD	= 2,
	EMSCONTROL_EXEC	= 3,
	EMSCONTROL_VALI	= 4,
	EMSCONTROL_INST	= 5,
	EMSCONTROL_APND	= 6,
	EMSCONTROL_LAST	= EMSCONTROL_APND + 1
    } 	EMSCONTROLDATAVALUE;



extern RPC_IF_HANDLE __MIDL_itf_EMSCommonTypes_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSCommonTypes_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


