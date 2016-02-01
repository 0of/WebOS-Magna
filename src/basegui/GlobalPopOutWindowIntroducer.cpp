#include "GlobalPopOutWindowIntroducer.h"

#include <cassert>

#include "Window_p.h"
#include "WindowAccessor.h"

namespace Magna{
  namespace GUI{
    
    GlobalPopOutWindowIntroducer &GlobalPopOutWindowIntroducer::getGlobalPopOutWindowIntroducer(){
      return shared_global_popout_wnd_introducer;
    }


    GlobalPopOutWindowIntroducer::GlobalPopOutWindowIntroducer()
      :m_context( Nullptr )
      ,m_requester( Nullptr ){

    }

    GlobalPopOutWindowIntroducer::~GlobalPopOutWindowIntroducer(){

    }


    void GlobalPopOutWindowIntroducer::introducePopOutWindow( SharedPtr<Window::WindowRoot>& r){
      if( !r.isNull() && r->m_int_runtimeId == 0
        && m_context != Nullptr && m_requester != Nullptr ){
        //
        r->m_RunnableContext = m_context;
        r->m_requester = m_requester;

        m_requester->requestStartPopOutWindow( r );
      }
    }

    void GlobalPopOutWindowIntroducer::init(  RunnableContext *c, OSGUIBehaviourRequester *r ){
      if( c != Nullptr && r != Nullptr ){
        m_context = c;
        m_requester = r;
      }
    }

    GlobalPopOutWindowIntroducer GlobalPopOutWindowIntroducer::shared_global_popout_wnd_introducer = GlobalPopOutWindowIntroducer();


  }//namespace GUI
}//namespace Magna