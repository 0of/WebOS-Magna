#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "basegui_lib.h"

#include "Controller.h"

namespace Magna{
  namespace GUI{
    
    class BASEGUI_LIB_EXPORT ProgressBar : public Controller{
      __Trigger public:
        TRIGGER_DEF(OnceValueChanged, sint32 )

      __Constructor_Destructor public:
        ProgressBar();
        explicit ProgressBar( sint32 init_val );
        explicit ProgressBar( float percentage );
        virtual ~ProgressBar();

      __Checker public:
        bool  isTextVisible () const;

      __Setter public:
        void  setMaximum ( sint32 maximum );
        void  setMinimum ( sint32 minimum );
        void  setRange ( sint32 minimum, sint32 maximum );
        void  setValue ( sint32 value );
        void setPercentage( float per );
        void setTextVisible( bool visible );

      __Getter public:
        sint32 getValue() const;
        float getPercentage() const;        
        sint32  getMaximum () const;
        sint32  getMinimum () const;

      public:
        void  reset();
        
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  PROGRESSBAR_H  */