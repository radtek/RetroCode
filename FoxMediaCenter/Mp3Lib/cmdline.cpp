/* cmdline.cpp

   Command line version of maplay written by John Fehr

   Fixes for HP-UX by Earle F Philhower <earle@geocities.com>

   This can be used for unix systems as well as the Win32 console. */

#ifndef __DATE__
#define __DATE__  Jul 07, 1997
#endif // __DATE__

#ifndef __TIME__
#define __TIME__   12:00:00
#endif // __TIME__

#ifdef __WIN32__
#include <windows.h>
#endif // __WIN32__

#include <stdio.h>
#include <string.h>
#include <iostream.h>
#include <process.h>

#include "all.h"
#include "crc.h"
#include "args.h"

#ifdef IRIX
#define MAPLAY_VERSION "SGI IRIX"
#define MAPLAY_PORTER  "Andres Meyer (ameyer@desun1.epfl.ch)"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#ifdef SunOS4_1_1
#define MAPLAY_VERSION "SPARC SunOS 4.1.1"
#define MAPLAY_PORTER  "Anonymous SPARC SunOS 4.1.1 Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef SunOS4_1_3
#define MAPLAY_VERSION "SPARC SunOS 4.1.3"
#define MAPLAY_PORTER  "Anonymous SPARC SunOS 4.1.3 Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef Solaris
#define MAPLAY_VERSION "SPARC Solaris 2.x"
#define MAPLAY_PORTER  "Anonymous SPARC Solaris 2.x Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef LINUX
#ifdef PENTIUM
#define MAPLAY_VERSION "Linux, Pentium CPU"
#else
#define MAPLAY_VERSION "Linux, 486 CPU"
#endif // PENTIUM
#define MAPLAY_PORTER  "Anonymous Linux Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef __FreeBSD__
#ifdef PENTIUM
#define MAPLAY_VERSION "FreeBSD, Pentium CPU"
#else
#define MAPLAY_VERSION "FreeBSD, 486 CPU"
#endif // PENTIUM
#define MAPLAY_PORTER  "Jeff Tsay"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#ifdef ULTRIX
#define MAPLAY_VERSION "RISC ULTRIX 4.x"
#define MAPLAY_PORTER  "Anonymous ULTRIX Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef HPUX
#define MAPLAY_VERSION "HP-UX 9.05 or greater"
#define MAPLAY_PORTER  "Earle Philhower (earle@geocities.com)"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#ifdef AIX
#define MAPLAY_VERSION "AIX"
#define MAPLAY_PORTER  "Anonymous AIX Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef NeXT
#define MAPLAY_VERSION "NeXTStep 3.2"
#define MAPLAY_PORTER  "Anonymous NeXTStep 3.2 Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#else
#ifdef __WIN32__
#ifdef PENTIUM
#define MAPLAY_VERSION "Win32 Console, Pentium CPU"
#else
#define MAPLAY_VERSION "Win32 Console, 486 CPU"
#endif // PENTIUM
#define MAPLAY_PORTER  "Jeff Tsay"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#ifdef BEOS
#define MAPLAY_VERSION "BeOS DR8.2/DR8.3"
#define MAPLAY_PORTER  "Thomas Philippe (tphilippe@sdv.fr)"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#ifdef __DOS__
#ifdef PENTIUM
#define MAPLAY_VERSION "DOS, Pentium CPU"
#else
#define MAPLAY_VERSION "DOS, 486 CPU"
#endif // PENTIUM
#define MAPLAY_PORTER  "Jochen Wilhelmy (digisnap@cs.tu-berlin.de)"
#define MAPLAY_PORT_VERSION_NUMBER "1.1"
#else
#define MAPLAY_VERSION "unknown"
#define MAPLAY_PORTER  "Anonymous Porter"
#define MAPLAY_PORT_VERSION_NUMBER "1.0"
#endif  // __DOS__
#endif  // BEOS
#endif  // _WIN32__
#endif  // NeXT
#endif  // AIX
#endif  // HPUX
#endif  // ULTRIX
#endif  // __FreeBSD__
#endif  // LINUX
#endif  // Solaris
#endif  // SunOS4_1_3
#endif  // SunOS4_1_1
#endif  // IRIX

#ifdef __WIN32__
HWAVEOUT hwo;
#endif // __WIN32__

bool verbose_mode = false;
char filename[512] = "";

uint32 maplay(MPEG_Args *);

int ProcessArgs(int32 argc, char *argv[], MPEG_Args *ma)
{

  Crc16 *crc = NULL;
  int i;

  ma->stdout_mode  = false;
  ma->verbose_mode = false;

#ifdef __WIN32__
  ma->phwo 			= &hwo;
  ma->output_mode = O_WAVEMAPPER;
  lstrcpy(ma->output_filename, "");
#endif

   ma->stream = new Ibitstream(filename);		// read from file

  ma->MPEGheader = new Header;
  if (!ma->MPEGheader->read_header(ma->stream, &crc)) {
    cerr << endl <<  "Error : no header found!" << endl;
    return 0;
  }
  return 1;
}

int maplay_setup(MPEG_Args *ma)
{
#ifdef VERBOSE
  if (verbose_mode)
  {
    // print information about the stream
    char *name = strrchr (filename, DIR_MARKER);
    if (name)
      ++name;
    else
      name = filename;
    cerr << name << " is a layer " << ma->MPEGheader->layer_string () << " "
	 << ma->MPEGheader->mode_string() << " "
    << ma->MPEGheader->version_string() << " audio stream with";
    if (!ma->MPEGheader->checksums())
      cerr << "out";
    cerr << " checksums.\nThe sample frequency is "
	 << ma->MPEGheader->sample_frequency_string () << " at a bitrate of "
	 << ma->MPEGheader->bitrate_string() << ".\n"
	    "This stream is ";
    if (ma->MPEGheader->original())
      cerr << "an original";
    else
      cerr << "a copy";
    cerr << " and is ";
    if (!ma->MPEGheader->copyright())
      cerr << "not ";
    cerr << "copyright protected.\n";
  }
#endif
  return 1;
}

//int main(int argc,char *argv[])
//{
//   MPEG_Args ma;
//   if (!ProcessArgs(argc,argv,&ma)) return 0;
//   maplay_setup(&ma);
//   maplay(&ma);
//   return 0;
//}

__declspec(dllexport) bool PlayFile(const char* szFileName)
{
	MPEG_Args ma;
	char* szFakeCmd[2]; 
	strcpy(filename,szFileName);
//	if (!ProcessArgs(argc,argv,&ma)) return 0;
	if (!ProcessArgs(2,szFakeCmd,&ma)) return false;
	maplay_setup(&ma);
	maplay(&ma);
	return true;
}

/*int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int cmdShow)
{
	MPEG_Args ma;
	char* szFakeCmd[2]; 
	strcpy(filename,"test.mp3");
//	if (!ProcessArgs(argc,argv,&ma)) return 0;
	if (!ProcessArgs(2,szFakeCmd,&ma)) return 0;
	maplay_setup(&ma);
	maplay(&ma);
	return 0;

//	MSG msg;	// Get and dispatch messages for this applicaton.
//	while (GetMessage(&msg, NULL, 0, 0)) {
//		TranslateMessage(&msg);
//		DispatchMessage(&msg); }
//	return msg.wParam;
} */

