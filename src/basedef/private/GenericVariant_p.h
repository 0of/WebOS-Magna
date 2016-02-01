#ifndef GENERICVARIANT_P_H
#define GENERICVARIANT_P_H

#include "SharedPtr.h"
#include "PointerTrait.h"
#include "CompilerTimeAssert.h"

#include "Private_p.h"

namespace Magna{  
   namespace Core{
     template<typename _class_type, bool _isPointer>
     struct _GenericTypeTrait;

     template<typename _class_type>
     struct _GenericTypeTrait<_class_type, true>{
        typedef SharedPtr<_class_type> GenericType;
     };

     template<typename _class_type>
     struct _GenericTypeTrait<_class_type, false>{
       typedef _class_type GenericType;
     };

     template<
          typename _type
          ,typename _generic_trait = _GenericTypeTrait<typename PointerTrait<_type>::OriginalType, PointerTrait<_type>::isPointer>
          >
    class GenericVariantPolicy{
      __Constructor_Destructor public:
        typedef typename _generic_trait::GenericType GenericVariantType;

        GenericVariantPolicy( const _type& instance )
          :m_instance( instance ){

        }
        
        GenericVariantPolicy( const GenericVariantPolicy<_type>& p )
          :m_instance( p.instance ){

        }

        ~GenericVariantPolicy(){

        }

      __Data_Field protected:
        typename _generic_trait::GenericType m_instance;
        
    };
   }//Core
}//Magna

#endif  /*  GENERICVARIANT_P_H  */