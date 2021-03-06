/*
  * This file is part of core library of Magna framework
  *
  * Copyright (c) 2012 by Magnus
  */
#ifndef STATICTYPETRAIT_H
#define STATICTYPETRAIT_H

#include "NullType.h"
#include "SystemDef.h"
#include "BaseTypes.h"
#include "Uninstantiable.h"

namespace Magna{
   渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀†   ⼀⨀℀†\brief
  †  †Use for statically checking type with several constraint types.
  †  †用来静态检测输入类型是否符合约束的类型。
  †*/

  † /*!  尀搀攀琀愀椀氀猀਀†     ⨀†When need for checking type won't match any
  †   *  挀漀渀猀琀爀愀椀渀琀 琀礀瀀攀猀Ⰰ 挀漀洀瀀椀氀攀爀 眀椀氀氀 眀愀爀渀 礀漀甀⸀਀†     ⨀਀†     ⨀†如果需要检测的类型不符合约束类型，
  †   * ⁿᚋ텖桒᥏ᩢꖕᤰȀ਀†     ⨀਀†     ⨀†\tparam Need_For_Checking_Type the type needs being checked
  †   *  †被检测的类型
  †   *  尀琀瀀愀爀愀洀 䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀 琀栀攀 挀漀渀猀琀爀愀椀渀琀 琀礀瀀攀猀਀†     ⨀† ⁵⡧敾ꙧ彶葼筗謀਀†     ⨀†\tparam Recursion_Type_Trait_Can_Be_Nullptr_Type another StaticTypeTrait uses for recursion checking
  †   *  †default one is NullType
  †   *  †另一个StaticTypeTrait，用来循环检测，默认值为NullType
  †   *  尀愀琀琀攀渀琀椀漀渀 琀栀攀 ㄀猀琀 琀攀洀瀀氀愀琀攀 瀀愀爀愀洀攀琀攀爀 漀昀 愀渀漀琀栀攀爀 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀 眀栀椀挀栀 爀攀瀀氀愀挀攀猀 琀栀攀 ㌀爀搀 琀攀洀瀀氀愀琀攀 瀀愀爀愀洀਀†     ⨀†  猀栀漀甀氀搀 戀攀 猀愀洀攀 琀漀 琀栀攀 瀀爀椀洀愀爀礀 漀渀攀✀猀਀†     ⨀†  尀源቟剶萀匀琀愀琀椀挀吀礀瀀攀吀爀愀椀瑶葻ⱎN⩓쉥灧Y絔豎㭏卶葻ⱎN⩓쉥灶ఀ਀†     ⨀਀†     ⨀†  尀戀 䔀⸀最⸀਀†     ⨀†  尀挀漀搀攀笀⸀挀瀀瀀紀਀†     ⨀਀†     ⨀†  ⼀⼀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀 㴀 昀氀漀愀琀਀†     ⨀†  ⼀⼀䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀 㴀 椀渀琀Ⰰ搀漀甀戀氀攀Ⰰ挀栀愀爀਀†     ⨀†  䌀伀䴀倀䤀䰀吀䔀刀开吀䤀䴀䔀开䄀匀匀䔀刀吀⠀⠀匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀昀氀漀愀琀Ⰰ椀渀琀Ⰰ 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀昀氀漀愀琀Ⰰ搀漀甀戀氀攀Ⰰ 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀昀氀漀愀琀Ⰰ挀栀愀爀㸀 㸀 㸀㨀㨀椀猀䴀愀琀挀栀攀搀⤀Ⰰ 匀栀愀氀氀开䴀愀琀挀栀攀猀开䌀栀愀爀开䤀渀琀开䐀漀甀戀氀攀⤀਀†     ⨀†   尀攀渀搀挀漀搀攀਀†     ⨀਀†     ⨀† \author  䴀愀最渀甀猀਀†     ⨀† \version   1.0.0.0
  †   *   尀搀愀琀攀†  ㈀　㄀㈀⼀㄀㈀⼀㈀㘀਀†     ⨀⼀਀਀⌀椀昀搀攀昀 开䴀匀䌀开嘀䔀刀਀†  †template
  †  †  㰀਀†  †  †  琀礀瀀攀渀愀洀攀 一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀਀†  †  †  Ⰰ挀氀愀猀猀 刀攀挀甀爀猀椀漀渀开吀礀瀀攀开吀爀愀椀琀开䌀愀渀开䈀攀开一甀氀氀瀀琀爀开吀礀瀀攀 㴀 一甀氀氀吀礀瀀攀਀†  †  †>
  †  挀氀愀猀猀 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀 㨀 唀渀椀渀猀琀愀渀琀椀愀戀氀攀笀਀†  †  瀀爀椀瘀愀琀攀㨀਀†  †  †template<typename _type>
  †  †  猀琀爀甀挀琀 倀爀椀瘀愀琀攀吀礀瀀攀吀爀愀椀琀笀਀†  †  †  琀礀瀀攀搀攀昀 挀栀愀爀 洀愀爀欀攀爀嬀㈀崀㬀਀†  †  †};

  †  †  琀攀洀瀀氀愀琀攀㰀㸀਀†  †  †struct PrivateTypeTrait<Constraint_Type>{
  †  †  †typedef char marker;
  †  †  紀㬀਀†  †  瀀甀戀氀椀挀㨀਀†  †  †//! A static checking result \n类型判断后的结果值
  †  †  ⼀⨀℀਀†  †  †  *    䌀愀渀 戀攀 甀猀攀搀 愀猀 愀 猀琀愀琀椀挀 瘀愀氀甀攀 琀漀 猀栀漀眀 琀栀攀 爀攀猀甀氀琀਀†  †  †  *  †\n 可以被用来作为判别结果
  †  †    ⨀਀†  †  †  *  †\var isMatched
  †  †    ⨀†  伀渀氀礀 椀渀 ㄀⠀琀爀甀攀⤀ 漀爀 　⠀昀愀氀猀攀⤀਀†  †  †  *  †值只能是1(真)或0(假)
  †  †    ⨀⼀਀†  †  †enum { isMatched=(sizeof PrivateTypeTrait<Need_For_Checking_Type>::marker\
  †  †  †==sizeof PrivateTypeTrait<Constraint_Type>::marker) || Recursion_Type_Trait_Can_Be_Nullptr_Type::isMatched };
  †  紀㬀਀਀†  †template
  †  †  㰀਀†  †  †  琀礀瀀攀渀愀洀攀 一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀਀†  †  †>
  †  挀氀愀猀猀 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀Ⰰ䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀 㨀 唀渀椀渀猀琀愀渀琀椀愀戀氀攀笀਀†  †  瀀爀椀瘀愀琀攀㨀਀†  †  †template<typename _type>
  †  †  猀琀爀甀挀琀 倀爀椀瘀愀琀攀吀礀瀀攀吀爀愀椀琀笀਀†  †  †  琀礀瀀攀搀攀昀 挀栀愀爀 洀愀爀欀攀爀嬀㈀崀㬀਀†  †  †};

  †  †  琀攀洀瀀氀愀琀攀㰀㸀਀†  †  †struct PrivateTypeTrait<Constraint_Type>{
  †  †  †typedef char marker;
  †  †  紀㬀਀†  †  瀀甀戀氀椀挀㨀਀†  †  †enum{ isMatched=(sizeof PrivateTypeTrait<Need_For_Checking_Type>::marker\
  †  †  †==sizeof PrivateTypeTrait<Constraint_Type>::marker) };
  †  紀㬀਀਀⌀攀氀椀昀 搀攀昀椀渀攀搀 开开䜀一唀䌀开开਀            琀攀洀瀀氀愀琀攀਀†  †  †<
  †  †  †typename Need_For_Checking_Type
  †  †  †,typename Constraint_Type
  †  †  †,class Recursion_Type_Trait_Can_Be_Nullptr_Type = NullType
  †  †  㸀਀†  †class StaticTypeTrait : Uninstantiable{
  †  †private:
  †  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开琀礀瀀攀Ⰰ 挀氀愀猀猀 䐀 㴀 瘀漀椀搀㸀਀†  †  †struct PrivateTypeTrait{
  †  †  †typedef char marker[2];
  †  †  紀㬀਀਀                    琀攀洀瀀氀愀琀攀㰀挀氀愀猀猀 䐀㸀਀†  †  †struct PrivateTypeTrait<Constraint_Type,D>{
  †  †  †typedef char marker;
  †  †  紀㬀਀†  †  瀀甀戀氀椀挀㨀਀†  †  †//! A static checking result \n类型判断后的结果值
  †  †  ⼀⨀℀਀†  †  †  *    䌀愀渀 戀攀 甀猀攀搀 愀猀 愀 猀琀愀琀椀挀 瘀愀氀甀攀 琀漀 猀栀漀眀 琀栀攀 爀攀猀甀氀琀਀†  †  †  *  †\n 可以被用来作为判别结果
  †  †    ⨀਀†  †  †  *  †\var isMatched
  †  †    ⨀†  伀渀氀礀 椀渀 ㄀⠀琀爀甀攀⤀ 漀爀 　⠀昀愀氀猀攀⤀਀†  †  †  *  †值只能是1(真)或0(假)
  †  †    ⨀⼀਀†  †  †enum { isMatched=(sizeof ( typename PrivateTypeTrait<Need_For_Checking_Type>::marker) ==sizeof (typename PrivateTypeTrait<Constraint_Type>::marker) ) || Recursion_Type_Trait_Can_Be_Nullptr_Type::isMatched };
  †  紀㬀਀਀            琀攀洀瀀氀愀琀攀਀†  †  †<
  †  †  †typename Need_For_Checking_Type
  †  †  †,typename Constraint_Type
  †  †  㸀਀†  †class StaticTypeTrait<Need_For_Checking_Type,Constraint_Type,NullType> : Uninstantiable{
  †  †private:
  †  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 开琀礀瀀攀Ⰰ 挀氀愀猀猀 䐀 㴀 瘀漀椀搀 㸀਀†  †  †struct PrivateTypeTrait{
  †  †  †typedef char marker[2];
  †  †  紀㬀਀਀†  †  †template<class D>
  †  †  猀琀爀甀挀琀 倀爀椀瘀愀琀攀吀礀瀀攀吀爀愀椀琀㰀䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀Ⰰ䐀㸀笀਀†  †  †  琀礀瀀攀搀攀昀 挀栀愀爀 洀愀爀欀攀爀㬀਀†  †  †};
  †  †public:
  †  †  攀渀甀洀笀 椀猀䴀愀琀挀栀攀搀㴀⠀猀椀稀攀漀昀 ⠀琀礀瀀攀渀愀洀攀 倀爀椀瘀愀琀攀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀㸀㨀㨀洀愀爀欀攀爀⤀ 㴀㴀猀椀稀攀漀昀 ⠀琀礀瀀攀渀愀洀攀 倀爀椀瘀愀琀攀吀礀瀀攀吀爀愀椀琀㰀䌀漀渀猀琀爀愀椀渀琀开吀礀瀀攀㸀㨀㨀洀愀爀欀攀爀⤀ ⤀  紀㬀਀†  †};

#else
#error UNKNOW_COMPILE_ENV
#endif/*  _MSC_VER    */



