
#include "dalresultdecoder.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "dalmsgs.h"
#include <iostream.h>
#include <stdio.h>
#include "convutility.h"

CEMSDALResultDecoder::CEMSDALResultDecoder()
{
}

CEMSDALResultDecoder::~CEMSDALResultDecoder()
{
}

void
CEMSDALResultDecoder::Decode( const unsigned long culRecordSize, const unsigned long culFields,
					const EMSFIELDDESCRIPTOR* caFields, const unsigned long culDataSize,
					const unsigned char* cabyData )
{
	if( !caFields || !cabyData )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	unsigned long ulRecords = culDataSize / culRecordSize;

	cout << ulRecords << " records retrieved." << endl;

	for( unsigned long l3 = 0; l3 < culFields; l3++ )
	{
		if( l3 > 0 )
		{
			printf( ", " );
		}

		printf( "%S", caFields[l3].wszName  );
	}

	printf("\n");

	unsigned char* pbyData = (unsigned char*) cabyData;

	for( unsigned long l = 0; l < ulRecords; l++ )
	{
		for( unsigned long l2 = 0; l2 < culFields; l2++ )
		{
			if( l2 > 0 )
			{
				printf( ", " );
			}
			
			switch( caFields[l2].eType )
			{
				case DBFLDTYPE_SHORT:
						{
							short sVal = 0;
							memcpy( &sVal, pbyData, caFields[l2].lSize );
							printf( "%d", sVal );
						}
						break;
					case DBFLDTYPE_USHORT:
						{
							unsigned short usVal = 0;
							memcpy( &usVal, pbyData, caFields[l2].lSize );
							printf( "%d", usVal );
						}
						break;
					case DBFLDTYPE_LONG:
						{
							long lVal = 0;
							memcpy( &lVal, pbyData, caFields[l2].lSize );
							printf( "%d", lVal );
						}
						break;
					case DBFLDTYPE_ULONG:
						{
							unsigned long ulVal = 0;
							memcpy( &ulVal, pbyData, caFields[l2].lSize );
							printf( "%d", ulVal );
						}
						break;
					case DBFLDTYPE_BIGINT:
						{
							__int64 i64Val = 0;
							memcpy( &i64Val, pbyData, caFields[l2].lSize );
							printf( "%I64d", i64Val );
						}
						break;
					case DBFLDTYPE_UBIGINT:
						{
							unsigned __int64 ui64Val = 0;
							memcpy( &ui64Val, pbyData, caFields[l2].lSize );
							printf( "%I64d", ui64Val );
						}
						break;
					case DBFLDTYPE_WSTRING:
						{
							printf( "%S", CEMSConversionUtil::ConvertToString( caFields[l2].lSize, pbyData ).c_str() );
						}
						break;
					case DBFLDTYPE_STRING:
						{
							printf( "%s", CEMSConversionUtil::ConvertToStringA( caFields[l2].lSize, pbyData ).c_str() );
						}
						break;
					case DBFLDTYPE_BINARY:
					case DBFLDTYPE_LONG_BINARY:
						{
							unsigned char* abyVal = new unsigned char[ caFields[l2].lSize ];

							memcpy( abyVal, pbyData, caFields[l2].lSize );

							printf( "0x" );
							for( long lByte = 0; lByte < caFields[l2].lSize; lByte++ )
							{
								printf( "%x", abyVal[lByte] );
							}

							delete[] abyVal;
							
						}
						break;
					case DBFLDTYPE_FLOAT:
						{
							float fVal = 0;
							memcpy( &fVal, pbyData, caFields[l2].lSize );
							printf( "%f", fVal );
						}
						break;
					case DBFLDTYPE_DOUBLE:
						{
							double dVal = 0;
							memcpy( &dVal, pbyData, caFields[l2].lSize );
							printf( "%f", dVal );
						}
						break;
					case DBFLDTYPE_TINYINT:
						{
							char cVal = 0;
							memcpy( &cVal, pbyData, caFields[l2].lSize );
							printf( "%d", cVal );
						}
						break;
					case DBFLDTYPE_UTINYINT:
						{
							unsigned char ucVal = 0;
							memcpy( &ucVal, pbyData, caFields[l2].lSize );
							printf( "%d", ucVal );
						}
						break;
					default:
						THROW_RUNTIME_EXCEPTION( EMS_DAL_UNKOWN_DATATYPE );
			}

			pbyData += caFields[l2].lSize;
		}

		printf("\n");
	}
}