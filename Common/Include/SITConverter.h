//! @file SITConverter.h
//! Header file for the CEMSSITConverter class.

#ifndef __SIT_CONVERTER_H__
#define __SIT_CONVERTER_H__

#include "mtl.h"

class CApiObjBase;
class CEMSSitMessageBase;

//! @class CEMSSITConverter
//! This class is used to convert SIT messages between different formats.
//! It can convert between the serialized version (for files and byte streams) of a SIT message and 
//! the deserialized version (a SIT loaded into the SIT object model).
class CEMSSITConverter : public CApiObjBase
{
	public:
		//! @fn CEMSSITConverter()
		//! @brief Default Constructor.
		CEMSSITConverter();

		//! @fn CEMSSITConverter( const CEMSSITConverter& sitConverter )
		//! @brief Copy Constructor.
		CEMSSITConverter( const CEMSSITConverter& sitConverter );

		//! @fn virtual ~CEMSSITConverter()
		//! @brief Destructor.
		virtual ~CEMSSITConverter();

		//! @fn void Serialize( CEMSSitMessageBase* pSit, IEMSSeqStream*& pStream )
		//! Converts a SIT message from a CEMSSitMessageBase to a stream.
		//! @param pSit A pointer to a SIT message class.
		//! @param pStream An input pointer to a stream.
		void Serialize( CEMSSitMessageBase* pSit, IEMSSeqStream*& pStream );

		//! @fn void Deserialize( IEMSSeqStream* pStream, int& iSits, CEMSSitMessageBase**& apSit )
		//! Converts a stream into a SIT message class.
		//! @param pStream A pointer to the SIT stream.
		//! @param ceInputType A The type of input data.
		//! @param iSits [out] The number of Sits found in the stream.
		//! @param apSit [out] An array of pointers to Sit objects.  The caller must allocate the input array and
		//! delete the objects pointed to in the returned array.
		void Deserialize( IEMSSeqStream* pStream, const EMSINPUTTYPE ceInputType, int& iSits, CEMSSitMessageBase**& apSit );

};

#endif // __SIT_CONVERTER_H__