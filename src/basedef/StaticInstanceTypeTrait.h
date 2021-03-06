/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef STATICINSTANCETYPETRAIT_H
#define STATICINSTANCETYPETRAIT_H

namespace Magna{  ਀† namespace Core{
   †/*!  尀戀爀椀攀昀਀†   †  䌀栀攀挀欀 琀栀攀 椀渀猀琀愀渀挀攀 琀礀瀀攀 愀渀搀 挀漀渀猀琀爀愀椀琀 琀礀瀀攀 愀爀攀 洀愀琀挀栀攀搀⸀਀†  † ⁒⑒⭛鹏譓ᙶ葼筗譎๾�驶葾ꙧ彼筗警⽔♓㦑䴀਀†     ⨀⼀਀†   ⼀⨀℀†
  †   *  䤀琀✀猀 挀漀洀洀漀渀 琀漀 猀攀攀 眀栀攀渀 琀攀洀瀀氀愀琀攀 瀀爀漀最爀愀洀洀椀渀最⸀਀†     ⨀†And with this tool, only by calling checks() can constrain the type you input.
  †   *  ਀†     ⨀†Here's three-step constraint: give the constraint type as template parameter
  †   *  琀栀攀渀 挀愀氀氀 挀栀攀挀欀猀⠀⤀ 愀渀搀 昀漀爀 琀栀攀 氀愀猀琀 瀀愀爀琀 椀昀 琀栀攀 琀眀漀 愀爀攀 渀漀琀 洀愀琀挀栀攀搀 挀漀洀瀀椀氀攀爀 琀栀爀漀眀猀⸀਀†     ⨀਀†     ⨀†It's only for static check, and when you refer to any RTTI or dynamic identification
  †   *  唀猀攀 吀礀瀀攀䤀搀攀渀琀椀昀椀攀爀 眀栀椀挀栀 挀愀渀 椀渀瀀甀琀 愀 椀渀猀琀愀渀挀攀 愀猀 愀 瀀愀爀愀洀攀琀攀爀 愀渀搀 礀漀甀✀氀氀 最攀琀 愀 瀀攀爀猀椀猀琀攀渀挀攀 椀搀攀渀琀椀昀椀攀爀⸀਀†     ⨀਀†     ⨀†\sa StaticTypeTrait, TypeIdentifier
  †   * 
  †   *  尀琀瀀愀爀愀洀 䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀 琀栀攀 挀漀渀猀琀爀愀椀渀琀 琀礀瀀攀਀†     ⨀਀†     ⨀†Here's a example
  †   *  尀挀漀搀攀笀⸀挀瀀瀀紀਀†     ⨀†Test m_test;
  †   *  匀琀愀琀椀挀䤀渀猀琀愀渀挀攀吀礀瀀攀吀爀愀椀琀㰀一漀琀吀攀猀琀㸀㨀㨀挀栀攀挀欀猀⠀洀开琀攀猀琀⤀㬀⼀⼀攀爀爀漀爀℀਀†     ⨀†\endcode
  †   *
  †   *   尀愀甀琀栀漀爀†Magnus
  †   *   尀瘀攀爀猀椀漀渀   ㄀⸀　⸀　⸀　਀†     ⨀† \date       2013/1/15
  †   */
  † template<typename Constraint_Type>
  † class StaticInstanceTypeTrait :Uninstantiable{
  † public:
  †   ⼀⼀℀†Checks the static type of the instance is equal to constraint one
  †   ⼀⨀℀†
  †     ⨀†When not matched, will throw an error \em "Shall_Matches_Given_Type"
  †     ⨀†\param instance the check instance you must input  ਀†  †   */
  †   琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䤀渀猀琀愀渀挀攀吀礀瀀攀㸀਀†  † static void checks( const InstanceType& instance ){
  †  † typedef StaticTypeTrait<InstanceType,Constraint_Type> TypeTrait;
  †  † COMPILTER_TIME_ASSERT( TypeTrait::isMatched, Shall_Matches_Given_Type)
  †  †}
  † };

   紀⼀⼀䌀漀爀攀਀紀⼀⼀䴀愀最渀愀਀⌀攀渀搀椀昀†/*  匀吀䄀吀䤀䌀䤀一匀吀䄀一䌀䔀吀夀倀䔀吀刀䄀䤀吀开䠀†*/