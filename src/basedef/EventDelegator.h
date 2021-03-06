/*
#ifndef EVENTDELEGATOR_H
#define EVENTDELEGATOR_H

#include "basedef_lib.h"

#include "SystemDef.h"
#include "BaseTypes.h"
#include "CompilerTimeAssert.h"
#include "IsBaseOf.h"  

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䜀唀䤀笀਀†  挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀笀紀㬀਀਀†  琀攀洀瀀氀愀琀攀㰀਀†  †typename BaseType
  †  Ⰰ 琀礀瀀攀渀愀洀攀 倀愀爀愀洀攀琀攀爀吀礀瀀攀 㴀 一甀氀氀吀礀瀀攀਀†  㸀਀†  挀氀愀猀猀 䐀攀氀攀最愀琀漀爀㬀਀਀†  琀攀洀瀀氀愀琀攀㰀਀†  †typename BaseType
  †>
  †class BASEDEF_LIB_EXPORT Delegator<BaseType, NullType>{
  †  琀礀瀀攀搀攀昀 瘀漀椀搀⠀䈀愀猀攀吀礀瀀攀㨀㨀⨀䐀攀氀攀最愀琀漀爀吀礀瀀攀⤀⠀⤀㬀 ਀†  †__Constructor_Destructor public:
  †  䐀攀氀攀最愀琀漀爀⠀⤀਀†  †  㨀洀开搀攀氀攀最愀琀漀爀⠀ 一甀氀氀瀀琀爀 ⤀笀਀਀†  †}

  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䈀椀渀搀攀爀Ⰰ 琀礀瀀攀渀愀洀攀 䤀渀瀀甀琀倀愀爀愀洀攀琀攀爀吀礀瀀攀㸀਀†  †Delegator( void(Binder::*customizedDelegator )() )
  †  †:m_delegator( Nullptr ) {
  †  †  琀礀瀀攀搀攀昀 䤀猀䈀愀猀攀伀昀㰀䈀椀渀搀攀爀Ⰰ 䈀愀猀攀吀礀瀀攀㸀 䈀椀渀搀攀爀䤀猀䈀愀猀攀伀昀㬀਀†  †  †COMPILTER_TIME_ASSERT( BinderIsBaseOf::isTrue, Binder_Type_Error )

  †  †  洀开搀攀氀攀最愀琀漀爀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䐀攀氀攀最愀琀漀爀吀礀瀀攀 ⨀㸀⠀ ☀挀甀猀琀漀洀椀稀攀搀䐀攀氀攀最愀琀漀爀 ⤀㬀਀†  †} 

  †  䐀攀氀攀最愀琀漀爀⠀ 挀漀渀猀琀 䐀攀氀攀最愀琀漀爀㰀䈀愀猀攀吀礀瀀攀㸀☀ 搀 ⤀਀†  †  㨀洀开搀攀氀攀最愀琀漀爀⠀ 搀⸀洀开搀攀氀攀最愀琀漀爀 ⤀笀਀਀†  †}

  †public:
  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䈀椀渀搀攀爀㸀਀†  †void invoke( Binder&invoker){
  †  †typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
  †  †COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

  †  †  椀昀⠀ 洀开搀攀氀攀最愀琀漀爀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  ⠀椀渀瘀漀欀攀爀⸀⨀洀开搀攀氀攀最愀琀漀爀⤀⠀ 瀀愀爀愀 ⤀㬀਀†  †  †}  ਀†  †}

  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䈀椀渀搀攀爀㸀਀†  †void invoke( Binder*invoker ){
  †  †typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
  †  †COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

  †  †  椀昀⠀ 椀渀瘀漀欀攀爀 ℀㴀 一甀氀氀瀀琀爀 ☀☀ 洀开搀攀氀攀最愀琀漀爀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  ⠀椀渀瘀漀欀攀爀ⴀ㸀⨀洀开搀攀氀攀最愀琀漀爀⤀⠀ 瀀愀爀愀 ⤀㬀਀†  †  †}  ਀†  †}

  †  开开伀瘀攀爀氀漀愀搀攀搀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀਀†  †template<typename Binder>
  †  䐀攀氀攀最愀琀漀爀㰀䈀愀猀攀吀礀瀀攀㸀☀†operator = ( void(Binder::*customizedDelegator )() ){
  †  †typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
  †  †COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

  †  †  洀开搀攀氀攀最愀琀漀爀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䐀攀氀攀最愀琀漀爀吀礀瀀攀 ⨀㸀⠀ ☀挀甀猀琀漀洀椀稀攀搀䐀攀氀攀最愀琀漀爀 ⤀㬀਀਀†  †  洀开搀攀氀攀最愀琀漀爀 㴀 挀甀猀琀漀洀椀稀攀搀䐀攀氀攀最愀琀漀爀㬀਀†  †  爀攀琀甀爀渀 ⨀琀栀椀猀㬀਀†  †}

  †  戀漀漀氀 漀瀀攀爀愀琀漀爀 㴀㴀 ⠀ 挀漀渀猀琀 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀☀ 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀 ⤀笀਀†  †  爀攀琀甀爀渀 洀开搀攀氀攀最愀琀漀爀 㴀㴀 一甀氀氀瀀琀爀㬀਀†  †}

  †  戀漀漀氀 漀瀀攀爀愀琀漀爀 ℀㴀 ⠀ 挀漀渀猀琀 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀☀ 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀 ⤀ 笀਀†  †  爀攀琀甀爀渀 洀开搀攀氀攀最愀琀漀爀 ℀㴀 一甀氀氀瀀琀爀㬀਀†  †}

  †  戀漀漀氀 漀瀀攀爀愀琀漀爀 㴀㴀 ⠀ 挀漀渀猀琀 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀☀ 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀 ⤀ 挀漀渀猀琀笀਀†  †  爀攀琀甀爀渀 洀开搀攀氀攀最愀琀漀爀 㴀㴀 一甀氀氀瀀琀爀㬀਀†  †}

  †  戀漀漀氀 漀瀀攀爀愀琀漀爀 ℀㴀 ⠀ 挀漀渀猀琀 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀☀ 一甀氀氀瀀琀爀䐀攀氀攀最愀琀漀爀 ⤀ 挀漀渀猀琀 笀਀†  †  爀攀琀甀爀渀 洀开搀攀氀攀最愀琀漀爀 ℀㴀 一甀氀氀瀀琀爀㬀਀†  †}

  †  开开䐀愀琀愀开䘀椀攀氀搀 瀀爀椀瘀愀琀攀㨀਀†  †DelegatorType m_delegator;
  †};




  †template<
  †  †  †typename BaseType
  †  †  †, typename ParameterType
  †  †  †>
  †class BASEDEF_LIB_EXPORT Delegator{
  †  琀礀瀀攀搀攀昀 瘀漀椀搀⠀䈀愀猀攀吀礀瀀攀㨀㨀⨀䐀攀氀攀最愀琀漀爀吀礀瀀攀⤀⠀倀愀爀愀洀攀琀攀爀吀礀瀀攀☀⤀㬀 ਀†  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †Delegator()
  †  †:m_delegator( Nullptr ){
  †  †
  †  紀਀਀†  †template<typename Binder, typename InputParameterType>
  †  䐀攀氀攀最愀琀漀爀⠀ 瘀漀椀搀⠀䈀椀渀搀攀爀㨀㨀⨀挀甀猀琀漀洀椀稀攀搀䐀攀氀攀最愀琀漀爀 ⤀⠀䤀渀瀀甀琀倀愀爀愀洀攀琀攀爀吀礀瀀攀☀⤀ ⤀਀†  †  㨀洀开搀攀氀攀最愀琀漀爀⠀ 一甀氀氀瀀琀爀 ⤀ 笀਀†  †  琀礀瀀攀搀攀昀 䤀猀䈀愀猀攀伀昀㰀䤀渀瀀甀琀倀愀爀愀洀攀琀攀爀吀礀瀀攀Ⰰ 倀愀爀愀洀攀琀攀爀吀礀瀀攀㸀 倀愀爀愀洀攀琀攀爀䤀猀䈀愀猀攀伀昀㬀਀†  †  䌀伀䴀倀䤀䰀吀䔀刀开吀䤀䴀䔀开䄀匀匀䔀刀吀⠀ 倀愀爀愀洀攀琀攀爀䤀猀䈀愀猀攀伀昀㨀㨀椀猀吀爀甀攀Ⰰ 倀愀爀愀洀攀琀攀爀开吀礀瀀攀开䔀爀爀漀爀 ⤀਀਀†  †  洀开搀攀氀攀最愀琀漀爀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䐀攀氀攀最愀琀漀爀吀礀瀀攀 ⨀㸀⠀ ☀挀甀猀琀漀洀椀稀攀搀䐀攀氀攀最愀琀漀爀 ⤀㬀਀†  †}

  †  䐀攀氀攀最愀琀漀爀⠀ 挀漀渀猀琀 䐀攀氀攀最愀琀漀爀㰀䈀愀猀攀吀礀瀀攀Ⰰ 倀愀爀愀洀攀琀攀爀吀礀瀀攀㸀☀ 搀 ⤀਀†  †  㨀洀开搀攀氀攀最愀琀漀爀⠀ 搀⸀洀开搀攀氀攀最愀琀漀爀 ⤀笀਀†
  †  紀਀਀†  瀀甀戀氀椀挀㨀਀†  †template<typename Binder>
  †  瘀漀椀搀 椀渀瘀漀欀攀⠀ 䈀椀渀搀攀爀☀椀渀瘀漀欀攀爀Ⰰ  倀愀爀愀洀攀琀攀爀吀礀瀀攀☀ 瀀愀爀愀 ⤀笀਀†  †  琀礀瀀攀搀攀昀 䤀猀䈀愀猀攀伀昀㰀䈀椀渀搀攀爀Ⰰ 䈀愀猀攀吀礀瀀攀㸀 䈀椀渀搀攀爀䤀猀䈀愀猀攀伀昀䈀愀猀攀吀礀瀀攀㬀਀†  †  䌀伀䴀倀䤀䰀吀䔀刀开吀䤀䴀䔀开䄀匀匀䔀刀吀⠀ 䈀椀渀搀攀爀䤀猀䈀愀猀攀伀昀䈀愀猀攀吀礀瀀攀㨀㨀椀猀吀爀甀攀Ⰰ 䤀渀瘀漀欀攀爀开吀礀瀀攀开䔀爀爀漀爀 ⤀਀਀†  †  椀昀⠀ 洀开搀攀氀攀最愀琀漀爀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †(invoker.*m_delegator)( para );
  †  †}  ਀†  †}

  †  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䈀椀渀搀攀爀㸀਀†  †void invoke( Binder*invoker,  ParameterType& para ){
  †  †typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
  †  †COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

  †  †if( invoker != Nullptr && m_delegator != Nullptr ){
  †  †  ⠀椀渀瘀漀欀攀爀ⴀ㸀⨀洀开搀攀氀攀最愀琀漀爀⤀⠀ 瀀愀爀愀 ⤀㬀਀†  †  紀†
  †  紀਀਀†  开开伀瘀攀爀氀漀愀搀攀搀开䴀攀琀栀漀搀猀 瀀甀戀氀椀挀㨀਀†  †template<typename Binder>
  †  䐀攀氀攀最愀琀漀爀㰀䈀愀猀攀吀礀瀀攀Ⰰ 倀愀爀愀洀攀琀攀爀吀礀瀀攀㸀☀†operator = ( void(Binder::*customizedDelegator )(ParameterType&) ){
  †  †typedef IsBaseOf<InputParameterType, ParameterType> ParameterIsBaseOf;
  †  †COMPILTER_TIME_ASSERT( ParameterIsBaseOf::isTrue, Parameter_Type_Error )

  †  †m_delegator = *reinterpret_cast<DelegatorType *>( &customizedDelegator );

  †  †m_delegator = customizedDelegator;
  †  †return *this;
  †  紀਀਀†  †bool operator == ( const NullptrDelegator& NullptrDelegator ){
  †  †return m_delegator == Nullptr;
  †  紀਀਀†  †bool operator != ( const NullptrDelegator& NullptrDelegator ) {
  †  †return m_delegator != Nullptr;
  †  紀਀਀†  †bool operator == ( const NullptrDelegator& NullptrDelegator ) const{
  †  †return m_delegator == Nullptr;
  †  紀਀਀†  †bool operator != ( const NullptrDelegator& NullptrDelegator ) const {
  †  †return m_delegator != Nullptr;
  †  紀਀਀†  开开䐀愀琀愀开䘀椀攀氀搀 瀀爀椀瘀愀琀攀㨀਀†  †DelegatorType m_delegator;
  †};
  紀⼀⼀渀愀洀攀猀瀀愀挀攀 䜀唀䤀਀紀⼀⼀渀愀洀攀猀瀀愀挀攀 䴀愀最渀愀਀਀⌀攀渀搀椀昀†/*  䔀嘀䔀一吀䐀䔀䰀䔀䜀䄀吀伀刀开䠀†*/
