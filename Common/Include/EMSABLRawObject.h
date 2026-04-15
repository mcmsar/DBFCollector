/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __EMS_RAW_LOCATION_OBJECT_H__
#define __EMS_RAW_LOCATION_OBJECT_H__


#include "aobjbase.h"
#include "logclient.h"
#include "CriticalSection.h"
#include "ablobject.h"
#include <list>

#include <cmath>
#include "emsconst.h"

#define SIND(a)		   (sin(a * c_dDegToRad))
#define SIND(a)		   (sin(a * c_dDegToRad))
#define COSD(a)        (cos(a * c_dDegToRad))
#define ATAND(a)       (c_dRadToDeg * atan(a))
#define ATAN2D(a,b)    (c_dRadToDeg * atan2(a,b))


//! @class CEMSABLRawObject
//! Encapsulates EMSABLRawData record.
class CEMSABLRawObject : public CApiObjBase
{
public:
	CEMSABLRawObject();
	CEMSABLRawObject( const EMSABLRawData& cABLRawData );
	CEMSABLRawObject( const EMSLOCATE& cemsLocate );
	CEMSABLRawObject( const CEMSABLRawObject& coRawLocationObj );
	virtual ~CEMSABLRawObject();

	void SetRawData( const EMSLOCATE& cemsLocate )
	{ 
		memcpy( &m_ABLRawData.locate, &cemsLocate, sizeof( EMSLOCATE ) );
		m_ABLRawData.dwStatus = 0;
		m_dVLAT = 0.0;
		m_dVLONG = 0.0;
		m_dCLALO = 0.0;
	}

	void GetRawData( EMSABLRawData& emsRawData ){ memcpy( &emsRawData, &m_ABLRawData, sizeof( EMSABLRawData ) );}
	void GetLocateData( EMSLOCATE& emsLocate ){ memcpy( &emsLocate, &(m_ABLRawData.locate), sizeof( EMSLOCATE ) );}

	void Reset(){ memset( &m_ABLRawData, 0, sizeof( EMSABLRawData ) );}

	EMSTIME GetTimestamp(){ return m_ABLRawData.locate.time;}
	EMSTIME GetTimeFirstData(){ return m_ABLRawData.locate.timeFirstData;}
	EMSTIME GetTimeLastData(){ return m_ABLRawData.locate.timeLastData;}
	EMSTIME GetTCA(){ return m_ABLRawData.locate.timeTCA;}

	INT64 GetBeaconID(){ return m_ABLRawData.locate.i64BeaconID;}

	ULONG GetLUTID(){ return m_ABLRawData.locate.ulLutID;}
	ULONG GetPassID(){ return m_ABLRawData.locate.ulSatPassID;}
	
	ULONG GetFirstSATID();
	void  GetSATIDs( std::list<ULONG>& lstSATIds );

	ULONG GetFirstLUTID();
	void  GetLUTIDs( std::list<ULONG>& lstLUTIds );

	double GetDistanceApart( const CEMSABLRawObject& oABLRaw );

	bool   IsAged( EMSTIME time, double dAgeoutPeriod );
	bool   IsOlderThan( const CEMSABLRawObject& oABLRaw );
	bool   Is406Data(){ return ( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC );}
	bool   IsDetectOnly(){ return ( (m_ABLRawData.locate.wType & EMSLOCTYPE_DETECT_ONLY ) == EMSLOCTYPE_DETECT_ONLY );}
	bool   IsSideA(){ return !( (m_ABLRawData.locate.wType & EMSLOCTYPE_B_SIDE) == EMSLOCTYPE_B_SIDE );}
	bool   IsPeer( CEMSABLRawObject& oRawObj ){ return false;}

	void   CalculateLatLongDeltaSigma( double dOrbDetErr, double dSDEL );

	double  GetVLat(){ return m_dVLAT;}
	double  GetVLong(){ return m_dVLONG;}
	double  GetCLALO(){ return m_dCLALO;}

	WORD    GetLocationType(){ return m_ABLRawData.locate.wType;}

	ULONG   GetCountryCode();

	int     GetBcnMsgErrorCnt();
	int     GetFSErrorCnt();
	int     GetPDF1ErrorCnt();
	int     GetPDF2ErrorCnt();

