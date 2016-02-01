#include "ScriptResourceHandler.h"
#include "ScriptResourceObject_p.h"

namespace Magna{
  namespace Resource{

    ScriptResourceHandler & ScriptResourceHandler::getScriptResourceHandler(){
      static ScriptResourceHandler res_loader;
      return res_loader;
    }

    ScriptResourceHandler::ScriptResourceHandler()
      :m_behaviour( Nullptr )
      ,m_mutex()
      ,m_scriptString(){

    }

    ScriptResourceHandler::~ScriptResourceHandler(){

    }

    void ScriptResourceHandler::setLoadBehaviour( ScriptResourceHandleBehaviour *behaviour){
      if( behaviour != Nullptr ){
        m_mutex.acquires();

        m_behaviour = behaviour;
        m_scriptString.clear();
      }
    }

    void ScriptResourceHandler::actLoad( ScriptResourceObject &obj ){
      if( m_behaviour != Nullptr ){
        m_behaviour->load( obj, m_scriptString );

        OnceLoadActed.triggers( obj.m_data , m_scriptString );

        m_behaviour = Nullptr;
        m_scriptString.clear();

        m_mutex.releases();
      }
    }

    void ScriptResourceHandler::actUnload( ScriptResourceObject &obj ){
      if( m_behaviour != Nullptr ){
        m_behaviour->unload( obj, m_scriptString );

        OnceUnloadActed.triggers( obj.m_data,m_scriptString );

        m_behaviour = Nullptr;
        m_scriptString.clear();

        m_mutex.releases();
      }
    }

  }//namespace Resource
}//namespace Magna
