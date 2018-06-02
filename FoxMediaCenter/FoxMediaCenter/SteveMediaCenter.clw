; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSettingsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "SteveMediaCenter.h"
LastPage=0

ClassCount=16
Class1=CSteveMediaCenterApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=13
Resource1=IDD_ABOUTBOX
Resource2=IDD_MY_MESSAGE
Class2=CChildView
Class5=CMyWnd
Resource3=IDR_MAINFRAME
Class6=CTimedShutdownDlg
Resource4=IDD_NEW_ASSOC_FILE_TYPE
Class7=CSettingsDlg
Resource5=IDD_SELECT_SKIN
Class8=CSelectSkinDlg
Resource6=IDD_MANAGE_PLAYLIST
Resource7=IDD_NEW_RANDOM_PLAYLIST
Resource8=IDD_SETTINGS
Class9=CMyButton
Class10=CMyStatic
Class11=CMyListBox
Class12=CMyMp3Player
Resource9=IDD_NEW_PLAYLIST_NAME
Class13=CFileAssociationDlg
Resource10=IDD_FILE_ASSOCIATION
Class14=CNewFileTypeDlg
Resource11=IDR_TRAY_MENU
Resource12=IDD_TIME_SHUTDOWN
Class15=CMyPlayerView
Class16=CMyIEDlgWnd
Resource13=IDD_PROXY_AUTHORIZE (English (Australia))

[CLS:CSteveMediaCenterApp]
Type=0
HeaderFile=SteveMediaCenter.h
ImplementationFile=SteveMediaCenter.cpp
Filter=N

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=SteveMediaCenter.cpp
ImplementationFile=SteveMediaCenter.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NEXT_PANE
Command6=ID_PREV_PANE
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_CUT
Command10=ID_EDIT_UNDO
CommandCount=10

[MNU:IDR_TRAY_MENU]
Type=1
Class=CMainFrame
Command1=ID_FILE_SHOWPLAYLIST
Command2=ID_FILE_HIDEPLAYLIST
Command3=ID_FILE_SETTINGS
Command4=ID_FILE_ACTIVATETIMEDSHUTDOWN
Command5=ID_FILE_SELECTSKIN
Command6=ID_FILE_SELECTPLAYLIST
Command7=ID_FILE_PLAY
Command8=ID_FILE_PAUSE
Command9=ID_FILE_STOP
Command10=ID_FILE_PREVIOUS
Command11=ID_FILE_NEXT
Command12=ID_FILE_EXIT
CommandCount=12

[CLS:CMyWnd]
Type=0
HeaderFile=MyWnd.h
ImplementationFile=MyWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyWnd

[DLG:IDD_TIME_SHUTDOWN]
Type=1
Class=CTimedShutdownDlg
ControlCount=10
Control1=IDC_EDIT_MINUTES,edit,1350631552
Control2=IDC_LOWER_VOLUME,button,1342242819
Control3=IDC_SHUTDOWN_COMPUTER,button,1342242819
Control4=IDOK,button,1342242827
Control5=IDCANCEL,button,1342242827
Control6=IDC_STATIC_TEXT,static,1342308352
Control7=IDC_STATIC4,static,1342308352
Control8=IDC_OR,static,1342308352
Control9=IDC_SHUTDOWN_AFTER_LAST_SONG,button,1342382089
Control10=IDC_TIME_TO_PLAY_CHOICE,button,1342373897

[CLS:CTimedShutdownDlg]
Type=0
HeaderFile=TimedShutdownDlg.h
ImplementationFile=TimedShutdownDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CTimedShutdownDlg

[DLG:IDD_SETTINGS]
Type=1
Class=CSettingsDlg
ControlCount=11
Control1=IDC_AUTO_START_APP,button,1342242819
Control2=IDC_SHOW_PLAYLIST,button,1342242819
Control3=IDC_AUTO_START_LAST_SONG,button,1342242819
Control4=IDC_ENABLE_SHORTCUT_KEYS,button,1342242819
Control5=IDC_PRELOAD_IE_WNDS,button,1342251011
Control6=IDC_HIDE_PLAYER,button,1342251011
Control7=IDC_REPEAT,button,1342242819
Control8=IDC_FILE_ASSOCIATION,button,1342242827
Control9=IDOK,button,1342242827
Control10=IDCANCEL,button,1342242827
Control11=IDC_APPEND_TO_TEMP,button,1073815555

[CLS:CSettingsDlg]
Type=0
HeaderFile=SettingsDlg.h
ImplementationFile=SettingsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_SELECT_SKIN]
Type=1
Class=CSelectSkinDlg
ControlCount=3
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_SELECT_SKIN,combobox,1344340227

[CLS:CSelectSkinDlg]
Type=0
HeaderFile=SelectSkinDlg.h
ImplementationFile=SelectSkinDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CSelectSkinDlg

[DLG:IDD_MANAGE_PLAYLIST]
Type=1
Class=?
ControlCount=9
Control1=IDOK,button,1342242827
Control2=IDCANCEL,button,1342242827
Control3=IDC_NEW_NORMAL_PLAYLIST,button,1342242827
Control4=IDC_NEW_RANDOM,button,1342242827
Control5=IDC_ADD_FILES,button,1342242827
Control6=IDC_DELETE,button,1342242827
Control7=IDC_TREE_PLAYLISTS,SysTreeView32,1350631463
Control8=IDC_PLAY_SELECTED,button,1342242827
Control9=IDC_RENAME_PLAYLIST,button,1342242827

