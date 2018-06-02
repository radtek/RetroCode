/* maplay.cpp - MPEG audio decoder

	Changes to original maplay 1.2, made by Jeff Tsay:

   - Header, bitstream, and miscellaneous flags come from main program
   - CRC and range check violations ignored.
   - Playtime not printed
	- Before every frame, maplay checks if the user has asked it to
     stop or seek, which will be reflected in the maplay_args. Every
     16 frames a message is sent to the parent telling it which frame
     maplay is decoding. All this stuff is synchronized using a mutex.
   - Eliminated reading of crc from maplay_args.
   - Layer III decoder object used for layer III frames. */

/*
 *  @(#) maplay.cc 1.20, last edit: 6/22/94 12:32:55
 *  @(#) Copyright (C) 1993, 1994 Tobias Bading (bading@cs.tu-berlin.de)
 *  @(#) Berlin University of Technology
 *
 *  Many thanks for ideas and implementations to:
 *  -> Jim Boucher (jboucher@flash.bu.edu)
 *     for his idea and first implementation of 8 kHz u-law output
 *  -> Louis P. Kruger (lpkruger@phoenix.princeton.edu)
 *     for his implementation of the LinuxObuffer class
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 *  Changes from version 1.1 to 1.2:
 *    - minor changes to create a LinuxObuffer object
 *    - minor changes for a u-law version, which creates 8 kHz u-law output
 *      on an amd device or in stdout mode, if compiled with ULAW defined
 *    - option -amd forces maplay to treat /dev/audio as an amd device
 *      in the u-law version. This is helpful on some SPARC clones.
 *    - iostreams manipulator calls like "cerr << setw (2) << ..." replaced by
 *      "cerr.width (2); ..." due to problems with older GNU C++ releases.
 */

#ifdef  __WIN32__
#include "mpw_msg.h"
#endif // __WIN32__

#ifndef  GUI
#include <iostream.h>  // for reporting errors
#endif   // GUI

#include "all.h"
#include "crc.h"
#include "header.h"
#include "subband.h"
#include "sublay1.h"
#include "sublay2.h"
#include "synfilt.h"
#include "ibitstr.h"
#include "obuffer.h"
#include "args.h"
#include "layer3.h"

#ifdef SEEK_STOP
#include "mutx_imp.h"
#endif

SynthesisFilter *filter1 = NULL, *filter2 = NULL;
Obuffer *buffer = NULL;
LayerIII_Decoder *l3decoder = NULL;

void maplay_Exit(uint32 returncode)
{

#ifdef SEEK_STOP
  if ((returncode == 1) && buffer) {
  	  buffer->set_stop_flag();
  }
#endif // SEEK_STOP

  delete buffer;
  buffer = NULL;

  delete filter1;
  filter1 = NULL;
  delete filter2;
  filter2 = NULL;

  delete l3decoder;
  l3decoder = NULL;
}

