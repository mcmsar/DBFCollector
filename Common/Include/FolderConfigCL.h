/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __FOLDER_CONFIG_CL_H__
#define __FOLDER_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) FolderConfig
{
	public:
		FolderConfig();
		FolderConfig( const string& rszFolderData, const string& rszFolderIndex, const string& rszFolderPath );
		FolderConfig( const FolderConfig& x );
		
		virtual ~FolderConfig();

		string GetFolderData() { return m_szFolderData; }
		void   SetFolderData( const string& rszFolderData ) { m_szFolderData = rszFolderData; }
        
		string GetFolderIndex() { return m_szFolderIndex; }
		void   SetFolderIndex( const string& rszFolderIndex ) { m_szFolderIndex = rszFolderIndex; }

		string GetFolderPath() { return m_szFolderPath; }
		void   SetFolderPath( const string& rszFolderPath ) { m_szFolderPath = rszFolderPath;}

	private:
		string        m_szFolderData;
		string        m_szFolderIndex;
		string        m_szFolderPath;
};

#endif