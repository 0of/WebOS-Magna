#include "ManipulateEngine.h"

#include "basedef/Thread.h"
using namespace Magna::Core;

namespace Magna{
  namespace Render{

    ManipulateEngine::ManipulateEngine()
      :m_availScriptManipulators()
      ,m_reservedScriptManipulators()
      ,m_mutex()
      ,m_resMutex()
      ,m_occupied( 0 ){

      m_availScriptManipulators.push_back( new ScriptManipulator );
    }

    ManipulateEngine::~ManipulateEngine(){

    }

    ScriptManipulator & ManipulateEngine::getDefaultScriptManipulator(){
      ScriptManipulator *_manipulator = Nullptr;
      m_mutex.acquires();
      if( m_availScriptManipulators.empty() ){
        m_availScriptManipulators.push_back( new ScriptManipulator );
      }
      _manipulator = m_availScriptManipulators.at( 0 );
      m_mutex.releases();

      return *_manipulator;
    }

    void ManipulateEngine::makeReservation(){
      for( ; m_occupied.read() ==1; Thread::yield() ){}
      m_resMutex.acquires();
      if( !m_availScriptManipulators.empty() ){
        m_mutex.acquires();
        m_reservedScriptManipulators.push_back( m_availScriptManipulators.front() );
        m_availScriptManipulators.erase( m_availScriptManipulators.begin() );
        m_mutex.releases();
      }
      m_resMutex.releases();
    }

    void ManipulateEngine::cancelReservation(){
      m_mutex.acquires();
      //clear all
      for( auto _iter = m_reservedScriptManipulators.begin()
        ; _iter != m_reservedScriptManipulators.end(); ++_iter ){
        if( (*_iter) != Nullptr ){
          (*_iter)->getOutter().clear();
          (*_iter)->getOutter().str( L"" );
          m_availScriptManipulators.push_back( (*_iter) );
        }
      }
      m_reservedScriptManipulators.clear();
      m_mutex.releases();
    }

    void ManipulateEngine::occupy(){
      for( ; m_occupied.read() ==1; Thread::yield() ){}
      m_occupied.write( 1 ) ;
    }

    void ManipulateEngine::deoccupy(){
      m_occupied.write( 0 );
    }


  }//namespace Render
}//namespace Magna
