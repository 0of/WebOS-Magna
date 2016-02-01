#ifndef GUIEVENTDELEGATORMANAGER_H
#define GUIEVENTDELEGATORMANAGER_H

#include "basedef/Uncopyable.h"

#include <unordered_map>

#include "Controller_p.h"
#include "Window_p.h"

#include "EventDelegator.h"
#include "EventArgConstants.h"


namespace Magna{
  namespace GUI{


    /*
    typedef Delegator<Controller::ControllerRoot, AbstractedEventArgs> ForwardDelegator ;
    typedef std::hash_map<GUIEventConstants::EventType, ForwardDelegator> DelegatorManager;
    class ControllerRootDelegatorManager : private DelegatorManager, Uncopyable{                                      
    public:
      static ControllerRootDelegatorManager & obtainDelegator();
    private:      
      ControllerRootDelegatorManager();
      ~ControllerRootDelegatorManager();

    public:  
      ForwardDelegator getDelegator( const DelegatorManager::key_type& key );
    };
    */

    //hash functions
    struct KeyHash {
       std::size_t operator()(const GUIEventConstants::EventType& key) const{
          return std::hash<uint32>()(key);
       }
    };

    struct KeyEqual {
     bool operator()(const GUIEventConstants::EventType& _cmpr, const GUIEventConstants::EventType& _cmpr_a) const{
        return _cmpr == _cmpr_a;
     }
    };


    template<typename T>
    class EventDelegatorManager;
    
    typedef EventDelegatorManager<Controller::ControllerRoot> ControllerRootDelegatorManager;
    typedef EventDelegatorManager<Window::WindowRoot> WindowRootDelegatorManager;

    template<>
    class EventDelegatorManager<Controller::ControllerRoot> 
      :  std::unordered_map<GUIEventConstants::EventType, Delegator<Controller::ControllerRoot, AbstractedEventArgs>,KeyHash,KeyEqual>, Uncopyable{
    public:
      typedef Delegator<Controller::ControllerRoot, AbstractedEventArgs> ForwardDelegator ;
      typedef std::unordered_map<GUIEventConstants::EventType, ForwardDelegator,KeyHash,KeyEqual> DelegatorManager;

    public:  
      EventDelegatorManager();
      ~EventDelegatorManager();

      static ControllerRootDelegatorManager & obtainDelegator();
      ForwardDelegator getDelegator( const DelegatorManager::key_type& key );

    };

    template<>
    class EventDelegatorManager<Window::WindowRoot> 
      :  std::unordered_map<GUIEventConstants::EventType, Delegator<Window::WindowRoot, AbstractedEventArgs>,KeyHash,KeyEqual >, Uncopyable{
    public:
      typedef Delegator<Window::WindowRoot, AbstractedEventArgs> ForwardDelegator ;
      typedef std::unordered_map<GUIEventConstants::EventType, ForwardDelegator,KeyHash,KeyEqual> DelegatorManager;

    public:  
      EventDelegatorManager();
      ~EventDelegatorManager();

      static WindowRootDelegatorManager & obtainDelegator();
      ForwardDelegator getDelegator( const DelegatorManager::key_type& key );

    };
    

  }//namespace GUI
}//namespace Magna

#endif  /*  GUIEVENTDELEGATORMANAGER_H  */
