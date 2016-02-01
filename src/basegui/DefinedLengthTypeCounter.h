#ifndef DEFINEDLENGTHTYPECOUNTER_H
#define DEFINEDLENGTHTYPECOUNTER_H

#include "TypeCounter.h"

namespace Magna{  
   namespace GUI{
     //  16 parameters the most!//
     template<
       typename T1 = NullType
       , typename T2 = NullType
       , typename T3 =NullType
       , typename T4 = NullType
       , typename T5 =NullType
       , typename T6 = NullType
       , typename T7 =NullType
       , typename T8 = NullType
       , typename T9 =NullType
       , typename T10 = NullType
       , typename T11 =NullType
       , typename T12 = NullType
       , typename T13 =NullType
       , typename T14 = NullType
       , typename T15 =NullType
       , typename T16 = NullType
     >
     class DefinedLengthTypeCounter{
     public:
       enum { Length = TypeCounter< T1
         , TypeCounter<T2
         , TypeCounter<T3 
         , TypeCounter<T4
         , TypeCounter<T5
         , TypeCounter<T6
         , TypeCounter<T7
         , TypeCounter<T8
         , TypeCounter<T9
         , TypeCounter<T10
         , TypeCounter<T11
         , TypeCounter<T12
         , TypeCounter<T13
         , TypeCounter<T14
         , TypeCounter<T15
         , TypeCounter<T16
         > > > > > > > > > > > > > > > >::counter 
       };
     };

     template<
       typename T1 = NullType
       , typename T2 = NullType
       , typename T3 =NullType
       , typename T4 = NullType
       , typename T5 =NullType
       , typename T6 = NullType
       , typename T7 =NullType
       , typename T8 = NullType
       , typename T9 =NullType
       , typename T10 = NullType
       , typename T11 =NullType
       , typename T12 = NullType
       , typename T13 =NullType
       , typename T14 = NullType
       , typename T15 =NullType
       , typename T16 = NullType
     >
     class DefinedLengthTriggerTypeCounter{
     public:
       enum { Length = TriggerTypeCounter< T1
         , TriggerTypeCounter<T2
         , TriggerTypeCounter<T3 
         , TriggerTypeCounter<T4
         , TriggerTypeCounter<T5
         , TriggerTypeCounter<T6
         , TriggerTypeCounter<T7
         , TriggerTypeCounter<T8
         , TriggerTypeCounter<T9
         , TriggerTypeCounter<T10
         , TriggerTypeCounter<T11
         , TriggerTypeCounter<T12
         , TriggerTypeCounter<T13
         , TriggerTypeCounter<T14
         , TriggerTypeCounter<T15
         , TriggerTypeCounter<T16
         > > > > > > > > > > > > > > > >::counter ,

         HereditableLength = TriggerTypeCounter< T1
         , TriggerTypeCounter<T2
         , TriggerTypeCounter<T3 
         , TriggerTypeCounter<T4
         , TriggerTypeCounter<T5
         , TriggerTypeCounter<T6
         , TriggerTypeCounter<T7
         , TriggerTypeCounter<T8
         , TriggerTypeCounter<T9
         , TriggerTypeCounter<T10
         , TriggerTypeCounter<T11
         , TriggerTypeCounter<T12
         , TriggerTypeCounter<T13
         , TriggerTypeCounter<T14
         , TriggerTypeCounter<T15
         , TriggerTypeCounter<T16
         > > > > > > > > > > > > > > > >::hereditableCounter    
       };
     };
   }//GUI
}//Magna
#endif  /*  DEFINEDLENGTHTYPECOUNTER_H  */