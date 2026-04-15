# Microsoft Developer Studio Project File - Name="Common" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Common - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Common.mak" CFG="Common - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Common - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Common - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Common"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Common - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "Common - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Common___Win32_Debug"
# PROP BASE Intermediate_Dir "Common___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Common___Win32_Debug"
# PROP Intermediate_Dir "Common___Win32_Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "Common - Win32 Release"
# Name "Common - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ADBOARD.CPP
# End Source File
# Begin Source File

SOURCE=.\AntennaTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\AOBJBASE.CPP
# End Source File
# Begin Source File

SOURCE=.\BCNCOUNT.CPP
# End Source File
# Begin Source File

SOURCE=.\beaconmsg.cpp
# End Source File
# Begin Source File

SOURCE=.\BinaryStream.cpp
# End Source File
# Begin Source File

SOURCE=.\BinMsgBody.cpp
# End Source File
# Begin Source File

SOURCE=.\Calib406BinStrm.cpp
# End Source File
# Begin Source File

SOURCE=.\calibcbcbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CBCBinStrm.cpp
# End Source File
# Begin Source File

SOURCE=.\CMDSINK.CPP
# End Source File
# Begin Source File

SOURCE=.\CMDSRC.CPP
# End Source File
# Begin Source File

SOURCE=.\comb406binstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\configbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\convutility.cpp
# End Source File
# Begin Source File

SOURCE=.\CountryCodes.cpp
# End Source File
# Begin Source File

SOURCE=.\dbutils.cpp
# End Source File
# Begin Source File

SOURCE=.\DCB32.cpp
# End Source File
# Begin Source File

SOURCE=.\ecmdproc.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSAntTime.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSBCH.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSBEACON.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSBEACONDF.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSBEACONID.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSCLOCK.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSCMREG.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSCONFG.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSCOORD.CPP
# End Source File
# Begin Source File

SOURCE=.\emsdberrorreporter.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSDEVFINDER.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSDEVREG.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSDOPPL.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSDYNMSTRM.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSEARTH.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSENCOD.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSEXCPT.CPP
# End Source File
# Begin Source File

SOURCE=.\emsflist.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSFSTRM.CPP
# End Source File
# Begin Source File

SOURCE=.\emsinifile.cpp
# End Source File
# Begin Source File

SOURCE=.\Emsit115.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSIT121.CPP
# End Source File
# Begin Source File

SOURCE=.\Emsit122.cpp
# End Source File
# Begin Source File

SOURCE=.\Emsit125.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSIT161.CPP
# End Source File
# Begin Source File

SOURCE=.\Emsit165.cpp
# End Source File
# Begin Source File

SOURCE=.\Emsit172.cpp
# End Source File
# Begin Source File

SOURCE=.\Emsit173.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSIT175.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT215.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT255.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT260.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT270.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT415.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT510.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT605.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT661.CPP
# End Source File
# Begin Source File

SOURCE=.\emsit662.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSIT750.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT751.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT760.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT770.CPP
# End Source File
# Begin Source File

SOURCE=.\emsit915.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSIT950.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT951.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT960.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSIT970.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSLOCAL.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSMSTRM.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSMUTEX.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSOITYPES.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSRANGE.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSRGKEY.CPP
# End Source File
# Begin Source File

SOURCE=.\emsrollover.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSSIT.CPP
# End Source File
# Begin Source File

SOURCE=.\emssourceinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\Emssun.cpp
# End Source File
# Begin Source File

SOURCE=.\emsthread.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSTIME.CPP
# End Source File
# Begin Source File

SOURCE=.\EMSTokenMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\EMSVECTR.CPP
# End Source File
# Begin Source File

SOURCE=.\ESECDESC.CPP
# End Source File
# Begin Source File

SOURCE=.\Eservice.cpp
# End Source File
# Begin Source File

SOURCE=.\ExceptionLogger.cpp
# End Source File
# Begin Source File

SOURCE=.\HexUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\lineterminator.cpp
# End Source File
# Begin Source File

SOURCE=.\LocateBinStrm.cpp
# End Source File
# Begin Source File

SOURCE=.\logbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\LOGEVENT.CPP
# End Source File
# Begin Source File

SOURCE=.\Logger.cpp
# End Source File
# Begin Source File

