

#ifndef __GMS_POSTPROCESS_SKX_CLK_HW_METRICS_HPP__
#define __GMS_POSTPROCESS_SKX_CLK_HW_METRICS_HPP__ 150820230813


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

    const unsigned int GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MAJOR = 1U;
    const unsigned int GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MINOR = 0U;
    const unsigned int GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MICRO = 0U;
    const unsigned int GMS_POSTPROCESS_SKX_CLK_HW_METRICS_FULLVER =
      1000U*GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MAJOR+
      100U*GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MINOR+
      10U*GMS_POSTPROCESS_SKX_CLK_HW_METRICS_MICRO;
    const char * const GMS_POSTPROCESS_SKX_CLK_HW_METRICS_CREATION_DATE = "15-08-2023 08:13 PM +00200 (TUE 15 AUG 2023 GMT+2)";
    const char * const GMS_POSTPROCESS_SKX_CLK_HW_METRICS_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const GMS_POSTPROCESS_SKX_CLK_HW_METRICS_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const GMS_POSTPROCESS_SKX_CLK_HW_METRICS_DESCRIPTION   = "Postprocessing (time-series analysis) of SKX and CLK HW metrics";

}

#include <cstdint>
#include "GMS_config.h"
#include "GMS_malloc.h"
#include "GMS_preprocess_skx_clk_hw_metrics.h"
#include "GMS_cpu_perf_time_series_analysis.h"
#include "GMS_pmc_events_descriptive_stats.hpp"


namespace gms {

  
           /*
                   CPU operating frequency (in GHz)
           */
        
        template<int32_t len, int32_t lagh>
        struct   SKX_cpu_operating_freq_t __ATTR_ALIGN__(64) {
        
                 __ATTR_ALIGN__(8) double * __restrict m_cpu_clk_unhalted_thread;
                 __ATTR_ALIGN__(8) double * __restrict m_cpu_clk_unhalted_ref_tsc;
                 __ATTR_ALIGN__(8) double * __restrict m_tsc_frequency;
                 __ATTR_ALIGN__(8) double * __restrict m_cpu_op_freq;
                            
                 
                 SKX_cpu_operating_freq_t() noexcept(true) {
                      
                      m_cpu_clk_unhalted_thread   = nullptr;
                      m_cpu_clk_unhalted_ref_tsc  = nullptr;
                      m_tsc_frequency             = nullptr;
                      m_cpu_op_freq               = nullptr;
               }
               
               SKX_cpu_operating_freq_t() noexcept(false) {
                      
                      using namespace gms::common;
                      const std::size_t samp_len = (std::size_t)len;
                      const std::size_t align    = (std::size_t)64;
                      m_cpu_clk_unhalted_thread  = (double*)gms_mm_malloc(samp_len,
                                                                          align);
                      m_cpu_clk_unhalted_ref_tsc = (double*)gms_mm_malloc(samp_len,
                                                                          align);
                      m_tsc_frequency            = (double*)gms_mm_malloc(samp_len,
                                                                          align);
                      m_cpu_op_freq              = (double*)gms_mm_malloc(samp_len,
                                                                          align);
               }
               
               SKX_cpu_operating_freq_t(const SKX_cpu_operating_freq_t &) = delete;
               
               SKX_cpu_operating_freq_t(SKX_cpu_operating_freq_t &&) = delete
               
               ~SKX_cpu_operating_freq_t() {
                     
                     using namespace gms::common;
                     if(__builtin_expect(nullptr!=
                        m_cpu_clk_unhalted_thread,0))  gms_mm_free(m_cpu_clk_unhalted_thread);
                     if(__builtin_expect(nullptr!=
                        m_cpu_clk_unhalted_ref_tsc,0)) gms_mm_free(m_cpu_clk_unhalted_ref_tsc);
                     if(__builtin_expect(nullptr!=
                        m_tsc_frequency,0))            gms_mm_free(m_tsc_frequency);
                     if(__builtin_expect(nullptr!=
                        m_cpu_op_freq,0))              gms_mm_free(m_cpu_op_freq);
               }     
               
               
               SKX_cpu_operating_freq_t &
               operator=(const SKX_cpu_operating_freq_t &) = delete;
               
               SKX_cpu_operating_freq_t &
               operator=(SKX_cpu_operating_freq_t &&) = delete;  
               
               void compute_metric() {
                    
                    skx_cpu_operating_freq_samples(m_cpu_clk_unhalted_thread,
                                                   m_cpu_clk_unhalted_ref_tsc,
                                                   m_tsc_frequency,
                                                   m_cpu_op_freq,
                                                   len);
               }     
               
               void analyze_metric_canarm(const char * __restrict fname,
                                          const char * __restrict data_type,
                                          const bool use_omp) {
                   
                    cpu_perf_time_series_canarm<len,lagh>(m_cpu_op_freq,fname,
                                                          data_type,use_omp);
                                                                            
             }  
             
             void analyze_metric_unimar(const char * __restrict fname,
                                        const char * __restrict data_type) {
                 
                    cpu_perf_time_series_unimar<len,lagh>(m_cpu_op_freq,
                                                          fname,data_type);                           
            } 
            
            void analyze_metric_unibar(const char * __restrict fname,
                                       const char * __restrict data_type) {
                                       
                    cpu_perf_time_series_unibar<len,lagh>(m_cpu_op_freq,
                                                          fname,data_type);                           
           }    
           
