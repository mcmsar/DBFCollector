// EMSDBFSynthesizer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "EMSDBFSynthesizer.h"
#include "Winsock2.h"
#include <stdio.h>


using namespace std;

SOCKET sSG384; /* sg384 tcpip socket */
unsigned sg_timeout = 6000; /* Read timeout in milliseconds */


CEMSDBFSynthesizer::CEMSDBFSynthesizer()
{
	//m_szSynthHostStr = "1.1.1.102"; //DBF rack
	//m_szSynthHostStr = "1.1.1.103";   //Test lab
	/* Initialize the sockets library */
	init_tcpip();
}

CEMSDBFSynthesizer::~CEMSDBFSynthesizer()
{
	//char buffer[1024];
	/* Make sure all commands have executed before closing connection */
	//sg_write("*opc?\n");
	//if ( !sg_read(buffer,sizeof(buffer)) )
	//	printf("Timeout\n");

}

void CEMSDBFSynthesizer::CloseSynthesizerConnection()
{
	/* Close the connection */
	if (sg_close())
		printf("Closed connection to Synthesizer\n");
	else
		printf("Unable to close connection\n");
}

void CEMSDBFSynthesizer::init_tcpip(void)
{
	 WSADATA wsadata;
	 if ( WSAStartup(2, &wsadata) != 0 ) 
	 {
		 printf("Unable to load windows socket library\n");
		 //exit(1);
		 return;
	}
}

int CEMSDBFSynthesizer::sg_write_bytes(const void *data, unsigned num)
{
	 /* Write string to connection */
	 int result;

	 result = send(sSG384,(const char *)data,(int)num,0);
	 if ( SOCKET_ERROR == result )
		result = 0;
	 return result;
}
int CEMSDBFSynthesizer::sg_read(char *buffer, unsigned num)
{
	 /* Read up to num bytes from connection */
	 int count;
	 fd_set setRead, setWrite, setExcept;
	 TIMEVAL tm;

	 /* Use select() so we can timeout gracefully */
	 tm.tv_sec = sg_timeout/1000;
	 tm.tv_usec = (sg_timeout % 1000) * 1000;
	 FD_ZERO(&setRead);
	 FD_ZERO(&setWrite);
	 FD_ZERO(&setExcept);
	 FD_SET(sSG384,&setRead);
	 count = select(0,&setRead,&setWrite,&setExcept,&tm);
	 if ( count == SOCKET_ERROR ) 
	 {
		 printf("select failed: connection aborted\n");
		 closesocket(sSG384);
		 //exit(1);
		 return 1;
	 }
	 count = 0;
	 if ( FD_ISSET(sSG384,&setRead) ) 
	 {
		 /* We've received something */
		 count = (int)recv(sSG384,buffer,num-1,0);
		 if ( SOCKET_ERROR == count ) 
		 {
			 printf("Receive failed: connection aborted\n");
			 closesocket(sSG384);
			 //exit(1);
			 return 1;
		 }
		 else if (count ) 
		 {
			buffer[count] = '\0';
		 }
		 else 
		 {
			 printf("Connection closed by remote host\n");
			 closesocket(sSG384);
			 //exit(1);
			 return 1;
		}
	 }
	 return count;
}

int CEMSDBFSynthesizer::sg_connect(unsigned long ip)
{
	 /* Connect to the sg384 */
	 struct sockaddr_in intrAddr;
	 int status;
	 sSG384 = socket(AF_INET,SOCK_STREAM,0);
	 if ( sSG384 == INVALID_SOCKET )
		return 0;
	 /* Bind to a local port */
	 memset(&intrAddr,0,sizeof(intrAddr));
	 intrAddr.sin_family = AF_INET;
	 intrAddr.sin_port = htons(0);
	 intrAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	 if ( SOCKET_ERROR == bind(sSG384,(const struct sockaddr *)&intrAddr,sizeof(intrAddr)) ) 
	 {
		 closesocket(sSG384);
		 sSG384 = INVALID_SOCKET;
		 return 0;
	 }
	 /* Setup address for the connection to sg on port 5025 */
	 memset(&intrAddr,0,sizeof(intrAddr));
	 intrAddr.sin_family = AF_INET;
	 intrAddr.sin_port = htons(5025);
	 intrAddr.sin_addr.S_un.S_addr = ip;
	 status = connect(sSG384,(const struct sockaddr *)&intrAddr,sizeof(intrAddr));
	 if ( status ) 
	 {
		 closesocket(sSG384);
		 sSG384 = INVALID_SOCKET;
		 return 0;
	 }

	return 1;
}
int CEMSDBFSynthesizer::sg_close(void)
{
	if ( closesocket(sSG384) != SOCKET_ERROR )
		return 1;
	else
		return 0;
}
int CEMSDBFSynthesizer::sg_write(char *str)
{
	 /* Write string to connection */
	 int result;

	 result = send(sSG384,str,(int)strlen(str),0);
	 if ( SOCKET_ERROR == result )
		result = 0;
	 return result;
}

