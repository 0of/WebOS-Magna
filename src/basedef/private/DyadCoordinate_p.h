#ifndef DYADCOORDINATE_P_H
#define DYADCOORDINATE_P_H

#include "../StaticTypeTrait.h"
#include "../CompilerTimeAssert.h"

namespace Magna{
   namespace Core{
     template<
       typename _type
       ,  class _type_trait =  StaticTypeTrait<_type, sint32, StaticTypeTrait<_type, float, StaticTypeTrait<_type, double> > >
     >
     class DyadCoordinatePolicy{

       __Data_Field public:
          _type m_x;
          _type m_y;

      __Constructor_Destructor public:
          DyadCoordinatePolicy()
            :m_x()
            ,m_y(){
             COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
          }
          explicit DyadCoordinatePolicy( const _type& x,const _type& y )
            :m_x ( x )
            ,m_y ( y ){
            COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
          }

          explicit DyadCoordinatePolicy( const DyadCoordinatePolicy<_type>& p )
            :m_x ( p.m_x )
            ,m_y ( p.m_y ){
            COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
          }

          ~DyadCoordinatePolicy(){

          }

        __Highlight_Property public:
          MAGNA_FORCEINLINE const _type& X() const{
            return m_x;
          }
          MAGNA_FORCEINLINE const _type& Y() const{
            return m_y;
          }
          MAGNA_FORCEINLINE _type& X() {
            return m_x;
          }
          MAGNA_FORCEINLINE _type& Y() {
            return m_y;
          }

        __Checker public:
          MAGNA_FORCEINLINE bool _isOrigin() const {
            return Comparer<_type>::isEqualToZero( m_x )
              && Comparer<_type>::isEqualToZero( m_y );
          }

          inline double _calDistanceBy( const DyadCoordinatePolicy& coord ) const{
            return std::sqrt( std::pow( static_cast<double>( m_x - coord.m_x ) , 2 )
              + std::pow(static_cast<double>( m_y - coord.m_y ), 2) );
          }

          inline double _calDistanceByOrigin() const{
            return std::sqrt( static_cast<double>( m_x * m_x + m_y * m_y ) );
          }

        __Overloaded_Methods public:
          DyadCoordinatePolicy& operator =(const DyadCoordinatePolicy<_type>& p){
            m_x = p.m_x;
            m_y = p.m_y;
            return *this;
          }

     };
     template class DyadCoordinatePolicy<float>;
     template class DyadCoordinatePolicy<double>;
     template class DyadCoordinatePolicy<sint32>;
   }//Core
}//Magna
#endif  /*  DYADCOORDINATE_P_H  */
