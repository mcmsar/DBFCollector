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


#if !defined(AFX_WIN32PORT_H__C8328843_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
#define AFX_WIN32PORT_H__C8328843_583A_11D5_9E1F_9C520CE36739__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <deque>
#include <string>
using namespace std;

#include <windows.h>
#include "EMSTime.h"

#include "rs232.h"
#include "Dcb32.h"
#include "MTDeque.h"

enum Win32PortError {
    WIN32_CHECK_WINDOWS_ERROR = RS232_NEXT_FREE_ERROR,
    WIN32_SETTINGS_FAILURE,
    WIN32_HANDSHAKE_LINE_IN_USE
};


class Win32Port : public RS232  
{
//
// Constructors and destructors
//
public :
    Win32Port( const string &port_name,
               long baud_rate = UNCHANGED,
               char parity = UNCHANGED,
               int word_length = UNCHANGED,
               int stop_bits = UNCHANGED,
               int dtr = SET,
               int rts = SET,
               int xon_xoff = DISABLE,
               int rts_cts = DISABLE,
               int dtr_dsr = DISABLE );

    virtual ~Win32Port();

protected :
    Win32Port() : m_TxQueue( MAX_OUTPUT_BUFFER_SIZE ),
                  m_RxQueue( MAX_INPUT_BUFFER_SIZE ),
				  m_DsQueue( MAX_DISPLAY_BUFFER_SIZE ){}
 
    enum { MAX_INPUT_BUFFER_SIZE = 2048 };
    enum { MAX_OUTPUT_BUFFER_SIZE = 2048 };
	enum { MAX_DISPLAY_BUFFER_SIZE = 512 };
    enum { EV_RINGTE = 0x2000 };


    HANDLE m_hPort;                    // Handle of the port, used everywhere
    int m_iBreakDuration;        
    int first_debug_output_line;
    bool m_bInputThreadReading;
    DWORD m_dwWindowsError;
    long m_hOutputThread;
    long m_hInputThread;

    MTdeque<char> m_TxQueue;               //Outbound data queue
    MTdeque<char> m_RxQueue;               //Incoming data queue
	MTdeque<char> m_DsQueue;			   //Monitoring & display queue

    Dcb32 m_Dcb;                     //Current DCB settings
    DWORD m_dwErrors;                //Cumulative line status error bits
    DWORD m_dwModemStatus;           //Current modem status bits
    //
    // These five Win32 events are all used to communicate requests to the
    // input and output threads.
    //
    HANDLE m_hKillOutputThreadEvent;
    HANDLE m_hKillInputThreadEvent;
    HANDLE m_hWriteRequestEvent;
    HANDLE m_hReadRequestEvent;
    HANDLE m_hBreakRequestEvent;

    RS232Error write_settings();
    void read_settings();
    
    void clear_error( COMSTAT *comstat = 0  );
    RS232Error translate_last_error();
    bool output_worker();
    static void OutputThread( void * arglist );
    static void InputThread( void *arglist );

    //
    // The following are the declarations for the RS232 class members
    // that are implemented by Win32Port.
    //
public :
    RS232Error Set( long baud_rate = UNCHANGED,
                    int parity = UNCHANGED,
                    int word_length = UNCHANGED,
                    int stop_bits = UNCHANGED );
    int Dtr( int setting = UNCHANGED );
    int Rts( int setting = UNCHANGED );
    int TXSpaceFree( void ){ return m_TxQueue.SpaceFree(); }
    int TXSpaceUsed( void ){ return m_TxQueue.SpaceUsed(); }
    int RXSpaceUsed( void ){ return m_RxQueue.SpaceUsed(); }
    int RXSpaceFree( void ){ return m_RxQueue.SpaceFree(); }
    int DtrDsrHandshaking( int setting = UNCHANGED );
    int RtsCtsHandshaking( int setting = UNCHANGED );
    int XonXoffHandshaking( int setting = UNCHANGED );
    int FormatDebugOutput( char *buffer = 0, int line_number = -1 );
    int ParityError( int clear = UNCHANGED );
    int BreakDetect( int clear = UNCHANGED );
    int FramingError( int clear = UNCHANGED );
    int HardwareOverrunError( int clear = UNCHANGED );
    int SoftwareOverrunError( int clear = UNCHANGED );
    int Break( long milliseconds = 300 );
    int Cd( void );
    int Ri( void );
    int Cts( void );
    int Dsr( void );
    int Peek( void *buffer, unsigned int count );
    int FlushRXBuffer( void );
    int FlushTXBuffer( void );
	int ReadDisplay();
    char *ErrorName( int error );

	void check_modem_status( bool first_time, DWORD event_mask );

protected :
    int read_buffer( char *buffer, unsigned int count );
    int write_buffer( char *buffer, unsigned int count = -1 );
    int read_byte( void );
    int write_byte( int c );
//
// The following notification functions all have null implemementations
// that do nothing in Win32Port.
//
    virtual void RxNotify( int byte_count ){};
    virtual void TxNotify(){};
    virtual void ParityErrorNotify(){};
    virtual void FramingErrorNotify(){};
    virtual void HardwareOverrunErrorNotify(){};
    virtual void SoftwareOverrunErrorNotify(){};
    virtual void BreakDetectNotify(){};
    virtual void CtsNotify( bool status ){};
    virtual void DsrNotify( bool status ){};
    virtual void CdNotify( bool status ){};
    virtual void RiNotify( bool status ) {};
};

#endif // !defined(AFX_WIN32PORT_H__C8328843_583A_11D5_9E1F_9C520CE36739__INCLUDED_)
