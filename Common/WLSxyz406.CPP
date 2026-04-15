/********************************************************************
*	Module:			WLSxyz406.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth    	Changes
	===	====			====	    =======

  0.0 01/11/2010	   R.Renner	     start
  
********************************************************************/
#pragma warning(disable:4786)

#define WIN32_LEAN_AND_MEAN // To prevent conflict with ActiveMQ class decaf::lang::Thread and defines in winspool.h
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <memory.h>

#include "emstypes.h"
#include "emserror.h"
#include "emstime.h"
#include "emsconst.h"
#include "emscoord.h"
#include "emsvectr.h"
#include "emsrange.h"
#include "emsaltit.h"
#include "emsfract.h"
#include "emstle.h"
#include "Locate.h"
#include "dal.h"
#include "WLSxyzTypes406.h"
#include "wlsxyz406.h"
//#include "locnserv406.h"
#include "locnmsgs.h"
#include "emshexgrid.h"
#include "emsoutlier.h"

#include "emsencod.h"
#include "EMSCLOCK.H"

//extern  LPEMSFract	  m_lpFract;
//extern  LPEMSAltit	  m_lpAltit;

const double c_dInitialCovariance[] = {1,0,0,0,1,0,0,1,0,1}; 
const int   c_nMinBiasPoints  = 3;
//const int	c_nMinimumNumPtsVisible = 2;   // allow for FDOA 2 point solutions

const int	c_nIterationsMax = 500;
const int	c_nIterationsMin = 10;
const int	c_nMaxOscillations = 8;
const int	c_nMinAcceptPointCount = 10;
const double c_dMaxPassMinutes = 20.0; // max expected minutes in a single pass
const double c_dMaxEECorrelation = 0.99;
const double c_dDeltaSecondsIfUnique	= 1.0;

const double c_dPointCountThreshold = 0.9; // allow a maximum of 10% of data to be outliers
const CEMSSystemClock c_sysClock;
const ULONG c_ulGEOSatID = 200;	// minimum Salellite ID used for GEO satellites 
const ULONG c_ulMEOSatID = 300;	// minimum Salellite ID used for MEO satellites 


BOOL  bAddIonos = FALSE;

//***********************************************************************************************

CEMSWLSxyz406::CEMSWLSxyz406()
{
	m_lplpTracerFile = 0;
	m_lpTracingLevel = 0;
	m_lpException = 0;

	m_dFreqWeight = 0.1;
	m_dTimeWeight = 5400.0;
	m_wProcessDataType = PROCESS_TDOA + PROCESS_FDOA + PROCESS_FREQ;
}

CEMSWLSxyz406::~CEMSWLSxyz406()
{ 	
	Reset( );
}

void CEMSWLSxyz406::Reset( void )
{
}


//***********************************************************************************************

int CEMSWLSxyz406::_GenerateSolutionIndex ( EMSWLSCONTROL *lpControl )
{
	int		nNumVariables;

	nNumVariables = 3;

	if ( lpControl )
	{


		if ( lpControl->iVariableFlag & PROCESS_FBIAS )
		{
			nNumVariables++;
		}

		if ( lpControl->iVariableFlag & PROCESS_TBIAS )
		{
			nNumVariables++;
		}

	}

	return nNumVariables;
}

//***********************************************************************************************

HRESULT CEMSWLSxyz406::SetDefaultControlValues( EMSWLSCONTROL *lpControl )
{
	HRESULT hr = EMS_OK;

	if ( lpControl )
	{
		memset( lpControl, 0, sizeof( EMSWLSCONTROL ) );

		lpControl->iVariableFlag   = PROCESS_FBIAS + PROCESS_TBIAS;

		_GenerateSolutionIndex ( lpControl );
		           
		lpControl->wProcessDataType = PROCESS_TDOA+PROCESS_FDOA+PROCESS_FREQ;
		
		lpControl->dCal406DurInHours = 24.0;
		lpControl->iCal406MeasMax    = 4096;
		lpControl->iCal406MeasMin    = 128;

		lpControl->iIterationsMax  = c_nIterationsMax;
		lpControl->iIterationsMin  = c_nIterationsMin;
		lpControl->iMinBiasPoints  = c_nMinBiasPoints;
		lpControl->dMaxFreqNoise   = 2.0;
		lpControl->dMaxTimeNoise   = 0.1;
		lpControl->ulMinPtsVisible = 3;

		lpControl->dFbias  = 0.0;	// initial estimate of frequency bias
		lpControl->dTbias  = 0.0;	// initial estimate of time bias

		lpControl->dXYZMax = 10.0;	// maximum change in XYZ coordinates
		lpControl->dFbiasMax = 2500.0;	// maximum change in frequency bias
		lpControl->dTbiasMax = 0.1;	// maximum change in time bias

		lpControl->dXYZMin = 0.01;	// minimum change in XYZ coordinates
		lpControl->dFbiasMin = 0.1;	// minimum change in frequency bias
		lpControl->dTbiasMin = 0.00001;	// minimum change in time bias

		lpControl->dResidThresholdMin = 5.0; // minimum allowed residual threshold(Hz)
		lpControl->dStdDevMax         = 2.0; // maximum number of standard deviations allowed for residual

		lpControl->dMinCovStdDev      = 1.0; // minimum covariance residual noise (Hz)

		lpControl->dNomErrorEllipseScaleFactor = 1.65; // Nominal Multiplier of error ellipse
		lpControl->dNomErrorEllipseOrbitError  = 0.75; // Nominal Orbit error to be included in error ellipse (km)
		lpControl->dMarErrorEllipseScaleFactor = 1.65; // Marginal Multiplier of error ellipse
		lpControl->dMarErrorEllipseOrbitError  = 0.75; // Marginal Orbit error to be included in error ellipse (km)

		lpControl->dFreqWeight  = 0.1; // Frequency Measurement weight factor
		lpControl->dTimeWeight  = 5400.0; // Time Measurement weight factor (conversion to msec)

		lpControl->bOutputEncoded = false;
		lpControl->bSingleBurstOnly = false;
		lpControl->bRefBeaconOption = false;

		lpControl->dMEOTimeOffset = 0.0;
		lpControl->dGEOTimeOffset = 0.0;

		memset(lpControl->iRemoveSAT, 0, 10 );
		memset(lpControl->iRemoveLUT, 0, 10 );


	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

//***********************************************************************************************

HRESULT CEMSWLSxyz406::SetInitialSolution( EMSWLSLOCATE *lpSolution, double dLatitude, double dLongitude )
{
	HRESULT hr = EMS_OK;

	if ( lpSolution )
	{
		memset( lpSolution, 0, sizeof( EMSWLSLOCATE ) );

		for ( int i = 0; i < EMS_LOCATE_COVARMATRIX_LENGTH; i++ ) 
			lpSolution->fCoVarianceMatrix[i] = (float) c_dInitialCovariance[i];
	
		lpSolution->dFrequency			= 0.0;
		lpSolution->fFreqBiasError		= 0;
		lpSolution->fFreqDrift			= 0;
		lpSolution->fHeading			= 0;
		lpSolution->fMajorError			= 0;
		lpSolution->fMinorError			= 0;
		lpSolution->fRadiusErrEllipse	= 0;
		lpSolution->fRMS				= 0;
		lpSolution->fTrend				= 0;
		lpSolution->location.degLatitude  = dLatitude;
		lpSolution->location.degLongitude = dLongitude;
		lpSolution->location.fAltitude	= 0.0;
		lpSolution->wNumIterations		= 0;
		lpSolution->wNumMsgs			= 0;
		lpSolution->wNumMsgsUsed		= 0;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

//***********************************************************************************************

int CEMSWLSxyz406::_ProcessTimeFlags ( EMSWLSCONTROL *lpControl, LPEMSCALIB406DATAEXT lpDATA,
							   int nPts, double dMean, double dStdDev, int nMinThresholdPts )
{
	
	// Set process flags
	int nPtsUsed = 0, nPtsRem = 0, nPtsAboveThreshold = 0;
	double dResidThreshold;

	double dTestResidual = 0.0, dMaxResidual1 = 0.0, dMaxResidual2 = 0.0;
	int nIndexMaxResidual1 = -1, nIndexMaxResidual2 = -1; 

	//dResidThreshold = max (lpControl->dResidThresholdMin, lpControl->dStdDevMax * (dStdDev));
	dResidThreshold = max (0.0001, lpControl->dStdDevMax * (dStdDev));

	for ( int i = 0; i < nPts; i ++ )
	{
		// Check if rejection flag is set 
		if ( !_TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
		{
			_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
		}
		else
		{
			_SetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );


			// Test residuals
			dTestResidual = fabs( lpDATA[i].extras.dTimeResidual - dMean );

			if ( dTestResidual > dResidThreshold )
			{
				if ( (nPts - nPtsRem) > nMinThresholdPts )
				{
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
					nPtsRem++;
				}
			}
			else
			{

				nPtsUsed++;		
					
				if ( dTestResidual > dMaxResidual2 ) // MaxResidual2 is always the smaller of the two
				{
					if ( dTestResidual > dMaxResidual1 )
					{
						dMaxResidual2 = dMaxResidual1;

						nIndexMaxResidual2 = nIndexMaxResidual1;

						dMaxResidual1 = dTestResidual;

						nIndexMaxResidual1 = i;
					}
					else
					{
				
						dMaxResidual2 = dTestResidual;

						nIndexMaxResidual2 = i;

					}	// max threshold 1 test
				}		// max threshold 2 test
			}			// all threshold test

		}				// end of reject test

	}					// end of nPts loop

/*
	// Special 406 test for up to 2 bad measurements
	if ( nPtsUsed > nMinThresholdPts )
	{
		if ( (dMaxResidual1 > lpControl->dResidThresholdMin) && _TestFlag( &lpDATA[nIndexMaxResidual1], EMS_C406PF_PROCESS_FREQ_FLAG ) )
		{
			_ResetFlag( &lpDATA[nIndexMaxResidual1], EMS_C406PF_PROCESS_TIME_FLAG );
			nPtsUsed--;
		}
	}
	if ( nPtsUsed > nMinThresholdPts )
	{
		if ( (dMaxResidual2 > lpControl->dResidThresholdMin) && _TestFlag( &lpDATA[nIndexMaxResidual2], EMS_C406PF_PROCESS_FREQ_FLAG ) )
		{
			_ResetFlag( &lpDATA[nIndexMaxResidual2], EMS_C406PF_PROCESS_TIME_FLAG );
			nPtsUsed--;
		}
	}
*/	
	return nPtsUsed;
}

//***********************************************************************************************

int CEMSWLSxyz406::_ProcessFreqFlags ( EMSWLSCONTROL *lpControl, LPEMSCALIB406DATAEXT lpDATA,
							   int nPts, double dMean, double dStdDev, int nMinThresholdPts )
{
	
	// Set process flags
	int nPtsUsed = 0, nPtsRem = 0, nPtsAboveThreshold = 0;
	double dResidThreshold;

	double dTestFreqResidual = 0.0, dMaxResidual1 = 0.0, dMaxResidual2 = 0.0;
	int nIndexMaxResidual1 = -1, nIndexMaxResidual2 = -1; 

	dResidThreshold = max (lpControl->dResidThresholdMin, lpControl->dStdDevMax * (dStdDev));

	for ( int i = 0; i < nPts; i ++ )
	{

		// Check if rejection flag is set 
		if ( !_TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
		{
		 	_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
		}
		else
		{		
			// Assumes all points are to be used until otherwise proven
			_SetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );

			dTestFreqResidual = fabs( lpDATA[i].extras.dFreqResidual - dMean );

			if ( dTestFreqResidual > dResidThreshold )
			{
				if ( (nPts - nPtsRem) > nMinThresholdPts )
				{
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
					nPtsRem++;
				}
			}
			else
			{

				nPtsUsed++;		
					
				if ( dTestFreqResidual > dMaxResidual2 ) // MaxResidual2 is always the smaller of the two
				{
					if ( dTestFreqResidual > dMaxResidual1 )
					{
						dMaxResidual2 = dMaxResidual1;

						nIndexMaxResidual2 = nIndexMaxResidual1;

						dMaxResidual1 = dTestFreqResidual;

						nIndexMaxResidual1 = i;
					}
					else
					{
				
						dMaxResidual2 = dTestFreqResidual;

						nIndexMaxResidual2 = i;

					}	// max threshold 1 test
				}		// max threshold 2 test
			}			// all threshold test

		}
	}				// end of nPts loop


	// Special 406 test for up to 2 bad measurements
	if ( nPtsUsed > nMinThresholdPts )
	{
		if ( (dMaxResidual1 > lpControl->dResidThresholdMin) && _TestFlag( &lpDATA[nIndexMaxResidual1], EMS_C406PF_PROCESS_FREQ_FLAG ) )
		{
			_ResetFlag( &lpDATA[nIndexMaxResidual1], EMS_C406PF_PROCESS_FREQ_FLAG );
			nPtsUsed--;
		}
	}
	if ( nPtsUsed > nMinThresholdPts )
	{
		if ( (dMaxResidual2 > lpControl->dResidThresholdMin) && _TestFlag( &lpDATA[nIndexMaxResidual2], EMS_C406PF_PROCESS_FREQ_FLAG ) )
		{
			_ResetFlag( &lpDATA[nIndexMaxResidual2], EMS_C406PF_PROCESS_FREQ_FLAG );
			nPtsUsed--;
		}
	}
	
	return nPtsUsed;
}

//***********************************************************************************************

int CEMSWLSxyz406::_SummaryStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,  
					double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend )
{
	int nPtsUsed	= 0;

	double dRMS		= 0.0;
	double dMean	= 0.0;
	double dStdDev	= -1.0;
	double dTrend	= 0.0;
	double dResidual = 0.0;

	if (nPts > 0 )
	{
		double dLastTimeResidual = 0.0;
		double dLastFreqResidual = 0.0;

		for ( int i = 0; i < nPts; i++ )
		{
			// ProcessFreqFlag checking
			if ( ( iOption && _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG ) ) || !iOption )
			{
				nPtsUsed ++;
				dResidual	 = lpDATA[i].extras.dFreqResidual; 
				dMean		+= dResidual;
				dRMS		+= dResidual * dResidual;

				dTrend += dResidual * dLastFreqResidual;

				dLastFreqResidual = dResidual;
			}

			// ProcessTimeFlag checking
			if ( ( iOption && _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG ) ) || !iOption )
			{
				nPtsUsed ++;
				dResidual	 = lpDATA[i].extras.dTimeResidual; 
				dMean		+= dResidual;
				dRMS		+= dResidual * dResidual;

				dTrend += dResidual * dLastTimeResidual;

				dLastTimeResidual = dResidual;
			}
		}
	}
	if ( nPtsUsed > 0 )
	{
		dMean   = dMean / nPtsUsed;
		dStdDev = sqrt( fabs( dRMS / nPtsUsed - dMean * dMean ) );
		dRMS    = sqrt( dRMS / nPtsUsed );
		dTrend  = sqrt( fabs( dTrend ) / nPtsUsed );
	}

	*pdRMS    = dRMS;
	*pdMean   = dMean;
	*pdStdDev = dStdDev;
	*pdTrend  = dTrend;

	return nPtsUsed;
}

//***********************************************************************************************

int CEMSWLSxyz406::_SummaryFreqStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,  
					double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend )
{
	int nPtsUsed	= 0;

	double dRMS		= 0.0;
	double dMean	= 0.0;
	double dStdDev	= -1.0;
	double dTrend	= 0.0;
	double dResidual = 0.0;

	if (nPts > 0 )
	{
		double dLastResidual = 0.0;

		for ( int i = 0; i < nPts; i++ )
		{
			// ProcessFlag checking
			if ( ( iOption && _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG ) ) || !iOption )
			{
				nPtsUsed ++;
				dResidual	 = lpDATA[i].extras.dFreqResidual; 
				dMean		+= dResidual;
				dRMS		+= dResidual * dResidual;

				dTrend += dResidual * dLastResidual;

				dLastResidual = dResidual;
			}
		}
	}
	if ( nPtsUsed > 0 )
	{
		dMean   = dMean / nPtsUsed;
		dStdDev = sqrt( fabs( dRMS / nPtsUsed - dMean * dMean ) );
		dRMS    = sqrt( dRMS / nPtsUsed );
		dTrend  = sqrt( fabs( dTrend ) / nPtsUsed );
	}

	*pdRMS    = dRMS;
	*pdMean   = dMean;
	*pdStdDev = dStdDev;
	*pdTrend  = dTrend;

	return nPtsUsed;
}

//***********************************************************************************************


int CEMSWLSxyz406::_SummaryTimeStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,  
					double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend )
{
	int nPtsUsed	= 0;

	double dRMS		= 0.0;
	double dMean	= 0.0;
	double dStdDev	= -1.0;
	double dTrend	= 0.0;
	double dResidual = 0.0;

	if (nPts > 0 )
	{
		double dLastResidual = 0.0;

		for ( int i = 0; i < nPts; i++ )
		{
			// Check if data accepted for processing
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
			{
				// ProcessFlag checking
				if ( ( iOption && _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG ) ) || !iOption )
				{
					nPtsUsed ++;
					dResidual	 = lpDATA[i].extras.dTimeResidual; 
					//dMean		+= dResidual;
					dRMS		+= dResidual * dResidual;

					dTrend += dResidual * dLastResidual;

					dLastResidual = dResidual;
				}
			}
		}
	}
	if ( nPtsUsed > 0 )
	{
		dMean   = dMean / nPtsUsed;
		dStdDev = sqrt( fabs( dRMS / nPtsUsed - dMean * dMean ) );
		dRMS    = sqrt( dRMS / nPtsUsed );
		dTrend  = sqrt( fabs( dTrend ) / nPtsUsed );
	}

	*pdRMS    = dRMS;
	*pdMean   = dMean;
	*pdStdDev = dStdDev;
	*pdTrend  = dTrend;

	return nPtsUsed;
}

