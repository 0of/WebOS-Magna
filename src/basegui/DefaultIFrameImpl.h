#ifndef DEFAULTFRAMEIMPL_H
#define DEFAULTFRAMEIMPL_H

#include "IFrame.h"

namespace Magna{
  namespace GUI{
    class DefaultIFrameImpl : public __Realizes IFrame{
      __Constructor_Destructor public:
        DefaultIFrameImpl();
        virtual ~DefaultIFrameImpl() {}

      __Override_Methods public:
        virtual uint32 getFrameHeight() const ;
        virtual void renderingFrame( const String& title
                                , const IntegerSize& textSize
                                , const uint32& frameWidth
                                , const Image& icon
                                , RenderingEventArgs& args ) ;

      __Data_Field private:
        FillBrush m_defaultFrameBrush;
        FillBrush m_textBrush;
        Font m_textFont;

    };
  }//namespace GUI
}//namespace Magna

#endif  /*  DEFAULTFRAMEIMPL_H  */