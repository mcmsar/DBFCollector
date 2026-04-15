/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
*	Portions of this code are derived from the gSoap 2.7 samples 
*   under the (mtom sample).
--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2000-2005, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "soapmimehandler.h"
#include "soapH.h"
#include "emsexcpt.h"
#include <sys/stat.h>

//! Use current folder as default.
std::string CEMSSoapMimeHandler::m_oszWriteFolder = ".";

void 
CEMSSoapMimeHandler::SetWriteFolder( const char* cszFolder )
{
	if( cszFolder )
		m_oszWriteFolder = cszFolder;
}

void* 
CEMSSoapMimeHandler::ReadOpen(struct soap* pSoap, void* pHandle, const char* cszId, 
							const char* cszType, const char* cszDescription)
{
	// Assuming that pHandle contains the __ptr field of xop__Include, and was set by the
	// application.  The return value of this method is used in the Read and ReadClose methods.
	FILE* pfAttachment = (FILE*) pHandle;
	return (void*) pfAttachment;
}

size_t 
CEMSSoapMimeHandler::Read(struct soap* pSoap, void* pHandle, char* pcBuf, size_t sizeLen )
{
	// Just read from handle into the buffer.
	return fread(pcBuf, 1, sizeLen, (FILE*)pHandle);
}

void 
CEMSSoapMimeHandler::ReadClose(struct soap* pSoap, void* pHandle)
{
	fclose( (FILE*) pHandle );
}

void* 
CEMSSoapMimeHandler::ServerWriteOpen(struct soap* pSoap, void* pUnusedHandle, const char* cszId, 
								const char* cszType, const char* cszDescription, 
								enum soap_mime_encoding eEncoding)
{
	struct mime_server_handle* pRet = NULL;
	const char* cszTempFile = NULL;

