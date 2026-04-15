// EMSDBFConstellationManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "EMSDBFConstellationManager.h"

//std::string inputXmlFile = "C:\\OCC_Project\\EMSDBFConstellationManager\\EMSDBFConstellationManager\\DBFConstellation.xml";
std::string inputXmlFile = "C:\\HGT\\Config\\DBFConstellation.xml";

const std::string szFreqInmarSat = "1526.37";
const std::string cszFreqLeo = "1533.8";
const std::string cszFreqGalileo = "1533.4";
const std::string cszFreqGlonass = "1534.2";
const std::string cszFreqBeidou = "1533.51";


CEMSDBFConstellationManager::CEMSDBFConstellationManager()
{
	m_nSwitch = 0;
	m_szSynthesizerIP.clear();
	m_szEnvSensorIP.clear();
}

CEMSDBFConstellationManager::CEMSDBFConstellationManager(int iSwitch, std::string szSyntIP, std::string szEnvSensorIP):m_nSwitch(iSwitch),
														m_szSynthesizerIP(szSyntIP),m_szEnvSensorIP(szEnvSensorIP) 
{
}

CEMSDBFConstellationManager::~CEMSDBFConstellationManager()
{
	/* Close sg384 connection */
	getSynthsizer().CloseSynthesizerConnection();

	/* Close all SNMP sessions */
	getEnvSensor().CloseEnvSensorConnection();
}

bool CEMSDBFConstellationManager::ConnectToSynthsizer()
{
	bool ret = true;
	/* Connect to the sg384 */
	if(!getSynthsizer().ConnectToSynthesizer(m_szSynthesizerIP))
		ret = false;

	return ret;
}

bool CEMSDBFConstellationManager::ConnectToEnvSensor()
{
	bool ret = true;
	/*Initialise Environment sensor */
	if(!getEnvSensor().InitEnvSensor(m_szEnvSensorIP))
		ret = false;

	return ret;
}

bool CEMSDBFConstellationManager::DisplayConfiguration()
{
	bool ret = true;
	/* Display current sg384 configuration */
	if(!getSynthsizer().DisplaySynthesizerConfig())
		ret = false;
	//std::cout << " Outta Display Synthesizer " ;
	///* Display current Environment sensor configuration */
	//if(!getEnvSensor().DisplayEnvSensorConfig())
	//	ret = false;
	//std::cout << " Outta DisplayEnvSensorConfig " ;

	return ret;
}

void CEMSDBFConstellationManager::SetSatelliteConstellation(EMSCONSTELLATIONTYPE Constellation)
{
	switch(Constellation)
	{
		case GAL:  //Galileo
			{
				getSynthsizer().SetFrquency(cszFreqGalileo);
				//getEnvSensor().SetPolarisation(LHCP, m_nSwitch);
				getEnvSensor().SetPolarisation(RHCP, m_nSwitch);

			}
			break;
		case BEIDOU:	//Bideou
			{
				getSynthsizer().SetFrquency(cszFreqBeidou);
				//getEnvSensor().SetPolarisation(RHCP, m_nSwitch);
				getEnvSensor().SetPolarisation(LHCP, m_nSwitch);

			}
			break;
		case GLONASS:  //Glonass
			{
				getSynthsizer().SetFrquency(cszFreqGlonass);
				getEnvSensor().SetPolarisation(LHCP, m_nSwitch);
			}
			break;
		case LEO:	//Leo
			{
				getSynthsizer().SetFrquency(cszFreqLeo);
				//getEnvSensor().SetPolarisation(LHCP, m_nSwitch);
				getEnvSensor().SetPolarisation(RHCP, m_nSwitch);

			}
			break;
		case INMARSAT:  //Inmarsat
			{
				getSynthsizer().SetFrquency(szFreqInmarSat);
				getEnvSensor().SetPolarisation(RHCP, m_nSwitch);
			}
			break;
		case 49:
		case 113:
				break; 
		default:
			//std::cout << "Invalid Selection. Please try Again." << std::endl; 
			break;

	}
}


