/*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc., All rights reserved
*
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __EMSPLOTTYPES_H__
#define __EMSPLOTTYPES_H__

typedef struct _tagEMSPLOTPOINT
{
	double dX;
	double dY;
	double dZ;
} EMSPLOTPOINT, *LPEMSPLOTPOINT;

#define EMSPLOT_MAX_AXES	3
typedef enum _tagEMSPLOTAXIS
{
	EMSPLOTAXIS_MIN = 0,
	EMSPLOTAXIS_X = 0,
	EMSPLOTAXIS_Y = 1,
	EMSPLOTAXIS_Z = 2,
	EMSPLOTAXIS_UNKNOWN = 3,
	EMSPLOTAXIS_MAX = 3
} EMSPLOTAXIS, *LPEMSPLOTAXIS;
#define VALID_EMSPLOTAXIS(e) (EMSPLOTAXIS_MIN <= e && EMSPLOTAXIS_MAX >= e)

typedef enum _tagEMSPLOTACTION
{
	EMSPLOTACTION_MIN = 0,
	EMSPLOTACTION_UNKNOWN = 0,
	EMSPLOTACTION_APPEND = 1,
	EMSPLOTACTION_REPLACE = 2,
	EMSPLOTACTION_MAX = 2
} EMSPLOTACTION, *LPEMSPLOTACTION;
#define VALID_EMSPLOTACTION(e) (EMSPLOTACTION_MIN <= e && EMSPLOTACTION_MAX >= e)

typedef enum _tagEMSPLOTTYPE
{
	EMSPLOTTYPE_MIN = 0,
	EMSPLOTTYPE_UNKNOWN = 0,
	EMSPLOTTYPE_2D = 1,
	EMSPLOTTYPE_3D = 2,
	EMSPLOTTYPE_MAX = 3
} EMSPLOTTYPE, *LPEMSPLOTTYPE;
#define VALID_EMSPLOTTYPE(e) (EMSPLOTTYPE_MIN <= e && EMSPLOTTYPE_MAX >= e)

typedef enum _tagEMSPLOTGRAPHICTYPE
{
	EMSPLOTGRAPHICTYPE_MIN = 0,
	EMSPLOTGRAPHICTYPE_UNKNOWN = 0,
	EMSPLOTGRAPHICTYPE_POINT = 1,
	EMSPLOTGRAPHICTYPE_BITMAP = 2,
	EMSPLOTGRAPHICTYPE_LINE = 3,
	EMSPLOTGRAPHICTYPE_MAX = 3
} 	EMSPLOTGRAPHICTYPE, *LPEMSPLOTGRAPHICTYPE;
#define VALID_EMSPLOTGRAPHICTYPE(e) (EMSPLOTGRAPHICTYPE_MIN <= e && EMSPLOTGRAPHICTYPE_MAX >= e)

typedef enum _tagEMSCOLORASSIGNMENT
{
	EMSCOLORASSIGNMENT_MIN = 0,
	EMSCOLORASSIGNMENT_UNKNOWN = 0,
	EMSCOLORASSIGNMENT_COLORDISCRETE = 1,
	EMSCOLORASSIGNMENT_COLORMAP = 2,
	EMSCOLORASSIGNMENT_MAX = 2
} EMSCOLORASSIGNMENT, *LPEMSCOLORASSIGNMENT;
#define VALID_EMSCOLORASSIGNMENT(e) (EMSCOLORASSIGNMENT_MIN <= e && EMSCOLORASSIGNMENT_MAX >= e)

#endif // __EMSPLOTTYPES_H__
