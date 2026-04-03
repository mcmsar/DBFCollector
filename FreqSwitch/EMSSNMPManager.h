#pragma once 

#include "Winsnmp.h"
#include "EMSSNMPSession.h"
#include <map>


class EMSSNMPManager {

friend class EMSSNMPSession;
friend class EMSSNMPRequest;
friend class EMSSNMPRemoteAgent;

protected:
	static EMSSNMPManager _snmpManager;
	
	static std::string pduTypeToStr(int type);
	static std::string pduErrorToStr(int error);	
	static std::string pduToStr(	HSNMP_ENTITY hDstEntity,
									HSNMP_ENTITY hSrcEntity,
									HSNMP_CONTEXT hContext,
									smiINT32 pduType,
									smiINT32 pduId,
									smiINT32 pduError,
									HSNMP_VBL hVbl,
									bool leftToRight = true);

	bool _init;
	smiUINT32 _nMajorVersion;
	smiUINT32 _nMinorVersion;
	smiUINT32 _nLevel;
	
	EMSSNMPManager();
	~EMSSNMPManager();
	//void cleanUp();  - Smruti commented
	
	std::map<HSNMP_SESSION,EMSSNMPSession*> _sessions;
	void unregisterSession(EMSSNMPSession * session);
	void registerSession(EMSSNMPSession * session); 
	EMSSNMPSession * getSession(HSNMP_SESSION handle);

public:
	static EMSSNMPManager * getManager() { return &_snmpManager; }

	void startup();
	std::string getDisplayInformation() const;

	void cleanUp(); //Smruti added
};


