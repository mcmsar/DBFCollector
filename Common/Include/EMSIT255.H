/********************************************************************
*	Module:			emsit255.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit255A  Class
*						Leosar Orbit ( Norad 2-line Element TLE )
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

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT255
#define INC_EMSIT255

#include "emssit.h"

#define EMSSIT255A_MAX_SATELLITES ( 99 )

/*
typedef struct tagEMSSIT255ADATA
{
	ULONG	ulSatID;
	ULONG ulOrbitNumber;
	ULONG ulNoradNumber;
	ULONG ulElementNumber;
	EMSTIME timeEpoch;
  double fXndt2o;
  double fXndd6o;
  double fBStar;
  int nOrbitNumber;
	double fInclination;
	double fRightAscNode;
	double fEccentricity;
	double fArgPerigee;
	double fMeanAnomaly;
	double fMeanMotion;
} EMSSIT255ADATA, *LPEMSSIT255ADATA;
*/

class CEMSSit255A : public CEMSSitMessageBase
{
public:
	CEMSSit255A();
	virtual ~CEMSSit255A();
	virtual void Reset( void );

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	int GetSatCount( void ) { return m_nSatCount; }
	EMS_RESULT GetOrbitData( LPEMSSIT255ADATA lpData, int nIndex );
	EMS_RESULT AddOrbitData( LPEMSSIT255ADATA lpData, int nIndex = -1 );

	inline void SetRequestMsgNumber( int nNumber ) { m_nRequestMsgNumber = nNumber; }
	inline int GetRequestMsgNumber( void ) { return m_nRequestMsgNumber; }

	inline EMSSITCONTROLCODE GetControlCode( void ) { return m_controlCode; }
	inline void SetControlCode( EMSSITCONTROLCODE controlCode ) { m_controlCode = controlCode; }


private: // methods
	EMS_RESULT _ParseLine1( CEMSSitTokenizer *lpTokenizer, EMSSIT255ADATA *lpData );
	EMS_RESULT _DecodeLine2( EMSSIT255ADATA *lpData, LPTSTR lpszLine );
	EMS_RESULT _DecodeLine3( EMSSIT255ADATA *lpData, LPTSTR lpszLine );
	EMSTIME _ConvertEpochTime( double dEpochTime );
	void _CorrectRange( double * lpdValue );
	int _GetCheckSum(char* lpszBuffer);
	LPCTSTR _GetControlCodeText( EMSSITCONTROLCODE code );

private:	// data
	int 					m_nSatCount;
	EMSSIT255ADATA 	m_data[ EMSSIT255A_MAX_SATELLITES ];
	EMSSITCONTROLCODE m_controlCode;
	int					m_nRequestMsgNumber;
};

#endif // INC_EMSIT255
