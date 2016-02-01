#ifdef _MSC_VER
#pragma warning(disable:4251)
#endif

#ifndef SCRIPTMANIPULATOR_H
#define SCRIPTMANIPULATOR_H

#include "render_lib.h"

#include "basedef/String.h"
using namespace Magna::Core;

#include "Manipulator.h"

#include <sstream>

namespace Magna{
  namespace Render{

    class RENDER_LIB_EXPORT ScriptManipulator : public Manipulator{
      public:
        ScriptManipulator();
        virtual ~ScriptManipulator();

      public:
        inline OutStringStream & getOutter(){ return m_outter; }

      private:
        OutStringStream m_outter;
    };

  }//namespace Render
}//namespace Magna

#endif  /*  SCRIPTMANIPULATOR_H  */
