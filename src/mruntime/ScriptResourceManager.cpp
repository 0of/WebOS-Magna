#include "ScriptResourceManager.h"

#include "RuntimeContainer.h"
using namespace Magna::Runtime;

namespace Magna{
  namespace Kernel{

    ScriptResourceManager & ScriptResourceManager::getScriptResourceManager(){
      static ScriptResourceManager _res_manager;
      return _res_manager;
    }


    ScriptResourceManager::ScriptResourceManager()
      :m_loadedResObjs(){

    }

    void ScriptResourceManager::loadResource( SharedPtr<ScriptResourceObject::PrivateData> privateObj, const String& script ){
      if( !privateObj.isNull() ){
        std::random_device _dev_gen;

        std::ranlux48_base _base64_ram( _dev_gen() );

        uint64 _id = 0;

        //ensure id unique
        //enter critical section
        m_mutex.acquires();    
        while( [&]() -> bool{ _id = _base64_ram()
          ; return m_loadedResObjs.count( _id )  != 0; }() ){}         

        privateObj->_assignRuntimeId( _id );

        m_loadedResObjs.emplace( std::make_pair(_id, privateObj  ) );
        //leave critical section
        m_mutex.releases();

        auto &_container = RuntimeContainer::getRuntimeContainer();
        _container.evalJavaScript( script );
      }    
    }

    void ScriptResourceManager::unloadResource( SharedPtr<ScriptResourceObject::PrivateData> privateObj , const String& script ){
      if( !privateObj.isNull() ){
        m_mutex.acquires();

        auto _found = m_loadedResObjs.find( privateObj->m_int_runtimeId );

        if( _found != m_loadedResObjs.end() ){
          auto &_container = RuntimeContainer::getRuntimeContainer();
          _container.evalJavaScript( script );

          privateObj->_deassignRuntimeId();

          //erase
          m_loadedResObjs.erase( _found );
        }

        m_mutex.releases();
      }
    }

    void ScriptResourceManager::notifyLoadFinished( const uint64& id ){
      m_mutex.acquires();

      auto _found = m_loadedResObjs.find( id );
      if( _found != m_loadedResObjs.end() ){

        auto &_privateObj = _found->second;

        if( !_privateObj.isNull() ){
          _privateObj->_assignLoaded();

        }
      }

      m_mutex.releases();
    }

    void ScriptResourceManager::unloadAll(){
      auto _iter = m_loadedResObjs.begin();
      for(; _iter != m_loadedResObjs.end(); ++_iter ){
        //_iter->second->
      }
    }

    ScriptResourceManager::~ScriptResourceManager(){
      unloadAll();
    }

  }
}