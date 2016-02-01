#include "AbstractedNotifier.h"

#include <set>

namespace Magna{
  namespace Core{

    const uint32 AbstractedNotifier::shared_DefaultType = AbstractedNotifier::registerNotifierType(0);

    uint32 AbstractedNotifier::registerNotifierType( uint32 hint ){
      static std::set<uint32> _registered;
      
      uint32 _hint = hint;
      while( _registered.count( hint ) != 0 ){
        ++_hint;
      }

            _registered.emplace( _hint );

      return _hint;
    }

    AbstractedNotifier::AbstractedNotifier( uint32 notifierType)
      :Message( MessageType_Notifier )
      ,m_notifierType( notifierType ){

    }

    AbstractedNotifier::~AbstractedNotifier(){

    }  

  }
}//namespace Magna
