#include "OSRenderBehaviourNotifier.h"

#include "RuntimeContainer.h"

namespace Magna{
  namespace Runtime{
    
    /*
    OSRenderBehaviourNotifier::OSRenderBehaviourNotifier(const assic_char* element_id,const std::string& content)
      :OSBehaviourNotifier()
      ,m_element_id( element_id )
      ,m_content( content ){

    } 
    */

    OSRenderBehaviourNotifier::OSRenderBehaviourNotifier( ManipulateEngine &engine )
      :OSBehaviourNotifier()
      ,m_engine( engine ){

    } 

    OSRenderBehaviourNotifier::~OSRenderBehaviourNotifier(){

    }

    void OSRenderBehaviourNotifier::notifyOS() {
      RuntimeContainer & _container = RuntimeContainer::getRuntimeContainer();

      m_engine.lockReserved();
      auto &_manips = m_engine.getReservedScriptManipulators();
      for( auto _iter = _manips.begin(); _iter != _manips.end() ; ++_iter ){
        if( (*_iter) != Nullptr ){
          auto &_outer = (*_iter)->getOutter();
          _container.evalJavaScript( _outer.str() );
        }  
      }
      m_engine.cancelReservation();
      m_engine.unlockReserved();

    }

  }//namespace Runtime
}//namespace Magna