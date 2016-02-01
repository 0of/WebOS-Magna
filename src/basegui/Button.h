#ifndef BUTTON_H
#define BUTTON_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT Button : public Controller{
      friend class ButtonGroup;

      __Trigger public:
        TRIGGER_DEF( OnceClicked )
        TRIGGER_DEF( OncePressed )
        TRIGGER_DEF( OnceReleased )
        TRIGGER_DEF( OnceChecked, bool )
        TRIGGER_DEF( OnceToggled, bool )

      __Constructor_Destructor public:
        Button();
        explicit Button( const String& text );
        explicit Button( const Image&  );
        virtual ~Button();

      __Checker public:
        bool isPressedDown() const;

        bool isCheckable() const;
        bool isToggleable() const;

        bool isChecked() const;
        bool isToggled() const;

      __Setter public:
        //short-cut

        void setCheckable( bool );
        void setToggleable( bool );

        void setChecked( bool );
        void setToggled( bool );
        void setText( const String& );

        void setFontBrush( const FillBrush& );
        void setPressedBrush( const FillBrush& );
        void setHoverBrush( const FillBrush& );

        //will scale to the size of button
        void setIcon( const Image& );
        void setHoverIcon( const Image& );
        void setPressedIcon( const Image& );

        void setData( uint32 );

        uint32 getData();

      __Getter public:
        String getText() const;
            
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  BUTTON_H  */