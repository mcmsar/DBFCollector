 //#include "emstypes.h"

#include "emserror.h"
#include "dbf_iq_demod_lowpass_filters.h"
#include "DBFBeamVectorCalculator.h"
#include "TrackDBFSatellites.h"
ULONG	ulTimeInterval = 30; // 30 secs.
#include <iomanip>
std::ofstream DBFTrackingFile;
std::string GetCurrentDateTimeStringEx ( const EMSTIME& inpTime)
{
	std::stringstream wstrmRet;
	/*CEMSTime timeNow;
	timeNow.SetTime( CEMSSystemClock::GetTime() );*/

	CEMSTime oTime( inpTime );

	EMSTIMEFIELDS tmFields;
	memset( &tmFields, 0, sizeof(EMSTIMEFIELDS) );

	oTime.GetTime( &tmFields );

	wstrmRet << tmFields.nYear << "_" << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMonth << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nDay << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nHour << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nMinute << "_"  << std::setw( 2 ) << std::setfill( '0' ) <<
				tmFields.nSecond;

	return wstrmRet.str();
	
}

void LogSatDetails ( std::fstream& fhLog, const EMSDBFPASSRECORDS& m_aPassSchedule, ULONG totSats)
{
	//std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName /*+ "_" + GetCurrentDateTimeStringEx()*/ + ".csv";
	//std::fstream fhLog( logPath,  std::fstream::out | std::fstream::app  );
	fhLog << totSats <<",";
	//if( !toSats )
	//	return;
	for( int i = 0; i < DBF_MAX_SATELLITES; i++ )
	{
		if( m_aPassSchedule.rec[i].ulSatID == 0 ) 
		{
			//fhLog << "0" << std::endl;
		}
		else
		{
			fhLog << std::fixed << std::setprecision(16) << m_aPassSchedule.rec[i].ulSatID << "," <<
				m_aPassSchedule.rec[i].fPlateAzimuth << "," <<m_aPassSchedule.rec[i].fPlateElevation << "," ;
		}
	}
}
template <typename T>
void LogDouble( const T* input, UINT size,std::string fileName, const EMSDBFPASSRECORDS& m_aPassSchedule, ULONG totSats, const EMSTIME &timeActual ) 
{
	//Log input values	
	std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName + ".csv";
	std::fstream fhLog( logPath,  std::fstream::out | std::fstream::app  );
	fhLog << GetCurrentDateTimeStringEx( CEMSSystemClock::GetTime()) << "," << GetCurrentDateTimeStringEx(timeActual) << ",";
	LogSatDetails( fhLog, m_aPassSchedule,totSats );
	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i] << "," ;	
	}
	fhLog<< std::endl;

	fhLog.close();
}

template <typename T>
void LogComplexD( const T* input, UINT size,std::string fileName,const EMSDBFPASSRECORDS& m_aPassSchedule, ULONG totSats, const EMSTIME &timeActual ) 
{
	//Log input values	
	std::string logPath = "C:\\TEMP\\DBFCovarianceFiles\\" + fileName /*+ "_" + GetCurrentDateTimeStringEx()*/ + ".csv";
	std::fstream fhLog( logPath,  std::fstream::out | std::fstream::app  );
	fhLog << GetCurrentDateTimeStringEx( CEMSSystemClock::GetTime()) << "," << GetCurrentDateTimeStringEx(timeActual) << ",";
	LogSatDetails( fhLog, m_aPassSchedule,totSats );
	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i].re;
		if( input[i].im >= 0)
			fhLog << "+" ;
		fhLog << std::fixed << std::setprecision(16) << input[i].im << "i," ;	
	}
	fhLog<< std::endl;
	fhLog.close();
}
template <typename T>

void LogDBFComplexD( const T* input, UINT size,std::ofstream &fhLog ) 
{
	for (int i = 0; i <  size; i++)
	{
		fhLog << std::fixed << std::setprecision(16) << input[i].re;
		if( input[i].im >= 0)
			fhLog << "+" ;
		fhLog << std::fixed << std::setprecision(16) << input[i].im << "i," ;	
	}
	//fhLog<< std::endl;
	//fhLog.close();
}

