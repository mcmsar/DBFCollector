/********************************************************************
*	Module:			emsit161.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit161  Class
*						Historical SIT used by orig Geo600 for GeoSarr data
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
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

	0.0	2002/10/31	rvw	start

********************************************************************/
#ifndef INC_EMSIT161
#define INC_EMSIT161

#include "emssit.h"

#define EMS_MAX_SIT161_ALERTS ( 99 ) 

class CEMSSit161 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit161();
	virtual ~CEMSSit161();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

private:
	LPCSTR _Convert10to36(unsigned long ulv10, int nDigits );
	EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
	EMS_RESULT _ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
	EMS_RESULT _ParseAlertLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
};


#endif // INC_EMSIT161
