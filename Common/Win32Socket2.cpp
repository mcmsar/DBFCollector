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
#ifdef WIN32
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#endif

#include "socket/win32socket2.h"
#include "socket/linger.h"
#include "emsexcpt.h"
#include "convutility.h"
#include "emserrormsgs.h"
#include "LogHelper.h"

bool CEMSWin32Socket2::ms_bWinSockInitialized = false;
CEMSCriticalSection CEMSWin32Socket2::ms_csWinSock;

// Support Winsock 2.0 and above 
const BYTE CEMSWin32Socket2::ms_cbyMajorVersion = 2;
const BYTE CEMSWin32Socket2::ms_cbyMinorVersion = 0;

// Message flags.
const int CEMSWin32Socket2::ms_ciPEEK = 0x01;
const int CEMSWin32Socket2::ms_ciOOB = 0x02;
const int CEMSWin32Socket2::ms_ciWAITALL = 0x04;
const int CEMSWin32Socket2::ms_ciDONTROUTE = 0x08;

// Shutdown flags
const int CEMSWin32Socket2::ms_ciRECEIVE = 0x00;
const int CEMSWin32Socket2::ms_ciSEND = 0x01;
const int CEMSWin32Socket2::ms_ciBOTH = 0x02;

CEMSWin32Socket2::CEMSWin32Socket2() : 
//#ifndef _USE_RAW_LOG4CXX_
//CEMSLogClient(L"CEMSWin32Socket2"), 
//#endif
m_Socket( INVALID_SOCKET ), m_bLastSendSuccess(true), m_bLastConnectSuccess(true)
{

#ifdef _USE_RAW_LOG4CXX_
	m_pLogger = log4cxx::Logger::getLogger( "Win32Socket2" );
#endif

	Init();

	// Assuming TCP/IP here.  Could allow user to specify.
	m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if ( INVALID_SOCKET == m_Socket ) 
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );

#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR );
#else
		LOG4CXX_ERROR( m_pLogger, "Error creating a socket.");
#endif
	}
}

	
CEMSWin32Socket2::CEMSWin32Socket2( SOCKET socket ) : 
#ifndef _USE_RAW_LOG4CXX_
//CEMSLogClient(L"CEMSWin32Socket2"), 
#endif
m_bLastSendSuccess( true ), m_bLastConnectSuccess( true )
{
	m_Socket = socket;

#ifdef _USE_RAW_LOG4CXX_
	m_pLogger = log4cxx::Logger::getLogger( "Win32Socket2" );
#endif
}

CEMSWin32Socket2::CEMSWin32Socket2( const CEMSWin32Socket2& x ) : 
#ifndef _USE_RAW_LOG4CXX_
//CEMSLogClient(L"CEMSWin32Socket2"), 
#endif
m_bLastSendSuccess( x.m_bLastSendSuccess ),
										m_bLastConnectSuccess( x.m_bLastConnectSuccess )
{
#ifdef _USE_RAW_LOG4CXX_
	m_pLogger = log4cxx::Logger::getLogger( "Win32Socket2" );
#endif

	// Don't copy the m_Socket member.
	Init();

	// Assuming TCP/IP here.  Could allow user to specify.
	m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if ( INVALID_SOCKET == m_Socket ) 
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
		//LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Error creating a socket.");
#endif
	}
}

CEMSWin32Socket2::~CEMSWin32Socket2()
{
	Close();
}

