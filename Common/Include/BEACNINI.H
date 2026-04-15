/********************************************************************
*	Module:			BeacnIni.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

  0.0 01/05/10	    rvw 	start

********************************************************************/
#ifndef INC_BEACNINI
#define INC_BEACNINI

#include "emsbeacn.h"

#define EMS_MAX_BEACONS ( 32 )

typedef struct _tagEMSREFBEACONTABLE
{
	__int64				i64BeaconID;
	BOOL 					bInUse;
	EMSREFBEACONDATA	data;
} EMSREFBEACONTABLE, *LPEMSREFBEACONTABLE;

const TCHAR c_szComponentName[]	   = TEXT("RefBeaconInfo");
const TCHAR c_szComponentDesc[]	   = TEXT("EMS Reference Beacon Info");

const TCHAR c_szSectionIntro[]		= TEXT("BEA:");

const TCHAR c_szType[]					= TEXT("Type");
const TCHAR c_szTypeRef[]				= TEXT("Reference");
const TCHAR c_szTypeOrb[]				= TEXT("Orbitography");
const TCHAR c_szTypeTest[]          = TEXT("Test");
const TCHAR c_szType121[]           = TEXT("121.5");
const TCHAR c_szType243[]           = TEXT("243.0");

const TCHAR c_szName[]              = TEXT("Name");
const TCHAR c_szActive[]            = TEXT("Active");
const TCHAR c_szBeaconMsg[]         = TEXT("BeaconMsg");
const TCHAR c_szLatitude[]          = TEXT("Latitude");
const TCHAR c_szLongitude[]         = TEXT("Longitude");
const TCHAR c_szAltitude[]          = TEXT("Altitude");
const TCHAR c_szModIndex[]          = TEXT("ModIndex");
const TCHAR c_szPower[]             = TEXT("Power");
const TCHAR c_szFrequency[]         = TEXT("Frequency");
const TCHAR c_szRepRate[]           = TEXT("RepRate");
const TCHAR c_szBitRate[]           = TEXT("BitRate");
const TCHAR c_szOrbitUpdate[]       = TEXT("OrbitUpdate");
const TCHAR c_szMCCSuppress[]       = TEXT("MCCsuppress");
const TCHAR c_szTCAL[]              = TEXT("TCAL");
const TCHAR c_szCalibrateGEO[]      = TEXT("Calibrate.GEO");

class CBeaconInitData 
{
public:
	CBeaconInitData( );
	virtual ~CBeaconInitData();

	HRESULT Init( LPEMSREFBEACONTABLE lpBeaconTable, int nMaxBeacons, LPINT lpBeaconCount );

	inline LPCTSTR GetINIFileName( void ) { return (LPCTSTR)m_lpszINIFile; }

private: // methods
	HRESULT _ProcessSection( LPCTSTR lpcszSection );	
	HRESULT _ProcessBeaconData( LPCTSTR lpcszSection, LPEMSREFBEACONDATA lpData );
	int _FindEmptySlot( void );
	int _FindBeaconSlot( __int64 i64BeaconID );
	__int64 _HexToInt64( LPCTSTR lpcszHexDigits );
	EMS_RESULT _SetIniFileName( void );

private: // data
	int						m_nMaxBeacons;
	int						m_nBeaconCount;
	LPEMSREFBEACONTABLE	m_lpBeaconTable;
	LPTSTR					m_lpszINIFile;
};							 

#endif // INC_BEACNINI

