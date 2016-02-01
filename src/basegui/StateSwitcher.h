#ifndef STATESWITCHER_H
#define STATESWITCHER_H

#include "basegui_lib.h"

#include "State.h"

#include <list>
#include <map>

namespace Magna{
   namespace GUI{


     template<typename StateType>
     struct SingleSwitcherMode{
       typedef  typename std::map<StateType, State<StateType> >::const_iterator StateNode;
     };

     template<typename StateType>
     struct MultiplexedSwitcherMode{
       typedef  std::list<typename std::map<StateType, State<StateType> >::const_iterator > StateNode;
     };


     template<typename StateType>
     class StateSwitcher{
     public:
      TRIGGER_DEF(OnceStateSwitched, const State<StateType>& , bool )
      TRIGGER_DEF(OnceStateSwitchedWithStateName,const StateType& , bool )

    __Constructor_Destructor protected:
      StateSwitcher(): m_states(){}
      ~StateSwitcher(){}

     public:
       void addState( const State<StateType>& state ){
         assert( m_states.count( state.getStateName() ) == 0 );

         m_states[ state.getStateName() ] = state;
        }

       void resetAt( const State<StateType>& state ){
         auto  _find_iter = m_states.find( state.getStateName() );
         if( _find_iter != m_states.end() ){
           *_find_iter = state;
          }
        }

       __Getter public:
        void getStateBy( const StateType& stateName, State<StateType>& out_state ){
          auto  _find_iter = m_states.find( stateName );
          if( _find_iter != m_states.end() ){
            out_state = *_find_iter;
          }
        }

        __Data_Field protected:
        std::map<StateType, State<StateType> > m_states;
     };

     template<typename StateType, template<typename Type = StateType> class SwitcherModePolicy> class ImplStateSwitcher;

     template<typename StateType>
     class BASEGUI_LIB_EXPORT ImplStateSwitcher<StateType, SingleSwitcherMode > : public StateSwitcher<StateType>{
       __Constructor_Destructor public:
        ImplStateSwitcher() :StateSwitcher<StateType>(),m_node(StateSwitcher<StateType>::m_states.end()) {}
        ~ImplStateSwitcher(){}

      public:
        void switches( const StateType& stateName ){
          auto  _find_iter = StateSwitcher<StateType>::m_states.find( stateName );
          assert( _find_iter != StateSwitcher<StateType>::m_states.end() );
          m_node = _find_iter;
        }

      __Checker public:
        inline bool isStateOn( const StateType& stateName ) const {
          return m_node->second.getStateName() == stateName ? true : false;
        }

       __Data_Field private:
        typename SingleSwitcherMode<StateType>::StateNode m_node;
     };


      template<typename StateType>
     class BASEGUI_LIB_EXPORT ImplStateSwitcher<StateType, MultiplexedSwitcherMode > : public StateSwitcher<StateType>{
      public:
        class StatePriorityComparer{
        __Overloaded_Methods public:
          bool operator()( const typename std::map<StateType, State<StateType> >::const_iterator& i1
            , const typename std::map<StateType, State<StateType> >::const_iterator& i2 ){
              return (i1->second).getPriority() < (i2->second).getPriority();
          }
        };

       __Constructor_Destructor public:
        ImplStateSwitcher() :StateSwitcher<StateType>(), m_node(), m_startFlag(0) {}
        ~ImplStateSwitcher(){}

      __Checker public:
        inline bool isStateOn( const StateType& stateName ) const {
          bool _isOn = false;
          auto _iter = m_node.begin();
          for( ;_iter != m_node.end(); ++_iter){
            _isOn = (*_iter)->second.getStateName() == stateName;
            if( _isOn ){
              break;
            }
          }
          return _isOn;
        }

      public:
        void beginSwitching(){
          m_node.clear();
          m_startFlag = ~0x0;
        }

        void endSwitching(){
          m_node.sort( StatePriorityComparer() );
          m_startFlag = (~m_startFlag);

          //trigger state changed
          auto _iter = m_node.begin();
          for( ; _iter != m_node.end(); ++_iter ){
            StateSwitcher<StateType>::OnceStateSwitched.triggers( (*_iter)->second, !false );
            StateSwitcher<StateType>::OnceStateSwitchedWithStateName.triggers( (*_iter)->first, !false );
          }

        }

        void switches( const StateType& stateName ){
          assert( m_startFlag != 0 );
          auto  _find_iter = StateSwitcher<StateType>::m_states.find( stateName );
          assert( _find_iter != StateSwitcher<StateType>::m_states.end() );
          m_node.push_back(_find_iter);

        }

        //only append state and trigger the state switched
        void attachState( const StateType& stateName ){
          auto  _find_iter = StateSwitcher<StateType>::m_states.find( stateName );
          assert( _find_iter != StateSwitcher<StateType>::m_states.end() );

          bool _existed = false;
          auto _existed_iter = m_node.begin();
          for( ; _existed_iter != m_node.end(); ++_existed_iter ){
            if( *_existed_iter == _find_iter ){
              _existed = !false;
              break;
            }
          }

          if( !_existed ){
            m_node.push_back(_find_iter);
            StateSwitcher<StateType>::OnceStateSwitched.triggers( _find_iter->second, !false );
            StateSwitcher<StateType>::OnceStateSwitchedWithStateName.triggers( _find_iter->first, !false );
          }
        }

        void detachState( const StateType& stateName ){
          auto  _find_iter = StateSwitcher<StateType>::m_states.find( stateName );
          assert( _find_iter != StateSwitcher<StateType>::m_states.end() );

          bool _existed = false;
          auto _existed_iter = m_node.begin();
          for( ; _existed_iter != m_node.end(); ++_existed_iter ){
            if( *_existed_iter == _find_iter ){
              _existed = !false;
              break;
            }
          }

          if( _existed ){
            m_node.erase( _existed_iter );
            StateSwitcher<StateType>::OnceStateSwitched.triggers( _find_iter->second, false );
            StateSwitcher<StateType>::OnceStateSwitchedWithStateName.triggers( _find_iter->first, false );
          }
        }

       __Data_Field private:
        uint32 m_startFlag;
        typename MultiplexedSwitcherMode<StateType>::StateNode m_node;
     };






   }//GUI
}//Magna
#endif  /*  STATESWITCHER_H  */
