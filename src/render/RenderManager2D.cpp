#include "RenderManager2D.h"

#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "DrawerToolKit.h"
#include "RenderStateSet.h"

#include "ManipulateDevice.h"
#include "ManipulateEngine.h"

namespace Magna{
  namespace Render{
    RenderManager2D::RenderManager2D()
      :RenderManager(RenderManager::ManagerType_Default2D)
      ,m_retrieveMutex()
      ,m_renderableOpacity( 1.0 )
      ,m_currentStateSet()
      ,m_stateSetStack()
      ,m_initDrawer( Nullptr ){

    }

    RenderManager2D::RenderManager2D( DyadCoordinateMapper *coordinateMapper  )
      :RenderManager(RenderManager::ManagerType_Default2D)
      ,m_retrieveMutex()
      ,m_renderableOpacity( 1.0 )
      ,m_currentStateSet()
      ,m_stateSetStack()
      ,m_initDrawer( Nullptr ) {
      m_coordinateMapper = coordinateMapper;
    }

    RenderManager2D::~RenderManager2D(){

    }

    void RenderManager2D::clearState(){
      m_currentStateSet = RenderStateSet();

      while( !m_stateSetStack.empty() ){
        m_stateSetStack.pop();
      }
    }


    bool RenderManager2D::retrieveDrawer( Canvas2DDrawer &drawer ){
      bool _retrieveSucc = false;
      m_retrieveMutex.acquires();

      if( m_initDrawer == Nullptr
        && m_manipulator != Nullptr
        && m_manipulator->getType() == Manipulator::Type_Script ){

        IntegerDyadCoordinate offset;
        if( m_coordinateMapper != Nullptr ){
          offset = m_coordinateMapper->toCoordOnManipulateDevice( IntegerDyadCoordinate( 0, 0 ) );
        }

        ScriptManipulator *scriptMani = reinterpret_cast<ScriptManipulator *>(m_manipulator);

        DrawerToolKit *_genToolKit
          = new DrawerToolKit(m_currentStateSet  //current state set
          , m_stateSetStack  //global state set
          , *this  //binding manager
          ,  offset  //coordinate mapper
          , scriptMani->getOutter() );  //script outter

        drawer.m_toolKit = _genToolKit;
        _retrieveSucc = !false;
      }

      m_retrieveMutex.releases();

      return _retrieveSucc;
    }

    void RenderManager2D::pullbackDrawer( Canvas2DDrawer &drawer ){
      if( m_initDrawer != Nullptr
        && m_initDrawer != &drawer
        && (&m_initDrawer->m_toolKit->m_bindingManager == this) ){
        delete m_initDrawer->m_toolKit;
        m_initDrawer = Nullptr;

        //clear the stack
        while( !m_stateSetStack.empty() )
          m_stateSetStack.pop();
      }
    }

    void RenderManager2D::activate( ManipulateEngine &engine, const unicode_char *id ) {

      if( id != Nullptr ){
        engine.occupy();

        m_engine = &engine;
        m_manipulator = &engine.getDefaultScriptManipulator();


        auto &_outter = engine.getDefaultScriptManipulator().getOutter();

        //find element
        _outter << L"{var canvas=document.getElementById("
          << id
          << L");if(canvas!=null){var context=canvas.getContext(\"2d\");";

      }
    }

    void RenderManager2D::deactivate() {
      if( m_engine != Nullptr ){
        if( m_engine->isOccupied() ){
          if( m_manipulator->getType() == Manipulator::Type_Script ){
            ScriptManipulator *_manipulator = reinterpret_cast<ScriptManipulator *>( m_manipulator );

            _manipulator->getOutter() << L"}}";

            m_engine->deoccupy();

            m_engine = Nullptr;
            m_manipulator = Nullptr;
          }
        }
      }
    }

    void RenderManager2D::setRenderableOpacity( float opacity ){
      m_renderableOpacity = opacity;
    }
    void RenderManager2D::setRenderableFont( const Font& f ){
      m_currentStateSet.RenderableFont() = f;
    }

    void RenderManager2D::setRenderableBrush( const FillBrush& brush ){
      m_currentStateSet.RenderableBrush() = brush;
    }
    //void setTransform( const TransformMatrix& mat );

  }//namespace Render
}//namespace Magna
