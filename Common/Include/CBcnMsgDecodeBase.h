#ifndef __CBCNMSGDECODEBASE_H_
#define __CBCNMSGDECODEBASE_H_

#include <assert.h>
#include "CBeaconMessage.h"
#include "CBeaconID.h"


enum TBFormat
{
    BF_SHORT = 0, BF_LONG
};

enum TBProtocolFlag
{
    //Note that the Protocol Flag is only one bit:
    //0 for STD or NAT, 1 for USER
    BT_STANDARD = 0, BT_USER, BT_NATIONAL, BT_RLS, BT_ELTDT
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
    LOC_NULL, LOC_USER, LOC_STANDARD, LOC_NATIONAL, LOC_RLS, LOC_ELTDT
};

enum TBAuxiliaryFlag
{
    AUX_NONE, AUX_121, AUX_SART, AUX_OTHER
};

//snl
enum RLSBeaconType
{
	RLS_ELT, RLS_EPIRB,RLS_PLB,RLS_TEST
};

class CBcnMsgDecodeBase
{
public:
	CBcnMsgDecodeBase() { Initialize(); }
	CBcnMsgDecodeBase( const CBcnMsgDecodeBase& x ) { assert(false); } // Copy constructor not supported
	virtual ~CBcnMsgDecodeBase() {}

    void            Initialize ( void );

	//! Same as Decode, but decodes without producing text member data.
	void			DecodeEx( CBeaconMessage& cbcnmsg );

	void			GetEncodedLocation( bool& bHasEncodedLocation, double& dLat, double& dLong );
	void			GetEncodedLocation( bool& bHasEncodedLocation, double& dLat, double& dLong, double& dAccuracy );

	bool IsFineValid() const { return LocationFineValid; }
	bool IsCoarseValid() const { return LocationCoarseValid; }

	double GetLatitudeFine() const { return LatitudeFine; }
	double GetLongitudeFine() const { return LongitudeFine; }
	double GetLatitudeCoarse() const { return LatitudeCoarse; }
	double GetLongitudeCoarse() const { return LongitudeCoarse; }

	static bool ValidFixedBits( CBeaconMessage& cbcnmsg );

protected:
	virtual void	_DecodeLocation( CBeaconMessage& cbcnmsg ); 
	const bool		_HaveData() { return m_bHaveData; }

	bool	m_bHasEncodedLocation;
	double	m_dEncodedLat;
	double	m_dEncodedLong;
	double	m_dEncodedAccuracy;

private:

	__int64       BeaconID;

	CBeaconID       cbcnid;

    TBFormat        Format;
    TBProtocolFlag  ProtocolFlag;
    unsigned long   ProtocolCode;
    TBLocationFlag  LocationFlag;
    TBAuxiliaryFlag AuxiliaryFlag;

    double          LatitudeFine;
    double          LatitudeCoarse;
    double          LongitudeFine;
    double          LongitudeCoarse;
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

	bool			m_bHaveData;

	//snl
	short			m_RLSTACNum;		
	BYTE			m_ELTDTMeansOfActivation;
	BYTE			m_ELTDTEncodedAltitude;
	BYTE			m_ELTDTEncodedLocationFreshness;
/*
	// The following members and methods had no users ... so have commented them out.

	void            Decode ( CBeaconMessage& cbcnmsg );

    char      CCTextShort[128];
    char      CCTextLong[256];
    char      ProtocolText[128];
    char      BeaconText[4096];
    char      AuxiliaryText[256];
	char* IntToPaddedStr( int number, int width );

	// The cbcnmsg member and the parameter to DecodeEx have the same name...
	// the former is never populated so have removed it and it's accessor
	const char*		_BeaconMessage() { return cbcnmsg.Hex36(); } 
	CBeaconMessage  cbcnmsg;

*/

};

#endif
