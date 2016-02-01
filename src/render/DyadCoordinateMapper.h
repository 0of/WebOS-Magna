#ifndef DYADOORDINATEMAPPER_H
#define DYADOORDINATEMAPPER_H

#include "render_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/DyadCoordinate.h"

using namespace Magna::Core;

namespace Magna{
  namespace Render{
    __Interface class RENDER_LIB_EXPORT DyadCoordinateMapper {

      __Constructor_Destructor public:
      virtual ~DyadCoordinateMapper() {}

      public:
        virtual IntegerDyadCoordinate toCoordOnScreen( const IntegerDyadCoordinate& coord ) const = 0;
        virtual IntegerDyadCoordinate fromCoordOnScreen( const IntegerDyadCoordinate& coord ) const = 0;

        virtual IntegerDyadCoordinate toCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const = 0;
        virtual IntegerDyadCoordinate fromCoordUnderParentCoordSystem( const IntegerDyadCoordinate& coord ) const = 0;

        virtual IntegerDyadCoordinate toCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const = 0;
        virtual IntegerDyadCoordinate fromCoordOnManipulateDevice( const IntegerDyadCoordinate& coord ) const = 0;
    };

  }//namespace Render
}//namespace Magna

#endif  /*  DYADOORDINATEMAPPER_H  */
