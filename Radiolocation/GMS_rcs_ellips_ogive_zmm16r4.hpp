

#ifndef __GMS_RCS_ELLIPS_OGIVE_ZMM16R4_HPP__
#define __GMS_RCS_ELLIPS_OGIVE_ZMM16R4_HPP__ 010320230919


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

    const unsigned int GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MAJOR = 1U;
    const unsigned int GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MINOR = 0U;
    const unsigned int GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MICRO = 0U;
    const unsigned int GMS_RCS_ELLIPS_OGIVE_ZMM16R4_FULLVER =
      1000U*GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MAJOR+
      100U*GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MINOR+
      10U*GMS_RCS_ELLIPS_OGIVE_ZMM16R4_MICRO;
    const char * const GMS_RCS_ELLIPS_OGIVE_ZMM16R4_CREATION_DATE = "01-03-2023 09:18 AM +00200 (WED 01 MAR 2023 GMT+2)";
    const char * const GMS_RCS_ELLIPS_OGIVE_ZMM16R4_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const GMS_RCS_ELLIPS_OGIVE_ZMM16R4_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const GMS_RCS_ELLIPS_OGIVE_ZMM16R4_DESCRIPTION   = "AVX512 optimized Ellipsoid and Ogive Radar Cross Section (analytic) functionality.";

}

#include <cstdint>
#include <immintrin.h>
#include "GMS_config.h"
#include "GMS_sleefsimdsp.hpp"


namespace gms {


          namespace radiolocation {


