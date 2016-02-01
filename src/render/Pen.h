/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#ifndef PEN_H
#define PEN_H

#ifdef _MSC_VER
#pragma warning(disable:4150)
#endif

#include "render_lib.h"

#include "basedef/SharedPtr.h"
#include "basedef/Color.h"
using namespace Magna::Core;

#include "Drawer.h"

namespace Magna{
   namespace Render{

     class FillBrush;
     class PenData;
     /*!  \brief
         The stroke style of a closed shape. 闭合形状的描边样式。
      */
     /*!  \details
      *    
      *    The Pen defines the stroke style of a closed shape drawn by
      *    2D drawer( For current version, only Drawer<DrawerEngine::DrawerEngine_Canvas2D> supported).
      *
      *    
      *
      * 
      *    \author 
      *    \version   
      *    \date      
      */
     class RENDER_LIB_EXPORT Pen{
       friend class Drawer< DrawerEngine::DrawerEngine_Canvas2D >;

       __Constants public:
        enum CapStyle{
          CapStyle_Flat = 0,
          CapStyle_Butt = CapStyle_Flat,
          CapStyle_Square = 1,
          CapStyle_Round = 2
        };

        enum JoinStyle{
          JoinStyle_Bevel  =  0,
          JoinStyle_Round = 1,
          JoinStyle_Miter = 2
        };

      __Constructor_Destructor public:
        Pen();
        explicit Pen( const Color& color );
        explicit Pen( const Color& color, float penWidth );
        explicit Pen( const FillBrush& brush, float penWidth, CapStyle capStyle = CapStyle_Flat, JoinStyle joinStyle = JoinStyle_Bevel);
        ~Pen();

      __Setter public:
        void setPenWidth( float width );
        void setFillBrush( const FillBrush& brush );
        void setCapStyle( CapStyle style );
        void setJoinStyle( JoinStyle style );
        void setMiterLimit( uint32 litmit );

      __Getter public:
        float getPenWidth() const;
        const FillBrush& getFillBrush() const;
        CapStyle getCapStyle();
        JoinStyle getjoinStyle();
        uint32 getMiterLimit() const;

      __Data_Field private:
        SharedPtr<PenData> m_data;
     };
   }//Render
}//Magna

#endif  /*  PEN_H  */
