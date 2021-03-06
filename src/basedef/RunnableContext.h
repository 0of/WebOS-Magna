/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#ifndef RUNNABLECONTEXT_H
#define RUNNABLECONTEXT_H

#include "basedef_lib.h"

#include "SystemDef.h"
#include "BaseTypes.h"

#include "Message.h"
#include "SharedPtr.h"
#include "Trigger.h"
#include "String.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  ⼀⨀℀†  尀戀爀椀攀昀਀†  †  䄀 爀甀渀渀愀戀氀攀 挀漀渀琀攀砀琀⸀⁓킈䱶葎੎୥蜀਀†   ⨀⼀਀†  ⼀⨀℀†  尀搀攀琀愀椀氀猀਀†   ⨀†
  † *  †A runnable context is a kind of run behavior which contains a
  † *  †event queue and a event looper and can receive messages and
  † *  †process messages sequentially. 
  † *  †
  † *  †一个可运行的上下文在语义上是一种运行的行为。该上下文包括消息队列和消息循环。
  † *  †可以朠⁞轣ꕥ㙙Ѵ٭衠漰Ȁ਀†   ⨀ ਀†   ⨀†  刀甀渀渀愀戀氀攀 挀漀渀琀攀砀琀 挀愀渀 戀攀 搀攀攀洀攀搀 愀猀 愀 瀀爀漀挀攀猀猀 眀栀椀挀栀 挀愀渀 栀愀猀 瀀愀爀攀渀琀 ਀†   ⨀†  瀀爀漀挀攀猀猀 愀渀搀 栀愀猀 椀琀猀 漀眀渀 洀攀猀猀愀最攀 洀攀挀栀愀渀椀猀洀 愀渀搀 挀愀渀 瀀爀漀挀攀猀猀 洀攀猀猀愀最攀猀⸀਀†   ⨀†  刀甀渀渀愀戀氀攀 挀漀渀琀攀砀琀 愀氀猀漀 挀愀渀 栀愀猀 瀀愀爀攀渀琀 Ⰰ眀栀椀挀栀 洀攀愀渀猀 椀昀 瀀愀爀攀渀琀 焀甀椀琀猀 愀氀氀 椀琀猀 ਀†   ⨀†  挀栀椀氀搀爀攀渀 眀椀氀氀 焀甀椀琀 愀甀琀漀洀愀琀椀挀愀氀氀礀⸀਀†   ⨀†  ਀†   ⨀†  ਀†   ⨀†  ਀†   ⨀†  圀栀攀渀 爀甀渀渀椀渀最Ⰰ 攀愀挀栀 挀漀渀琀攀砀琀 眀椀氀氀 猀琀愀爀琀 愀 椀渀昀椀渀椀琀攀 氀漀漀瀀 愀渀搀 椀琀✀氀氀 愀甀琀漀洀愀琀椀挀愀氀氀礀 ਀†   ⨀†  昀攀琀挀栀 洀攀猀猀愀最攀 昀爀漀洀 洀攀猀猀愀最攀 焀甀攀甀攀 愀渀搀 瀀爀漀挀攀猀猀 攀愀挀栀 洀攀猀猀愀最攀⸀ 圀栀攀渀 琀栀攀爀攀਀†   ⨀†  愀爀攀 渀漀 洀漀爀攀 洀攀猀猀愀最攀猀Ⰰ 挀甀爀爀攀渀琀 琀栀爀攀愀搀 眀椀氀氀 猀甀猀瀀攀渀搀⸀ 圀栀攀渀 愀渀礀 洀攀猀猀愀最攀 ਀†   ⨀†  愀爀爀椀瘀攀猀Ⰰ 琀栀攀 琀栀爀攀愀搀 眀椀氀氀 眀愀欀攀 甀瀀⸀ ਀†   ⨀†  ਀†   ⨀†  夀漀甀 挀愀渀 猀琀愀爀琀 爀甀渀渀椀渀最 眀椀琀栀 爀甀渀⠀⤀ 愀渀搀 瀀漀猀琀 洀攀猀猀愀最攀 眀椀琀栀 瀀漀猀琀䴀攀猀猀愀最攀⠀⤀⸀਀†   ⨀†  吀栀攀爀攀✀爀攀 琀眀漀 渀漀爀洀愀氀 眀愀礀猀 琀漀 猀栀甀琀搀漀眀渀 ⴀⴀ 愀戀漀甀琀吀漀匀栀甀琀䐀漀眀渀⠀⤀ 愀渀搀 椀渀猀琀愀渀琀氀礀匀栀甀琀䐀漀眀渀⠀⤀⸀਀†   ⨀†  愀戀漀甀琀吀漀匀栀甀琀䐀漀眀渀⠀⤀ 洀攀愀渀猀 猀琀漀瀀 琀栀攀 氀漀漀瀀 琀椀氀氀 愀氀氀 琀栀攀 洀攀猀猀愀最攀猀 愀爀攀 最漀渀攀 Ⰰ眀栀椀氀攀 椀渀猀琀愀渀琀氀礀匀栀甀琀䐀漀眀渀⠀⤀਀†   ⨀†  眀椀氀氀 猀琀漀瀀 琀栀攀 氀漀漀瀀 椀洀洀攀搀椀愀琀攀氀礀 戀攀昀漀爀攀 琀栀攀 洀攀猀猀愀最攀 椀猀 最漀椀渀最 琀漀 瀀爀漀挀攀猀猀 漀爀 琀栀攀 挀甀爀爀攀渀琀 洀攀猀猀愀最攀਀†   ⨀†  栀愀猀 搀漀渀攀 瀀爀漀挀攀猀猀椀渀最⸀਀†   ⨀†  ਀†   ⨀†  ਀†   ⨀ ਀†   ⨀†  尀愀甀琀栀漀爀†Magnus
  † *  †\version   1.0.0.0
  † *  †\date  †2013/4/25
  † */
  †class BASEDEF_LIB_EXPORT RunnableContext{
  †  昀爀椀攀渀搀 挀氀愀猀猀 刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀䄀挀挀攀猀猀漀爀㬀਀਀†  †protected:
  †  †TRIGGER_DEF(OnceRun)  ⼀⨀℀㰀 尀攀洀 吀爀椀最最攀爀 漀渀挀攀 爀甀渀 椀琀✀氀氀 琀爀椀最最攀爀猀⸀ 尀渀⁎e킈䱒᥏᪉터Ȁ ⨀⼀  †
  †  †TRIGGER_DEF(OnceShutDown)  ⼀⨀℀㰀  尀攀洀 吀爀椀最最攀爀 漀渀挀攀 猀栀甀琀搀漀眀渀 椀琀✀氀氀 琀爀椀最最攀爀猀⸀ 尀渀⁎e屫抏킈䱒᥏᪉터Ȁ ⨀⼀  ਀਀†  †protected:
  †  †//!  †constructor with context name. \n 上下文名字为参数的构造函数。
  †  †/*!  ਀†  †   ⨀†  尀瀀愀爀愀洀 渀愀洀攀਀†  †   ⨀†  挀漀渀琀攀砀琀 渀愀洀攀਀†  †   ⨀† ⁎੎୥蝔൛圀਀†  †   ⨀†  ਀†  †   ⨀†  尀猀愀 刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀⠀挀漀渀猀琀 匀琀爀椀渀最☀Ⰰ挀漀渀猀琀 匀栀愀爀攀搀倀琀爀㰀刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀㸀☀⤀਀†  †   ⨀⼀਀†  †  攀砀瀀氀椀挀椀琀 刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀⠀ 挀漀渀猀琀 匀琀爀椀渀最☀ 渀愀洀攀 ⤀㬀਀਀†  †  ⼀⼀℀†  挀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 挀漀渀琀攀砀琀 渀愀洀攀 愀渀搀 挀漀渀琀攀砀琀 瀀愀爀攀渀琀⸀ 尀渀⁎੎୥蝔൛坎쩲㙎੎୥蝎㩓쉥灶葧蒐⁑ﵥ瀰Ȁ਀†  †  ⼀⨀℀†
  †  † *  †\param name
  †  † *  †context name
  †  † *  †上下文名字
  †  † *  †
  †  † *  †\param parent
  †  † *  †if put null shared pointer, the context will be independently running.
  †  † *  †if parent context not null, when parent context shutdown the children of it all will
  †  † *  †shutdown.
  †  † *  †如果为空的共享指针，则该上下文则为独立运行的。
  †  † *  †如果父上下文不为空，则当父上下文停止运行时，其子上下文都将停止。
  †  † *  †
  †  † *  †\sa RunnableContext(const String&)
  †  † */
  †  †explicit RunnableContext( const String& name ,const SharedPtr<RunnableContext>& parent );
  †  ਀†  †public:
  †  †//!  †copy-constructor. \n复制构造
  †  †RunnableContext( const RunnableContext& );
  †  †//!  䐀攀猀琀爀甀挀琀漀爀⸀ 尀湧遧葑ﵥ瀀਀†  †  瘀椀爀琀甀愀氀 縀刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀⠀⤀㬀਀਀†  †public:
  †  †//!  †post message to the message queue. \n发送消息给消息队列
  †  †/*!  ਀†  †   ⨀†   椀昀 琀栀攀 挀漀渀琀攀砀琀 椀猀 渀漀琀 爀甀渀渀椀渀最Ⰰ 琀栀攀 洀攀猀猀愀最攀 眀椀氀氀 戀攀 愀戀愀渀搀漀渀攀搀⸀਀†  †   ⨀†   ਀†  †   ⨀† ⁙艧鱧⩗⢏킈䳿౭衠潓쉥灜ُ᪈ꮐ坟̰Ȁ਀†  †   ⨀†  ਀†  †   ⨀†  尀瀀愀爀愀洀 洀攀猀猀愀最攀਀†  †   ⨀†  愀 䴀攀猀猀愀最攀 猀栀愀爀攀搀 瀀漀椀渀琀攀爀⸀ ਀†  †   ⨀†  椀昀 琀栀攀 洀攀猀猀愀最攀 椀猀 愀 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀Ⰰ 椀琀✀氀氀 愀挀琀 渀漀琀椀昀椀挀愀琀椀漀渀 眀栀攀渀 瀀爀漀挀攀猀猀椀渀最 琀栀攀 洀攀猀猀愀最攀਀†  †   ⨀†  Ⰰ椀⸀攀 椀琀✀氀氀 挀愀氀氀 琀栀攀 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀⌀渀漀琀椀昀礀⠀⤀⸀ ਀†  †   ⨀† ⁎N⨀ 䴀攀猀猀愀最救煎ꭣޔ蠀਀†  †   ⨀† ⁙艧鲋衠潦⼀ 䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀牼筗诿౒᥏ᩗ⡙Ѵ٭衠潥枈䲐᩷蒈䱎㫿ఀ਀†  †   ⨀† ⁎彜ㅦ⾌͵⠀  䄀戀猀琀爀愀挀琀攀搀一漀琀椀昀椀攀爀⌀渀漀琀椀昀礀⠀⤀⁥륬픰Ȁ਀†  †   ⨀⼀਀†  †  瘀漀椀搀 瀀漀猀琀䴀攀猀猀愀最攀⠀ 挀漀渀猀琀 匀栀愀爀攀搀倀琀爀㰀䴀攀猀猀愀最攀㸀☀ 洀攀猀猀愀最攀 ⤀㬀਀਀†  †protected:
  †  †//!  †runs the context.  尀溏킈䲋੎୥蜀਀†  †  ⼀⨀℀†
  †  † *  †When calling this, it'll enter the infinite loop 
  †  † *  †and start to process messages. It'll never quit unless
  †  † *  †call aboutToShutDown(), instantlyShutDown() or processing
  †  † *  †quiting message or its parent shutting down(if has one). When the context is shutting down,
  †  † *  †this method will returns a exit code.
  †  † *  †
  †  † *  †当调用该方法时，将会进入一个无限循环，开始处理消息。
  †  † *  †除非调用 aboutToShutDown()、 instantlyShutDown() 或是处理退出消息或是
  †  † *  †其父上下文退出（如果存在＠⃿౔♒ᦋ륬한َ൏᪐Q侮Ȁ਀†  †   ⨀†  压륬햐Q贈᪏푖�N⪐Q祖㰰Ȁ਀†  †   ⨀†  ਀†  †   ⨀†  尀爀攀琀甀爀渀 愀 攀砀椀琀 挀漀搀攀਀†  †   ⨀†  　 椀猀 伀䬀⸀਀†  †   ⨀†  尀源Q喝ǿఀて⽥ᦋQ侮Ȁ਀†  †   ⨀†  ਀†  †   ⨀⼀਀†  †  甀椀渀琀㌀㈀ 爀甀渀⠀⤀㬀਀†  †  ⼀⼀℀†  愀戀漀甀琀 琀漀 焀甀椀琀⸀ 尀湓獜ڐQ切਀†  †  ⼀⨀℀†
  †  † *  †The context will quit if all the message has been processed.
  †  † *  †if not running, do nothing.
  †  † *  †
  †  † *  †上下文将退出当所朠⁭衠澈ꭙѴٛ谰Ȁ਀†  †   ⨀† ⁙艧鱬ꅗ⢏킈䳿౒᥎൏ᩐ婎ﭏ啎謰Ȁ਀†  †   ⨀⼀਀†  †  瘀漀椀搀 愀戀漀甀琀吀漀匀栀甀琀䐀漀眀渀⠀⤀㬀਀਀†  †  ⼀⼀℀†  焀甀椀琀 椀渀猀琀愀渀琀氀礀⸀ 尀湺쭓玐Q切਀†  †  ⼀⨀℀†
  †  † *  †The context will quit instantly.
  †  † *  †In other words,  the loop will quit before a new message is about to 
  †  † *  †process or after a message has been processed.
  †  † *  †if not running, do nothing.
  †  † *  †
  †  † *  †上下文立即退出。
  †  † *  †换句话说，在新的消息即将处理之前或是处理完一个消息后该循环退出。
  †  † *  †如果没在运行，则不会做任何事。
  †  † */
  †  †void instantlyShutDown();

  †  瀀甀戀氀椀挀㨀਀†  †  挀氀愀猀猀 刀甀渀渀愀戀氀攀䌀漀渀琀攀砀琀䔀渀琀椀琀礀㬀਀†  †protected:
  †  †SharedPtr<RunnableContextEntity> m_entity;
  †};

  紀਀紀⼀⼀渀愀洀攀猀瀀愀挀攀 䴀愀最渀愀਀਀⌀攀渀搀椀昀†/*  刀唀一一䄀䈀䰀䔀䌀伀一吀䔀堀吀开䠀†*/