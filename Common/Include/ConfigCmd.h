#ifndef __CONFIG_CMD_H__
#define __CONFIG_CMD_H__

#include "igateway.h"

class CEMSCommandProcessor;

typedef enum tagConfigCmdTypes
{
	CONFIGCMD_UNKNOWN = 0,
	CONFIGCMD_GET = 1,
	CONFIGCMD_SET_STRING = 2,
	CONFIGCMD_LOG_CONTENTS = 3
} EMSCONFIGCOMMAND;

//! @class CEMSConfigCmd
//! This class is used for creating and reading Configuration Manager commands from the 
//! EMSPipeline.
class CEMSConfigCmd
{
	public:
		CEMSConfigCmd();
		CEMSConfigCmd( const CEMSConfigCmd& x );
		~CEMSConfigCmd();

		inline EMSCONFIGCOMMAND GetCommandType() { return m_eType; }

		void SetGroupType( const wchar_t* cwszVal );
		wchar_t* GetGroupType() const;

		void SetGroupID( const wchar_t* cwszVal );
		wchar_t* GetGroupID() const;

		void SetKeyName( const wchar_t* cwszVal );
		wchar_t* GetKeyName() const;

		void SetStringValue( const wchar_t* cwszVal );
		wchar_t* GetStringValue() const;

		void SetAuthorization( const EMSAUTHORIZATIONINFO& cauthInfo );
		EMSAUTHORIZATIONINFO GetAuthorization() const;

		TCHAR* Serialize( const EMSCONFIGCOMMAND ceCmdType );
		void Deserialize( CEMSCommandProcessor* pCmdProcessor );
		void SendCommand( const EMSCONFIGCOMMAND ceCmdType );

	private:	// methods
		void _SetString( wchar_t*& wszLHS, const wchar_t* cwszRHS ) const;

	private:	// data
		wchar_t* m_wszGroupType;
		wchar_t* m_wszGroupID;
		wchar_t* m_wszKeyName;
		wchar_t* m_wszStringValue;
		EMSAUTHORIZATIONINFO m_authInfo;
		EMSCONFIGCOMMAND m_eType;
};


#endif // __CONFIG_CMD_H__