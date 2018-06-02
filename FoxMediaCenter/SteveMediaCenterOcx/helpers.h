

// helpers.h

#ifndef MY_HELPERS
#define MY_HELPERS

enum EnumFileType {NONE,WMP_VIDEO,REAL_VIDEO,WMP_AUDIO,REAL_AUDIO,QUICKTIME};

enum EnumPlayState {STOPPED,PLAYING,PAUSED,LOADING};


CString ParseXML(CString strTag,CString strParams);
CString ParseXMLArray(CString strTag,CString strParams);
CString ReplaceXML(CString strParam,CString strTag,CString strParams);
EnumFileType GetMediaFileType(CString strFileName);
BOOL SendMessageToInstanseOfApp(CString strMessage);
void LoadWebPage(CString strURL);

	
#endif
