#include "ShadowAppearanceEffect.h"

namespace Magna{
  namespace Render{
    
    ShadowAppearanceEffect::ShadowAppearanceEffect()
      :AppearanceEffect()
      ,m_shadowBlurGranularity( 20 )
      ,m_shadowColor( Color( 64, 64, 64 ) )
      ,m_shadowOffset( 0, 0 ){

    }

    ShadowAppearanceEffect::ShadowAppearanceEffect( uint32 g, const Color&c, const IntegerDyadCoordinate& o)
      :AppearanceEffect()
      ,m_shadowBlurGranularity( g )
      ,m_shadowColor( c )
      ,m_shadowOffset( o){

    }

    ShadowAppearanceEffect::ShadowAppearanceEffect( const ShadowAppearanceEffect& e)
      :AppearanceEffect()
      ,m_shadowBlurGranularity( e.m_shadowBlurGranularity )
      ,m_shadowColor( e.m_shadowColor )
      ,m_shadowOffset( e.m_shadowOffset ){

    }

    ShadowAppearanceEffect::~ ShadowAppearanceEffect(){

    }

    void ShadowAppearanceEffect::setBlurGranularity( uint32 g){
      m_shadowBlurGranularity = g;
    }
    void ShadowAppearanceEffect::setShadowColor( const Color& c ){
      m_shadowColor = c;
    }
    void ShadowAppearanceEffect::setShadowOffset( const IntegerDyadCoordinate& o){
      m_shadowOffset = o;
    }

    String ShadowAppearanceEffect::toString() const{
      OutStringStream _outer ;
      _outer << L"context.shadowBlur=" << m_shadowBlurGranularity
        << L";context.shadowColor=" << m_shadowColor.toString()
        << L";context.shadowOffsetX=" << m_shadowOffset.getX()
        << L";context.shadowOffsetY=" << m_shadowOffset.getY()
        << L";";
      return _outer.str();
    }

  }//namespace Render
}//namespace Magna