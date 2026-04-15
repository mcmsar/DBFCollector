/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1994 Intel Corporation. All Rights Reserved.
//
//  VSS: 
//      $Workfile: NspWarn.h $
//      $Revision: 1 $
//      $Modtime: 3.05.97 19:06 $
//
//  HISTORY:
//
*M*/


#ifndef __NSPWARN_H__
#define __NSPWARN_H__


#if _MSC_VER >= 1000

/* nonstandard extension used : nameless struct/union          */
#pragma warning(disable : 4201)
/* nonstandard extension used : bit field types other than int */
#pragma warning(disable : 4214)
/* unreferenced inline function has been removed               */
#pragma warning(disable : 4514)
/* named type definition in parentheses                        */
#pragma warning(disable : 4115)

#endif /* _MSC_VER >= 1000 */


#endif /* __NSPWARN_H__    */

