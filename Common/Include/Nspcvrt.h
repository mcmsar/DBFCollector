/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   Nspcvrt.h  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:22  $
//      $Archive:   X:/nsp40_arc/INCLUDE/Nspcvrt.h_v  $
//
//  Purpose: Data Convertion Functions.
*M*/

#if !defined (_NSPCVRT_H) || defined (_OWN_BLDPCS)
#define _NSPCVRT_H

/*-------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

/*-------Flags to determine the transformation-----------------------------*/

#define NSP_Noflags   0x0000         /* Specifies an absence of all flags       */

#define NSP_Round     0x0080       /* Specifies that floating-point values    */
                                /* should be rounded to the nearest integer*/
#define NSP_TruncZero 0x0100      /* Specifies that floating-point values    */
                                /* should be truncated toward zero         */
#define NSP_TruncNeg  0x0200      /* Specifies that floating-point values    */
                                /* should be truncated toward negative     */
                                /* infinity                                */
#define NSP_TruncPos  0x0400      /* Specifies that floating-point values    */
                                /* should be truncated toward positive     */
                                /* infinity                                */
#define NSP_Unsigned  0x0800      /* Specifies that integer values are       */
                                /* unsigned                                */
#define NSP_Clip      0x1000     /* Specifies that floating-point values    */
                                /* outside the allowable integer range     */
                                /* are saturated to maximum(minimum)       */
                                /* integer value                           */
#define NSP_OvfErr    0x2000     /* Specifies that an overflow error should */
                                /* be signaled with a call to nspError()   */

/*-------------------------------------------------------------------------*/
/* Maximum possible phase value for short function, corresponds to NSP_PI  */

#define NSP_CVRT_MAXPHASE ((short)16383)

#endif

/*-------------------------------------------------------------------------*/
/*             bFloatToInt, bIntToFloat                                    */
/*                                                                         */
/*Vector floating-point to integer and integer to floating-point conversion*/
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,d>bFloatToInt                                                   */
/* DESCRIPTION:                                                            */
/*   Converts the float point data in the input array and stores           */
/*   the results in the output array.                                      */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*   wordSize  - specifies the size of an integer in bits,                 */
/*                     and must be 8, 16 or 32;                            */
/*   flags     - specifies the sort of the conversion and consists of the  */
/*               bitwise-OR of flags, defined in the beginnig of this file */
/*                                                                         */

NSPAPI(void,nspsbFloatToInt,(const float  *src, void *dst, int len,
                                   int     wordSize,       int flags))
NSPAPI(void,nspdbFloatToInt,(const double *src, void *dst, int len,
                                   int     wordSize,       int flags))

/* FUNCTION:                                                               */
/*   nsp<s,d>bIntToFloat                                                   */
/* DESCRIPTION:                                                            */
/*   Converts the integer data in the input array and stores the results   */
/*   in the output array                                                   */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*   wordSize  - specifies the size of an integer in bits,                 */
/*                     and must be 8, 16 or 32;                            */
/*   flags     - specifies that integer values are unsigned or signed.     */
/*                                                                         */

NSPAPI(void,nspsbIntToFloat,(const void *src, float  *dst, int len,
                                   int   wordSize,         int flags))
NSPAPI(void,nspdbIntToFloat,(const void *src, double *dst, int len,
                                   int   wordSize,         int flags))

/*-------------------------------------------------------------------------*/
/*             bFloatToFix, bFixToFloat                                    */
/*                                                                         */
/* Vector floating-point to fixed-point and                                */
/*            fixed-point to floating-point conversion                     */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,d>bFloatToFix                                                   */
/* DESCRIPTION:                                                            */
/*   Converts the floating-point data in the input array and stores        */
/*   the results in the output array.                                      */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*   wordSize  - specifies the size of an fix-point in bits,               */
/*                     and must be 8, 16 or 32;                            */
/*   fractBits - specifies the number of fractional bits                   */
/*   flags     - specifies the sort of the conversion and consists of the  */
/*               bitwise-OR of flags, defined in the beginnig of this file */
/*                                                                         */

NSPAPI(void,nspsbFloatToFix,(const float  *src,     void *dst,      int len,
                                   int     wordSize,int   fractBits,int flags))
