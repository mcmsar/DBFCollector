
#ifndef __DAL_RESULT_DECODER_H__
#define __DAL_RESULT_DECODER_H__

#include "dal.h"

class CEMSDALResultDecoder
{
	public:
		CEMSDALResultDecoder();
		~CEMSDALResultDecoder();
		
		void Decode( const unsigned long culRecordSize, const unsigned long culFields,
					const EMSFIELDDESCRIPTOR* caFields, const unsigned long culDataSize,
					const unsigned char* cabyData );
};

#endif // __DAL_RESULT_DECODER_H__