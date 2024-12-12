/* Copyright (c) 2007-2008 CSIRO
   Copyright (c) 2007-2009 Xiph.Org Foundation
   Written by Jean-Marc Valin */
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "mathops.h"
#include "cwrs.h"
#include "vq.h"
#include "arch.h"
#include "os_support.h"
#include "bands.h"
#include "rate.h"
#include "pitch.h"

#ifndef OVERRIDE_vq_exp_rotation1
static void exp_rotation1(celt_norm *X, int len, int stride, opus_val16 c, opus_val16 s)
{
   int i;
   opus_val16 ms;
   celt_norm *Xptr;
   Xptr = X;
   ms = NEG16(s);
   for (i=0;i<len-stride;i++)
   {
      celt_norm x1, x2;
      x1 = Xptr[0];
      x2 = Xptr[stride];
      Xptr[stride] = EXTRACT16(PSHR32(MAC16_16(MULT16_16(c, x2),  s, x1), 15));
      *Xptr++      = EXTRACT16(PSHR32(MAC16_16(MULT16_16(c, x1), ms, x2), 15));
   }
   Xptr = &X[len-2*stride-1];
   for (i=len-2*stride-1;i>=0;i--)
   {
      celt_norm x1, x2;
      x1 = Xptr[0];
      x2 = Xptr[stride];
      Xptr[stride] = EXTRACT16(PSHR32(MAC16_16(MULT16_16(c, x2),  s, x1), 15));
      *Xptr--      = EXTRACT16(PSHR32(MAC16_16(MULT16_16(c, x1), ms, x2), 15));
   }
}
#endif /* OVERRIDE_vq_exp_rotation1 */

void exp_rotation(celt_norm *X, int len, int dir, int stride, int K, int spread)
{
   static const int SPREAD_FACTOR[3]={15,10,5};
   int i;
   opus_val16 c, s;
   opus_val16 gain, theta;
   int stride2=0;
   int factor;

   if (2*K>=len || spread==SPREAD_NONE)
      return;
   factor = SPREAD_FACTOR[spread-1];

   gain = celt_div((opus_val32)MULT16_16(Q15_ONE,len),(opus_val32)(len+factor*K));
   theta = HALF16(MULT16_16_Q15(gain,gain));

   c = celt_cos_norm(EXTEND32(theta));
   s = celt_cos_norm(EXTEND32(SUB16(Q15ONE,theta))); /*  sin(theta) */

   if (len>=8*stride)
   {
      stride2 = 1;
      /* This is just a simple (equivalent) way of computing sqrt(len/stride) with rounding.
         It's basically incrementing long as (stride2+0.5)^2 < len/stride. */
      while ((stride2*stride2+stride2)*stride + (stride>>2) < len)
         stride2++;
   }
   /*NOTE: As a minor optimization, we could be passing around log2(B), not B, for both this and for
      extract_collapse_mask().*/
   len = celt_udiv(len, stride);
   for (i=0;i<stride;i++)
   {
      if (dir < 0)
      {
         if (stride2)
            exp_rotation1(X+i*len, len, stride2, s, c);
         exp_rotation1(X+i*len, len, 1, c, s);
      } else {
         exp_rotation1(X+i*len, len, 1, c, -s);
         if (stride2)
            exp_rotation1(X+i*len, len, stride2, s, -c);
      }
   }
}

/** Takes the pitch vector and the decoded residual vector, computes the gain
    that will give ||p+g*y||=1 and mixes the residual with the pitch. */
static void normalise_residual(int * OPUS_RESTRICT iy, celt_norm * OPUS_RESTRICT X,
      int N, opus_val32 Ryy, opus_val16 gain)
{
   int i;
#ifdef FIXED_POINT
   int k;
#endif
   opus_val32 t;
   opus_val16 g;

#ifdef FIXED_POINT
   k = celt_ilog2(Ryy)>>1;
#endif
   t = VSHR32(Ryy, 2*(k-7));
   g = MULT16_16_P15(celt_rsqrt_norm(t),gain);

   i=0;
   do
      X[i] = EXTRACT16(PSHR32(MULT16_16(g, iy[i]), k+1));
   while (++i < N);
}

