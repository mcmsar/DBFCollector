/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __DM_CONFIG_CL_H__
#define __DM_CONFIG_CL_H__

#include <string>
#include <list>
using namespace std;

class __declspec(dllexport) DataSourceConfig
{
	public:
		DataSourceConfig(): m_dTimeLimit(0.0), m_ulMaxNumOfFiles(0), m_ulMaxFileSize(0) {}

		DataSourceConfig( const DataSourceConfig& x )
		{
			m_szID   = x.m_szID;
			m_szName = x.m_szName;
			m_szType = x.m_szType;

			m_dTimeLimit = x.m_dTimeLimit;
			m_ulMaxNumOfFiles = x.m_ulMaxNumOfFiles;
			m_ulMaxFileSize = x.m_ulMaxFileSize;
		}
		virtual ~DataSourceConfig(){}

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		string GetType() { return m_szType; }
		void   SetType( const string& rszType ) { m_szType = rszType; }

		double GetTimeLimit() { return m_dTimeLimit; }
		void   SetTimeLimit( unsigned long dTimeLimit ) { m_dTimeLimit = dTimeLimit; }

		unsigned long GetMaxNumOfFiles() { return m_ulMaxNumOfFiles; }
		void          SetMaxNumOfFiles( unsigned long ulMaxNumOfFiles ) { m_ulMaxNumOfFiles = ulMaxNumOfFiles; }

		unsigned long GetMaxFileSize() { return m_ulMaxFileSize; }
		void          SetMaxFileSize( unsigned long ulMaxFileSize ) { m_ulMaxFileSize = ulMaxFileSize; }

	private:
		string   m_szID;
		string   m_szName;
		string   m_szType;

		double			 m_dTimeLimit;  
		unsigned long    m_ulMaxNumOfFiles;  
		unsigned long    m_ulMaxFileSize;  
};


class __declspec(dllexport)  DataManagerConfig
{
	public:
		DataManagerConfig();
		DataManagerConfig( const DataManagerConfig& x );
		virtual ~DataManagerConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		unsigned long GetCheckPeriod() { return m_ulCheckPeriod; }
		void          SetCheckPeriod( unsigned long ulCheckPeriod ) { m_ulCheckPeriod = ulCheckPeriod; }

		string GetDBDrive() { return m_szDBDrive; }
		void   SetDBDrive( const string& rszDBDrive ) { m_szDBDrive = rszDBDrive; }

		string GetDBName() { return m_szDBName; }
		void   SetDBName( const string& rszDBName ) { m_szDBName = rszDBName; }

		string GetDirPath() { return m_szDirPath; }
		void   SetDirPath( const string& rszDirPath ) { m_szDirPath = rszDirPath; }

		unsigned long GetMinFreeDeskSpace() { return m_ulMinFreeDeskSpace; }
		void          SetMinFreeDeskSpace( unsigned long ulMinFreeDeskSpace ) { m_ulMinFreeDeskSpace = ulMinFreeDeskSpace; }


		list<DataSourceConfig> GetDataSource(){ return m_lstDataSource ;}
		void                   SetDataSource( list<DataSourceConfig>& rolstDataSrc ){ m_lstDataSource = rolstDataSrc;}

	private:

	private:
		string         m_szID;

		unsigned long  m_ulCheckPeriod;
	
		string         m_szDBDrive;
		string         m_szDBName;
		string         m_szDirPath;

		unsigned long    m_ulMinFreeDeskSpace;  

		list<DataSourceConfig> m_lstDataSource;
};

#endif

