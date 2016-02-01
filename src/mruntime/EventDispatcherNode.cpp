#include "EventDispatcherNode.h"
#include "EventArgsMapper.h"

#include "basegui/Window_p.h"
#include "application/Application_p.h"
#include "application/ApplicationWindowManager_p.h"
using namespace Magna::Application;

#include "ControllerManager.h"
#include "WindowManager.h"
using namespace Magna::Kernel;

namespace Magna{
  namespace Runtime{
    QString EventDispatcherNode::shared_NodeName = "DispatcherNode";

    EventDispatcherNode::EventDispatcherNode()
      :QObject(){

    }
    
    EventDispatcherNode::~EventDispatcherNode(){

    }

    void EventDispatcherNode::dispatchMousePressed( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers ){    
      auto _numeric_id = id.toLongLong();
      
      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseEvent< GUIEventConstants::GUIEvent_MousePressed >( _numeric_id, sx, sy, EventArgsMapper::shared_mouseButton_mapper[button], modifiers );
      
    }

    void EventDispatcherNode::dispatchMousePressingMoved(  const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseEvent< GUIEventConstants::GUIEvent_MousePressingMoved >( _numeric_id, sx, sy, EventArgsMapper::shared_mouseButton_mapper[button], modifiers );
    }

    void EventDispatcherNode::dispatchMouseReleased( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseEvent< GUIEventConstants::GUIEvent_MouseReleased >( _numeric_id, sx, sy, EventArgsMapper::shared_mouseButton_mapper[button], modifiers );
    }

    void EventDispatcherNode::dispatchMouseWheelUp( const QString& id , sint32 x, sint32 y, sint32 delta,  uint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseWheelEvent< GUIEventConstants::GUIEvent_MouseWheelUp >( _numeric_id, x, y, delta, modifiers );
    }

    void EventDispatcherNode::dispatchMouseWheelDown( const QString& id , sint32 x, sint32 y, sint32 delta,  uint32 modifiers  ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseWheelEvent< GUIEventConstants::GUIEvent_MouseWheelDown >( _numeric_id, x, y, delta, modifiers );
    }

    void EventDispatcherNode::dispatchMouseClicked( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseEvent< GUIEventConstants::GUIEvent_MouseClicked >( _numeric_id, sx, sy, EventArgsMapper::shared_mouseButton_mapper[button], modifiers );
    }

    void EventDispatcherNode::dispatchMouseDoubleClicked( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchMouseEvent< GUIEventConstants::GUIEvent_MouseDoubleClicked >( _numeric_id, sx, sy, EventArgsMapper::shared_mouseButton_mapper[button], modifiers );
    }

    void EventDispatcherNode::dispatchKeyPressed( const QString& id, qint32 pressedKey, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchKeyEvent< GUIEventConstants::GUIEvent_KeyPressed >( _numeric_id, (pressedKey | modifiers) );
    }

    void EventDispatcherNode::dispatchKeyReleased( const QString& id, qint32 pressedKey, qint32 modifiers ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchKeyEvent< GUIEventConstants::GUIEvent_KeyReleased>( _numeric_id, (pressedKey | modifiers) );
    }

    void EventDispatcherNode::dispatchWindowMoved( const QString& id, qint32 x, qint32 y ){
      auto _numeric_id = id.toLongLong();

      WindowManager &_manager = WindowManager::getWindowManager();
      _manager.dispatchMoveEvent( _numeric_id, x, y );
    }

    void EventDispatcherNode::dispatchWindowResized( const QString& id, qint32 w, qint32 h ){
      auto _numeric_id = id.toLongLong();

      WindowManager &_manager = WindowManager::getWindowManager();
      _manager.dispatchResizeEvent( _numeric_id, w, h );
    }

    void EventDispatcherNode::dispatchHoverIn( const QString& id ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchHoverEvent< GUIEventConstants::GUIEvent_MouseHoverIn >( _numeric_id );
    }

    void EventDispatcherNode::dispatchHoverOut( const QString& id ){
      auto _numeric_id = id.toLongLong();

      ControllerManager &_manager = ControllerManager::getControllerManager();
      _manager.dispatchHoverEvent< GUIEventConstants::GUIEvent_MouseHoverOut >( _numeric_id );
    }

  }
}//namespace Magna