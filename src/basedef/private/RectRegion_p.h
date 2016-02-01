#ifndef RECTREGION_P_H
#define RECTREGION_P_H

#pragma warning( disable: 4661 )

#include "../SystemDef.h"
#include "../BaseTypes.h"
#include "../StaticTypeTrait.h"

#include "../Comparer.h"
#include "../Size.h"
#include "../DyadCoordinate.h"
#include "../basedef_lib.h"

//STL
#include <limits>

namespace Magna{
   namespace Core{
     template<
          typename _type
          ,  class _type_trait =  StaticTypeTrait<_type, sint32, StaticTypeTrait<_type, float, StaticTypeTrait<_type, double> > >
          >
     class BASEDEF_LIB_EXPORT RectRegionPolicy{
       __Constants public:
         enum InvalidType{
           //all means bottom right coordinate stands -
          Valid = 0x00, StandsLeftSide = 0x01, StandsTopSide = 0x02, StandsLeftTopSide = 0x03
         };

       __Constructor_Destructor public:
         RectRegionPolicy()
           :m_topLeftCoord()
          ,m_bottomRightCoord(){

         }

         explicit RectRegionPolicy( const DyadCoordinate<_type>& topLeftCoord, const DyadCoordinate<_type>& bottomRightCoord )
           :m_topLeftCoord( topLeftCoord )
           ,m_bottomRightCoord( bottomRightCoord ){
          _normalizes();
         }

         explicit RectRegionPolicy( const DyadCoordinate<_type>& topLeftCoord, const Size<_type>& rectSize )
           :m_topLeftCoord( topLeftCoord )
           ,m_bottomRightCoord( topLeftCoord.translatesToEach( rectSize.getWidth(), rectSize.getHeight() ) ){
          _normalizes();
         }

         explicit RectRegionPolicy(  const DyadCoordinate<_type>& topLeftCoord, const _type& width, const _type& height )
           :m_topLeftCoord( topLeftCoord )
           ,m_bottomRightCoord( topLeftCoord.translatesToEach( width, height ) ){
          _normalizes();
         }

        RectRegionPolicy( const RectRegionPolicy<_type>& p ){
          ::memcpy( this, &p, sizeof( RectRegionPolicy<_type> ) );
          _normalizes();
         }

         ~RectRegionPolicy(){

         }

       __Checker public:
         bool _isOverlappedWith( const RectRegionPolicy<_type>& p ) const{
           const _type& xDifference = p.m_bottomRightCoord.getX()- m_bottomRightCoord.getX();
           const _type& yDifference = p.m_bottomRightCoord.getY()- m_bottomRightCoord.getY();
           bool result = false;
           if( Comparer<_type>::isHigherThanZero( xDifference ) ){
             if( Comparer<_type>::isHigherThanZero( yDifference ) ){
               if(  Comparer<_type>::isHigherThan( m_bottomRightCoord.getX(), p.m_topLeftCoord.getX() )
                 && Comparer<_type>::isHigherThan( m_bottomRightCoord.getY(), p.m_topLeftCoord.getY() ) ){
                   result = true;
               }
             }
             else {
               if(  Comparer<_type>::isHigherThan( m_bottomRightCoord.getX(), p.m_topLeftCoord.getX() )
                 && Comparer<_type>::isLowerThan(  m_topLeftCoord.getY(), p.m_bottomRightCoord.getY()) ){
                   result = true;
               }
             }
           }
           else{
             if( Comparer<_type>::isHigherThanZero( yDifference ) ){
               if( Comparer<_type>::isLowerThan(  m_topLeftCoord.getX(), m_topLeftCoord.getX() )
                 && Comparer<_type>::isLowerThan( m_topLeftCoord.getY(), p.m_topLeftCoord.getY()) ){
                   result = true;
               }
             }
             else {
               if( Comparer<_type>::isLowerThan(m_topLeftCoord.getX() , p.m_bottomRightCoord.getX())
                 && Comparer<_type>::isHigherThan( m_bottomRightCoord.getY() , p.m_topLeftCoord.getY() ) ){
                   result = true;
               }
               if( Comparer<_type>::isLowerThan( m_topLeftCoord.getX(), p.m_bottomRightCoord.getX())
                 && Comparer<_type>::isHigherThan( m_bottomRightCoord.getY(),  p.m_topLeftCoord.getY()) ){
                   result = true;
               }
             }
           }
           return result;
         }

       __Setter public:
         MAGNA_NOINLINE void _setTopLeftCoord( const DyadCoordinate<_type>& topLeftCoord ){
           if( Comparer<_type>::isHigherThan( m_bottomRightCoord.getX() , topLeftCoord.getX() ) ){
             m_topLeftCoord.setX( topLeftCoord.getX() ) ;
           }
           else{
             m_topLeftCoord.setX( m_bottomRightCoord.getX() );
             m_bottomRightCoord.setX( topLeftCoord.getX() );
           }

           if( Comparer<_type>::isHigherThan( m_bottomRightCoord.getY() , topLeftCoord.getY() ) ){
             m_topLeftCoord.setY( topLeftCoord.getY() ) ;
           }
           else{
             m_topLeftCoord.setY( m_bottomRightCoord.getY() );
             m_bottomRightCoord.setY( topLeftCoord.getY() );
           }
         }

