

#include "EMSTYPES.h"
#include "SGBTYPES.h"
#include "SGBmessage.h"
#include <memory.h>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void 
CSGBMESSAGE::getSGBdata( const char *cMessage, LPSGBMESSAGEDATA SGB )
{
	memset( SGB, 0, sizeof(SGBMESSAGEDATA));
	BYTE MsgBits[304];
	BYTE Msg[256];
	int i;
	EMS_RESULT hr = EMS_OK;

	memset( &MsgBits[0], 0, 304 );

	hr = SGB_BeaconID( &cMessage[0], SGB->BeaconID, SGB->i64BeaconID );
	
	if ( hr == EMS_OK )
	{

		ConvertChar2BinaryArray( &cMessage[0], &MsgBits[0], 75 );

		ConvertBinaryArray2Byte( &MsgBits[0], &SGB->BeaconMsg[0], 304 );
		
		ConvertBinaryArray2Byte( &MsgBits[0], &SGB->FrameSynch[0], 56 );
		SGB->FrameSynch[6] &= 0xF0;

		ConvertBinaryArray2Byte( &MsgBits[INFORMATION_START+ROTATE_FIELD_START-2], &SGB->RotateField[0], 48 );
		
		ConvertBinaryArray2Byte( &MsgBits[INFORMATION_START+SPARE_START-2], &SGB->Spare[0], 24 );
		SGB->Spare[2] &= 0x80;

		ConvertBinaryArray2Byte( &MsgBits[INFORMATION_START+BCH_START-2], &SGB->BCH[0], 48 );


		// Check Frame synch bits
		SGB->wBitErrorFS = 0;
		for ( i = 0; i < FRAME_SYNCH_BITS; i++ )
		{
			if ( MsgBits[i] > 0 ) SGB->wBitErrorFS += 1;
		}
	


		// Copy 250 message bits into temporary array for further processing

		memcpy( &Msg[0], &MsgBits[INFORMATION_START-1],  250 );

        getSGBcoding( Msg, SGB );
	
	}
	
	return;
}

////////////////////////////////////////////////////////////////////////////////////////
void
CSGBMESSAGE::getSGB51data( const char *cMessage, LPSGBMESSAGEDATA SGB )
{
	memset( SGB, 0, sizeof(SGBMESSAGEDATA));
	BYTE Msg[256];

	ConvertChar2BinaryArray( &cMessage[0], &Msg[0], 51 );
	
    getSGBcoding( &Msg[2], SGB );

    SGB_23xBeaconID( &Msg[2], SGB->BeaconID );

	ConvertBinaryArray2Byte( &Msg[ROTATE_FIELD_START+1], &SGB->RotateField[0], 48 );

	ConvertBinaryArray2Byte( &Msg[SPARE_START+1], &SGB->Spare[0], 14 );
    SGB->Spare[2] = 0;

	return;
}

