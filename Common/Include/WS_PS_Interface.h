//gsoap nsEMSFPServer service name: PS_WS
//gsoap nsEMSFPServer service encoding:	literal
//gsoap nsEMSFPServer service namespace: urn:tempuri
//gsoap nsEMSFPServer schema  namespace: urn:nsEMSPSServer


//! Pass schedule record.
struct nsEMSPSServer__PassSchedRec
{
	LONG64	i64SchedTime;
	unsigned short	usSeq;
	unsigned short	usCount;
	unsigned short	ulAntID;
	unsigned short	ulSatID;
	LONG64	i64AOSTime;
	double  dAzAOS;
	double	dElAOS;
	LONG64	i64LOSTime;
	double	dAzLOS;
	double	dElLOS;
	double	dMaxElevation;
	bool bTrackIt;
};

//! Pass Schedule array.
struct nsEMSPSServer__PassSchedRecArray
{	struct nsEMSPSServer__PassSchedRec*	__ptr;
	int									__size;
};

int nsEMSPSServer__SetManual( struct nsEMSPSServer__PassSchedRecArray strSched,
							  struct nsEMSPSServer__SetManualResponse{}& rRet );


int nsEMSPSServer__SetAutomatic( struct nsEMSPSServer__SetAutomaticResponse{}& rRet );

int nsEMSPSServer__SetDuration( long lDuration, struct nsEMSPSServer__SetDurationResponse{}& rRet );

int nsEMSPSServer__SetMinElevation( double dMinEl, struct nsEMSPSServer__SetMinElevationResponse{}& rRet );



