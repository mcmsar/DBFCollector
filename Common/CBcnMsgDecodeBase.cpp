#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "CBcnMsgDecodeBase.h"
#include "CBeaconID.h"
//#include "sarr_data_types.h"

#include "debugwin.h"
static CDebugWin debugWin;
static char szDebug[256];


void CBcnMsgDecodeBase::Initialize ( void )
{
    *(cbcnid.High())  = 0;
    *(cbcnid.Low())   = 0;

	BeaconID			= 0;

    Format              = BF_SHORT;
    ProtocolFlag        = BT_STANDARD;
    ProtocolCode        = BP_SPARE1;
    LocationFlag        = LOC_NULL;
    AuxiliaryFlag       = AUX_NONE;

	LatitudeFine        = 0.0;
    LatitudeCoarse      = 0.0;
    LongitudeFine       = 0.0;
    LongitudeCoarse     = 0.0;
    CountryCode         = 0;
    AuxiliaryDevice     = 0;
    BeaconNumber        = 0;
    BeaconType          = 0;
    CSCertificateNumber = 0;
    EmergencyCode       = 0;
    CSTypeApproval      = false;
    AutoActivation      = false;
    EmergencyCodeFlag   = false;
    LocationFineValid   = false;
    LocationCoarseValid = false;
    LocationInternal    = false;

	m_bHasEncodedLocation	= false;
	m_dEncodedLat			= 0.0;
	m_dEncodedLong			= 0.0;
	m_dEncodedAccuracy		= 0.0;

	m_bHaveData				= false;
	m_RLSTACNum				= 0;
}


