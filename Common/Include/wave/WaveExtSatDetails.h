/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#ifndef __WAVE_EXT_SAT_DETAILS_H__
#define __WAVE_EXT_SAT_DETAILS_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "emspipe.h"

//! Maintains information about a particular Satellite.
class CEMSWaveExtSatDetails : public CApiObjBase
{
	public:
		CEMSWaveExtSatDetails();
		CEMSWaveExtSatDetails( const CEMSWaveExtSatDetails& x );
		virtual ~CEMSWaveExtSatDetails();

		void SetSatID( const DWORD cdwSatID ) { m_satDetails.dwSatID = cdwSatID; }
		DWORD GetSatID() const { return m_satDetails.dwSatID; }

		void SetSatFlags( const DWORD cdwFlags ) { m_satDetails.dwFlags = cdwFlags; }
		DWORD GetSatFlags() const { return m_satDetails.dwFlags; }

		void SetSatOrbitNumber( const DWORD cdwOrbit ) { m_satDetails.dwOrbitNumber = cdwOrbit; }
		DWORD GetSatOrbitNumber() const { return m_satDetails.dwOrbitNumber; }

		void SetSatTLE( const EMSTLEDATA2 ctleData ) { m_satDetails.tleData = ctleData; }
		EMSTLEDATA2 GetSatTLE() const { return m_satDetails.tleData; }

		void SetSatCoordSystem( const EMSCOORDSYSTEM ceCoord ) { m_satDetails.eCoordSystem = ceCoord; }
		EMSCOORDSYSTEM GetSatCoordSystem() const { return m_satDetails.eCoordSystem; }

		void SetSatProbability( const double cdProb ) { m_satDetails.dProbability = cdProb; }
		double GetSatProbability() const { return m_satDetails.dProbability; }

		//! Serialize the entire SAT chunk into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData );

		//! Serialize the entire SAT chunk to the stream pointer specified.
		virtual DWORD Serialize( IEMSSeqStream* pStrm );

		//! Build the SAT chunk object model from the input byte array.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Build the SAT chunk object model from the input data stream.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		DWORD GetSize() const { return sizeof(m_satDetails); }
		
	private:
		EMSWAVEEXSATDETAILS m_satDetails;
};

#endif