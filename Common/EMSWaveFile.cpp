#include "EMSWaveFile.h"

#include <windows.h>
#include <stdio.h>

#include "EMSClock.h"

extern BOOL bDebugFlag;
const CEMSSystemClock  c_sysClock;
const char  months[]= "JanFebMarAprMayJunJulAugSepOctNovDec";

#pragma pack(2)

typedef   struct {
   char   id[4];              // "RIFF"
   DWORD  len;
}  tRiffHdr, *pRiffHdr;

typedef   struct {
   char   id[4];              // "fmt ", "data"
   DWORD  len;
}  tChunkHdr, *pChunkHdr;

typedef   struct {
   char   id[4];              // "LIST"
   DWORD  len;
   char   infoId[4];          // "INFO"
}  tChunkList, *pChunkList;

typedef   struct {
   char   id[4];              // "IART", "ICOP", "ICRD", "ICMT" "NAM", "IPRD", "ISFT", "ISRC"
   DWORD  len;
   char   text[256];
}  tChunkInfo, *pChunkInfo;

typedef   struct {
   char   id[4];              // "DISP"
   DWORD  len;
   DWORD  count;
   char   text[256];
}  tChunkDisp, *pChunkDisp;

typedef   struct {
   WORD   wFormatTag;         // Format category
   WORD   wChannels;          // Number of channels
   DWORD  dwSamplesPerSec;    // Sampling rate
   DWORD  dwAvgBytesPerSec;   // For buffer estimation
   WORD   wByteAlign;         // Data block size
}  tWaveChunkFmt, *pWaveChunkFmt;

typedef   struct {
   DWORD  dwBitsPerSample;    // Sample Size
}  tWavePcmFmt, *pWavePcmFmt;

tRiffHdr       riffHdr;
char           waveId[4];     // "WAVE";
tChunkHdr      chunkFmtHdr;
tChunkHdr      chunkDataHdr;
tWaveChunkFmt  waveChunkFmt;
tWavePcmFmt    wavePcmFmt;
tChunkList     chunkList;
tChunkInfo     chunkIART;
tChunkInfo     chunkICOP;
tChunkInfo     chunkICRD;
tChunkInfo     chunkICMT;
tChunkInfo     chunkINAM;
tChunkInfo     chunkIPRD;
tChunkInfo     chunkISFT;
tChunkInfo     chunkISRC;
tChunkDisp     chunkDISP;

CEMSWaveFile::CEMSWaveFile()
{
    m_hWaveFile         = INVALID_HANDLE_VALUE;
    m_ulLutID           = 0;
    m_ulSatID           = 0;
    m_StartTime.intTime = 0;
    m_fDuration = 0;
    m_fCenterFreq = 0;
    m_fBandWidth = 0;
	*m_szAudioFileName = 0;
	*m_szServiceName = 0;
	m_dwFileSize = 0;
	m_dFileDuration = 0.0;
}

CEMSWaveFile::~CEMSWaveFile()
{
}


void
CEMSWaveFile::setAudioFileName( const TCHAR* szAudioFileName )
{
	lstrcpy( m_szAudioFileName, szAudioFileName );
}

void
CEMSWaveFile::setServiceName( const TCHAR* szServiceName )
{
	if( lstrlen( szServiceName ) < sizeof( m_szServiceName ) )
	{
		lstrcpy( m_szServiceName, szServiceName );
	}
}

