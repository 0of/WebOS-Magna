#ifndef RENDEREVENTARGS_H
#define RENDEREVENTARGS_H

#include "basegui_lib.h"

#include "basedef/AbstractedEventArgs.h"
#include "basedef/RectRegion.h"
using namespace Magna::Core;

#include "render/RenderManager.h"
#include "render/RenderManager2D.h"
using namespace Magna::Render;

#include "GUIEventIndexer.h"
using namespace Magna;

#include "EventArgsAccessor.h"

namespace Magna{
  namespace GUI{
    class BASEGUI_LIB_EXPORT RenderingEventArgs : public __Generalizes AbstractedEventArgs{
      friend class EventArgsAccessor<Rendering>;
      __Constructor_Destructor public:
        explicit RenderingEventArgs( const IntegerRectRegion& renderingRegion , RenderManager *manager );
        ~RenderingEventArgs(){}

      __Getter public:
        //deprecated
      
        RenderManager * getRenderManager() { return m_renderManager ;}
        const IntegerRectRegion & getRenderingRectRegion() const { return m_renderingRectRegion; }

        RenderManager2D *getRenderManager2D(); 
      
      __Data_Field private:
        IntegerRectRegion m_renderingRectRegion;
        RenderManager *m_renderManager;
    };

  }//namespace GUI
}//namespace Magna
#endif  /*  RENDEREVENTARGS_H  */