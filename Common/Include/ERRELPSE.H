/******************************************************************** 
*	Module:			ErrElpse.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Error Ellipse 
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2004 Oct 6 rvw	start

********************************************************************/
#ifndef INC_ERRELPSE
#define INC_ERRELPSE

#include "emstime.h"		// EMSTIME
#include "locate.h"			// EMSLOCATE
//#include "emsbeacn.h"		// EMSREFBEACONDATAEX
#include "emsatinf.h"		// EMSEECONFIGDATA

//const 	int	c_nEMSMaxEESatID = 199;

#pragma pack(1)

typedef struct _tagEMSEEFACTOR
{
	double dScaleFactor;
	double dOrbitError;
} EMSEEFACTOR, *LPEMSEEFACTOR;

typedef enum _tagEMSEETYPE
{
	EMSLAT_FREQ_121 = 0x001,
	EMSLAT_FREQ_243 = 0x002,
	EMSLAT_FREQ_406 = 0x004,
	EMSLAT_SARP = 0x010 | EMSLAT_FREQ_406,
	EMSLAT_SARR = 0x020 | EMSLAT_FREQ_406,
	EMSLAT_SARRSARP = EMSLAT_SARP | EMSLAT_SARR,
	EMSLAT_CBC = 0x040,
	EMSLAT_CBC_121 = EMSLAT_CBC | EMSLAT_FREQ_121,
	EMSLAT_CBC_243 = EMSLAT_CBC | EMSLAT_FREQ_243,
	EMSLAT_CBC_406 = EMSLAT_CBC | EMSLAT_FREQ_406,
	EMSLAT_FDOA = 0x080 | EMSLAT_FREQ_406,
	EMSLAT_Marginal = 0x800,
	EMSLAT_Marginal_FDOA = EMSLAT_Marginal | EMSLAT_FDOA,
	EMSLAT_Marginal_CBC_121 = EMSLAT_Marginal | EMSLAT_CBC_121,
	EMSLAT_Marginal_CBC_243 = EMSLAT_Marginal | EMSLAT_CBC_243,
	EMSLAT_Marginal_CBC_406 = EMSLAT_Marginal | EMSLAT_CBC_406,
	EMSLAT_Marginal_SARP = EMSLAT_Marginal | EMSLAT_SARP,
	EMSLAT_Marginal_SARR = EMSLAT_Marginal | EMSLAT_SARR,
	EMSLAT_Marginal_SARRSARP = EMSLAT_Marginal | EMSLAT_SARRSARP,
	EMSLAT_Unknown = 0x0
} EMSEETYPE;

#pragma pack()

class CEMSErrorEllipse
{
public:
	CEMSErrorEllipse();
	virtual ~CEMSErrorEllipse();

	static EMSEETYPE GetBaseType( WORD wLocType );
	static EMSEETYPE GetType( LPEMSLOCATE lpLocnRecord );
	static EMSEEFACTOR GetEESettings( EMSEETYPE type, EMSEECONFIGDATA *lpEESettings );
	static EMSEEFACTOR GetNominalEESettings( EMSEETYPE type, EMSEECONFIGDATA *lpEESettings );
	static EMSEEFACTOR GetMarginalEESettings( EMSEETYPE type, EMSEECONFIGDATA *lpEESettings );
	static EMS_RESULT CalcErrEllipse( LPEMSWLSLOCATE lpSOLN, double dOrbitError, double dScaleFactor );

	static int IsInEllipse( EMSWLSLOCATE wls, EMSLOCATIOND locnBeacon );
	static int IsInEllipse( EMSWLSLOCATE wls, EMSLOCATION locnBeacon );
	static bool IsNominalSoln( LPEMSLOCATE lpSoln );

private: // methods
	static EMS_RESULT _CalcErrEllipse( LPEMSWLSLOCATE lpSOLN, EMSEEFACTOR ee )
		{ return CalcErrEllipse( lpSOLN, ee.dOrbitError, ee.dScaleFactor ); }
	static EMS_RESULT _CalcErrEllipse( LPEMSWLSLOCATE lpSOLN, EMSEECOEFFICIENT ee )
		{ return CalcErrEllipse( lpSOLN, ee.dAdjustment, ee.dScaleFactor ); }
	static double _CalcDistance( EMSLOCATIOND locA, EMSLOCATION locB );
	static EMSLOCATION _ProjectLocation( EMSLOCATION locOrig, double dAzim, double dDistance );
};

#endif // INC_ERRELPSE

