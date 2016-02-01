#ifndef RELATIVELAYOUT_H
#define RELATIVELAYOUT_H

#include "basegui_lib.h"

#include "Layout.h"

namespace Magna{
  namespace GUI{

    class BASEGUI_LIB_EXPORT RelativeLayout : public Layout{
      __Constants public:
        enum RelativeHorizontalPostition{
          Left,HCenter,Right
        };
        enum RelativeVerticalPostition{
          Top,VCenter,Bottom
        };

      __Constructor_Destructor public:
        RelativeLayout();
        virtual ~RelativeLayout();

      public:
        void addController( const SharedPtr<Controller>&, RelativeHorizontalPostition , RelativeVerticalPostition);
        void addController( const SharedPtr<Controller>&, float hPercent, float vPercent);

      __Override_Methods protected:
        //measure takes deploy 's job
        virtual void measure() ;

      __Data_Field private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
    };

  }
}

#endif  /*  RELATIVELAYOUT_H  */