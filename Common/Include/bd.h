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

#ifndef __BD_H__
#define __BD_H__

#include "aobjbase.h"
#include "emsbeacontype.h"
#include "beaconsummary.h"
#include "ccaccessor.h"
#include "mlbkeyaccessor.h"
#include <string>

//! Decoder that handles different types of beacons, including MLB (Seimac), 
//! CSEL and regular C-S beacons.
class CEMSBD : public CApiObjBase
{
	public:
		CEMSBD();
		CEMSBD( const CEMSBD& x );
		~CEMSBD();

		//! Set the encrypted MLB keys file and password, and the encrypted country code
		//! file and password.
		void Init( const char* cszMLBKeysFile, const char* cszMLBDecryptPwd, 
					const char* cszCountryFile, const char* cszCFDecryptPwd );

		//! Extract the encoded beacon id.
		INT64 GetBeaconID( const char* cszBeaconData );

		//! Determine the beacon type.
		EMSBEACONTYPE GetBeaconType( const char* cszBeaconData );

		//! Get summary information for the beacon message.
		EMSBEACONSUMMARY GetBeaconSummary( const char* cszBeaconData );

	private:
		bool _IsThisCountryCode( const char* cszBeaconData );
		EMSBEACONTYPE _GetBeaconType( const char* cszBeaconData );
		INT64 _GetStandardBeaconID( const char* cszBeaconData );
		INT64 _GetMLBBeaconID( const char* cszBeaconData );
		INT64 _GetCSELBeaconID( const char* cszBeaconData );
		EMSBEACONSUMMARY _GetStandardBeaconSummary( const char* cszBeaconData );
		EMSBEACONSUMMARY _GetMLBBeaconSummary( const char* cszBeaconData );
		EMSBEACONSUMMARY _GetCSELBeaconSummary( const char* cszBeaconData );
		void _GetBeaconMsg( const char* cszBeaconData, BYTE abyBcnData[18] );

	private:
		CEMSMLBKeyAccessor	m_oMLBKeys;
		CEMSCCAccessor		m_oCCAccessor;

};

#endif