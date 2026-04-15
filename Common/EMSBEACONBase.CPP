#pragma warning( disable : 4786)

#include <set>
#include <algorithm>
#include <iterator>

#include "EMSTYPES.h"
#include "EMSBEACONBase.h"
#include "EMSBEACONDFNS.h"

using namespace EMSBeaconDefs;

typedef std::multiset<CBeaconMsgBase::NatStandCodes> NatStandCodeSet;
typedef std::multiset<CBeaconMsgBase::UserCodes> UserCodeSet;

// define National, Standard and Test Code Sets using STL multisets
const CBeaconMsgBase::NatStandCodes NationalCodes[6] = { CBeaconMsgBase::BP_NAT_ELT,
                                                     //CBeaconMsgBase::BP_NAT_SPARE,
													 CBeaconMsgBase::BP_ELT_DT,
                                                     CBeaconMsgBase::BP_NAT_EPIRB,
                                                     CBeaconMsgBase::BP_NAT_PLB,
													 CBeaconMsgBase::BP_NAT_RLS,
                                                     CBeaconMsgBase::BP_NAT_TST };

//const CBeaconMsgBase::NatStandCodes StandardCodes[7] = { CBeaconMsgBase::BP_STD_EPIRB_MMSI,
const CBeaconMsgBase::NatStandCodes StandardCodes[8] = { CBeaconMsgBase::BP_STD_EPIRB_MMSI,
                                                     CBeaconMsgBase::BP_STD_ELT_AC24,
                                                     CBeaconMsgBase::BP_STD_ELT_SER,
                                                     CBeaconMsgBase::BP_STD_ELT_ACOD,
                                                     CBeaconMsgBase::BP_STD_EPIRB_SER,
                                                     CBeaconMsgBase::BP_STD_PLB_SER,
                                                     CBeaconMsgBase::BP_STD_TST,
													 CBeaconMsgBase::BP_SSAS };

const CBeaconMsgBase::NatStandCodes TestCodes[2] = { CBeaconMsgBase::BP_STD_TST,
                                                 CBeaconMsgBase::BP_NAT_TST };

const CBeaconMsgBase::NatStandCodes OrbitographyCodes[2] = { CBeaconMsgBase::BP_RESERVED1,
                                                         CBeaconMsgBase::BP_RESERVED2 };

//const CBeaconMsgBase::NatStandCodes NatStandLocationCodes[12] = { CBeaconMsgBase::BP_STD_EPIRB_MMSI,
const CBeaconMsgBase::NatStandCodes NatStandLocationCodes[14] = { CBeaconMsgBase::BP_STD_EPIRB_MMSI,
                                                              CBeaconMsgBase::BP_STD_ELT_AC24,
                                                              CBeaconMsgBase::BP_STD_ELT_SER,
                                                              CBeaconMsgBase::BP_STD_ELT_ACOD,
                                                              CBeaconMsgBase::BP_STD_EPIRB_SER,
                                                              CBeaconMsgBase::BP_STD_PLB_SER,
                                                              CBeaconMsgBase::BP_STD_TST,
                                                              CBeaconMsgBase::BP_NAT_ELT,
                                                              //CBeaconMsgBase::BP_NAT_SPARE,
															  CBeaconMsgBase::BP_ELT_DT,
                                                              CBeaconMsgBase::BP_NAT_EPIRB,
                                                              CBeaconMsgBase::BP_NAT_PLB,
                                                              CBeaconMsgBase::BP_SSAS,
															  CBeaconMsgBase::BP_NAT_RLS,
                                                              CBeaconMsgBase::BP_NAT_TST };

const CBeaconMsgBase::UserCodes UserLocationCodes[6] = { CBeaconMsgBase::USER_AVIATION,
                                                     CBeaconMsgBase::USER_MARINE,
                                                     CBeaconMsgBase::USER_SER,
                                                     CBeaconMsgBase::USER_NAT,
                                                     CBeaconMsgBase::USER_RCS,
                                                     CBeaconMsgBase::USER_TEST };

