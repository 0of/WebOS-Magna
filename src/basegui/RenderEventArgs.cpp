#include "RenderEventArgs.h"

#include "EventArgConstants.h"

namespace Magna{
  namespace GUI{
    
    RenderingEventArgs::RenderingEventArgs( const IntegerRectRegion& renderingRegion , RenderManager *manager )
      :AbstractedEventArgs( GUIEventConstants::GUIEvent_Rendering )
      ,m_renderingRectRegion( renderingRegion )
      ,m_renderManager( manager ){

    }

    RenderManager2D * RenderingEventArgs::getRenderManager2D(){
      RenderManager2D * _ret_2d_manager = Nullptr;
      if( m_renderManager != Nullptr &&  m_renderManager->getType() == RenderManager::ManagerType_Default2D ){
        _ret_2d_manager = static_cast<RenderManager2D *>( m_renderManager );
      }
      return _ret_2d_manager;
    }

  }//namespace GUI
}//namespace Magna