/********************************************************************
*	Module:			emsit760.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit760  Class
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
#ifndef INC_EMSIT760
#define INC_EMSIT760

#include "emssit.h"

class CEMSSit760A : public CEMSSitMessageBase
{
public:
	CEMSSit760A();
	virtual ~CEMSSit760A();

	virtual void SetMsgHeader( CEMSSitMessageBase *lpSitMsg );
	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual void Reset( void );

	inline int GetCheckCode( void ) { return m_nCheckCode; }
	inline void SetCheckCode( int nCheckCode ) { m_nCheckCode = nCheckCode; }

	inline int GetCheckSum( void ) { return m_nCheckSum; }
	inline void SetCheckSum( int nCheckSum ) { m_nCheckSum = nCheckSum; }

	inline EMSSITCONTROLCODE GetControlCode( void ) { return m_controlCode; }
	inline void SetControlCode( EMSSITCONTROLCODE controlCode ) { m_controlCode = controlCode; }

	inline CEMSSitMessageBase *GetSitMsg( void ) { return m_lpSitMsg; }
	inline void SetSitMsg( CEMSSitMessageBase *lpSitMsg ) { m_lpSitMsg = lpSitMsg; }

	void SetSecurityToken( EMSSITFIELD sitField );
	EMSSITFIELD GetSecurityToken();

private: // method
	LPCTSTR _GetControlCodeText( EMSSITCONTROLCODE code );
	EMS_RESULT _GenerateSpecialFields( IEMSSeqStream* lpStream );

private:	// data
	int			m_nCheckCode;
	int			m_nCheckSum;
	EMSSITCONTROLCODE m_controlCode;
	CEMSSitMessageBase *m_lpSitMsg;
	int			m_nFldCount;
	EMSSITFIELD m_sitField[ 16 ];
};

#endif // INC_EMSIT760
