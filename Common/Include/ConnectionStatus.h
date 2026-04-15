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

	$Log:
	$
********************************************************************/

#ifndef __CONNECTION_STATUS_H__
#define __CONNECTION_STATUS_H__

#include "netconnmgr.h"
#include <string>

#define EMS_CONN_STATUS_MAX 32

typedef struct _tagEMSConnectionStatus
{
	EMSCONNINFO strConnInfo;
	bool bIsActive;
} EMSCONNECTIONSTATUS, *PEMSCONNECTIONSTATUS;

typedef struct _tagEMSSystemConnectionStatus
{
	ULONG ulConnections;
	EMSCONNECTIONSTATUS astrConnections[ EMS_CONN_STATUS_MAX ];
} EMSSYSCONNECTIONSTATUS, *PEMSSYSCONNECTIONSTATUS;

#endif