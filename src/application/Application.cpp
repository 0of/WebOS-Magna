#pragma warning( disable: 4355 )

#include "Application.h"
#include "ApplicationEntry.h"

#include "basedef/Thread.h"
using namespace Magna::Core;

#include "basegui/Window.h"
#include "basegui/Window_p.h"
#include "basegui/WindowAccessor.h"
using namespace Magna::GUI;

#include "Application_p.h"
#include "ApplicationWindowManager_p.h"
#include "ApplicationIntroducer.h"

namespace Magna{
  namespace Application{
    
    SpinMutex MagnaApplication::shared_mutex = SpinMutex(true);
    SpinMutex MagnaApplication::shared_confirm_mutex = SpinMutex(true);
    MagnaApplication * MagnaApplication::shared_current_application = Nullptr;

    MagnaApplication::MagnaApplication( const String& appName )
      :RunnableContext( L"MagnaApplication")
      ,m_data( new PrivateData( appName ) ){

    }

    MagnaApplication::~MagnaApplication(){

    }

    void MagnaApplication::exec(){

      shared_current_application = this;
      shared_mutex.releases();
      shared_confirm_mutex.releases();

      RunnableContext::run();

    }

    void MagnaApplication::aboutToQuit(){

      RunnableContext::aboutToShutDown();

    }

    void MagnaApplication::quit(){

      RunnableContext::instantlyShutDown();

    }

    void MagnaApplication::introducesApplication( const String& p){
      ApplicationIntroducer& _i = ApplicationIntroducer::getApplicationIntroducer();
      _i.introduces( p );
    }

    void MagnaApplication::introducesApplicationWithDialog( const String& p){
      ApplicationIntroducer& _i = ApplicationIntroducer::getApplicationIntroducer();
      _i.introducesWithDialog( p );
    }

    void MagnaApplication::setupMainWindow( const SharedPtr<Window>& mainWnd ){

      if( !mainWnd.isNull() ){

        auto &&_root = WindowAccessor::getRoot( mainWnd );

        auto &_handler = m_data->m_eventHandler;

        //application event handler
        if( !_root.isNull() ){
          _root->m_requester = &_handler;
        }
        //binding application
        _root->m_RunnableContext = this;

        //push into window manager
        auto &_manager = m_data->m_wndManager;
        if( _manager.m_data != Nullptr ){
          _manager.m_data->postMainWindow( mainWnd );
        }
        
      }
      
    }

    SharedPtr<Window> MagnaApplication::getMainWindow(){
      return m_data->m_wndManager.getMainWindow();
    }

    String MagnaApplication::getApplicationName() const{
      return m_data->m_appName;
    }

    /*
    MagnaApplication::MagnaApplication( const assic_char* appName )
      :m_data( new PrivateData( appName ) ){
      
      m_data->m_loop.m_handler = &m_data->m_eventHandler;
    }

    MagnaApplication::~MagnaApplication(){
      
    }

    void MagnaApplication::sendMessageCode(sint32 code){
      if( shared_current_application != Nullptr ){
        //m_data->m_messageCode.write( code );

      }
    }

    //
    void MagnaApplication::exec(){

      shared_current_application = this;
      shared_mutex.releases();
      shared_confirm_mutex.releases();

      if( !m_data.isNull() ){
        m_data->m_loop.exec();
      }
          
      //Thread::exit();
    }

    void MagnaApplication::setupMainWindow( const SharedPtr<Window>& mainWnd ){
      m_data->m_wndManager.registerMainWindow( mainWnd );
    }

    SharedPtr<Window> MagnaApplication::getMainWindow(){
      return m_data->m_wndManager.getMainWindow();
    }

    const assic_char * MagnaApplication::getApplicationName() const{
      return m_data->m_appName;
    }
    */

    MagnaApplication *MagnaApplication::shared_Obtain_Application(){

      shared_mutex;

      shared_mutex.acquires();
      shared_confirm_mutex.acquires();
      MagnaApplication *_ret_app = MagnaApplication::shared_current_application;
      //edit 3.22
      MagnaApplication::shared_current_application = Nullptr;

      //shared_confirm_mutex.releases();
      //shared_mutex.releases();
      return _ret_app;
    }
  }//namespace Application
}//namespace Magna
