#include "StaticTypeTrait.h"
/*
template
    <
        typename T
        ,typename C
        ,class R
    >
class StaticTypeTrait{
  private:
    template<typename _type>
    struct PrivateTypeTrait{
      typedef char marker[2];
    };

    template<>
    struct PrivateTypeTrait<C>{
      typedef char marker;
    };

    enum{ _matched=(sizeof PrivateTypeTrait<T>::marker\
          ==sizeof PrivateTypeTrait<C>::marker) || R::_matched};

  public:
    StaticTypeTrait(){
      CompilerTimeAssert(_matched,Type_Shall_Match_)
    }
};

template
    <
        typename T
        ,typename C
    >
class StaticTypeTrait<T,C,NullType>{
  private:
    template<typename _type>
    struct PrivateTypeTrait{
      typedef char marker[2];
    };

    template<>
    struct PrivateTypeTrait<C>{
      typedef char marker;
    };

    enum{ _matched=(sizeof PrivateTypeTrait<T>::marker\
      ==sizeof PrivateTypeTrait<C>::marker) };
};
*/



