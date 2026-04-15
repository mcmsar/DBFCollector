/********************************************************************
*	Module:			Win32Port.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*					 
*			This file contains the class definition for Win32Port. This class
*				implements a version of class RS232 that works with the Win32 serial
*				API. The implementation of this class is in file Win32Port.cpp.
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

	0.0	2001/05/01		Igor Zabarsky	start

********************************************************************/
//#include "stdafx.h"
#include <windows.h>

//#include "MFC Test Antenna.h"
#include "Win32Port.h"

#include <process.h>
#include <cassert>
#include <sstream>
#include <iomanip>
using namespace std;
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
Win32Port::Win32Port( const string &port,
                      long baud_rate   /* = UNCHANGED */,
                      char parity      /* = UNCHANGED */,
                      int word_length  /* = UNCHANGED */,
                      int stop_bits    /* = UNCHANGED */,
                      int dtr          /* = SET       */,
                      int rts          /* = SET       */,
                      int xon_xoff     /* = DISABLE   */,
                      int rts_cts      /* = DISABLE   */,
                      int dtr_dsr      /* = DISABLE   */ )
    : m_TxQueue( MAX_OUTPUT_BUFFER_SIZE ),
      m_RxQueue( MAX_INPUT_BUFFER_SIZE ),
	  m_DsQueue( MAX_DISPLAY_BUFFER_SIZE )
{
//
// Win32Port has to share the debug output with the parent class.
// To determine where our first line starts, we call the
// FormatDebugOutput() function from our parent class.
//
    first_debug_output_line = RS232::FormatDebugOutput();
    debug_line_count = FormatDebugOutput();

    string temp = port;
    if ( temp.substr( 0, 4 ) == "\\\\.\\" )
        temp = temp.substr( 4, string::npos );
    if ( toupper( temp[ 0 ] ) == 'C' &&
         toupper( temp[ 1 ] ) == 'O' &&
         toupper( temp[ 2 ] ) == 'M' ) {
        temp = temp.substr( 3, string::npos );
        port_name = (RS232PortName) ( atoi( temp.c_str() ) - 1 );
    } else
        port_name = (RS232PortName) -1;		//Default port name

    m_hPort = CreateFile( port.c_str(), 
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          0,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                          0 );

    if ( m_hPort != INVALID_HANDLE_VALUE ) 
	{
        m_dwErrors = 0;            //Clear cumulative line status errors
        m_iBreakDuration = 0;    //No break in progress, initialize to 0
        SetLastError( 0 );        //Clear any Win32 error from this thread
        read_settings();           //Read and save current port settings 
        saved_settings = settings; //Only needed because base class dumps 
                                   //the saved settings in debug output

        //Init timeous to ensure our overlapped reads work
        COMMTIMEOUTS timeouts = { 0x01, 0, 0, 0, 0 };
        SetCommTimeouts( m_hPort, &timeouts );
        SetupComm( m_hPort, 500, 500 ); //set buffer sizes
        error_status = RS232_SUCCESS;     //clear current class error

        settings.Dtr = 1;                //Set these five values to their
        settings.Rts = 1;                //default values, the Adjust()
        settings.XonXoff = 0;            //function will modify them if                                    
        settings.RtsCts = 0;            //new values were passed in the args
        settings.DtrDsr = 0;            //to the constructor
        settings.Adjust( baud_rate,	
                         parity,
                         word_length = 8,
                         stop_bits = 1,
                         dtr = FALSE,
                         rts = FALSE,
                         xon_xoff = FALSE,
                         rts_cts = FALSE,
                         dtr_dsr =FALSE );
        //////settings.Adjust( baud_rate = 1200,	//default$$$$$$
        //////                 parity = 'N',
        //////                 word_length = 8,
        //////                 stop_bits = 1,
        //////                 dtr = FALSE,
        //////                 rts = FALSE,
        //////                 xon_xoff = FALSE,
        //////                 rts_cts = FALSE,
        //////                 dtr_dsr =FALSE );

			//Make any modifications needed to the DCB
        error_status = write_settings();    
        if ( error_status != RS232_SUCCESS ) 
		{
            CloseHandle( m_hPort );
            m_hPort = 0;
        } else {
            //
            // Since the port opened properly, we're ready to start the
            // input and output threads. Before they start we create the
            // five Win32 events that will be used to pass requests to
            // the threads. Note that the only argument passed to the
            // thread initialization is a pointer to this. The thread
            // needs that to find all of the data in the Win32Port 
            // object that it will be manipulating.
            //
            m_hKillInputThreadEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
            m_hKillOutputThreadEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

            m_hWriteRequestEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
            m_hReadRequestEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
            m_hBreakRequestEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

            m_hInputThread = _beginthread( InputThread, 0, (void *) this );
            m_hOutputThread = _beginthread( OutputThread, 0, (void *) this );
        }
    } 
    //
    // If the CreateFile() function didn't succeed, we're really in a bad
    // state. Just translate any error into something intellible and
    // exit.
    //
    else
        translate_last_error();
}