//***********************************************************************************************
int CEMSWLSxyz406::_FindCentralPoint( LPEMSCALIB406DATAEXT lpDATA, int nPts, int nStartIndex,
								EMSLOCATION locEstimate, DWORD dwFlags )
{
	int nIndex = nStartIndex, nCentralIndex = nStartIndex;

	if ( lpDATA && (nIndex < nPts ) )
	{
		int nBurstNumber =  lpDATA[nIndex++].extras.wBurstNumber;
		double dMaxElevationAngle = 0.0, dElevationAngle = 0.0;
		CEMSCoordSystem coordSys;

		while (( nIndex < nPts ) && ( nBurstNumber == lpDATA[nIndex].extras.wBurstNumber ) )
		{
			if ( _TestFlag( &lpDATA[nIndex], dwFlags ) )
			{
				// calc dElevationAngle
				EMSAZELVECTORD azel = coordSys.ToAzimuthAndElevation( lpDATA[nIndex].extras.SatTPVC, locEstimate );

				if ( azel.azel.degElevation > dMaxElevationAngle )
				{
					nCentralIndex = nIndex;
					dMaxElevationAngle = azel.azel.degElevation;
				}
			}
			nIndex++;
		}
	}

	

	return nCentralIndex;
	//return nStartIndex;
}

//******************************************************************************************************

int CEMSWLSxyz406::_WLSxyzfill( EMSWLSCONTROL *lpControl, EMSVECTORD vBEACON, LPEMSCALIB406DATAEXT lpDATA, 
								int nPts, int nBursts, double *dB, double dA[MAXVARIABLES][MAXVARIABLES] )
								
{	
	int i; // indices

	// If a Doppler only measurement is accepted then add FBias to state vector 

	int nNumVariables	= 5;

	double dResidualF1 = 0.0; 
	double dResidualT1 = 0.0;; 
	double dResidual   = 0.0;
	
	double dFOAdx, dFOAdy, dFOAdz, dTOAdx, dTOAdy, dTOAdz;
	double dFOAdf, dTOAdt;
//	double dFOAdx2, dFOAdy2, dFOAdz2, dTOAdx2, dTOAdy2, dTOAdz2;

	double dFOAdx1 = 0.0;
	double dFOAdy1 = 0.0;
	double dFOAdz1 = 0.0;
	double dTOAdx1 = 0.0;
	double dTOAdy1 = 0.0;
	double dTOAdz1 = 0.0;

	double dALTdx, dALTdy, dALTdz;
	double dR, dRE, dRP, dREP, dRPE;

	EMSRANGERATED RRate;
	//EMSRANGERATED xRRate, yRRate, zRRate;
	EMSVECTORD  vSATP, vSATV;


	// Temporary setting for inverse weights
	double dFreqWeight = 1.0;
	double dTimeWeight = 5400.0;

	if ( lpControl->dFreqWeight > 0 )
		dFreqWeight = lpControl->dFreqWeight;
	if ( lpControl->dTimeWeight > 0 )
		dTimeWeight = lpControl->dTimeWeight;


	memset( dB, 0, MAXVARIABLES * sizeof(double));
	memset( dA, 0, MAXVARIABLES * MAXVARIABLES * sizeof(double));


	int wBurstNumber = -1;

	if ( nBursts > 1 )
	{
		nNumVariables = 4; //  Multiple burst processing 
	}

	int nTimeCentralIdx = 0, nFreqCentralIdx = 0;

	double FOAfactor = dFreqWeight * 406.025e6 / c_dVelocityOfLight;
	double TOAfactor = dTimeWeight / c_dVelocityOfLight;
	bool   bProcessed;

	for (i = 0; i < nPts; i++)
	{
		
		bProcessed = false;
		
		CEMSRangeRate::Calculate( vBEACON, &lpDATA[i].extras.SatTPVC, 1, &RRate );

		//vBEACON.dX +=1.0;
		//CEMSRangeRate::Calculate( vBEACON, &lpDATA[i].extras.SatTPVC, 1, &xRRate );
		//vBEACON.dX -=1.0;
		
		//vBEACON.dY +=1.0;
		//CEMSRangeRate::Calculate( vBEACON, &lpDATA[i].extras.SatTPVC, 1, &yRRate );
		//vBEACON.dY -=1.0;
		
		//vBEACON.dZ +=1.0;
		//CEMSRangeRate::Calculate( vBEACON, &lpDATA[i].extras.SatTPVC, 1, &zRRate );
		//vBEACON.dZ -=1.0;
		
		vSATP = lpDATA[i].extras.SatTPVC.coord.radius;
		vSATV = lpDATA[i].extras.SatTPVC.coord.velocity;

		if ( _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG )  && 
			 _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG ))
		{

			dResidual = lpDATA[i].extras.dFreqResidual;

			dFOAdx = ( vSATV.dX + vSATP.dY*c_radEarthRotationRate + (vSATP.dX - vBEACON.dX) * RRate.dRangeRate / RRate.dRange ) / RRate.dRange;
			dFOAdy = ( vSATV.dY - vSATP.dX*c_radEarthRotationRate + (vSATP.dY - vBEACON.dY) * RRate.dRangeRate / RRate.dRange ) / RRate.dRange;
			//dFOAdx = ( vSATV.dX + (vSATP.dX - vBEACON.dX) * RRate.dRangeRate / RRate.dRange ) / RRate.dRange;
			//dFOAdy = ( vSATV.dY + (vSATP.dY - vBEACON.dY) * RRate.dRangeRate / RRate.dRange ) / RRate.dRange;
			dFOAdz = ( vSATV.dZ + (vSATP.dZ - vBEACON.dZ) * RRate.dRangeRate / RRate.dRange ) / RRate.dRange;

			//dFOAdx2 = RRate.dRangeRate - xRRate.dRangeRate;
			//dFOAdy2 = RRate.dRangeRate - yRRate.dRangeRate;
			//dFOAdz2 = RRate.dRangeRate - zRRate.dRangeRate;

			dFOAdx *= FOAfactor;
			dFOAdy *= FOAfactor;
			dFOAdz *= FOAfactor;
			dFOAdf  = 1.0;

			//if ( nBursts > 1 )
			//{
			//	if ( lpDATA[i].extras.wBurstNumber > wBurstNumber )
			//	{

			//		dResidualF1 = dResidual;
			//		dFOAdx1		= dFOAdx;
			//		dFOAdy1		= dFOAdy;
			//		dFOAdz1		= dFOAdz;

			//		dResidual   = 0.0;
			//		dFOAdx		= 0.0;
			//		dFOAdy		= 0.0;
			//		dFOAdz		= 0.0;
			//		dFOAdf      = 0.0;
			//		
			//	}
			//	else
			//	{
			//		dResidual   -= dResidualF1;
			//		dFOAdx		-= dFOAdx1;
			//		dFOAdy		-= dFOAdy1;
			//		dFOAdz		-= dFOAdz1;
			//		dFOAdf       = 0.0;
			//	}
			//}

			
			dB[0] += dResidual * dFOAdx;
			dB[1] += dResidual * dFOAdy;
			dB[2] += dResidual * dFOAdz;
			dB[3] += dResidual * dFOAdf;

			dA[0][0] += dFOAdx * dFOAdx;
			dA[0][1] += dFOAdx * dFOAdy;
			dA[0][2] += dFOAdx * dFOAdz;
			dA[0][3] += dFOAdx * dFOAdf;
			
			dA[1][1] += dFOAdy * dFOAdy;
			dA[1][2] += dFOAdy * dFOAdz;
			dA[1][3] += dFOAdy * dFOAdf;

			dA[2][2] += dFOAdz * dFOAdz;
			dA[2][3] += dFOAdz * dFOAdf;

			dA[3][3] += dFOAdf;

			bProcessed = true;


		}

		if ( _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG )	&& 
			 _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
		{
			
			dResidual      = lpDATA[i].extras.dTimeResidual;

			//dTOAdx = TOAfactor * vBEACON.dX / RRate.dRange;
			//dTOAdy = TOAfactor * vBEACON.dY / RRate.dRange;
			//dTOAdz = TOAfactor * vBEACON.dZ / RRate.dRange;
			dTOAdx = TOAfactor * (vSATP.dX - vBEACON.dX) / RRate.dRange;
			dTOAdy = TOAfactor * (vSATP.dY - vBEACON.dY) / RRate.dRange;
			dTOAdz = TOAfactor * (vSATP.dZ - vBEACON.dZ) / RRate.dRange;
			dTOAdt = 1.0;
			
			//dTOAdx2 = TOAfactor * ( RRate.dRange - xRRate.dRange );
			//dTOAdy2 = TOAfactor * ( RRate.dRange - yRRate.dRange );
			//dTOAdz2 = TOAfactor * ( RRate.dRange - zRRate.dRange );

			if ( nBursts > 1 )
			{
				if ( lpDATA[i].extras.wBurstNumber > wBurstNumber )
				{

					dResidualT1 = dResidual;
					dTOAdx1		= dTOAdx;
					dTOAdy1		= dTOAdy;
					dTOAdz1		= dTOAdz;

					dResidual   = 0.0;
					dTOAdx		= 0.0;
					dTOAdy		= 0.0;
					dTOAdz		= 0.0;
					dTOAdt		= 0.0;
					
				}
				else
				{
					dResidual   -= dResidualT1;
					dTOAdx		-= dTOAdx1;
					dTOAdy		-= dTOAdy1;
					dTOAdz		-= dTOAdz1;
					dTOAdt		 = 0.0;
				}
			}

			dB[0] += dResidual * dTOAdx;
			dB[1] += dResidual * dTOAdy;
			dB[2] += dResidual * dTOAdz;
			dB[4] += dResidual * dTOAdt;

			dA[0][0] += dTOAdx * dTOAdx;
			dA[0][1] += dTOAdx * dTOAdy;
			dA[0][2] += dTOAdx * dTOAdz;
			dA[0][4] += dTOAdx * dTOAdt;
			
			dA[1][1] += dTOAdy * dTOAdy;
			dA[1][2] += dTOAdy * dTOAdz;
			dA[1][4] += dTOAdy * dTOAdt;

			dA[2][2] += dTOAdz * dTOAdz;
			dA[2][4] += dTOAdz * dTOAdt;

			dA[4][4] += dTOAdt;

			bProcessed = true;


		}
		
		if ( bProcessed ) wBurstNumber = lpDATA[i].extras.wBurstNumber;
	}		

	// If altitude not required
	if( ! (lpControl->iVariableFlag & PROCESS_ALTITUDE) )
	{
		
		dRE = c_dEarthKmRadius; // equatorial radius
		dRP = c_dEarthKmRadius * ( 1.0 - c_dEarthFlatteningTerm ); // polar radius
		dRPE = dRP / dRE;
		dREP = dRE / dRP;

		dR = sqrt( dRPE * (vBEACON.dX * vBEACON.dX + vBEACON.dY * vBEACON.dY)
				 + dREP * (vBEACON.dZ * vBEACON.dZ) );
		dALTdx = 2.0 * dRPE * vBEACON.dX / dR;
		dALTdy = 2.0 * dRPE * vBEACON.dY / dR;
		dALTdz = 2.0 * dREP * vBEACON.dZ / dR;

		dResidual = - (dR - sqrt( dRE * dRP )); 
		dB[0] += dResidual * dALTdx;
		dB[1] += dResidual * dALTdy;
		dB[2] += dResidual * dALTdz;

		dA[0][0] += dALTdx * dALTdx;
		dA[0][1] += dALTdx * dALTdy;
		dA[0][2] += dALTdx * dALTdz;
		
		dA[1][1] += dALTdy * dALTdy;
		dA[1][2] += dALTdy * dALTdz;

		dA[2][2] += dALTdz * dALTdz;
	}

	// Create symmetric A matrix 
	dA[1][0] = dA[0][1];
	dA[2][0] = dA[0][2];
	dA[3][0] = dA[0][3];
	dA[4][0] = dA[0][4];
	dA[2][1] = dA[1][2];
	dA[3][1] = dA[1][3];
	dA[4][1] = dA[1][4];
	dA[3][2] = dA[2][3];
	dA[4][2] = dA[2][4];
	dA[4][3] = dA[3][4];


	if ( dA[4][4] == 0.0 ) nNumVariables = 4;
	if ( dA[3][3] == 0.0 ) nNumVariables = 3;

	return nNumVariables;
}

//***********************************************************************************************

HRESULT CEMSWLSxyz406::_UpdateSolutionErrors( LPEMSCALIB406DATAEXT lpDATA, int nPts, 
                                          EMSTCACTA *lpTcaCta, double dStdDev,
                                          double dA[MAXVARIABLES][MAXVARIABLES],
										  EMSWLSCONTROL *lpControl, LPEMSWLSLOCATE lpSOLN )
{
	HRESULT hr = EMS_OK;

	int i;
	int nNumVariables = 0;

	double dCOVARIANCE[ EMS_LOCATE_COVARMATRIX_LENGTH ];
	double dStdDev2;

	// Limit residual noise to 1 Hz
	if ( dStdDev < lpControl->dMinCovStdDev )
		dStdDev = lpControl->dMinCovStdDev;
	
	dStdDev2 = dStdDev * dStdDev;

	lpSOLN->fRadiusErrEllipse = 0.0; // Equivalent radius of error ellipse (km)
	lpSOLN->fMajorError       = 0.0; // Semi-major axis of error ellipse (km)
	lpSOLN->fMinorError       = 0.0; // Semi-minor axis of error ellipse (km)
	lpSOLN->fHeading          = 0.0; // Heading direction of error ellipse (deg +East from North)

	double ErrorAlpha    = 0.0;
	double ErrorBeta     = 0.0;
	double CorrAlphaBeta = 0.0;
	
	// Establish index numbers for solution variables
	nNumVariables =	_GenerateSolutionIndex ( lpControl );

	// Initialize upper triangle covariance matrix
	memset( dCOVARIANCE, 0, EMS_LOCATE_COVARMATRIX_LENGTH * sizeof(double));


	// Rotate XYZ covariance into lat/long coordinates
	
	double dLat  = lpSOLN->location.degLatitude;
	double dLong = lpSOLN->location.degLongitude;
	double dROT[3][3];

	double cLat, cLong, sLat, sLong;

	sLat  = sin( dLat * c_dDegToRad );
	cLat  = cos( dLat * c_dDegToRad );
	sLong = sin( dLong * c_dDegToRad );
	cLong = cos( dLong * c_dDegToRad );


    dROT[0][0] = dA[0][0] * cLong - dA[1][0] * sLong;
    dROT[0][1] = dA[0][1] * cLong - dA[1][1] * sLong;
	dROT[0][2] = dA[0][2] * cLong - dA[1][2] * sLong;
	dROT[1][0] = dA[0][0] * sLong + dA[1][0] * cLong;
	dROT[1][1] = dA[0][1] * sLong + dA[1][1] * cLong;
	dROT[1][2] = dA[0][2] * sLong + dA[1][2] * cLong;
	dROT[2][0] = dA[2][0];
	dROT[2][1] = dA[2][1];
	dROT[2][2] = dA[2][2];

	dA[0][0] = dROT[0][0];
	dA[0][1] = dROT[0][1];
	dA[0][2] = dROT[0][2];
    dA[1][0] = dROT[1][0] * cLat - dROT[2][0] * sLat;
    dA[1][1] = dROT[1][1] * cLat - dROT[2][1] * sLat;
	dA[1][2] = dROT[1][2] * cLat - dROT[2][2] * sLat;
	dA[2][0] = dROT[1][0] * sLat + dROT[2][0] * cLat;
	dA[2][1] = dROT[1][1] * sLat + dROT[2][1] * cLat;
	dA[2][2] = dROT[1][2] * sLat + dROT[2][2] * cLat;


	dCOVARIANCE[0] = dA[0][0];
	dCOVARIANCE[1] = dA[0][1];
	dCOVARIANCE[2] = dA[0][2];
	dCOVARIANCE[3] = dA[1][1];
	dCOVARIANCE[4] = dA[1][2];
	dCOVARIANCE[5] = dA[2][2];
	dCOVARIANCE[6] = dA[3][3];
	dCOVARIANCE[7] = dA[3][4];
	dCOVARIANCE[8] = dA[4][4];


	for ( i = 0; i < EMS_LOCATE_COVARMATRIX_LENGTH; i++ )
	{
		dCOVARIANCE[ i ] *= dStdDev2;
		lpSOLN->fCoVarianceMatrix[ i ] = (float) dCOVARIANCE[ i ];
	}

	lpSOLN->fFreqBiasError = (float) sqrt( fabs(dCOVARIANCE[ 6 ]) );

	ErrorAlpha = sqrt( fabs(dCOVARIANCE[ 0 ])  );
	ErrorBeta = sqrt( fabs(dCOVARIANCE[ 3 ])  );
	CorrAlphaBeta = dCOVARIANCE[ 1 ] / ErrorAlpha / ErrorBeta;

	// Convert from km to degrees
	ErrorAlpha /= (c_dDegToRad * c_dEarthKmRadius);
	ErrorBeta  /= (c_dDegToRad * c_dEarthKmRadius);

	// Limit correlation coefficient to range less than 1
	if ( CorrAlphaBeta > c_dMaxEECorrelation ) 
		CorrAlphaBeta = c_dMaxEECorrelation;
	if ( CorrAlphaBeta < -c_dMaxEECorrelation ) 
		CorrAlphaBeta = -c_dMaxEECorrelation;

	// rotate error ellipse
    lpSOLN->fHeading = (float) (0.5 * ATAN2D(2.0*ErrorAlpha*ErrorBeta*CorrAlphaBeta,
								ErrorAlpha*ErrorAlpha - ErrorBeta*ErrorBeta) );

	double sh  = SIND (lpSOLN->fHeading);
	double ch  = COSD (lpSOLN->fHeading);
	double vn  = (ErrorAlpha * c_dEarthKmRadius * c_dDegToRad );
	double ve  = (ErrorBeta  * c_dEarthKmRadius * c_dDegToRad );
	double cen = CorrAlphaBeta;

    double dNomCtaMin    = 1.0;    // deg
    double dNomCtaMax    = 20.0;   // deg
    int    nNom406PtsMin = 4;
    bool   bNom          = TRUE;

    bNom = (fabs( lpTcaCta->cta ) >= dNomCtaMin)    &&
           (fabs( lpTcaCta->cta ) <= dNomCtaMax)    &&
           (lpTcaCta->tca.intTime >= lpDATA[0].calib406.timeMsg.intTime) &&
           (lpTcaCta->tca.intTime <= lpDATA[nPts-1].calib406.timeMsg.intTime);
    bNom = bNom && (lpSOLN->wNumMsgsUsed >= nNom406PtsMin);

    double dOrbitError  = bNom ? lpControl->dNomErrorEllipseOrbitError  : lpControl->dMarErrorEllipseOrbitError;
    double dScaleFactor = bNom ? lpControl->dNomErrorEllipseScaleFactor : lpControl->dMarErrorEllipseScaleFactor;

	double orberr = dOrbitError * dOrbitError; // Orbit error to be included in error ellipse (km)

    lpSOLN->fMajorError  = (float) sqrt( fabs ((vn*ch)*(vn*ch) + (ve*sh)*(ve*sh) + 2.0*ve*vn*cen*sh*ch));
    lpSOLN->fMinorError  = (float) sqrt( fabs ((ve*ch)*(ve*ch) + (vn*sh)*(vn*sh) - 2.0*ve*vn*cen*sh*ch));
	lpSOLN->fMajorError *= (float) dScaleFactor;
	lpSOLN->fMinorError *= (float) dScaleFactor;

	// add orbit error term
    lpSOLN->fMajorError = (float) sqrt(lpSOLN->fMajorError * lpSOLN->fMajorError + orberr);
    lpSOLN->fMinorError = (float) sqrt(lpSOLN->fMinorError * lpSOLN->fMinorError + orberr);
    
	// swap major and minor axes if necessary
	if (lpSOLN->fMajorError < lpSOLN->fMinorError)
	{
		float ftemp = lpSOLN->fMajorError;
		lpSOLN->fMajorError = lpSOLN->fMinorError;
		lpSOLN->fMinorError = ftemp;
        lpSOLN->fHeading -= 90.0;
	}
    
	// adjust range of heading angle 
	if (lpSOLN->fHeading > 90.0) lpSOLN->fHeading -= 180.0;

	lpSOLN->fRadiusErrEllipse = (float) sqrt (lpSOLN->fMajorError*lpSOLN->fMajorError
		                             + lpSOLN->fMinorError*lpSOLN->fMinorError);

	return hr;
}

