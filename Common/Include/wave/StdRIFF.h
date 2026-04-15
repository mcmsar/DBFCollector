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

#ifndef __STD_RIFF_H__
#define __STD_RIFF_H__

#include "emswavechunk.h"
#include "aobjbase.h"
#include "riffheader.h"
#include "emspipe.h"
#include <string.h>

//! A generic RIFF chunk.
class CEMSStdRIFF : public CApiObjBase
{
	public:
		CEMSStdRIFF();
		CEMSStdRIFF( const CEMSStdRIFF& x );
		virtual ~CEMSStdRIFF();
		
		//! Write data into the RIFF's data chunk.
		virtual DWORD Write( const BYTE* cabyData, const DWORD cdwBytes ) = 0;

		//! Read data from the RIFF's data chunk.
		virtual DWORD Read( BYTE* abyData, const DWORD cdwBytes ) const = 0;
		
		//! Serialize the entire RIFF into an array of bytes.  The caller must
		//! release the returned array.  The return value is the number of bytes in the
		//! output array.
		virtual DWORD Serialize( BYTE*& abyData ) const = 0;

		//! Serialize the entire RIFF into a stream.
		virtual DWORD Serialize( IEMSSeqStream* pStrm ) const = 0;

		//! Take a stream of bytes comprising a RIFF and extract it into the object model.
		//! Returns the number of bytes read from the stream.  On return, abyData is
		//! advanced to the next byte to read from the stream and dwBytes indicates how
		//! many bytes remains to be read from the stream.
		virtual DWORD Deserialize( BYTE*& abyData, DWORD& dwBytes ) = 0;

		//! Take a stream of bytes comprising a RIFF and extract it into the object model.
		//! Returns the number of bytes read from the stream.
		virtual DWORD Deserialize( IEMSSeqStream* pStrm ) = 0;

		//! Retrieve the RIFF header.
		CEMSRIFFHeader GetHeader() const { return m_oHdr; }

	protected:
		virtual DWORD _GetMemberChunksSize() = 0;

	protected:
		CEMSRIFFHeader m_oHdr;
};

#endif