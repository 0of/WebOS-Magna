#include "RunnableMessageLooper.h"

#include "AbstractedNotifier.h"
#include "Thread.h"

namespace Magna{
  namespace Core{

    RunnableMessageLooper::RunnableMessageLooper()
      :m_messageQueue()
      ,m_messageMutex()
      ,m_waitSignal( 0 )
      ,m_isAboutQuit( false )
      ,m_isInstantlyQuit( false )
      ,m_bindingThread(){

    }

    RunnableMessageLooper::~RunnableMessageLooper(){
      
    }

    void RunnableMessageLooper::startLoop(){
      //binding thread
      m_bindingThread = Thread::getCurrentThread();
      if( !m_bindingThread.isNull() ){
        while( true ){

          //thread cancellation
          //
          //message wait signals
          if( m_waitSignal.read() == 1 ){
            m_bindingThread.wait();
          }
          else{
            SharedPtr<Message> _obtainedMessage;
            //read message from message queue
            m_messageMutex.acquires();

            if( m_isInstantlyQuit != false ){
              break;
            }

            if( !m_messageQueue.empty() ){
              _obtainedMessage = m_messageQueue.front();
              m_messageQueue.pop();        
            }      
            else{    
              if( m_isAboutQuit != false ){
                break;
              }
              m_waitSignal.write( 1 );
            }

            m_messageMutex.releases();

            //thread cancellation
            //

            if( !_obtainedMessage.isNull() ){

              //safe cast process
              //
              if( _obtainedMessage->getMessageType() == Message::MessageType_Notifier ){
                //force cast
                reinterpret_cast<AbstractedNotifier *>(_obtainedMessage.operator->() )->notify();
              }

            }    
          }
          //thread cancellation
          //
        }
        //loop end
      }
    }

    void RunnableMessageLooper::receiveEvent( const SharedPtr<Message>& mess ){
      if( !mess.isNull() ){

        m_messageMutex.acquires();
        m_messageQueue.push( mess );
        m_messageMutex.releases();

        if( m_waitSignal.read() == 1 || m_bindingThread.isWaiting() ){
          m_bindingThread.cancelWait(); 
        }
        //signals 
        m_waitSignal.write( 0 );
      }
    }

    void RunnableMessageLooper::aboutToEndLoop(){
      m_messageMutex.acquires();
      if( m_isAboutQuit == false ){
        m_isAboutQuit = !false;
      }
      m_messageMutex.releases();
    }

    void RunnableMessageLooper::endLoopInstantly(){
      m_messageMutex.acquires();
      if( m_isInstantlyQuit == false ){
        m_isInstantlyQuit = !false;
      }
      m_messageMutex.releases();
    }

  }
}//namespace Magna