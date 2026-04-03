// EMSDBFEnvSensor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EMSDBFEnvSensor.h"
#include "Winsnmp.h"
#include "EMSSNMPManager.h"
#include "EMSSNMPException.h"

//std::string host = "1.1.1.14"; //DBF rack
//std::string host = "1.1.1.15";
std::string community = "public";
int tmo = 1000; //Timeout
unsigned int port = 0;	

CEMSDBFEnvSensor::CEMSDBFEnvSensor()
{
	//m_szEnvSensorHostStr = "1.1.1.14";  //DBF rack
	//m_szEnvSensorHostStr = "1.1.1.15";	//Test Lab
}

CEMSDBFEnvSensor::~CEMSDBFEnvSensor()
{
}

void CEMSDBFEnvSensor:: CloseEnvSensorConnection()
{
	EMSSNMPManager::getManager()->cleanUp();
}

bool CEMSDBFEnvSensor::InitEnvSensor(std::string inputHost)
{
	bool ret = true;

	if(!inputHost.empty())
		m_szEnvSensorHostStr = inputHost;
	else
		return false;

	try
	{
		EMSSNMPManager::getManager()->startup();
		//std::cout<<"SNMP Manager started "<<std::endl;
	}
	catch(EMSSNMPException * pe)
	{
		ret = false;
		//std::cout << "\n\n";
		//std::cout << pe->toStringStack();
		//std::cout << "\n";
		delete pe;
	}

	return ret;
}

bool CEMSDBFEnvSensor::DisplayEnvSensorConfig()
{
	_getInternalTmp();
	_getInternalHumidity();
	_getInternalPower();
	_getInternalHeatIndex();
	GetPolarisation(1);   //Switch -1
	GetPolarisation(2);	  // Switch -2

	return true;
}

void CEMSDBFEnvSensor::SetPolarisation(__int64 i64Polarisation, int iSwitch)
{
	int type = SNMP_INT;
	std::string szSwitchOid;

	switch(iSwitch)
	{
		case 1:
			szSwitchOid = _getSwitch1Oid();
			break;
		case 2:
			szSwitchOid = _getSwitch2Oid();
			break;
		default:
			break;
	}
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);

	EMSSNMPObject obj(szSwitchOid);
	obj.setSyntax(type);

	obj.setValueAsInteger(i64Polarisation);
	EMSSNMPRemoteAgentSetRequest setReq(&obj);
	setReq.execute(&ragent);
	setReq.wait(tmo);
	if(!setReq.succeeded()) 
	{
		if(!setReq.timedOut()) 
		{
			//std::cout << setReq.getErrorAsString();
		} 
		else 
		{
			//std::cout << "timeout - SetPolarisation()";
		}
	} 
	else 
	{
		/*if(iSwitch == 1)
			std::cout<<"Polarisation (Switch-1) set to:"<<setReq.getResult(0)->getValueAsInteger()<<std::endl;
		if(iSwitch == 2)
			std::cout<<"Polarisation (Switch-2) set to:"<<setReq.getResult(0)->getValueAsInteger()<<std::endl;*/
	}
}

__int64 CEMSDBFEnvSensor::GetPolarisation(int iSwitch)
{

	__int64 i64Polarisation = -1;

	std::string szSwitchOid;

	switch(iSwitch)
	{
		case 1:
			szSwitchOid = _getSwitch1Oid();
			break;
		case 2:
			szSwitchOid = _getSwitch2Oid();
			break;
		default:
			break;
	}

	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szSwitchOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - GetPolarisation()";
		}
	} 
	else 
	{
		i64Polarisation = getReq.getResult(0)->getValueAsInteger();
		/*if(iSwitch == 1)
			std::cout<<"Polarisation (Switch-1) :"<<i64Polarisation<<std::endl;
		if(iSwitch == 2)
			std::cout<<"Polarisation (Switch-2) :"<<i64Polarisation<<std::endl;*/
	}

	return i64Polarisation;
}

