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
#pragma warning(disable:4786)

#include "streamdatachannel.h"
#include "streamsink.h"
#include "streamsource.h"
#include "logmsgparam.h"
#include "databaseresourcemsgs.h"
#include "arrayhelper.h"
#include "emsexcpt.h"

const ULONG CEMSStreamDataChannel::ms_culRetryWait = 500;	
const ULONG CEMSStreamDataChannel::ms_culMaxRetries = 10;
const ULONG CEMSStreamDataChannel::ms_culBytesPerRead = 4096;

CEMSStreamDataChannel::CEMSStreamDataChannel() : CEMSLogClient(L"CEMSStreamDataChannel")
{
}

CEMSStreamDataChannel::CEMSStreamDataChannel( const CEMSStreamDataChannel& x ) : CEMSLogClient(L"CEMSStreamDataChannel"),
																				m_owszURL( x.m_owszURL )
{
}

CEMSStreamDataChannel::~CEMSStreamDataChannel()
{
}

void 
CEMSStreamDataChannel::WriteData( const BYTE *pv, ULONG cb )
{
	try
	{
		m_ocsChannel.Enter();

		m_omapSinks.MoveFirst();

		CEMSStreamSink* pSink = m_omapSinks.GetNext();

		while( pSink )
		{
			EMS_RESULT hr = EMS_OK;
			ULONG cbWritten = 0;
			ULONG ulRetries = 0;

			do
			{
				hr = pSink->Write( pv, cb, &cbWritten );

				if( EMS_OVERFLOW == hr )
				{
					EMSLOG_DEBUG( this, L"Overflow occurred writing to data sink");
					Sleep( ms_culRetryWait );
					ulRetries++;
				}

			} while( EMS_OVERFLOW == hr && (ulRetries < ms_culMaxRetries) );

			if( EMS_OK != hr )
			{
				CEMSLogMsgParam oParam;
				oParam.AddX( hr );

				EMSLOGEX( this, EMSLogMsgWarn, EMS_DBRES_STREAM_WRITE_FAILURE, oParam );

				//throw CEMSException( EMS_DBRES_STREAM_WRITE_FAILURE, oParam );
			}

			if( cbWritten != cb )
			{
				CEMSLogMsgParam oParam;
				oParam.Add( cb );
				oParam.Add( cbWritten );

				EMSLOGEX( this, EMSLogMsgWarn, EMS_DBRES_STREAM_WRITE_UNDER, oParam );

				//throw CEMSException( EMS_DBRES_STREAM_WRITE_UNDER, oParam );
				
			}



			pSink->Release();
			pSink = 0;

			pSink = m_omapSinks.GetNext();
		}

		m_ocsChannel.Leave();

	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		throw;
	}
}

void 
CEMSStreamDataChannel::Cleanup()
{
	CEMSStreamSource* pSrc = 0;

	try
	{
		m_ocsChannel.Enter();

		m_omapSources.MoveFirst();

		pSrc = m_omapSources.GetNext();

		while( pSrc )
		{
			if( !pSrc->GetInUse() )
			{
				// It's no longer in use.  Does it still have unwritten data>
				if( !pSrc->HasData() )
				{
					m_omapSources.RemoveCurrent();
				}
			}

			pSrc->Release();
			pSrc = 0;

			pSrc = m_omapSources.GetNext();
		}

		m_ocsChannel.Leave();

	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		if( pSrc )
		{
			pSrc->Release();
			pSrc = 0;
		}


		throw;
	}
}

ULONG
CEMSStreamDataChannel::_AddSink( CEMSStreamSink* pSink )
{
	IEMSSeqStream* pKey = 0;
	ULONG ulRet = 0;

	try
	{
		m_ocsChannel.Enter();

		if( pSink )
		{
			pKey = pSink->GetStream();

			if( pKey )
			{
				m_omapSinks.Add( pKey, pSink );

				pKey->Release();
				pKey = 0;
			}

			ulRet = m_omapSinks.Count();

		}

		m_ocsChannel.Leave();
	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		if( pKey )
		{
			pKey->Release();
			pKey = 0;
		}

		throw;
	}

	return ulRet;
}

ULONG
CEMSStreamDataChannel::_RemoveSink( IEMSSeqStream* pStrm )
{
	ULONG ulRet = 0;

	try
	{
		m_ocsChannel.Enter();

		if( pStrm )
		{
			m_omapSinks.Remove( pStrm );
		}

		ulRet = m_omapSinks.Count();

		m_ocsChannel.Leave();
	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		throw;
	}

	return ulRet;
}

ULONG
CEMSStreamDataChannel::_AddSource( CEMSStreamSource* pSource )
{
	IEMSSeqStream* pKey = 0;
	ULONG ulRet = 0;

	try
	{
		m_ocsChannel.Enter();

		if( pSource )
		{
			pKey = pSource->GetStream();

			if( pKey )
			{
				m_omapSources.Add( pKey, pSource );

				pKey->Release();
				pKey = 0;
			}

			ulRet = m_omapSources.Count();

		}

		m_ocsChannel.Leave();
	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		if( pKey )
		{
			pKey->Release();
			pKey = 0;
		}

		throw;
	}

	return ulRet;
}

ULONG
CEMSStreamDataChannel::_RemoveSource( IEMSSeqStream* pStrm )
{
	ULONG ulRet = 0;

	CEMSStreamSource* pSrc = 0;

	try
	{
		m_ocsChannel.Enter();

		if( pStrm )
		{
			pSrc = m_omapSources.Get( pStrm );

			if( pSrc )
			{
				pSrc->SetInUse( false );
			}

			//m_omapSources.Remove( pStrm );
		}

		ulRet = m_omapSources.Count();

		m_ocsChannel.Leave();
	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		throw;
	}

	return ulRet;
}

ULONG 
CEMSStreamDataChannel::_ReadSources( BYTE*& rabyData )
{
	ULONG ulRet = 0;
	IEMSSeqStream* pStrm = 0;

	try
	{
		m_ocsChannel.Enter();

		m_omapSources.MoveFirst();

		pStrm = m_omapSources.GetNext();

		while( pStrm )
		{
			EMS_RESULT hr = EMS_OK;

			while( EMS_OK == hr )
			{
				BYTE abyData[ ms_culBytesPerRead ];
				ULONG ulRead = 0;

				hr = pStrm->Read( abyData, ms_culBytesPerRead, &ulRead );

				if( FAILED(hr) )
				{
					THROW_RUNTIME_EXCEPTION(hr);
				}

				if( ulRead > 0 )
				{
					CEMSArrayHelper::Concatenate( rabyData, ulRet, abyData, ulRead );
				}
			}

			pStrm->Release();
			pStrm = 0;

			pStrm = m_omapSources.GetNext();
		}

		m_ocsChannel.Leave();
	}
	catch( ... )
	{
		m_ocsChannel.Leave();

		if( rabyData )
		{
			delete[] rabyData;
			rabyData = 0;
		}

		if( pStrm )
		{
			pStrm->Release();
			pStrm = 0;
		}

		throw;
	}

	return ulRet;
}