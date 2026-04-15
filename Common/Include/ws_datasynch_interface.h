//gsoap nsEMSSynchServer service name: SynchEngine_WS
//gsoap nsEMSSynchServer service encoding:	literal
//gsoap nsEMSSynchServer service namespace: urn:tempuri
//gsoap nsEMSSynchServer schema  namespace: urn:nsEMSSynchServer

#import "WS-Header.h"

typedef wchar_t* xsd__string; 

int nsEMSSynchServer__ConfigureSynchService( xsd__string szSynchConfigs, 
										     struct nsEMSSynchServer__ConfigureSynchServiceResponse{}& ret );

int nsEMSSynchServer__SynchAll( struct nsEMSSynchServer__SynchAllResponse{}& ret );

int nsEMSSynchServer__Synch( xsd__string szSynchName, 
							 struct nsEMSSynchServer__SynchResponse{}& ret );

int nsEMSSynchServer__AddSynch( xsd__string szSynchConfig, 
								struct nsEMSSynchServer__AddSynchResponse{}& ret );


int nsEMSSynchServer__DeleteSynch( xsd__string szSynchName, 
										     struct nsEMSSynchServer__DeleteSynchResponse{}& ret );


int nsEMSSynchServer__UpdateSynch( xsd__string szSynchName, 
										     struct nsEMSSynchServer__UpdateSynchResponse{}& ret );

struct nsEMSSynchServer__GetSynchResponse
{
	xsd__string szSynchConfig;
};

int nsEMSSynchServer__GetSynch( xsd__string szSynchName, 
								struct nsEMSSynchServer__GetSynchResponse& ret );


struct nsEMSSynchServer__GetSynchListResponse
{
	xsd__string szSynchNames;
};

int nsEMSSynchServer__GetSynchList( struct nsEMSSynchServer__GetSynchListResponse& ret );
