/********************************************************************
*	Module:			emsit970.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit970  Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#ifndef INC_EMSIT970
#define INC_EMSIT970

#include "emssit.h"


class CEMSSit970 : public CEMSSitMessageBase
{
public:
	CEMSSit970();
	virtual ~CEMSSit970();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

	int GetSatelliteID( void ) { return m_nSatID; }
	void SetSatelliteID( int nNumber ) { m_nSatID = nNumber; }

	int GetPassID( void ) { return m_nPass; }
	void  SetPassID( int nNumber ) { m_nPass = nNumber; }

	void SetMsgType( TCHAR cMsgType ) { m_cMsgType = cMsgType; }
	EMS_RESULT SetMsgSource( LPCTSTR lpcszSource );
	EMS_RESULT SetMsgText( LPCTSTR lpcszText );

	EMS_RESULT SetAdvisoryMessage( LPCTSTR lpcszSource, TCHAR cMsgType, LPCTSTR lpcszMsgText );

	void Reset( void );

private: // methods
	void _ResetStrings( void );

private: // data
	int 				m_nSatID;
	int 				m_nPass;
	TCHAR				m_cMsgType;
	LPTSTR			m_lpszMsgSource;
	LPTSTR			m_lpszMsgText;
};

#endif // INC_EMSIT970
