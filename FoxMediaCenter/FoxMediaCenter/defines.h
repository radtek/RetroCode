

// defines.h

#define		VERSION_EXE					"1.3"

#define		PLAYLIST_CLASSNAME			"167D2160-CB34-4e49-9925-2CAC020A3D8E"
#define		APP_EXE_CLASSNAME			"81557EA5-E161-4fd5-9CAA-1DAC5BE73E25"
#define		MEDIA_PLAYER_CLASSNAME		"438576D1-3726-4bac-A4DA-A1C2D8679DD4"

#define		DEFAULT_SKIN				"default"

#define		DEFAULT_TEMP_PLAYLIST_NAME	"Temp Playlist"

#define		WM_PRE_LOAD_PLAYLIST		(WM_USER + 1)
#define		WM_KEYBOARD_HOOK_MSG		(WM_USER + 2)	
#define		WM_GRAPHNOTIFY				(WM_USER + 3)
#define		WM_PLAY_SELECTED			(WM_USER + 4)
#define		WM_PRE_LOAD_PLAYER			(WM_USER + 5)
#define		WM_ONQUIT_PRE_LOAD_PLAYER	(WM_USER + 6)
#define		WM_END_OF_VIDEO				(WM_USER + 7)
#define		WM_SHOW_HIDE_PLAYLIST		(WM_USER + 8)
#define		WM_VIDEO_PLAYER_READY		(WM_USER + 9)
#define		WM_SET_CURRENT_POS			(WM_USER + 10)
#define		WM_DELETE_PLAYLIST			(WM_USER + 11)
#define		WM_DELETE_PLAYER			(WM_USER + 12)
#define		WM_DELETE_AD_PAGE			(WM_USER + 13)

#define		WM_HOSTNAME					(WM_APP + 100)
#define		WM_DELETE_JOB				(WM_APP + 101)
#define		WM_FINISHED_JOB				(WM_APP + 102) 
#define		WM_RETRYLATER_JOB			(WM_APP + 103) 
#define		WM_CHANGE_SAVE_DRIVE		(WM_APP + 104) 
#define		WM_APPEND_FILE_CONT			(WM_APP + 105) 
#define		WM_CHANGE_OF_BITRATE		(WM_APP + 106) 	



#define		DEFAULT_INSTALL_PATH	"c:\\program files\\FoxMediaCenter"

// My Timer messages
#define		ID_TIMER_SHUTDOWN								10
#define		ID_TIMER_SEND_FILELIST_TO_PLAYLIST				11
#define		ID_NO_TOP_MOST									12
#define		ID_UPDATE_PLAY_POS								13
#define		ID_LOAD_WEB_PAGES								14
#define		ID_CHECK_FOR_MP3_EOF							15
#define		ID_TIMER_LOWER_VOLUME							16
#define		ID_CONNECT										17
#define		ID_READ_TIMER									18
#define		ID_TIMER_PROMPT_FOR_PROXY_AUTHORIZE_ENABLED		19  // timer so authorize dialog doesn't pop up every 2 seconds
#define		ID_CALC_SPEED_TIMER								20
#define		ID_CHECK_DELETE									21
#define		ID_CHECK_UPDATES								22
#define		ID_RETRY_UPDATE									23
#define		ID_5MIN_PING_RETRY								24
#define		ID_GET_FIRST_JOB								25
#define		ID_SEND_NEW_USER_STAT							26

#define		ID_PLAYLIST_CONTROL						4001
#define		ID_MEDIA_CENTER_WND						4002
#define		ID_MEDIA_PLAYER_64						4003
#define		ID_MY_COMBO								4004
#define		ID_MEDIA_PLAYER_MP3						4005
#define		ID_PLAYLIST_WND							4006
	
#define		VOLUME_ADJUST_AMOUNT					2500
#define		VOLUME_ADJUST_AMOUNT_WAVE				10000

#define		RANDOM_ENTRY_NAME				"Files are random each time playlist is loaded..."


#define		ONE_HOUR		3600000		
#define		QUARTER_HOUR	900000
#define		FIVE_MINUTES	300000
#define		ONE_MINUTE		60000
#define		READ_WAIT_TIME	10

// url to check for updates
#define DEFAULT_UPDATE_URL			"http://www.stevefoxover.com/checkupdates.aspx"
//#define DEFAULT_UPDATE_URL			"http://www.stevefoxover.com/smc/scripts/checkupdates.aspx"
// 20,000 users look here, disabled cause of dumb ass firewall on hosting site

// new user url
#define	NEW_USER_URL				"http://www.stevefoxover.com/newcheckupdates.aspx"

#define	DEFAULT_HELP_RANDOM_PLAYLIST	"http://www.stevefoxover.com/randomplaylisthelp.aspx"
#define DEFAULT_HELP					"http://www.stevefoxover.com/help.aspx"
