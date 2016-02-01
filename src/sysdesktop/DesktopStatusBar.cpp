#include "DesktopStatusBar.h"

#include "application/WindowIntroducer.h"
using namespace Magna::Application;

#include "DesktopWindow.h"
#include "DesktopApplication.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      uint32 DesktopStatusBar::shared_status_bar_width = 64;

      DesktopStatusBar::DesktopStatusBar( uint32 init_height )
        :Controller()
        ,m_winStatusBar( new WindowStatusBar )
        ,m_sysStatusColumn( new Controller )
        ,m_powerStatusButton( new Button(L"") )
        ,m_networkConnectionStatusButton( new Button( L"" ) )
        ,m_volumeStatusButton( new Button( L"" ) )
        ,m_batteryDetailsWnd( new BatteryDetailsWindow ){

        //takes 2/3 the height
        uint32 _bar_height = ((init_height >> 3 ) * 7);

        //calculate the pos
        uint32 _pos_y =  (init_height >> 3 ) - 4 ;

        if( !m_root.isNull() ){
          auto &_desktop_size = DesktopWindow::getDesktopRectRegion();
          m_root->_pos_set( IntegerDyadCoordinate( _desktop_size.getWidth() - 64, _pos_y ) );
          m_root->_size_set( IntegerSize( 64, _bar_height ) );

          Image _background_img(L"res/sysdesktop/status_bar_bg.png");
          _background_img.scale( 64, _bar_height, Image::ImageTransformationMode_Smooth );

          m_root->_brush_init( FillBrush( _background_img ) );
        }

        m_winStatusBar->setSize( IntegerSize( 64, _bar_height - 80 ) );
        m_sysStatusColumn->setSize( IntegerSize( 64, 70 ) );

        {
          //init system status column
          TableLayout *_column_layout = new TableLayout;        
          _column_layout->setHorizontalSpacing( 2 );
          _column_layout->setVerticalSpacing( 8 );
          _column_layout->setLayoutOffset( IntegerDyadCoordinate(2, 2) );

          //button sequence init
          SharedPtr<Button> _init_list[] = { 
            m_powerStatusButton,
            m_networkConnectionStatusButton,
            m_volumeStatusButton
          };

          Image _img_list[] = {
            Image (  m_batteryDetailsWnd->getCurrentStatusIcon() )
            ,Image ( DesktopWindow::getDesktopResDir() + L"disconn-network-icon.png" )
            ,Image (  DesktopWindow::getDesktopResDir() + L"medium_volume.png" )
          };
            
          const uint32& _list_len = sizeof( _init_list ) / sizeof( SharedPtr<Button> );

          for( auto _i = 0; _i != _list_len; ++_i ){
            auto &_each = _init_list[_i];

            _each->setSize( IntegerSize( 24, 24 ) );

            auto &_each_icon = _img_list[_i];
            _each_icon.scale( 24, 24, Image::ImageTransformationMode_Smooth );

            _each->setIcon( _each_icon );

            _column_layout->addController( _each, _i % 2 ,(_i >> 1) );
          }
          
          m_sysStatusColumn->setLayout( _column_layout );
        }

        //connections
        m_powerStatusButton->OnceClicked.connectAction( this, &DesktopStatusBar::showBatteryDetailsWindow);
  
        LinearLayout *layout = new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical )  ;
        layout->addController( m_winStatusBar );
        layout->addController( m_sysStatusColumn );

        layout->setLayoutOffset( 2, 2 );

        setLayout( layout );
      }

      DesktopStatusBar::~DesktopStatusBar(){

      }

      void DesktopStatusBar::showBatteryDetailsWindow(){
        WindowIntroducer::introduceWindow(*DesktopApplication::pInstance, m_batteryDetailsWnd);    
      }

    }
  }
}