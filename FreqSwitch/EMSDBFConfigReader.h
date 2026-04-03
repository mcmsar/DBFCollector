#include "DBFConstellation.hxx"
#include <vector>

struct EMSDBFCOMPUTERCFG
{
	int iSwitch;
	std::string szSynthesizerIP;
	std::string szEnvSensorIP;
	std::string szComputerId;
};

#pragma once

class CEMSDBFConfigReader
{
public:
	CEMSDBFConfigReader();
	~CEMSDBFConfigReader();
	
	void ReadDBFComputerXMLConfig(const char *inFile);

	EMSDBFCOMPUTERCFG GetDBFComputerCfg(std::string szComputerId);


private:

private:

	std::vector<EMSDBFCOMPUTERCFG>		m_dbfComputerCfg;
};

