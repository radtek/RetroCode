

// defines.h

#define		VERSION						"1.3"
#define		TB_HEIGHT					22
#define		PLAY_BUTTON					0

#define		DEFAULT_REGISTRATION_URL	"http://store.eSellerate.net/s.aspx?s=STR5020735789" 

// application variables
#define		MY_APP_NAME					"ReadToMe"
#define		MY_REGISTRY_PATH			"SOFTWARE\\STEVEFOXOVER\\ReadToMe\\Settings"
#define		APP_FILE					"ipi.prn"

#define SAFERELEASE(o) if(o){o->Release();o=NULL;}

#define HTML_PRE_CHAR_TEST		3
#define HTML_POST_CHAR_TEST		20

// custom messages
#define WM_TTSAPPCUSTOMEVENT		(WM_APP + 10)   // Window message used for systhesis events
#define MY_EM_SETSEL				(WM_APP + 11)	// custom message for set selected text
#define MY_WM_PLAY_FROM_POS			(WM_APP + 12)	// play from this position
#define	WM_RECALC_SCROLL_SIZE		(WM_APP + 13)	// recalc scroll size
#define MY_EM_END_OF_STREAM			(WM_APP + 14)	// end of text stream
#define MY_MSG_DOUBLE_CLICK			(WM_APP + 15)	// double click on html page
#define MY_MSG_STOP_SPEAKING		(WM_APP + 16)	// stop speaking

// timers
#define	ID_RESUME_AUTOSCROLL		10
#define ID_RESUME_PLAY_FROM_POS		11
#define	ID_NAG						12


#define		ENCRYPT_KEY			"43FF617AD3984e9fB6685DB152A9C3E!"
								
	