           void analyze_metric_exsar(const char * __restrict fname,
                                     const char * __restrict data_type) {
                                     
                    cpu_perf_time_series_exsar<len,lagh>(m_cpu_op_freq,
                                                         fname,data_type);                       
           }
           
           void analyze_metric_bispec(const char * __restrict fname,
                                      const char * __restrict data_type,
                                      const bool use_omp) {
                                      
                    cpu_perf_time_series_bispec<len,lagh>(m_cpu_op_freq,
                                                          fname,data_type,use_omp);                          
           }
           
           void analyze_metric_thirmo(const char * __restrict fname,
                                      const char * __restrict data_type) {
                                      
                    cpu_perf_time_series_thirmo<len,lagh>(m_cpu_op_freq,
                                                          fname,data_type);                
           }
           
           void analyze_metric_autocor(const char * __restrict fname,
                                       const char * __restrict data_type) {
                                       
                    cpu_perf_time_series_autocor<len,lagh>(m_cpu_op_freq,
                                                           fname,data_type);                            
          }
          
       
               
      };
      
      
      //////////////////////////////////////////////////////////////////////////////
      
      /*
            CPU utilization (percentage) all cores.
       */
       
         template<int32_t len, int32_t lagh>
         struct   SKX_cpu_utilization_t __ATTR_ALIGN__(64) {
        
                
                 __ATTR_ALIGN__(8) double * __restrict m_cpu_clk_unhalted_ref_tsc;
                 __ATTR_ALIGN__(8) double * __restrict m_tsc_frequency;
                 __ATTR_ALIGN__(8) double * __restrict m_cpu_util;
                            
                 
                 SKX_cpu_utilization_t() noexcept(true) {
                      
                  
                      m_cpu_clk_unhalted_ref_tsc  = nullptr;
                      m_tsc_frequency             = nullptr;
                      m_cpu_op_util               = nullptr;
               }
               
                 SKX_cpu_utilization_t() noexcept(false) {
                      
                      using namespace gms::common;
                      const std::size_t samp_len = (std::size_t)len;
                      const std::size_t align    = (std::size_t)64;
                      m_cpu_clk_unhalted_ref_tsc = (double*)gms_mm_malloc(samp_len,
                                                                          align);
                      m_tsc_frequency            = (double*)gms_mm_malloc(samp_len,
                                                                          align);
                      m_cpu_util                 = (double*)gms_mm_malloc(samp_len,
                                                                          align);
               }
               
                 SKX_cpu_utilization_t(const  SKX_cpu_utilization_t &) = delete;
               
                 SKX_cpu_utilization_t(SKX_cpu_utilization_t &&) = delete
               
                 ~SKX_cpu_utilization_t() {
                     
                     using namespace gms::common;
                     if(__builtin_expect(nullptr!=
                        m_cpu_clk_unhalted_ref_tsc,0)) gms_mm_free(m_cpu_clk_unhalted_ref_tsc);
                     if(__builtin_expect(nullptr!=
                        m_tsc_frequency,0))            gms_mm_free(m_tsc_frequency);
                     if(__builtin_expect(nullptr!=
                        m_cpu_util,0))                 gms_mm_free(m_cpu_util);
               }     
               
               
                 SKX_cpu_utilization_t &
                 operator=(const SKX_cpu_utilization_t &) = delete;
               
                 SKX_cpu_utilization_t &
                 operator=(SKX_cpu_utilization_t &&) = delete;  
               
                 void compute_metric() {
                    
                    skx_cpu_utilization_samples(m_cpu_clk_unhalted_ref_tsc,
                                                m_tsc_frequency,
                                                m_cpu_util,len);
                                             
               }     
               
                 void analyze_metric_canarm(const char * __restrict fname,
                                          const char * __restrict data_type,
                                          const bool use_omp) {
                   
                    cpu_perf_time_series_canarm<len,lagh>(m_cpu_util,fname,
                                                          data_type,use_omp);
                                                                            
             }  
             
                 void analyze_metric_unimar(const char * __restrict fname,
                                        const char * __restrict data_type) {
                 
                    cpu_perf_time_series_unimar<len,lagh>(m_cpu_util,
                                                          fname,data_type);                           
            } 
            
                 void analyze_metric_unibar(const char * __restrict fname,
                                       const char * __restrict data_type) {
                                       
                    cpu_perf_time_series_unibar<len,lagh>(m_cpu_util,
                                                          fname,data_type);                           
           }    
           
                 void analyze_metric_exsar(const char * __restrict fname,
                                     const char * __restrict data_type) {
                                     
                    cpu_perf_time_series_exsar<len,lagh>(m_cpu_util,
                                                         fname,data_type);                       
           }
           
                 void analyze_metric_bispec(const char * __restrict fname,
                                      const char * __restrict data_type,
                                      const bool use_omp) {
                                      
                    cpu_perf_time_series_bispec<len,lagh>(m_cpu_util,
                                                          fname,data_type,use_omp);                          
           }
           
                 void analyze_metric_thirmo(const char * __restrict fname,
                                      const char * __restrict data_type) {
                                      
                    cpu_perf_time_series_thirmo<len,lagh>(m_cpu_util,
                                                          fname,data_type);                
           }
           
                 void analyze_metric_autocor(const char * __restrict fname,
                                       const char * __restrict data_type) {
                                       
                    cpu_perf_time_series_autocor<len,lagh>(m_cpu_util,
                                                           fname,data_type);                            
          }
          
       
               
      };
      

} // gms

















#endif /*__GMS_POSTPROCESS_SKX_CLK_HW_METRICS_HPP__*/