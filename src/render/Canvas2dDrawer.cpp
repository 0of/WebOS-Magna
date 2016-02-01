#pragma warning(disable:4244)
#pragma warning(disable:4018)
#pragma warning(disable:4101)

#include "Drawer.h"
#include "Canvas2dDrawer.h"
#include "RenderManager2D.h"

#include "private/Pen_p.h"
#include "private/Font_p.h"
#include "private/FillBrush_p.h"

#include "basedef/Comparer.h"
using namespace Magna::Core;

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include "qt_glue_img/ImageResourceHandlerHelper.h"
using namespace Magna::Glue;

#include "DrawerToolKit.h"

namespace Magna{
   namespace Render{
     Drawer< DrawerEngine::DrawerEngine_Canvas2D >::Drawer()
       :m_toolKit(){


     }

    Drawer< DrawerEngine::DrawerEngine_Canvas2D >::~Drawer(){
      //////////////////////////////////////////////////////////////////////////
      //pass to manager to pull it back if user haven't explicitly do it
      if( m_toolKit != Nullptr ){
        RenderManager2D &manager = m_toolKit->m_bindingManager;
        //may result exception
        //use assert instead
        //!!!#
        manager.pullbackDrawer( *this );
      }
    }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawArc ( const IntegerDyadCoordinate& origin,  uint32 radius, float startRadian, float endRadian){
       //
      if( m_toolKit != Nullptr ){
        //coordinate mapper

        auto _mapped_origin = origin + m_toolKit->m_toRenderableCoordOffset;

        sint32 start_times = static_cast<sint32>(startRadian / 3.1415926);
         sint32 end_times = static_cast<sint32>(endRadian / 3.1415926);

        auto & _outer = (m_toolKit->m_outter);

        _outer << L"context.beginPath();"
          << L"context.arc(" << _mapped_origin.getX() << L',' << _mapped_origin.getY() << L','
          << radius << L',' << (startRadian - (start_times * 3.1415926)) << ','
          << (endRadian - (end_times * 3.1415926))
          << L");";

        auto & _currentState = m_toolKit->m_currentState;
        //fill
        if( _currentState.m_did_brush_set ){
          _outer << L"context.fill();";
        }

        //stroke
        //if no fill brush just stroke it
        if( (!_currentState.m_did_brush_set)
          || _currentState.m_did_pen_set  ){
          _outer << L"context.stroke();";
        }

      }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawArc ( const IntegerDyadCoordinate& origin,  uint32 radius, sint32 startAngle, sint32 endAngle ){
       if( m_toolKit != Nullptr ){

         auto _mapped_origin = origin + m_toolKit->m_toRenderableCoordOffset;

         float _start_radian =  (static_cast<float>(startAngle % 360) / 360.0) * 3.1415926;
         float _end_radian = (static_cast<float>(endAngle % 360) / 360.0) * 3.1415926;

         auto & _outer = (m_toolKit->m_outter);
         _outer << L"context.beginPath();"
           << L"context.arc(" << _mapped_origin.getX() << L',' << _mapped_origin.getY() << L','
           << radius << L',' << _start_radian << L',' << _end_radian << L");";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fill();";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.stroke();";
         }

       }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawEllipse ( const IntegerRectRegion& rectangle ){
       if( m_toolKit != Nullptr ){

         auto  _center = rectangle.getCenterCoord() ;
         _center += m_toolKit->m_toRenderableCoordOffset;

         IntegerDyadCoordinate _mapped_origin = rectangle.getTopLeftCoord();
         _mapped_origin += m_toolKit->m_toRenderableCoordOffset;


         const uint32 & _width = rectangle.getWidth();
         const uint32 & _height = rectangle.getHeight();

         uint32 _base = (_width > _height ) ? _width : _height;
         float _x_ratio = static_cast<float>(_width) / static_cast<float>(_base);
         float _y_ratio = static_cast<float>(_height) / static_cast<float>(_base);

         auto & _outer = (m_toolKit->m_outter);
         _outer << L"context.save();context.scale("
           << _x_ratio << L',' << _y_ratio << L");context.beginPath();"
           << L"context.arc(" << (_center.getX() / _x_ratio) << L','
           << (_center.getY() / _y_ratio) << L','
           << _base << L", 0, 6.2831852 ); context.closePath(); context.restore(); ";

        auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fill();";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.stroke();";
         }
       }
     }

