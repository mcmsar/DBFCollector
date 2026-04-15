//gsoap nsEMSADSServer service name:	ADS_WS
//gsoap nsEMSADSServer service encoding:	literal
//gsoap nsEMSADSServer service namespace: urn:tempuri
//gsoap nsEMSADSServer service namespace:	urn:nsEMSADSServer
//gsoap nsEMSADSServer service type: IADS_WS
//gsoap nsEMSADSServer service portName: ADSWS
////gsoap nsEMSADSServer service binding: ADSWSBinding
////gsoap occ600ws service location:	http://ems-satcom.com:/ADS600/WebService.cgi
//gsoap nsEMSADSServer service location: http://192.54.121.133:8181

#import "wsa.h"
#import "wsse.h"

//#import "WS-Header.h"


typedef char* xsd__string;
typedef time_t xsd__dateTime;
typedef LONG64 xsd__LONG64;

struct SOAP_ENV__Header
{  	
	mustUnderstand _wsse__Security	*wsse__Security	0; ///< WS-Security
	mustUnderstand _wsa__MessageID	 wsa__MessageID	0; ///< WS-Addressing
	mustUnderstand _wsa__RelatesTo	*wsa__RelatesTo	0; ///< WS-Addressing
	mustUnderstand _wsa__From		*wsa__From	0; ///< WS-Addressing
	mustUnderstand _wsa__ReplyTo		*wsa__ReplyTo	0; ///< WS-Addressing
	mustUnderstand _wsa__FaultTo		*wsa__FaultTo	0; ///< WS-Addressing
	mustUnderstand _wsa__To		 wsa__To	0; ///< WS-Addressing
	mustUnderstand _wsa__Action		 wsa__Action	0; ///< WS-Addressing
};


struct nsEMSADSServer__RouteList
{
	char*  Route;
};

struct nsEMSADSServer__RouteListArray
{
	struct nsEMSADSServer__RouteList*	__ptr;
	int	   	                            __size;
};

struct nsEMSADSServer__StartAfterRecord
{
    LONG64      TransmitTime;
	char*    	Route;
	int		    MessageNumber;
};

struct nsEMSADSServer__AlertCriteria
{
//	bool bUseTxStartTime;
	bool bUseTxEndTime;
	bool bUseRoute;
	bool bUseBeaconID;
	bool bUseCC;
	bool bUseFrequencyBand;

    struct nsEMSADSServer__StartAfterRecord  lastRecord;
	LONG64       i64TxEndTime;
    struct nsEMSADSServer__RouteListArray  routeList;
	xsd__string  HexBcnID;
	int          iCountryCode;
	int          iFreqBand;	// 1 for 121.5, 2 for 243.0, 3 for 406
};

// gps coordinates
struct nsEMSADSServer__GpsCoordinates
{
   float Longitude;
   float Latitude;
};

struct nsEMSADSServer__AlertRecord
{
   short int                              id;
   short int                              band;
   short int                              countryCode;
   xsd__string                            DecBcnId;
   struct nsEMSADSServer__GpsCoordinates  a;
   xsd__string                            route;
   LONG64                                 txTime;
   xsd__string                            HexBcnId;
   int                                    MessageNumber;
};

struct nsEMSADSServer__AlertRecordArray
{
	struct nsEMSADSServer__AlertRecord*	__ptr;
	int		       						__size;
};

struct nsEMSADSServer__GetAlertDataResponse
{
	int iCacheID;
	struct nsEMSADSServer__AlertRecordArray aRecs;
};


int nsEMSADSServer__GetAlertData( int iCacheID, int iRetrievalType, 
								  struct nsEMSADSServer__AlertCriteria strCriteria,
								  struct nsEMSADSServer__GetAlertDataResponse& rResponse );

