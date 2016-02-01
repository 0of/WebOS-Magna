#ifndef TRIGGERTRAIT_P_H
#define TRIGGERTRAIT_P_H

#include "../NullType.h"

namespace Magna{
  namespace Core{
    //with 9 template parameters trait
    template<
      typename Arg0 = NullType
      ,typename Arg1 = NullType
      ,typename Arg2 = NullType
      ,typename Arg3 = NullType
      ,typename Arg4 = NullType
      ,typename Arg5 = NullType
      ,typename Arg6 = NullType
      ,typename Arg7 = NullType
      ,typename Arg8 = NullType
    >
    struct TriggerTrait;
    //proxy struct
    class ProxyActor{};

    template<>
    struct TriggerTrait<NullType, NullType, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType>{
      //function type checker
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)() ){}
      inline static void CheckAction( void(*)() ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      template<typename Actor = NullType>
      struct ActionTrait;

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)();
      typedef void(MAGNA_CDECL *ProxyAction)();

      template<typename Actor>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)();
      };

      //template<>struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)();
      //};
    };

    template<>struct TriggerTrait<NullType, NullType, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType>::ActionTrait<NullType>{
            typedef void(MAGNA_CDECL *Action)();
        };

    template<typename Arg0>
    struct TriggerTrait<Arg0, NullType, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType>{
      //function type checker
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      template<typename Actor = NullType, typename SpecHelper= void>
      struct ActionTrait;

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0);

      template<typename Actor, typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 );
      };
      //template<>struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0 );
      //};
    };


        template<typename Arg0>
    template<typename SpecHelper> struct TriggerTrait<Arg0, NullType, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType> ::ActionTrait<NullType, SpecHelper>{
            typedef void(MAGNA_CDECL *Action)( Arg0 );
        };


    template<typename Arg0, typename Arg1>
    struct TriggerTrait<Arg0, Arg1, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType>{
      //function type checker
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1);

      template<typename Actor = NullType, typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor, typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1 );
      };

      //template<>struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1 );
      //};
    };

        template<typename Arg0, typename Arg1>
        template<typename SpecHelper>struct TriggerTrait<Arg0, Arg1, NullType, NullType
      ,NullType,NullType,NullType,NullType,NullType>::ActionTrait<NullType, SpecHelper>{
            typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1 );
        };

    template<typename Arg0, typename Arg1, typename Arg2>
    struct TriggerTrait<Arg0, Arg1, Arg2, NullType
      ,NullType,NullType,NullType,NullType,NullType>{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1,Arg2);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1,Arg2);

      template<typename Actor = NullType, typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor, typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2 );
      };

      //template<>struct ActionTrait<NullType>{
        //typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2 );
      //};
    };


        template<typename Arg0, typename Arg1, typename Arg2>
    template<typename SpecHelper>struct TriggerTrait<Arg0, Arg1, Arg2, NullType
      ,NullType,NullType,NullType,NullType,NullType>::ActionTrait<NullType,SpecHelper>{
        typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2 );
        };

    template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3>
    struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,NullType,NullType,NullType,NullType,NullType>{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1,Arg2,Arg3);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1,Arg2,Arg3);

      template<typename Actor = NullType, typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor, typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3 );
      };

      //template<> struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3 );
      //};
    };

        template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3>
    template<typename SpecHelper> struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,NullType,NullType,NullType,NullType,NullType>::ActionTrait<NullType,SpecHelper>{
        typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3 );
      };

    template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3
        , typename Arg4>
    struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,NullType,NullType,NullType,NullType>{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3,Arg4) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3,Arg4) ){}

      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1,Arg2,Arg3,Arg4);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1,Arg2,Arg3,Arg4);

      template<typename Actor = NullType,  typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor,  typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4);
      };

      //template<>struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4 );
      //};
    };

        template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3
        , typename Arg4>
        template<typename SpecHelper> struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,NullType,NullType,NullType,NullType>::ActionTrait<NullType,SpecHelper >{
            typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4 );
        };

    template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5>
    struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,NullType,NullType,NullType>{
    public:
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5);

      template<typename Actor = NullType,  typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor,  typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5 );
      };

      //template<>struct ActionTrait<NullType>{
      //public:
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5 );
      //};
    };


    template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5>
    template<typename SpecHelper> struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,NullType,NullType,NullType>::ActionTrait<NullType,SpecHelper>{
            typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5 );
        };

    template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5
          , typename Arg6>
    struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,Arg6,NullType,NullType>{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6);

      template<typename Actor = NullType,  typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor,  typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6 );
      };

      //template<> struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6 );
      //};
    };

        template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5
          , typename Arg6>
        template<typename SpecHelper>  struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,Arg6,NullType,NullType>::ActionTrait<NullType,SpecHelper>{
        typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6 );
        };

    template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3
        , typename Arg4
        , typename Arg5
        , typename Arg6
        , typename Arg7>
    struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,Arg6,Arg7,NullType>{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7);

      template<typename Actor = NullType,  typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor,  typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7 );
      };

      //template<>struct ActionTrait<NullType>{
      //  typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7 );
      //};
    };


        template<typename Arg0
        , typename Arg1
        , typename Arg2
        , typename Arg3
        , typename Arg4
        , typename Arg5
        , typename Arg6
        , typename Arg7>
    template<typename SpecHelper>struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,Arg6,Arg7,NullType>::ActionTrait<NullType,SpecHelper>{
      typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7 );
    };


    template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5
          , typename Arg6
          , typename Arg7
          , typename Arg8>
    struct TriggerTrait{
      template<typename Class>
      inline static void CheckAction( void(MAGNA_THISCALL Class::*)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8) ){}
      inline static void CheckAction( void(MAGNA_CDECL *)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8) ){}
      template<typename Class>
      static void CheckAction( Class ){
        COMPILTER_TIME_ASSERT( false,  Must_Be_A_Function_Pointer )
      }

      typedef void(MAGNA_THISCALL ProxyActor::*ProxyMemberAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);
      typedef void(MAGNA_CDECL *ProxyAction)(Arg0,Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8);

      template<typename Actor = NullType,  typename SpecHelper= void>
      struct ActionTrait;

      template<typename Actor,  typename SpecHelper>
      struct ActionTrait{
        typedef void(MAGNA_THISCALL Actor::*Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7,Arg8 arg8 );
      };

      //template<>struct ActionTrait<NullType>{
            //typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7,Arg8 arg8 );
      //};
    };

        template<typename Arg0
          , typename Arg1
          , typename Arg2
          , typename Arg3
          , typename Arg4
          , typename Arg5
          , typename Arg6
          , typename Arg7
          , typename Arg8>
    template<typename SpecHelper>struct TriggerTrait<Arg0, Arg1, Arg2, Arg3
      ,Arg4,Arg5,Arg6,Arg7,Arg8>::ActionTrait<NullType, SpecHelper>{
        typedef void(MAGNA_CDECL *Action)( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7,Arg8 arg8 );
        };
  }//namespace Core
}//namespace Magna

#endif  /*  TRIGGERTRAIT_P_H  */
