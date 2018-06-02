# Microsoft Developer Studio Project File - Name="SteveMediaCenter" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SteveMediaCenter - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SteveMediaCenter.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SteveMediaCenter.mak" CFG="SteveMediaCenter - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SteveMediaCenter - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SteveMediaCenter - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/SteveMediaCenter", QRHAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SteveMediaCenter - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib strmiids.lib /nologo /subsystem:windows /machine:I386 /out:"Release/FoxMediaCenter.exe"

!ELSEIF  "$(CFG)" == "SteveMediaCenter - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D ID3LIB_LINKOPTION=1 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib strmiids.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcprtd" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SteveMediaCenter - Win32 Release"
# Name "SteveMediaCenter - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Sockets\Authorizedlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\BASE64CODER.CPP
# End Source File
# Begin Source File

SOURCE=.\Blowfish\blowfish.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildView.cpp
# End Source File
# Begin Source File

SOURCE=.\CMyCommandLineInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FileAssociationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\helpers.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Httpsock.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Job.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Jobmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManagePlayListDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MP3Info.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Msgsockwndhttp.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Msgsockwndpost.cpp
# End Source File
# Begin Source File

SOURCE=.\MyBitMapButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MyButton.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDirectXPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MyIEWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\MyMediaPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\MyStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTreeCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\NewFileTypeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewPlayListNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\NewRandomPlaylistDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\PINGJOB.CPP
# End Source File
# Begin Source File

SOURCE=.\Sockets\Pingjobmanager.cpp
# End Source File
# Begin Source File

SOURCE=.\Sockets\Pingsocket.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayListManager.cpp
# End Source File
# Begin Source File

SOURCE=.\SelectSkinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SteveMediaCenter.cpp
# End Source File
# Begin Source File

SOURCE=.\SteveMediaCenter.rc
# End Source File
# Begin Source File

SOURCE=.\TimedShutdownDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\VolumeControl.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Blowfish\Blowfish.h
# End Source File
# Begin Source File

SOURCE=.\ChildView.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\FileAssociationDlg.h
# End Source File
# Begin Source File

SOURCE=.\helpers.h
# End Source File
# Begin Source File

SOURCE=.\Sockets\Jobmanager.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManagePlayListDlg.h
# End Source File
# Begin Source File

SOURCE=.\MP3Info.h
# End Source File
# Begin Source File

SOURCE=.\MyButton.h
# End Source File
# Begin Source File

SOURCE=.\MyDirectXPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MyIEWnd.h
# End Source File
# Begin Source File

SOURCE=.\MyListBox.h
# End Source File
# Begin Source File

SOURCE=.\MyMediaPlayer.h
# End Source File
# Begin Source File

SOURCE=.\MyStatic.h
# End Source File
# Begin Source File

SOURCE=.\MyTreeCtrl.h
# End Source File
# Begin Source File

SOURCE=.\NewFileTypeDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewPlayListNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\NewRandomPlaylistDlg.h
# End Source File
# Begin Source File

SOURCE=.\Sockets\PINGJOB.H
# End Source File
# Begin Source File

SOURCE=.\Sockets\PINGJOBMANAGER.H
# End Source File
# Begin Source File

SOURCE=.\Sockets\Pingsocket.h
# End Source File
# Begin Source File

SOURCE=.\PlayListManager.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelectSkinDlg.h
# End Source File
# Begin Source File

SOURCE=.\SettingsDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SteveMediaCenter.h
# End Source File
# Begin Source File

SOURCE=.\TimedShutdownDlg.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\button_d.bmp
# End Source File
# Begin Source File

SOURCE=.\res\button_u.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\drag.bmp
# End Source File
# Begin Source File

SOURCE=.\idr_main.ico
# End Source File
# Begin Source File

SOURCE=.\res\SteveMediaCenter.ico
# End Source File
# Begin Source File

SOURCE=.\res\SteveMediaCenter.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=".\version notes.txt"
# End Source File
# End Target
# End Project
