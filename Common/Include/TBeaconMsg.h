//---------------------------------------------------------------------------
#ifndef TBeaconMsgH
#define TBeaconMsgH
//---------------------------------------------------------------------------
#include "TBeaconID.h"
#include "TCountryCdData.h"

//
//typedef struct
//{
//    unsigned short  CCNum;           // Country Code Number
//    AnsiString      CCText;          // Country Name
//    AnsiString      CCFullText;      // Country Description
//} TCountryCdData;



//The values of these enumerated types correspond identically to their
//bit patterns in the 406 MHz Beacon Specifications.  Do not change their
//order!!
enum TBFormat
{
    BF_SHORT = 0, BF_LONG
};

enum TBProtocolFlag
{
    //Note that the Protocol Flag is only one bit:
    //0 for STD or NAT, 1 for USER
    BT_STANDARD = 0, BT_USER, BT_NATIONAL
};

enum TBUserCodes
{
    BP_USR_ORB = 0, BP_USR_AVI, BP_USR_MAR, BP_USR_SER, BP_USR_NAT,
    BP_USR_SPARE, BP_USR_RCS, BP_USR_TST
};

enum TBUserSerialCodes
{
    SER_ELT = 0, SER_ACOD, SER_EPIRB_FF, SER_AC24, SER_EPIRB_NFF,
    SER_SPARE1, SER_PLB, SER_SPARE2
};

enum TBStdNatCodes
{
    BP_RESERVED1 = 0, BP_RESERVED2, BP_STD_EPIRB_MMSI, BP_STD_ELT_AC24,
    BP_STD_ELT_SER, BP_STD_ELT_ACOD, BP_STD_EPIRB_SER, BP_STD_PLB_SER,
    BP_NAT_ELT, BP_NAT_SPARE, BP_NAT_EPIRB, BP_NAT_PLB, BP_SPARE1,
    BP_SPARE2, BP_STD_TST, BP_NAT_TST
};

enum TBLocationFlag
{
    LOC_NULL, LOC_USER, LOC_STANDARD, LOC_NATIONAL
};

enum TBAuxiliaryFlag
{
    AUX_NONE, AUX_121, AUX_SART, AUX_OTHER
};

class _export TBeaconMsg
{
public:
    unsigned char   Message[18];

                    TBeaconMsg( void );
    bool            Bit( const int Pos );
    int             Bits( const int Start, const int End );
    int             NibbleAlignedBits( const int Start, const int End );
    AnsiString      MBaudot( const int Start, const int End, const int CharSize = 6 );
    TBeaconID       BeaconID( void );
    void            Fill( float *f144 );
    AnsiString      Hex30( void );
    AnsiString      Hex36( void );
    TBeaconMsg      PDF1( void );
    TBeaconMsg      PDF2( void );
    void            ZeroFillExtended( void );
    void            OneFillExtended( void );
    int             ECCcheck ( int field_id, bool modify, BYTE* Message );
    TBeaconMsg&     operator&=( const TBeaconMsg& Msg );
    TBeaconMsg      operator&( const TBeaconMsg& Msg );
    TBeaconMsg&     operator|=( const TBeaconMsg& Msg );
    TBeaconMsg      operator|( const TBeaconMsg& Msg );
    bool            operator==( const TBeaconMsg& Msg );
};

class _export TDecodedMsg
{
public:
    TBeaconID       BeaconID;
    TBFormat        Format;
    TBProtocolFlag  ProtocolFlag;
    unsigned long   ProtocolCode;
    TBLocationFlag  LocationFlag;
    TBAuxiliaryFlag AuxiliaryFlag;
    TCountryCdData  *CCTable;
    AnsiString      CCTextShort;
    AnsiString      CCTextLong;
    AnsiString      ProtocolText;
    AnsiString      BeaconText;
    AnsiString      AuxiliaryText;
    float           LatitudeFine;
    float           LatitudeCoarse;
    float           LongitudeFine;
    float           LongitudeCoarse;
    int             CountryCode;
    int             AuxiliaryDevice;
    int             BeaconNumber;
    int             BeaconType;
    int             CSCertificateNumber;
    int             EmergencyCode;
    bool            CSTypeApproval;
    bool            AutoActivation;
    bool            EmergencyCodeFlag;
    bool            CCValid;
    bool            LocationFineValid;
    bool            LocationCoarseValid;
    bool            LocationInternal;

                    TDecodedMsg( TCountryCdData *CC = 0 );
    void            Decode( TBeaconMsg& BeaconMsg );

    static AnsiString IntToPaddedStr( int number, int width );
};

#endif
