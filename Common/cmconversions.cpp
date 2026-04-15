#include "iconfigmanager.h"
#include <emstime.h>

#include <sstream>

void
vart_to_string( const EMSVARITYPE* const pVaritype,
			    std::wstringstream& wszValue )
{
	if( pVaritype )
	{
		switch ( pVaritype->dataType )
		{
		case EMSVARITYPE_DATATYPE_BOOL:
			wszValue << ((0 == pVaritype->bVal) ? L"false" : L"true");
			break;
		
		case EMSVARITYPE_DATATYPE_STRING:
			wszValue << pVaritype->pwcsVal;
			break;
		
		case EMSVARITYPE_DATATYPE_TIME:
			{
				CEMSTime timeTemp( pVaritype->tmVal );
				EMSTIMEFIELDS  timeFields;
				double         dSeconds = 0.0;
				
				timeTemp.GetTime( &timeFields );
				
				dSeconds = (double)timeFields.nSecond;
				dSeconds += ( (double)timeFields.lNanosecond / 1000000000.0 );
				
				wchar_t wdatetime[512];
				memset( wdatetime, 0, sizeof( wdatetime ) );

				swprintf( wdatetime, 
					      L"%02i %03i %02i%02i %09.6lf", 
						  (timeFields.nYear - 2000),
						  timeFields.nJulianDay,
						  timeFields.nHour, 
						  timeFields.nMinute, 
						  dSeconds );

				wszValue << wdatetime;
				break;
			}

		case EMSVARITYPE_DATATYPE_BIGINT:
			{
				wchar_t wBigInt[128];
				swprintf( wBigInt, L"%I64i", pVaritype->i64Val );
				wszValue << wBigInt;
				
				break;   
			}

		case EMSVARITYPE_DATATYPE_INT:
			wszValue << pVaritype->iVal;
			break;

		case EMSVARITYPE_DATATYPE_INTRANGE:
			wszValue << pVaritype->iRange.iMinVal 
				     << L":" 
				     << pVaritype->iRange.iMaxVal;
			break;

		case EMSVARITYPE_DATATYPE_UINT:
			wszValue << pVaritype->uiVal;
			break;
		
		case EMSVARITYPE_DATATYPE_UINTRANGE:
			wszValue << pVaritype->uiRange.uiMinVal 
				     << L":" 
					 << pVaritype->uiRange.uiMaxVal;
			break;
		
		case EMSVARITYPE_DATATYPE_DOUBLE:
			wszValue << pVaritype->dVal;
			break;

		case EMSVARITYPE_DATATYPE_DOUBLERANGE:
			wszValue << pVaritype->dRange.dMinVal 
					 << L":" 
					 << pVaritype->dRange.dMaxVal;
			break;

		case EMSVARITYPE_DATATYPE_FLOAT:
			wszValue << pVaritype->fVal;
			break;
		
		case EMSVARITYPE_DATATYPE_FLOATRANGE:
			wszValue << pVaritype->fRange.fMinVal 
					 << L":" 
					 << pVaritype->fRange.fMaxVal;
			break;
		
		default:
			break;
		}
	}
}


EMS_RESULT
cm_getstring( IEMSConfigurationManager* pICM,
			  const wchar_t* wszGroup,
			  const wchar_t* wszGroupID,
			  const wchar_t* wszKeyName,
			  std::wstringstream& wszValue )
{
	EMS_RESULT retVal = EMS_OK;

	if( pICM && wszGroup && wszGroupID && wszKeyName )
	{
		const wchar_t* apwcsKeyNames[1]   = { wszKeyName };
		
		EMSCONFIGURATIONITEM    aConfigData[3];
		int                     nCount = 0;
		
		EMSVARITYPE varData;

		memset( aConfigData, 0, sizeof(aConfigData) );
		memset( &varData, 0, sizeof(varData) );

		retVal = pICM->GetEx( wszGroup, wszGroupID, apwcsKeyNames, 1,
                                        aConfigData, &nCount  );

		if( EMS_OK == retVal )
		{
			for( int ii = 0; ii < nCount; ii++ )
			{
				for ( int jj = 0; jj < aConfigData[ii].uiValues; jj++ )
				{
					vart_to_string( &(aConfigData[ii].ValueList[jj]), wszValue );
					if ( (jj + 1) < aConfigData[ii].uiValues )
					{
						wszValue << L";";
					}
					
					if( ( EMSVARITYPE_DATATYPE_STRING == aConfigData[ii].ValueList[jj].dataType )
						&& ( aConfigData[ii].ValueList[jj].pwcsVal ) )
					{
						CoTaskMemFree( aConfigData[ii].ValueList[jj].pwcsVal );
					}
				}
				
				CoTaskMemFree( aConfigData[ii].ValueList );
				CoTaskMemFree( aConfigData[ii].pwcsKeyName );
			}
		}
	}
	else
	{
		retVal = EMS_BAD_PARAM;
	}

	return retVal;
}

		  