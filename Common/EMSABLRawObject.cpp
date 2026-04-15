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


#include "EMSABLRawObject.h"
#include "emsencod.h"
#include "emsexcpt.h"
#include "emscoord.h"
#include "emsconst.h"
#include "EMSBEACON.h"
#include "convutility.h"
#include "CBeaconMessage.h"
#include <float.h>


const std::string CEMSABLRawObject::ms_szTimeFormat = "%d/%d/%d %d:%d:%d.%d";

CEMSABLRawObject::CEMSABLRawObject(): CApiObjBase("CEMSABLRawObject"),
									  m_dVLAT(0.0),
									  m_dVLONG(0.0),
									  m_dCLALO(0.0)
{
	memset( &m_ABLRawData, 0, sizeof( EMSABLRawData ) );
}

CEMSABLRawObject::CEMSABLRawObject( const EMSABLRawData& cABLRawData ): 
                                                           CApiObjBase("CEMSABLRawObject"),
 														   m_dVLAT(0.0),
														   m_dVLONG(0.0),
														   m_dCLALO(0.0)
{
	memcpy( &m_ABLRawData, &cABLRawData, sizeof( EMSABLRawData ) );
}


CEMSABLRawObject::CEMSABLRawObject( const EMSLOCATE& cemsLocate ): 
                                                           CApiObjBase("CEMSABLRawObject"),
														   m_dVLAT(0.0),
														   m_dVLONG(0.0),
														   m_dCLALO(0.0)
{
	memcpy( &m_ABLRawData.locate, &cemsLocate, sizeof( EMSLOCATE ) );
	m_ABLRawData.dwStatus = 0;
}

CEMSABLRawObject::CEMSABLRawObject( const CEMSABLRawObject& coABLRawObj ): 
														CApiObjBase("CEMSABLRawObject")
{
	memcpy( &m_ABLRawData, &(coABLRawObj.m_ABLRawData), sizeof( EMSABLRawData ) );
	m_dVLAT = coABLRawObj.m_dVLAT;
	m_dVLONG = coABLRawObj.m_dVLONG;
	m_dCLALO = coABLRawObj.m_dCLALO;
}

CEMSABLRawObject::~CEMSABLRawObject()
{
}


ULONG
CEMSABLRawObject::GetFirstSATID()
{
	ULONG ulRet = 0;
	ULONG ulTemp = 0;
	CEMSEncodedSatID::Expand( &m_ABLRawData.locate.cSatIDs, &ulRet, 1, &ulTemp );
	return ulRet;
}


void 
CEMSABLRawObject::GetSATIDs( std::list<ULONG>& lstSATIds )
{
	ULONG* aulSatId = NULL;
	ULONG ulTemp = 0;
	int iSize = sizeof( m_ABLRawData.locate.cSatIDs );

	aulSatId = new ULONG[iSize];
	if( aulSatId )
	{
		CEMSEncodedSatID::Expand( &m_ABLRawData.locate.cSatIDs, aulSatId, iSize, &ulTemp );
		for( int i = 0; i < ulTemp; i++ )
		{
			if( aulSatId[i] > 0 )
			{
				lstSATIds.push_back( aulSatId[i] );
			}
		}

		lstSATIds.sort();
		lstSATIds.unique();

		delete []aulSatId;
		aulSatId = NULL;
	}
	else
	{
		THROW_NOMEMORY_EXCEPTION();
	}
}

ULONG
CEMSABLRawObject::GetFirstLUTID()
{
	ULONG ulRet = 0;
	ULONG ulTemp = 0;
	CEMSEncodedLutID::Expand( &m_ABLRawData.locate.cLutIDs, &ulRet, 1, &ulTemp );
	return ulRet;
}


void 
CEMSABLRawObject::GetLUTIDs( std::list<ULONG>& lstLUTIds )
{
	ULONG* aulLUTId = NULL;
	ULONG ulTemp = 0;
	int iSize = sizeof( m_ABLRawData.locate.cLutIDs );

	aulLUTId = new ULONG[iSize];
	if( aulLUTId )
	{
		CEMSEncodedLutID::Expand( &m_ABLRawData.locate.cLutIDs, aulLUTId, iSize, &ulTemp );
		for( int i = 0; i < ulTemp; i++ )
		{
			if( aulLUTId[i] > 0 )
			{
				lstLUTIds.push_back( aulLUTId[i] );
			}
		}

		lstLUTIds.sort();
		lstLUTIds.unique();
		delete []aulLUTId;
		aulLUTId = NULL;
	}
	else
	{
		THROW_NOMEMORY_EXCEPTION();
	}
}


