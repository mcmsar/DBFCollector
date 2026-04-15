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

#include "rgbcolour.h"

CEMSRGBColour::CEMSRGBColour() : m_sRed(0), m_sGreen(0), m_sBlue(0)
{
}

CEMSRGBColour::CEMSRGBColour( const short csRed, const short csGreen, const short csBlue ) : m_sRed( csRed ),
																							m_sGreen( csGreen ),
																							m_sBlue( csBlue )
{
}

CEMSRGBColour::CEMSRGBColour( const CEMSRGBColour& x ) : m_sRed( x.m_sRed ), 
														m_sGreen( x.m_sGreen ), 
														m_sBlue(x.m_sBlue )
{
}

CEMSRGBColour::~CEMSRGBColour()
{
}

void 
CEMSRGBColour::Set( const short csRed, const short csGreen, const short csBlue )
{
	m_sRed = csRed;
	m_sGreen = csGreen;
	m_sBlue = csBlue;
}

CEMSRGBColour& 
CEMSRGBColour::operator=( const CEMSRGBColour& x )
{
	Set( x.m_sRed, x.m_sGreen, x.m_sBlue );

	return *this;
}