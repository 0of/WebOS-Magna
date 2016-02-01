
#include "Message.h"

#include <cassert>

namespace Magna{
  namespace Core{

    Message::Message( MessageType type )
      :m_messageType( type ){
      assert( static_cast<uint32>(type) <= MessageType_ContentValues );
    }

    Message::Message( const Message& message )
      :m_messageType( message.m_messageType ){

    }

    Message::~Message(){

    }

    Message& Message::operator = ( const Message& message ){
      m_messageType = message.m_messageType;
      return *this;
    }
  }
}//namespace Magna