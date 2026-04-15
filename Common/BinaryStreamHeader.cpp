
#include "igateway.h"
#include "emsmstrm.h"
#include "urlhandler.h"
#include "binarystream.h"
#include "binarystreamheader.h"

CEMSBinaryStreamHeader::CEMSBinaryStreamHeader()
{
	memset( &m_Header, 0, sizeof(EMSBINARYSTRMHEADER) );
	memset( m_Header.szEMSString, 0, sizeof(m_Header.szEMSString)/sizeof(m_Header.szEMSString[0]) );
}

CEMSBinaryStreamHeader::CEMSBinaryStreamHeader(	char* szEMSString,
												EMSTRIGGER eTrigger,
												EMSTIME timeCreation,
												EMSTIME timeModified,
												unsigned long ulSourceID,
												unsigned long ulDestID,
												EMSGATEWAYTOKEN secToken,
												EMSRECORDTYPE eRecType,
												unsigned short usDataVersion,
												unsigned long ulRecordCount )
{
	CEMSBinaryStreamHeader();

	if( szEMSString )
	{
		strncpy( m_Header.szEMSString, szEMSString, sizeof(m_Header.szEMSString)/sizeof(m_Header.szEMSString[0]) );
	}

	m_Header.trigger = eTrigger;
	m_Header.timeCreation.intTime = timeCreation.intTime;
	m_Header.timeModified.intTime = timeModified.intTime;
	m_Header.ulSourceID = ulSourceID;
	m_Header.ulDestID = ulDestID;
	memcpy( &m_Header.secToken, &secToken, sizeof(EMSGATEWAYTOKEN) );
	m_Header.eRecType = eRecType;
	m_Header.usDataVersion = usDataVersion;
	m_Header.ulRecordCount = ulRecordCount;
}

CEMSBinaryStreamHeader::~CEMSBinaryStreamHeader()
{
}

const EMSBINARYSTRMHEADER
CEMSBinaryStreamHeader::GetHeader()
{
	return m_Header;
}