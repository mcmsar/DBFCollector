//gsoap nsEMS600MapsServer service name: Maps_WS
//gsoap nsEMS600MapsServer service encoding:	literal
//gsoap nsEMS600MapsServer service namespace: urn:nsEMS600MapsServer
//gsoap nsEMS600MapsServer schema  namespace: urn:nsEMS600MapsServer

#import "wsa.h"
#import "wsse.h"
#import "xop.h"
#import "xmime.h"
#import "WS-Header.h" 

/* ===================== emsGsoapWSInfrastructure.h ==================================*/
typedef std::string xsd__string;
typedef time_t xsd__dateTime;
typedef LONG64 xsd__LONG64;
typedef unsigned int xsd__unsignedInt;
typedef unsigned short xsd__unsignedShort;
typedef unsigned xsd__unsigned;


/* file attachment */
struct xsd__base64Binary
{
	unsigned char *__ptr;
	int __size;
	char *id;
	char *type;
	char *options; 
};



struct nsEMS600MapsServer__StringArray
{
	xsd__string* __ptr;
	int __size;
};

struct nsEMS600MapsServer__LongArray 
{
	LONG64* __ptr;
	int __size;
};


struct nsEMS600MapsServer__IntegerArray 
{
	/*xsd__int* __ptr;*/
	int* __ptr;
	int __size;
};

struct nsEMS600MapsServer__UnsignedIntArray
{
	unsigned* __ptr;
	int __size;
};


struct nsEMS600MapsServer__FloatArray
{
	float* __ptr;
	int __size;
};

struct nsEMS600MapsServer__DoubleArray
{
	double* __ptr;
	int __size;
};

  enum nsEMS600MapsServer__Severity
    {        
		Information,
        Warning,
        Error,
        Critical   
    };

enum nsEMS600MapsServer__EntityType
{
      Contact,
      DistributionList,               
      Route,      
      MCC,
      RCC,
      SPOC,
      LUT,  
      Satellite,
      User,
      Rule,
      CountryCode
};

enum nsEMS600MapsServer__MeasurementUnit
{
	Feet,
	Miles,
	Meters,
	Kilometers	
};

class nsEMS600MapsServer__NameIdPair 
{    		    	
	xsd__string Name;    		
	LONG64 Id;		
};

struct nsEMS600MapsServer__Coordinate
{
	/* sign should denote direction */
	double Longitude;
	double Latitude;	
	double Altitude;	
};

struct nsEMS600MapsServer__Coordinates
{
	struct nsEMS600MapsServer__Coordinate* __ptr;
	int __size;
};

enum nsEMS600MapsServer__PassSchedStatus
{
	XX,
	OP,
	OR,
	OS
};

/* for certain actions such as Mark Beacon, AcknowledgeBeacon, etc
OCC should use this response structure.  Return ObjectState.Good if all is well.
 If not, return ObjectState.Error and specify error in Summary field */
class nsEMS600MapsServer__ActionResponse 
{
public:
	 enum nsEMS600MapsServer__ObjectState State;     
	 int CacheID;	 
	 /* xsd__anyType Data ;		 */
	 xsd__string Summary;        /* in response, please start with OCC600 Server: */
	 LONG64 TimeStamp;
};

/* required by gSOAP, see chapter 7.1.12 */
struct nsEMS600MapsServer__ActionResponseResponse
{
	 nsEMS600MapsServer__ActionResponse Response;
};


class nsEMS600MapsServer__SimpleEntity 
{    		    
	LONG64 Key;
	xsd__string Name;    		
	LONG64 Id;	
	enum nsEMS600MapsServer__EntityType EntityType;
	xsd__string Alias;	
};

class nsEMS600MapsServer__Entity  : public nsEMS600MapsServer__SimpleEntity
{    		
public:

    LONG64 TimeStamp;   			
	xsd__string Description; 
	xsd__string Group;		
	xsd__string Summary;
	bool IsActive;	
};

class nsEMS600MapsServer__FilterBase : nsEMS600MapsServer__Entity
{     
public:					
	LONG64 TimeStampStart;  
	LONG64 TimeStampEnd;

	bool UseTimeStampStart;  
	bool UseTimeStampEnd;

	bool ShouldLimitResponseCount;
	int MaxResponseCount;	
};

