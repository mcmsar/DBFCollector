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


#ifndef __BRRECORD_H__
#define __BRRECORD_H__

#include "aobjbase.h"
#include <string>
#include "dal.h"

//! Represents a Beacon Registry record.
class CEMSBRRecord : public CApiObjBase
{
	public:
		CEMSBRRecord();
		//! Create a new instance from a whole record in XML format defined by the C/S IRDB.
		CEMSBRRecord( const wchar_t* cwszRecord );
		CEMSBRRecord( const CEMSBRRecord& x );
		~CEMSBRRecord();

		//! Input a whole record in XML format defined by the C/S IRDB.
		void Set( const wchar_t* cwszRecord );

		//! Retrieve an entire record in XML format defined by the C/S IRDB.
		std::wstring Get() const;

		void ParseDSynchRecord( const wchar_t* cwszDSynchRecord );

		void SetBeaconID( const wchar_t* cwszValue );
		std::wstring GetBeaconID() const { return m_owszBeaconID; }

		void SetCSTACNumber( const wchar_t* cwszValue );
		std::wstring GetCSTACNumber() const { return m_owszCSTACNumber; }

		void SetBeaconRegType( const BYTE cbyValue );
		void SetBeaconRegType( const wchar_t* cwszValue );
		BYTE GetBeaconRegType() const { return m_byRegType; }

		void SetBeaconType( const wchar_t* cwszValue );
		std::wstring GetBeaconType() const { return m_owszBeaconType; }

		void SetBeaconCountryCode( const short csValue );
		void SetBeaconCountryCode( const wchar_t* cwszValue );
		short GetBeaconCountryCode() const { return m_sCountryCode; }

		void SetBeaconActivationMethod( const wchar_t* cwszValue );
		std::wstring GetBeaconActivationMethod() const { return m_owszActivationMethod; }

		void SetBeaconManufacturer( const wchar_t* cwszValue );
		std::wstring GetBeaconManufacturer() const { return m_owszManufacturer; }

		void SetBeaconModel( const wchar_t* cwszValue );
		std::wstring GetBeaconModel() const { return m_owszModel; }

		void SetSpecialStatus( const wchar_t* cwszValue );
		std::wstring GetSpecialStatus() const { return m_owszSpecialStatus; }

		void SetSpecialStatusDate( const EMSTIME ctimeValue );
		EMSTIME GetSpecialStatusDate() const { return m_timeSpecialStatusDate; }

		void SetSpecialStatusInfo( const wchar_t* cwszValue );
		std::wstring GetSpecialStatusInfo() const { return m_owszSpecialStatusInfo; }

		void SetPreviousSpecialStatus( const wchar_t* cwszValue );
		std::wstring GetPreviousSpecialStatus() const { return m_owszPreviousSpecialStatus; }

		void SetBeaconHomingDevice( const wchar_t* cwszValue );
		std::wstring GetBeaconHomingDevice() const { return m_owszBeaconHomingDevice; }

		void SetAdditionalBeaconData( const wchar_t* cwszValue );
		std::wstring GetAdditionalBeaconData() const { return m_owszAdditionalBeaconData; }

		void SetInitialDate( const EMSTIME ctimeValue );
		EMSTIME GetInitialDate() const { return m_timeInitialDate; }

		void SetLastEditDate( const EMSTIME ctimeValue );
		EMSTIME GetLastEditDate() const { return m_timeLastEditDate; }

		void SetConfirmPrintDate( const EMSTIME ctimeValue );
		EMSTIME GetConfirmPrintDate() const { return m_timeConfirmPrintDate; }

		void SetConfirmCompletedDate( const EMSTIME ctimeValue );
		EMSTIME GetConfirmCompletedDate() const { return m_timeConfirmCompletedDate; }

		void SetConfirmationStatus( const wchar_t* cwszValue );
		std::wstring GetConfirmationStatus() const { return m_owszConfirmationStatus; }

		void SetOwnerName( const wchar_t* cwszValue );
		std::wstring GetOwnerName() const { return m_owszOwnerName; }

		void SetPassword( const wchar_t* cwszValue );
		std::wstring GetPassword() const { return m_owszPassword; }