std::string CEMSDBFEnvSensor::_getMacAddress()
{
	std::string szMACOid =  _getMacAddressOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szMACOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getMacAddress()";
			return "";
		}
	} 
	else 
	{
		for(int i=0; i<getReq.getResultCount(); i++) 
		{	
			//std::cout << getReq.getResult(i)->getValueAsString() << "\n";
		}
	}

	return getReq.getResult(0)->getValueAsString();
}


std::string CEMSDBFEnvSensor::_getSerialNumber()
{
	std::string szSNOid =  _getSerialNumberOid();

	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szSNOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getSerialNumber()";
			return "";
		}
	} 
	else 
	{
		for(int i=0; i<getReq.getResultCount(); i++) 
		{	
			//std::cout << getReq.getResult(i)->getValueAsString() << "\n";
		}
	}

	return getReq.getResult(0)->getValueAsString();
}

std::string CEMSDBFEnvSensor::_getIpAddress()
{
	std::string szIPOid = _getIpAddressOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szIPOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getIpAddress()";
			return "";
		}
	} 
	else 
	{
		for(int i=0; i<getReq.getResultCount(); i++) 
		{	
			//std::cout << getReq.getResult(i)->getValueAsString() << "\n";
		}
	}

	return getReq.getResult(0)->getValueAsString();
}

std::string CEMSDBFEnvSensor::_getInternalTmp()
{
	std::string szInternalTmp;
	std::string szInternalTmpOid = _getInternalTmpOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
	
	//std::cout<<"szInternalTmpOid = "<<szInternalTmpOid<<std::endl;
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szInternalTmpOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	//std::cout<<"After getReq.execute"<<std::endl;
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getInternalTmp()";
			return "";
		}
	} 
	else 
	{
		szInternalTmp = getReq.getResult(0)->getValueAsString();
		int position = szInternalTmp.length() - 2;
		szInternalTmp.insert(position, 1, '.');
		//std::cout << "Internal Temp(Farenhit): "<<szInternalTmp<< std::endl;
	}

	return szInternalTmp;
}

std::string CEMSDBFEnvSensor::_getInternalHumidity()
{
	std::string szInternalHumidity;

	std::string szHumidityOid = _getInternalHumidityOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szHumidityOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getInternalHumidity() ";
			return "";
		}
	} 
	else 
	{
		szInternalHumidity = getReq.getResult(0)->getValueAsString();
		int position = szInternalHumidity.length() - 2;
		szInternalHumidity.insert(position, 1, '.');
		//std::cout << "Internal Humidity: "<<szInternalHumidity<< std::endl;
	}

	return szInternalHumidity;
}

std::string CEMSDBFEnvSensor::_getInternalPower()
{
	std::string szInternalPower;
	std::string szInternalPowerOid =  _getInternalPowerOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szInternalPowerOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getInternalPower()";
			return "";
		}
	} 
	else 
	{
		szInternalPower = getReq.getResult(0)->getValueAsString();
		//std::cout << "Internal Power: "<<szInternalPower<< std::endl;
	}

	return szInternalPower;
}

std::string CEMSDBFEnvSensor::_getInternalHeatIndex()
{
	std::string szInternalHeatIndex;
	std::string szHeatIndexOid =  _getInternalHeatIndexOid();
	EMSSNMPRemoteAgent ragent(m_szEnvSensorHostStr, community, port);
		
	EMSSNMPObject * oid = new EMSSNMPObject();
	oid->setOID(szHeatIndexOid);
	EMSSNMPRemoteAgentGetRequest getReq(oid);
	getReq.execute(&ragent);
	getReq.wait(tmo);
	delete oid;
	if(!getReq.succeeded()) 
	{
		if(!getReq.timedOut()) 
		{
			//std::cout << getReq.getErrorAsString();
		} else 
		{
			//std::cout << "timeout - _getInternalHeatIndex() ";
			return "";
		}
	} 
	else 
	{
		szInternalHeatIndex = getReq.getResult(0)->getValueAsString();
		int position = szInternalHeatIndex.length() - 2;
		szInternalHeatIndex.insert(position, 1, '.');
		//std::cout << "Internal Heat Index: "<<szInternalHeatIndex<< std::endl;
	}

	return szInternalHeatIndex;
}
