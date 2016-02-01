#ifndef MANIPULATOR_H
#define MANIPULATOR_H

#include "render_lib.h"

#include "basedef/Uncopyable.h"
using namespace Magna::Core;

namespace Magna{
  namespace Render{

    class RENDER_LIB_EXPORT Manipulator : Uncopyable{
      public:
        enum Type{
          Type_Script
        };
      protected:
        Manipulator( Type type ):m_type( type ){}
        virtual ~Manipulator() {} 

      public:
        Type getType() const{ return m_type; }

      private:
        Type m_type;
    };


  }//namespace Render
}//namespace Magna

#endif  /*  MANIPULATOR_H  */