Win32Port::~Win32Port()
{
    if ( m_hPort != INVALID_HANDLE_VALUE ) 
	{
        SetEvent( m_hKillOutputThreadEvent );
        SetEvent( m_hKillInputThreadEvent );

        long handles[ 2 ] = { m_hInputThread, m_hOutputThread };
        WaitForMultipleObjects( 2,
                                (HANDLE *) handles,
                                TRUE,
                                INFINITE );
        CloseHandle( m_hPort );
        m_hPort = INVALID_HANDLE_VALUE;

        CloseHandle( m_hKillInputThreadEvent );
        CloseHandle( m_hKillOutputThreadEvent );
        CloseHandle( m_hWriteRequestEvent );
        CloseHandle( m_hReadRequestEvent );
        CloseHandle( m_hBreakRequestEvent );
    }
}

// Since this is a virtual function, we can override it in ours
// derived class and use some object specific data to determine
// how it behaves.
//
int RS232::IdleFunction( void )
{
    return RS232_SUCCESS;
}

//
// The RS232 base class expects a global ReadTime() function that
// returns the current time in milliseconds. This matches up well
// with the GetTickCount() in the Windows API.
//
double ReadTime( void )
{
    return (double)GetTickCount();
}


RS232Error Win32Port::Set( long baud_rate  /* = UNCHANGED */,
                           int parity      /* = UNCHANGED */,
                           int word_length /* = UNCHANGED */,
                           int stop_bits   /* = UNCHANGED */ )
{
    settings.Adjust( baud_rate,
                     parity,
                     word_length,
                     stop_bits,
                     UNCHANGED,
                     UNCHANGED,
                     UNCHANGED,
                     UNCHANGED,
                     UNCHANGED );
		//Make any modifications needed to the DCB
    return write_settings();

}

int Win32Port::Dtr( int setting /* = UNCHANGED */ )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    if ( setting != UNCHANGED ) 
	{
        if ( settings.DtrDsr == 1 )
            return WIN32_HANDSHAKE_LINE_IN_USE;
        settings.Dtr = setting != 0;
        RS232Error error = write_settings();
        if ( error < RS232_SUCCESS )
            return error;
    }
    return settings.Dtr;
}

int Win32Port::Rts( int setting /* = UNCHANGED */ )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    if ( setting != UNCHANGED ) 
	{
        if ( settings.RtsCts == 1 )
            return WIN32_HANDSHAKE_LINE_IN_USE;
        settings.Rts = setting != 0;
        RS232Error error = write_settings();
        if ( error < RS232_SUCCESS )
            return error;
    }
    return settings.Rts;
}

int Win32Port::DtrDsrHandshaking( int setting /* = UNCHANGED */ )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    if ( setting != UNCHANGED ) 
	{
        settings.DtrDsr = setting != 0;
        RS232Error error = write_settings();
        if ( error < RS232_SUCCESS )
            return error;
    }
    return settings.DtrDsr;
}

int Win32Port::RtsCtsHandshaking( int setting )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    if ( setting != UNCHANGED ) 
	{
        settings.RtsCts = setting != 0;
        RS232Error error = write_settings();
        if ( error < RS232_SUCCESS )
            return error;
    }
    return settings.RtsCts;
}

int Win32Port::XonXoffHandshaking( int setting /* = UNCHANGED */ )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    if ( setting != UNCHANGED ) 
	{
        settings.XonXoff = setting != 0;
        RS232Error error = write_settings();
        if ( error < RS232_SUCCESS )
            return error;
    }
    return settings.XonXoff;
}


