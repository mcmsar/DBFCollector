#pragma once 

#include "Winsnmp.h"
#include <string>
#include <map>
#include "EMSSNMPRemoteAgent.h"
#include "EMSSNMPRequest.h"
#include "EMSSNMPTrap.h"

class EMSSNMPSession {

friend class EMSSNMPRemoteAgent;
friend class EMSSNMPManager;
friend class EMSSNMPRequest;
friend class EMSSNMPTrap;
friend SNMPAPI_STATUS CALLBACK snmpCallBackFunction( HSNMP_SESSION hSession, HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam, LPVOID lpClientData);

protected:
	HSNMP_SESSION _hSession;
	EMSSNMPSession(HSNMP_SESSION hSession);
	void closeSession();

	std::map<HSNMP_CONTEXT,EMSSNMPRemoteAgent*> _ragents;
	EMSSNMPRemoteAgent * getRemoteAgent(HSNMP_CONTEXT handle);
	void unregisterRemoteAgent(EMSSNMPRemoteAgent * ragent);
	void registerRemoteAgent(EMSSNMPRemoteAgent * ragent); 
	SNMPAPI_STATUS processNotification(WPARAM wParam, LPARAM lParam);
	
	const HSNMP_SESSION getHandle() const { return _hSession; }
public:
	EMSSNMPSession();
	~EMSSNMPSession();
	
	virtual void processTrap(const EMSSNMPObject & object) {}
};