NSPAPI(void,nspdbFloatToFix,(const double *src,     void *dst,      int len,
                                   int     wordSize,int   fractBits,int flags))

/* FUNCTION:                                                               */
/*   nsp<s,d>bFixToFloat                                                   */
/* DESCRIPTION:                                                            */
/*   Converts the fixed-point data in the input array and stores the       */
/*       results in the output array                                       */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*   wordSize  - specifies the size of an integer in bits,                 */
/*                     and must be 8, 16 or 32;                            */
/*   fractBits - specifies the number of fractional bits                   */
/*   flags     - specifies that fixed-point values are unsigned or signed  */
/*                                                                         */

NSPAPI(void,nspsbFixToFloat,(const void *src,     float  *dst,      int len,
                                   int   wordSize,int     fractBits,int flags))
NSPAPI(void,nspdbFixToFloat,(const void *src,     double *dst,      int len,
                                   int   wordSize,int     fractBits,int flags))


/*-------------------------------------------------------------------------*/
/* bFloatToS31Fix, bFloatToS15Fix, bFloatToS7Fix, bFloatToS1516Fix,        */
/* bS31FixToFloat, bS15FixToFloat, bS7FixToFloat, bS1516FixToFloat         */
/* Vector floating-point to fixed-point of format S.31, S.15, S.7, S15.16  */
/*                and fixed-point of format S.31, S.15, S.7, S15.16        */
/*                to floating-point conversion                             */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<s,d>bFloatToS31Fix                                                */
/*   nsp<s,d>bFloatToS15Fix                                                */
/*   nsp<s,d>bFloatToS7Fix                                                 */
/*   nsp<s,d>bFloatToS1516Fix                                              */
/* DESCRIPTION:                                                            */
/*   Converts the floating-point data in the input array and stores        */
/*   the results in the output array.                                      */
/*   nsp?bFloatToS31Fix() to format of S.31 (a sign bit,31 fractional bits)*/
/*   nsp?bFloatToS15Fix() to format of S.15 (a sign bit,15 fractional bits)*/
/*   nsp?bFloatToS7Fix()  to format of S.7  (a sign bit,7  fractional bits)*/
/*   nsp?bFloatToS1516Fix() to format of S15.16                            */
/*                    (a sign bit, 15 integer bits, 16 fractional bits)    */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*   flags     - specifies the sort of the conversion and consists of the  */
/*               bitwise-OR of flags, defined in the beginnig of this file */

NSPAPI(void,nspsbFloatToS31Fix,  (const float *src,long  *dst, int len,int flags))
NSPAPI(void,nspsbFloatToS15Fix,  (const float *src,short *dst, int len,int flags))
NSPAPI(void,nspsbFloatToS7Fix,   (const float *src,char  *dst, int len,int flags))
NSPAPI(void,nspsbFloatToS1516Fix,(const float *src,long  *dst, int len,int flags))

NSPAPI(void,nspdbFloatToS31Fix,  (const double *src,long  *dst,int len,int flags))
NSPAPI(void,nspdbFloatToS15Fix,  (const double *src,short *dst,int len,int flags))
NSPAPI(void,nspdbFloatToS7Fix,   (const double *src,char  *dst,int len,int flags))
NSPAPI(void,nspdbFloatToS1516Fix,(const double *src,long  *dst,int len,int flags))

/* FUNCTION:                                                               */
/*   nsp<s,d>bS31FixToFloat                                                */
/*   nsp<s,d>bS15FixToFloat                                                */
/*   nsp<s,d>bS7FixToFloat                                                 */
/*   nsp<s,d>bS1516FixToFloat                                              */
/* DESCRIPTION:                                                            */
/*   Converts the fixed-point data in the input array and stores the       */
/*       results in the output array                                       */
/*  nsp?bS31FixToFloat() from format of S.31(a sign bit,31 fractional bits)*/
/*  nsp?bS15FixToFloat() from format of S.15(a sign bit,15 fractional bits)*/
/*  nsp?bS7FixToFloat()  from format of S.7 (a sign bit,7  fractional bits)*/
/*  nsp?bS1516FixToFloat() from format of S15.16                           */
/*                    (a sign bit, 15 integer bits, 16 fractional bits)    */
/* PARAMETERS:                                                             */
/*   src       - an input array to be converted;                           */
/*   dst       - an output array to store the result;                      */
/*   len       - a length of the arrays;                                   */
/*                                                                         */

