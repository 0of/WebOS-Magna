#include "ScrollEventArgs.h"

#include <cstring>

namespace Magna{
  namespace GUI{
    
    ScrollEventArgs::ScrollEventArgs( sint32 oldScrollX, sint32 oldScrollY
      , sint32 scrollX, sint32 scrollY, const IntegerSize& scrollSize )
      :AbstractedEventArgs( GUIEventConstants::GUIEvent_Scrolled )
      ,m_oldScrollX( oldScrollX )
      ,m_oldScrollY( oldScrollY )
      ,m_newScrollX( scrollX )
      ,m_newScrollY( scrollY )
      ,m_scrollSize( scrollSize ){

    }

    ScrollEventArgs::ScrollEventArgs( const ScrollEventArgs& e)
      :AbstractedEventArgs( e )
      ,m_oldScrollX( e.m_oldScrollX )
      ,m_oldScrollY( e.m_oldScrollY )
      ,m_newScrollX( e.m_newScrollX )
      ,m_newScrollY( e.m_newScrollY )
      ,m_scrollSize( e.m_scrollSize ){

    }

    ScrollEventArgs::~ScrollEventArgs(){

    }

    ScrollEventArgs & ScrollEventArgs::operator = ( const ScrollEventArgs& args ){
      ::memcpy( this, &args, sizeof(ScrollEventArgs) ) ;
      return *this;
    }

    bool ScrollEventArgs::operator == ( const ScrollEventArgs& args ){
      return ::memcmp(this, &args, sizeof( ScrollEventArgs ) ) == 0;    
    }

    bool ScrollEventArgs::operator != ( const ScrollEventArgs& args ){
      return ::memcmp(this, &args, sizeof( ScrollEventArgs ) ) != 0;    
    }

  }//namespace GUI
}//namespace Magna