/********************************************************************
*       Module:                 emsit662.h
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Description of CEMSSit662A Class
*                              GeoLUT data collection summary
*       Usage:
*       Entry Point:
*       Input Files:
*       Output Files:
*       Comments:       
*                                       
*
*********************************************************************
*                     Copyright (c) 2002 by EMS Technologies, Inc.,
*                                                                               All rights reserved
*       This program is unpublished software and contains the trade secrets
*       and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

        Rev     Date                    Auth    Changes
        ===     ====                    ====    =======

        0.0     2002 Dec 20             fjp     start

********************************************************************/

#ifndef INC_EMSIT662
#define INC_EMSIT662

#include "emssit.h"
#include "emscollsummary.h"

class CEMSSit662A : public CEMSSitMessageBase
{
public:
   CEMSSit662A();
   virtual ~CEMSSit662A();

   virtual void Reset( void );

   virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
   virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

   EMS_RESULT SetCollectionSummary( EMSCOLLECTIONSUMMARY* lpData );
   EMS_RESULT GetCollectionSummary( EMSCOLLECTIONSUMMARY* lpData );

private: // methods
   EMS_RESULT _GenerateSitBodyLine1( IEMSSeqStream *lpStream );
   EMS_RESULT _GenerateSitBodyLine2( IEMSSeqStream *lpStream );

   virtual EMS_RESULT _ParseCollectionSummaryLine1( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParseCollectionSummaryLine2( CEMSSitTokenizer* lpTokenizer );

protected:
   EMSCOLLECTIONSUMMARY    m_data;
   bool                    m_bInitialized;
};

#endif // INC_EMSIT662
