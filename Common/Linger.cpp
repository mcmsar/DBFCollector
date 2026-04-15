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

#include "socket/linger.h"
#include "configurationaccessor.h"
#include "convutility.h"

const wchar_t* CEMSLinger::ms_cwszOnOff = L"Linger/OnOff";
const wchar_t* CEMSLinger::ms_cwszTimeout = L"Linger/Timeout";

#ifndef _NO_XML_
std::string 
CEMSLinger::Serialize()
{
	CEMSConfigurationAccessor oAccessor;
	
	oAccessor.SetElementValue( ms_cwszOnOff, GetOnOff() );
	oAccessor.SetElementValue( ms_cwszTimeout, GetLinger() );

	std::wstring owszSerialized = oAccessor.Serialize();

	return CEMSConversionUtil::ConvertToString( owszSerialized.c_str() );
}

void 
CEMSLinger::Deserialize( const char* cszData )
{
	if( cszData )
	{
		CEMSConfigurationAccessor oAccessor;
		oAccessor.SetSource( CEMSConversionUtil::ConvertToString( cszData ).c_str() );

		SetOnOff( oAccessor.GetElementValueUShort( ms_cwszOnOff ) );
		SetLinger( oAccessor.GetElementValueUShort( ms_cwszTimeout ) );
	}
}
#endif