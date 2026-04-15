/********************************************************************
*	Module:			emsit172.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit172  Class
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
#ifndef INC_EMSIT172
#define INC_EMSIT172

#include <stdio.h>
#include "emssit.h"
#include "bcncount.h"	//CEMSBeaconTimeCounter


#define EMS_MAX_SIT172_ALERTS ( 99 ) 

class CEMSSit172 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit172();
	virtual ~CEMSSit172();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln );

	void SetInvertedFSOnly( bool bFlag ) { m_bInvertedFSOnly = bFlag; }
	void SetBeaconWildcard( INT64 i64Prefix, INT64 i64Mask )
		{ m_i64BeaconPrefix = i64Prefix; m_i64BeaconMask = i64Mask; }

protected:
	EMS_RESULT _Parse406Message( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );

private: // methods
	virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );

private: // data
	bool						m_bInvertedFSOnly;
	INT64						m_i64BeaconPrefix;
	INT64						m_i64BeaconMask;
	CEMSBeaconTimeCounter m_bcnFirstMsg;
};

#endif // INC_EMSIT172
