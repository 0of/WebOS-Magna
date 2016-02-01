#include "FileInfoController.h"

#include "DesktopWindow.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      FileInfoController::FileInfoController( const Image& icon, const String& path, uint32 s, uint32 type )
        :Controller()
        ,m_fileEntry( new Button( L"" ) )
        ,m_nameLabel()
        ,m_path( path )
        ,m_seq( s )
        ,m_type( type ){

          auto _find = path.find_last_of( L'/');
          m_nameLabel = new Label( m_path.substr( _find + 1 )
            , TextRenderContants::TextAlignment_HCenter | TextRenderContants::TextAlignment_VCenter );
          auto _text = m_nameLabel->getText();

          m_fileEntry->setIcon(icon);
          m_fileEntry->setSize( IntegerSize( 84, 112 ) );

          LinearGradient *g = new LinearGradient( 0, 0, 0, 112 );
          g->setColorAt( Color( 255,255,255, 16), 0.0f );
          g->setColorAt( Color( 255,255,255, 255), 0.5f );
          g->setColorAt( Color( 255,255,255, 16), 1.0f );
          FillBrush _b( g );
          m_fileEntry->setPressedBrush( _b );
          m_nameLabel->setSize( IntegerSize( 84, 32 ) );
          ShadowAppearanceEffect *effect =new ShadowAppearanceEffect;
          effect->setBlurGranularity( 5 );
          effect->setShadowColor( Color( 255, 255,255) );

          Font _font;
          _font.setFontSize( 15 );
          m_nameLabel->setTextFillBrush( FillBrush( Color(255,255,255) ) );
          m_nameLabel->setTextEffect( effect );
          m_nameLabel->setFont(_font);

          LinearLayout *layout = new LinearLayout( LinearLayout::LinearLayoutOrientation_Vertical );
          layout->addController( m_fileEntry );
          layout->addController( m_nameLabel );

          layout->setSpacing( 0 );
          setLayout(layout);
          setSize( IntegerSize( 84 , 144 ) );

          m_fileEntry->OnceClicked.connectAction( this, &FileInfoController::processButtonClicked );
      }

      FileInfoController::~FileInfoController(){

      }

      void FileInfoController::processButtonClicked(){
      
        OnceAboutToEnter.triggers( m_path );
        OnceAboutToEnterByInfo.triggers( *this );
      }
    }
  }
}