uint32 maplay(MPEG_Args *maplay_args)
{
	uint32 layer;
	enum e_mode mode;

   bool read_ready = false, write_ready = false;

   // These arguments should not change while decoding
	Crc16 *crc         = NULL;
   Ibitstream *stream = maplay_args->stream;
   Header *header     = maplay_args->MPEGheader;
	enum e_channels which_channels = maplay_args->which_c;

#ifdef SEEK_STOP
   _Mutex mutex       = maplay_args->mutex;
#endif

#ifdef WIN32GUI
   HWND hWnd          = maplay_args->hWnd;
#else
	// copy your operating system dependent arguments here
#endif // WIN32GUI

   // get info from header of first frame:
   layer = header->layer();
   if ((mode = header->mode()) == single_channel)
	   which_channels = left;

   // create filter(s):
   {
      real scalefactor = (maplay_args->use_own_scalefactor) ?
      	    			    maplay_args->scalefactor  :
                         32768.0f;

		filter1 = new SynthesisFilter(0, scalefactor);

	   if ((mode != single_channel) && (which_channels == both))
		   filter2 = new SynthesisFilter(1, scalefactor);
   }

   // create buffer, and check to see if created ok:

#ifdef __WIN32__

	if (maplay_args->stdout_mode) {

   	buffer = create_stdout_obuffer(maplay_args);

   } else {

     switch (maplay_args->output_mode) {

      case O_DIRECTSOUND:
//      buffer = create_ds_obuffer(maplay_args);
//      break;

      case O_WAVEMAPPER:
      buffer = create_obuffer(maplay_args);
      break;

      case O_WAVEFILE:
      buffer = create_Wavefile_obuffer(maplay_args);
      break;
     }
   }

#else

   buffer = (maplay_args->stdout_mode) ?
   			create_stdout_obuffer(maplay_args) :
	   		create_obuffer(maplay_args);

#endif

   if (buffer == NULL) {
		maplay_Exit(0);
      return 1;
   }

  // Layer III : initialize decoder

  	if (layer == 3)
      l3decoder = new LayerIII_Decoder(stream, header, filter1,
      											filter2, buffer, which_channels);

   do
   {

#ifdef SEEK_STOP

	 mtx_lock(mutex);

	 if (maplay_args->stop) {
      maplay_Exit(1);
      mtx_unlock(mutex);
      return 0;
    }

	 if (maplay_args->position_change) {

		buffer->clear_buffer();

      if (!header->stream_seek(stream, maplay_args->desired_position)) {
      	maplay_Exit(0);
	      mtx_unlock(mutex);
         return 1;
      }

		maplay_args->position_change = false;

      filter1->reset();

      if ((which_channels == both) && (mode != single_channel))
      	filter2->reset();

      if (l3decoder)
        	l3decoder->seek_notify();

		// notify the parent of the current position

#ifdef WIN32GUI
		PostMessage(hWnd, SEEK_ACK, NULL, NULL);
		PostMessage(hWnd, SCROLL_POS, stream->current_frame(), 0);
#else

#endif // WIN32GUI

	 }

	 // Send notification to the scroll bar every 16 frames
    {
	  int32 cf = stream->current_frame();
	  if (!(cf & 0xf) && !(maplay_args->stop)) {
  	  // Notify the parent of the current position

#ifdef WIN32GUI
	  		 PostMessage(hWnd, SCROLL_POS, cf, 0);
#else

#endif // WIN32GUI
	  }

    mtx_unlock(mutex);
    }

#endif // SEEK_STOP

	 // is there a change in important parameters?
	 // (bitrate switching is allowed)
	 if (header->layer() != layer)
	 {
		// layer switching is allowed

      if (header->layer() == 3) {
         l3decoder = new LayerIII_Decoder(stream, header,
           											filter1, filter2,
                                          buffer, which_channels);
      } else if (layer == 3) {
      	delete l3decoder;
         l3decoder = NULL;
      }

		layer = header->layer();
	 }

	 if (layer != 3) {

	    Subband *subbands[32];
	    uint32 num_subbands = header->number_of_subbands();
       uint32 i;
       mode = header->mode();

		 // create subband objects:
		 if (layer == 1)
		 {
			if (mode == single_channel)
				for (i = 0; i < num_subbands; ++i)
				  subbands[i] = new SubbandLayer1(i);
			else if (mode == joint_stereo) {
				for (i = 0; i < header->intensity_stereo_bound(); ++i)
				  subbands[i] = new SubbandLayer1Stereo(i);
				for (; i < num_subbands; ++i)
				  subbands[i] = new SubbandLayer1IntensityStereo(i);
			} else {
				for (i = 0; i < num_subbands; ++i)
				  subbands[i] = new SubbandLayer1Stereo(i);
	      }

		 } else { // Layer II
			if (mode == single_channel)
				for (i = 0; i < num_subbands; ++i)
		   	  subbands[i] = new SubbandLayer2(i);
			else if (mode == joint_stereo)
			{
				for (i = 0; i < header->intensity_stereo_bound(); ++i)
			 	    subbands[i] = new SubbandLayer2Stereo(i);
				for (; i < num_subbands; ++i)
				    subbands[i] = new SubbandLayer2IntensityStereo(i);
			} else {
				for (i = 0; i < num_subbands; ++i)
				    subbands[i] = new SubbandLayer2Stereo(i);
         }
	 	 }

  	    // start to read audio data:
	    for (i = 0; i < num_subbands; ++i)
	       subbands[i]->read_allocation(stream, header, crc);

		 if (layer == 2)
			for (i = 0; i < num_subbands; ++i)
				((SubbandLayer2 *)subbands[i])->read_scalefactor_selection(stream,
            																		     crc);

		 if (!crc || header->checksum_ok())
		 {
			// no checksums or checksum ok, continue reading from stream:
			for (i = 0; i < num_subbands; ++i)
				subbands[i]->read_scalefactor(stream, header);

			do
			{
				for (i = 0; i < num_subbands; ++i)
					read_ready = subbands[i]->read_sampledata(stream);

				do
				{
					for (i = 0; i < num_subbands; ++i)
						write_ready = subbands[i]->put_next_sample(which_channels,
   	                                                       filter1, filter2);

					filter1->calculate_pcm_samples(buffer);
					if ((which_channels == both) && (mode != single_channel))
               	filter2->calculate_pcm_samples(buffer);
				} while (!write_ready);
			} while (!read_ready);

	      buffer->write_buffer(1);

		 } // checksum ok
	 // Jeff : Don't let user know if crc violated.
//	    else
		// Sh*t! Wrong crc checksum in frame!
//		cerr << "WARNING: frame contains wrong crc checksum! (throwing frame away)\n";

       for (i = 0; i < num_subbands; ++i)
			delete subbands[i];

    } else {  // Layer III
	   l3decoder->decode();
    }

   }
   while (header->read_header(stream, &crc));

#ifdef SEEK_STOP

   mtx_lock(mutex);

   if (!maplay_args->stop) {

      // notify the parent of the last frame

#ifdef WIN32GUI
      PostMessage(hWnd, SCROLL_POS, stream->current_frame(), 0);
#else

#endif // WIN32GUI
	}

#endif // SEEK_STOP

   maplay_Exit(0);

#ifdef SEEK_STOP
   maplay_args->done = true;

   if (!maplay_args->stop) {

     // tell the parent that we are done

#ifdef WIN32GUI
  	  PostMessage(hWnd, WM_THREADEND, NULL, NULL);
#else

#endif // WIN32GUI
	}

   mtx_unlock(mutex);

#endif // SEEK_STOP

   return 0;
}
