#ifndef DRAWINGPATH_P_H
#define DRAWINGPATH_P_H

#include "BaseTypes.h"
#include "SystemDef.h"

#include "Polygon.h"
#include "RectRegion.h"

namespace Magna{  
   namespace Core{
     class DrawingPathPolicy{
      __Constructor_Destructor public:
        DrawingPathPolicy();
        explicit DrawingPathPolicy( const RealDyadCoordinate& startPos );
        explicit DrawingPathPolicy( const RealRectRegion& rect );
        explicit DrawingPathPolicy( const RealPolygon& polygon );
        DrawingPathPolicy( const DrawingPath& path );

      __Data_Field protected:
        class PathElement{
          
        };


     }
   }//Core
}//Magna

#endif  /*  DRAWINGPATH_P_H  */