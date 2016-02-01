#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include "basegui_lib.h"

#include <map>

#include "basedef/Trigger.h"
using namespace Magna::Core;

#include "Button.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT ButtonGroup{
      friend class Button;
      typedef std::map< uint32 ,SharedPtr<Button> > Buttons;
      public:
        TRIGGER_DEF(OnceButtonToggled, const uint32& );
        TRIGGER_DEF(OnceButtonUntoggled, const uint32& );

      public:
        ButtonGroup();
        ~ButtonGroup();
      
      public:
        uint32 addButton( const SharedPtr<Button>& );
        void removeButton( const SharedPtr<Button>& );
        void removeButtonAt( uint32 );

        inline const Buttons & getButtons() const{
          return m_buttons;
        }

        inline void setExclusive( bool ex){
          m_isExclusive = ex;
        }

        inline bool isExclusive() const{
          return m_isExclusive;
        }
        inline uint32 getCurrentToggledIndex() const{
          return m_currentToggledButtonIndex;
        }

        void setButtonToggled( uint32 index );
        void setButtonUntoggled( uint32 index );

      private:
        Buttons m_buttons;
        uint32 m_currentToggledButtonIndex;
        //
        bool m_isExclusive;
        
    };

  }//namespace GUI
}//namespace Magna
#endif  /*  BUTTONGROUP_H  */