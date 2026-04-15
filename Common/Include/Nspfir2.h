/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile: Nspfir2.h $
//      $Revision: 1 $
//      $Date: 22/04/97 9:13 $
//      $Archive: /gres/project/nsp/filter2/Nspfir2.h $
//
//  Purpose: NSP20 Filter2D
*M*/

#if !defined (_NSPFIR2_H) || defined (_OWN_BLDPCS)
# define _NSPFIR2_H


NSPAPI(void,nspsFilter2D,(const float* x, int xCols, int xRows,
                          const float* h, int hCols, int hRows,
                                float* y))
NSPAPI(void,nspdFilter2D,(const double* x, int xCols, int xRows,
                          const double* h, int hCols, int hRows,
                                double* y))

NSPAPI(void,nspwFilter2D,(const short* x, int xCols, int xRows,
                          const float* h, int hCols, int hRows,
                                short* y,
                          int scaleMode, int* scaleFactorPtr))

#endif /* _NSPFIR2_H */
