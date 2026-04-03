#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "EMSSNMPObject.h"

class EMSSNMPSession;
class EMSSNMPRemoteAgent;
class EMSSNMPRequest;
class EMSSNMPRequestSet;
class EMSSNMPTrap;

class EMSSNMPRemoteAgent {
	friend class EMSSNMPSession;
	friend class EMSSNMPRequest;
	friend class EMSSNMPRequestSet;
	friend class EMSSNMPTrap;
protected:
	std::string _name;
	std::string _community;
	UINT _port;
	bool _bInit;
	bool _mySession;
	EMSSNMPSession * _pSession;
	HSNMP_ENTITY _hEntity;
	HSNMP_CONTEXT _hContext;

	HSNMP_ENTITY getCommunityHandle() { return _hEntity; }
	HSNMP_CONTEXT getContextHandle() { return _hContext; }
	EMSSNMPSession * getSession() { return _pSession; }

	std::map<int,EMSSNMPRequest*> _requestMap;
	void addToRequestMap(int id, EMSSNMPRequest* pRequest) { _requestMap[id] = pRequest; }
	void removeFromRequestMap(int id) { 
		_requestMap.erase(id); 
	}
	EMSSNMPRequest* getRequest(int id);
    
	void sendRequest(EMSSNMPRequest * pRequest);
	void cancelRequest(int id);

public:	
	EMSSNMPRemoteAgent(std::string name, std::string community, unsigned int port = 0, EMSSNMPSession * pSession = NULL);
	~EMSSNMPRemoteAgent();

	std::string	getName() { return _name; }
	std::string	getCommunity() { return _community; }

	virtual std::string getDisplayInformation() const;
};


