/********************************************************************
*	Module:			emsit152.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit152 Class
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

#ifndef INC_EMSIT152
#define INC_EMSIT152

#include "emssit.h"

#define EMS_MAX_LINES_PER_ABL_ALERT_SIT152 ( 6 )


class CEMSSit152 : public CEMSSitMessageBase
{
public:
	CEMSSit152();
	virtual ~CEMSSit152();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset();

	virtual EMS_RESULT AddABLAlert( const EMSSITABLDATA& crABLSITData );

	inline int GetAlertCount( void ) { return m_iAlertCount; }
	int GetMaxAlertCount( void );

	inline int GetSatelliteID( void ) { return m_iSatID; }
	inline void SetSatelliteID( int iSatID ) { m_iSatID = iSatID; }

	EMS_RESULT GetABLAlert( LPEMSSITABLDATA lpABLSITData, int nIndex );

protected:
	inline void _SetAlertCount( int iCount ) { m_iAlertCount = iCount; }
	inline int  _IncrAlertCount( void ) { return ++m_iAlertCount; }

	inline int  _GetNumAlertsToParse() { return m_iAlertsToParse; }
	inline void _SetNumAlertsToParse( int iCount ) { m_iAlertsToParse = iCount; }

	virtual EMS_RESULT _WriteABAlertData( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );

	virtual EMS_RESULT _WriteABAlertDataLine1( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _WriteABAlertDataLine2( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _WriteABAlertDataLine3( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _WriteABAlertDataLine4( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _WriteABAlertDataLine5( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _WriteABAlertDataLine6( IEMSSeqStream *lpStream, LPEMSSITABLDATA lpSitABLData );

	virtual EMS_RESULT _ParseABAlertData( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine4( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine5( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );
	virtual EMS_RESULT _ParseABAlertLine6( CEMSSitTokenizer *lpTokenizer, LPEMSSITABLDATA lpSitABLData );

private:
	int 	m_iAlertCount;
	int     m_iAllocCount;
	int		m_iSatID;       //Dummy Satellite ID.
	int     m_iAlertsToParse;
	LPEMSSITABLDATA	m_lpABAlerts;
};


#endif // INC_EMSIT152
