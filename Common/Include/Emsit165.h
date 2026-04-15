/********************************************************************
*	Module:			emsit165.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit165  Class
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


#ifndef INC_EMSIT165
#define INC_EMSIT165

#include "emssit.h"

#define EMS_MAX_SIT165_ALERTS ( 99 ) // make sure this is right

#define EMS_SOLUTION_UNKNOW	( 0 )
#define EMS_SOLUTION_BEACON	( 1 )
#define EMS_SOLUTION_INTERFERER	( 2 )

//typedef struct _tagEMSSIT165HEADER
//{
///*MF11*/	int 	nLutID;
///*MF117*/	WORD	wDataTypes;
///*MF19*/	WORD	wNumSideBands;
///*MF20*/	double	dSweep;
//			double	dSweepDev;
///*MF118*/	WORD	wSolutoinType;
//			ULONG	ulSatID;
//} EMSSIT165HEADER, *LPEMSSIT165HEADER;

//typedef struct _tagEMSSIT165SIDESOLN
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
//} EMSSIT165SIDESOLN, *LPEMSSIT165SIDESOLN;

//typedef struct _tagEMSSIT165SOLUTION
//{
//	EMSSIT165HEADER hdr;
//	EMSSIT165SIDESOLN sideA, sideB;
//} EMSSIT165SOLUTION, *LPEMSSIT165SOLUTION;

class CEMSSit165 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit165();
	virtual ~CEMSSit165();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

//	EMS_RESULT AddSolution( LPEMSSIT165SOLUTION lpSolution );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

//private:	// data
//	LPEMSSIT165SOLUTION m_lpSoln[ EMS_MAX_SIT165_ALERTS ];
};

#endif // INC_EMSIT165
