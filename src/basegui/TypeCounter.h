#ifndef TYPECOUNTER_H
#define TYPECOUNTER_H

#include "basedef/NullType.h"

using namespace Magna;
using namespace Core;

namespace Magna{  
   namespace GUI{
     template<typename Type, typename Next = NullType>
     class TriggerTypeCounter{
       template<typename Current, uint32 isHereditable>
       struct PrivateTypeCounter{
         enum{ value = 1 };    
         enum{ hereditableValue = isHereditable };    
       };
       
      template<uint32 isHereditable> struct PrivateTypeCounter<NullType,isHereditable>{
        enum{ value = 0 };
        enum{ hereditableValue = isHereditable };    
       };
     public:
       enum{ counter=PrivateTypeCounter<Type, Type::isHereditable>::value + Next::counter };
       enum{ hereditableCounter = PrivateTypeCounter<Type, Type::isHereditable>::hereditableValue + Next::hereditableCounter };
     };

     template<typename Type>
     class TriggerTypeCounter<Type, NullType>{
     public:
       enum{ counter=1 };
        enum{ hereditableCounter = Type::isHereditable };
     };

     template<>
     class TriggerTypeCounter<NullType, NullType>{
     public:
       enum{ counter=0 };
       enum{ hereditableCounter = 0 };
     };

    //
     template<typename Type, typename Next = NullType>
     class TypeCounter{
       template<typename Current>
       struct PrivateTypeCounter{
         enum{ value = 1 };    
       };

       template<> struct PrivateTypeCounter<NullType>{
         enum{ value = 0 };
       };
     public:
       enum{ counter=PrivateTypeCounter<Type>::value + Next::counter };
     };

     template<typename Type>
     class TypeCounter<Type, NullType>{
     public:
       enum{ counter=1 };
     };

     template<>
     class TypeCounter<NullType, NullType>{
     public:
       enum{ counter=0 };
     };
   }//GUI
}//Magna
#endif  /*  TYPECOUNTER_H  */