const NatStandCodeSet NationalCodeSet( NationalCodes, NationalCodes + 6 );
const NatStandCodeSet StandardCodeSet( StandardCodes, StandardCodes + 8 );
const NatStandCodeSet TestCodeSet( TestCodes, TestCodes + 2 );
const NatStandCodeSet OrbitographyCodeSet( OrbitographyCodes, OrbitographyCodes + 2 );
const NatStandCodeSet NatStandLocationCodeSet( NatStandLocationCodes, NatStandLocationCodes + 14 );
//const NatStandCodeSet NatStandLocationCodeSet( NatStandLocationCodes, NatStandLocationCodes + 12 );
const UserCodeSet UserLocationCodeSet( UserLocationCodes, UserLocationCodes + 6 );


// class implementation
CBeaconMsgBase::CBeaconMsgBase(  ) : m_Preamble(PREAMBLE_NULL)
{
    m_byPDF1BitErrors = 0;
    m_byPDF2BitErrors = 0;
}

CBeaconMsgBase::CBeaconMsgBase( const CBeaconMsgBase &rBeaconMsg )
{
    *this = rBeaconMsg;
}

CBeaconMsgBase::CBeaconMsgBase( const BYTE Msg[],
                        ULONG ulSrcOffset,
                        ULONG ulDestOffset,
                        ULONG ulLength )
{
    Set( Msg, ulSrcOffset, ulDestOffset, ulLength );
}

// The following constructor is deprecated and will be removed in a future software release.
// Instead use CBeaconMsg() followed by a call to Set( Msg[] ...)
CBeaconMsgBase::CBeaconMsgBase( const CBeaconID2 &rBeaconID ) : m_Preamble(PREAMBLE_NULL)
{
    m_PDF2.Clear();
    m_PDF1.setBeaconID( rBeaconID );
    m_byPDF1BitErrors = 0;
    m_byPDF2BitErrors = 0;
}
// end deprecated

CBeaconMsgBase::~CBeaconMsgBase(  )
{
}

CBeaconMsgBase & CBeaconMsgBase::operator = ( const CBeaconMsgBase &rBeaconMsg )
{
    if( this != &rBeaconMsg )
    {
        m_Preamble = rBeaconMsg.m_Preamble;
        m_PDF1 = rBeaconMsg.m_PDF1;
        m_PDF2 = rBeaconMsg.m_PDF2;
        m_byPDF1BitErrors = rBeaconMsg.m_byPDF1BitErrors;
        m_byPDF2BitErrors = rBeaconMsg.m_byPDF2BitErrors;
		m_strBeaconMsg = rBeaconMsg.m_strBeaconMsg;
    }

    return *this;
}

void CBeaconMsgBase::Set( const CBeaconMsgBase &rBeaconMsg )
{
    *this = rBeaconMsg;
}

void CBeaconMsgBase::Set( const BYTE Msg[],
                      ULONG ulSrcOffset,    // offset to start copying bits from
                      ULONG ulDestOffset,   // offset to start copying bits into
                      ULONG ulLength,       // number of bits to copy
                      BOOL bClear )
{
    ULONG ulSrcByte = ulSrcOffset / 8;
    ULONG ulSrcByteOffset = ulSrcOffset % 8;
    ULONG ulDestByteOffset = ulDestOffset % 8;
    ULONG ulPreamble = 0;
    ULONG ulPreambleMask = 0;
    ULONG ulMask = 0x800000 >> ulDestOffset;
    BYTE byMask = 0x80 >> ulSrcByteOffset;

	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";

    // clear beacon message
    if( bClear )
    {
        Clear(  );
    }

    // make sure length is not too long
    if( ulDestOffset + ulLength > LENGTH_BIT_BEACONMSG )
    {
        ulLength = LENGTH_BIT_BEACONMSG - ulDestOffset;
    }

    // set preamble
    while( (ulDestOffset < OFFSET_PDF1_BIT) && (ulLength > 0) )
    {
        ulPreambleMask |= ulMask;
        if( Msg[ulSrcByte] & byMask )
        {
            ulPreamble |= ulMask;
        }

        ulMask >>= 1;
        byMask >>= 1;
        if( 0 == byMask )
        {
            byMask = 0x80;
            ulSrcByte++;
        }

        ulSrcOffset++;
        ulDestOffset++;
        ulLength--;
    }
    
    if( ulPreambleMask )
    {
        m_Preamble = (Preamble)((((ULONG)m_Preamble) & ~ulPreambleMask) | ulPreamble);
    }

    // set PDF1
    if( (ulDestOffset < OFFSET_PDF2_BIT) && (ulLength > 0) )
    {
        ULONG ulPDF1Length = ulLength < LENGTH_BIT_PDF1 - (ulDestOffset - OFFSET_PDF1_BIT) ? ulLength : LENGTH_BIT_PDF1 - (ulDestOffset - OFFSET_PDF1_BIT);

        m_PDF1.setBitSequence( &Msg[ulSrcByte],
                               ulSrcOffset % 8,
                               ulDestOffset - OFFSET_PDF1_BIT,
                               ulPDF1Length,
                               bClear );

        ulLength -= ulPDF1Length;
        ulDestOffset += ulPDF1Length;
        ulSrcOffset += ulPDF1Length;
        ulSrcByte = ulSrcOffset / 8;
    }

    // set PDF2
    if( ulLength > 0 )
    {
        ULONG ulPDF2Length = ulLength < LENGTH_BIT_PDF2 - (ulDestOffset - OFFSET_PDF2_BIT) ? ulLength : LENGTH_BIT_PDF2 - (ulDestOffset - OFFSET_PDF2_BIT);

        m_PDF2.setBitSequence( &Msg[ulSrcByte],
                               ulSrcOffset % 8,
                               ulDestOffset - OFFSET_PDF2_BIT,
                               ulPDF2Length,
                               bClear );
    }

    //check for errors
    CorrectBitErrors();
}

