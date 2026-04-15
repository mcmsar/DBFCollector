//gsoap nsEMSBDServer service name: BeaconDecoder_WS
//gsoap nsEMSBDServer service encoding:	literal
//gsoap nsEMSBDServer service namespace: urn:tempuri
//gsoap nsEMSBDServer schema  namespace: urn:nsEMSBDServer

#import "WS-Header.h"

typedef char* xsd__string;

struct nsEMSBDServer__GetBeaconIDResponse
{	
	//! 15 Hex beacon ID.
	LONG64 i64BeaconID;
};

//! The szBeaconData string can be a 30 Hex Message or a 36 Hex Message.
int nsEMSBDServer__GetBeaconID( xsd__string szBeaconData, 
								struct nsEMSBDServer__GetBeaconIDResponse& rstrRet );

//! The beacon type.  This is a numeric enumerator that translates to a type.
struct nsEMSBDServer__GetBeaconTypeResponse
{
	int iBeaconType;
};

//! Given a 30 Hex or 36 Hex Message, return the type of beacon.
int nsEMSBDServer__GetBeaconType( xsd__string szBeaconData,
									struct nsEMSBDServer__GetBeaconTypeResponse& rstrRet );

//! Beacon message/id details
struct nsEMSBDServer__GetBeaconSummaryResponse
{
	LONG64 i64BeaconID;
	int iBeaconType;
	bool bValidLocation;
	double dLat;
	double dLong;
};

//! Given a 30 Hex or 36 Hex Message, retrieve various beacon details.
int nsEMSBDServer__GetBeaconSummary( xsd__string szBeaconData, struct nsEMSBDServer__GetBeaconSummaryResponse& rstrRet );