#include "EMSSNMPTracer.h"

#include <sstream>
#include <iostream>

#define __VER__ "1.0"

#pragma warning(disable : 4996)


//EMSSNMPTracer EMSSNMPTracer::_snmpTracer;

EMSSNMPTracer::EMSSNMPTracer() {
	_active = false;
	//_hConsole = INVALID_HANDLE_VALUE;
	//_hConsoleInput = INVALID_HANDLE_VALUE;
	//::AllocConsole();
	//_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
	//_hConsoleInput = ::GetStdHandle(STD_INPUT_HANDLE);
}

EMSSNMPTracer::~EMSSNMPTracer() {
	/*::CloseHandle(_hConsole);
	::CloseHandle(_hConsoleInput);
	::FreeConsole();*/
}

void EMSSNMPTracer::trace(const std::string & message)	{		
	if(!isEnabled() || _hConsole == INVALID_HANDLE_VALUE) {
		return;
	}
	std::stringstream ss;
	SYSTEMTIME	time;
	::GetLocalTime(&time);
	char timeStr[33];
	sprintf(timeStr, "%.2d:%.2d:%.2d,%.3d", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);
	ss << timeStr << ": " << message << "\n";
	DWORD chars;
	//::WriteConsole(_hConsole, ss.str().c_str(), (DWORD)ss.str().size(), &chars, NULL);
}
