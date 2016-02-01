#include "LinearGradient.h"

#include <sstream>

namespace Magna{  
   namespace Render{
     LinearGradient::LinearGradient()
       :Gradient( Gradient::GradientType_Linear )
       ,m_startCoord()
      ,m_endCoord(){

     }

    LinearGradient::LinearGradient( sint32 xStart, sint32 yStart, sint32 xEnd, sint32 yEnd )
      :Gradient( Gradient::GradientType_Linear )
      ,m_startCoord( xStart, yStart )
      ,m_endCoord( xEnd,yEnd ){

    }

    LinearGradient::LinearGradient( const IntegerDyadCoordinate& start, const IntegerDyadCoordinate& end )
      :Gradient( Gradient::GradientType_Linear )
      ,m_startCoord( start )
      ,m_endCoord( end ){

    }

    LinearGradient::~LinearGradient(){

    }

    String LinearGradient::_toString( const IntegerDyadCoordinate& offset ) const{
      //String _outter;
      //_outter.reserve( 75 );
    
      OutStringStream _outter;

      auto _startCoord = m_startCoord + offset;
      auto _endCoord = m_endCoord + offset;

      _outter <<  "var gradient=context.createLinearGradient("
        << _startCoord.getX() << ","
        << _startCoord.getY() << ","
        << _endCoord.getX() << ","
        << _endCoord.getY() << ");";

      std::list<Gradient::GradientStop>::const_iterator _t_iter = m_stops.begin();
      for( ; _t_iter != m_stops.end(); ++_t_iter ){
        _outter << "gradient.addColorStop(" ;
        _outter.precision(1);
        _outter << _t_iter->second << "," 
          << _t_iter->first.toString() << ");";
      }
      return _outter.str();

    }

   }//Render
}//Magna

