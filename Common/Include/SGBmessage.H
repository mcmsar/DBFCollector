#ifndef SGBMESSAGE_H
#define SGBMESSAGE_H

#include "emserror.h"
#include "SGBTYPES.h"

// The following class supports SGB beacons
class CSGBMESSAGE  
{
//protected:	
//	CSGBMESSAGE() { }
//	~CSGBMESSAGE() { }

public:
	static void getSGBdata( const char *cMessage, LPSGBMESSAGEDATA SGB );

	static void getSGBcoding( BYTE *Msg, LPSGBMESSAGEDATA SGB );

	static void getSGB51data( const char *cMessage, LPSGBMESSAGEDATA SGB );

	static int	SGB_ECCheck( bool modify, BYTE *Message );

	static EMS_RESULT SGB_BeaconID( const char *cMessage, BYTE *BeaconID, UINT64& i64BeaconID );

	static void SGB_23xBeaconID( BYTE *msg, BYTE *BeaconID );

	static void SGB_ECCgenerate( BYTE *Message );

	static void ConvertChar2ByteArray( const char *cMessage, BYTE *Message, int Nchar = 51 );
	
	static void ConvertChar2BinaryArray( const char *cMessage, BYTE *bMessage, int Nchar = 13 );
	
	static void ConvertByte2BinaryArray( BYTE *inMessage, BYTE *bMessage, int Nbyte = 32 );
	
	static void ConvertByteArray2Char( BYTE *Message, const char *cMessage, int Nbyte = 32 );

	static void ConvertBinaryArray2Byte( BYTE *bMessage, BYTE *Message, int Nbinary = 256 );

	static int HexChar( char Value );

	static void GF2Division( BYTE *bDividend, int N, BYTE *bDivsor, int M, BYTE * bQuoient  ); // N bDividend bytes / M bDivsor bytes =  M bQuoient bytes

	static void SGBencodedlocation( BYTE *Message, double& dSGBlatitude, double& dSGBlongitude, double& dSGBaltitude );


private:
	static void ConvertChar2Byte( const char Text,  BYTE data );

private: // data
	BYTE	 m_msg[300];
	BYTE	 m_bcnid[96];
	BYTE	 m_BeaconID[23];
	INT64	 m_i64BeaconID;
	WORD	 m_wBeaconID[12];
	WORD	 m_wBeaconMsg[32];
	WORD	 m_wFrameSynch[7];
	WORD	 m_wCountryCode;
	WORD	 m_wSelftest;
	WORD	 m_wHoming;
	WORD     m_wMID;
	WORD	 m_wTestProtocol;

	ULONG	 m_ulTAC;
	ULONG	 m_ulVesselID;

	double   m_dLatitude;
	double   m_dLongitude;
	double   m_dAltitude;


};

#endif