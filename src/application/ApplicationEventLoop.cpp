#include "ApplicationEventLoop.h"

#include "basegui/Window_p.h"

#include "ApplicationEventHandler.h"

namespace Magna{
  namespace Application{
    ApplicationEventLoop::ApplicationEventLoop()
      :m_messageQueue()
      ,m_messageMutex()
      ,m_handler( Nullptr ){

    }

    ApplicationEventLoop::~ApplicationEventLoop(){

    }


    void ApplicationEventLoop::exec(){
      while( true ){
        GUINotifierMessage _obtainedMessage;
        //read message from message queue
        m_messageMutex.acquires();

        if( !m_messageQueue.empty() ){
          _obtainedMessage = m_messageQueue.front();
          m_messageQueue.pop();
        }      
        m_messageMutex.releases();

        if( !_obtainedMessage.m_instance.isNull() 
          && _obtainedMessage.m_content != Nullptr ){

        //  _obtainedMessage.m_instance->_dispatchEventMessage(_obtainedMessage.m_content  );

        }    
      }
    }

    void ApplicationEventLoop::receiveEvent( const GUINotifierMessage& message ){
      m_messageMutex.acquires();
      m_messageQueue.push( message );
      m_messageMutex.releases();
    }

  }//namespace Application
}//namespace Magna
