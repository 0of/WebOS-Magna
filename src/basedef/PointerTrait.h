/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef POINTERTRAIT_H
#define POINTERTRAIT_H

#include "BaseTypes.h"
#include "Uninstantiable.h"

namespace Magna{  ਀† namespace Core{
  † /*
  † template<typename Type>
  † class PointerTrait : Uninstantiable{

  †   琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开琀礀瀀攀㸀਀†  † struct PrivatePointerTrait{
  †  † typedef sint8 Marker;
  †   紀㬀਀਀†  † template<typename _type>
  †   猀琀爀甀挀琀 倀爀椀瘀愀琀攀倀漀椀渀琀攀爀吀爀愀椀琀㰀开琀礀瀀攀 ⨀㸀笀਀†  †   琀礀瀀攀搀攀昀 挀栀愀爀 䴀愀爀欀攀爀嬀㈀崀㬀਀†  † };

  † public:
  †   攀渀甀洀 笀 椀猀倀漀椀渀琀攀爀 㴀 ⠀猀椀稀攀漀昀 倀爀椀瘀愀琀攀倀漀椀渀琀攀爀吀爀愀椀琀㰀吀礀瀀攀㸀㨀㨀䴀愀爀欀攀爀 㴀㴀 猀椀稀攀漀昀 ⠀猀椀渀琀㠀⤀⤀紀㬀਀†   紀㬀਀†   ⨀⼀਀†  ⼀⨀℀†\brief
  †  †A tool can use to distinguish the pointer from types.
  †  †用来静态检测输入类型是否为指针类型。
  †*/

  † /*!  ਀†     ⨀†It's use for static check and it's common to see when template programming
  †   *  䄀渀搀 漀昀 挀漀甀爀猀攀 琀栀攀 䌀⬀⬀　砀 匀吀䰀 栀愀猀 琀栀攀 琀爀愀椀琀 琀漀漀⸀ ਀†     ⨀਀†     ⨀†All you need to do is given the T type and access the enumerator value
  †   *  䤀昀 琀栀攀 吀 琀礀瀀攀 礀漀甀 椀渀瀀甀琀 椀猀 瀀漀椀渀琀攀爀 琀漀 愀渀礀 琀礀瀀攀Ⰰ 琀栀攀 瘀愀氀甀攀 眀椀氀氀 戀攀 ㄀⠀吀爀甀攀⤀਀†     ⨀†otherwsie 0(False).
  †   *
  †   *  䤀昀 礀漀甀 眀愀渀琀 琀漀 搀椀猀琀椀渀最甀椀猀栀 愀 瀀漀椀渀琀攀爀 昀爀漀洀 椀渀猀琀愀渀挀攀猀 渀漀琀 琀栀攀 琀礀瀀攀猀਀†     ⨀†\sa  倀漀椀渀琀攀爀䤀渀猀琀愀渀挀攀吀爀愀椀琀਀†     ⨀਀†     ⨀†\sa StaticTypeTrait, StaticInstanceTypeTrait
  †   *
  †   *  尀琀瀀愀爀愀洀 吀礀瀀攀 琀栀攀 琀礀瀀攀 渀攀攀搀猀 戀攀椀渀最 挀栀攀挀欀攀搀਀†     ⨀† ₈ꭨ쁭䭶葼筗謀਀†     ⨀†  ਀†     ⨀†  尀戀 䔀⸀最⸀਀†     ⨀†  尀挀漀搀攀笀⸀挀瀀瀀紀਀†     ⨀†
  †   *  †//T = sint32 *
  †   *  †bool isPointer = PointerTrait<T>::isPointer;//true
  †   *  † \endcode  ਀†     ⨀਀†     ⨀† \author  䴀愀最渀甀猀਀†     ⨀† \version   1.0.0.0
  †   *   尀搀愀琀攀†  ㈀　㄀㈀⼀㄀㈀⼀㈀㘀  ਀†     ⨀⼀਀†   琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 吀礀瀀攀㸀਀†   猀琀爀甀挀琀 倀漀椀渀琀攀爀吀爀愀椀琀 㨀 唀渀椀渀猀琀愀渀琀椀愀戀氀攀笀਀†  † //!  爀攀猀甀氀琀 攀渀甀洀攀爀愀琀漀爀਀†  † enum { isPointer = 0 /*!< if not a pointer the value is 0 */  };
  †   琀礀瀀攀搀攀昀 吀礀瀀攀 伀爀椀最椀渀愀氀吀礀瀀攀㬀਀†   紀㬀਀਀†   琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 吀礀瀀攀㸀਀†   猀琀爀甀挀琀 倀漀椀渀琀攀爀吀爀愀椀琀㰀吀礀瀀攀 ⨀㸀 㨀 唀渀椀渀猀琀愀渀琀椀愀戀氀攀笀਀†  † //!  爀攀猀甀氀琀 攀渀甀洀攀爀愀琀漀爀਀†  †enum { isPointer = 1 /*!< if is a pointer the value is 1 */};
  †  琀礀瀀攀搀攀昀 吀礀瀀攀 伀爀椀最椀渀愀氀吀礀瀀攀㬀਀†   紀㬀਀        ਀         琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开倀漀椀渀琀攀爀开吀礀瀀攀㸀ഀ਀         猀琀爀甀挀琀 倀漀椀渀琀攀爀吀礀瀀攀吀爀愀椀琀笀ഀ਀             琀礀瀀攀搀攀昀 开倀漀椀渀琀攀爀开吀礀瀀攀 开吀礀瀀攀㬀ഀ਀         紀㬀ഀ਀ഀ਀         琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开倀漀椀渀琀攀爀开吀礀瀀攀㸀ഀ਀         猀琀爀甀挀琀 倀漀椀渀琀攀爀吀礀瀀攀吀爀愀椀琀㰀开倀漀椀渀琀攀爀开吀礀瀀攀 嬀崀㸀笀ഀ਀             琀礀瀀攀搀攀昀 开倀漀椀渀琀攀爀开吀礀瀀攀 开吀礀瀀攀㬀ഀ਀         紀㬀ഀ਀† }//Core
}//Magna

#endif  ⼀⨀†POINTERTRAIT_H  ⨀