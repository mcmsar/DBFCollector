/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __DATA_ACCESS_HELPER_H__
#define __DATA_ACCESS_HELPER_H__

#include "dataaccesshelperbase.h"
#include "emsorbit.h"
#include "ChangeMonitor.h" // LUTDISPLAYSTATE

//! @class CEMSDataAccessHelper
//! This class performs local/remote data access and returns
//! data custom formatted and filtered.
class CEMSDataAccessHelper : public CEMSDataAccessHelperBase
{
	public:
		CEMSDataAccessHelper();
		CEMSDataAccessHelper( const CEMSDataAccessHelper& x );
		virtual ~CEMSDataAccessHelper();

		//! @fn CEMSObjectList<EMSSATELLITEPASS> GetSatelliteTracks( const ULONG culLutID, const EMSTIME ctimeStart, const EMSTIME ctimeEnd )
		//! Retrieve the satellite tracks with LOS times in the given range.  
		CEMSObjectList<EMSSATELLITEPASS> GetSatelliteTracks( const ULONG culLutID, const EMSTIME ctimeStart, 
																const EMSTIME ctimeEnd );

		//! @fn CEMSObjectList<EMSSATELLITEPASS> GetSatelliteTracksBySatellite( const ULONG culSatID, const EMSTIME ctimeStart, const EMSTIME ctimeEnd )
		//! Retrieve the satellite tracks with LOS times in the given range for the specified satellite.  
		CEMSObjectList<EMSSATELLITEPASS> GetSatelliteTracksBySatellite( const ULONG culSatID, const EMSTIME ctimeStart, 
																const EMSTIME ctimeEnd );

