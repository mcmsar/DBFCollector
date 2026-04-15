/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1996 Intel Corporation. All Rights Reserved.
//
//  PVCS:
//      $Workfile:   NSPSAMPL.H  $
//      $Revision:   1.0  $
//      $Modtime:   Dec 16 1996 17:47:12  $
//
//  Purpose: NSP sample
*M*/

#if !defined (_NSPSAMPL_H)  || defined (_OWN_BLDPCS)
# define _NSPSAMPL_H

/* ------------------------------------------------------------------------*/
/*        UpSample                                                     */
/*                                                                         */
/* Up-sample  a  signal, conceptually increasing  its  sampling rate by an */
/* integer factor and forming output parameters for next sampling;         */

 NSPAPI(void,nspsUpSample,(const float* src, const int srcLen,
                           float  *dst, int* dstLen, const int factor, int* phase))
 NSPAPI(void,nspcUpSample,(const SCplx* src, const int srcLen,
                           SCplx  *dst, int* dstLen, const int factor, int* phase))
 NSPAPI(void,nspdUpSample,(const double* src, const int srcLen,
                           double *dst, int* dstLen, const int factor, int* phase))
 NSPAPI(void,nspzUpSample,(const DCplx* src, const int srcLen,
                           DCplx  *dst, int* dstLen, const int factor, int* phase))
 NSPAPI(void,nspwUpSample,(const short* src, const int srcLen,
                           short  *dst, int* dstLen, const int factor, int* phase))
 NSPAPI(void,nspvUpSample,(const WCplx* src, const int srcLen,
                           WCplx  *dst, int* dstLen, const int factor, int* phase))
/* ------------------------------------------------------------------------*/
/*        DownSample                                                   */
/*                                                                         */
/* Down-sample a  signal, conceptually decreasing  its sample rate  by an  */
/* integer factor and forming output parameters for next sampling;         */

NSPAPI(void,nspsDownSample,(const float* src, const int srcLen,
                           float  *dst, int* dstLen, const int factor, int* phase))
NSPAPI(void,nspcDownSample,(const SCplx* src, const int srcLen,
                           SCplx  *dst, int* dstLen, const int factor, int* phase))
NSPAPI(void,nspdDownSample,(const double* src, const int srcLen,
                           double  *dst, int* dstLen, const int factor, int* phase))
NSPAPI(void,nspzDownSample,(const DCplx* src, const int srcLen,
                           DCplx *dst, int* dstLen, const int factor, int* phase))
NSPAPI(void,nspwDownSample,(const short* src, const int srcLen,
                           short  *dst, int* dstLen, const int factor, int* phase))
NSPAPI(void,nspvDownSample,(const WCplx* src, const int srcLen,
                           WCplx  *dst, int* dstLen, const int factor, int* phase))
#endif                                  /* _NSPSAMPL_H                     */
