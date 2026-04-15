/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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


#ifndef EMSSEIMACBEACON_H
#define EMSSEIMACBEACON_H

class CEMSSeimacBeacon  
{
public:
	CEMSSeimacBeacon();
	CEMSSeimacBeacon( const char* cBcnMsg, const int iSize ); // iSize either 18, 30 or 36
	virtual ~CEMSSeimacBeacon();

	bool   Bit( const int iPos );
    int    Bits( const int iStart, const int iEnd );

	void   CalculateLatLong( int iLatKey, int iLongKey );
	void   CalculateLatLong( const char* szHexLatKey, const char* szHexLongKey );

	double GetLat(){ return m_dLat;}
	double GetLong(){ return m_dLong;}

	bool     IsSeimacBeacon();
	__int64  GetBeaconID();
	__int64  GetSeimacBeaconID(){ return Bits( 48, 66 ); }
	void     GetHexBeaconId( char* szHexBcnId );

	int      GetFrameSynch(){ return Bits(1, 24);}
	int      GetFormatFlag(){ return Bits(25,25);}
	int      GetProtFlag(){ return Bits(26,26);}
	int      GetCountryCode(){ return Bits(27,36);}
	int      GetUserProt(){ return Bits(37,39);}
	int		 GetSystemId(){ return Bits(37,39);}

	static bool GetSeimacBcnLatLong( const char* cBcnMsg, const int iSize,
		                             int iLatKey, int iLongKey,
									 double* pdLat, double* pdLong );

	static bool GetSeimacBcnLatLong( const char* cBcnMsg, const int iSize,
		                             const char* szHexLatKey, const char* szHexLongKey,
									 double* pdLat, double* pdLong );

protected:
	void   _ReadHexString( const char* Hex, void* Buffer, int iLength );
	int    _GetHexChar( char cHexChar );
	void   _GetHexBeaconId( char* szHexBcnId, __int64 i64BcnId );

private:
	unsigned char   m_cBcnMsg[18];
	double          m_dLat;
	double          m_dLong;
};

#endif