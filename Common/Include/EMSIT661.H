/********************************************************************
*	Module:			emsit661.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit661  Class
*						Pass Processing Summary
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT661
#define INC_EMSIT661

#include "emssit.h"

typedef enum _tagEMSSIT661ORBITSTATUS
{
	EMSSIT661OrbitUpdateUnknown = 0,
	EMSSIT661OrbitUpdateInSpec = 1,
	EMSSIT661OrbitUpdateOutSpec = 2,
	EMSSIT661OrbitUpdatePredict = 3
} EMSSIT661ORBITSTATUS;

class CEMSSit661A : public CEMSSitMessageBase
{
public:
	CEMSSit661A();
	virtual ~CEMSSit661A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

	inline void SetSatelliteID( ULONG ulSatID ) { m_ulSatID = ulSatID; }
	inline ULONG GetSatelliteID( void ) { return m_ulSatID; }

	inline void SetOrbitNumber( ULONG ulOrbitNumber ) { m_ulOrbitNumber = ulOrbitNumber; }
	inline ULONG GetOrbitNumber( void ) { return m_ulOrbitNumber; }

	inline EMSTIME GetAOSTime( void ) { return m_timeAOS; }
	inline void SetAOSTime( EMSTIME t ) { m_timeAOS = t; }

	inline EMSTIME GetRolloverTime( void ) { return m_timeRollover; }
	inline void SetRolloverTime( EMSTIME t ) { m_timeRollover = t; }

	inline float GetUSOFreq( void ) { return m_fUSOFreq; }
	inline void SetUSOFreq( float fFreq ) { m_fUSOFreq = fFreq; }

	inline EMSTIME GetLOSTime( void ) { return m_timeLOS; }
	inline void SetLOSTime( EMSTIME t ) { m_timeLOS = t; }

	inline EMSTIME GetNextAOSTime( void ) { return m_timeNextAOS; }
	inline void SetNextAOSTime( EMSTIME t ) { m_timeNextAOS = t; }

	inline EMSTIME GetNextLOSTime( void ) { return m_timeNextLOS; }
	inline void SetNextLOSTime( EMSTIME t ) { m_timeNextLOS = t; }

	inline int GetSecondsDuration( void ) { return m_nSecsDuration; }
	inline void SetSecondsDuration( int nSeconds ) { m_nSecsDuration = nSeconds; }

	inline int GetSecondsCollecting( void ) { return m_nSecsCollecting; }
	inline void SetSecondsCollecting( int nSeconds ) { m_nSecsCollecting = nSeconds; }

	inline int GetPercentageCollecting( void ) { return m_nPercentageCollecting; }
	inline void SetPercentageCollecting( int nPercent ) { m_nPercentageCollecting = nPercent; }

	inline ULONG GetPassStatus( void ) { return m_ulPassStatus; }
	inline void SetPassStatus( ULONG ulPassStatus ) { m_ulPassStatus = ulPassStatus; }

	inline int GetPDSRecoveryRate( void ) { return m_nPDSRecoveryRate; }
	inline void SetPDSRecoveryRate( int nPDSRecoveryRate ) { m_nPDSRecoveryRate = nPDSRecoveryRate; }

	inline int GetFramesMissed( void ) { return m_nFramesMissed; }
	inline void SetFramesMissed( int nFramesMissed ) { m_nFramesMissed = nFramesMissed; }

	inline int GetTotalPDSCount( void ) { return m_nTotalPDSCount; }
	inline void SetTotalPDSCount( int nTotalPDSCount ) { m_nTotalPDSCount = nTotalPDSCount; }

	inline int GetDistinctPDSCount( void ) { return m_nDistinctPDSCount; }
	inline void SetDistinctPDSCount( int nDistinctPDSCount ) { m_nDistinctPDSCount = nDistinctPDSCount; }

	inline int GetSarrMessages( void ) { return m_nSarrMessages; }
	inline void SetSarrMessages( int nSarrMessages ) { m_nSarrMessages = nSarrMessages; }

	inline EMSTIME GetOrbitEpoch( void ) { return m_timeOrbitEpoch; }
	inline void SetOrbitEpoch( EMSTIME t ) { m_timeOrbitEpoch = t; }

	inline EMSVECTOR GetOrbitPosition( void ) { return m_vOrbitPosition; }
	inline void SetOrbitPosition( EMSVECTOR v ) { m_vOrbitPosition = v; }

	inline EMSVECTOR GetOrbitVelocity( void ) { return m_vOrbitVelocity; }
	inline void SetOrbitVelocity( EMSVECTOR v ) { m_vOrbitVelocity = v; }

	inline EMSSIT661ORBITSTATUS GetOrbitUpdateStatus( void ) { return m_orbitUpdateStatus; }
	inline void SetOrbitUpdateStatus( EMSSIT661ORBITSTATUS orbitUpdateStatus ) { m_orbitUpdateStatus = orbitUpdateStatus; }

	inline double GetOrbitPositionOffset( void ) { return m_dOrbitPositionOffset; }
	inline void SetOrbitPositionOffset( double dOrbitPositionOffset ) { m_dOrbitPositionOffset = dOrbitPositionOffset; }

	inline double GetOrbitVelocityOffset( void ) { return m_dOrbitVelocityOffset; }
	inline void SetOrbitVelocityOffset( double dOrbitVelocityOffset ) { m_dOrbitVelocityOffset = dOrbitVelocityOffset; }

	inline EMSTIME GetSolnProcessingTime( void ) { return m_timeSolnProcessing; }
	inline void SetSolnProcessingTime( EMSTIME t ) { m_timeSolnProcessing = t; }

	inline int Get121Transmitters( void ) { return m_n121Transmitters; }
	inline void Set121Transmitters( int n121Transmitters ) { m_n121Transmitters = n121Transmitters; }

	inline int Get243Transmitters( void ) { return m_n243Transmitters; }
	inline void Set243Transmitters( int n243Transmitters ) { m_n243Transmitters = n243Transmitters; }

	inline int Get406Interferers( void ) { return m_n406Interferers; }
	inline void Set406Interferers( int n406Interferers ) { m_n406Interferers = n406Interferers; }

	inline int Get406LocatedBeacons( void ) { return m_n406LocatedBeacons; }
	inline void Set406LocatedBeacons( int n406LocatedBeacons ) { m_n406LocatedBeacons = n406LocatedBeacons; }

	inline int Get406UnlocatedBeacons( void ) { return m_n406UnlocatedBeacons; }
	inline void Set406UnlocatedBeacons( int n406UnlocatedBeacons ) { m_n406UnlocatedBeacons = n406UnlocatedBeacons; }

	inline int GetUnlocatedAlerts( void ) { return m_nUnlocatedAlerts; }
	inline void SetUnlocatedAlerts( int nUnlocatedAlerts ) { m_nUnlocatedAlerts = nUnlocatedAlerts; }

	inline int GetAlarmMessages( void ) { return m_nAlarmMessages; }
	inline void SetAlarmMessages( int nAlarmMessages ) { m_nAlarmMessages = nAlarmMessages; }

	inline int GetWarningMessages( void ) { return m_nWarningMessages; }
	inline void SetWarningMessages( int nWarningMessages ) { m_nWarningMessages = nWarningMessages; }

	inline ULONG GetNextSatID( void ) { return m_ulNextSatID; }
	inline void SetNextSatID( ULONG ulNextSatID ) { m_ulNextSatID = ulNextSatID; }

	inline ULONG GetNextOrbitNumber( void ) { return m_ulNextOrbitNumber; }
	inline void SetNextOrbitNumber( ULONG ulNextOrbitNumber ) { m_ulNextOrbitNumber = ulNextOrbitNumber; }

	inline ULONG GetNextPassStatus( void ) { return m_ulNextPassStatus; }
	inline void SetNextPassStatus( ULONG ulNextPassStatus ) { m_ulNextPassStatus = ulNextPassStatus; }

	inline EMSTIME	GetSolutionProcessingTime( void ) { return m_timeSolnProcessing; }

	inline float  GetSarr406FreqOffset( void ) { return m_fSARR406FreqOff; }
	inline void SetSarr406FreqOffset( float fSARR406FreqOff ) { m_fSARR406FreqOff = fSARR406FreqOff; }

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

protected:
	int  _ChkMessageCountRange( const int iCount, const wchar_t* cwszText );

private: // methods
	void _Reset( void );

   virtual EMS_RESULT _ParsePassIDLine( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParseActualAOSLOSLine( CEMSSitTokenizer* lpTokenizer ){return EMS_OK;};
   virtual EMS_RESULT _ParsePassSummaryLine1( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryLine2( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryLine3( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryLine4( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryLine5( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryLine6( CEMSSitTokenizer* lpTokenizer );
   virtual EMS_RESULT _ParsePassSummaryStatsLine( CEMSSitTokenizer* lpTokenizer ){return EMS_OK;};
   virtual EMS_RESULT _ParsePassSummaryLine7( CEMSSitTokenizer* lpTokenizer );

private:	// data
	ULONG				m_ulSatID;
	ULONG				m_ulOrbitNumber;
	EMSTIME				m_timeAOS;
	EMSTIME				m_timeLOS;
	int					m_nSecsDuration;
	int					m_nSecsCollecting;
	int					m_nPercentageCollecting;
   ULONG             m_ulPassStatus;
	int 				m_nPDSRecoveryRate;
	int					m_nFramesMissed;
	int					m_nTotalPDSCount;
	int					m_nDistinctPDSCount;
	int					m_nSarrMessages;
	EMSTIME				m_timeOrbitEpoch;
	EMSVECTOR			m_vOrbitPosition;
	EMSVECTOR			m_vOrbitVelocity;
	EMSSIT661ORBITSTATUS m_orbitUpdateStatus;
	double				m_dOrbitPositionOffset;
	double				m_dOrbitVelocityOffset;
	EMSTIME				m_timeRollover;
	float					m_fUSOFreq;
	float					m_fSARR406FreqOff;
	EMSTIME				m_timeSolnProcessing;
	int					m_n121Transmitters;
	int					m_n243Transmitters;
	int					m_n406Interferers;
	int					m_n406LocatedBeacons;
	int					m_n406UnlocatedBeacons;
	int					m_nUnlocatedAlerts;
	int					m_nAlarmMessages;
	int					m_nWarningMessages;
	ULONG				m_ulNextSatID;
	ULONG				m_ulNextOrbitNumber;
	EMSTIME 			m_timeNextAOS;
	EMSTIME 			m_timeNextLOS;
	ULONG				m_ulNextPassStatus;
};

class CEMSSit661B : public CEMSSit661A
{
public:
	CEMSSit661B();
	virtual ~CEMSSit661B();

	virtual void Reset( void );

	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

	inline ULONG GetEpochOrbitNumber( void ) { return m_ulEpochOrbNum; }
	inline void SetEpochOrbitNumber( const ULONG ulEpochOrbNum ) { m_ulEpochOrbNum = ulEpochOrbNum; }

	inline double GetDoubleUSOFreq( void ) { return m_dUSOFreq; }
	inline void SetDoubleUSOFreq( const double dFreq ) { m_dUSOFreq = dFreq; }

	inline double GetMedianLocAccuracy( void ) { return m_dMedianLocAccuracy; }
	inline void SetMedianLocAccuracy( const double dMedian ) { m_dMedianLocAccuracy = dMedian; }

	inline int GetMedianLocAccSampleSize( void ) { return m_iMedianLocAccSampleSize; }
	inline void SetMedianLocAccSampleSize( const int iCount ) { m_iMedianLocAccSampleSize = iCount; }

	inline WORD GetGeneralStatus( void ) { return m_wGeneralStatus; }
	inline void SetGeneralStatus( const WORD wStatus ) { m_wGeneralStatus = wStatus; }

	inline EMSTIME GetActualAOSTime( void ) { return m_tmActualAOS; }
	inline void SetActualAOSTime( const EMSTIME t ) { m_tmActualAOS = t; }

	inline EMSTIME GetActualLOSTime( void ) { return m_tmActualLOS; }
	inline void SetActualLOSTime( const EMSTIME t ) { m_tmActualLOS = t; }

	inline EMSTIME GetLastClockSyncTime( void ) { return m_tmLastClockSync; }
	inline void SetLastClockSyncTime( const EMSTIME t ) { m_tmLastClockSync = t; }

	inline EMSTIME GetEarliestSARPTime( void ) { return m_tmEarliestSARP; }
	inline void SetEarliestSARPTime( const EMSTIME t ) { m_tmEarliestSARP = t; }

	inline EMSTIME GetLastSARPTime( void ) { return m_tmLastSARP; }
	inline void SetLastSARPTime( const EMSTIME t ) { m_tmLastSARP = t; }

private:
	void _Reset( void );

	virtual EMS_RESULT _ParseActualAOSLOSLine( CEMSSitTokenizer* lpTokenizer );
    virtual EMS_RESULT _ParsePassSummaryLine2( CEMSSitTokenizer* lpTokenizer );
    virtual EMS_RESULT _ParsePassSummaryLine3( CEMSSitTokenizer* lpTokenizer );
    virtual EMS_RESULT _ParsePassSummaryLine5( CEMSSitTokenizer* lpTokenizer );
    virtual EMS_RESULT _ParsePassSummaryLine6( CEMSSitTokenizer* lpTokenizer );
    virtual EMS_RESULT _ParsePassSummaryStatsLine( CEMSSitTokenizer* lpTokenizer );


    virtual EMS_RESULT _WritePassIDLine( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WriteActualAOSLOSLine( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine1( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine2( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine3( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine4( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine5( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine6( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryStatsLine( IEMSSeqStream *lpStream );
    virtual EMS_RESULT _WritePassSummaryLine7( IEMSSeqStream *lpStream );

private:	// data

	ULONG               m_ulEpochOrbNum;
	double              m_dUSOFreq;
	double              m_dMedianLocAccuracy;
	int					m_iMedianLocAccSampleSize;
	WORD				m_wGeneralStatus;
	EMSTIME				m_tmActualAOS;
	EMSTIME				m_tmActualLOS;
	EMSTIME				m_tmLastClockSync;
	EMSTIME				m_tmEarliestSARP;
	EMSTIME				m_tmLastSARP;
};

#endif // INC_EMSIT661

