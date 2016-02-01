#include "MusicPlayWindow.h"

#include "basegui/Window_p.h"
#include "basegui/LinearLayout.h"
using namespace Magna::GUI;

#include "application/ApplicationAccessor.h"
#include "application/ApplicationEventHandler.h"
using namespace Magna::Application;

#include "DesktopWindow.h"
#include "DesktopApplication.h"

namespace Magna{
  namespace SystemComponent{
    namespace Desktop{

      MusicEffectController::MusicEffectController()
        :Controller(){

      }

      MusicEffectController::~MusicEffectController(){

      }

      void MusicEffectController::startEffect(){

        if( !m_root.isNull() && m_root->m_int_runtimeId != 0 ){
          auto &_entity = ApplicationAccessor::accessApplication( DesktopApplication::pInstance  );
          if( !_entity.isNull() ){

            String _effect_script = L"Magna_Canvas_snow_effect.resetCanvas(";
            _effect_script.append( m_elementId )
              .append( L");Magna_Canvas_snow_effect.start();");

            _entity->m_eventHandler.requestScriptEval( _effect_script );
          }
        }
      }

      void MusicEffectController::stopEffect(){
        if( !m_root.isNull() && m_root->m_int_runtimeId != 0 ){
          auto &_entity = ApplicationAccessor::accessApplication( DesktopApplication::pInstance  );
          if( !_entity.isNull() ){

            String _effect_script = L"Magna_Canvas_snow_effect.stop();";

            _entity->m_eventHandler.requestScriptEval( _effect_script );
          }
        }
      }

      MusicPlayWindow::MusicPlayWindow()
        :Window()
        ,m_playerCtrl()
        ,m_effectController( new MusicEffectController )
        ,m_isPlaying( false ){

          uint32 _take_width = 500;
          uint32 _take_height = 400;

          setPos( IntegerDyadCoordinate(100, 100 ) );

          m_playerCtrl = new MusicPlayerContrController( _take_width );
          m_playerCtrl->setPos( IntegerDyadCoordinate( 0, _take_height - 160 ) );

          m_effectController->setSize( IntegerSize( _take_width, _take_height ) );

          AbsoluteLayout *layout = new AbsoluteLayout ;
          layout->addController(m_effectController);
          layout->addController( m_playerCtrl );

          setCenterLayout(layout);
          setSize( IntegerSize( _take_width, _take_height ) );
          setWindowTitle( L"MagnaÒôÀÖ²¥·ÅÆ÷");
          setWindowIcon( Image( DesktopWindow::getDesktopResDir() + L"audioplayer/Music-icon.png") );
          setBackgroundFillBrush( FillBrush( Image( DesktopWindow::getDesktopResDir() + L"audioplayer/bg.jpg") ) );

          m_playerCtrl->m_startPauseButton->OnceClicked.connectAction( this, &MusicPlayWindow::processPlayButton );
          m_playerCtrl->m_stopButton->OnceClicked.connectAction( this, &MusicPlayWindow::processStopButton );
          m_playerCtrl->m_playPreButton->OnceClicked.connectAction( this, &MusicPlayWindow::processPlayPre );
          m_playerCtrl->m_playNextButton->OnceClicked.connectAction( this, &MusicPlayWindow::processPlayNext );
      }

      MusicPlayWindow:: ~MusicPlayWindow(){

      }

      void MusicPlayWindow::setPlayQueue( const std::vector<String>& paths){
        AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
        for( auto _iter = paths.begin(); _iter != paths.end(); ++_iter ){
          _obj.appendNextSourceURL( *_iter );
        }
      }

      void MusicPlayWindow::setAboutToPlayAt( const uint32 &at){
        AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
        _obj.setCurAt( at );
      }

      void MusicPlayWindow::processPlayButton(){
        if( m_isPlaying == false ){
          AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
          _obj.play();

          m_effectController->startEffect();
          m_isPlaying = !false;
        }
        else{
          AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
          _obj.pause();

          m_effectController->stopEffect();
          m_isPlaying = false;
        }
      }

      void MusicPlayWindow::processStopButton(){
        if( m_isPlaying != false ){
          AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
          _obj.stop();
          m_effectController->stopEffect();

          m_isPlaying = false;
        }
      }

      void MusicPlayWindow::processPlayNext(){
        AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
        _obj.playNext();
      }

      void MusicPlayWindow::processPlayPre(){
        AudioOutObject &_obj = AudioOutObject::getAudioOutObject();
        _obj.playPrevious();
      }

    }
  }
}