SOURCE=.\LogMsgParam.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\msgnotificationmgr.cpp
# End Source File
# Begin Source File

SOURCE=.\NEXTVIS.CPP
# End Source File
# Begin Source File

SOURCE=.\PASSCHED.CPP
# End Source File
# Begin Source File

SOURCE=.\PKSINK.CPP
# End Source File
# Begin Source File

SOURCE=.\PKSOURCE.CPP
# End Source File
# Begin Source File

SOURCE=.\PKSTREAM.CPP
# End Source File
# Begin Source File

SOURCE=.\residualbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\RS232.cpp
# End Source File
# Begin Source File

SOURCE=.\SARAntenna.cpp
# End Source File
# Begin Source File

SOURCE=.\sarpbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sarpcalibbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sarrbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sarrcalibbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\sattrackbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\SHAREMEM.CPP
# End Source File
# Begin Source File

SOURCE=.\SIGPROC.CPP
# End Source File
# Begin Source File

SOURCE=.\SITConverter.cpp
# End Source File
# Begin Source File

SOURCE=.\SITFIELD.CPP
# End Source File
# Begin Source File

SOURCE=.\SitHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\SITPARSE.CPP
# End Source File
# Begin Source File

SOURCE=.\sitstream.cpp
# End Source File
# Begin Source File

SOURCE=.\SITTOKEN.CPP
# End Source File
# Begin Source File

SOURCE=.\spectrumbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\statusbinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\TCountryCdData.cpp
# End Source File
# Begin Source File

SOURCE=.\TEncodedMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\tlebinstrm.cpp
# End Source File
# Begin Source File

SOURCE=.\TSARData.cpp
# End Source File
# Begin Source File

SOURCE=.\Win32Port.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Include\41632dll.h
# End Source File
# Begin Source File

SOURCE=.\Include\416vxdio.h
# End Source File
# Begin Source File

SOURCE=.\Include\ADBOARD.H
# End Source File
# Begin Source File

SOURCE=.\Include\alertflt.h
# End Source File
# Begin Source File

SOURCE=.\Include\ALRMINFO.h
# End Source File
# Begin Source File

SOURCE=.\Include\ANTDEFNS.H
# End Source File
# Begin Source File

SOURCE=.\Include\Antenna.h
# End Source File
# Begin Source File

SOURCE=.\Include\AntennaTracker.h
# End Source File
# Begin Source File

SOURCE=.\Include\AntError.h
# End Source File
# Begin Source File

SOURCE=.\Include\antmsgs.h
# End Source File
# Begin Source File

SOURCE=.\Include\AntTypes.h
# End Source File
# Begin Source File

SOURCE=.\Include\AOBJBASE.H
# End Source File
# Begin Source File

SOURCE=.\Include\array.h
# End Source File
# Begin Source File

SOURCE=.\Include\audiodat.h
# End Source File
# Begin Source File

SOURCE=.\Include\BCNCOUNT.H
# End Source File
# Begin Source File

SOURCE=.\Include\beaconmsg.h
# End Source File
# Begin Source File

SOURCE=.\Include\BinaryStream.h
# End Source File
# Begin Source File

SOURCE=.\Include\BinMsgBody.h
# End Source File
# Begin Source File

SOURCE=.\Include\CALIB406.H
# End Source File
# Begin Source File

SOURCE=.\Include\Calib406BinStrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\calib406msg.h
# End Source File
# Begin Source File

SOURCE=.\Include\calibcbcbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\CBCBinStrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\CBCDATA.H
# End Source File
# Begin Source File

SOURCE=.\Include\CBCOUT.H
# End Source File
# Begin Source File

SOURCE=.\Include\CMDSINK.H
# End Source File
# Begin Source File

SOURCE=.\Include\CMDSRC.H
# End Source File
# Begin Source File

SOURCE=.\Include\CMMLIB.H
# End Source File
# Begin Source File

SOURCE=.\Include\Collector_Data_Types.h
# End Source File
# Begin Source File

SOURCE=.\Include\collmsgs.h
# End Source File
# Begin Source File

SOURCE=.\Include\comb406binstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\combine406.h
# End Source File
# Begin Source File

SOURCE=.\Include\configbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\convutility.h
# End Source File
# Begin Source File

