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
#ifndef __CALIB4062_BIN_STRM_H__
#define __CALIB4062_BIN_STRM_H__

//! Class used for reading and writing a binary stream containing calibrated 406 version 2
//! data records.
class CEMSCalib4062BinStrm : public CEMSBinMsgBody
{
	public:
		CEMSCalib4062BinStrm();

		CEMSCalib4062BinStrm( const CEMSCalib4062BinStrm& calib406Strm );

		virtual ~CEMSCalib4062BinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __CALIB4062_BIN_STRM_H__