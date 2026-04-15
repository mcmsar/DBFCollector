/********************************************************************
*	Module:			DCB32.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*			This file contains the class definition for Dcb32
*				class. It exists only because I can put in a
*				few convenience functions that are used to initialize
*				members of the DCB. They make code elsewhere in the program
*				a lot less cluttered.
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth			Changes
	===	====			====			=======

	0.0	2001/04/26		Igor Zabarsky	start

********************************************************************/


#if !defined(AFX_DCB32_H__C8328844_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
#define AFX_DCB32_H__C8328844_583A_11D5_9E1F_9C520CE36739__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

struct Dcb32 : public DCB
{
    Dcb32();
    void SetBaudRate( int rate );
    void SetParity( int parity, RS232Error &error );
    void SetWordLength( int word_length, RS232Error &error );
    void SetStopBits( int stop_bits, RS232Error &error );
    void SetDtr( int value );
    void SetRts( int value );
    void SetXonXoff( int value );
    void SetDtrDsr( int value );
    void SetRtsCts( int value );
};

#endif // !defined(AFX_DCB32_H__C8328844_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
