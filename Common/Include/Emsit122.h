/********************************************************************
*	Module:			emsit122.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit122  Class
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
#ifndef INC_EMSIT122
#define INC_EMSIT122

#include "emssit.h"

#define EMS_MAX_SIT122_ALERTS ( 99 ) 
#define EMS_MAX_SIT122A_ALERTS ( 999 )
#define EMS_MAX_SIT122B_ALERTS ( 999 )
#define EMS_MAX_SIT122C_ALERTS ( 999 )

class CEMSSit122 : public CEMSSitAlertMessageBase
{
public:
	CEMSSit122();
	virtual ~CEMSSit122();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

protected:
	EMS_RESULT _Parse406Message( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );

private:
	virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
};

//class CEMSSit122A : public CEMSSitAlertMessageBase

class CEMSSit122A : public CEMSSit122
{
public:
	CEMSSit122A();
	virtual ~CEMSSit122A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

private:
	virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
	virtual EMS_RESULT _ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
};

class CEMSSit122B : public CEMSSit122A
{
public:
	CEMSSit122B();
	virtual ~CEMSSit122B();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

   virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
   virtual EMS_RESULT _ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
};

class CEMSSit122C : public CEMSSit122A
{
public:
	CEMSSit122C();
	virtual ~CEMSSit122C();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

   virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
   virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );
};

class CEMSSit122E : public CEMSSit122A
{
public:
	CEMSSit122E();
	virtual ~CEMSSit122E();

	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	inline WORD GetLutType( void ) { return m_wLutType; }
	inline void SetLutType( const WORD wLutType ) { m_wLutType = wLutType; }

private:
	virtual EMS_RESULT _ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );//keep
	virtual EMS_RESULT _ParseAlertLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData );

private:

	WORD    m_wLutType;
};


#endif // INC_EMSIT122