void CBeaconMsgBase::Set( const CBeaconID2 &rBeaconID )
{
    m_PDF1 = rBeaconID;
    m_byPDF1BitErrors = 0;
    m_byPDF2BitErrors = 0;
	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";
}

void CBeaconMsgBase::Set( const float Msg[],
                      ULONG ulSrcOffset,
                      ULONG ulDestOffset,
                      ULONG ulLength,
                      BOOL bClear )
{
    ULONG ulDestByteOffset = ulDestOffset % 8;
    ULONG ulTemp = 0;
    ULONG ulMask = 0x800000 >> ulDestOffset;
    ULONG ulPreambleMask = 0;

	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";

    // clear beacon message
    if( bClear )
    {
        Clear(  );
    }

    // make sure length is not too long
    if( ulDestOffset + ulLength > LENGTH_BIT_BEACONMSG )
    {
        ulLength = LENGTH_BIT_BEACONMSG - ulDestOffset;
    }

    // set preamble
    while( (ulDestOffset < OFFSET_PDF1_BIT) && (ulLength > 0) )
    {
        ulPreambleMask |= ulMask;
        if( Msg[ulSrcOffset] > 0.0 )
        {
            ulTemp |= ulMask;
        }

        ulMask >>= 1;

        ulSrcOffset++;
        ulDestOffset++;
        ulLength--;
    }

    if( ulPreambleMask != 0 )
    {
        m_Preamble = (Preamble)((((ULONG)m_Preamble) & ~ulPreambleMask) | ulTemp);
    }

    // set PDF1
    if( (ulDestOffset < OFFSET_PDF2_BIT) && (ulLength > 0) )
    {
        BYTE abyMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG];
        BYTE byMask = 0x80;
        ULONG ulPDF1Length = ulLength < LENGTH_BIT_PDF1 - (ulDestOffset - OFFSET_PDF1_BIT) ? ulLength : LENGTH_BIT_PDF1 - (ulDestOffset - OFFSET_PDF1_BIT);
        ULONG ulTempDestByte = 0;

        memset( abyMsg, 0, sizeof(BYTE) * EMSBeaconDefs::LENGTH_BYTE_BEACONMSG );

        for( UINT i = 0; i < ulPDF1Length; i++ )
        {
            if( Msg[ulSrcOffset++] > 0.0 )
            {
                abyMsg[ulTempDestByte] |= byMask;
            }

            byMask >>= 1;
            if( !byMask )
            {
                byMask = 0x80;
                ulTempDestByte++;
            }
        }

        m_PDF1.setBitSequence( abyMsg,
                               0,
                               ulDestOffset - OFFSET_PDF1_BIT,
                               ulPDF1Length,
                               bClear );

        ulLength -= ulPDF1Length;
        ulDestOffset += ulPDF1Length;
    }

    // set PDF2
    if( ulLength > 0 )
    {
        BYTE abyMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG];
        BYTE byMask = 0x80;
        ULONG ulPDF2Length = ulLength < LENGTH_BIT_PDF2 - (ulDestOffset - OFFSET_PDF2_BIT) ? ulLength : LENGTH_BIT_PDF2 - (ulDestOffset - OFFSET_PDF2_BIT);
        ULONG ulTempDestByte = 0;

        memset( abyMsg, 0, sizeof(BYTE) * EMSBeaconDefs::LENGTH_BYTE_BEACONMSG );

        for( UINT i = 0; i < ulPDF2Length; i++ )
        {
            if( Msg[ulSrcOffset++] > 0.0 )
            {
                abyMsg[ulTempDestByte] |= byMask;
            }

            byMask >>= 1;
            if( !byMask )
            {
                ulTempDestByte++;
                byMask = 0x80;
            }
        }

        m_PDF2.setBitSequence( abyMsg,
                               0,
                               ulDestOffset - OFFSET_PDF2_BIT,
                               ulPDF2Length,
                               bClear );
    }

    // check and correct for errors
    CorrectBitErrors();
}

