#include "DefaultIFrameImpl.h"

#include "render/LinearGradient.h"

namespace Magna{
  namespace GUI{
    
    DefaultIFrameImpl::DefaultIFrameImpl()
      :IFrame()
      ,m_defaultFrameBrush()
      ,m_textBrush( Color( 255, 255, 255))
      ,m_textFont(){

      LinearGradient *linearGradient = new LinearGradient ( 0, 0, 0, 28 );
      //linearGradient->setColorAt( Color( 255,255,255 ), 0.0f );
      //linearGradient->setColorAt( Color( 192,192,192 ), 0.15f );
      //linearGradient->setColorAt( Color( 128,128,128 ), 0.33f );
      //linearGradient->setColorAt( Color( 192,192,192 ), 1.0f );
      // 
      linearGradient->setColorAt( Color( 189,191,255 ), 0.0f );
      linearGradient->setColorAt( Color( 134,138,226 ), 1.0f );

      m_defaultFrameBrush = FillBrush ( linearGradient );

      m_textFont.setFontSize( 13 );
    }

    uint32 DefaultIFrameImpl::getFrameHeight() const{
      return 28;
    }

    void DefaultIFrameImpl::renderingFrame( const String& title
                                        , const IntegerSize& textSize
                                        , const uint32& frameWidth
                                        , const Image& icon
                                        , RenderingEventArgs& args  ) {
      RenderManager2D *_2d_manager = args.getRenderManager2D();
      if( _2d_manager != Nullptr ){

        Drawer<DrawerEngine::DrawerEngine_Canvas2D> _drawer;

        bool _hasGot = _2d_manager->retrieveDrawer( _drawer );

        if( _hasGot ){
          const IntegerRectRegion &_baseBoundingRect = args.getRenderingRectRegion();
          //draw base frame
          _drawer.drawRect( _baseBoundingRect );

          //draw title bar
          _drawer.pushState();    
          _drawer.setFillBrush( m_defaultFrameBrush );

          _drawer.drawRect(_baseBoundingRect.getTopLeftCoord().getX()
            , _baseBoundingRect.getTopLeftCoord().getY()
            ,  _baseBoundingRect.getWidth() 
            , 30 );
          _drawer.popState();

          //draw icon
          //margin left 4
          if( !icon.isNull() ){
            Image _scaled_icon = icon;
            _scaled_icon.scale( 24, 24 );
            _drawer.drawImage( IntegerDyadCoordinate( 2, 2 ), _scaled_icon );
          }

          //draw text
          //margin left 4
          _drawer.setFillBrush( m_textBrush );
          _drawer.setFont( m_textFont );
          _drawer.drawText(  IntegerDyadCoordinate( 28, _baseBoundingRect.getCenterCoord().getY() + 6) ,  title );

          _2d_manager->pullbackDrawer( _drawer );
        }
    
      }    
    }

  }//namespace GUI
}//namespace Magna