		void SetAddress( const wchar_t* cwszValue );
		std::wstring GetAddress() const { return m_owszAddress; }

		void SetCity( const wchar_t* cwszValue );
		std::wstring GetCity() const { return m_owszCity; }

		void SetProvince( const wchar_t* cwszValue );
		std::wstring GetProvince() const { return m_owszProvince; }

		void SetMailCode( const wchar_t* cwszValue );
		std::wstring GetMailCode() const { return m_owszMailCode; }

		void SetMailCountry( const wchar_t* cwszValue );
		std::wstring GetMailCountry() const { return m_owszMailCountry; }

		void SetEmailAddress( const wchar_t* cwszValue );
		std::wstring GetEmailAddress() const { return m_owszEmailAddress; }

		void SetPhone1Num( const wchar_t* cwszValue );
		std::wstring GetPhone1Num() const { return m_owszPhone1Num; }

		void SetPhone1Type( const wchar_t* cwszValue );
		std::wstring GetPhone1Type() const { return m_owszPhone1Type; }

		void SetPhone2Num( const wchar_t* cwszValue );
		std::wstring GetPhone2Num() const { return m_owszPhone2Num; }

		void SetPhone2Type( const wchar_t* cwszValue );
		std::wstring GetPhone2Type() const { return m_owszPhone2Type; }

		void SetPhone3Num( const wchar_t* cwszValue );
		std::wstring GetPhone3Num() const { return m_owszPhone3Num; }

		void SetPhone3Type( const wchar_t* cwszValue );
		std::wstring GetPhone3Type() const { return m_owszPhone3Type; }

		void SetPhone4Num( const wchar_t* cwszValue );
		std::wstring GetPhone4Num() const { return m_owszPhone4Num; }

		void SetPhone4Type( const wchar_t* cwszValue );
		std::wstring GetPhone4Type() const { return m_owszPhone4Type; }

		void SetPrimaryContactName( const wchar_t* cwszValue );
		std::wstring GetPrimaryContactName() const { return m_owszPrimaryContactName; }

		void SetPrimaryContactAddressLine1( const wchar_t* cwszValue );
		std::wstring GetPrimaryContactAddressLine1() const { return m_owszPrimaryContactAddrLine1; }

		void SetPrimaryContactAddressLine2( const wchar_t* cwszValue );
		std::wstring GetPrimaryContactAddressLine2() const { return m_owszPrimaryContactAddrLine2; }

