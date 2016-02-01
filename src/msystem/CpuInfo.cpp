#include "CpuInfo.h"

#include "CpuInfo_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "SystemContextUninitializedException.h"

namespace Magna{
  namespace System{


    CpuInfo::CpuInfo()
      :m_data( new PrivateData ){

    }

    CpuInfo::~CpuInfo(){

    }

    CpuInfo::CpuInfo( const CpuInfo& info )
      :m_data( info.m_data ){

    }

    CpuInfo& CpuInfo::operator = ( const CpuInfo& info ){
      m_data = info.m_data;
      return *this;
    }

    uint64 CpuInfo::getCacheSize() const{
      uint64 _ret_cache_size = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_cache_size = m_data->m_cachedSize;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_cache_size;
    }

    uint32 CpuInfo::getCoresPerSocket() const{
      uint32 _ret_core_per_sock = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_core_per_sock = m_data->m_corePerSock;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_core_per_sock;
    }

    uint32 CpuInfo::getMhz() const{
      uint32 _ret_mhz = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_mhz = m_data->m_mhz;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_mhz;
    }

    String CpuInfo::getModel() const{
      String _ret_model;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_model = m_data->m_model;    
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_model;
    }

    uint32 CpuInfo::getTotalCores() const{
      uint32 _ret_total_cores = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_total_cores = m_data->m_totalCores;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_total_cores;
    }

    uint32 CpuInfo::getTotalSockets() const{
      uint32 _ret_total_sock = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_total_sock = m_data->m_totalSockets;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_total_sock;
    }

    String   CpuInfo::getVendor() const{
      String _ret_vendor;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized != 0 ){
            _ret_vendor = m_data->m_vendor;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }      
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_vendor;
    }

  }//namespace System
}//namespace Magna