SOURCE=.\Include\CountryCodes.h
# End Source File
# Begin Source File

SOURCE=.\Include\CriticalSection.h
# End Source File
# Begin Source File

SOURCE=.\Include\DartFtp.h
# End Source File
# Begin Source File

SOURCE=.\Include\DartSock.h
# End Source File
# Begin Source File

SOURCE=.\Include\DataAccessor.h
# End Source File
# Begin Source File

SOURCE=.\Include\dbsmsgs.h
# End Source File
# Begin Source File

SOURCE=.\Include\DCB32.h
# End Source File
# Begin Source File

SOURCE=.\Include\DEBUGWIN.H
# End Source File
# Begin Source File

SOURCE=.\Include\ecmdproc.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSALARM.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSANTENNA.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSAntTime.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsarchive.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSATINF.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSAUDIO.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBCH.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBEACN.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBEACON.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBEACONDF.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBEACONDFNS.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSBEACONID.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCLOCK.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCMDSK.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCMREG.H
# End Source File
# Begin Source File

SOURCE=.\Include\emscollsummary.h
# End Source File
# Begin Source File

SOURCE=.\Include\emscom.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCONFG.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCONST.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSCOORD.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsdberrorreporter.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSDEVFINDER.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSDEVICES.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSDEVREG.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsdoor.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSDOPPL.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSDYNMSTRM.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSEARTH.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSENCOD.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsenvir.h
# End Source File
# Begin Source File

SOURCE=.\Include\emserror.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSEXCPT.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsflist.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSFSTRM.H
# End Source File
# Begin Source File

SOURCE=.\Include\emshumid.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSICFG.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsinifile.h
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit115.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT121.H
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit122.h
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit125.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT161.H
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit165.h
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit172.h
# End Source File
# Begin Source File

SOURCE=.\Include\Emsit173.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT175.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT215.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT255.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT260.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsit270.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT415.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT510.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT605.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT661.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsit662.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT750.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT751.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT760.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT770.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsit915.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT950.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT951.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT960.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSIT970.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsiteif.H
# End Source File
# Begin Source File

SOURCE=.\Include\emslinfo.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSLOCAL.H
# End Source File
# Begin Source File

SOURCE=.\Include\emslog.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsloggr.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSLutPicker.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsmanoeuvre.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsmon.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSMSTRM.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSMUTEX.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSOITYPES.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSORBIT.h
# End Source File
# Begin Source File

SOURCE=.\Include\emspass.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSPassSched.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSPIPE.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSRANGE.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSRGKEY.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsrollover.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSSATX.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSSIT.H
# End Source File
# Begin Source File

SOURCE=.\Include\emssourceinfo.h
# End Source File
# Begin Source File

SOURCE=.\Include\Emssun.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSSWITCH.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSSYSTEMTEST.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSTALEO.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSTATUS.h
# End Source File
# Begin Source File

SOURCE=.\Include\emstemp.h
# End Source File
# Begin Source File

SOURCE=.\Include\emsthread.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSTIME.H
# End Source File
# Begin Source File

SOURCE=.\Include\emstle.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSTokenMgr.h
# End Source File
# Begin Source File

SOURCE=.\Include\emstrack.h
# End Source File
# Begin Source File

SOURCE=.\Include\emstypes.H
# End Source File
# Begin Source File

SOURCE=.\Include\EMSTYPEX.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsups.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSVECTR.H
# End Source File
# Begin Source File

SOURCE=.\Include\emsvolt.h
# End Source File
# Begin Source File

SOURCE=.\Include\EMSWIND.h
# End Source File
# Begin Source File

SOURCE=.\Include\ESARError.h
# End Source File
# Begin Source File

SOURCE=.\Include\ESECDESC.H
# End Source File
# Begin Source File

SOURCE=.\Include\Eservice.h
# End Source File
# Begin Source File

SOURCE=.\Include\ExceptionLogger.h
# End Source File
# Begin Source File

SOURCE=.\Include\fftdata.h
# End Source File
# Begin Source File

SOURCE=.\Include\FILESIGN.H
# End Source File
# Begin Source File

SOURCE=.\Include\gpsclock.h
# End Source File
# Begin Source File

SOURCE=.\Include\HexUtils.h
# End Source File
# Begin Source File

