/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2013 by Magnus
  */
#ifndef BaseRectRegion_H
#define BaseRectRegion_H

#include "basedef_lib.h"
#include "DyadCoordinate.h"

#include "private/RectRegion_p.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀†  ⼀⨀℀†\brief
  †  †Use to define a rectangle unit.用来定义一个矩形
  †  */
  †/*!
  †  *  †Each rectangle can be determined by two coordinates --
  †  *  †the coordinate standing at the top left and the other at the bottom right.
  †  *  †You can establish a rectangle by giving the two coordinates or an coordinate with size.
  †  *
  †  *  †Besides, you can get the size by calling getSize(), or getWidth() / getHeight() to get the raw value.
  †  *  †And you can use getters such like getTopLeftCoord(), getCenterCoord() and so forth to obtain
  †  *  †the property value.
  †  *
  †  *  †With isOverlappedWith() you can check two rects are overlapped.
  †  *  †And with intersectsTo(), joinsTo(), you can do some basis manipulation on rectangles.
  †  *
  †  *  †\tparam T  挀愀渀 戀攀 椀渀 昀氀漀愀琀Ⰰ 搀漀甀戀氀攀Ⰰ 猀椀渀琀㌀㈀ 昀漀爀 琀栀攀 砀 愀渀搀 礀 琀礀瀀攀਀†    ⨀†  尀愀琀琀攀渀琀椀漀渀†the T must be in float, double or sint32
  †  *  †  †  漀琀栀攀爀眀椀猀攀 琀栀攀 挀漀洀瀀椀氀攀爀 眀椀氀氀 琀栀爀漀眀 愀 攀爀爀漀爀⸀਀†    ⨀਀†    ⨀†  尀愀甀琀栀漀爀†  䴀愀最渀甀猀਀†    ⨀†  尀瘀攀爀猀椀漀渀   ㄀⸀　⸀　⸀　਀†    ⨀†  尀搀愀琀攀†  ㈀　㄀㌀⼀㄀⼀㐀਀†    ⨀⼀਀†  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 吀Ⰰ 琀礀瀀攀渀愀洀攀 倀漀氀椀挀礀 㴀 刀攀挀琀刀攀最椀漀渀倀漀氀椀挀礀㰀吀㸀 㸀਀†  挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 刀攀挀琀刀攀最椀漀渀 㨀 倀漀氀椀挀礀笀਀†  †__Constructor_Destructor public:
  †  †//!  䐀攀昀愀甀氀琀 挀漀渀猀琀爀甀挀琀漀爀਀†  †  刀攀挀琀刀攀最椀漀渀⠀⤀ 㨀 倀漀氀椀挀礀⠀⤀笀紀਀†  †  ⼀⼀℀†Constructor with two coords
  †  †/*!
  †  †  *  †If top left would not stand top and left to bottom right
  †  †  *  †the two coordinates position maybe changed
  †  †  *  †i.e. what you get from getTopLeftCoord() or getBottomRightCoord() may not
  †  †  *  †be equal to the parameters you input.
  †  †  *
  †  †  *  †\param  topLeftCoord  琀栀攀 琀漀瀀 氀攀昀琀 挀漀漀爀搀椀渀愀琀攀਀†  †    ⨀†  尀瀀愀爀愀洀  戀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀 琀栀攀 戀漀琀琀漀洀 爀椀最栀琀 挀漀漀爀搀椀渀愀琀攀਀†  †    ⨀†  †and its x and y must hight than top left coordinate's
  †  †  *  †  䤀昀 渀漀琀Ⰰ 椀琀✀氀氀 愀甀琀漀洀愀琀椀挀愀氀氀礀 渀漀爀洀愀氀椀稀攀 琀栀攀洀⸀਀†  †    ⨀⼀਀†  †  攀砀瀀氀椀挀椀琀 刀攀挀琀刀攀最椀漀渀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀 ☀ 琀漀瀀䰀攀昀琀䌀漀漀爀搀਀†  †  †  †  †  Ⰰ   挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀 ☀ 戀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⤀਀†  †  †  †  †  㨀倀漀氀椀挀礀⠀ 琀漀瀀䰀攀昀琀䌀漀漀爀搀Ⰰ 戀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀 ⤀笀਀਀†  †  紀਀਀†  †  ⼀⼀℀†Constructor with top left coordinate and its size
  †  †/*!
  †  †  *  †If the size is not a proper one ( contains negative value )
  †  †  *  †the top left coordinate may not be the same as your input.
  †  †  *
  †  †  *  †\param  topLeftCoord  琀栀攀 琀漀瀀 氀攀昀琀 挀漀漀爀搀椀渀愀琀攀਀†  †    ⨀†  尀瀀愀爀愀洀 眀椀搀琀栀 ✀搀 戀攀琀琀攀爀 渀漀琀 戀攀 渀攀最愀琀椀瘀攀਀†  †    ⨀†  尀瀀愀爀愀洀 栀攀椀最栀琀 ✀搀 戀攀琀琀攀爀 渀漀琀 戀攀 渀攀最愀琀椀瘀攀਀†  †    ⨀⼀਀†  †  攀砀瀀氀椀挀椀琀 刀攀挀琀刀攀最椀漀渀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀 ☀ 琀漀瀀䰀攀昀琀䌀漀漀爀搀Ⰰ 挀漀渀猀琀 吀☀ 眀椀搀琀栀Ⰰ 挀漀渀猀琀 吀☀ 栀攀椀最栀琀 ⤀਀†  †  †:Policy( topLeftCoord, width, height ){

  †  †}

  †  †//!  䌀漀瀀礀 挀漀渀猀琀爀甀挀琀漀爀਀†  †  刀攀挀琀刀攀最椀漀渀⠀ 挀漀渀猀琀 刀攀挀琀刀攀最椀漀渀㰀 吀㸀 ☀ 爀攀挀琀刀攀最椀漀渀 ⤀਀†  †  †:Policy( rectRegion ){

  †  †}
  †  †//!  䐀攀猀琀爀甀挀琀漀爀਀†  †  縀刀攀挀琀刀攀最椀漀渀⠀⤀笀਀਀†  †  紀਀਀†  †__Checker public:
  †  †inline bool contains( const DyadCoordinate<T>& coord ) const{
  †  †  †return  !Comparer<T>::isLowerThan( coord.getX(), Policy::_TopLeftCoord().getX() )
  †  †  †&& !Comparer<T>::isLowerThan( coord.getY(), Policy::_TopLeftCoord().getY() )
  †  †  †&& !Comparer<T>::isHigherThan( coord.getX(), Policy::_BottomRightCoord().getX() )
  †  †  †&& !Comparer<T>::isHigherThan( coord.getY(), Policy::_BottomRightCoord().getY() ) ;
  †  †}

  †  开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†Get the width of the rectangle
  †  †/*!
  †  †  *  †\return subtract the left -- left top coord 's x
  †  †  *  †  昀爀漀洀 爀椀最栀琀 ⴀⴀ 爀椀最栀琀 戀漀琀琀漀洀 挀漀漀爀搀✀猀 砀਀†  †    ⨀†  尀猀愀 猀攀琀圀椀搀琀栀Ⰰ 最攀琀䠀攀椀最栀琀Ⰰ 最攀琀匀椀稀攀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 吀 最攀琀圀椀搀琀栀⠀⤀ 挀漀渀猀琀笀਀†  †  †return Policy::_BottomRightCoord().getX() - Policy::_TopLeftCoord().getX();
  †  †}
  †  †//!  䜀攀琀 琀栀攀 栀攀椀最栀琀 漀昀 琀栀攀 爀攀挀琀愀渀最氀攀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀爀攀琀甀爀渀 猀甀戀琀爀愀挀琀 琀栀攀 琀漀瀀 ⴀⴀ 氀攀昀琀 琀漀瀀 挀漀漀爀搀 ✀猀 礀਀†  †    ⨀†  †from bottom -- right bottom coord's y
  †  †  *  †\sa setHeight, getWidth, getSize
  †  †  */
  †  †inline T getHeight() const{
  †  †  爀攀琀甀爀渀  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀ ⴀ  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get the size of the rectangle
  †  †/*!
  †  †  *  †\return a size instance
  †  †  *  †\sa  getWidth, getHeight
  †  †  */
  †  †inline Size<T> getSize() const{
  †  †  爀攀琀甀爀渀  匀椀稀攀㰀吀㸀⠀  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀最攀琀堀⠀⤀ ⴀ 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀堀⠀⤀਀†  †  †  Ⰰ 倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀ ⴀ  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get the top left coordinate
  †  †/*!
  †  †  *  †\return the const reference of the top left coordinate
  †  †  *  †\sa getBottomRightCoord, getTopRightCoord
  †  †  */
  †  †inline DyadCoordinate<T> getTopLeftCoord() const{
  †  †  爀攀琀甀爀渀 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get the bottom right coordinate
  †  †/*!
  †  † *  †\return the const reference of the bottom right coordinate
  †  † *  †\sa getTopLeftCoord, getBottomLeftCoord
  †  † */
  †  †inline DyadCoordinate<T> getBottomRightCoord() const{
  †  †  爀攀琀甀爀渀 倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get the center coordinate of the rectangle
  †  †/*!
  †  †  *  †\return the coordinate at the center of the rectangle
  †  †  */
  †  †inline DyadCoordinate<T> getCenterCoord() const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀⠀ 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀堀⠀⤀ ⬀ 最攀琀圀椀搀琀栀⠀⤀ ⼀ ㈀਀†  †  †  †  †  †  †  †, Policy::_TopLeftCoord().getY() + getHeight() / 2 );
  †  †}

  †  †//!  䜀攀琀 琀栀攀 琀漀瀀 爀椀最栀琀 挀漀漀爀搀椀渀愀琀攀਀†  †  椀渀氀椀渀攀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀 最攀琀吀漀瀀刀椀最栀琀䌀漀漀爀搀⠀⤀ 挀漀渀猀琀笀਀†  †  †return DyadCoordinate<T>( Policy::_BottomRightCoord().getX(), Policy::_TopLeftCoord().getY() );
  †  †}

  †  †//!  䜀攀琀 琀栀攀 戀漀琀琀漀洀 氀攀昀琀 挀漀漀爀搀椀渀愀琀攀਀†  †  椀渀氀椀渀攀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀 最攀琀䈀漀琀琀漀洀䰀攀昀琀䌀漀漀爀搀⠀⤀ 挀漀渀猀琀笀਀†  †  †return DyadCoordinate<T>( Policy::_TopLeftCoord().getX(), Policy::_BottomRightCoord().getY() );
  †  †}

  †  开开匀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†set the width of the rectangle
  †  †/*!
  †  †  *  †\param width 'd better not be negative
  †  †  *  †  椀昀 渀攀最愀琀椀瘀攀Ⰰ 琀栀攀 爀攀挀琀愀渀最氀攀 眀椀氀氀 渀漀爀洀愀氀椀稀攀 椀琀⸀਀†  †    ⨀†  尀猀愀 最攀琀圀椀搀琀栀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 瘀漀椀搀 猀攀琀圀椀搀琀栀⠀ 挀漀渀猀琀 吀☀ 眀椀搀琀栀⤀笀਀†  †  †Policy::_BottomRightCoord().setX( Policy::_TopLeftCoord().getX() + width );
  †  †}

  †  †//!  猀攀琀 琀栀攀 栀攀椀最栀琀 漀昀 琀栀攀 爀攀挀琀愀渀最氀攀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀瀀愀爀愀洀 栀攀椀最栀琀 ✀搀 戀攀琀琀攀爀 渀漀琀 戀攀 渀攀最愀琀椀瘀攀਀†  †    ⨀†  †if negative, the rectangle will normalize it.
  †  †  *  †\sa getHeight
  †  †  */
  †  †inline void setHeight( const T& height ){
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀猀攀琀夀⠀ 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀ ⬀ 栀攀椀最栀琀 ⤀㬀਀†  †  紀਀਀†  †  椀渀氀椀渀攀 瘀漀椀搀 猀攀琀匀椀稀攀⠀ 挀漀渀猀琀 匀椀稀攀㰀吀㸀☀ 猀椀稀攀 ⤀笀਀†  †  †Policy::_BottomRightCoord().setX( Policy::_TopLeftCoord().getX() + size.getWidth() );
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀猀攀琀夀⠀ 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀ ⬀ 猀椀稀攀⸀最攀琀䠀攀椀最栀琀⠀⤀ ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set the center coordinate of the rectangle
  †  †/*!
  †  †  *  † \sa getCenterCoord
  †  †  */
  †  †inline void setCenterCoord( const DyadCoordinate<T>& centerCoord ){
  †  †  挀漀渀猀琀 吀☀ 栀愀氀昀圀椀搀琀栀 㴀  最攀琀圀椀搀琀栀⠀⤀ ⼀ ㈀㬀਀†  †  †const T& halfHeight = getHeight() / 2;
  †  †  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀猀攀琀䌀漀漀爀搀椀渀愀琀攀⠀ 挀攀渀琀攀爀䌀漀漀爀搀⸀最攀琀堀⠀⤀ ⴀ 栀愀氀昀圀椀搀琀栀Ⰰ 挀攀渀琀攀爀䌀漀漀爀搀⸀最攀琀夀⠀⤀ ⴀ 栀愀氀昀䠀攀椀最栀琀 ⤀㬀਀†  †  †Policy::_BottomRightCoord().setCoordinate( centerCoord.getX() + halfWidth, centerCoord.getY() + halfHeight );
  †  †}

  †  †//! Set top left coordinate
  †  †/*!
  †  †  *  †If the new TopLeft coordinate is not standing at the top left
  †  †  *  †the real one may differ from the one you input.
  †  †  *  †\param topLeftCoord should be the top & left one
  †  †  *  †\sa getTopLeftCoord , setBottomRightCoord
  †  †  */
  †  †void setTopLeftCoord( const DyadCoordinate<T>& topLeftCoord ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀ 琀漀瀀䰀攀昀琀䌀漀漀爀搀 ⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Set the Left value
  †  †void setTopLeftCoordX( const T& x ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀ 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀⠀砀Ⰰ 倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀夀⠀⤀ ⤀ ⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Set the Top value
  †  †void setTopLeftCoordY( const T& y ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀ 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀㸀⠀倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀最攀琀堀⠀⤀Ⰰ 礀 ⤀ ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set bottom right coordinate
  †  †/*!
  †  †  *  †If the new BottomRight coordinate is not standing at the bottom right side
  †  †  *  †the real one may differ from the one you input.
  †  †  *  †\param bottomRightCoord should be the bottom & right one
  †  †  *  †\sa getBottomRightCoord, setTopLeftCoord
  †  †  */
  †  †void setBottomRightCoord( const DyadCoordinate<T>& bottomRightCoord ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀ 戀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀 ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set the Right value
  †  †void setBottomRightCoordX( const T& x ){
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀ ⤀⸀猀攀琀堀⠀ 砀 ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set the Bottom value
  †  †void setBottomRightCoordY( const T& y ){
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀猀攀琀夀⠀ 礀 ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set the top right coordinate
  †  †void setTopRightCoord( const DyadCoordinate<T>& topRightCoord ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀吀漀瀀刀椀最栀琀䌀漀漀爀搀⠀ 琀漀瀀刀椀最栀琀䌀漀漀爀搀 ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Set the bottom left coordinate
  †  †void setBottomLeftCoord( const DyadCoordinate<T>& bottomLeftCoord ){
  †  †  倀漀氀椀挀礀㨀㨀开猀攀琀䈀漀琀琀漀洀䰀攀昀琀䌀漀漀爀搀⠀ 戀漀琀琀漀洀䰀攀昀琀䌀漀漀爀搀 ⤀㬀਀†  †  紀਀਀†  †__Checker public:
  †  †//!  挀栀攀挀欀 琀栀攀 爀攀挀琀愀渀最氀攀 椀猀 漀瘀攀爀氀愀瀀瀀攀搀 眀椀琀栀 愀渀漀琀栀攀爀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀瀀愀爀愀洀 爀攀挀琀刀攀最椀漀渀 琀栀攀 挀栀攀挀欀 爀攀挀琀愀渀最氀攀਀†  †    ⨀†  尀爀攀琀甀爀渀 椀昀 椀猀 漀瘀攀爀氀愀瀀瀀攀搀 爀攀琀甀爀渀猀 琀爀甀攀 漀琀栀攀爀眀椀猀攀 昀愀氀猀攀਀†  †    ⨀⼀਀†  †  戀漀漀氀 椀猀伀瘀攀爀氀愀瀀瀀攀搀圀椀琀栀⠀ 挀漀渀猀琀 刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 爀攀挀琀刀攀最椀漀渀 ⤀ 挀漀渀猀琀笀਀†  †  †return  倀漀氀椀挀礀㨀㨀开椀猀伀瘀攀爀氀愀瀀瀀攀搀圀椀琀栀⠀ 爀攀挀琀刀攀最椀漀渀 ⤀㬀਀†  †  紀਀਀†  †public:
  †  †//!  洀漀搀椀昀礀 琀栀攀 挀甀爀爀攀渀琀 爀攀挀琀愀渀最氀攀 眀椀琀栀 琀栀攀 椀渀琀攀爀猀攀挀琀椀漀渀 爀攀挀琀愀渀最氀攀਀†  †  ⼀⨀℀਀†  †    ⨀†  䘀椀爀猀琀 挀愀氀挀甀氀愀琀攀 琀栀攀 椀渀琀攀爀猀攀挀琀椀漀渀 爀攀挀琀愀渀最氀攀 眀椀琀栀 挀甀爀爀攀渀琀 爀攀挀琀愀渀最氀攀਀†  †    ⨀†  愀渀搀 最椀瘀攀渀 爀攀挀琀愀渀最氀攀 愀猀 愀 瀀愀爀愀洀攀琀攀爀⸀ 琀栀攀渀 洀漀搀椀昀礀 琀栀攀 挀甀爀爀攀渀琀 漀渀攀਀†  †    ⨀†  眀椀琀栀 琀栀攀 爀攀猀甀氀琀਀†  †    ⨀਀†  †    ⨀†  尀瀀愀爀愀洀 爀攀挀琀刀攀最椀漀渀 琀栀攀 爀攀挀琀愀渀最氀攀 椀渀琀攀爀猀攀挀琀 眀椀琀栀਀†  †    ⨀†  尀爀攀琀甀爀渀 ⨀琀栀椀猀਀†  †    ⨀†  尀猀愀 樀漀椀渀攀搀䈀礀਀†  †    ⨀⼀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 椀渀琀攀爀猀攀挀琀攀搀䈀礀⠀ 挀漀渀猀琀 刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 爀攀挀琀刀攀最椀漀渀 ⤀ 㬀਀਀†  †  ⼀⼀℀†modify the current rectangle with the union rectangle
  †  †/*!
  †  †  *  †First calculate the union rectangle with current rectangle
  †  †  *  †and given rectangle as a parameter. then modify the current one
  †  †  *  †with the result
  †  †  *
  †  †  *  †\param rectRegion the rectangle joined with
  †  †  *  †\return *this
  †  †  *  †\sa intersectedBy
  †  †  */
  †  †RectRegion<T>& joinedBy( const RectRegion<T>& rectRegion ){
  †  †  椀昀⠀ 䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䰀漀眀攀爀吀栀愀渀⠀爀攀挀琀刀攀最椀漀渀⸀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开砀Ⰰ  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开砀 ⤀ ⤀笀਀†  †  †   倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开砀 㴀 爀攀挀琀刀攀最椀漀渀⸀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开砀㬀਀†  †  †}

  †  †  椀昀⠀ 䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䰀漀眀攀爀吀栀愀渀⠀爀攀挀琀刀攀最椀漀渀⸀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开礀Ⰰ  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开礀 ⤀ ⤀笀਀†  †  †  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开礀 㴀 爀攀挀琀刀攀最椀漀渀⸀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀洀开礀㬀਀†  †  †}

  †  †  椀昀⠀ 䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䠀椀最栀攀爀吀栀愀渀⠀爀攀挀琀刀攀最椀漀渀⸀倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开砀Ⰰ  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开砀 ⤀ ⤀笀਀†  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开砀 㴀 爀攀挀琀刀攀最椀漀渀⸀倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开砀㬀਀†  †  †}

  †  †  椀昀⠀ 䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䠀椀最栀攀爀吀栀愀渀⠀爀攀挀琀刀攀最椀漀渀⸀倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开礀Ⰰ  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开礀 ⤀ ⤀笀਀†  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开礀 㴀 爀攀挀琀刀攀最椀漀渀⸀倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀洀开礀㬀਀†  †  †}

  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†all the coordinates of the rect translated by translate the parameter
  †  †RectRegion<T>& translatedBy( const DyadCoordinate<T>& coord ){
  †  †  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀琀爀愀渀猀氀愀琀攀搀䈀礀⠀ 挀漀漀爀搀 ⤀㬀਀†  †  †Policy::_BottomRightCoord().translatedBy( coord );
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 琀爀愀渀猀氀愀琀攀搀䈀礀䔀愀挀栀⠀ 挀漀渀猀琀 吀☀ 搀砀Ⰰ 挀漀渀猀琀 吀☀ 搀礀 ⤀笀਀†  †  †Policy::_TopLeftCoord().translatedByEach( dx, dy );
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀琀爀愀渀猀氀愀琀攀搀䈀礀䔀愀挀栀⠀ 搀砀Ⰰ 搀礀 ⤀㬀਀†  †  †return *this;
  †  †}

  †  †RectRegion<T>& translatedByX( const T& dx ){
  †  †  倀漀氀椀挀礀㨀㨀开吀漀瀀䰀攀昀琀䌀漀漀爀搀⠀⤀⸀琀爀愀渀猀氀愀琀攀搀䈀礀堀⠀ 搀砀 ⤀㬀਀†  †  †Policy::_BottomRightCoord().translatedByX( dx );
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 琀爀愀渀猀氀愀琀攀搀䈀礀夀⠀ 挀漀渀猀琀 吀☀ 搀礀 ⤀笀਀†  †  †Policy::_TopLeftCoord().translatedByY( dy );
  †  †  倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀⸀琀爀愀渀猀氀愀琀攀搀䈀礀夀⠀ 搀礀 ⤀㬀਀†  †  †return *this;
  †  †}

  †  †//!  爀攀琀甀爀渀 琀栀攀 琀眀漀 爀攀挀琀猀 椀渀琀攀爀猀攀挀琀椀漀渀 爀攀挀琀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀 椀渀琀攀爀猀攀挀琀猀吀漀⠀ 挀漀渀猀琀 刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 刀攀挀琀刀攀最椀漀渀  ⤀ 挀漀渀猀琀㬀਀†  †  ⼀⼀℀†return the two rects union rect
  †  †RectRegion<T> joinsTo( const RectRegion<T>& rectRegion  ) const;
  †  †//!  琀爀愀渀猀氀愀琀攀 琀漀 愀 渀攀眀 爀攀挀琀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀 琀爀愀渀猀氀愀琀攀猀吀漀⠀ 挀漀渀猀琀 吀☀ 琀爀愀渀猀氀愀琀攀 ⤀㬀਀਀†  †__Override_Methods public:
  †  †//!  䄀猀猀椀最渀 漀瀀攀爀愀琀漀爀਀†  †  刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 漀瀀攀爀愀琀漀爀 㴀 ⠀ 挀漀渀猀琀 刀攀挀琀刀攀最椀漀渀㰀吀㸀☀ 爀攀挀琀刀攀最椀漀渀 ⤀笀਀†  †  † Policy::_TopLeftCoord() = rectRegion.Policy::_TopLeftCoord();
  †  †   倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀ 㴀 爀攀挀琀刀攀最椀漀渀⸀倀漀氀椀挀礀㨀㨀开䈀漀琀琀漀洀刀椀最栀琀䌀漀漀爀搀⠀⤀㬀਀†  †  † return *this;
  †  †}

  †  †// OR
  †  †//NOT bit OR
  †  †RectRegion<T> operator |( const RectRegion<T>& rectRegion );
  †  †RectRegion<T>& operator |= ( const RectRegion<T>& rectRegion );

  †  †// AND
  †  †//NOT bit AND
  †  †RectRegion<T> operator &( const RectRegion<T>& rectRegion );
  †  †RectRegion<T>& operator &= ( const RectRegion<T>& rectRegion );

  †};
  †typedef RectRegion<sint32> IntegerRectRegion;
  †typedef RectRegion<sint32> DigitRectRegion;
  †typedef RectRegion<float> FloatRectRegion;
  †typedef RectRegion<double> RealRectRegion;
  紀⼀⼀䌀漀爀攀਀紀⼀⼀䴀愀最渀愀਀਀⌀攀渀搀椀昀†/*  䈀愀猀攀刀攀挀琀刀攀最椀漀渀开䠀†*/