//***********************************************************************************************

int	CEMSWLSxyz406::_UniqueCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag )
{
	// Assumes (1) data in time order
	// and (2) burst times must be different by more than one second

	// Addition of uniqueness based upon SatID

	int nUniqueNumberUsed = 0;

	if ( lpDATA && nPts )
	{

		INT64 i64MinBurstInterval = 2000000000; // allowance of a minimum of 2 seconds separation


		INT64 i64LastTime = lpDATA[0].calib406.timeMsg.intTime - i64MinBurstInterval;

		ULONG ulLastSatID = 0;

		// Count unique FOA measurements
		for ( int j = 0; j < nPts; j ++ )
		{

			if ( !bUsedFlag || _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_MASK ) )
			{
				if ( ( lpDATA[j].calib406.timeMsg.intTime > i64LastTime ) ||
					( lpDATA[j].calib406.hdr.id.ulSatID != ulLastSatID ) )
					nUniqueNumberUsed++;
			
				ulLastSatID = lpDATA[j].calib406.hdr.id.ulSatID;

				i64LastTime = lpDATA[j].calib406.timeMsg.intTime + i64MinBurstInterval;

			}
		
		}

		i64LastTime = lpDATA[0].calib406.timeMsg.intTime - i64MinBurstInterval;

		// Count unique TOA measurements
		for ( int j = 0; j < nPts; j ++ )
		{

			if ( !bUsedFlag || _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_MASK ) )
			{
				if ( ( lpDATA[j].calib406.timeMsg.intTime < i64LastTime ) &&
					( lpDATA[j].calib406.hdr.id.ulSatID != ulLastSatID ) )
					nUniqueNumberUsed++;
			
				ulLastSatID = lpDATA[j].calib406.hdr.id.ulSatID;

				i64LastTime = lpDATA[j].calib406.timeMsg.intTime + i64MinBurstInterval;

			}
		
		}
	}
	
	return nUniqueNumberUsed;
}


//***********************************************************************************************

int	CEMSWLSxyz406::_BurstCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag )
{
	// Assumes (1) data in time order
	// and (2) burst times must be different by more than one second

	// Sets Burst Numbers

	int nNumBurstsUsed = 0;

	if ( lpDATA && nPts )
	{

		INT64 i64MinBurstInterval = 2000000000; // allowance of a minimum of 2 seconds separation


		INT64 i64LastTime = lpDATA[0].calib406.timeMsg.intTime - i64MinBurstInterval;

		for ( int j = 0; j < nPts; j ++ )
		{

			if ( !bUsedFlag || _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_MASK ) )
			{
				if ( lpDATA[j].calib406.timeMsg.intTime > i64LastTime )
					nNumBurstsUsed++;
			
				i64LastTime = lpDATA[j].calib406.timeMsg.intTime + i64MinBurstInterval;

			}
		
		}
	}
	

	return nNumBurstsUsed;
}

//***********************************************************************************************
	
int CEMSWLSxyz406::_ElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSLOCATION vLOC )
{
	CEMSCoordSystem	CS;

	EMSVECTORD SatVector, BeaVector;

	double dElevationAngle;

	double dMinElevationAngle = -5.0;

	int nPtsVisible = 0;

	BeaVector  = CS.ToEarthFixedDouble( vLOC );

	for ( int j = 0; j < nPts; j ++ )
	{
		if ( _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_MASK ) )
		{
			SatVector   = lpDATA[j].extras.SatTPVC.coord.radius;

			dElevationAngle = _ElevationAngle( SatVector, BeaVector );

			if  ( dElevationAngle > dMinElevationAngle )
				nPtsVisible++;
		}

	}
	return nPtsVisible;
}

//***********************************************************************************************
	
double CEMSWLSxyz406::_ElevationAngle( EMSVECTORD SatVector, EMSVECTORD BeaVector )
{
	EMSVECTORD DiffVector;

	double dBeaRadius, dDiffRadius, dElevation;

	double dCosAngle;

	dBeaRadius = sqrt( CEMSVector::DotProduct( BeaVector , BeaVector ) );

	DiffVector  = CEMSVector::Sub( SatVector, BeaVector );
			
	dDiffRadius = sqrt( CEMSVector::DotProduct( DiffVector , DiffVector ) );

	dCosAngle  = CEMSVector::DotProduct( BeaVector , DiffVector );
	dCosAngle /= ( dDiffRadius * dBeaRadius );

	dElevation = acos ( dCosAngle );
	dElevation *= c_dRadToDeg;
	dElevation = 90.0 - dElevation;;

	return dElevation;
}

//***********************************************************************************************

int CEMSWLSxyz406::_ProcessFlagElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSLOCATION vLOC )
{
	CEMSCoordSystem	CS;

	EMSVECTORD SatVector, BeaVector, DiffVector;

	double dBeaRadius, dDiffRadius;

	double dCosAngle;

	double dCosTest = cos( c_dDegToRad * 95.0 ); // Equivalent to elevation of -5 degrees

	int nPtsVisible = 0;

	BeaVector  = CS.ToEarthFixedDouble( vLOC );

	dBeaRadius = sqrt( CEMSVector::DotProduct( BeaVector , BeaVector ) );

	for ( int j = 0; j < nPts; j ++ )
	{

		// Count only those measurements that are flagged to be processed
		if ( _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_MASK ) )
		{
			SatVector   = lpDATA[j].extras.SatTPVC.coord.radius;

			DiffVector  = CEMSVector::Sub( SatVector, BeaVector );
			
			dDiffRadius = sqrt( CEMSVector::DotProduct( DiffVector , DiffVector ) );

			dCosAngle  = CEMSVector::DotProduct( BeaVector , DiffVector );
			dCosAngle /= ( dDiffRadius * dBeaRadius );

			// Reset process flags if not in view	
			if  ( dCosAngle > dCosTest )
			{
				// Count both frequency and time if process flag set
				if ( _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_FREQ_FLAG ) )
				{
					nPtsVisible++;
				}
				if ( _TestMask( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG ) )
				{
					nPtsVisible++;
				}
			}
			else
			{
				_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_FREQ_FLAG );
				_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG );
			}
		}
	}
	return nPtsVisible;
}

//***********************************************************************************************

HRESULT CEMSWLSxyz406::GetResiduals( EMSLOCATION vLOC, double dTxFrequency, LPEMSCALIB406DATAEXT lpDATA, int nPts ) 
{
	HRESULT hr = EMS_OK;

	if ( lpDATA )
	{

		EMSVECTORD vBeaconRadius;
		CEMSCoordSystem coordSys;

		vBeaconRadius = coordSys.ToEarthFixedDouble( vLOC ); 

		hr = _GetResiduals( vBeaconRadius, dTxFrequency, lpDATA, nPts );
	}
	return hr;
}

//***********************************************************************************************

HRESULT CEMSWLSxyz406::_GetResiduals( EMSVECTORD vBeaconRadius, double dTxFrequency, LPEMSCALIB406DATAEXT lpDATA, int nPts ) 
{
	HRESULT hr = EMS_OK;

	if ( lpDATA )
	{

		int		j;
		double  dRange, dRangeRate;
		double	dResid;

		WORD	wBurstNumber = 0;

		EMSVECTORD vDiffRadius, vDiffVelocity;
		EMSVECTORD vBeaconVelocity;

		CEMSCoordSystem coordSys;

		vBeaconVelocity = coordSys.EarthFixedVelocity( vBeaconRadius );

		WORD wMaxBursts = lpDATA[nPts-1].extras.wBurstNumber;
		
		double	*lpResidTimeSum = new double [ wMaxBursts + 1 ];
		double	*lpResidFreqSum = new double [ wMaxBursts + 1 ];

		int		*lpNtime = new int [ wMaxBursts + 1 ];
		int		*lpNfreq = new int [ wMaxBursts + 1 ];

		memset ( lpResidTimeSum, 0, (wMaxBursts+1) * sizeof( double ) );
		memset ( lpResidFreqSum, 0, (wMaxBursts+1) * sizeof( double ) );
		memset ( lpNtime, 0, (wMaxBursts+1) * sizeof( int ) );
		memset ( lpNfreq, 0, (wMaxBursts+1) * sizeof( int ) );

		for ( j = 0; j < nPts; j ++ )
		{
			wBurstNumber = lpDATA[j].extras.wBurstNumber;

			if ( wBurstNumber <= wMaxBursts && wBurstNumber >= 0 )
			{
				
				// Establish transmit frequency in each record
				lpDATA[j].extras.dTxFrequency = dTxFrequency;

				vDiffRadius   = CEMSVector::Sub( lpDATA[j].extras.SatTPVC.coord.radius , vBeaconRadius );
				vDiffVelocity = CEMSVector::Sub( lpDATA[j].extras.SatTPVC.coord.velocity , vBeaconVelocity );
				dRange        = sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );
				dRangeRate    = CEMSVector::DotProduct( vDiffRadius, vDiffVelocity ) / dRange;
				
				
				lpDATA[j].extras.dFreqResidual = 0.0;
				lpDATA[j].extras.dTimeResidual = 0.0;


				dResid  = (lpDATA[j].calib406.timeMsg.intTime) * 1e-9; 
				dResid -= (lpDATA[j].extras.timeTransmit.intTime) * 1e-9; 
				dResid -= (dRange / c_dVelocityOfLight);
				lpDATA[j].extras.dTimeResidual = dResid;// * 1e6;    // Microsec units

				dResid  = (lpDATA[j].calib406.dFrequency - lpDATA[j].extras.dTxFrequency); 
				dResid -= (-dRangeRate * lpDATA[j].extras.dTxFrequency / c_dVelocityOfLight); 
				lpDATA[j].extras.dFreqResidual = dResid;	// Hz units

				// Determine biases for valid data only
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_TIME_FLAG ) )
				{
					lpResidTimeSum[ wBurstNumber ] += lpDATA[j].extras.dTimeResidual;
					lpNtime[ wBurstNumber ]++;
				}
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
				{
					lpResidFreqSum[ wBurstNumber ] += lpDATA[j].extras.dFreqResidual;
					lpNfreq[ wBurstNumber ]++;
				}
			}


		}

		// Compute average residual per burst
		for ( j = 1; j <= wMaxBursts; j ++ )
		{
			if ( lpNtime[ j ] ) lpResidTimeSum[ j ] /= lpNtime[ j ];
			if ( lpNfreq[ j ] ) lpResidFreqSum[ j ] /= lpNfreq[ j ];
		}

		// Adjustment for bias removal
		for ( j = 0; j < nPts; j ++ )
		{
			wBurstNumber = lpDATA[j].extras.wBurstNumber;

			if ( wBurstNumber <= wMaxBursts && wBurstNumber >= 0 )
			{

				// TDOA data processing
				if ( lpNtime[ wBurstNumber ] > 1 )
				{
					if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_TIME_FLAG ) )
					{
						lpDATA[j].extras.dTimeResidual        -= lpResidTimeSum[ wBurstNumber ];
						lpDATA[j].extras.timeTransmit.intTime += (INT64) (lpResidTimeSum[ wBurstNumber ] * 1e9);
						
						// If used in determining transmit time then must be used in processing
						_SetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG ); 

						// Set TDOA flag
						_SetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TDOA_FLAG );
						
					}
				}
				else
				{
					// Reset time variables if only one measurement for a single burst
					_ResetFlag( &lpDATA[j], EMS_C406PF_ACCEPT_TIME_FLAG );
					_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG );
					
					// Reset TDOA flag
				  	_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TDOA_FLAG ); 
					
					lpDATA[j].extras.dTimeResidual        = 0.0;
					
					lpDATA[j].extras.timeTransmit.intTime = 0;
				}

				// FDOA data processing
				if ( lpNfreq[ wBurstNumber ] > 1 )
				{
					if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
					{
						lpDATA[j].extras.dFreqResidual -= lpResidFreqSum[ wBurstNumber ];
						lpDATA[j].extras.dTxFrequency  += lpResidFreqSum[ wBurstNumber ];
						
						// If used in determining transmit frequency then must be used in processing
						_SetFlag( &lpDATA[j], EMS_C406PF_PROCESS_FREQ_FLAG );
						
						// Set FDOA flag
						_SetFlag( &lpDATA[j], EMS_C406PF_PROCESS_FDOA_FLAG );

					}
				}
				else
				{
					// Reset FDOA flag
					_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_FDOA_FLAG );
				}
			}
		}
		

		// Delete memory allocations
		
		if ( lpResidTimeSum )
		{
			delete [] lpResidTimeSum;
			lpResidTimeSum = 0;
		}

		if ( lpResidFreqSum )
		{
			delete [] lpResidFreqSum;
			lpResidFreqSum = 0;
		}

		if ( lpNtime )
		{
			delete [] lpNtime;
			lpNtime = 0;
		}

		if ( lpNfreq )
		{
			delete [] lpNfreq;
			lpNfreq = 0;
		}

	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}
//***********************************************************************************************

