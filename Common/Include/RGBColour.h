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

#ifndef __RGB_COLOUR_H__
#define __RGB_COLOUR_H__

#include "aobjbase.h"

//! @class CEMSRGBColour
//! Stores the elements of an RGB colour.
class CEMSRGBColour : public CApiObjBase
{
	public:
		CEMSRGBColour();
		CEMSRGBColour( const short csRed, const short csGreen, const short csBlue );
		CEMSRGBColour( const CEMSRGBColour& x );
		~CEMSRGBColour();

		void Set( const short csRed, const short csGreen, const short csBlue );

		short GetRed() const { return m_sRed; }
		short GetGreen() const { return m_sGreen; }
		short GetBlue() const { return m_sBlue; }

		CEMSRGBColour& operator=( const CEMSRGBColour& x );

	private:
		short m_sRed;
		short m_sGreen;
		short m_sBlue;
};

#endif;