void
CEMSWin32Socket2::Init()
{
	try
	{
		ms_csWinSock.Enter();

		if( !ms_bWinSockInitialized )
		{
			WSADATA wsaData;

			int iResult = WSAStartup( MAKEWORD(ms_cbyMajorVersion,ms_cbyMinorVersion), &wsaData );
			if ( iResult != NO_ERROR )
			{
#ifndef _USE_RAW_LOG4CXX_
//				CEMSLogClient oClient( "CEMSWin32Socket2" );
#else
				log4cxx::LoggerPtr pLogger = log4cxx::Logger::getLogger( "Win32Socket2" );
#endif

				CEMSLogMsgParam oParam;
				oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//				oClient.LogMsg( EMSLogMsgAlarm, EMS_SOCKET_STARTUP_ERROR, oParam,  __FILE__, __LINE__ );
				CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_STARTUP_ERROR, oParam );
#else
				LOG4CXX_ERROR( pLogger, "Error starting socket runtime with code " << WSAGetLastError() << "." );
#endif
			}
			else
			{
				ms_bWinSockInitialized = true;
			}
		}

		ms_csWinSock.Leave();
	}
	catch( ... )
	{
		ms_csWinSock.Leave();

		throw;
	}
}

void
CEMSWin32Socket2::Shutdown()
{
	try
	{
		ms_csWinSock.Enter();

		WSACleanup();

		ms_csWinSock.Leave();
	}
	catch( ... )
	{
		ms_csWinSock.Leave();

		throw;
	}
}

void
CEMSWin32Socket2::Create()
{
	// Assuming TCP/IP here.  Could allow user to specify.
	m_Socket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if ( INVALID_SOCKET == m_Socket ) 
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CREATE_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Error creating a socket with code " << WSAGetLastError() << "." );
#endif
	}
}

IEMSSocket* 
CEMSWin32Socket2::Accept()
{

	CEMSWin32Socket2* pRet = 0;

	try
	{
		if( INVALID_SOCKET == m_Socket )
		{
			throw CEMSException( EMS_NOT_INITIALIZED );
		}

		sockaddr_in addrFrom;
		memset( &addrFrom, 0, sizeof(addrFrom) );

		int iLen = 0;

		//SOCKET socket = accept( m_Socket, (SOCKADDR*) &addrFrom, &iLen );
		SOCKET socket = accept( m_Socket, NULL, NULL );

		if( INVALID_SOCKET != socket )
		{
			CEMSLogMsgParam oParam;
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgDebug, EMS_SOCKET_ACCEPT_DEBUG, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_ACCEPT_DEBUG, oParam );
#else
			LOG4CXX_DEBUG( m_pLogger, "A socket has been accepted." );
#endif

			pRet = new CEMSWin32Socket2( socket );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
		else
		{
			CEMSLogMsgParam oParam;
			oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgAlarm, EMS_SOCKET_ACCEPT_ERROR, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_ACCEPT_ERROR, oParam );
#else
			LOG4CXX_ERROR( m_pLogger, "Error accepting socket with code " << WSAGetLastError() << "." );
#endif
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		throw;
	}

	return pRet;
}

