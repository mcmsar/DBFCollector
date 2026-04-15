/********************************************************************
*	Module:			ESecDesc.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Definition of CEMSSecurityDescriptor class 	
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#ifndef INC_ESECDESC
#define INC_ESECDESC

#include <windows.h>
#include "emserror.h"

class CEMSSecurityDescriptor
{
public: 
	CEMSSecurityDescriptor();
	virtual ~CEMSSecurityDescriptor();

	EMS_RESULT Initialize( void );
	EMS_RESULT InitializeFromThreadToken( void );
	EMS_RESULT SetOwner( PSID lpOwner );
	EMS_RESULT SetGroup( PSID lpGroup );

	inline operator PSECURITY_DESCRIPTOR() { return m_lpSD; }

//private: // methods
	DWORD _GetTokenInfoSize( HANDLE hToken, int nTokenInfoType ); 
	EMS_RESULT _GetTokenInfo( HANDLE hToken, int nTokenInfoType, LPVOID *lplpTokenInfo );
	EMS_RESULT _CopySid( PSID *lplpNewSid, PSID lpOldSid );
	EMS_RESULT _GetThreadSids( PSID *lplpUserSid, PSID *lplpGroupSid );
	EMS_RESULT _GetProcessSids( PSID *lplpUserSid, PSID *lplpGroupSid );
	EMS_RESULT _GetTokenSids( HANDLE hToken, PSID *lplpUserSid, PSID *lplpGroupSid );
private: // data
	PSECURITY_DESCRIPTOR 	m_lpSD;
	PSID							m_lpOwner;
	PSID							m_lpGroup;
};

#endif // INC_ESECDESC
