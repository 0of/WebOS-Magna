/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef ABSTRACTEDNOTIFIER_H
#define ABSTRACTEDNOTIFIER_H

#include "basedef_lib.h"

#include "Message.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  ⼀⨀℀†  尀戀爀椀攀昀਀†  †  吀栀椀猀 挀氀愀猀猀 爀攀瀀爀攀猀攀渀琀猀 琀栀攀 愀戀猀琀爀愀挀琀 渀漀琀椀昀椀攀爀⸀਀†  † ⁢붌憐᩷԰Ȁ਀†   ⨀⼀਀†  ⼀⨀℀†  尀搀攀琀愀椀氀猀਀†    ⨀†  ਀†    ⨀†  䄀 渀漀琀椀昀椀攀爀 椀猀 愀 洀攀猀猀愀最攀 戀甀琀 愀氀猀漀 栀愀猀 椀琀猀 漀眀渀 戀攀栀愀瘀椀漀爀猀⸀਀†    ⨀†  䜀攀渀攀爀愀氀氀礀Ⰰ 攀愀挀栀 渀漀琀椀昀椀攀爀 栀愀猀 渀漀琀椀昀椀攀攀 愀渀搀 椀琀猀 渀漀琀椀昀椀挀愀琀椀漀渀 戀攀栀愀瘀椀漀爀Ⰰ ਀†    ⨀†  愀挀琀甀愀氀氀礀 椀猀 愀 洀攀琀栀漀搀⸀ 吀栀攀 渀漀琀椀昀椀攀爀✀猀 渀漀琀椀昀椀挀愀琀椀漀渀 戀攀栀愀瘀椀漀爀 眀椀氀氀 戀攀 搀漀渀攀 戀礀਀†    ⨀†  瘀椀爀琀甀愀氀 洀攀琀栀漀搀 渀漀琀椀昀礀⠀⤀⸀ 吀漀 椀洀瀀氀攀洀攀渀琀 渀漀琀椀昀礀⠀⤀Ⰰ 挀漀洀洀漀渀氀礀Ⰰ 渀漀琀椀昀椀攀攀 眀椀氀氀 ਀†    ⨀†  挀愀氀氀 琀栀攀 渀漀琀椀昀椀挀愀琀椀漀渀 戀攀栀愀瘀椀漀爀⸀ ਀†    ⨀†  ਀†    ⨀† ₐ᩷զ⽎y쵭衠濿౏䙦⽢†其自己的行为。大体上来说，每个通知者都朠ₐ᩷葛歷愀਀†    ⨀† ⁎쪐᩷蒈䱎㫿౛麖䕎੦⽎N⩥륬픰ɥ瑎⪐᩷ն蒐᩷䱎㩏᪐᪏잆婥륬픀渀漀琀椀昀礀⠀⥧敛鹳뀰Ȁ਀†    ⨀† ⁙艧鲉腛鹳뀀 渀漀琀椀昀礀⠀⤀₆婥륬헿౎ⱜㅦ⾐᩷葛歷憌͵⢐᩷䱎㨰Ȁ਀†    ⨀†  ਀†    ⨀†  䄀 渀漀琀椀昀椀攀爀 攀砀椀猀琀猀 昀漀爀 猀琀漀爀椀渀最 愀 椀洀瀀氀攀洀攀渀琀愀戀氀攀 戀攀栀愀瘀椀漀爀 愀渀搀 愀氀猀漀 挀愀渀 戀攀 瀀漀猀琀਀†    ⨀†  琀漀 洀攀猀猀愀最攀 焀甀攀甀攀 眀愀椀琀椀渀最 昀漀爀 爀甀渀渀椀渀最 椀渀 攀瘀攀渀琀 氀漀漀瀀攀爀 琀栀爀攀愀搀⸀਀†    ⨀†  ਀†    ⨀† ₐ᩷՛塗⡶葡ཎ䥦⽓�塎N⩓枈䱶蒈䱎㫿౔౥当协屭衠潓톐ž�衠澖ὒ᝻䥟蔀਀†    ⨀† ⁗⡑癎홾뽺୎ⵢ枈䰰Ȁ਀†    ⨀†  ਀†    ⨀†  䔀愀挀栀 渀漀琀椀昀椀攀爀 挀愀渀 戀攀 爀攀最椀猀琀攀爀攀搀 戀礀 爀攀最椀猀琀攀爀一漀琀椀昀椀攀爀吀礀瀀攀⠀⤀⸀ 䤀昀 渀攀攀搀 琀漀 瀀漀猀琀 愀 甀猀攀爀 渀漀琀椀昀椀攀爀਀†    ⨀†  洀攀猀猀愀最攀Ⰰ 爀攀最椀猀琀攀爀 愀 渀漀琀椀昀椀攀爀 琀礀瀀攀 昀椀爀猀琀 愀渀搀 漀瘀攀爀爀椀搀攀 琀栀攀 渀漀琀椀昀礀⠀⤀ 洀攀琀栀漀搀Ⰰ 眀栀椀挀栀 ਀†    ⨀†  搀漀 琀栀攀 愀挀琀甀愀氀 戀攀栀愀瘀椀漀爀 椀渀 琀栀攀 渀漀琀椀昀礀⠀⤀ 猀挀漀瀀攀⸀ ਀†    ⨀†  ਀†    ⨀† ⁫콎⪐᩷֐ﵓ᪏윀 爀攀最椀猀琀攀爀一漀琀椀昀椀攀爀吀礀瀀攀⠀⤀⁧斏�䱬谰Ȁ⁙艧鱠⢁驎䥶蒐᩷׿ఀ਀†    ⨀† ⁓腬豼筒⭱㙔ຑ춏紀 渀漀琀椀昀礀⠀⤀⁥륬핓獓ఀ⁎彜ㅦ⽗⠀ 渀漀琀椀昀礀⠀⤀⁥륬핎ⵐ婛麖䕶葝尰Ȁ਀†    ⨀ ਀†    ⨀†  尀愀甀琀栀漀爀† Magnus
  †  *  †\version   1.0.0.0
  †  *  †\date  † 2013/4/21  ਀†    ⨀⼀਀਀†  开开䄀戀猀琀爀愀挀琀攀搀 挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀 㨀 瀀甀戀氀椀挀 䴀攀猀猀愀最攀笀਀†  †public:
  †  †//!  †register the notifier type. \n注册通知者类别
  †  †/*!  ਀†  †   ⨀†  尀瀀愀爀愀洀 栀椀渀琀਀†  †   ⨀†  愀 甀渀椀焀甀攀 甀椀渀琀㌀㈀ 甀猀攀爀 瘀愀氀甀攀਀†  †   ⨀†  椀昀 渀漀琀 甀渀椀焀甀攀Ⰰ  椀琀 眀椀氀氀 爀攀琀甀爀渀 愀 甀渀椀焀甀攀 渀攀眀 漀渀攀⸀਀†  †   ⨀†  尀湕⽎v萀甀椀渀琀㌀㈀⁐㳿ఀ⁙艧鱎ൕ⽎ÿ౒᥏᪏푖�N⩕⽎v葐㰰Ȁ਀†  †   ⨀†  ਀†  †   ⨀†  尀爀攀琀甀爀渀 愀 甀渀椀焀甀攀 渀漀琀椀昀椀攀爀 琀礀瀀攀਀†  †   ⨀†  椀昀 琀栀攀 栀椀渀琀 椀猀 甀渀椀焀甀攀 Ⰰ 椀琀✀ 氀氀 戀攀 攀焀甀愀氀 琀漀 栀椀渀琀⸀਀†  †   ⨀†  尀溏푖�⽎v蒐᩷ռ筒⬰ə艧鰀栀椀渀瑦⽕⽎v蓿౒᥎฀栀椀渀瑐㱶రȀ਀†  †   ⨀†  ਀†  †   ⨀⼀਀†  †  猀琀愀琀椀挀 甀椀渀琀㌀㈀ 爀攀最椀猀琀攀爀一漀琀椀昀椀攀爀吀礀瀀攀⠀ 甀椀渀琀㌀㈀ 栀椀渀琀 ⤀㬀 ਀਀†  †  猀琀愀琀椀挀 挀漀渀猀琀 甀椀渀琀㌀㈀ 猀栀愀爀攀搀开䐀攀昀愀甀氀琀吀礀瀀攀㬀†/*!<  default type , value is 0 */  

  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀爀漀琀攀挀琀攀搀㨀਀†  †  ਀†  †  ⼀⼀℀†  挀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 琀礀瀀攀⸀ 尀湾�骐᩷ռ筒⭶葧蒐⁑ﵥ瀀 ਀†  †  ⼀⨀℀†
  †  † *  †if do not need to identify the notifier, just put #shared_DefaultType
  †  † *  †as the parameter. Or register one with registerNotifierType() .
  †  † *  †
  †  † *  †如果无需鉴别通知者，仅需使用 #shared_DefaultType 作为参数。
  †  † *  †或者调用  registerNotifierType() 来进行注册一个类别。
  †  † *  †
  †  † *  †\sa registerNotifierType( uint32 )
  †  † */
  †  †explicit AbstractedNotifier( uint32 notifierType );

  †  †//!  †Destructor. \n析构函数
  †  †virtual ~AbstractedNotifier();

  †  瀀爀椀瘀愀琀攀㨀਀†  †  ⼀⼀℀†  挀漀瀀礀ⴀ挀漀渀猀琀爀甀挀琀漀爀 昀漀爀戀椀搀搀攀渀⸀ 尀湎൑䆋롙൒㙧蒐 ਀†  †  䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀⠀ 挀漀渀猀琀 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀☀ ⤀㬀਀†  †  ⼀⼀℀†  愀猀猀椀最渀 漀瀀攀爀愀琀漀爀 昀漀爀戀椀搀搀攀渀⸀ 尀湎൑䆋롙൒㘀 ਀†  †  䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀 ☀漀瀀攀爀愀琀漀爀 㴀  ⠀ 挀漀渀猀琀 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀☀ ⤀㬀਀਀†  †public:
  †  †//!  †notification behavior. \n 通知行为
  †  †/*!  ਀†  †   ⨀†  琀漀 愀挀琀 渀漀琀椀昀椀挀愀琀椀漀渀 戀攀栀愀瘀椀漀爀Ⰰ  椀洀瀀氀攀洀攀渀琀 琀栀椀猀 洀攀琀栀漀搀 氀椀欀攀 琀栀椀猀㨀਀†  †   ⨀†  ਀†  †   ⨀† ⁛鹳낐᩷䱎㫿౎얗�㞑춏綋륬헿ᨀ਀†  †   ⨀†  ਀†  †   ⨀†  尀挀漀搀攀笀⸀挀瀀瀀紀਀†  †   ⨀†  笀਀†  †   ⨀†  †//notifiee, a object pointer 对象指针
  †  † *  †  ⼀⼀渀漀琀椀挀愀琀椀漀渀开戀攀栀愀瘀椀漀爀Ⰰ 愀 洀攀洀戀攀爀 洀攀琀栀漀搀 瀀漀椀渀琀攀爀⁢ၔ塥륬핣ޔ蠀਀†  †   ⨀†  †//para... , parameter list 参数列表
  †  † *  †  ⠀渀漀琀椀昀椀攀攀ⴀ㸀⨀渀漀琀椀挀愀琀椀漀渀开戀攀栀愀瘀椀漀爀⤀⠀ 瀀愀爀愀⸀⸀⸀ ⤀㬀਀†  †   ⨀†  紀਀†  †   ⨀†   尀攀渀搀挀漀搀攀਀†  †   ⨀†  †
  †  † */
  †  †virtual void notify() = 0;

  †  †//!  †get the notifier type. \n获取通知者类别
  †  †inline uint32 getNotifierType() const{
  †  †  爀攀琀甀爀渀 洀开渀漀琀椀昀椀攀爀吀礀瀀攀㬀਀†  †  紀਀਀†  †private:
  †  †const uint32 m_notifierType;
  †};

  紀਀紀⼀⼀渀愀洀攀猀瀀愀挀攀 䴀愀最渀愀਀਀⌀攀渀搀椀昀†/*  䄀䈀匀吀刀䄀䌀吀䔀䐀一伀吀䤀䘀䤀䔀刀开䠀†*/