/* mci_obuf.cpp

	Output buffer class for Win32 multimedia system written by
   Jeff Tsay (ctsay@pasteur.eecs.berkeley.edu

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

/* Writing to Windows multimedia system with such a small
	buffer won't do, so we increase buffer size, and ignore
	most of the writes. Also we need to have a queue of 3 wave
	headers for smooth playback. The last header and the oldest
	header play while the current one is being filled in.

	Note that this does not support 8-bit soundcards yet! I don't
	know what the data format is to that */

/* Changes since last version: changed GMEM_MOVEABLE to GMEM_FIXED
	which is a bit faster, according to the suggestions of Paul Forgey.
	clear_buffer() added for seeking. Changes int16 parameter to int32
	for minor speed improvement. Last edit: 06/29/96. */

/* More changes: eliminated GlobalLock on the fixed memory, which
   is unnecessary.

   Added a function clear_buffer(), which clears the audio data
   when a seek is made by the user.

   Also added a function set_stop_flag() which
   sets a flag when playback is interrupted by the user. Then
   no attempt is made to unprepare headers after waveReset() is
   called by the main thread.

   Last edit: 10/12/96. */

/* Replaced usage of the PCMWAVEFORMAT structure with the more up
   to date WAVEFORMATEX structure.

   According to the suggestions of Sergey Kuzmin, replaced
   GlobalAlloc and GlobalFree with new and delete, which should
   eliminate memory leaks.

   Last edit: 12/31/96. */

#ifdef  __WIN32__
#define STRICT
#include <windows.h>
#include <process.h>

#ifndef WIN32GUI
#include <iostream.h>
#endif

#include "all.h"
#include "header.h"
#include "args.h"
#include "obuffer.h"
#include "mci_obuf.h"

HANDLE MCISemaphore;

#pragma argsused
void CALLBACK MCICallBack(HWAVEOUT hwo, UINT uMsg,
                          DWORD dwInstance,
                          DWORD dwParam1,
                          DWORD dwParam2)
{
	switch(uMsg)
	{
		case WOM_DONE:
		{
			LPWAVEHDR lpWaveHdr = (LPWAVEHDR) dwParam1;
			waveOutUnprepareHeader(hwo, lpWaveHdr, sizeof(WAVEHDR));
			ReleaseSemaphore(MCISemaphore, 1, NULL);
		}
      break;
	}
}

MCIbuffer::MCIbuffer(uint32 number_of_channels,
							MPEG_Args *maplay_args)
{
  channels  = number_of_channels;
  data_size = channels * BUFFERSIZE;

  if (maplay_args->MPEGheader->version() == MPEG2_LSF)
  		data_size >>= 1;

  if (maplay_args->MPEGheader->layer() == 1)
  		data_size /= 3;

  hdr_size      = sizeof(WAVEHDR);
  lpwavehdr_arr = new LPWAVEHDR[3];
  phwo          = maplay_args->phwo;
  fillup        = 0;

  lpwf = (tWAVEFORMATEX *) new WAVEFORMATEX;

  lpwf->wBitsPerSample  = 16;  // No 8-bit support yet
  lpwf->wFormatTag      = WAVE_FORMAT_PCM;
  lpwf->nChannels       = (WORD) channels;
  lpwf->nSamplesPerSec  = (DWORD) maplay_args->MPEGheader->frequency();
  lpwf->nAvgBytesPerSec = (DWORD) channels *
  											 maplay_args->MPEGheader->frequency() << 1;
  lpwf->nBlockAlign     = (WORD) (channels << 1);
  lpwf->cbSize          = 0;

  if (waveOutOpen(phwo, WAVE_MAPPER, (const tWAVEFORMATEX *) lpwf,
					   (DWORD) MCICallBack, NULL,
                  WAVE_ALLOWSYNC | CALLBACK_FUNCTION)
      != MMSYSERR_NOERROR)
  {
#ifdef WIN32GUI
_endthread(); return;
		MessageBox(maplay_args->hWnd, "Could not open wave device.","Audio playback error", MB_ICONSTOP | MB_OK);
		ExitProcess(-1);
#else
		cerr << endl << "Could not open wave device." << endl;
#endif
		return;
  }

  buffer_count = 0;

  uint32 i;

  for(i=0; i<3; i++) {
	  lpwavehdr_arr[i] = (LPWAVEHDR) new WAVEHDR;

     LPWAVEHDR temp = lpwavehdr_arr[i];

	  if(!temp) return;

	  temp->lpData = (LPSTR) new char[data_size];

	  if(!temp->lpData) return;
	  temp->dwBufferLength  = data_size;
	  temp->dwBytesRecorded = 0;
	  temp->dwUser          = 0;  // If played, dwUser = 1
	  temp->dwLoops         = 0;
	  temp->dwFlags         = NULL;
  }

  for(i=0; i<channels; i++)
	   bufferp[i] = i * channels;

  user_stop = 0;

  MCISemaphore = CreateSemaphore(NULL, 0, 1024, "MCISemaphore");
}

