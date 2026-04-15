/******************************************************************** 
*	Module:			chanconv.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSChannelConvertor
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003 June 18 rvw	start

********************************************************************/

#include <windows.h>

#define EMSERROR_NODEFINE_TYPES		// prevent annoying Windows dupl defintions

#include "chanconv.h"
#include "leodefns.h"
#include "emslog.h"					// EMSLOGDATA
#include "locate.h"					// EMSLOCATE
#include "sigdata.h"
#include "spectrum.h"				//	EMSSPECTRUM
#include "cbcdata.h"					// EMSCBCDATA
#include "emsencod.h"
#include "emstrack.h"				// EMSSATTRACKRECORD
#include "leostats.h"				// EMSLEOSTATUSUPDATE
#include "calib406.h"
#include "emstle.h"

const WORD 	c_wCurrentVersion = MAKEWORD( 5, 1 );	// 1.5x

#pragma pack(1)

typedef struct  _tagEMSTLERECORD_V12
    {
    	EMSTIME time;
    	ULONG ulLutID;
    	ULONG ulSatID;
    	int nOrbitNumber;
    	EMSTIME timeEpoch;
    	double fXndt2o;
    	double fXndd6o;
    	double fBStar;
    	double fInclination;
    	double fRightAscNode;
    	double fEccentricity;
    	double fArgPerigee;
    	double fMeanAnomaly;
    	double fMeanMotion;
    	double fCoVarMatrix[ 21 ];
    	EMSTIME timeEffective;
    }	EMSTLERECORD_V12;

typedef struct _tagEMSTLERECORD_V12 __RPC_FAR *LPEMSTLERECORD_V12;

typedef struct  _tagEMSCBCDATA_V12
    {
    EMSSIGDATAIDTYPE hdr;
    float fFreqOffset;
    float fFreqQFactor;
    float fThreshold;
    WORD wEntryCount;
    WORD wFrequency[ 128 ];
    BYTE cAmplitude[ 128 ];
    WORD wSweepPeriod[ 128 ];
    WORD wSweepCorrelation[ 128 ];
    WORD wSweepSpan[ 128 ];
    }	EMSCBCDATA_V12;

typedef struct _tagEMSCBCDATA_V12 __RPC_FAR *LPEMSCBCDATA_V12;

typedef struct  _tagEMSSPECTRUM_V12
    {
    EMSSIGDATAID id;
    float fMaxPower;
    float fFreqOffset;
    float fFreqQFactor;
    float fAGCRMS;
    float fAGCMean;
    float fCarrierFrequency;
    float fModIndex;
    float fModIndexMean;
    float fModIndexRMS;
    ULONG ulMarkerBitRate;
    WORD wModIndexBlock;
    BYTE cAmplitude[ 2048 ];
    }	EMSSPECTRUM_V12;

typedef struct _tagEMSSPECTRUM_V12 __RPC_FAR *LPEMSSPECTRUM_V12;

typedef struct  _tagEMSLOGDATA_V12
    {
    EMSTIME time;
    ULONG ulLutID;
    ULONG ulProcessID;
    DWORD dwMsgNumber;
    BYTE cTaskID;
    BYTE cMsgType;
    BYTE cMsg[ 256 ];
    }	EMSLOGDATA_V12;

typedef struct _tagEMSLOGDATA_V12 __RPC_FAR *LPEMSLOGDATA_V12;