		//! @fn EMSSATELLITEPASS GetSatelliteTracksBySatellitePass( const ULONG culSatID, const ULONG culPassID )
		//! Retrieve the satellite track specified.
		EMSSATELLITEPASS GetSatelliteTracksBySatellitePass( const ULONG culSatID, const ULONG culPassID );
		//! @fn EMSSATELLITEPASS GetSatelliteTracksBySatellitePass( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID )
		//! Retrieve the satellite track specified.
		EMSSATELLITEPASS GetSatelliteTracksBySatellitePass( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! @fn void GetLastSatellitePass( const ULONG culLutID, ULONG& ulSatID, ULONG& ulPassID)
		//! Consults the Pass Summary table for the last tracked satellite pass.
		void GetLastTrackedSatellitePass( const ULONG culLutID, ULONG& ulSatID, ULONG& ulPassID);

		//! @fn EMSTLEDATA GetTLE( const ULONG culSatID, const EMSTIME ctimeEffective )
		//! Retrieve the TLE for the given satellite with an effective time closest to and 
		//! earlier than the given time.
		EMSTLEDATA GetTLE( const ULONG culSatID, const EMSTIME ctimeEffective );

		//! @fn EMSTLEDATA GetTimeSolnProcessing( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID, EMSTIME& timeSolnProcessing )
		//! Retrieve the time that solution processing ended for a given pass.
		void	GetTimeSolnProcessing( 
						const ULONG culLutID,
						const ULONG	culSatID, 
						const ULONG	culPassID,
						EMSTIME&	timeSolnProcessing );

		//! @fn GetLastTimeSolnProcessing( 	const ULONG culLutID,	EMSTIME&	timeSolnProcessing )
		//! Retrieve the solution processing time of the last pass summary for the given LUT. The LUTID is optional.
		void GetLastTimeSolnProcessing( 
						const ULONG culLutID,
						EMSTIME&	timeSolnProcessing );

		//! CEMSObjectList<EMSLOCATE> GetLocations( const UINT64 cui64BeaconID, const INT64 ci64Timestamp, const WORD cwType )
		//! Retrieve a list of location records satisfying the given criteria.  BeaconID and Timestamp are
		//! required critiera, wType is optional.
		CEMSObjectList<EMSLOCATE> GetLocations( const UINT64 cui64BeaconID, const INT64 ci64Timestamp, const WORD cwType );

		//! Get pass information for the next scheduled pass for the specified LUT.  The next pass must be in the future.
		EMSSATELLITEPASS GetNextScheduledPass( const ULONG culLutID );

		//! Get the latest sensor data.
		EMSSENSORINFO GetLatestSensor( const ULONG culLutID );

		//! Get all log records newer than the given the time, up to the given maximum number, starting from
		//! the latest.
		CEMSObjectList<EMSLOGDATA> GetLogData( const ULONG culLutID, const EMSTIME ctimeNewerThan, const ULONG culCount = 50 );

		//! Get pass information for the currently scheduled pass for the specified LUT.
		EMSSATELLITEPASS GetCurrentScheduledPass( const ULONG culLutID, const ULONG culIdleDelaySec = 0 );

		//! Get the current antenna information.
		EMSANTENNAINFO GetCurrentAntennaData( const ULONG culLutID );

		//! Get the current collector information.
		EMSCOLLECTORINFO GetCurrentCollectorData( const ULONG culLutID );

		//! Get the time at which the LUT clock was last synchronized with a known good time source.
		EMSTIME GetLastClockSynchTime( const ULONG culLutID );

		//! Get the current WB data.
		EMSWIDEBANDINFO GetCurrentWBData( const ULONG culLutID );

		//! Get the current SARR Bent Pipe data.
		EMSSARRDATA GetCurrentSarrData( const ULONG culLutID, const ULONG culSatID = 0, const ULONG culPassID = 0 );

		//! Get the SARR Bent Pipe data: limited by time
		EMSSARRDATA GetCurrentGeoSarrData( const ULONG culLutID, const ULONG culSatID, const double cdElapsedMinutes );

		//! Get the latest pass summary record.
		EMSPASSSUMMARYINFO2 GetLatestPassSummary( const ULONG culLutID );

		//! Get the last entered collector information for a given pass.
		EMSCOLLECTORINFO GetCollectorData( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! Get the last entered location status for a given pass.
		EMSLOCATIONINFO GetLocationStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! Get a list of location records with timestamps in the given range and LUT ID.
		CEMSObjectList<EMSLOCATE> GetLocations( const EMSTIME ctimeStart, const EMSTIME ctimeEnd, const ULONG culLutID );

		//! Get the last entered orbit status for a given pass.
		EMSORBITDETERMINEINFO GetOrbitStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! Get the last entered TCAL status for a given pass.
		EMSTCALINFO GetTCALStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! Get the last entered SARR status for a given pass.
		EMSSARRCALIBINFO GetSARRStatus( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		//! Retrieve the number of log messages in the given interval with the given message id and level.
		ULONG GetNumLogMessages( const EMSTIME ctimeStart, const EMSTIME ctimeEnd, const ULONG culLutID,
							const EMS_RESULT chrMsg, const int ciLogLevel );

		//! Get the current comms status record.
		EMSCOMMSINFO GetCurrentCommsData( const ULONG culLutID );

		//! Get the current LUT Display State
		void GetCurrentLutDisplayState( const ULONG culLutID,
										const ULONG culIdleDelaySec,
										LUTDISPLAYSTATE& eCurrentState,
										EMSTIME& timeStateChange );

	private:
		std::wstring _BuildSatTrackSQL( const ULONG culLutID, const EMSTIME ctimeStart, const EMSTIME ctimeEnd );

		std::wstring _BuildSatTrackSQLForSatellite( const ULONG culLutID, const ULONG culSatID, const EMSTIME ctimeStart, const EMSTIME ctimeEnd );
		
		std::wstring _BuildSatTrackSQLForSatellitePass( const ULONG culLutID, const ULONG culSatID, const ULONG culPassID );

		std::wstring _BuildLastPassSummarySQL( const ULONG culLutID );

		std::wstring _BuildPassSummarySQL( 
									LPCWSTR*	cawszColumns,
									const short	csColumns,
									const ULONG	culLutID,
									const ULONG culSatID,
									const ULONG	culPassID );

		std::wstring _BuildLastPassSummarySQL( LPCWSTR* cawszColumns, const short csColumns, const ULONG culLutID );

		CEMSObjectList<EMSSATELLITEPASS> _AssembleSatelliteTracks( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords );
		
		std::wstring _BuildTLESQL( const ULONG culLutID, const ULONG culSatID, const EMSTIME ctimeEffective );

		EMSTLEDATA _AssembleTLE( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords );

		void _AssembleLastTrackedPass( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, ULONG& ulSatID, 
										ULONG& ulPassID );

		void _AssembleTimeSolnProcessing( 
						CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
						EMSTIME& timeSolnProcessing );

		std::wstring _BuildGetLocationsSQL( LPCWSTR* cawszColumns, const short csColumns,
											const UINT64 cuiBeaconID, const INT64 ci64Timestamp, 
											const WORD cwType, const ULONG culLutID );

		std::wstring _BuildGetLocationsSQL( LPCWSTR* cawszColumns, const short csColumns,
											const EMSTIME ctimeStart, const EMSTIME ctimeEnd,
											const ULONG culLutID );

		CEMSObjectList<EMSLOCATE> _AssembleLocationRecords( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords );

		std::wstring _BuildNextSchedPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const EMSTIME ctimeSched );

		void _AssembleNextSchedPass( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
										EMSSATELLITEPASS& rstrPass );

		std::wstring _BuildLastSensorSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleLastSensor( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
										EMSSENSORINFO& rstrSensor );

		std::wstring _BuildLogDataSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const EMSTIME ctimeNewerThan );

		void _AssembleLogData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								CEMSObjectList<EMSLOGDATA>& olstLogRecs );

