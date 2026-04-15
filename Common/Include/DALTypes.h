
#ifndef __DAL_TYPES_H__
#define __DAL_TYPES_H__

#include "dal.h"

#define _USEADO
#ifdef _USEADO
#pragma warning(push)
#pragma warning(disable:4146)
#import <msado15.dll> named_guids, rename("EOF", "EndOfFile" )
#pragma warning(pop)
using namespace ADODB;
#endif

typedef enum tagDBCmdDirectionType
{
	EMS_DBCMD_DIR_TYPE_UNKNOWN = 0,
	EMS_DBCMD_DIR_TYPE_INPUT = 1,
	EMS_DBCMD_DIR_TYPE_OUTPUT = 2,
	EMS_DBCMD_DIR_TYPE_INOUT = 3,
	EMS_DBCMD_DIR_TYPE_RETURN = 4
} EMSDBCMDDIRECTIONTYPE;

// For converting between ADO and EMS types.
typedef struct tagEMSADOFldTypeConversion
{
	DataTypeEnum eAdoType;
	EMSDBFLDTYPE eEmsType;
} EMSADOFLDTYPECONVERSION;

static const EMSADOFLDTYPECONVERSION s_caFldTypeConversions[] = {	{ adSmallInt, DBFLDTYPE_SHORT },
																	{ adUnsignedSmallInt, DBFLDTYPE_USHORT }, 
																	{ adInteger, DBFLDTYPE_LONG },
																	{ adUnsignedInt, DBFLDTYPE_ULONG },
																	{ adBigInt, DBFLDTYPE_BIGINT },
																	{ adUnsignedBigInt, DBFLDTYPE_UBIGINT },
																	{ adBSTR, DBFLDTYPE_WSTRING },
																	{ adChar, DBFLDTYPE_STRING },
																	{ adVarChar, DBFLDTYPE_STRING },
																	{ adBinary, DBFLDTYPE_BINARY },
																	{ adLongVarBinary, DBFLDTYPE_LONG_BINARY },
																	{ adSingle, DBFLDTYPE_FLOAT },
																	{ adDouble, DBFLDTYPE_DOUBLE },
																	{ adTinyInt, DBFLDTYPE_TINYINT },
																	{ adUnsignedTinyInt, DBFLDTYPE_UTINYINT },
																	{ adNumeric, DBFLDTYPE_DOUBLE },
																	{ adDecimal, DBFLDTYPE_DOUBLE },
																	{ adBoolean, DBFLDTYPE_BOOLEAN },
																	{ adVarChar, DBFLDTYPE_VARCHAR },
																	{ adDBTimeStamp, DBFLDTYPE_DATETIME },
																	{ adChar, DBFLDTYPE_CHAR },
																	{ (DataTypeEnum) 0, (EMSDBFLDTYPE) 0 }
																};

typedef struct tagEMSFLDDataSize
{
	EMSDBFLDTYPE eDataType;
	long lBytes;
} EMSFLDDATASIZE;

static const long s_clVariableSize = -1;

static const EMSFLDDATASIZE s_caFldSizes[] = {	{ DBFLDTYPE_SHORT, sizeof(short) },
												{ DBFLDTYPE_USHORT, sizeof(unsigned short) }, 
												{ DBFLDTYPE_LONG, sizeof(long) },
												{ DBFLDTYPE_ULONG, sizeof(unsigned long) },
												{ DBFLDTYPE_BIGINT, sizeof(__int64) },
												{ DBFLDTYPE_UBIGINT, sizeof(unsigned __int64) },
												{ DBFLDTYPE_WSTRING, s_clVariableSize },
												{ DBFLDTYPE_STRING, s_clVariableSize },
												{ DBFLDTYPE_BINARY, s_clVariableSize },
												{ DBFLDTYPE_LONG_BINARY, s_clVariableSize },
												{ DBFLDTYPE_FLOAT, sizeof(float) },
												{ DBFLDTYPE_DOUBLE, sizeof(double) },
												{ DBFLDTYPE_TINYINT, sizeof(char) },
												{ DBFLDTYPE_UTINYINT, sizeof(unsigned char) },
												{ DBFLDTYPE_BOOLEAN, sizeof(unsigned char) },
												{ DBFLDTYPE_VARCHAR, s_clVariableSize },
												{ DBFLDTYPE_DATETIME, sizeof(EMSTIME) },
												{ DBFLDTYPE_CHAR, s_clVariableSize },
												{ DBFLDTYPE_UNKNOWN, 0 }
											};


typedef enum tagObjectState
{
	DBOBJ_STATE_UNKNOWN = 0,
	DBOBJ_STATE_CLOSED = 1,
	DBOBJ_STATE_OPEN = 2,
	DBOBJ_STATE_CONNECTING = 3,
	DBOBJ_STATE_EXECUTING = 4,
	DBOBJ_STATE_FETCHING = 5
} EMSDBOBJECTSTATE;

typedef struct tagEMSADOObjStateConversion
{
	ObjectStateEnum eAdoState;
	EMSDBOBJECTSTATE eEmsState;
} EMSADOOBJSTATECONVERSION;

static const EMSADOOBJSTATECONVERSION s_caObjStateConversions[] = {	{ adStateClosed, DBOBJ_STATE_CLOSED },
																	{ adStateOpen, DBOBJ_STATE_OPEN }, 
																	{ adStateConnecting, DBOBJ_STATE_CONNECTING },
																	{ adStateExecuting, DBOBJ_STATE_EXECUTING },
																	{ adStateFetching, DBOBJ_STATE_FETCHING },
																	{ (ObjectStateEnum) -1, DBOBJ_STATE_UNKNOWN }
																};

static const HRESULT s_achrFilteredAlarms[] = { 0x80040E37L,	// "column not found"
												0x80040E14L,	// "syntax error or access violation"
												0x80040e4dL,	// "Invalid user authorization specification: Integrated logins are not permitted."
													0 };

static const HRESULT s_achrWarnings[] = { 0 };

typedef enum tagAffects
{
	DBAFFECT_UNKNOWN = 0,
	DBAFFECT_ALL = 1,
	DBAFFECT_CURRENT = 2,
	DBAFFECT_ALL_CHAPTERS = 3,
	DBAFFECT_GROUP = 4
} EMSDBAFFECTS;

#endif // __DAL_TYPES_H__