	try
	{
	
		pRet = reinterpret_cast<struct mime_server_handle*>( soap_malloc(pSoap, sizeof(struct mime_server_handle)) );

		if( !pRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( pRet, 0, sizeof(struct mime_server_handle) );

		// Get a temporary file name.
		const char* cszTempFile = tempnam(m_oszWriteFolder.c_str(), "soap_attach_");

		if( !cszTempFile )
		{
			THROW_RUNTIME_EXCEPTION( EMS_NO_FILE );
		}

		std::string oszTempFile = cszTempFile;

		// Add an extension based on the received type.
		oszTempFile.append( GetExtension( cszType ) );
		
		// File name becomes the key
		pRet->szKey = soap_strdup(pSoap, oszTempFile.c_str());
		pRet->szOptions = soap_strdup(pSoap, cszDescription);
		pRet->fp = fopen(oszTempFile.c_str(), "wb");

		free( (void*) cszTempFile);

		if( !pRet->fp )
		{ 
			THROW_RUNTIME_EXCEPTION( EMS_NO_FILE );
		}
	
	}
	catch( ... )
	{
		if( pRet )
		{
			if( pRet->fp )
			{
				fclose( pRet->fp );
				pRet->fp = NULL;
			}

			soap_dealloc( pSoap, pRet );
			pRet = NULL;
		}

		if( cszTempFile )
		{
			free( (void*) cszTempFile );
			cszTempFile = NULL;
		}

		throw;
	}

	return (void*) pRet;
}

void 
CEMSSoapMimeHandler::ServerWriteClose(struct soap* pSoap, void* pHandle)
{
	fclose( ( (struct mime_server_handle* )pHandle)->fp);
}

int 
CEMSSoapMimeHandler::ServerWrite(struct soap* pSoap, void* pHandle, const char* pcBuf, size_t sizeLen)
{
	int iRet = SOAP_OK;

	FILE* fpFile = ( (struct mime_server_handle* )pHandle)->fp;
	
	while( sizeLen )
	{ 
		size_t sizeWritten = fwrite(pcBuf, 1, sizeLen, fpFile);

		if (!sizeWritten)
		{ 
			THROW_RUNTIME_EXCEPTION( EMS_IO_ERROR );
		}
		
		sizeLen -= sizeWritten;
		pcBuf += sizeWritten;

		( (struct mime_server_handle* )pHandle)->iSize += sizeWritten;
	}

	return iRet;
}

void* 
CEMSSoapMimeHandler::ClientWriteOpen(struct soap* pSoap, void* pHandle, const char* cszId, 
									const char* cszType, const char* cszDescription, 
									enum soap_mime_encoding eEncoding)
{
	// Same handling as the server.
	return ServerWriteOpen( pSoap, pHandle, cszId, cszType, cszDescription, eEncoding );
}

void 
CEMSSoapMimeHandler::ClientWriteClose(struct soap* pSoap, void* pHandle)
{
	// Same handling as the server.
	ServerWriteClose( pSoap, pHandle );
}

int 
CEMSSoapMimeHandler::ClientWrite(struct soap* pSoap, void* pHandle, const char* cpcBuf, size_t sizeLen)
{
	// Same handling as the server.
	return ServerWrite( pSoap, pHandle, cpcBuf, sizeLen );
}

char*
CEMSSoapMimeHandler::GetMimeType(const char* cszFile)
{ 
	// This code is adopted from the gSOAP 2.7 MTOM sample.
	int n = strlen(cszFile);

	if (n > 4 && (!strcmp(cszFile + n - 4, ".xml")
			 || !strcmp(cszFile + n - 4, ".xsd")
			 || !strcmp(cszFile + n - 5, ".wsdl")))
		return "text/xml";
	if (n > 4 && !strcmp(cszFile + n - 4, ".jpg"))
		return "image/jpg";
	if (n > 4 && !strcmp(cszFile + n - 4, ".zip"))
		return "application/zip";
	
	return "*/*";
}

char*
CEMSSoapMimeHandler::GetExtension( const char* cszType )
{
	char* szRet = "";

	if( 0 == stricmp( "text/xml", cszType ) )
		szRet = ".xml";
	else if( 0 == stricmp( "application/zip", cszType ) )
		szRet = ".zip";
	else if( 0 == stricmp( "image/jpg", cszType ) )
		szRet = ".jpg";

	return szRet;
}

bool
CEMSSoapMimeHandler::LoadAttachment(struct soap* pSoapRuntime, const char* cszFile, 
								const char* cszOptions, _xop__Include* pxopData)
{ 
	bool bRet = false;

	FILE* fpFile = NULL;

	try
	{
		struct stat sb;
		int iSize = 0;

		if( !cszFile )
		{
			THROW_INVALID_ARG_EXCEPTION();
		}

		fpFile = fopen(cszFile, "rb");
		
		if (fpFile)
		{ 
			// Handle for streaming is the file.
			pxopData->__ptr = (unsigned char*)fpFile;
			
			if(	!fstat(fileno(fpFile), &sb) && 
				(sb.st_size > 0))
			{
				iSize = sb.st_size;
			}
			else
			{ 
				// Unknown file size.  So, use HTTP chunking.
				soap_set_omode(pSoapRuntime, SOAP_IO_CHUNK);
				iSize = 0;
			}

			pxopData->__size = iSize;
			pxopData->id = NULL;
			pxopData->type = GetMimeType( cszFile );

			if( cszOptions )
			{
				long lLen = strlen( cszOptions );

				if( lLen > 0 )
				{
					//pxopData->options = soap_dime_option(pSoapRuntime, 0, cszOptions);
					//pxopData->options = soap_strdup(pSoapRuntime, cszOptions);
				}
				else
					pxopData->options = NULL;
			}
			else
			{
				pxopData->options = NULL;
			}

			bRet = true;
		}
	}
	catch( ... )
	{
		if( fpFile )
		{
			fclose( fpFile );
			fpFile = NULL;
		}

		throw;
	}

	return bRet;
}