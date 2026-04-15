/********************************************************************
*	Module:			emsit175.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit175  Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#ifndef INC_EMSIT175
#define INC_EMSIT175

#include "emssit.h"

#define EMS_MAX_SIT175_ALERTS ( 99 ) // make sure this is right

//typedef struct _tagEMSSIT175HEADER
//{
///*MF11*/	int 	nPrimaryLutID;
///*MF18*/	int 	nSecondaryLutID;
///*MF07*/	ULONG	ulPass;
///*MF117*/	WORD	wDataTypes;
///*MF119*/	WORD	wTransmissionType;
///*MF126*/	WORD	wBitErrorsPreamble;
//				WORD	wBitErrorsField1;
//				WORD	wBitErrorsField2;
///*MF23*/	BYTE	cBeaconMsg[15];
//			ULONG	ulSatID;
//} EMSSIT175HEADER, *LPEMSSIT175HEADER;
//
//typedef struct _tagEMSSIT175SIDESOLN
//{
///*MF120*/	double dLatitude;
///*MF122*/	double dLongitude;
///*MF14*/	EMSTIME timeTCA;
///*MF15*/	WORD wWindowFactor;
///*MF105*/	WORD wNumPoints;
///*MF16*/	WORD wIterations;
///*MF125*/	double dCTA;
///*MF121*/	double dLatCorrCoeff;
///*MF123*/	double dLongCorrCoeff;
///*MF124*/	double dCorrCoef;	//Latitude/longitude correlation cofficient
///*MF27*/	double dErrEllipseAngle;		// degrees 000-359 nnn
//				double dErrEllipseMajAxis;		// km nnn.n
//				double dErrEllipseMinAxis;		// km nnn.n
///*MF28*/	double dProbability;
///*MF30*/	double dConfidence;
///*MF13*/	double dBias;						// Hz -25000.0 - +75000 snnnnn.n
//				double dBSdev;						// 000.0-900.0			nnn.n
//				double dDrift;						// -99.00 - +99.00   snn.nn
///*MF31*/	double dDataResSdev;				// Hz 000.0 - 250.0		nnn.n
//				double dDataResTrend;			// Hz 000.0 - 250.0   	nnn.n
//} EMSSIT175SIDESOLN, *LPEMSSIT175SIDESOLN;
//
//typedef struct _tagEMSSIT175SOLUTION
//{
//	EMSSIT175HEADER hdr;
//	EMSSIT175SIDESOLN sideA, sideB;
//} EMSSIT175SOLUTION, *LPEMSSIT175SOLUTION;

class CEMSSit175 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit175();
	virtual ~CEMSSit175();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
};

#endif // INC_EMSIT175
