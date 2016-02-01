#ifndef LISTGROUPCONTROLLER_H
#define LISTGROUPCONTROLLER_H

#include <vector>

#include "ScrollableController.h"

namespace Magna{
  namespace GUI{
    
    class ListGroupController : public ScrollableController{
      TRIGGER_DEF(OnceItemSelected, sint32)

      public:
        ListGroupController();
        virtual~ListGroupController();

      public:
        void addListItem( const String& text );
        void addListItems( const std::vector<String>& );

        void removeItemAt( sint32 index );

        void selectAt( sint32 index);

        //void setSeqNumberVisible( bool );
        void setSeparateLineVisible( bool );

    };

  }//namespace GUI
}//namespace Magna
#endif  /*  LISTGROUPCONTROLLER_H  */