ULONG
CEMSABLRawObject::GetCountryCode()
{
	ULONG  ulCntCode = 0;

	if( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) // TBV
	{
		CBeaconMsg oBcnMsg( m_ABLRawData.locate.info.rec406.cBeaconMsg );
		ulCntCode = oBcnMsg.getCountryCode();
	}
	return ulCntCode;
}

int
CEMSABLRawObject::GetBcnMsgErrorCnt()
{
	int  iErrorCnt = -1;

	if( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) // TBV
	{
		iErrorCnt = m_ABLRawData.locate.info.rec406.wBitErrorFrameSync + m_ABLRawData.locate.info.rec406.wBitErrorField1 + m_ABLRawData.locate.info.rec406.wBitErrorField2;
	}
	return iErrorCnt;
}

int
CEMSABLRawObject::GetFSErrorCnt()
{
	int  iErrorCnt = -1;

	if( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) 
	{
		CBeaconMsg oBcnMsg( m_ABLRawData.locate.info.rec406.cBeaconMsg );
		iErrorCnt = oBcnMsg.CheckFSError();
	}
	return iErrorCnt;
}

int
CEMSABLRawObject::GetPDF1ErrorCnt()
{
	int  iErrorCnt = -1;

	if( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) 
	{
		CBeaconMsg oBcnMsg( m_ABLRawData.locate.info.rec406.cBeaconMsg );
		iErrorCnt = oBcnMsg.getPDF1BitErrors();
	}
	return iErrorCnt;
}

int
CEMSABLRawObject::GetPDF2ErrorCnt()
{
	int  iErrorCnt = -1;

	if( (m_ABLRawData.locate.wType & EMSLOCTYPE_CBC ) != EMSLOCTYPE_CBC ) 
	{
		CBeaconMsg oBcnMsg( m_ABLRawData.locate.info.rec406.cBeaconMsg );
		iErrorCnt = oBcnMsg.getPDF2BitErrors();
	}
	return iErrorCnt;
}


double
CEMSABLRawObject::GetDistanceApart( const CEMSABLRawObject& oABLRaw )
{
	CEMSCoordSystem oCoordSys;

	return oCoordSys.DistanceApart( m_ABLRawData.locate.wlsSolution.location, oABLRaw.m_ABLRawData.locate.wlsSolution.location );
}

void
CEMSABLRawObject::CalculateLatLongDeltaSigma( double dOrbDetErr, double dSDEL )
{
	_CalculateVarCovarLatLong( m_ABLRawData.locate.wlsSolution.location.degLatitude, 
		                       m_dVLONG,
							   m_dVLAT,
							   m_dCLALO,
		                       m_ABLRawData.locate.wlsSolution.fMajorError,
							   m_ABLRawData.locate.wlsSolution.fMinorError,
							   m_ABLRawData.locate.wlsSolution.fHeading,
							   dOrbDetErr,
							   dSDEL );
}