//************************** MODEM STATUS ROUTINES *************************************
int Win32Port::Cd()
{
    return ( MS_RLSD_ON & m_dwModemStatus ) != 0;
}

int Win32Port::Cts()
{
    return ( MS_CTS_ON & m_dwModemStatus ) != 0;
}

int Win32Port::Dsr()
{
    return ( MS_DSR_ON & m_dwModemStatus ) != 0;
}

// This is particularly valuable for monitoring the RI line, as it may be difficult 
//  to catch an incoming ring in progress.
int Win32Port::Ri()
{
    return ( MS_RING_ON & m_dwModemStatus ) != 0;
}


//************************** LINE STATUS ERROR ROUTINES *********************************
int Win32Port::ParityError( int clear /* = UNCHANGED */ )
{
    int return_value;

    if ( error_status < RS232_SUCCESS )
        return error_status;
    return_value = ( m_dwErrors & CE_RXPARITY ) != 0;
    if ( clear != UNCHANGED && clear != 0 ) 
        m_dwErrors &= ~CE_RXPARITY;
    return return_value;
}

int Win32Port::FramingError( int clear /* = UNCHANGED */ )
{
    int return_value;

    if ( error_status < RS232_SUCCESS )
        return error_status;
    return_value = ( m_dwErrors & CE_FRAME ) != 0;
    if ( clear != UNCHANGED && clear != 0 ) 
        m_dwErrors &= ~CE_FRAME;
    return return_value;
}

int Win32Port::HardwareOverrunError( int clear /* = UNCHANGED */ )
{
    int return_value;

    if ( error_status < RS232_SUCCESS )
        return error_status;
    return_value = ( m_dwErrors & CE_OVERRUN ) != 0;
    if ( clear != UNCHANGED && clear != 0 ) 
        m_dwErrors &= ~CE_OVERRUN;
    return return_value;
}

int Win32Port::BreakDetect( int clear /* = UNCHANGED */ )
{
    int return_value;

    if ( error_status < RS232_SUCCESS )
        return error_status;
    return_value = ( m_dwErrors & CE_BREAK ) != 0;
    if ( clear != UNCHANGED && clear != 0 ) 
        m_dwErrors &= ~CE_BREAK;
    return return_value;
}

//******************** SOFTWARE OVERRUN ERROR ROUTINE ***********************************
int Win32Port::SoftwareOverrunError( int clear /* = UNCHANGED */ )
{
    int return_value;

    if ( error_status < RS232_SUCCESS )
        return error_status;
    return_value = ( m_dwErrors & CE_RXOVER ) != 0;
    if ( clear != UNCHANGED && clear != 0 ) 
        m_dwErrors &= ~CE_RXOVER;
    return return_value;
}
//**************************** END OF ROUTINES ******************************************
//***************************************************************************************


// The output thread is continually checking for the m_hBreakRequestEvent, and when it sees
// it, it faithfully sends the break.
int Win32Port::Break( long milliseconds )
{
    if ( milliseconds > 1000 )
        m_iBreakDuration = 1000;
    else
        m_iBreakDuration = milliseconds;

    SetEvent( m_hBreakRequestEvent );
    return RS232_SUCCESS;
}

int Win32Port::Peek( void *buffer, unsigned int count )
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    ByteCount = m_RxQueue.Peek( (char *) buffer, count );
    ( (char *) buffer )[ ByteCount ] = '\0';
    return RS232_SUCCESS;
}

int Win32Port::FlushRXBuffer()
{
    if ( error_status < RS232_SUCCESS )
        return error_status;

    m_RxQueue.Clear();

    PurgeComm( m_hPort, PURGE_RXCLEAR );
	
    if ( !m_bInputThreadReading )
        SetEvent( m_hReadRequestEvent );
    return RS232_SUCCESS;
}

int Win32Port::FlushTXBuffer()
{
    if ( error_status < RS232_SUCCESS )
        return error_status;
    m_TxQueue.Clear();
    PurgeComm( m_hPort, PURGE_TXCLEAR ); 
    return RS232_SUCCESS;
}

