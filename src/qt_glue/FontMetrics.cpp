#include "FontMetrics.h"

#include <QFont>
#include <QFontMetrics>

namespace Magna{
  namespace Glue{
    
    FontMetrics::FontMetrics()
      :m_text()
      ,m_font(){

    }

    FontMetrics::FontMetrics( const Font& f )
      :m_text()
      ,m_font( f ){

    }

    FontMetrics::FontMetrics( const String& text )
      :m_text( text )
      ,m_font(){

    }

    FontMetrics::FontMetrics( const String& text, const Font& f )
      :m_text( text )
      ,m_font( f ){

    }

    FontMetrics::~FontMetrics(){

    }

    void FontMetrics::setMetricsText( const String& text ){
      m_text = text;
    }

    void FontMetrics::setMetricsFont( const Font& f ){
      m_font = f;
    }

    const String& FontMetrics::getMetricsText() const{
      return m_text;
    }

    const Font& FontMetrics::getMetricsFont() const{
      return m_font;
    }

    sint32 FontMetrics::measureHeight() const{
      sint32 _measured_height = 0;

      QFont _q_font;

      const auto & _family = m_font.getFontFamily();

#ifdef _MSC_VER
      _q_font.setFamily(QString::fromUtf16( reinterpret_cast<const ushort *>(_family.c_str()), _family.size() ) );
#else
      _q_font.setFamily( QString::fromStdWString( _family ) );
#endif
      
      _q_font.setPixelSize( m_font.getFontSize() );
      _q_font.setStyle( static_cast<QFont::Style>( m_font.getFontStyle() ) );
      _q_font.setWeight( m_font.getFontWeight() / 10 );      

      QFontMetrics _q_font_metrics( _q_font );
      _measured_height =  _q_font_metrics.height() ;

      return _measured_height;    
    }

    sint32 FontMetrics::measureWidth() const{
      sint32 _measured_width = 0;

      QFont _q_font;

      const auto & _family = m_font.getFontFamily();

#ifdef _MSC_VER
      _q_font.setFamily(QString::fromUtf16( reinterpret_cast<const ushort *>(_family.c_str()), _family.size() ) );
#else
      _q_font.setFamily( QString::fromStdWString( _family ) );
#endif
      _q_font.setPixelSize( m_font.getFontSize() );
      _q_font.setStyle( static_cast<QFont::Style>( m_font.getFontStyle() ) );
      _q_font.setWeight( m_font.getFontWeight() / 10 );      

      QFontMetrics _q_font_metrics( _q_font );
#ifdef _MSC_VER
      _measured_width = ( _q_font_metrics.width( QString::fromUtf16( reinterpret_cast<const ushort *>(m_text.c_str()), m_text.size() )  ) );
#else
      _measured_width = ( _q_font_metrics.width( QString::fromStdWString( m_text ) ) );
#endif

      return _measured_width;  
    }

    IntegerSize FontMetrics::measureSize() const{
      IntegerSize _measured_size;

      QFont _q_font;
      //debug
      //auto &_font_str = f.toString();

      const auto & _family = m_font.getFontFamily();
#ifdef _MSC_VER
      _q_font.setFamily(QString::fromUtf16( reinterpret_cast<const ushort *>(_family.c_str()), _family.size() ) );
#else
      _q_font.setFamily( QString::fromStdWString( _family ) );
#endif
      _q_font.setPixelSize( m_font.getFontSize() );
      _q_font.setStyle( static_cast<QFont::Style>( m_font.getFontStyle() ) );
      _q_font.setWeight( m_font.getFontWeight() / 10 );      

      QFontMetrics _q_font_metrics( _q_font );
#ifdef _MSC_VER
      _measured_size.setWidth( _q_font_metrics.width( QString::fromUtf16( reinterpret_cast<const ushort *>(m_text.c_str()), m_text.size() )  ) );
#else
      _measured_size.setWidth( _q_font_metrics.width( QString::fromStdWString( m_text ) ) );
#endif
    
      _measured_size.setHeight( _q_font_metrics.height()  );

      return _measured_size;
    }

    IntegerSize FontMetrics::measureSize( const String& text, const Font& f  ){
      IntegerSize _measured_size;

      QFont _q_font;
      //debug
      //auto &_font_str = f.toString();

      const auto & _family = f.getFontFamily();
#ifdef _MSC_VER
      _q_font.setFamily(QString::fromUtf16( reinterpret_cast<const ushort *>(_family.c_str()), _family.size() ) );
#else
      _q_font.setFamily( QString::fromStdWString( _family ) );
#endif

      //set QFont pixel size if Font has been set pixel size
      _q_font.setPixelSize( f.getFontSize() );
      _q_font.setStyle( static_cast<QFont::Style>( f.getFontStyle() ) );

      //don't know the exact mapping HTML5 font weight to 
      //QT framework font weight 
      //just divide 10 for getting an approximate weight value
      _q_font.setWeight( f.getFontWeight() / 10 );      

      QFontMetrics _q_font_metrics( _q_font );
#ifdef _MSC_VER
      _measured_size.setWidth( _q_font_metrics.width( QString::fromUtf16( reinterpret_cast<const ushort *>(text.c_str()), text.size() )  ) );
#else
      _measured_size.setWidth( _q_font_metrics.width( QString::fromStdWString( text ) ) );
#endif
      _measured_size.setHeight( _q_font_metrics.height()  );

      return _measured_size;
    }

  }//namespace Glue
}//namespace Magna
