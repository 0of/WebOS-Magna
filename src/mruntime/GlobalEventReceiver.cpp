#include "GlobalEventReceiver.h"

#include "OSRenderBehaviourNotifier.h"
#include "OSAttachControllersBehaviourNotifier.h"
#include "OSDetachControllersBehaviourNotifier.h"
#include "OSScriptRunBehaviourNotifier.h"
#include "OSWindowCloseBehaviourNotifier.h"
#include "OSStartWindowBehaviourNotifier.h"
#include "OSStartApplicationBehaviourNotifier.h"
#include "OSQtWidgetInitBehaviourNotifier.h"

#include "RuntimeScript.h"
#include "ApplicationLoader.h"
#include "WindowManager.h"
#include "SystemComObjectManager.h"
using namespace Magna::SystemComponent;

#include <QApplication>

namespace Magna{
  namespace Runtime{
      GlobalEventReceiver& GlobalEventReceiver::getGlobalEventReceiver(){
        OSBehaviourNotifierHandler & _handler = OSBehaviourNotifierHandler::getOSBehaviourNotifierHandler();
        static SharedPtr<GlobalEventReceiver> eventReceiver = new GlobalEventReceiver( &_handler );
        return *eventReceiver;
      }

      GlobalEventReceiver::GlobalEventReceiver(OSBehaviourNotifierHandler *handler )
        :m_mutex()
        ,m_handler( handler ){

      }

      GlobalEventReceiver::~GlobalEventReceiver(){

      }

      void GlobalEventReceiver::requestWindowMoved(const unicode_char *id, const IntegerDyadCoordinate& coord ){

        QString _movedScript = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Window );
        _movedScript.append( RuntimeScript::shared_JavaScript_Service_set_window_pos )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif    
          .append( "," )
          .append( QString::number( coord.getX() ) )
          .append( "," )
          .append( QString::number( coord.getY() ) )
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( _movedScript );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();

      }

      void GlobalEventReceiver::requestDraggableWindowMove( const unicode_char *id, const IntegerDyadCoordinate& trigger_coord, const IntegerDyadCoordinate& offset ){

        QString _movedScript = QString(  RuntimeScript::shared_JavaScript_Functionality_Window_Rubber_Band );
        _movedScript.append( RuntimeScript::shared_JavaScript_Functionality_trigger_translate )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif
          .append( "," )
          .append( QString::number( trigger_coord.getX() ) )
          .append( "," )
          .append( QString::number( trigger_coord.getY() ) )
          .append( "," )
          .append( QString::number( offset.getX()) )
          .append( "," )
          .append( QString::number( offset.getY() ) )
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( _movedScript );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestWindowResized( const unicode_char *id, const IntegerSize& size){

        QString _resizedScript = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Window );
        _resizedScript.append( RuntimeScript::shared_JavaScript_Service_set_window_size )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif
          .append( "," )
          .append( QString::number( size.getWidth() ) )
          .append( "," )
          .append( QString::number( size.getHeight() ) )
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( _resizedScript );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestWindowRendering( ManipulateEngine& engine ){
        OSRenderBehaviourNotifier *notifier 
          = new OSRenderBehaviourNotifier( engine );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestControllersAttached(  std::vector<SharedPtr<Controller::ControllerRoot> > & ctrls ,RunnableContext * context){
        OSAttachControllersBehaviourNotifier *notifier 
          = new OSAttachControllersBehaviourNotifier( context, ctrls );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();        
      }

      void GlobalEventReceiver::requestControllersDetached( const std::vector< uint64 > & ids) {
        OSDetachControllersBehaviourNotifier  *notifier 
          = new OSDetachControllersBehaviourNotifier( ids );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();      
      }

      void GlobalEventReceiver::requestWindowClose( uint32 id) {
        OSWindowCloseBehaviourNotifier *notifier
          = new OSWindowCloseBehaviourNotifier( id );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();    
      }

      void GlobalEventReceiver::requestWindowVisibilityChanged( const unicode_char *id, bool isVisible) {
        QString visibScript = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Window );
        if( isVisible ){
          visibScript.append( RuntimeScript::shared_JavaScript_Service_set_window_visible )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
            .append( QString::fromStdWString(  id ) )
#endif
            .append( ");" );
        }
        else{
          visibScript.append( RuntimeScript::shared_JavaScript_Service_set_window_hidden )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
            .append( QString::fromStdWString(  id ) )
#endif
            .append( ");" );
        }

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( visibScript );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestWindowFocusChanged( const unicode_char * _id, uint32 _int_id, bool isFocusIn ) {
        //focus script
        QString focusScript = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Window );
        if( isFocusIn ){
          focusScript.append( RuntimeScript::shared_JavaScript_Service_window_focus_in )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( _id ) ) )
#else
            .append( QString::fromStdWString(  _id ) )
#endif
            .append( ");" );
        }
        else{
          focusScript.append( RuntimeScript::shared_JavaScript_Service_window_focus_out )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( _id ) ) )
#else
            .append( QString::fromStdWString(  _id ) )