CDBFBeamVectorCalculator::CDBFBeamVectorCalculator(CEMSQueue<DBFTrackingData >&dbfBeamVects): m_bRunning(false), 
	m_bIsCalculating(false),m_bInitialized(false),m_asRawTimeSeries(NULL),m_qrefDBFBeamVectors(dbfBeamVects),m_ulSatellites(0),
	m_iPrevPassSchedSATIDs(NULL),m_iBeamIDs(NULL),m_iPredictedSATIDs(NULL),m_dProbability(NULL)
{
	memset( &m_aPassSchedule, 0, sizeof(EMSDBFPASSRECORDS));
	m_timeActual.intTime = 0L;
}
CDBFBeamVectorCalculator::~CDBFBeamVectorCalculator()
{
	delete []m_asMatrix;
	delete []m_acIQMatrix;
	delete []m_iBeamIDs;
	delete []m_iPredictedSATIDs;
	delete []m_dProbability;
	if ( m_hProcessSignal != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hProcessSignal );
		m_hProcessSignal = INVALID_HANDLE_VALUE;
	}
}
void InitializeDBFTrackingFile () 
{
	DBFTrackingFile.open( "C:\\TEMP\\DBFCovarianceFiles\\DBFTracking.csv", std::ios::out | std::ios::app );
	DBFTrackingFile << "CurrTimeStampe,BufferTime,PrevSchedulerSatIDs,,,,,,,,,,CurrentSatIds,,,,,,,,,,SatElevation,,,,,,,,,,m_iBeamIDs,,,,,,,,,,m_iPredictedSATIDs \
		,,,,,,,,,,newBeamIds,,,,,,,,,, newPredSatIds,,,,,,,,,,m_dProbability,,,,,,,,,,DBFBeamVectors" << std::endl;
}
EMS_RESULT  CDBFBeamVectorCalculator::Initialize( )
{
	m_asMatrix = new float[ NUM_CHANNELS*DBF_SAMPLE_SIZE ];
	m_ulSamplesPerChannel = DBF_SAMPLE_SIZE;
	m_ulChannels   = DBF_MAX_CHANNELS;
	m_asRawTimeSeries = new unsigned long[ DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS ];
	m_afTemp1	= new float[DBF_FFT_REAL_SIZE];
	m_acIQMatrix = new EMSCOMPLEXD[NUM_CHANNELS*DBF_SAMPLE_SIZE];
	memset(m_acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEXD));	
	m_bInitialized = true;
	m_acDBFBeamVectors = new EMSCOMPLEXD[MAX_BEAMS*NUM_CHANNELS]; 
	memset( m_acDBFBeamVectors,0, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));	

	m_iBeamIDs = new int[ MAX_BEAMS ];
	memset( m_iBeamIDs , 0 , MAX_BEAMS * sizeof(int) );
	m_iPredictedSATIDs = new int[ MAX_BEAMS ];
	memset( m_iPredictedSATIDs, 0 , MAX_BEAMS * sizeof(int) );
	m_dProbability = new double[ MAX_BEAMS];
	std::fill_n(m_dProbability, MAX_BEAMS, 0.0);

	m_iPrevPassSchedSATIDs = new int[ MAX_BEAMS ];
	memset( m_iPrevPassSchedSATIDs, 0 , MAX_BEAMS * sizeof(int) );
	memset( m_asRawTimeSeries, 0, DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long) );
	m_hProcessSignal = CreateEvent( NULL, FALSE, FALSE, NULL );
	//InitializeDBFTrackingFile();
	return S_OK;
}


void LogDBFTrackingData( int *prevSchedulerSatIDs, int *currSchedulerSatIDs, int *prevBeamIDs, int *newBeamIDs, int * prevPredSatIDs, 
	int *newPredSatIDs, double *probability , const EMSTIME &timeActual, const EMSDBFPASSRECORDS& m_aPassSchedule, const EMSCOMPLEXD* input, UINT size)
{
	//LogDBFTrackingData( prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs,newBeamIds, newPredSatIds, m_dProbability );
	if( !prevSchedulerSatIDs || !currSchedulerSatIDs || !prevBeamIDs || !newBeamIDs || !prevPredSatIDs || !newPredSatIDs || !probability )
		return;
	DBFTrackingFile << GetCurrentDateTimeStringEx( CEMSSystemClock::GetTime()) << "," << GetCurrentDateTimeStringEx(timeActual) << ",";

	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << prevSchedulerSatIDs[i] << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << currSchedulerSatIDs[i] << "," ;
	for( int i = 0; i < DBF_MAX_SATELLITES; i++ )
		DBFTrackingFile << std::fixed << std::setprecision(16) << m_aPassSchedule.rec[i].fElevation << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << prevBeamIDs[i] << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << newBeamIDs[i] << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << prevPredSatIDs[i] << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << newPredSatIDs[i] << "," ;
	for ( int i = 0; i < MAX_BEAMS; i++ )
		DBFTrackingFile << probability[i]  << "," ;
	LogDBFComplexD( input,size, DBFTrackingFile );
	DBFTrackingFile << std::endl;
	//Log 

}

void
CDBFBeamVectorCalculator::Start()
{
	if(!m_bInitialized)
	{
		Initialize();
	}
	m_bRunning = true;
	start();
}

void
CDBFBeamVectorCalculator::Stop()
{
	SetEvent(m_hStopEvent);
//	stop();
}

EMS_RESULT
CDBFBeamVectorCalculator::SetRawData( const unsigned char* abytes, int iSize, const EMSDBFPASSRECORDS& dbfPassRecs )
{
	EMS_RESULT hr = EMS_BAD_PARAM;


	

	if( ( m_bIsCalculating == false ) && m_asRawTimeSeries && abytes )
	{
		if( (iSize - 8) <=  (DBF_SAMPLE_SIZE * DBF_MAX_CHANNELS * sizeof(unsigned long)) )
		{
			memcpy(m_asRawTimeSeries, abytes, iSize - 8 );// make it a const.
			m_aPassSchedule = dbfPassRecs;
			if( iSize == 128000008 )
			{
				INT64* pTM = (INT64*)&(abytes[iSize - 9]);
				m_timeActual.intTime = (*pTM);
			}
			hr = EMS_OK;
			SetEvent( m_hProcessSignal);

			//m_ulRawBuffSize = iSize - 8;
		}
	}
	else
	{
		//m_ulRawBuffSize = 0;
	}

	return hr;

	
}

