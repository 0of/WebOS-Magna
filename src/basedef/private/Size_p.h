#ifndef SIZE_P_H
#define SIZE_P_H

#include <cstring>

#include "../StaticTypeTrait.h"
#include "../basedef_lib.h"

#include "../Comparer.h"

namespace Magna{
   namespace Core{
     template<
       typename _type
       ,  class _type_trait =  StaticTypeTrait<_type, sint32, StaticTypeTrait<_type, float, StaticTypeTrait<_type, double> > >
     >
     class BASEDEF_LIB_EXPORT SizePolicy{
       __Data_Field public:
        _type m_height;
        _type m_width;

      __Constructor_Destructor public:
        SizePolicy()
          :m_height()
          ,m_width(){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        explicit SizePolicy( const _type& width, const _type& height)
          :m_height ( height )
          ,m_width ( width ){
          COMPILTER_TIME_ASSERT((_type_trait::isMatched), Shall_Matches_Int_Float_Double_Type)
        }

        SizePolicy( const SizePolicy<_type>& size )
          :m_height( size.m_height )
          ,m_width( size.m_width ){

        }

        ~SizePolicy(){

        }

      __Overloaded_Methods public:
        SizePolicy & operator = ( const SizePolicy<_type>& size ){
          ::memcpy( this, &size, sizeof(SizePolicy<_type>) );
          return *this;
        }

     };
   }//Core
}//Magna
#endif  /*  SIZE_P_H  */