void CBeaconMsgBase::toHexString( TCHAR szBeaconMsg[],
                              ULONG ulStartBit,
                              ULONG ulLengthNibbles ) const
{
    BYTE byBcnMsg[LENGTH_BYTE_BEACONMSG];
    ULONG ulDstByte = 0;
    ULONG ulSrcByte = ulStartBit / 8;
    ULONG ulSrcByteOffset = ulStartBit % 8;
    BYTE byMask = 0x80 >> ulSrcByteOffset;

    // make sure ulLengthNibbles is not too long
    if( LENGTH_BIT_BEACONMSG < ulStartBit + (ulLengthNibbles * 4) )
    {
        ulLengthNibbles = (LENGTH_BIT_BEACONMSG - ulStartBit) / 4;
    }

    Get( byBcnMsg );

    for( UINT i = 0; i < ulLengthNibbles; i++ )
    {
        BYTE byNibble = 0;

        for( INT j = 0; j < 4; j++ )
        {
            byNibble <<= 1;
            if( 0 != (byBcnMsg[ulSrcByte] & byMask) )
            {
                byNibble |= 1;
            }

            byMask >>= 1;
            if( 0 == byMask )
            {
                byMask = 0x80;
                ulSrcByte++;
            }
        }

        if( byNibble <= 9 )
        {
            szBeaconMsg[ulDstByte] = byNibble + '0';
        }
        else
        {
            szBeaconMsg[ulDstByte] = byNibble - 10 + 'A';
        }

        ulDstByte++;
    }
}

void CBeaconMsgBase::SetPreamble( Preamble preamble )
{
	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";
    m_Preamble = preamble;
}

void CBeaconMsgBase::SetPDF1( const CBeaconPDF1 &rBeaconPDF1 )
{
	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";
    m_PDF1 = rBeaconPDF1;
}

void CBeaconMsgBase::SetPDF2( const CBeaconPDF2 &rBeaconPDF2 )
{
	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";
    m_PDF2 = rBeaconPDF2;
}

BOOL CBeaconMsgBase::SetBit( ULONG ulBitNum )
{
	// New data so clear the stored string representation of the beacon message
	m_strBeaconMsg = "";

    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_BEACONMSG ) )
    {
        if( ulBitNum <= OFFSET_PDF1_BIT )
        {
            m_Preamble = (Preamble)(((ULONG)m_Preamble) | (0x800000 >> (ulBitNum - 1)));
        }
        else if( ulBitNum <= OFFSET_PDF2_BIT )
        {
            m_PDF1.setBit( ulBitNum - OFFSET_PDF1_BIT );
        }
        else
        {
            m_PDF2.setBit( ulBitNum - OFFSET_PDF2_BIT );
        }
        return TRUE;
    }
    return FALSE;
}

void CBeaconMsgBase::Clear(  )
{
    m_Preamble = PREAMBLE_NULL;
    m_PDF1.Clear(  );
    m_PDF2.Clear(  );
	m_strBeaconMsg = "";
}

BOOL CBeaconMsgBase::PreambleEncoded(  )
{
    return m_Preamble != PREAMBLE_NULL;
}

BOOL CBeaconMsgBase::PDF1Encoded(  )
{
    return TRUE;
}

BOOL CBeaconMsgBase::PDF2Encoded(  )
{
    return TRUE;
}

