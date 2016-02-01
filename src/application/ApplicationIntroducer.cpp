#include "ApplicationIntroducer.h"

namespace Magna{
  namespace Application{
    
    ApplicationIntroducer & ApplicationIntroducer::getApplicationIntroducer(){
      static ApplicationIntroducer _i;
      return _i;
    }

  }//namespace Application
}//namespace Magna