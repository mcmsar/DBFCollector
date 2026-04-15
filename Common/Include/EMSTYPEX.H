/******************************************************************** 
*	Module:			EMSTypex.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	EMS Specific additional base types
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	   Copyright (c) 2001 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/5/10		rvw	start

********************************************************************/
#ifndef INC_EMSTYPEX
#define INC_EMSTYPEX

typedef unsigned long HEVENT;

/*******************************************************************
*	EMSTIME
*		Basic unit of time is nanoseconds since January 1, 1970 00:00
********************************************************************/

#ifndef _EMSTIME_DEFINED
#define _EMSTIME_DEFINED

typedef union _tagEMSTIME
{
	INT64 intTime;
} EMSTIME, __RPC_FAR *LPEMSTIME;

#define EMS_MAX_TIME ((INT64)(0x7FFFFFFFFFFFFFFF))

#endif // _EMSTIME_DEFINED

typedef double EMSDEGREES;

typedef double EMSRADIANS;

typedef struct _tagEMSVECTOR
{
	float 		fX;
	float 		fY;
	float 		fZ;
} EMSVECTOR, *LPEMSVECTOR;

typedef struct _tagEMSVECTORD
{
	double 		dX;
	double 		dY;
	double 		dZ;
} EMSVECTORD, *LPEMSVECTORD;

typedef struct _tagEMSENUVECTOR
{
	float			fEast;
	float			fNorth;
	float			fUp;
} EMSENUVECTOR, *LPEMSENUVECTOR;

typedef EMSENUVECTOR EMSESUVECTOR;	 
typedef EMSENUVECTOR *LPEMSESUVECTOR;

typedef struct _tagEMSENUVECTORD
{
	double			dEast;
	double			dNorth;
	double			dUp;
} EMSENUVECTORD, *LPEMSENUVECTORD;

typedef EMSENUVECTORD EMSESUVECTORD;	 
typedef EMSENUVECTORD *LPEMSESUVECTORD;

typedef struct _tagEMSAZEL
{
	EMSDEGREES	degElevation;
	EMSDEGREES	degAzimuth;
} EMSAZEL, *LPEMSAZEL;

typedef struct _tagEMSAZELVECTOR
{
	EMSAZEL azel;
	float	fRange;
} EMSAZELVECTOR, *LPEMSAZELVECTOR;

typedef struct _tagEMSAZELVECTORD
{
	EMSAZEL azel;
	double	dRange;
} EMSAZELVECTORD, *LPEMSAZELVECTORD;

typedef struct _tagEMSCOORD
{
	EMSVECTOR	radius;
	EMSVECTOR	velocity;
} EMSCOORD, *LPEMSCOORD;

typedef struct _tagEMSCOORDD
{
	EMSVECTORD	radius;
	EMSVECTORD	velocity;
} EMSCOORDD, *LPEMSCOORDD;

typedef enum _tagEMSCOORDSYSTEM
{
	COORDSYS_StdEarthFixed = 3,			// Normal usage
	COORDSYS_Inertial = 1,
	COORDSYS_EarthFixed = 2					// non-standard usage
} EMSCOORDSYSTEM;

typedef struct _tagEMSLOCATION
{
	EMSDEGREES degLatitude;
	EMSDEGREES degLongitude;
	float fAltitude;
} EMSLOCATION, *LPEMSLOCATION;

typedef struct _tagEMSLOCATIOND
{
	EMSDEGREES degLatitude;
	EMSDEGREES degLongitude;
	double dAltitude;
} EMSLOCATIOND, *LPEMSLOCATIOND;

typedef struct _tagEMSLOCATIONVECTOR
{
	EMSVECTOR radius;
	EMSDEGREES degAzimuth;
	EMSDEGREES degElevation;
	float	fRGS;
	float	fVGS;
} EMSLOCATIONVECTOR, *LPEMSLOCATIONVECTOR;

typedef struct _tagEMSLOCATIONVECTORD
{
	EMSVECTORD radius;
	EMSDEGREES degAzimuth;
	EMSDEGREES degElevation;
	double	dRGS;
	double	dVGS;
} EMSLOCATIONVECTORD, *LPEMSLOCATIONVECTORD;

typedef struct _tagEMSRANGERATE
{
	EMSTIME	vTime;
	float fRange;				// km
	float fRangeRate;			// km/sec
} EMSRANGERATE, *LPEMSRANGERATE;

typedef struct _tagEMSRANGERATED
{
	EMSTIME	vTime;
	double 	dRange;				// km
	double	dRangeRate;			// km/sec
} EMSRANGERATED, *LPEMSRANGERATED;

typedef struct _tagEMSTIMECOORD
{
	EMSCOORDSYSTEM coordSystem;
	EMSTIME			vTime;
	EMSCOORD			coord;
} EMSTIMECOORD, *LPEMSTIMECOORD;

typedef struct _tagEMSTIMECOORDD
{
	EMSCOORDSYSTEM 	coordSystem;
	EMSTIME				vTime;
	EMSCOORDD			coord;
} EMSTIMECOORDD, *LPEMSTIMECOORDD;

typedef struct _tagEMSTCACTA 
{
	EMSTIME	tca;	// nanoseconds
	double   cta;	// degrees
} EMSTCACTA, *LPEMSTCACTA;

#endif // INC_EMSTYPEX

