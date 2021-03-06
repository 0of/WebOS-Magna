/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2013 by Magnus
  */
#ifndef LINE_H
#define LINE_H

#include "basedef_lib.h"

#include "private/Line_p.h"

namespace Magna{
   渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀ഀ਀†  ⼀⨀℀†\brief
  †  †A line segment with P1 and P2.
  †  †以两点标记的线段。
  †  */
  †/*!
  †  *  †A line segment can be instantiated by two coordinate P1 & P2
  †  *  †and you can call the constructor #Line(const DyadCoordinate<T>&, const DyadCoordinate<T>&) to initilize.
  †  *
  †  *  †Each line could be intersect with another in three ways, which are bounded intersection,
  †  *  †unbounded intersection and parallel. And you can obtain 2 lines intersection type by calling
  †  *  †intersectsWith() and the intersection types has been enumerated #IntersectionType.
  †  *
  †  *  †Besides, you can get the length by calling getLength() and the angle to the x-axle
  †  *  †or the angle between two lines. \see getAngle, getAngleTo
  †  *
  †  *  †What's more, you can get the P1 or P2 or even the point along the line segment.
  †  *  †getP1(), getP2(), getPointAt().
  †  *
  †  *  †\tparam T  挀愀渀 戀攀 椀渀 昀氀漀愀琀Ⰰ 搀漀甀戀氀攀Ⰰ 猀椀渀琀㌀㈀ 昀漀爀 琀栀攀 砀 愀渀搀 礀 琀礀瀀攀ഀ਀†    ⨀†  尀愀琀琀攀渀琀椀漀渀†the T must be in float, double or sint32
  †  *  †  †  漀琀栀攀爀眀椀猀攀 琀栀攀 挀漀洀瀀椀氀攀爀 眀椀氀氀 琀栀爀漀眀 愀 攀爀爀漀爀⸀ഀ਀†    ⨀ഀ਀†    ⨀†  尀愀甀琀栀漀爀†  䴀愀最渀甀猀ഀ਀†    ⨀†  尀瘀攀爀猀椀漀渀†1.0.0.0
  †  *  †\date  †2013/1/16
  †  */
  † template<typename T, typename Policy = LinePolicy<T> >
  † class BASEDEF_LIB_EXPORT Line : Policy{
  †   开开䌀漀渀猀琀愀渀琀猀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Three ways of intersection between two lines
  †  †enum IntersectionType{
  †  †  唀渀戀漀甀渀搀攀搀 㴀 　†/*!< The two line segments are not intersected actually but their extension lines would meet some where. */
  †  †  Ⰰ 䈀漀甀渀搀攀搀 㴀 ㄀†/*!< The two line segments are intersected at a point*/
  †  †  Ⰰ 倀愀爀愀氀氀攀氀 㴀 ㈀†/*!< Parallel*/
  †  †};

  †   开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Default constructor.
  †  †/*!
  †  †  *  †It's not a line segment theoretically but an origin
  †  †  */
  †  †Line() : Policy(){}
  †  †//!  䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 尀昀␀⠀瀀㄀开砀Ⰰ 瀀㄀开礀⤀尀昀␀ 愀渀搀 尀昀␀⠀瀀㈀开砀Ⰰ 瀀㈀开礀⤀尀昀␀ഀ਀†  †  攀砀瀀氀椀挀椀琀 䰀椀渀攀⠀  挀漀渀猀琀 吀☀ 瀀㄀开砀Ⰰ  挀漀渀猀琀 吀☀ 瀀㄀开礀Ⰰ 挀漀渀猀琀 吀☀ 瀀㈀开砀Ⰰ 挀漀渀猀琀 吀☀ 瀀㈀开礀 ⤀ഀ਀†  †  †:Policy( DyadCoordinate<T>(p1_x, p1_y),  DyadCoordinate<T>( p2_x, p2_y ) ){

  †  †}
  †  †//!  䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 琀眀漀 挀漀漀爀搀椀渀愀琀攀猀 倀㄀ ☀ 倀㈀ഀ਀†  †  攀砀瀀氀椀挀椀琀 䰀椀渀攀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 瀀㄀Ⰰ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 瀀㈀⤀ഀ਀†  †  †:Policy( p1,  p2){

