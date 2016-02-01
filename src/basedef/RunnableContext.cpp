#include "RunnableContext.h"

#include "private/RunnableContext_p.h"

namespace Magna{
  namespace Core{

    RunnableContext::RunnableContextEntity::RunnableContextEntity( const String& name)
      :m_contextName( name )
      ,m_int_runningId(0)
      ,m_looper()
      ,m_parentContext()
      ,m_childContext(){

    }

    RunnableContext::RunnableContextEntity::RunnableContextEntity( const String& name, const SharedPtr<RunnableContext>& parent)
      :m_contextName( name )
      ,m_int_runningId(0)
      ,m_looper()
      ,m_parentContext( parent )
      ,m_childContext(){

      //push into parent's child list
      //if parent is running assign running id
      ///
    }

    RunnableContext::RunnableContextEntity::~RunnableContextEntity(){

      auto _iter = m_childContext.begin();
      for( ; _iter != m_childContext.end(); ++_iter ){
        
        if( !_iter->isNull() ){
          (*_iter)->aboutToShutDown();
        }

      }

      //post to parent
      if( !m_parentContext.isNull() 
        && !m_parentContext->m_entity.isNull() ){
        auto &_parent_ctx_entity = m_parentContext->m_entity;

        auto _iter = _parent_ctx_entity->m_childContext.begin();
        for( ; _iter != _parent_ctx_entity->m_childContext.end(); ++_iter ){
          if( !_iter->isNull() && !(*_iter)->m_entity.isNull() ){
            if( ((*_iter)->m_entity->m_int_runningId) == m_int_runningId ){
              _parent_ctx_entity->m_childContext.erase( _iter );
              break;
            }
            else{
              continue;
            }        
          }
        }
      }

    }

    RunnableContext::RunnableContext( const String& name )
      :m_entity( new RunnableContextEntity( name ) ){

    }
      
    RunnableContext::RunnableContext( const String& name ,const SharedPtr<RunnableContext>& parent )
      :m_entity( new RunnableContextEntity( name, parent ) ){

    }

    RunnableContext::~RunnableContext(){

    }

    void RunnableContext::postMessage( const SharedPtr<Message>& message ){  
      if( !message.isNull() &&  !m_entity.isNull() ){
        m_entity->m_looper.receiveEvent( message );
      }
    }

    uint32 RunnableContext::run(){

      OnceRun.triggers();

      if( !m_entity.isNull() ){
        m_entity->m_looper.startLoop();
      }

      OnceShutDown.triggers();

      //return code
      return 0;
    }

    void RunnableContext::aboutToShutDown(){

      if( !m_entity.isNull() ){
        m_entity->m_looper.aboutToEndLoop();
      }

    }

    void RunnableContext::instantlyShutDown(){

      if( !m_entity.isNull() ){
        m_entity->m_looper.endLoopInstantly();
      }

    }

  }
}//namespace Magna