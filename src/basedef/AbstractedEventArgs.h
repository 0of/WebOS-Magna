/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2013 by Magnus
  */

#ifndef ABSTRACTEDEVENTARGS_H
#define ABSTRACTEDEVENTARGS_H

#include "basedef_lib.h"

#include "BaseTypes.h"
#include "SystemDef.h"

#include "Message.h"

namespace Magna{
   渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†   ⼀⨀℀†\brief
  †   †This class represents the abstract event argument.
  †  †抽象事件参数
  †  */
  †   /*!
  †  ⨀†AbstractedEventArgs is an abstracted class for event argument,
  †  ⨀†which is also a derived class of #Message.
  †  ⨀਀†  †*  䄀戀猀琀爀愀挀琀攀搀䔀瘀攀渀琀䄀爀最猀⁎㩢붌慶葎譎쉥烿౔౥彦⼀ 䴀攀猀猀愀最敶葛偼笰Ȁ਀†  †*
  †  ⨀†Every abstracted event argument has several properties: acceptance
  †  ⨀†,which is a flag indicating the event argument should be pass to other receivers or not
  †  ⨀†and can be modified by accept() or refuse() and can be checked by isAccepted() or isRefused().
  †  ⨀†,transmissible, which is a flag telling the event argument can recursively pass to receiver children.
  †  ⨀†,flags, which is reserved for other uses
  †  ⨀†,type, which would be the identifier of a event argument and can be accessed by getType()
  †  ⨀†and user can assign it with user value.
  †  ⨀਀†  †* ⁫콎⩢붌慶葎譎쉥炐ﵧ†这些属性：acceptance，该标志表名是否传递给其他的接受者，
  †  ⨀†也能通过 accept() （接收＠⁢ᘀ 爀攀昀甀猀攀⠀⤀⃿ࡢ퉾�†进行修改，同时也可以调用 isAccepted() 或isRefused()
  †  ⨀†来判别。transmissible， 该标志标志着该事件参数是否能递归传递给接受者。flags，为保留参数。
  †  ⨀†type， 为事件参数所表达的事件类型，可以通过getType()来访问，用户也可以赋予自定义的用户值。
  †  ⨀਀†  †*   尀愀甀琀栀漀爀†Magnus
  †  ⨀† \version  1.0.0.0
  †  ⨀   尀搀愀琀攀      ㈀　㄀㌀⼀㌀⼀㄀㐀਀†  †*/
  † __Abstracted class BASEDEF_LIB_EXPORT AbstractedEventArgs : public Message{
  †   开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀爀漀琀攀挀琀攀搀㨀਀਀†  †  ⼀⼀℀†Constructor with event type \n 事件类别为参数的构造函数
  †  †/*!
  †  †  *
  †  †  *  †\param  eventType
  †  †  *  †event type, user can assign for identifying user's event ,and also can assign
  †  †  *  †system existed event type.
  †  †  *  †\n事件类别，用户可以设置用户自定义的事件类别来判别用户事件，当然也可以设置系统已存在的事件类别
  †  †  *
  †  †  *  †\param  isTransmissible
  †  †  *  †a flag, if true(default) ,   眀栀椀挀栀 洀攀愀渀猀 琀栀攀 攀瘀攀渀琀 愀爀最甀洀攀渀琀 挀愀渀 爀攀挀甀爀猀椀瘀攀氀礀 瀀愀猀猀 琀漀 爀攀挀攀椀瘀攀爀 挀栀椀氀搀爀攀渀⸀਀†  †    ⨀†  尀湎N⩨ݟ휰ə艧鱎㩷῿࢞�ꑶ蓿†，表明事件参数可以被递归传递给其他接收者。
  †  †  */
  †  †explicit AbstractedEventArgs( uint16 eventType, bool isTransmissible = true );

  †  †//!  †Copy Constructor  \n 复制构造函数
  †  †AbstractedEventArgs( const AbstractedEventArgs& absArgs );
  †  瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†  䐀攀猀琀爀甀挀琀漀爀  尀渀⁧遧葑ﵥ瀀਀†  †  瘀椀爀琀甀愀氀 縀 䄀戀猀琀爀愀挀琀攀搀䔀瘀攀渀琀䄀爀最猀⠀⤀ 㴀 　㬀਀†  †public:
  †  †//!  †accept the event. \n 接受该事件
  †  †/*!
  †  † *  †if accept the event, the event argument can pass to other receivers.
  †  † *  †Besides, the default state is accepted.
  †  † *
  †  † *  †如果接收该事件，该事件参数即可传递给其他接受者。
  †  † *  †默认为接收的。
  †  † *  †\sa refuse() , isAccepted()
  †  † */
  †  †void accept();

  †  †//!  †refuse the event. \n 拒绝该事件
  †  †/*!
  †  †  *  †this event argument will stop passing to other receivers
  †  †  *  †when user call this method. In other words, if user refuse
  †  †  *  †the event in event processing one scope, other processing
  †  †  *  †scope will never jump into.
  †  †  *  †This can use for event filtering.
  †  †  *
  †  †  *  †当用户调用该方法的时候，事件将停止传递。
  †  †  *  †也就是说，当用户在某个处理事件的作用域调用该方法后，其他的处理
  †  †  *  †事件作用域将不可能访问到。
  †  †  *  †往往可以用来作事件过滤。
  †  †  *
  †  †  *  †\sa accept() , isRefused()
  †  †  */
  †  †void refuse();

  †  †//!  †get the event type. \n获取事件类别。
  †  †inline uint16 getType() { return m_type; }

  †  开开䌀栀攀挀欀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†  挀栀攀挀欀 椀猀 愀挀挀攀瀀琀攀搀 尀湒⑥굦⽔♎㩣ꕓ흶萰Ȁ਀†  †  戀漀漀氀 椀猀䄀挀挀攀瀀琀攀搀⠀⤀ 挀漀渀猀琀 笀 爀攀琀甀爀渀 洀开愀挀挀攀瀀琀愀渀挀攀㬀 紀਀†  †  ⼀⼀℀†  挀栀攀挀欀 椀猀 爀攀昀甀猀攀搀 尀湒⑥굦⽔♎㩢퉾�萰Ȁ਀†  †  戀漀漀氀 椀猀刀攀昀甀猀攀搀⠀⤀ 挀漀渀猀琀 笀 爀攀琀甀爀渀 ℀洀开愀挀挀攀瀀琀愀渀挀攀㬀 紀਀਀†  †__Overloaded_Methods public:
  †  †//!  †assign-operator. \n赋值操作符重载。
  †  †AbstractedEventArgs & operator = ( const AbstractedEventArgs& absArgs );

  †  †//!  †check two event argument is equal. \n比较事件参数是否相同
  †  †bool operator == ( const AbstractedEventArgs& absArgs ){
  †  †  爀攀琀甀爀渀 洀开琀礀瀀攀 㴀㴀 愀戀猀䄀爀最猀⸀洀开琀礀瀀攀㬀਀†  †  紀਀†  †  ⼀⼀℀†  挀栀攀挀欀 琀眀漀 攀瘀攀渀琀 愀爀最甀洀攀渀琀 椀猀 渀漀琀 攀焀甀愀氀⸀ 尀湫풏荎譎쉥灦⽔♎൶ఀ਀†  †  戀漀漀氀 漀瀀攀爀愀琀漀爀 ℀㴀  ⠀ 挀漀渀猀琀 䄀戀猀琀爀愀挀琀攀搀䔀瘀攀渀琀䄀爀最猀☀ 愀戀猀䄀爀最猀 ⤀笀਀†  †  †return m_type != absArgs.m_type;
  †  †}

  †  开开䐀愀琀愀开䘀椀攀氀搀 瀀爀漀琀攀挀琀攀搀㨀਀†  †  甀椀渀琀㄀㘀 洀开愀挀挀攀瀀琀愀渀挀攀 㨀 ㄀㬀਀†  †  甀椀渀琀㄀㘀 洀开椀猀吀爀愀渀猀洀椀猀猀椀戀氀攀 㨀 ㄀㬀਀†  †  甀椀渀琀㄀㘀 洀开昀氀愀最猀 㨀 ㄀㐀㬀਀†  †  甀椀渀琀㄀㘀 洀开琀礀瀀攀㬀਀†   紀㬀਀† }//Core
}//Magna
#endif  ⼀⨀†ABSTRACTEDEVENTARGS_H  ⨀⼀