		std::wstring _BuildCurrentSchedPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const EMSTIME ctimeSched,
											const ULONG culIdleDelaySec = 0 );

		std::wstring _BuildCurrentAntennaSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleCurrentAntennaData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSANTENNAINFO& roAntennaRec );

		std::wstring _BuildCurrentCollectorSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleCurrentCollectorData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSCOLLECTORINFO& roRec );

		std::wstring _BuildLastTimeSynchSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleLastTimeSynchData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSTIME& roTime );

		std::wstring _BuildCurrentWBSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleCurrentWBData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSWIDEBANDINFO& roRec );

		std::wstring _BuildCurrentSarrSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );
		std::wstring _BuildCurrentGeoSarrSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const double cdElapsedTime );

		void _AssembleCurrentSarrData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSSARRDATA& roRec );

		std::wstring _BuildLatestPassSummarySQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID);

		void _AssembleLatestPassSummaryData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSPASSSUMMARYINFO2& roRec );


		std::wstring _BuildCollectorForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );

		std::wstring _BuildLocationStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );

		void _AssembleLocationStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSLOCATIONINFO& roRec );

		std::wstring _BuildOrbitStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );

		void _AssembleOrbitStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSORBITDETERMINEINFO& roRec );

		std::wstring _BuildTCALStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );

		void _AssembleTCALStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSTCALINFO& roRec );

		std::wstring _BuildSARRStatusForPassSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID,
											const ULONG culSatID,
											const ULONG culPassID );

		void _AssembleSARRStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								EMSSARRCALIBINFO& roRec );

		std::wstring _BuildLogMsgCountSQL(  const EMSTIME ctimeStart,
											const EMSTIME ctimeEnd,
											const ULONG culLutID,
											const EMS_RESULT chrMsg, 
											const int ciLogLevel );

		void _AssembleLogMsgCountData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
								ULONG& rulCount );

		std::wstring _BuildCurrentCommsStatusSQL( LPCWSTR* cawszColumns, 
											const short csColumns,
											const ULONG culLutID );

		void _AssembleCommsStatusData( CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
										EMSCOMMSINFO& roRec );

		std::wstring _BuildCurrentLutDisplayStateSQL( const ULONG culLutID );

		void _AssembleLutDisplayStateData( 
					CEMSPointerList<CEMSRawDataRecordReader>& olstRecords, 
					const ULONG culIdleDelaySec,
					LUTDISPLAYSTATE& eCurrentState, EMSTIME& timeStateChange );

		LUTDISPLAYSTATE _DetermineLutDisplayState( 
					EMSTIME& ctimeStateChange, 
					const ULONG culIdleDelaySec, 
					const DWORD dwMsgID );
	private:
};

#endif