void 
CEMSABLRawObject::_CalculateVarCovarLatLong( double dLAT, 
											 double& dVLONG, 
											 double& dVLAT, 
											 double& dCLALO,
		                                     double dMajorError,
											 double dMinorError,
											 double dHeading,
											 double dOrbDetErr,
											 double dSDEL )
{
	if( dSDEL == 0.0 )
	{
		dSDEL = 1.0;
	}
	
	{
		if( !_finite( dHeading ) )
			dHeading = 0.0;

		while(dHeading > 360.0 )
			dHeading -= 360.0;

		while(dHeading < 0.0 )
			dHeading += 360.0;

		if( dHeading >= 359.5 ) 
			dHeading = 0.0;

		if( !_finite( dMajorError ) )
			dMajorError = 999.9;

		if( dMajorError > 999.9 )
			dMajorError = 999.9;

		if( dMajorError < 0.1 )
			dMajorError = 0.1;

		if( !_finite( dMinorError ) )
			dMinorError = 999.9;

		if( dMinorError > 999.9 )
			dMinorError = 999.9;

		if( dMinorError < 0.1 )
			dMinorError = 0.1;
	}

	double sh  = SIND( dHeading );
	double ch  = COSD( dHeading );

	double MajorSquare = ( (dMajorError * dMajorError) - (dOrbDetErr * dOrbDetErr) ) / (dSDEL * dSDEL);
	double MinorSquare = ( (dMinorError * dMinorError) - (dOrbDetErr * dOrbDetErr) ) / (dSDEL * dSDEL);

	double MM_S = MajorSquare + MinorSquare;

	// calculate standard deviation VE and VN and normalized convariance CEN for EAST and NORTH at ELT lat/long.
	double VN2 = MajorSquare * ch * ch + MinorSquare * sh * sh;
	double VE2 = MajorSquare * sh * sh + MinorSquare * ch * ch;

	double VN = sqrt( VN2 );
	double VE = sqrt( VE2 );

	double DENOM = 2.0 * VE * VN * sh * ch;

	double CEN = 0.0;

	if( 0.0 != DENOM )
	{
		CEN = (MajorSquare - VN2 * ch * ch - VE2 * sh * sh) / DENOM;
	}

	CEN = min( max(CEN, -1.0), 1.0 );

	// Calculate the standard deviations dVLAT and dVLONG of the lat /long and their normalized covariance dCLALO.
	if( (-90.0 != dLAT) && (90.0 != dLAT) )
	{
		dVLONG = VE / (c_dEarthKmRadius * COSD( dLAT) );
	}
	else
	{
		dVLONG = 0.0;
	}
	dVLONG = 180.0 * (dVLONG / c_dPI);
	
	dVLAT = VN / c_dEarthKmRadius;
	dVLAT = 180.0 * (dVLAT / c_dPI);

	dCLALO = CEN;
}



/*void 
CEMSABLRawObject::_CalculateVarCovarLatLong1( double dLAT, 
											 double& dVLONG, 
											 double& dVLAT, 
											 double& dCLALO,
		                                     double dMajorError,
											 double dMinorError,
											 double dHeading,
											 double dOrbDetErr,
											 double dSDEL )
{
	if( dSDEL == 0.0 )
	{
		dSDEL = 1.0;
	}

	double sh  = SIND( dHeading );
	double ch  = COSD( dHeading );
	double sh2h =  SIND( 2.0 * dHeading );
	double ch2h  = COSD( 2.0 * dHeading );

	double MajorSquare = ( (dMajorError * dMajorError) - (dOrbDetErr * dOrbDetErr) ) / (dSDEL * dSDEL);
	double MinorSquare = ( (dMinorError * dMinorError) - (dOrbDetErr * dOrbDetErr) ) / (dSDEL * dSDEL);

	double MM_S = MajorSquare + MinorSquare;

	// calculate standard deviation VE and VN and normalized convariance CEN for EAST and NORTH at ELT lat/long.
	double VN2 = MajorSquare * ch2h - MM_S * (ch2h - 1.0) / 2.0;

	double absVN2;
	if( 0.0 > VN2 )
	{
		absVN2 = -1.0 * VN2; 
	}
	else
	{
		absVN2 = VN2;
	}

	//double VN = sqrt( abs(VN2) );
	double VN = sqrt( absVN2 );

	double VE2 = MM_S - VN2;

	double absVE2;
	if( 0.0 > VE2 )
	{
		absVE2 = -1.0 * VE2; 
	}
	else
	{
		absVE2 = VE2;
	}

	//double VE = sqrt( abs(VE2) );
	double VE = sqrt( absVE2 );

	double DENOM = 2.0 * VE * VN * sh * ch;

	double CEN = 0.0;

	if( 0.0 != DENOM )
	{
		CEN = (MajorSquare - VN2 * ch * ch - VE2 * sh * sh) / DENOM;
	}

	CEN = min( max(CEN, -1.0), 1.0 );

	// Calculate the standard deviations dVLAT and dVLONG of the lat /long and their normalized covariance dCLALO.
	if( (-90.0 != dLAT) && (90.0 != dLAT) )
	{
		dVLONG = VE / (c_dEarthKmRadius * COSD( dLAT) );
	}
	else
	{
		dVLONG = 0.0;
	}
	dVLONG = 180.0 * (dVLONG / c_dPI);
	
	dVLAT = VN / c_dEarthKmRadius;
	dVLAT = 180.0 * (dVLAT / c_dPI);

	dCLALO = CEN;
}
*/

