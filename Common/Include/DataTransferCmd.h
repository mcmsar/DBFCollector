#ifndef __DATA_TRANSFER_CMD_H__
#define __DATA_TRANSFER_CMD_H__

#include "igateway.h"
#include <string>

class CEMSPacketSink;

const unsigned long MAX_XFERWHERE_LEN = 1023; // string to hold either comma separated list of indices, OR where clause

typedef struct tagDataTransferCommandStructure
{
	unsigned long	ulUploadTarget;
	EMSRECORDTYPE	eRecType;
	unsigned long	ulMaxPackageSize;
	wchar_t			wszWhere[MAX_XFERWHERE_LEN+1];
} EMSDATATRANSFERCOMMANDSTRUCTURE;


//! @class CEMSDTCmd
//! This class is used for creating and reading Data Transfer commands from the 
//! EMSPipeline.
class CEMSDTCmd
{
	public:
		CEMSDTCmd();
		CEMSDTCmd( const CEMSDTCmd& x );
		~CEMSDTCmd();

		inline void SetUploadTarget( const unsigned long culUploadTarget ) { m_ulUploadTarget = culUploadTarget; }
		inline unsigned long GetUploadTarget() const { return m_ulUploadTarget; }

		inline void SetRecType( const EMSRECORDTYPE ceRecType ) { m_eRecType = ceRecType; }
		inline EMSRECORDTYPE GetRecType() const { return m_eRecType; }

		inline void SetMaxPackageSize( const unsigned long culMaxPackageSize ) { m_ulMaxPackageSize = culMaxPackageSize; }
		inline unsigned long GetMaxPackageSize() const { return m_ulMaxPackageSize; }

		inline void SetWhereClause( const wchar_t* cszWhere ) { m_wszWhere = cszWhere; }
		inline const wchar_t* GetWhereClause() const { return m_wszWhere.c_str(); }

		EMSDATATRANSFERCOMMANDSTRUCTURE Serialize() const;
		void Deserialize( CEMSPacketSink* pCmdDataSink );

	private:
		unsigned long	m_ulUploadTarget;
		EMSRECORDTYPE	m_eRecType;
		unsigned long	m_ulMaxPackageSize;
		std::wstring	m_wszWhere;
};


#endif // __DATA_TRANSFER_CMD_H__
