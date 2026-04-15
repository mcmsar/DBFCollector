/********************************************************************
*	Module:			sitparse.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSitParser class
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
#ifndef INC_SITPARSE
#define INC_SITPARSE

#include "emstypes.h"
#include "emspipe.h"
#include "emserror.h"
#include "emstime.h"
#include "sittoken.h"
#include "emssit.h"
#include <list>

class CEMSSitParser
{
public:
	CEMSSitParser( );
	virtual ~CEMSSitParser();

	EMS_RESULT ParseSit( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg );
	EMS_RESULT ParseXML( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg );
	EMS_RESULT ParseCSV( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg );
	EMS_RESULT ParseSitFile( LPCTSTR lpcszSitFile, CEMSSitMessageBase **lplpSitMsg, 
										int nMaxSits, int *lpnSitCount );
	EMS_RESULT ParseSitStream(	IEMSSeqStream *lpStream, 
								int nMaxSits, 
								int *lpnSitCount, 
								CEMSSitMessageBase **lplpSitMsg );

	EMS_RESULT ParseSitStream(	IEMSSeqStream *lpStream, 
								std::list<CEMSSitMessageBase*>& lstpSitMsg );

	EMS_RESULT ParseSitByteArray(	BYTE cMsg[], 
									long lMsgSize, 
									CEMSSitMessageBase** lplpSitMsg, 
									int nMaxSits, 
									int* lpnSitCount );

private:
	CEMSSitMessageBase 		m_sitMsg;
};

#endif // INC_SITPARSE