NSPAPI(void,nspsbS31FixToFloat,  (const long  *src, float  *dst, int len))
NSPAPI(void,nspsbS15FixToFloat,  (const short *src, float  *dst, int len))
NSPAPI(void,nspsbS7FixToFloat,   (const char  *src, float  *dst, int len))
NSPAPI(void,nspsbS1516FixToFloat,(const long  *src, float  *dst, int len))
NSPAPI(void,nspdbS31FixToFloat,  (const long  *src, double *dst, int len))
NSPAPI(void,nspdbS15FixToFloat,  (const short *src, double *dst, int len))
NSPAPI(void,nspdbS7FixToFloat,   (const char  *src, double *dst, int len))
NSPAPI(void,nspdbS1516FixToFloat,(const long  *src, double *dst, int len))

/*-------------------------------------------------------------------------*/
/*  bReal, bImag, bCplxTo2Real, b2RealToCplx                               */
/*                                                                         */
/* Return the real and imaginary parts of complex vectors                  */
/* or construct complex vectors from real and imaginary components         */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<v,c,z>bReal                                                       */
/* DESCRIPTION:                                                            */
/*   Return the real part of the coplex vector                             */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   dst       - an output vector to store the real part;                  */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbReal,(const SCplx *src,float  *dst,int length))
NSPAPI(void,nspzbReal,(const DCplx *src,double *dst,int length))
NSPAPI(void,nspvbReal,(const WCplx *src,short  *dst,int length))

/* FUNCTION:                                                               */
/*   nsp<v,c,z>bImag                                                       */
/* DESCRIPTION:                                                            */
/*   Return the imaginary part of the coplex vector                        */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   dst       - an output vector to store the imaginary part;             */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbImag,(const SCplx *src,float  *dst,int length))
NSPAPI(void,nspzbImag,(const DCplx *src,double *dst,int length))
NSPAPI(void,nspvbImag,(const WCplx *src,short  *dst,int length))

/* FUNCTION:                                                               */
/*   nsp<v,c,z>bCplxTo2Real                                                */
/* DESCRIPTION:                                                            */
/*   Return the real and imaginary parts of the coplex vector              */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   dstReal   - an output vector to store the real part                   */
/*   dstImag   - an output vector to store the imaginary part;             */
/*   len       - a length of the arrays;                                   */
/*                                                                         */
NSPAPI(void,nspcbCplxTo2Real,(const SCplx  *src,    float  *dstReal,
                                    float  *dstImag,int     length))
NSPAPI(void,nspzbCplxTo2Real,(const DCplx  *src,    double *dstReal,
                                    double *dstImag,int     length))
NSPAPI(void,nspvbCplxTo2Real,(const WCplx  *src,    short  *dstReal,
                                    short  *dstImag,int     length))

/* FUNCTION:                                                               */
/*   nsp<v,c,z>b2RealToCplx                                                */
/* DESCRIPTION:                                                            */
/*   Construct complex vector from real and imaginary components           */
/* PARAMETERS:                                                             */
/*   srcReal   - an input real component. May be NULL - a real part of the */
/*               output will be zero;                                      */
/*   srcImag   - an input imaginary component. May be NULL - an imaginary  */
/*               part of the output will be zero;                          */
/*   dst       - an output complex vector;                                 */
/*   len       - a length of the arrays;                                   */
/*                                                                         */
NSPAPI(void,nspcb2RealToCplx,(const float  *srcReal,const float  *srcImag,
                                    SCplx  *dst,          int     length))
NSPAPI(void,nspzb2RealToCplx,(const double *srcReal,const double *srcImag,
                                    DCplx  *dst,          int     length))
NSPAPI(void,nspvb2RealToCplx,(const short  *srcReal,const short  *srcImag,
                                    WCplx  *dst,          int     length))

