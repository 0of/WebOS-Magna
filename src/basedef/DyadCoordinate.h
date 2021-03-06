/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2013 by Magnus
  */
#ifndef DYADCOORDINATE_H
#define DYADCOORDINATE_H

#include "basedef_lib.h"
#include "SystemDef.h"
#include "BaseTypes.h"
#include "Comparer.h"

#include "private/DyadCoordinate_p.h"

#include <cassert>
#include <cmath>

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  ⼀⨀℀†\brief
  †  †This class represents a point in 2-d coordinate system with two x & y.
  †  †该类作为二维平面坐标系中包含X和Y的一个点。
  †  */
  †/*!
  †  *  †The default constructor DyadCoordinate() will set the x and y to zero
  †  *  †which means the coord is origin and you can check with isOrigin().
  †  *  †And by using ::DigitDyadCoordinate, ::FloatDyadCoordinate, ::RealDyadCoordinate would be better.
  †  *
  †  *  †A DyadCoord can be set by using method setX() or setY()
  †  *  †Or even you can get the reference of x and y to modify their values.
  †  *
  †  *  †Besides, in 2-d coordinate system, each point stands at a quadrant.#Quadrant and #ImpreciseQuadrant
  †  *  †We've got 2 kind of quadrant, one is imprecise quadrant which is easier
  †  *  †for calculation and has no axles.You can get the enumurator value from
  †  *  †calling getImpreciseQuadrant().
  †  *
  †  *  †And measuring the distance can be calling the manhattanLength() or calDistanceBy()
  †  *
  †  *  †Also can call determinant() to calculate the square determinant
  †  *
  †  *  †\tparam T  挀愀渀 戀攀 椀渀 昀氀漀愀琀Ⰰ 搀漀甀戀氀攀Ⰰ 猀椀渀琀㌀㈀ 昀漀爀 琀栀攀 砀 愀渀搀 礀 琀礀瀀攀਀†    ⨀†  尀愀琀琀攀渀琀椀漀渀†the T must be in float, double or sint32
  †  *  †  †  漀琀栀攀爀眀椀猀攀 琀栀攀 挀漀洀瀀椀氀攀爀 眀椀氀氀 琀栀爀漀眀 愀 攀爀爀漀爀⸀਀†    ⨀਀†    ⨀†  尀愀甀琀栀漀爀†  䴀愀最渀甀猀਀†    ⨀†  尀瘀攀爀猀椀漀渀†1.0.0.0
  †  *  †\date  †2012/12/27
  †  */
  †template<typename T, class Policy = DyadCoordinatePolicy<T> >
  †class BASEDEF_LIB_EXPORT DyadCoordinate : Policy{
  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开吀礀瀀攀Ⰰ 挀氀愀猀猀  开吀爀愀椀琀㸀਀†  †friend class RectRegionPolicy;

  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开吀礀瀀攀Ⰰ 挀氀愀猀猀 开倀漀氀椀挀礀㸀਀†  †friend class RectRegion;

  †  开开䌀漀渀猀琀愀渀琀猀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†Quadrant Enum.\n象限
  †  †enum Quadrant{
  †  †  伀爀椀最椀渀 㴀 　砀　　　Ⰰ 䘀椀爀猀琀 㴀 　砀　　㄀　Ⰰ 匀攀挀漀渀搀 㴀 　砀　㄀㄀　Ⰰ 吀栀椀爀搀 㴀 　砀㄀㄀㄀　Ⰰ 䘀漀甀爀琀栀 㴀 　砀㄀　㄀　Ⰰ਀†  †  †XAxle = 0x0011, YAxle = 0x0111, NXAxle = 0x1111, XYAxle = 0x1011
  †  †};
  †  †//!  䤀洀瀀爀攀挀椀猀攀 儀甀愀搀爀愀渀琀 䔀渀甀洀⸀਀†  †  ⼀⨀℀਀†  †    ⨀†  唀猀攀 昀漀爀 椀洀瀀爀攀挀椀猀攀 挀愀氀挀甀氀愀琀椀漀渀猀⸀਀†  †    ⨀⼀਀†  †  攀渀甀洀 䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀笀਀†  †  †ImpreciseQuadrant_Origin = 0x000 /*!< Origin */ , ImpreciseQuadrant_First = 0x100/*!< First quadrant */
  †  †  Ⰰ 䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀开匀攀挀漀渀搀 㴀 　砀㄀　㄀⼀⨀℀㰀 匀攀挀漀渀搀 焀甀愀搀爀愀渀琀Ⰰ 挀漀渀琀愀椀渀猀 礀ⴀ愀砀氀攀 ⨀⼀਀†  †  †, ImpreciseQuadrant_Third = 0x111/*!< Third quadrant, contains n-x-axle & n-y-axle */
  †  †  Ⰰ 䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀开䘀漀甀爀琀栀 㴀 　砀㄀㄀　⼀⨀℀㰀 䘀漀甀爀琀栀 焀甀愀搀爀愀渀琀Ⰰ 挀漀渀琀愀椀渀猀 砀ⴀ愀砀氀攀  ⨀⼀਀†  †  紀㬀਀਀†  †__Constructor_Destructor public:
  †  †//!  䐀攀昀愀甀氀琀 挀漀渀猀琀爀甀挀琀漀爀⸀尀溞�ꑧ蒐⁑ﵥ瀀਀†  †  䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀⤀㨀倀漀氀椀挀礀⠀⤀笀 紀਀†  †  ⼀⼀℀†Constructor with x and y.\n以x,y为参数的构造函数
  †  †/*!
  †  †  *  †\param  砀†a x value of a coord
  †  †  *  †\param y  愀 礀 瘀愀氀甀攀 漀昀 愀 挀漀漀爀搀਀†  †    ⨀⼀਀†  †  攀砀瀀氀椀挀椀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀ 挀漀渀猀琀 吀☀ 砀Ⰰ挀漀渀猀琀 吀☀ 礀 ⤀㨀倀漀氀椀挀礀⠀ 砀Ⰰ 礀 ⤀笀 紀਀†  †  ⼀⼀℀†Copy constructor.\n复制构造函数
  †  †DyadCoordinate( const DyadCoordinate<T,Policy>& coord ):Policy( coord ){ }
  †  †~DyadCoordinate(){ }

  †  开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†get the imprecise quadrant of the coord.\n获取该点的imprecise quadrant
  †  †/*!
  †  †  *  †\return  the enum  #ImpreciseQuadrant
  †  †  *  †  椀昀 琀栀攀 挀漀漀爀搀 猀琀愀渀搀猀 愀琀 漀爀椀最椀渀 瀀漀椀渀琀 Ⰰ琀栀攀 瘀愀氀甀攀 椀猀 䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀㨀㨀䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀开伀爀椀最椀渀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀 最攀琀䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀⠀⤀ 挀漀渀猀琀笀਀†  †  †uint32 ret = ImpreciseQuadrant_Origin;
  †  †  ⼀⼀䤀洀瀀爀攀挀椀猀攀儀甀愀搀爀愀渀琀 爀攀琀 㴀 㬀਀†  †  †if( Comparer<T>::isLowerThanZero( Policy::m_x ) ){
  †  †  †ret |= 0x011;
  †  †  紀਀†  †  †if( Comparer<T>::isLowerThanZero( Policy::m_y ) ){
  †  †  †ret |=  0x101;
  †  †  紀਀†  †  †return static_cast<ImpreciseQuadrant>(ret);
  †  †}

  †  †/*!  䜀攀琀 琀栀攀 堀ⴀ挀漀漀爀搀 眀椀琀栀 挀漀渀猀琀 爀攀昀攀爀攀渀挀攀⸀尀溃띓혀塗偨ݶ葞㡟ᕵ⠀ ⨀⼀਀†  †  椀渀氀椀渀攀 挀漀渀猀琀 吀☀ 最攀琀堀⠀⤀ 挀漀渀猀琀 笀਀†  †  †return Policy::m_x;
  †  †}

  †  †//!  䜀攀琀 琀栀攀 夀ⴀ挀漀漀爀搀 眀椀琀栀 挀漀渀猀琀 爀攀昀攀爀攀渀挀攀⸀尀溃띓혀套偨ݶ葞㡟ᕵ⠀਀†  †  椀渀氀椀渀攀 挀漀渀猀琀 吀☀ 最攀琀夀⠀⤀ 挀漀渀猀琀 笀਀†  †  †return Policy::m_y;
  †  †}

  †  开开匀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†Set the X-coord.\n设置X坐标
  †  †inline void setX( const T& x ){
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 㴀 砀㬀਀†  †  紀਀†  †  ⼀⼀℀†Set the Y-coord.\n设置Y坐标
  †  †inline void setY( const T& y ){
  †  †  倀漀氀椀挀礀㨀㨀洀开礀 㴀 礀㬀਀†  †  紀਀†  †  ⼀⼀℀†Set X & Y coordinate\n设置X和Y坐标
  †  †inline void setCoordinate( const T& x, const T&y){
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 㴀 砀㬀਀†  †  †Policy::m_y = y;
  †  †}

  †  开开䌀栀攀挀欀攀爀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†Check the coordinate is the origin.\n判别该点是否为原点
  †  †bool isOrigin() const {
  †  †  爀攀琀甀爀渀 倀漀氀椀挀礀㨀㨀开椀猀伀爀椀最椀渀⠀⤀㬀਀†  †  紀਀਀†  †public:
  †  †//!  䜀攀琀 琀栀攀 愀瀀瀀爀漀砀椀洀愀琀攀 搀椀猀琀愀渀挀攀 戀攀琀眀攀攀渀 挀漀漀爀搀 愀渀搀 漀爀椀最椀渀⸀尀溃띓홥㥰륒こ齰륶蒏텏㱐㰀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀昀␀†d=dx+dy  尀昀␀ 眀栀椀挀栀 洀攀愀渀猀 椀琀✀氀氀 爀攀琀甀爀渀 愀 愀瀀瀀爀漀砀椀洀愀琀攀 搀椀猀琀愀渀挀攀਀†  †    ⨀†  戀攀琀眀攀攀渀 琀栀攀 挀漀漀爀搀 愀渀搀 琀栀攀 漀爀椀最椀渀Ⰰ 戀甀琀 椀琀 洀漀爀攀 昀愀猀琀攀爀 琀栀愀渀 瀀爀攀挀椀攀猀攀 漀渀攀⸀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 吀 洀愀渀栀愀琀琀愀渀䰀攀渀最琀栀⠀⤀ 挀漀渀猀琀 笀਀†  †  †return std::abs(Policy::m_x) + std::abs(Policy::m_y);
  †  †}
  †  †//!  䜀攀琀 琀栀攀 搀椀猀琀愀渀挀攀 戀攀琀眀攀攀渀 琀栀椀猀 挀漀漀爀搀 愀渀搀 愀渀漀琀栀攀爀⸀尀溃띟靎⑰릍�묀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀爀攀琀甀爀渀 琀栀攀 搀椀猀琀愀渀挀攀 椀渀 搀漀甀戀氀攀⹎㪋�뭐㰀਀†  †    ⨀਀†  †    ⨀†  吀栀攀 搀椀猀琀愀渀挀攀 挀愀氀挀甀氀愀琀椀漀渀 昀漀爀洀甀氀愀 椀猀 挀漀洀洀漀渀 琀漀 猀攀攀 尀昀␀ 搀㴀尀猀焀爀琀笀⠀砀ⴀ挀漀漀爀搀⸀砀⤀帀㈀⬀⠀礀ⴀ挀漀漀爀搀⸀礀⤀帀㈀紀 尀昀␀਀†  †    ⨀⼀਀†  †  搀漀甀戀氀攀 挀愀氀䐀椀猀琀愀渀挀攀䈀礀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀☀ 挀漀漀爀搀 ⤀ 挀漀渀猀琀笀਀†  †  †return Policy::_calDistanceBy( coord );
  †  †}
  †  †//!  䜀攀琀 琀栀攀 搀椀猀琀愀渀挀攀 戀攀琀眀攀攀渀 琀栀椀猀 挀漀漀爀搀 愀渀搀 漀爀椀最椀渀⸀尀溃띟鞍�齰륶葎⑰릍�묀਀†  †  搀漀甀戀氀攀 挀愀氀䐀椀猀琀愀渀挀攀䈀礀伀爀椀最椀渀⠀⤀ 挀漀渀猀琀 笀਀†  †  †return Policy::_calDistanceByOrigin();
  †  †}
  †  †//!  䜀攀琀 琀栀攀 搀攀琀攀爀洀椀渀愀渀琀 戀礀 甀猀椀渀最 砀 愀渀搀 礀 愀猀 攀氀攀洀攀渀琀猀⸀尀湎堀奎㩑䍽⁶蒈䱒᝟ༀ਀†  †  ⼀⨀℀਀†  †    ⨀†  尀爀攀琀甀爀渀 琀栀攀 搀攀琀攀爀洀椀渀愀渀琀 漀爀 挀爀漀猀猀†.为行列式或是两点叉积
  †  †  *
  †  †  *  †Here's the formula :\f$ det=\left[\begin{array}{cc} x1 & y1 \\ x2 & y2\end{array}  尀爀椀最栀琀崀 尀昀␀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 搀漀甀戀氀攀 搀攀琀攀爀洀椀渀愀渀琀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀☀ 挀漀漀爀搀 ⤀ 挀漀渀猀琀笀਀†  †  †return Policy::m_x * coord.m_y - Policy::m_y * coord.m_x;
  †  †}

  †  开开䈀礀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†x and y are translated by a distance.\n XY同时偏移一段距离
  †  †/*!
  †  †  *  †\param d  琀爀愀渀猀氀愀琀攀搀 搀椀猀琀愀渀挀攀਀†  †    ⨀†  戀漀琀栀 砀 愀渀搀 礀 眀椀氀氀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 琀爀愀渀猀氀愀琀攀搀䈀礀䈀漀琀栀⠀ 挀漀渀猀琀 吀☀ 搀 ⤀ 笀਀†  †  †Policy::m_x += d;
  †  †  倀漀氀椀挀礀㨀㨀洀开礀 ⬀㴀 搀㬀਀†  †  †return *this;
  †  †}
  †  †//!  砀 眀椀氀氀 戀攀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀砀⸀尀渀†X偏移dx量
  †  †inline DyadCoordinate<T,Policy>& translatedByX( const T& dx ) {
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 ⬀㴀 搀砀㬀਀†  †  †return *this;
  †  †}
  †  †//!  礀 眀椀氀氀 戀攀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀礀⸀尀渀†Y偏移dy量
  †  †inline DyadCoordinate<T,Policy>& translatedByY( const T& dy ) {
  †  †  倀漀氀椀挀礀㨀㨀洀开礀 ⬀㴀 搀礀㬀਀†  †  †return *this;
  †  †}
  †  †//!  砀 眀椀氀氀 戀攀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀砀Ⰰ 礀 眀椀氀氀 戀攀 琀爀愀渀猀氀愀琀攀搀 戀礀 搀礀⸀尀渀†X偏移dx量,Y偏移dy量
  †  †inline DyadCoordinate<T,Policy>& translatedByEach( const T& dx, const T& dy ) {
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 ⬀㴀 搀砀㬀਀†  †  †Policy::m_y += dy;
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀਀†  †  椀渀氀椀渀攀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 琀爀愀渀猀氀愀琀攀搀䈀礀⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 搀 ⤀ 笀਀†  †  †Policy::m_x += d.m_x;
  †  †  倀漀氀椀挀礀㨀㨀洀开礀 ⬀㴀 搀⸀洀开礀㬀਀†  †  †return *this;
  †  †}

  †  开开吀漀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀਀†  †  ⼀⼀℀†translate to a new coord with both x and y shifted by d .\n 返回一个XY都偏移d值的点
  †  †inline DyadCoordinate<T,Policy> translatesToBoth( const T& d ) const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⬀ 搀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⬀ 搀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†translate to a new coord with x shifted by dx and y dy .\n 返回一个X偏移dx,Y偏移dy值的点
  †  †inline DyadCoordinate<T,Policy> translatesToEach( const T& dx, const T& dy ) const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⬀ 搀砀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⬀ 搀礀⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†translate to a new coord with shifted by another coord.  尀渀†返回一个距离另一个点偏移的点
  †  †inline DyadCoordinate<T,Policy> translatesTo( const DyadCoordinate<T,Policy>& coord ) const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⬀ 挀漀漀爀搀⸀洀开砀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⬀ 挀漀漀爀搀⸀洀开礀⤀㬀਀†  †  紀਀਀†  †__Overloaded_Methods public:
  †  †//!  䌀栀攀挀欀 琀眀漀 挀漀漀爀搀 椀猀 琀栀攀 猀愀洀攀਀†  †  椀渀氀椀渀攀 戀漀漀氀 漀瀀攀爀愀琀漀爀 㴀㴀 ⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 挀漀漀爀搀 ⤀ 挀漀渀猀琀 笀਀†  †  †return Comparer<T>::isEqualTo( Policy::m_x, coord.m_x ) && Comparer<T>::isEqualTo( Policy::m_y, coord.m_y );
  †  †}
  †  †inline bool operator != ( const DyadCoordinate<T,Policy>& coord ) const {
  †  †  爀攀琀甀爀渀 ℀䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䔀焀甀愀氀吀漀⠀ 倀漀氀椀挀礀㨀㨀洀开砀Ⰰ 挀漀漀爀搀⸀洀开砀 ⤀  簀簀 ℀䌀漀洀瀀愀爀攀爀㰀吀㸀㨀㨀椀猀䔀焀甀愀氀吀漀⠀ 倀漀氀椀挀礀㨀㨀洀开礀Ⰰ 挀漀漀爀搀⸀洀开礀 ⤀ 㬀਀†  †  紀਀਀†  †  ⼀⼀℀†Assign operator
  †  †inline DyadCoordinate<T,Policy>& operator = ( const DyadCoordinate<T,Policy>& coord ){
  †  †  倀漀氀椀挀礀㨀㨀漀瀀攀爀愀琀漀爀 㴀⠀ 挀漀漀爀搀 ⤀㬀਀†  †  †return *this;
  †  †}
  †  †//!  琀爀愀渀猀氀愀琀攀 琀漀 愀 渀攀眀 挀漀漀爀搀 眀椀琀栀 猀栀椀昀琀攀搀 戀礀 愀渀漀琀栀攀爀 挀漀漀爀搀⸀†\n ₏푖�N⪍�뭓N⩰륐佹ﭶ葰뤀਀†  †  ⼀⨀℀਀†  †    ⨀†  尀猀愀 琀爀愀渀猀氀愀琀攀猀吀漀† , translatesToEach
  †  †  */
  †  †inline DyadCoordinate<T,Policy> operator + ( const DyadCoordinate<T,Policy>& coord ) const {
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⬀ 挀漀漀爀搀⸀洀开砀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⬀ 挀漀漀爀搀⸀洀开礀 ⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†translate to a new coord with reversed shifted by another coord.  尀渀†返回一个距离另一个点逆偏移的点
  †  †inline DyadCoordinate<T,Policy> operator - ( const DyadCoordinate<T,Policy>& coord ) const {
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⴀ 挀漀漀爀搀⸀洀开砀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⴀ 挀漀漀爀搀⸀洀开礀 ⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get a coord with both x and y multiplied by factor
  †  †inline DyadCoordinate<T,Policy> operator * ( const T& factor ) const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⨀ 昀愀挀琀漀爀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⨀ 昀愀挀琀漀爀 ⤀㬀਀†  †  紀਀†  †  ⼀⼀℀†Get a coord with both x and y divided by factor
  †  †inline DyadCoordinate<T,Policy> operator / ( const T& factor ) const{
  †  †  爀攀琀甀爀渀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀⠀ 倀漀氀椀挀礀㨀㨀洀开砀 ⼀ 昀愀挀琀漀爀Ⰰ 倀漀氀椀挀礀㨀㨀洀开礀 ⼀ 昀愀挀琀漀爀 ⤀㬀਀†  †  紀਀਀†  †  ⼀⼀℀†translated by anther coord.\n ₍�N⩰륐佹ﬀ਀†  †  ⼀⨀℀਀†  †    ⨀†  尀猀愀 琀爀愀渀猀氀愀琀攀搀䈀礀䔀愀挀栀਀†  †    ⨀⼀਀†  †  椀渀氀椀渀攀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 漀瀀攀爀愀琀漀爀 ⬀㴀 ⠀ 挀漀渀猀琀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀吀Ⰰ倀漀氀椀挀礀㸀☀ 挀漀漀爀搀 ⤀笀਀†  †  †Policy::m_x += coord.m_x;
  †  †  倀漀氀椀挀礀㨀㨀洀开礀 ⬀㴀 挀漀漀爀搀⸀洀开礀㬀਀†  †  †return *this;
  †  †}
  †  †//!  爀攀瘀攀爀猀攀搀 琀爀愀渀猀氀愀琀攀搀 戀礀 愀渀琀栀攀爀 挀漀漀爀搀⸀尀渀†距另一个点逆偏移
  †  †inline DyadCoordinate<T,Policy>& operator -= ( const DyadCoordinate<T,Policy>& coord ){
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 ⴀ㴀 挀漀漀爀搀⸀洀开砀㬀਀†  †  †Policy::m_y -= coord.m_y;
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀†  †  ⼀⼀℀†Both x and y are multiplied by factor
  †  †inline DyadCoordinate<T,Policy>& operator *= ( const T& factor ){
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 ⨀㴀 昀愀挀琀漀爀㬀਀†  †  †Policy::m_y *= factor;
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀†  †  ⼀⼀℀†Both x and y are divided by factor
  †  †inline DyadCoordinate<T,Policy>& operator /= ( const T& factor ){
  †  †  倀漀氀椀挀礀㨀㨀洀开砀 ⼀㴀 昀愀挀琀漀爀㬀਀†  †  †Policy::m_y /= factor;
  †  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †  紀਀†  紀㬀਀਀†  琀礀瀀攀搀攀昀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀猀椀渀琀㌀㈀㸀 䤀渀琀攀最攀爀䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㬀਀†  琀礀瀀攀搀攀昀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀猀椀渀琀㌀㈀㸀 䐀椀最椀琀䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㬀਀†  ⼀⨀⨀㰀 吀栀椀猀 椀猀 琀栀攀 搀漀挀甀洀攀渀琀愀琀椀漀渀 昀漀爀 琀栀攀 瀀爀攀挀攀搀椀渀最 琀礀瀀攀搀攀昀 ⨀⼀਀਀਀†  ⼀⼀℀†Coordinate in float
  †typedef DyadCoordinate<float> FloatDyadCoordinate;
  †//!  䌀漀漀爀搀椀渀愀琀攀 椀渀 搀漀甀戀氀攀਀†  琀礀瀀攀搀攀昀 䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㰀搀漀甀戀氀攀㸀 刀攀愀氀䐀礀愀搀䌀漀漀爀搀椀渀愀琀攀㬀਀਀਀†}//Core
}//Magna

#endif  ⼀⨀†DYADCOORDINATE_H  ⨀⼀