typedef 
enum _tagEMSLOCATETYPE_V12
    {	EMSLOCTYPE_V12_CBC	= 0x10,
	EMSLOCTYPE_V12_406	= 0x20,
	EMSLOCTYPE_V12_406_DOA	= 0x40,
	EMSLOCTYPE_V12_DETECT_ONLY	= 0x400,
	EMSLOCTYPE_V12_B_SIDE	= 0x800,
	EMSLOCTYPE_V12_CBC_DETECT	= 0x410,
	EMSLOCTYPE_V12_406_DETECT	= 0x420,
	EMSLOCTYPE_V12_406_DOA_DETECT	= 0x440,
	EMSLOCTYPE_V12_CBC_B	= 0x810,
	EMSLOCTYPE_V12_406_B	= 0x820,
	EMSLOCTYPE_V12_406_DOA_B	= 0x840,
	EMSLOCTYPE_V12_CBC_121	= EMSLOCTYPE_V12_CBC + 1,
	EMSLOCTYPE_V12_CBC_243	= EMSLOCTYPE_V12_CBC + 2,
	EMSLOCTYPE_V12_CBC_121_243	= EMSLOCTYPE_V12_CBC + 3,
	EMSLOCTYPE_V12_CBC_406	= EMSLOCTYPE_V12_CBC + 4,
	EMSLOCTYPE_V12_406_SARP	= EMSLOCTYPE_V12_406 + 1,
	EMSLOCTYPE_V12_406_SARR	= EMSLOCTYPE_V12_406 + 2,
	EMSLOCTYPE_V12_406_SARP_SARR	= EMSLOCTYPE_V12_406 + 3,
	EMSLOCTYPE_V12_406_FDOA	= EMSLOCTYPE_V12_406_DOA + 1,
	EMSLOCTYPE_V12_406_TDOA	= EMSLOCTYPE_V12_406_DOA + 2,
	EMSLOCTYPE_V12_406_FDOA_TDOA	= EMSLOCTYPE_V12_406_DOA + 3,
	EMSLOCTYPE_V12_CBC_121_B	= EMSLOCTYPE_V12_CBC_B + 1,
	EMSLOCTYPE_V12_CBC_243_B	= EMSLOCTYPE_V12_CBC_B + 2,
	EMSLOCTYPE_V12_CBC_121_243_B	= EMSLOCTYPE_V12_CBC_B + 3,
	EMSLOCTYPE_V12_CBC_406_B	= EMSLOCTYPE_V12_CBC_B + 4,
	EMSLOCTYPE_V12_406_SARP_B	= EMSLOCTYPE_V12_406_B + 1,
	EMSLOCTYPE_V12_406_SARR_B	= EMSLOCTYPE_V12_406_B + 2,
	EMSLOCTYPE_V12_406_SARP_SARR_B	= EMSLOCTYPE_V12_406_B + 3,
	EMSLOCTYPE_V12_406_FDOA_B	= EMSLOCTYPE_V12_406_DOA_B + 1,
	EMSLOCTYPE_V12_406_TDOA_B	= EMSLOCTYPE_V12_406_DOA_B + 2,
	EMSLOCTYPE_V12_406_FDOA_TDOA_B	= EMSLOCTYPE_V12_406_DOA_B + 3,
	EMSLOCTYPE_V12_CBC_121_DETECT	= EMSLOCTYPE_V12_CBC_DETECT + 1,
	EMSLOCTYPE_V12_CBC_243_DETECT	= EMSLOCTYPE_V12_CBC_DETECT + 2,
	EMSLOCTYPE_V12_CBC_121_243_DETECT	= EMSLOCTYPE_V12_CBC_DETECT + 3,
	EMSLOCTYPE_V12_CBC_406_DETECT	= EMSLOCTYPE_V12_CBC_DETECT + 4,
	EMSLOCTYPE_V12_406_SARP_DETECT	= EMSLOCTYPE_V12_406_DETECT + 1,
	EMSLOCTYPE_V12_406_SARR_DETECT	= EMSLOCTYPE_V12_406_DETECT + 2,
	EMSLOCTYPE_V12_406_SARP_SARR_DETECT	= EMSLOCTYPE_V12_406_DETECT + 3,
	EMSLOCTYPE_V12_406_FDOA_DETECT	= EMSLOCTYPE_V12_406_DOA_DETECT + 1,
	EMSLOCTYPE_V12_406_TDOA_DETECT	= EMSLOCTYPE_V12_406_DOA_DETECT + 2,
	EMSLOCTYPE_V12_406_FDOA_TDOA_DETECT	= EMSLOCTYPE_V12_406_DOA_DETECT + 3
    }	EMSLOCATETYPE_V12;

typedef struct  _tagEMSWLSLOCATE_V12
    {
    EMSLOCATION location;
    double dFrequency;
    float fFreqDrift;
    WORD wNumMsgs;
    WORD wNumMsgsUsed;
    WORD wNumBurstsUsed;
    WORD wNumIterations;
    float fRadiusErrEllipse;
    float fFreqBiasError;
    float fMajorError;
    float fMinorError;
    float fHeading;
    float fRMS;
    float fTrend;
    float fCoVarianceMatrix[ 10 ];
    }	EMSWLSLOCATE_V12;

typedef struct _tagEMSWLSLOCATE_V12 __RPC_FAR *LPEMSWLSLOCATE_V12;

