/********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMSIT219_H__
#define __EMSIT219_H__

#include "emssit.h"
#include "gpsephem.h"
#include <string>

#define EMSSIT219_MAX_SATELLITES ( 99 )
#define EMSSIT219_MAX_SIT_LINE_LENGTH (160)

class CEMSSit219 : public CEMSSitMessageBase
{
public:
	CEMSSit219();
	virtual ~CEMSSit219();
	virtual void Reset( void );

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	int GetSatCount( void ) { return m_nSatCount; }
	int GetMaxSatCount() { return EMSSIT219_MAX_SATELLITES; }

	EMS_RESULT GetEphemeris( EMSSCALEDEPHEMERISDATAEX* pData, int nIndex );
	EMS_RESULT AddEphemeris( const EMSSCALEDEPHEMERISDATAEX& crData, int nIndex = -1 );

protected:
	virtual int _GetMaxSitLineLength() { return EMSSIT219_MAX_SIT_LINE_LENGTH; }

private: // methods
	std::string _GenerateLine( const EMSSCALEDEPHEMERISDATAEX& crData );


	EMS_RESULT _ParseLine1( CEMSSitTokenizer *lpTokenizer, EMSEPHEMERISDATA* pData );
	EMS_RESULT _DecodeLine2( EMSSCALEDEPHEMERISDATAEX* pData, LPTSTR lpszLine );
	EMS_RESULT _DecodeLine3( EMSSCALEDEPHEMERISDATAEX* pData, LPTSTR lpszLine );

	EMSTIME _ConvertEpochTime( double dEpochTime );

private:	// data
	int 				m_nSatCount;
	EMSSCALEDEPHEMERISDATAEX 	m_data[ EMSSIT219_MAX_SATELLITES ];
};

#endif // INC_EMSIT255
