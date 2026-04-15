//! @file EMSCalibration.h
//! This file contains the declaration of the CEMSCalibration class.

#ifndef __CALIBRATION_H__
#define __CALIBRATION_H__

#include "aobjbase.h"

class CApiObjBase;

//! @class CEMSCalibration
//! Class used for calibrating supplied records on the LUT Server
//! For now this is just a wrapper so that we can provide this service later
class CEMSCalibration : public CApiObjBase
{
	public:
		CEMSCalibration() {}
		virtual ~CEMSCalibration() {}

		//! @fn void calibrate( EMSVARIANTRECORD& data );
		//!	Calibrates the supplied record before returning it.
		void calibrate( EMSVARIANTRECORD& data ) {}
};

#endif // __CALIBRATION_H__