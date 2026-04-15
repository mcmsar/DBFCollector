/********************************************************************
*	Module:			emsdoppl.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Definitions for the CEMSDoppler class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	2001/11/14	rvw	start

********************************************************************/
#ifndef INC_EMSDOPPL
#define INC_EMSDOPPL

#include "emsorbit.h"			// IEMSOrbit interface
#include "emstypes.h"
#include "emstime.h"
#include "emserror.h"

static const int c_nTemplIncr = 4; 
static const int c_nNumTempl = 32;
//static const int c_nTemplateLength = 251; // used to be 151
static const int c_nTemplateLength = 301; // used to be 151
static const float c_fTemplateDeltaTime = (float)3.0; // seconds
static const int c_nMaxTemplates = c_nTemplIncr * ( c_nNumTempl + 1 ) - 1;// Maximum number of templates.    

typedef struct _tagEMSDOPPLERTEMPLATES
{    
	int nCount;
	int nLength;
	float fDeltaTime;
	float fCTA[ c_nMaxTemplates ];	// array of cross-track angles
	float fDoppler[c_nTemplateLength][c_nMaxTemplates];// Doppler curves for CTAs
} EMSDOPPLERTEMPLATES, *LPEMSDOPPLERTEMPLATES;

class CEMSDoppler
{
protected:	
	CEMSDoppler() { }
	~CEMSDoppler() { }

public:
	static EMS_RESULT GenerateTemplates( EMSTIMECOORD *lpvCoord, ULONG ulCount, LPEMSDOPPLERTEMPLATES lpTemplates, 
					float fDeltaTime, double fFreqScale = 1.0 );
	static EMS_RESULT XXGenerateTemplates( EMSTIMECOORD *lpvCoord, ULONG ulCount, LPEMSDOPPLERTEMPLATES lpTemplates, 
					float fDeltaTime, double fFreqScale = 1.0 );

	static EMS_RESULT GenerateTemplates( LPEMSORBIT lpOrbit, ULONG ulSatID,
					EMSTIME timeCenter, LPEMSDOPPLERTEMPLATES lpTemplates, 
					float fDeltaTime, double dFreqScale = 1.0 );

private:
	static int _FindClosestEntry( EMSTIMECOORD *lpvCoord, ULONG ulCount,EMSTIME timeAT, int nStartIdx );
};

#endif // INC_EMSDOPPL