typedef struct  _tagEMSCBCLOCATE_V12
    {
    float fSweep;
    float fSweepError;
    WORD wSidebands;
    }	EMSCBCLOCATE_V12;

typedef struct _tagEMSCBCLOCATE_V12 __RPC_FAR *LPEMSCBCLOCATE_V12;

typedef struct  _tagEMS406LOCATE_V12
    {
    BYTE cBeaconMsg[ 18 ];
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    }	EMS406LOCATE_V12;

typedef struct _tagEMS406LOCATE_V12 __RPC_FAR *LPEMS406LOCATE_V12;

typedef struct  _tagEMSLOCATE_V12
    {
    EMSTIME time;
    WORD wType;
    BYTE cSatIDs[ 16 ];
    BYTE cLutIDs[ 16 ];
    ULONG ulSatPassID;
    INT64 i64BeaconID;
    EMSWLSLOCATE_V12 wlsSolution;
    EMSTIME timeTCA;
    float fCrossTrackAngle;
    WORD wWindowFactor;
    float fConfidence;
    float fProbability;
    float fPower;
    EMSTIME timeFirstData;
    EMSTIME timeLastData;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSCBCLOCATE_V12 recCBC;
        /* [case()] */ EMS406LOCATE_V12 rec406;
        /* [default] */  /* Empty union arm */ 
        }	info;
    }	EMSLOCATE_V12;

typedef struct _tagEMSLOCATE_V12 __RPC_FAR *LPEMSLOCATE_V12;

typedef struct  _tagEMSCALIB406DATA_V12
    {
    EMSSIGDATAIDTYPE hdr;
    INT64 i64BeaconID;
    EMSTIME timeMsg;
    INT64 i64TimeOffset;
    WORD wStatus;
    WORD wDuplicateMsgCount;
    double dFrequency;
    float fFreqOffset;
    float fCarrierPower;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    WORD wBitErrorFrameSynch;
    BYTE cMsg[ 15 ];
    }	EMSCALIB406DATA_V12;


#pragma pack()

CEMSChannelConvertor::CEMSChannelConvertor()
{
	m_wCurrentVersion = c_wCurrentVersion;
}

CEMSChannelConvertor::~CEMSChannelConvertor()
{
}

bool CEMSChannelConvertor::IsCurrentVersion( EMSCHANNELSIGNATURE *lpInput )
{
	bool bCurrent = true;

	if ( lpInput )
	{
		 bCurrent = ( lpInput->version.wNumber == m_wCurrentVersion );
	}

	return bCurrent;
}

