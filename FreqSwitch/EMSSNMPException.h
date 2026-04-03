#pragma once 

#include "Winsnmp.h"
#include <string>
#include <sstream>

#include "EMSSNMPTracer.h"

#define SNMP_THROW_BASE(e) { EMSSNMPException * psnmpe = e; SNMPTRACE(psnmpe->toString()); throw psnmpe; }

#define SNMP_THROW_EXCEPTION(message) SNMP_THROW_BASE(new EMSSNMPException(message, NULL, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))
#define SNMP_RETHROW_EXCEPTION(message, exception) SNMP_THROW_BASE(new EMSSNMPException(, exception, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))

#define SNMP_THROW_ERROR(message, number, level) SNMP_THROW_BASE(new EMSSNMPErrorException(number, level, message, NULL, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))
#define SNMP_RETHROW_ERROR(message, exception, number, level) SNMP_THROW_BASE(new EMSSNMPErrorException(number, level, message, exception, __FILE__, __LINE__, __DATE__, __TIME__, __VER__))


class EMSSNMPException {
protected:
	std::string _message;
	std::string _source;
	EMSSNMPException * _previous;
public:
	EMSSNMPException(	std::string message = "", 
					EMSSNMPException * prev = NULL, 
					const char * file = NULL, 
					int line = 0, 
					const char * date = NULL,
					const char * time = NULL, 
					const char * ver = NULL);
	virtual ~EMSSNMPException();
	virtual std::string toString();
	virtual std::string toStringStack();
};


#define SNMP_ERROR		0
#define SNMP_WARNING	1


class EMSSNMPErrorException : public EMSSNMPException {
protected:
	int _level;
	int _number;
public:
	EMSSNMPErrorException(int number = SNMPAPI_OTHER_ERROR, int level = SNMP_WARNING, std::string message = "", EMSSNMPException * prev = NULL, const char * file = NULL, int line = 0, const char * date = NULL, const char * time = NULL, const char * ver = NULL);	
	virtual ~EMSSNMPErrorException();
	virtual std::string toString();
};



