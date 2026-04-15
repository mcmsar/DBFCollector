#include "DBFConstellation.hxx"
#include <vector>

struct EMSDBFCOMPUTERCFG
{
	int iSwitch;
	std::string szSynthesizerIP;
	std::string szEnvSensorIP;
	std::string szComputerId;
	float fFrequencyOffset;   // Hz – read from <FrequencyOffset> in DBFConstellation.xml; 0 if absent
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

