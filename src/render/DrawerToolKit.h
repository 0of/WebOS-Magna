#ifndef DRAWERTOOLKIT_H
#define DRAWERTOOLKIT_H

#include "RenderStateSet.h"

#include <stack>

namespace Magna{
  namespace Render{
    class RenderManager2D;

    class DrawerToolKit{
      public:    
        explicit DrawerToolKit( const RenderStateSet& currentStateSet
          , std::stack<RenderStateSet> &stateSetStack
          , RenderManager2D &manager
          , const IntegerDyadCoordinate& toRenderableCoordOffset /*DyadCoordinateMapper *coordinateMapper*/
          , OutStringStream & outter )
          :m_currentState( currentStateSet ), m_stateSetStack( stateSetStack )
          ,  m_outter(outter), m_toRenderableCoordOffset( toRenderableCoordOffset ), m_bindingManager(manager) {}
  
        //////////////////////////////////////////////////////////////////////////
        // copy ?
        //DrawerToolKit( const DrawerToolKit& toolKit )
        //  :m_font( toolKit.m_font), m_brush( toolKit.m_brush )
        //  ,m_pen( toolKit.m_pen ), m_outter( toolKit.m_outter ){}
        RenderStateSet m_currentState;
        IntegerDyadCoordinate m_toRenderableCoordOffset ;
        std::stack<RenderStateSet> &m_stateSetStack;
        OutStringStream &m_outter;
        RenderManager2D &m_bindingManager;

    };
  }//namespace Render
}//namespace Magna
#endif  /*  DRAWERTOOLKIT_H   */