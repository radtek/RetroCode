/* unix_file_obuffer.h

   Output buffer for unix filesystems written by Tobias Bading
   (bading@cs.tu-berlin.edu)

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#ifndef UNIX_FILE_OBUFFER_H
#define UNIX_FILE_OBUFFER_H

#include "obuffer.h"

// An audio output class for raw pcm output
// or if ULAW is defined:
// An audio output class for 8-bit ulaw output at 8 kHz:
class FileObuffer : public Obuffer
{
private:
#ifdef ULAW
  ulawsample buffer[OBUFFERSIZE];
  ulawsample *bufferp[MAXCHANNELS];
#else
  int16 buffer[OBUFFERSIZE];
  int16 *bufferp[MAXCHANNELS];
#endif
  uint32 channels;

public:
	FileObuffer (uint32 number_of_channels);
       ~FileObuffer (void) {}
  void	append (uint32 channel, int16 value);
  void	write_buffer (int fd);

#ifdef SEEK_STOP
  void clear_buffer(void);
  void set_stop_flag(void);
#endif

};

Obuffer *create_stdout_obuffer(MPEG_Args *maplay_args);

#endif // UNIX_FILE_OBUFFER_H
