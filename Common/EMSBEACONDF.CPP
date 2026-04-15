#include "EMSBEACONDF.h"
#include "EMSBCH.h"
#include "EMSBEACONDFNS.h"

using namespace EMSBeaconDefs;

CBeaconPDF1::CBeaconPDF1(  )
{
    Clear(  );
}

CBeaconPDF1::CBeaconPDF1( const BYTE bsPDF1[],
                          ULONG ulSrcOffset,
                          ULONG ulDstOffset,
                          ULONG ulLengthBits )
{
	setBitSequence( bsPDF1,
                    ulSrcOffset,
                    ulDstOffset,
                    ulLengthBits );
}

CBeaconPDF1::CBeaconPDF1( const CBeaconPDF1 &rPDF1 )
{
    *this = rPDF1;
}

CBeaconPDF1::CBeaconPDF1( const CBeaconID2 &rBeaconID )
{
    *this = rBeaconID;
}

CBeaconPDF1::CBeaconPDF1( INT64 i64BeaconID )
{
    *this = i64BeaconID;
}

CBeaconPDF1 & CBeaconPDF1::operator = ( const CBeaconPDF1 &rPDF1 )
{
    if( this != &rPDF1 )
    {
        m_bsPDF1 = rPDF1.m_bsPDF1;
    }

    return *this;
}

CBeaconPDF1 & CBeaconPDF1::operator = ( const CBeaconID2 &rBeaconID )
{
    return *this = (INT64)rBeaconID;
}

CBeaconPDF1 & CBeaconPDF1::operator = ( INT64 i64BeaconID )
{
    Clear(  );

	for( INT i = 0; i < LENGTH_BIT_BEACONID; i++ )
	{
        m_bsPDF1.set( LENGTH_BIT_PDF1 + i - 61, i64BeaconID & 1 );
        i64BeaconID >>= 1;
	}

    return *this;
}

void CBeaconPDF1::Clear(  )
{
	m_bsPDF1.reset();
}

void CBeaconPDF1::setBitSequence( const BYTE bsPDF1[],
                                  ULONG ulSrcOffset,
                                  ULONG ulDstOffset,
                                  ULONG ulLengthBits,
                                  BOOL bClear )
{
    PDF1bs bsPD1;
    PDF1bs bsMask;
    ULONG ulSrcByte = ulSrcOffset / 8;
    ULONG ulSrcByteOffset = ulSrcOffset % 8;
    ULONG ulDstByte = ulDstOffset / 8;
    ULONG ulDstByteOffset = ulDstOffset % 8;

    // make sure length is not too long
    if( ulDstOffset + ulLengthBits > LENGTH_BIT_PDF1 )
    {
        ulLengthBits = LENGTH_BIT_PDF1 - ulDstOffset;
    }

    // Zero out the bits in PDF1
    if( bClear )
    {
        Clear(  );
    }

    bsPD1.reset();
    bsMask.reset();

    // mask, shift and copy lead-in bit(s) which are not alligned on byte boundary
    if( ulSrcByteOffset > 0 )
    {
        BYTE byTemp = 0;
        ULONG ulNumSBits = 8 - ulSrcByteOffset; // number of bits from first source byte to copy

        for( ULONG i = 0; i < ulNumSBits; i++ )
        {
            byTemp <<= 1;
            byTemp |= 0x1;
        }

        bsMask |= PDF1bs( byTemp ) << LENGTH_BIT_PDF1 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);
        bsPD1 |= PDF1bs( bsPDF1[ulSrcByte] & byTemp ) << LENGTH_BIT_PDF1 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);

        ulLengthBits -= ulNumSBits;
        ulSrcByte++;
        ulDstByte++;
    }

    // copy in one byte blocks
    while( ulLengthBits >= 8 )
    {
        bsMask |= PDF1bs( (BYTE)0xff ) << LENGTH_BIT_PDF1 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);
        bsPD1 |= PDF1bs( bsPDF1[ulSrcByte] ) << LENGTH_BIT_PDF1 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);

        ulSrcByte++;
        ulDstByte++;
        ulLengthBits -= 8;
    }

    // mask, shift and copy lead-out bits
    if( ulLengthBits > 0 )
    {
        BYTE byTemp = 0;

        for( ULONG j = 0; j < ulLengthBits; j++ )
        {
            byTemp >>= 1;
            byTemp |= 0x80;
        }
        bsMask |= PDF1bs( byTemp ) >> (8 - ulLengthBits);
        bsPD1 |= PDF1bs( bsPDF1[ulSrcByte] & byTemp ) >> (8 - ulLengthBits);
    }

    bsMask.flip();
    m_bsPDF1 &= bsMask;
    m_bsPDF1 |= bsPD1;
}