BOOL CBeaconMsgBase::LongLatEncoded(  ) const
{
    BOOL bRet = FALSE;

    if( getProtocolFlag() )
    {
        UserCodeSet protocol;
        UserCodeSet result;

        protocol.insert( (UserCodes)m_PDF1.getProtocolCode(  ) );

        std::set_intersection( protocol.begin( ),
                               protocol.end(  ),
                               UserLocationCodeSet.begin(  ),
                               UserLocationCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        bRet = result.empty(  ) ? FALSE : TRUE;
    }
    else
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;

        protocol.insert( (NatStandCodes)m_PDF1.getProtocolCode(  ) );

        std::set_intersection( protocol.begin( ),
                               protocol.end(  ),
                               NatStandLocationCodeSet.begin(  ),
                               NatStandLocationCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        bRet = result.empty(  ) ? FALSE : TRUE;
    }

    return bRet;
}

void CBeaconMsgBase::Get( BYTE Msg[],
                      ULONG ulDstOffset,
                      ULONG ulSrcOffset,
                      ULONG ulBitLength ) const
{
    ULONG ulDstByte = ulDstOffset / 8;
    ULONG ulSrcByte = ulSrcOffset / 8;
    ULONG ulDstByteOffset = ulDstOffset % 8;
    ULONG ulSrcByteOffset = ulSrcOffset % 8;
    ULONG ulTempPreamble = static_cast<ULONG>(m_Preamble) << ulSrcOffset;
    BYTE byMask = 0x80 >> ulSrcByteOffset;

    // make sure length is no too much
    if( ulSrcOffset + ulBitLength > LENGTH_BIT_BEACONMSG )
    {
        ulBitLength = LENGTH_BIT_BEACONMSG - ulSrcOffset;
    }

    // encode preamble
    while( (ulSrcOffset < OFFSET_PDF1_BIT) && (ulBitLength > 0) ) 
    {
        if( 0 != (ulTempPreamble & 0x800000) )
        {
            Msg[ulDstByte] |= byMask;
        }
        else
        {
            Msg[ulDstByte] &= ~byMask;
        }

        byMask >>= 1;
        if( 0 == byMask )
        {
            byMask = 0x80;
            ulDstByte++;
        }

        ulDstOffset++;
        ulSrcOffset++;
        ulBitLength--;
        ulTempPreamble <<= 1;
    }

    if( (ulSrcOffset < OFFSET_PDF2_BIT) && (ulBitLength > 0) )
    {
        ULONG ulPDF1Length = ulBitLength < LENGTH_BIT_PDF1 - (ulSrcOffset - OFFSET_PDF1_BIT) ? ulBitLength : LENGTH_BIT_PDF1 - (ulSrcOffset - OFFSET_PDF1_BIT);

        ulDstByte = ulDstOffset / 8;
        ulDstByteOffset = ulDstOffset % 8;

        m_PDF1.getBitSequence( &Msg[ulDstByte],
                               ulDstByteOffset,
                               ulSrcOffset - OFFSET_PDF1_BIT,
                               ulPDF1Length );

        ulBitLength -= ulPDF1Length;
        ulSrcOffset += ulPDF1Length;
        ulDstOffset += ulPDF1Length;
    }

    if( ulBitLength > 0 )
    {
        ULONG ulPDF2Length = ulBitLength < LENGTH_BIT_PDF2 - (ulSrcOffset - OFFSET_PDF2_BIT) ? ulBitLength : LENGTH_BIT_PDF2 - (ulSrcOffset - OFFSET_PDF2_BIT);

        ulDstByte = ulDstOffset / 8;
        ulDstByteOffset = ulDstOffset % 8;

        m_PDF2.getBitSequence( &Msg[ulDstByte],
                               ulDstByteOffset,
                               ulSrcOffset - OFFSET_PDF2_BIT,
                               ulPDF2Length );
    }
}

CBeaconMsgBase::Preamble CBeaconMsgBase::getPreamble(  ) const
{
    return m_Preamble;
}

CBeaconPDF1 & CBeaconMsgBase::getPDF1(  )
{
    return m_PDF1;
}

CBeaconPDF2 & CBeaconMsgBase::getPDF2(  )
{
    return m_PDF2;
}

BOOL CBeaconMsgBase::getFormatFlag(  ) const
{
    return m_PDF1.getFormatFlag(  );
}

BOOL CBeaconMsgBase::getProtocolFlag(  ) const
{
    return m_PDF1.getProtocolFlag(  );
}

ULONG CBeaconMsgBase::getProtocolCode(  ) const
{
    return m_PDF1.getProtocolCode(  );
}

ULONG CBeaconMsgBase::getCountryCode(  ) const
{
    return m_PDF1.getCountryCode(  );
}

CBeaconID2 CBeaconMsgBase::getBeaconID(  )
{
    CBeaconID2 beaconID;
    //if( !getProtocolFlag() )
	
	// Ticket 40176: C/S Specification T.002 4.2.5.3
    if( !getProtocolFlag() && (m_PDF1.CheckError() < 4) )
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;

        protocol.insert( (NatStandCodes)m_PDF1.getProtocolCode(  ) );

        std::set_intersection( protocol.begin( ),
                               protocol.end(  ),
                               NatStandLocationCodeSet.begin(  ),
                               NatStandLocationCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        if( !result.empty(  ) )
        {
            BYTE protocol;
            if( IsNational( &protocol ) )
            {
				if( (NatStandCodes)protocol == CBeaconMsgBase::BP_ELT_DT )
				{
					//we got an elt beacon!!
					beaconID = m_PDF1.getBeaconID( 0xFFFFFFFFFFF80000 );
					beaconID |= 0x3FDFF; // set the default location 
				}
				else if( (NatStandCodes)protocol == CBeaconMsgBase::BP_NAT_RLS )
				{
					//we got an elt beacon!!
					beaconID = m_PDF1.getBeaconID( 0xFFFFFFFFFFF80000 );
					beaconID |= 0x3FDFF; // set the default location 
				}
				else
				{
					beaconID = m_PDF1.getBeaconID( 0xFFFFFFFFF8000000 );
					beaconID |= 0x3F81FE0; // set the default location 
				}
            }
            else
            {
                beaconID = m_PDF1.getBeaconID( 0xFFFFFFFFFFE00000 );
                beaconID |= 0xFFBFF; // set the default location 
            }
        }
        else
        {
            beaconID = m_PDF1.getBeaconID();
        }
    }
    else
    {
        beaconID = m_PDF1.getBeaconID();
    }

    return beaconID;
}

BOOL CBeaconMsgBase::getBit( ULONG ulBitNum ) const
{
    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_BEACONMSG) )
    {
        if( ulBitNum <= OFFSET_PDF1_BIT )
        {
            return (((ULONG)m_Preamble) >> (LENGTH_BIT_PREAMBLE - ulBitNum)) & 0x1;
        }
        else if( ulBitNum <= OFFSET_PDF2_BIT )
        {
            return m_PDF1.getBit( ulBitNum - OFFSET_PDF1_BIT );
        }
        else
        {
            return m_PDF2.getBit( ulBitNum - OFFSET_PDF2_BIT );
        }
    }

    return FALSE;
}