		void SetPrimaryPhone1Num( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone1Num() const { return m_owszPrimaryPhone1Num; }

		void SetPrimaryPhone1Type( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone1Type() const { return m_owszPrimaryPhone1Type; }

		void SetPrimaryPhone2Num( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone2Num() const { return m_owszPrimaryPhone2Num; }

		void SetPrimaryPhone2Type( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone2Type() const { return m_owszPrimaryPhone2Type; }

		void SetPrimaryPhone3Num( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone3Num() const { return m_owszPrimaryPhone3Num; }

		void SetPrimaryPhone3Type( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone3Type() const { return m_owszPrimaryPhone3Type; }

		void SetPrimaryPhone4Num( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone4Num() const { return m_owszPrimaryPhone4Num; }

		void SetPrimaryPhone4Type( const wchar_t* cwszValue );
		std::wstring GetPrimaryPhone4Type() const { return m_owszPrimaryPhone4Type; }

		void SetAlternateContactName( const wchar_t* cwszValue );
		std::wstring GetAlternateContactName() const { return m_owszAlternateContactName; }

		void SetAlternateContactAddressLine1( const wchar_t* cwszValue );
		std::wstring GetAlternateContactAddressLine1() const { return m_owszAltContactAddrLine1; }

		void SetAlternateContactAddressLine2( const wchar_t* cwszValue );
		std::wstring GetAlternateContactAddressLine2() const { return m_owszAltContactAddrLine2; }
		
		void SetAlternatePhone1Num( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone1Num() const { return m_owszAlternatePhone1Num; }

		void SetAlternatePhone1Type( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone1Type() const { return m_owszAlternatePhone1Type; }

		void SetAlternatePhone2Num( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone2Num() const { return m_owszAlternatePhone2Num; }

		void SetAlternatePhone2Type( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone2Type() const { return m_owszAlternatePhone2Type; }

		void SetAlternatePhone3Num( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone3Num() const { return m_owszAlternatePhone3Num; }

		void SetAlternatePhone3Type( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone3Type() const { return m_owszAlternatePhone3Type; }

		void SetAlternatePhone4Num( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone4Num() const { return m_owszAlternatePhone4Num; }

		void SetAlternatePhone4Type( const wchar_t* cwszValue );
		std::wstring GetAlternatePhone4Type() const { return m_owszAlternatePhone4Type; }

		void SetOperatorID( const wchar_t* cwszValue );
		std::wstring GetOperatorID() const { return m_owszOperatorID; }

		void SetBlockID( const wchar_t* cwszValue );
		std::wstring GetBlockID() const { return m_owszBlockID; }

		void SetChallengeQuestion( const wchar_t* cwszValue );
		std::wstring GetChallengeQuestion() const { return m_owszChallengeQuestion; }

		void SetChallengeResponse( const wchar_t* cwszValue );
		std::wstring GetChallengeResponse() const { return m_owszChallengeResponse; }

		void SetNumLogonFail( const short csValue );
		short GetNumLogonFail() const { return m_sNumLogonFail; }

		void SetRecordStatus( const wchar_t* cwszValue );
		std::wstring GetRecordStatus() const { return m_owszRecordStatus; }

		void SetAdditionalData( const wchar_t* cwszValue );
		std::wstring GetAdditionalData() const { return m_owszAdditionalData; }

		void SetVehicleType( const wchar_t* cwszValue );
		std::wstring GetVehicleType() const { return m_owszVehicleType; }

		void SetVehicleNationality( const short csValue );
		short GetVehicleNationality() const { return m_sVehicleNationality; }

		void SetVehicleName( const wchar_t* cwszValue );
		std::wstring GetVehicleName() const { return m_owszVehicleName; }

		void SetMMSI( const wchar_t* cwszValue );
		std::wstring GetMMSI() const { return m_owszMMSI; }

		void SetCallsign( const wchar_t* cwszValue );
		std::wstring GetCallsign() const { return m_owszCallsign; }

		void SetVehicleRegistrationNumber( const wchar_t* cwszValue );
		std::wstring GetVehicleRegistrationNumber() const { return m_owszVehicleRegistrationNumber; }

		void SetColor( const wchar_t* cwszValue );
		std::wstring GetColor() const { return m_owszColor; }

		void SetLength( const short csValue );
		void SetLength( const wchar_t* cwszValue );
		short GetLength() const { return m_sLength; }

		void SetAircraft24BitAddress( const wchar_t* cwszValue );
		std::wstring GetAircraft24BitAddress() const { return m_owszAircraft24BitAddress; }

		void SetPeopleCapacity( const short csValue );
		void SetPeopleCapacity( const wchar_t* cwszValue );
		short GetPeopleCapacity() const { return m_sPeopleCapacity; }

		void SetVehicleCellularNum( const wchar_t* cwszValue );
		std::wstring GetVehicleCellularNum() const { return m_owszVehicleCellularNum; }

		void SetPhoneInmarsat( const wchar_t* cwszValue );
		std::wstring GetPhoneInmarsat() const { return m_owszPhoneInmarsat; }

		void SetRadioEquipment( const wchar_t* cwszValue );
		std::wstring GetRadioEquipment() const { return m_owszRadioEquipment; }

		void SetSurvivalType1Num( const short csValue );
		short GetSurvivalType1Num() const { return m_sSurvivalType1Num; }

		void SetSurvivalType1Desc( const wchar_t* cwszValue );
		std::wstring GetSurvivalType1Desc() const { return m_owszSurvivalType1Desc; }

		void SetSurvivalType2Num( const short csValue );
		short GetSurvivalType2Num() const { return m_sSurvivalType2Num; }

		void SetSurvivalType2Desc( const wchar_t* cwszValue );
		std::wstring GetSurvivalType2Desc() const { return m_owszSurvivalType2Desc; }

		void SetAircraftOperatingAgency( const wchar_t* cwszValue );
		std::wstring GetAircraftOperatingAgency() const { return m_owszAircraftOperatingAgency; }

		void SetLatitudeEncryptKey( const wchar_t* cwszValue );
		std::wstring GetLatitudeEncryptKey() const { return m_owszLatitudeEncryptKey; }

		void SetLongitudeEncryptKey( const wchar_t* cwszValue );
		std::wstring GetLongitudeEncryptKey() const { return m_owszLongitudeEncryptKey; }

		void SetBitRate( const double cdValue );
		double GetBitRate() const { return m_dBitRate; }

	public:	// constants
		static const wchar_t* ms_cwszRootRegDB406;

		static const wchar_t* ms_cwszRegistrationDB406;

		static const wchar_t* ms_cwszBcnId15;
		static const EMSDBFLDTYPE ms_ceTypeBcnId15;

		static const wchar_t* ms_cwszCSTACNumber;
		static const EMSDBFLDTYPE ms_ceTypeCSTACNumber;

		static const wchar_t* ms_cwszBeaconRegType;
		static const EMSDBFLDTYPE ms_ceTypeBeaconRegType;

		static const wchar_t* ms_cwszBeaconType;
		static const EMSDBFLDTYPE ms_ceTypeBeaconType;

		static const wchar_t* ms_cwszBeaconCountryCode;
		static const EMSDBFLDTYPE ms_ceTypeBeaconCountryCode;

		static const wchar_t* ms_cwszBeaconActivationMethod;
		static const EMSDBFLDTYPE ms_ceTypeBeaconActivationMethod;

		static const wchar_t* ms_cwszBeaconManufacturer;
		static const EMSDBFLDTYPE ms_ceTypeBeaconManufacturer;

		static const wchar_t* ms_cwszBeaconModel;
		static const EMSDBFLDTYPE ms_ceTypeBeaconModel;

		static const wchar_t* ms_cwszSpecialStatus;
		static const EMSDBFLDTYPE ms_ceTypeSpecialStatus;

		static const wchar_t* ms_cwszSpecialStatusDate;
		static const EMSDBFLDTYPE ms_ceTypeSpecialStatusDate;

		static const wchar_t* ms_cwszSpecialStatusInfo;
		static const EMSDBFLDTYPE ms_ceTypeSpecialStatusInfo;

		static const wchar_t* ms_cwszPreviousSpecialStatus;
		static const EMSDBFLDTYPE ms_ceTypePreviousSpecialStatus;

		static const wchar_t* ms_cwszBeaconHomingDevice;
		static const EMSDBFLDTYPE ms_ceTypeBeaconHomingDevice;

		static const wchar_t* ms_cwszAdditionalBeaconData;
		static const EMSDBFLDTYPE ms_ceTypeAdditionalBeaconData;

		static const wchar_t* ms_cwszInitialDate;
		static const EMSDBFLDTYPE ms_ceTypeInitialDate;

		static const wchar_t* ms_cwszLastEditDate;
		static const EMSDBFLDTYPE ms_ceTypeLastEditDate;

		static const wchar_t* ms_cwszConfirmPrintDate;
		static const EMSDBFLDTYPE ms_ceTypeConfirmPrintDate;

		static const wchar_t* ms_cwszConfirmCompletedDate;
		static const EMSDBFLDTYPE ms_ceTypeConfirmCompletedDate;

		static const wchar_t* ms_cwszConfirmationStatus;
		static const EMSDBFLDTYPE ms_ceTypeConfirmationStatus;

		static const wchar_t* ms_cwszOwnerName;
		static const EMSDBFLDTYPE ms_ceTypeOwnerName;

		static const wchar_t* ms_cwszPassword;
		static const EMSDBFLDTYPE ms_ceTypePassword;

		static const wchar_t* ms_cwszAddress;
		static const EMSDBFLDTYPE ms_ceTypeAddress;

		static const wchar_t* ms_cwszCity;
		static const EMSDBFLDTYPE ms_ceTypeCity;

		static const wchar_t* ms_cwszProvince;
		static const EMSDBFLDTYPE ms_ceTypeProvince;

		static const wchar_t* ms_cwszMailCode;
		static const EMSDBFLDTYPE ms_ceTypeMailCode;

		static const wchar_t* ms_cwszMailCountry;
		static const EMSDBFLDTYPE ms_ceTypeMailCountry;

		static const wchar_t* ms_cwszEmailAddress;
		static const EMSDBFLDTYPE ms_ceTypeEmailAddress;

		static const wchar_t* ms_cwszPhone1Num;
		static const EMSDBFLDTYPE ms_ceTypePhone1Num;

		static const wchar_t* ms_cwszPhone1Type;
		static const EMSDBFLDTYPE ms_ceTypePhone1Type;

		static const wchar_t* ms_cwszPhone2Num;
		static const EMSDBFLDTYPE ms_ceTypePhone2Num;

		static const wchar_t* ms_cwszPhone2Type;
		static const EMSDBFLDTYPE ms_ceTypePhone2Type;

		static const wchar_t* ms_cwszPhone3Num;
		static const EMSDBFLDTYPE ms_ceTypePhone3Num;

		static const wchar_t* ms_cwszPhone3Type;
		static const EMSDBFLDTYPE ms_ceTypePhone3Type;

		static const wchar_t* ms_cwszPhone4Num;
		static const EMSDBFLDTYPE ms_ceTypePhone4Num;

		static const wchar_t* ms_cwszPhone4Type;
		static const EMSDBFLDTYPE ms_ceTypePhone4Type;

		static const wchar_t* ms_cwszPrimaryContactName;
		static const EMSDBFLDTYPE ms_ceTypePrimaryContactName;

		static const wchar_t* ms_cwszPrimaryContactAddressLine1;
		static const EMSDBFLDTYPE ms_ceTypePrimaryContactAddressLine1;

		static const wchar_t* ms_cwszPrimaryContactAddressLine2;
		static const EMSDBFLDTYPE ms_ceTypePrimaryContactAddressLine2;

		static const wchar_t* ms_cwszPrimaryPhone1Num;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone1Num;

		static const wchar_t* ms_cwszPrimaryPhone1Type;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone1Type;

		static const wchar_t* ms_cwszPrimaryPhone2Num;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone2Num;

		static const wchar_t* ms_cwszPrimaryPhone2Type;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone2Type;

		static const wchar_t* ms_cwszPrimaryPhone3Num;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone3Num;

		static const wchar_t* ms_cwszPrimaryPhone3Type;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone3Type;

		static const wchar_t* ms_cwszPrimaryPhone4Num;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone4Num;

		static const wchar_t* ms_cwszPrimaryPhone4Type;
		static const EMSDBFLDTYPE ms_ceTypePrimaryPhone4Type;

		static const wchar_t* ms_cwszAlternateContactName;
		static const EMSDBFLDTYPE ms_ceTypeAlternateContactName;

		static const wchar_t* ms_cwszAlternateContactAddressLine1;
		static const EMSDBFLDTYPE ms_ceTypeAlternateContactAddressLine1;

		static const wchar_t* ms_cwszAlternateContactAddressLine2;
		static const EMSDBFLDTYPE ms_ceTypeAlternateContactAddressLine2;

		static const wchar_t* ms_cwszAlternatePhone1Num;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone1Num;

		static const wchar_t* ms_cwszAlternatePhone1Type;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone1Type;

		static const wchar_t* ms_cwszAlternatePhone2Num;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone2Num;

		static const wchar_t* ms_cwszAlternatePhone2Type;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone2Type;

		static const wchar_t* ms_cwszAlternatePhone3Num;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone3Num;

		static const wchar_t* ms_cwszAlternatePhone3Type;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone3Type;

		static const wchar_t* ms_cwszAlternatePhone4Num;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone4Num;

		static const wchar_t* ms_cwszAlternatePhone4Type;
		static const EMSDBFLDTYPE ms_ceTypeAlternatePhone4Type;

		static const wchar_t* ms_cwszOperatorID;
		static const EMSDBFLDTYPE ms_ceTypeOperatorID;

		static const wchar_t* ms_cwszBlockID;
		static const EMSDBFLDTYPE ms_ceTypeBlockID;

		static const wchar_t* ms_cwszChallengeQuestion;
		static const EMSDBFLDTYPE ms_ceTypeChallengeQuestion;

		static const wchar_t* ms_cwszChallengeResponse;
		static const EMSDBFLDTYPE ms_ceTypeChallengeResponse;

		static const wchar_t* ms_cwszNumLogonFail;
		static const EMSDBFLDTYPE ms_ceTypeNumLogonFail;

		static const wchar_t* ms_cwszRecordStatus;
		static const EMSDBFLDTYPE ms_ceTypeRecordStatus;

		static const wchar_t* ms_cwszAdditionalData;
		static const EMSDBFLDTYPE ms_ceTypeAdditionalData;

		static const wchar_t* ms_cwszVehicleType;
		static const EMSDBFLDTYPE ms_ceTypeVehicleType;

		static const wchar_t* ms_cwszVehicleNationality;
		static const EMSDBFLDTYPE ms_ceTypeVehicleNationality;

		static const wchar_t* ms_cwszVehicleName;
		static const EMSDBFLDTYPE ms_ceTypeVehicleName;

		static const wchar_t* ms_cwszMMSI;
		static const EMSDBFLDTYPE ms_ceTypeMMSI;

		static const wchar_t* ms_cwszCallsign;
		static const EMSDBFLDTYPE ms_ceTypeCallsign;

		static const wchar_t* ms_cwszVehicleRegistrationNumber;
		static const EMSDBFLDTYPE ms_ceTypeVehicleRegistrationNumber;

		static const wchar_t* ms_cwszColor;
		static const EMSDBFLDTYPE ms_ceTypeColor;

		static const wchar_t* ms_cwszLength;
		static const EMSDBFLDTYPE ms_ceTypeLength;

		static const wchar_t* ms_cwszAircraft24BitAddress;
		static const EMSDBFLDTYPE ms_ceTypeAircraft24BitAddress;

		static const wchar_t* ms_cwszPeopleCapacity;
		static const EMSDBFLDTYPE ms_ceTypePeopleCapacity;

		static const wchar_t* ms_cwszVehicleCellularNum;
		static const EMSDBFLDTYPE ms_ceTypeVehicleCellularNum;

		static const wchar_t* ms_cwszPhoneInmarsat;
		static const EMSDBFLDTYPE ms_ceTypePhoneInmarsat;

		static const wchar_t* ms_cwszRadioEquipment;
		static const EMSDBFLDTYPE ms_ceTypeRadioEquipment;

		static const wchar_t* ms_cwszSurvivalType1Num;
		static const EMSDBFLDTYPE ms_ceTypeSurvivalType1Num;

		static const wchar_t* ms_cwszSurvivalType1Desc;
		static const EMSDBFLDTYPE ms_ceTypeSurvivalType1Desc;

		static const wchar_t* ms_cwszSurvivalType2Num;
		static const EMSDBFLDTYPE ms_ceTypeSurvivalType2Num;

		static const wchar_t* ms_cwszSurvivalType2Desc;
		static const EMSDBFLDTYPE ms_ceTypeSurvivalType2Desc;

		static const wchar_t* ms_cwszAircraftOperatingAgency;
		static const EMSDBFLDTYPE ms_ceTypeAircraftOperatingAgency;

		static const wchar_t* ms_cwszLatitudeEncryptKey;
		static const EMSDBFLDTYPE ms_ceTypeLatitudeEncryptKey;

		static const wchar_t* ms_cwszLongitudeEncryptKey;
		static const EMSDBFLDTYPE ms_ceTypeLongitudeEncryptKey;

		static const wchar_t* ms_cwszBitRate;
		static const EMSDBFLDTYPE ms_ceTypeBitRate;
		
		static const wchar_t* ms_cwszColumn;
		static const wchar_t* ms_cwszColName;
		static const wchar_t* ms_cwszColValue;

	private:
		//! Convert a date from the YYYY/MM/DD or YYYY-MM-DD format to an EMSTIME type.
		EMSTIME _ConvertToEMSTime( const wchar_t* cwszDate ) const;

		//! Convert an EMSTIME to a string of the form YYYY-MM-DD.
		std::wstring _ConvertToDateString( const EMSTIME ctimeDate ) const;

	private:
		std::wstring	m_owszBeaconID;		//*
		std::wstring	m_owszCSTACNumber;
		BYTE			m_byRegType;
		std::wstring	m_owszBeaconType;
		short			m_sCountryCode;
		std::wstring	m_owszActivationMethod;
		std::wstring	m_owszManufacturer;
		std::wstring	m_owszModel;
		std::wstring	m_owszSpecialStatus;
		EMSTIME			m_timeSpecialStatusDate;
		std::wstring	m_owszSpecialStatusInfo;
		std::wstring	m_owszPreviousSpecialStatus;
		std::wstring	m_owszBeaconHomingDevice;
		std::wstring	m_owszAdditionalBeaconData;
		EMSTIME			m_timeInitialDate;
		EMSTIME			m_timeLastEditDate;
		EMSTIME			m_timeConfirmPrintDate;
		EMSTIME			m_timeConfirmCompletedDate;
		std::wstring	m_owszConfirmationStatus;
		std::wstring	m_owszOwnerName;	//*
		std::wstring	m_owszPassword;
		std::wstring	m_owszAddress;
		std::wstring	m_owszCity;
		std::wstring	m_owszProvince;
		std::wstring	m_owszMailCode;
		std::wstring	m_owszMailCountry;
		std::wstring	m_owszEmailAddress;
		std::wstring	m_owszPhone1Num;	//*
		std::wstring	m_owszPhone1Type;	//*
		std::wstring	m_owszPhone2Num;
		std::wstring	m_owszPhone2Type;
		std::wstring	m_owszPhone3Num;
		std::wstring	m_owszPhone3Type;
		std::wstring	m_owszPhone4Num;
		std::wstring	m_owszPhone4Type;
		std::wstring	m_owszPrimaryContactName;	//*
		std::wstring	m_owszPrimaryContactAddrLine1;
		std::wstring	m_owszPrimaryContactAddrLine2;
		std::wstring	m_owszPrimaryPhone1Num;		//*
		std::wstring	m_owszPrimaryPhone1Type;	//*
		std::wstring	m_owszPrimaryPhone2Num;
		std::wstring	m_owszPrimaryPhone2Type;
		std::wstring	m_owszPrimaryPhone3Num;
		std::wstring	m_owszPrimaryPhone3Type;
		std::wstring	m_owszPrimaryPhone4Num;
		std::wstring	m_owszPrimaryPhone4Type;
		std::wstring	m_owszAlternateContactName;
		std::wstring	m_owszAltContactAddrLine1;
		std::wstring	m_owszAltContactAddrLine2;
		std::wstring	m_owszAlternatePhone1Num;
		std::wstring	m_owszAlternatePhone1Type;
		std::wstring	m_owszAlternatePhone2Num;
		std::wstring	m_owszAlternatePhone2Type;
		std::wstring	m_owszAlternatePhone3Num;
		std::wstring	m_owszAlternatePhone3Type;
		std::wstring	m_owszAlternatePhone4Num;
		std::wstring	m_owszAlternatePhone4Type;
		std::wstring	m_owszOperatorID;
		std::wstring	m_owszBlockID;
		std::wstring	m_owszChallengeQuestion;
		std::wstring	m_owszChallengeResponse;
		short			m_sNumLogonFail;
		std::wstring	m_owszRecordStatus;
		std::wstring	m_owszAdditionalData;
		std::wstring	m_owszVehicleType;		//*
		short			m_sVehicleNationality;
		std::wstring	m_owszVehicleName;		//*
		std::wstring	m_owszMMSI;				//*
		std::wstring	m_owszCallsign;			//*
		std::wstring	m_owszVehicleRegistrationNumber;	//*
		std::wstring	m_owszColor;
		short			m_sLength;
		std::wstring	m_owszAircraft24BitAddress;
		short			m_sPeopleCapacity;
		std::wstring	m_owszVehicleCellularNum;
		std::wstring	m_owszPhoneInmarsat;
		std::wstring	m_owszRadioEquipment;
		short			m_sSurvivalType1Num;
		std::wstring	m_owszSurvivalType1Desc;
		short			m_sSurvivalType2Num;
		std::wstring	m_owszSurvivalType2Desc;
		std::wstring	m_owszAircraftOperatingAgency;
		std::wstring	m_owszLatitudeEncryptKey;
		std::wstring	m_owszLongitudeEncryptKey;
		double			m_dBitRate;

		bool			m_bValidate;
};

#endif