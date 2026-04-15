/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __EMS_RAW_BUFF_OBJECT_H__
#define __EMS_RAW_BUFF_OBJECT_H__

#include <windows.h>
#include <winbase.h>

#include "aobjbase.h"
//#include "logclient.h"
#include "emsDBFtypes.h"

class CEMSRawBuffObj : public CApiObjBase
{
public:
	CEMSRawBuffObj();
	CEMSRawBuffObj( const CEMSRawBuffObj& rawObj );
	virtual ~CEMSRawBuffObj();

	void Initialize( unsigned long ulBuffSize );
	void Reset();
	
/*	inline void SetBuffData( const unsigned char*  aData, unsigned long ulSize )
	{
		if( m_aBuff )
			memcpy( &m_aBuff, &aData, ulSize * sizeof( unsigned char ) );
	}

	inline unsigned long GetBuffData( unsigned char*  aData, unsigned long ulMaxSize )
	{
		if( m_aBuff )
		{
			unsigned long ulSize = lMaxSize < m_ulBuffSize ? lMaxSize : m_ulBuffSize;
			memcpy( &aData, &m_rawData, ulSize * sizeof( unsigned char ) );
			return ulSize;
		}
		else
			return 0;
	}*/

	void SetBuffData( const unsigned char*  aData, unsigned long ulSize );
	unsigned long GetBuffData( unsigned char*  aData, unsigned long ulMaxSize );

	unsigned char* GetRawData(){ return m_aBuff;}
	unsigned long GetBuffSize(){ return m_ulBuffSize;}

	void SetBuffTime( EMSTIME tm ){ m_timeStamp = tm; }
	EMSTIME GetBuffTime(){ return m_timeStamp; }

	void SetPassRecs( EMSDBFPASSRECORDS& passRecs );
	EMSDBFPASSRECORDS* GetPassRecs() {return &m_PassRecords;}


	void WriteToFile( const char* szFileName ); 

private:
	unsigned long      m_ulBuffSize;

	EMSTIME			   m_timeStamp;

	EMSDBFPASSRECORDS  m_PassRecords;

	unsigned char*	   m_aBuff;
	
};

#endif
