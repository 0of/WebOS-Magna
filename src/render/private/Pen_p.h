#ifndef PEN_P_H
#define PEN_P_H

#include "basedef/String.h"
using namespace Magna::Core;

#include "../Pen.h"

namespace Magna{
  namespace Render{
    class PenData{
       __Constants public:
        static const unicode_char *shared_CapStyleCodeLines[] ;
        static const unicode_char *shared_JoinStyleCodeLines[] ;

       __Constructor_Destructor public:
         PenData() : m_fillBrush(), m_capStyle( Pen::CapStyle_Flat )
           ,m_joinStyle( Pen::JoinStyle_Bevel ), m_miterLimit(0), m_width( 1.0 ){}
         PenData( const Color& color ) : m_fillBrush( color ), m_capStyle( Pen::CapStyle_Flat )
           ,m_joinStyle( Pen::JoinStyle_Bevel ), m_width( 1.0 ){}
         PenData( const Color& color, float penWidth ) : m_fillBrush( color ), m_capStyle( Pen::CapStyle_Flat )
           ,m_joinStyle( Pen::JoinStyle_Bevel ), m_width( penWidth ){}
         PenData( const FillBrush& brush, float penWidth, Pen::CapStyle capStyle , Pen::JoinStyle joinStyle ) : m_fillBrush( brush ), m_capStyle( capStyle )
           ,m_joinStyle( joinStyle ), m_width( penWidth ){}
      public:
        String _toString( const IntegerDyadCoordinate& ) const;

       __Data_Field public:
         FillBrush m_fillBrush;
         Pen::CapStyle m_capStyle;
         Pen::JoinStyle m_joinStyle;
         uint32 m_miterLimit;
         float m_width;
     };
  }//namespace Render
}//namespace Magna

#endif  /*  PEN_P_H  */
