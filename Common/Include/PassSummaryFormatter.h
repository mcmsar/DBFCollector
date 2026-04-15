
#ifndef __PASS_SUMMARY_FORMATTER_H__
#define __PASS_SUMMARY_FORMATTER_H__

#include "statpass.h"
#include "emstrack.h"

class CEMSSit661A;

class CEMSPassSummaryFormatter
{
	public:
		CEMSPassSummaryFormatter();
		CEMSPassSummaryFormatter( const CEMSPassSummaryFormatter& x );
		~CEMSPassSummaryFormatter();

		EMSPASSSUMMARYINFO2 GetPassSummaryInfo( CEMSSit661A* pSit661A ) const;
		EMSSATELLITETRACK	GetPassSchedule( CEMSSit661A* pSit661A ) const;
		
	private:
		int _ConvertStatus( WORD w1, WORD w2, WORD w3 ) const;

};

#endif // __PASS_SUMMARY_FORMATTER_H__