#endif
            .append( ");" );
        }

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( focusScript );
        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();

        auto & _coms_manager = SystemComObjectManager::getSystemComObjectManager();
        _coms_manager.getDesktopObject().actDispatchWindowFocusChanged( _int_id, isFocusIn );
      }

      void GlobalEventReceiver::requestStartPopOutWindow( const SharedPtr<Window::WindowRoot>& w) {
        if( !w.isNull() && w->m_requester != Nullptr && w->m_RunnableContext != Nullptr ){    
          OSStartWindowBehaviourNotifier*notifier 
            = new OSStartWindowBehaviourNotifier( w, WindowManager::WindowType_PopOut );
          m_mutex.acquires();
          QApplication::postEvent( m_handler, notifier );
          m_mutex.releases();
        }
      }

      void GlobalEventReceiver::requestStartNewWindow( const SharedPtr<Window::WindowRoot>& w ) {
        if( !w.isNull() && w->m_requester != Nullptr && w->m_RunnableContext != Nullptr ){    
          OSStartWindowBehaviourNotifier*notifier 
            = new OSStartWindowBehaviourNotifier( w, WindowManager::WindowType_Normal );
          m_mutex.acquires();
          QApplication::postEvent( m_handler, notifier );
          m_mutex.releases();
        }
      }

      void GlobalEventReceiver::requestStartNewApplication( const String& p, RunnableContext * r ) {
        OSStartApplicationBehaviourNotifier *notifier 
          = new OSStartApplicationBehaviourNotifier( false, p, r );
        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestScriptEval( const String& sc ){
        if( !sc.empty() ){

#ifdef _MSC_VER
          QString _sc = QString::fromUtf16( reinterpret_cast<const ushort *>( sc.c_str() ), sc.size() ) ;
#else
          QString _sc = QString::fromStdWString(  sc ) ;
#endif
          OSScriptRunBehaviourNotifier *notifier 
            = new OSScriptRunBehaviourNotifier( _sc );
          m_mutex.acquires();
          QApplication::postEvent( m_handler, notifier );
          m_mutex.releases();
        }
      }

      void GlobalEventReceiver::askObtainApplicationInfo( const String& a1, String& a2, String& a3){
        auto &_loader = ApplicationLoader::obtainLoader();
        _loader.loadApplicationExpInfo( a1, a2, a3 );
      }

      void GlobalEventReceiver::requestStartNewApplicationWithDialog( const String& p, RunnableContext * r ) {
        OSStartApplicationBehaviourNotifier *notifier 
          = new OSStartApplicationBehaviourNotifier( !false, p, r );
        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestControllerResized( const unicode_char *id, const IntegerSize& size ) {

        QString resized_sc = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Controller );

        resized_sc.append( RuntimeScript::shared_JavaScript_Service_controller_resize )
            .append( "(" )
#ifdef _MSC_VER
            .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
            .append( QString::fromStdWString(  id ) )
#endif
            .append( "," )
            .append( QString::number( size.getWidth() ) )
            .append( "," )
            .append( QString::number( size.getHeight() ) )
            .append( ");" );
      
        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( resized_sc );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestControllerMoved( const unicode_char *id, const IntegerDyadCoordinate& coord ) {
        QString moved_sc = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Controller );

        moved_sc.append( RuntimeScript::shared_JavaScript_Service_controller_move )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif
          .append( "," )
          .append( QString::number( coord.getX() ) )
          .append( "," )
          .append( QString::number( coord.getY() ) ) 
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( moved_sc );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestContentResized( const unicode_char *id, const IntegerSize& size ) {
        QString resized_sc = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Controller );

        resized_sc.append( RuntimeScript::shared_JavaScript_Service_content_resize )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif
          .append( "," )
          .append( QString::number( size.getWidth() ) )
          .append( "," )
          .append( QString::number( size.getHeight() ) )
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( resized_sc );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestWrapperResized( const unicode_char *id, const IntegerSize&  size) {
        QString resized_sc = QString(  RuntimeScript::shared_JavaScript_Service_Provider_Controller );

        resized_sc.append( RuntimeScript::shared_JavaScript_Service_wrapper_resize )
          .append( "(" )
#ifdef _MSC_VER
          .append( QString::fromUtf16( reinterpret_cast<const ushort *>( id ) ) )
#else
          .append( QString::fromStdWString(  id ) )
#endif
          .append( "," )
          .append( QString::number( size.getWidth() ) )
          .append( "," )
          .append( QString::number( size.getHeight() ) )
          .append( ");" );

        OSScriptRunBehaviourNotifier *notifier 
          = new OSScriptRunBehaviourNotifier( resized_sc );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();
      }

      void GlobalEventReceiver::requestQtWidgetInit( QtWidgetInitializer *init ) {

        OSQtWidgetInitBehaviourNotifier*notifier 
          = new OSQtWidgetInitBehaviourNotifier( init );

        m_mutex.acquires();
        QApplication::postEvent( m_handler, notifier );
        m_mutex.releases();

      }

      void GlobalEventReceiver::requestNotifierRunOnCore( const SharedPtr<AbstractedNotifier>& n ) {

      }
  }
}//namespace Magna