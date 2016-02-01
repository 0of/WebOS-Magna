#include "ToolBarElement.h"

namespace Magna{
  namespace GUI{
    
    ToolBarElement::ToolBarElement()
      :m_icon()
      ,m_text()
      ,m_name(){

    }

    ToolBarElement::ToolBarElement ( const ToolBarElement& element )
      :m_icon( element.m_icon )
      ,m_text( element.m_text )
      ,m_name( element.m_name ){

    }

    ToolBarElement::~ToolBarElement(){

    }

    ToolBarElement & ToolBarElement::operator = (const ToolBarElement& element){
      m_icon = element.m_icon;
      m_name = element.m_name;
      m_text = element.m_text;
      return *this;
    }

    void ToolBarElement::setIcon( const Image& img ){
      m_icon = img;
      m_icon.scale( 64, 64 );
    }

  }//namespace GUI
}//namespace Magna


  

