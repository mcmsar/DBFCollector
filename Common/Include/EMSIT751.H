/********************************************************************
*	Module:			emsit751.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit751A  Class
*						LUT Command Ack
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

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT751
#define INC_EMSIT751

#include "emssit.h"

#define EMS_SIT751A_STATUS_LEN ( 4 )

class CEMSSit751A : public CEMSSitMessageBase
{
public:
	CEMSSit751A();
	virtual ~CEMSSit751A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual void Reset( void );
	

	inline void SetAckMsgNumber( int nNumber ) { m_nAckMsgNumber = nNumber; }
	inline int GetAckMsgNumber( void ) { return m_nAckMsgNumber; }

	inline LPCTSTR GetStatus( void ) { return ( LPCTSTR ) m_szStatus; }
	void SetStatus( LPCTSTR lpcszStatus );

private:	// data
	int	m_nAckMsgNumber;
	TCHAR m_szStatus[ EMS_SIT751A_STATUS_LEN + 1 ];
};

#endif // INC_EMSIT751
