#ifndef FILLBRUSH_P_H
#define FILLBRUSH_P_H

#include "basedef/String.h"

#include "../FillBrush.h"
#include "../DyadCoordinateMapper.h"

#include <cassert>

namespace Magna{
  namespace Render{
     class FillBrush::PrivateData{
       __Constructor_Destructor public:
        PrivateData(): m_brushContent( FillBrush::BrushContent_Color )
          ,m_comfirmBrushContent( FillBrush::BrushContent_Color ){
          new (reinterpret_cast<Color *>(m_brushData)) Color ();
          //m_brushData.m_color = Color();
        }

        PrivateData( const Color& color ): m_brushContent( FillBrush::BrushContent_Color)
          ,m_comfirmBrushContent( FillBrush::BrushContent_Color ){
          new (reinterpret_cast<Color *>(m_brushData)) Color ( color );
          //m_brushData.m_color = color;
        }

        PrivateData( const Image& img )
          : m_brushContent( FillBrush::BrushContent_Texture )
          ,m_comfirmBrushContent( FillBrush::BrushContent_Texture ){
          new (reinterpret_cast<Image *>(m_brushData)) Image ( img );
          //m_brushData.m_imgElement = img;
        }

        PrivateData( TexturePattern * pattern )
          : m_brushContent( FillBrush::BrushContent_TexturePattern )
          ,m_comfirmBrushContent( FillBrush::BrushContent_TexturePattern ){
          assert( pattern != Nullptr );
          new (reinterpret_cast<SharedPtr<TexturePattern> *>(m_brushData)) SharedPtr<TexturePattern>(pattern);
          //m_brushData.m_pattern = pattern;
        }

        PrivateData( Gradient *gradient )
          : m_brushContent( FillBrush::BrushContent_Gradient )
          ,m_comfirmBrushContent( FillBrush::BrushContent_Gradient ){
          assert( gradient != Nullptr );
          new (reinterpret_cast<SharedPtr<Gradient> *>(m_brushData)) SharedPtr<Gradient>(gradient);

        }

        ~PrivateData(){
          switch( m_brushContent ){
          case FillBrush::BrushContent_Color:
            (*(reinterpret_cast<Color *>(m_brushData))).~Color();
            break;

          case FillBrush::BrushContent_Gradient:
            (*(reinterpret_cast<SharedPtr<Gradient> *>(m_brushData)) ).~SharedPtr<Gradient>();
            break;

          case FillBrush::BrushContent_Texture:
            (*(reinterpret_cast<Image *>(m_brushData))).~Image();
            break;

          case FillBrush::BrushContent_TexturePattern:
            (*(reinterpret_cast<SharedPtr<TexturePattern> *>(m_brushData))).~SharedPtr<TexturePattern>();
            break;

          default:
            break;

        }
      }

      public:
        String _toString( const IntegerDyadCoordinate& ) const;
        String _toFillString( const IntegerDyadCoordinate& ) const;

       __Data_Field public:
        FillBrush::BrushContent m_brushContent :16;
        FillBrush::BrushContent m_comfirmBrushContent :16 ;
        //using byte array replaces union type
        ///align 4 bytes
        uint8 m_brushData[ sizeof( Image ) >= sizeof( SharedPtr<Gradient> ) ?  sizeof( Image ) : sizeof( SharedPtr<Gradient> ) ];
     };
  }//namespace Render
}//namespace Magna

#endif  /*  FILLBRUSH_P_H  */
