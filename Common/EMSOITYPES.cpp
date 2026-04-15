///////////////////////////////////////////////////////////////////////////////
//  EMSOITYPES.cpp
//
//  PATH: C:\Dev\common
//
//  CREATED: 1/29/2003 2:24:41 PM by Christiaan Burchell
//
//  PURPOSE:  Common Types for the Operator Interface
//
//  COPYRIGHT NOTICE: Copyright (c) 2003-2005 by EMS Technologies, Inc., All rights reserved
//
//  LAST CHANGED: $Date$
//
//  REVISION HISTORY:
//  $Log$

// 

//#include "stdafx.h"
#include "EMSOITYPES.h"
#define INITGUID
#include <initguid.h>
#include "emsiteif.H"
#include "EMSOIConfig.h"
#include <atlbase.h>




const TCHAR c_szGeoLut600[] = TEXT("GeoLUT600");	
const TCHAR c_szLeoLut600[] = TEXT("LeoLUT600");	
const TCHAR c_szMeoLut600[] = TEXT("MeoLUT600");	
const TCHAR c_szOpInt[]		 = TEXT("Operator Interface");	
const TCHAR c_szATLut500[] = TEXT("ATLUT500");	
const TCHAR c_szTSILeoLut[] = TEXT("TSILeoLUT");	
const TCHAR c_szUnknownLut[] = TEXT("Unknown LUT");	
const TCHAR c_szLutServer[] = _T("LUT Server");

////////////////////////////////////////////////
//
// NAME: EMSOIType_GetTypeStr
//
// DESCRIPTION: Gets the Type string
//
// CREATED:     1/29/2003 2:25:00 PM
//
// PARAMETERS: 
//             EMSLUTType_e type
//
// RETURN: const char* 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
const TCHAR* EMSOIType_GetTypeStr(EMSLUTTYPECODE type)
{
	switch ( type )
		{
			case EMSGeoLut600:	return c_szGeoLut600;	break;
			case EMSLeoLut600:	return c_szLeoLut600;	break;
			case EMSMeoLut600:	return c_szMeoLut600;	break;
			case EMSOpIntType:	return c_szOpInt;			break;
			case EMSATLut500:		return c_szATLut500;		break;
			case EMSTSILeoLut:	return c_szTSILeoLut;	break;
            case EMSLutClopType:	return c_szLutServer;	break;
			default:					return c_szUnknownLut;	break;
		}
}



////////////////////////////////////////////////
//
// NAME: EMSOIType_GetStateStr
//
// DESCRIPTION: Gets the State String
//
// CREATED:     1/29/2003 2:25:21 PM
//
// PARAMETERS: 
//             EMSState_e type
//
// RETURN: const char* 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
const TCHAR* EMSOIType_GetStateStr(EMSState_e type)
{
    static const TCHAR* TypeStr[] = {_T("Ok"),_T("Warn"),_T("Error"),_T("Off"),_T("None"),_T("Unknown")};
    if(type>EMSState_MAX || type<0)
        return TypeStr[EMSState_MAX];
    return TypeStr[type];
}



////////////////////////////////////////////////
//
// NAME: EMSOIType_GetStateColour
//
// DESCRIPTION: Gets a colour based on the state
//
// CREATED:     2/20/2003 5:57:06 PM
//
// PARAMETERS: 
//             EMSState_e type
//
// RETURN: const DWORD 
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
const DWORD EMSOIType_GetStateColour(EMSState_e type)
{
    static const DWORD TypeColour[] = {RGB(0,255,0),RGB(255,255,0),RGB(255,0,0),RGB(128,128,128),RGB(255,255,255),RGB(255,255,255)};
    if(type>EMSState_MAX || type<0)
        return TypeColour[EMSState_MAX];
    return TypeColour[type];
}


void _PrintComError(const char* file,const int line,_com_error &e)
{
     _bstr_t bstrSource(e.Source());
	 _bstr_t bstrDescription(e.Description());
	// Print COM errors. 
    
#ifdef _UNICODE
    USES_CONVERSION;
	EMSTRACE2(TEXT("Error %s(%d)\n"),A2W(file),line);
#else
    EMSTRACE2(TEXT("Error %s(%d)\n"),file,line);
#endif
	EMSTRACE1(TEXT("\tCode = %08lx\n"), e.Error());
	EMSTRACE1(TEXT("\tCode meaning = %s\n"), e.ErrorMessage());
	EMSTRACE1(TEXT("\tSource = %s\n"), (LPCWSTR) bstrSource);
	EMSTRACE1(TEXT("\tDescription = %s\n"), (LPCWSTR) bstrDescription);

    //CString error;
    //error.Format("Error %s(%d)\n\tCode = %08lx\n\tCode meaning = %s\n\tSource = %s\n\tDescription = %s\n",file,line,e.Error(),e.ErrorMessage(),bstrSource,bstrDescription);
    //AfxMessageBox(error);
}



/////////////////////////////////////////////////
///
/// NAME: DSNFromLutID
///
/// DESCRIPTION: Gets the DNS from the LUT ID
///
/// CREATED:     9/23/2003 10:38:16 AM
///
/// PARAMETERS: 
///             DWORD LutID
///             TCHAR* buffer
///             DWORD MaxSize
///
/// RETURN: TCHAR* 
///
/// SIDE EFFECTS: 
///
/////////////////////////////////////////////////
TCHAR* CreateConnectionString(DWORD LutID,TCHAR* buffer,DWORD MaxSize,BOOL bDatabase)
{
    if(bDatabase)
    {
        CEMSOIConfig* pConfig = CEMSOIConfig::GetInstance();
	    DWORD	            ulSiteID = pConfig->GetLocalLutID();
        if(LutID == ulSiteID)
        {
            ::_sntprintf(buffer,MaxSize,_T("Provider=MSDASQL;data source=LeoLut600 Database;"));
        }
        else
        {
            ::_sntprintf(buffer,MaxSize,_T("data source=LUT_%d;"),LutID);
        }
    }
    else
    {
        ::_sntprintf(buffer,MaxSize,_T("%d"),LutID);
    }
    return buffer;
}