#ifndef DRAWER_H
#define DRAWER_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include "render_lib.h"

namespace Magna{
   namespace Render{
     struct DrawerEngine{
       enum Value{
         DrawerEngine_Canvas2D,
         DrawerEngine_SVG,

         DrawerEngine_WebGL
       };
     };
     template<DrawerEngine::Value value>
     class Drawer;

    class DrawerToolKit;
   }//Render
}//Magna

#endif  /*  DRAWER_H  */
