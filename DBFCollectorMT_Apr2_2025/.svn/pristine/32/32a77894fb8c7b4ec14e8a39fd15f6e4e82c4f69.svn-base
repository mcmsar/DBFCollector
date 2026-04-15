#pragma once 

#include "Winsnmp.h"
#include <string>

#define SNMPTRACE(a)		EMSSNMPTracer::getTracer()->trace(a)
#define SNMPTRACEAENABLED()	EMSSNMPTracer::getTracer()->isEnabled()

class EMSSNMPTracer {
protected:	
	//static EMSSNMPTracer _snmpTracer;
	
    HANDLE _hConsole;
	HANDLE _hConsoleInput;
	bool _active;

	EMSSNMPTracer();
	~EMSSNMPTracer();
	
public:
	//static EMSSNMPTracer * getTracer() { return &_snmpTracer; }

	void enable(bool on) { _active = on; }
	bool isEnabled() const { return _active; }
	void trace(const std::string & message);
};