        MAGNA_NOINLINE void _setBottomRightCoord( const DyadCoordinate<_type>& bottomRightCoord ){
           if(  Comparer<_type>::isHigherThan( bottomRightCoord.getX(), m_topLeftCoord.getX() ) ){
             m_bottomRightCoord.setX( bottomRightCoord.getX() );
           }
           else{
             m_bottomRightCoord.setX( m_topLeftCoord.getX() );
             m_topLeftCoord.setX( bottomRightCoord.getX() );
           }

           if( Comparer<_type>::isHigherThan( bottomRightCoord.getY() , m_topLeftCoord.getY() ) ){
             m_bottomRightCoord.setY( bottomRightCoord.getY() );
           }
           else{
             m_bottomRightCoord.setY( m_topLeftCoord.getY() );
             m_topLeftCoord.setY( bottomRightCoord.getY() );
           }
         }

        MAGNA_NOINLINE void _setTopRightCoord( const DyadCoordinate<_type>& topRightCoord ){
          if( Comparer<_type>::isHigherThan( topRightCoord.getX(), m_topLeftCoord.getX() ) ){
            m_bottomRightCoord.setX(  topRightCoord.getX() );
          }
          else{
            m_bottomRightCoord.setX( m_topLeftCoord.getX() );
            m_topLeftCoord.setX( topRightCoord.getX() );
          }

          if( Comparer<_type>::isHigherThan( topRightCoord.getY(), m_bottomRightCoord.getY() ) ){
            m_topLeftCoord.setY( topRightCoord.getY() );
          }
          else{
            m_topLeftCoord.setY( m_bottomRightCoord.getY());
            m_bottomRightCoord.setY( topRightCoord.getY() );
          }
        }

        MAGNA_NOINLINE void _setBottomLeftCoord( const DyadCoordinate<_type>& bottomLeftCoord ){
          if(  Comparer<_type>::isHigherThan(  bottomLeftCoord.getX(), m_topLeftCoord.getX() ) ){
            m_bottomRightCoord.setX( bottomLeftCoord.getX() );
          }
          else{
            m_bottomRightCoord.setX( m_topLeftCoord.getX() );
            m_topLeftCoord.setX( bottomLeftCoord.getX() );
          }

          if( Comparer<_type>::isHigherThan( bottomLeftCoord.getY(), m_bottomRightCoord.getY() ) ){
            m_topLeftCoord.setY( bottomLeftCoord.getY() );
          }
          else{
            m_topLeftCoord.setY( m_bottomRightCoord.getY() );
            m_bottomRightCoord.setY(  bottomLeftCoord.getY() );
          }
        }

      public:
        inline InvalidType  _isValid() const{
          uint32 resultType = RectRegionPolicy::Valid;
          if( Comparer<_type>::isLowerThan( m_bottomRightCoord.getX(), m_bottomRightCoord.getX() ) ){
            resultType |= RectRegionPolicy::StandsLeftSide;
          }

          if( Comparer<_type>::isLowerThan( m_bottomRightCoord.getY(), m_bottomRightCoord.getY() ) ){
            resultType |= RectRegionPolicy::StandsTopSide;
          }

          return static_cast<InvalidType>(resultType);
        }
        void _normalizes() {
          InvalidType result = _isValid();
          if( !result ){
            return;
          }

          if(  result & StandsLeftSide ){
            _type swap = m_bottomRightCoord.getX();
            m_bottomRightCoord.setX( m_topLeftCoord.getX() );
            m_topLeftCoord.setX( swap );
            ///Only for integer swap
            ///m_bottomRightCoord.getX()^= m_topLeftCoord.getX()\
            ///  ^= m_bottomRightCoord.getX() ^= m_topLeftCoord.getX();
          }

          if( result & StandsTopSide ){
            _type swap = m_bottomRightCoord.getY();
            m_bottomRightCoord.setY( m_topLeftCoord.getY() );
            m_topLeftCoord.setY( swap );
            ///Only for integer swap
            ///m_bottomRightCoord.getY()^= m_topLeftCoord.getY()\
            ///  ^= m_bottomRightCoord.getY()^= m_topLeftCoord.getY();
          }
        }

      __Highlight_Property public:
         MAGNA_FORCEINLINE DyadCoordinate<_type> & _TopLeftCoord(){
           return m_topLeftCoord;
         }
         MAGNA_FORCEINLINE DyadCoordinate<_type> & _BottomRightCoord(){
           return m_bottomRightCoord;
         }
         MAGNA_FORCEINLINE const DyadCoordinate<_type> & _TopLeftCoord() const{
           return m_topLeftCoord;
         }
         MAGNA_FORCEINLINE const DyadCoordinate<_type> & _BottomRightCoord() const{
           return m_bottomRightCoord;
         }

      __Overloaded_Methods public:
         inline RectRegionPolicy<_type> & operator = ( const RectRegionPolicy<_type>& p ){
           ::memcpy( this, &p, sizeof( RectRegionPolicy<_type> ) );
           return *this;
         }

      __Data_Field private:
        DyadCoordinate<_type> m_topLeftCoord;
        DyadCoordinate<_type> m_bottomRightCoord;
     };

    // template class RectRegionPolicy<float>;
     //template class RectRegionPolicy<double>;
     //template class RectRegionPolicy<sint32>;
   }//Core
}//Magna

#endif  /*  RECTREGION_P_H  */
