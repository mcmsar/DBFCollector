/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/

#include "brrecord.h"
#include "configurationaccessor.h"
#include "emstime.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "emsdomnode.h"

const wchar_t* CEMSBRRecord::ms_cwszRootRegDB406 = L"<RegistrationDB406/>";

const wchar_t* CEMSBRRecord::ms_cwszRegistrationDB406 = L"RegistrationDB406";

const wchar_t* CEMSBRRecord::ms_cwszBcnId15 = L"BcnId15";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBcnId15 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszCSTACNumber = L"CSTACNumber";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeCSTACNumber = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBeaconRegType = L"BeaconRegType";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconRegType = DBFLDTYPE_TINYINT;

const wchar_t* CEMSBRRecord::ms_cwszBeaconType = L"BeaconType";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconType = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBeaconCountryCode = L"BeaconCountryCode";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconCountryCode = DBFLDTYPE_SHORT;

const wchar_t* CEMSBRRecord::ms_cwszBeaconActivationMethod = L"BeaconActivationMethod";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconActivationMethod = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszBeaconManufacturer = L"BeaconManufacturer";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconManufacturer = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBeaconModel = L"BeaconModel";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconModel = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszSpecialStatus = L"SpecialStatus";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSpecialStatus = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszSpecialStatusDate = L"SpecialStatusDate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSpecialStatusDate = DBFLDTYPE_DATETIME;

const wchar_t* CEMSBRRecord::ms_cwszSpecialStatusInfo = L"SpecialStatusInfo";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSpecialStatusInfo = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPreviousSpecialStatus = L"PreviousSpecialStatus";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePreviousSpecialStatus = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBeaconHomingDevice = L"BeaconHomingDevice";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBeaconHomingDevice = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAdditionalBeaconData = L"AdditionalBeaconData";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAdditionalBeaconData = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszInitialDate	 = L"InitialDate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeInitialDate	 = DBFLDTYPE_DATETIME;

const wchar_t* CEMSBRRecord::ms_cwszLastEditDate = L"LastEditDate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeLastEditDate = DBFLDTYPE_DATETIME;

const wchar_t* CEMSBRRecord::ms_cwszConfirmPrintDate = L"ConfirmPrintDate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeConfirmPrintDate = DBFLDTYPE_DATETIME;

const wchar_t* CEMSBRRecord::ms_cwszConfirmCompletedDate = L"ConfirmCompletedDate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeConfirmCompletedDate = DBFLDTYPE_DATETIME;

const wchar_t* CEMSBRRecord::ms_cwszConfirmationStatus = L"ConfirmationStatus";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeConfirmationStatus = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszOwnerName = L"OwnerName";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeOwnerName = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPassword = L"Password";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePassword = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAddress	 = L"Address";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAddress	 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszCity = L"City";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeCity = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszProvince = L"Province";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeProvince = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszMailCode = L"MailCode";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeMailCode = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszMailCountry = L"MailCountry";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeMailCountry = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszEmailAddress = L"EmailAddress";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeEmailAddress = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone1Num = L"Phone1Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone1Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone1Type = L"Phone1Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone1Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone2Num = L"Phone2Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone2Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone2Type = L"Phone2Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone2Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone3Num = L"Phone3Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone3Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone3Type = L"Phone3Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone3Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone4Num = L"Phone4Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone4Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhone4Type = L"Phone4Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhone4Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryContactName = L"PrimaryContactName";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryContactName = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryContactAddressLine1 = L"PrimaryContactAddressLine1";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryContactAddressLine1 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryContactAddressLine2 = L"PrimaryContactAddressLine2";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryContactAddressLine2 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone1Num = L"PrimaryPhone1Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone1Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone1Type = L"PrimaryPhone1Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone1Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone2Num = L"PrimaryPhone2Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone2Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone2Type = L"PrimaryPhone2Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone2Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone3Num = L"PrimaryPhone3Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone3Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone3Type = L"PrimaryPhone3Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone3Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone4Num = L"PrimaryPhone4Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone4Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPrimaryPhone4Type = L"PrimaryPhone4Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePrimaryPhone4Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternateContactName = L"AlternateContactName";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternateContactName = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternateContactAddressLine1 = L"AlternateContactAddressLine1";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternateContactAddressLine1 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternateContactAddressLine2 = L"AlternateContactAddressLine2";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternateContactAddressLine2 = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone1Num = L"AlternatePhone1Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone1Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone1Type = L"AlternatePhone1Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone1Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone2Num = L"AlternatePhone2Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone2Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone2Type = L"AlternatePhone2Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone2Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone3Num = L"AlternatePhone3Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone3Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone3Type = L"AlternatePhone3Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone3Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone4Num = L"AlternatePhone4Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone4Num = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAlternatePhone4Type = L"AlternatePhone4Type";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAlternatePhone4Type = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszOperatorID = L"OperatorID";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeOperatorID = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBlockID = L"BlockID";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBlockID = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszChallengeQuestion = L"ChallengeQuestion";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeChallengeQuestion = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszChallengeResponse = L"ChallengeResponse";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeChallengeResponse = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszNumLogonFail = L"NumLogonFail";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeNumLogonFail = DBFLDTYPE_TINYINT;

const wchar_t* CEMSBRRecord::ms_cwszRecordStatus = L"RecordStatus";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeRecordStatus = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszAdditionalData = L"AdditionalData";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAdditionalData = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszVehicleType = L"VehicleType";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeVehicleType = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszVehicleNationality = L"VehicleNationality";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeVehicleNationality = DBFLDTYPE_SHORT;

const wchar_t* CEMSBRRecord::ms_cwszVehicleName = L"VehicleName";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeVehicleName = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszMMSI = L"MMSI";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeMMSI = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszCallsign = L"CallSign";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeCallsign = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszVehicleRegistrationNumber = L"VehicleRegistrationNumber";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeVehicleRegistrationNumber = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszColor = L"Color";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeColor = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszLength = L"Length";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeLength = DBFLDTYPE_SHORT;

const wchar_t* CEMSBRRecord::ms_cwszAircraft24BitAddress = L"Aircraft24BitAddress";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAircraft24BitAddress = DBFLDTYPE_CHAR;

const wchar_t* CEMSBRRecord::ms_cwszPeopleCapacity = L"PeopleCapacity";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePeopleCapacity = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszVehicleCellularNum = L"VehicleCellularNum";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeVehicleCellularNum = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszPhoneInmarsat = L"PhoneInmarsat";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypePhoneInmarsat = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszRadioEquipment = L"RadioEquipment";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeRadioEquipment = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszSurvivalType1Num = L"SurvivalType1Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSurvivalType1Num = DBFLDTYPE_SHORT;

