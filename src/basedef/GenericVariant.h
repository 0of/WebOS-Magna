/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef GENERTICVARIANT_H
#define GENERTICVARIANT_H

#include "SystemDef.h"
#include "BaseTypes.h"
#include "CompilerTimeAssert.h"

#include "private\GenericVariant_p.h"

namespace Magna{  ਀† namespace Core{

  †/*!  尀戀爀椀攀昀਀†  †  䄀 最攀渀攀爀椀挀 瘀愀爀椀愀渀琀⹚†涘瀷鍙傛暟
  †  */
  †/*!  ਀†    ⨀†  䄀 最攀渀攀爀椀挀 瘀愀爀椀愀渀琀 挀愀渀 戀攀 甀猀攀搀 愀猀 愀 挀漀渀琀愀椀渀攀爀 琀漀 猀琀漀爀攀 漀戀樀攀挀琀⸀਀†    ⨀†  ਀†    ⨀†  圀栀攀渀 挀愀氀氀椀渀最 ⌀䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀⠀⤀ 琀栀攀 挀漀渀猀琀爀甀挀琀漀爀Ⰰ 礀漀甀 挀愀渀 椀渀瀀甀琀 琀栀攀 ਀†    ⨀†  椀渀猀琀愀渀挀攀 漀爀 瀀漀椀渀琀攀爀 愀猀 愀 瀀愀爀愀洀攀琀攀爀⸀਀†    ⨀਀†    ⨀†  夀漀甀 挀愀渀 最攀琀 琀栀攀 漀戀樀攀挀琀 昀爀漀洀 挀愀氀氀椀渀最 最攀琀嘀愀爀椀愀渀琀⠀⤀਀†    ⨀†  愀渀搀 椀琀✀氀氀 爀攀琀甀爀渀 愀 爀攀昀 猀栀愀爀攀搀 瀀漀椀渀琀攀爀 漀昀 琀栀攀 挀氀愀猀猀 椀昀 礀漀甀 椀渀瀀甀琀 愀 爀愀眀 瀀漀椀渀琀攀爀਀†    ⨀†  愀猀 琀栀攀 瀀愀爀愀洀攀琀攀爀㬀 漀琀栀攀爀眀椀猀攀 愀 挀漀渀猀琀 爀攀昀 椀渀猀琀愀渀挀攀 眀漀甀氀搀 戀攀 爀攀琀甀爀渀攀搀⸀਀†    ⨀਀†    ⨀†  圀栀攀渀 猀攀琀 琀栀攀 瘀愀爀椀愀渀琀 戀礀 挀愀氀氀椀渀最 猀攀琀嘀愀爀椀愀渀琀⠀⤀⸀਀†    ⨀†  椀昀†initialized one is raw pointer, you'd pass a shared pointer to a instance.
  †  *
  †  *  †Here's a example:
  †  *  †\code{.cpp}
  †  *  †  䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀吀礀瀀攀㰀吀攀猀琀 ⨀㸀 瘀愀爀⠀ 爀愀眀开瀀漀椀渀琀攀爀开琀漀开吀攀猀琀 ⤀㬀਀†    ⨀†  †SharedPtr<Test> pointer = var.getVariant();
  †  *  †  䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀吀礀瀀攀㰀吀攀猀琀㸀 瘀愀爀⠀ 愀渀开椀渀猀琀愀渀挀攀开漀昀开吀攀猀琀 ⤀㬀਀†    ⨀†  †const Test & t_test = var.getVariant();
  †  *  †\endcode
  †  *
  †  *  †\tparam  吀†can be a class or a pointer to a class
  †  *  †
  †  *  †\attention  䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀 眀椀氀氀 尀攀洀 吀愀欀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 爀愀眀 瀀漀椀渀琀攀爀਀†    ⨀†  尀愀琀琀攀渀琀椀漀渀†The raw pointer must point to a \em Heap allocated instance.
  †  * 
  †  *  †\author  †Magnus
  †  *  †\version   1.0.0.0
  †  *  †\date  †2013/1/10
  †  */
   †template<
  †  †  琀礀瀀攀渀愀洀攀 吀਀†  †  †, typename VariantPolicy = GenericVariantPolicy<T> 
  †  †  㸀਀†  挀氀愀猀猀 䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀 㨀 嘀愀爀椀愀渀琀倀漀氀椀挀礀笀਀†  †__Constructor_Destructor public:
  †  †//!  䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 愀 椀渀猀琀愀渀挀攀਀†  †  ⼀⨀℀†
  †  †  *  †\param  椀渀椀琀 椀昀 礀漀甀爀 琀攀洀瀀氀愀琀攀 瀀愀爀愀洀攀琀攀爀 椀猀 愀 瀀漀椀渀琀攀爀 ਀†  †    ⨀†  †then the init is a raw pointer
  †  †  *
  †  †  *  †\attention  䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀 眀椀氀氀 尀攀洀 吀愀欀攀 琀栀攀 漀眀渀攀爀猀栀椀瀀 漀昀 琀栀攀 爀愀眀 瀀漀椀渀琀攀爀਀†  †    ⨀†  尀愀琀琀攀渀琀椀漀渀†The raw pointer must point to a \em Heap allocated instance.
  †  †  */
  †  †explicit GenericVariant( const T& init )
  †  †  㨀嘀愀爀椀愀渀琀倀漀氀椀挀礀⠀ 椀渀椀琀 ⤀笀਀†  †  ਀†  †  紀਀†  †  ਀†  †  ⼀⼀℀†Copy constructor
  †  †/*!  ਀†  †    ⨀†  琀栀攀 椀渀猀琀愀渀挀攀 眀椀氀氀 戀攀 挀愀氀氀 琀栀攀 挀漀瀀礀 挀漀渀猀琀爀甀挀琀漀爀 愀猀 眀攀氀氀਀†  †    ⨀†  愀渀搀 挀漀瀀礀ⴀ昀漀爀戀椀搀搀攀渀 挀氀愀猀猀 眀椀氀氀 琀栀爀漀眀 愀 攀爀爀漀爀⸀਀†  †    ⨀⼀਀†  †  䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀⠀ 挀漀渀猀琀 䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀㰀吀㸀☀ 瘀愀爀椀愀渀琀 ⤀਀†  †  †:VariantPolicy( variant ){

  †  †}
  †  †
  †  †//!  䐀攀猀琀爀甀挀琀漀爀਀†  †  縀䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀⠀⤀笀਀਀†  †  紀਀਀†  †__Getter public:
  †  †//!  䜀攀琀 琀栀攀 挀漀渀猀琀 爀攀昀 椀渀猀琀愀渀挀攀⸀਀†  †  ⼀⨀℀†
  †  †  *  †\return const ref instance
  †  †  *  †  椀昀 琀栀攀 椀渀椀琀椀愀氀椀稀攀搀 琀礀瀀攀 椀猀 愀 爀愀眀 瀀漀椀渀琀攀爀Ⰰ 琀栀攀 爀攀琀甀爀渀 琀礀瀀攀 椀猀 匀栀愀爀攀搀倀琀爀਀†  †    ⨀⼀਀†  †  挀漀渀猀琀 琀礀瀀攀渀愀洀攀 嘀愀爀椀愀渀琀倀漀氀椀挀礀㨀㨀䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀吀礀瀀攀 ☀ 最攀琀嘀愀爀椀愀渀琀⠀⤀ 挀漀渀猀琀 笀਀†  †  †return m_instance;
  †  †}

  †  †//!  䜀攀琀 琀栀攀 爀攀昀 椀渀猀琀愀渀挀攀⸀਀†  †  ⼀⨀℀†
  †  †  *  †\return ref instance
  †  †  *  †  椀昀 琀栀攀 椀渀椀琀椀愀氀椀稀攀搀 琀礀瀀攀 椀猀 愀 爀愀眀 瀀漀椀渀琀攀爀Ⰰ 琀栀攀 爀攀琀甀爀渀 琀礀瀀攀 椀猀 匀栀愀爀攀搀倀琀爀਀†  †    ⨀⼀਀†  †  琀礀瀀攀渀愀洀攀 嘀愀爀椀愀渀琀倀漀氀椀挀礀㨀㨀䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀吀礀瀀攀 ☀ 最攀琀嘀愀爀椀愀渀琀⠀⤀笀਀†  †  †return m_instance;
  †  †}

  †  开开匀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†Set the variant with instance or SharedPtr
  †  †/*!  ਀†  †    ⨀†  尀瀀愀爀愀洀 椀渀猀琀愀渀挀攀 椀昀 琀栀攀 椀渀椀琀椀愀氀椀稀攀搀 琀礀瀀攀 椀猀 愀 爀愀眀 瀀漀椀渀琀攀爀Ⰰ 琀栀攀 椀渀猀琀愀渀挀攀 琀礀瀀攀 椀猀 匀栀愀爀攀搀倀琀爀਀†  †    ⨀⼀਀†  †  瘀漀椀搀 猀攀琀嘀愀爀椀愀渀琀⠀ 挀漀渀猀琀 琀礀瀀攀渀愀洀攀 嘀愀爀椀愀渀琀倀漀氀椀挀礀㨀㨀䜀攀渀攀爀椀挀嘀愀爀椀愀渀琀吀礀瀀攀☀ 椀渀猀琀愀渀挀攀 ⤀笀਀†  †  †m_instance = instance;
  †  †}
  †};

   紀⼀⼀䌀漀爀攀਀紀⼀⼀䴀愀最渀愀਀⌀攀渀搀椀昀†/*  䜀䔀一䔀刀吀䤀䌀嘀䄀刀䤀䄀一吀开䠀†*/