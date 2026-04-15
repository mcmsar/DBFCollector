/********************************************************************
*	Module:			SimpleLogger.h
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
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/05/21		rvw	start

********************************************************************/
#include <string>
#include <fstream>
#include "emstime.h"
#include "EMSCLOCK.H"

#pragma once
class CLogger
{
public:
	CLogger();
public:
	void	Init(std::string strEventName = "");
	 /**
     *   Logs a message
     *   @param sMessage message to be logged.
     */
    void Log(const std::string& sMessage);
    void LogWithTimeElapsed(std::string formatString,  double number );
	void StartTimer ();
	double GetTimeStampDiffInSecs(  );
	static void SetLevel(int nLevel);

	
    /**
     *   Funtion to create the instance of logger class.
     *   @return singleton object of Clogger class..
     */
    //CLogger* getLogger();
private:
	std::string GetCurrentDateTimeString ();
	std::string GetCurrentDateTimeStringEx ();
   
	BOOL	HasFilesizeLimitExceeded () ;
	BOOL	CloseAndCreateNewLogger ();

private:   
	enum { All=0, Debug, Info, Warning, Error, Fatal, None };
    /**
     *   copy constructor for the Logger class.
     */
    CLogger( const CLogger&){};             // copy constructor is private
    /**
     *   assignment operator for the Logger class.
     */
    CLogger& operator=(const CLogger& ){ return *this;};  // assignment operator is private
	std::string GetFileName (  );

    /**
     *   Log file name.
     **/
    std::string m_sFileName;  
	static int  m_nLevel;
	static int nFilenameIndex;
	/**
     *   Log file stream object.
     **/
    std::ofstream m_Logfile;
	std::string	m_strEventName;	
	size_t nFileWrittenBytes;
	CEMSTime timeStart;
};