int 
CEMSWLSxyz406::_RemoveBurstMaxResiduals( LPEMSCALIB406DATAEXT lpDATA, int nPts )
{
	int nRejectPts = 0;

	if ( lpDATA && nPts > 1 )
	{

		int		i, j;

		WORD	wBurstNumber = 0;
		WORD	wMaxBursts = lpDATA[nPts-1].extras.wBurstNumber;

		double	*lpResidTimeMax = new double [ wMaxBursts + 1 ];
		double	*lpResidFreqMax = new double [ wMaxBursts + 1 ];

		int		*lpNtimeMax = new int [ wMaxBursts + 1 ];
		int		*lpNfreqMax = new int [ wMaxBursts + 1 ];
		int		*lpNCount	= new int [ wMaxBursts + 1 ];

		memset ( lpResidTimeMax, 0, (wMaxBursts+1) * sizeof( double ) );
		memset ( lpResidFreqMax, 0, (wMaxBursts+1) * sizeof( double ) );
		memset ( lpNtimeMax, -1, (wMaxBursts+1) * sizeof( int ) );
		memset ( lpNfreqMax, -1, (wMaxBursts+1) * sizeof( int ) );
		memset ( lpNCount, 0, (wMaxBursts+1) * sizeof( int ) );

		for ( j = 0; j < nPts; j ++ )
		{
			wBurstNumber = lpDATA[j].extras.wBurstNumber;

			if ( wBurstNumber <= wMaxBursts && wBurstNumber >= 0 )
			{
				// Count number of detections in each burst
				lpNCount[ wBurstNumber ]++;

				// TDOA data processing
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_TIME_FLAG ) &&
					 _TestFlag( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG ) )
				{
					// Determine maximum time residual for burst
					if ( fabs( lpDATA[j].extras.dTimeResidual ) > lpResidTimeMax[ wBurstNumber ] )
					{
						lpResidTimeMax[ wBurstNumber ] = fabs( lpDATA[j].extras.dTimeResidual );
						lpNtimeMax[ wBurstNumber ] = j;
					}
				}

				// FDOA data processing
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_ACCEPT_FREQ_FLAG ) &&
					 _TestFlag( &lpDATA[j], EMS_C406PF_PROCESS_FREQ_FLAG ) )
				{
					// Determine maximum frequency residual for burst
					// Preference given to GEO satellite frequency which has neglegible impact on lat/long 
					bool bGEO = ( lpDATA[j].calib406.hdr.id.ulSatID < 300 ) && 
								( lpDATA[j].calib406.hdr.id.ulSatID > 200 );
					{
						if ( fabs( lpDATA[j].extras.dFreqResidual ) > lpResidFreqMax[ wBurstNumber ] || bGEO )
						{
							lpResidFreqMax[ wBurstNumber ] = fabs( lpDATA[j].extras.dFreqResidual );
							lpNfreqMax[ wBurstNumber ] = j;
						}
					}	
				}
			}
		}

		// Remove maximum residual records for bursts with multiple detections
		for ( i = 1; i <= wMaxBursts; i ++ )
		{
			if ( lpNCount[i] > 1 )
			{
				j =  lpNtimeMax[i];
				if ( j >= 0 && j < nPts )
				{
					_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_TDOA_FLAG );
					nRejectPts++;
				}

				j =  lpNfreqMax[i];
				if ( j >= 0 && j < nPts )
				{
					_ResetFlag( &lpDATA[j], EMS_C406PF_PROCESS_FDOA_FLAG );
					nRejectPts++;
				}
			}
		}

		if ( lpResidTimeMax )
		{
			delete [] lpResidTimeMax;
			lpResidTimeMax = 0;
		}

		if ( lpResidFreqMax )
		{
			delete [] lpResidFreqMax;
			lpResidFreqMax = 0;
		}

		if ( lpNtimeMax )
		{
			delete [] lpNtimeMax;
			lpNtimeMax = 0;
		}

		if ( lpNfreqMax )
		{
			delete [] lpNfreqMax;
			lpNfreqMax = 0;
		}

		if ( lpNCount )
		{
			delete [] lpNCount;
			lpNCount = 0;
		}

	}

	return nRejectPts;
}
	
//***********************************************************************************************

HRESULT CEMSWLSxyz406::_WLSLocation( char *pKind, LPEMSCALIB406DATAEXT lpDATA, int nPts, 
					EMSWLSCONTROL *lpControl, EMSWLSLOCATE *lpSolnIN, LPEMSWLSLOCATE lpsolnOUT ) 

{	
	HRESULT hr = EMS_OK;
	
	CEMSCoordSystem oCoord;
	
	EMSVECTORD vBEACON;
	EMSLOCATION geoBEACON;

	EMSWLSLOCATE solnBEST;

	int     i, n;
    int     nNumVariables;

	int		nPtsVisible = 0;
	int		nNumUniqueUsed = 0;
	int		nNumBurstsUsed = 0;

	double	dA[MAXVARIABLES][MAXVARIABLES];
	double	dB[MAXVARIABLES];

	double	dX[MAXVARIABLES];
	double	dXMax[MAXVARIABLES];
	double	dXMin[MAXVARIABLES];

	double	dXLast[MAXVARIABLES];  // used to test for oscillation 

	double	dMaxFact = 1.0, dScale = 1.0, damp = 1.0;
	double 	dRMS = 0 , dMean = 0, dStdDev = 0, dTrend = 0;
	double 	dFreqRMS = 0 , dFreqMean = 0, dFreqStdDev = 0, dFreqTrend = 0;
	double 	dTimeRMS = 0 , dTimeMean = 0, dTimeStdDev = 0, dTimeTrend = 0;

	double dR		= 100000.0;
	double dRlast	= 100000.0;
	double dDeterminant = 0.0;

	double dFreqStdDevBEST = 1000.0;
	double dTimeStdDevBEST = 1000.0;


	ULONG ulPassID = 0;
	bool bMultiPass = false;

	// Initialize output solution structure
	*lpsolnOUT  = *lpSolnIN;
	memcpy( &solnBEST, lpsolnOUT, sizeof(EMSWLSLOCATE) );
	solnBEST.wNumIterations = lpControl->iIterationsMax + 1;
	solnBEST.wNumIterations |= EMS_LOCATE_MAX_ITERATIONS_FLAG;

	vBEACON = oCoord.ToEarthFixedDouble( lpSolnIN->location );

	// Initialize convergence flag
	m_bConverged  = false;
	
	// Initialize FDOA data flag
	m_bFDOAdata  = false;

	memset( dA,     0, sizeof(dA));
    memset( dB,     0, sizeof(dB));
    memset( dX,     0, sizeof(dX));
	memset( dXLast, 0, sizeof(dXLast));
	
	for ( int i = 0; i < MAXVARIABLES; i++ )
	{
		dXMax[i] = 1000.0;
		dXMin[i] = 1.0;
	}
	//memset( dXMax,  1000.0, sizeof(dXMax));   // worst case for frequency estimation
	//memset( dXMin,  1.0, sizeof(dXMin));	// worst case for frequency estimation

	// initialize vectors

	nNumVariables = 5;
		
	dXMax[0] = lpControl->dXYZMax;
	dXMin[0] = lpControl->dXYZMin;
	dXMax[1] = lpControl->dXYZMax;
	dXMin[1] = lpControl->dXYZMin;
	dXMax[2] = lpControl->dXYZMax;
	dXMin[2] = lpControl->dXYZMin;
	dXMax[3] = lpControl->dFbiasMax;
	dXMin[3] = lpControl->dFbiasMin;
	dXMax[4] = lpControl->dTbiasMax;
	dXMin[4] = lpControl->dTbiasMin;


	// Remove selected Satellite and/or selected LUT data
	_CheckSATLUT( lpControl, lpDATA, nPts );  


	nNumUniqueUsed = _UniqueUsedCount( lpDATA, nPts );

	nNumBurstsUsed = _BurstUsedCount( lpDATA, nPts );

	if ( nNumUniqueUsed < nNumVariables  )
	{
		if ( lpsolnOUT )
		{
			lpsolnOUT->wNumMsgs     = lpSolnIN->wNumMsgs;		// Number of measurements 
			lpsolnOUT->wNumMsgsUsed = 0;
			lpsolnOUT->wNumBurstsUsed = nNumBurstsUsed;
			lpsolnOUT->wNumIterations |= EMS_LOCATE_MAX_ITERATIONS_FLAG;

			// Update average transmit frequency
			lpsolnOUT->dFrequency = MeanTxFrequency( lpDATA, nPts );

			m_bConverged = true;  // Assume processing is finished (too much data or not enough)

			for( n = 0; n < nPts; n++ )
			{
				_ResetFlag( &lpDATA[n], EMS_C406PF_PROCESS_TIME_FLAG );
				_ResetFlag( &lpDATA[n], EMS_C406PF_PROCESS_FREQ_FLAG );

			}
		}


		hr = EMS_LOCN_INSUFF_POINTS;
	}
	else
	{
		//-----------------------------------------------------------------------------------------
		// Main Loop
		//-----------------------------------------------------------------------------------------

		int		iIterations		= 0;
		int		nOscillations	= 0;
		int		nPtsUsed		= 0;
		int		nFreqPtsUsed	= 0;
		int		nTimePtsUsed	= 0;
		int		nPtsRemoved		= 0;

		int		iSolve			= 0;

		ULONG	ulTcaSatID		= 0;
		double  dAltitudeError;


		EMSTERRAINENUMTYPE  eTerrainType;
		EMSTCACTA			tcaCta;

		// minimum #pts allowed before thresholding   
		int		nMinThresholdPts = nNumVariables * 3;

		tcaCta.tca = lpDATA[nPts/2].calib406.timeMsg;

		ulTcaSatID = lpDATA[nPts/2].calib406.hdr.id.ulSatID;

		bAddIonos = FALSE;

		//************************************************************* Debug 
		if ( (m_lplpTracerFile &&  *m_lplpTracerFile) && (nPts > 1) &&
			 (m_lpTracingLevel && (*m_lpTracingLevel > 1)) )
		{
   			fprintf( *m_lplpTracerFile, "%s,BeaconID,LutID,SatID,PassID,",pKind);
			fprintf( *m_lplpTracerFile, "nIterations,nPts,nBurstUsed,nPtsUsed,");
			fprintf( *m_lplpTracerFile, "dFreqMean,dFreqStdDev,dTimeMean,dTimeStddev,");
			fprintf( *m_lplpTracerFile, "latitude,Longitude,Frequency,bMultiPass,");
			fprintf( *m_lplpTracerFile, "dX0,dX1,dX3,NumVariables,iSolve\n");
		}
		//*************************************************************/ Debug


		while (!m_bConverged  && (iIterations < lpControl->iIterationsMax))
		{

			// Add altitude corrections

			//if( m_lpAltit )
			//{
			//	m_lpAltit->LoadAltitudeData( &lpsolnOUT->location );
			//	m_lpAltit->GetLocationAltitudeInfo( &lpsolnOUT->location, 
			//			  &dAltitudeError, &eTerrainType );
			//	
			//	// Convert to XYZ coordinates
			//	vBEACON = oCoord.ToEarthFixedDouble( lpsolnOUT->location );
			//}

			
			// Check if partial derivatives identify single point solutions
			nNumVariables =	_GenerateSolutionIndex ( lpControl );


			
			// Compute summary statistics
			nFreqPtsUsed = _SummaryFreqStatistics( 1, lpDATA, nPts, &dFreqRMS, &dFreqMean, &dFreqStdDev, &dFreqTrend );
			
			nTimePtsUsed = _SummaryTimeStatistics( 1, lpDATA, nPts, &dTimeRMS, &dTimeMean, &dTimeStdDev, &dTimeTrend );

			nPtsUsed = nFreqPtsUsed + nTimePtsUsed;

			// Set process flags only if greater than minimum number of iterations
			if ( iIterations > lpControl->iIterationsMin )
			{
				nFreqPtsUsed = _ProcessFreqFlags( lpControl, lpDATA, nPts, dFreqMean, dFreqStdDev, nMinThresholdPts );

				nTimePtsUsed = _ProcessTimeFlags( lpControl, lpDATA, nPts, dTimeMean, dTimeStdDev, nMinThresholdPts );

				nPtsUsed     = _ProcessFlagElevationTest( lpDATA, nPts, lpsolnOUT->location );
			}

			bMultiPass = IsMultiPass( lpDATA, nPts, true );

			// Fill the A matrix and B vector
			nNumVariables = _WLSxyzfill( lpControl, vBEACON, lpDATA, nPts, nNumBurstsUsed, (double *) &dB, dA );

			dDeterminant = _DetNxN( dA, nNumVariables );

			if( fabs(dDeterminant) < 1.0e-6 )
			{
				for( i = 0; i < nNumVariables; i++)
				{
					dA[i][i] += 0.0001;
				}
			}

			// Solve matrix equation B = AX by computing X = inv(A'A)*A'B
			iSolve = _Solve ( dA, (double *) &dB, (double *) &dX, nNumVariables , nNumVariables );

			// Limit size of corrections
			dScale = 1.0;

			dRlast = min( dXMax[0], dR );
			dR = sqrt( dX[0]*dX[0] + dX[1]*dX[1] + dX[2]*dX[2] );


			for( i = 0; i < 3; i++ )
			{
				if ( dRlast > 0.0 )
					dScale = max (dScale, fabs (dX[i]/dRlast ) );
			}

        
			// Check for convergence
			m_bConverged = true;
			for( i = 0; i < nNumVariables; i++ )
			{
				if ( i < 3 ) dX[i] /= dScale;
				dX[i] *= damp;
				if ( fabs(dX[i]) > dXMin[i] ) m_bConverged = false;
			}

			if( iIterations < lpControl->iIterationsMin )
			{
				m_bConverged = false;
			}


			if( ((dX[0]*dXLast[0] < 0) && (fabs( dX[0] + dXLast[0] ) <= dXMin[0])) ||
				((dX[1]*dXLast[1] < 0) && (fabs( dX[1] + dXLast[1] ) <= dXMin[1])) ||
				((dX[2]*dXLast[2] < 0) && (fabs( dX[2] + dXLast[2] ) <= dXMin[2])) )
			{
				nOscillations++;
				if( nOscillations == c_nMaxOscillations )
				{
					if( dMaxFact <= 1.0 )
					damp *= 0.50;
					nOscillations = 0;  
				}
			}
			else  nOscillations = 0;

			for( i = 0; i < nNumVariables; i++ )
			{
				  dXLast[i] = dX[i];
			}

			// Update solution vector

			vBEACON.dX += dX[0];
			vBEACON.dY += dX[1];
			vBEACON.dZ += dX[2];
			geoBEACON = oCoord.ToGeodetic( vBEACON );
			//geoBEACON.fAltitude = 0.0;

			//vBEACON = oCoord.ToEarthFixedDouble( geoBEACON );


			lpsolnOUT->location = geoBEACON;

			lpsolnOUT->dFrequency += dX[3];

			if( nNumVariables > 4 )
			{
				for( int i=0; i< nPts; i++ )
				{
					lpDATA[i].extras.timeTransmit.intTime += (INT64) (dX[4]*1e-9);
				}
			}

			hr = _GetResiduals( vBEACON, lpsolnOUT->dFrequency, lpDATA, nPts );

			//************************************************************* Debug 
			if ( (m_lplpTracerFile &&  *m_lplpTracerFile) && (nPts > 1) &&
                 (m_lpTracingLevel && (*m_lpTracingLevel > 1)) )
			{
   			    fprintf( *m_lplpTracerFile, "%s,%15I64X,%04ld,%03ld,%05ld,%03d,%04d,%04d,%04d,%7.3f,%7.3f,%7.3f,%7.3f,%8.3f,%9.3f,%12.2lf,%2d,%10.4f,%10.4f,%10.4f,%10.4f,%10.4f,%2d,%3d\n",
                        pKind, lpDATA[0].calib406.i64BeaconID,
                        lpDATA[0].calib406.hdr.id.ulLutID,
                        lpDATA[0].calib406.hdr.id.ulSatID,
                        lpDATA[0].calib406.ulPassID,
                        iIterations, nPts, nNumBurstsUsed, nPtsUsed,
						dFreqMean, dFreqStdDev,
						dTimeMean, dTimeStdDev,
                        lpsolnOUT->location.degLatitude,
                        lpsolnOUT->location.degLongitude,
                        lpsolnOUT->dFrequency,
						(int)(bMultiPass),
                        dX[0], dX[1], dX[2], dX[3], dX[4], nNumVariables, iSolve );
			}
			//*************************************************************/ Debug


			iIterations++;

			lpsolnOUT->wNumIterations = iIterations;// Number of iterations

			if ( iIterations > lpControl->iIterationsMax / 2 )
			{
				if( dFreqStdDev * dTimeStdDev < dFreqStdDevBEST * dTimeStdDevBEST )
				{
					memcpy( &solnBEST, lpsolnOUT, sizeof(EMSWLSLOCATE) );
					dFreqStdDevBEST = dFreqStdDev;
					dTimeStdDevBEST = dTimeStdDev;
				}
			}


		}// for MaxIter

	//-----------------------------------------------------------------------------------------
	//-----------------------------------------------------------------------------------------

		
	// fill output solution structure
		

		// Update average transmit frequency
		lpsolnOUT->dFrequency = MeanTxFrequency( lpDATA, nPts );

		// Compute summary statistics
		nFreqPtsUsed = _SummaryFreqStatistics( 1, lpDATA, nPts, &dFreqRMS, &dFreqMean, &dFreqStdDev, &dFreqTrend );
		
		nTimePtsUsed = _SummaryTimeStatistics( 1, lpDATA, nPts, &dTimeRMS, &dTimeMean, &dTimeStdDev, &dTimeTrend );

		if ( iIterations >= lpControl->iIterationsMax  )
		{
			memcpy( lpsolnOUT, &solnBEST, sizeof(EMSWLSLOCATE) );
			dFreqStdDev = dFreqStdDevBEST;
			dTimeStdDev = dTimeStdDevBEST;

		}

		double dTimeStdDevMsec = dTimeStdDev * 1000.0;

		//lpsolnOUT->wNumMsgs       = lpSolnIN->wNumMsgs;	// Number of measurements 
		lpsolnOUT->wNumMsgs       = nPts;	// Number of measurements 
		//lpsolnOUT->wNumMsgsUsed   = nFreqPtsUsed + nTimePtsUsed;		// Number of measurements used in location estimate
		
		if ( nFreqPtsUsed >= nTimePtsUsed )
			lpsolnOUT->wNumMsgsUsed   = nFreqPtsUsed;		// Number of measurements used in location estimate
		else
			lpsolnOUT->wNumMsgsUsed   = nTimePtsUsed;		// Number of measurements used in location estimate

		lpsolnOUT->fRMS           = (float) dFreqStdDev;	    // Standard Deviation of frequency measurement residuals (Hz) 
		lpsolnOUT->fTrend         = (float) dTimeStdDevMsec;	// Standard Deviation of of time residuals (msec) 

		// Check if TDOA only processing : EMSLOCATE_PROCESS_TDOA = 0x0001
		if ( lpControl->wProcessDataType == 0x0001 )
		{
			lpsolnOUT->fRMS = lpsolnOUT->fTrend;
		}


		// Count data in view of primary satellite
		nPtsVisible = _ElevationTest( lpDATA, nPts, lpsolnOUT->location );

		// Count number of bursts used in the solution
		nNumBurstsUsed = _BurstUsedCount( lpDATA, nPts );

		lpsolnOUT->wNumBurstsUsed = nNumBurstsUsed;

		// Special criteria for convergence test
		if ( ( dFreqStdDev > lpControl->dMaxFreqNoise ) || ( dTimeStdDev > lpControl->dMaxTimeNoise )
			|| ( nPtsVisible < (int)lpControl->ulMinPtsVisible ) )
		//if ( ( dFreqStdDev > lpControl->dMaxFreqNoise ) || ( dTimeStdDevMsec > lpControl->dMaxTimeNoise )
		//	|| ( nPtsVisible < (int)lpControl->ulMinPtsVisible ) )
		//if ( ( dFreqStdDev > lpControl->dMaxFreqNoise ) || ( dTimeStdDevMsec > lpControl->dMaxTimeNoise )
		//	|| ( nPtsVisible < (int)lpControl->ulMinPtsVisible )
		//	|| ( lpsolnOUT->wNumIterations >= lpControl->iIterationsMax ) )
		//if ( ( dFreqStdDev > lpControl->dMaxFreqNoise ) || ( nPtsVisible < (int)lpControl->ulMinPtsVisible ) )
		{
			lpsolnOUT->wNumIterations |= EMS_LOCATE_MAX_ITERATIONS_FLAG;
		}
		
		_UpdateSolutionErrors( lpDATA, nPts, &tcaCta, dFreqStdDev, dA, lpControl, lpsolnOUT );

		// Calculate HDOP.
		//lpsolnOUT->fFreqDrift = _HDOP( lpsolnOUT->location, lpDATA, nPts );
		lpsolnOUT->fFreqDrift = (float) _GDOP( lpsolnOUT->location, lpDATA, nPts, nTimePtsUsed );

		lpsolnOUT->fFreqBiasError = (float)nTimePtsUsed + (float)0.1;
		// a little extra required for storage of interger into a floating point number

	}

	return hr;
}

