#ifndef CPUTINFO_P_H
#define CPUTINFO_P_H

#include <cassert>

extern "C"{
#include "sigar/sigar.h"
};

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "CpuInfo.h"

namespace Magna{
  namespace System{
    
    struct CpuInfo::PrivateData{
      PrivateData() 
        : m_hasInitialized( 0 )
        ,m_cachedSize(0)
        ,m_corePerSock(0)
        ,m_mhz(0)
        ,m_totalCores( 0 )
        ,m_totalSockets( 0 )
        ,m_model()
        ,m_vendor(){

      }

      ~PrivateData() {

      }

      void init_sigar_context( sigar_cpu_info_t *_sigar_cput_ptr ){
        assert( _sigar_cput_ptr != Nullptr );

        m_cachedSize = _sigar_cput_ptr->cache_size;
        m_corePerSock = _sigar_cput_ptr->cores_per_socket;
        m_mhz = _sigar_cput_ptr->mhz;
        m_totalCores = _sigar_cput_ptr->total_cores;
        m_totalSockets = _sigar_cput_ptr->total_sockets;

        unicode_char _conv_wstr[128] = { 0 };  

        auto _char_model = _sigar_cput_ptr->model;
        auto _conv_size = ::mbstowcs( _conv_wstr, _char_model, 127 );      
        m_model = String( _conv_wstr, _conv_size );

        auto _char_vendor = _sigar_cput_ptr->vendor;
        _conv_size = ::mbstowcs( _conv_wstr, _char_vendor, 127 );    
        m_vendor = String( _conv_wstr, _conv_size );

        m_hasInitialized = !false;
      }

      //just a sign that the instance has been initialized
      uint32 m_hasInitialized;

      uint64 m_cachedSize;
      uint32 m_corePerSock;
      uint32 m_mhz;
      uint32 m_totalCores;
      uint32 m_totalSockets;

      String m_model;
      String m_vendor;
    };

  }//namespace System
}//namespace Magna

#endif  /*  CPUTINFO_P_H  */
