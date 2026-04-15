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

	$Log$
********************************************************************/

#ifndef __LPC_CLIENT_H__
#define __LPC_CLIENT_H__

#include "gatewayhelper.h"

//! Client class for accessing the LPC.  Calls are made via the Gateway,
//! providing both security and remote access.
class CEMSLPCClient : public CEMSGatewayHelper
{
	public:
		CEMSLPCClient();
		CEMSLPCClient( const CEMSLPCClient& x );
		virtual ~CEMSLPCClient();

		void InitManualProcessing(	const unsigned long culDestID,
									wchar_t* wszWhereClause,
									unsigned long& rulSessionID,
									unsigned long& rulRecords,
									EMSCALIB406DATA*& raBeaconData);
        
        void RemoveDataFromSet(		const unsigned long culDestID,
									const unsigned long culSessionID,
									const unsigned long culKeys,
									unsigned long* aulKeys);
        
        void Process406(	const unsigned long culDestID,
							const unsigned long culSessionID,
							wchar_t* wszControlFilename,
							unsigned long& rulResults,
							EMSLOCATE*& raLocations);
        
        void CancelSession(	const unsigned long culDestID,
				            const unsigned long culSessionID);
        
        void GetControlFilenames(	const unsigned long culDestID,
									unsigned long& rulCount,
									wchar_t**& rawszControlFilenames);
        
        void InitManual(	const unsigned long culDestID,
							const wchar_t* cwszWhereClause,
							const EMSMANUALPROCESSINGMODE ceProcessingMode,
							unsigned long& rulSessionID,
							unsigned long& rulRecords,
							EMSVARIANTRECORD*& raData);

};

#endif