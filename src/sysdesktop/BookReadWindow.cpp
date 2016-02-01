#include "BookReadWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "application/WindowIntroducer.h"
using namespace Magna::Application;

#include "DesktopWindow.h"
#include "basegui/Label.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      BookReadWindow::BookReadWindow()
        :Window( )
        ,m_textViewCtrl( new TextViewController() ){

          setWindowTitle( L"Magna¼òÂªµÄÔÄ¶ÁÆ÷");
          setWindowIcon( Image( DesktopWindow::getDesktopResDir() + L"Book-icon.png" ) );
          m_textViewCtrl->setFont(Font( L"¿¬Ìå", 20 ) );

          LinearLayout *layout = new LinearLayout;
          layout->addController( m_textViewCtrl );  
          setCenterLayout(layout);

          
          uint32 _take_width = 700;
          uint32 _take_height = 560;

          auto &_desktop_rect = DesktopWindow::getDesktopRectRegion();
          auto &_desktop_top_left = _desktop_rect.getTopLeftCoord();
          auto &_size = _desktop_rect.getSize();
          //top 30px bottom 30px
          //left 20px right 20px
          IntegerDyadCoordinate _top_left ( _desktop_top_left.getX() + (_size.getWidth() >> 1 ) - ( _take_width >> 1 ) 
            , _desktop_top_left.getY() +  (_size.getHeight() >> 1 ) - ( _take_height >> 1 )  );

          m_wndRoot->_pos_set( _top_left );
          m_wndRoot->_size_set( IntegerSize( _take_width,_take_height ));

          //m_textViewCtrl->setScrollSize(  IntegerSize( _take_width ,_take_height ) );
          m_textViewCtrl->setSize(  IntegerSize( _take_width ,_take_height - 28 ) );

      }

      BookReadWindow::~BookReadWindow(){

      }


    }
  }
}
