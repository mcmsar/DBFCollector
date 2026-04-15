#ifndef EMSBEACONMSGBASE_H
#define EMSBEACONMSGBASE_H

#include <string>
using std::string;

#include "EMSTYPES.h"
#include "EMSBEACONID.h"
#include "EMSBEACONDF.h"
#include "EMSBEACONDFNS.h"

class CBeaconMsgBase
{
public:
	enum Preamble
	{
        PREAMBLE_NULL = 0,
		PREAMBLE_NORMAL_FS = 0xFFFE2F,
		PREAMBLE_INVERTED_FS = 0xFFFED0
	};

	enum UserCodes
	{
		USER_ORBITOGRAPHY = 0,
		USER_AVIATION,
		USER_MARINE,
		USER_SER,
		USER_NAT,
		USER_SPARE,
		USER_RCS,
		USER_TEST
	};

	enum NatStandCodes
	{
		BP_RESERVED1 = 0,
		BP_RESERVED2,
		BP_STD_EPIRB_MMSI,
		BP_STD_ELT_AC24,
		BP_STD_ELT_SER,
		BP_STD_ELT_ACOD,
		BP_STD_EPIRB_SER,
		BP_STD_PLB_SER,
		BP_NAT_ELT,
		//BP_NAT_SPARE,
		BP_ELT_DT,
		BP_NAT_EPIRB,
		BP_NAT_PLB,
		BP_SSAS,				
//		BP_SPARE1,		- replaced by BP_SSAS
		//BP_SPARE2,
		BP_NAT_RLS,
		BP_STD_TST,
		BP_NAT_TST
	};


    CBeaconMsgBase(  );
    CBeaconMsgBase( const CBeaconMsgBase &rBeaconMsg );
// The following constructor is deprecated and will be removed in a future software release.
// Instead use CBeaconMsgBase() followed by a call to Set( Msg[] ...)
	CBeaconMsgBase( const BYTE Msg[],
                ULONG ulSrcOffset = 0,                      // bit to start copying from Msg
                ULONG ulDestOffset = 0,                     // bit to start copying Msg into
                ULONG ulLength = EMSBeaconDefs::LENGTH_BIT_BEACONMSG );
// end deprecated
    CBeaconMsgBase( const CBeaconID2 &rBeaconID );

    virtual ~CBeaconMsgBase(  );

    void    Set( const CBeaconMsgBase &rBeaconMsg );
    void    Set( const BYTE Msg[],
	             ULONG ulSrcOffset = 0,                     // bit to start copying from Msg
	             ULONG ulDestOffset = 0,                    // bit to start copying Msg into
	             ULONG ulLength = EMSBeaconDefs::LENGTH_BIT_BEACONMSG,
	             BOOL bClear = TRUE );
    void    Set( const CBeaconID2 &rBeaconID );
    void    Set( const float Msg[],                         // power array for 144 bits
                 ULONG ulSrcOffset = 0,                     // bit to start copying from Msg
                 ULONG ulDestOffset = 0,                    // bit to start copying Msg into
                 ULONG ulLength = EMSBeaconDefs::LENGTH_BIT_BEACONMSG,
                 BOOL bClear = TRUE );

    void toHexString( TCHAR szBeaconMsg[],
                      ULONG ulStartBit = 0,
                      ULONG ulLengthNibbles = EMSBeaconDefs::LENGTH_NIBBLE_BEACONMSG ) const;

	// Set fields
    void    SetPreamble( Preamble preamble = PREAMBLE_NORMAL_FS );
    void    SetPDF1( const CBeaconPDF1 &rBeaconPDF1 );
    void    SetPDF2( const CBeaconPDF2 &rBeaconPDF2 );
    BOOL    SetBit( ULONG ulBitNum );
    void    SetDefaultValues( );   // for beacons with encoded locations, replace encoded locations with default values
    void    SetDefaultValuesPDF1( bool bSetDefaultLocation = false );
	void	SetMultiInvalidValues( void );
    void    SetMultiInvalidValuesPDF2( void );
    void    SetDefaultValuesPDF2( bool bSetDefaultLocation = false );
    void    SetUnconfirmedValues( void );   // set defaults for UNCONFIRMED messages

	// clear beacon message
	void Clear(  );

	// check encoded fields
            INT     CheckFSError( Preamble &rPreamble );
			INT		CheckFSError( void );
			BOOL	PreambleEncoded(  );
			BOOL	PDF1Encoded(  );
			BOOL	PDF2Encoded(  );
	virtual	BOOL	LongLatEncoded(  ) const;

	// Get fields
            void            Get( BYTE Msg[],
                                 ULONG ulDstOffset = 0,
                                 ULONG ulSrcOffset = 0,
                                 ULONG ulBitLength = EMSBeaconDefs::LENGTH_BIT_BEACONMSG ) const;
	    	Preamble		getPreamble(  ) const;
			CBeaconPDF1&	getPDF1(  );
			CBeaconPDF2&	getPDF2(  );
			BOOL			getFormatFlag(  ) const;
			BOOL			getProtocolFlag(  ) const;
			ULONG			getProtocolCode(  ) const;
			ULONG			getCountryCode(  ) const;
	virtual	CBeaconID2		getBeaconID();
            BOOL            getBit( ULONG ulBitNum ) const;
            ULONG           getPDF1BitErrors(  ) const { return m_byPDF1BitErrors; };
            ULONG           getPDF2BitErrors(  ) const { return m_byPDF2BitErrors; };

	virtual	BOOL	IsUser(  ) const;
	virtual	BOOL	IsNational( BYTE* nSet = nullptr ) const;
	virtual	BOOL	IsStandard(  ) const;
	virtual	BOOL	IsTestBeacon(  ) const;
	virtual BOOL	IsOrbitography(  ) const;

	// assignment operators
	CBeaconMsgBase &operator= ( const CBeaconMsgBase &rBeaconMsg );
    CBeaconMsgBase &operator= ( const CBeaconID2 &rBeaconID );
    CBeaconMsgBase &operator= ( INT64 i64BeaconID );

protected:
    CBeaconPDF1	m_PDF1;
    CBeaconPDF2	m_PDF2;

	const char*	_GetBeaconMsgString() { _SetBeaconMsgString(); return m_strBeaconMsg.c_str(); }
	void _SetBeaconMsgString();

private:
    Preamble	m_Preamble;
    BYTE        m_byPDF1BitErrors;
    BYTE        m_byPDF2BitErrors;

    ULONG   CountBits( DWORD dword ) const;
    BOOL    PDF2Correctable() const;
    void    CorrectBitErrors();

	std::string	m_strBeaconMsg;
};

#endif