const wchar_t* CEMSBRRecord::ms_cwszSurvivalType1Desc = L"SurvivalType1Desc";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSurvivalType1Desc = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszSurvivalType2Num = L"SurvivalType2Num";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSurvivalType2Num = DBFLDTYPE_SHORT;

const wchar_t* CEMSBRRecord::ms_cwszSurvivalType2Desc = L"SurvivalType2Desc";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeSurvivalType2Desc = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszAircraftOperatingAgency = L"AircraftOperatingAgency";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeAircraftOperatingAgency = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszLatitudeEncryptKey = L"LatitudeEncryptKey";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeLatitudeEncryptKey = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszLongitudeEncryptKey = L"LongitudeEncryptKey";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeLongitudeEncryptKey = DBFLDTYPE_VARCHAR;

const wchar_t* CEMSBRRecord::ms_cwszBitRate = L"BitRate";
const EMSDBFLDTYPE CEMSBRRecord::ms_ceTypeBitRate = DBFLDTYPE_DOUBLE;

const wchar_t* CEMSBRRecord::ms_cwszColumn = L"column";
const wchar_t* CEMSBRRecord::ms_cwszColName = L"name";
const wchar_t* CEMSBRRecord::ms_cwszColValue = L"value";


CEMSBRRecord::CEMSBRRecord() : CApiObjBase(TEXT("CEMSBRRecord")), m_byRegType(0), m_sCountryCode(0),
							m_sNumLogonFail(0),
							m_sVehicleNationality(0), m_sLength(0), m_sPeopleCapacity(0),
							m_sSurvivalType1Num(0), m_sSurvivalType2Num(0), m_dBitRate(0.0), 
							m_bValidate( false )
{
	m_timeSpecialStatusDate.intTime = 0;
	m_timeInitialDate.intTime = 0;
	m_timeLastEditDate.intTime = 0;
	m_timeConfirmPrintDate.intTime = 0;
	m_timeConfirmCompletedDate.intTime = 0;
}

CEMSBRRecord::CEMSBRRecord( const wchar_t* cwszRecord ) : CApiObjBase(TEXT("CEMSBRRecord")), 
							m_byRegType(0), m_sCountryCode(0), m_sNumLogonFail(0), 
							m_sVehicleNationality(0), m_sLength(0), m_sPeopleCapacity(0),
							m_sSurvivalType1Num(0), m_sSurvivalType2Num(0), 
							m_dBitRate(0.0), m_bValidate( false )
{
	m_timeSpecialStatusDate.intTime = 0;
	m_timeInitialDate.intTime = 0;
	m_timeLastEditDate.intTime = 0;
	m_timeConfirmPrintDate.intTime = 0;
	m_timeConfirmCompletedDate.intTime = 0;

	Set( cwszRecord );
}

CEMSBRRecord::CEMSBRRecord( const CEMSBRRecord& x ) :
					CApiObjBase(TEXT("CEMSBRRecord")),
					m_owszBeaconID( x.m_owszBeaconID ),
					m_owszCSTACNumber( x.m_owszCSTACNumber ),
					m_byRegType( x.m_byRegType ),
					m_owszBeaconType( x.m_owszBeaconType ),
					m_sCountryCode( x.m_sCountryCode ),
					m_owszActivationMethod( x.m_owszActivationMethod ),
					m_owszManufacturer( x.m_owszManufacturer ),
					m_owszModel( x.m_owszModel ),
					m_owszSpecialStatus( x.m_owszSpecialStatus ),
					m_timeSpecialStatusDate( x.m_timeSpecialStatusDate ),
					m_owszSpecialStatusInfo( x.m_owszSpecialStatusInfo ),
					m_owszPreviousSpecialStatus( x.m_owszPreviousSpecialStatus ),
					m_owszBeaconHomingDevice( x.m_owszBeaconHomingDevice ),
					m_owszAdditionalBeaconData( x.m_owszAdditionalBeaconData ),
					m_timeInitialDate( x.m_timeInitialDate ),
					m_timeLastEditDate( x.m_timeLastEditDate ),
					m_timeConfirmPrintDate( x.m_timeConfirmPrintDate ),
					m_timeConfirmCompletedDate( x.m_timeConfirmCompletedDate ),
					m_owszConfirmationStatus( x.m_owszConfirmationStatus ),
					m_owszOwnerName( x.m_owszOwnerName ),
					m_owszPassword( x.m_owszPassword ),
					m_owszAddress( x.m_owszAddress ),
					m_owszCity( x.m_owszCity ),
					m_owszProvince( x.m_owszProvince ),
					m_owszMailCode( x.m_owszMailCode ),
					m_owszMailCountry( x.m_owszMailCountry ),
					m_owszEmailAddress( x.m_owszEmailAddress ),
					m_owszPhone1Num( x.m_owszPhone1Num ),
					m_owszPhone1Type( x.m_owszPhone1Type ),
					m_owszPhone2Num( x.m_owszPhone2Num ),
					m_owszPhone2Type( x.m_owszPhone2Type ),
					m_owszPhone3Num( x.m_owszPhone3Num ),
					m_owszPhone3Type( x.m_owszPhone3Type ),
					m_owszPhone4Num( x.m_owszPhone4Num ),
					m_owszPhone4Type( x.m_owszPhone4Type ),
					m_owszPrimaryContactName( x.m_owszPrimaryContactName ),
					m_owszPrimaryContactAddrLine1( x.m_owszPrimaryContactAddrLine1 ),
					m_owszPrimaryContactAddrLine2( x.m_owszPrimaryContactAddrLine2 ),
					m_owszPrimaryPhone1Num( x.m_owszPrimaryPhone1Num ),
					m_owszPrimaryPhone1Type( x.m_owszPrimaryPhone1Type ),
					m_owszPrimaryPhone2Num( x.m_owszPrimaryPhone2Num ),
					m_owszPrimaryPhone2Type( x.m_owszPrimaryPhone2Type ),
					m_owszPrimaryPhone3Num( x.m_owszPrimaryPhone3Num ),
					m_owszPrimaryPhone3Type( x.m_owszPrimaryPhone3Type ),
					m_owszPrimaryPhone4Num( x.m_owszPrimaryPhone4Num ),
					m_owszPrimaryPhone4Type( x.m_owszPrimaryPhone4Type ),
					m_owszAlternateContactName( x.m_owszAlternateContactName ),
					m_owszAltContactAddrLine1( x.m_owszAltContactAddrLine1 ),
					m_owszAltContactAddrLine2( x.m_owszAltContactAddrLine2 ),
					m_owszAlternatePhone1Num( x.m_owszAlternatePhone1Num ),
					m_owszAlternatePhone1Type( x.m_owszAlternatePhone1Type ),
					m_owszAlternatePhone2Num( x.m_owszAlternatePhone2Num ),
					m_owszAlternatePhone2Type( x.m_owszAlternatePhone2Type ),
					m_owszAlternatePhone3Num( x.m_owszAlternatePhone3Num ),
					m_owszAlternatePhone3Type( x.m_owszAlternatePhone3Type ),
					m_owszAlternatePhone4Num( x.m_owszAlternatePhone4Num ),
					m_owszAlternatePhone4Type( x.m_owszAlternatePhone4Type ),
					m_owszOperatorID( x.m_owszOperatorID ),
					m_owszBlockID( x.m_owszBlockID ),
					m_owszChallengeQuestion( x.m_owszChallengeQuestion ),
					m_owszChallengeResponse( x.m_owszChallengeResponse ),
					m_sNumLogonFail( x.m_sNumLogonFail ),
					m_owszRecordStatus( x.m_owszRecordStatus ),
					m_owszAdditionalData( x.m_owszAdditionalData ),
					m_owszVehicleType( x.m_owszVehicleType ),
					m_sVehicleNationality( x.m_sVehicleNationality ),
					m_owszVehicleName( x.m_owszVehicleName ),
					m_owszMMSI( x.m_owszMMSI ),
					m_owszCallsign( x.m_owszCallsign ),
					m_owszVehicleRegistrationNumber( x.m_owszVehicleRegistrationNumber ),
					m_owszColor( x.m_owszColor ),
					m_sLength( x.m_sLength ),
					m_owszAircraft24BitAddress( x.m_owszAircraft24BitAddress ),
					m_sPeopleCapacity( x.m_sPeopleCapacity ),
					m_owszVehicleCellularNum( x.m_owszVehicleCellularNum ),
					m_owszPhoneInmarsat( x.m_owszPhoneInmarsat ),
					m_owszRadioEquipment( x.m_owszRadioEquipment ),
					m_sSurvivalType1Num( x.m_sSurvivalType1Num ),
					m_owszSurvivalType1Desc( x.m_owszSurvivalType1Desc ),
					m_sSurvivalType2Num( x.m_sSurvivalType2Num ),
					m_owszSurvivalType2Desc( x.m_owszSurvivalType2Desc ),
					m_owszAircraftOperatingAgency( x.m_owszAircraftOperatingAgency ),
					m_owszLatitudeEncryptKey( x.m_owszLatitudeEncryptKey ),
					m_owszLongitudeEncryptKey( x.m_owszLongitudeEncryptKey ),
					m_dBitRate( x.m_dBitRate ),
					m_bValidate( x.m_bValidate )
{
}

