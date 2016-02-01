#ifndef GUICONSTANTS_H
#define GUICONSTANTS_H

namespace Magna{
  namespace GUI{
    
    struct GUIConstants{

      enum BorderStyle{
        BorderStyle_None = 0,
        BorderStyle_Dotted = 1,  
        BorderStyle_Dashed = 2,
        BorderStyle_Solid = 3,  
        BorderStyle_Double = 4 ,  
        BorderStyle_Groove = 5,
        BorderStyle_Ridge = 6,
        BorderStyle_Inset = 7,
        BorderStyle_Outset = 8  
      };


    };

  }//namespace GUI
}//namespace Magna

#endif  /*  GUICONSTANTS_H  */