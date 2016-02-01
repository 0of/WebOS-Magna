#ifndef LISTGROUPCONTROLLERIMPLEMENTOR_H
#define LISTGROUPCONTROLLERIMPLEMENTOR_H

#include <vector>

#include "ScrollableController.h"
#include "Controller_p.h"

#include "ListGroupController.h"

namespace Magna{
  namespace GUI{

    class ListGroupControllerImplementor : public ControllerImplementor{
      public:
        ListGroupControllerImplementor(ListGroupController &);
        virtual ~ListGroupControllerImplementor();

        virtual void mousePressed( MouseEventArgs& event );
        //virtual void mouseReleased( MouseEventArgs& event );

         virtual void rendering( RenderingEventArgs& eventArgs );

      public:
        void _remeasureAvgRect();

      public:
        sint32 m_selectedIndex;
        std::vector<String> m_items;

        uint32 m_isSeqNumVisible : 16;
        uint32 m_isSeparateLineVisible : 8;
        uint32 m_isPartlyUpdate : 8;

        IntegerRectRegion m_avgRect;

        ListGroupController &m_binding;
    };
  

  }
}

#endif  /*  LISTGROUPCONTROLLERIMPLEMENTOR_H  */