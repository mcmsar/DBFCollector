
#include "emssecuritytokenutility.h"

#include <string>
#include "emsexcpt.h"
#include "convutility.h"

void
CEMSSecurityTokenUtility::ConvertTokenToSITField( EMSGATEWAYTOKEN& token, EMSSITFIELD& sitField )
{
	// Convert the token into a string in order to write it into the SIT Field.
	std::wstring wszString = ConvertTokenToStringW( token ); 

#if defined(UNICODE) || defined(_UNICODE)
	if( wszString.length() <= EMS_MAX_SIT_LINE_LENGTH )
	{
		wcscpy( sitField.szText, wszString.c_str() );
		sitField.nLength = wszString.length();
	}
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
	}
#else
	std::string szString = CEMSConversionUtil::ConvertToString( wszString.c_str() );

	if( szString.length() <= EMS_MAX_SIT_LINE_LENGTH )
	{
		strcpy( sitField.szText, szString.c_str() );
		sitField.nLength = szString.length();
	}
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
	}
#endif
}

std::wstring 
CEMSSecurityTokenUtility::ConvertTokenToStringW( EMSGATEWAYTOKEN& token )
{
	return CEMSConversionUtil::ConvertToString( sizeof(token.cToken), (unsigned char*) token.cToken );
}