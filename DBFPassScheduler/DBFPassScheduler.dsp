# Microsoft Developer Studio Project File - Name="DBFPassScheduler" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=DBFPassScheduler - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "DBFPassScheduler.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "DBFPassScheduler.mak" CFG="DBFPassScheduler - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "DBFPassScheduler - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "DBFPassScheduler - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "DBFPassScheduler - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\common\include" /I "..\3rd party\microsoft\microsoft sdk\include" /I "..\3rd party\microsoft\msxml4" /I "..\..\common\include" /I "..\..\3rd party\microsoft\microsoft sdk\include" /I "..\..\3rd party\microsoft\msxml4" /I "..\ADBoards\GS" /I "..ADBoards\GS\Include" /I "..\3rd party\intel\ipp\5.2\ia32\include" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "EMS_USE_INTEL_PP" /YX /FD /c
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /machine:I386 /out:"Release/EMSDBFPassScheduler.exe"

!ELSEIF  "$(CFG)" == "DBFPassScheduler - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\common\include" /I "..\3rd party\microsoft\microsoft sdk\include" /I "..\3rd party\microsoft\msxml4" /I "..\..\common\include" /I "..\..\3rd party\microsoft\microsoft sdk\include" /I "..\..\3rd party\microsoft\msxml4" /I "..\ADBoards\GS" /I "..ADBoards\GS\Include" /I "..\3rd party\intel\ipp\5.2\ia32\include" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D _WIN32_WINNT=0x400 /D "EMS_USE_INTEL_PP" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /subsystem:console /debug /machine:I386 /out:"Debug/EMSDBFPassScheduler.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "DBFPassScheduler - Win32 Release"
# Name "DBFPassScheduler - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Common\AOBJBASE.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\ConfigurationAccessor.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\convutility.cpp
# End Source File
# Begin Source File

SOURCE=..\ADBoards\GS\DBFDataMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\DBFNullPointing.cpp
# End Source File
# Begin Source File

SOURCE=.\DBFPassScheduler.cpp
# End Source File
# Begin Source File

SOURCE=.\DBFPointingAngles.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\EMSCLOCK.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSCMREG.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSCOORD.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\emsdomdocument.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\emsdomnode.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\emsdomnodelist.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\EMSEARTH.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSENCOD.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSEXCPT.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSRANGE.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\Emssun.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\EMSTIME.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\EMSVECTR.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\ESECDESC.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\Eservice.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\LOGEVENT.CPP
# End Source File
# Begin Source File

SOURCE=..\Common\LogMsgParam.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\LogRegistrySettings.cpp
# End Source File
# Begin Source File

SOURCE=..\Common\RegistrySettings.cpp
# End Source File
# Begin Source File

SOURCE=.\SIGPROC.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\Common\Library\logger2sd.lib

!IF  "$(CFG)" == "DBFPassScheduler - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "DBFPassScheduler - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Common\Library\logger2s.lib

!IF  "$(CFG)" == "DBFPassScheduler - Win32 Release"

!ELSEIF  "$(CFG)" == "DBFPassScheduler - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\3rd Party\Intel\IPP\5.2\ia32\stublib\ipps.lib"
# End Source File
# Begin Source File

SOURCE="..\3rd Party\Intel\IPP\5.2\ia32\stublib\ippm.lib"
# End Source File
# End Target
# End Project
