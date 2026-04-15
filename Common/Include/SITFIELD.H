/********************************************************************
*	Module:			sitfield.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of SIT Message Field Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5	rvw	start

********************************************************************/
#ifndef INC_SITFIELD
#define INC_SITFIELD

#include "emstypes.h"
#include "emspipe.h"
#include "emserror.h"
#include "emstime.h"
#include "emssit.h"
#include "emsmanoeuvre.h"
#include "lineterminator.h"
#include "gpsephem.h"

typedef	struct _tagEMSSITMF605
{
	TCHAR cValue[4];
} EMSSITMF605, *LPEMSSITMF605;

typedef	struct _tagEMSSITMF610
{
	TCHAR cValue[3];
} EMSSITMF610, *LPEMSSITMF610;


/************************************* Note ***********************************
	Each TextMFnn method (by design) returns a pointer to a static array of 
	TCHAR and so each MF that has its TextMF method has to have its own static
	string and cannot use another TextMF method of a different MF number.
	
	As an example, the following method definition may cause bugs and wrong    
	returned value.
	
	LPCTSTR TextMF29( EMSTIME timeNextVis ) { return TextMF3( timeNextVis ); }
	
	And should not call TextMF3(). See the implemetation of TextMF29() as an
	example.
******************************************************************************/

class CEMSSitMsgField
{
public:
	CEMSSitMsgField( );
	virtual ~CEMSSitMsgField();

	BOOL IsEOL( LPCTSTR lpcszField );
	EMS_RESULT GetMF1( LPCTSTR lpcszField, int *lpMsgId, int *lpLastMsgId );
	EMS_RESULT GetMF1A( LPCTSTR lpcszField, int *lpMsgId );
	EMS_RESULT GetMF2( LPCTSTR lpcszField, int *lpMCCID );
	EMS_RESULT GetMF3( LPCTSTR lpcszField, EMSTIME *lpTimeMsg );
	LPCTSTR TextMF3( EMSTIME timeMsgTransmit );
	EMS_RESULT GetMF4( LPCTSTR lpcszField, int *lpnSitNumber );
	EMS_RESULT GetMF4A( LPCTSTR lpcszField, EMSSITCODE *lpSitCode );
	EMS_RESULT GetMF5( LPCTSTR lpcszField, int *lpnDestID );
	EMS_RESULT GetMF5A( LPCTSTR lpcszField, int *lpnDestID );
	EMS_RESULT GetMF6( LPCTSTR lpcszField, int *lpnSatID );
	EMS_RESULT GetMF6A( LPCTSTR lpcszField, int *lpnSatID );
	EMS_RESULT GetMF7( LPCTSTR lpcszField, int *lpnOrbitNumber );
	EMS_RESULT GetMF7A( LPCTSTR lpcszField, int *lpnOrbitNumber );
	EMS_RESULT GetMF7B( LPCTSTR lpcszField, int *lpnOrbitNumber );
	EMS_RESULT GetMF8( LPCTSTR lpcszField, int *lpnAlertCount );
	EMS_RESULT GetMF8A( LPCTSTR lpcszField, int *lpnAlertCount );
	EMS_RESULT GetMF8B( LPCTSTR lpcszField, int *lpn121LocCount );
	EMS_RESULT GetMF8C( LPCTSTR lpcszField, int *lpn243LocCount );
	EMS_RESULT GetMF8D( LPCTSTR lpcszField, int *lpn406IntLocCount );
	EMS_RESULT GetMF8E( LPCTSTR lpcszField, int *lpn406LocCount );
	EMS_RESULT GetMF8F( LPCTSTR lpcszField, int *lpnMedianLocAccSampleSize );
	EMS_RESULT GetMF10( LPCTSTR lpcszField, int *lpnAlertCount );
	EMS_RESULT GetMF10A( LPCTSTR lpcszField, int *lpnAlertCount );
	EMS_RESULT GetMF10B( LPCTSTR lpcszField, int *lpn406UnlocatedBeacons );
	EMS_RESULT GetMF10C( LPCTSTR lpcszField, int *lpnUnlocatedAlerts );
	EMS_RESULT GetMF11( LPCTSTR lpcszField, int *lpnLutID );
	EMS_RESULT GetMF12( LPCTSTR lpcszField, BOOL *lpbLocalFlag, int *lpnFreqBand );
	
