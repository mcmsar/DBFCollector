//gsoap nsEMSFPServer service name: FP_WS
//gsoap nsEMSFPServer service encoding:	literal
//gsoap nsEMSFPServer service namespace: urn:tempuri
//gsoap nsEMSFPServer schema  namespace: urn:nsEMSFPServer

#import "WS-Header.h"

//! Restart the FP software.
int nsEMSFPServer__Restart( struct nsEMSFPServer__RestartResponse{}& ret );

//! Reboot the FP.
int nsEMSFPServer__Reboot( bool bForce, struct nsEMSFPServer__RebootResponse{}& ret );

//! Start all configured collectors and controllers.
int nsEMSFPServer__Start( struct nsEMSFPServer__StartResponse{}& ret );

//! Stop all configured collectors and controllers.
int nsEMSFPServer__Stop( struct nsEMSFPServer__StopResponse{}& ret );

//! Idle all configured collectors and controllers.
int nsEMSFPServer__Idle( struct nsEMSFPServer__IdleResponse{}& ret );

//! Pass schedule record.
struct nsEMSFPServer__PassSchedRec
{
	LONG64	i64SchedTime;
	unsigned short	usSeq;
	unsigned short	usCount;
	unsigned short	ulLutID;
	unsigned long	ulSatID;
	unsigned long	ulFlags;
	unsigned long	ulOrbitNumber;
	LONG64	i64AOSTime;
	LONG64	i64LOSTime;
	LONG64	i64PeakTime;
	double	dMaxElevation;
	double	dMinElevation;
	double	dAOSAz;
	double	dLOSAz;
	LONG64	i64ActualStartTime;
	LONG64	i64ActualEndTime;
	double	dWeight;
};

//! Pass Schedule array.
struct nsEMSFPServer__PassSchedRecArray
{	struct nsEMSFPServer__PassSchedRec*	__ptr;
	int									__size;
};

//! Input a pass schedule.
int nsEMSFPServer__SetSchedule(	unsigned long ulPairID, 
								struct nsEMSFPServer__PassSchedRecArray strSched,
								struct nsEMSFPServer__SetScheduleResponse{}& rRet );

//! GetSchedule response.
struct nsEMSFPServer__GetScheduleResponse
{
	struct nsEMSFPServer__PassSchedRecArray aPasses;
};

//! Get a pass schedule.
int nsEMSFPServer__GetSchedule( unsigned long ulPairID, 
								 struct nsEMSFPServer__GetScheduleResponse& rRet);

//! Antenna/Data Stream pair.
struct nsEMSFPServer__AntennaDataPair
{
	unsigned long ulPairID;
	unsigned long ulAntennaID;
	unsigned long ulDataStreamID;
};


//! Antenna/Data Stream pair array.
struct nsEMSFPServer__AntennaDataPairArray
{
	struct nsEMSFPServer__AntennaDataPair*	__ptr;
	int										__size;
};

struct nsEMSFPServer__GetListResponse
{
	struct nsEMSFPServer__AntennaDataPairArray aAntennaDataPairs;
};

int nsEMSFPServer__GetList( struct nsEMSFPServer__GetListResponse& rRet );

struct nsEMSFPServer__DoubleArray
{
	double* __ptr;
	int		__size;
};

struct nsEMSFPServer__EMSTLERECORD
{
	LONG64			i64Time;			//	timeModified
	unsigned long	ulLutID;	
	unsigned long	ulSatID;
	int 			nOrbitNumber;
	LONG64		i64TimeEpoch;
	double 		dXndt2o;
	double 		dXndd6o;	  	// has exponent included
	double 		dBStar;		// has exponent included
	double 		dInclination;
	double 		dRightAscNode;
	double 		dEccentricity;
	double 		dArgPerigee;
	double 		dMeanAnomaly;
	double 		dMeanMotion;
	struct nsEMSFPServer__DoubleArray 		adCoVarMatrix;
	LONG64		i64TimeEffective;
	double		dVelocityDifference;
	double		dRadiusDifference;
};

//! EMSTLERECORD array.
struct nsEMSFPServer__EMSTLERECORDArray
{
	struct nsEMSFPServer__EMSTLERECORD*		__ptr;
	int										__size;
};

int nsEMSFPServer__SetOrbits( struct nsEMSFPServer__EMSTLERECORDArray aTLEs,
							 struct nsEMSFPServer__SetOrbitsResponse{}& rRet );

struct nsEMSFPServer__GetOrbitsResponse
{
	struct nsEMSFPServer__EMSTLERECORDArray aTLEs;
};

int nsEMSFPServer__GetOrbits( struct nsEMSFPServer__GetOrbitsResponse& rRet );

