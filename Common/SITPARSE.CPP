/********************************************************************
*	Module:			sitparse.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	CEMSSitParser class
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

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5	rvw	start
	0.1 2003 Mar 6   Lguan	add 770A parse code

********************************************************************/
#pragma warning(disable:4786)	// STL symbol size warning

#include <stdio.h>

#include "emscom.h"
#include "emstypes.h"
#include "sitparse.h"
#include "emsfstrm.h"
#include "emsmstrm.h"
#include "sittoken.h"
#include "emsit115.h"
#include "emsit121.h"
#include "emsit122.h"
#include "emsit125.h"
#include "emsit161.h"
#include "emsit215.h"
#include "emsit216.h"
#include "emsit218.h"
#include "emsit255.h"
#include "emsit260.h"
#include "emsit270.h"
#include "emsit415.h"
#include "emsit417.h"
#include "emsit510.h"
#include "emsit605.h"
#include "emsit607.h"
#include "emsit608.h"
#include "emsit661.h"
#include "emsit662.h"
#include "emsit722.h"
#include "emsit750.h"
#include "emsit751.h"
#include "emsit760.h"
#include "emsit770.h"
#include "emsit915.h"
#include "emsit950.h"
#include "emsit951.h"
#include "emsit960.h"
#include "emsit157.h"

const BOOL c_bPeekOnly = TRUE;

CEMSSitParser::CEMSSitParser( )
{
}

CEMSSitParser::~CEMSSitParser()
{
}

