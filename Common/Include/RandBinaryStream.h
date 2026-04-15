/********************************************************************
*	Module:			RandBinaryStream.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
	0.0	06Nov2003		ch		start
		26Nov2003		ch		WriteRecords() to return number of records
								in stream

********************************************************************/
//! @file RandBinaryStream.h
//! This file contains the declaration of the CEMSRandBinaryStream class.

#ifndef __RANDBINARY_STREAM_H__
#define __RANDBINARY_STREAM_H__

#include "binarystream.h"

//! @class CEMSRandBinaryStream
//! The base class used for reading/writing binary data from and to a stream.
//! The underlying data stream must support random access
class CEMSRandBinaryStream : public CEMSBinaryStream
{
	public:
		CEMSRandBinaryStream();
		CEMSRandBinaryStream( const CEMSRandBinaryStream& binStream );
		CEMSRandBinaryStream( const unsigned long culMaxRecords ); // circular stream

		virtual ~CEMSRandBinaryStream();

		EMSBINARYSTRMHEADER GetHeader();


		//! @fn void ResetHeader( EMSBINARYSTRMHEADER& header );
		//! Will update the header with current record counts & write offset
		//! and write to the file.  Returns the updated header.
		void ResetHeader( EMSBINARYSTRMHEADER& header );

		//! @fn void ReadRecords( const unsigned long	culMax, 
		//!						  unsigned long&		ulRead, 
		//!						  EMSVARIANTRECORD*		aRecord );
		//! Reads the next set of records from the stream up to the specified max.
		//! The caller must delete the returned array.
		void ReadRecords(	unsigned long&		ulRead, 
							EMSVARIANTRECORD*&	aRecord );

		//! Reads the next set of records from the stream up to the specified max.
		//! The caller must delete the returned array.
		void ReadRecords(	unsigned long&		ulRead, 
							EMSVARIANTRECORD2*&	aRecord );

		//! @fn void WriteRecord( const EMSVARIANTRECORD& record );
		//! Write a single record to the stream.  
		//! Will wrap if this is a circular stream and hit the end.
		//! Overrides base class method
		void WriteRecord( const EMSVARIANTRECORD& record );

		//! Write a single record to the stream.  
		//! Will wrap if this is a circular stream and hit the end.
		//! Overrides base class method
		void WriteRecord( const EMSVARIANTRECORD2& record );

		//! @fn unsigned long WriteRecords( const unsigned long culCount, 
		//!						   const EMSVARIANTRECORD* aRecord );
		//! Write a block of records to the stream.
		//! Will wrap if this is a circular stream and hit the end.
		//! Returns the number of records in the stream.
		unsigned long WriteRecords(	const unsigned long		culCount,
							const EMSVARIANTRECORD*	aRecord );

		//! Write a block of records to the stream.
		//! Will wrap if this is a circular stream and hit the end.
		//! Returns the number of records in the stream.
		unsigned long WriteRecords(	const unsigned long		culCount,
							const EMSVARIANTRECORD2*	aRecord );

	protected:
		// Ensure that m_pStrm is populated
		void _InitStream();

		// get writable stream, positioned at the beginning of the file
		IEMSSeqStream* _GetStreamStart(); 

		// get read stream, positioned at the beginning of the data
		IEMSSeqStream* _GetRecordStreamStart(); 
		// writable stream, positioned for the next write
		IEMSSeqStream* _GetRecordStream(); 

		int _GetRecordSize();

		unsigned long _WriteRecords( const unsigned long		culCount, 
							const EMSVARIANTRECORD*	aRecord );

		unsigned long _WriteRecords( const unsigned long		culCount, 
							const EMSVARIANTRECORD2*	aRecord );

		// Local copies of information held in the header
		unsigned long m_ulMaxRecords;
		unsigned long m_ulWriteOffset;
		unsigned long m_ulRecordCount;
};

#endif // __RANDBINARY_STREAM_H__