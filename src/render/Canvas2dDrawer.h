/*
 * This file is part of core library of Magna framework
 *
 * Copyright (c) 2013 by Magnus
 */

#ifndef CANVAS2DDRAWER_H
#define CANVAS2DDRAWER_H

#include "render_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/RectRegion.h"
#include "basedef/Line.h"
using namespace Magna::Core;

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

#include "Drawer.h"
#include "Font.h"
#include "Pen.h"
#include "FillBrush.h"
#include "ShadowAppearanceEffect.h"
#include "RenderContants.h"

#include <list>
#include <sstream>

namespace Magna{
  namespace Render{
    class DrawerToolKit;

    /*!    \brief
        A C++-HTML5 canvas drawer. C++--HTML5 canvas»æ»­Õß¡£
     */
    /*!    \details
     *
     *    A drawer provides the basis functionalities of drawing, which
     *    can draw some simple graphics items, such as a line, a rectangle,
     *    and also can draw some complex items, images and texts.
     *    
     *    Besides, you can modify drawing settings with those methods shown below:
     *    setFont() can use to modify font style, such as font weight, font family, with 
     *    Font as parameter.
     *    setFillBrush() sets the fill style of the shape you're about to drawing.
     *    setPen() sets the stroke style of the shape you're about to drawing.
     *    setOpacity() adjusts the global transpancy ranging from 0.0 to 1.0.
     *
     *    Canvas drawer also allows the developer to do some transformations which 
     *    mainly are rotation, shear, translation, scale. In addition, also provides transformation
     *    matrix that can do some customized transformations.
     *    
     *    And you can call pushState() to save current drawing settings and transformations
     *    and push into state stack, while call popState() will pop out the drawing settings and
     *    transformations from state stack for updating current drawing state.
     *
     *    \author  Magnus
     *    \version  1.0.0.0
     *    \date
     */

    template<>
    class RENDER_LIB_EXPORT Drawer< DrawerEngine::DrawerEngine_Canvas2D >{
    friend class RenderManager2D;
    __Constructor_Destructor public:
    Drawer();
    ~Drawer();

    public:
      void  drawArc ( const IntegerDyadCoordinate& origin,  uint32 radius, float startRadian, float endRadian);
      void  drawArc ( const IntegerDyadCoordinate& origin,  uint32 radius, sint32 startAngle, sint32 endAngle );

      void  drawEllipse ( const IntegerRectRegion& rectangle );
      void  drawEllipse ( sint32 centX, sint32 centY, uint32 width, uint32 height );

      void  drawLine ( const IntegerLine& line );
      void  drawLine ( const IntegerDyadCoordinate& p1, const IntegerDyadCoordinate& p2 );

      void  drawLines ( const std::list<IntegerLine> &lines);
      void  drawLines ( const std::list<std::pair<IntegerDyadCoordinate, IntegerDyadCoordinate> >& pointPairs );

      void  drawRect ( const IntegerRectRegion & rectangle );
      void  drawRect ( sint32 x, sint32 y, uint32 width, uint32 height );

      void  drawRects ( const std::list<IntegerRectRegion> rectangles );

      void  drawRoundedRect ( const IntegerRectRegion & rect, uint32 xRadius, uint32 yRadius );
      void  drawRoundedRect ( const IntegerRectRegion & rect, uint32 radius );

      void drawText( const IntegerDyadCoordinate& pos, const String &text );

      void drawText( const IntegerDyadCoordinate& pos, const String &text, TextAlignment aligmen  );
      void drawPie( const IntegerDyadCoordinate& center, uint32 r, uint32 startAngle, uint32 endAngle );
      void drawPie( const IntegerDyadCoordinate& center, uint32 r, float startRadian, float endRadian );

      void drawImage( const IntegerDyadCoordinate& pos, const Image& img );


      void clearRectRegion( const IntegerRectRegion& rect );
      //
      void fillRectRegion(  const IntegerRectRegion& rect );

      Font getFont();
      //getCurrentFontMetrics();

      float getTransparency();

      void rotateAngle( float angle );
      void rotateRadian( float radian );
      void scale( float xScaleRatio, float yScaleRatio );
      void shear( float xShear, float yShear );
      void translate( const IntegerDyadCoordinate & offset );
      void translate( sint32 xOffset, sint32 yOffset );

      void setAppearanceEffect( const SharedPtr<AppearanceEffect>& );

      //ex transform
      void mirror();

      void setFont( const Font& f );
      void setFillBrush( const FillBrush& brush );
      void setPen( const Pen& pen );
      void setOpacity( float opacity );

      void pushState();
      void popState();

    private:
      DrawerToolKit *m_toolKit;

    };

    typedef  Drawer< DrawerEngine::DrawerEngine_Canvas2D > Canvas2DDrawer;
  }//namespace Render
}//namespace Magna

#endif  /*  CANVAS2DDRAWER_H  */