static unsigned extract_collapse_mask(int *iy, int N, int B)
{
   unsigned collapse_mask;
   int N0;
   int i;
   if (B<=1)
      return 1;
   /*NOTE: As a minor optimization, we could be passing around log2(B), not B, for both this and for
      exp_rotation().*/
   N0 = celt_udiv(N, B);
   collapse_mask = 0;
   i=0; do {
      int j;
      unsigned tmp=0;
      j=0; do {
         tmp |= iy[i*N0+j];
      } while (++j<N0);
      collapse_mask |= (tmp!=0)<<i;
   } while (++i<B);
   return collapse_mask;
}

opus_val16 op_pvq_search_c(celt_norm *X, int *iy, int K, int N, int arch)
{
   VARDECL(celt_norm, y);
   VARDECL(celt_norm, signx);
   int i, j;
   int pulsesLeft;
   opus_val32 sum;
   opus_val32 xy;
   opus_val16 yy;
   SAVE_STACK;

   (void)arch;
   ALLOC(y, N, celt_norm);
   ALLOC(signx, N, celt_norm);

   sum = 0;
   xy = yy = 0;
   pulsesLeft = K;

   if (K > (N>>1))
   {
#if  !defined(E906) && !defined(E907)
      j=0; do {
         signx[j] = -(X[j]<0);
         X[j] = ABS16(X[j]);
         sum += X[j];
      } while (++j<N);
#else
      asm volatile(
            "mv        t2, %1           \n\t"   //X
            "mv        t3, %2           \n\t"   //signx
            "srai      t4, %3, 2        \n\t"
            "beq       t4, x0, 2f       \n\t"
            "mv        t1, x0           \n\t"   //j = 0
            "li        a7, 0x10001      \n\t"
            "1:                         \n\t"
            "lwia      t5, (t2), 1, 2   \n\t"
            "lwia      t6, (t2), 1, 2   \n\t"
            "scmplt16  a5, t5, x0       \n\t"
            "scmplt16  a6, t6, x0       \n\t"
            "swia      a5, (t3), 1, 2   \n\t"
            "swia      a6, (t3), 1, 2   \n\t"
            "kabs16    t5, t5           \n\t"
            "kabs16    t6, t6           \n\t"
            "sw        t5, -8(t2)       \n\t"
            "sw        t6, -4(t2)       \n\t"
            "kmada     %0, t5, a7       \n\t"
            "addi      t1, t1, 1        \n\t"   //j++
            "kmada     %0, t6, a7       \n\t"
            "blt       t1, t4, 1b       \n\t"
            "2:                         \n\t"
            "andi      t4, %3, 3        \n\t"
            "beq       t4, x0, 4f       \n\t"
            "mv        t1, x0           \n\t"   //j = 0
            "3:                         \n\t"
            "lhia      t5, (t2), 1, 1   \n\t"
            "addi      t1, t1, 1        \n\t"   //j++
            "scmplt16  a5, t5, x0       \n\t"
            "shia      a5, (t3), 1, 1   \n\t"
            "kabsw     t5, t5           \n\t"
            "sh        t5, -2(t2)       \n\t"
            "add       %0, %0, t5       \n\t"
            "blt       t1, t4, 3b       \n\t"
            "4:                         \n\t"
            :"+r"(sum)
            :"r"(X), "r"(signx), "r"(N)
            :"t1", "t2", "t3", "t4", "t5", "t6", "a7", "a5", "a6"
      );
#endif

      opus_val16 rcp;

      if (sum <= K)
      {
         X[0] = QCONST16(1.f,14);
         j=1; do
            X[j]=0;
         while (++j<N);
         sum = QCONST16(1.f,14);
      }
      rcp = EXTRACT16(MULT16_32_Q16(K, celt_rcp(sum)));
      j=0;
      do {
         iy[j] = MULT16_16_Q15(X[j],rcp);
         y[j] = (celt_norm)iy[j];
         yy = MAC16_16(yy, y[j],y[j]);
         xy = MAC16_16(xy, X[j],y[j]);
         y[j] *= 2;
         pulsesLeft -= iy[j];
      }  while (++j<N);
   }
   else
   {
#if  !defined(E906) && !defined(E907)
      j=0; do {
         signx[j] = -(X[j]<0);
         X[j] = ABS16(X[j]);
         iy[j] = 0;
         y[j] = 0;
      } while (++j<N);
#else
      asm volatile(
            "mv        a7, %3           \n\t"   //iy
            "mv        a4, %4           \n\t"   //y
            "mv        t2, %0           \n\t"   //X
            "mv        t3, %1           \n\t"   //signx
            "srai      t4, %2, 2        \n\t"
            "beq       t4, x0, 2f       \n\t"
            "mv        t1, x0           \n\t"   //j = 0
            "1:                         \n\t"
            "lwia      t5, (t2), 1, 2   \n\t"
            "lwia      t6, (t2), 1, 2   \n\t"
            "scmplt16  a5, t5, x0       \n\t"
            "scmplt16  a6, t6, x0       \n\t"
            "swia      a5, (t3), 1, 2   \n\t"
            "swia      a6, (t3), 1, 2   \n\t"
            "kabs16    t5, t5           \n\t"
            "kabs16    t6, t6           \n\t"
            "sw        t5, -8(t2)       \n\t"
            "sw        t6, -4(t2)       \n\t"
            "swia      x0, (a7), 1, 2   \n\t"
            "swia      x0, (a7), 1, 2   \n\t"
            "swia      x0, (a7), 1, 2   \n\t"
            "swia      x0, (a7), 1, 2   \n\t"
            "swia      x0, (a4), 1, 2   \n\t"
            "swia      x0, (a4), 1, 2   \n\t"
            "addi      t1, t1, 1        \n\t"   //j++
            "blt       t1, t4, 1b       \n\t"
            "2:                         \n\t"
            "andi      t4, %2, 3        \n\t"
            "beq       t4, x0, 4f       \n\t"
            "mv        t1, x0           \n\t"   //j = 0
            "3:                         \n\t"
            "lhia      t5, (t2), 1, 1   \n\t"
            "addi      t1, t1, 1        \n\t"   //j++
            "scmplt16  a5, t5, x0       \n\t"
            "shia      a5, (t3), 1, 1   \n\t"
            "kabsw     t5, t5           \n\t"
            "sh        t5, -2(t2)       \n\t"
            "swia      x0, (a7), 1, 2   \n\t"
            "shia      x0, (a4), 1, 1   \n\t"
            "blt       t1, t4, 3b       \n\t"
            "4:                         \n\t"
            :
            :"r"(X), "r"(signx), "r"(N), "r"(iy), "r"(y)
            :"t1", "t2", "t3", "t4", "t5", "t6", "a7", "a5", "a6", "a4"
      );
#endif
   }
   //celt_sig_assert(pulsesLeft>=0);

//#ifdef FIXED_POINT_DEBUG
   //celt_sig_assert(pulsesLeft<=N+3);
//#endif
   if (pulsesLeft > N+3)
   {
      opus_val16 tmp = (opus_val16)pulsesLeft;
      yy = MAC16_16(yy, tmp, tmp);
      yy = MAC16_16(yy, tmp, y[0]);
      iy[0] += pulsesLeft;
      pulsesLeft=0;
   }

   for (i=0;i<pulsesLeft;i++)
   {
      int best_id;
      int rshift;

      rshift = 1+celt_ilog2(K-pulsesLeft+i+1);

      best_id = 0;
      yy = ADD16(yy, 1);

      opus_val16 Rxy, Ryy;
      opus_val16 best_num;
      opus_val16 best_den;
      Rxy = EXTRACT16(SHR32(ADD32(xy, EXTEND32(X[0])),rshift));
      Ryy = ADD16(yy, y[0]);

      Rxy = MULT16_16_Q15(Rxy,Rxy);
      best_den = Ryy;
      best_num = Rxy;
      j=1;
      do {
         Rxy = EXTRACT16(SHR32(ADD32(xy, EXTEND32(X[j])),rshift));
         Ryy = ADD16(yy, y[j]);
         Rxy = MULT16_16_Q15(Rxy,Rxy);
         if (opus_unlikely(MULT16_16(best_den, Rxy) > MULT16_16(Ryy, best_num)))
         {
            best_den = Ryy;
            best_num = Rxy;
            best_id = j;
         }
      } while (++j<N);

      xy = ADD32(xy, EXTEND32(X[best_id]));
      yy = ADD16(yy, y[best_id]);

      y[best_id] += 2;
      iy[best_id]++;
   }

   j=0;
   do {
      iy[j] = (iy[j]^signx[j]) - signx[j];
   } while (++j<N);
   RESTORE_STACK;
   return yy;
}

