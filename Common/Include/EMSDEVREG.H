#ifndef INC_EMSDEVREG
#define INC_EMSDEVREG

#include "emscom.h"
#include "emserror.h"

class CEMSDeviceRegistry
{
public:
	CEMSDeviceRegistry( const CLSID *lpClsID = 0 );
	virtual ~CEMSDeviceRegistry();

	BOOL SetClassID( const CLSID *lpClsID );
	EMS_RESULT RegisterInterface( const IID *lpIID, LPCTSTR lpszDesc );

	EMS_RESULT RegisterDevice();
	EMS_RESULT UnregisterDevice();

private:

	int _WideCharToLocal( LPTSTR pLocal, LPWSTR pWide, DWORD dwChars );
	int _LocalToWideChar( LPWSTR pWide, LPCTSTR pLocal, DWORD dwChars );

	CLSID			m_clsID;
	DWORD			m_dwDevType;
	IID				*m_lpIID;
	int				m_iNumIID;
	LPTSTR			m_lpszCLSID;
};

#endif