// MibHolder.h: interface for the MibHolder class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMIBHOLDER_H__80ACCB3A_BBBA_4F59_A24D_A5952E2FF879__INCLUDED_)
#define AFX_CMIBHOLDER_H__80ACCB3A_BBBA_4F59_A24D_A5952E2FF879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ISnmpMib.h"

class CMibHolder : public ISnmpMib  
{
public:
	CMibHolder();
	bool Create(char *License);
	virtual ~CMibHolder();
};

#endif // !defined(AFX_CMIBHOLDER_H__80ACCB3A_BBBA_4F59_A24D_A5952E2FF879__INCLUDED_)
