/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPLAW.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:26  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPLAW.H_v  $
//
//  Purpose :  Convert samples from 8-bit A-law and Mu-law encoded format
//             to linear, or vice-versa.
//  Contents:
//             nsp?bLinToALaw  -
//                     Convert linear PCM samples to 8-bit A-law format.
//             nsp?bALawToLin  -
//                     Convert samples from 8-bit A-law encoded format
//                     to linear PCM.
//             nsp?bLinToMuLaw  -
//                     Convert linear PCM samples to 8-bit Mu-law format.
//             nsp?bMuLawToLin  -
//                     Convert samples from 8-bit Mu-law encoded format
//                     to linear PCM.
//             nspMuLawToALaw  -
//                     Converts samples from Mu-law encoded format
//                     to A-law encoded format.
//             nspALawToMuLaw  -
//                     Converts samples from A-law encoded format
//                     to Mu-law encoded format.
*M*/

#if !defined (_NSPLAW_H) || defined (_OWN_BLDPCS)
# define _NSPLAW_H

NSPAPI(void,nspwbLinToALaw,(const short    *src,unsigned char *dst,int len))
NSPAPI(void,nspibLinToALaw,(const long int *src,unsigned char *dst,int len))
NSPAPI(void,nspsbLinToALaw,(const float    *src,unsigned char *dst,int len))
NSPAPI(void,nspdbLinToALaw,(const double   *src,unsigned char *dst,int len))

NSPAPI(void,nspwbALawToLin,(const unsigned char *src,short    *dst,int len))
NSPAPI(void,nspibALawToLin,(const unsigned char *src,long int *dst,int len))
NSPAPI(void,nspsbALawToLin,(const unsigned char *src,float    *dst,int len))
NSPAPI(void,nspdbALawToLin,(const unsigned char *src,double   *dst,int len))

NSPAPI(void,nspwbLinToMuLaw,(const short    *src,unsigned char *dst,int len))
NSPAPI(void,nspibLinToMuLaw,(const long int *src,unsigned char *dst,int len))
NSPAPI(void,nspsbLinToMuLaw,(const float    *src,unsigned char *dst,int len))
NSPAPI(void,nspdbLinToMuLaw,(const double   *src,unsigned char *dst,int len))

NSPAPI(void,nspwbMuLawToLin,(const unsigned char *src,short    *dst,int len))
NSPAPI(void,nspibMuLawToLin,(const unsigned char *src,long int *dst,int len))
NSPAPI(void,nspsbMuLawToLin,(const unsigned char *src,float    *dst,int len))
NSPAPI(void,nspdbMuLawToLin,(const unsigned char *src,double   *dst,int len))

NSPAPI(void,nspMuLawToALaw,(const unsigned char *src,
                                  unsigned char *dst, int len))

NSPAPI(void,nspALawToMuLaw,(const unsigned char *src,
                                  unsigned char *dst, int len))

#endif                                  /* _NSPLAW_H                       */
