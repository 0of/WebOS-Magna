#ifndef APPLICATIONEVENTHANDLER_H
#define APPLICATIONEVENTHANDLER_H

#include "render/ManipulateEngine.h"
using namespace Magna::Render;

#include "basedef/Trigger.h"
#include "basedef/RunnableContext.h"
using namespace Magna::Core;

#include "basegui/Window.h"
#include "basegui/Window_p.h"
using namespace Magna::GUI;

#include "OSGUIBehaviourExRequester.h"

namespace Magna{
  namespace Application{

    //a proxy
    class ApplicationEventHandler : public OSGUIBehaviourExRequester{

      public:
        TRIGGER_DEF(OnceWindowIntroduced, const SharedPtr<Window>&)
    
      public:
        ApplicationEventHandler()
          :m_requester( Nullptr ){

        }
        virtual ~ApplicationEventHandler(){

        }
      public:
        void bindRequester( OSGUIBehaviourExRequester * requester){
          m_requester = requester;
        }

        virtual void requestWindowRendering( ManipulateEngine& engine ) {
          if( m_requester != Nullptr ){
            m_requester->requestWindowRendering( engine );
          }    
        }

        virtual void requestWindowMoved( const unicode_char *i, const IntegerDyadCoordinate& c) {
          if( m_requester != Nullptr ){
            m_requester->requestWindowMoved( i, c );
          }  
        }

        virtual void requestDraggableWindowMove( const unicode_char *i, const IntegerDyadCoordinate& c1 , const IntegerDyadCoordinate& c2 ){
          if( m_requester != Nullptr ){
            m_requester->requestDraggableWindowMove( i, c1, c2 );
          }  
        }

        virtual void requestWindowResized( const unicode_char *i, const IntegerSize& s) {
          if( m_requester != Nullptr ){
            m_requester->requestWindowResized( i, s );
          }  
        }

        virtual void requestControllersAttached(  std::vector<SharedPtr<Controller::ControllerRoot> > & c,RunnableContext *r ) {
          if( m_requester != Nullptr ){
            m_requester->requestControllersAttached( c, r );
          }  
        }

        virtual void requestControllerResized( const unicode_char *a1, const IntegerSize& a2  ) {
          if( m_requester != Nullptr ){
            m_requester->requestControllerResized( a1, a2);
          }  
        }

        virtual void requestControllerMoved( const unicode_char *a1, const IntegerDyadCoordinate& a2 ) {
          if( m_requester != Nullptr ){
            m_requester->requestControllerMoved( a1, a2);
          }  
        }

        virtual void requestWindowClose( uint32 id) {
          if( m_requester != Nullptr ){
            m_requester->requestWindowClose( id);
          }
        }

        virtual void requestControllersDetached( const std::vector< uint64 > & ids ) {
          if( m_requester != Nullptr ){
            m_requester->requestControllersDetached( ids );
          }
        }

        virtual void requestWindowVisibilityChanged( const unicode_char *id, bool t){
          if( m_requester != Nullptr ){
            m_requester->requestWindowVisibilityChanged( id, t );
          }
        }

        virtual void requestWindowFocusChanged( const unicode_char *id, uint32 _id, bool t){
          if( m_requester != Nullptr ){
            m_requester->requestWindowFocusChanged( id, _id, t );
          }
        }

        virtual void requestStartNewWindow( const SharedPtr<Window::WindowRoot>& w ) {
          if( m_requester != Nullptr ){
            m_requester->requestStartNewWindow( w );
          }
        }

        virtual void requestStartPopOutWindow( const SharedPtr<Window::WindowRoot>& w ) {
          if( m_requester != Nullptr ){
            m_requester->requestStartPopOutWindow( w );
          }
        }

        virtual void requestStartNewApplication( const String& a1, RunnableContext * a2= Nullptr ) {
          if( m_requester != Nullptr ){
            m_requester->requestStartNewApplication( a1, a2 );
          }
        }

        virtual void requestStartNewApplicationWithDialog( const String& a1, RunnableContext * a2= Nullptr ) {
          if( m_requester != Nullptr ){
            m_requester->requestStartNewApplicationWithDialog( a1, a2 );
          }
        }

        virtual void requestScriptEval( const String& sc ) {
          if( m_requester != Nullptr ){
            m_requester->requestScriptEval( sc );
          }
        }

        virtual void askObtainApplicationInfo( const String& a1, String& a2, String& a3) {
          if( m_requester != Nullptr ){
            m_requester->askObtainApplicationInfo( a1,a2,a3 );
          }
        }

        virtual void requestContentResized( const unicode_char *id, const IntegerSize& a2 ) {
          if( m_requester != Nullptr ){
            m_requester->requestContentResized( id,a2 );
          }
        }

        virtual void requestWrapperResized( const unicode_char *id, const IntegerSize&  a2) {
          if( m_requester != Nullptr ){
            m_requester->requestWrapperResized( id,a2 );
          }
        }

        virtual void requestQtWidgetInit( QtWidgetInitializer *i ) {
          if( m_requester != Nullptr ){
            m_requester->requestQtWidgetInit( i );
          }
        }

        virtual void requestNotifierRunOnCore( const SharedPtr<AbstractedNotifier>& n ) {
          if( m_requester != Nullptr ){
            m_requester->requestNotifierRunOnCore( n );
          }
        }

    private:
        OSGUIBehaviourExRequester *m_requester;

    };
  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONEVENTHANDLER_H  */