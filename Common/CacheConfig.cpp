#include "cacheconfig.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "memory.h"

CEMSCacheConfig::CEMSCacheConfig()
{
}

CEMSCacheConfig::CEMSCacheConfig( const CEMSCacheConfig& x )
{
}

CEMSCacheConfig::~CEMSCacheConfig()
{
}

void
CEMSCacheConfig::_SetString( wchar_t*& wszLHS, const wchar_t* cwszRHS ) const
{
	if( wszLHS )
	{
		delete[] wszLHS;
		wszLHS = 0;
	}

	if( cwszRHS )
	{

		long lLen = wcslen( cwszRHS );

		wszLHS = new wchar_t[ lLen + 1 ];

		if( !wszLHS )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( wszLHS, 0, (lLen+1)*sizeof(wchar_t) );

		wcscpy( wszLHS, cwszRHS );
	}
}