#ifndef SCROLLEVENTARGS_H
#define SCROLLEVENTARGS_H

#include "basegui_lib.h"

#include "basedef/Size.h"
#include "basedef/AbstractedEventArgs.h"
using namespace Magna::Core;

#include "EventArgConstants.h"

namespace Magna{
  namespace GUI{
  
    class BASEGUI_LIB_EXPORT ScrollEventArgs : public AbstractedEventArgs{

      __Constructor_Destructor public:
        explicit ScrollEventArgs( sint32 oldScrollX, sint32 oldScrollY
          , sint32 scrollX, sint32 scrollY, const IntegerSize& scrollSize );
        ScrollEventArgs( const ScrollEventArgs& );
        virtual ~ScrollEventArgs();

      __Overloaded_Methods public:
        ScrollEventArgs & operator = ( const ScrollEventArgs& args );

        bool operator == ( const ScrollEventArgs& args );
        bool operator != ( const ScrollEventArgs& args );

      __Getter public:
        inline sint32 getNewScrollX() const{
          return m_newScrollX;
        }
        inline sint32 getNewScrollY() const{
          return m_newScrollY;
        }

        inline sint32 getOldScrollX() const{
          return m_oldScrollX;
        }

        inline sint32 getOldScrollY() const{
          return m_oldScrollY;
        }

        IntegerSize getScrollSize() const{
          return m_scrollSize;
        }

      __Data_Field private:
        sint32 m_oldScrollX;
        sint32 m_oldScrollY;
        sint32 m_newScrollX;
        sint32 m_newScrollY;
        IntegerSize m_scrollSize;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  SCROLLEVENTARGS_H  */

