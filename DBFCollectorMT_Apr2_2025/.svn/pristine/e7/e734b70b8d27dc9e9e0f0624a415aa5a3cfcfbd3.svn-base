#include "EMSSNMPManager.h"
#include "EMSSNMPRemoteAgent.h"
#include "EMSSNMPSession.h"
#include "EMSSNMPObject.h"
#include "EMSSNMPException.h"
#include "EMSSNMPRequest.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"


EMSSNMPRemoteAgent::EMSSNMPRemoteAgent(std::string name, std::string community, unsigned int port, EMSSNMPSession * pSession) {
	_name = name;
	_port = port;
	_community = community;
	_bInit = false;
	_mySession = false;
	_pSession = pSession;
	_hEntity = SNMPAPI_FAILURE;
	_hContext = SNMPAPI_FAILURE;
	if(_pSession == NULL) {
		try {
			_pSession = new EMSSNMPSession();
		} catch(EMSSNMPException * pe) {
			//SNMP_RETHROW_ERROR("Could not create WinSNMP session", pe, SNMPAPI_OTHER_ERROR, SNMP_ERROR);
		}
		_mySession = true;
	}
	HSNMP_SESSION hSession = _pSession->getHandle();
	if(hSession == SNMPAPI_FAILURE) {
		if(_mySession && _pSession != NULL) {
			delete _pSession;
		}
		_pSession = NULL;		
		//SNMP_THROW_ERROR("Invalid session", SnmpGetLastError(NULL), SNMP_ERROR);
	}
	_hEntity = SnmpStrToEntity(hSession, _name.c_str());
	if (_hEntity == SNMPAPI_FAILURE) {
		LPHOSTENT lpHostent = gethostbyname(_name.c_str());
		IN_ADDR host;
		if(!lpHostent) {
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
//			SNMP_THROW_ERROR("Could not get host by name", SNMPAPI_OTHER_ERROR, SNMP_ERROR);
		}
		memmove (&host, lpHostent->h_addr, sizeof(IN_ADDR));
		_hEntity = SnmpStrToEntity(hSession, inet_ntoa(host));
		if (_hEntity == SNMPAPI_FAILURE) {
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
//			SNMP_THROW_ERROR("Could not convert remote agent address to entity", SnmpGetLastError(hSession), SNMP_ERROR);
		}
	}
	if(port != 0) {
		if(SnmpSetPort(_hEntity, port) != SNMPAPI_SUCCESS) {
			SnmpFreeEntity(_hEntity);
			_hEntity = SNMPAPI_FAILURE;
			if(_mySession && _pSession != NULL) {
				delete _pSession;
			}
			_pSession = NULL;
//			SNMP_THROW_ERROR("Could not set remote agent port", SnmpGetLastError(hSession), SNMP_ERROR);
		}
	}
	smiOCTETS dCtx;
	dCtx.len = (smiUINT32)strlen(community.c_str());
	dCtx.ptr = (smiLPBYTE)community.c_str();
	_hContext = SnmpStrToContext(hSession, &dCtx);
	if (_hContext == SNMPAPI_FAILURE)  {
		SnmpFreeEntity(_hEntity);
		_hEntity = SNMPAPI_FAILURE;
		if(_mySession && _pSession != NULL) {
			delete _pSession;
		}
		_pSession = NULL;
//		SNMP_THROW_ERROR("Could not convert community name to context", SnmpGetLastError(hSession), SNMP_ERROR);
	}
	_pSession->registerRemoteAgent(this);
	_bInit = true;
}


std::string EMSSNMPRemoteAgent::getDisplayInformation() const
{
	std::stringstream ss;
	if(_port != 0) {
		ss << "Remote Agent " << _name << ":" << _port << " " << _community;	
	} else {
		ss << "Remote Agent " << _name << " " << _community;	
	}
	return ss.str();
}

EMSSNMPRemoteAgent::~EMSSNMPRemoteAgent() {
	if(_bInit) {
		_pSession->unregisterRemoteAgent(this);
		SnmpFreeContext(_hContext);
		SnmpFreeEntity(_hEntity);
		_bInit = false;
	}
	if(_mySession && _pSession != NULL) {
		delete _pSession;
	}
	std::map<int,EMSSNMPRequest*>::iterator i;
	while((i=_requestMap.begin()) != _requestMap.end()) {
		cancelRequest((*i).first);
	}
}

EMSSNMPRequest* EMSSNMPRemoteAgent::getRequest(int id) {
	std::map<int,EMSSNMPRequest*>::const_iterator pos;
	pos = _requestMap.find(id);
	if(pos == _requestMap.end()) {
		return NULL;
	}
	return pos->second;
}

void EMSSNMPRemoteAgent::sendRequest(EMSSNMPRequest * pRequest) {
	if(!_bInit) {
		pRequest->setResult(SNMP_ERROR_GENERR);
		//SNMP_THROW_ERROR("Not initialized", SNMPAPI_OTHER_ERROR, SNMP_ERROR);
	}
	HSNMP_PDU hPDU = pRequest->_hPdu;
	int id = pRequest->_requestId;
	addToRequestMap(id, pRequest);
	/*if(SNMPTRACEAENABLED()) {
		std::stringstream trace;
		smiINT32 lReqId, lType, lErr, lIdx;
		HSNMP_VBL hVbl;
		SnmpGetPduData(hPDU, &lType, &lReqId, &lErr, &lIdx, &hVbl);
		trace << "tx " << EMSSNMPManager::pduToStr(_hEntity, 0, _hContext, lType, lReqId, lErr, hVbl, true);
		SnmpFreeVbl(hVbl);
		SNMPTRACE(trace.str());
	}
	*/if(SnmpSendMsg(_pSession->getHandle(), 0, _hEntity, _hContext, hPDU) == SNMPAPI_FAILURE) {
		pRequest->setResult(SNMP_ERROR_GENERR);
		//SNMP_THROW_ERROR("Could not send PDU", SnmpGetLastError(_pSession->getHandle()), SNMP_ERROR);
	}
}

void EMSSNMPRemoteAgent::cancelRequest(int id) {
	EMSSNMPRequest* pRequest = getRequest(id);
	if(pRequest) {
		SnmpCancelMsg(_pSession->getHandle(), id);
		removeFromRequestMap(id);
	}
}