void 
CEMSWin32Socket2::Bind( const CEMSSocketAddress& coAddr )
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	sockaddr_in service;
	service.sin_family = _GetWinsockFamily( coAddr.GetFamily() );
	service.sin_addr.s_addr = inet_addr( coAddr.GetIP().c_str() );
	service.sin_port = htons( coAddr.GetPort() );

	if( SOCKET_ERROR != bind( m_Socket, (SOCKADDR*) &service, sizeof(service) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
		oParam.Add( coAddr.GetPort() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_BIND_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_BIND_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Bound to a socket at IP=" << coAddr.GetIP().c_str() << " and port=" << coAddr.GetPort() << "." );
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
		oParam.Add( coAddr.GetPort() );
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_BIND_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_BIND_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Error binding to IP=" << coAddr.GetIP().c_str() << " and port=" << coAddr.GetPort() << " with error code " << WSAGetLastError() << "." );
#endif
	}

}

void 
CEMSWin32Socket2::Bind( const CEMSSocketAddress& coAddr, bool& bBound )
{
	bBound = true;
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	sockaddr_in service;
	service.sin_family = _GetWinsockFamily( coAddr.GetFamily() );
	service.sin_addr.s_addr = inet_addr( coAddr.GetIP().c_str() );
	service.sin_port = htons( coAddr.GetPort() );

	if( SOCKET_ERROR != bind( m_Socket, (SOCKADDR*) &service, sizeof(service) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
		oParam.Add( coAddr.GetPort() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_BIND_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_BIND_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Successfully bound to IP=" << coAddr.GetIP().c_str() << ", port=" << coAddr.GetPort() << "." );
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
		oParam.Add( coAddr.GetPort() );
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_BIND_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_BIND_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failed to bind to IP=" << coAddr.GetIP().c_str() << ", port=" << coAddr.GetPort() << " with error code " << WSAGetLastError() << "." );
#endif

		bBound = false;
	}
}

void 
CEMSWin32Socket2::Close()
{
	if( INVALID_SOCKET != m_Socket )
	{
		int iRet = closesocket( m_Socket );

		if( SOCKET_ERROR == iRet )
		{
			CEMSLogMsgParam oParam;
			oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CLOSE_ERROR, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CLOSE_ERROR, oParam );
#else
			LOG4CXX_ERROR( m_pLogger, "Error closing socket with error code " << WSAGetLastError() << "." );
#endif
		}

		m_Socket = INVALID_SOCKET;
	}

}

void 
CEMSWin32Socket2::Connect( const CEMSSocketAddress& coAddr )
{
	if( INVALID_SOCKET == m_Socket )
	{
		Create();
	}

	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	sockaddr_in service;
	service.sin_family = _GetWinsockFamily( coAddr.GetFamily() );
	service.sin_addr.s_addr = inet_addr( coAddr.GetIP().c_str() );
	service.sin_port = htons( coAddr.GetPort() );

	if( SOCKET_ERROR != connect( m_Socket, (SOCKADDR*) &service, sizeof(service) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
		oParam.Add( coAddr.GetPort() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_CONNECT_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_CONNECT_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Successfully connected to IP=" << coAddr.GetIP().c_str() << ", port=" << coAddr.GetPort() << "." );
#endif

		m_bLastConnectSuccess = true;
	}
	else
	{
		// Don't keep logging this.  The target is offline.
		if( m_bLastConnectSuccess )
		{
			CEMSLogMsgParam oParam;
			oParam.AddString( CEMSConversionUtil::ConvertToString( coAddr.GetIP().c_str() ).c_str() );
			oParam.Add( coAddr.GetPort() );
			oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CONNECT_ERROR, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_CONNECT_ERROR, oParam );
#else
			LOG4CXX_ERROR( m_pLogger, "Failed to connect to IP=" << coAddr.GetIP().c_str() << ", port=" << coAddr.GetPort() << " with error code " << WSAGetLastError() << "." );
#endif
		}

		m_bLastConnectSuccess = false;

		throw CEMSException();
	}

}

void 
CEMSWin32Socket2::Disconnect()
{
	throw CEMSException( EMS_UNSUPPORTED );

	// Only available on XP or Longhorn.

//	if( INVALID_SOCKET != m_Socket )
//	{
//		if( !DisconnectEx( m_Socket, 0, TF_REUSE_SOCKET, 0 ) )
//		{
#ifndef _USE_RAW_LOG4CXX_
	//			LogMsg( EMSLogMsgWarn, __FILE__, __LINE__, L"Error disconnecting socket:  %ld", WSAGetLastError() );
#endif
//		}
//	}
}

void 
CEMSWin32Socket2::Listen( const int ciBackLog )
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	if( SOCKET_ERROR != listen( m_Socket, ( 0 == ciBackLog ) ? SOMAXCONN : ciBackLog ) )
	{
		CEMSLogMsgParam oParam;
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_LISTEN_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_LISTEN_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Listening on socket." );
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_LISTEN_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_LISTEN_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failed to listen on socket with error code " << WSAGetLastError() << "." );
#endif
	}
}

int 
CEMSWin32Socket2::Receive( char* acBuf, int iLen, int iFlags )
{
	int iRet = 0;

	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iWS2Flags = _GetWinsockFlags( iFlags );

	if( SOCKET_ERROR == ( iRet = recv( m_Socket, acBuf, iLen, iWS2Flags ) ) )
	{
		// Log it ... Except if it's the time out message
		if ( WSAETIMEDOUT != WSAGetLastError() )
		{
			CEMSLogMsgParam oParam;
			oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgAlarm, EMS_SOCKET_RECV_ERROR, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_RECV_ERROR, oParam );
#else
			LOG4CXX_ERROR( m_pLogger, "Failed to receive data from socket with error code " << WSAGetLastError() << ".");
#endif
		}
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.Add( iRet );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_RECV_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_RECV_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Received " << iRet << " bytes on socket.");
#endif
	}

	return iRet;

}

int 
CEMSWin32Socket2::ReceiveFrom( char* acBuf, int iLen, int iFlags, CEMSSocketAddress& oAddr )
{
	int iRet = 0;

	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iWS2Flags = _GetWinsockFlags( iFlags );

	sockaddr_in addrRecv;
	memset( &addrRecv, 0, sizeof(addrRecv ) );

	int iAddrSize = sizeof(addrRecv);

	if( SOCKET_ERROR == ( iRet = recvfrom( m_Socket, acBuf, iLen, iWS2Flags, 
												(SOCKADDR *) &addrRecv, &iAddrSize ) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_RECV_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_RECV_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failure receiving from socket with error code " << WSAGetLastError() << "." );
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.Add( iRet );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_RECV_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_RECV_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Received " << iRet << " bytes from socket.");
#endif
	}

	return iRet;
}

int 
CEMSWin32Socket2::Send( const char* cacBuf, int iLen, int iFlags )
{
	int iRet = 0;

	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iWS2Flags = _GetWinsockFlags( iFlags );

	sockaddr_in addrRecv;
	memset( &addrRecv, 0, sizeof(addrRecv ) );

	CEMSLogMsgParam oParam;
	oParam.Add( iLen );
	oParam.Add( iWS2Flags );
#ifndef _USE_RAW_LOG4CXX_
//	LogMsg( EMSLogMsgDebug, EMS_SOCKET_SENDREQ_DEBUG, oParam,  __FILE__, __LINE__ );
	CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_SENDREQ_DEBUG, oParam );
#else
	LOG4CXX_DEBUG( m_pLogger, "Requesting send of " << iLen << " bytes with flags=" << iWS2Flags << ".");
#endif

	if( SOCKET_ERROR == ( iRet = send( m_Socket, cacBuf, iLen, iWS2Flags ) ) )
	{
		// Don't keep logging the send error.  It could be that the target has gone offline or there
		// is some network disruption.
		if( !m_bLastSendSuccess )
		{
			CEMSLogMsgParam oParam;
			oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SEND_ERROR, oParam,  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SEND_ERROR, oParam );
#else
			LOG4CXX_ERROR( m_pLogger, "Failed to send data with error code " << WSAGetLastError() << ".");
#endif
		}

		m_bLastSendSuccess = false;

		throw CEMSException();
	}
	else
	{
		m_bLastSendSuccess = true;

		CEMSLogMsgParam oParam;
		oParam.Add( iRet );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_SEND_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_SEND_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Successfully sent " << iRet << " bytes.");
#endif
	}

	return iRet; 
}

