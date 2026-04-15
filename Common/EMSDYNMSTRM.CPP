
#include "emsdynmstrm.h"
#include <math.h>

CEMSDynMemoryStream::CEMSDynMemoryStream( ULONG ulChunkSize ) : m_ulChunkSize( ulChunkSize )
{
	if( m_ulChunkSize < 1 )
		m_ulChunkSize = 1;		// must be at least one.
}

CEMSDynMemoryStream::~CEMSDynMemoryStream()
{
}

STDMETHODIMP CEMSDynMemoryStream::Write( const BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb, /* [out] */ ULONG __RPC_FAR *pcbWritten )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulBytesWritten = 0;

	if ( pv && cb )
	{
		hr = _ReAllocate( cb );

		if( SUCCEEDED(hr) )
		{
			if ( m_ulBufferPosition + cb > m_ulBufferAllocated )
				cb = m_ulBufferAllocated - m_ulBufferPosition;

			if ( cb )
			{
				memcpy( &m_lpBuffer[ m_ulBufferPosition ], pv, cb );

				ulBytesWritten = cb;
			
				m_ulBufferPosition += ulBytesWritten;

				if ( m_ulBufferPosition > m_ulBufferLength )
					m_ulBufferLength = m_ulBufferPosition;
			}
		}
		else
			hr = EMS_NOT_INITIALIZED;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( pcbWritten )
		*pcbWritten = ulBytesWritten;

	return hr;
}

EMS_RESULT
CEMSDynMemoryStream::_ReAllocate( ULONG ulBytes )
{
	EMS_RESULT hr = EMS_OK;

	// First, check if the buffer has enough space already.
	ULONG ulSpaceAvailable = _GetBytesAvailable();

	if( ulSpaceAvailable < ulBytes )
	{
		// There's not enough space.  So, allocate more room.
		ULONG ulSpaceNeeded = ulBytes - ulSpaceAvailable;

		// Get the number of chunks to allocate.
		ULONG ulNewChunks = _GetNumChunks( ulSpaceNeeded );

		// Get the number of chunks allocated.
		ULONG ulCurrentChunks = _GetNumChunks( m_ulBufferAllocated );

		LPBYTE pBuffer = 0;
		ULONG ulBufSize = 0;
		hr = _AllocateBuffer( ulNewChunks + ulCurrentChunks, pBuffer, ulBufSize );

		if( SUCCEEDED(hr) )
		{
			// Copy the existing buffer.
			memcpy( pBuffer, m_lpBuffer, m_ulBufferLength );

			// Reset the buffer.
			delete[] m_lpBuffer;
			m_lpBuffer = pBuffer;
			pBuffer = 0;
			
			m_ulBufferAllocated = ulBufSize;

		}
	}

	return hr;
}

ULONG
CEMSDynMemoryStream::_GetBytesAvailable()
{
	return (m_ulBufferAllocated - m_ulBufferPosition);
}

ULONG
CEMSDynMemoryStream::_GetNumChunks( ULONG ulBytes)
{
	ULONG ulRet = 0;

	if( 0 != ulBytes )
	{
//		ulRet = (ulBytes / m_ulChunkSize) + (fmod( ulBytes, m_ulChunkSize ) > 0 ? 1 : 0);
		ulRet = (ulBytes / m_ulChunkSize) + ((ulBytes % m_ulChunkSize) > 0 ? 1 : 0);

		if( 0 == ulRet )
			ulRet = 1;
	}

	return ulRet;
}

EMS_RESULT
CEMSDynMemoryStream::_AllocateBuffer( ULONG ulChunks, LPBYTE& pBuffer, ULONG& ulBufSize )
{
	EMS_RESULT hr = EMS_OK;

	ulBufSize = ulChunks*m_ulChunkSize;

	pBuffer = new BYTE[ulBufSize];

	if( pBuffer )
	{
		memset( pBuffer, 0, ulBufSize );
	}
	else
	{
		hr = EMS_NO_MEMORY;
	}

	return hr;
}