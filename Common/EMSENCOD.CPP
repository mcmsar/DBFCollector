/********************************************************************
*	Module:			emsencod.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSEncodedSatID and CEMSEncodedLutID
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/09/17	rvw	start

********************************************************************/
#include <memory.h>
#include <stdio.h>
#include <sstream>

#include "emstypes.h"
#include "emsencod.h"


const int c_nMaxLuts = 8;
const int c_nLastSatByte = sizeof( EMSENCODEDSATID ) - 1;
const BYTE c_cNewFmtCode = 0x81;
const int c_nMaxNewFmtSats = (( sizeof( EMSENCODEDSATID ) - 1 ) * 8 ) / 9;
const int c_nNewFmtLastByte = sizeof( EMSENCODEDSATID ) - 1;

CEMSEncodedSatID::CEMSEncodedSatID()
{
}

CEMSEncodedSatID::~CEMSEncodedSatID()
{
}

EMS_RESULT CEMSEncodedSatID::Reset( EMSENCODEDSATID *lpID )
{
	LPBYTE lpData = (LPBYTE)lpID;

	int x = c_nMaxNewFmtSats;
	int y = c_nNewFmtLastByte;

	if ( lpData )
	{
		memset( lpData, 0, sizeof( EMSENCODEDSATID ) );

#ifdef EMS_USE_NEW_SAT_ENCODER

#pragma message("CEMSEncodedSatID::Using New Sat Encoder")

		lpData[ c_nNewFmtLastByte ] = c_cNewFmtCode;

#endif
	}


	return EMS_OK;
}

