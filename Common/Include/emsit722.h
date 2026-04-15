/********************************************************************
*	Module:			emsit722.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Description of CEMSSit722  Class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_EMSIT722
#define INC_EMSIT722

#include "emssit.h"
#include "calib406ext.h"
#include "objectlist.h"

#define EMS_MAX_SIT722_BURSTS ( 99 ) 

class CEMSSit722 : public CEMSSitMessageBase
{
public:
	CEMSSit722();
	virtual ~CEMSSit722();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
	virtual void Reset( void );
	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );

	void SetMaxBurstCount( const int ciMaxBursts ) { m_iMaxBurstCount = ciMaxBursts; }
	int GetMaxBurstCount() const { return m_iMaxBurstCount; }

	void SetBurstCount( const int ciCount ) { m_iBurstCount = ciCount; }
	int GetBurstCount() const { return m_iBurstCount; }

	ULONG GetActualBurstCount() { return m_olst406Data.Count(); }

	EMS_RESULT Get( EMSCALIB406DATAEXT& rstr406, const ULONG culIndex );
	EMS_RESULT Add( const EMSCALIB406DATAEXT& crstr406 );

	void SetSourceID( const ULONG culSrcID ) { SetReportingMCC( culSrcID ); }


protected:
	virtual EMS_RESULT _ParseLine1( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData );
	virtual EMS_RESULT _ParseLine2( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData );
	virtual EMS_RESULT _ParseLine3( CEMSSitTokenizer *lpTokenizer, EMSCALIB406DATAEXT& rstrBurstData );

protected: // methods
	WORD _DataFlagsToMEOFlags( DWORD dwDataFlags );
	DWORD _MEOFlagsToDataFlags( WORD wMEOFlags );
	double _GetFrequencyOffset( const double cdRecValue ) const;

protected:
	int m_iMaxBurstCount;
	int m_iBurstCount;

	CEMSObjectList<EMSCALIB406DATAEXT> m_olst406Data;

};

class CEMSSit722A : public CEMSSit722
{
	public:
		CEMSSit722A();
		virtual ~CEMSSit722A();

		virtual EMS_RESULT GenerateMsgHeader( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateSitTrailer( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateMsgTrailer( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
		virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
		virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
		virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
		virtual EMSSITFORMATCLASS GetFormatClass() { return SIT_FMT_CLASS_XML; }

	private:
		static const wchar_t* ms_cwszRootEl;

};

class CEMSSit722B : public CEMSSit722
{
	public:
		CEMSSit722B();
		virtual ~CEMSSit722B();

		virtual EMS_RESULT GenerateMsgHeader( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateSitTrailer( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateMsgTrailer( IEMSSeqStream *lpStream ) { return EMS_OK; }
		virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
		virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
		virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer );
		virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE );
		virtual EMSSITFORMATCLASS GetFormatClass() { return SIT_FMT_CLASS_CSV; }

};


#endif // INC_EMSIT722
