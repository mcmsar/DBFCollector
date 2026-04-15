/********************************************************************
*	Module:			emsit173.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit173  Class
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

#ifndef INC_EMSIT173
#define INC_EMSIT173

#include "emssit.h"

#define EMS_MAX_SIT173_ALERTS ( 99 ) 


class CEMSSit173 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit173();
	virtual ~CEMSSit173();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

//	EMS_RESULT AddSolution( LPEMSSIT173SOLUTION lpSolution );
private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

private:	// data
//	LPEMSSIT173SOLUTION m_lpSoln[ EMS_MAX_SIT173_ALERTS ];
};

#endif // INC_EMSIT173