int 
CEMSWin32Socket2::SendTo( const char* cacBuf, int iLen, int iFlags, 
							const CEMSSocketAddress& coAddr )
{
	int iRet = 0;

	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iWS2Flags = _GetWinsockFlags( iFlags );

	sockaddr_in addrSend = _GetWinsockAddress( coAddr );

	if( SOCKET_ERROR == ( iRet = sendto( m_Socket, cacBuf, iLen, iWS2Flags, (SOCKADDR*) &addrSend, sizeof(addrSend) ) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SEND_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SEND_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failure sending data with error code " << WSAGetLastError() << "." );
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
		oParam.Add( iRet );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_SEND_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_SEND_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Successfully sent " << iRet << " bytes of data.");
#endif
	}

	return iRet; 
}

void 
CEMSWin32Socket2::Shutdown( int iHow )
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iWS2How = _GetWinsockShutdownFlags( iHow );

	if( SOCKET_ERROR == shutdown( m_Socket, iWS2How ) )
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SHUTDOWN_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SHUTDOWN_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failed to shutdown socket runtime with error code " << WSAGetLastError() << ".");
#endif
	}
	else
	{
		CEMSLogMsgParam oParam;
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, EMS_SOCKET_SHUTDOWN_DEBUG, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, EMS_SOCKET_SHUTDOWN_DEBUG, oParam );
#else
		LOG4CXX_DEBUG( m_pLogger, "Successfully shutdown socket runtime.");
