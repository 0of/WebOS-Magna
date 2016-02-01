#ifndef COMPARER_P_H
#define COMPARER_P_H

#include "../BaseTypes.h"
#include "../StaticTypeTrait.h"
#include "../CompilerTimeAssert.h"

//STL
#include <limits>
#include <cmath>

namespace Magna{
   namespace Core{
     template<
            typename _Type
            , class _TypeTrait = DigitStaticTypeTrait<_Type>
          >
     class DigitComparer{
       public:
         MAGNA_FORCEINLINE static bool isEqualTo( const _Type& instance, const _Type& compareOne ) {
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return instance == compareOne;
         }
         MAGNA_FORCEINLINE static bool isEqualToZero( const _Type& instance ) {
          COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
           return instance == 0;
         }
         MAGNA_FORCEINLINE static bool MAGNA_NOTHROW isHigherThanZero( const _Type& instance ) {
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
           return instance > 0;
         }
         MAGNA_FORCEINLINE static bool  MAGNA_NOTHROW isLowerThanZero( const _Type& instance ){
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
           return instance < 0;
         }
         MAGNA_FORCEINLINE static bool MAGNA_NOTHROW isHigherThan( const _Type& instance, const _Type& compareOne ){
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
           return instance > compareOne;
         }
         MAGNA_FORCEINLINE static bool MAGNA_NOTHROW isLowerThan( const _Type& instance, const _Type& compareOne ){
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
           return instance < compareOne;
         }
     };

     template<
            typename _Type
            , class _TypeTrait = RealStaticTypeTrait<_Type>
          >
     class RealComparer{
       public:
         MAGNA_FORCEINLINE static bool isEqualTo( const _Type& instance, const _Type& compareOne ) {
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return isAlmostToZero( instance - compareOne );
         }

         MAGNA_FORCEINLINE static bool isAlmostToZero( const _Type& instance ) {
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return std::abs( instance ) < std::numeric_limits<_Type>::epsilon() ;
         }
        MAGNA_FORCEINLINE static bool isEqualToZero( const _Type& instance ) {
            return isAlmostToZero( instance );
         }
         MAGNA_FORCEINLINE static bool isHigherThanZero( const _Type& instance ){
            COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return instance > std::numeric_limits<_Type>::epsilon();
         }
        MAGNA_FORCEINLINE static bool isLowerThanZero( const _Type& instance ){
            COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return instance < -std::numeric_limits<_Type>::epsilon();
         }
         MAGNA_FORCEINLINE static bool isHigherThan( const _Type& instance, const _Type& compareOne ){
            COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
            return instance - compareOne > std::numeric_limits<_Type>::epsilon();
         }
         MAGNA_FORCEINLINE static bool MAGNA_NOTHROW isLowerThan( const _Type& instance, const _Type& compareOne ){
           COMPILTER_TIME_ASSERT((_TypeTrait::isMatched), Shall_Matches_Integer_Type)
             return instance - compareOne < -std::numeric_limits<_Type>::epsilon();
         }
     };


   }//Core
}//Magna
#endif  /*  COMPARER_P_H  */
