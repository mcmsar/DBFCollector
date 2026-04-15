/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1996 Intel Corporation. All Rights Reserved.
//
//  PVCS:
//    $Workfile:   NSPDCT.H  $
//    Created: 1996/08/12  13:17:16
//    $Revision:   1.0  $
//    Author: Chan
//    $Modtime:   Dec 16 1996 17:47:04  $
//
//    Purpose : 
//    e-mail  : Boris_Sabanin@rstl.rfnc.nnov.su
//
*M*/

#if !defined (_NSPDCT_H_) || defined (_OWN_BLDPCS)

#define _NSPDCT_H_

#if !defined _OWN_BLDPCS

#define  NSP_DCT_Forward      1
#define  NSP_DCT_Inverse      2
#define  NSP_DCT_Free         8

#endif

NSPAPI(void,nspsDct,(const float* src, float* dst, int len, int flags))
NSPAPI(void,nspdDct,(const double* src, double* dst, int len, int flags))
NSPAPI(void,nspwDct,(const short* src, short* dst, int len, int flags))

#endif
