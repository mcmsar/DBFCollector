#ifndef __EMSDBFSYNTHESIZER_H__
#define __EMSDBFSYNTHESIZER_H__
#include <iostream>
#include <string>

class CEMSDBFSynthesizer
{
public:
	CEMSDBFSynthesizer();
	~CEMSDBFSynthesizer();

	void CloseSynthesizerConnection();
	bool ConnectToSynthesizer(std::string inputHost);
	void SetFrquency(std::string szInFreq);
	std::string GetFrequency();
	bool DisplaySynthesizerConfig();

private:
	void init_tcpip(void);
	int sg_connect(unsigned long ip);
	int sg_close(void);
	int sg_write(char *str);
	int sg_write_bytes(const void *data, unsigned num);
	int sg_read(char *buffer, unsigned num);

	std::string _getFrequency();
	std::string _getPhase();
	std::string _getAmplitudeOfLf();
	std::string _getAmplitudeOfRf();
	std::string _getModulationType();
	std::string _getModulationFunction();
	std::string _getModulationRate();
	std::string _getAmplitudeOfClkOutput();
	std::string _getOffsetOfClkOutput();
	std::string _getAmplitudeOfHf();
	std::string _getOffsetRearDC();

private:
	//std::string m_szSynthHostStr;
};

#endif