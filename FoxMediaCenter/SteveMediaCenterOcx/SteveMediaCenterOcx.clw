; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVolumeWnd
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SteveMediaCenterOcx.h"
CDK=Y

ClassCount=15
Class1=CSteveMediaCenterOcxCtrl
Class2=CSteveMediaCenterOcxPropPage

ResourceCount=7
LastPage=0
Class3=CMyListCtrl
Class4=CMyMediaPlayer
Class5=CMyDirectXPlayer
Class6=CDropFilesWnd
Class7=CMyComboPlayList
Resource1=IDD_SELECT_SKIN
Class8=CManagePlayListDlg
Class9=CMyTreeCtrl
Resource2=IDD_NEW_RANDOM_PLAYLIST
Class10=CNewRandomPlaylistDlg
Resource3=IDD_MANAGE_PLAYLIST
Class11=CNewPlayListNameDlg
Resource4=IDD_NEW_PLAYLIST_NAME
Class12=CSelectSkinDlg
Resource5=IDD_VOLUME_DLG
Resource6=IDD_PROPPAGE_STEVEMEDIACENTEROCX
Class13=CVolWaveDlg
Class14=CMySliderCtrl
Class15=CVolumeWnd
Resource7=IDR_POPUP_MENU

[CLS:CSteveMediaCenterOcxCtrl]
Type=0
HeaderFile=SteveMediaCenterOcxCtl.h
ImplementationFile=SteveMediaCenterOcxCtl.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CSteveMediaCenterOcxCtrl

[CLS:CSteveMediaCenterOcxPropPage]
Type=0
HeaderFile=SteveMediaCenterOcxPpg.h
ImplementationFile=SteveMediaCenterOcxPpg.cpp
Filter=D

[DLG:IDD_PROPPAGE_STEVEMEDIACENTEROCX]
Type=1
Class=CSteveMediaCenterOcxPropPage
ControlCount=0

[CLS:CMyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CMyListCtrl

[CLS:CMyMediaPlayer]
Type=0
HeaderFile=MyMediaPlayer.h
ImplementationFile=MyMediaPlayer.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyMediaPlayer

[CLS:CMyDirectXPlayer]
Type=0
HeaderFile=MyDirectXPlayer.h
ImplementationFile=MyDirectXPlayer.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyDirectXPlayer

[CLS:CDropFilesWnd]
Type=0
HeaderFile=DropFilesWnd.h
ImplementationFile=DropFilesWnd.cpp
BaseClass=generic CWnd
Filter=W

[CLS:CMyComboPlayList]
Type=0
HeaderFile=MyComboPlayList.h
ImplementationFile=MyComboPlayList.cpp
BaseClass=CComboBox
Filter=W
VirtualFilter=cWC
LastObject=CMyComboPlayList

[DLG:IDD_MANAGE_PLAYLIST]
Type=1
Class=CManagePlayListDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NEW_NORMAL_PLAYLIST,button,1342242816
Control4=IDC_NEW_RANDOM,button,1342242816
Control5=IDC_ADD_FILES,button,1342242816
Control6=IDC_DELETE,button,1342242816
Control7=IDC_TREE_PLAYLISTS,SysTreeView32,1350631463
Control8=IDC_PLAY_SELECTED,button,1342242816

[CLS:CManagePlayListDlg]
Type=0
HeaderFile=ManagePlayListDlg.h
ImplementationFile=ManagePlayListDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CManagePlayListDlg

[CLS:CMyTreeCtrl]
Type=0
HeaderFile=MyTreeCtrl.h
ImplementationFile=MyTreeCtrl.cpp
BaseClass=CTreeCtrl
Filter=W
VirtualFilter=GWC
LastObject=CMyTreeCtrl

[DLG:IDD_NEW_RANDOM_PLAYLIST]
Type=1
Class=CNewRandomPlaylistDlg
ControlCount=20
Control1=IDC_PLAYLIST_NAME,edit,1350631552
Control2=IDC_MAX_FILES,edit,1350631552
Control3=IDC_DIR_PATH,edit,1350631552
Control4=IDC_BROWSE,button,1342242816
Control5=IDC_ADD_DIR_TOLIST,button,1342242816
Control6=IDC_FILE_EXT,edit,1350631552
Control7=IDC_ADD_EXTENTION,button,1342242816
Control8=IDC_MAKE_RANDOM_EACH_TIME,button,1342242819
Control9=IDC_LIST_DIRS,listbox,1352728835
Control10=IDC_LIST_EXTS,listbox,1352728835
Control11=IDOK,button,1342242817
Control12=IDCANCEL,button,1342242816
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_RANDOM_PLAYLIST_HELP,button,1342242816

[CLS:CNewRandomPlaylistDlg]
Type=0
HeaderFile=NewRandomPlaylistDlg.h
ImplementationFile=NewRandomPlaylistDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_RANDOM_PLAYLIST_HELP

[DLG:IDD_NEW_PLAYLIST_NAME]
Type=1
Class=CNewPlayListNameDlg
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CNewPlayListNameDlg]
Type=0
HeaderFile=NewPlayListNameDlg.h
ImplementationFile=NewPlayListNameDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_SELECT_SKIN]
Type=1
Class=CSelectSkinDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SELECT_SKIN,combobox,1344340226

[CLS:CSelectSkinDlg]
Type=0
HeaderFile=SelectSkinDlg.h
ImplementationFile=SelectSkinDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[MNU:IDR_POPUP_MENU]
Type=1
Class=CSteveMediaCenterOcxCtrl
Command1=ID_FILE_SETTINGS
Command2=ID_FILE_ACTIVETIMEDSHUTDOWN
Command3=ID_FILE_SELECTSKIN
Command4=ID_FILE_SELECTPLAYLIST
CommandCount=4

[DLG:IDD_VOLUME_DLG]
Type=1
Class=CVolWaveDlg
ControlCount=4
Control1=IDC_VOLUME,msctls_trackbar32,1342242842
Control2=IDC_WAVE,msctls_trackbar32,1342242842
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352

[CLS:CVolWaveDlg]
Type=0
HeaderFile=VolWaveDlg.h
ImplementationFile=VolWaveDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_VOLUME

[CLS:CMySliderCtrl]
Type=0
HeaderFile=MySliderCtrl.h
ImplementationFile=MySliderCtrl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=KWC
LastObject=CMySliderCtrl

[CLS:CVolumeWnd]
Type=0
HeaderFile=VolumeWnd.h
ImplementationFile=VolumeWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CVolumeWnd