bool
CEMSABLRawObject::IsAged( EMSTIME time, double dAgeoutPeriod )
{
	bool bRet = false;
	CEMSTime timeCheck;

	timeCheck.SetTime( m_ABLRawData.locate.timeLastData );

	if( timeCheck.MinutesDifferent( time ) > dAgeoutPeriod )
	{
		bRet = true;
	}
	return bRet;
}

void
CEMSABLRawObject::ToCSVString( std::string& szCSVStr )
{
	CEMSABLRawObject::GetCSVString( &m_ABLRawData.locate, szCSVStr );
}

void 
CEMSABLRawObject::GetCSVString( EMSLOCATE* pLocateData, std::string& szCSVStr )
{
	szCSVStr = "";

	// This method needs to be redesigned and tested before being used.
	if( pLocateData )
	{
		char szLine[256];
		CEMSTime emsTime( pLocateData->time );
		EMSTIMEFIELDS timeF;

		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->ulLutID);
		szCSVStr += ',';
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, "%X", (unsigned long)pLocateData->wType );
		szCSVStr += szLine;
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wType);
		szCSVStr += ',';

		{
			ULONG* aulSatId = NULL;
			ULONG ulTemp = 0;
			int iSize = sizeof( pLocateData->cSatIDs );

			aulSatId = new ULONG[iSize];
			if( aulSatId )
			{
				try
				{
					CEMSEncodedSatID::Expand( &pLocateData->cSatIDs, aulSatId, iSize, &ulTemp );
					for( int i = 0; i < ulTemp; i++ )
					{
						if( aulSatId[i] > 0 )
						{
							szCSVStr += CEMSConversionUtil::ConvertToStringA( aulSatId[i] );
							szCSVStr += ' ';
						}
					}

					szCSVStr += ',';

					delete []aulSatId;
					aulSatId = NULL;
				}
				catch( ... )
				{
					if( aulSatId )
					{
						delete []aulSatId;
						aulSatId = NULL;
					}
					throw;
				}
			}
			else
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}

		{
			ULONG* aulLUTId = NULL;
			ULONG ulTemp = 0;
			int iSize = sizeof( pLocateData->cLutIDs );

			aulLUTId = new ULONG[iSize];
			if( aulLUTId )
			{
				try
				{
					CEMSEncodedLutID::Expand( &pLocateData->cLutIDs, aulLUTId, iSize, &ulTemp );
					for( int i = 0; i < ulTemp; i++ )
					{
						if( aulLUTId[i] > 0 )
						{
							szCSVStr += CEMSConversionUtil::ConvertToStringA( aulLUTId[i] );
							szCSVStr += ' ';
						}
					}

					szCSVStr += ',';

					delete []aulLUTId;
					aulLUTId = NULL;
				}
				catch( ... )
				{
					if( aulLUTId )
					{
						delete []aulLUTId;
						aulLUTId = NULL;
					}
					throw;
				}
			}
			else
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->ulSatPassID );
		szCSVStr += ',';
		szCSVStr += CBeaconMessage::ConvertToHexString( pLocateData->i64BeaconID );
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->i64BeaconID);
		szCSVStr += ',';

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.location.degLatitude );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.location.degLongitude );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.location.fAltitude );
		szCSVStr += ',';

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.dFrequency );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fFreqDrift );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wlsSolution.wNumMsgs );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wlsSolution.wNumMsgsUsed );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wlsSolution.wNumBurstsUsed );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wlsSolution.wNumIterations );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fRadiusErrEllipse );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fFreqBiasError );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fMajorError );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fMinorError );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fHeading );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fRMS );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fTrend );
		szCSVStr += ',';
		for( int i = 0; i < 10; i++ )
		{
			szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->wlsSolution.fCoVarianceMatrix[i] );
			szCSVStr += ',';
		}

		emsTime.SetTime( pLocateData->timeTCA );
		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->fCrossTrackAngle);
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->wWindowFactor);
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->fConfidence);
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->fProbability);
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->fPower);
		szCSVStr += ',';

		emsTime.SetTime( pLocateData->timeFirstData );
		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		emsTime.SetTime( pLocateData->timeLastData );
		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		if( (pLocateData->wType & EMSLOCTYPE_CBC ) == EMSLOCTYPE_CBC ) // TBV
		{
			szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->info.recCBC.fSweep );
			szCSVStr += ',';
			szCSVStr += CEMSConversionUtil::ConvertToStringA( pLocateData->info.recCBC.fSweepError );
			szCSVStr += ',';
			szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->info.recCBC.wSidebands );
			szCSVStr += ',';
		}
		else
		{
			szCSVStr += " , , ,";
			memset( szLine, 0, sizeof(szLine) );

			CBeaconMessage msg( pLocateData->info.rec406.cBeaconMsg );
			msg.GetHexString( (char*)szLine );

			//memcpy( szLine, pLocateData->info.rec406.cBeaconMsg, sizeof(pLocateData->info.rec406.cBeaconMsg) );
			for( int i = 0; i < 36; i++ )
			{
				szLine[i] = toupper( szLine[i] );
				if( szLine[i] ==  ' ' )
				{
					szLine[i] = '0';
				}
			}
			szCSVStr += szLine;
			szCSVStr += ',';
			szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->info.rec406.wBitErrorFrameSync );
			szCSVStr += ',';
			szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->info.rec406.wBitErrorField1 );
			szCSVStr += ',';
			szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pLocateData->info.rec406.wBitErrorField2 );
		}

		szCSVStr += '\n';


	}
}

