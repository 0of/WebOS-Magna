#ifndef EVENTDISPATCHERNODE_H
#define EVENTDISPATCHERNODE_H

#include "mruntime_global.h"

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"

#include <QObject>

namespace Magna{
  namespace Runtime{
    class MRUNTIME_EXPORT EventDispatcherNode : public QObject{
      Q_OBJECT
        Q_DISABLE_COPY(EventDispatcherNode)

        friend class RuntimeContainer;

    protected:
      EventDispatcherNode();
      virtual ~EventDispatcherNode();

      public slots:
        void dispatchMousePressed( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers );
        void dispatchMousePressingMoved(  const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers );
        void dispatchMouseReleased( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers );

        //void dispatchMouseHoverIn( const uint64& runtime_wid , sint32 x, sint32 y, uint32 buttons,  uint32 modifiers );
        //void dispatchMouseHovered( const uint64& runtime_wid , sint32 x, sint32 y, uint32 buttons,  uint32 modifiers );
        //void dispatchMouseHoverOut( const uint64& runtime_wid , sint32 x, sint32 y, uint32 buttons,  uint32 modifiers );

        void dispatchMouseWheelUp( const QString& id , sint32 x, sint32 y, sint32 delta,  uint32 modifiers );
        void dispatchMouseWheelDown( const QString& id , sint32 x, sint32 y, sint32 delta,  uint32 modifiers  );

        void dispatchMouseClicked( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers );
        void dispatchMouseDoubleClicked( const QString& id, qint32 sx, qint32 sy, qint32 button, qint32 modifiers );

        void dispatchKeyPressed( const QString& id, qint32 pressedKey, qint32 modifiers );
        void dispatchKeyReleased( const QString& id, qint32 pressedKey, qint32 modifiers );

        void dispatchWindowMoved( const QString& id, qint32 x, qint32 y );
        void dispatchWindowResized( const QString& id, qint32 w, qint32 h );

        void dispatchHoverIn( const QString& id );
        void dispatchHoverOut( const QString& id );
    public:  
      static QString shared_NodeName;
    };
  }
}//namespace Magna

#endif  /*  EVENTDISPATCHERNODE_H  */