#include "WindowStatusBar.h"

#include "render/RadialGradient.h"
#include "render/LinearGradient.h"
using namespace Magna::Render;

#include "glue/FontMetrics.h"
using namespace Magna::Glue;

#include "DesktopEventDispatcher.h"
#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      WindowStatusBar::WindowStatusBar()
        :Controller()
        ,m_group()
        ,m_reservedButtons()
        ,m_runningWnds()
        ,m_widMapsButtonIndex()
        ,m_layout( new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical ) )
        ,m_toggledIndex( 0 )
        ,m_unitSize( DesktopStatusBar::shared_status_bar_width - 6 , DesktopStatusBar::shared_status_bar_width + 4 )
        ,m_buttonSharedFillBrush()
        ,m_pressedButtonSharedFillBrush(){
          
        //setScrollSize( IntegerSize( DesktopStatusBar::shared_status_bar_width - 6, 600 ) );
        Image _unit_bg = Image( DesktopWindow::getDesktopResDir() + L"wnd_box.png") ;
        _unit_bg.scale( m_unitSize, Image::ImageTransformationMode_Smooth );

        m_buttonSharedFillBrush.setTexture(_unit_bg);

        Image _unit_pressed_bg = Image( DesktopWindow::getDesktopResDir() + L"wnd_box_focus.png") ;
        _unit_pressed_bg.scale( m_unitSize, Image::ImageTransformationMode_Smooth );

        m_pressedButtonSharedFillBrush.setTexture( _unit_pressed_bg );

        m_group.OnceButtonToggled.connectAction( this, &WindowStatusBar::buttonToggledAction);
        m_group.OnceButtonUntoggled.connectAction( this, &WindowStatusBar::buttonUntoggledAction);

        m_layout->setLayoutOffset( IntegerDyadCoordinate( 0, 12 ) );
        m_group.setExclusive( !false );
        setLayout( m_layout );
        //setScrollBarPolicy(ScrollBarPolicy_AlwaysOff);
      }

      WindowStatusBar::~WindowStatusBar(){

      }

      void WindowStatusBar::openNewWindow( const SharedPtr<Window::WindowRoot>& wnd ){

        if( !wnd.isNull() ){
          uint32 _added_index = 0;
          if( !m_reservedButtons.empty() ){

            auto &_button = m_reservedButtons.front();

            Image _scaled_icon = wnd->m_properties.m_icon;
            IntegerSize _icon_size( m_unitSize.getWidth() - 6,  m_unitSize.getWidth() - 6);
            _scaled_icon.scale( _icon_size );
            _button->setIcon( _scaled_icon );
            
            _added_index = m_group.addButton( _button );    
            m_reservedButtons.pop();

            _button->setToggled( true );

            m_layout->addController( _button );
          }
          else{
            //auto &_text_size = FontMetrics::measureSize( wnd->m_properties.m_title, Font() );
            //if( _text_size.getWidth() > DesktopStatusBar::shared_status_bar_width ){

            //}

            SharedPtr<Button> _button = new Button( L"" );

            _button->setSize( m_unitSize );
            _button->setBrush( m_buttonSharedFillBrush );
            _button->setPressedBrush( m_pressedButtonSharedFillBrush );

            Image _scaled_icon = wnd->m_properties.m_icon;
            IntegerSize _icon_size( m_unitSize.getWidth() - 6,  m_unitSize.getWidth() - 6);
            _scaled_icon.scale( _icon_size );
            _button->setIcon( _scaled_icon );
            
            _button->setFontBrush( FillBrush( Color(255,255,255) ) );
            _button->setToggleable( true );

            _added_index = m_group.addButton( _button );

            _button->setToggled( true );

            m_layout->addController( _button );

          }

          if( _added_index != 0 ){
            m_widMapsButtonIndex.emplace( std::make_pair(wnd->m_int_runtimeId, _added_index) );
            m_runningWnds.emplace( std::make_pair( _added_index, wnd )  );

            m_toggledIndex = _added_index;
          }
          
        }

      }

      /*
      void WindowStatusBar::openNewWindow( uint32 id, const String& title ){

        if( id != 0 ){
          if( !m_reservedButtons.empty() ){

            auto &_button = m_reservedButtons.front();

            m_group.addButton( _button );    
            m_reservedButtons.pop();

            _button->setToggled( true );

            m_layout->addController( _button );
          }
          else{

            SharedPtr<Button> _button = new Button( title );
            _button->setToggleable( true );

            m_group.addButton( _button );
            
            _button->setToggled( true );

            m_layout->addController( _button );
          }

          m_runningWIds.push_back( id );
        }

      }
      */
      void WindowStatusBar::closeWindow( uint32 id ){
        if( id != 0 ){
          auto &_exist_wid_mapper = m_widMapsButtonIndex.find( id );
          
          //find the window from the running windows by id
          if( _exist_wid_mapper != m_widMapsButtonIndex.end() ){

            auto &_button_index = _exist_wid_mapper->second;

            auto &_found_wnd = m_runningWnds.find( _button_index );
            if( _found_wnd != m_runningWnds.end() ){

              auto &_buttons = m_group.getButtons();
              auto _found_button_info = _buttons.find( _button_index );
              if( _found_button_info != _buttons.end() ){

                m_reservedButtons.push( _found_button_info->second );

                m_layout->removeChildController( _found_button_info->second );
                m_group.removeButton( _found_button_info->second );

                update();
              } 

              m_runningWnds.erase( _found_wnd);
            }
    
            m_widMapsButtonIndex.erase( _exist_wid_mapper );
          }
        }
      }
    

      void WindowStatusBar::buttonToggledAction( const uint32& index ){
        auto _found = m_runningWnds.find( index );
        if( _found != m_runningWnds.end() ){
          auto &wnd = _found->second;
          if( !wnd.isNull() ){
            wnd->m_binding.setVisible( !false );
          }
        }                  
      }

      void WindowStatusBar::buttonUntoggledAction( const uint32& index){
        auto _found = m_runningWnds.find( index );
        if( _found != m_runningWnds.end() ){
          auto &wnd = _found->second;

          if( !wnd.isNull() ){
            wnd->m_binding.setFocus( false );
          }

          if( m_toggledIndex == index ){
            wnd->m_binding.setVisible( false );
            m_toggledIndex = 0;
          }      
        }
            
      }

      void WindowStatusBar::actWhenWindowFocusChanged( uint32 wid , bool isFocusIn ){
        if( wid != 0 ){
          auto &_exist_wid_mapper = m_widMapsButtonIndex.find( wid );

          //find the window from the running windows by id
          if( _exist_wid_mapper != m_widMapsButtonIndex.end() ){

            auto &_button_index = _exist_wid_mapper->second;

            auto &_found_wnd = m_runningWnds.find( _button_index );
            if( _found_wnd != m_runningWnds.end() ){

              auto &_buttons = m_group.getButtons();
              auto _found_button_info = _buttons.find( _button_index );
              if( _found_button_info != _buttons.end() ){
                SharedPtr<Button> _button = _found_button_info->second;
                _button->setToggled( isFocusIn );    


              }       
            }
          }
        }
      }

    }
  }
}