/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#ifndef MESSAGE_H
#define MESSAGE_H

#include "basedef_lib.h"

#include "SystemDef.h"
#include "BaseTypes.h"

namespace Magna{
   渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†   ⼀⨀℀†\brief
  †   †A abstracted message.
  †  †抽象消息
  †  */
  † /*!  尀搀攀琀愀椀氀猀਀†    ⨀†  ਀†    ⨀†  吀栀椀猀 挀氀愀猀猀 爀攀瀀爀攀猀攀渀琀猀 愀 甀渀椀瘀攀爀猀愀氀 洀攀猀猀愀最攀 琀礀瀀攀 昀漀爀 挀漀洀洀甀渀椀挀愀琀椀漀渀 甀猀椀渀最 椀渀 琀栀椀猀 昀爀愀洀攀眀漀爀欀⸀਀†    ⨀†  吀栀攀 洀攀猀猀愀最攀 挀愀渀 戀攀 挀愀琀攀最漀爀椀稀攀搀 椀渀琀漀 昀漀甀爀 琀礀瀀攀猀㨀 甀猀攀爀 洀攀猀猀愀最攀Ⰰ਀†    ⨀†  攀瘀攀渀琀 愀爀最甀洀攀渀琀 ⠀ 䄀戀猀琀爀愀挀琀攀搀䔀瘀攀渀琀䄀爀最猀 ⤀Ⰰ 渀漀琀椀昀椀攀爀 ⠀ 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀 ⤀Ⰰ 挀漀渀琀攀渀琀 瘀愀氀甀攀猀⸀਀†    ⨀†  ਀†    ⨀† ₋筎桷䁥瑎⩨䙧뚐᩵⡶葭衠潼筗诿౎㮉腵⡎躐᪋꼰Ȁ਀†    ⨀† ⁭衠潓َ㫿᩵⡢㝭衠漰Ŏ譎衠漀⠀ 䄀戀猀琀爀愀挀琀攀搀䔀瘀攀渀琀䄀爀最猀 ⤰Ɛ᩷Ԁ⠀ 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀 ⤀਀†    ⨀† ‰ő蕛륐㰰Ȁ਀†    ⨀†  ਀†    ⨀†  尀愀甀琀栀漀爀†Magnus
  †  *  †\version   1.0.0.1
  †  *  †\date  †2013/4/21
  †  */
  † __Abstracted class BASEDEF_LIB_EXPORT Message{
  †   开开䌀漀渀猀琀愀渀琀猀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†  洀攀猀猀愀最攀 琀礀瀀攀 攀渀甀洀⸀ 尀湭衠潼筒⭧驎㸀਀†  †  攀渀甀洀 䴀攀猀猀愀最攀吀礀瀀攀笀਀†  †  †MessageType_User = 0,  ⼀⨀℀㰀 甀猀攀爀 洀攀猀猀愀最攀⸀ 尀湵⡢㝭衠漀 ⨀⼀  ਀†  †  †MessageType_EventArgs = 1,  ⼀⨀℀㰀 攀瘀攀渀琀 愀爀最甀洀攀渀琀⸀ 尀湎譎衠漀 ⨀⼀  ਀†  †  †MessageType_Notifier = 2,  ⼀⨀℀㰀 渀漀琀椀昀椀攀爀 ⸀ 尀源᩷Ԁ ⨀⼀  ਀†  †  †MessageType_ContentValues = 3 /*!< content values. \n内容值 */  
  †  †};
  †  瀀爀漀琀攀挀琀攀搀㨀਀†  †  ⼀⼀℀†  䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 洀攀猀猀愀最攀 琀礀瀀攀 尀渀⁼筒⭎㩓쉥灶葧蒐⁑ﵥ瀀਀†  †  ⼀⨀℀†
  †  † *  † \param type
  †  † *  † if user inherits this class to create a new message type, this type value should be
  †  † *  †Message::MessageType_User or any other value which should not in existed types.   ਀†  †   ⨀†   尀湙艧鱵⡢㝾羋筧敛鹳끥끶葭衠潼筗诿౒ᦋ㱞钋㨀 䴀攀猀猀愀最攀㨀㨀䴀攀猀猀愀最攀吀礀瀀攀开唀猀攀爀⁢ᙦ⽑癎홐㳿ఀ਀†  †   ⨀†  ₋㱎൞钋㩝콛塗⡶葼筗謰Ȁ਀†  †   ⨀⼀਀†  †  攀砀瀀氀椀挀椀琀 䴀攀猀猀愀最攀⠀ 䴀攀猀猀愀最攀吀礀瀀攀 琀礀瀀攀 ⤀㬀਀਀†  †  ⼀⼀℀†  䌀漀瀀礀 䌀漀渀猀琀爀甀挀琀漀爀  尀渀⁙൒㙧蒐⁑ﵥ瀀਀†  †  䴀攀猀猀愀最攀⠀ 挀漀渀猀琀 䴀攀猀猀愀最攀☀ 洀攀猀猀愀最攀 ⤀㬀਀਀†  †public:
  †  †//!  †Destructor  \n 析构函数
  †  †virtual ~Message();

  †  †//!  †assign-operator. \n赋值操作符重载。
  †  †Message& operator = ( const Message& message );

  †  开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†  最攀琀 琀栀攀 洀攀猀猀愀最攀 琀礀瀀攀⸀ 尀溃띓홭衠潼筒⬰Ȁ਀†  †  椀渀氀椀渀攀 䴀攀猀猀愀最攀吀礀瀀攀 最攀琀䴀攀猀猀愀最攀吀礀瀀攀⠀⤀ 挀漀渀猀琀笀਀†  †  †return m_messageType;
  †  †}

  †  开开䐀愀琀愀开䘀椀攀氀搀 瀀爀椀瘀愀琀攀㨀਀†  †  䴀攀猀猀愀最攀吀礀瀀攀 洀开洀攀猀猀愀最攀吀礀瀀攀㬀਀†  †  猀椀渀琀㌀㈀ 洀开琀愀最嘀愀氀甀攀㬀਀†   紀㬀਀† }//Core
}//Magna
#endif  ⼀⨀†MESSAGE_H  ⨀⼀