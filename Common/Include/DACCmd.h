#ifndef __DAC_CMD_H__
#define __DAC_CMD_H__

#include "igateway.h"

class CEMSCommandProcessor;

typedef enum tagDACCmdTypes
{
	DACCMD_UNKNOWN = 0,
	DACCMD_RECOVER = 1,
	DACCMD_SEND = 2,
	DACCMD_LAST
} EMSDACCOMMAND;

//! @class CEMSDACCmd
//! This class is used for creating and reading Data Acquisition commands from the 
//! EMSPipeline.
class CEMSDACCmd
{
	public:
		CEMSDACCmd();
		CEMSDACCmd( const CEMSDACCmd& x );
		~CEMSDACCmd();

		inline EMSDACCOMMAND GetCommandType() { return m_eType; }

		void SetLuts( const unsigned long culLuts, const unsigned long* caulLutIDs );
		void GetLuts( unsigned long& ulLuts, unsigned long*& aulLutIDs ) const;

		void SetDataTypes( const unsigned long culDataTypes, const EMSRECORDTYPE* caeRecTypes );
		void GetDataTypes( unsigned long& ulDataTypes, EMSRECORDTYPE*& aeRecTypes ) const;

		void SetSourceURL( const wchar_t* cwszSrcURL );
		wchar_t* GetSourceURL() const;

		void SetStartTime( const EMSTIME timeStart ) { m_timeStart = timeStart; }
		inline EMSTIME GetStartTime() const { return m_timeStart; }

		void SetEndTime( const EMSTIME timeEnd ) { m_timeEnd = timeEnd; }
		inline EMSTIME GetEndTime() const { return m_timeEnd; }

		TCHAR* Serialize( const EMSDACCOMMAND ceCmdType ) const;
		void Deserialize( CEMSCommandProcessor* pCmdProcessor );

	private:	// methods
		void _SetLuts( TCHAR* szLuts );
		void _SetDataTypes( TCHAR* szDataTypes );

	private:	// data
		unsigned long m_ulLuts;
		unsigned long* m_aulLuts;
		unsigned long m_ulDataTypes;
		EMSRECORDTYPE* m_aDataTypes;
		wchar_t* m_wszURL;
		EMSTIME m_timeStart;
		EMSTIME m_timeEnd;
		EMSDACCOMMAND m_eType;
};


#endif // __LOCATION_CMD_H__