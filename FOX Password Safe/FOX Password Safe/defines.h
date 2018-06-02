
#define MY_APP_TITLE		"FOX Password Safe"

#define REG_ENCRYPT_KEY		"nrtKn4gr47rpx5Z9yz6TtL3E4069t2sH"

#define APP_CLASS_NAME		"FOX_APP_7D1703B5-31B1-4746-9385-6105ECAFEEBC"

#define VERSION				"2.1"

#define	WM_STARTUP						(WM_USER + 1)	
#define	WM_TRAY_NOTIFICATION_MSG		(WM_USER + 2)
#define	WM_CHECK_ASK_PASSWORD			(WM_USER + 3)
#define WM_LOAD_URL						(WM_USER + 4)
#define WM_ENDDLG_OK					(WM_USER + 5)
#define WM_ENDDLG_CANCEL				(WM_USER + 6)

#define	ID_TIMER_UPDATE					10
#define ID_UNLOCK_BROWSER				11
#define ID_CLEAR_PASSWORD				12
#define ID_CHECK_SCREEN_SAVER_ACTIVE	13

#define	ONLINE_HELP_PAGE			"http://www.stevefoxover.com/FoxPasswordSafe/help.aspx"
//#define	ONLINE_REGISTRATION_PAGE	"http://www.stevefoxover.com/FoxPasswordSafe/register.aspx"
#define	ONLINE_REGISTRATION_PAGE	"http://store.eSellerate.net/s.aspx?s=STR5020735789" 

#define CUSTOM_PRINT_ARRAY_COLUMN_SIZE		6

typedef struct C2DStringTag
{
	CString straCol[CUSTOM_PRINT_ARRAY_COLUMN_SIZE];
} C2DString;

#define MAX_POPUP_MENUS		200
#define DEFAULT_AUTO_UNLOCK_BROWSER_SECS	120

// detect if screen saver is running 98+, not NT 4
#define SPI_GETSCREENSAVERRUNNING		0x0072
#define SCREEN_SAVER_CHECK_TIME			1000*60

#define ICON_SPACE_X					10

enum TOOLBAR_TYPES { TOOLBAR_CREDIT_CARD, TOOLBAR_ENCRYPTED_FILE, TOOLBAR_USERNAME_PASSWORD };

