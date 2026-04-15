/********************************************************************
*	Module:			emsit121.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit121  Class
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
#ifndef INC_EMSIT121
#define INC_EMSIT121

#include <emsit115.h>

#define EMS_MAX_SIT121_ALERTS ( 99 )
#define EMS_MAX_SIT121A_ALERTS ( 999 )
#define EMS_MAX_SIT121B_ALERTS ( 999 )

class CEMSSit121 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit121();
	virtual ~CEMSSit121();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

private:	// methods
	EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );
};



class CEMSSit121A : public CEMSSit115B
{
public:
	CEMSSit121A();
	virtual ~CEMSSit121A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

private:	// methods
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

};

class CEMSSit121B : public CEMSSit121A
{
public:
	CEMSSit121B();
	virtual ~CEMSSit121B();
	virtual void Reset( void );

private:	// methods
	virtual EMS_RESULT _GenerateSolnSide( IEMSSeqStream *lpStream, LPEMSSITLOCALERTSIDESOLN lpSide );

   virtual EMS_RESULT _ParseSolutionSideLine3( CEMSSitTokenizer* lpTokenizer, EMSSITLOCALERTSIDESOLN* pSolutionSide );
};



#endif // INC_EMSIT121