bool CEMSDBFSynthesizer::ConnectToSynthesizer(std::string inputHost)
{
	char buffer[1024];
	bool ret = true;

	if ( sg_connect( inet_addr(inputHost.c_str()) ) ) 
	{

		/* Get identification string */
		sg_write("*idn?\n");
		if ( sg_read(buffer,sizeof(buffer)) )
		{
			std::cout<< "Connected to " << buffer << std::endl;
			//printf(buffer);
		}
		else
		{
			printf("Timeout while reading identification string\n");
			ret = false;
		}
	}
	else
	{
		//std::cout<<"Connection Failed (SG384):"<<inputHost<<std::endl;
		ret = false;
	}

	return ret;
}

std::string CEMSDBFSynthesizer::_getFrequency()
{
	/* Get frequency in MHz*/
	std::string buffer;
	std::string szFreq;
	sg_write("freq? MHz\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		szFreq = buffer.c_str();
		//std::cout<<"Frequency :"<<szFreq;
	}
	else
	{
		//printf("Timeout while reading Current frequency\n");
	}

	return szFreq;
}

std::string CEMSDBFSynthesizer::_getPhase()
{
	/* Get Phase */
	std::string buffer;
	sg_write("phas?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Phase :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Current phase"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getAmplitudeOfLf()
{
	/* Get BNC output*/
	std::string buffer;
	sg_write("ampl?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Amplitude of LF (BNC output) :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Ampitude of LF(BNC output)"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getAmplitudeOfRf()
{
	/* Get Amplitude of RF (Type-N output) */
	std::string buffer;
	sg_write("ampr?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Amplitude of RF (Type-N output) :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Amplitude of RF (Type-N output)"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getModulationType()
{
	/* Get Modulation type */
	std::string buffer;
	sg_write("type?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Modulation type :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Modulation type"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getModulationFunction()
{
	/* Get Modulation function */
	std::string buffer;
	sg_write("mfnc?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Modulation function :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Modulation function"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getModulationRate()
{
	/* Get Modulation rate */
	std::string buffer;
	sg_write("rate?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Modulation rate :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Modulation rate"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getAmplitudeOfClkOutput()
{
	/* Get Amplitude of clock output */
	std::string buffer;
	sg_write("ampc?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Amplitude of clock output :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Amplitude of clock output"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getOffsetOfClkOutput()
{
	/* Get Offset of clock output */
	std::string buffer;
	sg_write("ofsc?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Offset of clock output :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Offset of clock output"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getAmplitudeOfHf()
{
	/* Get Amplitude of HF (RF doubler output) */
	std::string buffer;
	sg_write("amph?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Amplitude of HF (RF doubler output) :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Amplitude of HF (RF doubler output)"<<std::endl;
	}

	return buffer;
}

std::string CEMSDBFSynthesizer::_getOffsetRearDC()
{
	/* Get Offset of rear DC */
	std::string buffer;
	sg_write("ofsd?\n");
	if ( sg_read((char*)buffer.c_str(), sizeof(buffer)) )
	{
		//std::cout<<"Offset of rear DC :"<<buffer.c_str()<<std::endl;
		//std::cout<<"Offset of rear DC :"<<buffer.c_str();
	}
	else
	{
		//std::cout<<"Timeout while reading Offset of rear DC"<<std::endl;
	}

	return buffer;
}


bool CEMSDBFSynthesizer::DisplaySynthesizerConfig()
{
	/* Get Frequency in MHz */
	_getFrequency();

	/*Get Phase */
	_getPhase();

	/* Amplitude of LF (BNC output) */
	_getAmplitudeOfLf();

	/* Amplitude of RF (Type-N output) */
	_getAmplitudeOfRf();

	/* Modulation type */
	_getModulationType();

	/* Modulation function */
	_getModulationFunction();

	/* Modulation rate */
	_getModulationRate();

	/* Amplitude of clock output */
	//_getAmplitudeOfClkOutput();

	/* Offset of clock output */
	//_getOffsetOfClkOutput();

	/* Amplitude of HF (RF doubler output) */
	//_getAmplitudeOfHf();

	/* Offset of rear DC */
	//_getOffsetRearDC();

	return true;
}
void CEMSDBFSynthesizer::SetFrquency(std::string szInFreq)
{
	/* Set frequency in MHz */
	std::string szFrq = "freq " + szInFreq + "e6\n";
	if(!sg_write((char*)szFrq.c_str()))
	{}
		//std::cout<<"Socket write error for SetFrequency"<<std::endl;
}

string CEMSDBFSynthesizer::GetFrequency()
{
	/* Get Frequency in MHz */
	return _getFrequency();
}

