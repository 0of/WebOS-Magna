#ifndef RENDERINGEVENTARGSACCESSOR_H
#define RENDERINGEVENTARGSACCESSOR_H

#include "EventArgsAccessor.h"
#include "RenderEventArgs.h"

#include "GUIEventIndexer.h"
using namespace Magna;

namespace Magna{
  namespace GUI{
    template<>
    class EventArgsAccessor <Rendering >{
      public:
        inline static IntegerRectRegion & getRenderingRectRegion( RenderingEventArgs & eventArgs){
          return eventArgs.m_renderingRectRegion;
        }
    };
  }//namespace GUI
}//namespace Magna

#endif  /*  RENDERINGEVENTARGSACCESSOR_H  */