CEMSBRRecord::~CEMSBRRecord()
{
}

void 
CEMSBRRecord::Set( const wchar_t* cwszRecord )
{
	if( cwszRecord )
	{
		CEMSConfigurationAccessor oConfig;
		oConfig.SetSource( cwszRecord );

		SetBeaconID( oConfig.GetElementValue( ms_cwszBcnId15 ).c_str() );
		SetCSTACNumber( oConfig.GetElementValue( ms_cwszCSTACNumber ).c_str() );
		SetBeaconRegType( oConfig.GetElementValueShort( ms_cwszBeaconRegType ) );
		SetBeaconType( oConfig.GetElementValue( ms_cwszBeaconType ).c_str() );
		SetBeaconCountryCode( oConfig.GetElementValueShort( ms_cwszBeaconCountryCode ) );
		SetBeaconActivationMethod( oConfig.GetElementValue( ms_cwszBeaconActivationMethod ).c_str() );
		SetBeaconManufacturer( oConfig.GetElementValue( ms_cwszBeaconManufacturer ).c_str() );
		SetBeaconModel( oConfig.GetElementValue( ms_cwszBeaconModel ).c_str() );
		SetSpecialStatus( oConfig.GetElementValue( ms_cwszSpecialStatus ).c_str() );
		SetSpecialStatusDate( CEMSConversionUtil::ConvertToTime( oConfig.GetElementValue( ms_cwszSpecialStatusDate ).c_str() ) );
		SetSpecialStatusInfo( oConfig.GetElementValue( ms_cwszSpecialStatusInfo ).c_str() );
		SetPreviousSpecialStatus( oConfig.GetElementValue( ms_cwszPreviousSpecialStatus ).c_str() );
		SetBeaconHomingDevice( oConfig.GetElementValue( ms_cwszBeaconHomingDevice ).c_str() );
		SetAdditionalBeaconData( oConfig.GetElementValue( ms_cwszAdditionalBeaconData ).c_str() );
		SetInitialDate( CEMSConversionUtil::ConvertToTime( oConfig.GetElementValue( ms_cwszInitialDate	 ).c_str() ) );
		SetLastEditDate( CEMSConversionUtil::ConvertToTime( oConfig.GetElementValue( ms_cwszLastEditDate ).c_str() ) );
		SetConfirmPrintDate( CEMSConversionUtil::ConvertToTime( oConfig.GetElementValue( ms_cwszConfirmPrintDate ).c_str() ) );
		SetConfirmCompletedDate( CEMSConversionUtil::ConvertToTime( oConfig.GetElementValue( ms_cwszConfirmCompletedDate ).c_str() ) );
		SetConfirmationStatus( oConfig.GetElementValue( ms_cwszConfirmationStatus ).c_str() );
		SetOwnerName( oConfig.GetElementValue( ms_cwszOwnerName ).c_str() );
		SetPassword( oConfig.GetElementValue( ms_cwszPassword ).c_str() );
		SetAddress	( oConfig.GetElementValue( ms_cwszAddress	 ).c_str() );
		SetCity( oConfig.GetElementValue( ms_cwszCity ).c_str() );
		SetProvince( oConfig.GetElementValue( ms_cwszProvince ).c_str() );
		SetMailCode( oConfig.GetElementValue( ms_cwszMailCode ).c_str() );
		SetMailCountry( oConfig.GetElementValue( ms_cwszMailCountry ).c_str() );
		SetEmailAddress( oConfig.GetElementValue( ms_cwszEmailAddress ).c_str() );
		SetPhone1Num( oConfig.GetElementValue( ms_cwszPhone1Num ).c_str() );
		SetPhone1Type( oConfig.GetElementValue( ms_cwszPhone1Type ).c_str() );
		SetPhone2Num( oConfig.GetElementValue( ms_cwszPhone2Num ).c_str() );
		SetPhone2Type( oConfig.GetElementValue( ms_cwszPhone2Type ).c_str() );
		SetPhone3Num( oConfig.GetElementValue( ms_cwszPhone3Num ).c_str() );
		SetPhone3Type( oConfig.GetElementValue( ms_cwszPhone3Type ).c_str() );
		SetPhone4Num( oConfig.GetElementValue( ms_cwszPhone4Num ).c_str() );
		SetPhone4Type( oConfig.GetElementValue( ms_cwszPhone4Type ).c_str() );
		SetPrimaryContactName( oConfig.GetElementValue( ms_cwszPrimaryContactName ).c_str() );
		SetPrimaryContactAddressLine1( oConfig.GetElementValue( ms_cwszPrimaryContactAddressLine1 ).c_str() );
		SetPrimaryContactAddressLine2( oConfig.GetElementValue( ms_cwszPrimaryContactAddressLine2 ).c_str() );
		SetPrimaryPhone1Num( oConfig.GetElementValue( ms_cwszPrimaryPhone1Num ).c_str() );
		SetPrimaryPhone1Type( oConfig.GetElementValue( ms_cwszPrimaryPhone1Type ).c_str() );
		SetPrimaryPhone2Num( oConfig.GetElementValue( ms_cwszPrimaryPhone2Num ).c_str() );
		SetPrimaryPhone2Type( oConfig.GetElementValue( ms_cwszPrimaryPhone2Type ).c_str() );
		SetPrimaryPhone3Num( oConfig.GetElementValue( ms_cwszPrimaryPhone3Num ).c_str() );
		SetPrimaryPhone3Type( oConfig.GetElementValue( ms_cwszPrimaryPhone3Type ).c_str() );
		SetPrimaryPhone4Num( oConfig.GetElementValue( ms_cwszPrimaryPhone4Num ).c_str() );
		SetPrimaryPhone4Type( oConfig.GetElementValue( ms_cwszPrimaryPhone4Type ).c_str() );
		SetAlternateContactName( oConfig.GetElementValue( ms_cwszAlternateContactName ).c_str() );
		SetAlternateContactAddressLine1( oConfig.GetElementValue( ms_cwszAlternateContactAddressLine1 ).c_str() );
		SetAlternateContactAddressLine2( oConfig.GetElementValue( ms_cwszAlternateContactAddressLine2 ).c_str() );
		SetAlternatePhone1Num( oConfig.GetElementValue( ms_cwszAlternatePhone1Num ).c_str() );
		SetAlternatePhone1Type( oConfig.GetElementValue( ms_cwszAlternatePhone1Type ).c_str() );
		SetAlternatePhone2Num( oConfig.GetElementValue( ms_cwszAlternatePhone2Num ).c_str() );
		SetAlternatePhone2Type( oConfig.GetElementValue( ms_cwszAlternatePhone2Type ).c_str() );
		SetAlternatePhone3Num( oConfig.GetElementValue( ms_cwszAlternatePhone3Num ).c_str() );
		SetAlternatePhone3Type( oConfig.GetElementValue( ms_cwszAlternatePhone3Type ).c_str() );
		SetAlternatePhone4Num( oConfig.GetElementValue( ms_cwszAlternatePhone4Num ).c_str() );
		SetAlternatePhone4Type( oConfig.GetElementValue( ms_cwszAlternatePhone4Type ).c_str() );
		SetOperatorID( oConfig.GetElementValue( ms_cwszOperatorID ).c_str() );
		SetBlockID( oConfig.GetElementValue( ms_cwszBlockID ).c_str() );
		SetChallengeQuestion( oConfig.GetElementValue( ms_cwszChallengeQuestion ).c_str() );
		SetChallengeResponse( oConfig.GetElementValue( ms_cwszChallengeResponse ).c_str() );
		SetNumLogonFail( oConfig.GetElementValueShort( ms_cwszNumLogonFail ) );
		SetRecordStatus( oConfig.GetElementValue( ms_cwszRecordStatus ).c_str() );
		SetAdditionalData( oConfig.GetElementValue( ms_cwszAdditionalData ).c_str() );
		SetVehicleType( oConfig.GetElementValue( ms_cwszVehicleType ).c_str() );
		SetVehicleNationality( oConfig.GetElementValueShort( ms_cwszVehicleNationality ) );
		SetVehicleName( oConfig.GetElementValue( ms_cwszVehicleName ).c_str() );
		SetMMSI( oConfig.GetElementValue( ms_cwszMMSI ).c_str() );
		SetCallsign( oConfig.GetElementValue( ms_cwszCallsign ).c_str() );
		SetVehicleRegistrationNumber( oConfig.GetElementValue( ms_cwszVehicleRegistrationNumber ).c_str() );
		SetColor( oConfig.GetElementValue( ms_cwszColor ).c_str() );
		SetLength( oConfig.GetElementValueShort( ms_cwszLength ) );
		SetAircraft24BitAddress( oConfig.GetElementValue( ms_cwszAircraft24BitAddress ).c_str() );
		SetPeopleCapacity( oConfig.GetElementValueShort( ms_cwszPeopleCapacity ) );
		SetVehicleCellularNum( oConfig.GetElementValue( ms_cwszVehicleCellularNum ).c_str() );
		SetPhoneInmarsat( oConfig.GetElementValue( ms_cwszPhoneInmarsat ).c_str() );
		SetRadioEquipment( oConfig.GetElementValue( ms_cwszRadioEquipment ).c_str() );
		SetSurvivalType1Num( oConfig.GetElementValueShort( ms_cwszSurvivalType1Num ) );
		SetSurvivalType1Desc( oConfig.GetElementValue( ms_cwszSurvivalType1Desc ).c_str() );
		SetSurvivalType2Num( oConfig.GetElementValueShort( ms_cwszSurvivalType2Num ) );
		SetSurvivalType2Desc( oConfig.GetElementValue( ms_cwszSurvivalType2Desc ).c_str() );
		SetAircraftOperatingAgency( oConfig.GetElementValue( ms_cwszAircraftOperatingAgency ).c_str() );
		SetLatitudeEncryptKey( oConfig.GetElementValue( ms_cwszLatitudeEncryptKey ).c_str() );
		SetLongitudeEncryptKey( oConfig.GetElementValue( ms_cwszLongitudeEncryptKey ).c_str() );
		SetBitRate( oConfig.GetElementValueDouble( ms_cwszBitRate ) );
	}
}