struct nsEMS600MapsServer__Marking
{	
	bool IsMarked;										
	bool IsSuppressed;								    
	LONG64 MarkStartTime;
	LONG64 MarkEndTime;	
	struct nsEMS600MapsServer__IntegerArray MarkingContactIds;
};

struct nsEMS600MapsServer__MarkingFilter
{
    bool UseMarkStartTimeStart;
	bool UseMarkStartTimeEnd;
	LONG64 MarkStartTimeStart;
	LONG64 MarkStartTimeEnd;

	bool UseMarkEndTimeStart;
	bool UseMarkEndTimeEnd;
	LONG64 MarkEndTimeStart;
	LONG64 MarkEndTimeEnd;

	bool UseMarkingContacts;
	struct nsEMS600MapsServer__IntegerArray MarkingContactIds;	
};

/* =========================== Data Types =========================*/


struct nsEMS600MapsServer__Point
{	
	double X;
	double Y;	
	double Z;	
};

struct nsEMS600MapsServer__Points
{
	struct nsEMS600MapsServer__Point* __ptr;
	int __size;
};


struct nsEMS600MapsServer__PointCollection
{
	struct nsEMS600MapsServer__Points Points;
	enum nsEMS600MapsServer__MeasurementUnit Units;
	int SRID;
};

struct nsEMS600MapsServer__LineString
{
	int SRID;
	struct nsEMS600MapsServer__Points Vertices;		
};

struct nsEMS600MapsServer__LineStrings
{
	struct nsEMS600MapsServer__LineString* __ptr;
	int __size;	
};

/* For type "Polygon", the "coordinates" member must be an array of LinearRing coordinate arrays. For Polygons with multiple rings, 
the first must be the exterior ring and any others must be interior rings or holes.*/
struct nsEMS600MapsServer__Polygon
{			
	int SRID;	
	struct nsEMS600MapsServer__LineStrings Rings;		
};

struct nsEMS600MapsServer__MultiPolygon
{			
	struct nsEMS600MapsServer__Polygon* __ptr;	
	int __size;			
};

/* ===================== Satellite ====================*/

class nsEMS600MapsServer__SatelliteTrackQuery : nsEMS600MapsServer__FilterBase
{ 
	bool UseSatellites;	
	struct nsEMS600MapsServer__IntegerArray SatelliteIds; 
};

struct nsEMS600MapsServer__SatelliteTrack 
{		
	LONG64 StartTime;		
	LONG64 Duration;	/* in seconds since start time */
	int OrbitNumber;
	nsEMS600MapsServer__NameIdPair Satellite;
	struct nsEMS600MapsServer__LineString Track;		
};

struct nsEMS600MapsServer__SatelliteTracks 
{
	struct nsEMS600MapsServer__SatelliteTrack* __ptr;
	int __size;
};

struct nsEMS600MapsServer__SatelliteTrackQueryResult 
{	
	struct nsEMS600MapsServer__SatelliteTracks Tracks;	
};

struct nsEMS600MapsServer__SatelliteTrackResponse
{
	struct nsEMS600MapsServer__SatelliteTrack SatTrack;
};

int nsEMS600MapsServer__GetSatelliteTrack(
							  nsEMS600MapsServer__SatelliteTrackQuery query,
							  struct nsEMS600MapsServer__SatelliteTrackQueryResult &result );						

int nsEMS600MapsServer__GetLastSatelliteTrack(struct nsEMS600MapsServer__SatelliteTrackResponse &result );


/*============================ High Flyer Regin ===========================*/

class nsEMS600MapsServer__HighFlyerRegionQuery : nsEMS600MapsServer__FilterBase
{  	
	struct nsEMS600MapsServer__Point Center;	
	enum nsEMS600MapsServer__MeasurementUnit MeasurementUnit;
	nsEMS600MapsServer__NameIdPair Aircraft;
};

class nsEMS600MapsServer__Region 
{	
	nsEMS600MapsServer__NameIdPair RegionId;
	struct nsEMS600MapsServer__Polygon RegionGeometry;		
};

class nsEMS600MapsServer__HighFlyerRegion : nsEMS600MapsServer__Region
{	
	LONG64 TimeStamp;
	struct nsEMS600MapsServer__Point Center;
	nsEMS600MapsServer__NameIdPair Aircraft;
};




