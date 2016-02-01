/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */

#ifndef FILLBRUSH_H
#define FILLBRUSH_H

#pragma warning(disable:4150)

#include "render_lib.h"

#include "basedef/Color.h"
#include "basedef/SharedPtr.h"

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

#include "TexturePattern.h"
#include "Gradient.h"
#include "Drawer.h"

#include "Pen.h"

using namespace Magna;
using namespace Magna::Core;

namespace Magna{
   namespace Render{

     /*!  \brief
         The fill style of a closed shape. 闭合形状的填充样式。
      */
     /*!  \details
      *  
      *    The FillBrush defines the fill style of a closed shape drawn by
      *    2D drawer( For current version, only Drawer<DrawerEngine::DrawerEngine_Canvas2D> supported).
      *    The fill style can be color, gradient, texture and texture pattern.
      * 
      *    \author  Magnus
      *    \version   1.0.0.0
      *    \date    
      */
     class  RENDER_LIB_EXPORT FillBrush{
      friend class Drawer<DrawerEngine::DrawerEngine_Canvas2D>;
      friend class Pen;
      friend class PenData;

       __Constants public:
        enum BrushContent{
          BrushContent_None
          ,BrushContent_Color
          ,BrushContent_Gradient
          ,BrushContent_Texture
          ,BrushContent_TexturePattern
        };

      __Constructor_Destructor public:
        FillBrush();
        FillBrush( const FillBrush& brush );
        explicit FillBrush( const Color& color );
        explicit FillBrush( Gradient *gradient );
        explicit FillBrush( TexturePattern *pattern );
        explicit FillBrush( const Image& img );
        ~FillBrush();

      __Checker public:
        bool isNull() const{ return m_data.isNull(); }

      __Setter public:
        void setColor( const Color& color );
        void setGradient( Gradient *gradient );
        void setTexture( const Image& img );
        void setTexturePattern( TexturePattern *pattern );

      __Getter public:
        Color getColor() const;

        BrushContent getBrushContent() const;

        SharedPtr<Gradient> getGradient() const;
        SharedPtr<TexturePattern> getTexturePattern() const;
        Image getTexture() const;

      __Overloaded_Methods public:
        FillBrush & operator = ( const FillBrush& brush );

      __Data_Field private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
     };
   }//Render
}//Magna

#endif  /*  FILLBRUSH_H  */
