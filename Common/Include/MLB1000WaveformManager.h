///////////////////////////////////////////////////////////////////////////////
//  MLB1000WaveformManager.cpp
//
//  CREATED: March 18th, 2009
//
//  PURPOSE:  
//		Implementation of MLB1000WaveformManager class
//
//		The purpose of this class is to provide an interface between applications that need
//		to know the available waveforms at a given customer site for MLB-1000 beacons
//		and a storage system
//
//		This class makes use of the cryptocpp classes
//		This class is win32 only. MFC is not used
//
//  *********************************************************************                           
//  *	              Copyright (c) 2009 by EMS Technologies, Inc.,									 
//  *										All rights reserved										 
//  *	This program is unpublished software and contains the trade secrets							 
//  *	and confidential information of EMS Technologies, Inc.  It may not be 						 
//  * reproduced in whole or in part, in any form or by any means whatsoever 						 
//  * without the express written permission of EMS Technologies, Inc.								 
//  *																								 
//  ********************************************************************
//
//  LAST CHANGED: $Date: 4/23/2009 2:32:42 PM$
//
//  REVISION HISTORY:
//  $Log:
//   1    SARMaster  1.0         4/23/2009 2:32:42 PM   Morgan Fraser   
//  $
// 
// 
//
/////////////////////////////////////////////////////////////////////////////////

#pragma once

#ifndef WINVER
	typedef unsigned char BYTE;
	typedef unsigned char byte;
	typedef unsigned long       DWORD;
	#ifdef  UNICODE                     
		typedef wchar_t TCHAR, *PTCHAR;
	#else   // UNICODE 
		typedef char TCHAR, *PTCHAR;
	#endif// UNICODE 
	typedef long HRESULT;
	#define S_OK                            ((HRESULT)0x00000000L)
	#define E_POINTER						((HRESULT)0x80004003L)
	#define E_FAIL                          ((HRESULT)0x80004005L)
#endif

#define E_BADWAVEFORMDETECTED 0x80070057L

typedef unsigned _int64 QWORD;

class MLB1000WaveformManager
{
public:
	struct EncryptionKey {
		byte	m_key[24];
		byte	m_iv[8];
	};

	static HRESULT EncodeCustomerKey( const EncryptionKey CustomerKey
							   ,TCHAR *szBuffer
							   ,const long BufferSize );
	static HRESULT DecodeCustomerKey( const TCHAR *szCustomerKey
							   ,EncryptionKey &CustomerKey );
	static HRESULT EncodeWaveform( const EncryptionKey CustomerKey
							,QWORD qwWaveform
							,TCHAR *szBuffer
							,const long BufferSize );
	static HRESULT DecodeWaveform( const EncryptionKey CustomerKey
						    ,const TCHAR *szWaveform
							,QWORD &qwWaveform );
	static HRESULT GetAllWaveforms( const EncryptionKey CustomerKey
							 ,const TCHAR *szFilename
							 ,std::map<long,QWORD> &WaveformMap );

private:
	static byte MLB1000_MasterEncryption_key[24];
	static byte MLB1000_MasterEncryption_iv[8];	
};