void CBeaconPDF1::getBitSequence( BYTE bsPDF1[],
                                  ULONG ulDstOffset,
                                  ULONG ulSrcOffset,
                                  ULONG ulLengthBits ) const
{
    ULONG ulDstByte = ulDstOffset / 8;
    ULONG ulDstByteOffset = ulDstOffset % 8;
    BYTE byMask = 0x80 >> ulDstByteOffset;

    // make sure ulLengthBits is no too long
    if( LENGTH_BIT_PDF1 < (ulSrcOffset + ulLengthBits) )
    {
        ulLengthBits = LENGTH_BIT_PDF1 - ulSrcOffset;
    }

    for( INT i = 1; i <= ulLengthBits; i++ )
    {
        if( true == m_bsPDF1.test( LENGTH_BIT_PDF1 - ulSrcOffset - i ) )
        {
            bsPDF1[ulDstByte] |= byMask;
        }
        else
        {
            bsPDF1[ulDstByte] &= ~byMask;
        }

        byMask >>= 1;
        if( 0 == byMask )
        {
            byMask = 0x80;
            ulDstByte++;
        }
    }
}

BOOL CBeaconPDF1::setCountryCode( WORD wCountryCode )
{
	if( !(wCountryCode & 0xFC00) )
	{
		m_bsPDF1 |= PDF1bs(wCountryCode) << LENGTH_BIT_PDF1 - 10 - 2;
		return TRUE;
	}

	return FALSE;
}

void CBeaconPDF1::setFormatFlag( Format format )
{
    m_bsPDF1.set( LENGTH_BIT_PDF1 - 1, format == FORMAT_SHORT ? false : true );
}

void CBeaconPDF1::setProtocolFlag( Protocol protocol )
{
    m_bsPDF1.set( LENGTH_BIT_PDF1 - 2, protocol == FORMAT_STANDARD ? false : true );
}

BOOL CBeaconPDF1::setProtocolCode( BYTE byProtocol )
{
	BOOL bProtocol = m_bsPDF1.test( LENGTH_BIT_PDF1 - 2 );

	if( (bProtocol && !(byProtocol & 0xF8)) || (!bProtocol && (byProtocol & 0xF0) ) )
	{
		m_bsPDF1 |= PDF1bs( byProtocol ) << LENGTH_BIT_PDF1 - 12 - (bProtocol ? 3 : 4);
		return TRUE;
	}
	return FALSE;
}

void CBeaconPDF1::setBeaconID( const CBeaconID2 &rBeacon )
{
    *this = rBeacon;
}

BOOL CBeaconPDF1::setBit( ULONG ulBitNum )
{
    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_PDF1) )
    {
        m_bsPDF1.set( LENGTH_BIT_PDF1 - ulBitNum );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

WORD CBeaconPDF1::getCountryCode(  ) const
{
	WORD wCountryCode = 0;

	for( INT i = 0; i < LENGTH_BIT_COUNTRYCODE; i++ )
	{
		wCountryCode <<= 1;
		if( m_bsPDF1.test( LENGTH_BIT_PDF1 - i - 3 ) )
			wCountryCode++;
	}

	return wCountryCode;
}

BOOL CBeaconPDF1::getFormatFlag(  ) const
{
    return m_bsPDF1.test( LENGTH_BIT_PDF1 - 1 ) ? TRUE : FALSE;
}

BOOL CBeaconPDF1::getProtocolFlag(  ) const
{
    return m_bsPDF1.test( LENGTH_BIT_PDF1 - 2 ) ? TRUE : FALSE;
}

BYTE CBeaconPDF1::getProtocolCode(  ) const
{
	ULONG ulNumBits = m_bsPDF1.test( LENGTH_BIT_PDF1 - 2 ) ? 3 : 4;
	BYTE byProtocolCode = 0;

	for( INT i = 0; i < ulNumBits; i++ )
	{
		byProtocolCode <<= 1;
		if( m_bsPDF1.test(LENGTH_BIT_PDF1 - i - 13) )
			byProtocolCode++;
	}

	return byProtocolCode;
}

CBeaconID2 CBeaconPDF1::getBeaconID( INT64 i64BeaconMask ) const
{
	INT64 i64BeaconID = 0;

	for( INT i = 0; i < LENGTH_BIT_BEACONID; i++ )
	{
			i64BeaconID <<= 1;
			if( m_bsPDF1.test( LENGTH_BIT_PDF1 - i - 2 ) )
				i64BeaconID++;
	}

	return CBeaconID2( i64BeaconID & i64BeaconMask );
}

CBeaconID2 CBeaconPDF1::getBeaconID( const CBeaconID2 &rBeaconMask ) const
{
    return getBeaconID( (INT64)rBeaconMask );
}

BOOL CBeaconPDF1::getBit( ULONG ulBitNum ) const
{
    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_PDF1) )
    {
        return m_bsPDF1[LENGTH_BIT_PDF1 - ulBitNum];
    }
    else
    {
        return FALSE;
    }
}

