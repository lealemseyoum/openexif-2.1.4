# Microsoft Developer Studio Project File - Name="openexif" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=openexif - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OpenExif.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OpenExif.mak" CFG="openexif - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "openexif - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "openexif - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "openexif - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "openexif___Win32_Release"
# PROP BASE Intermediate_Dir "openexif___Win32_Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(JPEGROOT)" /I "$(JPEGROOT)\inc" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\openexif.lib"

!ELSEIF  "$(CFG)" == "openexif - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "openexif___Win32_Debug"
# PROP BASE Intermediate_Dir "openexif___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(JPEGROOT)" /I "$(JPEGROOT)\inc" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\lib\openexifd.lib"

!ENDIF 

# Begin Target

# Name "openexif - Win32 Release"
# Name "openexif - Win32 Debug"
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
# End Target
# End Project
