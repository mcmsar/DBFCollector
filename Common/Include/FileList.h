//! @file LPCManualImpl.h
//! Header file for the CEMSFileList class.
/********************************************************************
*	Module:			FileList.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Oct30		CH		Start

********************************************************************/
#ifndef __INC_EMSFILELIST
#define __INC_EMSFILELIST

#include <vector>
using std::vector;

#include <string>
using std::string;
using std::wstring;

typedef vector<string*> FILENAMEVECTOR;
typedef vector<wstring*> FILENAMEVECTORW;

//! @class CEMSFileList 
//! Utility class for retrieving lists of files for a given path
class CEMSFileList 
{
public:
	CEMSFileList();
	~CEMSFileList();

	//! @fn GetFilenames( const char* szPath, FILENAMEVECTOR& vectorFilenames )
	//! Method to retrieve a list of filenames
	//!		szPath:
	//!			[in] Pointer to a null-terminated string that specifies a 
	//!				 valid directory or path and file name, which can 
	//!				 contain wildcard characters (* and ?). If the string 
	//!				 ends with a wildcard, a period, or a directory name, 
	//!				 the user must have access to the root and all 
	//!				 subdirectories on the path.
	//!				 In the ANSI version of this function, the name is 
	//!				 limited to MAX_PATH characters. To extend this limit 
	//!				 to 32,767 wide characters, call the Unicode version 
	//!				 of the function and prepend "\\?\" to the path. For 
	//!				 more information, see Naming a File.
	//!				 (From MSDN FindFirstFile() documentation).
	//!		vectorFilenames:
	//!			[out] An stl vector containing the names of the matching files.
	//!				  You must free the memory for the contained strings.  These
	//!				  were allocated using new.
	static void
	GetFilenames( const char* szPath, FILENAMEVECTOR& vectorFilenames );

	//! @fn ReleaseFilenames( FILENAMEVECTOR& vectorFilenames )
	//! Release the memory held in a FILENAMEVECTOR
	static void
	ReleaseFilenames( FILENAMEVECTOR& vectorFilenames );

    static void
    GetFilenamesW( const wchar_t* wszPath, FILENAMEVECTORW& vectorFilenames );

	static UINT CountExtensionFiles(wstring strFile, wstring wildcard);
	

	static void
	ReleaseFilenamesW( FILENAMEVECTORW& vectorFilenames );
};

#endif // __INC_EMSFILELIST