struct nsEMS600MapsServer__Regions
{	
	nsEMS600MapsServer__Region* __ptr;
	int __size;
};

struct nsEMS600MapsServer__HighFlyerRegionQueryResult
{
	nsEMS600MapsServer__HighFlyerRegion HighFlyerRegion;
};

int nsEMS600MapsServer__GetHighFlyerRegion(
							  nsEMS600MapsServer__HighFlyerRegionQuery query,
							  struct nsEMS600MapsServer__HighFlyerRegionQueryResult &result );	 



/* =========================== Satellite Visibility =========================*/		

class nsEMS600MapsServer__SatelliteVisibilityRegionQuery : nsEMS600MapsServer__FilterBase
{	
	bool UseSatellites;	
	struct nsEMS600MapsServer__IntegerArray SatelliteIds; 
	struct nsEMS600MapsServer__Point Location;	
	enum nsEMS600MapsServer__MeasurementUnit MeasurementUnit;
	bool UseLocation;
};

class nsEMS600MapsServer__SatelliteVisibilityRegion : nsEMS600MapsServer__Region
{	
	nsEMS600MapsServer__NameIdPair Satellite;		
	struct nsEMS600MapsServer__Point Location;		
	LONG64 TimeStamp;
};

struct nsEMS600MapsServer__SatelliteVisibilityRegions 
{	
	nsEMS600MapsServer__SatelliteVisibilityRegion* __ptr;
	int __size;	
};

struct nsEMS600MapsServer__SatelliteVisibilityRegionsQueryResult
{
	struct nsEMS600MapsServer__SatelliteVisibilityRegions SatelliteVisibilityRegions;
};							

int nsEMS600MapsServer__GetSatelliteVisibilityRegion(
							  nsEMS600MapsServer__SatelliteVisibilityRegionQuery query,
							  struct nsEMS600MapsServer__SatelliteVisibilityRegionsQueryResult &result );


/* ============================= Next Visibility Query ===================================*/


struct nsEMS600MapsServer__NextVisibility
{
	LONG64 LOSTime;
	LONG64 CTATime;
	double MaxElevation;
	nsEMS600MapsServer__SimpleEntity Satellite;
	nsEMS600MapsServer__SimpleEntity Lut;	
	int OrbitNumber;	
	LONG64 Duration;
	bool IsForeign;
};

 struct nsEMS600MapsServer__NextVisibilities
{
	struct nsEMS600MapsServer__NextVisibility* __ptr;
	int __size;
};


struct nsEMS600MapsServer__NextVisibilitiesQueryResult
{	
	struct nsEMS600MapsServer__NextVisibilities NextVisibilities;	
};

class nsEMS600MapsServer__NextVisibilityQuery : nsEMS600MapsServer__FilterBase
{                                    				
	struct nsEMS600MapsServer__Point Location;	
	int NumberOfPasses;
	bool UseUserSchedName;
	xsd__string UserPassSchedName;
};

/* Use this to query for raw solutions database*/
int nsEMS600MapsServer__GetNextVisibilities(  nsEMS600MapsServer__NextVisibilityQuery query,
							                  struct nsEMS600MapsServer__NextVisibilitiesQueryResult &result );		

/* ============================================================= */

class nsEMS600MapsServer__MutualVisibilityQuery : nsEMS600MapsServer__FilterBase
{
	LONG64 StartTime;
	int    NumberOfMutualVisPasses;
	struct nsEMS600MapsServer__Point Location;
	bool UseUserSchedName;
	xsd__string UserPassSchedName;
};

struct nsEMS600MapsServer__MutualVisibilityRecord
{
	int    LUTID;
	int    SatId;
   	int    OrbitNumber;
	LONG64 TCA;
	LONG64 StartVisibility;
	double Duration;
	double MaxElevation;
	double AzimuthAOS;
	double AzimuthLOS;
	enum   nsEMS600MapsServer__PassSchedStatus  Status;
};


struct nsEMS600MapsServer__MutualVisibilityRecords
{
	struct nsEMS600MapsServer__MutualVisibilityRecord* __ptr;
	int     __size;
}

struct nsEMS600MapsServer__MutualVisibilityDataSummary
{
	int     iNumberOfMutualVisPasses;
	double  dAvgWaitingTime;
	double  dMinWaitingTime;
	double  dMaxWaitingTime;
}

