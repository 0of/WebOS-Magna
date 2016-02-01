#ifndef TEXTLINEEDITOR_H
#define TEXTLINEEDITOR_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT TextLineEditor : public Controller{
      __Trigger public:
        TRIGGER_DEF(OnceTextChanged, const String&)
        TRIGGER_DEF(OnceCursorChanged, uint32 , uint32 )

      __Constructor_Destructor public:
        TextLineEditor();
        explicit TextLineEditor( const String& hintText );
        explicit TextLineEditor( const String& hintText, const String& text );
        virtual ~TextLineEditor();

      public:
        void setHintText( const String& hint );

        void setText( const String& text );

        void clearText();


    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TEXTLINEEDITOR_H  */