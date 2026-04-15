/******************************************************************** 
*	Module:			chanconv.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSChannelConvertor
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

	0.0	2003 June 18 rvw	start

********************************************************************/
#ifndef INC_CHANCONV
#define INC_CHANCONV

#include "emserror.h"
#include "filesign.h"

class CEMSChannelConvertor
{
public:
	CEMSChannelConvertor();
	virtual ~CEMSChannelConvertor();

	inline void SetCurrentVersion( WORD wVersion ) { m_wCurrentVersion = wVersion; }
	inline WORD GetCurrentVersion( void ) { return m_wCurrentVersion; }
	bool IsCurrentVersion( EMSCHANNELSIGNATURE *lpInput );
	bool IsCurrentVersion( INT nChannel, WORD wVersion );

	EMS_RESULT Convert( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData = 0 );
	EMS_RESULT Convert( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, LPBYTE lpInput, INT nLength, INT nChannel, WORD wVersion );

private:	// methods
	EMS_RESULT _ConvertCalib406Data( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertLogData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertTLEData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertLocateData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertRawCBCData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertSpectrumData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertStatusData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );
	EMS_RESULT _ConvertPassScheduleData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData );

private:	// data
	WORD	m_wCurrentVersion;

};

#endif	// INC_CHANCONV
