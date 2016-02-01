#ifndef RENDERABLECONTEXT_H
#define RENDERABLECONTEXT_H

#include "render_lib.h"

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "ManipulateEngine.h"

namespace Magna{
  namespace Render{
    
    class RENDER_LIB_EXPORT ManipulateDevice{
      protected:
        ManipulateDevice();
        virtual ~ManipulateDevice();

      public:
        ManipulateEngine &getEngine(){ return m_engine; }

      protected:
        ManipulateEngine m_engine;
    };
  
  }//namespace Render
}//namespace Magna

#endif  /*  RENDERABLECONTEXT_H  */