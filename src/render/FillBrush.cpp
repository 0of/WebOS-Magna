#pragma warning(disable:4101)

#include "FillBrush.h"
#include "private/FillBrush_p.h"

#include "inner/InnerPrivateDataNullPointerException.h"
#include "inner/InnerIndexNotFoundException.h"
using namespace Magna::Inner;

#include "qt_glue_img/ImageResourceHandlerHelper.h"
using namespace Magna::Glue;

#include <sstream>

namespace Magna{
   namespace Render{


     FillBrush::FillBrush()
       :m_data(){

     }

     FillBrush::FillBrush( const FillBrush& brush )
       :m_data( brush.m_data ){

     }

     FillBrush::FillBrush( const Color& color )
       :m_data( new PrivateData( color ) ){

     }

     FillBrush::FillBrush( Gradient *gradient )
       :m_data( new PrivateData( gradient ) ){

     }

     FillBrush::FillBrush( const Image& img )
       :m_data( new PrivateData( img ) ){

     }

     FillBrush::FillBrush( TexturePattern *pattern )
       :m_data( new PrivateData( pattern ) ){

     }

     FillBrush::~FillBrush(){

     }

     FillBrush::BrushContent FillBrush::getBrushContent() const{
        FillBrush::BrushContent _content = FillBrush::BrushContent_None;

        if( !m_data.isNull() ){
          _content = m_data->m_brushContent;
        }

        return _content;
     }

