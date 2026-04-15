#include "EMSSNMPException.h"

#define __VER__ "1.0"


EMSSNMPException::EMSSNMPException(	std::string message, 
								EMSSNMPException * prev, 
								const char * file, 
								int line, 
								const char * date, 
								const char * time, 
								const char * ver) { 
	_previous = prev;
	_message = message;
	std::stringstream ss;
	if(file) {
		ss << file;
		ss << "(" << line << ")";
		if(ver) {
			ss << " v" << ver;
		}
		if(date) {
			ss << " " << date;
		}
		if(time) {
			ss << " " << time;
		}
	}
	_source = ss.str();
}

EMSSNMPException::~EMSSNMPException() {
	if(_previous) {
		delete _previous;
	}
}

std::string EMSSNMPException::toStringStack() {	
	std::stringstream ss;
	ss << toString();
	if(_previous) {
		ss << "\n    ";
		ss << _previous->toStringStack();
	}
	return ss.str(); 
}

std::string EMSSNMPException::toString() {
	std::stringstream ss;
	ss << _message << ".";
	if(_source != "") {
		ss << " [" << _source << "]";
	}
	return ss.str(); 
}




EMSSNMPErrorException::EMSSNMPErrorException(int number, int level, std::string message, EMSSNMPException * prev, const char * file, int line, const char * date, const char * time, const char * ver) : EMSSNMPException(message, prev, file, line, date, time, ver) {
	_number = number;
	_level = level;	
}

EMSSNMPErrorException::~EMSSNMPErrorException() {	
}

std::string EMSSNMPErrorException::toString() {
	std::stringstream ss;
	if(SNMP_WARNING == _level) {
		ss << "warning SNMP";
	} else {
		ss << "error SNMP";
	}
	ss << _number << ": " << EMSSNMPException::toString();
	return ss.str(); 
}
