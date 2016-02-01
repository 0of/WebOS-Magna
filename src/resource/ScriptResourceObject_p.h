#ifndef SCRIPTRESOURCEOBJECT_P_H
#define SCRIPTRESOURCEOBJECT_P_H

#include <cstring>

#include "ScriptResourceObject.h"

namespace Magna{
  namespace Resource{
     
    class ScriptResourceObject::PrivateData{
    public:
      PrivateData( uint32 type ) 
        :m_type( type )
        ,m_loaded( false )
        ,m_srcPath()
        ,m_int_runtimeId( 0 )
        ,m_runtimeId( Nullptr ){

      }

      ~PrivateData(){
        if( m_runtimeId != Nullptr ){
          delete [] m_runtimeId;
        }
      }

      void _assignRuntimeId( const uint64& id ){
        if( !m_loaded && id != 0 ){
          m_mutex.acquires();

          auto _conv_str = std::to_string( id );
          auto _size = _conv_str.size();

          m_runtimeId = new assic_char[ (_size + 3) ] ;

          ::memcpy( (m_runtimeId + 1), _conv_str.c_str(), _size );

          *(m_runtimeId) = '\'';
          *(m_runtimeId+ _size + 1 ) = '\'';
          *(m_runtimeId + _size + 2 ) = '\0';

          m_mutex.releases();
        }
      }

      void _assignLoaded(){
        if( !m_loaded && m_int_runtimeId != 0 ){
          m_mutex.acquires();
          m_loaded = !false;

          m_mutex.releases();
        }
      }

      void _deassignRuntimeId(){
        if( !m_loaded && m_int_runtimeId != 0 && m_runtimeId != Nullptr ){
          m_mutex.acquires();
          m_int_runtimeId = 0;
          delete [] m_runtimeId;
          m_runtimeId = Nullptr;

          m_loaded = false;
          m_mutex.releases();
        }
      }

      uint32 m_type : 24;
      uint32 m_loaded : 8;

      uint64 m_int_runtimeId;
      assic_char *m_runtimeId;

      SpinMutex m_mutex;

      std::string m_srcPath;
    };


  }//namespace Resource
}//namespace Magna

#endif  /*  SCRIPTRESOURCEOBJECT_P_H  */
