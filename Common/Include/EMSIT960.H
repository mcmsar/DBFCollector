/********************************************************************
*	Module:			emsit960.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit960  Class
*						Historical SIT used by Trenton Geo500 for GeoSarr data
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
#ifndef INC_EMSIT960
#define INC_EMSIT960

#include "emssit.h"

#define EMS_MAX_SIT960_ALERTS ( 999 ) 

class CEMSSit960 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit960();
	virtual ~CEMSSit960();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	inline void SetLutID( ULONG ulLutID ) { m_ulLutID = ulLutID; }
	inline ULONG GetLutID( void ) { return m_ulLutID; }

private:
	EMS_RESULT _SetBeaconMsgAndID( LPCTSTR lpcszBeaconMsg, LPEMSSITLOCALERTSOLUTION lpAlertData );
	EMS_RESULT _ParseAlertHeader( CEMSSitTokenizer *lpTokenizer );
	EMS_RESULT _ParseAlertLine( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
	EMS_RESULT _ParseAlertTrailer( CEMSSitTokenizer *lpTokenizer );

private: // data
	ULONG			m_ulLutID;
};


#endif // INC_EMSIT960