void
CEMSABLRawObject::GetLocateCSVHeaderString( std::string& szCSVHeader )
{
//	szCSVHeader += ',';
	// m_ABLRawData.locate.

	szCSVHeader = "time";
	szCSVHeader += ',';
	szCSVHeader += "ulLutID";
	szCSVHeader += ',';
	szCSVHeader += "wType";
	szCSVHeader += ',';
	szCSVHeader += "cSatIDs[ 16 ]";
	szCSVHeader += ',';
	szCSVHeader += "cLutIDs[ 16 ]";
	szCSVHeader += ',';
	szCSVHeader += "ulSatPassID";
	szCSVHeader += ',';
	szCSVHeader += "i64BeaconID";

	szCSVHeader += ',';
	szCSVHeader += "location.degLatitude";
	szCSVHeader += ',';
	szCSVHeader += "location.degLongitude";
	szCSVHeader += ',';
	szCSVHeader += "location.fAltitude";
	szCSVHeader += ',';
	szCSVHeader += "dFrequency";
	szCSVHeader += ',';
	szCSVHeader += "fFreqDrift";
	szCSVHeader += ',';
	szCSVHeader += "wNumMsgs";
	szCSVHeader += ',';
	szCSVHeader += "wNumMsgsUsed";
	szCSVHeader += ',';
	szCSVHeader += "wNumBurstsUsed";
	szCSVHeader += ',';
	szCSVHeader += "wNumIterations";
	szCSVHeader += ',';
	szCSVHeader += "fRadiusErrEllipse";
	szCSVHeader += ',';
	szCSVHeader += "fFreqBiasError";
	szCSVHeader += ',';
	szCSVHeader += "fMajorError";
	szCSVHeader += ',';
	szCSVHeader += "fMinorError";
	szCSVHeader += ',';
	szCSVHeader += "fHeading";
	szCSVHeader += ',';
	szCSVHeader += "fRMS";
	szCSVHeader += ',';
	szCSVHeader += "fTrend";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 0 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 1 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 2 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 3 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 4 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 5 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 6 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 7 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 8 ]";
	szCSVHeader += ',';
	szCSVHeader += "fCoVarianceMatrix[ 9 ]";

	szCSVHeader += ',';
	szCSVHeader += "timeTCA";
	szCSVHeader += ',';
	szCSVHeader += "fCrossTrackAngle";
	szCSVHeader += ',';
	szCSVHeader += "wWindowFactor";
	szCSVHeader += ',';
	szCSVHeader += "fConfidence";
	szCSVHeader += ',';
	szCSVHeader += "fProbability";
	szCSVHeader += ',';
	szCSVHeader += "fPower";
	szCSVHeader += ',';
	szCSVHeader += "timeFirstData";
	szCSVHeader += ',';
	szCSVHeader += "timeLastData";
	szCSVHeader += ',';
	szCSVHeader += "fSweep";
	szCSVHeader += ',';
	szCSVHeader += "fSweepError";
	szCSVHeader += ',';
	szCSVHeader += "wSidebands";
	szCSVHeader += ',';
	szCSVHeader += "cBeaconMsg[ 18 ]";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorFrameSync";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorField1";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorField2";

	szCSVHeader += '\n';
}