	EMS_RESULT GetMF12A( LPCTSTR lpcszField, TCHAR* lpcDataType );

	EMS_RESULT GetMF13( LPCTSTR lpcszField, 
					double *lpdBias, double *lpdBSDev, double *lpdDrift );

	LPCTSTR TextMF13(	double dBias, double dBSDev, double dDrift );


	EMS_RESULT GetMF14( LPCTSTR lpcszField, EMSTIME *lpTimeTCA );
	LPCTSTR TextMF14( EMSTIME timeTCA );
	LPCTSTR TextMF14A( EMSTIME timeFirstDetect );
	LPCTSTR TextMF14B( EMSTIME timeLastDetect );
	EMS_RESULT GetMF15( LPCTSTR lpcszField, int *lpnWindowFactor );
	EMS_RESULT GetMF16( LPCTSTR lpcszField, int *lpnIterations );
	LPCTSTR TextMF17( double dCTA );
	EMS_RESULT GetMF17A( LPCTSTR lpcszField, double* lpdCTA );
	LPCTSTR TextMF17A( double dCTA );

	EMS_RESULT GetMF18( LPCTSTR lpcszField, int *lpnSecondaryLutID );
	EMS_RESULT GetMF19( LPCTSTR lpcszField, int *lpnSideBands );

	EMS_RESULT GetMF20( LPCTSTR lpcszField, int *lpnSweepPeriod, int *lpnSweepPeriodSdev );

	EMS_RESULT GetMF21( LPCTSTR lpcszField, int *lpnNumPoints );
	EMS_RESULT GetMF21A( LPCTSTR lpcszField, int *lpnNumPoints );
	EMS_RESULT GetMF21B( LPCTSTR lpcszField, int *lpnNumPoints );

	LPCTSTR TextMF22( const INT64 ci64BeaconID );

	// 30Hex beacon message
	EMS_RESULT GetMF23( LPCTSTR lpcszField, BYTE* pacBeaconMsg );
	LPCTSTR TextMF23( const BYTE* cabyBeaconMsg );

	EMS_RESULT GetMF25( LPCTSTR lpcszField, double* lpdLatitude );
	LPCTSTR TextMF25( const double dLatitude );
	EMS_RESULT GetMF25A( LPCTSTR lpcszField, double* lpdLatitude );
	LPCTSTR TextMF25A( const double dLatitude );
	EMS_RESULT GetMF26( LPCTSTR lpcszField, double* lpdLongitude );
	LPCTSTR TextMF26( const double dLongitude );
	EMS_RESULT GetMF26A( LPCTSTR lpcszField, double* lpdLongitude );
	LPCTSTR TextMF26A( const double dLongitude );

	EMS_RESULT GetMF27( LPCTSTR lpcszField, double* lpdErrorElAngle, double* lpdErrorElMajor, double* lpdErrorElMinor );
	LPCTSTR TextMF27( double dErrorElAngle, double dErrorElMajor, double dErrorElMinor );
	EMS_RESULT GetMF28( LPCTSTR lpcszField, double *lpdProbability );
	EMS_RESULT GetMF29( LPCTSTR lpcszField, EMSTIME *lptimeNextVis );
	LPCTSTR TextMF29( EMSTIME timeNextVis );
	EMS_RESULT GetMF30( LPCTSTR lpcszField, double *lpdConfidence );
	EMS_RESULT GetMF31( LPCTSTR lpcszField, double* lpdDataResSdev, double* lpdDataResTrend );
	EMS_RESULT GetMF32( LPCTSTR lpcszField, int *lpnVectorCount );

