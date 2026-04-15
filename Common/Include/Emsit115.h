/********************************************************************
*	Module:			emsit115.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit115  Class
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
#ifndef INC_EMSIT115
#define INC_EMSIT115

#include "emssit.h"

#define EMS_MAX_SIT115_ALERTS ( 99 )
#define EMS_MAX_SIT115A_ALERTS ( 999 )
#define EMS_MAX_SIT115B_ALERTS ( 999 )
#define EMS_MAX_SIT115C_ALERTS ( 999 )

class CEMSSit115 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit115();
	virtual ~CEMSSit115();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
};

class CEMSSit115A : public CEMSSitAlertMessageBase
{
public:
	CEMSSit115A();
	virtual ~CEMSSit115A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer* lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer* lpTokenizer );

	EMS_RESULT AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln );

	int	GetAlertCount121( void ) { return m_nAlerts121; }
	int	GetAlertCount243( void ) { return m_nAlerts243; }

private:	// methods
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

	virtual EMS_RESULT _ParseSolutionHdr( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTHEADER* pSolutionHeader );
   virtual EMS_RESULT _ParseSolutionSide( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
   virtual EMS_RESULT _ParseSolutionSideLine1( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
   virtual EMS_RESULT _ParseSolutionSideLine2( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
   virtual EMS_RESULT _ParseSolutionSideLine3( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );

protected:	// data
	int 	m_nAlerts121;
	int	m_nAlerts243;
};

class CEMSSit115B : public CEMSSit115A
{
public:
	CEMSSit115B();
	virtual ~CEMSSit115B();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer* lpTokenizer, BOOL bPeek=FALSE );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
};


class CEMSSit115C : public CEMSSit115A
{
public:
	CEMSSit115C();
	virtual ~CEMSSit115C();
	virtual void Reset( void );

private:
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

   virtual EMS_RESULT _ParseSolutionSideLine3( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
};


#endif // INC_EMSIT115
