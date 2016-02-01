#ifndef REPEATTEXTUREPATTERN_H
#define REPEATTEXTUREPATTERN_H

#include "render_lib.h"

#include "TexturePattern.h"
#include "Image.h"

namespace Magna{  
   namespace Render{
     class RENDER_LIB_EXPORT RepeatTexturePattern : public __Generalizes TexturePattern{
       __Constants public:
        enum RepeatDirection{
          RepeatDirection_NoRepeat = 0x00000000,
          RepeatDirection_Horizontal = 0x00000001,
          RepeatDirection_Vertical = 0x00000002,
          RepeatDirection_Both_Horizontal_Vertical = 0x00000003
        };
      __Constructor_Destructor public:
        RepeatTexturePattern();
        explicit RepeatTexturePattern( RepeatDirection direction );
        virtual ~RepeatTexturePattern();
        
      __Override_Methods protected:
        virtual String _toString() const ;

      __Setter public:
        void setTextureImage( const Image& img );
        void setDirection( RepeatDirection dir );

      __Data_Field private:
        RepeatDirection m_direction;
      
     };
   }//Render
}//Magna

#endif  /*  REPEATTEXTUREPATTERN_H  */