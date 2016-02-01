#ifndef APPLICATIONINTRODUCER_H
#define APPLICATIONINTRODUCER_H

#include "application_lib.h"

#include "OSGUIBehaviourExRequester.h"

namespace Magna{
  namespace Application{
    
    class APPLICATION_LIB_EXPORT ApplicationIntroducer{
      public:
        static ApplicationIntroducer & getApplicationIntroducer();

      private:
        ApplicationIntroducer()
          :m_requester( Nullptr ){

        }

        ~ApplicationIntroducer(){

        }

      public:
        void bindRequester( OSGUIBehaviourExRequester * r){
          m_requester = r;
        }

        void introduces( const String& a1, RunnableContext * a2 = Nullptr ){
          if( m_requester != Nullptr ){
            m_requester->requestStartNewApplication( a1, a2 );
          }      
        }

        void introducesWithDialog( const String& a1, RunnableContext * a2 = Nullptr ){
          if( m_requester != Nullptr ){
            m_requester->requestStartNewApplicationWithDialog( a1, a2 );
          }      
        }

      private:
        OSGUIBehaviourExRequester *m_requester;
    };

  }//namespace Application
}//namespace Magna

#endif  /*  APPLICATIONINTRODUCER_H  */