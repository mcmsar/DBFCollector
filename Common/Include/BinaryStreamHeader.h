#ifndef __BINARY_STREAM_HEADER_H__
#define __BINARY_STREAM_HEADER_H__

class CEMSBinaryStreamHeader
{
	public:
		CEMSBinaryStreamHeader();

		CEMSBinaryStreamHeader( char* szEMSString,
								EMSTRIGGER eTrigger,
								EMSTIME timeCreation,
								EMSTIME timeModified,
								unsigned long ulSourceID,
								unsigned long ulDestID,
								EMSGATEWAYTOKEN secToken,
								EMSRECORDTYPE eRecType,
								unsigned short usDataVersion,
								unsigned long ulRecordCount );

		CEMSBinaryStreamHeader( const CEMSBinaryStreamHeader& header );

		~CEMSBinaryStreamHeader();

		const EMSBINARYSTRMHEADER GetHeader();

	private:
		EMSBINARYSTRMHEADER m_Header;
};

#endif // __BINARY_STREAM_HEADER_H__