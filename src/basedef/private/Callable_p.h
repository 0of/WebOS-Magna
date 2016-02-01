#ifndef CALLABLE_P_H
#define CALLABLE_P_H

#include "../BaseTypes.h"
#include "../SystemDef.h"

namespace Magna{
  namespace Core{
    class Callable {
      friend class _TriggerBase;
      template<typename Trait> friend class _TriggerImpEBody;
      template<
        typename Arg0
        ,typename Arg1
        ,typename Arg2
        ,typename Arg3
        ,typename Arg4
        ,typename Arg5
        ,typename Arg6
        ,typename Arg7
        ,typename Arg8
      >
      friend class Trigger;
      class Iterator{
      __Constructor_Destructor public:
        Iterator() : m_next( Nullptr ), m_callable( Nullptr ){}
        Iterator( const Iterator& iter ) : m_next( iter.m_next ), m_callable( iter.m_callable ){}
      public:
        bool hasNext() const{
          return m_next != Nullptr;
        }

        Callable *next(){
          if( m_next != Nullptr ){
            Iterator *_next = m_next;
            m_callable= m_next->m_callable;
            m_next = _next->m_next;

            delete _next;
          }
          return m_callable;
        }

        //the next pointer of first node is Nullptr
        Iterator *m_next;
        Callable *m_callable;
      };
      __Constructor_Destructor protected:
      explicit Callable( void *callableBody, bool isMember, bool blockable ) : m_next( Nullptr ), m_callableBody( callableBody ), m_blocked( false )
        ,m_blockable( blockable ), m_isMember( isMember )
        ,m_reserve( 0 ){}
      Callable *m_next;

      void *m_callableBody;

      uint32 m_blocked : 8;
      uint32 m_blockable : 8;
      uint32 m_isMember : 8;
      uint32 m_reserve : 8;
    };

    class MemberCallable : protected Callable{
      friend class _TriggerBase;
      template<typename Trait> friend class _TriggerImpEBody;
      template<
        typename Arg0
        ,typename Arg1
        ,typename Arg2
        ,typename Arg3
        ,typename Arg4
        ,typename Arg5
        ,typename Arg6
        ,typename Arg7
        ,typename Arg8
      >
      friend class Trigger;
    __Constructor_Destructor private:
      explicit MemberCallable( void *body, void *obj, bool blockable ) : Callable( body, !false, blockable ), m_obj( obj ){}
    __Data_Field private:
      void *m_obj;
  };

    class StaticCallable : protected Callable{
      friend class _TriggerBase;
      template<typename Trait> friend class _TriggerImpEBody;
      template<
        typename Arg0
        ,typename Arg1
        ,typename Arg2
        ,typename Arg3
        ,typename Arg4
        ,typename Arg5
        ,typename Arg6
        ,typename Arg7
        ,typename Arg8
      >
      friend class Trigger;
    __Constructor_Destructor private:
      explicit StaticCallable(void *body, bool blockable) : Callable( body, false, blockable ){}
    };
  }//namespace Core
}//namespace Magna

#endif  /*  CALLABLE_P_H  */