EMS_RESULT CEMSSitParser::ParseSit( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMessageBase *lpSitMsg=0;

	if ( lpTokenizer )
	{
		// First, check for standard SIT format.
		hr = m_sitMsg.ParseSitHeader( lpTokenizer, c_bPeekOnly );

		if ( hr == EMS_OK )			
		{
			switch ( m_sitMsg.GetSitCode() )
			{
				case 0:
					switch ( m_sitMsg.GetSitNumber() ) 
					{
						case 115:
							lpSitMsg = new CEMSSit115();
							break;

						case 122:
							lpSitMsg = new CEMSSit122();
							break;

						case 125:
							lpSitMsg = new CEMSSit125();
							break;

						case 152:
							lpSitMsg = new CEMSSit152();
							break;

						case 157:
							lpSitMsg = new CEMSSit157();
							break;

						case 161:
							lpSitMsg = new CEMSSit161();
							break;

						case 215:
							lpSitMsg = new CEMSSit215();
							break;

						case 216: // 2005 Oct 27
							lpSitMsg = new CEMSSit216();
							break;

						case 218: // 2011 Oct 25
							lpSitMsg = new CEMSSit218();
							break;

						case 415: 
							lpSitMsg = new CEMSSit415();
							break;

						case 417:
							lpSitMsg = new CEMSSit417( );
							break;

						case 510: 
							lpSitMsg = new CEMSSit510();
							break;

						case 607: 
							lpSitMsg = new CEMSSit607();
							break;

						case 608: 
							lpSitMsg = new CEMSSit608();
							break;

						case 722: 
							lpSitMsg = new CEMSSit722();
							break;

						case 915:	
							lpSitMsg = new CEMSSit915();
							break;

						case 960:	// Trenton Geo 500 GeoSarr data
							lpSitMsg = new CEMSSit960();
							break;

						default:	// unknown Sit type
							hr = EMS_UNKNOWN_SIT_TYPE;
							break;
					}
					break;
				
				case 0x115A:
					lpSitMsg = new CEMSSit115A();
					break;

				case 0x115B:
					lpSitMsg = new CEMSSit115B();
					break;

				case 0x115C:
					lpSitMsg = new CEMSSit115C();
					break;

				case 0x121A:
					lpSitMsg = new CEMSSit121A();
					break;

				case 0x121B:
					lpSitMsg = new CEMSSit121B();
					break;

				case 0x122A:
					lpSitMsg = new CEMSSit122A();
					break;

				case 0x122B:
					lpSitMsg = new CEMSSit122B();
					break;

				case 0x122C:
					lpSitMsg = new CEMSSit122C();
					break;

				case 0x122E:
					lpSitMsg = new CEMSSit122E();
					break;

				case 0x125A:
					lpSitMsg = new CEMSSit125A();
					break;

				case 0x125B:
					lpSitMsg = new CEMSSit125B();
					break;

				case 0x215A:
					lpSitMsg = new CEMSSit215A();
					break;

				case 0x215B:
					lpSitMsg = new CEMSSit215B();
					break;

				case 0x215C:
					lpSitMsg = new CEMSSit215C();
					break;

				case 0x255A:
					lpSitMsg = new CEMSSit255A();
					break;

				case 0x260A:
					lpSitMsg = new CEMSSit260A();
					break;

				case 0x260B:
					lpSitMsg = new CEMSSit260B();
					break;

				case 0x270A:
					lpSitMsg = new CEMSSit270A();
					break;

				case 0x415A:
					lpSitMsg = new CEMSSit415A();
					break;

				case 0x417A:
					lpSitMsg = new CEMSSit417A();
					break;

				case 0x417B:
					lpSitMsg = new CEMSSit417B();
					break;

				case 0x510A:
					lpSitMsg = new CEMSSit510A();
					break;

				case 0x605A:
					lpSitMsg = new CEMSSit605A();
					break;

				case 0x605B:
					lpSitMsg = new CEMSSit605B();
					break;

				case 0x605C:
					lpSitMsg = new CEMSSit605C();
					break;

				case 0x605D:
					lpSitMsg = new CEMSSit605D();
					break;

				case 0x661A:
					lpSitMsg = new CEMSSit661A();
					break;

				case 0x661B:
					lpSitMsg = new CEMSSit661B();
					break;

				case 0x662A:
					lpSitMsg = new CEMSSit662A();
					break;

				case 0x750A:
					lpSitMsg = new CEMSSit750A();
					break;

				case 0x751A:
					lpSitMsg = new CEMSSit751A();
					break;

				case 0x760A:
					lpSitMsg = new CEMSSit760A();
					break;

				case 0x770A:
					lpSitMsg = new CEMSSit770A();
					break;

				case 0x950A:
					lpSitMsg = new CEMSSit950A();
					break;

				case 0x951A:
					lpSitMsg = new CEMSSit951A();
					break;

				default:		// unknown EMS Sit Type
					hr = EMS_UNKNOWN_SIT_TYPE;
					break;
			}
			if ( ( hr == EMS_OK ) && lpSitMsg )
			{
			 	lpSitMsg->SetMsgHeader( &m_sitMsg );

				hr = lpSitMsg->ParseSitMessage( lpTokenizer );
			}
		}
		else
		{
			// Is it in a supported XML format?
			lpSitMsg = new CEMSSit722A();

			hr = lpSitMsg->ParseSitMessage( lpTokenizer );

			if( EMS_OK != hr )
			{
				delete lpSitMsg;

				// Is it a supported CSV format?
				lpSitMsg = new CEMSSit722B();

				hr = lpSitMsg->ParseSitMessage( lpTokenizer );

			}

			
		}
	}

	if( FAILED(hr) )
	{
		if( lpSitMsg )
		{
			delete lpSitMsg;
			lpSitMsg = 0;
		}
	}

	if ( lplpSitMsg )
		*lplpSitMsg = lpSitMsg;

	return hr;
}

EMS_RESULT CEMSSitParser::ParseXML( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMessageBase *lpSitMsg=0;

	if ( lpTokenizer )
	{
		// Is it in a supported XML format?
		lpSitMsg = new CEMSSit722A();

		hr = lpSitMsg->ParseSitMessage( lpTokenizer );
	}

	if( FAILED(hr) )
	{
		if( lpSitMsg )
		{
			delete lpSitMsg;
			lpSitMsg = 0;
		}
	}

	if ( lplpSitMsg )
		*lplpSitMsg = lpSitMsg;

	return hr;
}

