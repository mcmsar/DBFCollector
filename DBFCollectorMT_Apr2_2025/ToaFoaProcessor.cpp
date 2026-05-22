#include "ToaFoaProcessor.h"
#include "DBFCollectorConfig.h"
#include <stdio.h>
#include <math.h>



///////////////////////////////////////////////////////////////////////////////////////////////////

void
CToaFoaProcessor::_CopyData( float* fTest, float fValue, ULONG nCount )
{
	if ( nCount > 0 )
	{
		for ( ULONG i = 0; i < nCount; i++ )
		{
			fTest[i] = fValue;
		}
	}
}

int
CToaFoaProcessor::_Hex2Int( char cHex )
{
	if ( cHex == 'A' ) return 10;
	if ( cHex == 'B' ) return 11;
	if ( cHex == 'C' ) return 12;
	if ( cHex == 'D' ) return 13;
	if ( cHex == 'E' ) return 14;
	if ( cHex == 'F' ) return 15;
	return ( (int)cHex - 48 );
}

bool
CToaFoaProcessor::CheckBit( char cHex[36], int iBit )
{
	bool bOK = false;
	int i1, i2, i3, iHex;

	i1 = iBit / 4;
	i2 = ( iBit - i1 * 4 );
	i3 = 1 << i2;
	iHex = _Hex2Int( cHex[i1] );

	bOK = ( i3 & iHex ) ? true : false;

	return bOK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CToaFoaProcessor::InitializeTOAFOA(
	EMSTIME timestamp,
	ULONG ulSatellites,
	EMSDBFPASSRECORDS2* pPassSchedule,
	float* pTemp1,
	EMSCOMPLEX* pAcTemp1,
	EMSCOMPLEX* pAcFFTBeacon,
	EMSDBFTOAFOARECORD* pTOAFOA )
{
	EMS_RESULT hr = EMS_BAD_PARAM;

	if ( pTOAFOA )
	{
		bool bBeaconOK = false;

		//memset( pTOAFOA, 0, sizeof( EMSDBFTOAFOARECORD ) );
		memset(pTOAFOA->fTOA, 0, sizeof(pTOAFOA->fTOA));
		memset(pTOAFOA->fFOA, 0, sizeof(pTOAFOA->fFOA));
		memset(pTOAFOA->fBeaTOA, 0, sizeof(pTOAFOA->fBeaTOA));
		memset(pTOAFOA->fBeaFOA, 0, sizeof(pTOAFOA->fBeaFOA));
		memset(pTOAFOA->fCNR, 0, sizeof(pTOAFOA->fCNR));
		memset(pTOAFOA->fCORRTOA, 0, sizeof(pTOAFOA->fCORRTOA));
		memset(pTOAFOA->ulEigen, 0, sizeof(pTOAFOA->ulEigen));
		memset(pTOAFOA->fEigenProb, 0, sizeof(pTOAFOA->fEigenProb));
		memset(pTOAFOA->fPower, 0, sizeof(pTOAFOA->fPower));
		memset(pTOAFOA->cPower, 0, sizeof(pTOAFOA->cPower));

		pTOAFOA->timestamp.intTime = timestamp.intTime;
		pTOAFOA->fRefTxFrequency = pPassSchedule->rec[0].fRefTxFrequency;

		for ( int isat = 0; isat < (int)ulSatellites; isat++ )
		{
			//pTOAFOA->ulSatID[isat] = pPassSchedule->rec[isat].ulSatID;

			//if ( pPassSchedule->rec[isat].fBeaconElevation > 0 )
			{
				pTOAFOA->fBeaFOA[isat] = pPassSchedule->rec[isat].fFOA;
				pTOAFOA->fBeaTOA[isat] = pPassSchedule->rec[isat].fTOA;
				pTOAFOA->ulSatID[isat] = pPassSchedule->rec[isat].ulSatID;

				pTOAFOA->fPlateAz[isat] = pPassSchedule->rec[isat].fPlateAzimuth;
				pTOAFOA->fPlateEl[isat] = pPassSchedule->rec[isat].fPlateElevation;

				//if ( !bBeaconOK )
				{
					//memcpy( &pTOAFOA->cBeaconID[0], &pPassSchedule->rec[isat].cBeaconID[0], 15 );

					// Establish beacon message FFT for correlation tests
					char cBeacon[6];
					ULONG j,n, len2 = 0;

					// Assumes beacon with exactly 400 bps and 200 kHz bandwidth and 2 seconds duration
					ULONG ulBitSize = (ULONG)(0.0025 / 2 * DBF_LOG16_SIZE);
					ULONG ulBits = 24; // 112;
					ULONG ulSize   = ulBits * ulBitSize + 1;
					float fBit     = 0.0;

					memset( pTemp1,      0.0, DBF_LOG16_SIZE * sizeof(float) );
					memset( pAcTemp1,    0.0, DBF_LOG16_SIZE * sizeof(EMSCOMPLEX) );
					memset( pAcFFTBeacon, 0.0, DBF_LOG16_SIZE * sizeof(EMSCOMPLEX) );
					//memcpy( &cBeacon[0], &pPassSchedule->rec[isat].cBeaconMess[0], 36 );
					memcpy(&cBeacon[0], "FFFED0", 6);

					for ( j = 0; j < ulBits; j++ )
					{
						n = ulBitSize * j;
						if ( CheckBit( &cBeacon[0], j ) )
						{
							fBit = 1.0;
						}
						else
						{
							fBit = -1.0;
						}
						{
							_CopyData( &pTemp1[n],             fBit,  ulBitSize / 2 );
							_CopyData( &pTemp1[n + ulBitSize / 2], -fBit, ulBitSize / 2 );
						}
					}

					emssRealFftNip( pTemp1, pAcFFTBeacon, DBF_LOG16, EMS_SPL_FWD );

					// Normalize and conjugate
					float fFactor = 1.0f / (float)DBF_LOG16_SIZE;
					for ( j = 0; j < DBF_LOG16_SIZE; j++ )
					{
						pAcFFTBeacon[j].re /=  fFactor;
						pAcFFTBeacon[j].im /= -fFactor;
					}
					bBeaconOK = true;
				}
			}
		}


		//if ( bBeaconOK )
		//{
		//	CEMSTime oTime( pTOAFOA->timestamp );
		//	EMSTIMEFIELDS tmFields;
		//	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );
		//	oTime.GetTime( &tmFields );

		//	float fDeltaTime = (float)(p_aTOAFOA->timestamp.intTime - m_aPassSchedule.rec[0].timestamp.intTime)*1e-9;
		//	printf(" %15s, %02d:%02d:%02d.%06d DiffTime (Current - Schedule) %f\n",
		//		 pTOAFOA->cBeaconID, tmFields.nHour, tmFields.nMinute, tmFields.nSecond, tmFields.lNanosecond/1000, fDeltaTime);
		//}
		hr = EMS_OK;
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool
CToaFoaProcessor::SatelliteTOAFOA(
	int isat,
	EMSDBFPASSRECORDS2* pPassSchedule,
	float* pTemp1,
	EMSCOMPLEX* pAcTemp1,
	EMSCOMPLEX* pAcTemp2,
	EMSCOMPLEX* pAcTemp3,
	EMSCOMPLEX* pAcFFTBeacon,
	EMSDBFTOAFOARECORD* pTOAFOA )
{
	bool bOK = false;

	if (pTOAFOA->fRefTxFrequency < 1.0 ) return bOK;
	
	//float fFOA = 0.0;
	//float fTOA = 0.0;
	float fBeaconFOA = 0.0;
	float fBeaconTOA = 0.0;
	float fBeaconEL = 0.0;
	float fAvePower = 0.0;

	float fMaxPower = 0.0;
	float fSigmaPower = 0.0;
	float fCNR        = 0.0;
	float fCNRthreshold  = 35.0;
	float fCORRthreshold = 3.0;
	//float fBinsize = 0.5; 
	float fBinsize = (float)DBF_SAMPLE_RATE / (float)DBF_LOG20_SIZE;
	double dAvePower = 0.0;

	ULONG ulBeaconBandWidth = (ULONG) (15000.0 / fBinsize);
							  
	ULONG ulFreqBandWidth   = (ULONG) (100000.0 / fBinsize);
	ULONG ulFreqStart       = (ULONG) (50000.0 / fBinsize);
	ULONG ulFreq       = 0;
													   
	ULONG ulFreqIndex  = 0;
	ULONG ulTimeIndex  = 0;
	ULONG ulFreqOffset = 0;

	EMSCOMPLEX cBeaconFreq[2048];
	EMSCOMPLEX cBeaconTime[2048];
	float fBeaconTime[2048];
	float fCorrBeacon[4096];
	float fTestBeacon[1024];

	memset( &cBeaconFreq[0], 0 , sizeof(EMSCOMPLEX) * 2048 );
	memset( &cBeaconTime[0], 0 , sizeof(EMSCOMPLEX) * 2048 );
	memset( &fBeaconTime[0], 0 , sizeof(float) * 2048 );
	memset( &fCorrBeacon[0], 0 , sizeof(float) * 4096 );
	memset( &fTestBeacon[0], 0 , sizeof(float) * 1024 );
	
	ulFreq = (ULONG) (pTOAFOA->fRefTxFrequency / fBinsize );
	ulFreqOffset = ulFreqStart + (ulFreq - ulBeaconBandWidth/2);  // initial offset of 50 kHz

	if (  ulFreqOffset > DBF_LOG19_SIZE - ulFreqBandWidth )
	{
		ulFreqOffset = DBF_LOG19_SIZE - ulFreqBandWidth;
	}
	// Compare spectrum to noise floor

	/*
	long i1;
	float fCorr = 0.0;
	for (long i = ulFreqStart; i < DBF_LOG19_SIZE - ulFreqStart; i++)
	{
		i1 = i + ulBeaconBandWidth + 100;
		fAvePower = CSigProcHelpers::_EMSsMean(&pTemp1[i], ulBeaconBandWidth);
		fAvePower += CSigProcHelpers::_EMSsMean(&pTemp1[i1], ulBeaconBandWidth);
		fCorr += fabs(pTemp1[i1 - 50] - fAvePower / 2.0);
	}
	pTOAFOA->fCORRTOA[isat] = fCorr / (float)(DBF_LOG19_SIZE - 2* ulFreqStart);
	*/
	// Find Beacon Power and check above CNR threshold
	// assumes filter with 200 kHz bandwidth
	fMaxPower = CSigProcHelpers::_EMSsMaxExt( &pTemp1[ulFreqOffset], ulBeaconBandWidth, &ulFreqIndex );
	ulFreqIndex += ulFreqOffset;
	fAvePower = CSigProcHelpers::_EMSsMean( &pTemp1[ulFreqIndex + ulBeaconBandWidth], ulBeaconBandWidth / 2 );
	fCNR = 10.0f * log10( fMaxPower / fAvePower ) + 24.0f;
	//ulFreqIndex -= ulFreqStart;
	
	if ( fCNR > fCNRthreshold )
	{
		bOK = false;
		// Verify beaon detection

		// Generate beacon power template

		_CopyData( &fTestBeacon[0], 2.0, 20 * 8 );
		_CopyData( &fTestBeacon[160], 1.0, 44 * 8 );
		//fAvePower = _EMSsMean(&fTestBeacon[0], 1024 );
		//emssbSub1( fAvePower, &fTestBeacon[0], 1024 );

		// Convert from frequency domain to time domain
		memcpy( &cBeaconFreq[0], &pAcTemp3[ulFreqIndex - 128], 256 * sizeof(EMSCOMPLEX) );
		emscFftNip( &cBeaconFreq[0], &cBeaconTime[0], 11, EMS_SPL_INV );
		CSigProcHelpers::_EMScbPowerSpectr( &cBeaconTime[0], &fBeaconTime[0], 2048 );

		memcpy( &pTOAFOA->fPower[isat * 2048], &fBeaconTime[0], 2048 * sizeof(float) );
		memcpy( &pTOAFOA->cPower[isat * 2048], &pAcTemp3[ulFreqIndex - 1024], 2048 * sizeof(EMSCOMPLEX) );

		// Perform Power Correlation ( beacon is expected within the first one second )
		fMaxPower = 0.0;
		int iCorrLength = 2048-512; 
																									
		for ( int i = 0; i < iCorrLength; i++ )
		{
			//fCorrBeacon[i] = emssDotProd( &fTestBeacon[0], &fBeaconTime[i], 1024 );
			fCorrBeacon[i] = emssDotProd( &fTestBeacon[0], &fBeaconTime[i], 512 );
		}
		fMaxPower    = CSigProcHelpers::_EMSsMaxExt( &fCorrBeacon[0], iCorrLength, &ulTimeIndex );
		fSigmaPower  = (float)CSigProcHelpers::_EMSsMeanStdDev( &fCorrBeacon[0], iCorrLength, &dAvePower );
		fMaxPower   /= fSigmaPower;
		pTOAFOA->fCORRTOA[isat] = fMaxPower;

		pTOAFOA->fCNR[isat]	 = fCNR;
		if (ulFreqIndex > ulFreqStart) {
			pTOAFOA->fFOA[isat] = (float)(ulFreqIndex - ulFreqStart) * fBinsize;
		}
		//pTOAFOA->fFOA[isat] = (float)((long)ulFreqIndex - (long)ulFreqStart) * fBinsize;
		pTOAFOA->fTOA[isat]	 = (float)ulTimeIndex * 0.001024f;
		

		if ( fMaxPower > fCORRthreshold && pPassSchedule->rec[isat].fBeaconElevation > 0)
		{
			// perform Carrier Track given beacon detection
			// Assign phase coefficients from complex conjugate of strongest carrier signal
			//for( ULONG i = 0; i < DBF_NUM_ELEMENTS; i++ )
			//{
			//	m_acDBFBeamVectors[i + isat*DBF_NUM_ELEMENTS].re =  m_acMatrix[i*DBF_LOG19_SIZE + ulFreqIndex ].re;
			//	m_acDBFBeamVectors[i + isat*DBF_NUM_ELEMENTS].im = -m_acMatrix[i*DBF_LOG19_SIZE + ulFreqIndex ].im;
			//}
			
			// Beacon Message correlation
			memset( &pAcTemp1[0], 0, DBF_LOG16_SIZE * sizeof(EMSCOMPLEX) );
			for ( int i = 0; i < 2048; i++ )
			{
				pAcTemp1[i].re              = pAcTemp3[ulFreqIndex + i].re;
				pAcTemp1[i].im              = pAcTemp3[ulFreqIndex + i].im;
				pAcTemp1[DBF_LOG16_SIZE - i].re = pAcTemp3[ulFreqIndex - i].re;
				pAcTemp1[DBF_LOG16_SIZE - i].im = pAcTemp3[ulFreqIndex - i].im;
			}
			emscbMul2( &pAcFFTBeacon[0], &pAcTemp1[0], DBF_LOG16_SIZE );

			emscFftNip( &pAcTemp1[0], &pAcTemp2[0], DBF_LOG16, EMS_SPL_INV );
			CSigProcHelpers::_EMScbPowerSpectr( &pAcTemp2[0], &pTemp1[0], DBF_LOG16_SIZE );

			fMaxPower   = CSigProcHelpers::_EMSsMaxExt( &pTemp1[0], DBF_LOG16_SIZE, &ulTimeIndex );
			fSigmaPower = (float)CSigProcHelpers::_EMSsMeanStdDev( &pTemp1[0], DBF_LOG16_SIZE, &dAvePower );
			fMaxPower  /= fSigmaPower;

			bOK = true;
		}
	}
	return bOK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

bool
CToaFoaProcessor::IdentifyTOAFOA(
	EMSTIME tm,
	ULONG ulSatellites,
	EMSDBFPASSRECORDS2* pPassSchedule,
	CEMSQueue<DBFTrackingData>& qrefDBFBeamVectors,
	EMSCOMPLEX* acDBFBeamVectors_In,
	int* pBeamIDs,
	int* pPredictedSATIDs,
	float* pProbability,
	int* pPrevPassSchedSATIDs,
	EMSCOMPLEX* pAcDBFBeamVectors,
	EMSDBFTOAFOARECORD* pTOAFOA)
{
	bool bOK = false;
	int iTemp;

	int i, j, k;
	float fTOAdiff;
	float fTOAthreshold = 0.002f;
	float fFOAdiff;
	float fFOAthreshold = 25.0f;

	FILE* lpSatIdentityFile = NULL;
	FILE* lpToaFoaResidualsFile = NULL;
	char  szFileName[256];

	int CurrentSatIds[MAX_BEAMS];
	memset(CurrentSatIds, 0, sizeof(int) * MAX_BEAMS);
	for (i = 0; i < (int)ulSatellites; i++)
	{
		CurrentSatIds[i] = pPassSchedule->rec[i].ulSatID;
	}

	// Read from queue
	EMSCOMPLEX* prevDBFBeamVectors = qrefDBFBeamVectors.ReadFirst().dbfBeamVector;
	int* prevSchedulerSatIDs = qrefDBFBeamVectors.ReadFirst().schedulerSatIds;
	int* prevPredSatIDs = qrefDBFBeamVectors.ReadFirst().predSatIDs;
	int* prevBeamIds = qrefDBFBeamVectors.ReadFirst().predBeamIDs;
	float* prevProbability = qrefDBFBeamVectors.ReadFirst().probability;
	int         prevNumBeams = qrefDBFBeamVectors.ReadFirst().numBeams;

	// Check if first time
	if (!prevDBFBeamVectors && !prevBeamIds)
	{
		memset(pBeamIDs, 0, MAX_BEAMS * sizeof(int));
		for (i = 0; i < (int)ulSatellites; i++)
		{
			// First time so set default beam ids
			pBeamIDs[i] = i + 1;
		}
		DBFTrackingData obj;
		memcpy(pAcDBFBeamVectors, acDBFBeamVectors_In, MAX_BEAMS * NUM_CHANNELS * sizeof(EMSCOMPLEX));
		obj.dbfBeamVector = pAcDBFBeamVectors;
		obj.predBeamIDs = pBeamIDs;
		memcpy(pPredictedSATIDs, CurrentSatIds, MAX_BEAMS * sizeof(int));
		obj.predSatIDs = pPredictedSATIDs;
		obj.probability = pProbability;
		memcpy(pPrevPassSchedSATIDs, CurrentSatIds, sizeof(int) * MAX_BEAMS);
		obj.schedulerSatIds = pPrevPassSchedSATIDs;
		obj.numBeams = ulSatellites;
		qrefDBFBeamVectors.InsertAtFirst(obj);
		return true;
	}

	int newBeamIds[MAX_BEAMS];
	memset(newBeamIds, 0, sizeof(int) * MAX_BEAMS);
	int newPredSatIds[MAX_BEAMS];
	memset(newPredSatIds, 0, sizeof(int) * MAX_BEAMS);

	// Compute probabilities
	EMSCOMPLEX cTemp1[NUM_CHANNELS];
	EMSCOMPLEX cTemp;

	// Find new or missing satellites
	int iCount[MAX_BEAMS];
	memset(iCount, 0, sizeof(int) * MAX_BEAMS);

	int iMaxBeam = 0;
	for (i = 0; i < (int)ulSatellites; i++)
	{
		for (j = 0; j < prevNumBeams; j++)
		{
			if (CurrentSatIds[i] == prevPredSatIDs[j])
			{
				iCount[i] = j + 1;
				if (iMaxBeam < prevBeamIds[j]) iMaxBeam = prevBeamIds[j] + 1;
			}
		}
	}

	// Best match to previous eigenvector
	k = 0;
	for (i = 0; i < (int)ulSatellites; i++)
	{
		// Check orthogonality
		float fProb1[25];
		for (j = 0; j < (int)ulSatellites; j++)
		{
			memset(&cTemp1[0], 0.0, NUM_CHANNELS * sizeof(EMSCOMPLEX));
			emscbConj2(&pAcDBFBeamVectors[j * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS);
			cTemp = emscDotProd(&pAcDBFBeamVectors[i * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS);
			fProb1[k++] = (float)sqrt(cTemp.re * cTemp.re + cTemp.im * cTemp.im) / NUM_CHANNELS;
		}

		pProbability[i] = 0.0f;
		float fProb = 0.0f;

		if (iCount[i] > 0)  // Matching satellite condition
		{
			for (j = 0; j < prevNumBeams; j++)
			{
				memset(&cTemp1[0], 0.0, NUM_CHANNELS * sizeof(EMSCOMPLEX));
				emscbConj2(&prevDBFBeamVectors[j * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS);
				cTemp = emscDotProd(&pAcDBFBeamVectors[i * NUM_CHANNELS], &cTemp1[0], NUM_CHANNELS);
				fProb = (float)sqrt(cTemp.re * cTemp.re + cTemp.im * cTemp.im) / NUM_CHANNELS;
				if (fProb > pProbability[i])
				{
					pProbability[i] = fProb;
					newBeamIds[i] = prevBeamIds[j];
					newPredSatIds[i] = prevPredSatIDs[j];
				}
			}
		}
		else
		{
			newPredSatIds[i] = CurrentSatIds[i];
			newBeamIds[i] = iMaxBeam;
			iMaxBeam++;
		}
	}

	EMSTIMEFIELDS tmFlds;
	CEMSTime oTM(tm);
	oTM.GetTime(&tmFlds);
	ULONG ulHourSec = tmFlds.nHour * 60 * 60 + tmFlds.nMinute * 60 + tmFlds.nSecond;

	int iBeamTemp;
	int iSatTemp;
	EMSCOMPLEX acBeamTemp[NUM_CHANNELS];

	// Identify satellite based upon minimum TOA difference
	for (int isat = 0; isat < (int)ulSatellites; isat++)
	{
		if (pTOAFOA->fTOA[isat] > 0.0)
		{
			pTOAFOA->fTOA[isat] += tmFlds.lNanosecond * 1e-9f;
			if (pTOAFOA->fTOA[isat] > 1.0f) pTOAFOA->fTOA[isat] -= 1.0f;
			if (pTOAFOA->fTOA[isat] > 1.0f) pTOAFOA->fTOA[isat] -= 1.0f;
		}
	}

	for (int isat = 0; isat < (int)ulSatellites; isat++)
	{
		for (int jsat = 0; jsat < (int)ulSatellites; jsat++)
		{
			if (pTOAFOA->fBeaTOA[jsat] > 0.0)
			{
				fTOAdiff = pTOAFOA->fTOA[isat] - pTOAFOA->fBeaTOA[jsat];
				fFOAdiff = pTOAFOA->fFOA[isat] - pTOAFOA->fBeaFOA[jsat];
				//if ((abs(fTOAdiff) < fTOAthreshold) && (abs(fFOAdiff) < fFOAthreshold))
				if (abs(fTOAdiff) < fTOAthreshold)
				{
					pProbability[isat] = 9.99999999;
					if (abs(fFOAdiff - 850.0) < 100.0)
					{
						pProbability[isat] = 12.0;
						iSatTemp = newPredSatIds[isat];
						iBeamTemp = newBeamIds[isat];

						newPredSatIds[isat] = newPredSatIds[jsat];
						newPredSatIds[jsat] = iSatTemp;
						newBeamIds[isat] = newBeamIds[jsat];
						newBeamIds[jsat] = iBeamTemp;

						memcpy(&acBeamTemp[0], &acDBFBeamVectors_In[isat * NUM_CHANNELS], NUM_CHANNELS * sizeof(EMSCOMPLEX));
						memcpy(&pAcDBFBeamVectors[isat * NUM_CHANNELS], &acDBFBeamVectors_In[jsat * NUM_CHANNELS], NUM_CHANNELS * sizeof(EMSCOMPLEX));
						memcpy(&pAcDBFBeamVectors[jsat * NUM_CHANNELS], &acBeamTemp[0], NUM_CHANNELS * sizeof(EMSCOMPLEX));
					}
				}
			}
		}
	}

	memcpy(pBeamIDs, newBeamIds, sizeof(int) * MAX_BEAMS);
	memcpy(pPredictedSATIDs, newPredSatIds, MAX_BEAMS * sizeof(int));
	memcpy(pAcDBFBeamVectors, acDBFBeamVectors_In, MAX_BEAMS * NUM_CHANNELS * sizeof(EMSCOMPLEXD));
	memcpy(pPrevPassSchedSATIDs, &CurrentSatIds, sizeof(int) * MAX_BEAMS);

	DBFTrackingData obj;
	obj.dbfBeamVector = pAcDBFBeamVectors;
	obj.predBeamIDs = pBeamIDs;
	obj.predSatIDs = pPredictedSATIDs;
	obj.probability = pProbability;
	obj.schedulerSatIds = pPrevPassSchedSATIDs;
	obj.numBeams = ulSatellites;
	qrefDBFBeamVectors.InsertAtFirst(obj);

	for (int isat = 0; isat < (int)ulSatellites; isat++)
	{
		pTOAFOA->ulEigen[isat] = pBeamIDs[isat];
		pTOAFOA->fEigenProb[isat] = pProbability[isat];
	}

	//sprintf( szFileName, "%sDBF_TOAFOA_%06d.bin",
	//         CDBFCollectorConfig::GetInstance().GetSatIDDir().c_str(), ulHourSec );

	sprintf(szFileName, "C:\\HGT\\DBFPassData\\SatID\\DBF_TOAFOA_%06d.bin", ulHourSec);

	lpSatIdentityFile = fopen(szFileName, "w+b");

	if (lpSatIdentityFile)
	{
		fwrite(pTOAFOA, sizeof(EMSDBFTOAFOARECORD), 1, lpSatIdentityFile);

		flushall();
		fclose(lpSatIdentityFile);
		lpSatIdentityFile = NULL;
		bOK = true;

		CEMSTime oTime(pTOAFOA->timestamp);
		EMSTIMEFIELDS tmFields;
		memset(&tmFields, 0, sizeof(EMSTIMEFIELDS));
		oTime.GetTime(&tmFields);

		float tDiff = 10.0f;
		float fDiff = 10.0f;
		int iDiffIndex = 0;

		for (int i = 0; i < ulSatellites; i++) {
			if (pTOAFOA->fBeaTOA[i] != 0 && pTOAFOA->fBeaFOA[i] != 0) {
				float tSatDiff = abs(pTOAFOA->fBeaTOA[i] - pTOAFOA->fTOA[i]);
				float fSatDiff = abs(pTOAFOA->fBeaFOA[i] - pTOAFOA->fFOA[i]);
				// 0 value indicates an error reading values
				if (pTOAFOA->fCNR[i] != 0 && tSatDiff < tDiff) {
					tDiff = tSatDiff;
					fDiff = fSatDiff;
					iDiffIndex = i;
				}
			}
		}


		if (tDiff != 10.0f)
		{
			printf(" %02d:%02d:%02d.%06d, %d, %5.1f, TOA: %6.3f,%6.3f, FOA: %7.1f,%7.1f, dTOA: %6.4f, dFOA: %6.1f\n",
				tmFields.nHour, tmFields.nMinute, tmFields.nSecond, tmFields.lNanosecond / 1000,
				pTOAFOA->ulSatID[iDiffIndex], pTOAFOA->fCNR[iDiffIndex],
				pTOAFOA->fBeaTOA[iDiffIndex], pTOAFOA->fTOA[iDiffIndex],
				pTOAFOA->fBeaFOA[iDiffIndex], pTOAFOA->fFOA[iDiffIndex],
				tDiff, fDiff);
			
			sprintf(szFileName, "C:\\HGT\\DBFPassData\\DBF_TOAFOA_Residuals.csv");
			lpToaFoaResidualsFile = fopen(szFileName, "a");

			//double fDesiredOffsetFreqMin = -870.5f
			//double fDesiredOffsetFreqMax = -872.5f
			//double fFOADiffResult = pTOAFOA->fBeaTOA[iDiffIndex] - pTOAFOA->fBeaFOA[iDiffIndex]

			/*if (fFOADiffResult > fDesiredOffsetFreqMin && fFOADiffResult < fDesiredOffsetFreqMax) {

			}*/

			//if (pTOAFOA->fBeaTOA[iDiffIndex] != 0 && pTOAFOA->fBeaFOA[iDiffIndex] != 0) 
			{
				float fTOAdiff = pTOAFOA->fBeaTOA[iDiffIndex] - pTOAFOA->fTOA[iDiffIndex];
				float fFOAdiff = pTOAFOA->fBeaFOA[iDiffIndex] - pTOAFOA->fFOA[iDiffIndex];
				float fDeltaTime = (float)(pTOAFOA->timestamp.intTime - pPassSchedule->rec[iDiffIndex].timestamp.intTime) * 1e-9;
				
				/*printf(" %15s, %03d %02d:%02d:%02d.%06d, %5.2f, TOA %6.3f, %6.3f, FOA %7.1f, %7.1f, %3d\n",
					pTOAFOA->cBeaconID, tmFields.nDay, tmFields.nHour, tmFields.nMinute, tmFields.nSecond, tmFields.lNanosecond / 1000,
					pTOAFOA->fCNR[iDiffIndex], pTOAFOA->fBeaTOA[iDiffIndex],
					pTOAFOA->fTOA[iDiffIndex], pTOAFOA->fBeaFOA[iDiffIndex],
					pTOAFOA->fFOA[iDiffIndex], pTOAFOA->ulSatID[iDiffIndex]);*/

				if (lpToaFoaResidualsFile)
				{
					fprintf(lpToaFoaResidualsFile, "%s, %19I64u, %02d:%02d:%02d.%06d,%f,%5.2f,%6.3f,%6.3f,%7.1f,%7.1f,%d,%7.4f,%7.1f\n",
						pTOAFOA->cBeaconID, pTOAFOA->timestamp, tmFields.nHour, tmFields.nMinute, tmFields.nSecond, tmFields.lNanosecond / 1000,
						fDeltaTime, pTOAFOA->fCNR[iDiffIndex], pTOAFOA->fBeaTOA[iDiffIndex], pTOAFOA->fTOA[iDiffIndex],
						pTOAFOA->fBeaFOA[iDiffIndex], pTOAFOA->fFOA[iDiffIndex], pTOAFOA->ulSatID[iDiffIndex],
						fTOAdiff, fFOAdiff);
				}
			}

			flushall();
			fclose(lpToaFoaResidualsFile);
			lpToaFoaResidualsFile = NULL;
		}
	}

	return bOK;
}
