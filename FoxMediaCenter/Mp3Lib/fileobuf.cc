/* file_obuffer.cc

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <fcntl.h>

#ifndef __WIN32__
#include <unistd.h>	
#include <sys/ioctl.h>
#else
#include <io.h>
#endif

#include <iostream.h>

#include "obuffer.h"
#include "header.h"
#ifdef ULAW
#include "ulaw.h"
#endif

FileObuffer::FileObuffer (uint32 number_of_channels)
{
#ifdef DEBUG
  if (!number_of_channels || number_of_channels > MAXCHANNELS)
  {
    cerr << "FileObuffer: number of channels has to be in [1, " <<  MAXCHANNELS << "] !\n";
    exit (1);
  }
#endif

#ifdef ULAW
  if (number_of_channels > 1)
    cerr << "Are you sure you need stereo u-law output?\n";
#endif
  channels = number_of_channels;
  for (uint32 i = 0; i < number_of_channels; ++i)
    bufferp[i] = buffer + i;
}


void FileObuffer::append (uint32 channel, int16 value)
{
#ifdef DEBUG
  if (channel >= channels)
  {
    cerr << "illegal channelnumber in FileObuffer::append()!\n";
    exit (1);
  }
  if (bufferp[channel] - buffer >= OBUFFERSIZE)
  {
    cerr << "FileObuffer: buffer overflow!\n";
    exit (1);
  }
#endif

#ifdef ULAW
  // convert 16-bit PCM sample to 8-bit ulaw:
  *bufferp[channel] = linear2ulaw[value >> 3];
#else
  *bufferp[channel] = value;
#endif
  bufferp[channel] += channels;
}

#ifdef SEEK_STOP
void FileObuffer::clear_buffer(void)
{
}

void FileObuffer::set_stop_flag(void)
{
}
#endif // SEEK_STOP

void FileObuffer::write_buffer (int fd)
{
  int length = (int)((char *)bufferp[0] - (char *)buffer), writelength;

  if ((writelength = write (fd, (char *)buffer, length)) != length)
  {
    // buffer has not been written completely
    if (writelength < 0)
    {
      perror ("write");
      exit (1);
    }
    length -= writelength;
    char *buffer_pos = (char *)buffer;
    do
    {
      buffer_pos += writelength;
      if ((writelength = write (fd, buffer_pos, length)) < 0)
      {
	perror ("write");
	exit (1);
      }
    }
    while (length -= writelength);
  }

  for (unsigned int i = 0; i < channels; ++i)
    bufferp[i] = buffer + i;
}

Obuffer *create_stdout_obuffer(MPEG_Args *maplay_args)
{
	Obuffer *buffer;

	enum e_mode mode = maplay_args->MPEGheader->mode();
   enum e_channels which_channels = maplay_args->which_c;

   if (mode == single_channel || which_channels != both)
      buffer = new FileObuffer (1);
   else
      buffer = new FileObuffer (2);

   return(buffer);
}

