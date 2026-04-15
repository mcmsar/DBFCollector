
#include "aobjbase.h"
#include "igateway.h"
#include "emspipe.h"
#include "imsgbody.h"
#include "binmsgbody.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "variantrecordwrapper.h"


CEMSBinMsgBody::CEMSBinMsgBody() : m_pStrm(0)
{
}

CEMSBinMsgBody::CEMSBinMsgBody( const CEMSBinMsgBody& binMsgBody ) : m_pStrm(0)
{
	if( binMsgBody.m_pStrm )
	{
		m_pStrm = binMsgBody.m_pStrm;
		m_pStrm->AddRef();
	}
}

CEMSBinMsgBody::~CEMSBinMsgBody()
{
	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = 0;
	}
}

void
CEMSBinMsgBody::SetStream( IEMSSeqStream* pStrm )
{
	if( !pStrm )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( m_pStrm )
	{
		m_pStrm->Release();
		m_pStrm = 0;
	}

	m_pStrm = pStrm;
	m_pStrm->AddRef();
}

EMSVARIANTRECORD3* 
CEMSBinMsgBody::ReadNext3()
{
	EMSVARIANTRECORD3* pRet = NULL;
	EMSVARIANTRECORD2* pRecord2 = NULL;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		pRecord2 = ReadNext2();

		if( pRecord2 )
		{
			CEMSVariantRecord3 oVarRec;

			pRet = new EMSVARIANTRECORD3;

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			// convert V2 to V3
			oVarRec.SetData( *pRecord2 );

			*pRet = oVarRec.Get();
			delete pRecord2;
			pRecord2 = NULL;
		}
	}
	catch( ... )
	{
		if( pRet )
		{
			delete pRet;
			pRet = NULL;
		}

		if( pRecord2 )
		{
			delete pRecord2;
			pRecord2 = NULL;
		}

		throw;
	}

	return pRet;
}


void
CEMSBinMsgBody::WriteRecord3( const EMSVARIANTRECORD3& record )
{
	EMSVARIANTRECORD2  emsVarRec2;
	CEMSVariantRecord3 oVarRec(record);

	oVarRec.GetVarRecord2(emsVarRec2);
	
	WriteRecord2( emsVarRec2 );
}
