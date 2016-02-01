#include "FileSystemUsageQueryResult.h"

#include "FileSystemUsageQueryResult_p.h"

#include "SystemContextUninitializedException.h"

namespace Magna{
  namespace System{
    
    FileSystemUsageQueryResult::FileSystemUsageQueryResult()
      :m_data(){

    }

    FileSystemUsageQueryResult::FileSystemUsageQueryResult( const FileSystemUsageQueryResult& r)
      :m_data( r.m_data ){

    }

    FileSystemUsageQueryResult::~FileSystemUsageQueryResult(){

    }

    FileSystemUsageQueryResult & FileSystemUsageQueryResult::operator =( const FileSystemUsageQueryResult& r){
      m_data = r.m_data;
      return *this;
    }

    double FileSystemUsageQueryResult::getUsedPercentage() const{
      double _percent = 0.0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _percent = m_data->m_usePercent;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _percent;
    }

    uint64 FileSystemUsageQueryResult::getTotal() const{
      uint64 _total = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _total = m_data->m_total;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _total;
    }

    uint64 FileSystemUsageQueryResult::getFree() const{
      uint64 _free_size = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _free_size = m_data->m_free;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _free_size;
    }

    uint64 FileSystemUsageQueryResult::getUsed() const{
      uint64 _used_size = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _used_size = m_data->m_used;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _used_size;
    }

    uint64 FileSystemUsageQueryResult::getAvail() const{
      uint64 _ret_avail = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_avail = m_data->m_avail;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_avail;
    }

    uint64 FileSystemUsageQueryResult::getFiles() const{
      uint64 _ret_files = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_files = m_data->m_files;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_files;
    }

    uint64 FileSystemUsageQueryResult::getFreeFiles() const{
      uint64 _ret_free_files = 0;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_free_files = m_data->m_freeFiles;
          }
          else{
            throw SystemContextUninitializedException();
          }
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
      }
      return _ret_free_files;
    }

  }//namespace System
}//namespace Magna