//gsoap nsEMSDCServer service name: DC_WS
//gsoap nsEMSDCServer service style:	rpc
//gsoap nsEMSDCServer service namespace: urn:tempuri
//gsoap nsEMSDCServer schema  namespace: urn:nsEMSDCServer

#import "WS-Header.h"

//! Start collecting data on the given board and channel.
int nsEMSDCServer__Start( unsigned long ulADBoardID, unsigned long ulChannelID, 
						 struct nsEMSDCServer__StartResponse{}& ret );

//! Stop collecting data on the given board and channel.
int nsEMSDCServer__Stop( unsigned long ulADBoardID, unsigned long ulChannelID, 
						 struct nsEMSDCServer__StopResponse{}& ret );

//! Set the id of the satellite data being collected on the given board and channel.
int nsEMSDCServer__SetSatelliteID( unsigned long ulADBoardID, unsigned long ulChannelID,
									unsigned long ulSatID, 
									struct nsEMSDCServer__SetSatelliteIDResponse{}& ret );

//! Definition of the GetSatelliteID response data.
struct nsEMSDCServer__GetSatelliteIDResponse
{
	unsigned long ulSatID;
};

//! Get the id of the satellite data being collected on the given board and channel.
int nsEMSDCServer__GetSatelliteID( unsigned long ulADBoardID, unsigned long ulChannelID,
									struct nsEMSDCServer__GetSatelliteIDResponse& ret );

//! Set the Input ID for the ADBoard Channel.  This is the identifier of the device
//! attached to the channel.  E.g. for a tracking antenna input, it's the antenna's ID.  
//! For a DBF antenna, it's the face ID.
int nsEMSDCServer__SetInputDataID( unsigned long ulADBoardID, unsigned long ulChannelID,
								  unsigned long ulInputDataID,
								  struct nsEMSDCServer__SetInputDataIDResponse{}& ret );

//! Definition of the _GetInputDataID response data.
struct nsEMSDCServer__GetInputDataIDResponse
{
	unsigned long ulInputDataID;
};

//! Get the Input ID for the ADBoard Channel.  This is the identifier of the device
//! attached to the channel.  E.g. for a tracking antenna input, it's the antenna's ID.  
//! For a DBF antenna, it's the face ID.
int nsEMSDCServer__GetInputDataID( unsigned long ulADBoardID, unsigned long ulChannelID,
								  struct nsEMSDCServer__GetInputDataIDResponse& ret );

//! Input a configuraton string.
int nsEMSDCServer__SetConfiguration( wchar_t* cwszConfiguration, 
									struct nsEMSDCServer__SetConfigurationResponse{}& ret );

//! Definition of GetConfiguration response data.
struct nsEMSDCServer__GetConfigurationResponse
{
	wchar_t* wszConfiguration;
};

//! Get configuration string.
int nsEMSDCServer__GetConfiguration( struct nsEMSDCServer__GetConfigurationResponse& ret );

//! Set a specific configuration item using the given key.
int nsEMSDCServer__SetConfigItem( wchar_t* wszKey, wchar_t* wszValue, 
								 struct nsEMSDCServer__SetConfigItemResponse{}& ret );

//! Definitiono f GetConfigItem response data.
struct nsEMSDCServer__GetConfigItemResponse
{
	wchar_t* wszValue;
};

//! Get a specific configuration item using the given key.
int nsEMSDCServer__GetConfigItem( wchar_t* wszKey, struct nsEMSDCServer__GetConfigItemResponse& ret );