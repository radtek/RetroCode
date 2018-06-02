; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMyRealAudioCom
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SteveMediaPlayer.h"
CDK=Y

ClassCount=7
Class1=CSteveMediaPlayerCtrl
Class2=CSteveMediaPlayerPropPage

ResourceCount=1
LastPage=0
Class3=CSeekWnd
Class4=CMySeekSliderWnd
Class5=CFullScreenWnd
Class6=CMyQuickTimeWnd
Class7=CMyRealAudioCom
Resource1=IDD_PROPPAGE_STEVEMEDIAPLAYER

[CLS:CSteveMediaPlayerCtrl]
Type=0
HeaderFile=SteveMediaPlayerCtl.h
ImplementationFile=SteveMediaPlayerCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CSteveMediaPlayerCtrl

[CLS:CSteveMediaPlayerPropPage]
Type=0
HeaderFile=SteveMediaPlayerPpg.h
ImplementationFile=SteveMediaPlayerPpg.cpp
Filter=D

[DLG:IDD_PROPPAGE_STEVEMEDIAPLAYER]
Type=1
Class=CSteveMediaPlayerPropPage
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CSeekWnd]
Type=0
HeaderFile=SeekWnd.h
ImplementationFile=SeekWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CSeekWnd

[CLS:CMySeekSliderWnd]
Type=0
HeaderFile=MySeekSliderWnd.h
ImplementationFile=MySeekSliderWnd.cpp
BaseClass=generic CWnd
Filter=W

[CLS:CFullScreenWnd]
Type=0
HeaderFile=FullScreenWnd.h
ImplementationFile=FullScreenWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CFullScreenWnd

[CLS:CMyQuickTimeWnd]
Type=0
HeaderFile=MyQuickTimeWnd.h
ImplementationFile=MyQuickTimeWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyQuickTimeWnd

[CLS:CMyRealAudioCom]
Type=0
HeaderFile=MyRealAudioCom.h
ImplementationFile=MyRealAudioCom.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyRealAudioCom

