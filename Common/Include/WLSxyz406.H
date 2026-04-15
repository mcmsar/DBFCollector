/********************************************************************
*	Module:			wlsxyz406.h
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

	0.0 01/11/2010	    R.Renner	start

********************************************************************/
#ifndef INC_WLSXYZ406
#define INC_WLSXYZ406

#include <stdio.h>
#include "emspipe.h"
#include "emserror.h"
#include "locate.h"
#include "WLSxyzTypes406.h"
#include "emsorbit.h"
#include "emsexcpt.h"
#include "calib406ext.h"

class CEMSWLSxyz406
{
public:
	CEMSWLSxyz406();
	virtual ~CEMSWLSxyz406();	

	inline void SetExceptionPointer( CEMSException *lpException ) { m_lpException = lpException; } 
	void Reset( void );
	HRESULT SetDefaultControlValues( EMSWLSCONTROL *lpControl );
	HRESULT SetInitialSolution( EMSWLSLOCATE *lpSolution, double dLatitude=0.0, double dLongitude=0.0 );

	HRESULT _WLSLocation( char *pKind, LPEMSCALIB406DATAEXT lpDATA, int nPts, 
				EMSWLSCONTROL *lpControl,
				EMSWLSLOCATE *lpSOLN_IN, LPEMSWLSLOCATE lpSOLN_OUT ); 
	HRESULT _WLSLocationSingleBurst( char *pKind, LPEMSCALIB406DATAEXT lpDATA, int nPts, 
				EMSWLSCONTROL *lpControl, EMSWLSLOCATE *lpSolnIN, LPEMSWLSLOCATE lpsolnOUT ); 

	EMS_RESULT _ProcessSingleBurstManual( ULONG ulSatID, LPEMSWLSLOCATE lpSolnIN,
											LPEMSCALIB406DATAEXT  lpDATA, int   nCount,
											int nVariableFlag, LPEMSLOCATE lpSoln );
	EMS_RESULT _ProcessLocationManual( LPEMSLOCATE lpLocateA, LPEMSCALIB406DATAEXT lpDataExt, int nCount );
	int _TimeFreqInitialEstimate( LPEMSCALIB406DATAEXT lpDATA, int nPts );

	int _BurstCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag=false );
	int _BurstUsedCount( LPEMSCALIB406DATAEXT lpDATA, int nPts )
						{ return _BurstCount( lpDATA, nPts, true ); }
	bool _FindBurst( LPEMSCALIB406DATAEXT lpData, int nPts, int nBurstNumber,
									ULONG *ulBurstIndex, ULONG *ulBurstCount );


	int _UniqueCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag=false );
	int _UniqueUsedCount( LPEMSCALIB406DATAEXT lpDATA, int nPts )
						{ return _UniqueCount( lpDATA, nPts, true ); }

	int	_SatelliteCount( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bUsedFlag );
	int _SatelliteUsedCount( LPEMSCALIB406DATAEXT lpDATA, int nPts )
						{ return _SatelliteCount( lpDATA, nPts, true ); }


	EMS_RESULT _DetermineManualLocation( LPEMSWLSCONTROL lpWLSControl, LPEMSCALIB406DATAEXT lpDataExt, int nCount,
										 LPEMSLOCATE lpSolnOutput, int& nSolutions, int iMaxSolutions );

	HRESULT _PartialDerivatives( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSWLSCONTROL *lpControl,
				LPEMSWLSLOCATE SOLN, LPEMSPARTIALDERVATIVE PDfreq, LPEMSPARTIALDERVATIVE PDtime );

	void SetTracerFilePointer( FILE **lplpTracerFile )	{ m_lplpTracerFile = lplpTracerFile; }
	void SetTracingLevelPointer( long *lpTracingLevel )	{ m_lpTracingLevel = lpTracingLevel; }

	HRESULT GetMeshResiduals( LPEMSCALIB406DATAEXT lpDATA, int nPts, 
							LPEMSWLSLOCATE lpSOLN1, LPEMSWLSLOCATE lpSOLN2,
							double dAngle, int nXcells, int nYcells = 0 );
	
	HRESULT GetResiduals( EMSLOCATION location, double dTxFrequency, LPEMSCALIB406DATAEXT lpDATA, int nPts );

	EMS_RESULT GetTcaCta( EMSLOCATION location,  ULONG ulSatID, LPEMSCALIB406DATAEXT lpDATA,
							int nPts, LPEMSTCACTA lpTcaCta );
	
	bool IsMultiPass( LPEMSCALIB406DATAEXT lpDATA, int nPts, bool bOnlyIfUsed=false );

	double ElevationAngle( EMSVECTORD SatVector, EMSVECTORD BeaVector )
		{ return _ElevationAngle( SatVector, BeaVector); }

	//int ElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, LPEMSWLSLOCATE lpSOLN )
	//				{ return _ElevationTest( lpDATA, nPts, lpSOLN ); }
	int ElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSLOCATION vLOC )
					{ return _ElevationTest( lpDATA, nPts, vLOC ); }

	double MeanTxFrequency( LPEMSCALIB406DATAEXT lpData, int nPts );

private:	// methods

	bool _TestMask( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag );
	bool _TestFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag );
	void _SetFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag );
	void _ResetFlag( LPEMSCALIB406DATAEXT lpData, DWORD dwFlag );

	double _Det3x3( double dA[MAXVARIABLES][MAXVARIABLES] );

	int _Solve( double dA[MAXVARIABLES][MAXVARIABLES], double *pdColumnC, 
				double *pdSolutionB, int M, int N );
	int _SummaryStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,
				double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend );
	int _SummaryFreqStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,
				double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend );
	int _SummaryTimeStatistics ( int iOption, LPEMSCALIB406DATAEXT lpDATA, int nPts,
				double *pdRMS, double *pdMean, double *pdStdDev, double *pdTrend );
	int _ProcessFreqFlags ( EMSWLSCONTROL *lpControl, LPEMSCALIB406DATAEXT lpDATA,
				int nPts, double dMean, double dStdDev, int nMinThresholdPts );
	int _ProcessTimeFlags ( EMSWLSCONTROL *lpControl, LPEMSCALIB406DATAEXT lpDATA,
				int nPts, double dMean, double dStdDev, int nMinThresholdPts );
	int _WLSinit( EMSWLSCONTROL *lpControl, LPEMSCALIB406DATAEXT DATA, int nPts, double *dX,
				double *ddXMax, double *ddXMin );
	int _WLSxyzfill( EMSWLSCONTROL *lpControl, EMSVECTORD  vPosXYZ, LPEMSCALIB406DATAEXT DATA, 
				int nPts, int nBursts, double *dB, double dA[MAXVARIABLES][MAXVARIABLES] );

	int _FindCentralPoint( LPEMSCALIB406DATAEXT lpDATA, int nPts, int nStartIndex,
								EMSLOCATION locEstimate, DWORD dwFlags );

	int _GenerateSolutionIndex ( EMSWLSCONTROL *lpControl );

	HRESULT _UpdateSolution( EMSVECTORD vBEACON, EMSWLSCONTROL *lpControl,
				LPEMSWLSLOCATE lpSOLN );
	HRESULT _UpdateSolutionErrors( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSTCACTA *lpTcaCta,
                double dStdDev, double dA[MAXVARIABLES][MAXVARIABLES], 
				EMSWLSCONTROL *lpControl, LPEMSWLSLOCATE lpSOLN );

	HRESULT _GetResiduals( EMSVECTORD vLoc, double dTxFrequency, LPEMSCALIB406DATAEXT lpDATA, int nPts); 

	double _ElevationAngle( EMSVECTORD SatVector, EMSVECTORD BeaVector );
	int _ElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSLOCATION vLOC );
	int _ProcessFlagElevationTest( LPEMSCALIB406DATAEXT lpDATA, int nPts, EMSLOCATION vLOC );
	bool _IsMultiPass( LPEMSCALIB406DATAEXT lpDATA, int nPts );

	int _FreqThreshold( LPEMSCALIB406DATAEXT lpDATA, int nPts, double dMean, double dThreshold );
	int _TimeThreshold( LPEMSCALIB406DATAEXT lpDATA, int nPts, double dMean, double dThreshold );
	int _SetProcessFlags( LPEMSCALIB406DATAEXT lpDATA, int nPts );

	int _RemoveBurstMaxResiduals( LPEMSCALIB406DATAEXT lpDATA, int nPts );

	double _DOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts, int nRefsat,
							 double& rdDOPFdoa, double& rdDOPTdoa, double& rdDOPJoin );

	double _HDOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts);

	double _GDOP(EMSLOCATION location,LPEMSCALIB406DATAEXT lpDATA, int nPts, int nTimePts );

	double _ConvertTOAFOA2Km( double dTOAsec, double dFOAhz );

	void _CheckSATLUT( LPEMSWLSCONTROL lpControl, LPEMSCALIB406DATAEXT lpData, int nPts );
	
	double _DetNxN( double dA[MAXVARIABLES][MAXVARIABLES], int N );

	bool _IsGEO( ULONG ulSatID );
	bool _IsMEO( ULONG ulSatID );
	bool _IsLEO( ULONG ulSatID );

	WORD _LocationType ( LPEMSCALIB406DATAEXT lpData, int nPts );


private: // data
	FILE			**m_lplpTracerFile;
	long			*m_lpTracingLevel;
	bool			m_bConverged;
	bool			m_bFDOAdata;
	double			m_dFreqWeight;
	double			m_dTimeWeight;
	WORD			m_wProcessDataType;
	CEMSException  	*m_lpException;
};

#endif	// INC_WLSXYZ406

