#include "SystemInfo.h"

extern "C"{
#include "sigar/sigar.h"
#ifdef _MSC_VER
#include "windows.h"
#elif defined __GNUC__

#endif
}

#include "CpuInfo_p.h"
#include "FileSystemInfo_p.h"
#include "FileSystemUsageQueryResult_p.h"

namespace Magna{
  namespace System{
    
    struct SystemInfo::PrivateData{
      PrivateData()
        :m_sigar_ptr( Nullptr )
        ,m_cpuInfos(){

        //init sigar object
        auto _ret_code = sigar_open( &m_sigar_ptr );

        //init CPU infos
        {
          sigar_cpu_info_list_t _cpu_list;
          ::memset( &_cpu_list, 0, sizeof(sigar_cpu_info_list_t) );

          sigar_cpu_info_list_get( m_sigar_ptr, &_cpu_list );

          for( auto i = 0; i != _cpu_list.size; ++i ){
            CpuInfo _each_info;
            auto &_each_data = *(_cpu_list.data + i);
            _each_info.m_data->init_sigar_context( &_each_data );

            m_cpuInfos.push_back( _each_info );
          }

          sigar_cpu_info_list_destroy( m_sigar_ptr, &_cpu_list );
        }
      
      }


      sigar_t *m_sigar_ptr;

      std::vector<CpuInfo> m_cpuInfos;

    };

    SystemInfo & SystemInfo::getSystemInfo(){
      static SystemInfo _sys_info;
      return _sys_info;
    }


    SystemInfo::SystemInfo()
      :m_data( new PrivateData ){

    }

    SystemInfo::~SystemInfo(){
      if( m_data != Nullptr ){
        delete m_data;
      }
    }

    FileSystemUsageQueryResult SystemInfo::queryFileSystemUsage( const FileSystemInfo& info ) const{
      FileSystemUsageQueryResult _ret_result;
      try{
        if( m_data != Nullptr ){
          assic_char _conv_char_str[ 4096 ] = { 0 };
          auto _conv_size = ::wcstombs( _conv_char_str,  info.getDirPath().c_str(), 4095 );
      
          sigar_file_system_usage_t _usage_t;
          ::memset( &_usage_t, 0, sizeof( sigar_file_system_usage_t ) );
          sigar_file_system_usage_get( m_data->m_sigar_ptr, _conv_char_str, &_usage_t );

          if( _usage_t.total != 0 ){
            _ret_result.m_data = new FileSystemUsageQueryResult::PrivateData;
            _ret_result.m_data->init_sigar_context( &_usage_t );
          }
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
        abort();
      }
      return _ret_result;
    }

    std::vector<CpuInfo> SystemInfo::getCpuInfos() const{
      std::vector<CpuInfo> _ret_infos;
      try{
        if( m_data != Nullptr ){
          _ret_infos = m_data->m_cpuInfos;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
        abort();
      }
      return _ret_infos;
    }

    BatteryDeviceInfo SystemInfo::getBatteryDeviceInfo() const{
#ifdef _MSC_VER
      SYSTEM_POWER_STATUS _status;
      ::GetSystemPowerStatus(&_status);

      BatteryDeviceInfo::BatteryStatus _bat_status = BatteryDeviceInfo::BatteryStatus_Unknow;
      if( _status.ACLineStatus ==  0 ){
        _bat_status = BatteryDeviceInfo::BatteryStatus_DC;
      }
      else if( _status.ACLineStatus == 1 ){
        _bat_status = BatteryDeviceInfo::BatteryStatus_AC;
      }

      BatteryDeviceInfo::BatteryPowerStatus _bat_p_status = BatteryDeviceInfo::BatteryPowerStatus_Unknow;
      if(  _status.ACLineStatus == 1 ){
        _bat_p_status = BatteryDeviceInfo::BatteryPowerStatus_High;
      }
      else{
        if( (_status.BatteryFlag & 1) != 0 ){
          _bat_p_status = BatteryDeviceInfo::BatteryPowerStatus_High;
        }
        else if(  (_status.BatteryFlag & 2) != 0 ){
          _bat_p_status = BatteryDeviceInfo::BatteryPowerStatus_Medium;
        }
        else if( (_status.BatteryFlag & 4) != 0 ){
          _bat_p_status = BatteryDeviceInfo::BatteryPowerStatus_Low;
        }
      }
      
      bool _is_charging = false;
      if( (_status.BatteryFlag & 8) != 0 ){
        _is_charging = !false;
      }

      bool _has_battery = !false;
      if( (_status.BatteryFlag & 128) != 0 ){
        _has_battery = false;
      }

      BatteryDeviceInfo info(_bat_status, _bat_p_status
        , _status.BatteryLifePercent <= 100 ? _status.BatteryLifePercent : 100
        , _is_charging, _has_battery
        , _status.BatteryLifeTime != -1 ? _status.BatteryLifeTime: 0
        , _status.BatteryFullLifeTime != -1? _status.BatteryFullLifeTime : 0 );

      return std::move( info );
#elif defined __GNUC__

#endif
    }

    std::vector<FileSystemInfo> SystemInfo::getFileSystemInfos() const{
      std::vector<FileSystemInfo> _ret_fsInfos;
      try{
        if( m_data != Nullptr ){

          sigar_file_system_list_t _fs_list;
          ::memset( &_fs_list, 0, sizeof(sigar_file_system_list_t) );

          sigar_file_system_list_get( m_data->m_sigar_ptr, &_fs_list );

          for( auto i = 0; i != _fs_list.number; ++i ){
            FileSystemInfo _each_info;
            auto &_each_data = *(_fs_list.data + i);
            _each_info.m_data->init_sigar_context( &_each_data );

            _ret_fsInfos.push_back( _each_info );
          }

          sigar_file_system_list_destroy( m_data->m_sigar_ptr, &_fs_list );

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const std::exception& _ex){
        _ex.what();
        abort();
      }
      return _ret_fsInfos;
    }

  }//namespace System
}//namespace Magna