EMS_RESULT CDBFBeamVectorCalculator::_DBFProcessor8Impl( )
{
	m_ulSatellites = 0;
	//for( int i = 0; i < 4; i++ )
	for( int i = 0; i < DBF_MAX_SATELLITES; i++ )
	{
		if( m_aPassSchedule.rec[i].ulSatID > 0 ) m_ulSatellites++;
	}
	if( !m_ulSatellites )
		return E_FAIL;
	EMSCOMPLEXD  acCovarianceMatrix[NUM_CHANNELS*NUM_CHANNELS];	
	memset(acCovarianceMatrix, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));	
	float EigenValues[NUM_CHANNELS];
	MKL_Complex8 acEigenVectors[NUM_CHANNELS*NUM_CHANNELS];
	EMSCOMPLEXD acNormalizedEigenVectors[NUM_CHANNELS*NUM_CHANNELS];	
	m_bIsCalculating = true;
	INT nNumBeams = 6;
	//commented for testing
	nNumBeams = m_ulSatellites;
	/*if( nNumBeams < 6 )
		nNumBeams = 6;*/

	EMS_RESULT hr = ComputeCovarianceMatrix10( m_acIQMatrix,acCovarianceMatrix );
	std::stringstream str1;
	str1 << " Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( m_timeActual );
				
	if( hr != EMS_OK )
	{
		str1 << " Error in CDBFBeamVectorCalculator::ComputeCovarianceMatrix10 " << std::endl;
		//OutputDebugString( str1.str().c_str() );
	}
	else
	{
		str1 << " CDBFBeamVectorCalculator::ComputeCovarianceMatrix10 success " << std::endl;
		//OutputDebugString( str1.str().c_str() );
	}
	
	std::stringstream ostr;
	ostr<< "Time:" << CEMSConversionUtil::ConvertToDateTimeHiResString2A(  m_timeActual) <<
		"CDBFBeamVectorCalculator::Proc8 start beams" << nNumBeams << std::endl;
	//OutputDebugString( ostr.str().c_str() );


	EMSCOMPLEXD acDBFBeamVectors[MAX_BEAMS*NUM_CHANNELS]; 

	if ( (EMS_OK == hr) && (nNumBeams <= MAX_BEAMS) )
	{	
		hr = ComputeDBFBeamVectors(acCovarianceMatrix, nNumBeams, EigenValues, acEigenVectors,acNormalizedEigenVectors, acDBFBeamVectors );
		std::stringstream str2;
		str2 << " Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( m_timeActual );
		if (EMS_OK == hr)
		{
			str2 << "ComputeDBFBeamVectors success" << std::endl;
			//OutputDebugString( str2.str().c_str() );
		}
		else
		{
			str2 << "CDBFBeamVectorCalculator::ComputeDBFBeamVectors error " << std::endl;
			//OutputDebugString( str2.str().c_str() );

		}
		
		//m_qrefDBFBeamVectors.InsertAtFirst( acDBFBeamVectors );
		std::stringstream str3;
		str3 << "CDBFBeamVectorCalculatorEnd Timestamp: " << CEMSConversionUtil::ConvertToDateTimeHiResString2A( m_timeActual );
		str3 << " Before inserting into q " << "DBFBeamVect100 " << acDBFBeamVectors[99].re << "," << acDBFBeamVectors[99].im << std::endl ;
		//OutputDebugString( str3.str().c_str() );
		_BuildDBFSatsTrackingInfo( acDBFBeamVectors );
		//memcpy( acDBFBeamVectors, m_qrefDBFBeamVectors.ReadFirst(  ), MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
		
		/*LogComplexD( acDBFBeamVectors,MAX_BEAMS*NUM_CHANNELS,"acDBFBeamVectors", m_aPassSchedule, m_ulSatellites,m_timeActual);
		LogDouble( EigenValues, 31, "EigenValues",m_aPassSchedule, m_ulSatellites,m_timeActual);*/
	}

	m_bIsCalculating = false;

	return hr;
}

BOOL CDBFBeamVectorCalculator::_BuildDBFSatsTrackingInfo( EMSCOMPLEXD* acDBFBeamVectors)
{
	//call tracking function..
		CTrackDBFSatellites objTrackSats;
		//read existing values
		int CurrentSatIds [ MAX_BEAMS ];
		memset( CurrentSatIds, 0, sizeof(int) * MAX_BEAMS );
		//read from q
		EMSCOMPLEXD *prevDBFBeamVectors = m_qrefDBFBeamVectors.ReadFirst( ).dbfBeamVector;
		int *prevSchedulerSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).schedulerSatIds;
		int *prevPredSatIDs = m_qrefDBFBeamVectors.ReadFirst( ).predSatIDs;
		int *prevBeamIds = m_qrefDBFBeamVectors.ReadFirst( ).predBeamIDs;
		double *prevProbability = m_qrefDBFBeamVectors.ReadFirst( ).probability;
		int	prevNumBeams = m_qrefDBFBeamVectors.ReadFirst( ).numBeams;
		bool bFirstRun = false;
		//end
		for( int i = 0; i < m_ulSatellites; i++ )
		{
			CurrentSatIds[i] = m_aPassSchedule.rec[i].ulSatID;
			if( !prevDBFBeamVectors && !prevBeamIds )
			{
				//first time so set default beam ids
				m_iBeamIDs[i] = i+1;
				bFirstRun = true;
			}
		}
		if( bFirstRun  )
		{
			DBFTrackingData obj;
			memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
			obj.dbfBeamVector = m_acDBFBeamVectors;
			obj.predBeamIDs = m_iBeamIDs;
			memcpy( m_iPredictedSATIDs, CurrentSatIds, MAX_BEAMS * sizeof(int) );
			obj.predSatIDs = m_iPredictedSATIDs;
			obj.probability = m_dProbability;
			memcpy( m_iPrevPassSchedSATIDs, CurrentSatIds, sizeof(int) * MAX_BEAMS );
			obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
			obj.numBeams = m_ulSatellites;
			m_qrefDBFBeamVectors.InsertAtFirst( obj );
			return true;
		}
		const double Tup = 0.6;
		const double Tlo = 0.45;
		INT nNumBeams = m_ulSatellites;
		int *newBeamIds = new int[ MAX_BEAMS ];
		memset( newBeamIds, 0, sizeof(int) * MAX_BEAMS );
		int *newPredSatIds = new int [ MAX_BEAMS ];
		memset( newPredSatIds, 0, sizeof(int) * MAX_BEAMS );
		objTrackSats.perform_dbf_beam_and_sat_tracking( prevDBFBeamVectors, prevNumBeams, acDBFBeamVectors, nNumBeams,
														prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs, Tup, Tlo,
														newBeamIds, newPredSatIds, m_dProbability );
		//Log
		/*LogDBFTrackingData( prevSchedulerSatIDs,CurrentSatIds,m_iBeamIDs,m_iPredictedSATIDs,newBeamIds, newPredSatIds, m_dProbability, m_timeActual, m_aPassSchedule 
		,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS  );*/
		//end
		memcpy( m_iBeamIDs, newBeamIds, sizeof(int) * MAX_BEAMS );														
		memcpy( m_iPredictedSATIDs, newPredSatIds, MAX_BEAMS * sizeof(int) );
		DBFTrackingData obj;
		memcpy( m_acDBFBeamVectors,acDBFBeamVectors, MAX_BEAMS*NUM_CHANNELS*sizeof(EMSCOMPLEXD) );
		obj.dbfBeamVector = m_acDBFBeamVectors;
		obj.predBeamIDs = m_iBeamIDs;
		obj.predSatIDs = m_iPredictedSATIDs;
		obj.probability = m_dProbability;
		memcpy( m_iPrevPassSchedSATIDs, &CurrentSatIds, sizeof(int) * MAX_BEAMS );
		obj.schedulerSatIds = m_iPrevPassSchedSATIDs;
		obj.numBeams = nNumBeams;
		//obj.schedulerSatIds = 
		//m_qrefDBFBeamVectors.InsertAtFirst( acDBFBeamVectors );
		m_qrefDBFBeamVectors.InsertAtFirst( obj );
		delete []newBeamIds;
		delete []newPredSatIds;
		return TRUE;
}