void 
CEMSBRRecord::ParseDSynchRecord( const wchar_t* cwszDSynchRecord )
{
	if( cwszDSynchRecord && (wcslen(cwszDSynchRecord) > 0) )
	{
		CEMSDOMNodeList* pFieldsList = NULL;
		CEMSDOMNode*     pNode = NULL;
		CEMSDOMNode*     pSubNode = NULL;
		
		CEMSConfigurationAccessor oDSynchRecord;
		oDSynchRecord.SetSource( cwszDSynchRecord );

		CEMSConfigurationAccessor oConfig;
        oConfig.SetSource( ms_cwszRootRegDB406 );


		try
		{
			pFieldsList = oDSynchRecord.GetNodes( ms_cwszColumn );

			if( pFieldsList )
			{
				while( pNode = pFieldsList->NextNode() )
				{
					pSubNode = pNode->SelectSingleNode( ms_cwszColName );
					if( pSubNode )
					{
						std::wstring wszFieldValue;
						std::wstring wszFieldName = pSubNode->GetElementTextEx();
						pSubNode->Release();
						pSubNode = NULL;

						pSubNode = pNode->SelectSingleNode( ms_cwszColValue );
						if( pSubNode )
						{
							wszFieldValue = pSubNode->GetElementTextEx();
						}
						oConfig.SetElementValue( wszFieldName.c_str(), wszFieldValue.c_str() );
					}

					if( pSubNode )
					{
						pSubNode->Release();
						pSubNode = NULL;
					}
					
					pNode->Release();
					pNode = NULL;
				}
				pFieldsList->Release();
				pFieldsList = NULL;
			}

			Set( oConfig.Serialize().c_str() );
		}
		catch( ... )
		{
			if( pFieldsList )
			{
				pFieldsList->Release();
				pFieldsList = NULL;
			}

			if( pNode )
			{
				pNode->Release();
				pNode = NULL;
			}
			
			if( pSubNode )
			{
				pSubNode->Release();
				pSubNode = NULL;
			}
			throw;
		}
	}
}