char *Win32Port::ErrorName( int error )
{
    if ( error < RS232_NEXT_FREE_ERROR && error >= RS232_ERROR )
        return RS232::ErrorName( error );
    if ( error < RS232_NEXT_FREE_WARNING && error >= RS232_WARNING )
        return RS232::ErrorName( error );
    if ( error >= RS232_SUCCESS )
        return RS232::ErrorName( error );
    switch ( error ) {
        case WIN32_CHECK_WINDOWS_ERROR :
            return "Check Windows error code in m_dwWindowsError";
        case WIN32_SETTINGS_FAILURE :
            return "Failure to set port parameters";
        case WIN32_HANDSHAKE_LINE_IN_USE :
            return "Handshake line is already in use";
        default :
            return( "Undefined error" );
    }
}

static string DisplayChar( int val ) {
    char temp[ 2 ] = { val, 0 };
    if ( val >= ' ' && val <= 0x73 )
        return string( temp );
    ostringstream s;
    s << "0x" << setw( 2 ) << setfill( '0' ) << hex << val;
    return s.str();
}

int Win32Port::FormatDebugOutput( char *buffer, int line_number )
{
    char *StopBits[ 4 ] = {
        "1",
        "1.5",
        "2",
        "???"
    };
    char *DtrControl[ 4 ] = {
        "DISABLE",
        "ENABLE",
        "HANDSHAKE",
        "???"
    };
    char *RtsControl[ 4 ] = {
        "DISABLE",
        "ENABLE",
        "HANDSHAKE",
        "TOGGLE"
    };


    if ( buffer == 0 )
        return( first_debug_output_line +  9 );

    if ( line_number < first_debug_output_line )
        return RS232::FormatDebugOutput( buffer, line_number );

    switch ( line_number - first_debug_output_line ) 
	{
    case 0 :
        sprintf( buffer, 
                 "DCB-> Baud: %6d  " 
                 "fBinary: %1d  "
                 "fParity: %1d  "
                 "fOutxCtsFlow: %1d  "
                 "fOutxDsrFlow: %1d",
                 m_Dcb.BaudRate,
                 m_Dcb.fBinary,
                 m_Dcb.fParity,
                 m_Dcb.fOutxCtsFlow,
                 m_Dcb.fOutxDsrFlow );
        break;
    case 1 :
        sprintf( buffer, 
                 "DCB-> fDtrControl: %9s  "
                 "fDsrSensitivity: %1d  "
                 "fTXContinueOnXoff: %1d  ",
                 DtrControl[ m_Dcb.fDtrControl ],
                 m_Dcb.fDsrSensitivity,
                 m_Dcb.fTXContinueOnXoff );
        break;
    case 2 :
        sprintf( buffer, 
                 "DCB-> fOutX: %1d  "
                 "fInX: %1d  "
                 "fErrorChar: %1d  "
                 "fNull: %1d  "
                 "fRtsControl: %9s",
                 m_Dcb.fOutX,
                 m_Dcb.fInX,
                 m_Dcb.fErrorChar,
                 m_Dcb.fNull,
                 RtsControl[ m_Dcb.fRtsControl ] );
        break;
    case 3 :
        sprintf( buffer, 
                 "DCB-> fAbortOnError: %1d  "
                 "XonLim: %4d  "
                 "XoffLim: %4d  "
                 "ByteSize: %1d  "
                 "Parity: %1c ",
                 m_Dcb.fAbortOnError,
                 m_Dcb.XonLim,
                 m_Dcb.XoffLim,
                 m_Dcb.ByteSize,
                 "NOEMS"[ m_Dcb.Parity] );
        break;
    case 4 :
        sprintf( buffer,
                 "DCB-> StopBits: %3s  "
                 "XonChar: %s  "
                 "XoffChar: %s  "
                 "ErrorChar: %s  ",
                 StopBits[ m_Dcb.StopBits & 3 ],
                 DisplayChar( m_Dcb.XonChar ).c_str(),
                 DisplayChar( m_Dcb.XoffChar ).c_str(),
                 DisplayChar( m_Dcb.ErrorChar ).c_str() );
        break;
    case 5 :
        sprintf( buffer,
                 "DCB-> EofChar: %s  "
                 "EvtChar: %s  ",
                 DisplayChar( m_Dcb.EofChar ).c_str(),
                 DisplayChar( m_Dcb.EvtChar ).c_str() );
        break;
    case 6 : 
    {
        COMSTAT comstat;
        clear_error( &comstat );
        sprintf( buffer,
                 "COMSTAT-> fCtsHold: %1d  "
                 "fDsrHold: %1d  "
                 "fRlsHold: %1d  "
                 "fXoffHold: %1d  "
                 "fXoffSent: %1d",
                 comstat.fCtsHold,
                 comstat.fDsrHold,
                 comstat.fRlsdHold,
                 comstat.fXoffHold,
                 comstat.fXoffSent );
        break;
    }
    case 7 :
    {
        COMSTAT comstat;
        clear_error( &comstat );
        sprintf( buffer,
                 "COMSTAT-> fEof: %1d  "
                 "fTxim: %1d  "
                 "cbInQueue: %5d  "
                 "cbOutQueue: %5d",
                 comstat.fEof,
                 comstat.fTxim,
                 comstat.cbInQue,
                 comstat.cbOutQue );
        break;
    }
    case 8 :
        sprintf( buffer, 
                 "CE_-> BREAK: %1d  "
                 "FRAME: %1d  "
                 "OVERRUN: %1d  "
                 "RXOVER: %1d  "
                 "RXPARITY: %1d  "
                 "TXFULL: %1d",
                 ( m_dwErrors & CE_BREAK ) ? 1 : 0,
                 ( m_dwErrors & CE_FRAME ) ? 1 : 0,
                 ( m_dwErrors & CE_OVERRUN ) ? 1 : 0,
                 ( m_dwErrors & CE_RXOVER ) ? 1 : 0,
                 ( m_dwErrors & CE_RXPARITY ) ? 1 : 0,
                 ( m_dwErrors & CE_TXFULL ) ? 1 : 0 );
        break;
    default :
        return RS232_ILLEGAL_LINE_NUMBER;
    }
    return RS232_SUCCESS;
}