unsigned alg_quant(celt_norm *X, int N, int K, int spread, int B, ec_enc *enc,
      opus_val16 gain, int resynth, int arch)
{
   VARDECL(int, iy);
   opus_val16 yy;
   unsigned collapse_mask;
   SAVE_STACK;

   celt_assert2(K>0, "alg_quant() needs at least one pulse");
   celt_assert2(N>1, "alg_quant() needs at least two dimensions");

   /* Covers vectorization by up to 4. */
   ALLOC(iy, N+3, int);

   exp_rotation(X, N, 1, B, K, spread);

   yy = op_pvq_search(X, iy, K, N, arch);

   encode_pulses(iy, N, K, enc);

   if (resynth)
   {
      normalise_residual(iy, X, N, yy, gain);
      exp_rotation(X, N, -1, B, K, spread);
   }

   collapse_mask = extract_collapse_mask(iy, N, B);
   RESTORE_STACK;
   return collapse_mask;
}

/** Decode pulse vector and combine the result with the pitch vector to produce
    the final normalised signal in the current band. */
unsigned alg_unquant(celt_norm *X, int N, int K, int spread, int B,
      ec_dec *dec, opus_val16 gain)
{
   opus_val32 Ryy;
   unsigned collapse_mask;
   VARDECL(int, iy);
   SAVE_STACK;

   celt_assert2(K>0, "alg_unquant() needs at least one pulse");
   celt_assert2(N>1, "alg_unquant() needs at least two dimensions");
   ALLOC(iy, N, int);
   Ryy = decode_pulses(iy, N, K, dec);
   normalise_residual(iy, X, N, Ryy, gain);
   exp_rotation(X, N, -1, B, K, spread);
   collapse_mask = extract_collapse_mask(iy, N, B);
   RESTORE_STACK;
   return collapse_mask;
}

