#pragma once 

#include "Winsnmp.h"
#include <string>
#include <vector>
#include <map>
#include "EMSSNMPObject.h"
#include "EMSSNMPManager.h"


class EMSSNMPSession;
class EMSSNMPRemoteAgent;
class EMSSNMPRequestSet;

#define SNMP_RAREQ_STATE_NONE		0
#define SNMP_RAREQ_STATE_ONGOING	1
#define SNMP_RAREQ_STATE_TIMEDOUT	3
#define SNMP_RAREQ_STATE_SUCCEEDED	4
#define SNMP_RAREQ_STATE_ERROR		5
#define SNMP_RAREQ_STATE_CANCELLED	6

class EMSSNMPRequest {
	friend class EMSSNMPRemoteAgent;
	friend class EMSSNMPSession;
	friend class EMSSNMPRequestSet;
protected :
	std::vector<EMSSNMPObject*> _result;	
	std::vector<EMSSNMPObject*> _request;
	HSNMP_PDU _hPdu;
	HSNMP_VBL _hVbl;
	HANDLE _hWait;
	int _requestId;
	int _error;
	int _state;
	int _pduType;
	EMSSNMPRemoteAgent * _pRemoteAgent;
protected :	
	EMSSNMPRequest(int pduType, EMSSNMPObject * objects, int count, EMSSNMPRemoteAgent * pRemoteAgent);	
	void addToResult(EMSSNMPObject & object);
	void setResult(int error = SNMP_ERROR_NOERROR, bool traceIt = true);
	int getRequestCount()			{ return (int)_request.size(); }
	EMSSNMPObject * getRequest(int i)	{ return _request[i]; }

public:	
	virtual ~EMSSNMPRequest();

public:
	void execute(EMSSNMPRemoteAgent * pRemoteAgent = NULL);
	void cancel();
	void wait(DWORD timeout = INFINITE);

	bool isTerminated()		{ return _state != SNMP_RAREQ_STATE_ONGOING; }
	bool timedOut()			{ return _state == SNMP_RAREQ_STATE_TIMEDOUT; }
	bool succeeded()		{ return _state == SNMP_RAREQ_STATE_SUCCEEDED; }

	int getError()					{ return _error; }
	std::string getErrorAsString();

	int getResultCount()			{ return (int)_result.size(); }
	EMSSNMPObject * getResult(int i)	{ return _result[i]; }

	std::string getDisplayInformation() const;

	EMSSNMPRequest * clone();
};

class EMSSNMPRemoteAgentGetRequest : public EMSSNMPRequest {
public:
	EMSSNMPRemoteAgentGetRequest(EMSSNMPObject * objects, int count=1, EMSSNMPRemoteAgent * pRemoteAgent = NULL) : EMSSNMPRequest(SNMP_PDU_GET, objects, count, pRemoteAgent) {}
	virtual ~EMSSNMPRemoteAgentGetRequest() {}
};

class EMSSNMPRemoteAgentGetNextRequest : public EMSSNMPRequest {
public:
	EMSSNMPRemoteAgentGetNextRequest(EMSSNMPObject * objects, int count=1, EMSSNMPRemoteAgent * pRemoteAgent = NULL) : EMSSNMPRequest(SNMP_PDU_GETNEXT, objects, count, pRemoteAgent) {}
	virtual ~EMSSNMPRemoteAgentGetNextRequest() {}
};

class EMSSNMPRemoteAgentSetRequest : public EMSSNMPRequest {
public:
	EMSSNMPRemoteAgentSetRequest(EMSSNMPObject * objects, int count=1, EMSSNMPRemoteAgent * pRemoteAgent = NULL) : EMSSNMPRequest(SNMP_PDU_SET, objects, count, pRemoteAgent) {}
	virtual ~EMSSNMPRemoteAgentSetRequest() {}
};