	EMS_RESULT GetMF34( LPCTSTR lpcszField, EMSTIME *lptimeOrbit );
	LPCTSTR TextMF34( EMSTIME timeOrbit );
	EMS_RESULT GetMF35( LPCTSTR lpcszField, EMSVECTOR *lpvPosition );
	EMS_RESULT GetMF35A( LPCTSTR lpcszField, EMSVECTOR *lpvPosition );
	EMS_RESULT GetMF36( LPCTSTR lpcszField, EMSVECTOR *lpvVelocity );
	EMS_RESULT GetMF36A( LPCTSTR lpcszField, EMSVECTOR *lpvVelocity );
	EMS_RESULT GetMF37( LPCTSTR lpcszField, EMSTIME *lptimeCalib );
	LPCTSTR TextMF37( EMSTIME timeCalib );
	EMS_RESULT GetMF38( LPCTSTR lpcszField, double *lpdCalibFreq );
	LPCTSTR TextMF38( const double cdCalibFreq );
	EMS_RESULT GetMF38A( LPCTSTR lpcszField, double *lpdCalibFreq );
	LPCTSTR TextMF38A( const double cdCalibFreq );

	EMS_RESULT GetMF44( LPCTSTR lpcszField, int *lpnNumberSpacecraft );

	EMS_RESULT GetMF64( LPCTSTR lpcszField, double *lpdFreqOffset );
	EMS_RESULT GetMF65( LPCTSTR lpcszField, double *lpdFreqDrift );
	EMS_RESULT GetMF66( LPCTSTR lpcszField, EMSTIME *lpTimeMsg );
	LPCTSTR TextMF66( EMSTIME tm );

	EMS_RESULT GetMF67( LPCTSTR lpcszField, EMSTIME* pstrTime );
	LPCTSTR TextMF67( EMSTIME tm );
	LPCTSTR TextMF67( INT64 tm );
	EMS_RESULT GetMF67Ex( LPCTSTR lpcszField, EMSTIME* pstrTime );
	EMS_RESULT GetMF68( LPCTSTR lpcszField, double* pdFreq );
	EMS_RESULT GetMF69( LPCTSTR lpcszField, double* pdOffset );
	EMS_RESULT GetMF70( LPCTSTR lpcszField, double* pdOffset );
	EMS_RESULT GetMF71( LPCTSTR lpcszField, int* piAntennaData );
	EMS_RESULT GetMF72( LPCTSTR lpcszField, double* pdCN0 );
	EMS_RESULT GetMF74( LPCTSTR lpcszField, int* piNumDataBlocks );
	EMS_RESULT GetMF75( LPCTSTR lpcszField, double* pdBitRate );
	EMS_RESULT GetMF76( LPCTSTR lpcszField, WORD* pwSpare );
	EMS_RESULT GetMF76Ex( LPCTSTR lpcszField, WORD* pwSpare );

	EMS_RESULT GetMF601( LPCTSTR lpcszField, int* lpnSolutions );
	EMS_RESULT GetMF602( LPCTSTR lpcszField, EMSTIME *lptimeAOS );

	LPCTSTR TextMF602( EMSTIME timeAOS );
	EMS_RESULT GetMF602A( LPCTSTR lpcszField, EMSTIME *lptimeAOS );
	LPCTSTR TextMF602A( EMSTIME timeAOS );

	EMS_RESULT GetMF603( LPCTSTR lpcszField, EMSTIME *lptimeLOS );
	LPCTSTR TextMF603( EMSTIME timeLOS );
	EMS_RESULT GetMF603A( LPCTSTR lpcszField, EMSTIME *lptimeLOS );
	LPCTSTR TextMF603A( EMSTIME timeLOS );