BOOL CBeaconMsgBase::IsUser(  ) const
{
    return m_PDF1.getProtocolFlag(  );
}

BOOL CBeaconMsgBase::PDF2Correctable() const
{
    return (getFormatFlag() == TRUE) && (LongLatEncoded() == TRUE);
}

BOOL CBeaconMsgBase::IsNational( BYTE* nSet  ) const
{
    if( !m_PDF1.getProtocolFlag(  ) )
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;
		if( nSet )
			*nSet = m_PDF1.getProtocolCode(  );
        protocol.insert( (NatStandCodes)m_PDF1.getProtocolCode(  ) );

        std::set_intersection( protocol.begin( ),
                               protocol.end(  ),
                               NationalCodeSet.begin(  ),
                               NationalCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        return result.empty(  ) ? FALSE : TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CBeaconMsgBase::IsStandard(  ) const
{
    if( !m_PDF1.getProtocolFlag(  ) )
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;

        protocol.insert( (NatStandCodes)m_PDF1.getProtocolCode(  ) );

        std::set_intersection( protocol.begin( ),
                               protocol.end(  ),
                               StandardCodeSet.begin(  ),
                               StandardCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        return !result.empty(  );
    }
    else
    {
        return FALSE;
    }
}

BOOL CBeaconMsgBase::IsTestBeacon(  ) const
{
    BYTE byProtocolCode = m_PDF1.getProtocolCode(  );

    if( m_PDF1.getProtocolFlag(  ) )
    {
        return (NatStandCodes)byProtocolCode == USER_TEST;
    }
    else
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;

        protocol.insert( (NatStandCodes)byProtocolCode );

        std::set_intersection( protocol.begin(  ),
                               protocol.end(  ),
                               TestCodeSet.begin(  ),
                               TestCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        return !result.empty(  );
    }
}

BOOL CBeaconMsgBase::IsOrbitography(  ) const
{
    BYTE byProtocolCode = m_PDF1.getProtocolCode(  );

    if( m_PDF1.getProtocolFlag(  ) )
    {
        return (NatStandCodes)byProtocolCode == USER_ORBITOGRAPHY;
    }
    else
    {
        NatStandCodeSet protocol;
        NatStandCodeSet result;

        protocol.insert( (NatStandCodes)byProtocolCode );

        std::set_intersection( protocol.begin(  ),
                               protocol.end(  ),
                               OrbitographyCodeSet.begin(  ),
                               OrbitographyCodeSet.end(  ),
                               std::inserter( result, result.begin(  ) ) );

        return !result.empty(  );
    }
}

INT CBeaconMsgBase::CheckFSError( void ) 
{
	return CheckFSError( m_Preamble );
}

INT CBeaconMsgBase::CheckFSError( Preamble &rPreamble )
{
    ULONG ulMResult = ((ULONG)m_Preamble) ^ ((ULONG)CBeaconMsgBase::PREAMBLE_NORMAL_FS);
    ULONG ulTResult = ((ULONG)m_Preamble) ^ ((ULONG)CBeaconMsgBase::PREAMBLE_INVERTED_FS);
    ulMResult = CountBits( ulMResult );
    ulTResult = CountBits( ulTResult );

    if( ulMResult <= ulTResult )
    {
        rPreamble = PREAMBLE_NORMAL_FS;
        return ulMResult;
    }
    else
    {
        rPreamble = PREAMBLE_INVERTED_FS;
        return ulTResult;
    }

}

ULONG CBeaconMsgBase::CountBits( DWORD dword ) const
{
    ULONG ret = 0;
    while( dword )
    {
        if( dword & 0x1 )
        {
            ret++;
        }
        dword >>= 1;
    }

    return ret;
}

void CBeaconMsgBase::CorrectBitErrors()
{
    m_byPDF2BitErrors = 0;

    if( (m_byPDF1BitErrors = m_PDF1.CheckError()) <= BIT_ERRORS_PDF1_MAX )
    {
        m_PDF1.CorrectError( );

        // now determine if there is a PDF2 and if it can be corrected
        if( PDF2Correctable() )
        {
            if( (m_byPDF2BitErrors = m_PDF2.CheckError()) <= BIT_ERRORS_PDF2_MAX )
            {
                m_PDF2.CorrectError( );
            }
        }
    }
}

void CBeaconMsgBase::SetDefaultValues( )
{
	SetDefaultValuesPDF1( );
	SetDefaultValuesPDF2( );
}

void CBeaconMsgBase::SetUnconfirmedValues( void )
{
	bool bModify = true;
	BYTE byBitPattern[18];

	if ( TRUE == getFormatFlag() )	// Long Message
	{
		if ( IsOrbitography( ) )
			bModify = false;
		else
			memset( byBitPattern, 0xFF, sizeof( byBitPattern ) );	// ONEs
	}
	else										// Short Message
	{
		memset( byBitPattern, 0x0, sizeof( byBitPattern ) );	// ZEROs
	}

	if ( bModify )
	{
		// set bits 113 - 144 to byBitPattern

		m_PDF2.setBitSequence( byBitPattern,
                    		0,
                    		OFFSET_SUPPDATA_END - OFFSET_PDF2_BIT,
                    		LENGTH_BIT_BEACONMSG - OFFSET_SUPPDATA_END,
                    		FALSE );
	}
}

void CBeaconMsgBase::SetDefaultValuesPDF1( bool bSetDefaultLocation /* = false */ )
{
	if ( bSetDefaultLocation )
	{
    	if( (getProtocolFlag() == FALSE) && (LongLatEncoded() == TRUE) )
    	{
        	if( IsNational() )
        	{
            	m_PDF1.setBitSequence( National::DEFAULT_POSITION_VALUE,
                                   	0,
                                   	National::OFFSET_POSITION - OFFSET_PDF1_BIT,
                                   	National::LENGTH_BIT_POSITION,
                                   	FALSE );
        	}
        	else
        	{
            	m_PDF1.setBitSequence( Standard::DEFAULT_POSITION_VALUE,
                                   	0,
                                   	Standard::OFFSET_POSITION - OFFSET_PDF1_BIT,
                                   	Standard::LENGTH_BIT_POSITION,
                                   	FALSE );
        	}
    	}
	}
}

void CBeaconMsgBase::SetMultiInvalidValues( void )
{
	SetMultiInvalidValuesPDF2( );
}

void CBeaconMsgBase::SetMultiInvalidValuesPDF2( void )
{
	BYTE byOne[18];

	memset( byOne, 0xFF, sizeof( byOne ) );

  // set bits 113 - 144 to one
  m_PDF2.setBitSequence( byOne,
                             0,
                             OFFSET_SUPPDATA_END - OFFSET_PDF2_BIT,
                             LENGTH_BIT_BEACONMSG - OFFSET_SUPPDATA_END,
                             FALSE );
}

void CBeaconMsgBase::SetDefaultValuesPDF2( bool bSetDefaultLocation /* = false */ )
{
    if ( getFormatFlag() == TRUE )  
    {
	  	if ( m_byPDF1BitErrors > BIT_ERRORS_PDF1_MAX )
		{
        // set bits 113 - 144 to one
        BYTE byOne[18];
        memset( byOne, 0xFF, sizeof( byOne ) );

        m_PDF2.setBitSequence( byOne,
                             0,
                             OFFSET_SUPPDATA_END - OFFSET_PDF2_BIT,
                             LENGTH_BIT_BEACONMSG - OFFSET_SUPPDATA_END,
                             FALSE );
		}
		else if ( m_byPDF2BitErrors <= BIT_ERRORS_PDF2_MAX  )
        {
            if ( bSetDefaultLocation && ( LongLatEncoded() == TRUE ) )
            {
                if( getProtocolFlag() == TRUE )     // user
                {
                    m_PDF2.setBitSequence( User::DEFAULT_POSITION_VALUE,
                                           0,
                                           User::OFFSET_POSITION - OFFSET_PDF2_BIT,
                                           User::LENGTH_BIT_POSITION,
                                           FALSE );
                }
                else
                {
                    if( IsNational() )
                    {
                        m_PDF2.setBitSequence( National::DEFAULT_DELTA_POSITION_VALUE,
                                               0,
                                               National::OFFSET_DELTA_POSITION - OFFSET_PDF2_BIT,
                                               National::LENGTH_BIT_DELTA_POSITION,
                                               FALSE );
                    }
                    else    // standard
                    {
                        m_PDF2.setBitSequence( Standard::DEFAULT_DELTA_POSITION_VALUE,
                                               0, Standard::OFFSET_DELTA_POSITION - OFFSET_PDF2_BIT,
                                               Standard::LENGTH_BIT_DELTA_POSITION,
                                               FALSE );
                    }
                }
            }
        }
        else
        {
            // set bits 113 - 144 to one
            BYTE byOne[18];
            memset( byOne, 0xFF, sizeof( byOne ) );

            m_PDF2.setBitSequence( byOne,
                                   0,
                                   OFFSET_SUPPDATA_END - OFFSET_PDF2_BIT,
                                   LENGTH_BIT_BEACONMSG - OFFSET_SUPPDATA_END,
                                   FALSE );
        }
    }
    else
    {
        // set bits 113 - 144 to zero
        BYTE byZero[18];
        memset( byZero, 0, sizeof( byZero ) );

        m_PDF2.setBitSequence( byZero,
                               0,
                               OFFSET_SUPPDATA_END - OFFSET_PDF2_BIT,
                               LENGTH_BIT_BEACONMSG - OFFSET_SUPPDATA_END,
                               FALSE );
    }
}

void
CBeaconMsgBase::_SetBeaconMsgString()
{
	if ( 0 == m_strBeaconMsg.length() )
	{
		BYTE	abyMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG];
		Get( abyMsg );

		for(int i=0;i<EMSBeaconDefs::LENGTH_BYTE_BEACONMSG; i++ )
		{
			char	szByte[8];
			sprintf( szByte, "%02X", abyMsg[i] );
			m_strBeaconMsg += szByte;
		}
	}
}
