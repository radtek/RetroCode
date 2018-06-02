# Microsoft Developer Studio Project File - Name="Mp3 Decoder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=Mp3 Decoder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Mp3 Decoder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mp3 Decoder.mak" CFG="Mp3 Decoder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mp3 Decoder - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "Mp3 Decoder - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Mp3 Decoder - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "WIN32GUI" /D "DAMN_INTEL_BYTE_ORDER" /YX /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Mp3 Decoder.lib"

!ELSEIF  "$(CFG)" == "Mp3 Decoder - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "__WIN32__" /D "WIN32GUI" /D "DAMN_INTEL_BYTE_ORDER" /YX /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\Libs\Mp3 Decoder.lib"

!ENDIF 

# Begin Target

# Name "Mp3 Decoder - Win32 Release"
# Name "Mp3 Decoder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bit_res.cpp
# End Source File
# Begin Source File

SOURCE=.\cmdline.cpp
# End Source File
# Begin Source File

SOURCE=.\crc.cpp
# End Source File
# Begin Source File

SOURCE=.\header.cpp
# End Source File
# Begin Source File

SOURCE=.\huffman.cpp
# End Source File
# Begin Source File

SOURCE=.\ibitstr.cpp
# End Source File
# Begin Source File

SOURCE=.\inv_mdct.cpp
# End Source File
# Begin Source File

SOURCE=.\l3table.cpp
# End Source File
# Begin Source File

SOURCE=.\layer3.cpp
# End Source File
# Begin Source File

SOURCE=.\maplay.cpp
# End Source File
# Begin Source File

SOURCE=.\mci_obuf.cpp
# End Source File
# Begin Source File

SOURCE=.\obuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\playlist.cpp
# End Source File
# Begin Source File

SOURCE=.\scalfact.cpp
# End Source File
# Begin Source File

SOURCE=.\str_lib.cpp
# End Source File
# Begin Source File

SOURCE=.\sublay1.cpp
# End Source File
# Begin Source File

SOURCE=.\sublay2.cpp
# End Source File
# Begin Source File

SOURCE=.\synfilt.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\all.h
# End Source File
# Begin Source File

SOURCE=.\args.h
# End Source File
# Begin Source File

SOURCE=.\bit_res.h
# End Source File
# Begin Source File

SOURCE=.\crc.h
# End Source File
# Begin Source File

SOURCE=.\fileobuf.h
# End Source File
# Begin Source File

SOURCE=.\header.h
# End Source File
# Begin Source File

SOURCE=.\huffman.h
# End Source File
# Begin Source File

SOURCE=.\ibitstr.h
# End Source File
# Begin Source File

SOURCE=.\inv_mdct.h
# End Source File
# Begin Source File

SOURCE=.\l3table.h
# End Source File
# Begin Source File

SOURCE=.\l3type.h
# End Source File
# Begin Source File

SOURCE=.\layer3.h
# End Source File
# Begin Source File

SOURCE=.\mci_obuf.h
# End Source File
# Begin Source File

SOURCE=.\mpw_msg.h
# End Source File
# Begin Source File

SOURCE=.\mutx_imp.h
# End Source File
# Begin Source File

SOURCE=.\obuffer.h
# End Source File
# Begin Source File

SOURCE=.\playlist.h
# End Source File
# Begin Source File

SOURCE=.\scalfact.h
# End Source File
# Begin Source File

SOURCE=.\str_lib.h
# End Source File
# Begin Source File

SOURCE=.\subband.h
# End Source File
# Begin Source File

SOURCE=.\sublay1.h
# End Source File
# Begin Source File

SOURCE=.\sublay2.h
# End Source File
# Begin Source File

SOURCE=.\synfilt.h
# End Source File
# Begin Source File

SOURCE=.\wavefile_obuffer.h
# End Source File
# End Group
# End Target
# End Project