std::wstring 
CEMSBRRecord::Get() const
{
	CEMSConfigurationAccessor oConfig;

	oConfig.SetSource( ms_cwszRootRegDB406 );
	oConfig.SetElementValue( ms_cwszBcnId15, GetBeaconID().c_str() );
	oConfig.SetElementValue( ms_cwszCSTACNumber, GetCSTACNumber().c_str() );
	oConfig.SetElementValue( ms_cwszBeaconRegType, GetBeaconRegType() );
	oConfig.SetElementValue( ms_cwszBeaconType, GetBeaconType().c_str() );
	oConfig.SetElementValue( ms_cwszBeaconCountryCode, GetBeaconCountryCode() );
	oConfig.SetElementValue( ms_cwszBeaconActivationMethod, GetBeaconActivationMethod().c_str() );
	oConfig.SetElementValue( ms_cwszBeaconManufacturer, GetBeaconManufacturer().c_str() );
	oConfig.SetElementValue( ms_cwszBeaconModel, GetBeaconModel().c_str() );
	oConfig.SetElementValue( ms_cwszSpecialStatus, GetSpecialStatus().c_str() );
	oConfig.SetElementValue( ms_cwszSpecialStatusDate, CEMSConversionUtil::ConvertToString( GetSpecialStatusDate().intTime ).c_str() );
	oConfig.SetElementValue( ms_cwszSpecialStatusInfo, GetSpecialStatusInfo().c_str() );
	oConfig.SetElementValue( ms_cwszPreviousSpecialStatus, GetPreviousSpecialStatus().c_str() );
	oConfig.SetElementValue( ms_cwszBeaconHomingDevice, GetBeaconHomingDevice().c_str() );
	oConfig.SetElementValue( ms_cwszAdditionalBeaconData, GetAdditionalBeaconData().c_str() );
	oConfig.SetElementValue( ms_cwszInitialDate, CEMSConversionUtil::ConvertToString( GetInitialDate().intTime ).c_str() );
	oConfig.SetElementValue( ms_cwszLastEditDate, CEMSConversionUtil::ConvertToString( GetLastEditDate().intTime ).c_str() );
	oConfig.SetElementValue( ms_cwszConfirmPrintDate, CEMSConversionUtil::ConvertToString( GetConfirmPrintDate().intTime ).c_str() );
	oConfig.SetElementValue( ms_cwszConfirmCompletedDate, CEMSConversionUtil::ConvertToString( GetConfirmCompletedDate().intTime ).c_str() );
	oConfig.SetElementValue( ms_cwszConfirmationStatus, GetConfirmationStatus().c_str() );
	oConfig.SetElementValue( ms_cwszOwnerName, GetOwnerName().c_str() );
	oConfig.SetElementValue( ms_cwszPassword, GetPassword().c_str() );
	oConfig.SetElementValue( ms_cwszAddress, GetAddress().c_str() );
	oConfig.SetElementValue( ms_cwszCity, GetCity().c_str() );
	oConfig.SetElementValue( ms_cwszProvince, GetProvince().c_str() );
	oConfig.SetElementValue( ms_cwszMailCode, GetMailCode().c_str() );
	oConfig.SetElementValue( ms_cwszMailCountry, GetMailCountry().c_str() );
	oConfig.SetElementValue( ms_cwszEmailAddress, GetEmailAddress().c_str() );
	oConfig.SetElementValue( ms_cwszPhone1Num, GetPhone1Num().c_str() );
	oConfig.SetElementValue( ms_cwszPhone1Type, GetPhone1Type().c_str() );
	oConfig.SetElementValue( ms_cwszPhone2Num, GetPhone2Num().c_str() );
	oConfig.SetElementValue( ms_cwszPhone2Type, GetPhone2Type().c_str() );
	oConfig.SetElementValue( ms_cwszPhone3Num, GetPhone3Num().c_str() );
	oConfig.SetElementValue( ms_cwszPhone3Type, GetPhone3Type().c_str() );
	oConfig.SetElementValue( ms_cwszPhone4Num, GetPhone4Num().c_str() );
	oConfig.SetElementValue( ms_cwszPhone4Type, GetPhone4Type().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryContactName, GetPrimaryContactName().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryContactAddressLine1, GetPrimaryContactAddressLine1().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryContactAddressLine2, GetPrimaryContactAddressLine2().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone1Num, GetPrimaryPhone1Num().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone1Type, GetPrimaryPhone1Type().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone2Num, GetPrimaryPhone2Num().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone2Type, GetPrimaryPhone2Type().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone3Num, GetPrimaryPhone3Num().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone3Type, GetPrimaryPhone3Type().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone4Num, GetPrimaryPhone4Num().c_str() );
	oConfig.SetElementValue( ms_cwszPrimaryPhone4Type, GetPrimaryPhone4Type().c_str() );
	oConfig.SetElementValue( ms_cwszAlternateContactName, GetAlternateContactName().c_str() );
	oConfig.SetElementValue( ms_cwszAlternateContactAddressLine1, GetAlternateContactAddressLine1().c_str() );
	oConfig.SetElementValue( ms_cwszAlternateContactAddressLine2, GetAlternateContactAddressLine2().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone1Num, GetAlternatePhone1Num().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone1Type, GetAlternatePhone1Type().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone2Num, GetAlternatePhone2Num().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone2Type, GetAlternatePhone2Type().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone3Num, GetAlternatePhone3Num().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone3Type, GetAlternatePhone3Type().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone4Num, GetAlternatePhone4Num().c_str() );
	oConfig.SetElementValue( ms_cwszAlternatePhone4Type, GetAlternatePhone4Type().c_str() );
	oConfig.SetElementValue( ms_cwszOperatorID, GetOperatorID().c_str() );
	oConfig.SetElementValue( ms_cwszBlockID, GetBlockID().c_str() );
	oConfig.SetElementValue( ms_cwszChallengeQuestion, GetChallengeQuestion().c_str() );
	oConfig.SetElementValue( ms_cwszChallengeResponse, GetChallengeResponse().c_str() );
	oConfig.SetElementValue( ms_cwszNumLogonFail, GetNumLogonFail() );
	oConfig.SetElementValue( ms_cwszRecordStatus, GetRecordStatus().c_str() );
	oConfig.SetElementValue( ms_cwszAdditionalData, GetAdditionalData().c_str() );
	oConfig.SetElementValue( ms_cwszVehicleType, GetVehicleType().c_str() );
	oConfig.SetElementValue( ms_cwszVehicleNationality, GetVehicleNationality() );
	oConfig.SetElementValue( ms_cwszVehicleName, GetVehicleName().c_str() );
	oConfig.SetElementValue( ms_cwszMMSI, GetMMSI().c_str() );
	oConfig.SetElementValue( ms_cwszCallsign, GetCallsign().c_str() );
	oConfig.SetElementValue( ms_cwszVehicleRegistrationNumber, GetVehicleRegistrationNumber().c_str() );
	oConfig.SetElementValue( ms_cwszColor, GetColor().c_str() );
	oConfig.SetElementValue( ms_cwszLength, GetLength() );
	oConfig.SetElementValue( ms_cwszAircraft24BitAddress, GetAircraft24BitAddress().c_str() );
	oConfig.SetElementValue( ms_cwszPeopleCapacity, GetPeopleCapacity() );
	oConfig.SetElementValue( ms_cwszVehicleCellularNum, GetVehicleCellularNum().c_str() );
	oConfig.SetElementValue( ms_cwszPhoneInmarsat, GetPhoneInmarsat().c_str() );
	oConfig.SetElementValue( ms_cwszRadioEquipment, GetRadioEquipment().c_str() );
	oConfig.SetElementValue( ms_cwszSurvivalType1Num, GetSurvivalType1Num() );
	oConfig.SetElementValue( ms_cwszSurvivalType1Desc, GetSurvivalType1Desc().c_str() );
	oConfig.SetElementValue( ms_cwszSurvivalType2Num, GetSurvivalType2Num() );
	oConfig.SetElementValue( ms_cwszSurvivalType2Desc, GetSurvivalType2Desc().c_str() );
	oConfig.SetElementValue( ms_cwszAircraftOperatingAgency, GetAircraftOperatingAgency().c_str() );
	oConfig.SetElementValue( ms_cwszLatitudeEncryptKey, GetLatitudeEncryptKey().c_str() );
	oConfig.SetElementValue( ms_cwszLongitudeEncryptKey, GetLongitudeEncryptKey().c_str() );
	oConfig.SetElementValue( ms_cwszBitRate, GetBitRate() );

	return oConfig.Serialize();
}

