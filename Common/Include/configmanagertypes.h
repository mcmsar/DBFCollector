
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Nov 05 13:43:34 2003
 */
/* Compiler settings for configmanagertypes.idl:
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

#ifndef __configmanagertypes_h__
#define __configmanagertypes_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_configmanagertypes_0000 */
/* [local] */ 

typedef 
enum _tagEMSVARITYPE_DATATYPE
    {	EMSVARITYPE_DATATYPE_UNINITIALIZED	= 0,
	EMSVARITYPE_DATATYPE_BOOL	= 1,
	EMSVARITYPE_DATATYPE_STRING	= 2,
	EMSVARITYPE_DATATYPE_TIME	= 3,
	EMSVARITYPE_DATATYPE_BIGINT	= 4,
	EMSVARITYPE_DATATYPE_INT	= 5,
	EMSVARITYPE_DATATYPE_INTRANGE	= 6,
	EMSVARITYPE_DATATYPE_UINT	= 7,
	EMSVARITYPE_DATATYPE_UINTRANGE	= 8,
	EMSVARITYPE_DATATYPE_DOUBLE	= 9,
	EMSVARITYPE_DATATYPE_DOUBLERANGE	= 10,
	EMSVARITYPE_DATATYPE_FLOAT	= 11,
	EMSVARITYPE_DATATYPE_FLOATRANGE	= 12
    } 	EMSVARITYPE_DATATYPE;

typedef struct _tagEMSVARITYPE
    {
    EMSVARITYPE_DATATYPE dataType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ boolean bVal;
        /* [case()][string] */ wchar_t *pwcsVal;
        /* [case()] */ EMSTIME tmVal;
        /* [case()] */ INT64 i64Val;
        /* [case()] */ int iVal;
        /* [case()] */ struct 
            {
            int iMaxVal;
            int iMinVal;
            } 	iRange;
        /* [case()] */ unsigned int uiVal;
        /* [case()] */ struct 
            {
            unsigned int uiMaxVal;
            unsigned int uiMinVal;
            } 	uiRange;
        /* [case()] */ double dVal;
        /* [case()] */ struct 
            {
            double dMaxVal;
            double dMinVal;
            } 	dRange;
        /* [case()] */ float fVal;
        /* [case()] */ struct 
            {
            float fMaxVal;
            float fMinVal;
            } 	fRange;
        /* [default] */  /* Empty union arm */ 
        } 	;
    } 	EMSVARITYPE;

typedef struct _tagEMSVARITYPE *LPEMSVARITYPE;

typedef struct _tagEMSCONFIGURATIONITEM
    {
    /* [string] */ wchar_t *pwcsKeyName;
    unsigned short uiValues;
    /* [size_is] */ EMSVARITYPE *ValueList;
    } 	EMSCONFIGURATIONITEM;

typedef struct _tagEMSCONFIGURATIONITEM *LPEMSCONFIGURATIONITEM;



extern RPC_IF_HANDLE __MIDL_itf_configmanagertypes_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_configmanagertypes_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


