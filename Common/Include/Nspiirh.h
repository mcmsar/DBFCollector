/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPIIRH.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:26  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPIIRH.H_v  $
//
//  Purpose: NSP Infinite Impulse Response Filtering.
*M*/

#if !defined (_NSPIIRH_H) || defined (_OWN_BLDPCS)
# define _NSPIIRH_H

/*-------------------------------------------------------------------------*/
/*         IirInit, IirInitBq, IirFree                                     */
/*                                                                         */
/* These functions initialize an IIR filter and provide a higher-level     */
/* interface than the corresponding low-level IIR functions.               */
/*                                                                         */

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>IirInit                                                   */
/*   nsp<sc,cs,dz,zd>IirInit                                               */
/* DESCRIPTION:                                                            */
/*   These functions initialize an arbitrary order IIR filter.             */
/* PARAMETERS:                                                             */
/*   iirType  - input, describes the filter structure to use, and currently*/
/*              must be NSP_IirDefault;                                    */
/*   tapVals  - input, the 2*(order+1) length array specifies the filter   */
/*              coefficients as discussed for the low-level IIR function   */
/*              nsp?IirlInit());                                           */
/*   order    - input, sets polinomial order;                              */
/*   statePtr - output, the pointer to the IIR filter state structure.     */
/*                                                                         */

NSPAPI(void,nspsIirInit,(NSPIirType  iirType, const float         *tapVals,
                         int         order,         NSPIirState *statePtr))
NSPAPI(void,nspcIirInit,(NSPIirType  iirType, const SCplx       *tapVals,
                         int         order,         NSPIirState *statePtr))
NSPAPI(void,nspdIirInit,(NSPIirType  iirType, const double      *tapVals,
                         int         order,         NSPIirState *statePtr))
NSPAPI(void,nspzIirInit,(NSPIirType  iirType, const DCplx       *tapVals,
                         int          order,        NSPIirState *statePtr))
NSPAPI(void,nspwIirInit,(NSPIirType  iirType, const float       *tapVals,
                         int          order,        NSPIirState *statePtr))

NSPAPI(void,nspscIirInit,(NSPIirType iirType, const SCplx       *tapVals,
                          int        order,         NSPIirState *statePtr))
NSPAPI(void,nspcsIirInit,(NSPIirType iirType, const float        *tapVals,
                          int        order,         NSPIirState *statePtr))
NSPAPI(void,nspdzIirInit,(NSPIirType iirType, const DCplx       *tapVals,
                          int        order,         NSPIirState *statePtr))
NSPAPI(void,nspzdIirInit,(NSPIirType iirType, const double      *tapVals,
                          int        order,         NSPIirState *statePtr))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>IirInitBq                                                 */
/*   nsp<sc,cs,dz,zd>IirInitBq                                             */
/* DESCRIPTION:                                                            */
/*   These functions initialize an IIR filter defined by a cascade of      */
/*   biquads.                                                              */
/* PARAMETERS:                                                             */
/*   iirType  - input, describes the filter structure to use, and currently*/
/*              must be NSP_IirDefault;                                    */
/*   tapVals  - input, the 6*numQuads length array specifies the filter    */
/*              coefficients as discussed for the low-level IIR function   */
/*              nsp?IirlInitBq());                                         */
/*   numQuads - input, sets the number of biduads;                         */
/*   tapStPtr - output, pointer to the IIR state structure.                */
/*                                                                         */