EMS_RESULT CEMSSitParser::ParseCSV( CEMSSitTokenizer *lpTokenizer, CEMSSitMessageBase **lplpSitMsg )
{
	EMS_RESULT hr = EMS_OK;
	CEMSSitMessageBase *lpSitMsg=0;

	if ( lpTokenizer )
	{
		// Is it a supported CSV format?
		lpSitMsg = new CEMSSit722B();

		hr = lpSitMsg->ParseSitMessage( lpTokenizer );
	}

	if( FAILED(hr) )
	{
		if( lpSitMsg )
		{
			delete lpSitMsg;
			lpSitMsg = 0;
		}
	}

	if ( lplpSitMsg )
		*lplpSitMsg = lpSitMsg;

	return hr;
}

EMS_RESULT CEMSSitParser::ParseSitFile( LPCTSTR lpcszSitFile, CEMSSitMessageBase **lplpSitMsg,
													int nMaxSits, int *lpnSitCount )
{
	EMS_RESULT hr = EMS_OK;
	CEMSFileStream *lpFileStream = new CEMSFileStream();
	int nCount = 0;
	
	if ( lpFileStream )
	{
		hr = lpFileStream->OpenFile( lpcszSitFile, FALSE );

		if ( hr == EMS_OK )
		{
			CEMSSitTokenizer *lpTokenizer = new CEMSSitTokenizer( lpFileStream );
			CEMSSitMessageBase *lpSitMsg=0;
			BOOL bLastSit = FALSE;

			if ( lpTokenizer )
			{
				hr = m_sitMsg.ParseMsgStart( lpTokenizer );

				if ( hr == EMS_OK )
					hr = m_sitMsg.ParseMsgHeader( lpTokenizer );

				while ( ( nCount < nMaxSits ) && ( hr == EMS_OK ) && !bLastSit )
				{
					hr = ParseSit( lpTokenizer, &lpSitMsg );

					if ( ( hr == EMS_OK ) && lpSitMsg )
					{
						hr = lpSitMsg->ParseSitTrailer( lpTokenizer, &bLastSit );

						lplpSitMsg[ nCount++ ] = lpSitMsg;
					}
				}

				if ( hr == EMS_OK )
					hr = m_sitMsg.ParseMsgTrailer( lpTokenizer );

				delete lpTokenizer;
				lpTokenizer = 0;
			}
			else
				hr = EMS_NO_MEMORY;

			lpFileStream->CloseFile();
		}
		lpFileStream->Release();

		lpFileStream = 0;
	}

	if ( lpnSitCount )
		*lpnSitCount = nCount;  

	return hr;
}

EMS_RESULT CEMSSitParser::ParseSitStream(	IEMSSeqStream *lpStream, 
											int nMaxSits, 
											int	*lpnSitCount, 
											CEMSSitMessageBase **lplpSitMsg )
{
	EMS_RESULT hr = EMS_OK;
	int nCount = 0;
	
	if ( lpStream )
	{
		
		CEMSSitTokenizer *lpTokenizer = new CEMSSitTokenizer( lpStream );
		CEMSSitMessageBase *lpSitMsg=0;
		BOOL bLastSit = FALSE;

		if ( lpTokenizer )
		{
			hr = m_sitMsg.ParseMsgStart( lpTokenizer );

			if ( hr == EMS_OK )
				hr = m_sitMsg.ParseMsgHeader( lpTokenizer );

			while ( ( nCount < nMaxSits ) && ( hr == EMS_OK ) && !bLastSit )
			{
				hr = ParseSit( lpTokenizer, &lpSitMsg );

				if ( ( hr == EMS_OK ) && lpSitMsg )
				{
					hr = lpSitMsg->ParseSitTrailer( lpTokenizer, &bLastSit );

					lplpSitMsg[ nCount++ ] = lpSitMsg;
				}
			}

			if ( hr == EMS_OK )
				hr = m_sitMsg.ParseMsgTrailer( lpTokenizer );

			delete lpTokenizer;
			lpTokenizer = 0;
		}
		else
			hr = EMS_NO_MEMORY;

	}

	if ( lpnSitCount )
		*lpnSitCount = nCount;  

	return hr;
}

