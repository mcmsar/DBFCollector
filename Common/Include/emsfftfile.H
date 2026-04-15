/********************************************************************
*	Module:			emsfftfile.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSFFTFile
*						Class to manage/create reading and writing FFT files ( for Audio )
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2005/3/5		rrr&rvw	start

********************************************************************/
#ifndef INC_EMSFFTFILE
#define INC_EMSFFTFILE

#define EMSERROR_NODEFINE_TYPES

#include "emstypes.h"
#include "emserror.h"
#include "fftdata.h"
#include "emstime.h"
#include "sigproc.h"

/*! \class CEMSFFTFile
* \brief This class encapsulates Reading and Writing Audio FFT files created
* \brief by the Wideband process.
*
*/

typedef enum
{
	EMSFFTFILE_BEGIN = 0,
	EMSFFTFILE_CURR = 1,
	EMSFFTFILE_END = 2
} EMSFFTFILESEEKMETHOD;

class CEMSFFTFile
{
public:
	CEMSFFTFile( );
	virtual ~CEMSFFTFile( );

	EMS_RESULT Open( LPCTSTR lpcszFilespec, bool bShared=true );
	EMS_RESULT Create( LPCTSTR lpcszFilespec, bool bShared=true );
	EMS_RESULT Close( void );

	bool IsOpen( void ) { return INVALID_HANDLE_VALUE != m_hFile; }

	EMS_RESULT ReadHeader( EMSFFTHEADER2 *lpHeader );
	EMS_RESULT WriteHeader( EMSFFTHEADER2 *lpHeader );

/*! \fn EMS_RESULT CEMSFFTFile::Seek( LONG lRecord )
* \brief This method positions the file pointer to the desired record index.
*
*	The current record index is first compared to the desired value and 
* if it does not match a physical seek is performed to position the file pointer 
* to the appropriate record.
* \param lRecord is a index from 0 to maximum records in the file - 1.
* \return EMS_OK if successful, or an error indicating why it failed
*/

	EMS_RESULT Seek( LONG lRecord ) { return Seek( lRecord, EMSFFTFILE_BEGIN ); }
	EMS_RESULT Seek( LONG lRecord, EMSFFTFILESEEKMETHOD seekMethod );
	EMS_RESULT Seek( EMSTIME timeRecord );

	EMS_RESULT WriteRecord( EMSFFTDATA *lpData, EMSCOMPLEX *lpBuffer, LONG lCount );
	EMS_RESULT ReadRecord( EMSFFTDATA *lpData, EMSCOMPLEX *lpBuffer, LONG lMaxCount, LONG *lpCount );

	LONG GetRecordCount( void );
	LONG GetRecordIndex( void ) { return m_lCurrentRecord; }

private: // methods
	EMS_RESULT _ReadHeader( EMSFFTHEADER2 *lpHeader, bool bRestorePosn=true );
	LONG	_GetRecordLength( void );
	EMS_RESULT _ConvertFFTHeader( EMSFFTHEADER2 *lpHdr2, EMSFFTHEADER *lpHdr1 );
	EMS_RESULT _SeekFromBOF( LONG lRecord );
	EMS_RESULT _SeekFromEOF( LONG lRecord );
	EMS_RESULT _SeekFromCurrentPosn( LONG lRecord );

private: // data
	EMSFFTHEADER2 m_hdr;
	HANDLE		m_hFile;
	bool			m_bHeaderRead;
	LONG			m_lCurrentRecord;
	CEMSTime		m_timeCurrentRecord;
	INT			m_nHdrSize;
};

#endif // INC_EMSFFTFILE