	EMS_RESULT GetMF604( LPCTSTR lpcszField, int *lpnSecsDuration );
	EMS_RESULT GetMF605( LPCTSTR lpcszField, LPEMSSITMF605 lpMF );
	EMS_RESULT GetMF606( LPCTSTR lpcszField, int *lpnCount );
	EMS_RESULT GetMF607( LPCTSTR lpcszField, double *lpdOrbitPositionOffset );
	EMS_RESULT GetMF608( LPCTSTR lpcszField, double *lpdOrbitVelocityOffset );

	EMS_RESULT GetMF609( LPCTSTR lpcszField, EMSTIME *lpTimeSolnProcessing );

	LPCTSTR TextMF609( EMSTIME timeProcessCompleted );

	EMS_RESULT GetMF610( LPCTSTR lpcszField, LPEMSSITMF610 lpData );
	EMS_RESULT GetMF611( LPCTSTR lpcszField, int* lpnOrbitUpdateStatus );
	EMS_RESULT GetMF612( LPCSTR lpcszField, TCHAR* pszString, int iStringLen );
	EMS_RESULT GetMF613( LPCTSTR lpcszField, int *lpnAzAOL ); 
	EMS_RESULT GetMF614( LPCTSTR lpcszField, int *lpnAzPeak );
	EMS_RESULT GetMF615( LPCTSTR lpcszField, int *lpnAzLOS );
	EMS_RESULT GetMF616( LPCTSTR lpcszField, int *lpnMaxElevation );

	EMS_RESULT GetMF618( LPCTSTR lpcszField, EMSSITSOLNTYPE *lpSolnType );

	EMS_RESULT GetMF619( LPCTSTR lpcszField, int *lpnTransmissionType );

	EMS_RESULT GetMF620( LPCTSTR lpcszField, EMSTIME *lpStartTime );
	EMS_RESULT GetMF620Ex( LPCTSTR lpcszField, EMSTIME *lpStartTime );

	EMS_RESULT GetMF621( LPCTSTR lpcszField, EMSTIME *lpEndTime );

	EMS_RESULT GetMF622( LPCTSTR lpcszField, double* lpdLatLongCorrCoeff );
	LPCTSTR TextMF622( double dCorrCoeff );

	EMS_RESULT GetMF623( LPCTSTR lpcszField, int *lpnSeconds );
	EMS_RESULT GetMF624( LPCTSTR lpcszField, int *lpnSeconds );

	EMS_RESULT GetMF625( LPCSTR lpcszField, int *lpnSeconds );
	EMS_RESULT GetMF626( LPCSTR lpcszField, int *lpnPreamble, int *lpdnPF1, int *lpdnPF2 );
	LPCTSTR	   TextMF626( const int ciErrCountPreamble, const int ciErrCountPDF1, const int ciErrCountPDF2 );
	EMS_RESULT GetMF627( LPCSTR lpcszField, int *lpnDuplicates );
	EMS_RESULT GetMF628( LPCSTR lpcszField, double *lpdPower );
	EMS_RESULT GetMF629( LPCSTR lpcszField, int *lpnSecsCollecting );
	EMS_RESULT GetMF630( LPCSTR lpcszField, int *lpnPercentageCollecting );
	EMS_RESULT GetMF633( LPCSTR lpcszField, int *lpnAlarmMessages );
	EMS_RESULT GetMF634( LPCSTR lpcszField, int *lpnWarningMessages );
	EMS_RESULT GetMF635( LPCSTR lpcszField, int *lpnMsgCount );
	EMS_RESULT GetMF636( LPCSTR lpcszField, int *lpnSarrMessages );
	EMS_RESULT GetMF637( LPCTSTR lpcszField, int *lpnPDSRecoveryRate, int *lpnFramesMissed );
	EMS_RESULT GetMF638( LPCSTR lpcszField, int *lpnTotalPDSCount );
	EMS_RESULT GetMF639( LPCSTR lpcszField, int *lpnDistinctPDSCount );
	EMS_RESULT GetMF640( LPCSTR lpcszField, TCHAR* pszString, int iStringLen );
	EMS_RESULT GetMF641( LPCSTR lpcszField, TCHAR* pszString, int iStringLen );
	EMS_RESULT GetMF645( LPCSTR lpcszField, EMSSITFIELD* sitField );
	EMS_RESULT GetMF647( LPCSTR lpcszField, double *lpdFreq, double *lpdFreqOffset );
	EMS_RESULT GetMF648( LPCSTR lpcszField, EMSTIME *lptimeMsg, double *lpdTimeOffset );
	EMS_RESULT GetMF650( LPCTSTR lpcszField, int *lpnCheckCode, int *lpnCheckSum );
	EMS_RESULT GetMF652( LPCTSTR lpcszField, EMSTIME *lpStartTime );
	EMS_RESULT GetMF652Ex( LPCTSTR lpcszField, EMSTIME *lpStartTime );
	EMS_RESULT GetMF653( LPCTSTR lpcszField, double *lpdDuration );
	EMS_RESULT GetMF654( LPCTSTR lpcszField, double *lpdFreqBandwidth );
	EMS_RESULT GetMF655( LPCTSTR lpcszField, int nMax, 
										double **lplpdFreqCoeff,	int *lpnCount ); 
	EMS_RESULT GetMF656( LPCTSTR lpcszField, int *lpnOrderPolynomial);

