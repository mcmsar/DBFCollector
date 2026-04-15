/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS:
//      $Workfile:   NSPFIRG.H  $
//      $Revision:   1.0  $
//      $ModTime:   Nov 23 1997 17:06:34  $
//
//  AUTHOR:
//      Michael S. Kulikov.
//
//  PURPOSE:
//      Declaration of FIR filters design functions and structures.
//
//  FUNCTIONS:
//      nspdFirLowpass   -
//                 computes the lowpass FIR filter coefficients;
//
//      nspdFirHighpass  -
//                 computes the highpass FIR filter coefficients;
//
//      nspdFirBandpass  -
//                 computes the bandpass FIR filter coefficients;
//
//      nspdFirLowpass   -
//                 computes the bandstop FIR filter coefficients.
//
//  ARGUMENTS:
//      rLowFreq  -
//                 low frequency (0 < rLowFreq < 0.5);
//
//      rHighFreq -
//                 high frequency (0 < rHighFreq < 0.5)
//                 (the condition rLowFreq < rHighFreq must be true!);
//
//      taps      -
//                 pointer to the array which specifies
//                 the filter coefficients;
//
//      tapsLen   -
//                 the number of taps in taps[] array (tapsLen>=5);
//
//      winType   -
//                 the NSP_WindowType switch variable,
//                 which specifies the smoothing window type;
//
//      doNormal  -
//                 if doNormal=0 the functions calculates
//                 non-normalized sequence of filter coefficients,
//                 in other cases the sequence of coefficients
//                 will be normalized.
//
//  ENUMS:
//      NSP_WindowType -
//                 NSP_WinRect         no smoothing (smoothing by
//                                     rectangular window);
//                 NSP_WinBartlett     smoothing by Bartlett window;
//                 NSP_WinBlackmanOpt  smoothing by optimal
//                                     Blackman window;
//                 NSP_WinHamming      smoothing by Hamming window;
//                 NSP_WinHann         smoothing by Hann window.
//
//  RETURN:
//      integer value from following:
//                NSP_StsOk           no error;
//                NSP_StsBadPointer   the null pointer to taps[] array pass
//                                    to function;
//                NSP_StsBadLen       the length of coefficient is less five;
//                NSP_StsBadFreq      the low or high frequency isn’t satisfy
//                                    the condition 0 < rLowFreq < 0.5;
//                NSP_StsBadRel       the high frequency is less low.
*M*/

#define NSP_StsBadPointer    -9         /* null pointer was passed         */
#define NSP_StsBadLen       -10         /* bad length of vector was passed */
#define NSP_StsBadFreq      -11         /* bad frequency value was passed  */
#define NSP_StsBadRel       -12         /* bad relation between frequency  */

#if !defined (_NSPFIRG_H) || defined (_OWN_BLDPCS)
#define _NSPFIRG_H

#if !defined (_OWN_BLDPCS)

typedef enum {
   NSP_WinRect,
   NSP_WinBartlett,
   NSP_WinBlackmanOpt,
   NSP_WinHamming,
   NSP_WinHann
} NSP_WindowType;

#endif

NSPAPI(int, nspdFirLowpass,  (double         rfreq,
                              double        *taps,
                              int            tapsLen,
                              NSP_WindowType winType,
                              int            doNormal))

NSPAPI(int, nspdFirHighpass, (double         rfreq,
                              double        *taps,
                              int            tapsLen,
                              NSP_WindowType winType,
                              int            doNormal))

NSPAPI(int, nspdFirBandpass, (double         rLowFreq,
                              double         rHighFreq,
                              double        *taps,
                              int            tapsLen,
                              NSP_WindowType winType,
                              int            doNormal))

NSPAPI(int, nspdFirBandstop, (double         rLowFreq,
                              double         rHighFreq,
                              double        *taps,
                              int            tapsLen,
                              NSP_WindowType winType,
                              int            doNormal))
#endif

