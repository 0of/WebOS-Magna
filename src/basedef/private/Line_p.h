#ifndef LINE_P_H
#define LINE_P_H

#include "../BaseTypes.h"
#include "../SystemDef.h"
#include "../StaticTypeTrait.h"
#include "../CompilerTimeAssert.h"

#include "../Comparer.h"
#include "../DyadCoordinate.h"

//STL
#include <cmath>
#include <numeric>

namespace Magna{
   namespace Core{
     template<typename _type>
     class LinePolicy{
      __Constructor_Destructor protected:
        LinePolicy(): m_p1(), m_p2(){

        }

        explicit LinePolicy( const DyadCoordinate<_type> p1, const DyadCoordinate<_type> p2 )
          :m_p1( p1 )
          ,m_p2( p2 ){

        }

        LinePolicy( const LinePolicy<_type>& line )
          :m_p1( line.m_p1 )
          ,m_p2( line.m_p2 ){

        }

        ~LinePolicy(){

        }
    __Highlight_Property protected:
      MAGNA_FORCEINLINE DyadCoordinate<_type> & _P1() {
        return m_p1;
      }
      MAGNA_FORCEINLINE DyadCoordinate<_type> & _P2() {
        return m_p2;
      }
      MAGNA_FORCEINLINE const DyadCoordinate<_type> & _P1() const{
        return m_p1;
      }
      MAGNA_FORCEINLINE const DyadCoordinate<_type> & _P2()const {
        return m_p2;
      }
     private:
       typedef DyadCoordinate<_type> row_vector;

    __Getter protected:
       MAGNA_FORCEINLINE double _getLength() const{
         return std::sqrt( std::pow( m_p1.getX() - m_p2.getX(), 2.0 ) + std::pow( m_p1.getY() - m_p2.getY() , 2.0 ) ) ;
       }

       MAGNA_FORCEINLINE double _getAngle() const{
         return std::atan2( static_cast<double>(m_p2.getY() - m_p1.getY()), m_p2.getX() - m_p1.getX() ) * 180.0 / 3.1415926;
       }
       MAGNA_FORCEINLINE  double _getAngleTo( const LinePolicy<_type>& line ) const{
         return _getAngle() - line._getAngle();
       }

      protected:
        uint32 _intersectsWith( const LinePolicy<_type>& line ){
          row_vector rv_1( m_p1.getX() - m_p1.getX(), m_p1.getY() - m_p2.getY() );
          row_vector rv_2( line.m_p1.getX() - line.m_p2.getX(),  line.m_p1.getY() - line.m_p2.getY() );
          uint32 ret = 0;
          if( Comparer<double>::isAlmostToZero( dyad_dimension_square_det( rv_1, rv_2 ) )  ){
            ret = 3;//parallel
          }
          else{
            row_vector rv_master_p1_to_slave_p2(m_p1.getX() - line.m_p2.getX(), m_p1.getY()- line.m_p2.getY() );
            if( Comparer<double>::isHigherThanZero( dyad_dimension_square_det(rv_master_p1_to_slave_p2, rv_2) ) ){

              row_vector rv_slave_p1_to_master_p2(line.m_p1.getX() - m_p2.getX(), line.m_p1.getY()- m_p2.getY() );
              if(Comparer<double>::isLowerThanZero( dyad_dimension_square_det(rv_slave_p1_to_master_p2, rv_1) ) ){
                ret = 1;
              }
            }
          }
          return ret;
        }

      private:
        inline double dyad_dimension_square_det( const row_vector& rv_1, const row_vector& rv_2 ){
          return rv_1.getX() * rv_2.getY() - rv_1.getY() * rv_2.getX();
        }

      __Overloaded_Methods protected:
        LinePolicy & operator = ( const LinePolicy<_type>& p ){
          m_p1 = p.m_p1;
          m_p2 = p.m_p2;
          return *this;
        }

        bool operator == ( const LinePolicy<_type>& p ){
          return (m_p1 == p.m_p1) && (m_p2 == p.m_p2);
        }

      __Data_Field protected:
        DyadCoordinate<_type> m_p1;
        DyadCoordinate<_type> m_p2;
     };

   }//Core
}//Magna
#endif  /*  LINE_P_H  */