[DLG:IDD_NEW_PLAYLIST_NAME]
Type=1
Class=?
ControlCount=4
Control1=IDC_EDIT1,edit,1350631552
Control2=IDOK,button,1342242827
Control3=IDCANCEL,button,1342242827
Control4=IDC_STATIC_TEXT,static,1342308352

[DLG:IDD_NEW_RANDOM_PLAYLIST]
Type=1
Class=?
ControlCount=20
Control1=IDC_PLAYLIST_NAME,edit,1350631552
Control2=IDC_MAX_FILES,edit,1350631552
Control3=IDC_DIR_PATH,edit,1350631552
Control4=IDC_BROWSE,button,1342242827
Control5=IDC_ADD_DIR_TOLIST,button,1342242827
Control6=IDC_FILE_EXT,edit,1350631552
Control7=IDC_ADD_EXTENTION,button,1342242827
Control8=IDC_MAKE_RANDOM_EACH_TIME,button,1342242819
Control9=IDC_LIST_DIRS,listbox,1352729859
Control10=IDC_LIST_EXTS,listbox,1352729859
Control11=IDOK,button,1342242827
Control12=IDCANCEL,button,1342242827
Control13=IDC_STATIC2,static,1342308352
Control14=IDC_STATIC3,static,1342308352
Control15=IDC_STATIC4,static,1342308352
Control16=IDC_STATIC5,static,1342308352
Control17=IDC_STATIC1,static,1342308352
Control18=IDC_STATIC6,static,1342308352
Control19=IDC_STATIC7,static,1342308352
Control20=IDC_RANDOM_PLAYLIST_HELP,button,1342242827

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_EXIT
CommandCount=1

[CLS:CMyButton]
Type=0
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CMyButton

[CLS:CMyStatic]
Type=0
HeaderFile=MyStatic.h
ImplementationFile=MyStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CMyStatic

[CLS:CMyListBox]
Type=0
HeaderFile=MyListBox.h
ImplementationFile=MyListBox.cpp
BaseClass=CListBox
Filter=W
VirtualFilter=bWC
LastObject=CMyListBox

[CLS:CMyMp3Player]
Type=0
HeaderFile=MyMp3Player.h
ImplementationFile=MyMp3Player.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CMyMp3Player

[DLG:IDD_FILE_ASSOCIATION]
Type=1
Class=CFileAssociationDlg
ControlCount=13
Control1=IDC_LIST1,SysListView32,1350631429
Control2=IDC_NEW_TYPE_BUTTON,button,1342242827
Control3=IDC_REMOVE,button,1342242827
Control4=IDC_MP3,button,1342242818
Control5=IDC_OGG,button,1342242818
Control6=IDC_MPG,button,1342242818
Control7=IDC_DIVX,button,1342242818
Control8=IDC_QUICKTIME,button,1342242818
Control9=IDC_WIN_AUDIO,button,1342242818
Control10=IDC_WIN_VIDEO,button,1342242818
Control11=IDOK,button,1342242827
Control12=IDC_LIST_TEXT,static,1342308352
Control13=IDC_QUICK_TYPE_TEXT,static,1342308352

[CLS:CFileAssociationDlg]
Type=0
HeaderFile=FileAssociationDlg.h
ImplementationFile=FileAssociationDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFileAssociationDlg

[DLG:IDD_NEW_ASSOC_FILE_TYPE]
Type=1
Class=CNewFileTypeDlg
ControlCount=8
Control1=IDC_EDIT1,edit,1350631552
Control2=IDC_AUDIO,button,1342308356
Control3=IDC_VIDEO,button,1342308356
Control4=IDOK,button,1342242827
Control5=IDCANCEL,button,1342242827
Control6=IDC_TEXT1,static,1342308352
Control7=IDC_TEXT3,static,1342308352
Control8=IDC_TEXT2,static,1342308352

[CLS:CNewFileTypeDlg]
Type=0
HeaderFile=NewFileTypeDlg.h
ImplementationFile=NewFileTypeDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_VIDEO

[DLG:IDD_MY_MESSAGE]
Type=1
Class=?
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_MSG,static,1342308352

[DLG:IDD_PROXY_AUTHORIZE (English (Australia))]
Type=1
Class=?
ControlCount=10
Control1=IDC_USERNAME,edit,1350631552
Control2=IDC_PASSWORD,edit,1350631584
Control3=IDC_PASSWORD2,edit,1350631584
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,button,1342177287

[CLS:CMyPlayerView]
Type=0
HeaderFile=MyPlayerView.h
ImplementationFile=MyPlayerView.cpp
BaseClass=CHtmlView
Filter=C
LastObject=CMyPlayerView

[CLS:CMyIEDlgWnd]
Type=0
HeaderFile=MyIEDlgWnd.h
ImplementationFile=MyIEDlgWnd.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMyIEDlgWnd

