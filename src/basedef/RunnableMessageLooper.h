#ifndef RUNNABLEMESSAGELOOPER_H
#define RUNNABLEMESSAGELOOPER_H

#include "basedef_lib.h"

#include <queue>

#include "SharedPtr.h"
#include "Message.h"
#include "AtomicType.h"
#include "Thread.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 刀甀渀渀愀戀氀攀䴀攀猀猀愀最攀䰀漀漀瀀攀爀笀਀†  †__Constructor_Destructor public:
  †  †RunnableMessageLooper();
  †  †virtual ~RunnableMessageLooper();

  †  瀀甀戀氀椀挀㨀਀†  †  瘀漀椀搀 猀琀愀爀琀䰀漀漀瀀⠀⤀㬀਀†  †  瘀漀椀搀 爀攀挀攀椀瘀攀䔀瘀攀渀琀⠀ 挀漀渀猀琀 匀栀愀爀攀搀倀琀爀㰀䴀攀猀猀愀最攀㸀☀ ⤀㬀਀†  †  瘀漀椀搀 愀戀漀甀琀吀漀䔀渀搀䰀漀漀瀀⠀⤀㬀਀†  †  瘀漀椀搀 攀渀搀䰀漀漀瀀䤀渀猀琀愀渀琀氀礀⠀⤀㬀਀਀†  †protected:
  †  †std::queue< SharedPtr<Message> > m_messageQueue;
  †  †SpinMutex m_messageMutex;
  †  †AtomicInt m_waitSignal;
  †  †uint16 m_isAboutQuit;
  †  †uint16 m_isInstantlyQuit;
  †  †Thread m_bindingThread;
  †};

  紀਀紀⼀⼀渀愀洀攀猀瀀愀挀攀 䴀愀最渀愀਀਀⌀攀渀搀椀昀†/*  刀唀一一䄀䈀䰀䔀䴀䔀匀匀䄀䜀䔀䰀伀伀倀䔀刀开䠀†*/