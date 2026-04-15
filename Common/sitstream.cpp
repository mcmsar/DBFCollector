
#include "sitstream.h"
#include <stdio.h>
#include "sitparse.h"

#define MEM_STREAM_ALLOCATION_SIZE 4

EMS_RESULT
CEMSSitStream::WriteStream( BYTE cMsg[], long lMsgSize, CEMSMemoryStream*& pStream )
{
	EMS_RESULT hr = EMS_OK;

	if( lMsgSize )
	{
		pStream = new CEMSMemoryStream();

		if( pStream )
		{
			hr = pStream->Allocate( lMsgSize );

			if( SUCCEEDED(hr) )
			{
				unsigned long ulWritten = 0;
				hr = pStream->Write( cMsg, lMsgSize, &ulWritten );
			}
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}

		if( FAILED(hr) )
		{
			if( pStream )
			{
				pStream->Release();
				pStream = 0;
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::GetStream( CEMSSitMessageBase* pSit, CEMSMemoryStream*& pStream )
{
	EMS_RESULT hr = EMS_OK;

	if( !pSit )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		pStream = new CEMSMemoryStream();

		if( pStream )
		{
			hr = pSit->Generate( pStream );
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}

		if( FAILED(hr) )
		{
			if( pStream )
			{
				pStream->Release();
				pStream = 0;
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::WriteSITToFile( CEMSMemoryStream* pStream, TCHAR* szFileName )
{
	EMS_RESULT hr = EMS_OK;
	
	if( !pStream || !szFileName || !_tcslen( szFileName ) )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		// The input stream is a memory stream.
		// It needs to be written to a file stream.
		CEMSFileStream* pStrmFile = 0;
		hr = _OpenSitMsgFile( szFileName, pStrmFile );

		if( SUCCEEDED(hr) )
		{
			unsigned long ulStreamSize = pStream->GetLength();
			BYTE* pBufSit = new BYTE[ ulStreamSize ];

			unsigned long ulRead = 0;
			if( pBufSit )
			{
				memset( pBufSit, 0, ulStreamSize*sizeof(BYTE) );
				hr = pStream->SetPosition( 0 );

				if( SUCCEEDED(hr) )
				{
					hr = pStream->Read( pBufSit, ulStreamSize, &ulRead );
				}
			}
			else
			{
				hr = EMS_NO_MEMORY;
			}

			if( SUCCEEDED(hr) )
			{
				// Write it into the file stream.
				unsigned long ulWritten = 0;
				hr = pStrmFile->Write( pBufSit, ulRead, &ulWritten );
			}

			if( SUCCEEDED(hr) )
			{
				hr = pStrmFile->CloseFile();
			}

			if( pBufSit )
			{
				delete[] pBufSit;
				pBufSit = 0;
			}

			if( pStrmFile )
			{
				pStrmFile->Release();
				pStrmFile = 0;
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::WriteSITToFile( BYTE cMsg[], long lMsgSize, TCHAR* szFileName )
{
	EMS_RESULT hr = EMS_OK;

	if( !lMsgSize || !szFileName )
	{
		hr = EMS_BAD_PARAM;
	}

	if( SUCCEEDED(hr) )
	{
		CEMSFileStream* pStrmFile = 0;
		hr = _OpenSitMsgFile( szFileName, pStrmFile );

		if( SUCCEEDED(hr) )
		{
			unsigned long ulWritten = 0;
			hr = pStrmFile->Write( cMsg, lMsgSize, &ulWritten );
		}

		if( SUCCEEDED(hr) )
		{
			// Close it.
			hr = pStrmFile->CloseFile();
		}

		if( pStrmFile )
		{
			pStrmFile->Release();
			pStrmFile = 0;
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::GetClass( IEMSSeqStream* pStream, CEMSSitMessageBase*& pSit )
{
	EMS_RESULT hr = EMS_OK;

	if( !pStream )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{
		pSit = new CEMSSitMessageBase();

		if( pSit )
		{
			hr = pSit->GenerateSit( pStream );
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}

		if( FAILED(hr) )
		{
			if( pSit )
			{
				delete pSit;
				pSit = 0;
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::GetByteArray( CEMSSitMessageBase* pSit, BYTE*& cMsg, long& lArraySize )
{
	EMS_RESULT hr = EMS_OK;

	if( !pSit )
	{
		hr = EMS_INVALID_PTR;
	}
	else
	{
		// Init.
		cMsg = 0;
		lArraySize = 0;
	}

	if( SUCCEEDED(hr) )
	{
		// First convert the SIT message to a stream
		CEMSDynMemoryStream* pStream = new CEMSDynMemoryStream(MEM_STREAM_ALLOCATION_SIZE);

		if( pStream )
		{
			hr = pSit->Generate( pStream );

			if( SUCCEEDED(hr) )
			{
				// Allocate the output array.
				lArraySize = pStream->GetLength();
				cMsg = new BYTE[ lArraySize ];
				memset( cMsg, 0, lArraySize );

				// Fill the output array.
				unsigned long ulRead = 0;
				hr = pStream->SetPosition( 0 );

				if( SUCCEEDED(hr) )
				{
					hr = pStream->Read( cMsg, lArraySize, &ulRead );
				}
			}

			pStream->Release();
			pStream = 0;
		}
		else
		{
			hr = EMS_NO_MEMORY;
		}
	}

	if( FAILED(hr) )
	{
		if( cMsg )
		{
			delete[] cMsg;
			cMsg = 0;

			lArraySize = 0;
		}
	}

	return hr;
}

EMS_RESULT
CEMSSitStream::GetClass( BYTE cMsg[], long lMsgSize, CEMSSitMessageBase*& pSit )
{
	CEMSSitParser oSitParser;


	int nCount = 0;
	int nMaxSits = 1;
	EMS_RESULT hr = oSitParser.ParseSitByteArray( cMsg, lMsgSize, &pSit, nMaxSits, &nCount );

	return hr;
}

EMS_RESULT 
CEMSSitStream::_OpenSitMsgFile(	TCHAR* szFile, 
								CEMSFileStream*& pFileStream ) 
{
	EMS_RESULT hr = EMS_OK;

	if( !szFile )
	{
		hr = EMS_INVALID_PTR;
	}

	if( SUCCEEDED(hr) )
	{

		pFileStream = new CEMSFileStream();

		if ( pFileStream )
		{
			hr = pFileStream->CreateFile( szFile );

			if( FAILED(hr) )
			{
				pFileStream->Release();
				pFileStream = 0;
			}
		}
		else
			hr = EMS_NO_MEMORY;
	}

	return hr;
}