void 
CEMSBRRecord::SetBeaconID( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 15 != wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BcnId15 (" << oszLogVal << ")" );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszBeaconID = cwszValue;
	}
}

void 
CEMSBRRecord::SetCSTACNumber( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 10 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of CSTACNumber (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszCSTACNumber = cwszValue;
	}
}

void 
CEMSBRRecord::SetBeaconRegType( const BYTE cbyValue )
{
	if( m_bValidate )
	{
	}
	
	m_byRegType = cbyValue;
}

void 
CEMSBRRecord::SetBeaconRegType( const wchar_t* cwszValue )
{
	if( m_bValidate )
	{
	}
	
	m_byRegType = CEMSConversionUtil::ConvertToByte( cwszValue );
}

void 
CEMSBRRecord::SetBeaconType( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 32 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BeaconType (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszBeaconType = cwszValue;
	}
}

void 
CEMSBRRecord::SetBeaconCountryCode( const short csValue )
{
	if( m_bValidate )
	{
	}
	
	m_sCountryCode = csValue;
}

void 
CEMSBRRecord::SetBeaconCountryCode( const wchar_t* cwszValue )
{
	if( m_bValidate )
	{
	}
	
	m_sCountryCode = CEMSConversionUtil::ConvertToShort( cwszValue );
}

void 
CEMSBRRecord::SetBeaconActivationMethod( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BeaconActivationMethod (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszActivationMethod = cwszValue;
	}
}

void 
CEMSBRRecord::SetBeaconManufacturer( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BeaconManufacturer (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszManufacturer = cwszValue;
	}
}

void 
CEMSBRRecord::SetBeaconModel( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 32 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BeaconModel (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
		m_owszModel = cwszValue;
	}
}

