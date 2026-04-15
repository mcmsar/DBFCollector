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

#ifndef __CALIB406EX_BIN_STRM_H__
#define __CALIB406EX_BIN_STRM_H__

//! @class CEMSCalib046ExBinStrm
//! Class used for reading and writing a binary stream containing extended calibrated 406
//! data records.
class CEMSCalib406ExBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSCalib406ExBinStrm();
		CEMSCalib406ExBinStrm( const CEMSCalib406ExBinStrm& calib406Strm );
		virtual ~CEMSCalib406ExBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();
		virtual void WriteRecord( const EMSVARIANTRECORD& record );
		EMSVARIANTRECORD2* ReadNext2();
		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif 