#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#include "render_lib.h"

#include "DyadCoordinateMapper.h"
#include "ManipulateDevice.h"
#include "Manipulator.h"

#include <sstream>

namespace Magna{
   namespace Render{
     //////////////////////////////////////////////////////////////////////////
     class RENDER_LIB_EXPORT RenderManager{
       friend class RenderableElement;
    __Constants public:
      enum ManagerType{
        ManagerType_Default2D = 0
      };
     __Constructor_Destructor protected:
       explicit RenderManager( ManagerType type)
         :m_type(type), m_manipulator( Nullptr )
        ,m_coordinateMapper( Nullptr )
        ,m_engine( Nullptr ){

       }
       virtual ~RenderManager() {}

    __Getter public:
       inline ManagerType getType() const { return m_type; }
       inline bool isActivited() const { return m_manipulator != Nullptr; }

       virtual void activate( ManipulateEngine &engine, const unicode_char *id ) = 0;
       virtual void deactivate() = 0;

       void resetCoordinateMapper( DyadCoordinateMapper *coordinateMapper ){
         m_coordinateMapper = coordinateMapper;
       }

    __Data_Field protected:
      ManagerType m_type;
      Manipulator *m_manipulator;
      ManipulateEngine *m_engine;
      DyadCoordinateMapper *m_coordinateMapper;
     };
   }//Render
}//Magna

#endif  /*  RENDERMANAGER_H  */