  †  ⼀⨀℀†\brief

  †    ⨀⼀਀†  †template<typename Need_For_Checking_Type>
  †  挀氀愀猀猀 䐀椀最椀琀匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀 㨀 瀀甀戀氀椀挀 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  †  †  †  †  Ⰰ 猀椀渀琀㠀Ⰰ 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  †  †  †  †  †, sint16, StaticTypeTrait<Need_For_Checking_Type
  †  †  †  †  †  †  †  †,sint32, StaticTypeTrait<Need_For_Checking_Type
  †  †  †  †  †  †  †  †  Ⰰ猀椀渀琀㘀㐀Ⰰ 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  †  †  †  †  †  †  Ⰰ甀椀渀琀㠀Ⰰ 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  †  †  †  †  †  †  †,uint16, StaticTypeTrait<Need_For_Checking_Type
  †  †  †  †  †  †  †  †  †  †,uint32, StaticTypeTrait<Need_For_Checking_Type,uint64> > > > > > > >{
  †  紀㬀਀਀†  †/*!  尀戀爀椀攀昀਀਀†  †  */
  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀㸀਀†  †class RealStaticTypeTrait : public StaticTypeTrait<Need_For_Checking_Type
  †  †  †  †  †  †  †  †  †  †,float, StaticTypeTrait<Need_For_Checking_Type
  †  †  †  †  †  †  †  †  †  †  Ⰰ搀漀甀戀氀攀Ⰰ匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀一攀攀搀开䘀漀爀开䌀栀攀挀欀椀渀最开吀礀瀀攀਀†  †  †  †  †  †  †  †  †  †  †  Ⰰ氀漀渀最 搀漀甀戀氀攀㸀 㸀 㸀笀਀†  †};