//***********************************************************************************************

double CEMSWLSxyz406::_Det3x3( double dA[MAXVARIABLES][MAXVARIABLES] )
{
	double det = 0.0;

	det =   dA[0][0] * dA[1][1] * dA[2][2] 
		  + dA[0][1] * dA[1][2] * dA[2][0]
		  + dA[0][2] * dA[1][0] * dA[2][1]
		  - dA[0][0] * dA[1][2] * dA[2][1]
		  - dA[0][1] * dA[1][0] * dA[2][2]
		  - dA[0][2] * dA[1][1] * dA[2][0];

	return det;
}

//***********************************************************************************************

double CEMSWLSxyz406::_DetNxN( double dA[MAXVARIABLES][MAXVARIABLES], int N )
{
	//WARNING : ***** Recursive subroutine *****
	
	double dB[MAXVARIABLES][MAXVARIABLES]; // temp matrix storage
	
	int	i, j, k, m, n;
	
	double dDeterminant = 0.0;

	if( N == 2 )
	{
		dDeterminant = dA[0][0]*dA[1][1] - dA[0][1]*dA[1][0];
	}
	else
	{
		for( k = 0; k < N; k++)
		{
			m = 0;
			n = 0;

			for( i = 1; i < N; i++)
			{
				for( j = 0; j < N; j++ )
				{
					if( !(j == k) )
					{
						dB[m][n] = dA[i][j];
						n++;
						if(n == N-1)
						{
							m++;
							n = 0;
						}
					}
				}
			}

			dDeterminant = dDeterminant + dA[0][k]*pow((double) -1,k)*_DetNxN(dB,N-1);
 
		}
	}
	return dDeterminant;
}

//***********************************************************************************************

int CEMSWLSxyz406::_Solve( double ppdMatrixA[MAXVARIABLES][MAXVARIABLES], double *pdColumnC, 
		 double *pdSolutionB, int M, int N )

		// solves a set of up to 10 simultaneous linear equations 
		// using the Gauss-Jordan reduction method with pivoting, 
		// first by inverting the input coefficient matrix, then 
		// multiplying it by the right-hand side column matrix
		// ppdMatrixA(M,M) - coefficients matrix, size M*M
		// pdColumnC(M) - right-hand column matrix, size 1*M
		// pdSolutionB(M) - column matrix of solutions to linear equations
		// M - size of matrix A
		// N - number of variables to be solved
{
	int i, j, k, l; // indices
	int nIcol = 0; // column index
	int nIrow = 0; // row index
	int nIpiv[10]; // pivot flags
	int nIndex[10][2]; // sorting matrix to restore rows and columns
	int iError = 0; // return error condition
	double dTemp; // temporary variable for matrix element
	double dPiv; // pivot element

	// zero pivot indices
	for ( j = 0; j < N; j ++ )
	{
		nIpiv[j] = 0;
	}
	// invert the square coefficient matrix A
	for ( i = 0; i < N; i ++ )
	{
		// search for largest element to be pivot 
		dPiv = 0;
		for ( j = 0; j < N; j ++ ) 
		{
			if ( nIpiv[j] != 1 )
			{
				for ( k = 0; k < N; k ++ ) 
				{
					if ( nIpiv[k] != 1 )
					{
						if ( fabs(dPiv) < fabs( ppdMatrixA[j][k]) ) 
						{
							nIrow = j;
							nIcol = k;
							dPiv = ppdMatrixA[j][k];
						}
					}
				}
			} // if !
		} 
		nIpiv[nIcol] ++;

		// check validity of the pivot
		// Requires input matrix to be properly scaled
		//if ( dPiv == 0 )
		if ( fabs(dPiv) < 1e-10 )
		{
			iError = -1;	// flag error!

			for ( i = 0; i < N; i ++ )
			{
				pdSolutionB[i] = 0;
			}
			return iError;
		}

		// put pivot element on diagonal if not already on it
		if ( nIrow != nIcol )
		{
			for ( l = 0; l < N; l ++ )
			{
				dTemp = ppdMatrixA[nIrow][l];
				ppdMatrixA[nIrow][l] = ppdMatrixA[nIcol][l];
				ppdMatrixA[nIcol][l] = dTemp;
			}
		}
			nIndex[i][0] = nIrow;
			nIndex[i][1] = nIcol;

			// divide pivot row by pivot element
			ppdMatrixA[nIcol][nIcol] = 1.0;

			for ( l = 0; l < N; l++ )
			{
				ppdMatrixA[nIcol][l] = ppdMatrixA[nIcol][l] / dPiv;
			}

			// reduce non-pivot rows

			for ( k = 0; k < N; k ++ )
			{
				if ( k != nIcol )
				{
					dTemp = ppdMatrixA[k][nIcol];
					ppdMatrixA[k][nIcol] = 0;

					for ( l = 0; l < N; l ++ )
					{
						ppdMatrixA[k][l] = ppdMatrixA[k][l] - ppdMatrixA[nIcol][l] * dTemp;
					}
				}
			}		
	} //for

	// coefficient matrix inverted, but with possible column changes
	// interchange them as necessary

	for ( i = 0; i < N; i ++ )
	{
		l = N - i - 1;
		if ( nIndex[l][0] != nIndex[l][1] )
		{
			nIrow = nIndex[l][0];
			nIcol = nIndex[l][1];

			for ( k = 0; k < N; k ++ )
			{
				dTemp = ppdMatrixA[k][nIrow];
				ppdMatrixA[k][nIrow] = ppdMatrixA[k][nIcol];
				ppdMatrixA[k][nIcol] = dTemp;
			}
		}
	}

	// multiply inverted coefficient matrix A by right
	// hand side column matrix C, and store it in solution
	// column matrix B
	for ( i = 0; i < N; i ++ )
	{
		pdSolutionB[i] = 0;
		for ( j = 0; j < N; j ++ )
		{
			pdSolutionB[i] = pdSolutionB[i] + ppdMatrixA[i][j]*pdColumnC[j];
		}
	}

	return iError;
}


// ********************************************************************************************

HRESULT CEMSWLSxyz406::GetMeshResiduals( LPEMSCALIB406DATAEXT lpDATA, int nPts, 
											LPEMSWLSLOCATE lpSOLN1, LPEMSWLSLOCATE lpSOLN2,
											double dAngle, int nXcells, int nYcells ) 
{	
	HRESULT hr = EMS_OK;

	EMSLOCATION	vLOC;
	EMSLOCATION	vBestLOC;
		
	CEMSCoordSystem coordSys;

	CEMSHexGrid oMesh;

	LPEMSHEXGRID lpGrid = 0;

	double	dStdDevMin = 1e6;
	double	dFreqStdDev, dFreqMedian, dFreqMean;
	double	dTimeStdDev, dTimeMedian, dTimeMean;
	double	dStdDev;
	double	dMinTxFrequency = 406000000.0;  // Minimum allowed for transmit frequency
	double	dMeanTxFrequency;  // transmit frequency

	int		nFreqPtsUsed = 0;
	int		nTimePtsUsed = 0;
	int		nPtsUsed = 0;
	int		nFreqAcceptPts = 0;
	int		nTimeAcceptPts = 0;
	int		nFreqRejectPts = 0;
	int		nTimeRejectPts = 0;

	int		nAcceptTestPts = 0;
	int		nElevTestPts = 0;
	int		nMaxPtsUsed = 0;

	int		nGlobalIndex = 0;
	int		nLocalIndex = 0;

	double	dPointCountThreshold = c_dPointCountThreshold;
	double	disttest;

	CEMSOutlier	oFreqOutlier;
	CEMSOutlier	oTimeOutlier;

	oFreqOutlier.Init( nPts );
	oTimeOutlier.Init( nPts );

	nAcceptTestPts = _SetProcessFlags( lpDATA, nPts );

	if ( nAcceptTestPts > c_nMinAcceptPointCount )
	{
		nAcceptTestPts = int ( dPointCountThreshold * nAcceptTestPts + 0.5 );
	}

	// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if ( (m_lplpTracerFile &&  *m_lplpTracerFile) &&
		(m_lpTracingLevel && (*m_lpTracingLevel >= 4)) )
	{
		fprintf( *m_lplpTracerFile, "MESH,BeaconID,GridIndex,Latitude,Longitude,CostFunction,");
		fprintf( *m_lplpTracerFile, "nFreqPtsUsed,dFreqMean,dFreqMedian,dFreqStDev,");
		fprintf( *m_lplpTracerFile, "nTimePtsUsed,dTimeMean,dTimeMedian,dTimeStDev,");
		fprintf( *m_lplpTracerFile, "nFreqAcceptPts,nTimeAcceptPts,nAcceptTestPts,nElevTestPts\n");
	
	}
	// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	vLOC = lpSOLN1->location;

	lpSOLN1->wNumMsgsUsed	= 0;	// Number of measurements used in location estimate
	lpSOLN1->fRMS			= -1.0;	// Standard Deviation of frequency measurement residuals (Hz) 
	lpSOLN1->fTrend			= -1.0;	// Standard Deviation of time measurement residuals (sec)

	dMeanTxFrequency = MeanTxFrequency( lpDATA, nPts );

	//hr = oMesh.CalculateGrid ( dAngle, nXcells, nYcells );

	//hr = oMesh.RotateGrid ( vLOC.degLatitude, vLOC.degLongitude );

	hr = oMesh.GenerateGrid( vLOC.degLatitude, vLOC.degLongitude, dAngle, nXcells, nYcells );

	int nTotalCells = oMesh.GetGridSize();

	lpGrid = new EMSHEXGRID [ nTotalCells ];

	memset( lpGrid, 0, nTotalCells*sizeof(EMSHEXGRID) );

	// Compute grid array entries

	for ( int i = 0; i < nTotalCells; i++ )
	{

		hr = oFreqOutlier.Reset();
		hr = oTimeOutlier.Reset();

		nFreqPtsUsed = 0;
		nTimePtsUsed = 0;
				
		dFreqMean = 0.0;
		dTimeMean = 0.0;

		dFreqMedian = 0.0;
		dTimeMedian = 0.0;

		dFreqStdDev = 0.0;
		dTimeStdDev = 0.0;

		vLOC = oMesh.GetGridLocation( i );

		vLOC.fAltitude = 0.0;

		// Initialize Grid entry
		lpGrid[i].vGridLocation = vLOC;
		lpGrid[i].dMeanFrequency= dMeanTxFrequency;
		lpGrid[i].dStdDev		= -1.0;
		lpGrid[i].nPtsUsed		= 0;
		lpGrid[i].dTimeStdDev	= -1.0;
		lpGrid[i].dFreqStdDev	= -1.0;
		lpGrid[i].nTimePtsUsed	= 0;
		lpGrid[i].nFreqPtsUsed	= 0;
		lpGrid[i].nElevTestPts	= 0;
		lpGrid[i].wFlags		= -1;


		// Satellite footprint checks
		nPtsUsed     = _SetProcessFlags( lpDATA, nPts );
		nElevTestPts = _ProcessFlagElevationTest( lpDATA, nPts, vLOC );

		if ( nElevTestPts >= nAcceptTestPts )
		{

			//hr = GetResiduals( vLOC, lpSOLN1->dFrequency, lpDATA, nPts );
			hr = GetResiduals( vLOC, dMeanTxFrequency, lpDATA, nPts );


			for ( int j = 0; j < nPts; j++ )
			{
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_PROCESS_FREQ_FLAG ) )
				{
					hr = oFreqOutlier.AddRecord( lpDATA[j].extras.dFreqResidual );
				}
				if ( _TestFlag( &lpDATA[j], EMS_C406PF_PROCESS_TIME_FLAG ) )
				{
					hr = oTimeOutlier.AddRecord( lpDATA[j].extras.dTimeResidual );
				}
			}

			if ( oFreqOutlier.GetTotalCount() > 0 )
			{
				hr = oFreqOutlier.Sort();
				
				nFreqAcceptPts = int ( dPointCountThreshold * oFreqOutlier.GetTotalCount() + 0.5);
				nFreqRejectPts = oFreqOutlier.GetTotalCount() - nFreqAcceptPts;
				
				hr = oFreqOutlier.SetCountThreshold( nFreqRejectPts, oFreqOutlier.GetMedian() );
				
				dFreqMean = oFreqOutlier.GetMean();
				dFreqMedian = oFreqOutlier.GetMedian();
				dFreqStdDev = oFreqOutlier.GetStddev();
				nFreqPtsUsed = oFreqOutlier.GetThresholdCount();
			}

			if ( oTimeOutlier.GetTotalCount() > 0 )
			{
				hr = oTimeOutlier.Sort();

				nTimeAcceptPts = int ( dPointCountThreshold * oTimeOutlier.GetTotalCount() + 0.5);
				nTimeRejectPts = oTimeOutlier.GetTotalCount() - nTimeAcceptPts;

				hr = oTimeOutlier.SetCountThreshold( nTimeRejectPts, oFreqOutlier.GetMedian() );
				
				dTimeStdDev = oTimeOutlier.GetStddev();
				dTimeMedian = oTimeOutlier.GetMedian();
				dTimeMean = oTimeOutlier.GetMean();
				nTimePtsUsed = oTimeOutlier.GetThresholdCount();
			}
