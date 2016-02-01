#ifndef WEBFRAMECONTROLLER_H
#define WEBFRAMECONTROLLER_H

#include "basegui_lib.h"

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT WebFrameController : public Controller{
      public:
        WebFrameController();
        explicit WebFrameController( const String& );
        virtual ~WebFrameController();

      public:
        void setAccessURL( const String& );

      protected:
        virtual String toProtogenousInitString( const String& start = L"function(element){"
          , const String& end = L"}", const String& element = L"element") const ;

      private:
        String m_currentURL;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  WEBFRAMECONTROLLER_H  */