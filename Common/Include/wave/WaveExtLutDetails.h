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

#ifndef __WAVE_EXT_LUT_DETAILS_H__
#define __WAVE_EXT_LUT_DETAILS_H__

#include "aobjbase.h"
#include "wave/emswavechunk.h"
#include "emspipe.h"
#include "emsexcpt.h"

//! Maintains information about a particular LUT.
class CEMSWaveExtLutDetails : public CApiObjBase
{
	public:
		CEMSWaveExtLutDetails();
		CEMSWaveExtLutDetails( const CEMSWaveExtLutDetails& x );
		virtual ~CEMSWaveExtLutDetails();

		void SetLutID( const DWORD cdwLutID ) { m_lutDetails.dwLutID = cdwLutID; }
		DWORD GetLutID() const { return m_lutDetails.dwLutID; }

		void SetLutFlags( const DWORD cdwFlags ) { m_lutDetails.dwFlags = cdwFlags; }
		DWORD GetLutFlags() const { return m_lutDetails.dwFlags; }

		void SetLutLocation( const EMSLOCATIOND cLoc ) { m_lutDetails.location = cLoc; }
		EMSLOCATIOND GetLutLocation() const { return m_lutDetails.location; }

		void SetLutLatitude( const EMSDEGREES cDegLat ) { m_lutDetails.location.degLatitude = cDegLat; }
		EMSDEGREES GetLutLatitude() const { return m_lutDetails.location.degLatitude; }

		void SetLutLongitude( const EMSDEGREES cDegLong ) { m_lutDetails.location.degLongitude = cDegLong; }
		EMSDEGREES GetLutLongitude() const { return m_lutDetails.location.degLongitude; }

		void SetLutAltitude( const double cdAlt ) { m_lutDetails.location.dAltitude = cdAlt; }
		double GetLutAltitude() const { return m_lutDetails.location.dAltitude; }

		void SetAntennaID( const WORD cwAntennaID ) { m_lutDetails.wAntennaID = cwAntennaID; }
		WORD GetAntennaID() const { return m_lutDetails.wAntennaID; }

		//! Serialize the entire LUT chunk into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData );

		//! Serialize the entire LUT chunk to the stream pointer specified.
		virtual DWORD Serialize( IEMSSeqStream* pStrm );

		//! Build the LUT chunk object model from the input byte array.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes );

		//! Build the LUT chunk object model from the input data stream.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm );

		DWORD GetSize() const { return sizeof(m_lutDetails); }

	private:
		EMSWAVEEXTLUTDETAILS m_lutDetails;
};

#endif