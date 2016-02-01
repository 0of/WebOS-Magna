#include "ButtonImplementor.h"

#include "Button.h"

#include "render/Gradient.h"
#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "qt_glue/FontMetrics.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{

    ButtonImplementor::ButtonImplementor( Button & bindingButton )
      :ControllerImplementor()
      ,m_checkable( false )
      ,m_toggleable( false )
      ,m_isReleased( !false )
      ,m_isPressed( false )
      ,m_isHovered( false )
      ,m_checked( false )
      ,m_toggled( false )
      ,m_hasHoverParaSet( false )
      ,m_hoverIcon()
      ,m_hoveredBrush()
      ,m_text( L"OK" )
      ,m_icon()
      ,m_pressedIcon()
      ,m_bindingGroup( Nullptr )
      ,m_groupIndex( 65536 )
      ,m_fontBrush()
      ,m_bindingButton( bindingButton ){    

      const auto &_topLeftCoord = bindingButton.getBoundingRectRegion().getTopLeftCoord();
      const auto & _bottonRightCoord = bindingButton.getBoundingRectRegion().getBottomRightCoord();

        LinearGradient *pressed_gradient = new LinearGradient (_topLeftCoord.getX() 
          , _topLeftCoord.getY()
          , _topLeftCoord.getX() 
          , _bottonRightCoord.getY() );
        pressed_gradient->setColorAt( Color( 128,128,128 ), 0.0 );
        pressed_gradient->setColorAt( Color( 255,255,255 ), 1.0 );
    
      m_pressedBrush = FillBrush( pressed_gradient );

      //measure text
      _remeasureText();
    }

    ButtonImplementor::~ButtonImplementor(){

      if( m_bindingGroup != Nullptr ){
        m_bindingGroup->removeButtonAt( m_groupIndex );
      }

    }

    void ButtonImplementor::mousePressed( MouseEventArgs& event ){
      if( event.isAccepted() ){
        m_isPressed = !false;

        m_bindingButton.OncePressed.triggers();

        //update
        m_bindingButton.update();    
      }
    }

    void ButtonImplementor::mouseReleased( MouseEventArgs& event ){
      if( event.isAccepted() ){
        m_isPressed = false;

        m_bindingButton.OnceReleased.triggers();
        m_bindingButton.OnceClicked.triggers();

        if( m_toggleable ){
          m_toggled = !m_toggled;
          m_bindingButton.OnceToggled.triggers( m_toggled );

          if( m_bindingGroup != Nullptr ){
            if( m_toggled != false ){
              m_bindingGroup->setButtonToggled(m_groupIndex);
              //m_bindingGroup->OnceButtonToggled.triggers( m_groupIndex );
            }
            else{
              m_bindingGroup->setButtonUntoggled( m_groupIndex );
              //m_bindingGroup->OnceButtonUntoggled.triggers( m_groupIndex );
            }
          }      
        }

        m_bindingButton.update();  
        

        if( m_checkable ){
          m_checked = !m_checked;
          m_bindingButton.OnceChecked.triggers( m_checked );
        }      

      }
    }

    /*
    void ButtonImplementor::mouseClicked( MouseEventArgs& event ){
      if( event.isAccepted() ){
        m_isPressed = !false;

        m_bindingButton.OnceClicked.triggers();

        if( m_toggleable ){
          m_toggled = !m_toggled;
          m_bindingButton.OnceToggled.triggers( m_toggled );

          if( m_bindingGroup != Nullptr ){
            if( m_toggled != false ){
              m_bindingGroup->setButtonToggled(m_groupIndex);
              //m_bindingGroup->OnceButtonToggled.triggers( m_groupIndex );
            }
            else{
              m_bindingGroup->setButtonUntoggled( m_groupIndex );
              //m_bindingGroup->OnceButtonUntoggled.triggers( m_groupIndex );
            }
          }      
        }

        if( m_checkable ){
          m_checked = !m_checked;
          m_bindingButton.OnceChecked.triggers( m_checked );
        }      
      }
    }
    */

    void ButtonImplementor::rendering( RenderingEventArgs& eventArgs ){
      if( eventArgs.isAccepted() ){
        auto *_2d_manager = eventArgs.getRenderManager2D();
        if( _2d_manager != Nullptr ){
          Canvas2DDrawer _drawer;
          if( _2d_manager->retrieveDrawer( _drawer ) != false ){
            //normal state
            /*
            _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
            _drawer.pushState();

            if( m_isPressed ){
              _drawer.setFillBrush( m_pressedBrush );
              _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 2 );        
            }
            else{
              _drawer.setFillBrush( m_bindingButton.getBrush() );
              _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 2 );        
            }  
            _drawer.popState();
            */
            const auto &_rect = eventArgs.getRenderingRectRegion();
            const auto &_size = _rect.getSize();

            if( m_isPressed ){
              bool _need_pressed_draw = false;
              if( m_toggleable ){
                if( !m_toggled ){
                  _need_pressed_draw = !false;
                }
              }
              else{
                _need_pressed_draw = !false;            
              }

              if( _need_pressed_draw ){
                if( !m_pressedBrush.isNull() ){
                  _drawer.pushState();  
                  _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
                  _drawer.setFillBrush( m_pressedBrush );
                  _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 2 );        
                  _drawer.popState();
                }    

                if( !m_pressedIcon.isNull() ){
                  //draw at center
                  const auto&_icon_size = m_pressedIcon.getSize();
                  auto _x = (_size.getWidth() >> 1) - (_icon_size.getWidth() >> 1);
                  auto _y = (_size.getHeight() >> 1) - (_icon_size.getHeight() >> 1);
                  IntegerDyadCoordinate _coord(  _x > 0 ? _x : 0 , _y > 0? _y : 0 );

                  _drawer.drawImage( _coord, m_pressedIcon );
                }
                else if( !m_icon.isNull() ){
                  const auto&_icon_size = m_icon.getSize();
                  auto _x = (_size.getWidth() >> 1) - (_icon_size.getWidth() >> 1);
                  auto _y = (_size.getHeight() >> 1) - (_icon_size.getHeight() >> 1);
                  IntegerDyadCoordinate _coord(  _x > 0 ? _x : 0 , _y > 0? _y : 0 );

                  _drawer.drawImage( _coord, m_icon );
                }
              }                          
            }
            else{

              if( m_toggleable ){
                if( m_toggled ){
                  if( !m_pressedBrush.isNull() ){
                    _drawer.pushState();  
                    _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
                    _drawer.setFillBrush( m_pressedBrush );
                    _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 2 );        
                    _drawer.popState();
                  }  

                  if( !m_icon.isNull() ){
                    const auto&_icon_size = m_icon.getSize();
                    auto _x = (_size.getWidth() >> 1) - (_icon_size.getWidth() >> 1);
                    auto _y = (_size.getHeight() >> 1) - (_icon_size.getHeight() >> 1);
                    IntegerDyadCoordinate _coord(  _x > 0 ? _x : 0 , _y > 0? _y : 0 );

                    _drawer.drawImage( _coord, m_icon );
                  }
                }
              }

              if( m_hasHoverParaSet && m_isHovered ){
                if( !m_hoveredBrush.isNull() ){
                  _drawer.pushState();  
                  _drawer.clearRectRegion( eventArgs.getRenderingRectRegion() );
                  _drawer.setFillBrush( m_hoveredBrush );
                  _drawer.drawRoundedRect( eventArgs.getRenderingRectRegion(), 2 );        
                  _drawer.popState();
                }  

                if( !m_hoverIcon.isNull() ){
                  const auto&_icon_size = m_hoverIcon.getSize();
                  auto _x = (_size.getWidth() >> 1) - (_icon_size.getWidth() >> 1);
                  auto _y = (_size.getHeight() >> 1) - (_icon_size.getHeight() >> 1);
                  IntegerDyadCoordinate _coord(  _x > 0 ? _x : 0 , _y > 0? _y : 0 );

                  _drawer.drawImage(_coord, m_hoverIcon );
                }
              }
              else if ( !m_icon.isNull() ){
                const auto&_icon_size = m_icon.getSize();
                auto _x = (_size.getWidth() >> 1) - (_icon_size.getWidth() >> 1);
                auto _y = (_size.getHeight() >> 1) - (_icon_size.getHeight() >> 1);
                IntegerDyadCoordinate _coord(  _x > 0 ? _x : 0 , _y > 0? _y : 0 );

                _drawer.drawImage( _coord, m_icon );
              }          

            }
              
            if( !m_text.empty() ){
              _drawer.setFont( m_bindingButton.getFont() );
              _drawer.setFillBrush( m_fontBrush );
              _drawer.drawText( m_textBoundingRect.getBottomLeftCoord(), m_text );
            }
            
            _2d_manager->pullbackDrawer( _drawer );
          }
        }
      }
    }

    void ButtonImplementor::_remeasureText(){
      m_mutex.acquires();
      const auto &_size = FontMetrics::measureSize(m_text, m_bindingButton.getFont() );
      m_textBoundingRect.setSize( _size );

      //default alignment is center
      const auto &_center = m_bindingButton.getBoundingRectRegion().getCenterCoord();
      if( _center.getX() - _size.getWidth() > 0
        && _center.getY() - _size.getHeight() > 0){
          IntegerDyadCoordinate _translated_coord( _center.getX() - (_size.getWidth() / 2 )
            , _center.getY() - (_size.getHeight()  / 2 ) - (_size.getHeight()  / 4 ) );    /* normalized value  */
          m_textBoundingRect.translatedBy( _translated_coord );
            
      }

      m_mutex.releases();
    }

    void ButtonImplementor::hoverIn( HoverEventArgs& event ){
      if( event.isAccepted() ){
        m_isHovered = !false;
        if( m_hasHoverParaSet ){    
          m_bindingButton.update();
        }
      }
    }

    void ButtonImplementor::hoverOut( HoverEventArgs& event ){
      if( event.isAccepted() ){
        m_isHovered = false;
        bool _need_update = false;
        if( m_isPressed ){
          m_isPressed = false;
          _need_update = !false;
        }
        if( m_hasHoverParaSet ){    
          _need_update = !false;
        }
        if( _need_update ){
          m_bindingButton.update();
        }
      }
    }

  }//namespace GUI
}//namespace Magna
