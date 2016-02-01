#include "WebsPopWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      WebsPopWindow::WebsPopWindow()
        :PopOutWindow( WindowAttribute_NoWindowFrame )
        ,m_webFrameCtrl( new WebFrameController ){

          LinearLayout *layout = new LinearLayout;
          layout->addController( m_webFrameCtrl );

          setCenterLayout(layout);

          auto &_userRect = DesktopWindow::getUserRectRegion();
          uint32 _take_width = (_userRect.getWidth() >> 1);
          uint32 _take_height = (_userRect.getHeight() >> 1);

          auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
          auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
          auto &_size = _desktop_rect.getSize();
          //top 30px bottom 30px
          //left 20px right 20px
          IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
            , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

          m_wndRoot->_pos_set( _top_left );
          m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));

          m_webFrameCtrl->setSize(  IntegerSize( 100,200 ) );
      }

      WebsPopWindow::~WebsPopWindow(){

      }

    }
  }
}