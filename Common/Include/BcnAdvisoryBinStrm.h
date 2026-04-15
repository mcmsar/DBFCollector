/*********************************************************************
*	              Copyright (c) 2010 by EMS Technologies, Inc.,
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
#ifndef __BCN_ADVISORY_BIN_STRM_H__
#define __BCN_ADVISORY_BIN_STRM_H__

//! Class used for reading and writing a binary stream containing beacon advisory
//! data records.
class CEMSBcnAdvisoryBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSBcnAdvisoryBinStrm();

		CEMSBcnAdvisoryBinStrm( const CEMSBcnAdvisoryBinStrm& bcnAdvStrm );

		virtual ~CEMSBcnAdvisoryBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		virtual EMSVARIANTRECORD2* ReadNext2();

		virtual void WriteRecord2( const EMSVARIANTRECORD2& record );
	
		virtual EMSVARIANTRECORD3* ReadNext3();

		virtual void WriteRecord3( const EMSVARIANTRECORD3& record );
};

#endif // __BCN_ADVISORY_BIN_STRM_H__