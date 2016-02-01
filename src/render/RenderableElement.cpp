#include "RenderableElement.h"

namespace Magna{
  namespace Render{
    RenderableElement::RenderableElement()
      :AbstractedElementNativeSource(L"canvas")
      ,m_renderableRect()
      ,m_manager( Nullptr ){

    }

    RenderableElement::RenderableElement( const String& s)
      :AbstractedElementNativeSource( s )
      ,m_renderableRect()
      ,m_manager( Nullptr ){

    }

    RenderableElement::RenderableElement( RenderManager *manager )
      :AbstractedElementNativeSource(L"canvas")
      ,m_renderableRect()
      ,m_manager( manager ){

    }

    RenderableElement::~RenderableElement(){

    }

    /*
    void RenderableElement::setSize( const IntegerSize& size ){
      m_mutex.accquires();
      m_renderableRect.setSize( size );
      m_mutex.releases();
    }

    void RenderableElement::setPos( const IntegerDyadCoordinate& pos ){
      m_mutex.accquires();
      m_renderableRect.setTopLeftCoord( pos );
      m_mutex.releases();
    }
    */

  }//namespace Render
}//namespace Magna
