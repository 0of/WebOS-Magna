#ifndef PROGRESSBARIMPLEMENTOR_H
#define PROGRESSBARIMPLEMENTOR_H

#include "render/FillBrush.h"
using namespace Magna::Render;

#include "ControllerImplementor.h"

#include "ProgressBar.h"

namespace Magna{
  namespace GUI{
    
    class ProgressBarImplementor: public ControllerImplementor{
      __Constructor_Destructor public:
        explicit ProgressBarImplementor( ProgressBar &progressBar );
        explicit ProgressBarImplementor( ProgressBar &progressBar , sint32 int_val );
        virtual ~ProgressBarImplementor();

      __Override_Methods public:
        void rendering( RenderingEventArgs& eventArgs );

      public:
        void _remeasureText();
        void _setProgressValue( sint32 val );

      __Data_Field public:
        String m_text;
        sint32 m_max;
        sint32 m_min;
        sint32 m_value;

        uint32 m_textVisible;

        IntegerRectRegion m_textBoundingRect;
        IntegerRectRegion m_barBoundingRect;

        FillBrush m_barBrush;
        FillBrush m_baseBarBrush;
        Pen m_baseBorderPen;

        ProgressBar &m_progressBar;
    };

  }//namespace GUI
}//namespace Magna

#endif  /*  PROGRESSBARIMPLEMENTOR_H  */