//			dStdDev = 0.0;
//			if ( nFreqPtsUsed > 1)
//				dStdDev += dFreqStdDev * m_dFreqWeight;
//			if ( nTimePtsUsed > 1)
//				dStdDev += dTimeStdDev * m_dTimeWeight;
			dStdDev = _ConvertTOAFOA2Km( dTimeStdDev, dFreqStdDev );

			nPtsUsed = nFreqPtsUsed + nTimePtsUsed;
					
			//dMeanTxFrequency = MeanTxFrequency( lpDATA, nPts );

			lpGrid[i].vGridLocation = vLOC;
			lpGrid[i].dMeanFrequency= dMeanTxFrequency + dFreqMean;
			lpGrid[i].dStdDev		= dStdDev;
			lpGrid[i].nPtsUsed		= nPtsUsed;
			lpGrid[i].dTimeStdDev	= dTimeStdDev;
			lpGrid[i].dFreqStdDev	= dFreqStdDev;
			lpGrid[i].nTimePtsUsed	= nTimePtsUsed;
			lpGrid[i].nFreqPtsUsed	= nFreqPtsUsed;
			lpGrid[i].nElevTestPts	= nElevTestPts;
			lpGrid[i].wFlags		= 0;

			// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			if ( (m_lplpTracerFile &&  *m_lplpTracerFile) &&
				(m_lpTracingLevel && (*m_lpTracingLevel >= 4)) )
			{
				fprintf( *m_lplpTracerFile, "MESH,%15I64X,%5d,%10.3f,%10.3f,%10.3f,%5d,%10.3f,%10.3f,%10.3f,%5d,%10.6f,%10.6f,%10.6f,%5d,%5d,%5d,%5d\n",
					lpDATA[0].calib406.i64BeaconID, i ,vLOC.degLatitude, vLOC.degLongitude, dStdDev,
					nFreqPtsUsed, dFreqMean, dFreqMedian, dFreqStdDev,
					nTimePtsUsed, dTimeMean*1e3, dTimeMedian*1e3, dTimeStdDev*1e3,
					nFreqAcceptPts, nTimeAcceptPts, nAcceptTestPts, nElevTestPts  );
			
			}
			// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			if ( (nPtsUsed >= nMaxPtsUsed) && (nPtsUsed > 1) )
			{
				if ( dStdDev < dStdDevMin || nPtsUsed > nMaxPtsUsed )
				{


					lpSOLN1->location		= vLOC;

					//if ( dMinTxFrequency < dMeanTxFrequency )
					//	lpSOLN1->dFrequency = dMeanTxFrequency;

					//lpSOLN1->dFrequency      += dFreqMean;		// Update carrier frequency estimate
					
					lpSOLN1->dFrequency     = dMeanTxFrequency + dFreqMean;	// Update carrier frequency estimate
					lpSOLN1->wNumMsgsUsed	= nPtsUsed;			// Number of measurements used in location estimate
					lpSOLN1->fRMS			= (float) dFreqStdDev;	// Standard Deviation of frequency measurement residuals (Hz) 
					lpSOLN1->fTrend			= (float) dTimeStdDev;	// Standard Deviation of time measurement residuals (sec)

					dStdDevMin				= dStdDev;
					nMaxPtsUsed				= nPtsUsed;
					nGlobalIndex			= i;
				}
			}

		} // End of elevation point count check
	} // End of Mesh loop


	// Check if local minimum required
	if ( lpSOLN2 )
	{
		// Find local and global minimums
		lpGrid[nGlobalIndex].wFlags |= EMS_GLOBAL_MINIMUM;
		
		nLocalIndex = nGlobalIndex; // special case if no local minimum is found

		dStdDevMin  = 1000000.0;
		nMaxPtsUsed = 1;

		vBestLOC = lpGrid[nGlobalIndex].vGridLocation;

		for ( int i = 0; i < nTotalCells; i++ )
		{
//			if ( i != nGlobalIndex )
			if ( lpGrid[i].wFlags == 0 )
			{

/*
				int pIndexArray[6];
				int nCount = 0;
				int nIndex = 0;

				if (! (lpGrid[i].wFlags & EMS_NO_LOCAL_MINIMUM) )
				{
					nCount = oMesh.GetNearestNeighbours( i, 6, dAngle*1.2, (int *) &pIndexArray );

					for ( int j = 0; j < nCount; j++ )
					{
						nIndex = pIndexArray[j];
						// Test for local
						if ( (lpGrid[i].nPtsUsed >= lpGrid[nIndex].nPtsUsed) 
							&& ( lpGrid[i].dStdDev < lpGrid[nIndex].dStdDev ) )
						{
							lpGrid[nIndex].wFlags |= EMS_NO_LOCAL_MINIMUM;
						}
						else
						{
							lpGrid[i].wFlags |= EMS_NO_LOCAL_MINIMUM;
							nCount = 0;
						}
					}
*/

				// Compute separation distance
				vLOC = lpGrid[i].vGridLocation;

				disttest = coordSys.DistanceApart( vLOC, vBestLOC );

				// Accept only locations separated by more than 1000 km	
				if ( disttest > 1000.0 )
				{
				// Check if 'best' local minimum
//					if (! (lpGrid[i].wFlags & EMS_NO_LOCAL_MINIMUM) )
					{
						lpGrid[i].wFlags |= EMS_LOCAL_MINIMUM;

						if ( (lpGrid[i].nPtsUsed >= nMaxPtsUsed) 
							&& ( lpGrid[i].dStdDev < dStdDevMin ) )
						{
							nMaxPtsUsed = lpGrid[i].nPtsUsed;
							dStdDevMin  = lpGrid[i].dStdDev;
							nLocalIndex = i;
						}

					}

				}
			}

		}

		memcpy( lpSOLN2, lpSOLN1, sizeof(EMSWLSLOCATE) );

		lpSOLN2->location		= lpGrid[nLocalIndex].vGridLocation;
		lpSOLN2->dFrequency		= lpGrid[nLocalIndex].dMeanFrequency;
		lpSOLN2->wNumMsgsUsed	= lpGrid[nLocalIndex].nPtsUsed;
		lpSOLN2->fRMS			= (float) lpGrid[nLocalIndex].dFreqStdDev;	// Standard Deviation of frequency measurement residuals (Hz) 
		lpSOLN2->fTrend			= (float) lpGrid[nLocalIndex].dTimeStdDev;	// Standard Deviation of time measurement residuals (sec)

	}

	// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	if ( (m_lplpTracerFile &&  *m_lplpTracerFile) &&
		(m_lpTracingLevel && (*m_lpTracingLevel >= 4)) )
	{
		fprintf( *m_lplpTracerFile, "GLOBAL,%15I64X,%5d,%10.3f,%10.3f,%10.3f,%5d,%10.3f,%5d,%10.6f,%5d,%3X\n",
					lpDATA[0].calib406.i64BeaconID,nGlobalIndex,
					lpGrid[nGlobalIndex].vGridLocation.degLatitude,
					lpGrid[nGlobalIndex].vGridLocation.degLongitude,
					lpGrid[nGlobalIndex].dStdDev,
					lpGrid[nGlobalIndex].nFreqPtsUsed, lpGrid[nGlobalIndex].dFreqStdDev,
					lpGrid[nGlobalIndex].nTimePtsUsed, lpGrid[nGlobalIndex].dTimeStdDev*1e3,
					lpGrid[nGlobalIndex].nElevTestPts, lpGrid[nGlobalIndex].wFlags  );
		if ( lpSOLN2 )
		{
			fprintf( *m_lplpTracerFile, "LOCAL,%15I64X,%5d,%10.3f,%10.3f,%10.3f,%5d,%10.3f,%5d,%10.6f,%5d,%3X\n",
					lpDATA[0].calib406.i64BeaconID,nLocalIndex,
					lpGrid[nLocalIndex].vGridLocation.degLatitude,
					lpGrid[nLocalIndex].vGridLocation.degLongitude,
					lpGrid[nLocalIndex].dStdDev,
					lpGrid[nLocalIndex].nFreqPtsUsed, lpGrid[nLocalIndex].dFreqStdDev,
					lpGrid[nLocalIndex].nTimePtsUsed, lpGrid[nLocalIndex].dTimeStdDev*1e3,
					lpGrid[nLocalIndex].nElevTestPts, lpGrid[nLocalIndex].wFlags  );
		}
	}
	// Debug ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	
	if ( lpGrid ) 
	{
		delete [ ] lpGrid;
		lpGrid = 0;
	}

	return hr;
}

//**********************************************************************************************

int CEMSWLSxyz406::_TimeThreshold( LPEMSCALIB406DATAEXT lpDATA, int nPts, double dMean, double dThreshold )
{

	int nTimePtsUsed = 0;

	if ( lpDATA && ( nPts > 0 ) )
	{
		double dResidual;

		for ( int i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG ) )
			{
				dResidual  = lpDATA[i].extras.dTimeResidual;

				if ( fabs( dResidual - dMean ) > dThreshold )
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
				else
					nTimePtsUsed++;
			}

		}

	}

	return nTimePtsUsed;
}

//**********************************************************************************************

int CEMSWLSxyz406::_FreqThreshold( LPEMSCALIB406DATAEXT lpDATA, int nPts, double dMean, double dThreshold )
{

	int nFreqPtsUsed = 0;

	if ( lpDATA && ( nPts > 0 ) )
	{
		double dResidual;

		for ( int i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG ) )
			{
				dResidual  = lpDATA[i].extras.dFreqResidual;

				if ( fabs( dResidual - dMean ) > dThreshold )
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
				else
					nFreqPtsUsed++;
			}

		}

	}

	return nFreqPtsUsed;
}

//**********************************************************************************************

int CEMSWLSxyz406::_SetProcessFlags( LPEMSCALIB406DATAEXT lpDATA, int nPts )
{

	int nPtsUsed = 0;

	if ( lpDATA && ( nPts > 0 ) )
	{

		for ( int i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
			{
				_SetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
				nPtsUsed++;
			}
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
			{
				_SetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
				nPtsUsed++;
			}
		}

	}

	return nPtsUsed;
}

//**********************************************************************************************

EMS_RESULT CEMSWLSxyz406::GetTcaCta( EMSLOCATION location, ULONG ulSatID,
									   LPEMSCALIB406DATAEXT lpDATA, int nPts,
									   LPEMSTCACTA lpTcaCta ) 
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( lpDATA && nPts && ulSatID && &location && lpTcaCta )
	{

		hr = EMS_OK;

		CEMSCoordSystem CS;		
		EMSTCACTA		a;
		LPEMSTIMECOORDD lpSatvec  = new EMSTIMECOORDD[ nPts ];

		ULONG			ulCount = 0;

		for ( int i = 0; i < nPts; i++ )
		{	
			if ( lpDATA[i].calib406.hdr.id.ulSatID == ulSatID )
			{
				lpSatvec[ulCount] = lpDATA[i].extras.SatTPVC;
				ulCount++;
			}
		}

		if ( ulCount == 1 )
		{
			lpSatvec[ulCount] = lpSatvec[0];
			lpSatvec[ulCount].coord.radius.dX += lpSatvec[0].coord.velocity.dX;
			lpSatvec[ulCount].coord.radius.dY += lpSatvec[0].coord.velocity.dY;
			lpSatvec[ulCount].coord.radius.dZ += lpSatvec[0].coord.velocity.dZ;
			ulCount++;
		}
			
		a = CS.ToTcaCta( location, lpSatvec, ulCount );

		if ( lpSatvec ) 
		{
			delete [ ] lpSatvec;
			lpSatvec = 0;
		}

		*lpTcaCta = a;
	
	}

	return hr;
}

//**********************************************************************************************

double CEMSWLSxyz406::MeanTxFrequency( LPEMSCALIB406DATAEXT lpData, int nPts )
{
	double	dMeanTxFrequency = 0.0;
	double	dMeanTxFrequencyAll = 0.0;
	int		nCount = 0;
	int		nCountAll = 0;

	for ( int i=0; i < nPts; i++ )
	{
		if ( _TestFlag( &lpData[i], EMS_C406PF_PROCESS_FREQ_FLAG ) )
		{
			dMeanTxFrequency += lpData[i].extras.dTxFrequency;
			nCount++;
		}
		dMeanTxFrequencyAll += lpData[i].extras.dTxFrequency;
		nCountAll++;

	}

	if ( nCount > 0 )
	{
		dMeanTxFrequency = dMeanTxFrequency / nCount;
	}
	else if ( nCountAll > 0 )
	{
		dMeanTxFrequency = dMeanTxFrequencyAll / nCountAll;
	}

	return dMeanTxFrequency;
}
//**********************************************************************************************

bool CEMSWLSxyz406::IsMultiPass( LPEMSCALIB406DATAEXT lpData, int nPts, bool bOnlyIfUsed )
{
	bool bMultiPass = false;

	if ( lpData && nPts )
	{
		double dMinutes = 0.0;
		ULONG ulLastSatID = 0;
		CEMSTime timeLast;

		for ( int i = 0; i < nPts; i++ ) // first id all of the satellites
		{
			if ( !bOnlyIfUsed || _TestFlag( &lpData[i], EMS_C406PF_PROCESS_FREQ_FLAG ) )
			{
				if ( ( lpData[i].calib406.hdr.id.ulSatID != ulLastSatID ) ||
					( timeLast.MinutesDifferent( lpData[i].calib406.timeMsg ) > c_dMaxPassMinutes ) ) 
				{
					if ( 0 != ulLastSatID )
					{
						bMultiPass = true;
					}
					ulLastSatID = lpData[ i ].calib406.hdr.id.ulSatID;

					timeLast.SetTime( lpData[ i ].calib406.timeMsg );
				}
			}
		}
	}

	return bMultiPass;
}

//***********************************************************************************************

double CEMSWLSxyz406::_ConvertTOAFOA2Km( double dTOAsec, double dFOAhz )
{
	double dRet = 0.0;

	if ( dFOAhz > 0.0 )
	{
		dRet +=  ( dFOAhz * (c_dVelocityOfLight/406.0e6) / c_radEarthRotationRate )
				*( dFOAhz * (c_dVelocityOfLight/406.0e6) / c_radEarthRotationRate );
	}

	if ( dTOAsec > 0.0 )
	{
		dRet += ( dTOAsec * c_dVelocityOfLight ) * ( dTOAsec * c_dVelocityOfLight );
	}

	if ( dRet > 0.0 )
	{
		dRet = sqrt( dRet );
	}

	return dRet;
}

//***********************************************************************************************

double CEMSWLSxyz406::_GDOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts, int nTimePts )
{
	double dRet = 0.0;

	EMSTIMECOORDD vCoord;

	CEMSCoordSystem oCoordSys;

	EMSVECTORD vGLoc = oCoordSys.ToEarthFixedDouble( location );

	double* adH1 = NULL;
	double* adH2 = NULL;
	double* adH3 = NULL;

	if( nPts )
	{
		adH1 = new double[nPts];
		adH2 = new double[nPts];
		adH3 = new double[nPts];
	}

	memset(adH1, 0, nPts*sizeof(double) );
	memset(adH2, 0, nPts*sizeof(double) );
	memset(adH3, 0, nPts*sizeof(double) );

	for ( ULONG i = 0; i < (ULONG)nPts ; i++ )
	{
		switch ( lpDATA[i].extras.SatTPVC.coordSystem )
		{
			case COORDSYS_EarthFixed:
				memset( &vCoord, 0, sizeof( vCoord ) );

				vCoord.vTime = lpDATA[i].extras.SatTPVC.vTime;

				vCoord.coord.radius = vGLoc;

				vCoord.coord.velocity = oCoordSys.EarthFixedVelocity( vGLoc );
				break;

			case COORDSYS_Inertial:
				vCoord = oCoordSys.EarthFixedToInertial( vGLoc, lpDATA[i].extras.SatTPVC.vTime );
				break;

			default:
				break;
		}



		EMSVECTORD vDiffRadius;

		vDiffRadius = CEMSVector::Sub( lpDATA[i].extras.SatTPVC.coord.radius , vCoord.coord.radius );


		double dRange = sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );


		adH1[i] = vDiffRadius.dX / dRange;
		adH2[i] = vDiffRadius.dY / dRange;
		adH3[i] = vDiffRadius.dZ / dRange;

	}


	double adZ[MAXVARIABLES][MAXVARIABLES]; 
	memset( &adZ, 0, MAXVARIABLES*MAXVARIABLES*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adH1[j]*adH1[j];
		adZ[0][1] += adH1[j]*adH2[j];
		adZ[0][2] += adH1[j]*adH3[j];
		adZ[0][3] += adH1[j];

		adZ[1][0] += adH2[j]*adH1[j];
		adZ[1][1] += adH2[j]*adH2[j];
		adZ[1][2] += adH2[j]*adH3[j];
		adZ[1][3] += adH2[j];

		adZ[2][0] += adH3[j]*adH1[j];
		adZ[2][1] += adH3[j]*adH2[j];
		adZ[2][2] += adH3[j]*adH3[j];
		adZ[2][3] += adH3[j];

		adZ[3][0] += adH1[j];
		adZ[3][1] += adH2[j];
		adZ[3][2] += adH3[j];
		adZ[3][3] += 1.0;
	}


	double adSolutionB[4];
	double adColumnC[4] = { 1.0, 1.0, 1.0, 1.0 };
	int iSolve;

	if ( nTimePts > 3 )
	{
		iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 4, 4 );
		dRet = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] + adZ[3][3] );
	}
	else
	{
		iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 3, 3 );
		dRet = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] );
	}

	if( adH1 )
	{
		delete[] adH1;
		adH1 = NULL;
	}

	if( adH2 )
	{
		delete[] adH2;
		adH2 = NULL;
	}
	
	if( adH3 )
	{
		delete[] adH3;
		adH3 = NULL;
	}

	return dRet;
}

//***********************************************************************************************

