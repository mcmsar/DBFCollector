#pragma message( "!!!!!!!!!!!!!!!!_AllocSolutions() prevents large SIT172 messages (ie. with many alerts) from being parsed properly!!!!!!!!!!")

/********************************************************************
*	Module:			emsit172.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSit172
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	Copyright (c) 2001-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include <stdio.h>
#include <array.h>
#include "emscom.h"
#include "emstypes.h"
#include "emsit172.h"
#include "sitfield.h"
#include "emsbeacon.h"
#include "cbcnmsgdecode.h"

const TCHAR c_szSit172HdrFmt[ ] = TEXT("/%03d/%04d/%03d/%02d");
const TCHAR c_szSit172SolnHdr1Fmt[] = TEXT("/%04d/%s/%s/%02d");
const TCHAR c_szSit172SolnHdr2Fmt[] = TEXT("/%s");
const TCHAR c_szSit172SolnHdr3Fmt[] = TEXT("/%05d/%02d/%02d/%s/%08.3lf/%s/%s/%I64X/%s");
//const TCHAR c_szSit172SolnHdr4Fmt[] = TEXT("/%I64X/%07.3lf/%07.3lf");
const TCHAR c_szSit172SolnHdr4Fmt[] = TEXT("/%I64X");

CEMSSit172::CEMSSit172()
{
	m_bInvertedFSOnly = true; // by default
	m_i64BeaconPrefix = 0;
	m_i64BeaconMask = 0;

	SetSitNumber(172);
	SetMaxAlertCount( EMS_MAX_SIT172_ALERTS );

	m_bcnFirstMsg.SetUpdateMode( EMSBTC_UpdateNever );
}

CEMSSit172::~CEMSSit172()
{
	Reset();

}

void CEMSSit172::Reset( void )
{
	CEMSSitAlertMessageBase::Reset();

	SetAlertCount( 0 );
	SetSitNumber(172);
	SetMaxAlertCount( EMS_MAX_SIT172_ALERTS );
}

EMS_RESULT CEMSSit172::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szBuffer[256], szBeaconMsg[36];
	CBeaconMsg bcnMsg;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		try
		{
			for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
			{
				LPEMSSITLOCALERTSOLUTION lpSoln = _GetSolutionPtr(i);

				if ( lpSoln )
				{
			   	// Number of Bursts Used
					int nNumPoints = lpSoln->sideA.nNumPoints;	//MF21

					if ( 0 == nNumPoints )	// if non used - report number of bursts
						nNumPoints = lpSoln->hdr.nNumPoints;

					if ( nNumPoints > 99 ) 
						nNumPoints = 99;

   				if ( nNumPoints < 1 )
   					nNumPoints = 1;

					for ( int j = 0; j < 15; j++ )
					{
						sprintf( &szBeaconMsg[j*2], "%02X", lpSoln->hdr.cBeaconMsg[3+j] );
					}

					bcnMsg.Set( lpSoln->hdr.cBeaconMsg );

					sprintf( szBuffer, c_szSit172SolnHdr1Fmt, 
							lpSoln->hdr.nPrimaryLutID,	//MF11

							msgField.TextMF13( lpSoln->sideA.dBias,
									lpSoln->sideA.dBSdev,
									lpSoln->sideA.dDrift ),

							msgField.TextMF14( lpSoln->sideA.timeTCA ),

							nNumPoints // MF21
					 	);

					hr = WriteLine( lpStream, szBuffer );

					if ( hr == EMS_OK )
					{
						sprintf( szBuffer, c_szSit172SolnHdr2Fmt, szBeaconMsg); //MF23

						hr = WriteLine( lpStream, szBuffer );
					}

					if ( EMS_OK == hr )
					{
						TCHAR szAttr[132]="";
						bool bAdded = false;

						if ( bcnMsg.IsStandard( ) )
						{
							lstrcat( szAttr, TEXT("STD" ) );
							bAdded = true;
						}

						if ( bcnMsg.IsNational( ) )
						{
							if ( bAdded )
								lstrcat( szAttr, TEXT("/" ) );

							lstrcat( szAttr, TEXT("NAT" ) );

							bAdded = true;
						}

						if ( bcnMsg.LongLatEncoded( ) )
						{
							if ( bAdded )
								lstrcat( szAttr, TEXT("/" ) );

							lstrcat( szAttr, TEXT("LOC" ) );

							bAdded = true;
						}

						INT64 i64BeaconID = bcnMsg.getBeaconID( );
						EMSTIME tMsgFirst = m_bcnFirstMsg.GetBeaconTime( i64BeaconID );

						if ( (int)tMsgFirst.intTime == GetCurrentMsgNumber( ) )
							tMsgFirst.intTime = 0;

						sprintf( szBuffer, c_szSit172SolnHdr3Fmt, 
								(int)tMsgFirst.intTime, 
								1, 1, " ",
								0.0, " ", " ", bcnMsg.getBeaconID( ), szAttr );

						hr = WriteLine( lpStream, szBuffer );
					}

					if ( EMS_OK == hr )
					{
						/*****  SARMaster doesn't like a position of 0.0/0.0 and does its own decoding anyway.  So,
								don't include the encoded lat/long.
						double dLat = 0.0, dLong = 0.0;

						try
						{
							CBcnMsgDecode bcnDecode;
							CBeaconMessage bMsg( lpSoln->hdr.cBeaconMsg );

							bcnDecode.Initialize( );

							// DO NOT USE .Decode( ) - it is unstable

							bcnDecode.DecodeEx( bMsg );

							if ( bcnDecode.IsFineValid() )
							{
								dLat = bcnDecode.GetLatitudeFine();
								dLong = bcnDecode.GetLongitudeFine();
							}
							else if ( bcnDecode.IsCoarseValid() )
							{
								dLat = bcnDecode.GetLatitudeCoarse();
								dLong = bcnDecode.GetLongitudeCoarse();
							}
						}
						catch ( ... )
						{
						}

						sprintf( szBuffer, c_szSit172SolnHdr4Fmt, bcnMsg.getBeaconID( ), dLat, dLong );
						*/

						sprintf( szBuffer, c_szSit172SolnHdr4Fmt, bcnMsg.getBeaconID( ) );

						hr = WriteLine( lpStream, szBuffer );
					}
				}
				else
					hr = EMS_UNKNOWN_ERROR;
			}									
		}

		catch ( ... )
		{
		}

	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit172::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		INT64 i64BeaconID = 0;
		EMSTIME tMsgNumber;
		
		// go through list of Beacons (m_bcnFirstMsg) and update the MsgNumber if zero 

		for ( int i = 0; i < m_bcnFirstMsg.GetMaxCount( ); i++ )
		{
			i64BeaconID = m_bcnFirstMsg.GetBeaconID( i );

			if ( 0 != i64BeaconID )
			{
				tMsgNumber = m_bcnFirstMsg.GetBeaconTime( i );

				if ( 0 == tMsgNumber.intTime )
				{
					tMsgNumber.intTime = GetCurrentMsgNumber( );

					m_bcnFirstMsg.SetBeaconTime( i, tMsgNumber );
				}
			}
		}
 
		sprintf( szBuffer, c_szSit172HdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSatelliteID(),
						GetAlertCount() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit172::ParseSitMessage( CEMSSitTokenizer *lpTokenizer )
{
	EMS_RESULT hr = ParseSitHeader( lpTokenizer );

	if ( hr == EMS_OK )
	{
		EMSSITLOCALERTSOLUTION alertData, *lpAlertData=0;
		int nCount = _AllocSolutions( GetAlertCount( ) );

		for ( int i = 0; ( hr == EMS_OK ) && ( i < GetAlertCount() ); i++ )
		{
			memset( &alertData, 0, sizeof( alertData ) );

			hr = _ParseAlertLine1( lpTokenizer, &alertData );

			if ( hr == EMS_OK )
				hr = _Parse406Message( lpTokenizer, &alertData );

			if ( ( hr == EMS_OK ) && ( i < nCount ) )
			{
				lpAlertData = _GetSolutionPtr( i );
				
				if ( lpAlertData )
					*lpAlertData = alertData;
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSit172::ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek )
{
	EMS_RESULT hr = EMS_OK;
	EMSSITFIELD sitField[ 16 ];
	int nFldCount = 0, nSitNumber = 0, nSitDestination = 0;

	hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

	if ( hr == EMS_OK )
	{
		CEMSSitMsgField msgField;

		// should find /MF4/MF5/MF6/MF10

		if ( nFldCount == 5 )
		{
			int nSatNumber=0, nAlertCount=0, nNumber = 0;

			hr = msgField.GetMF4( sitField[0].szText, &nSitNumber );

			if ( hr == EMS_OK )
			{
				SetSitNumber( nSitNumber );

				hr = msgField.GetMF5( sitField[1].szText, &nSitDestination );
			}

			if ( hr == EMS_OK )
			{
				SetSitDestination( nSitDestination );

				hr = msgField.GetMF6( sitField[2].szText, &nSatNumber );
			}

			if ( hr == EMS_OK )
			{
				SetSatelliteID( nSatNumber );

				hr = msgField.GetMF10( sitField[3].szText, &nAlertCount );
			}

			if ( hr == EMS_OK )
			{
				SetAlertCount( nAlertCount );

				if ( !msgField.IsEOL( sitField[4].szText ) )
					hr = EMS_SIT_SYNTAX_EOL;
			}
		}
		else
			hr = EMS_SIT_FIELD_COUNT_ERROR;

		if ( bPeek )
			UnReadSitLine( lpTokenizer, sitField, nFldCount );
	}
	else 
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit172::_ParseAlertLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF11/MF13/MF14/MF21 EOL 

			if ( nFldCount == 5 )
			{
				CEMSSitMsgField msgField;
				EMSTIME timeTCA;
				int nNumber=0, nLutID = 0, nPoints=0;
				double dBias = 0.0, dBSDev = 0.0, dDrift = 0.0;

				hr = msgField.GetMF11( sitField[0].szText, &nLutID );

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nPrimaryLutID = nLutID;

					hr = msgField.GetMF13( sitField[0].szText, &dBias,
												&dBSDev, &dDrift );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->sideA.dBias = dBias;

					lpAlertData->sideA.dBSdev = dBSDev;

					lpAlertData->sideA.dDrift = dDrift;

					hr = msgField.GetMF14( sitField[ 2 ].szText, &timeTCA );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->sideA.timeTCA = timeTCA;

					hr = msgField.GetMF21( sitField[ 3 ].szText, &nPoints );
				}

				if ( hr == EMS_OK )
				{
					lpAlertData->hdr.nNumPoints = nPoints;

					if ( !msgField.IsEOL( sitField[4].szText ) )
						hr = EMS_SIT_SYNTAX_EOL;
				}
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit172::_Parse406Message( CEMSSitTokenizer *lpTokenizer, LPEMSSITLOCALERTSOLUTION lpAlertData )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpAlertData )
	{
		EMSSITFIELD sitField[ 16 ];
		int nFldCount = 0;

		hr = ReadSitLine( lpTokenizer, sitField, 16, &nFldCount );

		if ( hr == EMS_OK )
		{
			// should find /MF EOL

			if ( nFldCount == 2 )
			{
				if ( sitField[0].nLength > 30 )
				{
					INT64 i64BeaconID = 0;
					TCHAR szTemp[32];

					lstrcpy( szTemp, TEXT("0x") );

					for ( int i = 0; i < 30; i += 2 )
					{
						lstrcpyn( &szTemp[2], &sitField[0].szText[i+1], 3 );

						lpAlertData->hdr.cBeaconMsg[ 3+ (i/2) ] = (BYTE)strtol( szTemp, 0, 16 );
					}

					//Extract beacon id from beacon msg 

					i64BeaconID = ( 0x7F & lpAlertData->hdr.cBeaconMsg[3] );

					for ( int j = 1; j < 7; j++ )
					{
						i64BeaconID = i64BeaconID << 8;
						i64BeaconID |= lpAlertData->hdr.cBeaconMsg[3+j];
					}

					i64BeaconID = i64BeaconID << 5;

					i64BeaconID |= ( 0x1F & ( lpAlertData->hdr.cBeaconMsg[10] >> 3 ) );

					lpAlertData->hdr.i64BeaconID = i64BeaconID;
				}
				else
					hr = EMS_SIT_SYNTAX_ERROR;
			}
			else
				hr = EMS_SIT_FIELD_COUNT_ERROR;
		}
		else 
			hr = EMS_BAD_PARAM;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSit172::AddSolution( LPEMSSITLOCALERTSOLUTION lpSoln )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpSoln )
	{
		EMSTIME lastMsg;	// ugly reuse of an existing class
		CBeaconMsg bcnMsg;
		
		bcnMsg.Set( lpSoln->hdr.cBeaconMsg );

		INT64 i64BeaconID = bcnMsg.getBeaconID( );

		if ( ( i64BeaconID & m_i64BeaconMask ) == m_i64BeaconPrefix )
		{
			bool bInvertedFS = ( 0xD0 == lpSoln->hdr.cBeaconMsg[2] );

			if ( bInvertedFS || !m_bInvertedFSOnly )
			{
				lastMsg = m_bcnFirstMsg.GetBeaconTime( i64BeaconID );

				m_bcnFirstMsg.AddBeacon( i64BeaconID, lastMsg );

				hr = CEMSSitAlertMessageBase::AddSolution( lpSoln );
			}
		}
	}			
	return hr;
}

