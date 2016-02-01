#ifndef FILESYSTEMUSAGEQUERYRESULT_P_H
#define FILESYSTEMUSAGEQUERYRESULT_P_H

#include <cassert>
#include <cstring>

extern "C"{
#include "sigar/sigar.h"
};

#include "FileSystemUsageQueryResult.h"

namespace Magna{
  namespace System{

    #pragma pack( push )
    #pragma pack( 4 )
    struct FileSystemUsageQueryResult::PrivateData{

      PrivateData() 
        :m_hasInitialized( 0 )
        ,m_usePercent( 0.0 )
        ,m_total( 0 )
        ,m_free( 0 )
        ,m_used( 0 )
        ,m_avail( 0 )
        ,m_files( 0 )
        ,m_freeFiles( 0 ){

      }

      ~PrivateData(){

      }

      void init_sigar_context( sigar_file_system_usage_t *_sigar_fsu_ptr ){
        assert( _sigar_fsu_ptr != Nullptr );

        if( _sigar_fsu_ptr->total != 0 ){
          uint8 *_data_addr = reinterpret_cast<uint8 *>( _sigar_fsu_ptr );
          _data_addr += sizeof( sigar_disk_usage_t );
          
          uint8 *_des_data_addr = (reinterpret_cast<uint8 *>( this ));
          ::memcpy( _des_data_addr,_data_addr, ( sizeof( PrivateData ) - sizeof( decltype(m_usePercent) ) ) );
          
          m_hasInitialized = !false;
        }
      
      }    
      double m_usePercent;
      uint64 m_total;
      uint64 m_free;
      uint64 m_used;
      uint64 m_avail;
      uint64 m_files;
      uint64 m_freeFiles;
      uint32 m_hasInitialized;
    };
    #pragma pack( pop )
  }//namespace System
}//namespace Magna

#endif  /*  FILESYSTEMUSAGEQUERYRESULT_P_H  */
