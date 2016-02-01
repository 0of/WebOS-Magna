#include "ScriptResourceObject.h"
#include "ScriptResourceObject_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include <hash_map>

namespace Magna{
  namespace Resource{
    
    uint16 ScriptResourceObject::registerObjectType( uint16 hint ){
      auto & _factory = getRegisteredTypeFactory();
      uint16 _hint = hint;
      auto _emp_ret = _factory.emplace( _hint );
      while( !_emp_ret.second ){
        _hint = (_hint + 769 ) % 65535;
         _emp_ret = _factory.emplace( _hint );
      }
      return _hint;
    }

    std::set<uint16> &ScriptResourceObject::getRegisteredTypeFactory(){
      static std::set<uint16>_registered_factory;
      return _registered_factory;
    }

    ScriptResourceObject::ScriptResourceObject( uint16 type )
      :m_data( new PrivateData( type ) ){


    }
    
    ScriptResourceObject::ScriptResourceObject( uint16 type, const std::string& src )
      :m_data( new PrivateData( type ) ){

    }

    ScriptResourceObject::~ScriptResourceObject(){

    }

    bool ScriptResourceObject::isLoaded() const{
      bool _ret_loaded = false;
      try{
        if( !m_data.isNull() ){
          m_data->m_mutex.acquires();
          _ret_loaded = static_cast<const bool>(m_data->m_loaded);
          m_data->m_mutex.releases();
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
        abort();
      }
      return _ret_loaded;
    }

    std::string ScriptResourceObject::getSourcePath() const{
      std::string _ret_path;
      try{
        if( !m_data.isNull() ){
          _ret_path = m_data->m_srcPath;
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& _ex ){
        _ex.what();
        abort();
      }
      return _ret_path;
    }

  }//namespace Resource
}//namespace Magna