#include "EMSSNMPManager.h"
#include "EMSSNMPRequest.h"
#include "EMSSNMPRemoteAgent.h"
#include "EMSSNMPSession.h"
#include "EMSSNMPObject.h"
#include "EMSSNMPException.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"


std::string EMSSNMPRequest::getDisplayInformation() const
{
	std::stringstream ss;
	ss << EMSSNMPManager::pduTypeToStr(_pduType) << " Request: ";		
	switch(_state) {
		case SNMP_RAREQ_STATE_NONE: ss << "NONE"; break;
		case SNMP_RAREQ_STATE_ONGOING: ss << "ONGOING"; break;
		case SNMP_RAREQ_STATE_TIMEDOUT: ss << "TIMEDOUT"; break;
		case SNMP_RAREQ_STATE_SUCCEEDED: ss << "SUCCEEDED"; break;
		case SNMP_RAREQ_STATE_ERROR: ss << "ERROR"; break;
		case SNMP_RAREQ_STATE_CANCELLED: ss << "CANCELLED"; break;
		default: ss << "?"; break;
	}
	ss << "(" << _error << ") [";
	int i;
	for(i=0; i<(int)_request.size(); i++) {
		ss << _request[i]->getOID();
		if(i < (int)_request.size()-1) {
			ss << ", ";
		}
	}
	ss << "] = [";
	for(i=0; i<(int)_result.size(); i++) {
		ss <<_result[i]->getDisplayInformation();
		if(i < (int)_result.size()-1) {
			ss << ", ";
		}
	}
	ss << "]";

	return ss.str();
}

EMSSNMPRequest * EMSSNMPRequest::clone()
{
	EMSSNMPRequest * myclone = new EMSSNMPRequest(_pduType, NULL, 0, _pRemoteAgent);
	for(int i=0; i<(int)_request.size(); i++) {
		myclone->_request.insert(myclone->_request.end(), new EMSSNMPObject(*_request[i]));
	}
	return myclone;
}

EMSSNMPRequest::EMSSNMPRequest(int pduType, EMSSNMPObject * objects, int count, EMSSNMPRemoteAgent * pRemoteAgent) {
	_pduType = pduType;
	_state = SNMP_RAREQ_STATE_NONE;
	_error = SNMP_ERROR_NOERROR;
	_requestId = 0;
	_hWait = ::CreateEvent (NULL, TRUE, FALSE, NULL);
	if(_hWait == NULL) {
		_error = SNMP_ERROR_GENERR;
//		SNMP_THROW_ERROR("Failed to create event", _error, SNMP_ERROR);
	}
	_pRemoteAgent = pRemoteAgent;
	for(int i=0; i<count; i++) {
		_request.insert(_request.end(), new EMSSNMPObject(objects[i]));
	}
}

EMSSNMPRequest::~EMSSNMPRequest()
{
	if(!isTerminated()) {
		cancel();
	}
	if(_hWait) {
		::CloseHandle(_hWait);
	}
	while((int)_request.size()) {
		delete _request[0];
		_request.erase(_request.begin());
	}
	while((int)_result.size()) {
		delete _result[0];
		_result.erase(_result.begin());
	}
}


std::string EMSSNMPRequest::getErrorAsString()	{ 
	return EMSSNMPManager::pduErrorToStr(_error); 
}