void 
CEMSBRRecord::SetSpecialStatus( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of SpecialStatus (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
		m_owszSpecialStatus = cwszValue;
	}
}

void 
CEMSBRRecord::SetSpecialStatusDate( const EMSTIME ctimeValue )
{
	if( m_bValidate )
	{
	}

	m_timeSpecialStatusDate = ctimeValue;
}

void 
CEMSBRRecord::SetSpecialStatusInfo( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 255 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of SpecialStatusInfo (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszSpecialStatusInfo = cwszValue;
	}
}

void 
CEMSBRRecord::SetPreviousSpecialStatus( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PreviousSpecialStatus (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPreviousSpecialStatus = cwszValue;
	}
}

void 
CEMSBRRecord::SetBeaconHomingDevice( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 10 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BeaconHomingDevice (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszBeaconHomingDevice = cwszValue;
	}
}

void 
CEMSBRRecord::SetAdditionalBeaconData( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AdditionalBeaconData (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAdditionalBeaconData = cwszValue;
	}
}

void 
CEMSBRRecord::SetInitialDate( const EMSTIME ctimeValue )
{
	if( m_bValidate )
	{
	}

	m_timeInitialDate = ctimeValue;
}

void 
CEMSBRRecord::SetLastEditDate( const EMSTIME ctimeValue )
{
	m_timeLastEditDate = ctimeValue;
}

void 
CEMSBRRecord::SetConfirmPrintDate( const EMSTIME ctimeValue )
{
	if( m_bValidate )
	{
	}
	
	m_timeConfirmPrintDate = ctimeValue;
}

void 
CEMSBRRecord::SetConfirmCompletedDate( const EMSTIME ctimeValue )
{
	if( m_bValidate )
	{
	}
	
	m_timeConfirmCompletedDate = ctimeValue;
}

void 
CEMSBRRecord::SetConfirmationStatus( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of ConfirmationStatus (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszConfirmationStatus = cwszValue;
	}
}

void 
CEMSBRRecord::SetOwnerName( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of OwnerName (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszOwnerName = cwszValue;
	}
}

void 
CEMSBRRecord::SetPassword( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Password (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPassword = cwszValue;
	}
}

void 
CEMSBRRecord::SetAddress( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Address (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAddress = cwszValue;
	}
}

void 
CEMSBRRecord::SetCity( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 32 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of City (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszCity = cwszValue;
	}
}

void 
CEMSBRRecord::SetProvince( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 32 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Province (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszProvince = cwszValue;
	}
}

void 
CEMSBRRecord::SetMailCode( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of MailCode (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszMailCode = cwszValue;
	}
}

void 
CEMSBRRecord::SetMailCountry( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 60 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of MailCountry (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszMailCountry = cwszValue;
	}
}

void 
CEMSBRRecord::SetEmailAddress( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of EmailAddress (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszEmailAddress = cwszValue;
	}
}

void 
CEMSBRRecord::SetPhone1Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( owszValue.empty() )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Phone1Num (cannot be null string), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
			else if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of Phone1Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone1Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPhone1Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Phone1Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone1Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPhone2Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 24 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;
/*
				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of Phone2Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone2Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPhone2Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Phone2Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
		
		m_owszPhone2Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPhone3Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 24 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of Phone3Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
		m_owszPhone3Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPhone3Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Phone3Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone3Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPhone4Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 24 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of Phone4Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone4Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPhone4Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Phone4Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhone4Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryContactName( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryContactName (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryContactName = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryContactAddressLine1( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 80 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryContactAddressLine1 (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryContactAddrLine1 = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryContactAddressLine2( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 80 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryContactAddressLine2 (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryContactAddrLine2 = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone1Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( owszValue.empty() )
			{
				// throw an error.
			}
			else if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of PrimaryPhone1Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone1Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone1Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryPhone1Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone1Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone2Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of PrimaryPhone2Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone2Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone2Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryPhone2Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone2Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone3Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of PrimaryPhone3Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone3Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone3Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryPhone3Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone3Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone4Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of PrimaryPhone4Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone4Num = owszValue;
	}
}

void 
CEMSBRRecord::SetPrimaryPhone4Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PrimaryPhone4Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPrimaryPhone4Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternateContactName( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternateContactName (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternateContactName = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternateContactAddressLine1( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 80 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternateContactAddressLine1 (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAltContactAddrLine1 = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternateContactAddressLine2( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 80 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternateContactAddressLine2 (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAltContactAddrLine2 = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone1Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of AlternatePhone1Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone1Num = owszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone1Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternatePhone1Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone1Type  = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone2Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of AlternatePhone2Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone2Num = owszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone2Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternatePhone2Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone2Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone3Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of AlternatePhone3Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone3Num = owszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone3Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternatePhone3Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone3Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone4Num( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		std::wstring owszValue = cwszValue;
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
				// For now, take the first 48 character until we have a real validation.
				wchar_t wszPhoneNum[25];

				memset( wszPhoneNum, 0, 25 * sizeof(wchar_t) ); 
				wcsncpy( wszPhoneNum, cwszValue, 24); 
				owszValue = wszPhoneNum;

/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_INFO( m_pLogger, "BR record: Invalid value of AlternatePhone4Num (" << oszLogVal << "), Beacon ID = " << oszLogBcnId << ". Will take the first 48 characters" );*/
				//THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone4Num = owszValue;
	}
}

void 
CEMSBRRecord::SetAlternatePhone4Type( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 4 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AlternatePhone4Type (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAlternatePhone4Type = cwszValue;
	}
}

void 
CEMSBRRecord::SetOperatorID( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of OperatorID (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszOperatorID = cwszValue;
	}
}

void 
CEMSBRRecord::SetBlockID( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of BlockID (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszBlockID = cwszValue;
	}
}

void 
CEMSBRRecord::SetChallengeQuestion( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of ChallengeQuestion (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszChallengeQuestion = cwszValue;
	}
}

void 
CEMSBRRecord::SetChallengeResponse( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) || 0 == wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of ChallengeResponse (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszChallengeResponse = cwszValue;
	}
}

void 
CEMSBRRecord::SetNumLogonFail( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sNumLogonFail = csValue;
}

void 
CEMSBRRecord::SetRecordStatus( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 1 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of RecordStatus (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
	}
	
	m_owszRecordStatus = cwszValue;
}

void 
CEMSBRRecord::SetAdditionalData( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 255 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AdditionalData (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAdditionalData = cwszValue;
	}
}

void 
CEMSBRRecord::SetVehicleType( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) || wcslen(cwszValue) == 0 )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of VehicleType (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}
		m_owszVehicleType = cwszValue;
	}
}