#endif
	}
}

void 
CEMSWin32Socket2::SetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName, 
								const char* cszValue )
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	char* acVal = 0;
	int iValSize = 0;

	_GetWinsockValue( ceOptionName, cszValue, acVal, iValSize );

	setsockopt( m_Socket, _GetWinsockLevel( ceLevel ), _GetWinsockOption( ceOptionName ),
					acVal, iValSize );

	if( acVal )
	{
		delete[] acVal;
		acVal = 0;
	}

}

void 
CEMSWin32Socket2::SetOptionTimeOut( DWORD dwTimeOut)
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

    int iRet = setsockopt( m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&dwTimeOut,  sizeof dwTimeOut );

}

std::string
CEMSWin32Socket2::GetOption( const EMSSOCKETLEVEL ceLevel, const EMSSOCKETOPTION ceOptionName )
{
	throw CEMSException( EMS_UNSUPPORTED );
}

bool 
CEMSWin32Socket2::IsReadData()
{
	return ( 0 < Select( true ) ? true : false );
}

bool 
CEMSWin32Socket2::IsConnection()
{
	return ( 0 < Select( true ) ? true : false );
}

int 
CEMSWin32Socket2::Select( const bool cbRead )
{
	if( INVALID_SOCKET == m_Socket )
	{
		throw CEMSException( EMS_NOT_INITIALIZED );
	}

	int iRet = 0;

	fd_set setRead;
	fd_set setWrite;
	fd_set setExcpt;

	FD_ZERO( &setRead );
	FD_ZERO( &setWrite );
	FD_ZERO( &setExcpt );

	if( cbRead )
	{
		FD_SET( m_Socket, &setRead );
	}
	else
	{
		FD_SET( m_Socket, &setWrite );
	}

	TIMEVAL timeoutValue;
	timeoutValue.tv_sec = 0;
	timeoutValue.tv_usec = 500000;	// 500 milliseconds


	if( SOCKET_ERROR == ( iRet = select( 0, &setRead, &setWrite, &setExcpt, &timeoutValue ) ) )
	{
		CEMSLogMsgParam oParam;
		oParam.Add( WSAGetLastError() );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SELECT_ERROR, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgAlarm, EMS_SOCKET_SELECT_ERROR, oParam );
#else
		LOG4CXX_ERROR( m_pLogger, "Failed to select socket status with error code " << WSAGetLastError() << ".");
#endif
	}
	else
	{
		DWORD dwMsgID = 0;
		if( cbRead )
		{
			dwMsgID = EMS_SOCKET_SELECT_READ_DEBUG;
		}
		else
		{
			dwMsgID = EMS_SOCKET_SELECT_WRITE_DEBUG;
		}
		
		CEMSLogMsgParam oParam;
		oParam.Add( iRet );
#ifndef _USE_RAW_LOG4CXX_
//		LogMsg( EMSLogMsgDebug, dwMsgID, oParam,  __FILE__, __LINE__ );
		CEMSLogHelper::LogMsg( EMSLogMsgDebug, dwMsgID, oParam );
#else
//		LOG4CXX_DEBUG( m_pLogger, "Socket status selected successfully." );
#endif
	}

	return iRet;
}