int Win32Port::write_byte( int c )
{
    if ( error_status < 0 )
        return error_status;
    if ( m_TxQueue.SpaceFree() < 0 )
        return RS232_TIMEOUT;
    m_TxQueue.Insert( c );
    ::SetEvent( m_hWriteRequestEvent );
    return RS232_SUCCESS;
}

int Win32Port::write_buffer( char *buffer, unsigned int count )
{
    ByteCount = 0;
    if ( error_status < 0 )
        return error_status;
    ByteCount = m_TxQueue.Insert( buffer, count );
    ::SetEvent( m_hWriteRequestEvent );
    if ( ByteCount == count )
        return RS232_SUCCESS;
    else
        return RS232_TIMEOUT;
}

int Win32Port::read_byte( void )
{
    if ( error_status < 0 )
        return error_status;
    int ret_val = m_RxQueue.Extract();
    if ( !m_bInputThreadReading )
        SetEvent( m_hReadRequestEvent );
    if ( ret_val < 0 )
        return RS232_TIMEOUT;
    else
        return ret_val;
}

int Win32Port::ReadDisplay()
{
	return m_DsQueue.Extract();
}

int Win32Port::read_buffer( char *buffer, unsigned int count )
{
    ByteCount = 0;
    if ( error_status < 0 )
        return error_status;
    ByteCount = m_RxQueue.Extract( buffer, count );
    buffer[ ByteCount ] = '\0';
    if ( !m_bInputThreadReading )
        SetEvent( m_hReadRequestEvent );
    if ( ByteCount < count )
        return RS232_TIMEOUT;
    else
        return RS232_SUCCESS;
}


// This function is called from both the FormatDebugOutput() routine as well as inside
// the receive thread. This opens the window for at least the 
// possibility of missing an incoming error if FormatDebugOutput()
// is called while an incoming error is seen. This could be solved
// by adding a critical section, but since FormatDebugOutput()
// is usually only called during testing and diagnostics, I didn't
// add it to this routine.
//
void Win32Port::clear_error( COMSTAT *comstat /* = 0 */ )
{
    COMSTAT c;
    if ( comstat == 0 )
        comstat = &c;
    DWORD errors;
    ClearCommError( m_hPort, &errors, comstat );
    m_dwErrors |= errors;
    if ( errors & CE_BREAK )
        BreakDetectNotify();
    if ( errors & CE_FRAME )
        FramingErrorNotify();
    if ( errors & CE_OVERRUN )
        HardwareOverrunErrorNotify();
    if ( errors & CE_RXPARITY )
        ParityErrorNotify();
    if ( errors & CE_RXOVER )
        SoftwareOverrunErrorNotify();
}

