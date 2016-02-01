#ifndef RENDERABLEELEMENT_H
#define RENDERABLEELEMENT_H

#include "render_lib.h"

#include "basedef/Size.h"
#include "basedef/RectRegion.h"
#include "basedef/SharedPtr.h"
using namespace Magna::Core;

#include "interpret/AbstractedElementNativeSource.h"
using namespace Magna::Interpret;

#include "RenderManager.h"

namespace Magna{
   namespace Render{

     class RENDER_LIB_EXPORT  RenderableElement : public __Generalizes AbstractedElementNativeSource{
      __Constructor_Destructor protected:
        RenderableElement();
        explicit RenderableElement( const String& );
        RenderableElement( RenderManager *manager );
        virtual~RenderableElement() = 0;

      __Override_Methods protected:
        virtual String toElementString () const = 0;
        virtual String toIntermediaCode () const = 0;

        //CSS style
        virtual String toStyleString() const = 0;
        //JavaScript
        virtual String toScriptString () const = 0;

        virtual void initFromString( const String& str ) = 0;

        virtual String toProtogenousInitString( const String& start = L"function(element){"
          , const String& end = L"}", const String& element = L"element") const = 0;

      /*
      protected:
        void setSize( const IntegerSize& size );
        void setPos( const IntegerDyadCoordinate& pos );

      protected:
        inline IntegerDyadCoordinate getPos() const{ return m_renderableRect.getTopLeftCoord(); }
        inline IntegerSize getSize() const { return m_renderableRect.getSize(); }
        inline const IntegerRectRegion &getBoundingRectRegion() const{ return m_renderableRect; }
      */

      protected:
        IntegerRectRegion m_renderableRect;
        RenderManager * m_manager;
     };


   }//Render
}//Magna

#endif  /*  RENDERABLEELEMENT_H  */