  †  †}
  †  †//!  䌀漀瀀礀 䌀漀渀猀琀爀甀挀琀漀爀ഀ਀†  †  䰀椀渀攀⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀ഀ਀†  †  †:Policy ( line ){

  †  †}
  †  †//!  䐀攀猀琀爀甀挀琀漀爀ഀ਀†  †  縀䰀椀渀攀⠀⤀笀ഀ਀ഀ਀†  †  紀ഀ਀ഀ਀†  †__Checker public:
  †  †//!  挀栀攀挀欀 琀栀攀 琀眀漀 氀椀渀攀猀 愀爀攀 甀渀戀漀甀渀搀攀搀 椀渀琀攀爀猀攀挀琀攀搀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀猀愀 椀猀倀愀爀愀氀氀攀氀圀椀琀栀Ⰰ椀猀䈀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀Ⰰ椀渀琀攀爀猀攀挀琀猀圀椀琀栀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 ⌀䤀渀琀攀爀猀攀挀琀椀漀渀吀礀瀀攀ഀ਀†  †    ⨀⼀ഀ਀†  †  戀漀漀氀 椀猀唀渀戀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀笀ഀ਀†  †  †return static_cast<IntersectionType>(Policy::_intersectsWith(line) ) == Unbounded;
  †  †}
  †  †//!  挀栀攀挀欀 琀栀攀 琀眀漀 氀椀渀攀猀 愀爀攀 戀漀甀渀搀攀搀 椀渀琀攀爀猀攀挀琀攀搀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀猀愀 椀猀倀愀爀愀氀氀攀氀圀椀琀栀Ⰰ椀猀唀渀戀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀Ⰰ椀渀琀攀爀猀攀挀琀猀圀椀琀栀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 ⌀䤀渀琀攀爀猀攀挀琀椀漀渀吀礀瀀攀ഀ਀†  †    ⨀⼀ഀ਀†  †  戀漀漀氀 椀猀䈀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀笀ഀ਀†  †  †return static_cast<IntersectionType>(Policy::_intersectsWith(line) ) == Bounded;
  †  †}
  †  †//!  挀栀攀挀欀 琀栀攀 琀眀漀 氀椀渀攀猀 愀爀攀 瀀愀爀愀氀氀攀氀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀猀愀 椀猀唀渀戀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀Ⰰ椀猀䈀漀甀渀搀攀搀䤀渀琀攀爀猀攀挀琀攀搀圀椀琀栀Ⰰ椀渀琀攀爀猀攀挀琀猀圀椀琀栀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 ⌀䤀渀琀攀爀猀攀挀琀椀漀渀吀礀瀀攀ഀ਀†  †    ⨀⼀ഀ਀†  †  戀漀漀氀 椀猀倀愀爀愀氀氀攀氀圀椀琀栀⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀笀ഀ਀†  †  †return static_cast<IntersectionType>(Policy::_intersectsWith(line) ) == Parallel;
  †  †}

  †  开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  椀渀氀椀渀攀 搀漀甀戀氀攀 最攀琀䰀攀渀最琀栀⠀⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Policy::_getLength();
  †  †}

  †  †//!  䜀攀琀 琀栀攀 愀 瀀漀椀渀琀 愀氀漀渀最 琀栀攀 氀椀渀攀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  琀栀攀 猀琀愀爀琀 瀀漀椀渀琀 椀猀 倀㄀ 愀渀搀 攀渀搀 椀猀 倀㈀ഀ਀†  †    ⨀†  椀琀✀氀氀 挀愀氀挀甀氀愀琀攀 琀栀攀 漀昀昀猀攀琀 戀礀 琀栀攀 最椀瘀攀渀 瀀愀爀愀洀攀琀攀爀 ⴀⴀ 琀栀攀 瀀攀爀挀攀渀琀愀最攀ഀ਀†  †    ⨀†  愀渀搀 琀栀攀 倀㄀ 瀀氀甀猀 攀愀挀栀 漀昀昀猀攀琀 椀渀 砀 愀渀搀 礀 眀漀甀氀搀 戀攀 琀栀攀 爀攀猀甀氀琀ഀ਀†  †    ⨀†  尀瀀愀爀愀洀†at  爀愀渀最椀渀最 昀爀漀洀 　縀㄀⸀　ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀†a point at the line; P1 plus the offset
  †  †  */
  †  †DyadCoordinate<T> getPointAt( const double& at );

  †  †//!  最攀琀 愀渀最氀攀 戀攀琀眀攀攀渀 琀栀攀 氀椀渀攀 愀渀搀 琀栀攀 砀ⴀ愀砀氀攀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 琀栀攀 搀攀最爀攀攀ഀ਀†  †    ⨀†  尀猀愀 最攀琀䄀渀最氀攀吀漀ഀ਀†  †    ⨀⼀ഀ਀†  †  椀渀氀椀渀攀 搀漀甀戀氀攀 最攀琀䄀渀最氀攀⠀⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Policy::_getAngle();
  †  †}
  †  †//!  最攀琀 琀栀攀 愀渀最氀攀 戀攀琀眀攀攀渀 琀眀漀 氀椀渀攀猀ഀ਀†  †  ⼀⨀℀ഀ਀†  †    ⨀†  尀爀攀琀甀爀渀 琀栀攀 搀攀最爀攀攀ഀ਀†  †    ⨀†  尀猀愀 最攀琀䄀渀最氀攀ഀ਀†  †    ⨀⼀ഀ਀†  †  椀渀氀椀渀攀 搀漀甀戀氀攀 最攀琀䄀渀最氀攀吀漀⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Policy::_getAngleTo( line );
  †  †}

  †  †//!  䜀攀琀 琀栀攀 倀㄀ 挀漀漀爀搀椀渀愀琀攀ഀ਀†  †  挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 最攀琀倀㄀⠀⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Policy::_P1();
  †  †}
  †  †//!  䜀攀琀 琀栀攀 倀㈀ 挀漀漀爀搀椀渀愀琀攀ഀ਀†  †  挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 最攀琀倀㈀⠀⤀ 挀漀渀猀琀笀ഀ਀†  †  †return Policy::_P2();
  †  †}

  †  开开匀攀琀琀攀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Set the line with new  \f$(p1_x, p1_y)\f$ and \f$(p2_x, p2_y)\f$
  †  †void setLine( const T& p1_x,  const T& p1_y, const T& p2_x, const T& p2_y ){
  †  †  倀漀氀椀挀礀㨀㨀开倀㄀⠀⤀ 㴀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀⠀ 瀀㄀开砀Ⰰ 瀀㄀开礀 ⤀㬀ഀ਀†  †  †Policy::_P2() = DyadCoordinate<T>( p2_x, p2_y );
  †  †}
  †  †//!  匀攀琀 琀栀攀 氀椀渀攀 眀椀琀栀 琀眀漀 挀漀漀爀搀椀渀愀琀攀猀ഀ਀†  †  瘀漀椀搀 猀攀琀䰀椀渀攀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 瀀㄀Ⰰ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀☀ 瀀㈀ ⤀笀ഀ਀†  †  †Policy::_P1() = p1;
  †  †  倀漀氀椀挀礀㨀㨀开倀㈀⠀⤀ 㴀 瀀㈀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Set P1 coordinate
  †  †void setP1( const DyadCoordinate<T>& p1 ){
  †  †  倀漀氀椀挀礀㨀㨀开倀㄀⠀⤀ 㴀 瀀㄀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Set P2 coordinate
  †  †void setP2( const DyadCoordinate<T>& p2 ){
  †  †  倀漀氀椀挀礀㨀㨀开倀㈀⠀⤀ 㴀 瀀㈀㬀ഀ਀†  †  紀ഀ਀ഀ਀†  †__By_Methods public:
  †  †//!  吀栀攀 眀栀漀氀攀 氀椀渀攀 椀猀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀砀 愀渀搀 搀礀ഀ਀†  †  䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀 ☀ 琀爀愀渀猀氀愀琀攀搀䈀礀⠀ 挀漀渀猀琀 吀☀ 砀吀爀愀渀猀氀愀琀攀Ⰰ 挀漀渀猀琀 吀☀ 礀吀爀愀渀猀氀愀琀攀 ⤀笀ഀ਀†  †  †Policy::_P1().translatedByEach( xTranslate, yTranslate );
  †  †  倀漀氀椀挀礀㨀㨀开倀㈀⠀⤀⸀琀爀愀渀猀氀愀琀攀搀䈀礀䔀愀挀栀⠀ 砀吀爀愀渀猀氀愀琀攀Ⰰ 礀吀爀愀渀猀氀愀琀攀 ⤀㬀ഀ਀†  †  †return *this;
  †  †}

  †  开开吀漀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†The whole line is translated to anther new line
  †  †Line<T, Policy>translatesTo( const T& xTranslate, const T& yTranslate ){
  †  †  爀攀琀甀爀渀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀⠀倀漀氀椀挀礀㨀㨀开倀㄀⠀⤀⸀琀爀愀渀猀氀愀琀攀猀吀漀䔀愀挀栀⠀ 砀吀爀愀渀猀氀愀琀攀Ⰰ 礀吀爀愀渀猀氀愀琀攀 ⤀ഀ਀†  †  †  †  †  Ⰰ†Policy::_P2().translatesToEach( xTranslate, yTranslate ) );
  †  †}

  †  瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†Get the #IntersectionType between two lines
  †  †/*!
  †  †  *  †\sa isParallelWith,isBoundedIntersectedWith,isUnboundedIntersectedWith
  †  †  *  †\return #IntersectionType
  †  †  */
  †  †MAGNA_NOINLINE IntersectionType intersectsWith( const Line<T, Policy>& line ){
  †  †  爀攀琀甀爀渀 猀琀愀琀椀挀开挀愀猀琀㰀䤀渀琀攀爀猀攀挀琀椀漀渀吀礀瀀攀㸀⠀倀漀氀椀挀礀㨀㨀开椀渀琀攀爀猀攀挀琀猀圀椀琀栀⠀ 氀椀渀攀 ⤀ ⤀㬀ഀ਀†  †  紀ഀ਀ഀ਀†  †__Overloaded_Methods public:
  †  †//!  䄀猀猀椀最渀 漀瀀攀爀愀琀漀爀ഀ਀†  †  䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀 ☀ 漀瀀攀爀愀琀漀爀 㴀 ⠀ 挀漀渀猀琀 䰀椀渀攀㰀吀Ⰰ 倀漀氀椀挀礀㸀☀ 氀椀渀攀 ⤀笀ഀ਀†  †  †Policy::operator =( line );
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Check two lines are the same
  †  †bool operator == ( const Line<T, Policy>& line ){
  †  †  爀攀琀甀爀渀 倀漀氀椀挀礀㨀㨀漀瀀攀爀愀琀漀爀 㴀㴀⠀ 氀椀渀攀 ⤀㬀ഀ਀†  †  紀ഀ਀†  †  ⼀⼀℀†Check two lines are not the same
  †  †bool operator != ( const Line<T, Policy>& line ){
  †  †  爀攀琀甀爀渀 ℀倀漀氀椀挀礀㨀㨀漀瀀攀爀愀琀漀爀 㴀㴀⠀ 氀椀渀攀 ⤀㬀ഀ਀†  †  紀ഀ਀†   紀㬀ഀ਀†   琀礀瀀攀搀攀昀 䰀椀渀攀㰀猀椀渀琀㌀㈀㸀 䤀渀琀攀最攀爀䰀椀渀攀㬀ഀ਀† }//Core
}//Magna
#endif  ⼀⨀†LINE_H  ⨀⼀