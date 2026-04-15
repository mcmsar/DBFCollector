#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "statusbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSStatusBinStrm::CEMSStatusBinStrm()
{
}

CEMSStatusBinStrm::CEMSStatusBinStrm( const CEMSStatusBinStrm& statusStrm )
{
}

CEMSStatusBinStrm::~CEMSStatusBinStrm()
{
}

EMSVARIANTRECORD*
CEMSStatusBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSLEOSTATUSUPDATE status;
		memset( &status, 0, sizeof(EMSLEOSTATUSUPDATE) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &status, sizeof(EMSLEOSTATUSUPDATE), &ulRead );

        if( EMS_EOF == hr )
        {
        }
        else if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
        else
        {
		    pRecord = new EMSVARIANTRECORD;

		    if( !pRecord )
		    {
			    THROW_NOMEMORY_EXCEPTION();
		    }

            switch( status.type )
            {
            case EMSAntennaStatus:
                pRecord->eType = EMSRT_ANTENNA;
                break;
            case EMSCollectorStatus:
                pRecord->eType = EMSRT_COLLECTOR;
                break;
            case EMSWidebandStatus:
                pRecord->eType = EMSRT_WIDEBAND_STATS;
                break;
            case EMSCommsStatus:
                pRecord->eType = EMSRT_COMMS_STATS;
                break;
            case EMSPassSummaryStatus:
                pRecord->eType = EMSRT_PASS_STATS;
                break;
            case EMSCalibrate406Status:
                pRecord->eType = EMSRT_LEO_CALIB406_STATS;
                break;
            case EMSCalibrateCBCStatus:
                pRecord->eType = EMSRT_CALIBCBC_STATS;
                break;
            case EMSOrbitDetermineStatus:
                pRecord->eType = EMSRT_ORBIT_STATS;
                break;
            case EMSLocationStatus:
                pRecord->eType = EMSRT_LOCATE_STATS;
                break;
            case EMSTCalStatus:
                pRecord->eType = EMSRT_SARP_CALIB_STATS;
                break;
            case EMSCombine406Status:
                pRecord->eType = EMSRT_COMB406_STATS;
                break;
            case EMSCalibrateSarrStatus:
                pRecord->eType = EMSRT_SARR_CALIB_STATS;
                break;
            case EMSSensorStatusEx:
                pRecord->eType = EMSRT_SENSOR;
                break;
            case EMSGeoSummary:
                pRecord->eType = EMSRT_GEO_STATS;
                break;
            case EMSGeoCalib406Status:
                pRecord->eType = EMSRT_GEO_CALIB406_STATS;
                break;
			case EMSLutStatus:
				pRecord->eType = EMSRT_LUT_STATUS;
				break;
            default:
                pRecord->eType = EMSRT_STAT_SUMMARY;
                break;
            }
		    memcpy( &(pRecord->data.status), &status, sizeof(EMSLEOSTATUSUPDATE) );
        }
	}
	catch( ... )
	{
		if( pRecord )
		{
			delete pRecord;
			pRecord = 0;
		}

		throw;
	}

	return pRecord;
}

void
CEMSStatusBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.status), sizeof(EMSLEOSTATUSUPDATE), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSStatusBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSLEOSTATUSUPDATE status;
		memset( &status, 0, sizeof(EMSLEOSTATUSUPDATE) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &status, sizeof(EMSLEOSTATUSUPDATE), &ulRead );

        if( EMS_EOF == hr )
        {
        }
        else if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
        else
        {
		    pRecord = new EMSVARIANTRECORD2;

		    if( !pRecord )
		    {
			    THROW_NOMEMORY_EXCEPTION();
		    }

            switch( status.type )
            {
            case EMSAntennaStatus:
                pRecord->eType = EMSRT_ANTENNA;
                break;
            case EMSCollectorStatus:
                pRecord->eType = EMSRT_COLLECTOR;
                break;
            case EMSWidebandStatus:
                pRecord->eType = EMSRT_WIDEBAND_STATS;
                break;
            case EMSCommsStatus:
                pRecord->eType = EMSRT_COMMS_STATS;
                break;
            case EMSPassSummaryStatus:
                pRecord->eType = EMSRT_PASS_STATS;
                break;
            case EMSCalibrate406Status:
                pRecord->eType = EMSRT_LEO_CALIB406_STATS;
                break;
            case EMSCalibrateCBCStatus:
                pRecord->eType = EMSRT_CALIBCBC_STATS;
                break;
            case EMSOrbitDetermineStatus:
                pRecord->eType = EMSRT_ORBIT_STATS;
                break;
            case EMSLocationStatus:
                pRecord->eType = EMSRT_LOCATE_STATS;
                break;
            case EMSTCalStatus:
                pRecord->eType = EMSRT_SARP_CALIB_STATS;
                break;
            case EMSCombine406Status:
                pRecord->eType = EMSRT_COMB406_STATS;
                break;
            case EMSCalibrateSarrStatus:
                pRecord->eType = EMSRT_SARR_CALIB_STATS;
                break;
            case EMSSensorStatusEx:
                pRecord->eType = EMSRT_SENSOR;
                break;
            case EMSGeoSummary:
                pRecord->eType = EMSRT_GEO_STATS;
                break;
            case EMSGeoCalib406Status:
                pRecord->eType = EMSRT_GEO_CALIB406_STATS;
                break;
			case EMSLutStatus:
				pRecord->eType = EMSRT_LUT_STATUS;
				break;
            default:
                pRecord->eType = EMSRT_STAT_SUMMARY;
                break;
            }
		    memcpy( &(pRecord->data.status), &status, sizeof(EMSLEOSTATUSUPDATE) );
        }
	}
	catch( ... )
	{
		if( pRecord )
		{
			delete pRecord;
			pRecord = 0;
		}

		throw;
	}

	return pRecord;
}

void
CEMSStatusBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.status), sizeof(EMSLEOSTATUSUPDATE), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}