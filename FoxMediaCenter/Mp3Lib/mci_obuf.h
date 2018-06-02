/* mci_obuf.h

   Obuffer implementation for Win32. Written by Jeff Tsay. */

#ifndef MCI_OBUF_H
#define MCI_OBUF_H

#ifdef  __WIN32__
#define STRICT
#include <windows.h>

#include "all.h"
#include "header.h"
#include "args.h"
#include "obuffer.h"

#define TWO_TIMES   5
static const uint32 BUFFERSIZE = OBUFFERSIZE << TWO_TIMES;
#define BIT_SELECT  0x1f

#define SLEEPTIME   256

// MCIbuffer class written by Jeff Tsay

class MCIbuffer : public Obuffer
{
public:
	MCIbuffer(uint32 number_of_channels, MPEG_Args *maplay_args);
	~MCIbuffer();

  void	append(uint32 channel, int16 value);
  void	write_buffer(int32 fd);

#ifdef SEEK_STOP
  void   clear_buffer();
  void   set_stop_flag();
#endif

private:
  uint32 bufferp[MAXCHANNELS];
  uint32 channels;
  tWAVEFORMATEX *lpwf;
  LPWAVEHDR* lpwavehdr_arr;
  HWAVEOUT *phwo;
  uint32 buffer_count;
  uint32 hdr_size;
  uint32 fillup;
  DWORD data_size;
  uint32 user_stop;

  void   wave_swap();
};

#endif // __WIN32__
#endif // MCI_OBUFFER_H
