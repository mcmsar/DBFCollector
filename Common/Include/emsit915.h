/********************************************************************
*	Module:			emsit915.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit915  Class
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

	0.0	2003 Jan 31		LGuan	start

********************************************************************/
#ifndef INC_EMSIT915
#define INC_EMSIT915

#include "emssit.h"


class CEMSSit915 : public CEMSSitMessageBase
{
public:
	CEMSSit915();
	virtual ~CEMSSit915();

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

private: // methods
	
	EMS_RESULT CEMSSit915::_ParseText( CEMSSitTokenizer *lpTokenizer );


private:	// data

	
};

#endif // INC_EMSIT915