double CEMSWLSxyz406::_DOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts, int nRefsat,
							 double& rdDOPFdoa, double& rdDOPTdoa, double& rdDOPJoin )
{
	double dRet = 0.0;

	EMSTIMECOORDD vCoord;

	CEMSCoordSystem oCoordSys;

	EMSVECTORD vGLoc = oCoordSys.ToEarthFixedDouble( location );

	double* adH1 = NULL;
	double* adH2 = NULL;
	double* adH3 = NULL;

	double* adG1 = NULL;
	double* adG2 = NULL;
	double* adG3 = NULL;

	if( nPts )
	{
		adH1 = new double[nPts];
		adH2 = new double[nPts];
		adH3 = new double[nPts];

		adG1 = new double[nPts];
		adG2 = new double[nPts];
		adG3 = new double[nPts];
	}

	memset(adH1, 0, nPts*sizeof(double) );
	memset(adH2, 0, nPts*sizeof(double) );
	memset(adH3, 0, nPts*sizeof(double) );

	memset(adG1, 0, nPts*sizeof(double) );
	memset(adG2, 0, nPts*sizeof(double) );
	memset(adG3, 0, nPts*sizeof(double) );

	for ( ULONG i = 0; i < (ULONG)nPts ; i++ )
	{
		switch ( lpDATA[i].extras.SatTPVC.coordSystem )
		{
			case COORDSYS_EarthFixed:
				memset( &vCoord, 0, sizeof( vCoord ) );

				vCoord.vTime = lpDATA[i].extras.SatTPVC.vTime;

				vCoord.coord.radius = vGLoc;

				vCoord.coord.velocity = oCoordSys.EarthFixedVelocity( vGLoc );
				break;

			case COORDSYS_Inertial:
				vCoord = oCoordSys.EarthFixedToInertial( vGLoc, lpDATA[i].extras.SatTPVC.vTime );
				break;

			default:
				break;
		}


		EMSRANGERATE RangeRate;
		memset( &RangeRate, 0, sizeof(RangeRate) );

		EMSVECTORD vDiffRadius, vDiffVelocity;

		vDiffRadius = CEMSVector::Sub( lpDATA[i].extras.SatTPVC.coord.radius , vCoord.coord.radius );

		vDiffVelocity = CEMSVector::Sub( lpDATA[i].extras.SatTPVC.coord.velocity , vCoord.coord.velocity );

		RangeRate.fRange = (float)sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );

		RangeRate.fRangeRate = (float)CEMSVector::DotProduct( vDiffRadius, vDiffVelocity ) /
													RangeRate.fRange;

		RangeRate.vTime = lpDATA[i].extras.SatTPVC.vTime;


		double dConst1 = RangeRate.fRangeRate / RangeRate.fRange;

		adH1[i] = vDiffRadius.dX / (double) RangeRate.fRange;
		adH2[i] = vDiffRadius.dY / (double) RangeRate.fRange;
		adH3[i] = vDiffRadius.dZ / (double) RangeRate.fRange;

		adG1[i] = ( vDiffVelocity.dX - vDiffRadius.dX*dConst1 ) / (double) RangeRate.fRange / c_radEarthRotationRate;
		adG2[i] = ( vDiffVelocity.dY - vDiffRadius.dY*dConst1 ) / (double) RangeRate.fRange / c_radEarthRotationRate;
		adG3[i] = ( vDiffVelocity.dZ - vDiffRadius.dZ*dConst1 ) / (double) RangeRate.fRange / c_radEarthRotationRate;

	}


	double adZ[MAXVARIABLES][MAXVARIABLES]; 
	memset( &adZ, 0, MAXVARIABLES*MAXVARIABLES*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adH1[j]*adH1[j];
		adZ[0][1] += adH1[j]*adH2[j];
		adZ[0][2] += adH1[j]*adH3[j];
		adZ[0][3] += adH1[j];

		adZ[1][0] += adH2[j]*adH1[j];
		adZ[1][1] += adH2[j]*adH2[j];
		adZ[1][2] += adH2[j]*adH3[j];
		adZ[1][3] += adH2[j];

		adZ[2][0] += adH3[j]*adH1[j];
		adZ[2][1] += adH3[j]*adH2[j];
		adZ[2][2] += adH3[j]*adH3[j];
		adZ[2][3] += adH3[j];

		adZ[3][0] += adH1[j];
		adZ[3][1] += adH2[j];
		adZ[3][2] += adH3[j];
		adZ[3][3] += 1.0;
	}


	double adSolutionB[4];
	double adColumnC[4] = { 1.0, 1.0, 1.0, 1.0 };
	int iSolve;

	if ( nPts > 3 )
	{
		iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 4, 4 );

		dRet = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] + adZ[3][3] );
	}
	else
	{
		iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 3, 3 );

		dRet = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] );
	}


	// Compute Joint DOP

	for( int j = 0; j < nPts; j++ )
	{
		adH1[j] -= adH1[nRefsat];
		adH2[j] -= adH2[nRefsat];
		adH3[j] -= adH3[nRefsat];

		adG1[j] -= adG1[nRefsat];
		adG2[j] -= adG2[nRefsat];
		adG3[j] -= adG3[nRefsat];
	}

	memset( &adZ, 0, 4*4*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adH1[j]*adH1[j];
		adZ[0][1] += adH1[j]*adH2[j];
		adZ[0][2] += adH1[j]*adH3[j];

		adZ[1][0] += adH2[j]*adH1[j];
		adZ[1][1] += adH2[j]*adH2[j];
		adZ[1][2] += adH2[j]*adH3[j];

		adZ[2][0] += adH3[j]*adH1[j];
		adZ[2][1] += adH3[j]*adH2[j];
		adZ[2][2] += adH3[j]*adH3[j];
	}

	adColumnC[0] = 1.0;
	adColumnC[1] = 1.0;
	adColumnC[2] = 1.0;

	iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 3, 3 );

	rdDOPTdoa = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] );

	memset( &adZ, 0, 4*4*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adG1[j]*adG1[j];
		adZ[0][1] += adG1[j]*adG2[j];
		adZ[0][2] += adG1[j]*adG3[j];

		adZ[1][0] += adG2[j]*adG1[j];
		adZ[1][1] += adG2[j]*adG2[j];
		adZ[1][2] += adG2[j]*adG3[j];

		adZ[2][0] += adG3[j]*adG1[j];
		adZ[2][1] += adG3[j]*adG2[j];
		adZ[2][2] += adG3[j]*adG3[j];
	}

	adColumnC[0] = 1.0;
	adColumnC[1] = 1.0;
	adColumnC[2] = 1.0;

	iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 3, 3 );

	rdDOPFdoa = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] );

	memset( &adZ, 0, 4*4*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adH1[j]*adH1[j] + adG1[j]*adG1[j];
		adZ[0][1] += adH1[j]*adH2[j] + adG1[j]*adG2[j];
		adZ[0][2] += adH1[j]*adH3[j] + adG1[j]*adG3[j];

		adZ[1][0] += adH2[j]*adH1[j] + adG2[j]*adG1[j];
		adZ[1][1] += adH2[j]*adH2[j] + adG2[j]*adG2[j];
		adZ[1][2] += adH2[j]*adH3[j] + adG2[j]*adG3[j];

		adZ[2][0] += adH3[j]*adH1[j] + adG3[j]*adG1[j];
		adZ[2][1] += adH3[j]*adH2[j] + adG3[j]*adG2[j];
		adZ[2][2] += adH3[j]*adH3[j] + adG3[j]*adG3[j];
	}

	adColumnC[0] = 1.0;
	adColumnC[1] = 1.0;
	adColumnC[2] = 1.0;

	iSolve = _Solve( adZ, (double*) &adColumnC, (double*) &adSolutionB, 3, 3 );

	rdDOPJoin = sqrt( adZ[0][0] + adZ[1][1] + adZ[2][2] );

   
	if( adH1 )
	{
		delete[] adH1;
		adH1 = NULL;
	}

	if( adH2 )
	{
		delete[] adH2;
		adH2 = NULL;
	}
	
	if( adH3 )
	{
		delete[] adH3;
		adH3 = NULL;
	}

	if( adG1 )
	{
		delete[] adG1;
		adG1 = NULL;
	}

	if( adG2 )
	{
		delete[] adG2;
		adG2 = NULL;
	}
	
	if( adG3 )
	{
		delete[] adG3;
		adG3 = NULL;
	}

	return dRet;
}

//***********************************************************************************************

double CEMSWLSxyz406::_HDOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts)
{
	double dHDOP = 0.0;

	EMSTIMECOORDD vCoord;

	CEMSCoordSystem oCoordSys;

	EMSVECTORD vGLoc = oCoordSys.ToEarthFixedDouble( location );

	double* adH1 = NULL;
	double* adH2 = NULL;

	if( nPts )
	{
		adH1 = new double[nPts];
		adH2 = new double[nPts];

	}

	memset(adH1, 0, nPts*sizeof(double) );
	memset(adH2, 0, nPts*sizeof(double) );

	double dSinLongitude = sin( location.degLongitude * c_dDegToRad );
	double dCosLongitude = cos( location.degLongitude * c_dDegToRad );
	double dSinLatitude  = sin( location.degLatitude * c_dDegToRad );
	double dCosLatitude  = cos( location.degLatitude * c_dDegToRad );
	double dRange;

	EMSVECTORD vDiffRadius;

	for ( ULONG i = 0; i < (ULONG)nPts ; i++ )
	{
		switch ( lpDATA[i].extras.SatTPVC.coordSystem )
		{
			case COORDSYS_EarthFixed:
				memset( &vCoord, 0, sizeof( vCoord ) );

				vCoord.vTime = lpDATA[i].extras.SatTPVC.vTime;

				vCoord.coord.radius = vGLoc;

				vCoord.coord.velocity = oCoordSys.EarthFixedVelocity( vGLoc );
				break;

			case COORDSYS_Inertial:
				vCoord = oCoordSys.EarthFixedToInertial( vGLoc, lpDATA[i].extras.SatTPVC.vTime );
				break;

			default:
				break;
		}



		vDiffRadius = CEMSVector::Sub( lpDATA[i].extras.SatTPVC.coord.radius , vCoord.coord.radius );

		dRange = sqrt( CEMSVector::DotProduct( vDiffRadius, vDiffRadius ) );


		// Rotate vectors into North, East, Up coordinates


		adH1[i] = -( ( dSinLatitude * dCosLongitude * vDiffRadius.dX ) +
					 ( dSinLatitude * dSinLongitude * vDiffRadius.dY ) -
					 ( dCosLatitude * vDiffRadius.dZ ) ) / dRange;

		adH2[i] = ( ( -dSinLongitude * vDiffRadius.dX ) +
					( dCosLongitude * vDiffRadius.dY ) ) / dRange;


	}


	double adZ[4][4]; 
	memset( &adZ, 0, 4*4*sizeof(double) );

	for( int j = 0; j < nPts; j++ )
	{
		adZ[0][0] += adH1[j]*adH1[j];
		adZ[0][1] += adH1[j]*adH2[j];

		adZ[1][0] += adH2[j]*adH1[j];
		adZ[1][1] += adH2[j]*adH2[j];
	}

	// Inverse of 2x2 Matrix
	double det = adZ[0][0] * adZ[1][1] - adZ[0][1] * adZ[1][0];

	dHDOP = sqrt( (adZ[1][1] + adZ[0][0]) / det ); 

   
	if( adH1 )
	{
		delete[] adH1;
		adH1 = NULL;
	}

	if( adH2 )
	{
		delete[] adH2;
		adH2 = NULL;
	}
	
	return dHDOP;
}

//***********************************************************************************************

void CEMSWLSxyz406::_CheckSATLUT( LPEMSWLSCONTROL lpControl, LPEMSCALIB406DATAEXT lpData, int nPts )  
{

	bool bValid = false;
	ULONG ulSatID;
	ULONG ulLutID; 

	for ( int i = 0; i < nPts; i++ )
	{
		
		bValid = false;
		ulSatID = lpData[i].calib406.hdr.id.ulSatID;
		ulLutID = lpData[i].calib406.hdr.id.ulLutID;

		bValid = ( (ULONG)lpControl->iRemoveSAT == ulSatID || (ULONG)lpControl->iRemoveLUT == ulLutID );

		if ( bValid )
		{
			lpData[i].extras.dwProcessFlags = 0;
		}
	}
	return;	
}

//***********************************************************************************************


int	CEMSWLSxyz406::_SatelliteCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag )
{

	int nNumSatellites = 0;

	if ( lpDATA && nPts )
	{

		ULONG* lpSAT = new ULONG[nPts];

		memset(lpSAT,0, sizeof(ULONG) * nPts );


		for ( int i = 0; i < nPts; i ++ )
		{

			if ( !bUsedFlag || _TestMask( &lpDATA[i], EMS_C406PF_PROCESS_MASK ) )
			{

				ULONG testSAT = lpDATA[i].calib406.hdr.id.ulSatID;
				bool bSAT = false;

				for ( int j = 0; j < nNumSatellites; j ++ )
				{
					if ( testSAT == lpSAT[j] ) bSAT = true;
				}
				
				if ( !bSAT )
				{
					lpSAT[nNumSatellites] = testSAT;
					nNumSatellites++;
				}
			}
		
		}

		if ( lpSAT )
		{
			delete [] lpSAT;
			lpSAT = 0;
		}
	}
	

	return nNumSatellites;
}

//***********************************************************************************************

void CEMSWLSxyz406::_ResetFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag )
{
	if ( lpData )
	{
		lpData->extras.dwProcessFlags &= ~dwFlag;
	}
}

void CEMSWLSxyz406::_SetFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag )
{
	if ( lpData )
	{
		lpData->extras.dwProcessFlags |= dwFlag;
	}
}

bool CEMSWLSxyz406::_TestFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag )
{
	bool bSet = false;

	if ( lpData )
	{
		bSet = ( dwFlag == ( dwFlag & lpData->extras.dwProcessFlags ) );
	}
	return bSet;
}

bool CEMSWLSxyz406::_TestMask( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag )
{
	bool bSet = false;

	if ( lpData )
	{
		bSet = ( 0 != ( dwFlag & lpData->extras.dwProcessFlags ) );
	}
	return bSet;
}

//***********************************************************************************************

EMS_RESULT CEMSWLSxyz406::_DetermineManualLocation( LPEMSWLSCONTROL	lpWLSControl, LPEMSCALIB406DATAEXT lpDataExt, int nCount,
													LPEMSLOCATE lpSolnOutput, int& nSolutions, int iMaxSolutions )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpDataExt && nCount )
	{
		int nPtsUsed = nCount, nBursts = 0;

		m_wProcessDataType = lpWLSControl->wProcessDataType;
		
		nSolutions = 0;

		nBursts = _TimeFreqInitialEstimate( lpDataExt, nCount );

		if ( ( hr == EMS_OK ) && lpDataExt )
		{
			if ( nPtsUsed )
			{
				CEMSCoordSystem COORD;
				EMSWLSLOCATE	solnINA, solnINB;
				EMSLOCATE		solnA, solnB;
				EMSVECTORD		Bvector;
				EMSVECTORD		Svector;
				int				nVariableFlag = 0;
				int				count406 = 0;
				ULONG			ulSatIDUsed = 0;
				ULONG			ulSatID = 0;

				memset( &solnINA, 0, sizeof(solnINA) );
				memset( &solnINB, 0, sizeof(solnINB) );
				memset( &solnA,   0, sizeof(solnA) );
				memset( &solnB,   0, sizeof(solnB) );
				memset( &Bvector, 0, sizeof( EMSVECTORD ) );
				memset( &Svector, 0, sizeof( EMSVECTORD ) );

				// Generate Initial Estimate and relevent Satellite vectors
				SetInitialSolution( &solnINA );

				solnINA.wNumMsgs = nPtsUsed;

				// Establish initial estimate based upon all unique satellites
		
				int nSatellites = _SatelliteUsedCount( lpDataExt, nCount );
		
				bool bNewSat = true;

				for ( int i = 0; i < nCount; i++ )
				{
					if ( _TestMask( &lpDataExt[i], EMS_C406PF_ACCEPT_MASK ) )
					{
						count406++;
						ulSatID = lpDataExt[i].calib406.hdr.id.ulSatID;
						bNewSat = true;
			
						for ( int j = 0; j < i; j++ )
						{
							if ( _TestMask( &lpDataExt[j], EMS_C406PF_ACCEPT_MASK ) )
							{
								if ( ulSatID == lpDataExt[j].calib406.hdr.id.ulSatID )
								{
									bNewSat = false;
									break;
								}
							}
						}
						if ( bNewSat ) 
						{
							Svector = CEMSVector::Normalize( lpDataExt[i].extras.SatTPVC.coord.radius );
							Bvector = CEMSVector::Add( Bvector, Svector  );
						}
					}
				}

				if ( count406 > 0 )
				{
					Bvector = CEMSVector::Normalize( Bvector );
					Bvector = CEMSVector::Mult( Bvector, c_dEarthKmRadius ); 

					solnINA.location = COORD.ToGeodetic( Bvector );
					solnINA.location.fAltitude = 0.0;
				}


				try
				{

					// Single Burst Processing (Assumes data in time/burst order)
					solnINA.dFrequency = MeanTxFrequency( lpDataExt, nCount );
					
					solnA.wType = EMSLOCTYPE_DETECT_ONLY;

					// Process only the last 30 bursts (max)
					int iStartBurst = 0;
					if ( nBursts > 30 ) iStartBurst = nBursts - 30;

					for ( int i = 0/*iStartBurst*/; (i < nBursts) && (nSolutions < iMaxSolutions - 1); i++ )
					{
						memset( &solnA, 0, sizeof(solnA) );

						solnA.wType = EMSLOCTYPE_DETECT_ONLY;
						
						ULONG ulBurstIndex = 0;
						ULONG ulBurstCount = 0;
						int nSatellitesSingleBurst = 0;
						
						bool bExist = _FindBurst( lpDataExt, nCount, i+1, &ulBurstIndex, &ulBurstCount );

						if ( bExist )
						{
							// Single Burst with 3 or more satellites
							if ( ulBurstCount > 2 )
							{
								nSatellitesSingleBurst = _SatelliteUsedCount( &lpDataExt[ulBurstIndex], (int)ulBurstCount );
								
								if ( nSatellitesSingleBurst > 2 )
								{

									char           sKind[16];

									solnINA.location.fAltitude  = 0.0;

									sprintf( sKind, "A side" );

									solnA.wlsSolution.wNumBurstsUsed = 1;
									solnA.wlsSolution.wNumMsgs = ulBurstCount;

									hr = _WLSLocation( sKind, &lpDataExt[ulBurstIndex], ulBurstCount, lpWLSControl,
																&solnINA, &solnA.wlsSolution );
									
									solnA.fProbability = (float) COORD.DistanceApart( solnA.wlsSolution.location, solnINA.location );
									
 									hr = _ProcessLocationManual( &solnA, &lpDataExt[ulBurstIndex], (int)ulBurstCount );

									lpSolnOutput[nSolutions++] = solnA;

								}
							}

					
						}
					} // End of 'exist' test for beacon burst

				

					// ******************** All bursts Location Processing ***************

					if( nBursts > 1)
					{
						// Process 'A' side
						//hr = _ProcessSide( EMSLOCTYPE_A_SIDE, ulSatIDUsed, &solnINA,
						//				   lpDataExt, nCount, nVariableFlag, &solnA );
						
						char           sKind[16];

						solnINA.location.fAltitude  = 0.0;

						sprintf( sKind, "A side" );

						solnA.wlsSolution.wNumBurstsUsed = nBursts;
						solnA.wlsSolution.wNumMsgs = nCount;

						hr = _WLSLocation( sKind, lpDataExt, nCount, lpWLSControl,
													&solnINA, &solnA.wlsSolution );
									
						solnA.fProbability = (float) COORD.DistanceApart( solnA.wlsSolution.location, solnINA.location );

						// Determine remaining parameters of location record(s) and output
						hr = _ProcessLocationManual( &solnA, lpDataExt, nCount );
															
						lpSolnOutput[nSolutions++] = solnA;


					}
									


				}
				catch( ... ) 
				{
					throw;
				}
			}			
	

		}
	}
	return hr;
}

