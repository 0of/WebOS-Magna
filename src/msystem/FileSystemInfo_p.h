#ifndef FILESYSTEMINFO_P_H
#define FILESYSTEMINFO_P_H

#include <cassert>

extern "C"{
#include "sigar/sigar.h"
};

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "FileSystemInfo.h"

namespace Magna{
  namespace System{
    
    struct FileSystemInfo::PrivateData{
      uint32 m_hasInitialized;

      String m_dirPath;
      String m_deviceName;
      String m_typeName;
      String m_systemTypeName;
      String m_options;

      FileSystemInfo::FileSystemType m_type;

      PrivateData()
        : m_hasInitialized( 0 )
        ,m_dirPath()
        ,m_deviceName()
        ,m_typeName()
        ,m_systemTypeName()
        ,m_options()
        ,m_type( FileSystemInfo::FileSystemType_Unknow ){

      }
      ~PrivateData(){

      }

      void init_sigar_context( sigar_file_system_t *_sigar_fs_ptr ){
        assert( _sigar_fs_ptr != Nullptr );
        assert( _sigar_fs_ptr->type < SIGAR_FSTYPE_MAX );
        m_type = static_cast<FileSystemType>(_sigar_fs_ptr->type);
            
        uint32 _conv_size = 0;
        {
          unicode_char _l_conv_wstr[4096] = { 0 };  

          auto _char_dir_name = _sigar_fs_ptr->dir_name;
          _conv_size = ::mbstowcs( _l_conv_wstr, _char_dir_name, 4095 );    
          m_dirPath = String( _l_conv_wstr, _conv_size );

          auto _char_dev_name = _sigar_fs_ptr->dev_name;
          _conv_size = ::mbstowcs( _l_conv_wstr, _char_dev_name, 4095 );    
          m_deviceName = String( _l_conv_wstr, _conv_size );
        }
        
        {
          unicode_char _conv_wstr[256] = { 0 };

          auto _char_type_name = _sigar_fs_ptr->type_name;
          _conv_size = ::mbstowcs( _conv_wstr, _char_type_name, 255 );    
          m_typeName = String( _conv_wstr, _conv_size );

          auto _char_sys_type_name = _sigar_fs_ptr->sys_type_name;
          _conv_size = ::mbstowcs( _conv_wstr, _char_sys_type_name, 255 );    
          m_systemTypeName = String( _conv_wstr, _conv_size );

          auto _char_options = _sigar_fs_ptr->options;
          _conv_size = ::mbstowcs( _conv_wstr, _char_options, 255 );    
          m_options = String( _conv_wstr, _conv_size );
          
        }      
        m_hasInitialized = !false;
      }
    };


  }//namespace System
}//namespace Magna

#endif  /*  FILESYSTEMINFO_H  */