void EMSSNMPRequest::execute(EMSSNMPRemoteAgent * pRemoteAgent) {
	if(!isTerminated()) {
		cancel();
	}	
	while((int)_result.size()) {
		delete _result[0];
		_result.erase(_result.begin());
	}
	_state = SNMP_RAREQ_STATE_ONGOING;
	_error = SNMP_ERROR_NOERROR;
	if(pRemoteAgent) {
		_pRemoteAgent = pRemoteAgent;
	}

	EMSSNMPSession * session = _pRemoteAgent->getSession();
	//_requestId = session->getNextRequestId();
	smiVALUE dValue;
	int i;
	int count = getRequestCount();
	dValue.syntax = SNMP_SYNTAX_NULL;
	dValue.value.uNumber = 0;	
	_hVbl = SnmpCreateVbl(session->getHandle(), NULL, NULL);
	if(_hVbl == SNMPAPI_FAILURE) {
		_requestId = 0;
		_state = SNMP_RAREQ_STATE_ERROR;
		_error = SnmpGetLastError(session->getHandle());
//		SNMP_THROW_ERROR("Could not create variable bindings list", _error, SNMP_ERROR);
	}
	for(i=0; i<count; i++) {
		EMSSNMPObject *pObj = getRequest(i);
		smiOID * pOid = pObj->getBinaryOID();
		if(_pduType == SNMP_PDU_SET) {
			pObj->getValue(&dValue);
		}		
		if(pOid==NULL || SnmpSetVb(_hVbl, 0, pOid, &dValue) == SNMPAPI_FAILURE) {
			SnmpFreeVbl(_hVbl);
			_requestId = 0;
			_state = SNMP_RAREQ_STATE_ERROR;
			_error = SNMP_ERROR_GENERR;
//			SNMP_THROW_ERROR("Could not add object to the variable bindings list", SnmpGetLastError(session->getHandle()), SNMP_ERROR);
		}
		if(_pduType == SNMP_PDU_SET) {
			if(dValue.syntax == SNMP_SYNTAX_OID) {
				SnmpFreeDescriptor(dValue.syntax, (smiLPOPAQUE)&dValue.value.oid);
			} else if(	dValue.syntax == SNMP_SYNTAX_OPAQUE ||
						dValue.syntax == SNMP_SYNTAX_OCTETS ||
						dValue.syntax == SNMP_SYNTAX_BITS ||
						dValue.syntax == SNMP_SYNTAX_IPADDR ||
						dValue.syntax == SNMP_SYNTAX_NSAPADDR) {
				free(dValue.value.string.ptr);
			}
		}
	}
	_hPdu = SnmpCreatePdu(session->getHandle(), _pduType, 0, 0, 0, _hVbl);
	if(_hPdu == SNMPAPI_FAILURE) {
		SnmpFreeVbl(_hVbl);
		_requestId = 0;
		_state = SNMP_RAREQ_STATE_ERROR;
		_error = SNMP_ERROR_GENERR;
//		SNMP_THROW_ERROR("Could not create PDU", SnmpGetLastError(session->getHandle()), SNMP_ERROR);
	}
	smiINT32 id;
	if(SnmpGetPduData(_hPdu, NULL, &id, NULL, NULL, NULL) == SNMPAPI_FAILURE) {
		SnmpFreeVbl(_hVbl);
		_requestId = 0;
		_state = SNMP_RAREQ_STATE_ERROR;
		_error = SNMP_ERROR_GENERR;
//		SNMP_THROW_ERROR("Could not query PDU request id", SnmpGetLastError(session->getHandle()), SNMP_ERROR);
	}
	_requestId = id;
	_pRemoteAgent->sendRequest(this);
}

void EMSSNMPRequest::cancel() {	
	if(isTerminated()) {
		return;
	}
	_pRemoteAgent->cancelRequest(_requestId);
	//if(SNMPTRACEAENABLED()) {
	//	std::stringstream trace;
	//	trace << "rx < cancelled(" << _requestId << ")";
	//	SNMPTRACE(trace.str());
	//}
	_requestId = 0;
	SnmpFreePdu(_hPdu);
	SnmpFreeVbl(_hVbl);
	_error = SNMP_ERROR_NOERROR;
	_state = SNMP_RAREQ_STATE_CANCELLED;
	::ResetEvent(_hWait);
}

void EMSSNMPRequest::addToResult(EMSSNMPObject & object) {
	_result.insert(_result.end(), new EMSSNMPObject(object));
}

void EMSSNMPRequest::setResult(int error, bool traceIt) {
	if(isTerminated()) {
		return;
	}
	SnmpFreePdu(_hPdu);
	SnmpFreeVbl(_hVbl);
	_error = error;
	if(_error != SNMP_ERROR_NOERROR) {
		_state = SNMP_RAREQ_STATE_ERROR;
		if(traceIt /*&& SNMPTRACEAENABLED()*/) {
			std::stringstream trace;
			trace << "rx < error(" << _requestId << ", " << _error << ")";
			//SNMPTRACE(trace.str());
		}
	} else {
		_state = SNMP_RAREQ_STATE_SUCCEEDED;
	}
	::SetEvent(_hWait);
}

void EMSSNMPRequest::wait(DWORD timeout) {
	DWORD waitRet = ::WaitForSingleObject(_hWait, timeout);
	::ResetEvent(_hWait);
	// _state, _error and result set by WinSNMP!
	_pRemoteAgent->cancelRequest(_requestId);	
	SnmpFreePdu(_hPdu);
	SnmpFreeVbl(_hVbl);
	if(waitRet == WAIT_FAILED) {
		_state = SNMP_RAREQ_STATE_ERROR;
		_error = SNMP_ERROR_GENERR;
		_requestId = 0;
		//SNMP_THROW_ERROR("Wait failed", _error, SNMP_ERROR);
	}
	if(waitRet == WAIT_TIMEOUT || _state == SNMP_RAREQ_STATE_ONGOING) {	
		_state = SNMP_RAREQ_STATE_TIMEDOUT;
		_error = SNMP_ERROR_NOERROR;
		//if(SNMPTRACEAENABLED()) {
		//	std::stringstream trace;
		//	trace << "rx < timeout(" << _requestId << ", " << timeout << ")";
		//	//SNMPTRACE(trace.str());
		//}
	}
	_requestId = 0;
}