void MCIbuffer::append(uint32 channel, int16 value)
{
  // Need to break up the 32-bit integer into 2 8-bit bytes.
  // (ignore the first two bytes - either 0x0000 or 0xffff)
  // Note that Intel byte order is backwards!!!

  LPSTR temp = lpwavehdr_arr[2]->lpData;

  temp[bufferp[channel]]   = (char) (value & 0xff);
  temp[bufferp[channel]+1] = (char) (value >> 8);

  bufferp[channel] += channels << 1;

  return;
}

#pragma argsused
void MCIbuffer::write_buffer(int32 fd)
{
	// Actually write only when buffer is actually full.
	if ((++buffer_count & BIT_SELECT) == 0) {

		buffer_count = 0;

		// Wait for 2 completed headers
		if (fillup > 1) {

			// Prepare & write newest header
			waveOutPrepareHeader(*phwo, lpwavehdr_arr[2], hdr_size);
			waveOutWrite(*phwo, lpwavehdr_arr[2], hdr_size);

			// Header has now been sent
			lpwavehdr_arr[2]->dwUser = 1;

			wave_swap();

			// Unprepare oldest header
			if (lpwavehdr_arr[2]->dwUser) {
			   WaitForSingleObject(MCISemaphore, 10000);
			}

		} else {

			if (++fillup == 2) {

					// Write the previously calculated 2 headers
					waveOutPrepareHeader(*phwo, lpwavehdr_arr[0], hdr_size);
					waveOutWrite(*phwo, lpwavehdr_arr[0], hdr_size);

					// Header has now been sent
					lpwavehdr_arr[0]->dwUser = 1;

					wave_swap();

					waveOutPrepareHeader(*phwo, lpwavehdr_arr[0], hdr_size);
					waveOutWrite(*phwo, lpwavehdr_arr[0], hdr_size);

					// Header has now been sent
					lpwavehdr_arr[0]->dwUser = 1;

			} else {
				wave_swap();
         }
		}

		for(uint32 i=0; i<channels; i++)
		  bufferp[i] = i * channels;
	}
	return;
}

void MCIbuffer::wave_swap()
{
	LPWAVEHDR temp   = lpwavehdr_arr[2];
   lpwavehdr_arr[2] = lpwavehdr_arr[1];
   lpwavehdr_arr[1] = lpwavehdr_arr[0];
	lpwavehdr_arr[0] = temp;

	return;
}

#ifdef SEEK_STOP
void MCIbuffer::clear_buffer()
// Clear all the data in the buffers
{

	waveOutReset(*phwo);

   unsigned int i;

	for(i=0; i<3; i++) {

		LPWAVEHDR temp = lpwavehdr_arr[i];

		if ((temp->dwUser) && (i < 2))
			WaitForSingleObject(MCISemaphore, 10000);

		temp->dwUser = 0;

		for(unsigned int j=0; j<data_size; j++)
			temp->lpData[j] = (char) 0;
	}

//  	waveOutReset(*phwo);

	// Reset buffer pointers
	for(i=0; i<channels; i++)
		bufferp[i] = i * channels;

	// Force the buffers to fillup before playing.
	fillup = buffer_count = 0;

}

void MCIbuffer::set_stop_flag()
// Set the flag to avoid unpreparing non-existent headers
{
	user_stop = 1;
   return;
}
#endif


MCIbuffer::~MCIbuffer()
{
   if (user_stop) {

     waveOutReset(*phwo);

   } else {

   	if (fillup == 1) {

	   	// Write the last header calculated (at the top of the array).
		   waveOutPrepareHeader(*phwo, lpwavehdr_arr[0], hdr_size);
     		waveOutWrite(*phwo, lpwavehdr_arr[0], hdr_size);

         // Header has been written.
		   lpwavehdr_arr[0]->dwUser = 1;
      }

      if (buffer_count) {

      	// Write the last wave header (probably not be written due to buffer
         //	size increase.)

         for(unsigned int i = bufferp[channels-1]; i < data_size; i++)
    			 lpwavehdr_arr[2]->lpData[i] = (char) 0;

		   waveOutPrepareHeader(*phwo, lpwavehdr_arr[2], hdr_size);
    		waveOutWrite(*phwo, lpwavehdr_arr[2], hdr_size);

		   // Header has been written.
         lpwavehdr_arr[2]->dwUser = 1;
         wave_swap();
  	   }
   }

	// Unprepare and free the header memory.
	for (int j=2; j>=0; j--) {
  		if (lpwavehdr_arr[j]->dwUser && !user_stop)
			WaitForSingleObject(MCISemaphore, 10000);

      delete [] lpwavehdr_arr[j]->lpData;
      delete lpwavehdr_arr[j];
	}

   delete [] lpwavehdr_arr;
	delete lpwf;

	while(waveOutClose(*phwo) == WAVERR_STILLPLAYING)
		Sleep(SLEEPTIME);

   CloseHandle(MCISemaphore);

	return;
}

Obuffer *create_obuffer(MPEG_Args *maplay_args)
{
	Obuffer *buffer;

	enum e_mode mode = maplay_args->MPEGheader->mode();
   enum e_channels which_channels = maplay_args->which_c;

	if ((mode == single_channel) || (which_channels != both))
		buffer = new MCIbuffer(1, maplay_args);	// mono
   else
		buffer = new MCIbuffer(2, maplay_args);	// stereo

   return(buffer);
}

#endif // __WIN32__