/*-------------------------------------------------------------------------*/
/*  bCartToPolar, brCartToPolar, bPolarToCart, brPolarToCart               */
/*                                                                         */
/* Cartesian to polar and polar to cartesian coordinate conversions.       */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<v,c,z>bCartToPolar                                                */
/* DESCRIPTION:                                                            */
/*   Convert cartesian coordinate to polar. Input data are formed as       */
/*            a complex vector.                                            */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector;                                  */
/*   mag       - an output vector to store the magnitude components;       */
/*   phase     - an output vector to store the phase components (in rad)); */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbCartToPolar,(const SCplx *src, float  *mag, float  *phase,
                                    int    len))
NSPAPI(void,nspzbCartToPolar,(const DCplx *src, double *mag, double *phase,
                                    int    len))

/* FUNCTION:                                                               */
/*   nsp<w,s,d>brCartToPolar                                               */
/* DESCRIPTION:                                                            */
/*   Convert cartesian coordinate to polar. Input data are formed as       */
/*            two different real vectors.                                  */
/* PARAMETERS:                                                             */
/*   srcReal   - an input vector containing the coordinates X;             */
/*   srcImag   - an input vector containing the coordinates Y;             */
/*   mag       - an output vector to store the magnitude components;       */
/*   phase     - an output vector to store the phase components (in rad)); */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspsbrCartToPolar,(const float  *srcReal,const float  *srcImag,
                                     float  *mag,          float  *phase,
                                     int     len))
NSPAPI(void,nspdbrCartToPolar,(const double *srcReal,const double *srcImag,
                                     double *mag,          double *phase,
                                     int     len))

/* FUNCTION:                                                               */
/*   nsp<v,c,z>bPolarToCart                                                */
/* DESCRIPTION:                                                            */
/*   Convert polar coordinate to cartesian. Output data are formed as      */
/*            a complex vector.                                            */
/* PARAMETERS:                                                             */
/*   mag       - an input vector containing the magnitude components;      */
/*   phase     - an input vector containing the phase components(in rad)); */
/*   dst       - an output complex vector to store the cartesian coords;   */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbPolarToCart,(const float  *mag, const float  *phase,
                                    SCplx  *dst,       int     len))
NSPAPI(void,nspzbPolarToCart,(const double *mag, const double *phase,
                                    DCplx  *dst,       int     len))

/* FUNCTION:                                                               */
/*   nsp<s,d>brPolarToCart                                                 */
/* DESCRIPTION:                                                            */
/*   Convert polar coordinate to cartesian. Output data are formed as      */
/*            two real vectors.                                            */
/* PARAMETERS:                                                             */
/*   mag       - an input vector containing the magnitude components;      */
/*   phase     - an input vector containing the phase components(in rad)); */
/*   dstReal   - an output complex vector to store the coordinates X;      */
/*   dstImag   - an output complex vector to store the coordinates Y;      */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspsbrPolarToCart,(const float *mag, const float  *phase,
                                     float *dstReal,   float  *dstImag,int len))
NSPAPI(void,nspdbrPolarToCart,(const double *mag,const double *phase,
                                     double *dstReal,  double *dstImag,int len))

/*-------------------------------------------------------------------------*/
/*  bPowerSpectr, brPowerSpectr, bMag, brMag, bPhase, brPhase              */
/*                                                                         */
/* Compute the magnitude and phase of complex vector elements.             */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<v,c,z>bMag                                                        */
/* DESCRIPTION:                                                            */
/*   Compute the magnitude of complex vector elements.                     */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   mag       - an output vector to store the magnitude components;       */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbMag,(const SCplx *src,float  *mag,int length))
NSPAPI(void,nspzbMag,(const DCplx *src,double *mag,int length))
NSPAPI(void,nspvbMag,(const WCplx *src,short  *mag,int length,
                        int ScaleMode, int    *ScaleFactor))

/* FUNCTION:                                                               */
/*   nsp<w,s,d>brMag                                                       */
/* DESCRIPTION:                                                            */
/*   Compute the magnitude of complex data formed as two real vectors.     */
/* PARAMETERS:                                                             */
/*   srcReal   - an input vector containing a real part of complex data    */
/*   srcImag   - an input vector containing an imag. part of complex data  */
/*   mag       - an output vector to store the magnitude components;       */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */

