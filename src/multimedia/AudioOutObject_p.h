#ifndef AUDIOOUTOBJECT_P_H
#define AUDIOOUTOBJECT_P_H

#include <QObject>
#include <Phonon/AudioOutput>
#include <Phonon/MediaObject>

#include <qfile.h>
using namespace Phonon;

#include "AudioOutObject.h"

namespace Magna{
  namespace MultiMedia{
    
    class AudioOutObject::PrivateData : public QObject{
      Q_OBJECT

    public:
      AudioOutput *m_outputDevice;
      MediaObject *m_manipulatorObject;

      std::vector<String> m_URLs;
      uint32 m_cur;

      AudioOutObject &m_object;

    public:
      PrivateData( AudioOutObject & obj)
        :m_outputDevice( Nullptr )
        ,m_manipulatorObject( Nullptr )
        ,m_URLs()
        ,m_cur(0)
        ,m_object( obj ){

          m_manipulatorObject = new MediaObject(this);
          m_outputDevice = new Phonon::AudioOutput(Phonon::VideoCategory, this);
        
          createPath(m_manipulatorObject, m_outputDevice);

          QObject::connect( m_manipulatorObject , SIGNAL(finished ()), this,  SLOT( processFinished() ), Qt::DirectConnection);
          QObject::connect( m_manipulatorObject,  SIGNAL(stateChanged ( Phonon::State, Phonon::State ) ), this,  SLOT( processStateChanged( Phonon::State, Phonon::State ) ), Qt::DirectConnection);

      } 

      ~PrivateData(){
      
      }

      private slots:
        void processFinished(){
          m_object.OnceFinished.triggers();

          m_object.playNext();
        }
        void processPlay(){
          m_object.OncePlaying.triggers();
        }
        void processStop(){
          m_object.OnceStopPlaying.triggers();
        }
        void processPause(){
          m_object.OnceStopPlaying.triggers();
        }

        void processStateChanged ( Phonon::State newstate, Phonon::State oldstate ){

        }
    };

  }//namespace MultiMedia
}//namespace Magna

#endif  /*  AUDIOOUTOBJECT_P_H  */
