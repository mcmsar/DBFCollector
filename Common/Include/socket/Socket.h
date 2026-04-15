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

#ifndef __EMS_SOCKET_H__
#define __EMS_SOCKET_H__

#include "socketaddress.h"
#include <string>

//! An EMS socket interface.
class IEMSSocket : public CApiObjBase
{
	public:
		typedef enum tagSocketLevel
		{
			EMSSOCKETLEVEL_UNKNOWN = 0,
			EMSSOCKETLEVEL_SOCKET = 1,
			EMSSOCKETLEVEL_IPPROTO_TCP1 = 2,
			EMSSOCKETLEVEL_NSPROTO_IPX = 3
		} EMSSOCKETLEVEL;

		typedef enum tagSocketOption
		{
			EMSSOCKETOPT_UNKNOWN = 0,
			
			//! Enables transmission and receipt of broadcast messages.  Type = boolean.
			//! For boolean types, use a string value of "true", "false", "yes", or "no".
			EMSSOCKETOPT_BROADCAST = 1,

			//! Enables sockets to delay the acknowledgement of a connection until after the 
			//! WSAAccept (or equivalent) condition function is called.  Type = boolean.
			EMSSOCKETOPT_CONDITIONAL_ACCEPT = 2,

			//! Record debugging information.  Type = boolean.
			EMSSOCKETOPT_DEBUG = 3,

			//! Do not block close waiting for unsent data to be sent.  Type = boolean.
			EMSSOCKETOPT_DONT_LINGER = 4,

			//! Do not route; send directly to interface.  Type = boolean.
			EMSSOCKETOPT_DONT_ROUTE = 5,

			//! Reserved.  Type = integer
			EMSSOCKETOPT_GROUP_PRIORITY = 6,

			//! Send keep alives.  Type = boolean.
			EMSSOCKETOPT_KEEP_ALIVE = 7,

			//! Lingers on a close if unsent data is present.  Type = CEMSLinger.  When setting or getting
			//! the serialized form of CEMSLinger is passed through the interface.
			EMSSOCKETOPT_LINGER = 8,

			//! Receives out of band data in the normal data stream.  Type = boolean.
			EMSSOCKETOPT_OOBINLINE = 9,

			//! Specifies the total per-socket buffer space reserved for receives. 
			//! This is unrelated to SO_MAX_MSG_SIZE or the size of a TCP window.  Type = integer.
			EMSSOCKETOPT_RCVBUF = 10,

			//! Allows the socket to be bound to an address that is already in use.  Type = boolean.
			EMSSOCKETOPT_REUSE_ADDR = 11,

			//! Enables a socket to be bound for exclusive access. 
			//! Does not require administrative privilege. Type = boolean.
			EMSSOCKETOPT_EXCLUSIVE_ADDR_USE = 12,

			//! Specifies the total per-socket buffer space reserved for sends. 
			//! This is unrelated to SO_MAX_MSG_SIZE or the size of a TCP window.
			//! Type = integer.
			EMSSOCKETOPT_SNDBUF = 13,

			//! Updates the accepting socket with the context of the listening socket.
			//! Type = integer.
			EMSSOCKETOPT_SO_UPDATE_ACCEPT_CONTEXT = 14,

			//! This object stores the configuration information for the service provider 
			//! associated with socket s. The exact format of this data structure is service 
			//! provider specific.
			EMSSOCKETOPT_PVD_CONFIG = 15

		} EMSSOCKETOPTION;


		IEMSSocket() {}
		virtual ~IEMSSocket() {}

		//! Accepts an incoming connection.  This may block until a connection attempt arrives.
		//! Blocking vs. non-blocking is dependent upon the options set.  The caller must release
		//! the returned socket.
		virtual IEMSSocket* Accept() = 0;

		//! Associate a local address with a socket.
		virtual void Bind( const CEMSSocketAddress& coAddr ) = 0;

		//! Close the socket.
		virtual void Close() = 0;

		//! Connect to the given address.
		virtual void Connect( const CEMSSocketAddress& coAddr ) = 0;

		//! Place the socket in a state where it is waiting for an incoming connection.
		//! The maximum length of the queue of pending connections can be set.  By default,
		//! the maximum allowable by the underlying service provider will be used.
		virtual void Listen( const int ciBackLog = 0 ) = 0;

		//! Receive data from a connected or bound socket.
		virtual int Receive( char* acBuf, int iLen, int iFlags ) = 0;

		//! Receives a datagram and stores the source address.
		virtual int ReceiveFrom( char* acBuf, int iLen, int iFlags, CEMSSocketAddress& oAddr ) = 0;

		//! Send data over the socket.
		virtual int Send( const char* cacBuf, int iLen, int iFlags ) = 0;

		//! Sends data to a specific destination.
		virtual int SendTo( const char* cacBuf, int iLen, int iFlags, const CEMSSocketAddress& coAddr ) = 0;

		//! Disables sends or receives on the socket.
		virtual void Shutdown( int iFlags ) = 0;

		//! Set a socket option.  Option is input as a string.  See the documentation on
		//! EMSSOCKETOPTION for the appropriate string format.
		virtual void SetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName, 
								const char* cszValue ) = 0;

		//! Get a socket option.  Option is output as a string. See the documentation on
		//! EMSSOCKETOPTION for the appropriate string format.
		virtual std::string GetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName ) = 0;

		//! Determines whether there is data available to be read on this socket.
		virtual bool IsReadData() = 0;

		//! Determines whether there is a connection waiting to be accepted on this socket.
		virtual bool IsConnection() = 0;

		//! Determine the status of the socket.  A parameter of true will return the read status and
		//! a parameter of false will return the write status.  A return value of 1 indicates that it is
		//! ready.
		virtual int Select( const bool cbRead ) = 0;


	public:	// constants
		static const char* ms_cszBooleanTrue;
		static const char* ms_cszBooleanFalse;

};

#endif