void CBcnMsgDecodeBase::DecodeEx( CBeaconMessage& cbcnmsg )
{
	m_bHaveData = true;

	// Assume that a completely zero beacon message is invalid and cannot be decoded
	// We use these messages when the beacon is a non-406
	if ( cbcnmsg.IsEmptyBcnMessage() ) return;

    // Default settings
    *(cbcnid.High())  = cbcnmsg.Bits( 26, 53 );
    *(cbcnid.Low())   = cbcnmsg.Bits( 54, 85 );

    CSTypeApproval      = false;
    AutoActivation      = true;    // always true unless otherwise specified
    EmergencyCodeFlag   = false;
    LocationFineValid   = false;
    LocationCoarseValid = false;
    LocationInternal    = false;
    CSCertificateNumber = 0;
    AuxiliaryDevice     = 0;
    BeaconNumber        = 0;
    BeaconType          = 0;
    EmergencyCode       = 0;
    LatitudeFine        = 99.999;
    LongitudeFine       = 999.999;
    LatitudeCoarse      = 99.999;
    LongitudeCoarse     = 999.999;
    CountryCode         = 999;
    Format              = BF_SHORT;
    ProtocolFlag        = BT_USER;
    ProtocolCode        = BP_USR_SPARE;
    LocationFlag        = LOC_NULL;
    AuxiliaryFlag       = AUX_NONE;

    //--------------------------------------------------------------------------
    // Message Length (long or short)
    // Bit 25: 0 = short, 1 = long
    if( cbcnmsg.Bit( 25 ) )
        Format = BF_LONG;

    //--------------------------------------------------------------------------
    // Country Codes
    // Bits 27-36: Country Code
    CountryCode = cbcnmsg.Bits( 27, 36 );

	debugWin.OutputMsg ( "CBcnMsgDecodeBase::Decode step1" );

	//--------------------------------------------------------------------------
    // Protocol Types
    // Bit 26 = 1 : User
    // Bits 26 = 0, 37 = 0 : Standard
    // Bits 26 = 0, 37 = 1 : National  or Standard Test
    //--------------------------------------------------------------------------
    if( cbcnmsg.Bit( 26 ) )
    {
        ProtocolFlag = BT_USER;
    }
    else if( cbcnmsg.Bit( 37 ) )
    {
        ProtocolFlag = BT_NATIONAL;
        if( cbcnmsg.Bits( 37, 40 ) == 0x0E)
           ProtocolFlag = BT_STANDARD;
		//snl
        else if( cbcnmsg.Bits( 37, 40 ) == 0x0D)
           ProtocolFlag = BT_RLS;
		else if ( cbcnmsg.Bits( 37, 40 ) == 0x09)
			ProtocolFlag = BT_ELTDT;

    }
    else
    {
        ProtocolFlag = BT_STANDARD;
    }

	debugWin.OutputMsg ( "CBcnMsgDecodeBase::Decode step3" );

    //----------------------------------------------------------------------
    // Protocol Type Processing
    switch ( ProtocolFlag )
    {
        // User Protocols
        case BT_USER :

            AuxiliaryDevice = cbcnmsg.Bits( 84, 85 );

            // Emergency Code Field (short message user protocol only)
            if( Format == BF_SHORT )
            {
                // Bits 107-112: Non-Protected Data Field
                if( cbcnmsg.Bit( 107 ) )
                    EmergencyCodeFlag = true;
                if( !cbcnmsg.Bit( 108 ) )
                    AutoActivation = false;
                EmergencyCode = cbcnmsg.Bits( 109, 112 );
            }
            else
            {
                // Position Data (if available)
                LocationFlag  = LOC_USER;
                AuxiliaryFlag = (TBAuxiliaryFlag)cbcnmsg.Bits(84,85);
            }

            // Bits 37-39: User Protocols
            ProtocolCode = cbcnmsg.Bits( 37, 39 );
            switch( ProtocolCode )
            {
                case BP_USR_MAR:  // Maritime User Protocol
                    break;
                case BP_USR_RCS:  // Radio Call Sign User Protocol
                    break;
                case BP_USR_AVI:  // Aviation User Protocol
					break;
                case BP_USR_SER:  // Serial User Protocols
                    CSTypeApproval = cbcnmsg.Bit(43);
                    if ( CSTypeApproval )
                        CSCertificateNumber = cbcnmsg.Bits( 74, 83 );
                    BeaconType = cbcnmsg.Bits( 40, 42 );
                    switch( BeaconType )
                    {
                        case SER_ELT:  // ELTs with serial identification number
                            BeaconNumber = cbcnmsg.Bits(44,63);
							break;
                        case SER_EPIRB_FF:  // float free EPIRBs with serial identification number
                            BeaconNumber = cbcnmsg.Bits(44,63);
                            break;
                        case SER_EPIRB_NFF:  // non float free EPIRBs with serial identification number
                            BeaconNumber = cbcnmsg.Bits(44,63);
                            break;
                        case SER_PLB:  // PLBs with serial identification number
                            BeaconNumber = cbcnmsg.Bits(44,63);
                            break;
                        case SER_ACOD:  // ELTs with aircraft operator designator & serial number
                            BeaconNumber = cbcnmsg.Bits(62,73);
                            break;
                        case SER_AC24:  // ELTs with aircraft 24-bit address
                            BeaconNumber = cbcnmsg.Bits(44,67);
                            break;

                        // spares
                        default :
                            break;
                    }
                    break;
                case BP_USR_TST:  // Test User Protocol
                    break;
                case BP_USR_ORB:  // Orbitography Protocol
                    LocationCoarseValid = false;

                    // Special test for French TCAL beacon
                    //if( CountryCode == 227 ) //Ticket #48086: all ORB bcns don't have encoded locations.
                    {
                        LocationFlag  = LOC_NULL;
                    }
                    break;
                case BP_USR_NAT:  // National User Protocol
					{
						LocationCoarseValid = false;
						LocationFlag  = LOC_NULL; //Ticket #48086: ABL provides encoded for a msg that C/S does not recognize as encoded 
					}
                    break;
                default:	// Spare
                    LocationCoarseValid = false;
            }
            break;

        //----------------------------------------------------------------------
        // Standard Location Protocol Beacons
        case BT_STANDARD:

            LocationFlag = LOC_STANDARD;
            if( cbcnmsg.Bit(111) )
                LocationInternal = true;
            if( cbcnmsg.Bit(112) )
                AuxiliaryFlag = AUX_121;

            // Bits 37-40: Check Specific Standard Protocols
            ProtocolCode = cbcnmsg.Bits( 37, 40 );
            switch( ProtocolCode )
            {
                case BP_STD_EPIRB_MMSI:
                    break;
                case BP_STD_ELT_AC24:
                    BeaconNumber = cbcnmsg.Bits(41,64);
                    break;
                case BP_STD_ELT_SER:
                    CSTypeApproval = true;
                    CSCertificateNumber = cbcnmsg.Bits( 41, 50 );
                    BeaconNumber = cbcnmsg.Bits(51,64);
                    break;
                case BP_STD_ELT_ACOD:
                    BeaconNumber = cbcnmsg.Bits(56,64);
                    break;
                case BP_STD_EPIRB_SER:
                    CSTypeApproval = true;
                    CSCertificateNumber = cbcnmsg.Bits( 41, 50 );
                    BeaconNumber = cbcnmsg.Bits(51,64);
                    break;
                case BP_STD_PLB_SER:
                    CSTypeApproval = true;
                    CSCertificateNumber = cbcnmsg.Bits( 41, 50 );
                    BeaconNumber = cbcnmsg.Bits(51,64);
                    break;
                case BP_STD_TST:
                    break;
                default :
                    break;
            }
            break;

        //----------------------------------------------------------------------
        // National Location Protocol Beacons
        case BT_NATIONAL:

            LocationFlag = LOC_NATIONAL;
            BeaconNumber = cbcnmsg.Bits(41,58);
            if( Format == BF_LONG )
			{
			}

            if( cbcnmsg.Bit(111) )
                LocationInternal = true;
            if( cbcnmsg.Bit(112) )
                AuxiliaryFlag = AUX_121;

            // Bits 37-40: Check Specific National Protocols
            ProtocolCode = cbcnmsg.Bits( 37, 40 );

            break;
		//snl
		case BT_RLS:
            LocationFlag = LOC_RLS;

			BeaconType = cbcnmsg.Bits( 41, 42 );
            ProtocolCode = cbcnmsg.Bits( 37, 40 );

            switch( BeaconType )
            {
                case 0:  // ELTs with serial identification number
				case 1:  //EPIRB
				case 2:	 //PLB
				case 3:  //Location Test
					m_RLSTACNum	= cbcnmsg.Bits( 43,52 );
                    BeaconNumber = cbcnmsg.Bits(53,66);
					break;
               

                // spares
                default :
                    break;
            }
			break;
		case BT_ELTDT:
            LocationFlag = LOC_ELTDT;
            ProtocolCode = cbcnmsg.Bits( 37, 40 );

			BeaconType = cbcnmsg.Bits( 41, 42 );
            switch( BeaconType )
            {
                case 0:  // Aircraft 24 bit address
				case 1:  //Aircraft operators designator
				case 2:	 //TAC with serial num
				case 3:  //ELTDT Location Test
                    BeaconNumber = cbcnmsg.Bits(43,66);
					break;
               

                // spares
                default :
                    break;
            }
			break;
        default :
            break;

    } // End of protocol processing

    //--------------------------------------------------------------------------
    // Location Data
    //--------------------------------------------------------------------------
	_DecodeLocation( cbcnmsg );
}