EMS_RESULT  CDBFBeamVectorCalculator::ComputeNullingVectors(const EMSCOMPLEXD *acEigenVectors, 
                                  const int nNumBeams, EMSCOMPLEXD *acDBFBeamVectors)
{   
  EMS_RESULT hr = EMS_FALSE;
  
  int DEBUG;
  
  //row major storage assumed for all matrices and vectors defined below
  EMSCOMPLEXD acVectors[NUM_CHANNELS*(MAX_BEAMS-1)];
  EMSCOMPLEXD acA[NUM_CHANNELS*(MAX_BEAMS-1)]; //A
  EMSCOMPLEXD acAt[(MAX_BEAMS-1)*NUM_CHANNELS]; //A transposed
  EMSCOMPLEXD acAh[(MAX_BEAMS-1)*NUM_CHANNELS]; //A' =conj(A transposed) = hermitian transpose of A
  EMSCOMPLEXD acAhA[(MAX_BEAMS-1)*(MAX_BEAMS-1)]; //A'*A
  EMSCOMPLEXD acinvAhA[(MAX_BEAMS-1)*(MAX_BEAMS-1)]; //inv(A'*A)
  EMSCOMPLEXD acinvAhAAh[(MAX_BEAMS-1)*NUM_CHANNELS]; //inv(A'*A)*A'
  EMSCOMPLEXD acAinvAhAAh[NUM_CHANNELS*NUM_CHANNELS];//A*inv(A'*A)*A'
  EMSCOMPLEXD u[NUM_CHANNELS], v[NUM_CHANNELS], w[NUM_CHANNELS];
  
  memset( acVectors, 0, NUM_CHANNELS*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acA, 0, NUM_CHANNELS*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acAt, 0,(MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAh, 0,(MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAhA, 0, (MAX_BEAMS-1)*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acinvAhA, 0, (MAX_BEAMS-1)*(MAX_BEAMS-1) * sizeof( EMSCOMPLEXD) );
  memset( acinvAhAAh, 0, (MAX_BEAMS-1)*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( acAinvAhAAh, 0, NUM_CHANNELS*NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( u,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( v,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  memset( w,0, NUM_CHANNELS * sizeof( EMSCOMPLEXD) );
  
  if (nNumBeams <= MAX_BEAMS)
  {
      if (nNumBeams == 1)
      {
		   for(int ichan=0; ichan<NUM_CHANNELS; ichan++)
		   {
				acDBFBeamVectors[ichan] = acEigenVectors[ichan];
		   }
		   
		   hr= 1;
      } 
      else if (nNumBeams > 1)
      {
           for(int iBeam = 0; iBeam < nNumBeams; iBeam++)
           {
                int l = 0;
                for ( int jBeam = 0; jBeam < nNumBeams; jBeam++ )
                {
				    if ( !( jBeam == iBeam ) )
				    {
						  for ( int ichan = 0; ichan < NUM_CHANNELS; ichan++ )
						  {
							  acVectors[l++] = acEigenVectors[jBeam*NUM_CHANNELS+ichan];
							  // row major storage assumed here !!!
						  }
				    }
				}
				DEBUG=0;
				
		   
		        //myConj( acVectors, acAh, (nNumBeams-1)*NUM_CHANNELS);
				emscbConj2d( acVectors, acAh, (nNumBeams-1)*NUM_CHANNELS);
				DEBUG=0;
				
				
		        //myMatrixTransposeC( acVectors, acA, NUM_CHANNELS, nNumBeams-1); 
				emscbMatrixTransposed( acVectors, acA, NUM_CHANNELS, nNumBeams-1); 

                DEBUG=0;
				

                //myMatrixMultiplyC_row( acAh, nNumBeams-1, NUM_CHANNELS, acA,  NUM_CHANNELS,nNumBeams-1, acAhA );
				emscbMatrixMultiplyd( acAh, nNumBeams-1, NUM_CHANNELS, acA,  NUM_CHANNELS,nNumBeams-1, acAhA );
				
                hr = _ComplexMatrixInverse( acAhA, acinvAhA, nNumBeams-1); 
				
			   if (EMS_OK == hr)
			   {
					//myMatrixMultiplyC_row( acinvAhA,  nNumBeams-1, nNumBeams-1,acAh,  nNumBeams-1,NUM_CHANNELS, acinvAhAAh );
					emscbMatrixMultiplyd( acinvAhA,  nNumBeams-1, nNumBeams-1,acAh,  nNumBeams-1,NUM_CHANNELS, acinvAhAAh );
					
					//myMatrixMultiplyC_row( acA,  NUM_CHANNELS, nNumBeams-1,acinvAhAAh,  nNumBeams-1,nNumBeams-1, acAinvAhAAh );
					//myMatrixMultiplyC_row( acA,  NUM_CHANNELS, nNumBeams-1,acinvAhAAh,  nNumBeams-1,NUM_CHANNELS, acAinvAhAAh );
					emscbMatrixMultiplyd( acA,  NUM_CHANNELS, nNumBeams-1,acinvAhAAh,  nNumBeams-1,NUM_CHANNELS, acAinvAhAAh );
					
					
					for (int ichan=0; ichan< NUM_CHANNELS; ichan++)
					{
						u[ichan]= acEigenVectors[iBeam*NUM_CHANNELS+ichan];
					}             
	  
					//myMatrixMultiplyC_row(acAinvAhAAh, NUM_CHANNELS,NUM_CHANNELS, u, NUM_CHANNELS,1, v);
					emscbMatrixMultiplyd(acAinvAhAAh, NUM_CHANNELS,NUM_CHANNELS, u, NUM_CHANNELS,1, v);
					
					for (int ichan=0; ichan< NUM_CHANNELS; ichan++)
					{
						// no normalization performed here
						acDBFBeamVectors[iBeam*NUM_CHANNELS+ichan].re = u[ichan].re-v[ichan].re;
						acDBFBeamVectors[iBeam*NUM_CHANNELS+ichan].im = u[ichan].im-v[ichan].im;
					} 


                    DEBUG=0;
					
					hr = EMS_OK;
				} 
		   }				
        }
    }else
    {
	   return EMS_FALSE;
    }
    return hr;       
}                           



EMS_RESULT  
CDBFBeamVectorCalculator::PerformEigenVectorNormalization(const MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors)
{
	double amp;
	double x,y;
	
	memset(acNormalizedEigenVectors, 0, NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEXD));
	
	for (int i =0; i<NUM_CHANNELS; i++)
	{
		for (int j=0;j<NUM_CHANNELS;j++)
		{
			x=acEigenVectors[i*NUM_CHANNELS+j].real;
			y=acEigenVectors[i*NUM_CHANNELS+j].imag;
			amp= sqrt(x*x+y*y);
			if (amp>0.0)
			{
				acNormalizedEigenVectors[i*NUM_CHANNELS+j].re =	acEigenVectors[i*NUM_CHANNELS+j].real/amp;
			    acNormalizedEigenVectors[i*NUM_CHANNELS+j].im =	acEigenVectors[i*NUM_CHANNELS+j].imag/amp;
			}			
		}
	}
    
    return EMS_OK;
	
}


EMS_RESULT CDBFBeamVectorCalculator::PerformEigenDecomposition(const EMSCOMPLEXD *acCovarianceMatrix, 
                              float *EigenValues, MKL_Complex8 *acEigenVectors)
{
	CHGTEigenVectors eigenVect;
	eigenVect.PerformEigenDecomposition( (MKL_Complex8 *)acCovarianceMatrix, EigenValues, acEigenVectors );
	return S_OK;						 
}

EMS_RESULT  CDBFBeamVectorCalculator::ComputeDBFBeamVectors(const EMSCOMPLEXD *acCovarianceMatrix, const int nNumBeams,
    float *EigenValues,  MKL_Complex8 *acEigenVectors, EMSCOMPLEXD *acNormalizedEigenVectors, EMSCOMPLEXD *acDBFBeamVectors )
{
	  EMS_RESULT hr = EMS_BAD_PARAM;
	  memset(EigenValues,0, NUM_CHANNELS*sizeof(float));
	  memset(acEigenVectors,0,NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  memset(acNormalizedEigenVectors,0,NUM_CHANNELS*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  memset(acDBFBeamVectors,0,nNumBeams*NUM_CHANNELS*sizeof(EMSCOMPLEX));
	  {
		  //m_timeElapsed.FuncTimerStart("PerformEigenDec" );	 
		  hr = PerformEigenDecomposition(acCovarianceMatrix,EigenValues, acEigenVectors);
		  //m_timeElapsed.FuncTimerClose();
	  }
	  //m_timeElapsed.FuncTimerStart("ComputeDBFBmVct" );

	  if(EMS_OK == hr)
	  {
		   hr = PerformEigenVectorNormalization(acEigenVectors, acNormalizedEigenVectors);
	   
		   // Extracting the nNumBeams largest eigenvectors 
		   if (EMS_OK==hr)
		   {
			   EMSCOMPLEXD *acLargestEigenVectors  = new EMSCOMPLEXD[nNumBeams*NUM_CHANNELS];
			   memset(acLargestEigenVectors,0,nNumBeams*NUM_CHANNELS*sizeof(EMSCOMPLEXD));
			  // Extracting the nNumBeams largest eigenvectors
			  for (int  iBeam =0; iBeam<nNumBeams; iBeam++)
			  {
				  for(int ichan=0; ichan<NUM_CHANNELS; ichan++)
				  {
					   acLargestEigenVectors[iBeam*NUM_CHANNELS+ichan] = acNormalizedEigenVectors[(30-iBeam)*NUM_CHANNELS+ichan];
				  }
			  }			  
		  
			  //hr = ComputeNullingVectors(acNormalizedEigenVectors,  nNumBeams, acDBFBeamVectors); 
			   hr = ComputeNullingVectors(acLargestEigenVectors, nNumBeams, acDBFBeamVectors); 	
			   delete [] acLargestEigenVectors;		   
		   }
	 }
	  //m_timeElapsed.FuncTimerClose();

  return hr;
}

void
CDBFBeamVectorCalculator::run()
{
	if( m_bInitialized )
	{
		EMS_RESULT hr = EMS_OK;
		

		HANDLE hEvent[2];

		hEvent[0] = m_hStopEvent;
		hEvent[1] = m_hProcessSignal;

//		hEvent[1] = m_hEvent; //filler event

		DWORD dwTimeout = 400;
		DWORD dwEventCount = 2;
		 
		while( m_bRunning )
		{
			
			try
			{
				hr = WaitForMultipleObjects( dwEventCount, hEvent, FALSE, dwTimeout ); // Wait for the interrupt
				switch(hr)	
				 {						
					case WAIT_OBJECT_0:	
						{
							//stop
							m_bRunning = false;
						}
						break;
					case WAIT_OBJECT_0 + 1:
						{
							int x  = 5;
							//_ProcessData();
							_DBFProcessor8Impl();

						}
						break;
					case WAIT_TIMEOUT:			// timed out
						{
							//_DBFProcessor8Impl();
						}
					default:
						{
							//_ProcessData();
						}
						break;
				}
			}
			catch( ... )
			{
				// a error occured, log it and stop the thread.
				m_bRunning = false;
				
			}
		}

		m_bRunning = false;
	}
}

// Feb. 9, 2021
EMS_RESULT  CDBFBeamVectorCalculator::PerformIQDemodulation10(unsigned long *clpRawTimeSeries, EMSCOMPLEXD *acIQMatrix)
{
    EMS_RESULT hr = EMS_BAD_PARAM;

    const float fc = 0.3;
    const float fScaleFactor = (float)ADC_OFFSET;   // Scale factor for real to integer conversion
    const float fScaleFactorInverse = 1.0 / fScaleFactor;  // Scale factor for integer to real conversion
	
	const double c[20]={
	1.000000000000000,   0.587785252292473,  -0.309016994374947,  -0.951056516295153,  -0.809016994374947,  -0.000000000000000,
    0.809016994374947,   0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292473,
    0.309016994374945,   0.951056516295153,   0.809016994374948,   0.000000000000001,  -0.809016994374947,  -0.951056516295154,
   -0.309016994374948,   0.587785252292474  };
	
	const double s[20] = {
	 0,                  -0.809016994374947,  -0.951056516295154,  -0.309016994374948,   0.587785252292473,   1.000000000000000,
     0.587785252292474,  -0.309016994374947,  -0.951056516295154,  -0.809016994374948,  -0.000000000000000,   0.809016994374947,
     0.951056516295154,   0.309016994374948,  -0.587785252292473,  -1.000000000000000,  -0.587785252292474,   0.309016994374945,
     0.951056516295153,   0.809016994374947 };
		
    if ( clpRawTimeSeries)
    {
        ULONG ichan, jsample, index;
        double dMean   = 0.0;
        double dStdDev = 0.0; 
				 
        memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
        memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE*sizeof(float));
				 
        for ( ichan = 1; ichan < (int)m_ulChannels; ichan++ )
        {
            // Convert integer to float 
            //memset( m_afTemp1, 0, DBF_SAMPLE_SIZE*sizeof(float));
            for ( jsample = 0, index = ichan; jsample < m_ulSamplesPerChannel;  jsample++, index += m_ulChannels )
            {
	              m_afTemp1[jsample] = (float) m_asRawTimeSeries[index] * fScaleFactorInverse;
            }

            dStdDev = _EMSsMeanStdDev( m_afTemp1, m_ulSamplesPerChannel, &dMean );
            if( dStdDev == 0.00 )
                continue;
				 
            //Normalize the raw data sample sequence
            _EMSsbNormalize(m_afTemp1, m_asMatrix+(ichan-1)*DBF_SAMPLE_SIZE, m_ulSamplesPerChannel, dMean, dStdDev);   
   
            																																				
             //Perform frequency shifting by translating 150KHz to 0 KHz
             //memset( acIQSeq, 0, DBF_SAMPLE_SIZE*sizeof(EMSCOMPLEX));
             //for (index = 0; index < DBF_SAMPLE_SIZE; index++)
             //{    
             //     acIQSeq[index].re =  cos(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]);
	         //     acIQSeq[index].im = -sin(index*fc*PI)*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index]); 				  
             //}
			 EMSCOMPLEXD *acIQSeq = new EMSCOMPLEXD[DBF_SAMPLE_SIZE];

			 for (index = 0; index < DBF_SAMPLE_SIZE/20; index++)
             {    
		          for(int j = 0; j < 20; j++)
				  {
                      acIQSeq[index*20+j].re =  c[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]);
	                  acIQSeq[index*20+j].im =  s[j]*(m_asMatrix[(ichan-1)*DBF_SAMPLE_SIZE+index*20+j]); 
				  }				  
             }
			 
#if DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 1
	
             hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 128, acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		 

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 2
	
	         hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 32,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);		

#elif DBF_IQ_DEMOD_LOWPASS_FILTER_OPTION == 3
	
             hr = PerformSymFIRFiltering1( dbf_iq_demod_lowpass_filter, 16,  acIQSeq, DBF_SAMPLE_SIZE, acIQMatrix+(ichan-1)*DBF_SAMPLE_SIZE);	

#endif
			 delete []acIQSeq;
			 acIQSeq = NULL;
        } 
    }
    return hr;
}


// Feb. 9, 2021
EMS_RESULT  CDBFBeamVectorCalculator::ComputeCovarianceMatrix10(EMSCOMPLEXD *acIQMatrix, EMSCOMPLEXD *acCovarianceMatrix)
{

  EMS_RESULT hr = EMS_BAD_PARAM;

  unsigned long *clpRawTimeSeries = m_asRawTimeSeries ;
  
  if ( clpRawTimeSeries)
  {
	 //Perform baseband IQ demodulation
	 memset(m_asMatrix,   0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof(float));
	 memset(acIQMatrix, 0, NUM_CHANNELS*DBF_SAMPLE_SIZE* sizeof( EMSCOMPLEXD ));
	 {
        //m_timeElapsed.FuncTimerStart("PerformIQDemod10" );		
		hr = PerformIQDemodulation10(clpRawTimeSeries, acIQMatrix);
		//m_timeElapsed.FuncTimerClose();
	 }
	 //m_timeElapsed.FuncTimerStart("ComputeCovaMat10");
	 if (EMS_OK == hr)
	 {  
	  //hr = CalculateCovarianceMatrix2(acIQMatrix, acCovarianceMatrix);
		hr = CalculateCovarianceMatrix4(acIQMatrix, acCovarianceMatrix);
		//m_timeElapsed.FuncTimerClose();
	 }                           
  }
  
  return hr;
}







//Feb. 9, 2021
EMS_RESULT  CDBFBeamVectorCalculator::CalculateCovarianceMatrix3( const EMSCOMPLEX *acIQMatrix, EMSCOMPLEX *acCovarianceMatrix)
{
	const int BLEN =32000;
    const int B=(DBF_SAMPLE_SIZE/BLEN); //31;
    const int RLEN=DBF_SAMPLE_SIZE-B*BLEN; //8000;
	int index, i, j, b, k,n, m;
	EMSCOMPLEX buffer[BLEN];
	EMSCOMPLEX temp;
    //upper triangular portion of hermitian matrix
	for(i=0; i<NUM_CHANNELS; i++)
	{
		for(j=i;j<NUM_CHANNELS;j++)
		{
			index=i*NUM_CHANNELS+j;
			acCovarianceMatrix[index].re =0.0;
			acCovarianceMatrix[index].im =0.0;
			for(b=0; b< B; b++)
			{
				n= i*DBF_SAMPLE_SIZE+b*BLEN;
				m= j*DBF_SAMPLE_SIZE+b*BLEN;	
				
				/* 
				for(k=0; k<BLEN; k++)
				{
				    acCovarianceMatrix[index].re +=  
					  ( (acIQMatrix[n+k].re)*(acIQMatrix[m+k].re) 
						+ (acIQMatrix[n+k].im)*(acIQMatrix[m+k].im) );	 
				
				    acCovarianceMatrix[index].im +=   
					  ( (acIQMatrix[m+k].re)*(acIQMatrix[n+k].im) 
						 - (acIQMatrix[n+k].re)*(acIQMatrix[m+k].im) );	
				}	 
				*/
                memset(buffer, 0, sizeof(EMSCOMPLEX)*BLEN);
				emscbConj2(acIQMatrix+m, buffer, BLEN);
				temp = emscDotProd(acIQMatrix+n, buffer,BLEN);
                acCovarianceMatrix[index].re += temp.re;
				acCovarianceMatrix[index].im += temp.im;
			}	
			
			//remainder
			n= i*DBF_SAMPLE_SIZE+B*BLEN;
			m= j*DBF_SAMPLE_SIZE+B*BLEN;	
			/* 
			for(k= 0; k< RLEN; k++)
			{
				acCovarianceMatrix[index].re +=  
					  ( (acIQMatrix[n+k].re)*(acIQMatrix[m+k].re) 
						+ (acIQMatrix[n+k].im)*(acIQMatrix[m+k].im) );	 
				
				acCovarianceMatrix[index].im +=   
					  ( (acIQMatrix[m+k].re)*(acIQMatrix[n+k].im) 
						 - (acIQMatrix[n+k].re)*(acIQMatrix[m+k].im) );	
			}	 
			*/
			memset(buffer, 0, sizeof(EMSCOMPLEX)*RLEN);
			emscbConj2(acIQMatrix+m, buffer, RLEN);
			temp = emscDotProd(acIQMatrix+n, buffer,RLEN);
			acCovarianceMatrix[index].re += temp.re;
			acCovarianceMatrix[index].im += temp.im;
		}
	}
	
	//lower triangular portion 
	for(int i=1; i<NUM_CHANNELS; i++)
	{
		for(int j=i-1;j >= 0;j--)
		{
			acCovarianceMatrix[i*NUM_CHANNELS+j].re = acCovarianceMatrix[j*NUM_CHANNELS+i].re;
			acCovarianceMatrix[i*NUM_CHANNELS+j].im = -acCovarianceMatrix[j*NUM_CHANNELS+i].im;	
		}
	}
	
	
	for( int iIndx = 0; iIndx < NUM_CHANNELS*NUM_CHANNELS; iIndx++ )
	{
		acCovarianceMatrix[iIndx].re /= DBF_SAMPLE_SIZE;
		acCovarianceMatrix[iIndx].im /= DBF_SAMPLE_SIZE;
	}
	
	return EMS_OK;
}


EMS_RESULT  CDBFBeamVectorCalculator::PerformSymFIRFiltering1( const double *SymFirFilter, const int Q, 
      const EMSCOMPLEX *InputArray, const int N, 
            EMSCOMPLEX *OutputArray)
{
	//Q=2M must be even in this implementation and must be less than or equal to 128 !
	
	int index, jsample;
	
	EMS_RESULT hr = EMS_FALSE;
	
	int M = Q/2;
	
	const int BUFFER_LEN = 128/2;
	double buffer_re[BUFFER_LEN];
	double buffer_im[BUFFER_LEN];
	
	//memset(OutputArray, 0, sizeof(EMSCOMPLEX));
	memset(OutputArray, 0, sizeof(EMSCOMPLEX)*N);
	//for (index=0; index< N; index++)
	//{
		//OutputArray[index].re = 0.0;
		//OutputArray[index].im = 0.0;
		/* if (index<Q)
		{
			OutputArray[index].re = 0.0;
		    OutputArray[index].im = 0.0;
			for (jsample=0; jsample <= index; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*InputArray[index-jsample].re;	
				OutputArray[index].im += SymFirFilter[jsample]*InputArray[index-jsample].im;
			}		
		}else
		{ */
	    for(index=Q-1; index<N; index++)
		{
			/* 
			for (jsample=0; jsample < M; jsample++)
			{
				OutputArray[index].re += SymFirFilter[jsample]*(InputArray[index-jsample].re + InputArray[index-(Q-1)+jsample].re );	
				OutputArray[index].im += SymFirFilter[jsample]*(InputArray[index-jsample].im + InputArray[index-(Q-1)+jsample].im );
			}	 
			*/
			for (jsample=0; jsample < M; jsample++)
			{
				buffer_re[jsample] = InputArray[index-jsample].re + InputArray[index-(Q-1)+jsample].re;
				buffer_im[jsample] = InputArray[index-jsample].im + InputArray[index-(Q-1)+jsample].im;
			}
			OutputArray[index].re = emssDotProd64(SymFirFilter, buffer_re, M);
			OutputArray[index].im = emssDotProd64(SymFirFilter, buffer_im, M);
			
		}	
	//}
 
	hr =EMS_OK;
    
	return hr;
}	


//July. 12, 2021
EMS_RESULT  CDBFBeamVectorCalculator::CalculateCovarianceMatrix4( const EMSCOMPLEX *acIQMatrix, EMSCOMPLEX *acCovarianceMatrix)
{
	const int REDUCTION_RATE  = 4;
	
	const int BLEN = 32000/REDUCTION_RATE;
    
	const int B=(DBF_SAMPLE_SIZE/REDUCTION_RATE)/BLEN; 
	
	const int RLEN=DBF_SAMPLE_SIZE/REDUCTION_RATE-B*BLEN;
	
	
	int index, i, j, b, k,n, m;
	int n1=0;
	int n2=0;
	
	/* EMSCOMPLEX buffer[BLEN];
	   EMSCOMPLEX temp; 
	   new[k]= old[k*REDUCTION_RATE], k=0, 1, ... , DBF_SAMPLE_SIZE/REDUCTION_RATE  
	*/
	
    //upper triangular portion of hermitian matrix
	for(i=0; i < NUM_CHANNELS; i++)
	{
		for(j=i;j < NUM_CHANNELS;j++)
		{
			index=i*NUM_CHANNELS+j;
			acCovarianceMatrix[index].re =0.0;
			acCovarianceMatrix[index].im =0.0;
			for(b=0; b< B; b++)
			{
				n= i*DBF_SAMPLE_SIZE/REDUCTION_RATE+b*BLEN;
				m= j*DBF_SAMPLE_SIZE/REDUCTION_RATE+b*BLEN;
				for(k=0; k<BLEN; k++)
				{
					n1=(n+k)*REDUCTION_RATE;
					n2=(m+k)*REDUCTION_RATE;
				    acCovarianceMatrix[index].re +=  ( (acIQMatrix[n1].re)*(acIQMatrix[n2].re) + (acIQMatrix[n1].im)*(acIQMatrix[n2].im) );	 
				
				    acCovarianceMatrix[index].im +=  ( (acIQMatrix[n2].re)*(acIQMatrix[n1].im)  - (acIQMatrix[n1].re)*(acIQMatrix[n2].im) );	
				}

               /* n= i*DBF_SAMPLE_SIZE+b*BLEN;
				  m= j*DBF_SAMPLE_SIZE+b*BLEN;			
				
                memset(buffer, 0, sizeof(EMSCOMPLEX)*BLEN);
				emscbConj2(acIQMatrix+m, buffer, BLEN);
				temp = emscDotProd(acIQMatrix+n, buffer,BLEN);
                acCovarianceMatrix[index].re += temp.re;
				acCovarianceMatrix[index].im += temp.im; */
			}	
			
			//remainder
			n= i*DBF_SAMPLE_SIZE/REDUCTION_RATE+B*BLEN;
			m= j*DBF_SAMPLE_SIZE/REDUCTION_RATE+B*BLEN;	
			
			for(k= 0; k< RLEN; k++)
			{
				n1=(n+k)*REDUCTION_RATE;
				n2=(m+k)*REDUCTION_RATE;
				acCovarianceMatrix[index].re += ( (acIQMatrix[n1].re)*(acIQMatrix[n2].re) + (acIQMatrix[n1].im)*(acIQMatrix[n2].im) );	 
				
				acCovarianceMatrix[index].im += ( (acIQMatrix[n2].re)*(acIQMatrix[n1].im) - (acIQMatrix[n1].re)*(acIQMatrix[n2].im) );	
			}	 	
		}
	}
	
	//lower triangular portion 
	for(int i=1; i<NUM_CHANNELS; i++)
	{
		for(int j=i-1;j >= 0;j--)
		{
			acCovarianceMatrix[i*NUM_CHANNELS+j].re = acCovarianceMatrix[j*NUM_CHANNELS+i].re;
			acCovarianceMatrix[i*NUM_CHANNELS+j].im = -acCovarianceMatrix[j*NUM_CHANNELS+i].im;	
		}
	}
	
	for( int iIndx = 0; iIndx < NUM_CHANNELS*NUM_CHANNELS; iIndx++ )
	{
		acCovarianceMatrix[iIndx].re /= (DBF_SAMPLE_SIZE/REDUCTION_RATE);
		acCovarianceMatrix[iIndx].im /= (DBF_SAMPLE_SIZE/REDUCTION_RATE);
	}
	
	return EMS_OK;
}