/********************************************************************
*	Module:			emscoord.h
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

	0.0	2001/03/22	rvw	start

********************************************************************/

#ifndef INC_EMSCOORD
#define INC_EMSCOORD

#include "emstypes.h"

class CEMSCoordSystem
{
public:
	CEMSCoordSystem();
	CEMSCoordSystem( EMSTIMECOORD  timeCoord );
	CEMSCoordSystem( EMSTIMECOORDD timeCoord );
	~CEMSCoordSystem();

	EMSTIMECOORD   ToInertial(            EMSTIMECOORD  srcCoord    ) const;
	EMSTIMECOORDD  ToInertial(            EMSTIMECOORDD srcCoord    ) const;
	EMSTIMECOORD   ToEarthFixed(          EMSTIMECOORD  srcCoord    ) const;
	EMSTIMECOORDD  ToEarthFixed(          EMSTIMECOORDD srcCoord    ) const;
	EMSTIMECOORD   ToStdEarthFixed(       EMSTIMECOORD  srcCoord    ) const;
	EMSTIMECOORDD  ToStdEarthFixed(       EMSTIMECOORDD srcCoord    ) const;
	EMSVECTOR      ToEarthFixed(          EMSLOCATION   srcLocation ) const;
	EMSVECTORD     ToEarthFixedDouble(    EMSLOCATION   srcLocation ) const;
	double         DistanceApart(         EMSLOCATION   locA, EMSLOCATION locB ) const;
	EMSVECTOR      EarthFixedVelocity(    EMSLOCATION   srcLocation ) const;
	EMSVECTORD     EarthFixedVelocityDouble(EMSLOCATION srcLocation ) const;
	EMSVECTOR      EarthFixedVelocity(    EMSVECTOR     vLoc        ) const;
	EMSVECTORD     EarthFixedVelocity(    EMSVECTORD    vLoc        ) const;
//	EMSVECTOR      ToEarthFixed(          EMSCOORD      srcCoord    ) const;
	EMSAZELVECTOR  ToAzimuthAndElevation( EMSENUVECTOR  enuVector   ) const;
	EMSAZELVECTORD ToAzimuthAndElevation( EMSENUVECTORD enuVector   ) const;
	EMSAZELVECTOR  ToAzimuthAndElevation( EMSTIMECOORD  srcInertialVector,  EMSLOCATION location ) const;
	EMSAZELVECTORD ToAzimuthAndElevation( EMSTIMECOORDD srcInertialVector,  EMSLOCATION location ) const;
	EMSENUVECTOR   ToTopocentricHorizon(  EMSTIMECOORD  srcInertialVector,  EMSLOCATION location ) const;
	EMSENUVECTORD  ToTopocentricHorizon(  EMSTIMECOORDD srcInertialVector,  EMSLOCATION location ) const;
	EMSENUVECTOR   ToTopocentricHorizon(  EMSVECTOR     srcInterialVector,  EMSLOCATION location,  EMSTIME emsTime ) const;
	EMSENUVECTORD  ToTopocentricHorizon(  EMSVECTORD    srcInterialVector,  EMSLOCATION location,  EMSTIME emsTime ) const;
	EMSVECTOR      ToInertialPosition(    EMSLOCATION   srcLocation,        EMSTIME      srcTime  ) const;
	EMSVECTORD     ToInertialPositionDouble(EMSLOCATION srcLocation,        EMSTIME      srcTime  ) const;
	EMSLOCATION    ToGeodetic( EMSVECTOR    position )  const;
	EMSLOCATION    ToGeodetic( EMSVECTORD   position )  const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSTIMECOORD    sat1,   EMSTIMECOORD  sat2     ) const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSTIMECOORDD   sat1,   EMSTIMECOORDD sat2     ) const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSCOORD        sat )   const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSCOORDD       sat )   const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSTIMECOORD    sat )   const;
	EMSLOCATION    ToGeodetic( EMSTCACTA    a,        EMSTIMECOORDD   sat )   const;
	EMSTCACTA      ToTcaCta(   EMSLOCATION  location, EMSTIMECOORD    sat1,   EMSTIMECOORD  sat2     ) const;
	EMSTCACTA      ToTcaCta(   EMSLOCATION  location, EMSTIMECOORDD   sat1,   EMSTIMECOORDD sat2     ) const;
	EMSTCACTA      ToTcaCta(   EMSLOCATION  location, LPEMSTIMECOORD  satvec, ULONG         ulCount  ) const;
	EMSTCACTA      ToTcaCta(   EMSLOCATION  location, LPEMSTIMECOORDD satvec, ULONG         ulCount  ) const;
	EMSTCACTA      ToTcaCta(   EMSVECTOR    position, EMSTIMECOORD    sat1,   EMSTIMECOORD  sat2     ) const;
	EMSTCACTA      ToTcaCta(   EMSVECTORD   position, EMSTIMECOORDD   sat1,   EMSTIMECOORDD sat2     ) const;

	EMSTIMECOORD   EarthFixedToInertial(  EMSVECTOR  vLoc, EMSTIME t ) const;
	EMSTIMECOORDD  EarthFixedToInertial(  EMSVECTORD vLoc, EMSTIME t ) const;

	EMSTIMECOORDD  PZ90toWGS84( EMSTIMECOORDD satPZ90 ) const;

private: // methods
	EMSTIMECOORD  _InertialToEarthFixed(      EMSTIMECOORD  srcCoord ) const;
	EMSTIMECOORDD _InertialToEarthFixed(      EMSTIMECOORDD srcCoord ) const;
	EMSTIMECOORD  _EarthFixedToInertial(      EMSTIMECOORD  srcCoord ) const;
	EMSTIMECOORDD _EarthFixedToInertial(      EMSTIMECOORDD srcCoord ) const;
	EMSTIMECOORD  _StdEarthFixedToEarthFixed( EMSTIMECOORD  srcCoord ) const;
	EMSTIMECOORDD _StdEarthFixedToEarthFixed( EMSTIMECOORDD srcCoord ) const;
	EMSTIMECOORD  _EarthFixedToStdEarthFixed( EMSTIMECOORD  srcCoord ) const;
	EMSTIMECOORDD _EarthFixedToStdEarthFixed( EMSTIMECOORDD srcCoord ) const;

private: // data
	EMSTIMECOORD  m_timeCoord;
	EMSTIMECOORDD m_timeCoordd;
};

#endif // INC_EMSCOORD