	void    GetBeaconMsg( BYTE* aMsg, int iSize ){ memcpy( aMsg, m_ABLRawData.locate.info.rec406.cBeaconMsg, iSize);}
	WORD    GetBitErrorFS(){ return m_ABLRawData.locate.info.rec406.wBitErrorFrameSync;}
	WORD    GetBitErrorF1(){ return m_ABLRawData.locate.info.rec406.wBitErrorField1;}
	WORD    GetBitErrorF2(){ return m_ABLRawData.locate.info.rec406.wBitErrorField2;}

	EMSLOCATION GetLocation(){ return m_ABLRawData.locate.wlsSolution.location;}

	double  GetConfidence(){ return m_ABLRawData.locate.fConfidence;}
	double  GetProbability(){ return m_ABLRawData.locate.fProbability;}
	void    SetProbability( const double dProb ){ m_ABLRawData.locate.fProbability = dProb;}
	double  GetMajorError(){ return m_ABLRawData.locate.wlsSolution.fMajorError;}
	double  GetMinorError(){ return m_ABLRawData.locate.wlsSolution.fMinorError;}
	double  GetHeading(){ return m_ABLRawData.locate.wlsSolution.fHeading;}
	double  GetRadiusErrEllipse(){ return m_ABLRawData.locate.wlsSolution.fRadiusErrEllipse;}
	double  GetTOANoise(){ return m_ABLRawData.locate.wlsSolution.fTrend;}
	double  GetFOANoise(){ return m_ABLRawData.locate.wlsSolution.fRMS;}
	double  GetLocationError(){ return 0.0;}
	
	WORD    GetNumMsgs(){ return m_ABLRawData.locate.wlsSolution.wNumMsgs;}
	WORD    GetNumMsgsUsed(){ return m_ABLRawData.locate.wlsSolution.wNumMsgsUsed;}
	WORD    GetNumBurstsUsed(){ return m_ABLRawData.locate.wlsSolution.wNumBurstsUsed;}
	WORD    GetNumMissedBursts(){ return 0.0;}

	WORD    GetNumFOAMsgUsed() { return m_ABLRawData.locate.wlsSolution.wNumMsgsUsed;}
	WORD    GetNumTOAMsgUsed() { return (WORD)m_ABLRawData.locate.wlsSolution.fFreqBiasError;}

	double  GetCNR(){ return m_ABLRawData.locate.fPower;}
	double  GetFrequency(){ return m_ABLRawData.locate.wlsSolution.dFrequency;}
	double  GetBitRate(){ return 0.0;}
	double  GetRepetitionRate(){ return 0.0;}

	double  GetFreqBiasError() { return m_ABLRawData.locate.wlsSolution.fFreqBiasError;}

	double  GetHDOP() { return m_ABLRawData.locate.wlsSolution.fFreqDrift;}
	double  GetCNR_Ave() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[0];}
	double  GetCNR_Sigma() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[1];}
	double  GetFrequency_Ave() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[2];}
	double  GetFrequency_Sigma() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[3];}
	double  GetBitRate_Ave() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[4];}
	double  GetBitRate_Sigma() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[5];}
	double  GetRepetitionRate_Ave() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[6];}
	double  GetRepetitionRate_Sigma() { return m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[7];}
	DWORD   GetWaveFormID() 
	{
		DWORD wRet = (m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[8] == -1.0) ? -1 : (DWORD)((int)m_ABLRawData.locate.wlsSolution.fCoVarianceMatrix[8]);
		return wRet;
	}
	

	void    ToCSVString( std::string& szCSVStr );

	static void GetCSVString( EMSLOCATE* pLocateData, std::string& szCSVStr );
	static void GetLocateCSVHeaderString( std::string& szCSVHeader );

protected:
	void _CalculateVarCovarLatLong( double  dLAT,
		                            double& dVLONG,
									double& dVLAT,
									double& dCLALO,
		                            double  dMajorError,
									double  dMinorError,
									double  dHeading,
								    double dOrbDetErr,
								    double dSDEL );

private:
	double m_dVLAT;
	double m_dVLONG;
	double m_dCLALO;

	EMSABLRawData  m_ABLRawData;

	static const std::string ms_szTimeFormat; 
};

inline bool 
CEMSABLRawObject::IsOlderThan( const CEMSABLRawObject& oABLRaw )
{
	return (oABLRaw.m_ABLRawData.locate.timeLastData.intTime - m_ABLRawData.locate.timeLastData.intTime) > 0;
}


#endif 
