#ifndef __CALIB406UTIL_H__
#define __CALIB406UTIL_H__

#include "EMSTYPES.h"
#include "calib406.h"

class CEMSCalib406Util
{
public:
    static BOOL IsGeoRecord( const EMSCALIB406DATA &rCalib406 );
	static void Convert( const EMSCALIB406DATA& crstrSource, EMSCALIB406DATA2& rstrDest );
};

#endif