class nsEMS600MapsServer__MutualVisibilityQueryResult
{
	struct nsEMS600MapsServer__MutualVisibilityDataSummary ExtraData;
	struct nsEMS600MapsServer__MutualVisibilityRecords MutualVisibilityRecords;
};

class nsEMS600MapsServer__GetMutualVisResponse
{
	int iCacheID;
	nsEMS600MapsServer__MutualVisibilityQueryResult mutualVisData;	
};


/* gSOAP requirement */
struct nsEMS600MapsServer__GetMutualVisQueryResultWrap
{
	nsEMS600MapsServer__GetMutualVisResponse Result;
};


int nsEMS600MapsServer__GetMutualVisibility(
                                        nsEMS600MapsServer__MutualVisibilityQuery criteria,
                                        struct nsEMS600MapsServer__GetMutualVisQueryResultWrap &response );


/* =========================== Satellite Locations =========================*/		

class nsEMS600MapsServer__SatelliteLocationQuery : nsEMS600MapsServer__FilterBase
{	
	bool UseElevation;	
	double Elevation;
};

struct nsEMS600MapsServer__SatelliteLocation
{		
	nsEMS600MapsServer__NameIdPair Satellite;			
    struct nsEMS600MapsServer__LineString Track;	
	struct nsEMS600MapsServer__LineString VisibilityRegion;		
};

struct nsEMS600MapsServer__SatelliteLocations 
{	
	struct nsEMS600MapsServer__SatelliteLocation* __ptr;
	int __size;	
};


struct nsEMS600MapsServer__SatelliteLocationsQueryResult
{
	struct nsEMS600MapsServer__SatelliteLocations SatelliteLocations;
};							

int nsEMS600MapsServer__GetSatelliteLocations(
							  nsEMS600MapsServer__SatelliteLocationQuery query,
							  struct nsEMS600MapsServer__SatelliteLocationsQueryResult &result );

/* =========================== Beacon Decoder =========================*/		
struct nsEMS600MapsServer__BeaconMsgDecoderQuery
{
	xsd__string BeaconMsg;
}

struct nsEMS600MapsServer__BeaconMessageDecoderResult
{
	xsd__string Result;
};							

int nsEMS600MapsServer__DecodeBeaconMessage(
							  struct nsEMS600MapsServer__BeaconMsgDecoderQuery query,
							  struct nsEMS600MapsServer__BeaconMessageDecoderResult &result );


/* =========================== Contours =========================*/		
struct nsEMS600MapsServer__ContoursQuery
{
	int SchedOrAll;
	int Type;
	double StepSize;
	double LineValue;
	bool UseUserSchedName;
	xsd__string UserPassSchedName;
}

struct nsEMS600MapsServer__ContoursResult
{
	struct nsEMS600MapsServer__LineStrings Contours;		
};							

int nsEMS600MapsServer__GetContours(
							  struct nsEMS600MapsServer__ContoursQuery query,
							  struct nsEMS600MapsServer__ContoursResult &result );


/* =========================== Interferers =========================*/		
struct nsEMS600MapsServer__InterfererQuery 
{     
      int PersistenceLimit;
      int DataCoverage;
      int OutputType;
      bool UpdateLoationInfo;

      LONG64 TimeStampStart;  
      LONG64 TimeStampEnd;    
};

struct nsEMS600MapsServer__Interferer
{                 
      xsd__string Content;    
};


struct nsEMS600MapsServer__InterfererQueryResult
{     
      struct nsEMS600MapsServer__Interferer Interferers;           
};                                        

int nsEMS600MapsServer__GetInterferers(
                                            struct nsEMS600MapsServer__InterfererQuery query,
                                            struct nsEMS600MapsServer__InterfererQueryResult &result );



											
/* =========================== QMS reports =========================*/		
struct nsEMS600MapsServer__QMSQuery 
{     
      int ReportType;

      LONG64 ReportDate;
      LONG64 ReportEndDate;
};

struct nsEMS600MapsServer__QMS
{                 
      xsd__string Content;    
};


struct nsEMS600MapsServer__QMSQueryResult
{     
      struct nsEMS600MapsServer__QMS QMS;           
};                                        

int nsEMS600MapsServer__GetQMS(
                                            struct nsEMS600MapsServer__QMSQuery query,
                                            struct nsEMS600MapsServer__QMSQueryResult &result );
