#include "RadialGradient.h"

#include <sstream>

namespace Magna{  
   namespace Render{
     RadialGradient::RadialGradient()
        :Gradient( Gradient::GradientType_Radial )
        ,m_center()
        ,m_focus()
        ,m_centerRadius()
        ,m_focusRadius(){

     }

     RadialGradient::RadialGradient( const IntegerDyadCoordinate& center, float centerRadius
       ,  const IntegerDyadCoordinate& focus, float focusRadius)
      :Gradient( Gradient::GradientType_Radial )
        ,m_center( center )
        ,m_focus( focus )
        ,m_centerRadius( centerRadius )
        ,m_focusRadius( focusRadius ){

     }

     RadialGradient::RadialGradient( sint32 xCenter, sint32 yCenter, float centerRadius
       ,  sint32 xFocus, sint32 yFocus, float focusRadius)
       :Gradient( Gradient::GradientType_Radial )
        ,m_center( xCenter, yCenter )
        ,m_focus( xFocus, yFocus )
        ,m_centerRadius( centerRadius )
        ,m_focusRadius( focusRadius ){

     }

     RadialGradient::~RadialGradient(){

     }

     String RadialGradient::_toString( const IntegerDyadCoordinate& offset ) const{
       OutStringStream _outter;

       auto _focus = m_focus + offset;
       auto _center = m_center + offset;

      _outter << "var _rgradient=context.createRadialGradient("
        << _focus.getX() << ',' << _focus.getY() << ','
        << m_focusRadius << ',' << _center.getX() << ','
        << _center.getY() << ',' << m_centerRadius;

      std::list<Gradient::GradientStop>::const_iterator _t_iter = m_stops.begin();
      for( ; _t_iter != m_stops.end(); ++_t_iter ){
        _outter << "gradient.addColorStop(" << _t_iter->second ;
      }
      return _outter.str();
     }
   }//Render
}//Magna