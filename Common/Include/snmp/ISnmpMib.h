//
// ISnmpMib.h: Definition of the ISnmpMib class.
// Copyright 2000, DARTCOM Inc.
// Purpose: Provide a concise wrapper for Dart's Snmp Control
//          Integrates Properties, Methods, and Events
//          Properties and Methods: Use the pMib member to directly access Properties and Methods
//          Events: Derive your class and provide the desired Virtual Functions
// Example:	pMib->Load(...);
//			Vars1 = pMib->GetVariables();
//
//
//////////////////////////////////////////////////////////////////////

#if !defined(DART_MIB_CLASS)
#define DART_MIB_CLASS

// import definition of Snmp Control interfaces
//	named_guids imports information we need about the DIID and CLSID
#import <DartSnmp2.dll> named_guids

class ISnmpMib
{
private:
	// save reference count
	long Ref;
protected:
	// AddRef and Release virtual functions are required for IUnknown...
	virtual ULONG __stdcall AddRef();
	virtual ULONG __stdcall Release();
public:
	// smart pointer to Snmp Control interface
	DartSnmp::ISnmpMibPtr pMib;
	// overload -> operator to use m_Mib->Load(...) instead of m_Mib->pMib->Load(...)
	DartSnmp::ISnmpMibPtr operator->() {return pMib;}
	// You use Create to create the licensed Snmp Control after calling CoInitialize()
	BOOL Create (char *License);
	// You use Destroy to free resources allocated in Create before calling CoUninitialize()
	virtual void Destroy ();
	ISnmpMib();
	virtual ~ISnmpMib();
};

#endif // !defined(DART_MIB_CLASS)
