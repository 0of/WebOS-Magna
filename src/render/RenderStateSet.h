#ifndef RENDERSTATESET_H
#define RENDERSTATESET_H

#include "basedef/Comparer.h"

#include "TransformMatrix.h"
#include "Font.h"
#include "FillBrush.h"
#include "Pen.h"

namespace Magna{
  namespace Render{
    struct RenderStateSet{
      RenderStateSet(): 
      m_did_font_set( false )
      ,m_did_brush_set( false )
      ,m_did_pen_set( false )
      ,m_did_matrix_set( false )
      ,m_did_opacity_set( false )
      ,m_opacity( 1.0 )
      ,m_renderableFont()
      ,m_renderablePen(), m_renderableFillBrush(), m_renderableCurrentMat(){

      }

      explicit RenderStateSet( float opacity, const Font& renderableFont, const Pen& renderablePen
        , const FillBrush& renderableFillBrush, const TransformMatrix& renderableCurrentMat )
        : m_did_font_set( !false )
        ,m_did_brush_set( !false )
        ,m_did_pen_set( !false )
        ,m_did_matrix_set( !false )
        ,m_did_opacity_set( !false )
        ,m_opacity(opacity), m_renderableFont( renderableFont ),m_renderablePen( renderablePen )
        , m_renderableFillBrush( renderableFillBrush ), m_renderableCurrentMat( renderableCurrentMat ){
        if( m_renderableFillBrush.isNull() ){
          m_did_brush_set = false;
        }

        if(  Comparer< decltype(m_opacity) >::isHigherThan( m_opacity, 1.00 )  
          || Comparer< decltype(m_opacity) >::isLowerThanZero( m_opacity ) ){
            m_opacity = 1.00;
        }

      }


      RenderStateSet( const RenderStateSet& set )
        : m_did_font_set( set.m_did_font_set )
        ,m_did_brush_set( set.m_did_brush_set )
        ,m_did_pen_set( set.m_did_pen_set )
        ,m_did_matrix_set( set.m_did_matrix_set )
        ,m_renderableFont( set.m_renderableFont ),m_renderablePen( set.m_renderablePen )
        , m_renderableFillBrush( set.m_renderableFillBrush ), m_renderableCurrentMat( set.m_renderableCurrentMat ){}

      RenderStateSet & operator = ( const RenderStateSet& set ){
        ::memcpy( this, &set, sizeof( bool ) << 2 );
        //m_did_font_set = set.m_did_font_set;
        //m_did_brush_set = set.m_did_brush_set;
        //m_did_pen_set = set.m_did_pen_set;
        //m_did_matrix_set = set.m_did_matrix_set;

        m_renderableFont =set.m_renderableFont;
        m_renderablePen = set.m_renderablePen;
        m_renderableFillBrush = set.m_renderableFillBrush;
        m_opacity = set.m_opacity;
        //m_renderableCurrentMat = set.m_renderableCurrentMat;

        return *this;
      }

      inline Pen & RenderablePen(){ m_did_pen_set = !false; return m_renderablePen; }
      inline Font & RenderableFont(){ m_did_font_set = !false; return m_renderableFont; }
      inline FillBrush & RenderableBrush(){ m_did_brush_set = !false; return m_renderableFillBrush; }
      inline float & RenderableOpacity(){ m_did_opacity_set = !false; return m_opacity; }

      bool m_did_font_set;
      bool m_did_brush_set;
      bool m_did_pen_set;
      bool m_did_matrix_set : 4;
      bool m_did_opacity_set : 4;

    private:
      float m_opacity;
      Font m_renderableFont;
      Pen m_renderablePen;
      FillBrush m_renderableFillBrush;
      TransformMatrix m_renderableCurrentMat;
    };

  }//namespace Render
}//namespace Magna

#endif  /*  RENDERSTATESET_H  */