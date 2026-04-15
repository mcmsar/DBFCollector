#include <iostream>
#include <string>

class CEMSDBFEnvSensor
{
public:
	CEMSDBFEnvSensor();
	~CEMSDBFEnvSensor();

	bool InitEnvSensor(std::string inputHost);
	__int64 GetPolarisation(int iSwitch);
	void SetPolarisation(__int64 i64Polarisation, int iSwitch);
	bool DisplayEnvSensorConfig();
	void CloseEnvSensorConnection();

private:
	std::string _getInternalTmp();
	std::string _getInternalHumidity();
	std::string _getInternalPower();
	std::string _getInternalHeatIndex();
	std::string _getSerialNumber();
	std::string _getMacAddress();
	std::string _getIpAddress();

	/* Set/Get the OIDs */
	void _setIpAddressOid(std::string szOid){}
	std::string _getIpAddressOid()
	{
		std::string szIPOid = "1.3.6.1.2.1.4.20.1.1.1.1.1.15.0";
		return szIPOid;
	}

	void _setMacAddressOid(std::string szOid){}
	std::string _getMacAddressOid()
	{
		std::string szMACOid = "1.3.6.1.2.1.2.2.1.6.1";
		return szMACOid;
	}

	void _setSerialNumberOid(std::string szOid){}
	std::string _getSerialNumberOid()
	{
		std::string szSNOid = "1.3.6.1.2.1.1.1.0";
		return szSNOid;
	}

	void _setInternalHeatIndexOid(std::string szHeatIndexOid){}
	std::string _getInternalHeatIndexOid()
	{
		std::string szHeatIndexOid = "1.3.6.1.4.1.20916.1.8.1.1.4.1.0";
		return szHeatIndexOid;
	}

	void _setInternalPowerOid(std::string szInternalPowerOid){}
	std::string _getInternalPowerOid()
	{
		std::string szInternalPowerOid = "1.3.6.1.4.1.20916.1.8.1.1.3.1.0";
		return szInternalPowerOid;
	}

	void _setInternalHumidityOid(std::string szHumidityOid){}
	std::string _getInternalHumidityOid()
	{
		std::string szHumidityOid = "1.3.6.1.4.1.20916.1.8.1.1.2.1.0";
		return szHumidityOid;
	}

	void _setInternalTmpOid(std::string szInternalTmpOid){}
	std::string _getInternalTmpOid()
	{
		std::string szInternalTmpOid = "1.3.6.1.4.1.20916.1.8.1.1.1.1.0";
		return szInternalTmpOid;
	}

	std::string _getSwitch1Oid()
	{
		std::string szSwitch1Oid = "1.3.6.1.4.1.20916.1.8.1.1.6.1.0";  //Switch 1
		return szSwitch1Oid;
	}
	
	std::string _getSwitch2Oid()
	{
		std::string szSwitch2Oid = "1.3.6.1.4.1.20916.1.8.1.1.6.2.0";  //Switch 2
		return szSwitch2Oid;
	}

private:
	std::string m_szEnvSensorHostStr;
};