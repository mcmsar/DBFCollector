/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPALLOC.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:20  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPALLOC.H_v  $
//
//  Purpose: NSP 8 bytes aligned allocator/deallocator
//
*M*/

#if !defined(_NSPALLOC_H) || defined (_OWN_BLDPCS)
#define _NSPALLOC_H


NSPAPI(void*,  nspMalloc, (int length))

NSPAPI(float*, nspsMalloc,(int length))
NSPAPI(double*,nspdMalloc,(int length))
NSPAPI(SCplx*, nspcMalloc,(int length))
NSPAPI(DCplx*, nspzMalloc,(int length))

NSPAPI(short*, nspwMalloc,(int length))
NSPAPI(WCplx*, nspvMalloc,(int length))
NSPAPI(long*,  nspiMalloc,(int length))
NSPAPI(ICplx*, nspjMalloc,(int length))

NSPAPI(void,   nspFree,   (void* ptr ))

#endif                                  /* _NSPALLOC_H                     */