INT CBeaconPDF1::CheckError(  )
{
    BYTE byTempBcnMsg[LENGTH_BYTE_BEACONMSG];

    getBitSequence( &byTempBcnMsg[3] );

    return CBCHCoder::CheckPDF1( byTempBcnMsg );
}

INT CBeaconPDF1::CorrectError( )
{
//    if( bCorrect )
    {
        BYTE byTempBcnMsg[LENGTH_BYTE_BEACONMSG];
        INT iNumError;

        getBitSequence( &byTempBcnMsg[3] );

        iNumError = CBCHCoder::CorrectPDF1( byTempBcnMsg );

        setBitSequence( &byTempBcnMsg[3] );

        return iNumError;
    }
//    else
//        return 0;
}

void CBeaconPDF1::EncodeECC(  )
{
}

INT CBeaconPDF1::Compare( const CBeaconPDF1 &rPDF1 ) const
{
    PDF1bs tempBs = m_bsPDF1 ^ rPDF1.m_bsPDF1;
    INT iBitsDiff = tempBs.count( );

    if( 0 < iBitsDiff )
    {
        CBeaconID2 PDF1a = getBeaconID( );
        CBeaconID2 PDF1b = rPDF1.getBeaconID( );
        if( (INT64)PDF1a < (INT64)PDF1b )
            iBitsDiff = -iBitsDiff;
    }

    return iBitsDiff;
}

CBeaconPDF2::CBeaconPDF2(  )
{
    Clear(  );
}

CBeaconPDF2::CBeaconPDF2( const CBeaconPDF2 &rPDF2 )
{
    *this = rPDF2;
}

CBeaconPDF2::CBeaconPDF2( const BYTE bsPDF2[],
                          ULONG ulSrcOffset,
                          ULONG ulDstOffset,
                          ULONG ulLengthBits )
{
    setBitSequence( bsPDF2,
                    ulSrcOffset,
                    ulDstOffset,
                    ulLengthBits );
}

CBeaconPDF2&  CBeaconPDF2::operator= ( const CBeaconPDF2 &rPDF2 )
{
    if( this != &rPDF2 )
    {
        m_bsPDF2 = rPDF2.m_bsPDF2;
    }

    return *this;
}

void CBeaconPDF2::setBitSequence( const BYTE bsPDF2[],
                                  ULONG ulSrcOffset,
                                  ULONG ulDstOffset,
                                  ULONG ulLengthBits,
                                  BOOL bClear )
{
    PDF2bs bsPF2;
    PDF2bs bsMask;
    ULONG ulSrcByte = ulSrcOffset / 8;
    ULONG ulSrcByteOffset = ulSrcOffset % 8;
    ULONG ulDstByte = ulDstOffset / 8;
    ULONG ulDstByteOffset = ulDstOffset % 8;

    // make sure length is not too long
    if( ulDstOffset + ulLengthBits > LENGTH_BIT_PDF2 )
    {
        ulLengthBits = LENGTH_BIT_PDF2 - ulDstOffset;
    }

    // Zero out the bits in PDF2
    if( bClear )
    {
        Clear(  );
    }

    bsPF2.reset();
    bsMask.reset();

    // mask, shift and copy lead-in bit(s) which are not alligned on byte boundary
    if( ulSrcByteOffset > 0 )
    {
        BYTE byTemp = 0;
        ULONG ulNumSBits = 8 - ulSrcByteOffset; // number of bits from first source byte to copy

        for( ULONG i = 0; i < ulNumSBits; i++ )
        {
            byTemp <<= 1;
            byTemp |= 0x1;
        }

        bsMask |= PDF2bs( byTemp ) << LENGTH_BIT_PDF2 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);
        bsPF2 |= PDF2bs( bsPDF2[ulSrcByte] & byTemp ) << LENGTH_BIT_PDF2 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);

        ulLengthBits -= ulNumSBits;
        ulSrcByte++;
        ulDstByte++;
    }

    // copy in one byte blocks
    while( ulLengthBits >= 8 )
    {
        bsMask |= PDF2bs( (BYTE)0xff ) << LENGTH_BIT_PDF2 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);
        bsPF2 |= PDF2bs( bsPDF2[ulSrcByte] ) << LENGTH_BIT_PDF2 - (((ulDstByte + 1) << 3) + ulDstByteOffset - ulSrcByteOffset);
        ulSrcByte++;
        ulDstByte++;
        ulLengthBits -= 8;
    }

    // mask, shift and copy lead-out bits
    if( ulLengthBits > 0 )
    {
        BYTE byTemp = 0;

        for( ULONG j = 0; j < ulLengthBits; j++ )
        {
            byTemp >>= 1;
            byTemp |= 0x80;
        }

        bsMask |= PDF2bs( byTemp ) >> (8 - ulLengthBits);
        bsPF2 |= PDF2bs( bsPDF2[ulSrcByte] & byTemp ) >> (8 - ulLengthBits);
    }

    bsMask.flip();

    m_bsPDF2 &= bsMask;
    m_bsPDF2 |= bsPF2;
}