RS232Error Win32Port::write_settings()
{
    RS232Error error = RS232_SUCCESS;
    m_Dcb.SetBaudRate( settings.BaudRate );
    m_Dcb.SetParity( settings.Parity, error );
    m_Dcb.SetWordLength( settings.WordLength, error );
    m_Dcb.SetStopBits( settings.StopBits, error );
    //
    // Even though we think that we're setting up DTR and RTS,
    // we might not actually be pulling it off. If one of the
    // two hardware handshaking protocols is enabled, it will
    // wipe out the DCB setting for the corresponding control
    // line and change it to use handshaking instead.
    //
    m_Dcb.SetDtr( settings.Dtr ); 
    m_Dcb.SetRts( settings.Rts );
    m_Dcb.SetXonXoff( settings.XonXoff );
    m_Dcb.SetRtsCts( settings.RtsCts );
    m_Dcb.SetDtrDsr( settings.DtrDsr );
    SetCommState( m_hPort, &m_Dcb );
    if ( GetLastError() != 0 ) {
        if ( GetLastError() == ERROR_INVALID_HANDLE )
            return (RS232Error) WIN32_SETTINGS_FAILURE;
        else {
            m_dwWindowsError = GetLastError();
            return (RS232Error) WIN32_CHECK_WINDOWS_ERROR;
        }
    }
    return error;
}

void Win32Port::read_settings()
{
    DCB dcb;
    GetCommState( m_hPort, &dcb );
    settings.BaudRate = dcb.BaudRate;
    if ( !dcb.fParity )
        settings.Parity = 'N';
    else 
        switch ( dcb.Parity ) {
        case EVENPARITY  : settings.Parity = 'E'; break;
        case ODDPARITY   : settings.Parity = 'O'; break;
        case MARKPARITY  : settings.Parity = 'M'; break;
        case SPACEPARITY : settings.Parity = 'S'; break;
        default          : settings.Parity = 'N'; break;
        }
    settings.WordLength = dcb.ByteSize;
    if ( dcb.StopBits == ONESTOPBIT )
        settings.StopBits = 1;
    else
        settings.StopBits = 2;
    if ( dcb.fDtrControl == DTR_CONTROL_DISABLE )
        settings.Dtr = 0;
    else
        settings.Dtr = 1;
    if ( dcb.fRtsControl == RTS_CONTROL_DISABLE )
        settings.Rts = 0;
    else
        settings.Rts = 1;
    if ( dcb.fOutX || dcb.fInX )
        settings.XonXoff = 1;
    else
        settings.XonXoff = 0;
    if ( dcb.fOutxCtsFlow || dcb.fRtsControl == RTS_CONTROL_HANDSHAKE )
        settings.RtsCts = 1;
    else
        settings.RtsCts = 0;
    if ( dcb.fOutxDsrFlow || dcb.fDtrControl == DTR_CONTROL_HANDSHAKE )
        settings.DtrDsr = 1;
    else
        settings.DtrDsr = 0;
}

RS232Error Win32Port::translate_last_error()
{
    switch ( m_dwWindowsError = GetLastError() )
    {
    case ERROR_ACCESS_DENIED  : return error_status = RS232_PORT_IN_USE;
    case ERROR_FILE_NOT_FOUND : return error_status = RS232_PORT_NOT_FOUND;
    }
    return error_status = (RS232Error) WIN32_CHECK_WINDOWS_ERROR;
}

