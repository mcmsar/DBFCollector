#include "emserror.h"
#include "CriticalSection.h"

#define INITGUID			
#include <initguid.h>
#include "bdwsclientclsid.h"
#include "BeaconDecoder.h"

#include "CBcnMsgDecode.h"

CBcnMsgDecode::CBcnMsgDecode() : m_pDecoderWS(NULL)
{
}

CBcnMsgDecode::~CBcnMsgDecode()
{
	if ( m_pDecoderWS )
	{
		m_pDecoderWS->Release();
		m_pDecoderWS = NULL;
	}
}

void
CBcnMsgDecode::_DecodeLocation( CBeaconMessage& cbcnmsg )
{
	assert( _HaveData() );

	bool		bHaveDecode = false;

	if ( _InitWebServiceConnection() )
	{
		EMSBEACONLOCATION	bcnLoc;
		memset( &bcnLoc, 0, sizeof(EMSBEACONLOCATION) );

		// Use the web service
		EMS_RESULT	hr = m_pDecoderWS->GetBeaconLocation( cbcnmsg.Hex36(), &bcnLoc );
		if ( SUCCEEDED(hr) )
		{
			m_bHasEncodedLocation	= bcnLoc.bHasGPSLocation ? true : false;
			m_dEncodedLat			= bcnLoc.dLat;
			m_dEncodedLong			= bcnLoc.dLong;

			bHaveDecode = true;
		}
	}

	if ( !bHaveDecode )
	{
		// Defer to the the base class implementation
		CBcnMsgDecodeBase::_DecodeLocation( cbcnmsg );
	}
}


bool
CBcnMsgDecode::_InitWebServiceConnection()
{
	EMS_RESULT			hr = EMS_OK;
	static bool			sbAlreadyTried = false;
	static bool			sbAvailable = true;

	// Nothing to do if we have already figured out that
	// the web service is not available 
	if ( sbAlreadyTried && !sbAvailable )  return false;

	// Only do within a critical section if this is the first time trying ...
	// Note that I am trying to limit the number of times that we have a failed call 
	// to CoCreateInstance().  My recollection is that these are expensive!
	if ( !sbAlreadyTried )
	{
		static	CEMSCriticalSection	soCS;
		soCS.Enter();
		try
		{
			hr = CoCreateInstance( CLSID_EMSBDWSClient, NULL, CLSCTX_ALL, 
					IID_IEMSBeaconDecoder, (void**) &m_pDecoderWS );
			
			if ( FAILED(hr) )
			{
				sbAvailable = false;
			}
			else
			{
				sbAvailable = true;
			}
			// regardless --- we've tried
			sbAlreadyTried = true;

			soCS.Leave();
		}
		catch(...)
		{
			if ( m_pDecoderWS ) 
			{
				m_pDecoderWS->Release();
				m_pDecoderWS = NULL;
			}

			// Assume the worst
			sbAlreadyTried = true;
			sbAvailable = false;

			soCS.Leave();
		}
	}

	if ( sbAvailable && !m_pDecoderWS )
	{
		hr = CoCreateInstance( CLSID_EMSBDWSClient, NULL, CLSCTX_ALL, 
				IID_IEMSBeaconDecoder, (void**) &m_pDecoderWS );
	}

	// Note this code assumes that an error is simply an indication that the 
	// web service is unavailable

	// Only proceed if we have a web service connection
	return ( m_pDecoderWS ? true : false );
}