////////////////////////////////////////////////////////////////////////////////////////
void 
CSGBMESSAGE::getSGBcoding( BYTE *Msg, LPSGBMESSAGEDATA SGB )
{
	bool bSign;
	int i;

	// Country code
	SGB->wCountryCode = 0;
	for ( i = CCODE_START; i < CCODE_START+CCODE_BITS; i++ )
	{
		SGB->wCountryCode += Msg[i-1];
		SGB->wCountryCode *= 2;
	}
	SGB->wCountryCode /= 2;

   // C/S TAC No
	SGB->ulTAC = 0;
	for ( i = TAC_START; i < TAC_START+TAC_BITS; i++ )
	{
		SGB->ulTAC += Msg[i-1];
		SGB->ulTAC *= 2;
	}
	SGB->ulTAC /= 2;

	// Beacon Serial Number
	SGB->wSerialNumber = 0;
	for ( i = SERIAL_START; i < SERIAL_START+SERIAL_BITS; i++ )
	{
		SGB->wSerialNumber += Msg[i-1];
		SGB->wSerialNumber *= 2;
	}
	SGB->wSerialNumber /= 2;

   // Beacon Vessel Type
	SGB->ulVesselType = 0;
	for ( i = VESSEL_TYPE_START; i < VESSEL_TYPE_START+VESSEL_TYPE_BITS; i++ )
	{
		SGB->ulVesselType += Msg[i-1];
		SGB->ulVesselType *= 2;
	}
	SGB->ulVesselType /= 2;

	// Beacon Vessel ID
	SGB->i64VesselID = 0;
	for ( i = VESSEL_ID_START; i < VESSEL_ID_START+VESSEL_ID_BITS; i++ )
	{
		SGB->i64VesselID += Msg[i-1];
		SGB->i64VesselID *= 2;
	}
	SGB->i64VesselID /= 2;

   // Beacon Homing Flag
	SGB->bHoming = false;
	if (Msg[HOMING_START-1] > 0 ) SGB->bHoming = true;
    // Beacon Selftest Flag  // Self test flag moved to bit 0 of full message
	SGB->bSelftest = false;
	if (Msg[SELF_TEST_START-1] > 0 ) SGB->bSelftest = true;
	// Beacon Test Protocol Flag
	SGB->bTestProtocol = false;
	if (Msg[TEST_PROTOCOL_START-1] > 0 ) SGB->bTestProtocol = true;

	// Beacon Type
	SGB->wBeaconType = 0;
	for ( i = BEACON_TYPE_START; i < BEACON_TYPE_START+BEACON_TYPE_BITS; i++ )
	{
		SGB->wBeaconType += Msg[i-1];
		SGB->wBeaconType *= 2;
	}
	SGB->wBeaconType /= 2;

	// RLS Beacon Protocol Flag
	SGB->bRLS = false;
	if (Msg[RLS_START-1] > 0 ) SGB->bRLS = true;


	// Test for cancellation message (all spare bits equal 0)
	SGB->bCancellation = true;
	for ( i = SPARE_START; i < SPARE_START+SPARE_BITS; i++ )
	{
		if ( Msg[i-1] > 0 ) SGB->bCancellation = false;
	}

	// Establish Rotating field Identifier
	SGB->wRotateFieldNumber = 0;
	for ( i = ROTATE_FIELD_START; i < ROTATE_FIELD_START+ROTATE_ID_BITS; i++ )
	{
		SGB->wRotateFieldNumber += Msg[i-1];
		SGB->wRotateFieldNumber *= 2;
	}
	SGB->wRotateFieldNumber /= 2;

	// Check default. If either Latitude or Longitude are defaulted, both should be considered default
	//
	// Exclude sign bit from test. If sign bit=0 then default. 
	// If sign bit=1 then does not have encoded capability so consider defaulted
	SGB->bDefaultLocation = true;
	SGB->bEncodedCapable = true;
	SGB->dLatitude  = 99.9;
	SGB->dLongitude = 999.9;
	SGB->dAltitude  = -999.9;

	for ( i = 0; i < LATITUDE_BITS; i++ )
	{
		if ( (i > 0 && i < 8 ) || ( i > 12 && i < 18 ) )
		{
			if ( Msg[LATITUDE_START+i-1] == 0 ) SGB->bDefaultLocation = false;
		}
		else if ( i > 0 ) // do not include sign bit
		{
			if (Msg[LATITUDE_START+i-1] == 1 ) SGB->bDefaultLocation = false;
		}
	}

	for ( i = 0; i < LONGITUDE_BITS; i++ )
	{
		if ( (i > 0 && i < 14 ) || ( i > 18 && i < 25 ) )
		{
			if ( Msg[LONGITUDE_START+i-1] == 0 ) SGB->bDefaultLocation = false;
		}
		else if ( i > 0 ) // do not include sign bit
		{
			if (Msg[LONGITUDE_START+i-1] == 1 ) SGB->bDefaultLocation = false;
		}
	}

	if ( !SGB->bDefaultLocation )
	{

		// GNSS latitude
		bSign = false;
		if (Msg[LATITUDE_START-1] > 0) bSign = true;
		double dLatitudeDeg = 0.0;
		for ( i = LATITUDE_START; i < LATITUDE_START+7; i++ )
		{
			dLatitudeDeg += Msg[i];
			dLatitudeDeg *= 2;
		}
		dLatitudeDeg /= 2;

		double dLatitudeFract = 0.0;
		for ( i = LATITUDE_START+7; i < LATITUDE_START+LATITUDE_BITS-1; i++ )
		{
			dLatitudeFract += Msg[i];
			dLatitudeFract *= 2;
		}
		dLatitudeFract /= 65536;
		SGB->dLatitude = dLatitudeDeg + dLatitudeFract;
		if (bSign) SGB->dLatitude *= -1.0;

		// GNSS longitude
		bSign = false;
		if (Msg[LONGITUDE_START-1] > 0) bSign = true;
		double dLongitudeDeg = 0.0;
		for ( i = LONGITUDE_START; i < LONGITUDE_START+8; i++ )
		{
			dLongitudeDeg += Msg[i];
			dLongitudeDeg *= 2;
		}
		dLongitudeDeg /= 2;

		double dLongitudeFract = 0.0;
		for ( i = LONGITUDE_START+8; i < LONGITUDE_START+LONGITUDE_BITS-1; i++ )
		{
			dLongitudeFract += Msg[i];
			dLongitudeFract *= 2;
		}
		dLongitudeFract /= 65536;
		SGB->dLongitude = dLongitudeDeg + dLongitudeFract;
		if (bSign) SGB->dLongitude *= -1.0;

		// Check if rotating field is #0 or #1 which contains altitude

		if ( SGB->wRotateFieldNumber <= 1 )
		{
			// Altitude is provided in steps of 16 metres starting at -400 metres
			double dAltitude = 0.0;
			for ( i = ALTITUDE_START; i < ALTITUDE_START+ALTITUDE_BITS; i++ )
			{
				dAltitude += Msg[i-1];
				dAltitude *= 2;
			}
			dAltitude /= 32;
			SGB->dAltitude = dAltitude - 400.0;
		}

	
	}
	else   // If Defaulted, but sign bit is 1 then beacon does not have Encoded Location Capability
	{
		if ( Msg[LATITUDE_START-1] == 1 ) SGB->bEncodedCapable = false;
		if ( Msg[LONGITUDE_START-1] == 1 ) SGB->bEncodedCapable = false;
	}
	
	return;
}



