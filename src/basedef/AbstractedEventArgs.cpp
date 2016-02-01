#include "AbstractedEventArgs.h"

#include <cstring>

namespace Magna{
  namespace Core{
    AbstractedEventArgs::AbstractedEventArgs( uint16 eventType, bool isTransmissible )
      :Message( Message::MessageType_EventArgs )
      ,m_acceptance( true )
      ,m_isTransmissible( isTransmissible )
      ,m_type( eventType ){

    }

    AbstractedEventArgs::~ AbstractedEventArgs() {

    }

    AbstractedEventArgs::AbstractedEventArgs( const AbstractedEventArgs& absArgs )
      :Message( absArgs )
            ,m_acceptance( absArgs.m_acceptance )
      ,m_isTransmissible( absArgs.m_isTransmissible )
      ,m_type( absArgs.m_type ){

    }

    AbstractedEventArgs & AbstractedEventArgs::operator = ( const AbstractedEventArgs& absArgs ){
      Message::operator = ( absArgs );
      m_acceptance = absArgs.m_acceptance;
      m_isTransmissible =  absArgs.m_isTransmissible;
      m_type = absArgs.m_type;
      return *this;
    }




  }
}
