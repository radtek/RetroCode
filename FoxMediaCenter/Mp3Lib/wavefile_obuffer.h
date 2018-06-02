/* wavefile_obuffer.h

	Output buffer declarations for writing to a PCM wave file
   in Win32, written by Jeff Tsay (ctsay@pasteur.eecs.berkeley.edu). */

#ifndef WAVEFILE_OBUFFER_H
#define WAVEFILE_OBUFFER_H

#ifdef  __WIN32__
#define STRICT
#include <windows.h>

#include "all.h"
#include "header.h"
#include "args.h"
#include "obuffer.h"

class Wavefile_Obuffer : public Obuffer
{
private:

  uint32 bufferp[MAXCHANNELS];
  uint32 channels;
  uint32 data_size;

  BYTE *temp;

  HMMIO    hmmioOut;
  MMIOINFO mmioinfoOut;
  MMCKINFO ckOutRIFF;
  MMCKINFO ckOut;

public:
	Wavefile_Obuffer(uint32 number_of_channels, MPEG_Args *maplay_args);
	~Wavefile_Obuffer();

  void	append(uint32 channel, int16 value);
  void	write_buffer(int32 fd);

#ifdef SEEK_STOP
  void   clear_buffer();
  void   set_stop_flag();
#endif

};

Obuffer *create_Wavefile_obuffer(MPEG_Args *maplay_args);

#endif // __WIN32__
#endif // WAVEFILE_OBUFFER_H
