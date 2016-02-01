#include "ApplicationTaskBlock.h"

#include "basedef/RunnableContextAccessor.h"

#include <assert.h>

namespace Magna{
  namespace Application{
    
    class ApplicationEntryRunner : public __Realizes Runner
                              , Uncopyable{
      public:
        ApplicationEntryRunner(app_entry entry)
          :m_entry( entry ){
          assert( entry != Nullptr );    
        }

      __Implemented_Methods public:
        virtual void operator()(){
          m_entry();
        }

      private:
        app_entry m_entry;
    };

    ApplicationTaskBlock::ApplicationTaskBlock() 
      :Thread( "app task" )
      ,m_id(0)
      ,m_appObj( Nullptr )
      ,m_instance( Nullptr ){

    }

    ApplicationTaskBlock::ApplicationTaskBlock(app_entry entry, AppInstance *instance)
      :Thread( "app task")
      ,m_id(0)
      ,m_appObj( Nullptr )
      ,m_instance( instance ){

      if( entry != Nullptr ){
        initRunner( new ApplicationEntryRunner( entry ) );
      }

    }

    //each window
    //application
    ApplicationTaskBlock::~ApplicationTaskBlock(){
      if( m_instance != Nullptr ){
        m_instance->unload();
        delete m_instance;
      }

      Runner * _runner = getRunner();
      if( _runner != Nullptr ){
        delete _runner;
      }

    }

    void ApplicationTaskBlock::assignBlockId( uint32 id ){
      //assert( m_id != 0 );

      m_id = id;

      auto &&_entity = RunnableContextAccessor::getEntity( m_appObj );
      if( !_entity.isNull() ){
        _entity->m_int_runningId = id;
      }
  
    }

    void ApplicationTaskBlock::assignRunningApplication( MagnaApplication * app ){
      assert( app != Nullptr );

      m_appObj = app;
    }

    bool ApplicationTaskBlock::operator == ( const ApplicationTaskBlock& block ) {
      bool _ret_equ = false;
      if( m_id != 0 && block.m_id != 0 ){
        _ret_equ = (m_id == block.m_id);
      }
      return _ret_equ;
    }

    bool ApplicationTaskBlock::operator != ( const ApplicationTaskBlock& block ) {
      return !operator == ( block );
    }

  }//namespace Application
}//namespace Magna