SOURCE=.\Include\igateway.h
# End Source File
# Begin Source File

SOURCE=.\Include\IMsgBody.h
# End Source File
# Begin Source File

SOURCE=.\Include\JRNLMSGS.H
# End Source File
# Begin Source File

SOURCE=.\Include\LEO600Devices.h
# End Source File
# Begin Source File

SOURCE=.\Include\leodefns.h
# End Source File
# Begin Source File

SOURCE=.\Include\LeoLut600DBS.h
# End Source File
# Begin Source File

SOURCE=.\Include\LEOSITE.h
# End Source File
# Begin Source File

SOURCE=.\Include\leostats.h
# End Source File
# Begin Source File

SOURCE=.\Include\LineTerminator.h
# End Source File
# Begin Source File

SOURCE=.\Include\LOCATE.H
# End Source File
# Begin Source File

SOURCE=.\Include\LocateBinStrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\logbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\LOGEVENT.H
# End Source File
# Begin Source File

SOURCE=.\Include\Logger.h
# End Source File
# Begin Source File

SOURCE=.\Include\loggrcat.h
# End Source File
# Begin Source File

SOURCE=.\Include\LogMsgParam.h
# End Source File
# Begin Source File

SOURCE=.\Include\Memory_Data_Types.h
# End Source File
# Begin Source File

SOURCE=.\Include\Memory_Functions.h
# End Source File
# Begin Source File

SOURCE=.\Include\MEMTYPES.H
# End Source File
# Begin Source File

SOURCE=.\Include\MessType.h
# End Source File
# Begin Source File

SOURCE=.\Include\msgnotificationmgr.h
# End Source File
# Begin Source File

SOURCE=.\Include\MTDeque.h
# End Source File
# Begin Source File

SOURCE=.\Include\MTL.h
# End Source File
# Begin Source File

SOURCE=.\Include\MTLConfiguration.h
# End Source File
# Begin Source File

SOURCE=.\Include\NEXTVIS.H
# End Source File
# Begin Source File

SOURCE=.\Include\Nsp.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspalloc.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsparith.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspcnv2d.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspconv.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspcorr.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspcvrt.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspdct.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspdotp.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsperror.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspfft.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspfir2.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspfirg.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspfirh.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspfirl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspgrtzl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspgrtzw.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspiirh.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspiirl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsplaw.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsplmsh.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsplmsl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsplnexp.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsplogic.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspmisc.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspnorm.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsppatch.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsprand.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspsampl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsptone.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nsptrngl.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspvec.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspwarn.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspwin.h
# End Source File
# Begin Source File

SOURCE=.\Include\Nspwlt.h
# End Source File
# Begin Source File

SOURCE=.\Include\odetmsgs.h
# End Source File
# Begin Source File

SOURCE=.\Include\PASSCHED.H
# End Source File
# Begin Source File

SOURCE=.\Include\PCI416_32dll.h
# End Source File
# Begin Source File

SOURCE=".\Include\pci416df new.h"
# End Source File
# Begin Source File

SOURCE=.\Include\pci416df.h
# End Source File
# Begin Source File

SOURCE=.\Include\Pci416io.h
# End Source File
# Begin Source File

SOURCE=.\Include\PCI416libW95.h
# End Source File
# Begin Source File

SOURCE=.\Include\Pcilib32.h
# End Source File
# Begin Source File

SOURCE=.\Include\PDS_Data_Types.h
# End Source File
# Begin Source File

SOURCE=.\Include\pipemsgs.h
# End Source File
# Begin Source File

SOURCE=.\Include\PKSINK.H
# End Source File
# Begin Source File

SOURCE=.\Include\PKSOURCE.H
# End Source File
# Begin Source File

SOURCE=.\Include\PKSTREAM.H
# End Source File
# Begin Source File

SOURCE=.\Include\PSNOTIFY.h
# End Source File
# Begin Source File

SOURCE=.\Include\Residual.h
# End Source File
# Begin Source File

SOURCE=.\Include\residualbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\RS232.h
# End Source File
# Begin Source File

SOURCE=.\Include\SARAntenna.h
# End Source File
# Begin Source File

SOURCE=.\Include\sarpbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\sarpcalib.h
# End Source File
# Begin Source File

