/*
 * This file is part of core library of Magna framework
 *
 * Copyright (c) 2013 by Magnus
 */
#ifndef SPINMUTEX_H
#define SPINMUTEX_H

#include "basedef_lib.h"
#include "SystemDef.h"
#include "BaseTypes.h"

#include "AtomicType.h"

namespace Magna{
   渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†   ⼀⨀℀†\brief
  †   †A synchronization mechanism.
  †  †一种同步机制
  †  */
  † /*!  尀搀攀琀愀椀氀猀਀†    ⨀਀†    ⨀†  䄀 猀瀀椀渀 洀甀琀攀砀 攀渀猀甀爀攀猀 洀甀琀甀愀氀氀礀 攀砀挀氀甀猀椀瘀攀 愀挀挀攀猀猀 琀漀 愀 猀椀渀最氀攀 爀攀猀漀甀爀挀攀 眀栀椀挀栀਀†    ⨀†  椀猀 猀栀愀爀攀搀 愀洀漀渀最 琀栀爀攀愀搀猀⸀਀†    ⨀਀†    ⨀† ₁쭎鉥ꕏ卸湏�᩾뽺஋뾕౎S啎⪍䑮過鉥ꕠ✰Ȁ਀†    ⨀਀†    ⨀†  吀漀 愀挀焀甀椀爀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 洀甀琀攀砀Ⰰ 椀昀 琀栀攀 洀甀琀攀砀 栀愀猀 愀氀爀攀愀搀礀 漀挀挀甀瀀椀攀搀Ⰰ਀†    ⨀†  琀栀攀 洀甀琀攀砀 眀椀氀氀 愀猀欀 昀漀爀 琀栀攀 漀眀渀攀爀猀栀椀瀀 愀渀搀 礀椀攀氀搀 昀漀爀 愀 眀栀椀氀攀 愀氀琀攀爀渀愀琀攀氀礀 琀椀氀氀 椀琀 漀戀琀愀椀渀 椀琀⸀਀†    ⨀਀†    ⨀† ⁎㩓恵⡎鉥ꕏ叿ౙ艧鱎鉥ꕏ卝쾈ꭓ恵⣿౒᥏᪋䉓恵⡎쩻䥐屎N୎ꑦｑ侀냿౶こ恵⠰Ȁ਀†    ⨀਀†    ⨀†  尀愀甀琀栀漀爀†Magnus
  †  *  †\version   1.0.0.0
  †  *  †\date  †2013/4/3
  †  */
  † class BASEDEF_LIB_EXPORT SpinMutex{
  †   开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†  搀攀昀愀甀氀琀 挀漀渀猀琀爀甀挀琀漀爀⸀ 尀溞�ꑧ蒐⁑ﵥ瀀਀†  †  匀瀀椀渀䴀甀琀攀砀⠀⤀ 㨀 洀开愀琀漀洀椀挀䌀漀甀渀琀攀爀⠀　⤀笀紀਀†  †  ⼀⼀℀†  挀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 椀渀椀琀椀愀氀 猀琀愀琀攀⸀ 尀湞♧†初始状态的构造函数
  †  †/*!
  †  † *  †\param  occupied
  †  † *  †if occupied is true, the initial state of the mutex is acquired.
  †  † *  †\n如果occupied初始值为true，则该互斥体初始状态即为已占用的。
  †  † */
  †  †explicit SpinMutex( bool occupied ) : m_atomicCounter( occupied == false ? 0: 1){}
  †  †//!  †copy-constructor. \n复制构造函数
  †  †SpinMutex( const SpinMutex& mutex) : m_atomicCounter( mutex.m_atomicCounter ){}
  †  †//!  †destructor. \n析构函数
  †  †~SpinMutex() {}
  †  †//!  †assign-operator. \n赋值操作符重载
  †  †SpinMutex& operator = ( const SpinMutex& mutex ) { m_atomicCounter.write( mutex.m_atomicCounter.read() ); return *this; }

  †   瀀甀戀氀椀挀㨀਀†  †   ⼀⼀℀†  愀挀焀甀椀爀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 洀甀琀攀砀⸀ 尀湓恵⡎鉥ꕏ匀਀†  †   瘀漀椀搀 愀挀焀甀椀爀攀猀⠀⤀ 挀漀渀猀琀㬀਀਀†  †   ⼀⼀℀†  爀攀氀攀愀猀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 洀甀琀攀砀⸀ 尀溑쩥㹎鉥ꕏ匀਀†  †   瘀漀椀搀 爀攀氀攀愀猀攀猀⠀⤀ 挀漀渀猀琀㬀਀਀†  †   ⼀⼀℀†  愀挀焀甀椀爀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 洀甀琀攀砀⸀ 尀湓恵⡎鉥ꕏ匀਀†  †   瘀漀椀搀 愀挀焀甀椀爀攀猀⠀⤀ 㬀਀਀†  †   ⼀⼀℀†  爀攀氀攀愀猀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 洀甀琀攀砀⸀ 尀溑쩥㹎鉥ꕏ匀਀†  †   瘀漀椀搀 爀攀氀攀愀猀攀猀⠀⤀ 㬀਀਀†  † __Data_Field private:
  †      洀甀琀愀戀氀攀 䄀琀漀洀椀挀㰀猀椀渀琀㌀㈀㸀 洀开愀琀漀洀椀挀䌀漀甀渀琀攀爀㬀਀†   紀㬀਀† }//Core
}//Magna
#endif  ⼀⨀†SPINMUTEX_H  ⨀⼀