BOOL
CEMSWaveFile::InitWaveFile( TCHAR *pszFileName, WORD dwBitsPerSample,
                                       DWORD dwSamplesPerSec, int iChans )
{
	ULONG  ulBytes;

	m_dwFileSize = 0;
	m_dFileDuration = 0.0;

    m_hWaveFile = CreateFile( pszFileName, GENERIC_WRITE | GENERIC_READ,
							FILE_SHARE_READ | FILE_SHARE_WRITE,
                              0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
    if( m_hWaveFile == INVALID_HANDLE_VALUE )
    {
       if( bDebugFlag )  printf( " _InitWaveFile:     cannot create file, error %ld\n",
                                 GetLastError( ) );
       return( FALSE );
    }
    if( bDebugFlag )  printf( " _InitWaveFile:     file created, handle %ld\n", m_hWaveFile );
    memcpy( riffHdr.id, "RIFF", 4 );
    riffHdr.len = 0;
    _WriteFile( m_hWaveFile, &riffHdr, sizeof( riffHdr ), &ulBytes );

    memcpy( waveId, "WAVE", 4 );
    _WriteFile( m_hWaveFile, &waveId,   sizeof( waveId ), &ulBytes );
    riffHdr.len = sizeof( waveId );

    memcpy( chunkFmtHdr.id,  "fmt ",  4 );
    chunkFmtHdr.len = sizeof( waveChunkFmt ) + sizeof( wavePcmFmt );
    _WriteFile( m_hWaveFile, &chunkFmtHdr, sizeof( chunkFmtHdr ), &ulBytes  );
    riffHdr.len += sizeof( chunkFmtHdr );

    wavePcmFmt.dwBitsPerSample    = dwBitsPerSample;

    waveChunkFmt.wFormatTag       = WAVE_FORMAT_PCM;
    waveChunkFmt.wChannels        = iChans;
    waveChunkFmt.dwSamplesPerSec  = dwSamplesPerSec;
    waveChunkFmt.dwAvgBytesPerSec = waveChunkFmt.wChannels*waveChunkFmt.dwSamplesPerSec*(wavePcmFmt.dwBitsPerSample/8);;
    waveChunkFmt.wByteAlign       = waveChunkFmt.wChannels*(WORD)(wavePcmFmt.dwBitsPerSample/8);
    _WriteFile( m_hWaveFile, &waveChunkFmt, sizeof( waveChunkFmt ), &ulBytes );
    _WriteFile( m_hWaveFile, &wavePcmFmt,   sizeof( wavePcmFmt   ), &ulBytes );
    riffHdr.len += sizeof( waveChunkFmt ) + sizeof( wavePcmFmt );

    memcpy( chunkDataHdr.id, "data", 4 );
    chunkDataHdr.len = 0;
    _WriteFile( m_hWaveFile, &chunkDataHdr, sizeof( chunkDataHdr ), &ulBytes  );
    riffHdr.len += sizeof( chunkDataHdr );

    return( TRUE );

} 

void 
CEMSWaveFile::WriteWaveFile( void *pData, DWORD len )
{
    ULONG  ulBytes;

    _WriteFile( m_hWaveFile, pData, len, &ulBytes );
    chunkDataHdr.len += len;
    riffHdr.len      += len;

	if ( waveChunkFmt.dwAvgBytesPerSec )
	  m_dFileDuration += (double)len / (double)waveChunkFmt.dwAvgBytesPerSec;
}

void 
CEMSWaveFile::CloseWaveFile( void )
{
	if( m_hWaveFile != INVALID_HANDLE_VALUE )
	{
		ULONG          ulBytes;
		char           vers[10];
		EMSTIMEFIELDS  jTime;
		EMSTIME        now = c_sysClock.GetTime( );

		memcpy( chunkList.id, "LIST", 4 );
		memcpy( chunkList.infoId, "INFO", 4 );
		chunkList.len = 4;

		CEMSTime helpTime;
		helpTime.SetTime( m_StartTime );
		helpTime.GetTime( &jTime );
		memcpy(  chunkIART.id, "IART", 4 );
		memset(  chunkIART.text, 0, sizeof( chunkIART.text ) );
		sprintf( chunkIART.text, "Lut %ld, Sat %03ld, Start Time %d-%3.3s-%d %02d:%02d:%02d, Duration %d secs, Center Frequency %ld Hz, Bandwidth %ld Hz",
				 m_ulLutID, m_ulSatID, 
				 jTime.nDay,  &months[3*jTime.nMonth-3], jTime.nYear,
				 jTime.nHour, jTime.nMinute, jTime.nSecond,
				 (short)m_fDuration, (long)m_fCenterFreq, (long)m_fBandWidth );
		chunkIART.len  = (strlen( chunkIART.text ) + 4) & ~3;
		chunkList.len += (chunkIART.len + 8);

		memcpy( chunkICOP.id, "ICOP", 4 );
		memset( chunkICOP.text, 0, sizeof( chunkICOP.text ) );
		strcpy( chunkICOP.text, "Copyright (c) 2003 by EMS Technologies, Inc." );
		chunkICOP.len  = (strlen( chunkICOP.text ) + 4) & ~3;
		chunkList.len += (chunkICOP.len + 8);

		helpTime.SetTime( now );
		helpTime.GetTime( &jTime );
		memcpy( chunkICRD.id, "ICRD", 4 );
		memset( chunkICRD.text, 0, sizeof( chunkICRD.text ) );
		sprintf( chunkICRD.text, "%4d-%02d-%02d %02d:%02d:%02d",
				 jTime.nYear, jTime.nMonth,  jTime.nDay,
				 jTime.nHour, jTime.nMinute, jTime.nSecond );
		chunkICRD.len  = (strlen( chunkICRD.text ) + 4) & ~3;
		chunkList.len += (chunkICRD.len + 8);

		memcpy( chunkICMT.id, "ICMT", 4 );
		memset( chunkICMT.text, 0, sizeof( chunkICMT.text ) );
		sprintf( chunkICMT.text, "Lut %ld, Sat %03ld, Duration %d secs, Center Frequency %ld Hz, Bandwidth %ld Hz ",
				 m_ulLutID, m_ulSatID, 
				 (short)m_fDuration, (long)m_fCenterFreq, (long)m_fBandWidth );
		chunkICMT.len  = (strlen( chunkICMT.text ) + 4) & ~3;
		chunkList.len += (chunkICMT.len + 8);

		memcpy( chunkINAM.id, "INAM", 4 );
		memset( chunkINAM.text, 0, sizeof( chunkINAM.text ) );
		strcpy( chunkINAM.text, m_szAudioFileName );
		chunkINAM.len  = (strlen( chunkINAM.text ) + 4) & ~3;
		chunkList.len += (chunkINAM.len + 8);

		memcpy( chunkIPRD.id, "IPRD", 4 );
		memset( chunkIPRD.text, 0, sizeof( chunkIPRD.text ) );
		strcpy( chunkIPRD.text, "EMS LEOLUT 600" );
		chunkIPRD.len  = (strlen( chunkIPRD.text ) + 4) & ~3;
		chunkList.len += (chunkIPRD.len + 8);

		_GetVersion( vers, sizeof( vers ) );
		memcpy( chunkISFT.id, "ISFT", 4 );
		memset( chunkISFT.text, 0, sizeof( chunkISFT.text ) );
		sprintf( chunkISFT.text, "%s - Version %s", m_szServiceName, vers );
		chunkISFT.len  = (strlen( chunkISFT.text ) + 4) & ~3;
		chunkList.len += (chunkISFT.len + 8);

		memcpy( chunkISRC.id, "ISRC", 4 );
		memset( chunkISRC.text, 0, sizeof( chunkISRC.text ) );
		strcpy( chunkISRC.text, "EMS Technologies, Inc." );
		chunkISRC.len  = (strlen( chunkISRC.text ) + 4) & ~3;
		chunkList.len += (chunkISRC.len + 8);

		_WriteFile( m_hWaveFile, &chunkList, sizeof( chunkList ), &ulBytes );
		_WriteFile( m_hWaveFile, &chunkIART, chunkIART.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkICOP, chunkICOP.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkICRD, chunkICRD.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkICMT, chunkICMT.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkINAM, chunkINAM.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkIPRD, chunkIPRD.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkISFT, chunkISFT.len + 8,   &ulBytes );
		_WriteFile( m_hWaveFile, &chunkISRC, chunkISRC.len + 8,   &ulBytes );
		riffHdr.len += (chunkList.len + 8);

		helpTime.SetTime( m_StartTime );
		helpTime.GetTime( &jTime );
		memcpy( chunkDISP.id, "DISP", 4 );
		chunkDISP.count = 1;
		memset( chunkDISP.text, 0, sizeof( chunkDISP.text ) );
		sprintf( chunkDISP.text, "Lut ID %ld, Satellite ID %03ld, Start time %d-%3.3s-%d %02d:%02d:%02d",
				 m_ulLutID, m_ulSatID,
				 jTime.nDay,  &months[3*jTime.nMonth-3], jTime.nYear,
				 jTime.nHour, jTime.nMinute, jTime.nSecond );
		chunkDISP.len = 4 + (strlen( chunkDISP.text ) + 4) & ~3;
		_WriteFile( m_hWaveFile, &chunkDISP, chunkDISP.len + 8, &ulBytes );
		riffHdr.len += (chunkDISP.len + 8);

		SetFilePointer( m_hWaveFile, 0, NULL, FILE_BEGIN );

		// NOT calling _WriteFile so bytes won't be added to m_dwFileSize

		WriteFile(      m_hWaveFile, &riffHdr,      sizeof( riffHdr      ), &ulBytes, 0 );
		WriteFile(      m_hWaveFile, &waveId,       sizeof( waveId       ), &ulBytes, 0 );
		WriteFile(      m_hWaveFile, &chunkFmtHdr,  sizeof( chunkFmtHdr  ), &ulBytes, 0 );
		WriteFile(      m_hWaveFile, &waveChunkFmt, sizeof( waveChunkFmt ), &ulBytes, 0 );
		WriteFile(      m_hWaveFile, &wavePcmFmt,   sizeof( wavePcmFmt   ), &ulBytes, 0 );
		WriteFile(      m_hWaveFile, &chunkDataHdr, sizeof( chunkDataHdr ), &ulBytes, 0 );
		BOOL bSuccess = CloseHandle(  m_hWaveFile  );
		if( bDebugFlag )  printf( " _CloseWaveFile:    handle %ld, error %ld\n",
								  m_hWaveFile, bSuccess ? 0 : GetLastError( ) );
		m_hWaveFile = INVALID_HANDLE_VALUE;
	}
}

void
CEMSWaveFile::_GetVersion( char *pVers, int vLen )
{
    UCHAR    *pData;
    USHORT   *pulVer;
    UCHAR    **pBuff;
    ULONG    ulBytes;
    UINT     len;
    DWORD    hVer;
    HMODULE  hMod;
    char     exeName[256];
    char     fileDesc[64];

    memset( pVers, 0, vLen );
    *pVers  = '?';
    hMod    = GetModuleHandle( NULL );
    GetModuleFileName( hMod, exeName, sizeof( exeName ) );
    ulBytes = GetFileVersionInfoSize( exeName, &hVer );
    if( ulBytes )
    {
        pData = new UCHAR [ulBytes];
        GetFileVersionInfo( exeName, hVer, ulBytes, pData );
        VerQueryValue( pData, TEXT("\\VarFileInfo\\Translation"), (PVOID *)&pulVer, &len );
        if( len )
        {
            sprintf( fileDesc, "\\StringFileInfo\\%04x%04x\\ProductVersion", pulVer[0], pulVer[1] );
            VerQueryValue( pData, fileDesc, (PVOID *)&pBuff, &len );
            if( len )  memcpy( pVers, pBuff, vLen-1 );
        }
        delete [ ] pData;
    }

}

BOOL CEMSWaveFile::_WriteFile( HANDLE hFile, const LPVOID lpBuffer, DWORD nNumberOfBytesToWrite,
					    LPDWORD lpNumberOfBytesWritten )
{
	BOOL bOK;
	DWORD dwBytesWritten = 0;

	if ( 0 == lpNumberOfBytesWritten )
		lpNumberOfBytesWritten = &dwBytesWritten;
	
	bOK = WriteFile( hFile, lpBuffer, nNumberOfBytesToWrite, 
								lpNumberOfBytesWritten, 0 );

	if ( bOK )
		m_dwFileSize += *lpNumberOfBytesWritten;

	return bOK;
}