SOURCE=.\Include\sarpcalibbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\SARPDATA.H
# End Source File
# Begin Source File

SOURCE=.\Include\sarrbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\sarrcalib.h
# End Source File
# Begin Source File

SOURCE=.\Include\sarrcalibbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\SARRDATA.H
# End Source File
# Begin Source File

SOURCE=.\Include\SARTASK.H
# End Source File
# Begin Source File

SOURCE=.\Include\sattrackbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\SHAREMEM.H
# End Source File
# Begin Source File

SOURCE=.\Include\SIGDATA.H
# End Source File
# Begin Source File

SOURCE=.\Include\SIGPROC.H
# End Source File
# Begin Source File

SOURCE=.\Include\SITConverter.h
# End Source File
# Begin Source File

SOURCE=.\Include\SITFIELD.H
# End Source File
# Begin Source File

SOURCE=.\Include\SitHelper.h
# End Source File
# Begin Source File

SOURCE=.\Include\SITPARSE.H
# End Source File
# Begin Source File

SOURCE=.\Include\SITServerImpl.h
# End Source File
# Begin Source File

SOURCE=.\Include\sitstream.h
# End Source File
# Begin Source File

SOURCE=.\Include\SITTOKEN.H
# End Source File
# Begin Source File

SOURCE=.\Include\SITTYPES.H
# End Source File
# Begin Source File

SOURCE=.\Include\soapH.h
# End Source File
# Begin Source File

SOURCE=.\Include\soapMTLSOAPServerProxy.h
# End Source File
# Begin Source File

SOURCE=.\Include\soapstub.h
# End Source File
# Begin Source File

SOURCE=.\Include\SPECTRUM.H
# End Source File
# Begin Source File

SOURCE=.\Include\spectrumbinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\Standards.h
# End Source File
# Begin Source File

SOURCE=.\Include\STATANT.h
# End Source File
# Begin Source File

SOURCE=.\Include\statc406.h
# End Source File
# Begin Source File

SOURCE=.\Include\statccbc.h
# End Source File
# Begin Source File

SOURCE=.\Include\statcoll.h
# End Source File
# Begin Source File

SOURCE=.\Include\STATCOMB.H
# End Source File
# Begin Source File

SOURCE=.\Include\STATCOMM.h
# End Source File
# Begin Source File

SOURCE=.\Include\statenv.h
# End Source File
# Begin Source File

SOURCE=.\Include\statgeo.h
# End Source File
# Begin Source File

SOURCE=.\Include\statlocn.h
# End Source File
# Begin Source File

SOURCE=.\Include\statodet.h
# End Source File
# Begin Source File

SOURCE=.\Include\statpass.h
# End Source File
# Begin Source File

SOURCE=.\Include\statsarr.h
# End Source File
# Begin Source File

SOURCE=.\Include\STATSENS.h
# End Source File
# Begin Source File

SOURCE=.\Include\stattcal.h
# End Source File
# Begin Source File

SOURCE=.\Include\statusBinStrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\STATWIDE.h
# End Source File
# Begin Source File

SOURCE=.\Include\TBeaconID.h
# End Source File
# Begin Source File

SOURCE=.\Include\TBeaconMsg.h
# End Source File
# Begin Source File

SOURCE=.\Include\TCountryCdData.h
# End Source File
# Begin Source File

SOURCE=.\Include\TEncodedMsg.h
# End Source File
# Begin Source File

SOURCE=.\Include\TIMEFREQ.H
# End Source File
# Begin Source File

SOURCE=.\Include\tlebinstrm.h
# End Source File
# Begin Source File

SOURCE=.\Include\TrueTimeSDK.h
# End Source File
# Begin Source File

SOURCE=.\Include\TSARData.h
# End Source File
# Begin Source File

SOURCE=.\Include\TSARTime.h
# End Source File
# Begin Source File

SOURCE=.\Include\wbandmsg.h
# End Source File
# Begin Source File

SOURCE=.\Include\WBDTYPES.H
# End Source File
# Begin Source File

SOURCE=.\Include\Wideband_Data_Types.h
# End Source File
# Begin Source File

SOURCE=.\Include\Win32Port.h
# End Source File
# End Group
# End Target
# End Project
