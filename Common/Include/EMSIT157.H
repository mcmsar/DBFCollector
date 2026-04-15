/********************************************************************
*	Module:			emsit157.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit157 Class
*						Detect only alerts (ABL).
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_EMSIT157
#define INC_EMSIT157

#include "emsit152.h"

#define EMS_MAX_LINES_PER_ABL_ALERT_SIT157 ( 7 )


class CEMSSit157 : public CEMSSit152
{
public:
	CEMSSit157();
	virtual ~CEMSSit157();

	virtual void Reset();

protected:
	virtual EMS_RESULT _WriteABAlertData( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );

	virtual EMS_RESULT _WriteABAlertDataLine7( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );

	virtual EMS_RESULT _ParseABAlertData( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine7( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
};


#endif // INC_EMSIT157