NSPAPI(void,nspsIirInitBq,(NSPIirType  iirType, const float         *tapVals,
                           int         numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspcIirInitBq,(NSPIirType  iirType, const SCplx       *tapVals,
                           int         numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspdIirInitBq,(NSPIirType  iirType, const double      *tapVals,
                           int         numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspzIirInitBq,(NSPIirType  iirType, const DCplx       *tapVals,
                           int         numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspwIirInitBq,(NSPIirType  iirType, const float       *tapVals,
                           int         numQuads,      NSPIirState *statePtr))

NSPAPI(void,nspscIirInitBq,(NSPIirType iirType, const SCplx       *tapVals,
                            int        numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspcsIirInitBq,(NSPIirType iirType, const float       *tapVals,
                            int        numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspdzIirInitBq,(NSPIirType iirType, const DCplx       *tapVals,
                            int        numQuads,      NSPIirState *statePtr))
NSPAPI(void,nspzdIirInitBq,(NSPIirType iirType, const double      *tapVals,
                            int        numQuads,      NSPIirState *statePtr))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nspIirFree                                                            */
/* DESCRIPTION:                                                            */
/*   This function must be called after all filtering is done to free      */
/*   dynamic memory associated with statePtr. After calling this function, */
/*   statePtr should not be referenced again.                              */
/* PARAMETERS:                                                             */
/*   statePtr - pointer to the IIR filter state structure.                 */
/*                                                                         */

NSPAPI(void,nspIirFree,(NSPIirState *statePtr))

/*-------------------------------------------------------------------------*/
/*         Iir, bIir                                                       */
/*                                                                         */
/* Filter a signal through a IIR filter.                                   */
/*                                                                         */

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>Iir                                                       */
/*   nsp<sc,cs,dz,zd>Iir                                                   */
/* DESCRIPTION:                                                            */
/*   These functions filter a single sample samp through an IIR filter and */
/*   return the result.                                                    */
/* PARAMETERS:                                                             */
/*   statePtr - input, pointer to the IIR state structure;                 */
/*   samp     - input, the sample value.                                   */
/* RETURNS:                                                                */
/*   the filtering result.                                                 */
/*                                                                         */

NSPAPI(float, nspsIir,(NSPIirState *statePtr, float  samp))
NSPAPI(SCplx, nspcIir,(NSPIirState *statePtr, SCplx  samp))
NSPAPI(double,nspdIir,(NSPIirState *statePtr, double samp))
NSPAPI(DCplx, nspzIir,(NSPIirState *statePtr, DCplx  samp))
NSPAPI(short, nspwIir,(NSPIirState *statePtr, short  samp,
                       int          scaleMode,int   *scaleFactor))

NSPAPI(SCplx,nspscIir,(NSPIirState *statePtr, float  samp))
NSPAPI(SCplx,nspcsIir,(NSPIirState *statePtr, SCplx  samp))
NSPAPI(DCplx,nspdzIir,(NSPIirState *statePtr, double samp))
NSPAPI(DCplx,nspzdIir,(NSPIirState *statePtr, DCplx  samp))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>bIir                                                      */
/*   nsp<sc,cs,dz,zd>bIir                                                  */
/* DESCRIPTION:                                                            */
/*   These functions filter a block of numIters samples inSamps through an */
/*   IIR filter and return the result in outSamps.                         */
/* PARAMETERS:                                                             */
/*   statePtr - input, pointer to the IIR state structure;                 */
/*   inSamps  - input, the pointer to block of numIters samples;           */
/*   outSamps - output, the pointer to block of numIters filtered samples; */
/*   numIters - input, the size of samples' block.                         */
/*                                                                         */

NSPAPI(void,nspsbIir,(NSPIirState *statePtr,  const float  *inSamps,
                      float       *outSamps,        int     numIters))
NSPAPI(void,nspcbIir,(NSPIirState *statePtr,  const SCplx  *inSamps,
                      SCplx       *outSamps,        int     numIters))
NSPAPI(void,nspdbIir,(NSPIirState *statePtr,  const double *inSamps,
                      double      *outSamps,        int     numIters))
NSPAPI(void,nspzbIir,(NSPIirState *statePtr,  const DCplx  *inSamps,
                      DCplx       *outSamps,        int     numIters))
NSPAPI(void,nspwbIir,(NSPIirState *statePtr,  const short  *inSamps,
                      short       *outSamps,        int     numIters,
                      int          scaleMode,       int    *scaleFactor))

NSPAPI(void,nspscbIir,(NSPIirState *statePtr, const float  *inSamps,
                       SCplx       *outSamps,       int     numIters))
NSPAPI(void,nspcsbIir,(NSPIirState *statePtr, const SCplx  *inSamps,
                       SCplx       *outSamps,       int     numIters))
NSPAPI(void,nspdzbIir,(NSPIirState *statePtr, const double *inSamps,
                       DCplx       *outSamps,       int     numIters))
NSPAPI(void,nspzdbIir,(NSPIirState *statePtr, const DCplx  *inSamps,
                       DCplx       *outSamps,       int     numIters))

#endif                                  /* _NSPIIRH_H                      */
