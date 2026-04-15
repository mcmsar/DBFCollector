//! @file LPSessionID.h
//! Header file for the CEMSLPSessionID.class.
/********************************************************************
*	Module:			LPSessionID.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Nov11		CH		written

********************************************************************/

#ifndef __LP_SESSIONID_H__
#define __LP_SESSIONID_H__

//! @class CEMSLPSessionID
//! This class is used to set/check whether a session ID is associated with
//! a manual request for location processing.
//! The session ID for a manual processing session has its high order (i.e. sign bit) set
class CEMSLPSessionID
{
public:
	static bool IsManualSessionID( const unsigned long culID )
	{
		return ((long )culID < 0 ) ? true : false;
	}
	static void SetManual( unsigned long& ulID )
	{
		ulID = (unsigned long )(-1 * ulID );
	}
};

#endif // __LP_SESSIONID_H__

