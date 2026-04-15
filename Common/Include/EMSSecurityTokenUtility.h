
#ifndef __EMS_SECURITY_TOKEN_UTILITY__
#define __EMS_SECURITY_TOKEN_UTILITY__

#include "igateway.h"
#include "emssit.h"
#include <string>

class CEMSSecurityTokenUtility
{
	public:
		CEMSSecurityTokenUtility() {}
		~CEMSSecurityTokenUtility() {}

		void ConvertTokenToSITField( EMSGATEWAYTOKEN& token, EMSSITFIELD& sitField );
		std::wstring ConvertTokenToStringW( EMSGATEWAYTOKEN& token );
};

#endif