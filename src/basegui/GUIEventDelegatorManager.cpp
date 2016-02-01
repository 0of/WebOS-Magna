
#include "GUIEventDelegatorManager.h"

#include <cassert>

namespace Magna{
  namespace GUI{

    ControllerRootDelegatorManager & ControllerRootDelegatorManager::obtainDelegator(){
      static ControllerRootDelegatorManager _manager;
      return _manager;
    }

    ControllerRootDelegatorManager::EventDelegatorManager()
      :DelegatorManager(){

        ForwardDelegator _delegator = &Controller::ControllerRoot::mousePressed;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MousePressed, _delegator ) );
        
        _delegator = &Controller::ControllerRoot::mousePressingMoved;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MousePressingMoved, _delegator  ) );

        _delegator = &Controller::ControllerRoot::mouseReleased;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseReleased, _delegator) );

        _delegator = &Controller::ControllerRoot::mouseClicked;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseClicked, _delegator ) );

        _delegator = &Controller::ControllerRoot::mouseDoubleClicked;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseDoubleClicked, _delegator ) );
          
        auto _wheel_event_delegator = &Controller::ControllerRoot::mouseWheelUp;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseWheelUp, _wheel_event_delegator ) );

        _wheel_event_delegator = &Controller::ControllerRoot::mouseWheelDown;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseWheelDown, _wheel_event_delegator ) );

        auto _key_event_delegator = &Controller::ControllerRoot::keyPressed;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_KeyPressed, _key_event_delegator ) );

        _key_event_delegator = &Controller::ControllerRoot::keyReleased;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_KeyReleased, _key_event_delegator) );

        auto _hover_event_delegator = &Controller::ControllerRoot::hoverIn;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseHoverIn, _hover_event_delegator ) );

        _hover_event_delegator = &Controller::ControllerRoot::hovered;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseHovered, _hover_event_delegator ) );

        _hover_event_delegator = &Controller::ControllerRoot::hoverOut;
        DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_MouseHoverOut, _hover_event_delegator) );


    }

    ControllerRootDelegatorManager::~EventDelegatorManager(){

    }

    ControllerRootDelegatorManager::ForwardDelegator ControllerRootDelegatorManager::getDelegator( const DelegatorManager::key_type& key ){
      auto _found = find( key ) ;
      assert( _found != end() );
      return _found->second;
    }


    WindowRootDelegatorManager & WindowRootDelegatorManager::obtainDelegator(){
      static WindowRootDelegatorManager _manager;
      return _manager;
    }

    WindowRootDelegatorManager::EventDelegatorManager()
      :DelegatorManager(){

      ForwardDelegator _delegator = &Window::WindowRoot::windowMoved;
      DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_Moved, _delegator ) );

      ForwardDelegator _resized_delegator = &Window::WindowRoot::windowResized;
      DelegatorManager::emplace( std::make_pair( GUIEventConstants::GUIEvent_Resized, _resized_delegator ) );
    }

    WindowRootDelegatorManager::~EventDelegatorManager(){

    }

    WindowRootDelegatorManager::ForwardDelegator WindowRootDelegatorManager::getDelegator( const DelegatorManager::key_type& key ){
      auto _found = find( key ) ;
      assert( _found != end() );
      return _found->second;
    }

  }//namespace GUI
}//namespace Magna