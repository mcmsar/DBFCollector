/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include "emsit150.h"

CEMSSit150::CEMSSit150()
{
	memset( &m_locate, 0, sizeof(m_locate));
	SetSitNumber( 150 );
}

CEMSSit150::CEMSSit150( const CEMSSit150& x ) : CEMSSitSimpleMEOAlertMessageBase( x ),
												m_locate( x.m_locate )
{
	SetSitNumber( 150 );
}

CEMSSit150::~CEMSSit150()
{
}

EMS_RESULT 
CEMSSit150::_WriteFinalSolution( IEMSSeqStream* lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( !lpStream ) 
	{
		hr = EMS_INVALID_PTR;
	}

	if( EMS_OK == hr )
	{
		TCHAR szSolution[256];
		memset( szSolution, 0, sizeof(szSolution));

		_GetSolutionLine( m_locate, szSolution, 255 );

		hr = WriteLine( lpStream, szSolution );
	}

	return hr;
}


