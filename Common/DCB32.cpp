/********************************************************************
*	Module:			DCB32.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*			The m_Dcb member of the Win32Port class is used to hold most
*				of the information regarding the current state of the port.
*				The only reason that the DCB was encapsulated into this
*				class was simply to make the Win32Port code more readable.
*				The Win32Port code becomes more readable because a lot of
*				the initialization code for the various members is offloaded
*				to the Dcb class. Note that this class is derived from the
*				DCB structure defined in the WIN32 header files, so any
*				function that takes a pointer to a DCB can take a pointer to
*				one of these structures as well.
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


//#include "stdafx.h"
//#include "MFC Test Antenna.h"

#include <cctype>
#include "rs232.h"

#include "DCB32.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
Dcb32::Dcb32()
{
    DCBlength = sizeof( DCB );			//Windows API expects this
    BaudRate = 9600;					//Default baud rate
    fBinary = TRUE;						//Under Win32 this should always be true
    fParity = FALSE;					//Our default is no parity
    fOutxCtsFlow = FALSE;				//Default is no RTS/CTS flow control
    fOutxDsrFlow = FALSE;				//Default is no DTR/DSR flow control
    fDtrControl = DTR_CONTROL_DISABLE;	//No DTR by default
    fDsrSensitivity = FALSE;			//Ignore incoming DSR by default
    fTXContinueOnXoff = FALSE;			//No special action on Xoff by default
    fOutX = FALSE;						//No outbound XON/XOFF handshaking
    fInX = FALSE;						//No incoming XON/XOFF handshaking
    fErrorChar = FALSE;					//No special character on line errors
    fNull = FALSE;						//No null detection
    fRtsControl = RTS_CONTROL_ENABLE;	//Assert RTS by default
    fAbortOnError = TRUE;				//Always respond to errors
    fDummy2 = 0;
    wReserved = 0;
    XonLim = 128;						//Issue XON when 128 characters left
    XoffLim = 128;						//Issue XOFF when space left = 128
    ByteSize = 8;						//Default word size
    Parity = NOPARITY;					//Default is no parity
    StopBits = ONESTOPBIT;				//Default is one stop bit
    XonChar = 0x11;						//Default XON is ^Q
    XoffChar = 0x13;					//Default XOFF is ^S
    ErrorChar = 0;						//Not using error char, don't care
    EofChar = 0;						//Not using EOF char, don't care
    EvtChar = 0;						//Not using event char, don't care
}

void Dcb32::SetBaudRate( int rate )
{
    if ( rate != UNCHANGED )
        BaudRate = rate;
}

void Dcb32::SetParity( int parity, RS232Error &error )
{
    switch ( toupper( parity ) ) 
	{
    case 'N'       : fParity = FALSE; Parity = NOPARITY;    break;
    case 'E'       : fParity = TRUE;  Parity = EVENPARITY;  break;
    case 'O'       : fParity = TRUE;  Parity = ODDPARITY;   break;
    case 'M'       : fParity = TRUE;  Parity = MARKPARITY;  break;
    case 'S'       : fParity = TRUE;  Parity = SPACEPARITY; break;
    case UNCHANGED :                              break;
    default        : error = RS232_ILLEGAL_PARITY_SETTING;
    }
}

//
// The word length setting is trivial.
//
void Dcb32::SetWordLength( int word_length, RS232Error &error )
{
    switch ( word_length ) 
	{
    case 5         : ByteSize = 5; break;
    case 6         : ByteSize = 6; break;
    case 7         : ByteSize = 7; break;
    case 8         : ByteSize = 8; break;
    case UNCHANGED : break;
    default        : error = RS232_ILLEGAL_WORD_LENGTH;
    }
}

//
// Setting the number of stop bits is nice and simple. I don't
// take into account the possibility of 1.5 stop bits in this
// function, as it really serves no practical purpose.
//
void Dcb32::SetStopBits( int stop_bits, RS232Error &error )
{
    switch ( stop_bits ) 
	{
    case 1              : StopBits = ONESTOPBIT;  break;
    case 2              : StopBits = TWOSTOPBITS; break;
    case UNCHANGED    :                            break;
    default           : error = RS232_ILLEGAL_STOP_BITS; break;
    }
}

void Dcb32::SetDtr( int value )
{
    if ( value == UNCHANGED )
        return;
    else if ( value )
        fDtrControl = DTR_CONTROL_ENABLE;
    else
        fDtrControl = DTR_CONTROL_DISABLE;
}

void Dcb32::SetRts( int value )
{
    if ( value == UNCHANGED )
        return;
    else if ( value )
        fRtsControl = RTS_CONTROL_ENABLE;
    else
        fRtsControl = RTS_CONTROL_DISABLE;
}

void Dcb32::SetXonXoff( int value )
{
    if ( value != UNCHANGED ) 
	{
        if ( value ) 
		{
            fOutX = TRUE;
            fInX = TRUE;
        } else {
            fOutX = FALSE;
            fInX = FALSE;
        }
    }
}

void Dcb32::SetDtrDsr( int value )
{
    if ( value != UNCHANGED ) 
	{
        if ( value ) 
		{
            fDtrControl = DTR_CONTROL_HANDSHAKE;
            fOutxDsrFlow = TRUE;
        } else
            fOutxDsrFlow = FALSE;
    }
}

void Dcb32::SetRtsCts( int value )
{
    if ( value != UNCHANGED ) 
	{
        if ( value ) 
		{
            fRtsControl = RTS_CONTROL_HANDSHAKE;
            fOutxCtsFlow = TRUE;
        } else
            fOutxCtsFlow = FALSE;
    }
}

