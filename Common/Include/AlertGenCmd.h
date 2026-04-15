#ifndef __ALERT_GEN_CMD_H__
#define __ALERT_GEN_CMD_H__

#include "igateway.h"
#include <vector>
#include "emscc.h"

class CEMSCommandProcessor;

typedef enum tagAlertGenCmdTypes
{
	ALERTGENCMD_UNKNOWN = 0,
	ALERTGENCMD_GENERATE = 1,
	DACCMD_LAST
} EMSALERTGENCOMMAND;

//! @class CEMSAlertGenCmd
//! This class is used for creating and reading Alert Generator commands from the 
//! EMSPipeline.
class CEMSAlertGenCmd
{
	public:
		CEMSAlertGenCmd();
		CEMSAlertGenCmd( const CEMSAlertGenCmd& x );
		~CEMSAlertGenCmd();

		inline EMSALERTGENCOMMAND GetCommandType() const { return m_eType; }

		void SetDestinations( const unsigned long culDests, const unsigned long* caulDests );
		void GetDestinations( unsigned long& ulDests, unsigned long*& aulDests ) const;

		void SetLocations( const unsigned long culLocations, const EMSLOCATIONKEY* caLocations );
		void GetLocations( unsigned long& ulLocations, EMSLOCATIONKEY*& aLocations ) const;

		void SetUserID( unsigned char szUser[ EMS_MAX_USER_NAME ] );
		void GetUserID( unsigned char szUser[ EMS_MAX_USER_NAME ] );

		EMSCMDGENALERT GetCommand();

	private:	// methods

	private:	// data
		EMSCMDGENALERT		m_dataAlert;
		EMSALERTGENCOMMAND	m_eType;
};


#endif // __ALERT_GEN_CMD_H__