  †  ⼀⨀℀਀†  †  *  †\def  䤀匀开匀吀䄀吀䤀䌀开吀夀倀䔀开䴀䄀吀䌀䠀䔀䐀开䈀夀㄀⠀渀攀攀搀开昀漀爀开挀栀攀挀欀开琀礀瀀攀Ⰰ挀漀渀猀琀爀愀椀渀琀开琀礀瀀攀⤀਀†  †  *  †  刀攀瀀氀愀挀攀洀攀渀琀 洀愀挀爀漀 爀攀瀀氀愀挀攀猀 匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀 琀攀洀瀀氀愀琀攀 挀氀愀猀猀 眀椀琀栀 ㈀ 琀攀洀瀀氀愀琀攀 瀀愀爀愀洀攀琀攀爀猀਀†  †  *  † ⁦｣扛迿౦｣扎蘀㉎⩪ⅲ䡓쉥灶萀匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀਀†  †  */
  †  开开䐀攀昀椀渀椀琀椀漀渀猀਀†  †#define IS_STATIC_TYPE_MATCHED_BY1(need_for_check_type,constraint_type)  尀਀†  †   †StaticTypeTrait<need_for_check_type,constraint_type>::isMatched

  †  ⼀⨀℀਀†  †  *  †\file StaticTypeTrait.h
  †    ⨀†  尀搀攀昀†IS_STATIC_TYPE_MATCHED_BY2(need_for_check_type,constraint_type_1,constraint_type_2)
  †    ⨀†  †Replacement macro replaces StaticTypeTrait template class with 3 template parameters
  †    ⨀†  †替换宏，替换了3个模版参数的StaticTypeTrait
  †    ⨀⼀਀†  †#define IS_STATIC_TYPE_MATCHED_BY2(need_for_check_type,constraint_type_1,constraint_type_2)  尀਀†  †  †StaticTypeTrait<need_for_check_type,constraint_type_1\
  †  †  Ⰰ匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀渀攀攀搀开昀漀爀开挀栀攀挀欀开琀礀瀀攀Ⰰ挀漀渀猀琀爀愀椀渀琀开琀礀瀀攀开㈀㸀 㸀㨀㨀椀猀䴀愀琀挀栀攀搀਀਀†  †  /*!
  †    ⨀†  尀搀攀昀†IS_STATIC_TYPE_MATCHED_BY3(need_for_check_type,constraint_type_1,constraint_type_2,constraint_type_3)
  †    ⨀†  †Replacement macro replaces StaticTypeTrait template class with 4 template parameters
  †    ⨀†  †替换宏，替换了4个模版参数的StaticTypeTrait
  †    ⨀⼀਀†  †#define IS_STATIC_TYPE_MATCHED_BY3(need_for_check_type,constraint_type_1,constraint_type_2,constraint_type_3)  尀਀†  †  †  匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀渀攀攀搀开昀漀爀开挀栀攀挀欀开琀礀瀀攀Ⰰ挀漀渀猀琀爀愀椀渀琀开琀礀瀀攀开㄀尀਀†  †  †  Ⰰ匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀渀攀攀搀开昀漀爀开挀栀攀挀欀开琀礀瀀攀Ⰰ挀漀渀猀琀爀愀椀渀琀开琀礀瀀攀开㈀尀਀†  †  †  Ⰰ匀琀愀琀椀挀吀礀瀀攀吀爀愀椀琀㰀渀攀攀搀开昀漀爀开挀栀攀挀欀开琀礀瀀攀Ⰰ挀漀渀猀琀爀愀椀渀琀开琀礀瀀攀开㌀ 㸀 㸀 㸀㨀㨀椀猀䴀愀琀挀栀攀搀਀਀਀† }//Core
}//Magna

#endif  ⼀⨀†STATICTYPETRAIT_H  ⨀⼀