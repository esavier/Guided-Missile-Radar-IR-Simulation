

#ifndef __GMS_RCS_PLANAR_SURF_ZMM16R4_HPP__
#define __GMS_RCS_PLANAR_SURF_ZMM16R4_HPP__ 180420231543



/*MIT License
Copyright (c) 2020 Bernard Gingold
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

namespace file_version {

    const unsigned int GMS_RCS_PLANAR_SURF_ZMM16R4_MAJOR = 1U;
    const unsigned int GMS_RCS_PLANAR_SURF_ZMM16R4_MINOR = 0U;
    const unsigned int GMS_RCS_PLANAR_SURF_ZMM16R4_MICRO = 0U;
    const unsigned int GMS_RCS_PLANAR_SURF_ZMM16R4_FULLVER =
      1000U*GMS_RCS_PLANAR_SURF_ZMM16R4_MAJOR+
      100U*GMS_RCS_PLANAR_SURF_ZMM16R4_MINOR+
      10U*GMS_RCS_PLANAR_SURF_ZMM16R4_MICRO;
    const char * const GMS_RCS_PLANAR_SURF_ZMM16R4_CREATION_DATE = "18-04-2023 15:43 PM +00200 (TUE 18 APR 2023 GMT+2)";
    const char * const GMS_RCS_PLANAR_SURF_ZMM16R4_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const GMS_RCS_PLANAR_SURF_ZMM16R4_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const GMS_RCS_PLANAR_SURF_ZMM16R4_DESCRIPTION   = "AVX512 optimized Planar Surfaces Radar Cross Section (analytic) functionality.";

}

#include <cstdint>
#include <immintrin.h>
#include "GMS_config.h"
#include "GMS_sleefsimdsp.hpp"
#include "GMS_complex_zmm16r4.hpp"
#include "GMS_simd_utils.hpp"


namespace  gms {


         namespace radiolocation {


                 /*
                       Complex impedances.
                       Formula 7.1-6
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void zi_f716_zmm16r4(const __m512 tht,
                                        const __m512 mur,
                                        const __m512 mui,
                                        const __m512 epsr,
                                        const __m512 epsi,
                                        __m512 * __restrict zr,
                                        __m512 * __restrict zi) {

                        register __m512 cost,invc,divr,divi,csqr,csqi,wrkc;
                        cost = xcosf(tht);
                        wrkc = _mm512_setzero_ps();
                        cdiv_zmm16r4(mur,mui,epsr,epsi,&divr,&divi);
                        invc = _mm512_rcp14_ps(cost);
                        csqrt_zmm16r4(divr,divi,&wrkc,&csqr,&csqi);
                        *zr = _mm512_mul_ps(invc,csqr);
                        *zi = _mm512_mul_ps(invc,csqi);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void zi_f716_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                        const float * __restrict __ATTR_ALIGN__(64) pmur,
                                        const float * __restrict __ATTR_ALIGN__(64) pmui,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsr,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsi,
                                        float * __restrict __ATTR_ALIGN__(64) zr,
                                        float * __restrict __ATTR_ALIGN__(64)  zi) {

                        register __m512 tht  = _mm512_load_ps(&ptht[0]);
                        register __m512 mur  = _mm512_load_ps(&pmur[0]);
                        register __m512 mui  = _mm512_load_ps(&pmui[0]);
                        register __m512 epsr = _mm512_load_ps(&pepsr[0]);
                        register __m512 epsi = _mm512_load_ps(&pepsi[0]);
                        register __m512 cost,invc,divr,divi,csqr,csqi,wrkc;
                        cost = xcosf(tht);
                        wrkc = _mm512_setzero_ps();
                        cdiv_zmm16r4(mur,mui,epsr,epsi,&divr,&divi);
                        invc = _mm512_rcp14_ps(cost);
                        csqrt_zmm16r4(divr,divi,&wrkc,&csqr,&csqi);
                        _mm512_store_ps(&zr[0] ,_mm512_mul_ps(invc,csqr));
                        _mm512_store_ps(&zi[0] ,_mm512_mul_ps(invc,csqi));
                }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void zi_f716_zmm16r4_u(const float * __restrict  ptht,
                                        const float * __restrict  pmur,
                                        const float * __restrict  pmui,
                                        const float * __restrict  pepsr,
                                        const float * __restrict  pepsi,
                                        float * __restrict  zr,
                                        float * __restrict   zi) {

                        register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                        register __m512 mur  = _mm512_loadu_ps(&pmur[0]);
                        register __m512 mui  = _mm512_loadu_ps(&pmui[0]);
                        register __m512 epsr = _mm512_loadu_ps(&pepsr[0]);
                        register __m512 epsi = _mm512_loadu_ps(&pepsi[0]);
                        register __m512 cost,invc,divr,divi,csqr,csqi,wrkc;
                        cost = xcosf(tht);
                        wrkc = _mm512_setzero_ps();
                        cdiv_zmm16r4(mur,mui,epsr,epsi,&divr,&divi);
                        invc = _mm512_rcp14_ps(cost);
                        csqrt_zmm16r4(divr,divi,&wrkc,&csqr,&csqi);
                        _mm512_storeu_ps(&zr[0] ,_mm512_mul_ps(invc,csqr));
                        _mm512_storeu_ps(&zi[0] ,_mm512_mul_ps(invc,csqi));
                }


                 /*
                          Equivalent complex impedances.
                          Formula 7.1-4
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f714_zmm16r4( const __m512 tht1,
                                        const __m512 mur1,
                                        const __m512 mui1,
                                        const __m512 epsr1,
                                        const __m512 epsi1,
                                        const __m512 tht2,
                                        const __m512 mur2,
                                        const __m512 mui2,
                                        const __m512 epsr2,
                                        const __m512 epsi2,
                                        __m512 * __restrict Rr,
                                        __m512 * __restrict Ri) {

                     using namespace gms::math;
                     register __m512 z1r,z1i,z2r,z2i;
                     register __m512 t0r,t0i,t1r,t1i;
                     zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                     zi_f716_zmm16r4(tht2,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                     t0r = _mm512_sub_ps(z1r,z2r);
                     t1r = _mm512_add_ps(z1r,z2r);
                     t0i = _mm512_sub_ps(z1i,z2i);
                     t1i = _mm512_add_ps(z1i,z2i);
                     t0r = negate_zmm16r4(t0r);
                     t0i = negate_zmm16r4(t0i);
                     cdiv_zmm16r4(t0r,t0i,t1r,t1i,*Rr,*Ri);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f714_zmm16r4_a( const float * __restrict __ATTR_ALIGN__(64) ptht1,
                                        const float * __restrict __ATTR_ALIGN__(64) pmur1,
                                        const float * __restrict __ATTR_ALIGN__(64) pmui1,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsr1,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsi1,
                                        const float * __restrict __ATTR_ALIGN__(64) ptht2,
                                        const float * __restrict __ATTR_ALIGN__(64) pmur2,
                                        const float * __restrict __ATTR_ALIGN__(64) pmui2,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsr2,
                                        const float * __restrict __ATTR_ALIGN__(64) pepsi2,
                                        float * __restrict __ATTR_ALIGN__(64) Rr,
                                        float * __restrict __ATTR_ALIGN__(64) Ri) {

                     using namespace gms::math;
                     register __m512 tht1  = _mm512_load_ps(&ptht1[0]);
                     register __m512 mur1  = _mm512_load_ps(&pmur1[0]);
                     register __m512 mui1  = _mm512_load_ps(&pmui1[0]);
                     register __m512 epsr1 = _mm512_load_ps(&pepsr1[0]);
                     register __m512 epsi1 = _mm512_load_ps(&pepsi1[0]);
                     register __m512 tht2  = _mm512_load_ps(&ptht2[0]);
                     register __m512 mur2  = _mm512_load_ps(&pmur2[0]);
                     register __m512 mui2  = _mm512_load_ps(&pmui2[0]);
                     register __m512 epsr2 = _mm512_load_ps(&pepsr2[0]);
                     register __m512 epsi2 = _mm512_load_ps(&pepsi2[0]);
                     register __m512 z1r,z1i,z2r,z2i;
                     register __m512 t0r,t0i,t1r,t1i,resr,resi;
                     zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                     zi_f716_zmm16r4(tht2,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                     t0r = _mm512_sub_ps(z1r,z2r);
                     t1r = _mm512_add_ps(z1r,z2r);
                     t0i = _mm512_sub_ps(z1i,z2i);
                     t1i = _mm512_add_ps(z1i,z2i);
                     t0r = negate_zmm16r4(t0r);
                     t0i = negate_zmm16r4(t0i);
                     cdiv_zmm16r4(t0r,t0i,t1r,t1i,&resr,&resi);
                     _mm512_store_ps(&Rr[0], resr);
                     _mm512_store_ps(&Ri[0], resi);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f714_zmm16r4_u( const float * __restrict  ptht1,
                                        const float * __restrict  pmur1,
                                        const float * __restrict  pmui1,
                                        const float * __restrict  pepsr1,
                                        const float * __restrict  pepsi1,
                                        const float * __restrict  ptht2,
                                        const float * __restrict  pmur2,
                                        const float * __restrict  pmui2,
                                        const float * __restrict  pepsr2,
                                        const float * __restrict  pepsi2,
                                        float * __restrict  Rr,
                                        float * __restrict  Ri) {

                     using namespace gms::math;
                     register __m512 tht1  = _mm512_loadu_ps(&ptht1[0]);
                     register __m512 mur1  = _mm512_loadu_ps(&pmur1[0]);
                     register __m512 mui1  = _mm512_loadu_ps(&pmui1[0]);
                     register __m512 epsr1 = _mm512_loadu_ps(&pepsr1[0]);
                     register __m512 epsi1 = _mm512_loadu_ps(&pepsi1[0]);
                     register __m512 tht2  = _mm512_loadu_ps(&ptht2[0]);
                     register __m512 mur2  = _mm512_loadu_ps(&pmur2[0]);
                     register __m512 mui2  = _mm512_loadu_ps(&pmui2[0]);
                     register __m512 epsr2 = _mm512_loadu_ps(&pepsr2[0]);
                     register __m512 epsi2 = _mm512_loadu_ps(&pepsi2[0]);
                     register __m512 z1r,z1i,z2r,z2i;
                     register __m512 t0r,t0i,t1r,t1i,resr,resi;
                     zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                     zi_f716_zmm16r4(tht2,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                     t0r = _mm512_sub_ps(z1r,z2r);
                     t1r = _mm512_add_ps(z1r,z2r);
                     t0i = _mm512_sub_ps(z1i,z2i);
                     t1i = _mm512_add_ps(z1i,z2i);
                     t0r = negate_zmm16r4(t0r);
                     t0i = negate_zmm16r4(t0i);
                     cdiv_zmm16r4(t0r,t0i,t1r,t1i,&resr,&resi);
                     _mm512_storeu_ps(&Rr[0], resr);
                     _mm512_storeu_ps(&Ri[0], resi);
                }


                  /*
                        Transmission coefficient components.
                        Formula 7.1-5
                    */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void T_f715_zmm16r4( const __m512 tht1,
                                        const __m512 mur1,
                                        const __m512 mui1,
                                        const __m512 epsr1,
                                        const __m512 epsi1,
                                        const __m512 tht2,
                                        const __m512 mur2,
                                        const __m512 mui2,
                                        const __m512 epsr2,
                                        const __m512 epsi2,
                                        __m512 * __restrict Tr,
                                        __m512 * __restrict Ti) {

                     const __m512 _2 = _mm512_set1_ps(2.0f);
                     register __m512 z1r,z1i,z2r,z2i;
                     register __m512 t0r,t0i,t1r,t1i;
                     zi_f716_zmm16r4(tht2,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                     zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                     t0r = _mm512_mul_ps(_2,z2r);
                     t1r = _mm512_add_ps(z1r,z2r);
                     t0i = _mm512_mul_ps(_2,z2i);
                     t1i = _mm512_add_ps(z1i,z2i);
                     cdiv_zmm16r4(t0r,t0i,t1r,t1i,*Tr,*Ti);
             }


                /*
                        Reflection coefficient special cases:
                        1) k1<k2, eps1,eps2 (real), mu1 = m2 = mu0
                        Formula 7.1-17
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7117_zmm16r4(const __m512 tht,
                                          const __m512 eps1,
                                          const __m512 eps2) {

                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps1,eps2);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7117_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) peps1,
                                            const float * __restrict __ATTR_ALIGN__(64) peps2) {

                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 eps1= _mm512_load_ps(&peps1[0]);
                          register __m512 eps2= _mm512_load_ps(&peps2[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps1,eps2);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7117_zmm16r4_u(const float * __restrict  ptht,
                                            const float * __restrict  peps1,
                                            const float * __restrict  peps2) {

                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                          register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps1,eps2);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }


                   /*
                        Reflection coefficient special cases:
                        1) k1<k2, eps1,eps2 (real), mu1 = m2 = mu0
                        Formula 7.1-18
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7118_zmm16r4(const __m512 tht,
                                          const __m512 eps1,
                                          const __m512 eps2) {

                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps2,eps1);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7118_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) peps1,
                                            const float * __restrict __ATTR_ALIGN__(64) peps2) {

                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 eps1= _mm512_load_ps(&peps1[0]);
                          register __m512 eps2= _mm512_load_ps(&peps2[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps2,eps1);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 R_f7118_zmm16r4_u(const float * __restrict  ptht,
                                            const float * __restrict  peps1,
                                            const float * __restrict  peps2) {

                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                          register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 e1e2,sqr1,sqr2,num,den,R;
                          register __m512 cost,sint,x0,x1;
                          e1e2 = _mm512_div_ps(eps2,eps1);
                          cost = xcosf(tht);
                          sqr1 = _mm512_sqrt_ps(e1e2);
                          sint = xsinf(tht);
                          x0   = _mm512_mul_ps(sqr1,cost);
                          x1   = _mm512_mul_ps(_mm512_sub_ps(_1,e1e2),
                                                     _mm512_mul_ps(sint,sint));
                          sqr2 = _mm512_sqrt_ps(x1);
                          num  = _mm512_sub_ps(x0,x1);
                          den  = _mm512_add_ps(x0,x1);
                          R    = _mm512_div_ps(num,den);
                          return (R);
                }



                    /*
                        Reflection coefficient special cases:
                        2) k2<k1, eps1,eps2 (real), mu1 = mu2 = mu0
                        Formula 7.1-23
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7123_zmm16r4(const __m512 tht,
                                        const __m512 eps2,
                                        const __m512 eps1,
                                        __m512 * __restrict Rr,
                                        __m512 * __restrict Ri) {

                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        sint = xsinf(tht);
                        x0   = _mm512_mul_ps(cost,cost);
                        x1   = _mm512_sub_ps(_mm512_mul_ps(sint,sint),e2e1);
                        rat  = _mm512_div_ps(x1,x0);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        *Rr = cer;
                        *Ri = cei;
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7123_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) peps1,
                                            const float * __restrict __ATTR_ALIGN__(64) peps2
                                            float * __restrict __ATTR_ALIGN__(64) Rr,
                                            float * __restrict __ATTR_ALIGN__(64) Ri) {

                        register __m512 tht = _mm512_load_ps(&ptht[0]);
                        register __m512 eps1= _mm512_load_ps(&peps1[0]);
                        register __m512 eps2= _mm512_load_ps(&peps2[0]);
                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        sint = xsinf(tht);
                        x0   = _mm512_mul_ps(cost,cost);
                        x1   = _mm512_sub_ps(_mm512_mul_ps(sint,sint),e2e1);
                        rat  = _mm512_div_ps(x1,x0);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        _mm512_store_ps(&Rr[0] ,cer);
                        _mm512_store_ps(&Ri[0] ,cei);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7123_zmm16r4_u(  const float * __restrict  ptht,
                                            const float * __restrict  peps1,
                                            const float * __restrict  peps2
                                            float * __restrict  Rr,
                                            float * __restrict  Ri) {

                        register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                        register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                        register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        cost = xcosf(tht);
                        ear  = _mm512_setzero_ps();
                        sint = xsinf(tht);
                        x0   = _mm512_mul_ps(cost,cost);
                        x1   = _mm512_sub_ps(_mm512_mul_ps(sint,sint),e2e1);
                        rat  = _mm512_div_ps(x1,x0);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        _mm512_storeu_ps(&Rr[0] ,cer);
                        _mm512_storeu_ps(&Ri[0] ,cei);
                }


                    /*
                        Reflection coefficient special cases:
                        2) k2<k1, eps1,eps2 (real), mu1 = mu2 = mu0
                        Formula 7.1-24
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7124_zmm16r4(const __m512 tht,
                                        const __m512 eps2,
                                        const __m512 eps1,
                                        __m512 * __restrict Rr,
                                        __m512 * __restrict Ri) {

                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        const __m512 _1 = _mm512_set1_ps(1.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,e1e2,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        sint = xsinf(tht);
                        ear  = _mm512_setzero_ps();
                        cost = xcosf(tht);
                        x0   = _mm512_mul_ps(e2e1,_mm512_fmsub_ps(sint,sint,_1));
                        e1e2 = _mm512_div_ps(eps1,eps2);
                        x1   = _mm512_mul_ps(e1e2,_mm512_mul_ps(cost,cost));
                        rat  = _mm512_div_ps(x0,x1);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        *Rr  = cer;
                        *Ri  = cei;
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7124_zmm16r4_a(  const float * __restrict __ATTR_ALIGN__(64) ptht,
                                            const float * __restrict __ATTR_ALIGN__(64) peps1,
                                            const float * __restrict __ATTR_ALIGN__(64) peps2
                                            float * __restrict __ATTR_ALIGN__(64) Rr,
                                            float * __restrict __ATTR_ALIGN__(64) Ri) {

                        register __m512 tht = _mm512_load_ps(&ptht[0]);
                        register __m512 eps1= _mm512_load_ps(&peps1[0]);
                        register __m512 eps2= _mm512_load_ps(&peps2[0]);
                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        const __m512 _1 = _mm512_set1_ps(1.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,e1e2,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        sint = xsinf(tht);
                        ear  = _mm512_setzero_ps();
                        cost = xcosf(tht);
                        x0   = _mm512_mul_ps(e2e1,_mm512_fmsub_ps(sint,sint,_1));
                        e1e2 = _mm512_div_ps(eps1,eps2);
                        x1   = _mm512_mul_ps(e1e2,_mm512_mul_ps(cost,cost));
                        rat  = _mm512_div_ps(x0,x1);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        _mm512_store_ps(&Rr[0] ,cer);
                        _mm512_store_ps(&Ri[0] ,cei);
                }



                     __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7124_zmm16r4_u(  const float * __restrict  ptht,
                                            const float * __restrict  peps1,
                                            const float * __restrict  peps2
                                            float * __restrict  Rr,
                                            float * __restrict  Ri) {

                        register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                        register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                        register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                        const __m512 n2 = _mm512_set1_ps(-2.0f);
                        const __m512 _1 = _mm512_set1_ps(1.0f);
                        register __m512 ear,eai,cer,cei;
                        register __m512 sint,cost,e2e1,e1e2,rat,arg,atarg;
                        register __m512 x0,x1;
                        e2e1 = _mm512_div_ps(eps2,eps1);
                        sint = xsinf(tht);
                        ear  = _mm512_setzero_ps();
                        cost = xcosf(tht);
                        x0   = _mm512_mul_ps(e2e1,_mm512_fmsub_ps(sint,sint,_1));
                        e1e2 = _mm512_div_ps(eps1,eps2);
                        x1   = _mm512_mul_ps(e1e2,_mm512_mul_ps(cost,cost));
                        rat  = _mm512_div_ps(x0,x1);
                        arg  = _mm512_sqrt_ps(rat);
                        atarg= xatanf(arg);
                        eai  = _mm512_mul_ps(n2,atarg);
                        cexp_zmm16r4(ear,eai,&cer,&cei);
                        _mm512_storeu_ps(&Rr[0] ,cer);
                        _mm512_storeu_ps(&Ri[0] ,cei);
                }


                  /*
                       Lateral displacement of the incident ray.
                       Formula 7.1-27
                   */

                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7127_zmm16r4(    const __m512 gam0,
                                              const __m512 tht,
                                              const __m512 eps2,
                                              const __m512 eps1) {

                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,rat);
                         return (D);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7127_zmm16r4_a(    const float * __restrict __ATTR_ALIGN__(64)  pgam0,
                                                const float * __restrict __ATTR_ALIGN__(64)  ptht,
                                                const float * __restrict __ATTR_ALIGN__(64)  peps2,
                                                const float * __restrict __ATTR_ALIGN__(64)  peps1) {

                         register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                         register __m512 tht = _mm512_load_ps(&ptht[0]);
                         register __m512 eps1= _mm512_load_ps(&peps1[0]);
                         register __m512 eps2= _mm512_load_ps(&peps2[0]);
                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,rat);
                         return (D);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7127_zmm16r4_u(    const float * __restrict   pgam0,
                                                const float * __restrict   ptht,
                                                const float * __restrict   peps2,
                                                const float * __restrict   peps1) {

                         register __m512 gam0= _mm512_loadu_ps(&pgam0[0]);
                         register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                         register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                         register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,rat);
                         return (D);
                }


                    /*
                       Lateral displacement of the incident ray.
                       Formula 7.1-28
                   */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7128_zmm16r4(    const __m512 gam0,
                                              const __m512 tht,
                                              const __m512 eps2,
                                              const __m512 eps1) {

                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,e1e2,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         e1e2 = _mm512_div_ps(eps1,eps2);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,_mm512_mul_ps(e1e2,rat));
                         return (D);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7128_zmm16r4_a(    const float * __restrict __ATTR_ALIGN__(64)  pgam0,
                                                const float * __restrict __ATTR_ALIGN__(64)  ptht,
                                                const float * __restrict __ATTR_ALIGN__(64)  peps2,
                                                const float * __restrict __ATTR_ALIGN__(64)  peps1) {

                         register __m512 gam0= _mm512_load_ps(&pgam0[0]);
                         register __m512 tht = _mm512_load_ps(&ptht[0]);
                         register __m512 eps1= _mm512_load_ps(&peps1[0]);
                         register __m512 eps2= _mm512_load_ps(&peps2[0]);
                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,e1e2,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         e1e2 = _mm512_div_ps(eps1,eps2);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,_mm512_mul_ps(e1e2,rat));
                         return (D);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 D_f7128_zmm16r4_u(    const float * __restrict   pgam0,
                                                const float * __restrict   ptht,
                                                const float * __restrict   peps2,
                                                const float * __restrict   peps1) {

                         register __m512 gam0= _mm512_loadu_ps(&pgam0[0]);
                         register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                         register __m512 eps1= _mm512_loadu_ps(&peps1[0]);
                         register __m512 eps2= _mm512_loadu_ps(&peps2[0]);
                         const __m512 invpi = _mm512_set1_ps(0.318309886183790671537767526745f);
                         register __m512 g0pi,ttht,sint,e2e1,e1e2,sqr,rat;
                         register __m512 D;
                         g0pi = _mm512_mul_ps(gam0,invpi);
                         e2e1 = _mm512_div_ps(eps2,eps1);
                         ttht = xtanf(tht);
                         sint = _mm512_fmsub_ps(sint,sint,e2e1);
                         e1e2 = _mm512_div_ps(eps1,eps2);
                         sqr  = _mm512_sqrt_ps(sint);
                         rat  = _mm512_div_ps(ttht,sqr);
                         D    = _mm512_mul_ps(g0pi,_mm512_mul_ps(e1e2,rat));
                         return (D);
                }


                      /*
                             For (k1/k2)^2*sin^2(theta)<<1 (Simplification
                             of formulae 7.1-9 and 7.1-10).
                             Formula 7.1-29
                        */


                    
                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7129_zmm16r4(const __m512 tht,
                                        const __m512 mur1,
                                        const __m512 mui1,
                                        const __m512 epsr1,
                                        const __m512 epsi1,
                                        const __m512 mur2,
                                        const __m512 mui2,
                                        const __m512 epsr2,
                                        const __m512 epsi2,
                                        __m512 * __restrict Rr,
                                        __m512 * __restrict Ri) {

                       register __m512 z1r,z1i,z2r,z2i;
                       register __m512 cost,numr,numi,denr,deni;
                       register __m512 resr,resi;
                       zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                       cost = xcosf(tht);
                       zi_f716_zmm16r4(tht1,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                       numr = _mm512_fmsub_ps(z2r,cost,z1r);
                       denr = _mm512_fmadd_ps(z2r,cost,z2r);
                       numi = _mm512_fmsub_ps(z2i,cost,z1i);
                       deni = _mm512_fmadd_ps(z2i,cost,z2i);
                       cdiv_zmm16r4(numr,numi,denr,deni,&resr,&resi);
                       *Rr = resr;
                       *Ri = resi;
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7129_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur1,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui1,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr1,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi1,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur2,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui2,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr2,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi2,
                                          float * __restrict __ATTR_ALIGN__(64) Rr,
                                          float * __restrict __ATTR_ALIGN__(64) Ri) {

                       register __m512 tht  = _mm512_load_ps(&ptht[0]);
                       register __m512 mur1  = _mm512_load_ps(&pmur1[0]);
                       register __m512 mui1  = _mm512_load_ps(&pmui1[0]);
                       register __m512 epsr1 = _mm512_load_ps(&pepsr1[0]);
                       register __m512 epsi1 = _mm512_load_ps(&pepsi1[0]);
                       register __m512 mur2  = _mm512_load_ps(&pmur2[0]);
                       register __m512 mui2  = _mm512_load_ps(&pmui2[0]);
                       register __m512 epsr2 = _mm512_load_ps(&pepsr2[0]);
                       register __m512 epsi2 = _mm512_load_ps(&pepsi2[0]);
                       register __m512 z1r,z1i,z2r,z2i;
                       register __m512 cost,numr,numi,denr,deni;
                       register __m512 resr,resi;
                       zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                       cost = xcosf(tht);
                       zi_f716_zmm16r4(tht1,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                       numr = _mm512_fmsub_ps(z2r,cost,z1r);
                       denr = _mm512_fmadd_ps(z2r,cost,z2r);
                       numi = _mm512_fmsub_ps(z2i,cost,z1i);
                       deni = _mm512_fmadd_ps(z2i,cost,z2i);
                       cdiv_zmm16r4(numr,numi,denr,deni,&resr,&resi);
                       *Rr = resr;
                       *Ri = resi;
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7129_zmm16r4_u(const float * __restrict  ptht,
                                          const float * __restrict  pmur1,
                                          const float * __restrict  pmui1,
                                          const float * __restrict  pepsr1,
                                          const float * __restrict  pepsi1,
                                          const float * __restrict  pmur2,
                                          const float * __restrict  pmui2,
                                          const float * __restrict  pepsr2,
                                          const float * __restrict  pepsi2,
                                          float * __restrict  Rr,
                                          float * __restrict  Ri) {

                       register __m512 tht  = _mm512_loadu_ps(&ptht[0]);
                       register __m512 mur1  = _mm512_loadu_ps(&pmur1[0]);
                       register __m512 mui1  = _mm512_loadu_ps(&pmui1[0]);
                       register __m512 epsr1 = _mm512_loadu_ps(&pepsr1[0]);
                       register __m512 epsi1 = _mm512_loadu_ps(&pepsi1[0]);
                       register __m512 mur2  = _mm512_loadu_ps(&pmur2[0]);
                       register __m512 mui2  = _mm512_loadu_ps(&pmui2[0]);
                       register __m512 epsr2 = _mm512_loadu_ps(&pepsr2[0]);
                       register __m512 epsi2 = _mm512_loadu_ps(&pepsi2[0]);
                       register __m512 z1r,z1i,z2r,z2i;
                       register __m512 cost,numr,numi,denr,deni;
                       register __m512 resr,resi;
                       zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                       cost = xcosf(tht);
                       zi_f716_zmm16r4(tht1,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                       numr = _mm512_fmsub_ps(z2r,cost,z1r);
                       denr = _mm512_fmadd_ps(z2r,cost,z2r);
                       numi = _mm512_fmsub_ps(z2i,cost,z1i);
                       deni = _mm512_fmadd_ps(z2i,cost,z2i);
                       cdiv_zmm16r4(numr,numi,denr,deni,&resr,&resi);
                       *Rr = resr;
                       *Ri = resi;
                }


                  /*
                             For (k1/k2)^2*sin^2(theta)<<1 (Simplification
                             of formulae 7.1-9 and 7.1-10).
                             Formula 7.1-30

                     */

   
                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7130_zmm16r4(const __m512 tht,
                                        const __m512 mur1,
                                        const __m512 mui1,
                                        const __m512 epsr1,
                                        const __m512 epsi1,
                                        const __m512 mur2,
                                        const __m512 mui2,
                                        const __m512 epsr2,
                                        const __m512 epsi2,
                                        __m512 * __restrict Rr,
                                        __m512 * __restrict Ri) {

                       register __m512 z1r,z1i,z2r,z2i;
                       register __m512 cost,numr,numi,denr,deni;
                       register __m512 resr,resi,t0r,t0i;
                       zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                       cost = xcosf(tht);
                       t0r  = _mm512_mul_ps(z1r,cost);
                       t0i  = _mm512_mul_ps(z1i,cost);
                       zi_f716_zmm16r4(tht1,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                       numr = _mm512_sub_ps(z2r,t0r);
                       denr = _mm512_add_ps(z2r,t0r);
                       numi = _mm512_sub_ps(z2i,t0i);
                       deni = _mm512_add_ps(z2i,t0i);
                       cdiv_zmm16r4(numr,numi,denr,deni,&resr,&resi);
                       *Rr = resr;
                       *Ri = resi;
               }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   void R_f7130_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) ptht,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur1,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui1,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr1,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi1,
                                          const float * __restrict __ATTR_ALIGN__(64) pmur2,
                                          const float * __restrict __ATTR_ALIGN__(64) pmui2,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsr2,
                                          const float * __restrict __ATTR_ALIGN__(64) pepsi2,
                                          float * __restrict __ATTR_ALIGN__(64) Rr,
                                          float * __restrict __ATTR_ALIGN__(64) Ri) {

                       register __m512 tht   = _mm512_load_ps(&ptht[0]);
                       register __m512 mur1  = _mm512_load_ps(&pmur1[0]);
                       register __m512 mui1  = _mm512_load_ps(&pmui1[0]);
                       register __m512 epsr1 = _mm512_load_ps(&pepsr1[0]);
                       register __m512 epsi1 = _mm512_load_ps(&pepsi1[0]);
                       register __m512 mur2  = _mm512_load_ps(&pmur2[0]);
                       register __m512 mui2  = _mm512_load_ps(&pmui2[0]);
                       register __m512 epsr2 = _mm512_load_ps(&pepsr2[0]);
                       register __m512 epsi2 = _mm512_load_ps(&pepsi2[0]);

                       register __m512 z1r,z1i,z2r,z2i;
                       register __m512 cost,numr,numi,denr,deni;
                       register __m512 resr,resi,t0r,t0i;
                       zi_f716_zmm16r4(tht1,mur1,mui1,epsr1,epsi1,&z1r,&z1i);
                       cost = xcosf(tht);
                       t0r  = _mm512_mul_ps(z1r,cost);
                       t0i  = _mm512_mul_ps(z1i,cost);
                       zi_f716_zmm16r4(tht1,mur2,mui2,epsr2,epsi2,&z2r,&z2i);
                       numr = _mm512_sub_ps(z2r,t0r);
                       denr = _mm512_add_ps(z2r,t0r);
                       numi = _mm512_sub_ps(z2i,t0i);
                       deni = _mm512_add_ps(z2i,t0i);
                       cdiv_zmm16r4(numr,numi,denr,deni,&resr,&resi);
                       _mm512_store_ps(&Rr[0] ,resr);
                       _mm512_store_ps(&Ri[0] ,resi);
               }



      } // radiolocation


} // gms


























#endif /*__GMS_RCS_PLANAR_SURF_ZMM16R4_HPP__*/