#include "AudioOutObject.h"

#include "AudioOutObject_p.h"

namespace Magna{
  namespace MultiMedia{

    AudioOutObject & AudioOutObject::getAudioOutObject(){
      static AudioOutObject o;
      return o;
    }

    AudioOutObject::AudioOutObject()
      :m_data( new PrivateData( *this ) ){

    }

    AudioOutObject::~AudioOutObject(){

    }

    void  AudioOutObject::setMuted ( bool mute ){
      if( !m_data.isNull() ){
        m_data->m_outputDevice->setMuted( mute );
      }
    }

    void  AudioOutObject::setVolume ( double newVolume ){
      if( !m_data.isNull() ){
        m_data->m_outputDevice->setVolume( newVolume );
      }
    }

    void AudioOutObject::setCurAt( uint32 at){
      if( !m_data.isNull() ){
        auto &_data = *m_data;
        if( at < _data.m_URLs.size() ){

          if( at != _data.m_cur ){
            _data.m_cur  = at;

            auto &_current_URL = _data.m_URLs.at( _data.m_cur );
#ifdef _MSC_VER
            QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( _current_URL.c_str() ), _current_URL.size() ); 
#else
            QString _URL = QString::fromStdWString( _current_URL );
#endif    
            _data.m_manipulatorObject->setCurrentSource( _URL );  
          }

        }
      }
    }

    void AudioOutObject::setCurrentSourceURL( const String&url){
      if( !m_data.isNull() ){    
        m_data->m_cur = m_data->m_URLs.size();
        m_data->m_URLs .push_back( url );

#ifdef _MSC_VER
        QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( url.c_str() ), url.size() ); 
#else
        QString _URL = QString::fromStdWString( url );
#endif    
        m_data->m_manipulatorObject->setCurrentSource( _URL );
      }
    }

    bool AudioOutObject::isMuted() const{
      bool _ret_muted = false;
      if( !m_data.isNull() ){
        _ret_muted = m_data->m_outputDevice->isMuted();
      }
      return _ret_muted;
    }

    void AudioOutObject::appendNextSourceURL( const String& url){
      if( !m_data.isNull() ){
        m_data->m_URLs .push_back( url );
      }
    }

    void AudioOutObject::play(){
      if( !m_data.isNull() ){
        auto &_data = *m_data;
        if( !_data.m_URLs.empty() ){

          if( _data.m_cur < _data.m_URLs.size() ){
                  
            auto &_current_URL = _data.m_URLs.at( _data.m_cur );
  #ifdef _MSC_VER
            QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( _current_URL.c_str() ), _current_URL.size() ); 
  #else
            QString _URL = QString::fromStdWString( _current_URL );
  #endif    
            _data.m_manipulatorObject->setCurrentSource( _URL );

            _data.m_manipulatorObject->play();
          }
        }
      }
    }

    void AudioOutObject::pause(){
      if( !m_data.isNull() ){
        auto &_data = *m_data;
        _data.m_manipulatorObject->pause();    
      }
    }

    void AudioOutObject::stop(){
      if( !m_data.isNull() ){
        auto &_data = *m_data;
        _data.m_manipulatorObject->stop();    
      }
    }

    void AudioOutObject::playPrevious(){
      if( !m_data.isNull() ){
        auto &_data = *m_data;
        if( !_data.m_URLs.empty() ){

          if( _data.m_cur > 0 ){
            --_data.m_cur;

            auto &_current_URL = _data.m_URLs.at( _data.m_cur );
#ifdef _MSC_VER
            QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( _current_URL.c_str() ), _current_URL.size() ); 
#else
            QString _URL = QString::fromStdWString( _current_URL );
#endif    
            _data.m_manipulatorObject->setCurrentSource( _URL );

            _data.m_manipulatorObject->play();
          }
        }
      }
    }

    void AudioOutObject::playNext(){

      if( !m_data.isNull() ){
        auto &_data = *m_data;
        if( !_data.m_URLs.empty() ){

          if( _data.m_cur < (_data.m_URLs.size() - 1) ){
            ++_data.m_cur;

            auto &_current_URL = _data.m_URLs.at( _data.m_cur );
#ifdef _MSC_VER
            QString _URL = QString::fromUtf16( reinterpret_cast<const ushort *>( _current_URL.c_str() ), _current_URL.size() ); 
#else
            QString _URL = QString::fromStdWString( _current_URL );
#endif    
            _data.m_manipulatorObject->setCurrentSource( _URL );

            _data.m_manipulatorObject->play();
          }
        }
      }

    }

  }//namespace MultiMedia
}//namespace Magna