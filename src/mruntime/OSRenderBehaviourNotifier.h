#ifndef OSRENDERBEHAVOURNOTIFIER_H
#define OSRENDERBEHAVOURNOTIFIER_H

#include "render/ManipulateEngine.h"
using namespace Magna::Render;

#include "OSBehaviourNotifier.h"

#include <string>

namespace Magna{
  namespace Runtime{
    
    class OSRenderBehaviourNotifier : public OSBehaviourNotifier{
      __Constructor_Destructor public:
        explicit OSRenderBehaviourNotifier( ManipulateEngine &engine );
        //explicit OSRenderBehaviourNotifier( const assic_char* element_id,const std::string& content );
        virtual ~OSRenderBehaviourNotifier();

      __Override_Methods public:
        virtual void notifyOS() ;

      __Data_Field private:
        ManipulateEngine &m_engine;
      //  const assic_char* m_element_id;
      //  const std::string m_content;
    };

  }//namespace Runtime
}//namespace Magna

#endif  /*  OSRENDERBEHAVOURNOTIFIER_H  */