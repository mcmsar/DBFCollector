

#ifndef INC_SITSTREAM
#define INC_SITSTREAM

#include "emssit.h"
#include "emsmstrm.h"
#include "emsfstrm.h"
#include "emsdynmstrm.h"

class CEMSSitStream
{
public:
	CEMSSitStream() {}
	~CEMSSitStream() {}

	// Convert the SIT message from a byte array into a stream.
	static EMS_RESULT WriteStream( BYTE cMsg[], long lMsgSize, CEMSMemoryStream*& pStream );
	// Convert the SIT message from a SIT object into a stream.
	static EMS_RESULT GetStream( CEMSSitMessageBase* pSit, CEMSMemoryStream*& pStream );
	// Output the SIT message stream to a file.
	static EMS_RESULT WriteSITToFile( CEMSMemoryStream* pStream, TCHAR* szFileName );
	// Output the SIT byte array to a file.
	static EMS_RESULT WriteSITToFile( BYTE cMsg[], long lMsgSize, TCHAR* szFileName );
	// Convert a serialized SIT message stream into a CEMSSITMessageBase class.
	static EMS_RESULT GetClass( IEMSSeqStream* pStream, CEMSSitMessageBase*& pSIT );
	// Convert a SIT message from a SIT object into a byte array.
	static EMS_RESULT GetByteArray( CEMSSitMessageBase* pSit, BYTE*& cMsg, long& lArraySize );
	// Convert a SIT message from a byte array into a CEMSSITMessageBase class.
	static EMS_RESULT GetClass( BYTE cMsg[], long lMsgSize, CEMSSitMessageBase*& pSit );


private:
	// Create and open a SIT message file.
	static EMS_RESULT _OpenSitMsgFile( TCHAR* szFile, CEMSFileStream*& pFileStream );


};
#endif // INC_SITSTREAM