EMS_RESULT CEMSSitParser::ParseSitStream(	IEMSSeqStream *lpStream, 
								std::list<CEMSSitMessageBase*>& lstpSitMsg )
{
	EMS_RESULT hr = EMS_OK;
	
	if ( lpStream )
	{
		
		CEMSSitTokenizer *lpTokenizer = new CEMSSitTokenizer( lpStream );
		CEMSSitMessageBase *lpSitMsg=0;
		BOOL bLastSit = FALSE;

		if ( lpTokenizer )
		{
			hr = m_sitMsg.ParseMsgStart( lpTokenizer );

			if ( hr == EMS_OK )
				hr = m_sitMsg.ParseMsgHeader( lpTokenizer );

			while ( ( hr == EMS_OK ) && !bLastSit )
			{
				hr = ParseSit( lpTokenizer, &lpSitMsg );

				if ( ( hr == EMS_OK ) && lpSitMsg )
				{
					hr = lpSitMsg->ParseSitTrailer( lpTokenizer, &bLastSit );

					lstpSitMsg.push_back( lpSitMsg );
				}
			}

			if ( hr == EMS_OK )
				hr = m_sitMsg.ParseMsgTrailer( lpTokenizer );

			delete lpTokenizer;
			lpTokenizer = 0;
		}
		else
			hr = EMS_NO_MEMORY;

	}

	return hr;
}

EMS_RESULT CEMSSitParser::ParseSitByteArray(	BYTE cMsg[], 
												long lMsgSize, 
												CEMSSitMessageBase** lplpSitMsg,
												int nMaxSits,
												int* lpnSitCount )
{
	EMS_RESULT hr = EMS_OK;
	CEMSMemoryStream *lpMemStream = new CEMSMemoryStream();
	int nCount = 0;
	
	if ( lpMemStream )
	{
		hr = lpMemStream->Allocate( lMsgSize );

		if( SUCCEEDED(hr) )
		{
			ULONG ulWritten = 0;
			hr = lpMemStream->Write( cMsg, lMsgSize, &ulWritten );
		}

		if( SUCCEEDED(hr) )
		{
			hr = lpMemStream->SetPosition( 0 );
		}

		if ( hr == EMS_OK )
		{
			CEMSSitTokenizer *lpTokenizer = new CEMSSitTokenizer( lpMemStream );
			CEMSSitMessageBase *lpSitMsg=0;
			BOOL bLastSit = FALSE;

			if ( lpTokenizer )
			{
				hr = m_sitMsg.ParseMsgStart( lpTokenizer );

				if ( hr == EMS_OK )
					hr = m_sitMsg.ParseMsgHeader( lpTokenizer );

				while ( ( nCount < nMaxSits ) && ( hr == EMS_OK ) && !bLastSit )
				{
					hr = ParseSit( lpTokenizer, &lpSitMsg );

					if ( ( hr == EMS_OK ) && lpSitMsg )
					{
						hr = lpSitMsg->ParseSitTrailer( lpTokenizer, &bLastSit );

						lplpSitMsg[ nCount++ ] = lpSitMsg;
					}
				}

				if ( hr == EMS_OK )
					hr = m_sitMsg.ParseMsgTrailer( lpTokenizer );

				delete lpTokenizer;
				lpTokenizer = 0;
			}
			else
				hr = EMS_NO_MEMORY;

		}
		lpMemStream->Release();

		lpMemStream = 0;
	}

	if ( lpnSitCount )
		*lpnSitCount = nCount;  

	return hr;
}
