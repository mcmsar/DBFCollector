/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
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


#ifndef __CSEL_BEACON_H__
#define __CSEL_BEACON_H__

#include "emstypes.h"

//! Decodes CSEL type beacons.
class CEMSCSELBeacon
{
public:
	CEMSCSELBeacon();
	CEMSCSELBeacon( const CEMSCSELBeacon& x );
	CEMSCSELBeacon( const char* cBcnMsg, const int iSize ); // iSize either 18, 30 or 36
	virtual ~CEMSCSELBeacon();

	bool   Bit( const int iPos ) const;
    int    Bits( const int iStart, const int iEnd ) const;


	bool	HasValidEncodedLocation() const;
	double	GetLat() const;
	double	GetLong() const;
	bool	GetLatLong( double& rdLat, double& rdLong ) const { return _CalculateLocation( rdLat, rdLong); }

	bool    IsCSELBeacon() const;
	INT64	GetBeaconID() const;
	void    GetHexBeaconId( char* szHexBcnId ) const;

	int     GetFrameSynch() const { return Bits(1, 24);}
	int     GetFormatFlag() const { return Bits(25,25);}
	int     GetProtFlag() const { return Bits(26,26);}
	int     GetCountryCode() const { return Bits(27,36);}
	int     GetUserProt() const { return Bits(37,39);}
	int		GetSystemId() const { return Bits(40,47);}
	bool	IsUserProtocol() const { return Bit(26); }
	bool	IsLongMsg() const { return Bit(25); }

	void SetCountryCode( const long clCode ) { m_lCC = clCode; }

protected:
	void	_GetHexBeaconId( char* szHexBcnId, INT64 i64BcnId ) const;
	bool	_CalculateLocation( double& rdLat, double& rdLong ) const;

private:
	BYTE	m_cBcnMsg[18];
	long	m_lCC;
};

#endif