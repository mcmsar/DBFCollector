/********************************************************************
*	Module:			DBFCalibration.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

	0.0	2011/13/02		rcr		start

********************************************************************/
#ifndef INC_DBFCALIBRATION
#define INC_DBFCALIBRATION

#include <windows.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#include "emstypes.h"
#include "emserror.h"
#include "emsDBFtypes.h"
#include "sigproc.h"

#define MAX_CALIB_RECORDS (10000)

class CDBFCalibration
{
public:

	~CDBFCalibration( void );
	CDBFCalibration();


	EMS_RESULT Initialize( ULONG ulChannels, ULONG ulRecordCount);

	void _Reset( );
	


protected:

	EMS_RESULT _GetCalibrationRecords( ULONG ulCount );

	EMS_RESULT _GetCalibrationCoefficients( void );

//private: // methods

private: // data

	BOOL		m_bInitialized;
	ULONG		m_ulChannels;
	ULONG		m_ulCalibCount;

	EMSCOMPLEX	m_acCalibCoeff[DBF_MAX_CHANNELS];
	EMSDBFCALIBRECORD*	m_aCalibData;


//private: // constants

};


#endif // INC_DBFCALIBRATION