//////////////////////////////////////////////////////////////////////////////////

EMS_RESULT
CSGBMESSAGE::SGB_BeaconID( const char *cMessage, BYTE *BeaconID, UINT64& i64BeaconID )
{
	BYTE	bcnid[96];
	BYTE    TempByte[300];
	BYTE	msg[250];
	int i;
	
	EMS_RESULT hr = EMS_OK;;

	bcnid[0]  = 1;
	bcnid[11] = 1;
	bcnid[12] = 0;
	bcnid[13] = 1;
	bcnid[91] = 1;
	bcnid[92] = 0;
	bcnid[93] = 0;
	bcnid[94] = 0;
	bcnid[95] = 0;

   
	ConvertChar2BinaryArray( &cMessage[0], &TempByte[0], 75 );

	memcpy(&msg[0],&TempByte[INFORMATION_START-1],250);

    SGB_23xBeaconID( msg, BeaconID );

	i64BeaconID = 0;
	for ( i = 0; i < 60; i++ )
	{
	  // i64BeaconID += ((UINT64)  bcnid[i]) << (59-i);
	   i64BeaconID += ((UINT64)  bcnid[i]);
	   i64BeaconID *= 2;
	}
	i64BeaconID /= 2;

	if ( i64BeaconID == 0 ) hr = EMS_FALSE;

	return hr;
}

