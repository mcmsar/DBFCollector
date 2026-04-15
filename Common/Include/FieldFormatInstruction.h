/*********************************************************************
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

	$Log$
********************************************************************/

#ifndef __FIELD_FORMAT_INSTRUCTION_H__
#define __FIELD_FORMAT_INSTRUCTION_H__

#include "aobjbase.h"

typedef enum tagEFormatType
{
	FORMAT_FIRST = 0,
	FORMAT_UNKNOWN = FORMAT_FIRST,
	FORMAT_DATETIME = 1,
	FORMAT_USEPRINTFSTYPE = 2,
	FORMAT_LAST = FORMAT_USEPRINTFSTYPE

} EMSDATAFORMATTYPE;

//! @class CEMSFieldFormatInstruction
//! Contains instructions for formatting a data field.
class CEMSFieldFormatInstruction : public CApiObjBase
{
	public:
		CEMSFieldFormatInstruction() : m_eType( FORMAT_UNKNOWN ) {}
		CEMSFieldFormatInstruction( const CEMSFieldFormatInstruction& x ) : m_eType( x.m_eType ) {}
		virtual ~CEMSFieldFormatInstruction() {}

		void SetFormatType( const EMSDATAFORMATTYPE ceFormatType ) { m_eType = ceFormatType; }
		EMSDATAFORMATTYPE GetFormatType() { return m_eType; }
		
	private:
		EMSDATAFORMATTYPE m_eType;
				
};

#endif