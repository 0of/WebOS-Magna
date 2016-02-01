#include "private/Trigger_p.h"
#include "private/Callable_p.h"

#include <cassert>

namespace Magna{
  namespace Core{
    _TriggerBase::_TriggerBase()
      :m_callables( Nullptr ), m_endCallable( Nullptr ), m_mutex() {

    }

    _TriggerBase::~_TriggerBase(){
      clear();
    }

    void _TriggerBase::block(){
      m_mutex.acquires();
      Callable *_each = m_callables;
      while(  _each != Nullptr ){
        if( _each->m_blockable ){
          _each->m_blocked = !false;
        }
        _each = _each->m_next;
      }  
      m_mutex.releases();
    }

    void _TriggerBase::resume(){
      m_mutex.acquires();
      Callable *_each = m_callables;
      while(  _each != Nullptr ){
        _each->m_blocked = false;
        _each = _each->m_next;
      }  
      m_mutex.releases();
    }

    void  _TriggerBase::clear(){
      m_mutex.acquires();
      Callable *_each = m_callables;
      while(  _each != Nullptr ){
        Callable *_curr_node = _each;
        _each = _each->m_next;
        delete _curr_node;    
      }  
      m_callables = Nullptr;
      m_endCallable = Nullptr;

      m_mutex.releases();
    }

    void  _TriggerBase::append( Callable *callable ){
      assert( callable != Nullptr );
      m_mutex.acquires();
      if(  m_callables != Nullptr && m_endCallable != Nullptr ){
        m_endCallable->m_next = callable;
        m_endCallable = callable;
      }
      else{
        m_callables = callable;
        m_endCallable = callable;
      }
      m_mutex.releases();
    }

    void  _TriggerBase::remove( Callable *callable  ){
      assert( callable != Nullptr );
      m_mutex.acquires();
      Callable *_each = m_callables;
      if( _each == callable ){
        m_callables = _each->m_next;
        if( m_callables == Nullptr ){
          m_endCallable = Nullptr;
        }
      }
      else{
        while( _each != Nullptr && _each->m_next != callable ){
          _each = _each->m_next;
        }
        if( _each != Nullptr ){
          _each->m_next = callable->m_next;
          if( _each == m_endCallable ){
            m_endCallable = _each;
          }
          delete callable;  
        }
      }
      m_mutex.releases();
    }

    Callable::Iterator _TriggerBase::find( void *obj, void *action ){
      Callable::Iterator _ret_iter;
      Callable::Iterator * _last = &_ret_iter;

      m_mutex.acquires();
      Callable *_each = m_callables;

      while( _each != Nullptr ){
        if(_each->m_isMember){
          MemberCallable *_mem = static_cast<MemberCallable *>( _each );
          if( _mem != Nullptr 
            && _mem->m_obj == obj
            && _mem->m_callableBody == action ){
              Callable::Iterator *_appended = new Callable::Iterator;
              _appended->m_callable = _each;

              _last->m_next = _appended;
              _last = _appended;          
          }
        }
        _each = _each->m_next;
      }
      m_mutex.releases();
      return _ret_iter;
    }


    Callable::Iterator _TriggerBase::findByObject( void *obj ){
      Callable::Iterator _ret_iter;
      Callable::Iterator * _last = &_ret_iter;

      m_mutex.acquires();
      Callable *_each = m_callables;

      while( _each != Nullptr ){
        if(_each->m_isMember){
          MemberCallable *_mem = static_cast<MemberCallable *>( _each );
          if( _mem != Nullptr 
            && _mem->m_obj == obj ){
              Callable::Iterator *_appended = new Callable::Iterator;
              _appended->m_callable = _each;

              _last->m_next = _appended;
              _last = _appended;          
          }
        }
        _each = _each->m_next;
      }

      m_mutex.releases();
      return _ret_iter;
    }

    Callable::Iterator _TriggerBase::findByAction( void *action ){
      Callable::Iterator _ret_iter;
      Callable::Iterator * _last = &_ret_iter;

      m_mutex.acquires();
      Callable *_each = m_callables;

      while( _each != Nullptr ){
        if( _each->m_callableBody == action ){
          Callable::Iterator *_appended = new Callable::Iterator;
          _appended->m_callable = _each;

          _last->m_next = _appended;
          _last = _appended;          
        }
        _each = _each->m_next;
      }

      m_mutex.releases();
      return _ret_iter;
    }

  }//namespace Core
}//namespace Magna