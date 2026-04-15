/******************************************************************** 
*	Module:			EMSError.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	EMS Result codes
*						
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	Copyright (c) 2000-2005 by EMS Technologies Canada, Ltd. Ottawa ON
*							All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
*	not be reproduced in whole or in part, in any form or by any means 
*	whatsoever without the express written permission of EMS Technologies 
*	Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	00/11/13		rvw		start
	14	05/01/05		ch		Moved error codes to EMSErrorMsgs.mc

********************************************************************/
#ifndef INC_EMSERROR
#define INC_EMSERROR

#include "emstypes.h"

typedef LONG EMS_RESULT;

#ifndef EMSERROR_NODEFINE_TYPES

#ifndef MAKE_HRESULT

    typedef EMS_RESULT HRESULT;
#define FACILITY_ITF 4
#define MAKE_HRESULT(sev,fac,code)						\
	((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) |   \
	((unsigned long)(code))) )

#ifndef SUCCEEDED
	#ifdef __BORLANDC__
		#define SUCCEEDED(Status) ((HRESULT)(Status) >= 0)
	#else
		#define SUCCEEDED(Status) (((unsigned long)(Status)>>31) == 0)
	#endif
#endif

#ifndef FAILED
	#ifdef __BORLANDC__
		#define FAILED(Status) ((HRESULT)(Status)<0)
	#else
		#define FAILED(Status) (((unsigned long)(Status)>>31) != 0)
	#endif
#endif

#else
//#   include <winerror.h>
#endif /* MAKE_HRESULT */

#endif // EMSERROR_NODEFINE_TYPES

//
// Return the code
//
#define EMS_CODE(emsresult)      ((emsresult) & 0x00FF)

//
//  Return the facility
//
#define EMS_FACILITY(emsresult)  (((emsresult) >> 16) & 0x1fff)

//
//  Return the category
//
#define EMS_CATEGORY(emsresult)  (((emsresult) >> 8) & 0x00ff)

//
//  Return the severity
//
#define EMS_SEVERITY(emsresult)  (((emsresult) >> 31) & 0x1)

// Note that the following macro is obsolete and should NEVER be used.
// All error codes must be defined via an MC file with a corresponding message
#define MAKE_EMS_RESULT(sev, category, code) MAKE_HRESULT(sev, FACILITY_ITF,	    \
    (unsigned)((category << 8) | (code)))

#define EMS_OK						     0x00000000
#define EMS_FALSE				 	     0x00000001

// Include EMSErrorMsgs.h so that all status codes previously defined in this file 
// are still available.
// This is a hack but is being done to limit the number of files being modified
#include "EMSErrorMsgs.h"

#endif // INC_EMSERROR