	EMS_RESULT GetMF660( LPCTSTR lpcszField, EMSMANOEUVRETYPE*   pManoeuvreType );       // manoeuvre type
	LPCTSTR TextMF660( EMSMANOEUVRETYPE manType );
	EMS_RESULT GetMF661( LPCTSTR lpcszField, EMSTIME*            pManoeuvreStartTime );  // time of manoeuvre start
	EMS_RESULT GetMF662( LPCTSTR lpcszField, int*                piManoeuvreDuration );  // manoeuvre duration
	EMS_RESULT GetMF663( LPCTSTR lpcszField, EMSMANOEUVRESTATUS* pManoeuvreType );       // manoeuvre type
	LPCTSTR TextMF663( EMSMANOEUVRESTATUS manStatus );
	LPCTSTR TextMF664( EMSTIME timeOrbitEffective );

	EMS_RESULT GetMF664( LPCTSTR lpcszField, EMSTIME *lptimeOrbitEffective );   // orbit data effective time
	EMS_RESULT GetMF665( LPCTSTR lpcszField, WORD* pwStatus );
	EMS_RESULT GetMF666( LPCTSTR lpcszField, EMSTIME *lptmLastClockSync );
	LPCTSTR TextMF666( EMSTIME timeClkSync );
	EMS_RESULT GetMF667( LPCTSTR lpcszField, EMSTIME *lptmEarliestSARP );
	LPCTSTR TextMF667( EMSTIME tmEarliestSARP );
	EMS_RESULT GetMF668( LPCTSTR lpcszField, EMSTIME *lptmLastSARP );
	LPCTSTR TextMF668( EMSTIME timeLastSARP );
	EMS_RESULT GetMF669( LPCTSTR lpcszField, double* pdMedianLocAcc );

	// Get MF665, an IP Address.
	EMS_RESULT GetMF677( LPCSTR lpcszField, TCHAR* pszString, int iStringLen );

	// Get MF666, a network connection status.
	EMS_RESULT GetMF678( LPCSTR lpcszField, TCHAR* pcConStatus );

	// Get MF667, a network connection type.
	EMS_RESULT GetMF679( LPCSTR lpcszField, TCHAR* pcConType );

	EMS_RESULT GetMFN4( LPCTSTR lpcszField, EMSTIME *lptimeFirst );
	LPCTSTR TextMFN4( EMSTIME timeFirst );
	EMS_RESULT GetMFN5( LPCTSTR lpcszField, EMSTIME *lptimeLast );
	LPCTSTR TextMFN5( EMSTIME timeLast );
	
