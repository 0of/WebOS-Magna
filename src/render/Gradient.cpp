#include "Gradient.h"

#include "basedef/Comparer.h"

#include <cassert>

namespace Magna{  
   namespace Render{
     Gradient::Gradient( Gradient::GradientType childType )
       :m_type( childType ), m_stops(){

     }

     Gradient::~Gradient() {

     }

     void Gradient::setColorAt( const Color& color, float at ){
       assert( !Comparer<float>::isLowerThanZero( at ) 
         && !Comparer<float>::isHigherThan( at, 1.00 ) );
       m_stops.push_back( std::make_pair(color,at) ) ;
     }
     void Gradient::addStop( const GradientStop& stop ){
       assert( !Comparer<float>::isLowerThanZero( stop.second ) 
         &&  !Comparer<float>::isHigherThan( stop.second, 1.00 )  ); 
       m_stops.push_back( stop );
     }

     void Gradient::clearStop(){
       m_stops.clear();
     }
   }//Render
}//Magna
