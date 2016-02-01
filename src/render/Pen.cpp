#pragma warning( disable: 4101)

#include "basedef/Comparer.h"

#include "Pen.h"
#include "FillBrush.h"
#include "private/Pen_p.h"
#include "private/FillBrush_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
using namespace Magna::Inner;

#include <cassert>

namespace Magna{
   namespace Render{

    const unicode_char * PenData::shared_CapStyleCodeLines[]
    = { L"context.lineCap='butt';", L"context.lineCap='round';", L"context.lineCap='square';" };
    const unicode_char *PenData::shared_JoinStyleCodeLines[]
    = {  L"context.lineJoin='bevel';", L"context.lineJoin='miter';", L"context.lineJoin='round';" };

     Pen::Pen()
       :m_data( new PenData ){

     }

     Pen::Pen( const Color& color )
       :m_data( new PenData( color ) ){

     }
     Pen::Pen( const Color& color, float penWidth )
       :m_data( new PenData( color, penWidth ) ){

     }

     Pen::Pen( const FillBrush& brush, float penWidth, CapStyle capStyle, JoinStyle joinStyle )
       :m_data( new PenData( brush, penWidth, capStyle,joinStyle  ) ){

     }
     Pen::~Pen(){

     }

     void Pen::setPenWidth( float width ){
       assert( Comparer<float>::isHigherThanZero( width ) );
       try{
         if( !m_data.isNull() ){
          m_data->m_width = width;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }
     void Pen::setFillBrush( const FillBrush& brush ){
       try{
         if( !m_data.isNull() ){
           m_data->m_fillBrush = brush;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Pen::setCapStyle( CapStyle style ){
       try{
         if( !m_data.isNull() ){
           m_data->m_capStyle = style;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Pen::setJoinStyle( JoinStyle style ){
       try{
         if( !m_data.isNull() ){
           m_data->m_joinStyle = style;
         }
         else{
           throw InnerPrivateDataNullPointerException();
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void Pen::setMiterLimit( uint32 litmit ){

     }

     String PenData::_toString( const IntegerDyadCoordinate& offset) const{
       OutStringStream _outter;
       //pen cap style
       _outter << PenData::shared_CapStyleCodeLines[ m_capStyle ];
       //pen join style
       _outter << PenData::shared_JoinStyleCodeLines[ m_joinStyle ];

       //line width
      _outter << L"context.lineWidth=" << m_width << L';';

      auto &_brush_data =  m_fillBrush.m_data;
      if( !_brush_data.isNull() ){
        _outter << _brush_data->_toFillString( offset );
        _outter << L"strokeStyle=style;";
      }

      return _outter.str();
     }

   }//Render
}//Magna
