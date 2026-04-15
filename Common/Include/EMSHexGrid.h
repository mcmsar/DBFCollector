/********************************************************************
*	Module:			emshexgrid.h
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
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

	0.0	2006/09/15		rcr		start

********************************************************************/

#ifndef INC_EMSHEXGRID
#define INC_EMSHEXGRID

#include "emstypes.h"
#include "emserror.h"

const int c_nMaxCells = 10201;  //maximum of 101x101 grid


#define EMS_GLOBAL_MINIMUM		0x01
#define EMS_LOCAL_MINIMUM		0x02
#define EMS_NO_LOCAL_MINIMUM	0x04

typedef struct _tagEMSHEXGRID // Grid data
{
	EMSLOCATION vGridLocation;
	double		dMeanFrequency;
	double		dStdDev;
	double		dTimeStdDev;
	double		dFreqStdDev;
	int			nTimePtsUsed;
	int			nFreqPtsUsed;
	int			nPtsUsed;
	int			nElevTestPts;
	WORD		wFlags;
} EMSHEXGRID, *LPEMSHEXGRID;


class CEMSHexGrid
{
public:
	CEMSHexGrid();
	~CEMSHexGrid();

	int GetGridSize(void){ return m_Tcells;}

	EMSVECTORD GetGridVector( int nIndex ){ return m_GridVector[nIndex]; }
	EMSLOCATION GetGridLocation( int nIndex ){ return m_GridLocation[nIndex]; }

	EMS_RESULT GetGridVectors( LPEMSVECTOR pGridVectors );
	EMS_RESULT GetGridLocations( LPEMSLOCATION pGridLocations );

	EMS_RESULT CalculateGrid( double dAngle, int nXcells, int nYcells = 0);
	
	EMS_RESULT RotateGrid( double dLatitude, double dLongitude);
	
	int GetNearestNeighbours( int nIndex, int nNumber, double dAngle, int *pIndexArray);
	
	EMS_RESULT GenerateGrid( double dDegLatitude, double dDegLongitude, double dAngle, int nXCells, int nYCells );

private: // methods

private: // data
	int				m_Tcells;
	int				m_Xcells;
	int				m_Ycells;
	EMSVECTORD		m_GridArray[ c_nMaxCells ];
	EMSVECTORD		m_GridVector[ c_nMaxCells ];
	EMSLOCATION		m_GridLocation[ c_nMaxCells ];
	double			m_RotationMatrix[3][3];
};

#endif // INC_EMSHEXGRID
