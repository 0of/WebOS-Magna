#ifndef AUDIOOUTOBJECT_H
#define AUDIOOUTOBJECT_H

#include "multimedia_lib.h"

#include "basedef/SharedPtr.h"
#include "basedef/Trigger.h"
#include "basedef/String.h"
using namespace Magna::Core;

namespace Magna{
  namespace MultiMedia{
    
    class MULTIMEDIA_LIB_EXPORT AudioOutObject{
      public:
        static AudioOutObject & getAudioOutObject();
      public:
        TRIGGER_DEF(OnceFinished)
        TRIGGER_DEF(OncePlaying)
        //includes pause & stop
        TRIGGER_DEF(OnceStopPlaying)

      public:
        AudioOutObject();
        ~AudioOutObject();

      private:
        explicit AudioOutObject( const AudioOutObject & );

      public:

        void  setMuted ( bool mute );
        void  setVolume ( double newVolume );

        void setCurrentSourceURL( const String&);

        bool isMuted() const;

        void appendNextSourceURL( const String& );
        void setCurAt( uint32 );

        void playPrevious();
        void playNext();

        void play();
        void pause();
        void stop();

        //void setLoopMode( bool );

      private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }//namespace MultiMedia
}//namespace Magna
#endif  /*  AUDIOOUTOBJECT_H  */