// Four potential events can be signaled. The events are
//  1) a kill message fromt the main thread, which comes when
// the port is being closed, 
//  2) incoming data that has been read in from
// the serial port,
//  3) a line status error or modem status change on the
// serial port, 
//  4) a read request message, which indicates that some
// room may have been opened up in the input buffer.
//
void Win32Port::InputThread( void * arglist )
{
    Win32Port *port = (Win32Port *) arglist;


	// This guarantees that the notification functions for the modem status will be called
    //  once with the initial values, which will often be a useful thing for the calling 
    //  program.
    //
    port->check_modem_status( true, 0 );
    port->clear_error();

    OVERLAPPED AsyncReadInfo = { 0 };
    OVERLAPPED AsyncStatusInfo = { 0 };
    AsyncReadInfo.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    AsyncStatusInfo.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    assert( AsyncReadInfo.hEvent );
    assert( AsyncStatusInfo.hEvent );
    //
    // This word is used as an argument to WaitForCommEvent()
    //
    DWORD dwCommEvent;

    bool waiting_on_status = false;
    port->m_bInputThreadReading = false;

    HANDLE handles[ 4 ] = { port->m_hKillInputThreadEvent,
                            AsyncReadInfo.hEvent,
                            AsyncStatusInfo.hEvent,
                            port->m_hReadRequestEvent };

    SetCommMask( port->m_hPort, 
                 EV_BREAK | EV_CTS  | EV_DSR   | EV_RXCHAR |
                 EV_ERR   | EV_RING | EV_RLSD  | EV_RINGTE );




    //
    // This is the main loop. It executes until the done flag is set,
    // which won't happen until the kill thread message is sent.
    for ( bool done = false ; !done ; ) 
	{
        //
        // Under normal conditions this loop should have a read action
        // in progress at all times. The only time this won't be true
        // is when there is no room in the RX queue. I have a member
        // in class Win32Port that defines whether or not a read is
        // presently active. This section of code just makes sure that
        // if no read is currently in progress, I do my best to get
        // one started.
        //
        int bytes_to_read = 0;
        char read_buffer[ 256 ];
        DWORD dwBytesRead;
        if ( !port->m_bInputThreadReading ) 
		{
            bytes_to_read = port->m_RxQueue.SpaceFree();
            if ( bytes_to_read > 256 )
                bytes_to_read = 256;

			// If there isn't any data in the buffer, ReadFile() can return immediately
            //  with the actual input in progress but not complete. If there was enough data
            //  in the input stream already to fulfill the read, 
            //  it might return with data present.
            //
            if ( bytes_to_read > 0 ) 
			{
                if ( !ReadFile( port->m_hPort, read_buffer, bytes_to_read, &dwBytesRead, 
					&AsyncReadInfo ) )
                { 
                    //  Using overlapped I/O.
                    port->m_bInputThreadReading = true;
                } else 
				{    
					// Returned immediatly
                    if ( dwBytesRead ) 
					{
                        port->m_RxQueue.Insert( read_buffer, dwBytesRead );
						port->m_DsQueue.DisplayIn( read_buffer, dwBytesRead );
                        port->RxNotify( dwBytesRead );
                    }
                }
            } else 
			{
				// No room in the RX queue
                ResetEvent( AsyncReadInfo.hEvent );
            }
        }


        if ( !waiting_on_status  ) 
		{
            if ( !WaitCommEvent( port->m_hPort, 
                                 &dwCommEvent, 
                                 &AsyncStatusInfo ) ) 
			{
                // ERROR_IO_PENDING, which means that no events are currently queued
                waiting_on_status = true;
            } else 
			{ 
                // Returned immediately, 
                port->check_modem_status( false, dwCommEvent );
                port->clear_error();
            }
        }

			//Ready to wait if neaded
        if ( waiting_on_status && 
           ( port->m_bInputThreadReading || bytes_to_read == 0 ) ) 
		{
            DWORD result = WaitForMultipleObjects( 4,
                                                   handles,
                                                   FALSE,
                                                   INFINITE );


            switch ( result ) 
			{
            case 0 : // kill thread event
                done = true; 
                break;  
            case 1 : //Read event
                if ( GetOverlappedResult( port->m_hPort, 
                                          &AsyncReadInfo, 
                                          &dwBytesRead, 
                                          FALSE ) ) 
                {      // read completed successfully
                    if ( dwBytesRead ) {
                        port->m_RxQueue.Insert( read_buffer, dwBytesRead );
						port->m_DsQueue.DisplayIn( read_buffer, dwBytesRead );
                        port->RxNotify( dwBytesRead );
                    }
                }
                port->m_bInputThreadReading = false;
                break;
            case 2 : 
				{ /* Status event */ 
                DWORD dwOverlappedResult;
                if ( GetOverlappedResult( port->m_hPort, 
                                          &AsyncStatusInfo, 
                                          &dwOverlappedResult, 
                                          FALSE ) ) 
                {
                    port->check_modem_status( false, dwCommEvent );
                    port->clear_error();
                }
                waiting_on_status = false;
                break;
            }
            case 3 : //make new call to ReadFile() by user request
                break;
            default ://bad case
                assert( false );
            }
        }
    }

    CloseHandle( AsyncReadInfo.hEvent );
    CloseHandle( AsyncStatusInfo.hEvent );
}