int CEMSDBFConstellationManager::Initialize(/*int iSwitch, std::string szSyntIP, std::string szEnvSensorIP*/)
{
	
	//Read config
	CEMSDBFConfigReader oCfg;
	oCfg.ReadDBFComputerXMLConfig(inputXmlFile.c_str());

	EMSDBFCOMPUTERCFG cfg = oCfg.GetDBFComputerCfg("computer1");
	//CEMSDBFConstellationManager oConMgr(, , );
	m_nSwitch = cfg.iSwitch;
	m_szSynthesizerIP = cfg.szSynthesizerIP;
	m_szEnvSensorIP = cfg.szEnvSensorIP;
	/*EMSDBFCOMPUTERCFG cfg1 = oCfg.GetDBFComputerCfg("computer2");
	CEMSDBFConstellationManager oConMgr2(cfg1.iSwitch, cfg1.szSynthesizerIP, cfg1.szEnvSensorIP);*/

	if(!ConnectToSynthsizer())
	{
		//std::cout<<" Connect to synthesizer failed "<<std::endl;
		return 1;
	}

	if(!ConnectToEnvSensor())
	{
		//std::cout<<" Connect to Environment sensor failed "<<std::endl;
		return 1;
	}

	DisplayConfiguration();
	//oConMgr2.DisplayConfiguration();

	//char input;
	//do
	//{
	//	std::string szInFrequency;
	//	__int64 i64Polarisation = -1;
	//	int iConstellation = 0;

	//	std::cout<<"Enter 1 to set frequency "<<std::endl;
	//	std::cout<<"Enter 2 to get frequency "<<std::endl;
	//	std::cout<<"Enter 3 to set polarisation "<<std::endl;
	//	std::cout<<"Enter 4 to get polarisation "<<std::endl;
	//	std::cout<<"Enter 5 to change constellation "<<std::endl;
	//	std::cout <<"Enter q to quit" << std::endl;
	//	std::cout << "Follow by return key in each case." << std::endl;
	//	std::cout << "Enter input: "; 
	//	std::cin>>input;
	//	switch(input)
	//	{
	//		case '1':
	//			std::cout<<"Enter Frequency in MHz: ";
	//			std::cin >> szInFrequency;
	//			oConMgr.SetFrquency(szInFrequency);
	//			break;
	//		case '2':
	//			oConMgr.GetFrequency();
	//			break;
	//		case '3':
	//			std::cout<<"Enter 0 for RHCP/S-BAND "<<std::endl;
	//			std::cout<<"Enter 1 for LHCP/L-BAND "<<std::endl;
	//			std::cout<<"Enter Polarisation (0/1) : ";
	//			std::cin >> i64Polarisation;
	//			oConMgr.SetPolarisation(i64Polarisation, cfg.iSwitch);
	//			break;
	//		case '4':
	//			oConMgr.GetPolarisation(cfg.iSwitch);
	//			break;
	//		case '5':
	//			std::cout<<"Enter 1 for Galileo "<<std::endl;
	//			std::cout<<"Enter 2 for Bideou "<<std::endl;
	//			std::cout<<"Enter 3 for Glonass "<<std::endl;
	//			std::cout<<"Enter 4 for Leo "<<std::endl;
	//			std::cout<<"Enter 5 for Inmarsat "<<std::endl;
	//			std::cout<<"Enter Constellation (1/2/3/4/5) : ";
	//			std::cin >> iConstellation;
	//			if((iConstellation >= 1) && (iConstellation <= 5))
	//				oConMgr.SetSatelliteConstellation(iConstellation);
	//			else
	//			{
	//				std::cout << "Invalid Selection." << std::endl; 
	//				input = 'q';
	//			}
	//			break;
	//		case 'Q':
	//		case 'q':
	//			break; 
	//		default:
	//			std::cout << "Invalid Selection. Please try Again." << std::endl; 
	//	}
	//}while(!((input == 'Q') ||(input == 'q')));


	return 0;
}

