/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPPATCH.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:30  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPPATCH.H_v  $
//
//  Purpose: NSP Common Header file
*M*/

/*===========================================================================*/

#if !defined _NSPPATCH_H && defined __BORLANDC__
#define _NSPPATCH_H

#if defined _NSP_H
#error #include "nsppatch.h" must be before #include "nsp.h"
#endif

/* nsparith.h */
#define nspcAdd      c_nspcAdd
#define nspcSub      c_nspcSub
#define nspcMpy      c_nspcMpy
#define nspcDiv      c_nspcDiv
#define nspcConj     c_nspcConj
#define nspcSet      c_nspcSet
/* nspcnv2d.h */
/* nspconv.h  */
/* nspcorr.h  */
/* nspcvrt.h  */
/* nspdotp.h  */
#define nspcDotProd  c_nspcDotProd
#define nspscDotProd c_nspscDotProd
#define nspcsDotProd c_nspcsDotProd
#define nspvDotProdExt  c_nspvDotProdExt 
#define nspwvDotProdExt c_nspwvDotProdExt 
#define nspvwDotProdExt c_nspvwDotProdExt 

/* nsperror.h */
/* nspfft.h   */
/* nspfir2.h  */
/* nspfirh.h  */
#define nspcFir      c_nspcFir
#define nspscFir     c_nspscFir
#define nspcsFir     c_nspcsFir
/* nspfirl.h */
#define nspcFirl     c_nspcFirl
#define nspscFirl    c_nspscFirl
#define nspcsFirl    c_nspcsFirl
/* nspgrtzl.h */
#define nspsGoertz   c_nspsGoertz
#define nspcGoertz   c_nspcGoertz
#define nspsbGoertz  c_nspsbGoertz
#define nspcbGoertz  c_nspcbGoertz
/* nspiirh.h */
#define nspcIir      c_nspcIir
#define nspscIir     c_nspscIir
#define nspcsIir     c_nspcsIir
/* nspiirl.h */
#define nspcIirl     c_nspcIirl
#define nspscIirl    c_nspscIirl
#define nspcsIirl    c_nspcsIirl
/* nsplaw.h */
/* nsplmsh.h */
#define nspcLms      c_nspcLms
#define nspscLms     c_nspscLms
#define nspcbLms     c_nspcbLms
#define nspscbLms    c_nspscbLms
#define nspcLmsDes   c_nspcLmsDes
#define nspscLmsDes  c_nspscLmsDes
#define nspcLmsGetErrVal c_nspcLmsGetErrVal
/* nsplmsl.h */
#define nspcLmsl     c_nspcLmsl
#define nspscLmsl    c_nspscLmsl
#define nspcbLmsl    c_nspcbLmsl
#define nspscbLmsl   c_nspscbLmsl
#define nspcLmslNa   c_nspcLmslNa
#define nspscLmslNa  c_nspscLmslNa
#define nspcsLmslNa  c_nspcsLmslNa
/* nsplnexp.h */
/* nspmisc.h  */
/* nsprand.h  */
#define nspcRandUni  c_nspcRandUni
#define nspcRandGaus c_nspcRandGaus
/* nspsampl.h */
/* nsptone.h  */
#define nspcTone     c_nspcTone
/* nsptrngl.h */
#define nspcTrngl    c_nspcTrngl
/* nspvec.h   */
/* nspwin.h   */


#endif                                            /* _OWNPATCH_H             */


