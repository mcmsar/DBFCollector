#ifndef EMSBEACONDF_H
#define EMSBEACONDF_H

#include <bitset>
#include "EMSTYPES.h"
#include "EMSBEACONID.h"
#include "EMSBEACONDFNS.h"

typedef std::bitset<EMSBeaconDefs::LENGTH_BIT_PDF1>   PDF1bs;

class CBeaconPDF1
{
public:
	enum Format
	{
		FORMAT_SHORT = 0,
		FORMAT_LONG
	};

	enum Protocol
	{
		FORMAT_STANDARD = 0,
		FORMAT_USER = 1,
		FORMAT_NATIONAL = 1
	};

	CBeaconPDF1(  );
    CBeaconPDF1( const CBeaconPDF1 &rPDF1 );
    CBeaconPDF1( const CBeaconID2 &rBeaconID );
    CBeaconPDF1( INT64 i64BeaconID );                       // LSB justified
	CBeaconPDF1( const BYTE bsPDF1[],
                 ULONG ulSrcOffset = 0,
                 ULONG ulDstOffset = 0,
                 ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF1);

	void	setBitSequence( const BYTE bsPDF1[],
                            ULONG ulSrcOffset = 0,
                            ULONG ulDstOffset = 0,
                            ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF1,
                            BOOL bclear = TRUE );
	void	getBitSequence( BYTE bsPDF1[],
                            ULONG ulDstOffset = 0,
                            ULONG ulSrcOffset = 0,
                            ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF1 ) const;
	void	Clear();

	// generic set statments for PDF1
	BOOL    setCountryCode( WORD wCountryCode );	// 10-bit country code
	void    setFormatFlag( Format format );
	void    setProtocolFlag( Protocol protocol );
	BOOL    setProtocolCode( BYTE byProtocol );
	void    setBeaconID( const CBeaconID2 &rBeacon );
    BOOL    setBit( ULONG ulBitNum );               // one based bit index

	// generic get statments for PDF1
	WORD        getCountryCode(  ) const;
	BOOL        getFormatFlag(  ) const;
	BOOL        getProtocolFlag(  ) const;
	BYTE        getProtocolCode(  ) const;
	CBeaconID2  getBeaconID( INT64 i64BeaconMask = 0xFFFFFFFFFFFFFFFF ) const;  //LSB justitfied
    CBeaconID2  getBeaconID( const CBeaconID2 &rBeaconMask ) const;
    BOOL        getBit( ULONG ulBitNum ) const;     // one based bit index

    INT         Compare( const CBeaconPDF1 &rPDF1 ) const;

	INT		CheckError(  );
//	INT		CorrectError( BOOL bCorrect = FALSE );
	INT		CorrectError( );
	void	EncodeECC(  );

    CBeaconPDF1& operator= ( const CBeaconPDF1 &rPDF1 );
    CBeaconPDF1& operator= ( const CBeaconID2 &rBeaconID );
    CBeaconPDF1& operator= ( const INT64 i64PDF1 );         // LSB justified

private:
	PDF1bs  m_bsPDF1;

};

typedef std::bitset<EMSBeaconDefs::LENGTH_BIT_PDF2>   PDF2bs;

class CBeaconPDF2
{
public:
	CBeaconPDF2(  );
    CBeaconPDF2( const CBeaconPDF2 &rPDF2 );
	CBeaconPDF2( const BYTE bsPDF2[],
                 ULONG ulSrcOffset = 2,
                 ULONG ulDstOffset = 0,
                 ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF2);

	void	setBitSequence( const BYTE bsPDF2[],
                            ULONG ulSrcOffset = 2,
                            ULONG ulDstOffset = 0,
                            ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF2,
                            BOOL bClear = TRUE );
	void	getBitSequence( BYTE bsPDF2[],
                            ULONG ulDstOffset = 2,
                            ULONG ulSrcOffset = 0,
                            ULONG ulLengthBits = EMSBeaconDefs::LENGTH_BIT_PDF2 ) const;
	void	Clear();

    BOOL    setBit( ULONG ulBitNum );
    BOOL    getBit( ULONG ulBitNum ) const;

    INT     Compare( const CBeaconPDF2 &rPDF2 ) const;

	INT		CheckError(  );
//	INT		CorrectError( BOOL bCorrect = FALSE );
	INT		CorrectError( );
	void	EncodeECC(  );

    CBeaconPDF2& operator= ( const CBeaconPDF2 &rPDF2 );

private:
	PDF2bs  m_bsPDF2;

};

#endif