short 
CEMSWin32Socket2::_GetWinsockFamily( const CEMSSocketAddress::EMSADDRFAMILY ceAddrFamily )
{
	short sRet = 0;

	switch( ceAddrFamily )
	{
		case CEMSSocketAddress::EMSADDRFAMILY_INET:
			sRet = AF_INET;
			break;
		default:
#ifndef _USE_RAW_LOG4CXX_
//			LogMsg( EMSLogMsgWarn, EMS_SOCKET_FAMILY_ERROR, CEMSLogMsgParam(),  __FILE__, __LINE__ );
			CEMSLogHelper::LogMsg( EMSLogMsgWarn, EMS_SOCKET_FAMILY_ERROR, CEMSLogMsgParam() );
#else
			LOG4CXX_ERROR( m_pLogger, "An attempt was made to use an unsupported socket family." );
#endif
			break;
	}

	return sRet;
}

int 
CEMSWin32Socket2::_GetWinsockFlags( const int ciEMSFlags )
{
	int iRet = 0;

	if( (ciEMSFlags & ms_ciPEEK) == ms_ciPEEK )
	{
		iRet |= MSG_PEEK;
	}

	if( (ciEMSFlags & ms_ciOOB) == ms_ciOOB )
	{
		iRet |= MSG_OOB;
	}

	if( (ciEMSFlags & ms_ciWAITALL) == ms_ciWAITALL )
	{
//		iRet |= MSG_WAITALL;
	}

	if( (ciEMSFlags & ms_ciDONTROUTE) == ms_ciDONTROUTE )
	{
		iRet |= MSG_DONTROUTE;
	}

	return iRet;
}

sockaddr_in 
CEMSWin32Socket2::_GetWinsockAddress( const CEMSSocketAddress& coAddr )
{
	sockaddr_in addrRet;
	memset( &addrRet, 0, sizeof(addrRet) );

	addrRet.sin_family = _GetWinsockFamily( coAddr.GetFamily() );
	addrRet.sin_addr.s_addr = inet_addr( coAddr.GetIP().c_str() );
	addrRet.sin_port = htons( coAddr.GetPort() );

	return addrRet;
}

int 
CEMSWin32Socket2::_GetWinsockShutdownFlags( const int ciEMSFlags )
{
	int iRet = 0;

	if( ciEMSFlags == ms_ciSEND )
	{
//		iRet = SD_SEND;
	}
	else if( ciEMSFlags == ms_ciRECEIVE )
	{
//		iRet = SD_RECEIVE;
	}
	else if( ciEMSFlags == ms_ciBOTH )
	{
//		iRet = SD_BOTH;
	}

	return iRet;
}

int 
CEMSWin32Socket2::_GetWinsockLevel( const EMSSOCKETLEVEL ceLevel )
{
	int iRet = 0;

	switch( ceLevel )
	{
		case EMSSOCKETLEVEL_SOCKET:
			iRet = SOL_SOCKET;
			break;
		case EMSSOCKETLEVEL_IPPROTO_TCP1:
//			iRet = IPPROTO_TCP1;
			break;
		case EMSSOCKETLEVEL_NSPROTO_IPX:
//			iRet = NSPROTO_IPX;
			break;
	}

	return iRet;
}

