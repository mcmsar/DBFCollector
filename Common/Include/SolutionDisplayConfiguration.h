/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __SOLUTION_DISPLAY_CONFIGURATION_H__
#define __SOLUTION_DISPLAY_CONFIGURATION_H__

#include "aobjbase.h"
#include <string>
#include "objectlist.h"
#include "iconfigmanager.h"

class CEMSSDBeaconSymbolConfig;
class CEMSRGBColour;

//! @class CEMSSolutionDisplayConfiguration
//! Provides access to map server configuration data.
class CEMSSolutionDisplayConfiguration : public CApiObjBase
{
	public:
		
		typedef struct tagEMSGeosetTransform
		{
			double dXOffset;
			double dXMin;
			double dXMax;
		} EMSGEOSETTRANSFORM;

		~CEMSSolutionDisplayConfiguration();

		//! @fn static CEMSSolutionDisplayConfiguration* GetInstance()
		//! Get a pointer to an instance of this class.
		static CEMSSolutionDisplayConfiguration* GetInstance();

		//! @fn CEMSSDBeaconSymbolConfig* GetBeaconSymbolInfo( const wchar_t* cwszBeaconType )
		//! Get information regarding the symbol used to represent the specified beacon type.
		//! The caller must Release() the returned pointer.
		CEMSSDBeaconSymbolConfig* GetBeaconSymbolInfo( const wchar_t* cwszBeaconType );

		//! @fn CEMSRGBColour* GetSatelliteTrackColour()
		//! Retrieve the colour to use for rendering a satellite track.
		//! The caller must Release() the returned pointer.
		CEMSRGBColour* GetSatelliteTrackColour();

		//! @fn CEMSRGBColour* GetMutualVisRegionColour()
		//! Retrieve the colour to use for rendering a satellite track.
		//! The caller must Release() the returned pointer.
		CEMSRGBColour* GetMutualVisRegionColour();

		//! @fn ULONG GetSatelliteTrackWidth()
		//! Retrieve the width of the line (in tenths of a point) in which to
		//! render satellite tracks.
		ULONG GetSatelliteTrackWidth();

		//! Retrieve the transform that has been applied to the given geoset.
		EMSGEOSETTRANSFORM GetGeosetTransform( const wchar_t* cwszGeoset );

		//! @fn ULONG AddRef()
		//! This is a singleton so override base class method.
		ULONG AddRef() { return 1; }

		//! @fn ULONG Release()
		//! This is a singleton so override base class method.
		ULONG Release() { return 1; }

	private:
		std::wstring _GetBeaconSymbolKey( const wchar_t* cwszBeaconType );

		IEMSConfigurationManager* _GetConfigManager();
		
	protected:
		CEMSSolutionDisplayConfiguration();

	private:
		//! @var static CEMSSolutionDisplayConfiguration ms_oConfig
		//! The one and only instance of the solution display configuration.
		static CEMSSolutionDisplayConfiguration ms_oConfig;

	private:
		static const wchar_t* ms_cwszSDGroup;
		static const wchar_t* ms_cwszSDNoGroupID;
		static const wchar_t* ms_cwszBeacon121BitmapSymbol;
		static const wchar_t* ms_cwszBeacon243BitmapSymbol;
		static const wchar_t* ms_cwszBeacon406BitmapSymbol;
		static const wchar_t* ms_cwszBeacon406InterfererBitmapSymbol;
		static const wchar_t* ms_cwszSDSatelliteTrackColour;
		static const wchar_t* ms_cwszSDSatelliteTrackWidth;
		static const wchar_t* ms_cwszSDMutualVisRegionColour;
		static const wchar_t* ms_cwszSDGeosetTransform;

};

#endif