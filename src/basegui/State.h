#ifndef STATE_H
#define STATE_H

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"

#include "basedef/Trigger.h"
using namespace Magna::Core;

namespace Magna{
   namespace GUI{
     template<typename StateType>
     class State{
      __Constructor_Destructor public:
        State() :m_stateName()/*,  m_stateInfo()*/, m_priority(0){}
        explicit State( const StateType& name, uint32 priority = 0 )
          :m_stateName( name )/*,  m_stateInfo()*/, m_priority( priority ){}
        //explicit State( const StateType& name, const UnionVariant& info, uint32 priority = 0 )
        //  :m_stateName( name ),  m_stateInfo( info ), m_priority( priority ){}
        State ( const State<StateType>& state )
          :m_stateName( state.m_stateName )/*,  m_stateInfo( state.m_stateInfo )*/, m_priority( state.m_priority ){}
        ~State(){}

      __Getter public:
        inline const StateType& getStateName() const { return m_stateName ; }
        //inline const UnionVariant& getStateInfo() const { return m_stateInfo; }
        inline uint32 getPriority() const { return m_priority; }

      __Overloaded_Methods public:
        bool operator == ( const State<StateType>& state){
          return m_stateName == state.m_stateName;
        }

        bool operator != ( const State<StateType>& state ){
          return m_stateName != state.m_stateName;
        }

        State<StateType>& operator =( const State<StateType>& state ){
          m_stateName = state.m_stateName;
          //m_stateInfo = state.m_stateInfo;
          m_priority = state.m_priority;
          return *this;
        }

      __Data_Field private:
        StateType m_stateName;
        //UnionVariant m_stateInfo;
        uint32 m_priority;
     };
   }//GUI
}//Magna

#endif  /*  STATE_H  */
