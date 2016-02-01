#include "Color.h"

#include <sstream>
#include <cassert>
#include <cstring>

namespace Magna{
   namespace Core{
     Color::Color()
       :m_red( 0 )
       ,m_green( 0 )
       ,m_blue( 0 )
       ,m_alpha( 0xFF ){


     }

     Color::Color( RGBColor color )
       :m_red( 0 )
       ,m_green( 0 )
       ,m_blue( 0 )
       ,m_alpha( 0xFF ){

     }

    Color::Color( uint8 red, uint8 green, uint8 blue, uint8 alpha_channel )
       :m_red( red )
       ,m_green( green )
       ,m_blue( blue )
       ,m_alpha( alpha_channel ){

     }

    Color::Color( const Color& color ){
      ::memcpy( this, &color, sizeof( Color ) );
    }

    Color::~Color(){

    }

    RGBColor Color::toRGBColor() const{
      return RGBColorMake(m_red,m_green,m_blue);
    }

    String Color::toString() const{
      OutStringStream _outter;
      _outter << "'";
      if( m_alpha == 255 ){
        _outter << L"#";
        _outter.flags( std::ios::hex );
        _outter << m_red <<  m_green <<  m_blue ;
      }
      else{
        _outter << L"rgba("
          << m_red << L","
          << m_green << L","
          << m_blue << L",";
        _outter.precision(3);
        _outter << (static_cast<float>(m_alpha) / 255.00) << ")";
      }
      _outter << L"'";
      return _outter.str();
    }

    String Color::toString( ColorStringFormat format, ColorStringQualifiers qualifiers, ColorStringNumericBase base ) const{
      OutStringStream _outter;
      if( (qualifiers & ColorStringQualifier_Quotations) != 0 ){
        _outter << L"'";
      }

      if( (qualifiers & ColorStringQualifier_NumberSign) != 0 ){
        //assert
        assert( format != ColorStringFormat_Warpper_RGBA && format != ColorStringFormat_Warpper_RGB );
        _outter << L"#";
      }

      if( (qualifiers & ColorStringQualifier_NumericBase ) != 0 ){
        //assert
        assert( format != ColorStringFormat_Warpper_RGBA && format != ColorStringFormat_Warpper_RGB );
        _outter.setf ( std::ios::showbase );
      }

      switch( base ){
        case  ColorStringNumericBase_Hexadecimal:
          _outter.flags( std::ios::hex );
          break;

        case ColorStringNumericBase_Decimal:
          _outter.flags( std::ios::dec );
          break;

        case ColorStringNumericBase_Octal:
          _outter.flags( std::ios::oct );
          break;

        default:break;
      }

      switch( format ){
        case  ColorStringFormat_Numeric_RGB:
          _outter << m_red << m_green << m_blue ;
          break;

        case  ColorStringFormat_Warpper_RGBA:
          _outter << L"rgba("<< m_red << L","
            << m_green << L","
            << m_blue << L",";
          _outter.precision(3);
          _outter << (static_cast<float>(m_alpha) / 255.00) << ")";
          break;

        case ColorStringFormat_Numeric_ARGB:
          _outter << m_alpha << m_red << m_green << m_blue ;
          break;

        case ColorStringFormat_Warpper_RGB:
          _outter << L"rgb("<< m_red << L","
            << m_green << L","
            << m_blue << L")";
          break;

        default:
          break;
      }

      if( (qualifiers & ColorStringQualifier_Quotations) != 0 ){
        _outter << L"'";
      }
      return _outter.str();
    }

    Color & Color::operator = ( const Color& color ){
      ::memcpy( this, &color, sizeof( Color ) );
      return *this;
    }

    bool Color::operator == ( const Color& color ){
      return (*reinterpret_cast<uint32*>(this))
        == (*reinterpret_cast<uint32*>(&const_cast<Color&>(color)));
    }

   }//Core
}//Magna
