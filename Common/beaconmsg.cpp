/********************************************************************
*	Module:			BeaconMsg.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Implementation of the CEMSBeaconMsg class
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
#include <string.h>

#include "beaconmsg.h"

CEMSBeaconMsg::CEMSBeaconMsg( )
{
	_Init();
}

CEMSBeaconMsg::~CEMSBeaconMsg( )
{
}

BOOL CEMSBeaconMsg::_Init( void )
{
	m_i64ID = 0;

	memset( m_cMsg, 0, sizeof( m_cMsg ) );

	return TRUE;
}

CEMSBeaconMsg::CEMSBeaconMsg( float *lpfArray144 )
{
	Set( lpfArray144 );
}

CEMSBeaconMsg::CEMSBeaconMsg( LPBYTE lpcBinary, INT nLength, INT nOffset )
{
	Set( lpcBinary, nLength, nOffset );
}

CEMSBeaconMsg::CEMSBeaconMsg( LPCTSTR lpcszHex, INT nLength, INT nOffset )
{
	Set( lpcszHex, nLength, nOffset );
}

void CEMSBeaconMsg::Set( float *lpfArray144 )
{
	if ( lpfArray144 )
	{
    for ( int i = 0; i < 18; i++ )
    {
        m_cMsg[i] = 0;

        for ( int j = 0; j < 8; j++ )
        {
            m_cMsg[i] <<= 1;

            if ( *lpfArray144 > 0 )
            {
                m_cMsg[i]++;
            }

            lpfArray144++;
        }
    }
	}
	m_i64ID = 0;
}

void CEMSBeaconMsg::Set( LPBYTE lpcBinary, INT nLength, INT nOffset )
{
	memset( m_cMsg, 0, sizeof( m_cMsg ) );

	if ( lpcBinary && ( nOffset + nLength < sizeof( m_cMsg ) ) )
	{
		for ( int i = nOffset; i < nOffset+nLength; i++ )
		{
			m_cMsg[ i ] = *lpcBinary;

			lpcBinary++;
		}
	}
}

void CEMSBeaconMsg::Set( LPCTSTR lpcszHex, INT nLength, INT nOffset )
{
	memset( m_cMsg, 0, sizeof( m_cMsg ) );
}

BOOL CEMSBeaconMsg::IsLongMsgFmt( void )
{
	BOOL bFlag = FALSE;

	return bFlag;
}
