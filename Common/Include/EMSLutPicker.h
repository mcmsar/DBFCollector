///////////////////////////////////////////////////////////////////////////////
//  LutPicker.h
//
//  PATH: C:\Dev\LutPicker
//
//  CREATED: 1/27/2003 2:19:15 PM by Christiaan Burchell
//
//  PURPOSE:  the Lut Picker DLL
//
//  COPYRIGHT NOTICE: Copyright (c) 2003 by EMS Technologies, Inc., All rights reserved
//
//  LAST CHANGED: $Date$
//
//  REVISION HISTORY:
//  $Log$

// 


#include "EMSOITypes.h"

#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif




#ifndef __LUTPICKER_H__
#define __LUTPICKER_H__
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LUTPICKER_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// LUTPICKER_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef LUTPICKER_EXPORTS
#define LUTPICKER_API  __declspec(dllexport)
#else
#define LUTPICKER_API __declspec(dllimport)
#endif

////////////////////////////////////////////////
//
// NAME: ShowLutPickerDlg
//
// DESCRIPTION: Shows the Lut Picker Dialog
//
// CREATED:     1/27/2003 2:19:34 PM
//
// PARAMETERS: 
//             DWORD LutId : the lut ID
//             HWND hWnd   : a parent window handle for the dialog
//             EMSLUT* pLut : the selected lut data
//
// RETURN: int : IDOK succeded else dialog failed
//
// SIDE EFFECTS: 
//
////////////////////////////////////////////////
LUTPICKER_API int ShowLutPickerDlg(DWORD LutId, HWND hWnd, EMSLUT* pLut, const long clLimitToTypes = 0);

LUTPICKER_API TCHAR* DSNFromLutID(DWORD LutID,TCHAR* buffer,DWORD MaxSize);

#endif //__LUTPICKER_H__


#ifdef __cplusplus
}
#endif