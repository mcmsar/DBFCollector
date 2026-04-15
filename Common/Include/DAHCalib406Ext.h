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

#ifndef __DAH_CALIB406EXT_H__
#define __DAH_CALIB406EXT_H__

#include "dataaccesshelperbase.h"
#include "rawdatarecordreader.h"

//! Data Access Helper for Calib406 extended records.
//! This class performs local/remote data access of calib406 extended records and returns
//! data custom formatted and filtered.
class CEMSDAHCalib406Ext : public CEMSDataAccessHelperBase
{
	public:
		CEMSDAHCalib406Ext();
		CEMSDAHCalib406Ext( const CEMSDAHCalib406Ext& x );
		virtual ~CEMSDAHCalib406Ext();

		CEMSPointerList<CEMSRawDataRecordReader> Get( const ULONG culColumns, const wchar_t** cawsColumns,
														const ULONG culLutID,
														const EMSTIME ctimeStart, const EMSTIME ctimeEnd,
														const bool cbDistinct = false );

};

#endif // __DAH_CALIB406EXT_H__