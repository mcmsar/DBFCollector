/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __TSTRING_H__
#define __TSTRING_H__

#include <string>
#include <tchar.h>

typedef std::basic_string<TCHAR> tstring;

//class  tstring : public std::basic_string<TCHAR>
//{
//	public:
//		bool operator==( const TCHAR* szRHS ) const { return ( (0 == this->compare( szRHS )) ? true : false ); }
//		bool operator!=( const TCHAR* szRHS ) const { return ( (0 != this->compare( szRHS )) ? true : false ); }
//};

#endif
