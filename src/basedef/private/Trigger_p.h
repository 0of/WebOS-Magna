#ifndef TRIGGER_P_H
#define TRIGGER_P_H

#include "../basedef_lib.h"

#include "Callable_p.h"

#include "../SpinMutex.h"
#include "../SystemDef.h"
#include "../BaseTypes.h"
#include "../Uncopyable.h"

#include <cassert>

namespace Magna{
  namespace Core{

    class BASEDEF_LIB_EXPORT _TriggerBase : Uncopyable{
      __Constructor_Destructor protected:
        _TriggerBase();
        ~_TriggerBase();

      public:
        void block();
        void resume();

        void clear();

      protected:
        void append( Callable *callable );
        void remove( Callable *callable  );

        Callable::Iterator find( void *obj, void *action );
        Callable::Iterator findByObject( void *obj );
        Callable::Iterator findByAction( void *action );

      __Data_Field protected:
        Callable *m_callables;
        Callable *m_endCallable;

        SpinMutex  m_mutex;
    };

    template<typename Trait>
    class _TriggerImpEBody  : public _TriggerBase{
      __Constructor_Destructor public:
        _TriggerImpEBody() : _TriggerBase(){}
        ~_TriggerImpEBody() {}

    public:
      template<typename Actor>
      void connectAction(Actor *actorObj, typename Trait::template ActionTrait<Actor>::Action action, bool blockable = false ){
        assert( actorObj != Nullptr );
        assert( action != Nullptr );

          MemberCallable *_gen_callable
            = new MemberCallable( *reinterpret_cast<void **>( &action),actorObj, blockable );

          append( _gen_callable );
        }

        void connectAction( typename Trait::template ActionTrait<>::Action action,bool blockable = false ){
          assert( action != Nullptr );

          StaticCallable *_gen_callable
            = new StaticCallable( *reinterpret_cast<void **>( &action) , blockable );

          append( _gen_callable );
        }


        template<typename Actor>
        void disconnectAction( Actor *actorObj , typename Trait::template ActionTrait<Actor>::Action action ){
          assert( actorObj != Nullptr );

          Callable::Iterator  _found_callables = find( actorObj, *reinterpret_cast<void **>( &action) );

          while( _found_callables.hasNext() ){
            Callable *_each = _found_callables.next();
            remove( _each );
          }
        }

        template<typename Actor>
        void resumeByObject( Actor *actorObj ){
          assert( actorObj != Nullptr );

          Callable::Iterator  _found_callables = find( actorObj );

          m_mutex.acquires();
          while( _found_callables.hasNext() ){
            Callable *_each = _found_callables.next();
            _each->m_blocked = false;
          }
          m_mutex.releases();
        }

        template<typename Action>
        void resumeByAction( Action action ){
          Trait::CheckAction( action );
          Callable::Iterator  _found_callables = findByAction( *reinterpret_cast<void **>( &action) );

          m_mutex.acquires();
          while( _found_callables.hasNext() ){
            Callable *_each = _found_callables.next();
            _each->m_blocked = false;
          }
          m_mutex.releases();
        }

        template<typename Action>
        void blockByAction( Action action ){
          Trait::CheckAction( action );

          Callable::Iterator  _found_callables = findByAction( *reinterpret_cast<void **>( &action) );

          m_mutex.acquires();
          while( _found_callables.hasNext() ){
            Callable *_each = _found_callables.next();
            if( _each->m_blockable ){
              _each->m_blocked = !false;
            }
          }
          m_mutex.releases();
        }
    };


  }//namespace Core
}//namespace Magna

#endif  /*  TRIGGER_P_H  */
