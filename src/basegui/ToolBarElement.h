#ifndef TOOLBARELEMENT_H
#define TOOLBARELEMENT_H

#include "qt_glue_img/Image.h"
using namespace Magna::Glue;

namespace Magna{
  namespace GUI{
    
    class ToolBarElement{
      public:
        ToolBarElement();
        ToolBarElement( const ToolBarElement& element);
        ~ToolBarElement();

        ToolBarElement & operator = (const ToolBarElement& element);

      public:
        void setIcon( const Image& img );

        void setText( const String& text ){
          m_text = text;
        }

        void setIdentifier( const String& name ){
          m_name = name;
        }

        inline Image getIcon() const{
          return m_icon;
        }

        inline String getText() const{
          return m_text;
        }

        inline String getIdentifier() const { 
          return m_name; 
        }

      private:
        Image m_icon;
        String m_text;
        String m_name;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  TOOLBARELEMENT_H  */