void
CBcnMsgDecodeBase::_DecodeLocation( CBeaconMessage& cbcnmsg )
{
    switch( LocationFlag )
    {
        case LOC_USER:

            // Bits 107-132: Position Data (if available)
            LocationCoarseValid = true;
            LatitudeCoarse  = cbcnmsg.Bits(109,115);
            LatitudeCoarse += cbcnmsg.Bits(116,119)/15.0;
            if( cbcnmsg.Bit(108) )
                LatitudeCoarse *= -1;
            LongitudeCoarse  = cbcnmsg.Bits(121,128);
            LongitudeCoarse += cbcnmsg.Bits(129,132)/15.0;
            if( cbcnmsg.Bit(120) )
                LongitudeCoarse *= -1;
            if( cbcnmsg.Bit(107) )
                LocationInternal = true;

            break;

        case LOC_STANDARD:

            // Set BeaconID to default bits 65 to 85
            (*(cbcnid.Low())) &= 0xFFE00000;
            (*(cbcnid.Low())) |= 0x000FFBFF;

            if( cbcnmsg.Bit(111) )
                LocationInternal = true;

            // Check for default values
            if( cbcnmsg.Bits(65,74) != 0x1FF &&
                cbcnmsg.Bits(75,85) != 0x3FF )
                LocationCoarseValid = true;

            // Coarse Location Data for Standard Protocol
            if( LocationCoarseValid )
            {
                LatitudeCoarse  = cbcnmsg.Bits(66,74)/4.0;
                if( cbcnmsg.Bit(65) )
                    LatitudeCoarse *= -1;
                LongitudeCoarse  = cbcnmsg.Bits(76,85)/4.0;
                if( cbcnmsg.Bit(75) )
                    LongitudeCoarse *= -1;
            }
            if( Format == BF_LONG )
            {
                // Check for default values
                if( cbcnmsg.Bits(113,122) != 0x20F &&
                    cbcnmsg.Bits(123,132) != 0x20F &&
                    cbcnmsg.Bits(113,132) != 0xFFFFF )
                    LocationFineValid = true;

                // Fine Location Data for Standard Protocol
                if( LocationFineValid )
                {
                    LatitudeFine  = (float)cbcnmsg.Bits(114,118)/60.0;
                    LatitudeFine += (float)cbcnmsg.Bits(119,122)/60.0/15.0;
                    if( !cbcnmsg.Bit(113) )
                        LatitudeFine *= -1;
                    LongitudeFine  = (float)cbcnmsg.Bits(124,128)/60.0;
                    LongitudeFine += (float)cbcnmsg.Bits(129,132)/60.0/15.0;
                    if( !cbcnmsg.Bit(123) )
                        LongitudeFine *= -1;
                }

                // Add to coarse location only if locations valid
                if( LocationCoarseValid && LocationFineValid )
                {
                    if ( LatitudeCoarse < 0.0 )
                        LatitudeFine = LatitudeCoarse - LatitudeFine;
                    else
                        LatitudeFine += LatitudeCoarse;
                    if ( LongitudeCoarse < 0.0 )
                        LongitudeFine = LongitudeCoarse - LongitudeFine;
                    else
                        LongitudeFine += LongitudeCoarse;
                }
            }
            break;

			//snl
		case LOC_RLS:
			// Set BeaconID to default bits 67 to 85
            (*(cbcnid.Low())) &= 0xFFF80000;
            (*(cbcnid.Low())) |= 0x0003FDFF;

			if( cbcnmsg.Bit(107) )
                LocationInternal = true;

            // Check for default values
            if( cbcnmsg.Bits(67,75) != 0xFF &&
                cbcnmsg.Bits(76,85) != 0x1FF )
                LocationCoarseValid = true;

			 // Coarse Location Data for Standard Protocol
            if( LocationCoarseValid )
            {
                LatitudeCoarse  = cbcnmsg.Bits(68,75)/2.0;
                if( cbcnmsg.Bit(67) )
                    LatitudeCoarse *= -1;
                LongitudeCoarse  = cbcnmsg.Bits(77,85)/2.0;
                if( cbcnmsg.Bit(76) )
                    LongitudeCoarse *= -1;
            }

			if( Format == BF_LONG )
            {
                // Check for default values
                if( cbcnmsg.Bits(115,123) != 0x10F &&
                    cbcnmsg.Bits(124,132) != 0x10F &&
                    cbcnmsg.Bits(115,132) != 0x3FFFF )
                    LocationFineValid = true;
				// Fine Location Data for RLS Protocol
                if( LocationFineValid )
                {
                    LatitudeFine  = (float)cbcnmsg.Bits(116,119)/60.0;
                    LatitudeFine += (float)cbcnmsg.Bits(120,123)/60.0/15.0;
                    if( !cbcnmsg.Bit(115) )
                        LatitudeFine *= -1;
                    LongitudeFine  = (float)cbcnmsg.Bits(125,128)/60.0;
                    LongitudeFine += (float)cbcnmsg.Bits(129,132)/60.0/15.0;
                    if( !cbcnmsg.Bit(124) )
                        LongitudeFine *= -1;
                }

				// Add to coarse location only if locations valid
                if( LocationCoarseValid && LocationFineValid )
                {
                    if ( LatitudeCoarse < 0.0 )
                        LatitudeFine = LatitudeCoarse - LatitudeFine;
                    else
                        LatitudeFine += LatitudeCoarse;
                    if ( LongitudeCoarse < 0.0 )
                        LongitudeFine = LongitudeCoarse - LongitudeFine;
                    else
                        LongitudeFine += LongitudeCoarse;
                }
			}
			break;

		case LOC_ELTDT:
			// Set BeaconID to default bits 67 to 85
            (*(cbcnid.Low())) &= 0xFFF80000;
            (*(cbcnid.Low())) |= 0x0003FDFF;

			//107,108 - means of activation
			m_ELTDTMeansOfActivation = cbcnmsg.Bits( 107,108 );
			//109-112 encoded altitude
			m_ELTDTEncodedAltitude = cbcnmsg.Bits( 109,112 );
			//113, 114 - Encoded location freshness
			m_ELTDTEncodedLocationFreshness = cbcnmsg.Bits( 113,114 );
            

            // Check for default values
            if( cbcnmsg.Bits(67,75) != 0xFF &&
                cbcnmsg.Bits(76,85) != 0x1FF )
                LocationCoarseValid = true;

			 // Coarse Location Data for Standard Protocol
            if( LocationCoarseValid )
            {
                LatitudeCoarse  = cbcnmsg.Bits(68,75)/2.0;
                if( cbcnmsg.Bit(67) )
                    LatitudeCoarse *= -1;
                LongitudeCoarse  = cbcnmsg.Bits(77,85)/2.0;
                if( cbcnmsg.Bit(76) )
                    LongitudeCoarse *= -1;
            }

			if( Format == BF_LONG )
            {
                // Check for default values
                if( cbcnmsg.Bits(115,123) != 0x10F &&
                    cbcnmsg.Bits(124,132) != 0x10F &&
                    cbcnmsg.Bits(115,132) != 0x3FFFF )
                    LocationFineValid = true;
				// Fine Location Data for RLS Protocol
                if( LocationFineValid )
                {
                    LatitudeFine  = (float)cbcnmsg.Bits(116,119)/60.0;
                    LatitudeFine += (float)cbcnmsg.Bits(120,123)/60.0/15.0;
                    if( !cbcnmsg.Bit(115) )
                        LatitudeFine *= -1;
                    LongitudeFine  = (float)cbcnmsg.Bits(125,128)/60.0;
                    LongitudeFine += (float)cbcnmsg.Bits(129,132)/60.0/15.0;
                    if( !cbcnmsg.Bit(124) )
                        LongitudeFine *= -1;
                }

				// Add to coarse location only if locations valid
                if( LocationCoarseValid && LocationFineValid )
                {
                    if ( LatitudeCoarse < 0.0 )
                        LatitudeFine = LatitudeCoarse - LatitudeFine;
                    else
                        LatitudeFine += LatitudeCoarse;
                    if ( LongitudeCoarse < 0.0 )
                        LongitudeFine = LongitudeCoarse - LongitudeFine;
                    else
                        LongitudeFine += LongitudeCoarse;
                }
			}
			break;

        case LOC_NATIONAL:

            // Set BeaconID to default bits 59 to 85
            (*(cbcnid.Low())) &= 0xF0000000;
            (*(cbcnid.Low())) |= 0x03F81FE0;

            // Check for default values
            if( cbcnmsg.Bits(59,71) != 0x0FE0 &&
                cbcnmsg.Bits(72,85) != 0x1FE0 )
                LocationCoarseValid = true;

            // Coarse Location Data for National Protocol
            if( LocationCoarseValid )
            {
                LatitudeCoarse  = cbcnmsg.Bits(60,66);
                LatitudeCoarse += cbcnmsg.Bits(67,71)/30.0;
                if( cbcnmsg.Bit(59) )
                    LatitudeCoarse *= -1;
                LongitudeCoarse  = cbcnmsg.Bits(73,80);
                LongitudeCoarse += cbcnmsg.Bits(81,85)/30.0;
                if( cbcnmsg.Bit(72) )
                    LongitudeCoarse *= -1;
            }

            if( Format == BF_LONG && cbcnmsg.Bit(110))
            {
                // Check for default values
                if( cbcnmsg.Bits(113,119) != 0x4F &&
                    cbcnmsg.Bits(120,126) != 0x4F &&
                    cbcnmsg.Bits(113,126) != 0x3FFF )
                    LocationFineValid = true;

                // Fine Location Data for Standard Protocol
                if( LocationFineValid )
                {
                    LatitudeFine  = cbcnmsg.Bits(114,115)/60.0;
                    LatitudeFine += cbcnmsg.Bits(116,119)/60.0/15.0;
                    if(  !cbcnmsg.Bit(113) )
                        LatitudeFine *= -1;
                    LongitudeFine  = cbcnmsg.Bits(121,122)/60.0;
                    LongitudeFine += cbcnmsg.Bits(123,126)/60.0/15.0;
                    if(  !cbcnmsg.Bit(120) )
                        LongitudeFine *= -1;
                }

                // Add to coarse location only if locations valid
                if( LocationCoarseValid && LocationFineValid )
                {
                    if ( LatitudeCoarse < 0.0 )
                        LatitudeFine = LatitudeCoarse - LatitudeFine;
                    else
                        LatitudeFine += LatitudeCoarse;
                    if ( LongitudeCoarse < 0.0 )
                        LongitudeFine = LongitudeCoarse - LongitudeFine;
                    else
                        LongitudeFine += LongitudeCoarse;
                }
            }
            break;

        default :

            break;

    } // End of location processing

   // Check for valid location data (according to convention)
   if(  fabs(LatitudeCoarse) > 90.0  ||
        fabs(LongitudeCoarse) > 180.0 )
        LocationCoarseValid = false;
   if(  fabs(LatitudeFine) > 90.0  ||
        fabs(LongitudeFine) > 180.0 )
        LocationFineValid = false;

	// Populate the summary values
	m_bHasEncodedLocation = LocationCoarseValid;

	if( LocationCoarseValid )
	{
		m_dEncodedLat = LatitudeCoarse;
		m_dEncodedLong = LongitudeCoarse;
		m_dEncodedAccuracy = 4.0; // Course accuracy = 2 or 15 minutes

		if( LocationFineValid )
		{
			m_dEncodedLat = LatitudeFine;
			m_dEncodedLong = LongitudeFine;
			m_dEncodedAccuracy = 0.125;  // Fine accuracy = 4 seconds
		}
	}
}


