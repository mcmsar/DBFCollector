/********************************************************************
*       Module:                 emsit270.h
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Description of CEMSSit270A Class
*                              MetOps Manoeuvre schedule notification
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

        0.0     2002 Dec 12             fjp     start

********************************************************************/

#ifndef INC_EMSIT270
#define INC_EMSIT270

#include "emssit.h"
#include "emsmanoeuvre.h"

class CEMSSit270A : public CEMSSitMessageBase
{
public:
   CEMSSit270A();
   virtual ~CEMSSit270A();

   virtual void Reset( void );

   virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
   virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

   virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
   virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

   EMS_RESULT GetManoeuvreData( EMSMANOEUVREDATA* lpData );

private: // methods
   virtual EMS_RESULT _ParseManoeuvreDataLine( CEMSSitTokenizer* lpTokenizer );

protected:
   EMSMANOEUVREDATA     m_data;
   bool                 m_bInitialized;
};

#endif // INC_EMSIT270
