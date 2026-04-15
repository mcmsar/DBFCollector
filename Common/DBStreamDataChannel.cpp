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

#include "dbstreamdatachannel.h"
#include "dbretriever.h"
#include "databaseresourcemsgs.h"
#include "emsexcpt.h"
#include "streamsink.h"
#include "streamsource.h"

CEMSDBStreamDataChannel::CEMSDBStreamDataChannel() :	m_pDB(0), m_ulSrcID(0), m_ulDestID(0),
														m_ulTestPeriod(0), m_ulChunkSize(0)
{
	 SetParent( L"CEMSDBStreamChannel" );
}

CEMSDBStreamDataChannel::CEMSDBStreamDataChannel( const CEMSDBStreamDataChannel& x ) :
															CEMSStreamDataChannel( x ),
															m_pDB( x.m_pDB ), m_owszRoute( x.m_owszRoute ),
															m_ulSrcID( x.m_ulSrcID ), m_ulDestID( x.m_ulDestID ),
															m_owszSQL( x.m_owszSQL ), m_owszSrcTable( x.m_owszSrcTable ),
															m_owszSrcColumn( x.m_owszSrcColumn ),
															m_owszCriteria( x.m_owszCriteria ), 
															m_ulTestPeriod( x.m_ulTestPeriod ),
															m_owszDBConn( x.m_owszDBConn ),
															m_ulChunkSize( x.m_ulChunkSize )
{
	SetParent( L"CEMSDBStreamChannel" );

	if( m_pDB )
		m_pDB->AddRef();
}

CEMSDBStreamDataChannel::~CEMSDBStreamDataChannel()
{
	_ReleaseRetriever();
}

void 
CEMSDBStreamDataChannel::ConnectSinkStream( IEMSSeqStream*& pSink, const wchar_t* cwszSignalName,
											const ULONG culMaxBufferSize )
{
	if( !cwszSignalName )
	{
		throw CEMSException( EMS_DBRES_DATA_CHANNEL_NO_SIGNAL );
	}

	CEMSStreamSink* pNewSink = 0;

	try
	{
		pNewSink = new CEMSStreamSink;

		if( !pNewSink )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		pNewSink->SetSignalName( cwszSignalName );
		pNewSink->SetMaxBufferSize( culMaxBufferSize );

		_AddSink( pNewSink );

		pSink = pNewSink->GetStream();

		pNewSink->Release();
		pNewSink = 0;
	
	}
	catch( ... )
	{
		if( pNewSink )
		{
			pNewSink->Release();
			pNewSink = 0;
		}

		if( pSink )
		{
			pSink->Release();
			pSink = 0;
		}

		throw;
	}
}

void 
CEMSDBStreamDataChannel::DisconnectSinkStream( IEMSSeqStream* pSink )
{
	try
	{
		if( 0 == _RemoveSink( pSink ) )
		{
			_ReleaseRetriever();
		}
	}
	catch( ... )
	{
		throw;
	}
}

void 
CEMSDBStreamDataChannel::ConnectSourceStream( IEMSSeqStream*& pSource, const wchar_t* cwszSignalName,
									const ULONG culMaxBufferSize )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSDBStreamDataChannel::DisconnectSourceStream( IEMSSeqStream* pSink )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void 
CEMSDBStreamDataChannel::Activate()
{
	_ConnectRetriever();
}

void 
CEMSDBStreamDataChannel::Deactivate()
{
	_ReleaseRetriever();
}

void 
CEMSDBStreamDataChannel::GetMetaData( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields )
{
	if( m_pDB )
	{
		m_pDB->GetMetaData( ulFields, aFields );
	}
}

void 
CEMSDBStreamDataChannel::_ReleaseRetriever()
{
	if( m_pDB )
	{
		m_pDB->Release();
		m_pDB = 0;
	}
}

void 
CEMSDBStreamDataChannel::_ConnectRetriever()
{
	if( !m_pDB )
	{
		m_pDB = new CEMSDBRetriever;

		if( !m_pDB )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		m_pDB->SetRoute( m_owszRoute.c_str() );
		m_pDB->SetSrcDestID( m_ulSrcID, m_ulDestID );
		m_pDB->SetSQL( m_owszSQL.c_str() );
		m_pDB->SetActive( m_owszSrcTable.c_str(), m_owszSrcColumn.c_str(), m_owszCriteria.c_str(), 
							m_ulTestPeriod );
		//m_pDB->SetEventName( m_owszEventName.c_str() );
		m_pDB->SetCallback( this );
		m_pDB->SetDBConnection( m_owszDBConn.c_str() );
		m_pDB->SetChunkSize( m_ulChunkSize );

	}
	else
	{
		// Ask it to refresh so that the new sink gets some data.
		// This is done by stopping and starting it.
		m_pDB->Stop();
	}

	m_pDB->start();
}