void 
CEMSBRRecord::SetVehicleNationality( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sVehicleNationality = csValue;
}

void 
CEMSBRRecord::SetVehicleName( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 48 < wcslen(cwszValue) || wcslen(cwszValue) == 0 )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of VehicleName (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszVehicleName = cwszValue;
	}
}

void 
CEMSBRRecord::SetMMSI( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 9 < wcslen(cwszValue) || wcslen(cwszValue) == 0 )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of MMSI (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszMMSI = cwszValue;
	}
}

void 
CEMSBRRecord::SetCallsign( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 10 < wcslen(cwszValue) || wcslen(cwszValue) == 0 )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Callsign (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszCallsign = cwszValue;
	}
}

void 
CEMSBRRecord::SetVehicleRegistrationNumber( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 16 < wcslen(cwszValue) || wcslen(cwszValue) == 0 )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of VehicleRegistrationNumber (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszVehicleRegistrationNumber = cwszValue;
	}
}

void 
CEMSBRRecord::SetColor( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Color (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszColor = cwszValue;
	}
}

void 
CEMSBRRecord::SetLength( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sLength = csValue;
}

void 
CEMSBRRecord::SetLength( const wchar_t* cwszValue )
{
	if( m_bValidate )
	{
	}

	m_sLength = CEMSConversionUtil::ConvertToShort( cwszValue );
}

void 
CEMSBRRecord::SetAircraft24BitAddress( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 6 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of Aircraft24BitAddress (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAircraft24BitAddress = cwszValue;
	}
}

void 
CEMSBRRecord::SetPeopleCapacity( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sPeopleCapacity = csValue;
}

void 
CEMSBRRecord::SetPeopleCapacity( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
		}
	}

	m_sPeopleCapacity = CEMSConversionUtil::ConvertToShort( cwszValue );
}

void 
CEMSBRRecord::SetVehicleCellularNum( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of VehicleCellularNum (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszVehicleCellularNum = cwszValue;
	}
}

void 
CEMSBRRecord::SetPhoneInmarsat( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 24 < wcslen(cwszValue) )
			{
		/*		std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of PhoneInmarsat (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszPhoneInmarsat = cwszValue;
	}
}

void 
CEMSBRRecord::SetRadioEquipment( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 32 < wcslen(cwszValue) )
			{
				/*std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of RadioEquipment (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszRadioEquipment = cwszValue;
	}
}

void 
CEMSBRRecord::SetSurvivalType1Num( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sSurvivalType1Num = csValue;
}

void 
CEMSBRRecord::SetSurvivalType1Desc( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of SurvivalType1Desc (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszSurvivalType1Desc = cwszValue;
	}
}

void 
CEMSBRRecord::SetSurvivalType2Num( const short csValue )
{
	if( m_bValidate )
	{
	}

	m_sSurvivalType2Num = csValue;
}

void 
CEMSBRRecord::SetSurvivalType2Desc( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of SurvivalType2Desc (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszSurvivalType2Desc = cwszValue;
	}
}

void 
CEMSBRRecord::SetAircraftOperatingAgency( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of AircraftOperatingAgency (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszAircraftOperatingAgency = cwszValue;
	}
}

void 
CEMSBRRecord::SetLatitudeEncryptKey( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of LatitudeEncryptKey (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszLatitudeEncryptKey = cwszValue;
	}
}

void 
CEMSBRRecord::SetLongitudeEncryptKey( const wchar_t* cwszValue )
{
	if( cwszValue )
	{
		if( m_bValidate )
		{
			if( 64 < wcslen(cwszValue) )
			{
/*				std::string oszLogVal = CEMSConversionUtil::ConvertToString( cwszValue );
				std::string oszLogBcnId = CEMSConversionUtil::ConvertToString( GetBeaconID().c_str() );
				LOG4CXX_ERROR( m_pLogger, "BR record: Invalid value of LongitudeEncryptKey (" << oszLogVal << "), Beacon ID = " << oszLogBcnId );*/
				THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
			}
		}

		m_owszLongitudeEncryptKey = cwszValue;
	}
}

void 
CEMSBRRecord::SetBitRate( const double cdValue )
{
	if( m_bValidate )
	{
	}

	m_dBitRate = cdValue;
	
}

EMSTIME 
CEMSBRRecord::_ConvertToEMSTime( const wchar_t* cwszDate ) const
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	wchar_t* wszTemp = NULL;

	try
	{
		if( cwszDate && (wcslen( cwszDate ) > 0) )
		{
			wszTemp = new wchar_t[ wcslen( cwszDate ) + 1 ];

			if( !wszTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszTemp, 0, (wcslen(cwszDate)+1)*sizeof(wchar_t) );

			wcsncpy( wszTemp, cwszDate, wcslen(cwszDate) );

			int iYear = 0;
			int iMonth = 0;
			int iDay = 0;

			int iToken = 0;
			bool bDone = false;

			wchar_t* wszTok = wcstok( wszTemp, L"/-" );

			do
			{
				switch( iToken )
				{
					case 0:
						iDay = _wtoi( wszTok );
						break;
					case 1:
						iMonth = _wtoi( wszTok );
						break;
					case 2:
						iYear = _wtoi( wszTok );
						break;
					default:
						bDone = true;
				}

				iToken++;

			} while( ( wszTok = wcstok( NULL, L"/-" ) ) && !bDone );

			CEMSTime oTime( iYear, iMonth, iDay );

			timeRet = oTime;

			delete[] wszTemp;
			wszTemp = NULL;
		}
	}
	catch( ... )
	{
		if( wszTemp )
		{
			delete[] wszTemp;
			wszTemp = NULL;
		}

		throw;
	}

	return timeRet;
}

std::wstring 
CEMSBRRecord::_ConvertToDateString( const EMSTIME ctimeDate ) const
{
	std::wstring owszRet;

	const wchar_t* cwszDateFormat = L"%02d-%02d-%04d";

	wchar_t wszTempDate[ 11 ];
	memset( wszTempDate, 0, 11*sizeof(wchar_t) );

	EMSTIMEFIELDS tmFields;
	CEMSTime oTime( ctimeDate );

	oTime.GetTime( &tmFields );

	swprintf( wszTempDate, cwszDateFormat, tmFields.nDay, tmFields.nMonth, tmFields.nYear );

	owszRet = wszTempDate;

	return owszRet;
}