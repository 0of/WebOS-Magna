
#include "FileSystemInfo.h"

#include "FileSystemInfo_p.h"

#include "SystemContextUninitializedException.h"

namespace Magna{
  namespace System{
    
    FileSystemInfo::FileSystemInfo()
      :m_data( new PrivateData() ){

    }

    FileSystemInfo::~FileSystemInfo(){

    }

    FileSystemInfo::FileSystemInfo( const FileSystemInfo& info)
      :m_data( info.m_data ){

    }

    FileSystemInfo& FileSystemInfo::operator = ( const FileSystemInfo& info){
      m_data = info.m_data;
      return *this;
    }

    String FileSystemInfo::getDirPath() const{
      String _ret_path;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_path = m_data->m_dirPath;
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
      return _ret_path;
    }

    String FileSystemInfo::getDeviceName() const{
      String _ret_dev;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_dev = m_data->m_deviceName;
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
      return _ret_dev;
    }

    String FileSystemInfo::getTypeName() const{
      String _ret_type_name;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_type_name = m_data->m_typeName;
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
      return _ret_type_name;
    }

    String FileSystemInfo::getSystemTypeName() const{
      String _ret_sys_type_name;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_sys_type_name = m_data->m_systemTypeName;
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
      return _ret_sys_type_name;
    }

    String FileSystemInfo::getOptions() const{
      String _ret_options;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _ret_options = m_data->m_options;
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
      return _ret_options;
    }

    FileSystemInfo::FileSystemType FileSystemInfo::getType() const{
      FileSystemInfo::FileSystemType _type = FileSystemInfo::FileSystemType_None;
      try{
        if( !m_data.isNull() ){
          if( m_data->m_hasInitialized ){
            _type = m_data->m_type;
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
      return _type;
    }

  }//namespace System
}//namespace Magna