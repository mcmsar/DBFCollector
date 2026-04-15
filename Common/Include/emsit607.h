/********************************************************************
*	Module:			emsit607.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Satellite status message
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_EMSIT607
#define INC_EMSIT607

#include "emssit.h"

class CEMSSit607 : public CEMSSitMessageBase
{
	public:
		CEMSSit607();
		virtual ~CEMSSit607() {}

		virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream) { return EMS_OK; }
		virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
		virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
		virtual void Reset( void );

		void SetSatCount( const int ciCount ) { m_iSatCount = ciCount; }
		int GetSatCount() const { return m_iSatCount; }

	private: // methods

	protected: // data
		int m_iSatCount;

	private:	// data

};


#endif // INC_EMSIT607
