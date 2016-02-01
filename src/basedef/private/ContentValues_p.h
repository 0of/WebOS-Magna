#ifndef CONTENTVALUES_P_H
#define CONTENTVALUES_P_H

#include "BaseTypes.h"
#include "SystemDef.h"
#include "UnionVariant.h"

//STL
#include <map>

namespace Magna{  
   namespace Core{
     class PrivateContentValues{
      __Constructor_Destructor protected:
         PrivateContentValues()
           :m_maps(){
        }
        
         explicit PrivateContentValues( const std::string& key,  const UnionVariant& val )
          :m_maps( key, val ){

        }

        ~PrivateContentValues();

      protected:
        inline void _insert(  const std::string& key,  const UnionVariant& val  ){
          m_maps.insert( std::pair<std::string,UnionVariant>( key, val ) );
        }

        inline UnionVariant _find(  const std::string& key  ){
          std::map<sint32, UnionVariant>::iterator _iter = m_maps.find( key )  ;
            return _iter != m_maps.end() ?
              *_iter : UnionVariant();
        }

      __Data_Field private:
        std::map<sint32, UnionVariant> m_maps;
     }
   }//Core
}//Magna

#endif  /*  CONTENTVALUES_P_H  */