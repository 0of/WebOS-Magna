#ifndef RENDERMANAGER2D_H
#define RENDERMANAGER2D_H

#include "basedef/SpinMutex.h"

#include "TransformMatrix.h"
#include "RenderManager.h"
#include "Canvas2dDrawer.h"

#include "RenderStateSet.h"

#include <stack>

namespace Magna{
  namespace Render{
    
    class RENDER_LIB_EXPORT RenderManager2D : public RenderManager{
      __Constructor_Destructor public:
        RenderManager2D();
        explicit RenderManager2D( DyadCoordinateMapper *coordinateMapper );
        virtual ~RenderManager2D();

      public:
        bool retrieveDrawer( Canvas2DDrawer &drawer );
        void pullbackDrawer( Canvas2DDrawer &drawer );

        void setRenderableOpacity( float opacity );
        void setRenderableFont( const Font& f );

        void setRenderableBrush( const FillBrush& brush );
        void setTransform( const TransformMatrix& mat );

        void clearState();


      __Override_Methods public:
        virtual void activate( ManipulateEngine &engine, const unicode_char *id ) ;
        virtual void deactivate() ;

      private:
        SpinMutex m_retrieveMutex;
        float m_renderableOpacity;
        RenderStateSet m_currentStateSet;
        std::stack<RenderStateSet> m_stateSetStack;      
        Canvas2DDrawer *m_initDrawer;


    };
  }//namespace Render
}//namespace Magna

#endif  /*  RENDERMANAGER2D_H  */