#ifndef NOTIFIERMESSAGE_H
#define NOTIFIERMESSAGE_H

namespace Magna{
  namespace Application{
    
    //a simple 
    template<typename NotifiedType, typename ContentType>
    class NotifierMessage{
      public:
        NotifierMessage()
          :m_instance(), m_content(){}
        explicit NotifierMessage( const NotifiedType& instance, const ContentType& content )
          :m_instance( instance ), m_content( content ){}
         NotifierMessage( const NotifierMessage<NotifiedType, ContentType>& message )
          :m_instance( message.m_instance ), m_content( message.m_content ){}
        ~NotifierMessage(){}

        NotifierMessage<NotifiedType, ContentType>& operator = ( const NotifierMessage<NotifiedType, ContentType>& message ){
          m_instance = message.m_instance;
          m_content = message.m_content;
          return *this;
        }

      public:
        NotifiedType m_instance;
        ContentType m_content;
    };
    

  }//namespace Application
}//namespace Magna
#endif  /*  NOTIFIERMESSAGE_H  */