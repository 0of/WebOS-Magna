#include "FileSystemButton.h"

#include "render/AppearanceEffect.h"
#include "render/ShadowAppearanceEffect.h"
using namespace Magna::Render;

#include "application/Application.h"
using namespace Magna::Application;

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      FileSystemButton::FileSysButtonIconManager::FileSysButtonIconManager()
        :m_diskIcon( DesktopWindow::getDesktopResDir() + L"Disk-HD-icon.png")
        ,m_cdromIcon( DesktopWindow::getDesktopResDir() + L"Disk-HD-CDRom-icon.png" ){

        m_diskIcon.scale( 86, 86 );
        m_cdromIcon.scale( 86, 86 );
      }

      FileSystemButton::FileSysButtonIconManager::~FileSysButtonIconManager(){

      }

      FileSystemButton::FileSysButtonIconManager FileSystemButton::shared_file_sys_icon_manager 
        = FileSystemButton::FileSysButtonIconManager();


      FileSystemButton::FileSystemButton( const String& dir, FileSystemInfo::FileSystemType type
        , const String& label, float usage, const String& info)
        :Controller()
        ,m_fileSysDir( dir )
        ,m_fileSystemNameLabel( new Label( label ) )
        ,m_dishButton( new Button( L"" ) )
        ,m_usageBar( new ProgressBar( usage ) )
        ,m_fileUsageInfoLabel( new Label ( info ) ){

        //m_fileSystemNameLabel->setLayoutAttribute()
        setSize( IntegerSize( 86, 223 ) );

        FillBrush _text_brush( Color( 255,255,255) );
        Font _text_font;
        _text_font.setFontSize( 9 );

        Font _title_font;
        _title_font.setFontSize ( 11 );
        _title_font.setFontWeight( Font::FontWeight_Bold );
        ShadowAppearanceEffect *effect 
          = new ShadowAppearanceEffect( 5, Color( 255,255,255) , IntegerDyadCoordinate() );

        m_fileSystemNameLabel->setSize( IntegerSize( 86, 40 ) );
        m_fileSystemNameLabel->setTextFillBrush(_text_brush);
        m_fileSystemNameLabel->setFont( _title_font );
        m_fileSystemNameLabel->setTextEffect( effect );

        m_dishButton->setSize(  IntegerSize( 86, 108 ) );
        m_usageBar->setSize( IntegerSize( 84, 20 ) );
      

        m_fileUsageInfoLabel->setSize( IntegerSize( 86, 40 ) );
        m_fileUsageInfoLabel->setTextFillBrush(_text_brush);
        m_fileUsageInfoLabel->setFont( _text_font );


        if( type == FileSystemInfo::FileSystemType_LocalDisk ){
          m_dishButton->setIcon( shared_file_sys_icon_manager.m_diskIcon );
        }
        else if( type == FileSystemInfo::FileSystemType_CDRom ){
          m_dishButton->setIcon( shared_file_sys_icon_manager.m_cdromIcon );
        }

        //connections
        m_dishButton->OnceClicked.connectAction( this, &FileSystemButton::accessFileSystem);

        LinearLayout *_layout = new LinearLayout(LinearLayout::LinearLayoutOrientation_Vertical );
        _layout->setSpacing( 5 );

        _layout->addController( m_fileSystemNameLabel );
        _layout->addController( m_dishButton );
        _layout->addController( m_usageBar );
        _layout->addController( m_fileUsageInfoLabel );

        setLayout( _layout );
      }

      void FileSystemButton::accessFileSystem(){      
        MagnaApplication::introducesApplicationWithDialog( m_fileSysDir );        
      }

      FileSystemButton::~FileSystemButton(){

      }

      void FileSystemButton::updateUsageBar( float per ){
        if( !m_usageBar.isNull() ){
          m_usageBar->setPercentage( per );
        }
      }

      void FileSystemButton::updateFileUsageInfo( const String& info ){
        if( !m_fileUsageInfoLabel.isNull() ){
          m_fileUsageInfoLabel->setText( info );
        }
      }
    }
  }
}//namespace Magna