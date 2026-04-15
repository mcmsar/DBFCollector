/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __SOAP_MIME_HANDLER_H__
#define __SOAP_MIME_HANDLER_H__

#include "stdsoap2.h"
//#include "xop.h"
#include <string>

struct _xop__Include;

struct mime_server_handle
{ 
	// File name
	char* szKey;

	// File
	FILE* fp;

	// File size;
	int iSize;

	// Extra information.
	char* szOptions;
};

//! Implementation of streaming MIME-handler callback functions.
class CEMSSoapMimeHandler
{
	public:
		CEMSSoapMimeHandler() {}
		CEMSSoapMimeHandler( const CEMSSoapMimeHandler& x ) {}
		~CEMSSoapMimeHandler() {}

		//! Set the folder into which received attachments are written.  This is generally a 
		//! temporary folder.
		static void SetWriteFolder( const char* cszFolder );

		static void* ReadOpen(struct soap* pSoap, void* pHandle, const char* cszId, 
							const char* cszType, const char* cszDescription);

		static size_t Read(struct soap* pSoap, void* pHandle, char* pcBuf, size_t sizeLen );

		static void ReadClose(struct soap* pSoap, void* pHandle);

		static void* ServerWriteOpen(struct soap* pSoap, void* pUnusedHandle, const char* cszId, 
							const char* cszType, const char* cszDescription, 
							enum soap_mime_encoding eEncoding);

		static void ServerWriteClose(struct soap* pSoap, void* pHandle);

		static int ServerWrite(struct soap* pSoap, void* pHandle, const char* cpcBuf, size_t sizeLen);

		static void* ClientWriteOpen(struct soap* pSoap, void* pHandle, const char* cszId, 
									const char* cszType, const char* cszDescription, 
									enum soap_mime_encoding eEncoding);

		static void ClientWriteClose(struct soap* pSoap, void* pHandle);

		static int ClientWrite(struct soap* pSoap, void* pHandle, const char* cpcBuf, size_t sizeLen);

		static char* GetMimeType( const char* cszFile );

		static char* GetExtension( const char* cszType );

		static bool LoadAttachment(struct soap* pSoap, const char* cszFile, 
								const char* cszOptions, _xop__Include* pxopData);
	private:
		static std::string m_oszWriteFolder;
};

#endif