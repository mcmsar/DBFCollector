#include <pksource.h>
#include <emsexcpt.h>
#include <leodefns.h>
#include <commandformats.h>
#include <gatewaydata.h>

CEMSGatewayData::CEMSGatewayData() :
   m_pDataPipeline( 0 ),
   m_pConfigDataSrc( 0 )
{
}

CEMSGatewayData::~CEMSGatewayData()
{
   _ReleaseObjects();
}

void
CEMSGatewayData::_ReleaseObjects()
{
   if ( m_pDataPipeline )
   {
      if ( m_pConfigDataSrc )
      {
         m_pDataPipeline->UnRegisterSource( m_pConfigDataSrc );

         m_pConfigDataSrc->Release();
         m_pConfigDataSrc = 0;
      }
      m_pDataPipeline->Release();
      m_pDataPipeline = 0;
   }
}

IEMSDataPipeline*
CEMSGatewayData::_GetDataPipeline()
{
   EMS_RESULT hr = EMS_OK;

   if ( !m_pDataPipeline )
   {
      // Data pipeline
      hr = CoCreateInstance( CLSID_EMSDataPipeline, 0, CLSCTX_ALL, 
                  IID_IEMSDataPipeline, (LPVOID*)&m_pDataPipeline );

      if ( FAILED(hr) )
      {
         THROW_RUNTIME_EXCEPTION( hr );
      }
      if ( !m_pDataPipeline )
      {
         THROW_NOMEMORY_EXCEPTION();
      }
   }
   return m_pDataPipeline;
}

CEMSPacketSource*
CEMSGatewayData::_GetConfigDataSrc()
{
   EMS_RESULT hr = EMS_OK;

   if ( !m_pConfigDataSrc )
   {
      m_pDataPipeline = _GetDataPipeline();

      if ( m_pDataPipeline )
      {
         m_pConfigDataSrc = new CEMSPacketSource( LUT_CONFIG_GET, sizeof( EMSFIXEDVARITYPE ) );
         if ( !m_pConfigDataSrc )
         {
            THROW_NOMEMORY_EXCEPTION();
         }

         hr = m_pDataPipeline->RegisterSource( m_pConfigDataSrc );
         if ( FAILED(hr) )
         {
            THROW_RUNTIME_EXCEPTION( hr );
         }
      }
   }
   return m_pConfigDataSrc;
}

void
CEMSGatewayData::SendConfigData( const EMSVARITYPE* const pData )
{
   EMS_RESULT hr = EMS_OK;

   if ( pData )
   {
      EMSFIXEDVARITYPE  fixedData;

      memset( &fixedData, 0, sizeof(fixedData) );

      if ( EMSVARITYPE_DATATYPE_STRING ==  pData->dataType )
      {
         if ( pData->pwcsVal )
         {
            fixedData.dataType = EMSVARITYPE_DATATYPE_STRING;

            wcsncpy( fixedData.wszVal, pData->pwcsVal,  MAX_CONFIG_STRING_VALUE_LENGTH );
         }
         else
         {
         }
      }
      else
      {
         memcpy( &fixedData, pData, sizeof(fixedData) );
      }

      m_pConfigDataSrc = _GetConfigDataSrc();

      if ( m_pConfigDataSrc )
      {
         if ( m_pDataPipeline )
         {
            EMSDATACHANNELINFO channelInfo;

            hr = m_pDataPipeline->GetChannelInfo( LUT_CONFIG_GET, &channelInfo );

            if (  ( EMS_OK == hr ) 
               && ( channelInfo.wSinks > 0 )
               && ( m_pConfigDataSrc )
               )
            {
               unsigned long ulBytesWritten = 0;

               hr = m_pConfigDataSrc->Write( reinterpret_cast<LPBYTE>(&fixedData), 
                                             sizeof( fixedData ), &ulBytesWritten );

			   if( FAILED(hr) )
			   {
				   THROW_RUNTIME_EXCEPTION( hr );
			   }
            }
         }
      }
   }
   else
   {
	   THROW_NULL_POINTER_EXCEPTION();
   }
}


