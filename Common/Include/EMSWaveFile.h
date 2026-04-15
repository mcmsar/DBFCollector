#ifndef _EMS_WAVE_FILE_
#define _EMS_WAVE_FILE_

#include "emstypes.h"
#include "emstime.h"

class CEMSWaveFile
{
public: 
	CEMSWaveFile();
	virtual ~CEMSWaveFile();

	BOOL InitWaveFile( TCHAR *pszFileName, WORD dwBitsPerSample,
                                       DWORD dwSamplesPerSec, int iChans );
	void CloseWaveFile( void );
	void WriteWaveFile( void *pData, DWORD len );

	inline double GetFileDuration( void ) { return m_dFileDuration; }
	inline DWORD GetFileSize( void ) { return m_dwFileSize; }

	void setStartTime( const EMSTIME& stTime )
	{	m_StartTime = stTime;	};

	void setSatID( const ULONG& ulSatID )
	{	m_ulSatID = ulSatID;	};

	void setLutID( const ULONG& ulLutID )
	{	m_ulLutID = ulLutID;	};

	void setDuration( const float& f )
	{	m_fDuration = f;	};

	void setCenterFreq( const float& f )
	{	m_fCenterFreq = f;	};

	void setBandWidth( const float& f )
	{	m_fBandWidth = f;	};

	void setAudioFileName( const TCHAR* szAudioFileName );
	void setServiceName( const TCHAR* szServiceName );

private:	// methods
	void _GetVersion( char  *pVersion, int vLen );
	BOOL _WriteFile( HANDLE hFile, const LPVOID lpBuffer, DWORD nNumberOfBytesToWrite,
					    LPDWORD lpNumberOfBytesWritten );

protected:
    ULONG                       m_ulLutID;
    ULONG                       m_ulSatID;
    EMSTIME                     m_StartTime;
    float                       m_fDuration;
    float                       m_fCenterFreq;
    float                       m_fBandWidth;
	TCHAR                       m_szAudioFileName[256];
	TCHAR						m_szServiceName[64];

private:	// data
	DWORD			m_dwFileSize;
	double		m_dFileDuration;
	HANDLE m_hWaveFile;
};

#endif // _EMS_WAVE_FILE_
