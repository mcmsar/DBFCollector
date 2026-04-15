/********************************************************************
*	Module:			emsencod.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSEncodedSatID & CEMSEncodedLutID
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
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

	0.0	2001/09/17	rvw	start

********************************************************************/
#ifndef INC_EMSENCOD
#define INC_EMSENCOD

#include <sstream>

#include "emserror.h"

typedef BYTE EMSENCODEDSATID[16];

typedef BYTE EMSENCODEDLUTID[16];

class CEMSEncodedSatID
{
public:
	CEMSEncodedSatID();
	~CEMSEncodedSatID();

	static EMS_RESULT Reset( EMSENCODEDSATID *lpID );
	static EMS_RESULT Reset( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT Set( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT Set( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulCount );
	static EMS_RESULT Expand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount );
	static BOOL Test( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static int Count( EMSENCODEDSATID *lpID );

	static std::string GetDecodedStringA( const EMSENCODEDSATID caSat );
	static std::wstring GetDecodedStringW( const EMSENCODEDSATID caSat );
#ifdef UNICODE
	static std::wstring GetDecodedString( const EMSENCODEDSATID caSat ) { return GetDecodedStringW( caSat ); }
#else
	static std::string GetDecodedString( const EMSENCODEDSATID caSat ) { return GetDecodedStringA( caSat ); }
#endif

private:
	static	bool _NewFmt( EMSENCODEDSATID *lpID );
	static	int _Index( ULONG ulSatID );
	static	int _Bit( ULONG ulSatID );
	static	int _Byte( ULONG ulSatID );

	static EMS_RESULT _OldReset( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT _OldSet( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT _OldSet( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulCount );
	static EMS_RESULT _OldExpand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount );
	static BOOL _OldTest( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static int _OldCount( EMSENCODEDSATID *lpID );

	static EMS_RESULT _NewReset( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT _NewSet( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static EMS_RESULT _NewSet( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulCount );
	static EMS_RESULT _NewExpand( EMSENCODEDSATID *lpID, ULONG *lpulSatID, ULONG ulMax, ULONG *lpulCount );
	static BOOL _NewTest( EMSENCODEDSATID *lpID, ULONG ulSatID );
	static int _NewCount( EMSENCODEDSATID *lpID );

	static bool _TestBit( EMSENCODEDSATID *lpID, int nBitNumber );
	static void _SetBit( EMSENCODEDSATID *lpID, int nBitNumber );

};

class CEMSEncodedLutID
{
public:
	CEMSEncodedLutID();
	~CEMSEncodedLutID();

	static EMS_RESULT Reset( EMSENCODEDLUTID *lpID );
	static EMS_RESULT Reset( EMSENCODEDLUTID *lpID, ULONG ulLutID );
	static EMS_RESULT Set( EMSENCODEDLUTID *lpID, ULONG ulLutID );
	static EMS_RESULT Set( EMSENCODEDLUTID *lpID, ULONG *lpulLutID, ULONG ulCount );
	static EMS_RESULT Expand( const EMSENCODEDLUTID *lpID, ULONG *lpulLutID, ULONG ulMax, ULONG *lpulCount );
	static EMS_RESULT Encode( ULONG* aulLutIDs, ULONG ulLuts, EMSENCODEDLUTID* lpID );
	static BOOL Test( EMSENCODEDLUTID *lpID, ULONG ulLutID );
	static int Count( EMSENCODEDLUTID *lpID );
	static std::string GetDecodedStringA( const EMSENCODEDLUTID caLut );
	static std::wstring GetDecodedStringW( const EMSENCODEDLUTID caLut );
#ifdef UNICODE
	static std::wstring GetDecodedString( const EMSENCODEDLUTID caLut ) { return GetDecodedStringW( caLut ); }
#else
	static std::string GetDecodedString( const EMSENCODEDLUTID caLut ) { return GetDecodedStringA( caLut ); }
#endif

private:
	static int _Index( EMSENCODEDLUTID *lpID, ULONG ulLutID );
};



#endif // INC_EMSENCOD
