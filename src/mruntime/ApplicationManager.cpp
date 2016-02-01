#include "ApplicationManager.h"

#include <cassert>
#include <random>

namespace Magna{
  namespace Application{
    ApplicationManager &ApplicationManager::getApplicationManager(){
      static ApplicationManager _manager;
      return _manager;
    }

    ApplicationManager::ApplicationManager()
      :m_blocks(){

    }

    ApplicationManager::~ApplicationManager(){
      auto _begin = m_blocks.begin();
      while( [&]()->bool{
        bool _continued = _begin != m_blocks.end() ;
        if( _continued ){
          auto _each_block = _begin->second;        
           
          for( ; !_each_block->isFinished() ;Thread::yield() ){}

          delete _each_block;
          ++_begin;
        }
        return _continued;
      }()){}
  
    }

    void ApplicationManager::pushAppTaskBlock( ApplicationTaskBlock *app ){
      //gen random id

      std::random_device _dev_gen;
#ifdef _MSC_VER
      std::linear_congruential_engine<uint32, 16807, 10000, 40000> _linear_eng ( _dev_gen );
#elif defined __GNUG__
      std::mt19937 _linear_eng( _dev_gen() );
#endif
      //the id of 10000 can not be reached by any applications
      uint32 _gen_id = 10000;
      //ensure id unique
      //enter critical section
      m_mutex.acquires();    
      while( [&]() -> bool{ _gen_id = _linear_eng()
          ; return m_blocks.count( _gen_id )  != 0; }() ){}         

      
      app->assignBlockId( _gen_id );

      m_blocks.emplace( std::make_pair(_gen_id, app) );
      //leave critical section
      m_mutex.releases();
    }

    void ApplicationManager::pushSpecificAppTaskBlock( ApplicationTaskBlock *app, uint32 id ){
      m_mutex.acquires();    

      assert( m_blocks.count( id ) == 0 );
      m_blocks.emplace( std::make_pair(id, app) );

      m_mutex.releases();
    }

    void ApplicationManager::endAppTaskBlock( uint32 aid ){
      m_mutex.acquires();    

      auto _found_it = m_blocks.find( aid );
      if( _found_it != m_blocks.end() ){
        auto _found = _found_it->second;
        
        for( ; !_found->isFinished() ;Thread::yield() ){}

        delete _found;
        m_blocks.erase ( _found_it );    
      }

      m_mutex.releases();
    }

  }//namespace Application
}//namespace Magna
