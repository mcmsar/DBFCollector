/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __LPD_TOOLS_H__
#define __LPD_TOOLS_H__

#include "emsexcpt.h"
#include <map>
#include <string>
#include "MLB1000WaveformManager.h"

#define MAXLPD (24)
#define NHEXLPD (9)

//! A collection of common methods used in LPD.
class CEMSLPDTools
{
	public:
		CEMSLPDTools();
		CEMSLPDTools( const CEMSLPDTools& x );
		virtual ~CEMSLPDTools();

		void Init( const MLB1000WaveformManager::EncryptionKey ckeyEncrypt, 
					const wchar_t* cwszFilename );
		
		EMS_RESULT GetFrameSynch ( const long clId, long* calFS ); 
		ULONG GetNumFrameSynchs() { _InitWaveforms(); return m_omapWaveforms.size(); }
		std::map<long,QWORD> GetAllFrameSynchs() const { return m_omapWaveforms; }

	private:
		void _InitWaveforms();

	private: // data
		bool	m_bWaveformInit;
		std::map<long,QWORD> m_omapWaveforms;
		MLB1000WaveformManager::EncryptionKey m_keyEncrypt;
		std::wstring m_owszFilename;



};	

#endif