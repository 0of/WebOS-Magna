#ifndef LAYOUTATTRIBUTE_H
#define LAYOUTATTRIBUTE_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"

namespace Magna{
  namespace GUI{
    //update

    class BASEGUI_LIB_EXPORT LayoutAttribute{
      __Constants public:
        enum LayoutHint{
          LayoutHint_Specific,  
          LayoutHint_HorizontalExpand,
          LayoutHint_VerticalExpand,
          LayoutHint_BothExpand
        };

        enum LayoutHorizontalAlignment{
          HAlignment_Left,
          HAlignment_Center,
          HAlignment_Right,
        };

        enum LayoutVerticalAlignment{
          VAlignment_Top,
          VAlignment_Center,
          VAlignment_Bottom,
        };

        typedef uint32 LayoutAlignment;

      __Constructor_Destructor public:
        LayoutAttribute() : m_hint( LayoutHint_Specific )
          ,m_alignment( HAlignment_Center |  VAlignment_Center ){}
        ~LayoutAttribute(){}

      __Overloaded_Methods public:
        bool operator == ( const LayoutAttribute& att ){
          return m_hint == att.m_hint;
        }
        bool operator != ( const LayoutAttribute& att ){
          return m_hint != att.m_hint;
        }

      __Data_Field public:
        LayoutHint m_hint ;
        LayoutAlignment m_alignment;

    };
  }//namespace GUI
}//namespace Magna

#endif  /*  LAYOUTATTRIBUTE_H  */