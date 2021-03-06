/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2013 by Magnus
  */
#ifndef SIZE_H
#define SIZE_H

#include "basedef_lib.h"
#include "Comparer.h"

#include "private/Size_p.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀ഀ਀†  ⼀⨀℀†\brief
  †  †A class with property width and height.
  †  †具朠⁛뵔貚�幠❶葼笰Ȁഀ਀†    ⨀⼀ഀ਀†  ⼀⨀℀ഀ਀†    ⨀†  䔀愀挀栀 猀椀稀攀 栀愀猀 眀椀搀琀栀 愀渀搀 栀攀椀最栀琀 愀渀搀 礀漀甀 挀愀渀 椀渀椀琀椀愀氀椀稀攀 漀渀攀 眀椀琀栀 琀栀漀猀攀 瀀爀漀瀀攀爀琀椀攀猀⸀ഀ਀†    ⨀†  ⌀匀椀稀攀⠀⤀ 愀渀搀 琀栀攀 眀椀搀琀栀 愀渀搀 栀攀椀最栀琀 挀愀渀 戀攀 渀攀最愀琀椀瘀攀Ⰰ 戀甀琀 礀漀甀✀搀 戀攀琀琀攀爀 渀漀琀 猀攀琀 琀栀攀洀 戀攀 渀攀最愀琀椀瘀攀⸀ഀ਀†    ⨀ഀ਀†    ⨀†  䄀渀搀 最攀琀琀攀爀猀 氀椀欀攀 最攀琀圀椀搀琀栀⠀⤀Ⰰ 最攀琀䠀攀椀最栀琀⠀⤀ 挀愀渀 栀攀氀瀀 礀漀甀 最攀琀 琀栀攀 瘀愀氀甀攀 漀昀 琀栀攀 瀀爀漀瀀攀爀琀礀⸀ഀ਀†    ⨀†  䈀攀猀椀搀攀猀 猀漀洀攀 漀昀昀猀攀琀 昀甀渀挀琀椀漀渀猀 挀愀渀 戀攀 甀猀攀搀 愀猀 洀漀搀椀昀椀攀爀 琀漀 洀漀搀椀昀礀 琀栀攀 瘀愀氀甀攀猀ഀ਀†    ⨀ഀ਀†    ⨀†  䘀漀爀 挀漀漀爀搀椀渀愀琀攀 漀爀 猀漀洀攀 猀栀愀瀀攀猀 吀漀ⴀ洀攀琀栀漀搀 漀爀 䈀礀ⴀ洀攀琀栀漀搀 琀栀攀 瘀攀爀戀 眀攀 甀猀攀搀 椀猀 ∀琀爀愀渀猀氀愀琀攀∀ഀ਀†    ⨀†  䈀甀琀 昀漀爀 猀椀稀攀 眀攀 甀猀攀 ∀漀昀昀猀攀琀∀⸀ഀ਀†    ⨀ഀ਀†    ⨀†  尀琀瀀愀爀愀洀 吀†can be in float, double, sint32 for the x and y type
  †  *  †\attention  琀栀攀 吀 洀甀猀琀 戀攀 椀渀 昀氀漀愀琀Ⰰ 搀漀甀戀氀攀 漀爀 猀椀渀琀㌀㈀ഀ਀†    ⨀†  †  †otherwise the compiler will throw a error.
  †  *
  †  *  †\author  †Magnus
  †  *  †\version   1.0.0.0
  †  *  †\date  †2012/12/27
  †  */
  †template<typename T, typename Policy = SizePolicy<T> >
  †class BASEDEF_LIB_EXPORT Size : Policy{

  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Default constructor
  †  †Size() : Policy(){ }

  †  †//!  䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 眀椀搀琀栀 愀渀搀 栀攀椀最栀琀ഀ਀†  †  攀砀瀀氀椀挀椀琀 匀椀稀攀⠀ 挀漀渀猀琀 吀☀ 眀椀搀琀栀Ⰰ 挀漀渀猀琀 吀☀  栀攀椀最栀琀⤀ 㨀 倀漀氀椀挀礀 ⠀ 眀椀搀琀栀 Ⰰ栀攀椀最栀琀 ⤀ 笀 紀ഀ਀ഀ਀†  †  ⼀⼀℀†Constructor with same width and height
  †  †explicit Size( const T& square ) : Policy( square, square ) { }

  †  †//! A destructor.
  †  †~Size() { }

  †  开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Get width value
  †  †inline T getWidth() const { return Policy::m_width; }
  †  †//!  䜀攀琀 栀攀椀最栀琀 瘀愀氀甀攀ഀ਀†  †  椀渀氀椀渀攀 吀 最攀琀䠀攀椀最栀琀⠀⤀ 挀漀渀猀琀 笀 爀攀琀甀爀渀 倀漀氀椀挀礀㨀㨀洀开栀攀椀最栀琀㬀 紀ഀ਀ഀ਀†  †__Setter public:
  †  †//!  匀攀琀 眀椀搀琀栀 瘀愀氀甀攀ഀ਀†  †  椀渀氀椀渀攀 瘀漀椀搀 猀攀琀圀椀搀琀栀⠀ 挀漀渀猀琀 吀☀ 眀椀搀琀栀 ⤀笀 倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 㴀 眀椀搀琀栀㬀 紀ഀ਀†  †  ⼀⼀℀†Set height value
  †  †inline void setHeight( const T& height ){ Policy::m_height = height; }

  †  开开䈀礀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 樀漀椀渀攀搀䈀礀⠀ 挀漀渀猀琀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 猀椀稀攀 ⤀笀ഀ਀†  †  †if( Policy::m_width < size.Policy::m_width ){
  †  †  †Policy::m_width = size.Policy::m_width;
  †  †  紀ഀ਀ഀ਀†  †  †if( Policy::m_height < size.Policy::m_height ){
  †  †  †Policy::m_height = size.Policy::m_height;
  †  †  紀ഀ਀†  †  †return *this;
  †  †}

  †  †//!  圀椀搀琀栀 愀渀搀 栀攀椀最栀琀 愀氀氀 漀昀昀猀攀琀 戀礀 漀昀昀猀攀琀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 漀昀昀猀攀琀䈀礀䈀漀琀栀⠀ 挀漀渀猀琀 吀☀ 漀昀昀猀攀琀 ⤀笀ഀ਀†  †  †Policy::m_height += offset;
  †  †  倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⬀㴀 漀昀昀猀攀琀㬀ഀ਀†  †  †return *this;
  †  †}
  †  †//!  圀椀搀琀栀 漀昀昀猀攀琀 戀礀 眀椀搀琀栀伀昀昀猀攀琀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 漀昀昀猀攀琀䈀礀圀椀搀琀栀⠀ 挀漀渀猀琀 吀☀ 眀椀搀琀栀伀昀昀猀攀琀 ⤀笀ഀ਀†  †  †Policy::m_width += widthOffset;
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Height offset by heightOffset
  †  †inline Size<T,Policy>& offsetByHeight( const T& heightOffset ){
  †  †  倀漀氀椀挀礀㨀㨀洀开栀攀椀最栀琀 ⬀㴀 栀攀椀最栀琀伀昀昀猀攀琀㬀ഀ਀†  †  †return *this;
  †  †}

  †  开开吀漀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Get a new Size with both shifted by the same value
  †  †inline Size<T,Policy> offsetsToBoth( const T& offset ){
  †  †  爀攀琀甀爀渀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀⠀ 倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⬀ 漀昀昀猀攀琀 Ⰰ 倀漀氀椀挀礀㨀㨀洀开栀攀椀最栀琀 ⬀ 漀昀昀猀攀琀⤀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Get a new Size with shifted by the each value
  †  †inline Size<T,Policy> offsetsToEach( const T& widthOffset, const T& heightOffset ){
  †  †  爀攀琀甀爀渀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀⠀倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⬀ 眀椀搀琀栀伀昀昀猀攀琀Ⰰ  倀漀氀椀挀礀㨀㨀洀开栀攀椀最栀琀 ⬀ 栀攀椀最栀琀伀昀昀猀攀琀⤀㬀ഀ਀†  †  紀ഀ਀ഀ਀†  †__Checker public:
  †  †//!  䌀栀攀挀欀 琀栀攀 猀椀稀攀 椀猀 瘀愀氀椀搀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 椀昀 眀椀搀琀栀 漀爀 栀攀椀最栀琀 椀猀 氀漀眀攀爀 琀栀愀渀 稀攀爀漀ഀ਀†  †    ⨀†  爀攀琀甀爀渀猀 琀甀爀攀 漀琀栀攀爀眀椀猀攀 昀愀氀猀攀⸀ഀ਀†  †    ⨀⼀ഀ਀†  †  椀渀氀椀渀攀 戀漀漀氀 椀猀嘀愀氀椀搀⠀⤀ 挀漀渀猀琀 笀 爀攀琀甀爀渀 ℀䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䰀漀眀攀爀吀栀愀渀娀攀爀漀⠀ 倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⤀ഀ਀†  †  †&& !Comparer<T>::isLowerThanZero( Policy::m_height ) ;}

  †  开开伀瘀攀爀氀漀愀搀攀搀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Assign operator
  †  †inline Size<T,Policy>& operator = ( const Size<T,Policy>& size ){
  †  †  倀漀氀椀挀礀㨀㨀漀瀀攀爀愀琀漀爀㴀⠀ 猀椀稀攀 ⤀㬀ഀ਀†  †  †return *this;
  †  †}
  †  †//!  䌀栀攀挀欀 琀眀漀 猀椀稀攀猀 愀爀攀 攀焀甀愀氀ഀ਀†  †  椀渀氀椀渀攀 戀漀漀氀 漀瀀攀爀愀琀漀爀 㴀㴀 ⠀ 挀漀渀猀琀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 猀椀稀攀 ⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Comparer<T>::isEqualTo( Policy::m_width, size.Policy::m_width )
  †  †  †&& Comparer<T>::isEqualTo( Policy::m_height, size.Policy::m_height );
  †  †}
  †  †//!  䌀栀攀挀欀 琀眀漀 猀椀稀攀猀 愀爀攀 渀漀琀 攀焀甀愀氀ഀ਀†  †  椀渀氀椀渀攀 戀漀漀氀 漀瀀攀爀愀琀漀爀 ℀㴀  ⠀ 挀漀渀猀琀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 猀椀稀攀 ⤀ 挀漀渀猀琀笀ഀ਀†  †  †return (!Comparer<T>::isEqualTo( Policy::m_width, size.Policy::m_width ) )
  †  †  †|| (!Comparer<T>::isEqualTo( Policy::m_height, size.Policy::m_height ) );
  †  †}

  †  †//!  䜀攀琀 愀 渀攀眀 猀椀稀攀 眀椀琀栀 眀椀搀琀栀 愀渀搀 栀攀椀最栀琀 洀甀氀琀椀瀀氀椀攀搀 戀礀 昀愀挀琀漀爀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀 漀瀀攀爀愀琀漀爀 ⨀ ⠀ 挀漀渀猀琀 昀氀漀愀琀☀ 昀愀挀琀漀爀 ⤀笀ഀ਀†  †  †return Size( Policy::m_width * factor, Policy::m_height * factor );
  †  †}
  †  †//!  䜀攀琀 愀 渀攀眀 猀椀稀攀 眀椀琀栀 眀椀搀琀栀 愀渀搀 栀攀椀最栀琀 搀椀瘀椀搀攀搀 戀礀 昀愀挀琀漀爀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀 漀瀀攀爀愀琀漀爀 ⼀ ⠀ 挀漀渀猀琀 昀氀漀愀琀☀ 昀愀挀琀漀爀 ⤀笀ഀ਀†  †  †return Size(Policy::m_width / factor ,  Policy::m_height / factor);
  †  †}
  †  †//!  圀椀搀琀栀 愀渀搀 栀攀椀最栀琀 洀甀氀琀椀瀀氀椀攀搀 戀礀 昀愀挀琀漀爀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 漀瀀攀爀愀琀漀爀 ⨀㴀 ⠀ 挀漀渀猀琀 昀氀漀愀琀☀ 昀愀挀琀漀爀 ⤀笀ഀ਀†  †  †Policy::m_height *= factor;
  †  †  倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⨀㴀 昀愀挀琀漀爀㬀ഀ਀†  †  †return *this;
  †  †}
  †  †//!  圀椀搀琀栀 愀渀搀 栀攀椀最栀琀 搀椀瘀椀搀攀搀 戀礀 昀愀挀琀漀爀ഀ਀†  †  椀渀氀椀渀攀 匀椀稀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 漀瀀攀爀愀琀漀爀 ⼀㴀 ⠀ 挀漀渀猀琀 昀氀漀愀琀☀ 昀愀挀琀漀爀 ⤀笀ഀ਀†  †  †Policy::m_height /= factor;
  †  †  倀漀氀椀挀礀㨀㨀洀开眀椀搀琀栀 ⼀㴀 昀愀挀琀漀爀㬀ഀ਀†  †  †return *this;
  †  †}
  †};
  †typedef Size<sint32> DigitSize ;

  †typedef Size<sint32> IntegerSize ;
  †typedef Size<float> FloatSize ;
  †typedef Size<double> RealSize ;
  紀⼀⼀䌀漀爀攀ഀ਀紀⼀⼀䴀愀最渀愀ഀ਀⌀攀渀搀椀昀†/*  匀䤀娀䔀开䠀†*/
