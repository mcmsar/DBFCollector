/********************************************************************
*	Module:			emsoutlier.h
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

#ifndef INC_EMSOUTLIER
#define INC_EMSOUTLIER

#include "emstypes.h"
#include "emserror.h"

class CEMSOutlier
{
public:
	CEMSOutlier();
	~CEMSOutlier();

	EMS_RESULT Init( int nPts );
	EMS_RESULT Reset( void );
	EMS_RESULT Sort( void );
	EMS_RESULT Calculate( void );
	EMS_RESULT AddRecord( double dDATA );

	int GetThresholdCount( void ){ return (m_nPts - m_nOutliers); }
	int GetOutlierCount( void ){ return m_nOutliers; }
	int GetTotalCount( void ){ return m_nPts; }
	bool TestOutlier( int nIndex );

	EMS_RESULT SetThreshold( double dThreshold, double dOffset );
	EMS_RESULT SetCountThreshold( int nMaxPtsAllowed, double dOffset );

	double GetMean( void ){ return m_dMean; }
	double GetStddev( void ){ return m_dStddev; }
	double GetMedian( void ){ return m_dMedian; }


private: // methods
	void _CalculateStats();
	void _HeapSort();
	void _HeapSiftDown( int nRoot, int nBottom );
	bool _TestSort( void );

private: // data
	int				m_nOutliers;
	double			m_dMean;
	double			m_dMedian;
	double			m_dStddev;

	double			*m_lpDATA;
	bool			*m_lpOUTLIER;
	int				*m_lpIndex;
	int				m_nMaxPts;
	int				m_nPts;
};

#endif // INC_EMSOUTLIER
