
#ifndef __GMS_STAT_CONTAINERS_YMM4R8_HPP__
#define __GMS_STAT_CONTAINERS_YMM4R8_HPP__ 131220230809


namespace file_info {

     const unsigned int GMS_STAT_CONTAINERS_YMM4R8_MAJOR = 1;
     const unsigned int GMS_STAT_CONTAINERS_YMM4R8_MINOR = 1;
     const unsigned int GMS_STAT_CONTAINERS_YMM4R8_MICRO = 0;
     const unsigned int GMS_STAT_CONTAINERS_YMM4R8_FULLVER =
       1000U*GMS_STAT_CONTAINERS_YMM4R8_MAJOR+100U*GMS_STAT_CONTAINERS_YMM4R8_MINOR+
       10U*GMS_STAT_CONTAINERS_YMM4R8_MICRO;
     const char * const GMS_STAT_CONTAINERS_YMM4R8_CREATION_DATE = "13-12-2023 08:09 +00200 (WED 13 DEC 2023 GMT+2)";
     const char * const GMS_STAT_CONTAINERS_YMM4R8_BUILD_DATE    = __DATE__ " " __TIME__;
     const char * const GMS_STAT_CONTAINERS_YMM4R8_SYNOPSIS      = "Dynamically allocated, 64-byte aligned YMM4R8-based dense containers."

}





#include <cstdint>
#include "GMS_config"
#include "GMS_complex_ymm4r8.hpp"
#include "GMS_simd_memops.h"

// Enable non-temporal stores for this class only( used with free-standing operators)
// defaulted to 0.
#if !defined (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)
#define USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES 0
#endif


namespace gms {

           template<std::size_t Nx,
                    std::size_t Ny,
                    std::size_t Nz>
           struct  SC3D_ymm4c8_t {
                     
                    std::size_t mnx = Nx;
                    std::size_t mny = Ny;
                    std::size_t mnz = Nz;  
                    __ATTR_ALIGN__(64)  ymm4c8_t mx[(mnx == 0) ? 2 : mnx];
                    __ATTR_ALIGN__(64)  ymm4c8_t my[(mny == 0) ? 2 : mny];
                    __ATTR_ALIGN__(64)  ymm4c8_t mz[(mnz == 0) ? 2 : mnz];
                     
             
                    SC3D_ymm4c8_t() = delete;
                          