EMS_RESULT CEMSChannelConvertor::Convert( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, LPBYTE lpInputData, INT nLength, INT nChannel, WORD wVersion )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && ulMaxLen && lpInputData )
	{
		EMSCHANNELSIGNATURE sign;

		memset( &sign, 0, sizeof( sign ) );

		sign.version.wNumber = wVersion;

		sign.wChannel = nChannel;

		sign.nRecLength = nLength;

		hr = Convert( lpOutput, ulMaxLen, lpulLength, &sign, lpInputData );
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSChannelConvertor::Convert( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput , LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && ulMaxLen && lpInput )
	{
		if ( !lpInputData )
			lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

		if ( IsCurrentVersion( lpInput ) ) 
		{
			if ( lpInput->nRecLength <= (int)ulMaxLen )
			{
				ulRetLength = (ULONG)lpInput->nRecLength;

				memcpy( lpOutput, lpInputData, ulRetLength );
			}
			else
				hr = EMS_UNKNOWN_ERROR;
		}
		else
		{
			switch ( lpInput->wChannel )
			{
				case LEO_TLE_DATA:
					hr = _ConvertTLEData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case  LEO_LOG_DATA:
					hr = _ConvertLogData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case LEO_SOLUTION_DATA:	// in DBUtil by mistake
				case LEO_LOCATE_DATA:
					hr = _ConvertLocateData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case LEO_SAT_TRACK_PASS_DATA:
					hr = _ConvertPassScheduleData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;
					
				case LEO_SPECTRUM_DATA:
					hr = _ConvertSpectrumData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case LEO_STATUS_DATA:
					hr = _ConvertStatusData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case LEO_CALIBRATE_406_DATA:
					hr = _ConvertCalib406Data( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;

				case LEO_CBC_DATA:
					hr = _ConvertRawCBCData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
					break;
			
				default:
					switch ( lpInput->nRecLength )
					{
						case sizeof( EMSLEOSTATUSUPDATE ):
							hr = _ConvertStatusData( lpOutput, ulMaxLen, &ulRetLength, lpInput, lpInputData );
							break;

						default:
							break;
					}
					hr = EMS_OK;
					break;
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertCalib406Data( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSCALIB406DATA ) )
		{
			EMSCALIB406DATA calib406Data;

			if ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &calib406Data, 0, sizeof( calib406Data ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						EMSCALIB406DATA_V12 *lpOldCalib = (EMSCALIB406DATA_V12*)lpInputData;

						int nLength = sizeof( EMSCALIB406DATA_V12 );

						calib406Data.hdr = lpOldCalib->hdr;

						calib406Data.ulPassID = 0;

						calib406Data.i64BeaconID = lpOldCalib->i64BeaconID;
						calib406Data.timeMsg = lpOldCalib->timeMsg;
						calib406Data.i64TimeOffset = lpOldCalib->i64TimeOffset;
						calib406Data.wStatus = lpOldCalib->wStatus;
						calib406Data.wDuplicateMsgCount = lpOldCalib->wDuplicateMsgCount;
						calib406Data.dFrequency = lpOldCalib->dFrequency;
						calib406Data.fFreqOffset = lpOldCalib->fFreqOffset;
						calib406Data.fCarrierPower = lpOldCalib->fCarrierPower;
						calib406Data.wBitErrorField1 = lpOldCalib->wBitErrorField1;
						calib406Data.wBitErrorField2 = lpOldCalib->wBitErrorField2;
						calib406Data.wBitErrorFrameSynch = lpOldCalib->wBitErrorFrameSynch;

						memcpy( &calib406Data.cBeaconMsg[ 3 ], lpOldCalib->cMsg, 
											sizeof( lpOldCalib->cMsg ) );
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( calib406Data );

				memcpy( lpOutput, &calib406Data, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertRawCBCData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSCBCDATA ) )
		{
			EMSCBCDATA cbcData;

			if ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &cbcData, 0, sizeof( cbcData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						LPEMSCBCDATA_V12 lpOldCBC = (LPEMSCBCDATA_V12)lpInputData;

						cbcData.hdr = lpOldCBC->hdr;

						cbcData.ulPassID = 0;

						cbcData.fFreqOffset = lpOldCBC->fFreqOffset;

						cbcData.fFreqQFactor = lpOldCBC->fFreqQFactor;

						cbcData.fThreshold = lpOldCBC->fThreshold;

						cbcData.wEntryCount = lpOldCBC->wEntryCount;

						for ( int i = 0; i < cbcData.wEntryCount; i++ )
						{
							cbcData.wFrequency[i] = lpOldCBC->wFrequency[i];

							cbcData.cAmplitude[i] = lpOldCBC->cAmplitude[i];

							cbcData.wSweepPeriod[i] = lpOldCBC->wSweepPeriod[i];

							cbcData.wSweepCorrelation[i] = lpOldCBC->wSweepCorrelation[i];

							cbcData.wSweepSpan[i] = lpOldCBC->wSweepSpan[i];
						}
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( cbcData );

				memcpy( lpOutput, &cbcData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertLocateData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSLOCATE ) )
		{
			EMSLOCATE locateData;

			if ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &locateData, 0, sizeof( locateData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						LPEMSLOCATE_V12 lpOldLocate = (LPEMSLOCATE_V12)lpInputData;

						memcpy( locateData.cSatIDs, lpOldLocate->cSatIDs,
												sizeof( locateData.cSatIDs ) ) ;

						memcpy( locateData.cLutIDs, lpOldLocate->cLutIDs,
												sizeof( locateData.cLutIDs ) ) ;

						locateData.time = lpOldLocate->time;

						locateData.ulLutID = 0;

						ULONG ulCount = 0;

						CEMSEncodedLutID::Expand( (EMSENCODEDLUTID *)locateData.cLutIDs, 
							&locateData.ulLutID, 1, &ulCount );

						locateData.wType = lpOldLocate->wType;

						locateData.ulSatPassID = lpOldLocate->ulSatPassID;

						locateData.i64BeaconID = lpOldLocate->i64BeaconID;

						locateData.timeTCA = lpOldLocate->timeTCA;

						locateData.fCrossTrackAngle = lpOldLocate->fCrossTrackAngle;

						locateData.wWindowFactor = lpOldLocate->wWindowFactor;

						locateData.fConfidence = lpOldLocate->fConfidence;

						locateData.fProbability = lpOldLocate->fProbability;

						locateData.fPower = lpOldLocate->fPower;

						locateData.timeFirstData = lpOldLocate->timeFirstData;

						locateData.timeLastData = lpOldLocate->timeLastData;

						locateData.wlsSolution.location = lpOldLocate->wlsSolution.location;
						locateData.wlsSolution.dFrequency = lpOldLocate->wlsSolution.dFrequency;
						locateData.wlsSolution.fFreqDrift = lpOldLocate->wlsSolution.fFreqDrift;
						locateData.wlsSolution.wNumMsgs = lpOldLocate->wlsSolution.wNumMsgs;
						locateData.wlsSolution.wNumMsgsUsed = lpOldLocate->wlsSolution.wNumMsgsUsed;
						locateData.wlsSolution.wNumBurstsUsed = lpOldLocate->wlsSolution.wNumBurstsUsed;
						locateData.wlsSolution.wNumIterations = lpOldLocate->wlsSolution.wNumIterations;
						locateData.wlsSolution.fRadiusErrEllipse = lpOldLocate->wlsSolution.fRadiusErrEllipse;
						locateData.wlsSolution.fFreqBiasError = lpOldLocate->wlsSolution.fFreqBiasError;
						locateData.wlsSolution.fMajorError = lpOldLocate->wlsSolution.fMajorError;
						locateData.wlsSolution.fMinorError = lpOldLocate->wlsSolution.fMinorError;
						locateData.wlsSolution.fHeading = lpOldLocate->wlsSolution.fHeading;
						locateData.wlsSolution.fRMS = lpOldLocate->wlsSolution.fRMS;
						locateData.wlsSolution.fTrend = lpOldLocate->wlsSolution.fTrend;
						locateData.wlsSolution.location = lpOldLocate->wlsSolution.location;

						memcpy( locateData.wlsSolution.fCoVarianceMatrix, 
								lpOldLocate->wlsSolution.fCoVarianceMatrix,
								sizeof( locateData.wlsSolution.fCoVarianceMatrix ) );

						if ( ( locateData.wType & EMSLOCTYPE_CBC ) == EMSLOCTYPE_CBC ) 
						{
							locateData.info.recCBC.fSweep = lpOldLocate->info.recCBC.fSweep;
							locateData.info.recCBC.fSweepError = lpOldLocate->info.recCBC.fSweepError;
							locateData.info.recCBC.wSidebands = lpOldLocate->info.recCBC.wSidebands;
						}
						else
						{
							memcpy( locateData.info.rec406.cBeaconMsg, 
								lpOldLocate->info.rec406.cBeaconMsg, sizeof( locateData.info.rec406.cBeaconMsg ) );
							locateData.info.rec406.wBitErrorFrameSync = 0;
							locateData.info.rec406.wBitErrorField1 = lpOldLocate->info.rec406.wBitErrorField1;
							locateData.info.rec406.wBitErrorField2 = lpOldLocate->info.rec406.wBitErrorField2;
						}
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( locateData );

				memcpy( lpOutput, &locateData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertSpectrumData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSSPECTRUM ) )
		{
			EMSSPECTRUM spectrumData;

			if  ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &spectrumData, 0, sizeof( spectrumData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						LPEMSSPECTRUM_V12 lpOldSpectrum = (LPEMSSPECTRUM_V12)lpInputData;

						spectrumData.id = lpOldSpectrum->id;
						spectrumData.fMaxPower = lpOldSpectrum->fMaxPower;
						spectrumData.fFreqOffset = lpOldSpectrum->fFreqOffset;
						spectrumData.fFreqQFactor = lpOldSpectrum->fFreqQFactor;
						spectrumData.fAGCRMS = lpOldSpectrum->fAGCRMS;
						spectrumData.fAGCMean = lpOldSpectrum->fAGCMean;
						spectrumData.fCarrierFrequency = lpOldSpectrum->fCarrierFrequency;
						spectrumData.fModIndexMean = lpOldSpectrum->fModIndexMean;
						spectrumData.fModIndexRMS = lpOldSpectrum->fModIndexRMS;
						spectrumData.ulMarkerBitRate = lpOldSpectrum->ulMarkerBitRate;
						spectrumData.wModIndexBlock = lpOldSpectrum->wModIndexBlock;
						for ( int i = 0; i < 2048; i++ )
							spectrumData.cAmplitude[ i ] = lpOldSpectrum->cAmplitude[ i ];
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( spectrumData );

				memcpy( lpOutput, &spectrumData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertLogData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSLOGDATA ) )
		{
			EMSLOGDATA logData;

			if ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &logData, 0, sizeof( logData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						LPEMSLOGDATA_V12 lpOldLogData = (LPEMSLOGDATA_V12)lpInputData;

						logData.time = lpOldLogData->time;
    					logData.ulLutID = lpOldLogData->ulLutID;
    					logData.ulProcessID = lpOldLogData->ulProcessID;
	    				logData.dwMsgNumber = lpOldLogData->dwMsgNumber;
  	  				logData.cTaskID = lpOldLogData->cTaskID;
    					logData.cMsgType = lpOldLogData->cMsgType;

						memcpy( logData.cMsg, lpOldLogData->cMsg, sizeof( logData.cMsg ) );
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( logData );

				memcpy( lpOutput, &logData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertPassScheduleData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSSATTRACKRECORD ) )
		{
			EMSSATTRACKRECORD scheduleData;

			if ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &scheduleData, 0, sizeof( scheduleData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						if ( lpInput->nRecLength == sizeof( scheduleData ) )
							memcpy( &scheduleData, lpInputData, sizeof(scheduleData ) );
						else
							hr = EMS_UNKNOWN_ERROR;
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( scheduleData );

				memcpy( lpOutput, &scheduleData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertTLEData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSTLERECORD ) )
		{
			EMSTLERECORD tleData;

			if  ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &tleData, 0, sizeof( tleData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						EMSTLERECORD_V12 *lpOldTLE = ( EMSTLERECORD_V12* )lpInputData;

						tleData.time = lpOldTLE->time;
						tleData.ulLutID = lpOldTLE->ulLutID;
						tleData.ulSatID = lpOldTLE->ulSatID;
						tleData.nOrbitNumber = lpOldTLE->nOrbitNumber;
						tleData.timeEpoch = lpOldTLE->timeEpoch;
						tleData.fXndt2o = lpOldTLE->fXndt2o;
						tleData.fXndd6o = lpOldTLE->fXndd6o;
						tleData.fBStar = lpOldTLE->fBStar;
						tleData.fInclination = lpOldTLE->fInclination;
						tleData.fRightAscNode = lpOldTLE->fRightAscNode;
						tleData.fEccentricity = lpOldTLE->fEccentricity;
						tleData.fArgPerigee = lpOldTLE->fArgPerigee;
						tleData.fMeanAnomaly = lpOldTLE->fMeanAnomaly;
						tleData.fMeanMotion = lpOldTLE->fMeanMotion;

						for ( int i = 0; i < 21; i++ )
						{
							tleData.fCoVarMatrix[i] = lpOldTLE->fCoVarMatrix[i];
						}
						tleData.timeEffective = lpOldTLE->timeEffective;
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( tleData );

				memcpy( lpOutput, &tleData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}

EMS_RESULT CEMSChannelConvertor::_ConvertStatusData( LPBYTE lpOutput, ULONG ulMaxLen, ULONG *lpulLength, EMSCHANNELSIGNATURE *lpInput, LPBYTE lpInputData )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulRetLength = 0;

	if ( lpOutput && lpInput )
	{
		if ( ulMaxLen >= sizeof( EMSLEOSTATUSUPDATE ) )
		{
			EMSLEOSTATUSUPDATE statusData;

			if  ( !lpInputData )
				lpInputData = (LPBYTE)lpInput + sizeof( EMSCHANNELSIGNATURE );

			memset( &statusData, 0, sizeof( statusData ) );

			switch ( lpInput->version.wNumber )
			{
				case MAKEWORD( 2, 1 ):	// 1.2x
					{
						if ( lpInput->nRecLength == sizeof( statusData ) )
							memcpy( &statusData, lpInputData, sizeof(statusData ) );
						else
							hr = EMS_UNKNOWN_ERROR;
					}
					break;

				default:
					hr = EMS_UNKNOWN_ERROR;
					break;
			}

			if ( hr == EMS_OK )
			{
				ulRetLength = sizeof( statusData );

				memcpy( lpOutput, &statusData, ulRetLength );
			}
		}
		else
			hr = EMS_UNKNOWN_ERROR;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulLength )
		*lpulLength = ulRetLength;
	
	return hr;
}