int 
CEMSWin32Socket2::_GetWinsockOption( const EMSSOCKETOPTION ceOption )
{
	int iRet = 0;

	switch( ceOption )
	{
		case EMSSOCKETOPT_BROADCAST:
			iRet = SO_BROADCAST;
			break;

		case EMSSOCKETOPT_CONDITIONAL_ACCEPT:
			iRet = SO_CONDITIONAL_ACCEPT;
			break;

		case EMSSOCKETOPT_DEBUG:
			iRet = SO_DEBUG;
			break;

		case EMSSOCKETOPT_DONT_LINGER:
			iRet = SO_DONTLINGER;
			break;

		case EMSSOCKETOPT_DONT_ROUTE:
			iRet = SO_DONTROUTE;
			break;

		case EMSSOCKETOPT_GROUP_PRIORITY:
			iRet = SO_GROUP_PRIORITY;
			break;

		case EMSSOCKETOPT_KEEP_ALIVE:
			iRet = SO_KEEPALIVE;
			break;

		case EMSSOCKETOPT_LINGER:
			iRet = SO_LINGER;
			break;

		case EMSSOCKETOPT_OOBINLINE:
			iRet = SO_OOBINLINE;
			break;

		case EMSSOCKETOPT_RCVBUF:
			iRet = SO_RCVBUF;
			break;

		case EMSSOCKETOPT_REUSE_ADDR:
			iRet = SO_REUSEADDR;
			break;

		case EMSSOCKETOPT_EXCLUSIVE_ADDR_USE:
			iRet = SO_EXCLUSIVEADDRUSE;
			break;

		case EMSSOCKETOPT_SNDBUF:
			iRet = SO_SNDBUF;
			break;

		case EMSSOCKETOPT_SO_UPDATE_ACCEPT_CONTEXT:
//			iRet = SO_UPDATE_ACCEPT_CONTEXT;
			break;

		case EMSSOCKETOPT_PVD_CONFIG:
			iRet = PVD_CONFIG;
			break;
	}


	return iRet;
}

void 
CEMSWin32Socket2::_GetWinsockValue( const EMSSOCKETOPTION ceOptionName, const char* cszValue,
								char*& acVal, int& iValSize )
{
	acVal = 0;
	iValSize = 0;

	BOOL bValue = FALSE;
	int iValue = 0;
	linger lingValue;
	memset( &lingValue, 0, sizeof(linger) );

	char* pVal = 0;

	if( cszValue )
	{
		switch( ceOptionName )
		{
			case EMSSOCKETOPT_BROADCAST:
			case EMSSOCKETOPT_CONDITIONAL_ACCEPT:
			case EMSSOCKETOPT_DEBUG:
			case EMSSOCKETOPT_DONT_LINGER:
			case EMSSOCKETOPT_DONT_ROUTE:
			case EMSSOCKETOPT_KEEP_ALIVE:
			case EMSSOCKETOPT_OOBINLINE:
			case EMSSOCKETOPT_REUSE_ADDR:
			case EMSSOCKETOPT_EXCLUSIVE_ADDR_USE:

				if( 0 == stricmp( cszValue, ms_cszBooleanTrue ) )
				{
					bValue = TRUE;
				}
				else if( 0 == stricmp( cszValue, ms_cszBooleanFalse ) )
				{
					bValue = FALSE;
				}

				iValSize = sizeof(bValue);
				pVal = reinterpret_cast<char*>( &bValue );

				break;
	
			case EMSSOCKETOPT_GROUP_PRIORITY:
			case EMSSOCKETOPT_RCVBUF:
			case EMSSOCKETOPT_SNDBUF:
			case EMSSOCKETOPT_SO_UPDATE_ACCEPT_CONTEXT:
				
				iValue = CEMSConversionUtil::ConvertToLong( cszValue );

				iValSize = sizeof(iValue);
				pVal = reinterpret_cast<char*>( &iValue );

				break;

			case EMSSOCKETOPT_LINGER:
				{
					CEMSLinger oLinger;
#ifndef _NO_XML_
					oLinger.Deserialize( cszValue );
#endif

					lingValue.l_onoff = oLinger.GetOnOff();
					lingValue.l_linger = oLinger.GetLinger();

					iValSize = sizeof(lingValue);
					pVal = reinterpret_cast<char*>( &lingValue );
				}

				break;

		}

		if( pVal && (iValSize > 0) )
		{
			acVal = new char[ iValSize ];
			
			if( !acVal )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memcpy( acVal, pVal, iValSize );
				
		}
	}
}