                    inline SC3D_ymm4c8_t(ymm4c8_t m_x[Nx],
                                         ymm4c8_t m_y[Ny],
                                         ymm4c8_t m_z[Nz]) {
                          using namespace gms::common;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_uncached_memmove(&this->mz[0],&m_z[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_cached_memmove(&this->mz[0],&m_z[0],this->mnz);
#endif                         
                      }  
                      
                      
                     inline SC3D_ymm4c8_t(const std::size_t _mnx,
                                      const std::size_t _mny,
                                      const std::size_t _mnz,
                                      ymm4c8_t * __restrict m_x,
                                      ymm4c8_t * __restrict m_y,
                                      ymm4c8_t * __restrict m_z) {
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_uncached_memmove(&this->mz[0],&m_z[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_cached_memmove(&this->mz[0],&m_z[0],this->mnz);
#endif                         
                      }  
                      
                   
                      
                    
                   
                              
                                                
                 inline    SC3D_ymm4c8_t(const SC3D_ymm4c8_t &rhs)  {
                     
                          using namespace gms::common;
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mnz = rhs.mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                  avx512_uncached_memmove(&this->mz[0],&rhs.mz[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                  avx512_cached_memmove(&this->mz[0],&rhs.mz[0],this->mnz);
#endif                            
                     }           
                      
                    
                      
                 inline    SC3D_ymm4c8_t & operator=(const SC3D_ymm4c8_t &rhs) {
                     
                           using namespace gms::common;
                           if(this == &rhs) return (*this);
                           this->mnx = rhs.mnx;
                           this->mny = rhs.mny;
                           this->mnz = rhs.mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                   avx512_uncached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                   avx512_uncached_memmove(&this->mz[0],&rhs.mz[0],this->mnz);
#else
	                   avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                   avx512_cached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                   avx512_cached_memmove(&this->mz[0],&rhs.mz[0],this->mnz);
#endif                  
                          return (*this);           
                    }
                      
                    
                 inline    ymm4c8_t __restrict *  mx_ptr() const {
                          
                          return (std::__addressof(this->mx[0]));
                    } 
                    
                 inline    ymm4c8_t __restrict * my_ptr() const {
                          
                          return (std::__addressof(this->my[0]));
                    }
                    
                 inline    ymm4c8_t __restrict * mz_ptr() const {
                         
                          return (std::__addressof(this->mz[0]));
                    } 
                     
                    
              };
              
              
           template<std::size_t Nx,
                    std::size_t Ny>
           struct  SC2D_ymm4c8_t {
                     
                    std::size_t mnx = Nx;
                    std::size_t mny = Ny;
                    __ATTR_ALIGN__(64)  ymm4c8_t mx[(mnx == 0) ? 2 : mnx];
                    __ATTR_ALIGN__(64)  ymm4c8_t my[(mny == 0) ? 2 : mny];
                   
                     
             
                    SC2D_ymm4c8_t() = delete;
                          
                    inline SC2D_ymm4c8_t(ymm4c8_t m_x[Nx],
                                     ymm4c8_t m_y[Ny]) {
                                     
                          using namespace gms::common;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                  
#endif                         
                      }  
                      
                      
                     inline SC2D_ymm4c8_t(const std::size_t _mnx,
                                      const std::size_t _mny,
                                      ymm4c8_t * __restrict m_x,
                                      ymm4c8_t * __restrict m_y)
                                 
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                 
#endif                         
                      }  
                      
                   
                                          
                inline  SC2D_ymm4c8_t(const SC2D_ymm4c8_t &rhs)  {
                     
                          using namespace gms::common;
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                
#else
	                  avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                 
#endif                            
                     }           
                      
                    
                      
                  inline  SC2D_ymm4c8_t & operator=(const SC2D_ymm4c8_t &rhs) {
                     
                           using namespace gms::common;
                           if(this == &rhs) return (*this);
                           this->mnx = rhs.mnx;
                           this->mny = rhs.mny;
                          
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                   avx512_uncached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                  
#else
	                   avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                   avx512_cached_memmove(&this->my[0],&rhs.my[0],this->mny);
	                  
#endif                  
                          return (*this);           
                    }
                      
                    
                 inline    ymm4c8_t __restrict *  mx_ptr() const {
                          
                          return (std::__addressof(this->mx[0]));
                    } 
                    
                 inline    ymm4c8_t __restrict * my_ptr() const {
                          
                          return (std::__addressof(this->my[0]));
                    }
                    
                     
                     
                    
              };
              
              
           template<std::size_t Nx>
           struct  SC1D_ymm4c8_t {
                     
                    std::size_t mnx = Nx;
                    __ATTR_ALIGN__(64)  ymm4c8_t mx[(mnx == 0) ? 2 : mnx];
                                   
                            
                    SC1D_ymm4c8_t() = delete;
                          
                    inline SC1D_ymm4c8_t(ymm4c8_t m_x[Nx]) {
                                    
                          using namespace gms::common;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	                
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                
	                  
#endif                         
                      }  
                      
                      
                     inline SC1D_ymm4c8_t(const std::size_t _mnx,
                                      ymm4c8_t * __restrict m_x) {
                                    
                          using namespace gms::common;
                          this->mnx = _mnx;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  	                  
#else	                 
                          avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                                  
#endif                         
                      }  
                      
                   
                      
                                                 
                                                
                   inline   SC1D_ymm4c8_t(const SC1D_ymm4c8_t &rhs)  {
                     
                          using namespace gms::common;
                          this->mnx = rhs.mnx;
                                                 
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                
	               
#else
	                  avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                 
	                 
#endif                            
                     }           
                      
                    
                      
                  inline   SC1D_ymm4c8_t & operator=(const SC1D_ymm4c8_t &rhs) {
                     
                           using namespace gms::common;
                           if(this == &rhs) return (*this);
                           this->mnx = rhs.mnx;
                                                    
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                  
	                  
#else
	                   avx512_cached_memmove(&this->mx[0],&rhs.mx[0],this->mnx);
	                
	                  
#endif                  
                          return (*this);           
                    }
                      
                    
                  inline   ymm4c8_t __restrict *  mx_ptr() const {
                          
                          return (std::__addressof(this->mx[0]));
                    } 
                    
                  
                    
                     
                     
                    
              };
              
              
              
               
             
               template<std::size_t Nx,
                        std::size_t Ny,
                        std::size_t Nz>
               struct  SC3D__m256d_t {
                     
                      std::size_t mnx = Nx;
                      std::size_t mny = Ny;
                      std::size_t mnz = Nz;
                     __ATTR_ALIGN__(64) __m256d  mxr[(mnx == 0) ? 2 : mnx];
                     __ATTR_ALIGN__(64) __m256d  mxi[(mny == 0) ? 2 : mny];
                     __ATTR_ALIGN__(64) __m256d  myr[(myr == 0) ? 2 : myr];
                     __ATTR_ALIGN__(64) __m256d  myi[(myi == 0) ? 2 : myi];
                     __ATTR_ALIGN__(64) __m256d  mzr[(mzr == 0) ? 2 : mzr];
                     __ATTR_ALIGN__(64) __m256d  mzi[(mzi == 0) ? 2 : mzi];
                     
                   
                      inline SC3D__m256d_t() = delete;
                      
                      
                                        
                      
                      inline SC3D__m256d_t(const std::size_t _mnx,
                                    const std::size_t _mny,
                                    const std::size_t _mnz,
                                    const __m256d * __restrict m_xr,   
                                    const __m256d * __restrict m_xi,
                                    const __m256d * __restrict m_yr,
                                    const __m256d * __restrict m_yi,
                                    const __m256d * __restrict m_zr,
                                    const __m256d * __restrict m_zi) {
                         
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                  avx512_uncached_memmove(&this->myr[0],&m_yr[0],this->mny);
	                  avx512_uncached_memmove(&this->myi[0],&m_yi[0],this->mny);
	                  avx512_uncached_memmove(&this->mzr[0],&m_zr[0],this->mnz);
	                  avx512_uncached_memmove(&this->mzi[0],&m_zi[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                  avx512_cached_memmove(&this->myr[0],&m_yr[0],this->mny);
	                  avx512_cached_memmove(&this->myi[0],&m_yi[0],this->mny);
	                  avx512_cached_memmove(&this->mzr[0],&m_zr[0],this->mnz);
	                  avx512_cached_memmove(&this->mzi[0],&m_zi[0],this->mnz);
#endif          
                      }
                      
                     
                     inline SC3D__m256d_t(const SC3D__m256d_t &rhs) {
                          
                         using namespace gms::common;
                         this->mnx = rhs.mnx;
                         this->mny = rhs.mny;
                         this->mnz = rhs.mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                  avx512_uncached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                  avx512_uncached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                  avx512_uncached_memmove(&this->mzr[0],&rhs.mzr[0],this->mnz);
	                  avx512_uncached_memmove(&this->mzi[0],&rhs.mzi[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                  avx512_cached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                  avx512_cached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                  avx512_cached_memmove(&this->mzr[0],&rhs.mzr[0],this->mnz);
	                  avx512_cached_memmove(&this->mzi[0],&rhs.mzi[0],this->mnz);
#endif
                    }            
                      
                    
                      
                   inline   SC3D__m256d_t & operator=(const SC3D__m256d_t &rhs) {
                      
                          using namespace gms::common;
                          if(this == &rhs) return (*this);
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mnz = rhs.mnz;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                   avx512_uncached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                   avx512_uncached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                   avx512_uncached_memmove(&this->mzr[0],&rhs.mzr[0],this->mnz);
	                   avx512_uncached_memmove(&this->mzi[0],&rhs.mzi[0],this->mnz);
#else
	                   avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                   avx512_cached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                   avx512_cached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                   avx512_cached_memmove(&this->mzr[0],&rhs.mzr[0],this->mnz);
	                   avx512_cached_memmove(&this->mzi[0],&rhs.mzi[0],this->mnz);
#endif                   
                           return (*this);       
                    }
                    
                  inline  __m256d * __restrict get_mxr() const {
                         
                         return (std::__addressof(this->mxr[0]));
                   }
                   
                  inline  __m256d * __restrict get_mxi() const {
                         
                         return (std::__addressof(this->mxi[0]));
                   }
                   
                 inline   __m256d * __restrict get_myr() const {
                         
                         return (std::__addressof(this->myr[0]));
                   }
                   
                inline    __m256d * __restrict get_myi() const {
                         
                         return (std::__addressof(this->myi[0]));
                   }
                   
                inline    __m256d * __restrict get_mzr() const {
                         
                         return (std::__addressof(this->mzr[0]));
                   }
                   
                inline    __m256d * __restrict get_mzi() const {
                         
                         return (std::__addressof(this->mzi[0]));
                   }
                      
                     
                   
              };
              
              
              template<std::size_t Nx,
                       std::size_t Ny>
              struct  SC2D__m256d_t {
                     
                      std::size_t  mnx = Nx;
                      std::size_t  mny = Ny;
                     __ATTR_ALIGN__(64) __m256d  mxr[(mnx == 0) ? 2 : mnx];
                     __ATTR_ALIGN__(64) __m256d  mxi[(mny == 0) ? 2 : mny];
                     __ATTR_ALIGN__(64) __m256d  myr[(myr == 0) ? 2 : myr];
                     __ATTR_ALIGN__(64) __m256d  myi[(myi == 0) ? 2 : myi];
                                       
                     inline SC2D__m256d_t() = delete;
                                                        
                    
                                           
                     inline SC2D__m256d_t(const std::size_t _mnx,
                                    const std::size_t _mny,
                                    const __m256d * __restrict m_xr,   
                                    const __m256d * __restrict m_xi,
                                    const __m256d * __restrict m_yr,
                                    const __m256d * __restrict m_yi) {
                                    
                          this->mnx = _mnx;
                          this->mny = _mny;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                  avx512_uncached_memmove(&this->myr[0],&m_yr[0],this->mny);
	                  avx512_uncached_memmove(&this->myi[0],&m_yi[0],this->mny);
	                 
#else
	                  avx512_cached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                  avx512_cached_memmove(&this->myr[0],&m_yr[0],this->mny);
	                  avx512_cached_memmove(&this->myi[0],&m_yi[0],this->mny);
	                  
#endif          
                      }
                      
                     
                    inline  SC2D__m256d_t(const SC2D__m256d_t &rhs) {
                          
                         using namespace gms::common;
                         this->mnx = rhs.mnx;
                         this->mny = rhs.mny;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                  avx512_uncached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                  avx512_uncached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                 
#else
	                  avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                  avx512_cached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                  avx512_cached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                  
#endif
                    }            
                      
                    
                      
                    inline  SC2D__m256d_t & operator=(const SC2D__m256d_t &rhs) {
                      
                          using namespace gms::common;
                          if(this == &rhs) return (*this);
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                   avx512_uncached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                   avx512_uncached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                   
#else
	                   avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                   avx512_cached_memmove(&this->myr[0],&rhs.myr[0],this->mny);
	                   avx512_cached_memmove(&this->myi[0],&rhs.myi[0],this->mny);
	                   
#endif                   
                           return (*this);       
                    }
                    
                 inline   __m256d * __restrict get_mxr() const {
                         
                         return (std::__addressof(this->mxr[0]));
                   }
                   
                 inline   __m256d * __restrict get_mxi() const {
                         
                         return (std::__addressof(this->mxi[0]));
                   }
                   
                 inline   __m256d * __restrict get_myr() const {
                         
                         return (std::__addressof(this->myr[0]));
                   }
                   
                 inline   __m256d * __restrict get_myi() const {
                         
                         return (std::__addressof(this->myi[0]));
                   }
                   
                   
            
         
             
              };
              
              
             
            template<std::size_t Nx>
            struct  SC1D__m256d_t {
                     
                      std::size_t  mnx = Nx;
                     __ATTR_ALIGN__(64) __m256d  mxr[(mnx == 0) ? 2 : mnx];
                     __ATTR_ALIGN__(64) __m256d  mxi[(mny == 0) ? 2 : mny];
                    
                                       
                     inline SC1D__m256d_t() = delete;
                                                        
                       
                    
                      
                      inline SC1D__m256d_t(const std::size_t _mnx,
                                       const __m256d * __restrict m_xr,   
                                       const __m256d * __restrict m_xi) {
                                      
                          this->mnx = _mnx;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                  
	                 
#else
	                  avx512_cached_memmove(&this->mxr[0],&m_xr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&m_xi[0],this->mnx);
	                 
	                  
#endif          
                      }
                      
                     
                    inline  SC1D__m256d_t(const SC1D__m256d_t &rhs) {
                          
                         using namespace gms::common;
                         this->mnx = rhs.mnx;
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                 
	                 
#else
	                  avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                  avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                  
	                  
#endif
                    }            
                      
                    
                      
                   inline   SC1D__m256d_t & operator=(const SC1D__m256d_t &rhs) {
                      
                          using namespace gms::common;
                          if(this == &rhs) return (*this);
                          this->mnx = rhs.mnx;
                        
#if (USE_GMS_STAT_CONTAINERS_YMM4R8_NT_STORES)  == 1
	                   avx512_uncached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_uncached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                   
	                   
#else
	                   avx512_cached_memmove(&this->mxr[0],&rhs.mxr[0],this->mnx);
	                   avx512_cached_memmove(&this->mxi[0],&rhs.mxi[0],this->mnx);
	                 
	                   
#endif                   
                           return (*this);       
                    }
                    
                 inline   __m256d * __restrict get_mxr() const {
                         
                         return (std::__addressof(this->mxr[0]));
                   }
                   
                 inline   __m256d * __restrict get_mxi() const {
                         
                         return (std::__addressof(this->mxi[0]));
                   }
                   
                    
             
              };
              
              
              
            
           
              
              

              
              




} //gms

















#endif /*__GMS_STAT_CONTAINERS_YMM4R8_HPP__*/