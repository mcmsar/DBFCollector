#ifndef __LOCATION_CMD_H__
#define __LOCATION_CMD_H__

#include "igateway.h"
#include <string>

class CEMSPacketSink;

typedef enum tagLocateCmdTypes
{
	LOCCMD_UNKNOWN = 0,
	LOCCMD_INIT = 1,
	LOCCMD_REMOVE = 2,
	LOCCMD_PROCESS = 3,
	LOCCMD_CANCEL = 4,
	LOCCMD_GET_CONTROL_FILENAMES = 5
} EMSLOCATECOMMAND;


const unsigned long MAX_WHEREKEYS_LEN = 1023; // string to hold either comma separated list of indices, OR where clause
const unsigned long MAX_CONTROLFILE_LEN = 127;

typedef struct tagLocateCommandStructure
{
	EMSLOCATECOMMAND		eType;
	unsigned long			ulSessionID;
	unsigned long			ulKeyCount;
	EMSMANUALPROCESSINGMODE	eProcessingMode;
	wchar_t					wszControlFile[ MAX_CONTROLFILE_LEN + 1 ];
	wchar_t					wszWhereKeys[ MAX_WHEREKEYS_LEN + 1 ];
} EMSLOCATECOMMANDSTRUCTURE;

//! @class CEMSLocationCmd
//! This class is used for creating and reading Location Processor Controller commands from the 
//! EMSPipeline.
class CEMSLocationCmd
{
	public:
		CEMSLocationCmd();
		CEMSLocationCmd( const CEMSLocationCmd& x );
		~CEMSLocationCmd();

		inline EMSLOCATECOMMAND GetCommandType() { return m_eType; }

		inline void SetWhereClause( const wchar_t* cwszWhere ) { m_wszWhereKeys = cwszWhere; }
		inline std::wstring GetWhereClause() const { return m_wszWhereKeys; }

		inline void SetProcessingMode( const EMSMANUALPROCESSINGMODE ceMode ) { m_eProcessingMode = ceMode; }
		inline EMSMANUALPROCESSINGMODE GetProcessingMode() const { return m_eProcessingMode; }

		inline void SetSessionID( const unsigned long culSessionID ) { m_ulSessionID = culSessionID; }
		inline unsigned long GetSessionID() const { return m_ulSessionID; }

		void SetKeys( const unsigned long culKeys, const unsigned long* caulKeys );
		void GetKeys( unsigned long& ulKeys, unsigned long*& aulKeys ) const;

		inline void SetControlFile( const wchar_t* cwszFilename )  { m_wszControlFile = cwszFilename; }
		inline std::wstring GetControlFile() const { return m_wszControlFile; }

		EMSLOCATECOMMANDSTRUCTURE Serialize( const EMSLOCATECOMMAND ceCmdType );
		void Deserialize( CEMSPacketSink* pCmdDataSink );

	private:
		std::wstring	m_wszWhereKeys;
		unsigned long	m_ulSessionID;
		unsigned long	m_ulKeyCount;
		std::wstring	m_wszControlFile;
		EMSLOCATECOMMAND m_eType;
		EMSMANUALPROCESSINGMODE m_eProcessingMode;
};


#endif // __LOCATION_CMD_H__