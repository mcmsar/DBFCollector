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

#include "wave/riffheader.h"
#include <memory.h>
#include <string.h>

const char* CEMSRIFFHeader::ms_cszDefaultID = "RIFF";
const char* CEMSRIFFHeader::ms_cszDefaultFormat = "WAVE";

CEMSRIFFHeader::CEMSRIFFHeader()
{
	m_strRIFFHeader.dwChunkID = 0;
	m_strRIFFHeader.dwChunkSize = 0; 
	m_strRIFFHeader.dwFormat = 0;

	memcpy( &m_strRIFFHeader.dwChunkID, ms_cszDefaultID, 
		(strlen(ms_cszDefaultID) > sizeof(m_strRIFFHeader.dwChunkID)) ? sizeof(m_strRIFFHeader.dwChunkID) : strlen(ms_cszDefaultID) );

	memcpy( &m_strRIFFHeader.dwFormat, ms_cszDefaultFormat, 
		(strlen(ms_cszDefaultFormat) > sizeof(m_strRIFFHeader.dwFormat)) ? sizeof(m_strRIFFHeader.dwFormat) : strlen(ms_cszDefaultFormat) );
}

CEMSRIFFHeader::CEMSRIFFHeader( const CEMSRIFFHeader& x ) 
{
	Set( x.m_strRIFFHeader );
}

CEMSRIFFHeader::~CEMSRIFFHeader()
{
}

void 
CEMSRIFFHeader::SetMemberChunksSize( const DWORD cdwSize )
{
	m_strRIFFHeader.dwChunkSize = cdwSize + sizeof(m_strRIFFHeader.dwFormat);
}