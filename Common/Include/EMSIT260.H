/********************************************************************
*	Module:			emsit260.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit260  Class
*						Pass Schedule
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2002 June 3 rvw	start

********************************************************************/

#ifndef INC_EMSIT260
#define INC_EMSIT260

#include "emssit.h"
#include "sittypes.h"

#define EMSSIT260_MAX_SATELLITES ( 999 )

#define EMS_LINES_PER_SATELLITE ( 2 )

//typedef enum tagEMSSCHEDUSAGE
//{
//	EMSSchedUsageUnknown = 0,
//	EMSSchedUsageInstall = 1,
//	EMSSchedUsageAppend = 2,
//	EMSSchedUsageInfo = 3,
//	EMSSchedUsageValidate = 4
//} EMSSCHEDUSAGE;

/*typedef struct  _tagEMSSIT260DATA
{
    ULONG ulLutID;
    ULONG ulSatID;
	  WORD wPassSchedOrigin;								
	  WORD wPassSchedStatus;
	  WORD wPassProcessStatus;
    ULONG ulOrbitNumber;
    EMSTIME timeAOS;
    EMSTIME timeLOS;
	  double dPrePassOffset;		 	// seconds
	  double dStartDataCollectionOffset;	// seconds
	  double dStopDataCollectionOffset;	// seconds
    EMSDEGREES degMaxElevation;
    EMSDEGREES degAzimuthAOS;
    EMSDEGREES degAzimuthPeak;
    EMSDEGREES degAzimuthLOS;
}	EMSSIT260DATA, *LPEMSSIT260DATA;
*/
#pragma pack(1)
typedef struct _tagEMSSIT260DATAUNION
{
	union
	{
		EMSSIT260DATA data;
		EMSSIT260DATAEX dataEx;
	} x;
} EMSSIT260DATAUNION, *LPEMSSIT260DATAUNION;
#pragma pack()

class CEMSSit260Base : public CEMSSitMessageBase
{
public:
	CEMSSit260Base( );
	virtual ~CEMSSit260Base( );

	virtual void Reset( void );

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream);

	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );

	inline int GetSatelliteCount( void ) { return m_nSatCount; }
	inline int GetMaxSatelliteCount( void ) { return EMSSIT260_MAX_SATELLITES; }
	inline void SetSatelliteCount( int nCount ) { m_nSatCount = nCount; }
	inline EMSSCHEDUSAGE GetScheduleUsage( void ) { return m_usage; }
	inline void SetScheduleUsage( EMSSCHEDUSAGE usage ) { m_usage = usage; }

	bool ForSingleAntenna();

	EMS_RESULT AddPass( LPEMSSIT260DATA lpPass );
	LPEMSSIT260DATA GetPass( int nIndex );

	EMS_RESULT AddPassEx( LPEMSSIT260DATAEX lpPass );
	LPEMSSIT260DATAEX GetPassEx( int nIndex );

protected: // methods
	int _ChkELRange( const double dElevation, const wchar_t* cwszText );
	int _ChkSatCountRange( const int iCount, const wchar_t* cwszText ); 
	int _ChkAZRange( const double dAzimuth, const wchar_t* cwszText );
	int _ChkOffsetRange( const double dOffset, const wchar_t* cwszText );
	ULONG _ChkLutIdRange( const ULONG ulLutId, const wchar_t* cwszText );
	ULONG _ChkAntennaIdRange( const ULONG ulAntennaId, const wchar_t* cwszText );
	ULONG _ChkSatIdRange( const ULONG ulSatId, const wchar_t* cwszText );
	ULONG _ChkOrbitNoRange( const ULONG ulOrbitNo, const wchar_t* cwszText );
	virtual EMS_RESULT _ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData );
	virtual EMS_RESULT _ParsePassLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData  );

protected: // data
	int						m_nSatCount;
	int						m_nAllocCount;
	EMSSCHEDUSAGE 			m_usage;		// Append / Info / Validation / Install
	LPEMSSIT260DATAUNION m_lpData;
};

class CEMSSit260A : public CEMSSitMessageBase
{
public:
	CEMSSit260A();
	CEMSSit260A::CEMSSit260A( CEMSSit260A* pSit );
	// Note that it is up to the caller to confirm that 
	// the supplied SIT contains a schedule for a single antenna
	CEMSSit260A::CEMSSit260A( CEMSSit260Base* pSit );
	virtual ~CEMSSit260A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	virtual void Reset( void );

	int GetSatelliteCount( void ) { return m_nSatCount; }
	int GetMaxSatelliteCount( void ) { return EMSSIT260_MAX_SATELLITES; }
	void SetSatelliteCount( int nCount ) { m_nSatCount = nCount; }
	EMSSCHEDUSAGE GetScheduleUsage( void ) { return m_usage; }
	void SetScheduleUsage( EMSSCHEDUSAGE usage ) { m_usage = usage; }

	EMS_RESULT AddPass( LPEMSSIT260DATA lpPass );
	LPEMSSIT260DATA GetPass( int nIndex );

private: // methods
	EMS_RESULT _ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATA lpData );
	EMS_RESULT _ParsePassLine2( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATA lpData  );
	int _ChkELRange( const double dElevation, const wchar_t* cwszText );
	int _ChkSatCountRange( const int iCount, const wchar_t* cwszText ); 
	int _ChkAZRange( const double dAzimuth, const wchar_t* cwszText );
	int _ChkOffsetRange( const double dOffset, const wchar_t* cwszText );
	ULONG _ChkLutIdRange( const ULONG ulLutId, const wchar_t* cwszText );
	ULONG _ChkSatIdRange( const ULONG ulSatId, const wchar_t* cwszText );
	ULONG _ChkOrbitNoRange( const ULONG ulOrbitNo, const wchar_t* cwszText );

private:	// data
	int				m_nSatCount;
	int				m_nAllocCount;
	EMSSCHEDUSAGE 	m_usage;		// Append / Info / Validation / Install
	LPEMSSIT260DATA m_lpData;
};


class CEMSSit260B : public CEMSSit260Base
{
public:
	CEMSSit260B();
	virtual ~CEMSSit260B();

	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );

protected: // methods
	virtual EMS_RESULT _ParsePassLine1( CEMSSitTokenizer *lpTokenizer, LPEMSSIT260DATAEX lpData );
};

#endif // INC_EMSIT260
