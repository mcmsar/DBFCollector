/********************************************************************
*	Module:			emsit951.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit951A  Class
*						Retransmit Message Request
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

#ifndef INC_EMSIT951
#define INC_EMSIT951

#include "emssit.h"

class CEMSSit951A : public CEMSSitMessageBase
{
public:
	CEMSSit951A();
	virtual ~CEMSSit951A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	inline void SetMsgDestNumber( int nNumber ) { m_nMsgDestID = nNumber; }
	inline int GetMsgDestNumber( void ) { return m_nMsgDestID; }

	inline void SetMsgReqNumber( int nNumber ) { m_nMsgReqNumber = nNumber; }
	inline int GetMsgReqNumber( void ) { return m_nMsgReqNumber; }

	inline void SetMsgReqCount( int nNumber ) { m_nMsgReqCount = nNumber; }
	inline int GetMsgReqCount( void ) { return m_nMsgReqCount; }

private: // methods
	EMS_RESULT _ParseRequestLine( CEMSSitTokenizer *lpTokenizer );

private:	// data
	int	m_nMsgDestID;
	int	m_nMsgReqNumber;
	int	m_nMsgReqCount;
};

#endif // INC_EMSIT951