EMS_RESULT CEMSEncodedSatID::Reset( EMSENCODEDSATID *lpID , ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( _NewFmt( lpID ) )
		hr = _NewReset( lpID, ulSatID );
	else
		hr = _OldReset( lpID, ulSatID );

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_OldReset( EMSENCODEDSATID *lpID , ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpID && ( _Index( ulSatID ) >= 0) )
	{
		LPBYTE lpcByte = ( LPBYTE )lpID;
		int nByte = _Byte( ulSatID );
		int nBit = _Bit( ulSatID );
		
		lpcByte[ nByte ] &= ~( 0x1 << nBit );
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_NewReset( EMSENCODEDSATID *lpID , ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpID )
	{
		ULONG i, ulCount=0, ulTempSatID[ c_nMaxNewFmtSats ];
		bool bChanged = false;

		_NewExpand( lpID, ulTempSatID, c_nMaxNewFmtSats, &ulCount );

		for ( i = 0; i < ulCount; i++ )
		{
			if ( ulSatID == ulTempSatID[ i ] )
			{
				bChanged = true;
				ulTempSatID[ i ] = 0;
			}
		}

		if ( bChanged )
		{
			Reset( lpID );

			for ( i = 0; i < ulCount; i++ )
			{
				if ( ulTempSatID[ i ] )
					hr = _NewSet( lpID, ulTempSatID[ i ] );
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

int CEMSEncodedSatID::Count( EMSENCODEDSATID *lpID )
{
	int nCount = 0;

	if ( _NewFmt( lpID ) )
		nCount = _NewCount( lpID );
	else
		nCount = _OldCount( lpID );

	return nCount;
}

int CEMSEncodedSatID::_OldCount( EMSENCODEDSATID *lpID )
{
	int nCount = 0;

	if ( lpID )
	{
		BYTE cMask = 0x1, *lpcByte = (LPBYTE)lpID;

		for ( int i = 0; i < sizeof( EMSENCODEDSATID ); i++ )
		{
			cMask = 0x1;

			for ( int j = 0; j < 8; j++ )
			{
				if ( cMask & lpcByte[i] )
					nCount++;
			
				cMask = cMask << 1;
			}
		}
	}

	return nCount;
}

int CEMSEncodedSatID::_NewCount( EMSENCODEDSATID *lpID )
{
	int nCount = 0;

	if ( lpID )
	{
		ULONG ulCount=0, ulTempSatID[ c_nMaxNewFmtSats ];

		_NewExpand( lpID, ulTempSatID, c_nMaxNewFmtSats, &ulCount );

		for ( ULONG i = 0; i < ulCount; i++ )
		{
			if ( 0 != ulTempSatID[ i ] )
				nCount++;
		}
	}

	return nCount;
}


bool CEMSEncodedSatID::_NewFmt( EMSENCODEDSATID *lpID )
{
	LPBYTE lpData = (LPBYTE)lpID;

	return ( lpData  && ( c_cNewFmtCode == ( lpData[ c_nNewFmtLastByte ] & c_cNewFmtCode ) ) );
}


int CEMSEncodedSatID::_Bit( ULONG ulSatID )
{
	return _Index( ulSatID ) % 8;
}

int CEMSEncodedSatID::_Byte( ULONG ulSatID )
{ 
	return sizeof( EMSENCODEDSATID ) - ( _Index( ulSatID ) / 8 ) - 1;
}

int CEMSEncodedSatID::_Index( ULONG ulSatID )
{
	int nIndex = -1;

	switch ( ulSatID / 100 )
	{
		// 5 bytes
		case 0:	// Sarsat
			if ( ulSatID < ( 5 * 8 ) ) 
				nIndex = ulSatID;
			break;

		// 5 bytes
		case 1:	// Cospas
			if (( ulSatID-100) < ( 5 * 8 ) ) 
				nIndex = (ulSatID-100) + ( 5 * 8 );
			break;

		// 5 bytes
		case 2:	// Geo
			if (( ulSatID-200) < ( 5 * 8 ) ) 
				nIndex = (ulSatID-200) + ( 2 * 5 * 8 );
			break;

		// this leaves 1 byte for future use
	}
	return nIndex;
}

EMS_RESULT CEMSEncodedSatID::Expand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	
	if ( _NewFmt( lpID ) )
		hr = _NewExpand( lpID, lpulSatID, ulMax, lpulCount );
	else
		hr = _OldExpand( lpID, lpulSatID, ulMax, lpulCount );

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_NewExpand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0;

	if ( lpID && lpulSatID && ulMax )
	{
		ULONG i, ulTempSatID[ c_nMaxNewFmtSats ], ulSatID;

		for ( i = 0; i < c_nMaxNewFmtSats; i++ )
		{
			ulSatID = 0;

			for ( int j = 0; j < 9; j++ )
			{
				ulSatID = ulSatID << 1;

				if ( _TestBit( lpID, (i*9)+j ) )
					ulSatID |= 1;
			}
			ulTempSatID[ i ] = ulSatID;
		}

		for ( i = 0 ; ( i < c_nMaxNewFmtSats ) && ( ulCount < ulMax ); i++ )
		{
			if ( ulTempSatID[ i ] )
				lpulSatID[ ulCount++ ] = ulTempSatID[ i ];
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulCount )
		*lpulCount = ulCount;

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_OldExpand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0;

	if ( lpID && lpulSatID && ulMax )
	{
		for ( ULONG i = 0; ( i < 300 ) && ( ulCount < ulMax ) ; i++ )		
		{
			if ( Test( lpID, i ) )
			{
				lpulSatID[ ulCount++ ] = i;
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulCount )
		*lpulCount = ulCount;

	return hr;
}

EMS_RESULT CEMSEncodedSatID::Set( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpulSatID )
	{
		for ( ULONG i = 0; ( hr == EMS_OK ) && ( i < ulCount ); i++ )
			hr = Set( lpID, lpulSatID[i] );
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}


EMS_RESULT CEMSEncodedSatID::Set( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( _NewFmt( lpID ) )
		hr = _NewSet( lpID, ulSatID );
	else 
		hr = _OldSet( lpID, ulSatID );

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_OldSet( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpID && ( _Index( ulSatID ) >= 0) )
	{
		LPBYTE lpcByte = ( LPBYTE )lpID;
		int nByte = _Byte( ulSatID );
		int nBit = _Bit( ulSatID );
		
		lpcByte[ nByte ] |= ( 0x1 << nBit );
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSEncodedSatID::_NewSet( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpID )
	{
		ULONG i, ulCount=0, ulTempSatID[ c_nMaxNewFmtSats ];
		bool bFound = false, bAdded = false;

		memset( ulTempSatID, 0, sizeof( ulTempSatID ) );

		_NewExpand( lpID, ulTempSatID, c_nMaxNewFmtSats, &ulCount );

		for ( i = 0; i < ulCount; i++ )
		{
			if ( ulSatID == ulTempSatID[ i ] )
				bFound = true;
		}

		if ( !bFound )
		{
			for ( i = 0; !bAdded && ( i < c_nMaxNewFmtSats ); i++ )
			{
				if ( 0 == ulTempSatID[ i ] )
				{
					ulTempSatID[ i ] = ulSatID;
					bAdded = true;
				}
			}

		if ( bAdded )
		{
			ULONG ulID = 0, ulTestBit = 0x10;

			for ( i = 0; i < c_nMaxNewFmtSats; i++ )
			{
				ulID = ulTempSatID[i];

				ulTestBit = 0x100;

				for ( int j = 0; j < 9; j++ )
				{
					if ( ulID & ulTestBit )
						_SetBit( lpID, (i*9)+j );

					ulTestBit = ulTestBit >> 1;
				}
			}
		}
		else if ( !bFound )
			hr = EMS_OVERFLOW;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

bool CEMSEncodedSatID::_TestBit( EMSENCODEDSATID *lpID, int nBitNumber )
{
	bool bSet = FALSE;
	LPBYTE lpData = (LPBYTE)lpID;

	if ( lpData )
	{
		int nByte = nBitNumber / 8;
		int nBit = nBitNumber % 8;
		BYTE cMask = 0x80 >> nBit;

		bSet = ( lpData[ nByte ] & cMask ) == cMask;
	}

	return bSet;
}

void CEMSEncodedSatID::_SetBit( EMSENCODEDSATID *lpID, int nBitNumber )
{
	LPBYTE lpData = (LPBYTE)lpID;

	if ( lpData )
	{
		int nByte = nBitNumber / 8;
		int nBit = nBitNumber % 8;
		BYTE cMask = 0x80 >> nBit;

		lpData[ nByte ] |= cMask;
	}
}


BOOL CEMSEncodedSatID::Test( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	BOOL bSet = FALSE;

	if  ( _NewFmt( lpID ) )
		bSet = _NewTest( lpID, ulSatID );
	else
		bSet = _OldTest( lpID, ulSatID );

	return bSet;
}

BOOL CEMSEncodedSatID::_NewTest( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	BOOL bSet = FALSE;

	if ( lpID )
	{
		ULONG ulCount=0, ulTempSatID[ c_nMaxNewFmtSats ];

		_NewExpand( lpID, ulTempSatID, c_nMaxNewFmtSats, &ulCount );

		for ( ULONG i = 0; !bSet && (i < ulCount); i++ )
		{
			if ( ulSatID == ulTempSatID[ i ] )
				bSet = TRUE;
		}
	}


	return bSet;
}

BOOL CEMSEncodedSatID::_OldTest( EMSENCODEDSATID *lpID, ULONG ulSatID )
{
	BOOL bSet = FALSE;

	if ( lpID && ( _Index( ulSatID ) >= 0) )
	{
		LPBYTE lpcByte = ( LPBYTE )lpID;
		int nByte = _Byte( ulSatID );
		int nBit = _Bit( ulSatID );
		
		bSet = ( lpcByte[ nByte ] & ( 0x1 << nBit ) ) != 0;
	}

	return bSet;
}

std::string 
CEMSEncodedSatID::GetDecodedStringA( const EMSENCODEDSATID caSat )
{
	std::stringstream ostrmRet;

	ULONG aulSatIDs[ 300 ];
	ULONG ulActual = 0;

	EMSENCODEDSATID aSat;
	memcpy( aSat, caSat, sizeof(EMSENCODEDSATID) );

	EMS_RESULT hr = Expand( &aSat, aulSatIDs, 300, &ulActual );

	if( EMS_OK == hr )
	{
		for( ULONG l = 0; l < ulActual; l++ )
		{
			if( 0 != l )
				ostrmRet << " ";

			ostrmRet << aulSatIDs[l];
		}
	}

	return ostrmRet.str();
}

std::wstring 
CEMSEncodedSatID::GetDecodedStringW( const EMSENCODEDSATID caSat )
{
	std::wstringstream owstrmRet;

	ULONG aulSatIDs[ 300 ];
	ULONG ulActual = 0;

	EMSENCODEDSATID aSat;
	memcpy( aSat, caSat, sizeof(EMSENCODEDSATID) );

	EMS_RESULT hr = Expand( &aSat, aulSatIDs, 300, &ulActual );

	if( EMS_OK == hr )
	{
		for( ULONG l = 0; l < ulActual; l++ )
		{
			if( 0 != l )
				owstrmRet << L" ";

			owstrmRet << aulSatIDs[l];
		}
	}

	return owstrmRet.str();
}


CEMSEncodedLutID::CEMSEncodedLutID()
{
}

CEMSEncodedLutID::~CEMSEncodedLutID()
{
}

EMS_RESULT CEMSEncodedLutID::Reset( EMSENCODEDLUTID *lpID )
{
	if ( lpID )
		memset( lpID, 0, sizeof( EMSENCODEDLUTID ) );

	return EMS_OK;
}

EMS_RESULT CEMSEncodedLutID::Reset( EMSENCODEDLUTID *lpID , ULONG ulLutID )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpID )
	{
		LPWORD lpwID = (LPWORD)lpID;

		for ( int i = 0; i < c_nMaxLuts; i++ )
		{
			if ( lpwID[ i ] == (WORD)ulLutID )
				lpwID[ i ] = 0;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

int CEMSEncodedLutID::Count( EMSENCODEDLUTID *lpID )
{
	int nCount = 0;

	if ( lpID )
	{
		LPWORD lpwID = (LPWORD)lpID;

		for ( int i = 0; i < c_nMaxLuts; i++ )
		{
			if ( lpwID[ i ] )
				nCount++;
		}
	}

	return nCount;
}

EMS_RESULT CEMSEncodedLutID::Expand( const EMSENCODEDLUTID *lpID, ULONG *lpulLutID, ULONG ulMax, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0;

	if ( lpID && lpulLutID && ulMax )
	{
		LPWORD lpwID = (LPWORD)lpID;

		for ( int i = 0; i < c_nMaxLuts; i++ )
		{
			if ( lpwID[ i ] && ( ulCount < ulMax ) )
			{
				lpulLutID[ ulCount++ ] = lpwID[ i ];
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulCount )
		*lpulCount = ulCount;

	return hr;
}

EMS_RESULT CEMSEncodedLutID::Encode( ULONG* aulLutIDs, ULONG ulLuts, EMSENCODEDLUTID* lpID )
{
	EMS_RESULT hr = EMS_OK;

	if( aulLutIDs && lpID )
	{
		LPWORD lpwID = (LPWORD) lpID;

		for( ULONG l = 0; (l < ulLuts) && (l < c_nMaxLuts); l++ )
		{
			if( aulLutIDs[l] ) 
			{
				lpwID[ l ] = (WORD) aulLutIDs[ l ];
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

int CEMSEncodedLutID::_Index( EMSENCODEDLUTID *lpID, ULONG ulLutID )
{
	int nIndex = -1;

	if ( lpID )
	{
		LPWORD lpwID = ( LPWORD )lpID;

		for ( int i = 0; ( nIndex == -1 ) && ( i < c_nMaxLuts ); i++ )
		{
			if ( lpwID[ i ] == (WORD)ulLutID )
				nIndex = i;
		}
	}
	
	return nIndex;	
}

EMS_RESULT CEMSEncodedLutID::Set( EMSENCODEDLUTID *lpID, ULONG *lpulLutID, ULONG ulCount )
{
	EMS_RESULT hr = EMS_OK;
	BOOL bSet = FALSE;

	if ( lpulLutID )
	{
		LPWORD lpwID = (LPWORD)lpID;

		for ( ULONG x = 0; x < ulCount; x++ )
		{
			if ( _Index( lpID, lpulLutID[ x ] ) == -1 )
			{
				for ( int i = 0; !bSet && ( i < c_nMaxLuts ); i++ )
				{
					if ( !lpwID[ i ] )
					{
						lpwID[ i ] = (WORD)lpulLutID[ x ];

						bSet = TRUE;
					}
				}
			}
		}
		if ( !bSet )
			hr = EMS_FALSE;
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSEncodedLutID::Set( EMSENCODEDLUTID *lpID, ULONG ulLutID )
{
	return Set( lpID, &ulLutID, 1 );
}

BOOL CEMSEncodedLutID::Test( EMSENCODEDLUTID *lpID, ULONG ulLutID )
{
	return ( _Index( lpID, ulLutID ) != -1 );  
}

std::string 
CEMSEncodedLutID::GetDecodedStringA( const EMSENCODEDLUTID caLut )
{
	std::stringstream ostrmRet;

	ULONG aulLutIDs[ c_nMaxLuts ];
	ULONG ulActual = 0;

	EMSENCODEDLUTID aLut;
	memcpy( aLut, caLut, sizeof(EMSENCODEDLUTID) );

	EMS_RESULT hr = Expand( &aLut, aulLutIDs, c_nMaxLuts, &ulActual );

	if( EMS_OK == hr )
	{
		for( ULONG l = 0; l < ulActual; l++ )
		{
			if( 0 != l )
				ostrmRet << " ";

			ostrmRet << aulLutIDs[l];
		}
	}

	return ostrmRet.str();

}

std::wstring 
CEMSEncodedLutID::GetDecodedStringW( const EMSENCODEDLUTID caLut )
{
	std::wstringstream owstrmRet;

	ULONG aulLutIDs[ c_nMaxLuts ];
	ULONG ulActual = 0;

	EMSENCODEDLUTID aLut;
	memcpy( aLut, caLut, sizeof(EMSENCODEDLUTID) );

	EMS_RESULT hr = Expand( &aLut, aulLutIDs, c_nMaxLuts, &ulActual );

	if( EMS_OK == hr )
	{
		for( ULONG l = 0; l < ulActual; l++ )
		{
			if( 0 != l )
				owstrmRet << L" ";

			owstrmRet << aulLutIDs[l];
		}
	}

	return owstrmRet.str();
}

/*

int main( int argc, char *argv[] )
{
	EMSENCODEDSATID id;
//	EMSENCODEDLUTID lutid;
	int nCount;
	ULONG ulSatIDs[] = { 3, 6, 7, 109, 0 ,0  };

	printf(" sizeof  = %d\n", sizeof( EMSENCODEDSATID ) );

	CEMSEncodedSatID::Reset( &id );

	CEMSEncodedSatID::Set( &id, 7 );

	nCount = CEMSEncodedSatID::Count( &id );

	BOOL bSet = CEMSEncodedSatID::Test( &id, 7 );

	CEMSEncodedSatID::Reset( &id, 7 );

	CEMSEncodedSatID::Set( &id, 302 );

	CEMSEncodedSatID::Set( &id, ulSatIDs, 4 );

	CEMSEncodedSatID::Expand( &id, ulSatIDs, 5, 0 );

	bSet = CEMSEncodedSatID::Test( &id, 7 );

	nCount = CEMSEncodedSatID::Count( &id );


	
	CEMSEncodedLutID::Reset( &lutid );

	CEMSEncodedLutID::Set( &lutid, 2271 );
	
	CEMSEncodedLutID::Set( &lutid, 2272 );

	CEMSEncodedLutID::Set( &lutid, 1234 );

	nCount = CEMSEncodedLutID::Count( &lutid );

	ULONG ulLuts[32], ulLutCount;

	CEMSEncodedLutID::Expand( &lutid, ulLuts, 10, &ulLutCount );

	return 0;
}
*/