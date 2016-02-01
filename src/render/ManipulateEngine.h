#pragma once

#ifdef _MSC_VER
#pragma warning(disable:4800)
#endif

#ifndef MANIPULATEENGINE_H
#define MANIPULATEENGINE_H

#include "render_lib.h"

#include <vector>

#include "basedef/SpinMutex.h"
using namespace Magna::Core;

#include "ScriptManipulator.h"

namespace Magna{
  namespace Render{

    class RENDER_LIB_EXPORT ManipulateEngine{
      public:
        ManipulateEngine();
        ~ManipulateEngine();

      public:
        ScriptManipulator & getDefaultScriptManipulator();
        void makeReservation();
        void cancelReservation();

        std::vector<ScriptManipulator *> &getReservedScriptManipulators(){
          return m_reservedScriptManipulators;
        }

        void lockReserved(){ m_resMutex.acquires(); }
        void unlockReserved() { m_resMutex.releases(); }

        inline bool isOccupied() const{ return m_occupied.read(); }

        void occupy();
        void deoccupy();

      private:
        std::vector<ScriptManipulator *> m_availScriptManipulators;
        std::vector<ScriptManipulator *> m_reservedScriptManipulators;

        SpinMutex m_mutex;
        SpinMutex m_resMutex;
        //
        AtomicInt m_occupied;
    };

  }//namespace Render
}//namespace Magna

#endif  /*  MANIPULATEENGINE_H  */