    void  Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawEllipse ( sint32 centX, sint32 centY, uint32 width, uint32 height ){
      if( m_toolKit != Nullptr ){

        auto  _center = IntegerDyadCoordinate( centX + m_toolKit->m_toRenderableCoordOffset.getX()
                                          , centY + m_toolKit->m_toRenderableCoordOffset.getY() );

        uint32 _base = (width > height ) ? width : height;
         float _x_ratio = static_cast<float>(width) / static_cast<float>(_base);
         float _y_ratio = static_cast<float>(height) / static_cast<float>(_base);

         auto & _outer = (m_toolKit->m_outter);
         _outer << L"context.save();context.scale("
           << _x_ratio << L',' << _y_ratio << L");context.beginPath();"
           << L"context.arc(" << ( _center.getX() / _x_ratio) << L','
           << (_center.getY() / _y_ratio) << L','
           << _base << L", 0, 6.2831852 ); context.restore(); ";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fill();";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.stroke();";
         }
      }
    }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawLine ( const IntegerLine& line ){
       if( m_toolKit != Nullptr ){

         IntegerDyadCoordinate _p1 = line.getP1();
         _p1 += m_toolKit->m_toRenderableCoordOffset;

         IntegerDyadCoordinate _p2 = line.getP2();
         _p2 += m_toolKit->m_toRenderableCoordOffset;

         auto & _outer = (m_toolKit->m_outter);
         _outer << L"context.beginPath();context.moveTo("
           << _p1.getX() << L',' << _p1.getY()
           << L");context.lineTo(" << _p2.getX() << L','
           <<_p2.getY() << L");";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fill();";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.stroke();";
         }
       }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawLine ( const IntegerDyadCoordinate& p1, const IntegerDyadCoordinate& p2 ){
       if( m_toolKit != Nullptr ){

         IntegerDyadCoordinate _p1 = p1;
         _p1 += m_toolKit->m_toRenderableCoordOffset;

         IntegerDyadCoordinate _p2 = p2;
         _p2 += m_toolKit->m_toRenderableCoordOffset;

         auto & _outer = (m_toolKit->m_outter);
         _outer << L"context.beginPath();context.moveTo("
           << _p1.getX() << L',' << _p1.getY()
           << L");context.lineTo(" << _p2.getX() << L','
           <<_p2.getY() << L");";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fill();";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.stroke();";
         }
       }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawLines ( const std::list<IntegerLine> &lines){
       if( m_toolKit != Nullptr ){
         std::list<IntegerLine>::const_iterator _it_each = lines.begin();
         if( _it_each != lines.end() ){


           auto & _outer = (m_toolKit->m_outter);
           _outer << L"context.beginPath();";

           if( !m_toolKit->m_toRenderableCoordOffset.isOrigin() ){
             for( ; _it_each != lines.end(); ++_it_each ){
               IntegerDyadCoordinate _p1 = _it_each->getP1();
               _p1 += m_toolKit->m_toRenderableCoordOffset;

               IntegerDyadCoordinate _p2 =  _it_each->getP2() ;
               _p2 += m_toolKit->m_toRenderableCoordOffset;

               _outer << L"context.moveTo("
                 << _p1.getX() << L',' << _p1.getY()
                 << L");context.lineTo(" << _p2.getX() << L','
                 << _p2.getY() << L");";
             }
           }
           else{
             for( ; _it_each != lines.end(); ++_it_each ){
               const IntegerDyadCoordinate& _each_p1 = _it_each->getP1() ;
               const IntegerDyadCoordinate& _each_p2 = _it_each->getP2() ;
               _outer << L"context.moveTo("
                 << _each_p1.getX() << L',' << _each_p1.getY()
                 << L");context.lineTo(" << _each_p2.getX() << L','
                 << _each_p2.getY() << L");";
             }
           }
           auto & _currentState = m_toolKit->m_currentState;
           //fill
           if( _currentState.m_did_brush_set ){
             _outer << L"context.fill();";
           }

           //stroke
           //if no fill brush just stroke it
           if( (!_currentState.m_did_brush_set)
             || _currentState.m_did_pen_set  ){
               _outer << L"context.stroke();";
           }
         }
       }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawLines ( const std::list<std::pair<IntegerDyadCoordinate, IntegerDyadCoordinate> >& pointPairs ){
        if( m_toolKit != Nullptr ){
         std::list<std::pair<IntegerDyadCoordinate, IntegerDyadCoordinate> >::const_iterator _it_each = pointPairs.begin();
         if( _it_each != pointPairs.end() ){


           auto & _outer = (m_toolKit->m_outter);
           _outer << L"context.beginPath();";

           if(  !m_toolKit->m_toRenderableCoordOffset.isOrigin() ){
             for( ; _it_each != pointPairs.end(); ++_it_each ){
               IntegerDyadCoordinate _each_p1 = _it_each->first;
               _each_p1 += m_toolKit->m_toRenderableCoordOffset;

               IntegerDyadCoordinate _each_p2 =  _it_each->second;
               _each_p2 += m_toolKit->m_toRenderableCoordOffset;

               _outer << "context.moveTo("
                 << _each_p1.getX() << L',' << _each_p1.getY()
                 << L");context.lineTo(" << _each_p2.getX() << L','
                 << _each_p2.getY() << L");";
             }
           }
           else{
             for( ; _it_each != pointPairs.end(); ++_it_each ){
               const IntegerDyadCoordinate& _each_p1 = _it_each->first;
               const IntegerDyadCoordinate& _each_p2 = _it_each->second;
               _outer << L"context.moveTo("
                 << _each_p1.getX() << L',' << _each_p1.getY()
                 << L");context.lineTo(" << _each_p2.getX() << L','
                 << _each_p2.getY() << L");";
             }
           }

           auto & _currentState = m_toolKit->m_currentState;
           //fill
           if( _currentState.m_did_brush_set ){
             _outer << L"context.fill();";
           }

           //stroke
           //if no fill brush just stroke it
           if( (!_currentState.m_did_brush_set)
             || _currentState.m_did_pen_set  ){
               _outer << L"context.stroke();";
           }
         }
        }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawRect ( const IntegerRectRegion & rectangle ){
        if( m_toolKit != Nullptr ){
         auto  _topLeft = rectangle.getTopLeftCoord() ;
         _topLeft += m_toolKit->m_toRenderableCoordOffset;

         auto & _outer = (m_toolKit->m_outter);
         //extra rect parameters script
         OutStringStream _extra_rect_para_outter;

         _extra_rect_para_outter
           << _topLeft.getX()
           << L',' << _topLeft.getY()
           << L',' << rectangle.getWidth()
           << L',' << rectangle.getHeight() ;

         _outer << L"context.rect("
            << _extra_rect_para_outter.str()
            << L");";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fillRect("
             << _extra_rect_para_outter.str()
             << L");";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
          _outer << L"context.strokeRect("
            << _extra_rect_para_outter.str()
            << L");";
         }
        }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawRect ( sint32 x, sint32 y, uint32 width, uint32 height ){
       if( m_toolKit != Nullptr ){

         auto  _topLeft = IntegerDyadCoordinate( x + m_toolKit->m_toRenderableCoordOffset.getX()
            , y + m_toolKit->m_toRenderableCoordOffset.getY() );

         auto & _outer = (m_toolKit->m_outter);

         //extra rect parameters script
         OutStringStream _extra_rect_para_outter;

         _extra_rect_para_outter
           << _topLeft.getX()
           << L',' << _topLeft.getY()
           << L',' << width
           << L',' << height;

         _outer << L"context.rect("
           << _extra_rect_para_outter.str()
           << L");";

         auto & _currentState = m_toolKit->m_currentState;
         //fill
         if( _currentState.m_did_brush_set ){
           _outer << L"context.fillRect("
             << _extra_rect_para_outter.str()
             << L");";
         }

         //stroke
         //if no fill brush just stroke it
         if( (!_currentState.m_did_brush_set)
           || _currentState.m_did_pen_set  ){
             _outer << L"context.strokeRect("
               << _extra_rect_para_outter.str()
               << L");";
         }
        }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawRects ( const std::list<IntegerRectRegion> rectangles ){
        if( m_toolKit != Nullptr ){
         std::list<IntegerRectRegion>::const_iterator _it_each = rectangles.begin();

         if( _it_each != rectangles.end() ){
          for( ; _it_each != rectangles.end(); ++_it_each ) {
             drawRect( *_it_each );
          }
         }
       }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawRoundedRect ( const IntegerRectRegion & rect, uint32 xRadius, uint32 yRadius ){
        if( m_toolKit != Nullptr ){
          if( xRadius != yRadius ){

            auto _topLeft = rect.getTopLeftCoord();
            _topLeft += m_toolKit->m_toRenderableCoordOffset;

            const uint32& _width = rect.getWidth();
            const uint32& _height = rect.getHeight();

            const uint32& _x = _topLeft.getX();
            const uint32& _y = _topLeft.getY();

            if( xRadius > (rect.getWidth() >> 1) ){
              xRadius = (rect.getWidth() >> 1) ;
            }
            if( yRadius  > (rect.getHeight() >> 1) ){
              yRadius = (rect.getHeight() >> 1) ;
            }

            auto & _outer = (m_toolKit->m_outter);
            _outer << L"var _r_x="<<_x
              << L";var _r_y=" << _y << L";var _r_right="<< (_x+ _width)
              << L";var _r_bottom=" << (_y + _height )
              << L";context.beginPath();context.moveTo("

              << (_x + xRadius) << L",_r_y);context.lineTo("
              << (_x + _width - xRadius )
              << L",_r_y);context.quadraticCurveTo(_r_right,_r_y,_r_right,"
              << (_y + yRadius)

              <<L");context.lineTo(_r_right," << (_y + _height - yRadius)
              <<L");context.quadraticCurveTo(_r_right,_r_bottom,"
              <<  (_x + _width - xRadius) << L"_r_bottom);context.lineTo("

              << _x + xRadius << L",_r_bottom); context.quadraticCurveTo(x,y+h, x,"
              << _y + _height - yRadius << L");context.lineTo(_r_x" << _y + yRadius

              << L");context.quadraticCurveTo(_r_x,_r_bottom, _r_x, "
              << _y + _height - yRadius

              << L");  ";

           auto & _currentState = m_toolKit->m_currentState;
           //fill
           if( _currentState.m_did_brush_set ){
             _outer << L"context.fill();";
           }

           //stroke
           //if no fill brush just stroke it
           if( (!_currentState.m_did_brush_set)
             || _currentState.m_did_pen_set  ){
               _outer << L"context.stroke();";
           }
          }
          else{
            drawRoundedRect( rect, xRadius );
          }
        }
     }

     void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawRoundedRect ( const IntegerRectRegion & rect, uint32 radius ){
        if( m_toolKit != Nullptr ){
        if( radius != 0 ){

          auto _topLeft = rect.getTopLeftCoord();
          _topLeft += m_toolKit->m_toRenderableCoordOffset;

          const uint32& _width = rect.getWidth();
          const uint32& _height = rect.getHeight();
          const uint32& _x = _topLeft.getX();
          const uint32& _y = _topLeft.getY();

          if( radius > (rect.getWidth() >> 1) ){
            radius = (rect.getWidth() >> 1) ;
          }
          if( radius  > (rect.getHeight() >> 1) ){
            radius = (rect.getHeight() >> 1) ;
          }

          auto & _outer = (m_toolKit->m_outter);
          _outer << L"var _r_x="<<_x
            << L";var _r_y=" << _y << L";var _r_right="<< (_x+ _width)
            << L";var _r_bottom=" << (_y + _height )
            << L";var _r_r=" << radius
            << L";context.beginPath();context.moveTo("
            << radius + _x
            << L", _r_y ); context.arcTo(_r_right ,_r_y, _r_right, _r_bottom, _r_r);\
               context.arcTo(_r_right, _r_bottom, _r_x, _r_bottom, _r_r );\
               context.arcTo(_r_x, _r_bottom, _r_x, _r_y, _r_r );\
               context.arcTo(_r_x, _r_y, _r_right, _r_y, _r_r);\
               context.closePath();";

          auto & _currentState = m_toolKit->m_currentState;
           //fill
           if( _currentState.m_did_brush_set ){
             _outer << L"context.fill();";
           }

           //stroke
           //if no fill brush just stroke it
           if( (!_currentState.m_did_brush_set)
             || _currentState.m_did_pen_set  ){
               _outer << L"context.stroke();";
           }

         }
       }
     }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawText( const IntegerDyadCoordinate& pos, const String &text ){
       if( m_toolKit != Nullptr ){

         auto _pos = pos;
         _pos += m_toolKit->m_toRenderableCoordOffset;

         auto & _outer = (m_toolKit->m_outter);

         OutStringStream _text_script_outter;
         _text_script_outter << L"\"" << text<< L"\", "
            << _pos.getX() <<L',' << _pos.getY() ;

         auto & _currentState = m_toolKit->m_currentState;

         //stroke
         if( _currentState.m_did_pen_set ){
           _outer << L"context.strokeText("
             << _text_script_outter.str()
             << L");";
         }

         //fill
         if( !_currentState.m_did_pen_set
           || _currentState.m_did_brush_set ){
           _outer << L"context.fillText("
             << _text_script_outter.str()
             << L");";
         }
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawPie( const IntegerDyadCoordinate& center, uint32 r, uint32 startAngle, uint32 endAngle ){
      //
       if( m_toolKit != Nullptr ){
        auto & _outer = (m_toolKit->m_outter);

        auto _center = center;
        _center += m_toolKit->m_toRenderableCoordOffset;

        if( (endAngle - startAngle) == 5760
           || (endAngle - startAngle) == -5760) {
          //draw a circle
         _outer <<L"var _p_x="<< _center.getX()
              <<L";var _p_y=" << _center.getY()
              << L";var _p_r=" << r
              << L";context.beginPath();context.arc( _p_x, _p_y, _p_r, 0,  6.2831852 );";
        }
        else{
          _outer <<L"var _p_x="<< _center.getX()
              <<L";var _p_y=" << _center.getY()
              << L";var _p_r=" << r
              << L";var _p_sr=" << (startAngle *3.1415926 ) / 5760.0
              << L";var _p_er=" << (endAngle *3.1415926 ) / 5760.0
              << L";context.beginPath();context.arc( _p_x, _p_y, _p_r, _p_sr, _p_er );\
              context.lineTo( _p_x, _p_y );context.closePath();";
        }

        auto & _currentState = m_toolKit->m_currentState;
        //fill
        if( _currentState.m_did_brush_set ){
          _outer << L"context.fill()";
        }

        //stroke
        //if no fill brush just stroke it
        if( (!_currentState.m_did_brush_set)
          || _currentState.m_did_pen_set  ){
            _outer << L"context.stroke();";
        }
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawPie( const IntegerDyadCoordinate& center, uint32 r, float startRadian, float endRadian ){
      if( m_toolKit != Nullptr ){

        auto _center = center;
        _center += m_toolKit->m_toRenderableCoordOffset;

        auto & _outer = (m_toolKit->m_outter);

        if( Comparer<float>::isAlmostToZero(  ::abs( endRadian - startRadian) - 6.2831852 ) ){
          //draw a circle
          _outer <<L"var _p_x="<< _center.getX()
              <<L";var _p_y=" << _center.getY()
              << L";var _p_r=" << r
              << L";context.beginPath();context.arc( _p_x, _p_y, _p_r, 0,  6.2831852 );";
        }
        else{
          _outer <<L"var _p_x="<< _center.getX()
              <<L";var _p_y=" << _center.getY()
              << L";var _p_r=" << r
              << L";var _p_sr=" << startRadian
              << L";var _p_er=" << endRadian
              << L";context.beginPath();context.arc( _p_x, _p_y, _p_r, _p_sr, _p_er );\
              context.lineTo( _p_x, _p_y );context.closePath();";
        }
        auto & _currentState = m_toolKit->m_currentState;
        //fill
        if( _currentState.m_did_brush_set ){
          _outer << L"context.fill();";
        }

        //stroke
        //if no fill brush just stroke it
        if( (!_currentState.m_did_brush_set)
          || _currentState.m_did_pen_set  ){
            _outer << L"context.stroke();";
        }
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::drawImage( const IntegerDyadCoordinate& pos, const Image& img ){
       if( m_toolKit != Nullptr ){

         auto & _outer = (m_toolKit->m_outter);
         if( ImageResourceHandlerHelper::getImageResourceString( img, _outer ) ){
           auto _pos = pos;
           _pos += m_toolKit->m_toRenderableCoordOffset;

           _outer << L"context.drawImage(image,"
             << _pos.getX() << L"," << _pos.getY() << L");";
         }
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::clearRectRegion( const IntegerRectRegion& rect ){
       if( m_toolKit != Nullptr ){
        if( rect.getWidth() != 0 && rect.getHeight() != 0 ){

          auto _topLeft = rect.getTopLeftCoord();
          _topLeft += m_toolKit->m_toRenderableCoordOffset;

          auto & _outer = (m_toolKit->m_outter);

          _outer << L"context.clearRect(" << _topLeft.getX()
            << L',' << _topLeft.getY()
            << L',' << rect.getWidth() << L',' << rect.getHeight()
            << L");";
        }
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::fillRectRegion(  const IntegerRectRegion& rect ){
      if( m_toolKit != Nullptr ){
        if( rect.getWidth() != 0 && rect.getHeight() != 0 ){

          auto _topLeft = rect.getTopLeftCoord();
          _topLeft += m_toolKit->m_toRenderableCoordOffset;

          auto & _outer = (m_toolKit->m_outter);
          _outer << L"context.fillRect(" << _topLeft.getX()
            << L',' << _topLeft.getY()
            << L',' << rect.getWidth() << L',' << rect.getHeight()
            << L");";
        }
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::rotateAngle( float angle ){
      if( m_toolKit != Nullptr ){

        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.rotate("
          << ( (angle * 6.2831852) / 360.0)
          << L");";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::rotateRadian( float radian ){
      if( m_toolKit != Nullptr ){
        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.rotate("
          << radian
          << L");";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::scale( float xScaleRatio, float yScaleRatio ){
      if( m_toolKit != Nullptr ){
        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.scale("
          << xScaleRatio << L',' << yScaleRatio
          << L");";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::shear( float xShear, float yShear ){
      if( m_toolKit != Nullptr ){
        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.transform(1,"
          << xShear << L',' << yShear << L",1,0,0);";
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::translate( const IntegerDyadCoordinate & offset ){
       if( m_toolKit != Nullptr ){

         auto _offset = offset;
         _offset += m_toolKit->m_toRenderableCoordOffset;

         auto & _outer = (m_toolKit->m_outter);
         _outer << L" context.translate("
           << _offset.getX() << L',' << _offset.getY() << L");";
       }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::translate( sint32 xOffset, sint32 yOffset ){
      if( m_toolKit != Nullptr ){

        auto _offset = IntegerDyadCoordinate( xOffset + m_toolKit->m_toRenderableCoordOffset.getX()
                    ,  yOffset + m_toolKit->m_toRenderableCoordOffset.getY() );

        auto & _outer = (m_toolKit->m_outter);
        _outer << L" context.translate("
          << _offset.getX() << L',' << _offset.getY() << L");";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::setFont( const Font& f ){
      try{
         if( m_toolKit != Nullptr ){
           if( !f.m_data.isNull() ){
             m_toolKit->m_currentState.RenderableFont() = f;

             auto & _outer = (m_toolKit->m_outter);
             _outer << L"context.font=" << f.m_data->_toString()
               << L";";
           }
           else{
             throw InnerPrivateDataNullPointerException();
           }
         }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //
        abort();
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::setFillBrush( const FillBrush& brush ){
      try{
        if( m_toolKit != Nullptr ){

          m_toolKit->m_currentState.RenderableBrush() = brush;
          if( brush.isNull() ){
            m_toolKit->m_currentState.m_did_brush_set = false;
          }
          else{
            auto & _outer = (m_toolKit->m_outter);
            _outer << brush.m_data->_toString( m_toolKit->m_toRenderableCoordOffset );
          }

        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //
        abort();
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::setPen( const Pen& pen ){
      try{
        if( m_toolKit != Nullptr ){
          if( !pen.m_data.isNull() ){
            m_toolKit->m_currentState.RenderablePen() = pen;
            auto & _outer = (m_toolKit->m_outter);
            _outer << pen.m_data->_toString( m_toolKit->m_toRenderableCoordOffset );
          }
          else{
            throw InnerPrivateDataNullPointerException();
          }
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //
        abort();
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::setOpacity( float opacity ){
      try{
        if( m_toolKit != Nullptr  ){

          if(  Comparer< decltype(opacity) >::isHigherThan( opacity, 1.00 )
            || Comparer< decltype(opacity) >::isLowerThanZero( opacity ) ){
              opacity = 1.00;
          }

          m_toolKit->m_currentState.RenderableOpacity() = opacity;

          auto & _outer = (m_toolKit->m_outter);

          _outer.precision(3);
          _outer << L"context.globalAlpha=" << opacity << L";";
        }
        else{
          throw InnerPrivateDataNullPointerException();
        }
      }
      catch( const InnerPrivateDataNullPointerException& ex ){
        //
        abort();
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::pushState(){
      if( m_toolKit != Nullptr  ){
        m_toolKit->m_stateSetStack.push( m_toolKit->m_currentState );
        m_toolKit->m_currentState = RenderStateSet();
        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.save();";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::popState(){
      if( m_toolKit != Nullptr && !m_toolKit->m_stateSetStack.empty()  ){
        m_toolKit->m_currentState =  m_toolKit->m_stateSetStack.top() ;
        m_toolKit->m_stateSetStack.pop();
        auto & _outer = (m_toolKit->m_outter);
        _outer << L"context.restore();";
      }
    }

    void Drawer< DrawerEngine::DrawerEngine_Canvas2D >::setAppearanceEffect( const SharedPtr<AppearanceEffect>& effect){
      if( !effect.isNull() ){
        auto & _outer = (m_toolKit->m_outter);
        _outer << effect->toString();
      }
    }

   }//Render
}//Magna
