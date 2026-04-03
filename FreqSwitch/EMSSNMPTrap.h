#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "EMSSNMPObject.h"


class EMSSNMPSession;
class EMSSNMPRemoteAgent;

class EMSSNMPTrap {
	friend class EMSSNMPRemoteAgent;
	friend class EMSSNMPSession;
protected :
	std::string _pattern;
	smiOID _oidPattern;
	EMSSNMPRemoteAgent * _pRemoteAgent;
	bool _registered;

public:	
	EMSSNMPTrap(std::string pattern, EMSSNMPRemoteAgent * pRemoteAgent);
	virtual ~EMSSNMPTrap();

public:
	void enable(EMSSNMPRemoteAgent * pRemoteAgent = NULL);
	void disable();

	EMSSNMPTrap * clone();

	std::string getDisplayInformation() const;
};