	EMS_RESULT GetMFN1( LPCTSTR lpcszField, int *lpiWaveID );
	EMS_RESULT GetMFN6( LPCTSTR lpcszField, int *lpiNumBursts );
	EMS_RESULT GetMFN7( LPCTSTR lpcszField, int *lpiNumMsgs );
	EMS_RESULT GetMFN8( LPCTSTR lpcszField, double *lpdFreq );
	EMS_RESULT GetMFN9( LPCTSTR lpcszField, double *lpdQF );
	EMS_RESULT GetMFN22( LPCTSTR lpcszField, __int64* lpi64BcnId );

	// 36Hex beacon message
	EMS_RESULT GetMF82( LPCTSTR lpcszField, BYTE* pacBeaconMsg );
	LPCTSTR TextMF82( const BYTE* cabyBeaconMsg );

	// 55Hex beacon message
	EMS_RESULT GetMF99( LPCTSTR lpcszField, BYTE* pacBeaconMsg );
	LPCTSTR TextMF99( const BYTE* cabyBeaconMsg );

	// Defined for MEO by C-S.  The definition has changed.  Create a new
	// method to maintain backward compatability.
	LPCTSTR TextMF75A( double dX, double dY, double dZ );
	EMS_RESULT GetMF75A( LPCTSTR lpccszField, double& rdX, double& rdY, double& rdZ );

	// Defined for MEO by C-S.  The definition has changed.  Create a new
	// method to maintain backward compatability.
	LPCTSTR TextMF76A( double dX, double dY, double dZ );
	EMS_RESULT GetMF76A( LPCTSTR lpcszField, double& rdX, double& rdY, double& rdZ );

	// Defined for MEO by C-S.
	LPCTSTR TextMF77( const double cdAltitude );
	LPCTSTR TextMF79( const double cdMeanCN );

	// Extensions (for MEOSAR SARVTB);
	LPCTSTR TextMFA01( EMSTIME time );
	LPCTSTR TextMFE07( const BYTE* cabyBeaconMsg );
	EMS_RESULT GetMFB01( LPCTSTR lpcszField, EMSUTCCONVERSION *lpUtcConversion );
	EMS_RESULT GetMFB02( LPCTSTR lpcszField, EMSSCALEDEPHEMERISDATAEX *lpScaledEphem );

private: // methods
	EMS_RESULT _GetAlphaField( LPCTSTR lpcszField, LPCSTR lpcszSyntax, TCHAR* pszString, int iStringLen );
	EMS_RESULT _GetIntegerField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, int *lpnNumber );
	EMS_RESULT _GetDecimalField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, double *lpdNumber );
	EMS_RESULT _GetDecimalField( LPCTSTR lpcszField, LPCSTR lpcszSyntax, float *lpfNumber );
	EMS_RESULT _GetVectorField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSVECTOR *lpVector );
	EMS_RESULT _CheckSyntax( LPCTSTR lpcszField, LPCTSTR lpcszSyntax );
	EMS_RESULT _GetTime( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSTIME *lpTime );
	BOOL _ValidSitCode( EMSSITCODE sitCode );
	int _GetMinLength( LPCTSTR lpcszSyntax );
	EMS_RESULT _GetUTCConversionField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSUTCCONVERSION *lpUtcConversion );
	EMS_RESULT _GetScaledEphemField( LPCTSTR lpcszField, LPCTSTR lpcszSyntax, EMSSCALEDEPHEMERISDATAEX *lpScaledEphem );

	// time format "nn nnn nnnn"
	void _TextTime( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen );
	// time format "nn nnn nnnn nn.nn"
	void _TextTime1( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen );
	// time format "nn nnn nnnn nn.nnn"
	void _TextTime2( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen );
	// time format "nn nnn nnnn nn.nnnnnn"
	void _TextTime3( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen );
	// time format "nn nnn nnnn nn"
	void _TextTime4( const EMSTIME cTime, TCHAR* pszText, const int iMaxLen );

private: // data
	CEMSLineTerminator m_LT;
};

#endif // INC_SITFIELD
