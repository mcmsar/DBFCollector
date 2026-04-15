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

#ifndef __RIFF_HEADER_H__
#define __RIFF_HEADER_H__

#include "emswavechunk.h"
#include "aobjbase.h"

//! The header portion of a RIFF chunk.
class CEMSRIFFHeader : public CApiObjBase
{
	public:
		CEMSRIFFHeader();
		CEMSRIFFHeader( const CEMSRIFFHeader& x );
		virtual ~CEMSRIFFHeader();

		//! Set the chunk id field.  This is typically equal to "RIFF".
		void SetChunkID( const DWORD cdwChunkID ) { m_strRIFFHeader.dwChunkID = cdwChunkID; }

		//! Get the chunk id field.
		DWORD GetChunkID() const { return m_strRIFFHeader.dwChunkID; }

		//! Set the chunk size.  This is the size of the entire RIFF in bytes, not including
		//! the chunk id and chunk size fields.
		void SetChunkSize( const DWORD cdwChunkSize ) { m_strRIFFHeader.dwChunkSize = cdwChunkSize; }

		//! Get the chunk size.
		DWORD GetChunkSize() const { return m_strRIFFHeader.dwChunkSize; }

		//! Set the RIFF format.  This value indicates the type of RIFF.  For example,
		//! it could be WAV, AVI, etc.
		void SetFormat( const DWORD cdwFormat ) { m_strRIFFHeader.dwFormat = cdwFormat; }

		//! Get the RIFF format.
		DWORD GetFormat() const { return m_strRIFFHeader.dwFormat; }

		//! Set the contents of the entire RIFF header.
		void Set( const EMSWAVERIFFHEADER cstrRIFFHeader ) { m_strRIFFHeader = cstrRIFFHeader; }

		//! Get the contents of the entire RIFF header.
		EMSWAVERIFFHEADER Get() const { return m_strRIFFHeader; }

		//! Set the sum of the sizes of the chunks comprising this RIFF.  The value is used to set the
		//! header's ChunkSize field.  For example, in a WAVE RIFF, this would be the sum of the format
		//! and data chunk sizes.
		void SetMemberChunksSize( const DWORD cdwSize );

		//! Get the total size in bytes of the RIFF header.
		DWORD GetSize() const { return sizeof(m_strRIFFHeader); }

	private:
		EMSWAVERIFFHEADER	m_strRIFFHeader;

	private:	// constants
		//! The default chunk id.
		static const char* ms_cszDefaultID;

		//! The default RIFF format/type.
		static const char* ms_cszDefaultFormat;

};

#endif