//////////////////////////////////////////////////////////////////////////////////

void
CSGBMESSAGE::SGB_23xBeaconID( BYTE *msg, BYTE *BeaconID )
{
	BYTE	bcnid[96];
	int i;
	
	EMS_RESULT hr = EMS_OK;;

	bcnid[0]  = 1;
	bcnid[11] = 1;
	bcnid[12] = 0;
	bcnid[13] = 1;
	bcnid[92] = 0;
	bcnid[93] = 0;
	bcnid[94] = 0;
	bcnid[95] = 0;
   
   // Country code
   for ( i = 0; i < CCODE_BITS; i++ )
   {
	   bcnid[i+1] = msg[CCODE_START-1 + i];
   }
   
   // C/S TAC No
   for ( i = 0; i < TAC_BITS; i++ )
   {
	   bcnid[i+14] = msg[TAC_START-1 + i];
   }

   // Beacon Serial Number
   for ( i = 0; i < SERIAL_BITS; i++ )
   {
	   bcnid[i+30] = msg[SERIAL_START-1 + i];
   }
   
   // Test Protocol Flag
   bcnid[44] = 	msg[TEST_PROTOCOL_START-1];

   // Vessel ID type
   for ( i = 0; i < VESSEL_TYPE_BITS; i++ )
   {
	   bcnid[i+45] = msg[VESSEL_TYPE_START-1 + i];
   }

   // Beacon Serial Number
   for ( i = 0; i < VESSEL_ID_BITS; i++ )
   {
	   bcnid[i+48] = msg[VESSEL_ID_START-1 + i];
   }

   	ConvertBinaryArray2Byte( &bcnid[0], &BeaconID[0], 96 );

	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void 
CSGBMESSAGE::SGB_ECCgenerate( BYTE *Message )
{
    
	BYTE msg[256];
	BYTE genpoly[49];
	BYTE genpoly1[52];
	BYTE BCH[49];
	char cBCHGenPoly[] = "1C7EB85DF3C97";
	int i;

//   BCH (255,207) generator
//   𝑔(𝑋) =	  𝑋48 + 𝑋47 + 𝑋46 + 𝑋42 + 𝑋41 + 𝑋40 + 𝑋39 + 𝑋38 + 𝑋37 + 𝑋35 + 𝑋33 + 𝑋32 + 𝑋31
//			+ 𝑋26 + 𝑋24 + 𝑋23 + 𝑋22 + 𝑋20 + 𝑋19 + 𝑋18 + 𝑋17 + 𝑋16 + 𝑋13 + 𝑋12 + 𝑋11 + 𝑋10
//			+ 𝑋7  + 𝑋4  + 𝑋2  + 𝑋   + 1

	memset(  genpoly,  0,  49 * sizeof(BYTE) );
	memset(  genpoly1, 0,  52 * sizeof(BYTE) );
	memset(  msg,      0, 256 * sizeof(BYTE) );

	ConvertChar2BinaryArray( cBCHGenPoly, &genpoly1[0], 13 );
	 
	for ( i = 0; i < 49; i++ )
	{
		genpoly[i] = genpoly1[i+3];
	}

	ConvertByte2BinaryArray( &Message[0], &msg[0], 32 );
   
	GF2Division( &msg[0], 250, &genpoly[0], 49, &BCH[0]  );

	memcpy( &msg[202], &BCH[1], 48*sizeof(BYTE) );

	ConvertBinaryArray2Byte( &msg[0], &Message[0], 256 );

	// Check syndromes
	BYTE rem[10];
	char syn[] = "11D1771F31691BD1E7";  
	ConvertChar2BinaryArray( syn, &genpoly1[0], 18 );

	for ( int i = 3; i < 72; i+= 12 )
	{
		GF2Division( &msg[0], 250, &genpoly1[i], 9, &rem[0]  );
	}

	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
CSGBMESSAGE::ConvertChar2BinaryArray( const char *cMessage, BYTE *Message, int Nchar )
{
	int i, j, k;
	BYTE b1, b2;
	k = 0;

	for (  i = 0; i < Nchar; i ++ )
	{
		b1 = (BYTE) HexChar(cMessage[i]);

		for ( j = 0; j < 4; j++ )
		{
			b2 = (b1 >> (3-j));
			b2 = 0x01 & b2;
			Message[k] = b2;
			k++;
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
CSGBMESSAGE::ConvertByte2BinaryArray( BYTE *inMessage, BYTE *bMessage, int Nbyte )
{
	int i, j, k;
	k = 0;
   
   for ( i = 0; i < Nbyte; i++ )
   {
      for ( j = 0; j < 8; j++ )
      {
         bMessage[k++] = 0x01 & ( inMessage[i] >> ( 7 - j ) );
       }
   }

	return;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void
CSGBMESSAGE::ConvertBinaryArray2Byte( BYTE *bMessage, BYTE *Message, int Nbinary )
{
	int i, j, k;
	i = 0;
	k = 0;
   
	while( k < Nbinary )
	{
		Message[i] = 0;
		for ( j = 0; j < 8; j++ )
		{
			if ( k < Nbinary )
				Message[i] += bMessage[k++] << ( 7 - j );
		}
		i++;
	}

	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void 
CSGBMESSAGE::ConvertChar2ByteArray( const char *cMessage, BYTE *Message, int Nchar )
{

	int i, j;
	BYTE b1, b2;
	j = 0;
	b1 = 0;
	b2 = 0;
	for (  i = 0; i < Nchar; i += 2 )
	{
		b1 = (BYTE) HexChar(cMessage[i]);
		b2 = (BYTE) HexChar(cMessage[i+1]);
		Message[j++] = (BYTE) (b1*16 + b2);
	}

	return;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//void
//CSGBMESSAGE::ConvertByteArray2Char( BYTE *Message, char *outMessage, int Nbyte )
//{
//	int i, j;
//	j = 0;
//	for ( i = 0; i < Nbyte; i++ )
//	{
//		sprintf( &outMessage[j++], "%1X", Message[i] >> 4 );
//		sprintf( &outMessage[j++], "%1X", Message[i] & 0x0000000f);
//	}
//
//	return;
//}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int 
CSGBMESSAGE::HexChar( char Value )
{
    switch( Value )
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return Value - '0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return Value - 'A' + 10;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return Value - 'a' + 10;
        default:
//            throw EConvertError( "Invalid character in hexadecimal string." );
            // EMS_RESULT hr = ???
			//return hr;
			return -1;  // RVW_bai
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void 
CSGBMESSAGE::GF2Division( BYTE *bDividend, int N, BYTE *bDivsor, int M, BYTE * bRemainder  )
{
    
	int i, j;

   memcpy(  bRemainder, bDividend, M*sizeof( BYTE) ); 

   i = M;

	while ( i < N )
   {	   
	   while ( bRemainder[0] == 0 && i < N )
	   {
		   for ( j = 0; j < 48; j++ )
		   {
			   bRemainder[j] = bRemainder[j+1];
		   }
		   bRemainder[M-1] = bDividend[i++];
	   }

	   for ( j = 0; j < M; j++ )
	   {
		   if ( bRemainder[j] == bDivsor[j] ) 
		   {
				bRemainder[j] = 0;
		   }
		   else
		   {
				bRemainder[j] = 1;
		   }
	   }

   }

   return;
}

void
CSGBMESSAGE::SGBencodedlocation( BYTE *Message, double& dSGBlatitude, double& dSGBlongitude, double& dSGBaltitude )
{
	LPSGBMESSAGEDATA SGB;
	getSGBcoding( Message, SGB );
    
	dSGBlatitude  = SGB->dLatitude;
	dSGBlongitude = SGB->dLongitude;
	dSGBaltitude  = SGB->dAltitude;

	return;
}

