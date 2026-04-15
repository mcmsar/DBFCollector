/********************************************************************
*	Module:			emsdal.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Declaration of CEMSDALProvider. Implements the data
*					access layer allowing retrieval, insertion,
*					update and deletion of records.
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************
	$Log$
Log. For some reason, $Log keyword made into the revision
	       history comments, which is causing these problems.
	 11   Include   1.10        2002/12/03 14:28:01    Hussein Said    last one
	       seems to have wroked. One final sanity check.
	 10   Include   1.9         2002/12/03 14:27:04    Hussein Said    yet another
	       try
	 9    Include   1.8         2002/12/03 14:25:22    Hussein Said    yet another
	       try to check in the file
	 8    Include   1.7         2002/12/03 14:24:46    Hussein Said    One more
	       try.
	 7    Include   1.6         2002/12/03 14:16:09    Hussein Said    soemthing
	       has gone horribly wrong. One more try.
	 6    Include   1.5         2002/12/03 14:15:30    Hussein Said    Fixed more
	       keyowrd expnasion issues.

	 5    Include   1.4         2002/12/03 09:30:49    Hussein Said    fixed $LOG
	       issues.
	 4    Include   1.3         2002/12/03 09:01:29    Hussein Said    limited
	       $Log entries to 20
	 3    Include   1.2         2002/12/03 08:59:11    Hussein Said    added $LOG$
	       information
	 2    Include   1.1         2002/12/03 08:57:47    Hussein Said    added
	       required includes.
Added revision and Header information
	 1    Include   1.0         2002/10/21 16:21:32    Jason Bass      
	$[20]$
   $Header$     

********************************************************************/

#ifndef __EMSBASE_H__
#define __EMSBASE_H__

// standard includes
#include <string>          // STD library
using std::string;

// EMS includes
#include <criticalsection.h>

class CEMSBase
{
public:
	CEMSBase() : m_ulRefCount(1)
	{
	}

	CEMSBase( const char* cszClassName ) : m_ulRefCount(1), m_szClassName(cszClassName)
	{
	}

	virtual ~CEMSBase()
	{
	}

	unsigned long AddRef()
	{
		m_CS.Enter();
		m_ulRefCount++;
		m_CS.Leave();

		return m_ulRefCount;
	}

	unsigned long Release()
	{
		m_CS.Enter();
		m_ulRefCount--;
		m_CS.Leave();

		if( 0 == m_ulRefCount )
		{
			delete this;
			return 0;

		}

		return m_ulRefCount;
	}

protected:
	string m_szClassName;

private:
	CEMSCriticalSection m_CS;
	unsigned long m_ulRefCount;

};

#endif	// __EMSBASE_H__