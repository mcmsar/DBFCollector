/********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMSIT218_H__
#define __EMSIT218_H__

#include "emssit.h"
#include "gpsephem.h"
#include <string>

#define EMSSIT218_MAX_SATELLITES ( 99 )
#define EMSSIT218_MAX_SIT_LINE_LENGTH (160)

class CEMSSit218 : public CEMSSitMessageBase
{
public:
	CEMSSit218();
	virtual ~CEMSSit218();
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	int GetSatCount( void ) { return m_nSatCount; }
	int GetMaxSatCount() { return EMSSIT218_MAX_SATELLITES; }

	EMS_RESULT GetScaledEphemerisData( LPEMSSCALEDEPHEMERISDATAEX lpData, int nIndex );
	EMSUTCCONVERSION GetUtcConversionParams() { return m_utcConversion; }

protected:
	virtual int _GetMaxSitLineLength() { return EMSSIT218_MAX_SIT_LINE_LENGTH; }

private: // methods
	EMS_RESULT _ParseBody( CEMSSitTokenizer *lpTokenizer, EMSSCALEDEPHEMERISDATAEX* pData );

	EMSTIME _ConvertEpochTime( double dEpochTime );

private:	// data
	int 				m_nSatCount;
	EMSSCALEDEPHEMERISDATAEX 	m_data[ EMSSIT218_MAX_SATELLITES ];
	EMSUTCCONVERSION			m_utcConversion;
};

#endif 
