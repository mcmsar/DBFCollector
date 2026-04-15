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

#include "emsit154.h"

CEMSSit154::CEMSSit154()
{
	SetSitNumber(154);
}

CEMSSit154::CEMSSit154( const CEMSSit154& x ) : CEMSSitMEOAlertMessageBase( x )
{
	SetSitNumber(154);
}

CEMSSit154::~CEMSSit154()
{
}