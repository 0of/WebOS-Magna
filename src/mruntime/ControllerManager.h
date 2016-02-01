#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include "basedef/RunnableContext.h"
#include "basedef/RunnableMessageLooper.h"
using namespace Magna::Core;

#include "basegui/Controller.h"
#include "basegui/Controller_p.h"
using namespace Magna::GUI;

#include "application/ApplicationWindowManager.h"
//#include "application/ApplicationEventLoop.h"
#include "application/GUIEventNotifier.h"
using namespace Magna::Application;

//c++ 11 STL
#include <unordered_map>
#include <queue>

namespace Magna{
  namespace Kernel{

    class ControllerManager{
      public:
        static ControllerManager & getControllerManager();
        
#ifdef MAGNA_DIV_CANVAS_WRAPPER
        //void registerController(  const SharedPtr<Controller::ControllerRoot>& ,  ApplicationEventLoop & );
        //void registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& ,  ApplicationEventLoop & );
        void registerController(  const SharedPtr<Controller::ControllerRoot>& ,  RunnableMessageLooper * );
        void registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& ,  RunnableMessageLooper * );

        //will update its parent
        void registerDynamicControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >& ,  RunnableMessageLooper * );


        //void registerControllers( const std::vector<SharedPtr<Controller::ControllerRoot> >&& ,  RunnableMessageLooper * );
#else
        void registerController( const unicode_char* wnd_id, const SharedPtr<Controller::ControllerRoot>& ,  ApplicationEventLoop & );
        void registerControllers( const unicode_char* wnd_id, const std::vector<SharedPtr<Controller::ControllerRoot> >& ,  ApplicationEventLoop & );
#endif
        //do not need to script manipulate
        //its parent window has done all
        void unregisterController( const uint64& id );
        void unregisterController( const std::vector<uint64>& ids );
        void unregisterController( const std::vector<SharedPtr<Controller::ControllerRoot> >& );

        //will not update its parent
        void unregisterDynamicController( const std::vector<uint64>& ids );

        //dispatchers
        template<GUIEventConstants::EventType type>
        void dispatchMouseEvent( const uint64& runtime_id , sint32 x, sint32 y, uint32 buttons,  uint32 modifiers ){
          //  Mouse event type check
          //
          // 

          m_mutex.acquires();
          auto _it = m_runingCtrls.find( runtime_id );
          auto _end = m_runingCtrls.end() ;
          m_mutex.releases();

          if( _it != _end ){
            //generate Event argument
            auto _root = _it->second.first;
            SharedPtr<AbstractedEventArgs> eventArgs = new MouseEventArgs( type
              , buttons, DigitDyadCoordinate( x, y)
              , modifiers);

            if( _it->second.second != Nullptr ){
            //  ApplicationEventLoop& _app_eve_loop = *(_it->second.second);

            //  GUINotifierMessage notifierMessage( _root,  eventArgs );
              
            //  _app_eve_loop.receiveEvent( notifierMessage );

              RunnableMessageLooper *_app_eve_loop = (_it->second.second);

              SharedPtr<Message> _gen_message = new GUIEventNotifier( _root, eventArgs );

              _app_eve_loop->receiveEvent( _gen_message );
            }

          }
        }


        template<GUIEventConstants::EventType type>
        void dispatchKeyEvent( const uint64& runtime_id, uint32 pressedKey ){
          //  event type check
          //
          // 
          m_mutex.acquires();
          auto _it = m_runingCtrls.find( runtime_id );
          auto _end = m_runingCtrls.end() ;
          m_mutex.releases();

          if( _it != _end ){
            //generate Event argument
            auto _root =_it->second.first;

            SharedPtr<AbstractedEventArgs> eventArgs = new KeyEventArgs( type, pressedKey );

            //ApplicationEventLoop& _app_wnd_manager_data = _it->second.second;
            if( _it->second.second != Nullptr ){
              //ApplicationEventLoop& _app_eve_loop = *(_it->second.second);

              //GUINotifierMessage notifierMessage( _root,  eventArgs );
              //auto &_binding_data = _app_wnd_manager_data.m_loop;
              //_app_eve_loop.receiveEvent( notifierMessage );
              //_ 
              RunnableMessageLooper *_app_eve_loop = (_it->second.second);

              SharedPtr<Message> _gen_message = new GUIEventNotifier( _root, eventArgs );

              _app_eve_loop->receiveEvent( _gen_message );
            }
          }
        }

        template<GUIEventConstants::EventType type>
        void dispatchMouseWheelEvent( const uint64& runtime_id , sint32 x, sint32 y, sint32 delta,  uint32 modifiers ){
          //  event type check
          //
          // 
          m_mutex.acquires();
          auto _it = m_runingCtrls.find( runtime_id );
          auto _end = m_runingCtrls.end() ;
          m_mutex.releases();

          if( _it != _end ){
            //generate Event argument
            auto _root =_it->second.first;
            auto _mapper_hub = _root->m_centreLayout.operator->();

            SharedPtr<AbstractedEventArgs> eventArgs = new MouseWheelEventArgs( type
              , delta, DigitDyadCoordinate( x, y)
              , modifiers );

            //ApplicationEventLoop& _app_wnd_manager_data = _it->second.second;
            if( _it->second.second != Nullptr ){
              //ApplicationEventLoop& _app_eve_loop = *(_it->second.second);

              //GUINotifierMessage notifierMessage( _root,  eventArgs );
              //auto &_binding_data = _app_wnd_manager_data.m_loop;
              //_app_eve_loop.receiveEvent( notifierMessage );
              //_ 
              RunnableMessageLooper *_app_eve_loop = (_it->second.second);

              SharedPtr<Message> _gen_message = new GUIEventNotifier( _root, eventArgs );

              _app_eve_loop->receiveEvent( _gen_message );
            }

          }
        }

        template<GUIEventConstants::EventType type>
        void dispatchHoverEvent( const uint64& runtime_id ){

          m_mutex.acquires();
          auto _it = m_runingCtrls.find( runtime_id );
          auto _end = m_runingCtrls.end() ;
          m_mutex.releases();

          if( _it != _end ){
            //generate Event argument
            auto _root =_it->second.first;
            auto _mapper_hub = _root->m_centreLayout.operator->();
            SharedPtr<AbstractedEventArgs> eventArgs = new HoverEventArgs( type );
      
            if( _it->second.second != Nullptr ){
              RunnableMessageLooper *_app_eve_loop = (_it->second.second);

              SharedPtr<Message> _gen_message = new GUIEventNotifier( _root, eventArgs );

              _app_eve_loop->receiveEvent( _gen_message );
            }
          }
        }


      private:
        typedef std::pair<SharedPtr<Controller::ControllerRoot>, RunnableMessageLooper *>  ControllerDataPack;
        //typedef std::pair<SharedPtr<Controller::ControllerRoot>, ApplicationEventLoop *>  ControllerDataPack;
        std::unordered_map<uint64,  ControllerDataPack > m_runingCtrls;
        SpinMutex m_mutex;
    };

  }
}

#endif  /*  CONTROLLERMANAGER_H  */
