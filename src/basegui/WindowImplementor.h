#ifndef WINDOWIMPLEMENTOR_H
#define WINDOWIMPLEMENTOR_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

#include "CommonEventArgs.h"
#include "WindowPropertySet.h"

namespace Magna{  
   namespace GUI{
     class WindowImplementor{
    __Constructor_Destructor  public:
       explicit WindowImplementor( WindowPropertySet& properties ) : m_properties( properties ){}
       virtual~WindowImplementor();
     public:
       virtual void windowClose( CloseEventArgs& eventArgs )
       {

       }
       virtual void windowHide( HideEventArgs& eventArgs ){

       }
       virtual void windowShow( ShowEventArgs& eventArgs ){
       }
     private:
      WindowPropertySet& m_properties;
     };
   }//GUI
}//Magna

#endif  /*  WINDOWIMPLEMENTOR_H  */