#include "CategoryBar.h"

#include "basegui/Controller_p.h"
#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{
      
      CategoryBar::CategoryBar( uint32 _init_height )
        :Controller()
        ,m_group()
        ,m_fileSystemButton( new Button(L"") )
        ,m_frequencyUseAppsButton( new Button(L"")  )
        ,m_newsButton( new Button(L"")  )
        ,m_documentsButton ( new Button(L"")  )
        ,m_readingsButton ( new Button(L"")  )
        ,m_musicButton ( new Button(L"")  )
        ,m_filmVideoButton ( new Button(L"")  )
        ,m_gamesButton ( new Button(L"")  )
        ,m_linearLayout( new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical ) )
        ,m_indexMapsPopOutWnd()
        ,m_fileSysPopOutWindow( new FileSystemPopWindow() )
        ,m_videoPopOutWindow( new VideoPopWindow() )
        ,m_frePopWindow( new FrequentUsedAppPopWindow )
        ,m_bookPopOutWindow( new BookPopWindow )
        ,m_websPopOutWindow( new WebsPopWindow )
        ,m_musicPopOutWindow( new MusicPopWindow ){
    
          uint32 _avg_height = 0;
          uint32 _avg_width = shared_default_width;
          uint32 _height = 0;

          //margin top 6
          //margin bottom 6
          //original height
          /*
          uint32 _orig_height = (static_cast<uint32>(shared_default_width * 1.5) << 3) + 70;

          if( _init_height > _orig_height ){
            _avg_height = shared_default_width * 1.5;

            _height = (_avg_height << 3) + 86;                
          }
          else{
            //takes 7/8
            _height = (_init_height >> 3) * 7;
            
            _avg_height = ((_height - 70) >> 3) ;
            _avg_width = ((_height - 70) >> 3) / 1.5f;
          }          
          */

          uint32 _orig_height = (static_cast<uint32>(shared_default_width * 1.5) * 6 ) + 50;

          if( _init_height > _orig_height ){
            _avg_height = shared_default_width * 1.5;

            _height = (_avg_height * 6 ) + 68;                
          }
          else{
            //takes 7/8
            _height = (_init_height / 6 ) * 5 ;

            _avg_height = ((_height - 50) / 6) ;
            _avg_width = ((_height - 50) / 6) / 1.5f;
          }    

          m_root->_size_set(  IntegerSize( _avg_width + 16, _height ) );
          //show vertical center
          auto _y_center = (_init_height >> 1) - ( (_height >> 1) );
          m_root->_y_set( _y_center );


          {
            //buttons properties init
            SharedPtr<Button> _init_list[] = { m_fileSystemButton
              , m_frequencyUseAppsButton
            //  , m_newsButton
              //, m_documentsButton
              , m_readingsButton 
              ,m_musicButton
              ,m_filmVideoButton
              ,m_gamesButton
            };

            const String&_base_dir = DesktopWindow::getDesktopResDir();

            Image _img_list[] = {
              Image ( _base_dir + L"res_file_icon.png" )
              ,Image (  L"res/sysdesktop/res_fav_icon.png" )
              ,Image (  L"/res/sysdesktop/res_read_icon.png" )
              ,Image (  L"/res/sysdesktop/res_music_icon.png" )
              ,Image (  L"/res/sysdesktop/res_video_icon.png" )
              ,Image (  L"/res/sysdesktop/res_gam_icon.png" )
            };

            SharedPtr<PopOutWindow> _wnd_list[] = { m_fileSysPopOutWindow
              , m_frePopWindow
              //, m_websPopOutWindow          
              //, new PopOutWindow 
              , m_bookPopOutWindow
              ,m_musicPopOutWindow
              ,m_videoPopOutWindow
              ,new PopOutWindow
            };

            const uint32& _list_len = sizeof( _init_list ) / sizeof( SharedPtr<Button> );

            for( auto _i = 0; _i != _list_len; ++_i ){
              auto &_each = _init_list[_i];

              _each->setSize( IntegerSize( _avg_width, _avg_height  ) );

              auto &_each_icon = _img_list[_i];
              _each_icon.scale( _avg_width, _avg_height, Image::ImageTransformationMode_Smooth );

              _each->setIcon( _each_icon );
              _each->setToggleable( !false );
              _each->setPressedBrush( FillBrush() );

              auto _index = m_group.addButton( _each );
              m_linearLayout->addController( _each );

              m_indexMapsPopOutWnd.emplace( std::make_pair(  _index, _wnd_list[_i] ) );
            }
          }
        
          //Image _hover_img( DesktopWindow::getDesktopResDir() + L"/res_doc_icon_hover.png" );
          //_hover_img.scale( _avg_width, _avg_height, Image::ImageTransformationMode_Smooth );
          //m_documentsButton->setPressedIcon(_hover_img );

          //Image _file_icon( DesktopWindow::getDesktopResDir() + L"/res_file_icon_toggled.png" );
          //_file_icon.scale( _avg_width, _avg_height, Image::ImageTransformationMode_Smooth );
          //m_fileSystemButton->setPressedIcon( _file_icon );

          m_group.OnceButtonToggled.connectAction( this, &CategoryBar::toggleCategroyPanel);
          m_group.OnceButtonUntoggled.connectAction( this, &CategoryBar::untoggleCategoryPanel);

          {
            //init properties 

            m_group.setExclusive( true );

            Image _background_img(L"/res/sysdesktop/cat_bar_bg.png");

            _background_img.scale( shared_default_width + 16, _height , Image::ImageTransformationMode_Smooth );
            //setBrush( FillBrush(_background_img) );
            m_root->_brush_init( FillBrush( _background_img ) );
            //FillBrush _backgroundBrush( Color( 128, 128, 128, 128 ) );
            //setBrush( _backgroundBrush );

            m_linearLayout->setLayoutOffset( 16, 8 );
            setLayout( m_linearLayout );
          }
        
        


          //window
          //m_fileSysPopOutWindow = new FileSystemPopWindow;



          //connections
          //m_fileSystemButton->OnceToggled.connectAction( this, &CategoryBar::toggleFileSystemCategroyPanel );        
      }

      CategoryBar::~CategoryBar(){

      }

      void CategoryBar::toggleCategroyPanel(  const uint32& index){
        auto _found = m_indexMapsPopOutWnd.find( index);
        if( _found != m_indexMapsPopOutWnd.end() ){
          auto &_pop_out_wnd = _found->second;
          if( !_pop_out_wnd.isNull() ){
            _pop_out_wnd->popOut();
          }
        }
      }

      void CategoryBar::untoggleCategoryPanel( const uint32 & index){
        auto _found = m_indexMapsPopOutWnd.find( index);
        if( _found != m_indexMapsPopOutWnd.end() ){
          auto &_pop_out_wnd = _found->second;
          if( !_pop_out_wnd.isNull() ){
            _pop_out_wnd->popIn();
          }
        }
      }
      
    }//namespace Desktop
  }//namespace SystemComponent
}//namespace Magna