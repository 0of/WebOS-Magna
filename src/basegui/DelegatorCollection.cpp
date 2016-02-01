#include "DelegatorCollection.h"

namespace Magna{
  namespace GUI{
    
    DelegatorCollection::DelegatorCollection( uint16 type, uint16 shared /* = !false */ )
      :m_shared( shared )
      ,m_type( type ){

    }

    DelegatorCollection::DelegatorCollection( const DelegatorCollection& collection )
      :m_shared( collection.m_shared )
      ,m_type( collection.m_type ){

    }

    DelegatorCollection::~DelegatorCollection(){

    }

  }//namespace GUI
}//namespace Magna