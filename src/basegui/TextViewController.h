#ifndef TEXTVIEWCONTROLLER_H
#define TEXTVIEWCONTROLLER_H

#include "basegui_lib.h"

#include "Controller.h"
#include "ScrollableController.h"

#include <fstream>

namespace Magna{
  namespace GUI{
    //Perl Tools/Scripts/build-webkit --qt --debug --no-webkit2
    class BASEGUI_LIB_EXPORT TextViewController : public ScrollableController{
      public:
        TextViewController();
        explicit TextViewController( const String&);
        //when read finished, will close the file
        explicit TextViewController( std::wifstream& );
        virtual ~TextViewController();

      public:
        void setText( const String& );
        void loadFromFile( const String& );

      protected:
        virtual String toProtogenousInitString( const String& start = L"function(element){"
          , const String& end = L"}", const String& element = L"element") const ;
      
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TEXTVIEWCONTROLLER_H  */