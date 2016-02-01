#include "RectRegion_p.h"

namespace Magna{
  namespace Core{
    /*
    template<
      typename _type
      ,  class _type_trait
    >
    void RectRegionPolicy<_type, _type_trait>::_normalizes() {
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

    template<
      typename _type
      ,  class _type_trait
    >
    bool RectRegionPolicy<_type, _type_trait>::_isOverlappedWith( const RectRegionPolicy<_type>& p ) const{
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
    */
    //template class RectRegionPolicy<float>;
    //template class RectRegionPolicy<double>;
    //template class RectRegionPolicy<sint32>;
  }//Core
}//Magna
