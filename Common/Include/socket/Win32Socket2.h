/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __WIN32_SOCKET_2_H__
#define __WIN32_SOCKET_2_H__

#include "socket.h"
//#ifndef _USE_RAW_LOG4CXX_
//#include "logclient.h"
//#else
//#include <log4cxx/logger.h>
//#endif
#include "criticalsection.h"
#include <winsock2.h>

//! Windows Sockets 2 (Winsock) implementation.
class CEMSWin32Socket2 : public IEMSSocket 
//#ifndef _USE_RAW_LOG4CXX_
//					, public CEMSLogClient
//#endif
{
	public:
		CEMSWin32Socket2();
		CEMSWin32Socket2( SOCKET socket );
		CEMSWin32Socket2( const CEMSWin32Socket2& x );
		virtual ~CEMSWin32Socket2();

		//! Initialize Winsock.
		static void Init();

		//! Terminates all sockets and unloads Winsock runtime.  This is a process-wide shutdown.
		static void Shutdown();

		//! Create a new socket.  A socket is automatically created when this object is
		//! created.  If the Close command is called then this method must be called to reuse
		//! this object.
		void Create();

		//! Accepts an incoming connection.  This may block until a connection attempt arrives.
		//! Blocking vs. non-blocking is dependent upon the options set.  The caller must release
		//! the returned socket.
		IEMSSocket* Accept();

		//! Associate a local address with a socket.
		void Bind( const CEMSSocketAddress& coAddr );

		//! Associate a local address with a socket.
		void Bind( const CEMSSocketAddress& coAddr, bool& bBound );

		//! Close the socket.
		void Close();

		//! Connect to the given address.
		void Connect( const CEMSSocketAddress& coAddr );

		//! Disconnect the socket, allowing the handle to be reused.
		void Disconnect();

		//! Place the socket in a state where it is waiting for an incoming connection.
		//! The maximum length of the queue of pending connections can be set.  By default,
		//! the maximum allowable by the underlying service provider will be used.
		void Listen( const int ciBackLog = 0 );

		//! Receive data from a connected or bound socket.  Return value is number of bytes received.
		int Receive( char* acBuf, int iLen, int iflags );

		//! Receives a datagram and stores the source address.
		int ReceiveFrom( char* acBuf, int iLen, int iFlags, CEMSSocketAddress& oAddr );

		//! Send data on a connected socket.  Returns the number of bytes sent.
		int Send( const char* cacBuf, int iLen, int iFlags );

		//! Sends data to a specific destination.  Returns the number of bytes sent.
		int SendTo( const char* cacBuf, int iLen, int iFlags, const CEMSSocketAddress& coAddr );

		//! Disables sends or receives on the socket.
		void Shutdown( int iFlags );

		//! Set a socket option.  Option is input as a string.
		void SetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName, 
								const char* cszValue );
		void SetOptionTimeOut( DWORD dwTimeOut);

		//! Get a socket option.  Option is output as a string.  Not currently supported.
		std::string GetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName );

		//! Determines whether there is data available to be read on this socket.
		bool IsReadData();

		//! Determines whether there is a connection waiting to be accepted on this socket.
		bool IsConnection();

		//! Determine the status of the socket.  A parameter of true will return the read status and
		//! a parameter of false will return the write status.  A return value of 1 indicates that it is
		//! ready.
		int Select( const bool cbRead );

	private:
		//! Convert the socket address family to the correct Winsock value.
		short _GetWinsockFamily( const CEMSSocketAddress::EMSADDRFAMILY ceAddrFamily );

		//! Convert EMS flags to Winsock receive flags.
		int _GetWinsockFlags( const int ciEMSFlags );

		//! Convert a socket address class into a Winsock structure.
		sockaddr_in _GetWinsockAddress( const CEMSSocketAddress& coAddr );

		//! Convert EMS shutdown flags to Winsock shutdown flags.
		int _GetWinsockShutdownFlags( const int ciEMSFlags );

		//! Convert EMS Socket option level to Winsock.
		int _GetWinsockLevel( const EMSSOCKETLEVEL ceLevel );

		//! Convert EMS Socket option name to Winsock.
		int _GetWinsockOption( const EMSSOCKETOPTION ceOption );

		//! Convert the value from a string to a native type stored in a byte array.
		//! The caller must delete the returned array.
		void _GetWinsockValue( const EMSSOCKETOPTION ceOptionName, const char* cszValue,
								char*& acVal, int& iValSize );

	public:	// Constants.

		//! Message flag instructing to peek at incoming data.  The data is copied into the input
		//! buffer, but not removed from the input queue.
		static const int ms_ciPEEK;

		//! Message flag instructing to process out of band data.
		static const int ms_ciOOB;

		//! Message flag instructing that the receive request will not complete until the buffer supplied
		//! by the caller is full or the connection has been closed or the connection has been cancelled.
		static const int ms_ciWAITALL;

		//! Message flag specifying that data should not be subject to routing.
		static const int ms_ciDONTROUTE;

		// Flag indicating that a shutdown should be excecuted and all subsequent send operations disallowed.
		static const int ms_ciSEND;

		// Flag indicating that a shutdown should be excecuted and all subsequent receive operations disallowed.
		static const int ms_ciRECEIVE;

		// Flag indicating that a shutdown should be excecuted and all subsequent send and receive operations disallowed.
		static const int ms_ciBOTH;

	private:
		SOCKET	m_Socket;
		bool	m_bLastSendSuccess;
		bool	m_bLastConnectSuccess;

#ifdef _USE_RAW_LOG4CXX_
		log4cxx::LoggerPtr m_pLogger;
#endif

	private:
		static bool ms_bWinSockInitialized;
		static CEMSCriticalSection ms_csWinSock;

		static const BYTE ms_cbyMajorVersion;
		static const BYTE ms_cbyMinorVersion;

};

#endif