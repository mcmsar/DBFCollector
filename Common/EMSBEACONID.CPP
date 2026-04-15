#include "EMSTYPES.h"
#include "EMSBEACONID.h"
#include "EMSBEACONDFNS.h"

using namespace EMSBeaconDefs;

CBeaconID2::CBeaconID2(  ) : m_i64BeaconID( 0 )
{
}

CBeaconID2::CBeaconID2( BYTE bsBeaconID[LENGTH_BYTE_BEACONID] )
{
    *this = bsBeaconID;
}

CBeaconID2::CBeaconID2( CBeaconID2 &rBeaconID )
{
    *this = rBeaconID;
}

CBeaconID2::CBeaconID2( INT64 i64BeaconID ) : m_i64BeaconID( i64BeaconID )
{
}

CBeaconID2::~CBeaconID2(  )
{
}

void CBeaconID2::toHexString( TCHAR szBeaconID[LENGTH_NIBBLE_BEACONID] ) const
{
    INT64 i64BeaconID = m_i64BeaconID;  // make temp copy

    for( INT i = LENGTH_NIBBLE_BEACONID - 1; i >= 0; i-- )
    {
        if( (i64BeaconID & 0xF) <= 9 )
        {
            szBeaconID[i] = (TCHAR)(i64BeaconID & 0xF) + '0';
        }
        else
        {
            szBeaconID[i] = (TCHAR)(i64BeaconID & 0xF) - 10 + 'A';
        }

        i64BeaconID >>= 4;
    }
}

CBeaconID2& CBeaconID2::operator= ( const CBeaconID2 &rBeaconID )
{
    if( this != &rBeaconID )
    {
        m_i64BeaconID = rBeaconID.m_i64BeaconID;
    }

    return *this;
}

CBeaconID2& CBeaconID2::operator= ( INT64 i64BeaconID )
{
    m_i64BeaconID = i64BeaconID;;
    return *this;
}

CBeaconID2& CBeaconID2::operator= ( const BYTE bsBeaconID[LENGTH_BYTE_BEACONID] )
{
    BOOL bHighNibble = TRUE;
    ULONG ulByte = 0;

    m_i64BeaconID = 0;

    for( INT i = 0; i < LENGTH_NIBBLE_BEACONID; i++ )
    {
        m_i64BeaconID <<= 4;

        if( bHighNibble )
        {
            m_i64BeaconID |= ( bsBeaconID[ulByte] & 0xF0 ) >> 4;
            bHighNibble = FALSE;
        }
        else
        {
            m_i64BeaconID |= bsBeaconID[ulByte] & 0xF;
            bHighNibble = TRUE;
            ulByte++;
        }
    }

    return *this;
}

CBeaconID2& CBeaconID2::operator= ( const TCHAR szHexBeaconID[LENGTH_NIBBLE_BEACONID] )
{
    m_i64BeaconID = 0;

    for( INT i = 0; i < LENGTH_NIBBLE_BEACONID; i++ )
    {
        m_i64BeaconID <<= 4;

        if( szHexBeaconID[i] >= '0' && szHexBeaconID[i] <= '9' )
        {
            m_i64BeaconID |= szHexBeaconID[i] - '0';
        }
        else if( szHexBeaconID[i] >= 'A' && szHexBeaconID[i] <= 'F' )
        {
            m_i64BeaconID |= szHexBeaconID[i] - 'A' + 10;
        }
        else if( szHexBeaconID[i] >= 'a' && szHexBeaconID[i] <= 'f' )
        {
            m_i64BeaconID |= szHexBeaconID[i] - 'a' + 10;
        }
        else
        {
            m_i64BeaconID = 0;
        }
    }

    return *this;
}

BOOL CBeaconID2::operator== ( const CBeaconID2 &beaconID ) const
{
    return m_i64BeaconID == beaconID.m_i64BeaconID;
}

CBeaconID2 &  CBeaconID2::operator|= ( const CBeaconID2 &rBeaconID )
{
    m_i64BeaconID |= rBeaconID;
    return *this;
}