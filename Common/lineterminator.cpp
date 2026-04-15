#include "lineterminator.h"

// Default valid read terminators.
const long clNumDefTerminators = 3;
TCHAR* alpcszDefTerminators[] = { _T("\r\n"), _T("\n"), _T("\r\r\n") };

// Default write terminators.
TCHAR* lpcszDefUseWriteTerminators = _T("\r\r\n\0");


CEMSLineTerminator::CEMSLineTerminator() : m_alpszTerminators(0), m_lNumTerminators(0)
{
	memset( m_lpszTerminator, 0, clWriteTermMaxLength*sizeof(TCHAR) );
	SetValid( clNumDefTerminators, (TCHAR**) alpcszDefTerminators );
	Use( lpcszDefUseWriteTerminators );
}

CEMSLineTerminator::CEMSLineTerminator( CEMSLineTerminator& oLT ) : m_alpszTerminators(0), m_lNumTerminators(0)
{
	memset( m_lpszTerminator, 0, clWriteTermMaxLength*sizeof(TCHAR) );

	SetValid( oLT.m_lNumTerminators, oLT.m_alpszTerminators );
	Use( oLT.m_lpszTerminator );
}

CEMSLineTerminator::~CEMSLineTerminator()
{
	_ReleaseTerminators();
	_ReleaseWriteTerminator();
}


EMS_RESULT
CEMSLineTerminator::SetValid( const long clCount, TCHAR** alpszTerminators )
{
	EMS_RESULT hr = EMS_OK;

	if( clCount > 0 )
	{
		_ReleaseTerminators();

		m_alpszTerminators = new TCHAR*[clCount];

		if( m_alpszTerminators )
		{
			memset( m_alpszTerminators, 0, clCount*sizeof(TCHAR*) );
			m_lNumTerminators = clCount;

			for( long l = 0; l < clCount; l++ )
			{
				long lSize = _tcslen(alpszTerminators[l]) + 1;
				m_alpszTerminators[l] = new TCHAR[ lSize ];

				if( m_alpszTerminators[l] )
				{
					memset( m_alpszTerminators[l], 0, lSize );

					_tcsncpy( m_alpszTerminators[l], alpszTerminators[l], lSize - 1 );
				}
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSLineTerminator::AddValid( TCHAR* lpszTerminator )
{
	return EMS_NOT_IMPLEMENTED;	// not implemented.
}

EMS_RESULT
CEMSLineTerminator::Use( TCHAR* lpszTerminator )
{
	HRESULT hr = EMS_OK;

	if( lpszTerminator )
	{
		if( _tcslen(lpszTerminator) < clWriteTermMaxLength )
		{
			_ReleaseWriteTerminator();
			_tcsncpy( m_lpszTerminator, lpszTerminator, clWriteTermMaxLength - 1 );
		}
		else
		{
			// Too long.
			hr = EMS_OVERFLOW;
		}
	}

	return hr;
}

TCHAR* 
CEMSLineTerminator::WriteEOL()
{
	return m_lpszTerminator;
}

BOOL
CEMSLineTerminator::IsEOL( TCHAR* lpszField )
{
	BOOL bIsEOL = FALSE;

	if( lpszField )
	{
		for( long l = 0; l < m_lNumTerminators && !bIsEOL; l++ )
		{
			if( m_alpszTerminators[l] )
			{
				if( 0 == _tcscmp( m_alpszTerminators[l], lpszField ) )
				{
					bIsEOL = TRUE;
				}
			}
		}
	}

	return bIsEOL;

}

BOOL
CEMSLineTerminator::IsEOL( TCHAR cValue )
{
	BOOL bIsEOL = FALSE;

	// Iterate over the valid sequences.
	for( long l = 0; l < m_lNumTerminators && !bIsEOL; l++ )
	{
		// Search the sequence for the character.
		if( _tcschr( m_alpszTerminators[l], cValue ) )
		{
			bIsEOL = TRUE;;
		}
	}

	return bIsEOL; 
}

BOOL
CEMSLineTerminator::MatchesEOLSequence( TCHAR cValue, unsigned long ulPos )
{
	// This method could become much more sophisticated (and accurate) if
	// it maintained state.  That would be necessary to ensure that an entire
	// sequence of characters matches rather than individual characters.

	BOOL bMatches = FALSE;

	// Iterate over the valid sequences
	for( long l = 0; l < m_lNumTerminators && !bMatches; l++ )
	{
		// Make sure the index exists in the sequence.
		if( ulPos < _tcslen( m_alpszTerminators[l] ) )
		{
			// Does it match?
			if( cValue == m_alpszTerminators[l][ulPos] )
			{
				bMatches;
			}
		}
	}

	return bMatches;
}

void
CEMSLineTerminator::_ReleaseWriteTerminator()
{
	// Clear it.
	memset( m_lpszTerminator, 0, clWriteTermMaxLength*sizeof(TCHAR) );
}

void
CEMSLineTerminator::_ReleaseTerminators()
{
	if( m_alpszTerminators )
	{
		for( long l = 0; l < m_lNumTerminators; l++ )
		{
			if( m_alpszTerminators[l] )
			{
				delete[] m_alpszTerminators[l];
				m_alpszTerminators[l] = 0;
			}
		}

		delete[] m_alpszTerminators;
		m_alpszTerminators = 0;

		m_lNumTerminators = 0;
	}

}