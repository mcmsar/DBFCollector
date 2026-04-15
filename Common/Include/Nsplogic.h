/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1998 Intel Corporation. All Rights Reserved.
//
//  VSS:
//    $Workfile:: NspLogic.h                       $
//    $Revision:: 8                                $
//    $Modtime:: 20.08.98 22:34      $Nokeywords::$$
//
//  Purpose: NSP Vector Shift and Logical Operations Header File
//
*M*/


#if !defined (_NSPLOGIC_H_) || defined (_OWN_BLDPCS)
#define  _NSPLOGIC_H_




/*-------------------------------------------------------*/
//              Vector Logical Functions
/*-------------------------------------------------------*/




/*
// bShift: Left or right shift the elements of the vector.
//
//  Parameters:
//        dst   Pointer to the vector dst which stores the results of the
//              left shift  dst << nShift or right shift  dst >> nShift (L/R).
//          n   The number of elements to be operated on.
//       nShift The number of position which vector elements to be shifted on.
*/

NSPAPI(void,nspwbShiftL,(short *dst,int n,int nShift))

NSPAPI(void,nspwbShiftR,(short *dst,int n,int nShift))




/*
//  bAnd1 : ANDs the elements of a vector with a scalar.
//  bAnd2 : ANDs the elements of two vectors.
//  bAnd3 : ANDs the elements of two vectors and stores the result in
//          a third vector.
//
//  Parameters:
//        dst   Pointer to the vector dst which stores the results
//              of the AND operation src AND dst.
//        src   Pointer to the vector to be bitwise ANDed with
//              elements of dst.
//        val   The value to be ANDed with each element of the vector
//              dst.
// srcA, srcB   Pointers to the vectors whose elements are to be
//          n   The number of elements to be operated on.
*/

NSPAPI(void,nspwbAnd1,(short val,short *dst,int n))

NSPAPI(void,nspwbAnd2,(const short *src,short *dst,int n))

NSPAPI(void,nspwbAnd3,(const short *srcA,const short *srcB,short *dst,int n))




/*
//  bXor1 : XORs the elements of a vector with a scalar.
//  bXor2 : XORs the elements of two vectors.
//  bXor3 : XORs the elements of two vectors and stores the result in
//          a third vector.
//
//  Parameters:
//        dst   Pointer to the vector dst which stores the results
//              of the XOR operation src XOR dst.
//        src   Pointer to the vector to be bitwise XORed with
//              elements of dst.
// srcA, srcB   Pointers to the vectors whose elements are to be
//              bitwise XORed.
//        val   The scalar which is XORed with each vector element.
//          n   The number of elements to be operated on.
*/

NSPAPI(void,nspwbXor1,(short val,short *dst,int n))

NSPAPI(void,nspwbXor2,(const short *src,short *dst,int n))

NSPAPI(void,nspwbXor3,(const short *srcA,const short *srcB,short *dst,int n))




/*
//  bOr1  : ORs the elements of a vector with a scalar.
//  bOr2  : ORs the elements of two vectors.
//  bOr3  : ORs the elements of two vectors and stores the result in
//          a third vector.
//
//  Parameters:
//        dst   Pointer to the vector dst which stores the results
//              of the OR operation src OR dst.
//        src   Pointer to the vector to be bitwise ORed with
//              elements of dst.
//        val   The scalar which is ORed with each vector element.
// srcA, srcB   Pointers to the vectors whose elements are to be
//              bitwise ORed.
//          n   The number of elements to be operated on.
*/

NSPAPI(void,nspwbOr1,(short val,short *dst,int n))

NSPAPI(void,nspwbOr2,(const short *src,short *dst,int n))

NSPAPI(void,nspwbOr3,(const short *srcA,const short *srcB,short *dst,int n))




/*
//  bNot : Performs a logical NOT of the elements of a vector
//
//  Parameters:
//        dst   Pointer to the vector dst which stores the results
//              of the logical operation NOT dst.
//          n   The number of elements to be operated on.
*/

NSPAPI(void,nspwbNot,(short *dst,int n))


#endif /* _NSPLOGIC_H_ */

