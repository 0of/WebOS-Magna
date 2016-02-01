#ifndef SHADOWAPPEARANCEEFFECT_H
#define SHADOWAPPEARANCEEFFECT_H

#include "render_lib.h"

#include "basedef/DyadCoordinate.h"
#include "basedef/Color.h"
using namespace Magna::Core;

#include "AppearanceEffect.h"

namespace Magna{  
  namespace Render{
    class RENDER_LIB_EXPORT ShadowAppearanceEffect : public AppearanceEffect{
      public:
        ShadowAppearanceEffect();
        ShadowAppearanceEffect( const ShadowAppearanceEffect& );
        explicit ShadowAppearanceEffect( uint32, const Color&, const IntegerDyadCoordinate& );
        virtual~ ShadowAppearanceEffect();

      public:
        void setBlurGranularity( uint32 );
        void setShadowColor( const Color& );
        void setShadowOffset( const IntegerDyadCoordinate& );

      public:
        virtual String toString() const;

      private:
        uint32 m_shadowBlurGranularity;
        Color m_shadowColor;
        IntegerDyadCoordinate m_shadowOffset;
    };
  }
}

#endif  /*  SHADOWAPPEARANCEEFFECT_H  */

