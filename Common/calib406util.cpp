#include "calib406util.h"

BOOL CEMSCalib406Util::IsGeoRecord( const EMSCALIB406DATA &rCalib406 )
{
    return rCalib406.hdr.id.ulSatID > 199 && rCalib406.hdr.id.ulSatID < 300;
}

void 
CEMSCalib406Util::Convert( const EMSCALIB406DATA& crstrSource, EMSCALIB406DATA2& rstrDest )
{
	rstrDest.hdr = crstrSource.hdr;
	rstrDest.ulPassID = crstrSource.ulPassID;
	rstrDest.i64BeaconID = crstrSource.i64BeaconID;
	rstrDest.timeMsg = crstrSource.timeMsg;
	rstrDest.i64TimeOffset = crstrSource.i64TimeOffset;
	rstrDest.wStatus = crstrSource.wStatus;
	rstrDest.wDuplicateMsgCount = crstrSource.wDuplicateMsgCount;
	rstrDest.dFrequency = crstrSource.dFrequency;
	rstrDest.dFreqOffset = crstrSource.fFreqOffset;
	rstrDest.dCarrierPower = crstrSource.fCarrierPower;
	rstrDest.wBitErrorField1 = crstrSource.wBitErrorField1;
	rstrDest.wBitErrorField2 = crstrSource.wBitErrorField2;
	rstrDest.wBitErrorFrameSynch = crstrSource.wBitErrorFrameSynch;
	memcpy( rstrDest.cBeaconMsg, crstrSource.cBeaconMsg, sizeof(crstrSource.cBeaconMsg) );
}