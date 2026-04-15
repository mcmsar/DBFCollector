/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPIIRL.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:26  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPIIRL.H_v  $
//
//  Purpose: NSP Infinite Impulse Response Filtering.
*M*/

#if !defined (_NSPIIRL_H) || defined (_OWN_BLDPCS)
# define _NSPIIRL_H

/* ------------------------------------------------------------------------*/

# if !defined (_OWN_BLDPCS)

/*---- User tap type ------------------------------------------------------*/

typedef enum _NSPIirType {NSP_IirNull, NSP_IirDefault} NSPIirType;

/*---- Implementation tap type of initialization --------------------------*/

typedef enum _NSPIirInit {NSP_IirInit, NSP_IirInitBq}  NSPIirInit;

/*---- IIR filter tap state structure -------------------------------------*/

typedef struct _NSPIirTapState {
    int          order;                 /*  order/number of biquads        */
    void        *taps;                  /*  pointer to taps                */
    NSPIirType   iirtype;               /*  user type                      */
    NSPIirInit   initype;               /*  type of initialiuzation        */
} NSPIirTapState;

/*---- IIR filter delay line state structure ------------------------------*/

typedef struct _NSPIirDlyState {
    void        *dlyl;                  /*  pointer to delay line          */
} NSPIirDlyState;

/*---- IIR filter state structure -----------------------------------------*/

typedef struct _NSPIirState {
    NSPIirTapState  tapSt;              /* tap state structure             */
    NSPIirDlyState  dlySt;              /* delay line state structure      */
    int             init;               /* initialization flag             */
} NSPIirState;

# endif                                 /*_NSPIIRL_DEF                     */

/*-------------------------------------------------------------------------*/
/*         IirlInit, IirlInitBq, IirlInitDlyl                              */
/*                                                                         */
/* Perform infinite impulse response filtering.                            */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>IirlInit                                                  */
/* DESCRIPTION:                                                            */
/*   Taps initialization of low-level arbitrary order IIR-filter with      */
/*   transfer function expressed as the ratio of two polinomials of order  */
/*   "order".                                                              */
/* PARAMETERS:                                                             */
/*   iirType  - input, determines the filter structure to use, currently   */
/*              must be NSP_IirDefault;                                    */
/*   taps     - input/output, sets the array taps of filter with transfer  */
/*              function                                                   */
/*                   B0+B1/z+B2/z/z ... +Border/z**order                   */
/*              H(z)=------------------------------------                  */
/*                   A0+A1/z+A2/z/z ... +Aorder/z**order                   */
/*              in following order:                                        */
/*                  B0, B1, ... Border,A0, A1, ... Aorder.                 */
/*              A0 must not be zero;                                       */
/*   order    - input, sets polinomial order;                              */
/*   tapStPtr - output, the pointer to the tap state structure.            */
/*                                                                         */

NSPAPI(void,nspwIirlInit,(NSPIirType      iirType, float  *taps, int order,
                          NSPIirTapState *tapStPtr))
NSPAPI(void,nspsIirlInit,(NSPIirType      iirType, float  *taps, int order,
                          NSPIirTapState *tapStPtr))
NSPAPI(void,nspcIirlInit,(NSPIirType      iirType, SCplx  *taps, int order,
                          NSPIirTapState *tapStPtr))
NSPAPI(void,nspdIirlInit,(NSPIirType      iirType, double *taps, int order,
                          NSPIirTapState *tapStPtr))
NSPAPI(void,nspzIirlInit,(NSPIirType      iirType, DCplx  *taps, int order,
                          NSPIirTapState *tapStPtr))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>IirlInitBq                                                */
/* DESCRIPTION:                                                            */
/*   Low-level IIR-filter iinitialization taps to reference a cascade of   */
/*   biquads. Transfer function is a product of numQuads biquads.          */
/* PARAMETERS:                                                             */
/*   iirType  - input, determines the filter structure to use, currently   */
/*              must be NSP_IirDefault;                                    */
/*   taps     - input/output, sets the array taps of filter                */
/*              with the transfer function                                 */
/*                   (B10+B11/z+B12/z**2)* ... *(BnQ0+BnQ1/z+BnQ2/z**2)    */
/*              H(z)=--------------------------------------------------    */
/*                   (A10+A11/z+A12/z**2)* ... *(AnQ0+AnQ1/z+AnQ2/z**2)    */
/*              in following order:                                        */
/*                   B10, B11, B12, A10, A11, A12, ... ,                   */
/*                   BnQ0, BnQ1, BnQ2, AnQ0, AnQ1, AnQ2.                   */
/*              All Bi0 and Ai0 must not be zero;                          */
/*   numQuads - input, sets the number of biduads;                         */
/*   tapStPtr - output, pointer to the tap state structure.                */
/*                                                                         */

NSPAPI(void,nspwIirlInitBq,(NSPIirType      iirType, float  *taps,int numQuads,
                            NSPIirTapState *tapStPtr))
NSPAPI(void,nspsIirlInitBq,(NSPIirType      iirType, float  *taps,int numQuads,
                            NSPIirTapState *tapStPtr))