void
CBcnMsgDecodeBase::GetEncodedLocation( bool& bHasEncodedLocation, double& dLat, double& dLong )
{
	bHasEncodedLocation	= m_bHasEncodedLocation;
	dLat				= m_dEncodedLat;
	dLong				= m_dEncodedLong;
}

void
CBcnMsgDecodeBase::GetEncodedLocation( bool& bHasEncodedLocation, double& dLat, double& dLong, double& dAccuracy )
{
	GetEncodedLocation( bHasEncodedLocation, dLat, dLong );
	dAccuracy			= m_dEncodedAccuracy;
}

bool
CBcnMsgDecodeBase::ValidFixedBits( CBeaconMessage& cbcnmsg )
{
	bool bValid = true;
	
	TBLocationFlag  LocnFlag = LOC_NULL;
	TBProtocolFlag  ProtFlag = BT_STANDARD;

	//--------------------------------------------------------------------------
	// Protocol Types
	// Bit 26 = 1 : User
	// Bits 26 = 0, 37 = 0 : Standard
	// Bits 26 = 0, 37 = 1 : National  or Standard Test or RLS or ELT(DT)
	//--------------------------------------------------------------------------
	if( cbcnmsg.Bit( 26 ) )
	{
		ProtFlag = BT_USER;
	}
	else if( cbcnmsg.Bit( 37 ) )
	{
		ProtFlag = BT_NATIONAL;
		if( cbcnmsg.Bits( 37, 40 ) == 0x0E)
		   ProtFlag = BT_STANDARD;
	}
	else
	{
		ProtFlag = BT_STANDARD;
	}

    //----------------------------------------------------------------------
    // Protocol Type Processing
    switch ( ProtFlag )
    {
        // User Protocols
        case BT_USER:
			{
				// we don't care about the fixed bits validation for the user's
				LocnFlag = LOC_NULL;
			}
			break;
		case BT_STANDARD:
			{
	            LocnFlag = LOC_STANDARD;
			}
			break;
		case BT_NATIONAL:
			{
				LocnFlag = LOC_NATIONAL;
			}
			break;
	}

	if( LOC_STANDARD == LocnFlag )
	{
		if( cbcnmsg.Bits(107, 110) != 0x0D )
		   bValid = false;
	}
	else if( LOC_NATIONAL == LocnFlag )
	{
		if( cbcnmsg.Bits( 37, 40 ) == 0x0D) // RLS has no fixed bits
		   bValid = true;
		else if( cbcnmsg.Bits( 37, 40 ) == 0x09) // ELT(DT) has no fixed bits
		   bValid = true;
		else if( cbcnmsg.Bits( 107, 109 ) != 0x06)
		   bValid = false;
	}

	return bValid;
}