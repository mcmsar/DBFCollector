#ifndef EMSBEACONID_H
#define EMSBEACONID_H

#include "EMSTYPES.h"
#include "EMSBEACONDFNS.h"

class CBeaconID2
{
public:
	CBeaconID2(  );
    CBeaconID2( BYTE bsBeaconID[EMSBeaconDefs::LENGTH_BYTE_BEACONID] );	// Beacon Data should be MSB justified
	CBeaconID2( CBeaconID2 &rBeaconID );
	CBeaconID2( INT64 i64BeaconID );        // BeaconID should be LSB justified

	~CBeaconID2(  );

	void toHexString( TCHAR szBeaconID[EMSBeaconDefs::LENGTH_NIBBLE_BEACONID] ) const;

	CBeaconID2 &operator= ( const CBeaconID2 &rBeaconID );
	CBeaconID2 &operator= ( INT64 i64BeaconID );
	CBeaconID2 &operator= ( const BYTE bsBeaconID[EMSBeaconDefs::LENGTH_BYTE_BEACONID] );  // Beacon Data should be MSB justified
	CBeaconID2 &operator= ( const TCHAR szHexBeaconID[EMSBeaconDefs::LENGTH_NIBBLE_BEACONID] );

    CBeaconID2 &operator&= ( const CBeaconID2 &rBeaconID );
    CBeaconID2 &operator|= ( const CBeaconID2 &rBeaconID );

    INT64 operator& ( const CBeaconID2 &rBeaconID ) const;
    INT64 operator| ( const CBeaconID2 &rBeaconID ) const;

	BOOL operator== ( const CBeaconID2 &beaconID ) const;

    inline operator INT64(  ) const { return m_i64BeaconID; };  // BeaconID should be LSB justified

private:
	INT64	m_i64BeaconID;      // Beacon is LSB justified

};

#endif