NSPAPI(void,nspcIirlInitBq,(NSPIirType      iirType, SCplx  *taps,int numQuads,
                            NSPIirTapState *tapStPtr))
NSPAPI(void,nspdIirlInitBq,(NSPIirType      iirType, double *taps,int numQuads,
                            NSPIirTapState *tapStPtr))
NSPAPI(void,nspzIirlInitBq,(NSPIirType      iirType, DCplx  *taps,int numQuads,
                            NSPIirTapState *tapStPtr))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>IirlInitDlyl                                              */
/* DESCRIPTION:                                                            */
/*   Initialization of delay array for low-level IIR-filter.               */
/* PARAMETERS:                                                             */
/*   tapStPtr - input, the pointer to the tap state structure,             */
/*              initializated previously by the function nsp?IirInit or    */
/*              nsp?IirInitBq;                                             */
/*   dlyl     - input/output, the delay line array. In this implementation */
/*              the input array element values are ignored.                */
/*   dlyStPtr - output, the pointer to the delay line state structure.     */
/*                                                                         */

NSPAPI(void,nspwIirlInitDlyl,(const NSPIirTapState *tapStPtr, long  *dlyl,
                                    NSPIirDlyState *dlyStPtr))
NSPAPI(void,nspsIirlInitDlyl,(const NSPIirTapState *tapStPtr, float  *dlyl,
                                    NSPIirDlyState *dlyStPtr))
NSPAPI(void,nspcIirlInitDlyl,(const NSPIirTapState *tapStPtr, SCplx  *dlyl,
                                    NSPIirDlyState *dlyStPtr))
NSPAPI(void,nspdIirlInitDlyl,(const NSPIirTapState *tapStPtr, double *dlyl,
                                    NSPIirDlyState *dlyStPtr))
NSPAPI(void,nspzIirlInitDlyl,(const NSPIirTapState *tapStPtr, DCplx  *dlyl,
                                    NSPIirDlyState *dlyStPtr))

/*-------------------------------------------------------------------------*/
/*         Iirl, bIirl                                                     */
/*                                                                         */
/* Filter a signal through a low-level IIR filter.                         */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>Iirl                                                      */
/*   nsp<sc,cs,dz,zd>Iirl                                                  */
/* DESCRIPTION:                                                            */
/*   filters a single sample throuth a low-level IIR filter and returns    */
/*   the result.                                                           */
/* PARAMETERS:                                                             */
/*   tapStPtr - input, pointer to the tap state structure;                 */
/*   dlyStPtr - input, pointer to the delay line state structure;          */
/*   smp      - input, the sample value.                                   */
/* RETURNS:                                                                */
/*   the filtering result.                                                 */
/*                                                                         */

NSPAPI(short, nspwIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              short           samp,    int  scaleMode,
                                                       int *scaleFactor))
NSPAPI(float, nspsIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              float           samp))
NSPAPI(SCplx, nspcIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              SCplx           samp))
NSPAPI(double,nspdIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              double          samp))
NSPAPI(DCplx, nspzIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              DCplx           samp))

NSPAPI(SCplx,nspscIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              float           samp))
NSPAPI(SCplx,nspcsIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              SCplx           samp))
NSPAPI(DCplx,nspdzIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              double          samp))
NSPAPI(DCplx,nspzdIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                              DCplx           samp))

/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,c,d,z>bIirl                                                     */
/*   nsp<sc,cs,dz,zd>bIirl                                                 */
/* DESCRIPTION:                                                            */
/*   filters an input block of samples throuth a low-level IIR filter and  */
/*   returns the result in output block.                                   */
/* PARAMETERS:                                                             */
/*   tapStPtr - input, the pointer to the tap state structure;             */
/*   dlyStPtr - input, the pointer to the delay line state structure;      */
/*   inSamps  - input, the block of samples;                               */
/*   outSamps - output, the block of filtered samples;                     */
/*   numIters - input, the size of samples' block.                         */
/*                                                                         */

NSPAPI(void,nspwbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                       const short          *inSamps, short          *outSamps,
                             int             numIters,int  scaleMode,
                                                      int *scaleFactor))
NSPAPI(void,nspsbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                       const float          *inSamps, float          *outSamps,
                             int             numIters))
NSPAPI(void,nspcbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                       const SCplx          *inSamps, SCplx          *outSamps,
                             int             numIters))
NSPAPI(void,nspdbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                       const double         *inSamps, double         *outSamps,
                             int             numIters))
NSPAPI(void,nspzbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                       const DCplx          *inSamps, DCplx          *outSamps,
                             int             numIters))

NSPAPI(void,nspscbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                        const float          *inSamps, SCplx          *outSamps,
                              int             numIters))
NSPAPI(void,nspcsbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                        const SCplx          *inSamps, SCplx          *outSamps,
                              int             numIters))
NSPAPI(void,nspdzbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                        const double         *inSamps, DCplx          *outSamps,
                              int             numIters))
NSPAPI(void,nspzdbIirl,(const NSPIirTapState *tapStPtr,NSPIirDlyState *dlyStPtr,
                        const DCplx          *inSamps, DCplx          *outSamps,
                              int             numIters))

# endif                                 /* _NSPIIRL_H                      */
