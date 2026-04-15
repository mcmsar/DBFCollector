/********************************************************************
*	Module:			emsit510.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit510 & CEMSSit510A Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
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

	0.0	2002 June 3 rvw	start

********************************************************************/
#ifndef INC_EMSIT510
#define INC_EMSIT510

#include "emssit.h"

#define EMSSIT510_MAX_SATELLITES ( 99 )

/*
typedef struct tagEMSSIT510DATA
{
	ULONG ulSatID;
	double dFreqOffset;
	double dFreqDrift;
	EMSTIME timeCalibration;
} EMSSIT510DATA, *LPEMSSIT510DATA;
*/

class CEMSSit510 : public CEMSSitMessageBase
{
public:
	CEMSSit510();
	virtual ~CEMSSit510();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );

	virtual void Reset( void );

	inline int GetSatCount( void ) { return m_nSatCount; }
	inline void SetSatCount( int nCount ) { m_nSatCount = nCount; }
	EMS_RESULT GetSatData( LPEMSSIT510DATA lpData, int nIndex );
	EMS_RESULT AddSatData( LPEMSSIT510DATA lpData, int nIndex = -1 );

private: // methods
	EMS_RESULT _ParseSitLine( CEMSSitTokenizer *lpTokenizer, int iIndex, BOOL bPeek=FALSE );

private:	// data
	int 				m_nSatCount;
	EMSSIT510DATA m_data[ EMSSIT510_MAX_SATELLITES ];
};

class CEMSSit510A : public CEMSSit510
{
public:
	CEMSSit510A();
	virtual ~CEMSSit510A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
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

#endif // INC_EMSIT510