void CBeaconPDF2::getBitSequence( BYTE bsPDF2[],
                                  ULONG ulDstOffset,
                                  ULONG ulSrcOffset,
                                  ULONG ulLengthBits ) const
{
    ULONG ulDstByte = ulDstOffset / 8;
    ULONG ulDstByteOffset = ulDstOffset % 8;
    BYTE byMask = 0x80 >> ulDstByteOffset;

    // make sure ulLengthBits is no too long
    if( LENGTH_BIT_PDF1 < (ulSrcOffset + ulLengthBits) )
    {
        ulLengthBits = LENGTH_BIT_PDF2 - ulSrcOffset;
    }

    for( INT i = 1; i <= ulLengthBits; i++ )
    {
        if( true == m_bsPDF2.test( LENGTH_BIT_PDF2 - ulSrcOffset - i ) )
        {
            bsPDF2[ulDstByte] |= byMask;
        }
        else
        {
            bsPDF2[ulDstByte] &= ~byMask;
        }

        byMask >>= 1;
        if( 0 == byMask )
        {
            byMask = 0x80;
            ulDstByte++;
        }
    }
}

void CBeaconPDF2::Clear()
{
    m_bsPDF2.reset(  );
}

BOOL CBeaconPDF2::setBit( ULONG ulBitNum )
{
    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_PDF2) )
    {
        m_bsPDF2.set( LENGTH_BIT_PDF2 - ulBitNum );
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL CBeaconPDF2::getBit( ULONG ulBitNum ) const
{
    if( (ulBitNum != 0) && (ulBitNum <= LENGTH_BIT_PDF2) )
    {
        return m_bsPDF2[LENGTH_BIT_PDF2 - ulBitNum];
    }
    else
    {
        return FALSE;
    }
}

INT CBeaconPDF2::CheckError(  )
{
    BYTE byTempBcnMsg[LENGTH_BYTE_BEACONMSG];

    getBitSequence( &byTempBcnMsg[13] );

    return CBCHCoder::CheckPDF2( byTempBcnMsg );
}

INT CBeaconPDF2::CorrectError( )
{
 //   if( bCorrect )
    {
        BYTE byTempBcnMsg[LENGTH_BYTE_BEACONMSG];
        INT iNumError;

        getBitSequence( &byTempBcnMsg[13] );

        iNumError = CBCHCoder::CorrectPDF2( byTempBcnMsg );

        setBitSequence( &byTempBcnMsg[13] );

        return iNumError;
    }
//    else
//       return 0;
}

void CBeaconPDF2::EncodeECC(  )
{
}

INT CBeaconPDF2::Compare( const CBeaconPDF2 &rPDF2 ) const
{
    PDF2bs tempBs = m_bsPDF2 ^ rPDF2.m_bsPDF2;
    INT iBitsDiff = tempBs.count( );

    if( 0 < iBitsDiff )
    {
	    INT64 i64PDF2a = 0;
	    INT64 i64PDF2b = 0;

        for( INT i = 0; i < LENGTH_BIT_PDF2; i++ )
	    {
			    i64PDF2a <<= 1;
			    if( m_bsPDF2.test( LENGTH_BIT_PDF2 - i - 1 ) )
				    i64PDF2a++;
			    i64PDF2b <<= 1;
			    if( rPDF2.m_bsPDF2.test( LENGTH_BIT_PDF2 - i - 1 ) )
				    i64PDF2b++;
	    }

        if( i64PDF2a < i64PDF2b )
        {
            iBitsDiff = -iBitsDiff;
        }
    }

    return iBitsDiff;
}