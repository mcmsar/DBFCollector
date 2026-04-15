//gsoap nsEMSFPServer service name: BR_WS
//gsoap nsEMSFPServer service encoding:	literal
//gsoap nsEMSFPServer service namespace: urn:tempuri
//gsoap nsEMSFPServer schema  namespace: urn:nsEMSBRServer

#import "WS-Header.h"

typedef wchar_t* xsd__string; 

int nsEMSBRServer__Insert406Registration( xsd__string szRecords, 
										 struct nsEMSBRServer__Insert406RegistrationResponse{}& ret );

int nsEMSBRServer__Update406Registration( xsd__string szRecords, 
										 struct nsEMSBRServer__Update406RegistrationResponse{}& ret );

int nsEMSBRServer__Delete406Registration( xsd__string szRecords, 
										 struct nsEMSBRServer__Delete406RegistrationResponse{}& ret );

struct nsEMSBRServer__Int64Array
{	
	LONG64*	__ptr;
	int		__size;
};

struct nsEMSBRServer__ShortArray
{	
	short*	__ptr;
	int		__size;
};

struct nsEMSBRServer__StringArray
{	
	xsd__string*	__ptr;
	int				__size;
};

struct nsEMSBRServer__Select406RegistrationResponse
{
	xsd__string szRecords;
};

int nsEMSBRServer__Select406Registration( struct nsEMSBRServer__Int64Array strBeaconIDs, 
										 struct nsEMSBRServer__ShortArray strCountryCodes,
										 struct nsEMSBRServer__StringArray strStatus,
										 struct nsEMSBRServer__StringArray strBeaconTypes,
										 struct nsEMSBRServer__StringArray strVehicleNames,
										 struct nsEMSBRServer__Select406RegistrationResponse& ret );