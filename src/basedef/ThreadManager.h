#ifndef THREADMANAGER_H
#define THREADMANAGER_H

#include <map>

#include "SpinMutex.h"
#include "Thread.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  挀氀愀猀猀 吀栀爀攀愀搀䴀愀渀愀最攀爀笀਀†  †public:
  †  †static ThreadManager &getThreadManager();

  †  瀀爀椀瘀愀琀攀㨀਀†  †  吀栀爀攀愀搀䴀愀渀愀最攀爀⠀⤀㬀਀†  †  縀吀栀爀攀愀搀䴀愀渀愀最攀爀⠀⤀㬀਀਀†  †public:
  †  †//call in the main thread
  †  †void initMainThread();

  †  †void registerThread( Thread& );
  †  †void unregisterThread( Thread& );

  †  †Thread getCurrentThread();

  †  †bool isMainThread( const Thread& );

  †  瀀爀椀瘀愀琀攀㨀਀†  †  猀琀搀㨀㨀洀愀瀀㰀甀椀渀琀㌀㈀Ⰰ 吀栀爀攀愀搀㸀 洀开琀栀爀攀愀搀猀㬀਀†  †  甀椀渀琀㌀㈀ 洀开洀愀椀渀吀栀爀攀愀搀䤀搀㬀਀†  †  匀瀀椀渀䴀甀琀攀砀 洀开洀甀琀攀砀㬀਀†  紀㬀਀਀†}
}//namespace Magna

#endif  ⼀⨀†THREADMANAGER_H  ⨀