// CQuickTime.h : interface of the CQuickTime class
//
/////////////////////////////////////////////////////////////////////////////

#include <Movies.h>
#include <scrap.h>

#include <windows.h>	// Microsoft Windows
#include <winuser.h>

#ifndef __CQUICKTIME__
#define __CQUICKTIME__

#ifdef __cplusplus
extern "C" {
#endif
Boolean MCFilter(MovieController mc, short action, void*params, long refCon);
#ifdef __cplusplus
}
#endif

#define MINWINDOWWIDTH		320

class CQuickTime
{

public:
	CQuickTime();
	~CQuickTime();

	virtual BOOL	OpenMovie(unsigned char *fullPath);
	virtual void	CloseMovie(void);
	virtual void	ProcessMovieEvent(HWND hWnd, unsigned int message, unsigned int wParam, long lParam); 
	virtual int		OnMovieWindowCreate(HWND hWnd, CREATESTRUCT *lpCreateStruct); 
	virtual void	OnMovieWindowDestroy();
	virtual void	CreateNewMovieController(Movie theMovie);

	virtual void	GetFileNameFromFullPath(unsigned char *fileName); 
	virtual void	GetAppName(unsigned char *appName); 

	virtual void	CToPstr(char *theString);
	virtual void	PToCstr(char *theString);

	virtual void	GetMaxBounds(Rect *maxRect);

	virtual Movie	GetMovie(void);

public:
	CRect m_rectSize;
	unsigned char	theAppName[128];
	HWND			theHwnd;
	HWND			theViewHwnd;
    MovieController theMC;
private: 
	BOOL			movieOpened;
	Movie			theMovie;
	Rect			theMovieRect;
	Rect			theMCRect;
	unsigned char	theFullPath[255];


// Operations

};

#endif
