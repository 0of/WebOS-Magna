#ifndef TABLELAYOUT_H
#define TABLELAYOUT_H

#include "basegui_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "Layout.h"

namespace Magna{
  namespace GUI{
      
    class BASEGUI_LIB_EXPORT TableLayout  : public __Generalizes Layout{
      __Constants public:
        enum AutoDeployBreakPolicy{
          AutoDeployBreakPolicy_NoBreak,
          AutoDeployBreakPolicy_HorizontalBreak,
          AutoDeployBreakPolicy_VerticalBreak
        };

      __Constructor_Destructor public:
        TableLayout();
        virtual ~TableLayout();

      __Override_Methods protected:
        virtual void measure() ;
        virtual void deploy() ;

      public:
        void addController( const SharedPtr<Controller>& controller, uint16 rowAt, uint16 colAt );
        void addController( const SharedPtr<Controller>& controller, uint16 rowAt, uint16 colAt, uint16 rowSpan, uint16 colSpan );

        void addAutoDeployController( const SharedPtr<Controller>& controller );
        void addAutoDeployControllers( const std::vector<SharedPtr<Controller> >& controllers, AutoDeployBreakPolicy policy = AutoDeployBreakPolicy_HorizontalBreak );

      __Setter public:
        void setHorizontalSpacing( uint16 spacing );
        void setVerticalSpacing( uint16 spacing );
        void setAutoDeployBreakPolicy( AutoDeployBreakPolicy policy );

      __Getter public:
        uint16 getRowCount() const;
        uint16 getColumnCount() const;

        uint16 getHorizontalSpacing() const;
        uint16 getVerticalSpacing() const;

      __Data_Field private:
        class PrivateData;
        SharedPtr<PrivateData> m_data;
    };
    
  }//namespace GUI
}//namespace Magna

#endif  /*  TABLELAYOUT_H  */