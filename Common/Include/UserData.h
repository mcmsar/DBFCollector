/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*							All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef _USERDATA_H
#define _USERDATA_H


//! @class CEMSUserData
//! Create a copy of supplied data for later use.
//! Note that it is up to the user to supply something that 
//! can safely be copied.  For example if the data is a pointer
//! then this class will simply copy the pointer ... not the 
//! data that the pointer references.
class CEMSUserData
{
public:
	CEMSUserData( const BYTE* cabyData, const ULONG culDataSize );
	virtual ~CEMSUserData();

	//! @fn void GetData()
	//! Return a pointer to the data
	BYTE* const GetData() { return m_abyData; }

	//! @fn void GetDataSize()
	//! How many bytes of data?
	ULONG const GetDataSize() { return m_ulDataSize; }

private:
	BYTE*	m_abyData;
	ULONG	m_ulDataSize;

};

#endif // _USERDATA_H
