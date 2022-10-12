# Microsoft Developer Studio Project File - Name="OpenExifi" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=OpenExifi - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenExifi.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenExifi.mak" CFG="OpenExifi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OpenExifi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OpenExifi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OpenExifi - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Releasei"
# PROP Intermediate_Dir "Releasei"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENEXIFI_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W2 /GR /GX /O2 /I "$(JPEGROOT)" /I "$(JPEGROOT)\inc" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "EXIF_BUILD_DLL" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ole32.lib /nologo /dll /machine:I386
# ADD LINK32 jpeg.lib ole32.lib /nologo /dll /machine:I386 /out:"../../../lib/openexifi.dll" /implib:"../../../lib/openexifi.lib" /libpath:"$(JPEGROOT)" /libpath:"$(JPEGROOT)\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "OpenExifi - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debugi"
# PROP Intermediate_Dir "Debugi"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OPENEXIFI_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(JPEGROOT)" /I "$(JPEGROOT)\inc" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "EXIF_BUILD_DLL" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ole32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jpeg.lib ole32.lib /nologo /dll /debug /machine:I386 /out:"../../../lib/openexifid.dll" /implib:"../../../lib/openexifid.lib" /pdbtype:sept /libpath:"$(JPEGROOT)" /libpath:"$(JPEGROOT)\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "OpenExifi - Win32 Release"
# Name "OpenExifi - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\ExifApp0Seg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifApp3Seg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifAppSegManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifAppSegment.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifFileIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIFD.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIJGWrapper.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIJGWriteFrame.c
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifImageDescUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifImageFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifInternetIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegDataDst.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegDataSrc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifMemoryIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifMisc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifOpenFile.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifRawAppSeg.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifStripImage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifTiffAppSeg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\ExifApp0Seg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifApp3Seg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifAppSegManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifAppSegment.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifComp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifConf.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifDefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifErrorCodes.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifFactoryT.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifFileIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifGPtr.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIFD.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIJGWrapper.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIJGWriteFrame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifImageDescUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifImageFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifInternetIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegExtn.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifJpegTables.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifMapT.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifMemoryIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifMisc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifOpenFile.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifRawAppSeg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifStripImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifTagEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifTags.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifTiffAppSeg.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ExifTypeDefs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
