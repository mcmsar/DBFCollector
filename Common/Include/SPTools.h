/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __SP_TOOLS_H__
#define __SP_TOOLS_H__

#include "sigproc.h"

//! A collection of common methods used in Signal Processing.
class CEMSSPTools
{
	public:
		CEMSSPTools();
		CEMSSPTools( const CEMSSPTools& x );
		virtual ~CEMSSPTools();
		
		static double GetFrequencyComponents( const EMSCOMPLEX* cacmplxRawBurstFreq, const double cdFrequency0,
								const ULONG culZoomSize, const ULONG culWindowWidth,
								const ULONG culFFTElements, const float cfBinSize, 
								long& rlDopplerPeakIndex, long& rlDopplerStartIndex, 
								long& rlDopplerEndIndex, 
								long& rlAdjustedDopplerPeakIndex, EMSCOMPLEX* acmplxNodBurstFreq	);

		static void DoKaiserBesselWindow( const EMSCOMPLEX* cacmplxFilter, const EMSCOMPLEX* cacmplxData,
										const ULONG culSize, const ULONG culOffset, EMSCOMPLEX* acmplxOutput );

		static void FrameSynch ( const EMSCOMPLEX* cacmplxData,  const EMSCOMPLEX* cacmplxFBS, 
								const ULONG culSize, float& rfFSMax, long& rlFSIndex );

		static void FrameSynchEx( const EMSCOMPLEX* cacmplxData, const EMSCOMPLEX* cacmplxFBS,
			                      const ULONG culSize, float& rfFSMax, 
								  long& rlFSIndex, double& rdFSIndex );


		static double GetTimeOffset( const long clOffsetIndex,	const double cdSampleRate );

		static void GetBitShapeFilter( float* afFilter, const ULONG culFilterLength, const ULONG culInterval );

		static void GetFrameSynchFilter( const long* calMFS, const ULONG culMFSSize,
							const long* calTFS, const ULONG culTFSSize,
							const ULONG culSize, const float cfBitSize,
							EMSCOMPLEX* acmplxBurstFilter, EMSCOMPLEX* acmplxFBSReal,
							EMSCOMPLEX* aFBSTest );

		static void GetFrameSynchFilter( const long* calMFS, const ULONG culMFSSize, 
							const ULONG culSize, const float cfBitSize,	EMSCOMPLEX* acmplxFBSReal );

		
		static void GetBitsSynchFilter( const long* calMFS, const ULONG culBitNum, const ULONG culSize, 
			                            const float cfBitSize, EMSCOMPLEX* acmplxBurstFilter, EMSCOMPLEX* acmplxFBSReal );

		static double QuadraticInterpolation ( const float* cafPower, const ULONG culIndex );

};	

#endif