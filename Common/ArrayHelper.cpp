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

	$Log:
	$
********************************************************************/

#include "arrayhelper.h"
#include "emsexcpt.h"
#include <memory.h>

void 
CEMSArrayHelper::Concatenate( BYTE*& abyData, DWORD& dwDataSize, 
								const BYTE* cabyNewData, const DWORD cdwNewDataSize )
{
	BYTE* abyNewOutput = 0;

	try
	{
		if( cdwNewDataSize > 0 )
		{
			DWORD dwNewSize = dwDataSize + cdwNewDataSize;

			if( dwNewSize > 0 )
			{
				abyNewOutput = new BYTE[ dwNewSize ];

				if( !abyNewOutput )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( abyNewOutput, 0, dwNewSize );
			
				if( dwDataSize )
				{
					memcpy( abyNewOutput, abyData, dwDataSize );

					delete[] abyData;
					abyData = 0;
				}

				memcpy( abyNewOutput + dwDataSize, cabyNewData, cdwNewDataSize );

				abyData = abyNewOutput;
				abyNewOutput = 0;
				dwDataSize = dwNewSize;
			}
		}
	}
	catch( ... )
	{
		if( abyNewOutput )
		{
			delete[] abyNewOutput;
			abyNewOutput = 0;
		}

		throw;
	}
}