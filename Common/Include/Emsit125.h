/********************************************************************
*	Module:			emsit125.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit125  Class
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

#ifndef INC_EMSIT125
#define INC_EMSIT125

#include <emsit115.h>
#include <emssit.h>

#define EMS_MAX_SIT125_ALERTS ( 99 ) 
#define EMS_MAX_SIT125A_ALERTS ( 999 ) 
#define EMS_MAX_SIT125B_ALERTS ( 999 ) 

class CEMSSit125 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit125();
	virtual ~CEMSSit125();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
};

class CEMSSit125A : public CEMSSit115A
{
public:
	CEMSSit125A();
	virtual ~CEMSSit125A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

private:	// methods
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
   virtual EMS_RESULT _ParseSolutionHdr( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTHEADER* pSolutionHeader );
};


class CEMSSit125B : public CEMSSit125A
{
public:
	CEMSSit125B();
	virtual ~CEMSSit125B();
	virtual void Reset( void );

private:	// methods
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
   virtual EMS_RESULT _ParseSolutionSideLine3( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
};

#endif // INC_EMSIT125
