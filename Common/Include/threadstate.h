/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#ifndef __THREAD_STATE_H__
#define __THREAD_STATE_H__

typedef enum tagThreadState
{
	EMS_THREAD_STATE_UNKNOWN = 0,
	EMS_THREAD_STATE_STOPPED = 1,
	EMS_THREAD_STATE_STOP_PENDING = 2,
	EMS_THREAD_STATE_RUNNING = 3,

} EMSTHREADSTATE;

#endif