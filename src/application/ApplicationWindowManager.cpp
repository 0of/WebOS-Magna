#include "ApplicationWindowManager.h"

#include "ApplicationWindowManager_p.h"
#include "ApplicationAccessor.h"
#include "ApplicationEventHandler.h"

#include "basegui/WindowAccessor.h"
using namespace Magna::GUI;
#include <cassert>

namespace Magna{
  namespace Application{
    ApplicationWindowManager::ApplicationWindowManager()
      :m_data( new PrivateData){

    }

    ApplicationWindowManager::~ApplicationWindowManager(){

    }
    /*
    ApplicationWindowManager::ApplicationWindowManager(ApplicationEventHandler &handler)
      :m_data( new PrivateData( handler ) ){
      
    }

    ApplicationWindowManager::~ApplicationWindowManager(){
    
    }


    void ApplicationWindowManager::registerMainWindow( const SharedPtr<Window>& window ){
      if( m_data != Nullptr ){
        m_data->m_mainWindow = window;

        //connect
        auto &_root = WindowAccessor::getRoot( window );

        //application event handler
        if( !_root.isNull() ){
          _root->OnceRendered.connectAction( &m_data->m_handler.OnceWindowRender
            , &Trigger<ManipulateEngine&>::triggers );
        }
      }

    }
    */

    SharedPtr<Window> ApplicationWindowManager::getMainWindow(){
      return m_data->m_mainWindow;
    }

    void ApplicationWindowManager::PrivateData::decreaseRunningWindow(){
      assert( m_runningWndCounter != 0 );

      --m_runningWndCounter;
      if( m_runningWndCounter == 0 ){
        //m_binding.
      }
    }


  }//namespace Application
}//namespace Magna