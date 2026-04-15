/*********************************************************************
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

	$Log:
	$
********************************************************************/

#ifndef __DAL_ORBIT_H__
#define __DAL_ORBIT_H__

#include "dalclient.h"
#include "emsorbit.h"
#include "pointerlist.h"
#include "rawdatarecordreader.h"

#include <string>


//! Retrieves orbit data via the DAL.
class CEMSDALOrbit
{
	public:
		CEMSDALOrbit();
		CEMSDALOrbit( const CEMSDALOrbit& x );
		virtual ~CEMSDALOrbit();

		bool GetTLE( const ULONG culSatID, const EMSTIME ctimeTLEEffective, EMSTLEDATA& rtleData );

	private:
		std::wstring _BuildTLESQL( const ULONG culSatID, const EMSTIME ctimeEffective );

		EMSTLEDATA _AssembleTLE( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords );

		CEMSPointerList<CEMSRawDataRecordReader> _ProcessData( const ULONG culFields, 
													const EMSFIELDDESCRIPTOR* caFields,
													const ULONG culDataSize, 
													const unsigned char* cabyData,
													const ULONG culRecordSize );

	private:
		 CEMSDALClient m_oDALClient;
};

#endif