//
// The output thread will never wait for output to be complete.
void Win32Port::OutputThread(void * arglist)
{
    Win32Port *port = (Win32Port *) arglist;

    HANDLE handles[ 3 ] = { port->m_hKillOutputThreadEvent,
                            port->m_hWriteRequestEvent,
                            port->m_hBreakRequestEvent };
    port->TxNotify();
    for ( bool done = false ; !done ; ) 
	{
        switch ( WaitForMultipleObjects( 3, handles, FALSE, INFINITE ) ) 
		{
        case 0 : //m_hKillOutputThreadEvent
            done = true; 
            break;
        case 1 : //m_hWriteRequestEvent
            done = port->output_worker();
            break;
        case 2 : //m_hBreakRequestEvent
            SetCommBreak( port->m_hPort );
            SleepEx( port->m_iBreakDuration, FALSE );
            ClearCommBreak( port->m_hPort );
            break;
        //
        // This can only be bad!
        //
        default :
            assert( false );
            break;
        }
    }
}

//
// When a request comes in to transmit some data, this routine is called.
bool Win32Port::output_worker()
{
    OVERLAPPED AsyncWriteInfo = { 0 };
    AsyncWriteInfo.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    assert( AsyncWriteInfo.hEvent );
    HANDLE handles[ 2 ] = { m_hKillOutputThreadEvent,
                            AsyncWriteInfo.hEvent };
    bool killed = false;
    for ( bool done = false ; !done; ) 
	{
        char data[ 500 ];
        int count = m_TxQueue.Extract( data, 500 );
		TxNotify();
        if ( count == 0 ) 
            break;
        DWORD result_count;
        if ( !WriteFile( m_hPort, 
                         data, 
                         count, 
                         &result_count, 
                         &AsyncWriteInfo ) ) 
		{
            if ( GetLastError() == ERROR_IO_PENDING ) 
			{
                switch ( WaitForMultipleObjects( 2, handles, FALSE, INFINITE ) ) 
				{
                case 0 : //m_hKillOutputThreadEvent
                    done = true; 
                    killed = true;
                    PurgeComm( m_hPort, PURGE_TXABORT ); 
                    break;
                case 1 : //AsyncWriteInfo.hEvent
                    if ( !GetOverlappedResult( m_hPort, 
                                               &AsyncWriteInfo, 
                                               &result_count, 
                                               FALSE ) ||
                          result_count != count ) 
					{
                        if ( GetLastError() == ERROR_IO_PENDING )
                            clear_error();
                        else
                            translate_last_error();
                        done = true;                        
                    } 
                    break;
                default :
                    assert( false );
                }
            } else {
              translate_last_error();
              done = true;                        
            }
        } else {
            if ( result_count != count ) 
			{
                translate_last_error();
                done = true;
            }
        }
                         
    }

    CloseHandle( AsyncWriteInfo.hEvent );
    return killed;
}

//
// When an asynchronous event is processed from the call to 
// WaitCommEvent(), We check each of the modemstatus lines to see who
// changed, then call the notification functions to let the
// calling process know what happened.
//
void Win32Port::check_modem_status(bool first_time, DWORD event_mask )
{
    if ( !GetCommModemStatus( m_hPort, &m_dwModemStatus ) )
        assert( false );

    if ( first_time ) //report everything
    {
        CtsNotify( ( MS_CTS_ON & m_dwModemStatus ) != 0 );
        DsrNotify( ( MS_DSR_ON & m_dwModemStatus ) != 0 );
        CdNotify( ( MS_RLSD_ON & m_dwModemStatus ) != 0 );
        RiNotify( 0 );
    } else 
	{ //Only report events
        if ( event_mask & EV_CTS )
            CtsNotify( ( MS_CTS_ON & m_dwModemStatus ) != 0 );
        if ( event_mask & EV_DSR )
            DsrNotify( ( MS_DSR_ON & m_dwModemStatus ) != 0 );
        if ( event_mask & EV_RLSD )
            CdNotify( ( MS_RLSD_ON & m_dwModemStatus ) != 0 );
        if ( event_mask & ( EV_RING | EV_RINGTE ) )
            if ( ( MS_RING_ON & m_dwModemStatus ) == 0 )
            RiNotify( 0 );
    }
}

// EOF Win32Port.cpp