     void FillBrush::setColor( const Color& color ){
       try{
         if( m_data.isNull() ){
           m_data = SharedPtr<PrivateData>( new PrivateData( color ) );
         }
         else{
           if(m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Color ){
               (*reinterpret_cast<Color *>(m_data->m_brushData)) = color;
             }
             else{
               m_data = SharedPtr<PrivateData>( new PrivateData(color) );
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     Color FillBrush::getColor() const{
       Color _retColor;
       try{
         if( !m_data.isNull() ){
           if( m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Color ){
               _retColor = (*reinterpret_cast<const Color *>(m_data->m_brushData));
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
      return _retColor;
     }

     void FillBrush::setGradient( Gradient *gradient ){
       assert( gradient != Nullptr );

       try{
         if( m_data.isNull() ){
           m_data = SharedPtr<PrivateData>( new PrivateData( gradient ) );
         }
         else{
           if(m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Gradient ){
               (*(reinterpret_cast<SharedPtr<Gradient> *>(m_data->m_brushData))) = SharedPtr<Gradient>( gradient );
             }
             else{
               m_data = SharedPtr<PrivateData>( new PrivateData(gradient) );
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     SharedPtr<Gradient> FillBrush::getGradient() const{
       SharedPtr<Gradient> _retGradient ;
       try{
         if( !m_data.isNull() ){
           if( m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Gradient ){
               _retGradient = *(reinterpret_cast<const SharedPtr<Gradient> *>( m_data->m_brushData ));
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
       return _retGradient;
     }

     Image FillBrush::getTexture() const{
       Image _image;
       try{
         if( !m_data.isNull() ){
           if( m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Texture ){
               _image = *(reinterpret_cast<const Image *>( m_data->m_brushData ));
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
      return _image;
     }

     void FillBrush::setTexture( const Image& img ){
       try{
         if( m_data.isNull() ){
           m_data = SharedPtr<PrivateData>( new PrivateData( img ) );
         }
         else{
           if(m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_Texture ){
               (*reinterpret_cast<Image *>(m_data->m_brushData)) = img;
             }
             else{
               m_data = SharedPtr<PrivateData>( new PrivateData(img) );
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     void FillBrush::setTexturePattern( TexturePattern *pattern ){
       assert( pattern != Nullptr );
       try{
         if( m_data.isNull() ){
           m_data = SharedPtr<PrivateData>( new PrivateData( pattern ) );
         }
         else{
           if(m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_TexturePattern ){
               (*reinterpret_cast<SharedPtr<TexturePattern> *>(m_data->m_brushData)) = SharedPtr<TexturePattern>(pattern);
             }
             else{
               m_data = SharedPtr<PrivateData>( new PrivateData(pattern) );
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
     }

     SharedPtr<TexturePattern> FillBrush::getTexturePattern() const{
       SharedPtr<TexturePattern> _retPattern ;
       SharedPtr<Gradient> _retGradient ;
       try{
         if( !m_data.isNull() ){
           if( m_data->m_brushContent == m_data->m_comfirmBrushContent ){
             if( m_data->m_brushContent == FillBrush::BrushContent_TexturePattern ){
               _retPattern = *(reinterpret_cast<const SharedPtr<TexturePattern> *>( m_data->m_brushData ));
             }
           }
           else{
             throw std::runtime_error("Memory Corruption");
           }
         }
       }
       catch( const std::exception& ex ){
         abort();
       }
       return _retPattern;
     }

    FillBrush & FillBrush::operator = ( const FillBrush& brush ){
      m_data = brush.m_data;
      return *this;
    }

    String FillBrush::PrivateData::_toFillString( const IntegerDyadCoordinate& offset ) const{
      OutStringStream _outter;
      try{
        if( m_brushContent == m_comfirmBrushContent){
          if( m_brushContent == FillBrush::BrushContent_Color ){
            const Color & _color = *( reinterpret_cast<const Color *>( m_brushData ) );
            _outter << "var style=" << _color.toString() << L";";
          }
          else if( m_brushContent == FillBrush::BrushContent_Gradient ){
            const SharedPtr<Gradient>& _gradient = *(reinterpret_cast<const SharedPtr<Gradient> *>( m_brushData ));
            _outter << _gradient->_toString( offset );
            _outter <<  "var style=gradient;";
          }
          else if( m_brushContent == FillBrush::BrushContent_Texture ){
            const Image& _img  = *(reinterpret_cast<const Image *>( m_brushData ));
            if( ImageResourceHandlerHelper::getImageResourceString( _img, _outter ) ){
              _outter << "var style=context.createPattern(image,\"no-repeat\");";
            }
          }
          else if( m_brushContent == FillBrush::BrushContent_TexturePattern ){
            const SharedPtr<TexturePattern>& _pattern = *(reinterpret_cast<const SharedPtr<TexturePattern> *>( m_brushData ));
            _outter << _pattern->_toString();
            _outter << "var style=pattern;";
          }
          else{
            throw InnerIndexNotFoundException();
          }
        }
        else{
          throw std::runtime_error("Memory Corruption");
        }
      }
      catch ( const std::exception& ex ){
        //
        abort();
      }
      return _outter.str();
    }

    ///private implementations
     String FillBrush::PrivateData::_toString( const IntegerDyadCoordinate& offset ) const{
       OutStringStream _outter;
       try{
         if( m_brushContent == m_comfirmBrushContent){
           if( m_brushContent == FillBrush::BrushContent_Color ){
             const Color & _color = *( reinterpret_cast<const Color *>( m_brushData ) );
             _outter << L"context.fillStyle=" << _color.toString() << L";";
           }
           else if( m_brushContent == FillBrush::BrushContent_Gradient ){
             const SharedPtr<Gradient>& _gradient = *(reinterpret_cast<const SharedPtr<Gradient> *>( m_brushData ));
             _outter << _gradient->_toString( offset );
             _outter <<  L"context.fillStyle=gradient;";
           }
           else if( m_brushContent == FillBrush::BrushContent_Texture ){
             const Image& _img  = *(reinterpret_cast<const Image *>( m_brushData ));
             if( ImageResourceHandlerHelper::getImageResourceString( _img, _outter ) ){
               _outter << L"context.fillStyle=context.createPattern(image,\"no-repeat\");";
             }
           }
           else if( m_brushContent == FillBrush::BrushContent_TexturePattern ){
             const SharedPtr<TexturePattern>& _pattern = *(reinterpret_cast<const SharedPtr<TexturePattern> *>( m_brushData ));
             _outter << _pattern->_toString();
             _outter << L"context.fillStyle=pattern;";
           }
           else{
             throw InnerIndexNotFoundException();
           }
         }
         else{
           throw std::runtime_error("Memory Corruption");
         }
       }
       catch ( const std::exception& ex ){
         //
         abort();
       }
      return _outter.str();
     }

   }//Render
}//Magna