NSPAPI(void,nspsbrMag,(const float  *srcReal,const float  *srcImag,
                             float  *mag,          int     length))
NSPAPI(void,nspdbrMag,(const double *srcReal,const double *srcImag,
                             double *mag,          int     length))
NSPAPI(void,nspwbrMag,(const short  *srcReal,const short  *srcImag,
                             short  *mag,          int     length,
                               int   ScaleMode,    int    *ScaleFactor))

/* FUNCTION:                                                               */
/*   nsp<v,c,z>bPhase                                                      */
/* DESCRIPTION:                                                            */
/*   Compute the phase (in radians) of complex vector elements.            */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   phase     - an output vector to store the phase components;           */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */

NSPAPI(void,nspcbPhase,(const SCplx *src,float  *phase,int length))
NSPAPI(void,nspzbPhase,(const DCplx *src,double *phase,int length))
NSPAPI(void,nspvbPhase,(const WCplx *src,short  *phase,int length))

/* FUNCTION:                                                               */
/*   nsp<w,s,d>brPhase                                                     */
/* DESCRIPTION:                                                            */
/*   Compute the phase of complex data formed as two real vectors.         */
/* PARAMETERS:                                                             */
/*   srcReal   - an input vector containing a real part of complex data    */
/*   srcImag   - an input vector containing an imag. part of complex data  */
/*   phase     - an output vector to store the magnitude components;       */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */

NSPAPI(void,nspsbrPhase,(const float  *srcReal,const float *srcImag,
                               float  *phase,        int    length))
NSPAPI(void,nspdbrPhase,(const double *srcReal,const double *srcImag,
                               double *phase,        int     length))
NSPAPI(void,nspwbrPhase,(const short  *srcReal,const short *srcImag,
                               short  *phase,        int     length))

/*-------------------------------------------------------------------------*/
/*  bPowerSpectr, brPowerSpectr                                            */
/*                                                                         */
/* Compute the power spectrum of complex vector.                           */
/*-------------------------------------------------------------------------*/
/* FUNCTION:                                                               */
/*   nsp<v,c,z>bPowerSpectr                                                */
/* DESCRIPTION:                                                            */
/*   Compute the power spectrum of complex vector.                         */
/* PARAMETERS:                                                             */
/*   src       - an input complex vector                                   */
/*   mag       - an output vector to store the power spectrum components;  */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */
NSPAPI(void,nspcbPowerSpectr,(const SCplx *src,float  *spectr,int length))
NSPAPI(void,nspzbPowerSpectr,(const DCplx *src,double *spectr,int length))
NSPAPI(void,nspvbPowerSpectr,(const WCplx *src,short  *spectr,int length,
                                    int    ScaleMode,
                                    int   *ScaleFactor))

/* FUNCTION:                                                               */
/*   nsp<w,s,d>brPowerSpectr                                               */
/* DESCRIPTION:                                                            */
/*   Compute the power spectrum of complex data formed as two real vectors */
/* PARAMETERS:                                                             */
/*   srcReal   - an input vector containing a real part of complex data    */
/*   srcImag   - an input vector containing an imag. part of complex data  */
/*   mag       - an output vector to store the power spectrum components;  */
/*   len       - a length of the arrays;                                   */
/* ERRORS:                                                                 */
/*    1) Some of pointers to input or output data are NULL                 */
/*    2) The length of the arrays is less or equal zero                    */
/*  These errors are registered only if NSP_DEBUG is defined               */
/*                                                                         */

NSPAPI(void,nspsbrPowerSpectr,(const float  *srcReal,const float  *srcImag,
                             float  *spectr,               int     length))
NSPAPI(void,nspdbrPowerSpectr,(const double *srcReal,const double *srcImag,
                             double *spectr,               int     length))
NSPAPI(void,nspwbrPowerSpectr,(const short  *srcReal,const short  *srcImag,
                                     short  *spectr,       int     length,
                                       int   ScaleMode,    int    *ScaleFactor))

#endif                                 /*   _NSPCVRT_H                     */