WORD CEMSWLSxyz406::_LocationType ( LPEMSCALIB406DATAEXT lpData, int nPts )
{

	WORD wType           = 0;
	WORD wTypeProcessed  = 0;
	WORD wTypeDetectOnly = 0;
	int  nPtsProcessed   = 0;


	if ( lpData && nPts > 0 )
	{
		for ( int i = 0; i < nPts; i++ )
		{
			
			if ( _TestMask( &lpData[ i ], EMS_C406PF_PROCESS_MASK ) )
			{
				if ( _TestFlag( &lpData[ i ], EMS_C406PF_PROCESS_TDOA_FLAG ) ) wTypeProcessed |= EMSLOCTYPE_TDOA;
				if ( _TestFlag( &lpData[ i ], EMS_C406PF_PROCESS_FDOA_FLAG ) ) wTypeProcessed |= EMSLOCTYPE_FDOA;
			
				wTypeProcessed |= lpData[i].calib406.hdr.wType;

				nPtsProcessed++;

			}
		
			wTypeDetectOnly |= lpData[i].calib406.hdr.wType;

		}

		if ( nPtsProcessed )
		{
			wType = wTypeProcessed;
		}
		else
		{
			wType = wTypeDetectOnly;
		}

		// Assume SARR data type if frequency flag not set
		if( !( wType & 0x20 ) )
			wType = wType | EMSCALIBTYPE_406_SARR;
	}


	return wType;
}


//***********************************************************************************************

bool CEMSWLSxyz406::_FindBurst( LPEMSCALIB406DATAEXT lpData, int nPts, int nBurstNumber,
									ULONG *ulBurstIndex, ULONG *ulBurstCount )
{

	bool bExist = false;
	int nBurstCount = 0;
	int nBurstIndex = -1;

	if ( lpData && nPts > 0 )
	{
		for( int i = 0; i < nPts; i++ )
		{
			if ( nBurstNumber == lpData[i].extras.wBurstNumber )
			{
				if ( nBurstIndex < 0 ) nBurstIndex = i;

				// Check if data is to be processed
				if ( _TestMask( &lpData[i], EMS_C406PF_PROCESS_MASK ) )	nBurstCount++;

			}
		}

		if ( nBurstCount > 0 )
		{
			bExist = true;
		}
	}

	if ( nBurstIndex < 0 ) nBurstIndex = 0;

	*ulBurstCount = (ULONG)nBurstCount;
	*ulBurstIndex = (ULONG)nBurstIndex;


	return( bExist );
}
//***********************************************************************************************

//***********************************************************************************************

EMS_RESULT CEMSWLSxyz406::_ProcessLocationManual( LPEMSLOCATE lpLocateA, LPEMSCALIB406DATAEXT lpDataExt, int nCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpLocateA  && lpDataExt && nCount )
	{
		CEMSCoordSystem COORD;
		EMSLOCATE		locateSideA;
		INT64			i64TimeFirst, i64TimeLast;
		int				nVariableFlag = 0;
		ULONG			ulSatIDUsed = 0;
		ULONG			ulLutIDUsed = 0;
		bool			bMultiPass = false;
		int				nSatsUsed=0;

		// Allow long time interval constraint for MEO satellites
		double			dOutsideSeconds = 600.0;

		memset( &locateSideA, 0, sizeof( locateSideA ) );
		locateSideA.wlsSolution = lpLocateA->wlsSolution;
											
		locateSideA.wType = _LocationType ( lpDataExt, nCount );

		Sleep( 2 ); // want to ensure time resolution

		locateSideA.time = c_sysClock.GetTime( );

		// iterate through the records encoding satellite and lut IDs
		// as well need to know what kinds of records were used in the solution
		
		// Ensure that the "new format" flag is set by calling Reset.
		CEMSEncodedSatID::Reset( (EMSENCODEDSATID*)&locateSideA.cSatIDs );
		CEMSEncodedLutID::Reset( (EMSENCODEDLUTID*)&locateSideA.cLutIDs );

		double dPower = 0.0;
		int   nPtsUsed = 0;
		i64TimeFirst = lpDataExt[0].calib406.timeMsg.intTime;
		i64TimeLast  = lpDataExt[nCount-1].calib406.timeMsg.intTime;
		WORD wBitErrorField1=0xFFFF, wBitErrorField2=0xFFFF, wBitErrorFrameSync=0;
		BYTE cBeaconMsg[ 18 ];
		memset( cBeaconMsg, 0, sizeof( cBeaconMsg ) );
		bool bNormalFS = false;
		bool bInvertedFS = false;

		for ( int i = 0; i < nCount; i++ )
		{
			if ( _TestMask( &lpDataExt[i], EMS_C406PF_PROCESS_MASK ) )
			{
				// most recent satellite used 
				ulSatIDUsed = lpDataExt[i].calib406.hdr.id.ulSatID;
				ulLutIDUsed = lpDataExt[i].calib406.hdr.id.ulLutID;

				if( lpDataExt[ i ].calib406.cBeaconMsg[2] == 0x2F )
				{
					bNormalFS = true;
				}
				if( lpDataExt[ i ].calib406.cBeaconMsg[2] == 0xD0 )
				{
					bInvertedFS = true;
				}

				// Find best message
				if ( ( wBitErrorField1 > lpDataExt[i].calib406.wBitErrorField1 )
					&& ( wBitErrorField2 > lpDataExt[i].calib406.wBitErrorField2 ) )
				{
					memcpy( cBeaconMsg, lpDataExt[ i ].calib406.cBeaconMsg, sizeof( cBeaconMsg ) );
					wBitErrorField1 = lpDataExt[i].calib406.wBitErrorField1;
					wBitErrorField2 = lpDataExt[i].calib406.wBitErrorField2;
					wBitErrorFrameSync = lpDataExt[i].calib406.wBitErrorFrameSynch;

				}
				CEMSEncodedSatID::Set( (EMSENCODEDSATID*)&locateSideA.cSatIDs, ulSatIDUsed );

				CEMSEncodedLutID::Set( (EMSENCODEDLUTID*)&locateSideA.cLutIDs, ulLutIDUsed );

				if ( lpDataExt[i].calib406.timeMsg.intTime > i64TimeLast )
					i64TimeLast  = lpDataExt[i].calib406.timeMsg.intTime;
				if ( lpDataExt[i].calib406.timeMsg.intTime < i64TimeFirst )
					i64TimeFirst = lpDataExt[i].calib406.timeMsg.intTime;

	
				nPtsUsed++;
				dPower += lpDataExt[i].calib406.dCarrierPower;

				// Check if GEO satellite used in solution
				if ( ( ulSatIDUsed > 200 ) && ( ulSatIDUsed < 300 ) )
				{
					locateSideA.wType |= EMSLOCTYPE_406_GEO;
				}

				locateSideA.wType |= lpDataExt[i].calib406.hdr.wType;


			}
		}

		locateSideA.fPower = (float) (dPower / nPtsUsed);

		locateSideA.i64BeaconID = lpDataExt[0].calib406.i64BeaconID;

		locateSideA.ulLutID = 9999;

		locateSideA.timeFirstData.intTime = i64TimeFirst;
		locateSideA.timeLastData.intTime  = i64TimeLast;

		locateSideA.info.rec406.wBitErrorField1 = wBitErrorField1;
		locateSideA.info.rec406.wBitErrorField2 = wBitErrorField2;
		locateSideA.info.rec406.wBitErrorFrameSync = wBitErrorFrameSync;
		memcpy( locateSideA.info.rec406.cBeaconMsg, cBeaconMsg, sizeof( cBeaconMsg ) );

		if( bNormalFS &&  bInvertedFS )
		{
			locateSideA.wType |= EMSLOCTYPE_ABGEN;
			locateSideA.info.rec406.cBeaconMsg[2] = 0x2F;
		}

		// if the solution didn't converge, treat it as DETECT_ONLY
		if (   ( locateSideA.wlsSolution.wNumIterations & 0x8000 )
			|| ( locateSideA.wlsSolution.wNumMsgsUsed == 0 ) )
		{
			locateSideA.wType |= EMSLOCTYPE_DETECT_ONLY;	
		}


		locateSideA.ulSatPassID = lpDataExt[nCount-1].calib406.ulPassID;

		locateSideA.fConfidence = 0.0;

		locateSideA.fCrossTrackAngle = -1.0;		

		
		*lpLocateA = locateSideA;
	}
	return hr;
}
	
//***********************************************************************************************


int CEMSWLSxyz406::_TimeFreqInitialEstimate( LPEMSCALIB406DATAEXT lpDATA, int nPts )
{
	int nBursts = 0;

	// list is in Beacon, Sat , Time order so just compare with last unique point 

	if ( lpDATA && nPts )
	{
		CEMSTime lastTime( 0 );
		INT64	i64BurstTime		= 0;
		int		i;
		int		nGEOpts				= 0;
		int		nMEOpts				= 0;
		int		nLEOpts				= 0;
		double	dGEOBurstFrequency	= 0.0;
		double	dMEOBurstFrequency	= 0.0;
		double	dLEOBurstFrequency	= 0.0;
		double	dBurstFrequency		= 0.0;
		double	dSecs				= 0.0;

		ULONG	ulLastSatID			= 0;
		ULONG	ulSatID				= 0;
		int		nLastIndex			= 0;
		int		nDuplicates			= 0;

		DWORD	dAllFlags = ( EMS_C406PF_ACCEPT_TIME_FLAG | EMS_C406PF_ACCEPT_FREQ_FLAG
							| EMS_C406PF_PROCESS_TIME_FLAG | EMS_C406PF_PROCESS_FREQ_FLAG );

		// Set all flags		
		for ( i = 0; i < nPts; i++ )
		{
			_SetFlag( &lpDATA[i], dAllFlags );
		}

		
		// Find and remove duplicate records (if any)
		// Assumes data in time order


		for ( i = 0; i < nPts; i++ )
		{
			ulSatID		= lpDATA[i].calib406.hdr.id.ulSatID;

			dSecs = lastTime.SecondsDifferent( lpDATA[i].calib406.timeMsg );
			
			// Check for duplicate records and remove them
			if ( ( fabs( dSecs ) < c_dDeltaSecondsIfUnique )
				&& ( ulSatID == ulLastSatID ) )
			{
				// Save data with largest CNR
				if ( lpDATA[i].calib406.dCarrierPower > lpDATA[nLastIndex].calib406.dCarrierPower )
				{
					_ResetFlag( &lpDATA[nLastIndex], dAllFlags );
					nLastIndex = i;
					lastTime.SetTime ( lpDATA[i].calib406.timeMsg );
					ulLastSatID = ulSatID;
				}
				else
				{
					_ResetFlag( &lpDATA[i], dAllFlags );
				}
				// Negate all flags
				nDuplicates++;
			}
			else
			{
				nLastIndex = i;
				lastTime.SetTime ( lpDATA[i].calib406.timeMsg );
				ulLastSatID = ulSatID;
			}
		}

		// Check for SARP records and negate all time flags
		for ( i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
			{
				// Reset time flags if SARP record type
				if ( EMSCALIBTYPE_406_SARP == lpDATA[i].calib406.hdr.wType )
				{
					_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG );
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
				}
			}
		}

		// Check for SARR invalid time records and negate all time flags
		for ( i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
			{
				if ( EMSCALIBTYPE_406_SARR == lpDATA[i].calib406.hdr.wType )
				{
					// Reset time flags if SARR invalid time record
					if ( EMS_C406RF_TIMERES_UKN == (lpDATA[i].calib406.dwResolutionFlags && '1xF' ))
					{
						_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG );
						_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
					}
				}
			}
		}

/*
		// Check for GEO records and negate all frequency flags
		for ( i = 0; i < nPts; i++ )
		{
			if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
			{
				ulSatID = lpDATA[i].calib406.hdr.id.ulSatID;
				
				// Check for GEO records and reject all DOPPLER frequency processing
				if ( _IsGEO( ulSatID ) )
				{
					_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG );
					_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
				}
			}
		}
*/
		// Compute expected transmit frequency using all measurements
		for ( i = 0; i < nPts; i++ )
		{
			ulSatID = lpDATA[i].calib406.hdr.id.ulSatID;

			if ( _IsGEO( ulSatID ) )
			{
				dGEOBurstFrequency += lpDATA[i].calib406.dFrequency;
				nGEOpts++;
			}
			else if ( _IsMEO( ulSatID ) )
			{
				dMEOBurstFrequency += lpDATA[i].calib406.dFrequency;
				nMEOpts++;
			}
			else if ( _IsLEO( ulSatID ) )
			{
				dLEOBurstFrequency += lpDATA[i].calib406.dFrequency;
				nLEOpts++;
			}
		}

		// Use GEO measurements (if available) as best estimate of transmit frequency
		if ( nGEOpts > 0 )
			dBurstFrequency = dGEOBurstFrequency / nGEOpts;
		else if ( nMEOpts > 0 )
			dBurstFrequency = dMEOBurstFrequency / nMEOpts;
		else if ( nLEOpts > 0 )
			dBurstFrequency = dLEOBurstFrequency / nLEOpts;


		// Reset Last Time variable
		lastTime.SetTime( lpDATA[0].calib406.timeMsg );

		// Determine number of bursts
		for ( i = 0; i < nPts; i++ )
		{

			dSecs = lastTime.SecondsDifferent( lpDATA[i].calib406.timeMsg );
			
			lastTime.SetTime ( lpDATA[i].calib406.timeMsg );
			
			// Set burst number and transmit time and frequency
			if ( (fabs( dSecs ) > c_dDeltaSecondsIfUnique) || i == 0)
			{
				nBursts++;

				i64BurstTime = lpDATA[i].calib406.timeMsg.intTime;
			}
			
			lpDATA[i].extras.timeTransmit.intTime	= i64BurstTime;
			lpDATA[i].extras.dTxFrequency			= dBurstFrequency;
			lpDATA[i].extras.wBurstNumber			= nBursts;

		}

		// Find all bursts with more than one measurement from different satellites
		if ( nBursts )
		{
			int *nBurstCount = 0;
			ULONG *ulBurstSatID = 0;

			nBurstCount  = new int [nBursts];
			ulBurstSatID = new ULONG [nBursts];
			int j = 0;
			
			memset( nBurstCount, 0, nBursts * sizeof( int ) );
			memset( ulBurstSatID, 0, nBursts * sizeof( ULONG ) );

			for ( i = 0; i < nPts; i++ )
			{
				j		= lpDATA[i].extras.wBurstNumber - 1;
				ulSatID = lpDATA[i].calib406.hdr.id.ulSatID;

				if ( j < nBursts )
				{
					ulLastSatID = ulBurstSatID[ j ];

					if ( ulLastSatID != ulSatID )
					{
						nBurstCount[ j ]++;

						ulBurstSatID[ j ] = lpDATA[i].calib406.hdr.id.ulSatID;
					}
				}
			}

			// Reject all time measurements unless within the same burst
			// from different satellites and not a duplicate
			for ( i = 0; i < nPts; i++ )
			{
				if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
				{
					j = lpDATA[i].extras.wBurstNumber - 1;
					if ( j < nBursts  )
					{
						if ( nBurstCount[ j ] <= 1 )
						{
							_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG );
							_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
						}	
					}
				}
			}

			// Adjust receive times if 1 second error is detected
			for ( i = 0; i < nPts; i++ )
			{
				if ( _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG ) )
				{
					lastTime.SetTimeNano ( lpDATA[i].extras.timeTransmit.intTime );
			
					dSecs = lastTime.SecondsDifferent( lpDATA[i].calib406.timeMsg );

					if ( dSecs > 0.5 )
					{
						lpDATA[i].calib406.timeMsg.intTime -= c_iNanoSecsPerSec;
					}
					else if ( dSecs < - 0.5 )
					{
						lpDATA[i].calib406.timeMsg.intTime += c_iNanoSecsPerSec;
					}
				}
			}			
			
			
			// Reject all GEO frequency measurements unless within the same burst
			// from different satellites and not a duplicate
			for ( i = 0; i < nPts; i++ )
			{
				if ( _IsGEO( lpDATA[i].calib406.hdr.id.ulSatID ) &&
					 _TestFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG ) )
				{
					j = lpDATA[i].extras.wBurstNumber - 1;
					if ( j < nBursts  )
					{
						if ( nBurstCount[ j ] <= 1 )
						{
							// Reject GEO frequency data if only measurement in burst
							_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG );
							_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
						}	
					}
				}
			}

	
			if ( nBurstCount )
			{
				delete [] nBurstCount;
				nBurstCount = 0;
			}
			
			if ( ulBurstSatID )
			{
				delete [] ulBurstSatID;
				ulBurstSatID = 0;
			}

		}


		// Check TDOA process data type & reject all TDOA if not set
		if ( !(m_wProcessDataType & PROCESS_TDOA) )
		{
			for ( i = 0; i < nPts; i++ )
			{
				_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_TIME_FLAG );
				_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_TIME_FLAG );
			}	
		}
		// Check FDOA and/or DOPPLER process data type & reject all if not set
		// Note: FDOA and DOPPLER processing will always be performed in the absense of TDOA
		else if ( !(m_wProcessDataType & (PROCESS_FDOA | PROCESS_FREQ)) )
		{
			for ( i = 0; i < nPts; i++ )
			{
				_ResetFlag( &lpDATA[i], EMS_C406PF_ACCEPT_FREQ_FLAG );
				_ResetFlag( &lpDATA[i], EMS_C406PF_PROCESS_FREQ_FLAG );
			}	
		}


	}

	return nBursts;
}

	
//***********************************************************************************************

bool CEMSWLSxyz406::_IsGEO( ULONG ulSatID )
{
	bool bGEO = false;
	if ( (ulSatID > c_ulGEOSatID) && (ulSatID < c_ulMEOSatID) )
		bGEO = true;

	return bGEO;
}
bool CEMSWLSxyz406::_IsMEO( ULONG ulSatID )
{
	bool bMEO = false;
	if ( ulSatID > c_ulMEOSatID )
		bMEO = true;

	return bMEO;
}
bool CEMSWLSxyz406::_IsLEO( ULONG ulSatID )
{
	bool bLEO = false;
	if ( ulSatID < c_ulGEOSatID )
		bLEO = true;

	return bLEO;
}

//***********************************************************************************************