                      /*
                            High-frequency cross-section of perfectly
                            conducting ellipsoid.
                            Bistatic case.
                            Formula 5.1.54
                        */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5154_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 c,
                                            const __m512 th1,
                                            const __m512 phi1,
                                            const __m512 th2,
                                            const __m512 phi2) {

                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5154_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pc,
                                            const float * __restrict __ATTR_ALIGN__(64) pth1,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                            const float * __restrict __ATTR_ALIGN__(64) pth2,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi2) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 th1 = _mm512_load_ps(&pth1[0]);
                          register __m512 phi1= _mm512_load_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_load_ps(&pth2[0]);
                          register __m512 phi2= _mm512_load_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5154_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pc,
                                            const float * __restrict  pth1,
                                            const float * __restrict  pphi1,
                                            const float * __restrict  pth2,
                                            const float * __restrict  pphi2) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 th1 = _mm512_loadu_ps(&pth1[0]);
                          register __m512 phi1= _mm512_loadu_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_loadu_ps(&pth2[0]);
                          register __m512 phi2= _mm512_loadu_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,c2,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          c2   = _mm512_mul_ps(c,c);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(c2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                       /*
                            High-frequency cross-section of perfectly
                            conducting ellipsoid.
                            Backscattering case.
                            Formula 5.1.55
                        */ 


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5155_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 c,
                                            const __m512 th,
                                            const __m512 phi) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                     __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5155_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) pth,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi) {
                                           
                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 th  = _mm512_load_ps(&pth[0]);
                          register __m512 phi = _mm512_load_ps(&pphi[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                  __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5155_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pb,
                                              const float * __restrict  pc,
                                              const float * __restrict  pth,
                                              const float * __restrict  pphi) {
                                           
                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 th  = _mm512_loadu_ps(&pth[0]);
                          register __m512 phi = _mm512_loadu_ps(&pphi[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,c2,sphi,sphis,cth,cths,sth,sths,cphi,cphis;
                          register __m512 num,x0,trm1;
                          a2  = _mm512_mul_ps(a,a);
                          sphi= xsinf(phi);
                          b2  = _mm512_mul_ps(b,b);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          cth = xcosf(th);
                          c2  = _mm512_mul_ps(c,c);
                          cths= _mm512_mul_ps(cth,cth);
                          sth = xsinf(th);
                          num = _mm512_mul_ps(a2,_mm512_mul_ps(b2,c2));
                          sths= _mm512_mul_ps(sth,sth);
                          cphi= xcosf(phi);
                          cphis= _mm512_mul_ps(cphi,cphi);
                          trm1 = _mm512_fmadd_ps(_mm512_mul_ps(a2,sths),cphis,
                                                 _mm512_fmadd_ps(_mm512_mul_ps(b2,sths),
                                                                 _mm512_mul_ps(c2,cths)));
                          x0   = _mm512_mul_ps(trm1,trm1);
                          rcs  = _mm512_div_ps(num,x0);
                          return (rcs);
                }


                    /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Bistatic case.
                           Formula 5.1-67
                        */

                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5167_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 th1,
                                            const __m512 phi1,
                                            const __m512 th2,
                                            const __m512 phi2) {

                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5167_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pb,
                                              const float * __restrict __ATTR_ALIGN__(64) pth1,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi1,
                                              const float * __restrict __ATTR_ALIGN__(64) pth2,
                                              const float * __restrict __ATTR_ALIGN__(64) pphi2) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 th1 = _mm512_load_ps(&pth1[0]);
                          register __m512 phi1= _mm512_load_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_load_ps(&pth2[0]);
                          register __m512 phi2= _mm512_load_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5167_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pb,
                                              const float * __restrict  pth1,
                                              const float * __restrict  pphi1,
                                              const float * __restrict  pth2,
                                              const float * __restrict  pphi2) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 th1 = _mm512_loadu_ps(&pth1[0]);
                          register __m512 phi1= _mm512_loadu_ps(&pphi1[0]);
                          register __m512 th2 = _mm512_loadu_ps(&pth2[0]);
                          register __m512 phi2= _mm512_loadu_ps(&pphi2[0]);
                          const __m512 _4pi = _mm512_set1_ps(12.566370614359172953850573533118f);
                          register __m512 rcs,a2,b2,b4,sth1,cphi1,sth2,cphi2,cth1,cth2;
                          register __m512 trm1,trm2,trm3,num,den,x0,strm1,strm2,strm3;
                          a2   = _mm512_mul_ps(a,a);
                          sth1 = xsinf(phi1);
                          b2   = _mm512_mul_ps(b,b);
                          cphi1= xcosf(phi1);
                          b4   = _mm512_mul_ps(b2,b2);
                          sth2 = xsinf(th2);
                          x0   = _mm512_mul_ps(a2,b4);
                          cphi2= xcosf(phi2);
                          num  = _mm512_mul_ps(_4pi,x0);
                          cth1 = xcosf(th1);
                          trm1 = _mm512_fmadd_ps(sth1,cphi1,_mm512_mul_ps(sth2,cphi2));
                          strm1= _mm512_mul_ps(a2,_mm512_mul_ps(trm1,trm1));
                          cth2 = xcosf(th2);
                          trm2 = _mm512_fmadd_ps(sth1,sphi1,_mm512_mul_ps(sth2,sphi2));
                          strm2= _mm512_mul_ps(b2,_mm512_mul_ps(trm2,trm2));
                          trm3 = _mm512_mul_ps(cth1,cth2);
                          strm3= _mm512_mul_ps(b2,_mm512_mul_ps(trm3,trm3));
                          x0   = _mm512_add_ps(strm1,_mm512_add_ps(strm2,strm3));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                 }


                  /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Backscatter case.
                           Formula 5.1-68
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5168_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 phi) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5168_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pphi) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 phi = _mm512_load_ps(&pph1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                  __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5168_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pphi) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 phi = _mm512_loadu_ps(&pph1[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          register __m512 rcs,a2,b2,b4,num,x0;
                          register __m512 cphi,cphis,sphi,sphis,den;
                          a2   = _mm512_mul_ps(a,a);
                          cphi = xcosf(phi);
                          b2   = _mm512_mul_ps(b,b);
                          sphi = xsinf(phi);
                          b4   = _mm512_mul_ps(b2,b2);
                          num  = _mm512_mul_ps(pi,_mm512_mul_ps(a2,b4));
                          cphis= _mm512_mul_ps(cphi,cphi);
                          sphis= _mm512_mul_ps(sphi,sphi);
                          x0   = _mm512_fmadd_ps(a2,cphis,_mm512_mul_ps(b2,sphis));
                          den  = _mm512_mul_ps(x0,x0);
                          rcs  = _mm512_div_ps(num,den);
                          return (rcs);
                }


                    /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Incidence along a the major axis -- the backscatter RCS.
                           Formula 5.1-69
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5169_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5169_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5169_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict pb,
                                            const float * __restrict  pk0) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,b4,k0a,k02a2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0a  = _mm512_mul_ps(k0,a);
                          arg  = _mm512_add_ps(k0a,k0a);
                          b2   = _mm512_mul_ps(b,b);
                          k02a2= _mm512_mul_ps(a2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          b4   = _mm512_mul_ps(b2,b2);
                          trm1 = _mm512_div_ps(_mm512_mul_ps(pi,b4),a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02a2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                  /*
                           High frequency solutions.
                           Perfectly conducting spheroids.
                           Incidence along a the minor axis -- the backscatter RCS.
                           Formula 5.1-70

                    */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5170_zmm16r4(const __m512 a,
                                            const __m512 b,
                                            const __m512 k0) {

                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                     __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5170_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                            const float * __restrict __ATTR_ALIGN__(64) pb,
                                            const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 b   = _mm512_load_ps(&pb[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5170_zmm16r4_u(const float * __restrict  pa,
                                            const float * __restrict  pb,
                                            const float * __restrict  pk0) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 b   = _mm512_loadu_ps(&pb[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 pi = _mm512_set1_ps(3.14159265358979323846264338328f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 rcs,a2,b2,k0b,k02b2,arg,sarg;
                          register __m512 trm1,trm2,trm3,x0;  
                          a2   = _mm512_mul_ps(a,a);
                          k0b  = _mm512_mul_ps(k0,b);
                          arg  = _mm512_add_ps(k0b,k0b);
                          b2   = _mm512_mul_ps(b,b);
                          k02b2= _mm512_mul_ps(b2,_mm512_mul_ps(k0,k0));
                          sarg = xsinf(arg);
                          trm1 = _mm512_mul_ps(pi,a2);
                          x0   = _mm512_mul_ps(sarg,sarg);
                          trm2 = _mm512_sub_ps(_1,_mm512_div_ps(sarg,arg));
                          trm3 = _mm512_div_ps(x0,k02b2);
                          rcs  = _mm512_mul_ps(trm1,_mm512_add_ps(trm2,trm3));
                          return (rcs);
                }


                   /*
                         Oblate spheroids.
                         Low frequency solutions.
                         Helper parameters: Ia,Ib
                         Formula 5.1-91
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 IaIb_f5191_zmm16r4(const __m512 a,
                                             const __m512 c) {

                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 IaIb_f5191_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                               const float * __restrict __ATTR_ALIGN__(64) pc) {

                          register __m512 a = _mm512_load_ps(&pa[0]);
                          register __m512 c = _mm512_load_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 IaIb_f5191_zmm16r4_u(const float * __restrict  pa,
                                               const float * __restrict  pc) {

                          register __m512 a = _mm512_loadu_ps(&pa[0]);
                          register __m512 c = _mm512_loadu_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 IaIb,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(_1,_mm512_add_ps(e2m1,e2m1));
                          x0   = _mm512_mul_ps(e2,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          asarg= _mm512_sub_ps(asarg,_1);
                          IaIb = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (IaIb);
                 }


                     /*
                         Oblate spheroids.
                         Low frequency solutions.
                         Helper parameters: Ia,Ib
                         Formula 5.1-92
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 Ic_f5192_zmm16r4(const __m512 a,
                                             const __m512 c) {

                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 Ic_f5192_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                           const float * __restrict __ATTR_ALIGN__(64) pc) {

                          register __m512 a = _mm512_load_ps(&pa[0]);
                          register __m512 c = _mm512_load_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 Ic_f5192_zmm16r4_u(const float * __restrict  pa,
                                           const float * __restrict  pc) {

                          register __m512 a = _mm512_loadu_ps(&pa[0]);
                          register __m512 c = _mm512_loadu_ps(&pc[0]);
                          const __m512 _2 = _mm512_set1_ps(2.0f);
                          const __m512 _1 = _mm512_set1_ps(1.0f);
                          register __m512 Ic,e,a2c,arg,asarg,e2m1s;
                          register __m512 trm1,trm2,trm3,e2m1,x0,x1;
                          e    = _mm512_div_ps(a,c);
                          a2c  = _mm512_mul_ps(c,_mm512_mul_ps(a,a));
                          e2   = _mm512_mul_ps(e,e);
                          trm1 = _mm512_div_ps(_2,a2c);
                          e2m1 = _mm512_sub_ps(e2,_1);
                          trm2 = _mm512_div_ps(e2,e2m1,e2m1);
                          x0   = _mm512_sub_ps(_1,e2m1);
                          e2m1s= _mm512_sqrt_ps(e2m1);
                          arg  = _mm512_div_ps(e2m1s,e);
                          x1   = _mm512_sqrt_ps(x0);
                          asarg= _mm512_asin_ps(arg);
                          trm3 = _mm512_rcp14_ps(x1);
                          Ic   = _mm512_mul_ps(_mm512_mul_ps(trm1,trm2),
                                               _mm512_mul_ps(trm3,asarg));
                          return (Ic);
                 }


                   /*
                         Oblate spheroids (perfectly conducting);
                         Low frequency solutions.
                         Backscatter RCS.
                         Formula 5.1-89
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5189_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht,
                                            const __m512 k0) {

                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5189_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0 ) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                    __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5189_zmm16r4_u(const float * __restrict  pa,
                                              const float * __restrict  pc,
                                              const float * __restrict  ptht,
                                              const float * __restrict  pk0 ) {

                          register __m512 a   = _mm512_loadu_ps(&pa[0]);
                          register __m512 c   = _mm512_loadu_ps(&pc[0]);
                          register __m512 tht = _mm512_loadu_ps(&ptht[0]);
                          register __m512 k0  = _mm512_loadu_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 hlf = _mm512_set1_ps(0.5f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,trm23,trm1,IaIc,x1;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          x0   = _mm512_fmadd_ps(stht2,hlf,_1);
                          trm3 = _mm512_div_ps(ctht2,IaIc);
                          trm2 = _mm512_div_ps(x0,Ia);
                          x1   = _mm512_add_ps(trm2,trm3);
                          trm23= _mm512_mul_ps(x1,x1);
                          rcs  = _mm512_mul_ps(trm1,trm23);
                          return (rcs);
                 }


                     /*
                         Oblate spheroids (perfectly conducting);
                         Low frequency solutions.
                         Backscatter RCS.
                         Formula 5.1-90
                     */


                   __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5190_zmm16r4(const __m512 a,
                                            const __m512 c,
                                            const __m512 tht,
                                            const __m512 k0) {

                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,strm,trm1,IaIc,x1,inv;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          inv  = _mm512_rcp14_ps(IaIc);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          trm2 = _mm512_div_ps(ctht2,Ia);
                          trm3 = _mm512_div_ps(stht3,Ic);
                          strm = _mm512_add_ps(trm2,trm3);
                          x1   = _mm512_mul_ps(strm,strm);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 } 


                  __ATTR_ALWAYS_INLINE__
	           __ATTR_HOT__
	           __ATTR_ALIGN__(32)
                   __ATTR_VECTORCALL__
	           static inline
                   __m512 rcs_f5190_zmm16r4_a(const float * __restrict __ATTR_ALIGN__(64) pa,
                                              const float * __restrict __ATTR_ALIGN__(64) pc,
                                              const float * __restrict __ATTR_ALIGN__(64) ptht,
                                              const float * __restrict __ATTR_ALIGN__(64) pk0) {

                          register __m512 a   = _mm512_load_ps(&pa[0]);
                          register __m512 c   = _mm512_load_ps(&pc[0]);
                          register __m512 tht = _mm512_load_ps(&ptht[0]);
                          register __m512 k0  = _mm512_load_ps(&pk0[0]);
                          const __m512 _1  = _mm512_set1_ps(1.0f);
                          const __m512 ptrm= _mm512_set1_ps(5.585053606381854646155810459164f);
                          register __m512 rcs,Ia,Ic,k04,x0,stht,ctht,stht2,ctht2,trm1;
                          register __m512 trm2,trm3,strm,trm1,IaIc,x1,inv;
                          x0   = _mm512_mul_ps(k0,k0);
                          Ia   = IaIb_f5191_zmm16r4(a,c);
                          k04  = _mm512_mul_ps(x0,x0);
                          Ic   = Ic_f5192_zmm16r4(a,c);
                          trm1 = _mm512_mul_ps(k04,ptrm);
                          stht = xsinf(tht); 
                          IaIc = _mm512_add_ps(Ia,Ic);
                          inv  = _mm512_rcp14_ps(IaIc);
                          ctht = xcosf(tht);
                          stht2= _mm512_mul_ps(stht,stht);
                          ctht2= _mm512_mul_ps(ctht,ctht);
                          trm2 = _mm512_div_ps(ctht2,Ia);
                          trm3 = _mm512_div_ps(stht3,Ic);
                          strm = _mm512_add_ps(trm2,trm3);
                          x1   = _mm512_mul_ps(strm,strm);
                          rcs  = _mm512_mul_ps(trm1,x1);
                          return (rcs);
                 } 


                   /*
                          Low-frequency oblate spheroid Rayleigh
                          bistatic scattered fields.
                          E-field, formula 5.1-83
                    */

                 



                   

       }



}














#endif /*__GMS_RCS_ELLIPS_OGIVE_ZMM16R4_HPP__*/