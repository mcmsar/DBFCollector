/********************************************************************
*	Module:			emsit215.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit215 & CEMSSit215A Class
*						Leosar Orbit Vectors ( Earth-Fixed Format )
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

#ifndef INC_EMSIT215
#define INC_EMSIT215

#include "emssit.h"

#define EMSSIT215_MAX_SATELLITES ( 99 )

/*typedef struct tagEMSSIT215DATA
{
	ULONG	ulSatID;
	ULONG ulOrbitNumber;
	ULONG ulOrbitVectors;
	EMSTIME timeOrbit;
	EMSTIME timeEffective;
	EMSVECTOR vOrbitPosition;
	EMSVECTOR vOrbitVelocity;
} EMSSIT215DATA, *LPEMSSIT215DATA;
*/

class CEMSSit215 : public CEMSSitMessageBase
{
public:
	CEMSSit215();
	virtual ~CEMSSit215();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

	inline void SetSatCount( int nCount ) { m_nSatCount = nCount; }
	inline int GetSatCount( void ) { return m_nSatCount; }
	EMS_RESULT GetOrbitData( LPEMSSIT215DATA lpData, int nIndex );
	EMS_RESULT AddOrbitData( LPEMSSIT215DATA lpData, int nIndex = -1 );


private: // methods
   virtual EMS_RESULT   _WriteVectorLine1( IEMSSeqStream* pStrm, int iDataIndex );
   virtual EMS_RESULT   _WriteVectorLine2( IEMSSeqStream* pStrm, int iDataIndex );
   virtual EMS_RESULT   _WriteVectorLine3( IEMSSeqStream* pStrm, int iDataIndex );

   virtual EMS_RESULT _ParseOrbitVectorLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData );
   EMS_RESULT _ParseOrbitVectorLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData );
   virtual EMS_RESULT _ParseOrbitVectorLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData );

protected: // data
	EMSSIT215DATA	m_data[ EMSSIT215_MAX_SATELLITES ];

private:	// data
	int 				m_nSatCount;
};

class CEMSSit215A : public CEMSSit215
{
public:
	CEMSSit215A();
	virtual ~CEMSSit215A();

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

class CEMSSit215B : public CEMSSit215A
{
public:
   CEMSSit215B();
   virtual ~CEMSSit215B();

   virtual void         Reset( void );

private: // methods
   virtual EMS_RESULT   _WriteVectorLine1( IEMSSeqStream*, int );
   EMS_RESULT           _ParseOrbitVectorLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData );
};

class CEMSSit215C : public CEMSSit215B
{
public:
   CEMSSit215C();
   virtual ~CEMSSit215C();

   virtual void         Reset( void );

private: // methods
	virtual EMS_RESULT  _WriteVectorLine3( IEMSSeqStream* pStrm, int iDataIndex );
	virtual EMS_RESULT  _ParseOrbitVectorLine3( CEMSSitTokenizer *lpTokenizer, LPEMSSIT215DATA lpData );
};

#endif // INC_EMSIT215
