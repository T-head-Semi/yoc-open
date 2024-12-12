/* Copyright (c) 2013 Jean-Marc Valin */
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
   OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* This is meant to be a simple example of encoding and decoding audio
   using Opus. It should make it easy to understand how the Opus API
   works. For more information, see the full API documentation at:
   https://www.opus-codec.org/docs/ */
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <opus.h>
#include <stdio.h>
#include "test_data.h"
/*The frame size is hardcoded for this sample code but it doesn't have to be*/
#define FRAME_SIZE 960
#define CHANNELS 2
#define APPLICATION OPUS_APPLICATION_AUDIO
#define BITRATE 64000

#define MAX_FRAME_SIZE 6*960
#define MAX_PACKET_SIZE (3*1276)
unsigned char pcm_bytes[MAX_FRAME_SIZE*CHANNELS*2];

#if defined(CONFIG_OPUS_DECODER_TEST) && CONFIG_OPUS_DECODER_TEST > 0
#define OUT_LEN AUDIO_DATA_SIZE
static unsigned char g_outbuf[OUT_LEN];
#endif

static int read_buf(char *buf, int buf_len, int *index, int read_len, char *out_buf)
{
    int cur = *index;
    int read_byte = read_len;

    if((cur + read_byte) > buf_len) {
        read_byte = buf_len - cur;
    }

    if(read_byte)
        memcpy(out_buf, &buf[cur], read_byte);
    cur = cur + read_byte;
    *index = cur;

    return read_byte;
}

opus_int16 in[FRAME_SIZE*CHANNELS];
opus_int16 out[MAX_FRAME_SIZE*CHANNELS];
unsigned char cbits[MAX_PACKET_SIZE];


void* opus_test()
{
   int nbBytes;
   /*Holds the state of the encoder and decoder */
   OpusEncoder *encoder;
   OpusDecoder *decoder;
   int err;
   int in_buf_index = 0;
   int out_pos = 0;
   char*  in_pcm;
   int in_pcm_size = 0;

#if defined(CONFIG_OPUS_DECODER_TEST) && CONFIG_OPUS_DECODER_TEST > 0
   int frame_size = 0;
   g_audio_info.out_data = (char*)g_outbuf;
   memcpy(g_outbuf, wav_audio_data, 78);
   out_pos += 78;
#else
   g_audio_info.out_data = 0x0;
#endif
   g_audio_info.out_data_len = 0x0;
   in_pcm = (char*)wav_audio_data + 78;
   in_pcm_size = AUDIO_DATA_SIZE - 78;
//#endif
   // 	g_audio_info.out_data = g_outbuf;
   //  g_audio_info.out_data_len = OUT_LEN;

   /*Create a new encoder state */
   encoder = opus_encoder_create(g_audio_info.audio_sample_rate, g_audio_info.audio_channel, APPLICATION, &err);
   if (err<0)
   {
      printf( "failed to create an encoder: %s\n", opus_strerror(err));
      return NULL;
   }
   /* Set the desired bit-rate. You can also set other parameters if needed.
      The Opus library is designed to have good defaults, so only set
      parameters you know you need. Doing otherwise is likely to result
      in worse quality, but better. */
   err = opus_encoder_ctl(encoder, OPUS_SET_BITRATE(BITRATE));
   if (err<0)
   {
      printf( "failed to set bitrate: %s\n", opus_strerror(err));
      return NULL;
   }
   err = opus_encoder_ctl(encoder, OPUS_SET_COMPLEXITY(4));
   if (err<0)
   {
      printf( "failed to set complexity: %s\n", opus_strerror(err));
      return NULL;
   }

   /* Create a new decoder state. */
   decoder = opus_decoder_create(g_audio_info.audio_sample_rate, g_audio_info.audio_channel, &err);
   if (err<0)
   {
      printf( "failed to create decoder: %s\n", opus_strerror(err));
      return NULL;
   }

   while (1)
   {
      int i;
      /* Read a 16 bits/sample audio frame. */
      //fread(pcm_bytes, sizeof(short)*CHANNELS, FRAME_SIZE, fin);
      if (read_buf((char*)in_pcm, in_pcm_size, &in_buf_index, FRAME_SIZE * sizeof(short) * g_audio_info.audio_channel, (char*)pcm_bytes) == 0)
         break;
      /* Convert from little-endian ordering. */
      for (i=0;i<g_audio_info.audio_channel*FRAME_SIZE;i++)
         in[i]=pcm_bytes[2*i+1]<<8|pcm_bytes[2*i];

      /* Encode the frame. */
      // init_testsuite();
      nbBytes = opus_encode(encoder, in, FRAME_SIZE, cbits, MAX_PACKET_SIZE);
      if (nbBytes<0)
      {
         printf( "encode failed: %s\n", opus_strerror(nbBytes));
         return NULL;
      }

      /* Decode the data. In this example, frame_size will be constant because
         the encoder is using a constant frame size. However, that may not
         be the case for all encoders, so the decoder must always check
         the frame size returned. */
#if defined(CONFIG_OPUS_DECODER_TEST) && CONFIG_OPUS_DECODER_TEST > 0
      frame_size = opus_decode(decoder, cbits, nbBytes, out, MAX_FRAME_SIZE, 0);
      if (frame_size<0)
      {
         printf( "decoder failed: %s\n", opus_strerror(frame_size));
         return NULL;
      }

      /* Convert to little-endian ordering. */
      for(i=0;i<g_audio_info.audio_channel*frame_size;i++)
      {
         pcm_bytes[2*i]=out[i]&0xFF;
         pcm_bytes[2*i+1]=(out[i]>>8)&0xFF;
      }
      /* Write the decoded audio to file. */
      //fwrite(pcm_bytes, sizeof(short), frame_size*CHANNELS, fout);
      memcpy(g_outbuf + out_pos, pcm_bytes, sizeof(short) * frame_size * g_audio_info.audio_channel);
      out_pos += sizeof(short) * frame_size * g_audio_info.audio_channel;
#endif
   }
   g_audio_info.out_data_len = out_pos;
   /*Destroy the encoder state*/
   opus_encoder_destroy(encoder);
   opus_decoder_destroy(decoder);

   return &g_audio_info;
}
