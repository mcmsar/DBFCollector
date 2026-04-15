#ifndef __GATEWAYDATA_H__
#define __GATEWAYDATA_H__

#include <emspipe.h>
#include <configmanagertypes.h>

class CEMSPacketSource;

//! @class CEMSGatewayData
//! This class is used for sending data to the Gateway over the EMSPipeline.

class CEMSGatewayData
{
public:

   CEMSGatewayData();
   virtual ~CEMSGatewayData();

   void SendConfigData( const EMSVARITYPE* const pData );

protected:

   void                 _ReleaseObjects();
   IEMSDataPipeline*    _GetDataPipeline();
   CEMSPacketSource*    _GetConfigDataSrc();

protected:
   IEMSDataPipeline*                   m_pDataPipeline;
   CEMSPacketSource*                   m_pConfigDataSrc;
};


#endif // __GATEWAYDATA_H__

