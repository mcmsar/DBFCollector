/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/


#ifndef __OCC_INTERFACE_H__
#define __OCC_INTERFACE_H__

typedef __int64 LONG64;

//! Value of cache ID that indicates no more records are available in the cache.
const long clNoMoreRecords = -1;

typedef enum tagRetrievalType
{
	RETRIEVAL_TYPE_UNKNOWN = 0,
	RETRIEVAL_TYPE_BUFFERED = 1,
	RETRIEVAL_TYPE_NOT_BUFFERED = 2
} EMSRETRIEVALTYPE;

typedef struct tagAlertCriteria
{
	bool bUseTCAStartTime;
	bool bUseTCAEndTime;
	bool bUseRecvStartTime;
	bool bUseRecvEndTime;
	bool bUseBeaconID;
	bool bUseCC;
	bool bUseMMSI;
	bool bUseFrequencyBand;
	bool bUseAreaRectangle;
	bool bUseAreaCircle;
	bool bUseMode;
	bool bUseSRR;
	bool bUseSolutionAttribute;

	LONG64 i64TCAStartTime;
	LONG64 i64TCAEndTime;
	LONG64 i64RecvStartTime;
	LONG64 i64RecvEndTime;
	LONG64 i64BeaconID;
	int iCountryCode;
	int iMMSI;
	int iFreqBand;	// 1 for 121.5, 2 for 243.0, 3 for 406
	
	// A rectangular area is defined by a diagonal line.  The line is defined by two points.
	double dAreaRectangleLat1;
	double dAreaRectangleLong1;
	double dAreaRectangleLat2;
	double dAreaRectangleLong2;

	// A circular area is defined by a centre point and radius.
	double dAreaCircleCentreLat;
	double dAreaCircleCentreLong;
	double dAreaCircleRadius;

	int iMode;	// 1 for normal, 2 for test.

	int iSRR;	// identifier for Search and Rescue region.

	// Assuming an alert can have only one attribute.
	// 1 == active, 2 == new, 3 == unlocated, ... (see SRS).
	int iAttribute;  
} EMSALERTCRITERIA;

typedef struct tagAlertRecord
{
} EMSALERTRECORD;


//! Interface to the EMS OCC.
class IEMSOCC
{
	public:
		//! Retrieve alert data.
		virtual void GetAlerts( long& rlCacheID, const EMSRETRIEVALTYPE ceRetrieveType,
								const EMSALERTCRITERIA& crstrCriteria, ULONG& rulAlerts,
								EMSALERTRECORD*& raRecs) = 0;
};

#endif