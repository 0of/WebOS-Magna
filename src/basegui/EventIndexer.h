#ifndef EVENTINDEXER_H
#define EVENTINDEXER_H

#include "basedef/NullType.h"
#include "basedef/Uninstantiable.h"

using namespace Magna::Core;

namespace Magna{  
  template<typename EventType, typename IndexOffsetTrait = NullType>
  class EventIndexer{};

  template<uint32> 
  class Error_Ensure_Event_Index_Unique{};

#define EVENT_DEFINE(name,index)\
  class name;\
  template<typename IndexOffsetTrait> struct EventIndexer<name, IndexOffsetTrait>{ enum{Index=(index-IndexOffsetTrait::Offset)}; };\
  template<> struct EventIndexer<name, NullType>{ enum{Index=index}; };\
  template<> class Error_Ensure_Event_Index_Unique<index>: Uninstantiable{};
}//Magna

#endif  /*  EVENTINDEXER_H  */