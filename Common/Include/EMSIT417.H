/********************************************************************
*	Module:			emsit417.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit417 & CEMSSit417A Class
*						Time and Frequency Calibration for a SARP
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT417
#define INC_EMSIT417

#include "emssit.h"

class CEMSSit417 : public CEMSSitMessageBase
{
public:
	CEMSSit417();
	virtual ~CEMSSit417();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	virtual void Reset( void );

	ULONG GetSatelliteID( void ) { return m_ulSatID; }
	void SetSatelliteID( ULONG ulNumber ) { m_ulSatID = ulNumber; }

	ULONG GetOrbitNumber( void ) { return m_ulOrbitNumber; }
	void SetOrbitNumber( ULONG ulNumber ) { m_ulOrbitNumber = ulNumber; }

	EMSTIME GetCalibrationTime( void ) { return m_timeCalibration; }
	void SetCalibrationTime( EMSTIME t ) { m_timeCalibration = t; }

	double GetFrequency( void ) { return m_dFrequency; }
	void SetFrequency( double dFreq ) { m_dFrequency = dFreq; }

private:	// data
	ULONG				m_ulSatID;
	ULONG				m_ulOrbitNumber;
	EMSTIME			m_timeCalibration;
	double			m_dFrequency;
};

class CEMSSit417A : public CEMSSit417
{
public:
	CEMSSit417A();
	virtual ~CEMSSit417A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

	inline void SetRequestMsgNumber( int nNumber ) { m_nRequestMsgNumber = nNumber; }
	inline int GetRequestMsgNumber( void ) { return m_nRequestMsgNumber; }

	inline EMSSITCONTROLCODE GetControlCode( void ) { return m_controlCode; }
	inline void SetControlCode( EMSSITCONTROLCODE controlCode ) { m_controlCode = controlCode; }

private: // methods
	LPCTSTR _GetControlCodeText( EMSSITCONTROLCODE code );

private: // data
	EMSSITCONTROLCODE m_controlCode;
	int					m_nRequestMsgNumber;
};

class CEMSSit417B : public CEMSSit417A
{
public:
	CEMSSit417B();
	virtual ~CEMSSit417B();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

	EMSTIME GetEffectiveTime( void ) { return m_tmEffectiveTime; }
	void SetEffectiveTime( const EMSTIME effectiveTime ) { m_tmEffectiveTime = effectiveTime; }

private: // data
	EMSTIME			m_tmEffectiveTime;
};


#endif // INC_EMSIT417