#ifndef OVERRIDE_renormalise_vector
void renormalise_vector(celt_norm *X, int N, opus_val16 gain, int arch)
{
   int i;
#ifdef FIXED_POINT
   int k;
#endif
   opus_val32 E;
   opus_val16 g;
   opus_val32 t;
   celt_norm *xptr;
   E = EPSILON + celt_inner_prod(X, X, N, arch);
#ifdef FIXED_POINT
   k = celt_ilog2(E)>>1;
#endif
   t = VSHR32(E, 2*(k-7));
   g = MULT16_16_P15(celt_rsqrt_norm(t),gain);

   xptr = X;
   for (i=0;i<N;i++)
   {
      *xptr = EXTRACT16(PSHR32(MULT16_16(g, *xptr), k+1));
      xptr++;
   }
   /*return celt_sqrt(E);*/
}
#endif /* OVERRIDE_renormalise_vector */

int stereo_itheta(const celt_norm *X, const celt_norm *Y, int stereo, int N, int arch)
{
   int i;
   int itheta;
   opus_val16 mid, side;
   opus_val32 Emid, Eside;

   Emid = Eside = EPSILON;
   if (stereo)
   {
      for (i=0;i<N;i++)
      {
         celt_norm m, s;
         m = ADD16(SHR16(X[i],1),SHR16(Y[i],1));
         s = SUB16(SHR16(X[i],1),SHR16(Y[i],1));
         Emid = MAC16_16(Emid, m, m);
         Eside = MAC16_16(Eside, s, s);
      }
   } else {
      Emid += celt_inner_prod(X, X, N, arch);
      Eside += celt_inner_prod(Y, Y, N, arch);
   }
   mid = celt_sqrt(Emid);
   side = celt_sqrt(Eside);
#ifdef FIXED_POINT
   /* 0.63662 = 2/pi */
   itheta = MULT16_16_Q15(QCONST16(0.63662f,15),celt_atan2p(side, mid));
#else
   itheta = (int)floor(.5f+16384*0.63662f*fast_atan2f(side,mid));
#endif

   return itheta;
}
