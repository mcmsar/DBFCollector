/*******************************************************************************
*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __EPHEMERIS_CL_H__
#define __EPHEMERIS_CL_H__

#include "UserConfigCL.h"	//AO reuse for UTC
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  Ephemeris
{
	public:
		Ephemeris();
		Ephemeris( const Ephemeris& x );
		virtual ~Ephemeris();

		unsigned long  GetSatId() { return m_ulSatId; }
		void SetSatId( unsigned long ulSatId ) { m_ulSatId = ulSatId; }

		long GetMeanAnomaly() { return m_lMeanAnomaly; }
		void SetMeanAnomaly( long lMeanAnomaly ) { m_lMeanAnomaly = lMeanAnomaly; }

		long GetMeanMotionDiff() { return m_lMeanMotionDiff; }
		void SetMeanMotionDiff( long lMeanMotionDiff ) { m_lMeanMotionDiff = lMeanMotionDiff; }

		long GetEccentricity() { return m_lEccentricity; }
		void SetEccentricity( long lEccentricity ) { m_lEccentricity = lEccentricity; }

		long GetSemiMajor() { return m_lSemiMajor; }
		void SetSemiMajor( long lSemiMajor ) { m_lSemiMajor = lSemiMajor; }

		long GetLongitudeAscNode() { return m_lLongitudeAscNode; }
		void SetLongitudeAscNode( long lLongitudeAscNode ) { m_lLongitudeAscNode = lLongitudeAscNode; }

		long GetInclineAngle() { return m_lInclineAngle; }
		void SetInclineAngle( long lInclineAngle ) { m_lInclineAngle = lInclineAngle; }

		long GetArgPerigee() { return m_lArgPerigee; }
		void SetArgPerigee( long lArgPerigee ) { m_lArgPerigee = lArgPerigee; }

		long GetRateRightAsc() { return m_lRateRightAsc; }
		void SetRateRightAsc( long lRateRightAsc ) { m_lRateRightAsc = lRateRightAsc; }

		long GetRateIncAngle() { return m_lRateIncAngle; }
		void SetRateIncAngle( long lRateIncAngle ) { m_lRateIncAngle = lRateIncAngle; }

		long GetCUC() { return m_lCUC; }
		void SetCUC( long lCUC ) { m_lCUC = lCUC; }

		long GetCUS() { return m_lCUS; }
		void SetCUS( long lCUS ) { m_lCUS = lCUS; }

		long GetCRC() { return m_lCRC; }
		void SetCRC( long lCRC ) { m_lCRC = lCRC; }

		long GetCRS() { return m_lCRS; }
		void SetCRS( long lCRS ) { m_lCRS = lCRS; }

		long GetCIC() { return m_lCIC; }
		void SetCIC( long lCIC ) { m_lCIC = lCIC; }

		long GetCIS() { return m_lCIS; }
		void SetCIS( long lCIS ) { m_lCIS = lCIS; }

		long GetRefTime() { return m_lRefTime; }
		void SetRefTime( long lRefTime ) { m_lRefTime = lRefTime; }

		long GetWeekNumber() { return m_lWeekNumber; }
		void SetWeekNumber( long lWeekNumber ) { m_lWeekNumber = lWeekNumber; }

		long GetExt1() { return m_lExt1; }
		void SetExt1( long lExt1 ) { m_lExt1 = lExt1; }

private:

	private:
		unsigned long m_ulSatId;
		long		  m_lMeanAnomaly;
		long		  m_lMeanMotionDiff;
		long		  m_lEccentricity;
		long		  m_lSemiMajor;
		long		  m_lLongitudeAscNode;
		long		  m_lInclineAngle;
		long		  m_lArgPerigee;
		long		  m_lRateRightAsc;
		long		  m_lRateIncAngle;
		long		  m_lCUC;
		long		  m_lCUS;
		long		  m_lCRC;
		long		  m_lCRS;
		long		  m_lCIC;
		long		  m_lCIS;
		long		  m_lRefTime;
		long		  m_lWeekNumber;
		long		  m_lExt1;
};

#endif  // __EPHEMERIS_CL_H__

