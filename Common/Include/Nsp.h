/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS:
//      $Workfile: nsp30/include/nsp.h $
//      $Revision: 1.5 $
//      $Modtime: 1995/08/10 11:15:36 $
//
//  Purpose: NSP Common Header file
*M*/


#if !defined (_NSP_H)
#if defined (__BORLANDC__)
#include "nsppatch.h"
#endif

#define _NSP_H

#include "nspwarn.h"

/* ======================================================================== */



/* ---------------------------- Definitions ------------------------------- */

#define  NSP_EPS   (1.0E-12)
#define  NSP_PI    (3.14159265358979324)     /* Standard C not support M_PI */
#define  NSP_2PI   (6.28318530717958648)
#define  NSP_PI_2  (1.57079632679489662)
#define  NSP_PI_4  (0.785398163397448310)

#define  NSP_DegToRad(deg)  ((deg)/180.0 * NSP_PI)

#define  NSPsDegToRad(deg)  ((float) ((deg)/180.0 * NSP_PI))
#define  NSPdDegToRad(deg)  ((double)((deg)/180.0 * NSP_PI))

#define  MAX(a,b)  (((a) > (b)) ? (a) : (b))
#define  MIN(a,b)  (((a) < (b)) ? (a) : (b))

#if !defined (FALSE)
#define  FALSE  0
#define  TRUE   1
#endif

/* --------------------------- Common Types ------------------------------- */

  typedef struct _SCplx {
    float        re;
    float        im;
  } SCplx;

  typedef struct _DCplx {
    double        re;
    double        im;
  } DCplx;

  typedef struct _WCplx {
    short         re;
    short         im;
  } WCplx;

  typedef struct _ICplx {
    long int         re;
    long int         im;
  } ICplx;

/* ======================================================================== */

#endif                                                            /* _NSP_H */


#ifdef __cplusplus
extern "C" {
#endif


/* -------------------------- NSPAPI Definition --------------------------- */

#if !defined (NSPAPI)
# if !defined(NSP_W32DLL)
#  define NSPAPI(type,name,arg) extern    type __stdcall name arg;
# elif defined (__BORLANDC__)
#  define NSPAPI(type,name,arg) extern  type _import __stdcall name arg;
# else
#  define NSPAPI(type,name,arg) extern  __declspec(dllimport) type __stdcall name arg;
# endif
#endif


/* ---------------------- NSP Library Control Symbols -----------------------

nsp_UsesVector:     vector/scalar Zero,Set,Copy,Add,Sub,Mpy,Div,Conj
                    b<,Inv>Tresh<1,2>,bAbs<1,2>,bAdd<2,3>,bExp<1,2>,bLn<1,2>,
                    bMpy<2,3>, bSqr<1,2>, bSqrt<1,2>, Max, Maxext, Min, Minext
                    Mean, StDev
                    Dotprod, Dotprodext,
                    bConj<,Extend><1,2>, bConjFlip2
                    b<Mu,A>LawToLin, bLinTo<Mu,A>Law
                    AutoCorr<Biased,Unbiased>, CrossCorr,
                    Norm, Normext, Normalize

nsp_UsesConversion: bImag, bReal, bCplxTo2Real, b2RealToCplx,
                    b<,r>Mag, b<,rPhase>,
                    bFloatTo<Int,Fix,S31Fix,S15Fix,S7Fix,S1516Fix>,
                    b<Int,Fix,S31Fix,S15Fix,S7Fix,S1516Fix>ToFloat,
                    b<,r>CartToPolar, b<,r>PolarToCart

nsp_UsesConvolution:Conv
                    Conv2D
                    Filter2D

nsp_UsesDct:        Dct

nsp_UsesTransform:  Dft
                    Fft<,Nip>, <Real,Ccs>Fftl<,Nip>, MpyRC<Perm,Pack><2,3>
                    <Real,Ccs><,2>Fft<,Nip>
                    Goertz

nsp_UsesFir:        struct FirState,FirInit<,Mr>,FirFree,Fir<Get,Set><Taps,Dlyl>
                    struct Fir<Taps|Dly>State, <Up,Down>Sample,
                    FirlInit<,Mr,Dlyl>, Firl, Firl<Get,Set><Taps,Dlyl>

nsp_UsesFirGen:     nspdFirLowpass, nspdFirHighpass, nspdFirBandpass 
                    nspdFirBandstop 
                        

nsp_UsesIir:        struct Iir<Tap,Dly>State, IirlInit<,Bq,Dlyl>, Iirl
                    struct Iir<Tap,Dly>State, IirInit<,Bq>, Iir, IirFree

nsp_UsesLms:        struct Lms<Tap,Dly>State, LmslInit<,Mr,Dlyl>,
                    Lmsl<Get,Set><Step,Leak>, Lmsl<,Na>

nsp_UsesMisc:       BitRevTbl,BitRev,
                    TwdTbl

nsp_UsesSampleGen:  struct ToneState, ToneInit, Tone
                    struct TrnglState, TrnglInit, Trngl
                    bRandUni, RandUni, RandUniInit
                    bRandGauss, RandGauss, RandGausInit

nsp_UsesWin:        Win<Bartlett,Hann,Hamming,Blackman<,Std,Opt>,Kaiser>

nsp_UsesWavelet:    WtInit, WtInitLen, WtSetState, WtGetState,
                    WtDecompose, WtReconstruct */


/* ---------------------------- NSP Library Parts ------------------------- */

#if defined (nsp_UsesAll) || defined (nsp_UsesConvolution)
# include  "nspconv.h"
# include  "nspcnv2d.h"
# include  "nspfir2.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesConversion)
# include  "nspcvrt.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesDct)
# include "nspdct.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesFir)
# include  "nspfirl.h"
# include  "nspfirh.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesFirGen)
# include  "nspfirg.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesIir)
# include  "nspiirl.h"
# include  "nspiirh.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesLms)
# include  "nsplmsl.h"
# include  "nsplmsh.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesMisc)
# include  "nspmisc.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesSampleGen)
# include  "nsprand.h"
# include  "nsptone.h"
# include  "nsptrngl.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesTransform)
# include  "nspfft.h"
# include  "nspgrtzl.h"
# include  "nspgrtzw.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesVector)
# include  "nsparith.h"
# include  "nspcorr.h"
# include  "nsplaw.h"
# include  "nsplnexp.h"
# include  "nspsampl.h"
# include  "nspvec.h"
# include  "nspdotp.h"
# include  "nspnorm.h"
# include  "nsplogic.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesWin)
# include  "nspwin.h"
#endif

#if defined (nsp_UsesAll) || defined (nsp_UsesWavelet)
# include  "nspwlt.h"
#endif

#include "nsperror.h"
#include "nspalloc.h"

/* ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif

