/* wavefile_obuffer.cpp

	Output buffer class for writing to a PCM wave file
   in Win32, written by Jeff Tsay (ctsay@pasteur.eecs.berkeley.edu).

   Based on the lowpass filter example by Microsoft.

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

#ifdef  __WIN32__
#include <windows.h>

#ifndef WIN32GUI
#include <iostream.h>
#endif

#include "header.h"
#include "args.h"
#include "obuffer.h"
#include "wavefile_obuffer.h"

Wavefile_Obuffer::Wavefile_Obuffer(uint32 number_of_channels,MPEG_Args *maplay_args)
{
  channels  = number_of_channels;
  data_size = channels * OBUFFERSIZE;

  if (maplay_args->MPEGheader->version() == MPEG2_LSF)
     data_size >>= 1;

  if (maplay_args->MPEGheader->layer() == 1)
  	  data_size /= 3;

  temp = new BYTE[data_size];

  hmmioOut = mmioOpen(maplay_args->output_filename, NULL,
                      MMIO_ALLOCBUF | MMIO_WRITE | MMIO_CREATE);

  if (!hmmioOut) {

#ifdef WIN32GUI
	  MessageBox(NULL, "Could not open file.", "Wave file output error",
                MB_OK | MB_ICONEXCLAMATION);
#else
	  cerr << "could not open file : " << maplay_args->output_filename
          << endl;
#endif

	  ExitProcess(1);
  }

  // Create the output file RIFF chunk of form type WAVE.

  ckOutRIFF.fccType = mmioFOURCC('W', 'A', 'V', 'E');
  ckOutRIFF.cksize  = 0;
  if (mmioCreateChunk(hmmioOut, &ckOutRIFF, MMIO_CREATERIFF)
  		!= MMSYSERR_NOERROR) {

#ifdef WIN32GUI
	  MessageBox(NULL, "Could not write file.", "Wave file output error",
                MB_OK | MB_ICONEXCLAMATION);
#else
	  cerr << "could not write file : " << maplay_args->output_filename
	   	 << endl;
#endif

	  ExitProcess(1);
  }

  // Initialize the WAVEFORMATEX structure

  WAVEFORMATEX pwf;

  pwf.wBitsPerSample  = 16;  // No 8-bit support yet
  pwf.wFormatTag      = WAVE_FORMAT_PCM;
  pwf.nChannels       = (WORD) channels;
  pwf.nSamplesPerSec  = (DWORD) maplay_args->MPEGheader->frequency();
  pwf.nAvgBytesPerSec = (DWORD) (channels *
								maplay_args->MPEGheader->frequency() << 1);
  pwf.nBlockAlign     = (WORD) (channels << 1);
  pwf.cbSize          = 0;

  // Create the fmt chunk

  ckOut.ckid = mmioFOURCC('f', 'm', 't', ' ');
  ckOut.cksize = sizeof(pwf);

  if (mmioCreateChunk(hmmioOut, &ckOut, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
		MessageBox(NULL, "Could not write file!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
	 cerr << "could not write file : " << maplay_args->output_filename
		  << endl;
#endif

	 ExitProcess(1);
  }

  // Write the WAVEFORMATEX structure to the fmt chunk.

  if (mmioWrite(hmmioOut, (HPSTR) &pwf, sizeof(pwf))
      != sizeof(pwf)) {

#ifdef WIN32GUI
	  MessageBox(NULL, "Could not write file!", "Wave file output error",
                MB_OK | MB_ICONEXCLAMATION);
#else
	  cerr << "could not write file : " << maplay_args->output_filename
	   	 << endl;
#endif

	  ExitProcess(1);
  }

  // Ascend out of the fmt chunk, back into the RIFF chunk.

  if (mmioAscend(hmmioOut, &ckOut, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
	  MessageBox(NULL, "Could not write file!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
     cerr << "could not write file : " << maplay_args->output_filename
          << endl;
#endif

	  ExitProcess(1);
  }

  // Create the data chunk that holds the waveform samples.

  ckOut.ckid   = mmioFOURCC('d', 'a', 't', 'a');
  ckOut.cksize = 0;
  if (mmioCreateChunk(hmmioOut, &ckOut, 0) != MMSYSERR_NOERROR)   {

#ifdef WIN32GUI
		MessageBox(NULL, "mmioSetInfo() failed!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
	 cerr << "could not write file : " << maplay_args->output_filename
		  << endl;
#endif

	 ExitProcess(1);
  }

  mmioGetInfo(hmmioOut, &mmioinfoOut, 0);

  int i;
  for(i=0; i<channels; i++)
	   bufferp[i] = i * channels;
}

void Wavefile_Obuffer::append (uint32 channel, int16 value)
{
  // Need to break up the 32-bit integer into 2 8-bit bytes.
  // (ignore the first two bytes - either 0x0000 or 0xffff)
  // Note that Intel byte order is backwards!!!

  temp[bufferp[channel]]   = (BYTE) (value & 0xff);
  temp[bufferp[channel]+1] = (BYTE) (value >> 8);

  bufferp[channel] += channels << 1;

  return;
}

#pragma argsused
void Wavefile_Obuffer::write_buffer(int32 fd)
{
  int write_pos;
  for (write_pos = 0; write_pos < data_size; write_pos++) {

  	  // Check if we are at the end of the output buffer.
     // If so, flush it.
	  if (mmioinfoOut.pchNext == mmioinfoOut.pchEndWrite)
	  {
	     mmioinfoOut.dwFlags |= MMIO_DIRTY;

	     if (mmioAdvance(hmmioOut, &mmioinfoOut, MMIO_WRITE)
            != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
				MessageBox(NULL, "mmioAdvance() failed!", "Wave file output error",
      		           MB_OK | MB_ICONEXCLAMATION);
#else
				cerr << "mmioAdvance() failed!" << endl;
#endif
				ExitProcess(1);
	     }
	  }

     // Copy one byte
	  *mmioinfoOut.pchNext++ = temp[write_pos];
  }

  // Reset buffer pointers
  int i;
  for(i=0; i<channels; i++)
   	bufferp[i] = i * channels;

  return;
}

#ifdef SEEK_STOP
void Wavefile_Obuffer::clear_buffer()

{
	// Since we write each frame, and seeks and stops occur between
   // frames, nothing is needed here.
}

void Wavefile_Obuffer::set_stop_flag()

{
}
#endif


Wavefile_Obuffer::~Wavefile_Obuffer()
{
	// Mark the current chunk as dirty and flush it
   mmioinfoOut.dwFlags |= MMIO_DIRTY;
   if (mmioSetInfo(hmmioOut, &mmioinfoOut, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
		MessageBox(NULL, "mmioSetInfo() failed!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
		cerr << "mmioSetInfo() failed!" << endl;
#endif
   }

   // Ascend out of data chunk
   if (mmioAscend(hmmioOut, &ckOut, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
		MessageBox(NULL, "Ascend on data chunk failed!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
		cerr << "mmioAscend() failed!" << endl;
#endif
   }

   // Ascend out of RIFF chunk
   if (mmioAscend(hmmioOut, &ckOutRIFF, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
		MessageBox(NULL, "Ascend on RIFF chunk failed!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
		cerr << "mmioAscend() failed!" << endl;
#endif
   }

   // Close the file
   if (mmioClose(hmmioOut, 0) != MMSYSERR_NOERROR) {

#ifdef WIN32GUI
		MessageBox(NULL, "Could not close output file!", "Wave file output error",
                 MB_OK | MB_ICONEXCLAMATION);
#else
		cerr << "mmioClose() failed!" << endl;
#endif
	}

   // Free the buffer memory
 	delete [] temp;
}

Obuffer *create_Wavefile_obuffer(MPEG_Args *maplay_args)
{
	Obuffer *buffer;

	enum e_mode mode = maplay_args->MPEGheader->mode();
   enum e_channels which_channels = maplay_args->which_c;

	if ((mode == single_channel) || (which_channels != both))
		buffer = new Wavefile_Obuffer(1, maplay_args);	// mono
   else
		buffer = new Wavefile_Obuffer(2, maplay_args);	// stereo

   return(buffer);
}

#endif // __WIN32__
