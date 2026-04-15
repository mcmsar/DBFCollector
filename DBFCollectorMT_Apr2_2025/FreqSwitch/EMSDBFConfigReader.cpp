#include "EMSDBFConfigReader.h"
#include <iostream>
//snl
#include "emsdbf.h"

CEMSDBFConfigReader::CEMSDBFConfigReader(void)
{
}


CEMSDBFConfigReader::~CEMSDBFConfigReader(void)
{
}

EMSDBFCOMPUTERCFG 
CEMSDBFConfigReader::GetDBFComputerCfg(std::string szComputerId)
{
	EMSDBFCOMPUTERCFG computerCfg;

	for(unsigned int iCount = 0; iCount < m_dbfComputerCfg.size(); iCount++)
	{
		if(m_dbfComputerCfg[iCount].szComputerId == szComputerId)
		{
			computerCfg = m_dbfComputerCfg[iCount];
			break;
		}
	}

	return computerCfg;
}

void CEMSDBFConfigReader::ReadDBFComputerXMLConfig(const char *inFile)
{
	try
	{
		::std::auto_ptr< ::dbfconstellation::computers > dbComputerCfg (::dbfconstellation::computers_(inFile));
		std::string szConnectInfo = std::string("<Connection><ip_address>")  + dbComputerCfg->SP() + std::string("</ip_address><port_id>9070</port_id></Connection>");

		//CDigitalBeamFormer::SetSPIP( szConnectInfo );
		for(::dbfconstellation::computers::computer_const_iterator iter (dbComputerCfg->computer().begin());
				iter != dbComputerCfg->computer().end(); ++iter)
		{
			EMSDBFCOMPUTERCFG computerCfg;

			computerCfg.szComputerId = iter->id();
			computerCfg.iSwitch = iter->Switch();
			computerCfg.szEnvSensorIP = iter->EnvSensorIP();
			computerCfg.szSynthesizerIP = iter->SynthesizerIP();
			computerCfg.fFrequencyOffset = iter->FrequencyOffset().present()
			                               ? iter->FrequencyOffset().get()
			                               : 0.0f;

			m_dbfComputerCfg.push_back(computerCfg);
		}

	}
	catch (const xml_schema::exception& e)
	{
		std::cerr << e << std::endl;
		return;
	}
}