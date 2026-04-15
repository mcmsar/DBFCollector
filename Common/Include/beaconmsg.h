/********************************************************************
*	Module:			BeaconMsg.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Definitions for CEMSBeaconMsg class
*						
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

  0.0 02/03/10	    rvw 	start

********************************************************************/
#ifndef INC_BEACONMSG
#define INC_BEACONMSG

#include "emstypes.h"

class CEMSBeaconMsg
{
public:
	CEMSBeaconMsg( );
	CEMSBeaconMsg( float *lpfArray144 );
	CEMSBeaconMsg( LPBYTE lpcBinary, INT nLength=18, INT nOffset=0);
	CEMSBeaconMsg( LPCTSTR lpcszHex, INT nLength=36, INT nOffset=0);
	virtual ~CEMSBeaconMsg( );

	BOOL IsLongMsgFmt( void );

	void Set( float *lpfArray144 );
	void Set( LPBYTE lpcBinary, INT nLength=18, INT nOffset=0);
	void Set( LPCTSTR lpcszHex, INT nLength=36, INT nOffset=0);

	INT64 GetID( void ) { return m_i64ID; }

private: // methods
	BOOL _Init( void );

private:	// data
	BYTE			m_cMsg[18];
	INT64			m_i64ID;
};

#endif // INC_BEACONMSG

