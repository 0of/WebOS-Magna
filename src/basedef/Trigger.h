#ifndef TRIGGER_H
#define TRIGGER_H

#include "SystemDef.h"
#include "BaseTypes.h"

#include "NullType.h"

#include "private/Callable_p.h"
#include "private/Trigger_p.h"
#include "private/TriggerTrait_p.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀਀†  ⼀⼀琀爀椀最最攀爀 搀攀挀氀愀爀愀琀椀漀渀਀†  琀攀洀瀀氀愀琀攀㰀਀†  †  †  琀礀瀀攀渀愀洀攀 䄀爀最　 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㄀ 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㈀ 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㌀ 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㐀 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㔀 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㘀 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㜀 㴀 一甀氀氀吀礀瀀攀਀†  †  †  Ⰰ琀礀瀀攀渀愀洀攀 䄀爀最㠀 㴀 一甀氀氀吀礀瀀攀਀†  †  †  㸀਀†  挀氀愀猀猀 吀爀椀最最攀爀㬀਀਀†  ⼀⼀一漀 愀爀最甀洀攀渀琀਀†  琀攀洀瀀氀愀琀攀㰀㸀挀氀愀猀猀 吀爀椀最最攀爀㰀一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀਀†  †  Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  †  㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀㸀 㸀笀਀†  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  †Trigger() : _TriggerImpEBody(){}
  †  †  縀吀爀椀最最攀爀⠀⤀笀紀਀਀†  †   public:
  †  † void triggers(){
  †  †   琀礀瀀攀搀攀昀 吀爀椀最最攀爀吀爀愀椀琀㰀㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀㬀਀†  †  † typedef TriggerTrait<>::ProxyAction ActionType;

  †  †  洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each = m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀吀爀椀最最攀爀吀爀愀椀琀㰀㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀开愀挀琀漀爀ⴀ㸀⨀开愀挀琀椀漀渀⤀⠀⤀㬀਀†  †  †  †}
  †  †  †  ⼀⼀猀琀愀琀椀挀 洀攀琀栀漀搀猀਀†  †  †  †else{
  †  †  †  †ActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀吀爀椀最最攀爀吀爀愀椀琀㰀㸀㨀㨀倀爀漀砀礀䄀挀琀椀漀渀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀⨀开愀挀琀椀漀渀⤀⠀⤀㬀਀†  †  †  †}
  †  †  †}
  †  †  †//fetch next
  †  †  †_each = _each->m_next;
  †  †  紀਀†  †  †m_mutex.releases();
  †  †}
  †  紀㬀਀਀†  ⼀⼀㄀ 愀爀最甀洀攀渀琀਀†  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䄀爀最　㸀਀†  挀氀愀猀猀 吀爀椀最最攀爀㰀䄀爀最　Ⰰ 一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀਀†  †,NullType,NullType,NullType,NullType,NullType>
  †  㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　㸀 㸀笀਀†  †    typedef _TriggerImpEBody< TriggerTrait<Arg0> > ImpEBody;

  †  †__Constructor_Destructor public:
  †  †  吀爀椀最最攀爀⠀⤀ 㨀 䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  †~Trigger() {}

  †  †public:
  †  †  瘀漀椀搀 琀爀椀最最攀爀猀⠀ 䄀爀最　 愀爀最　 ⤀笀਀                    琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀㬀਀                    琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　㸀㨀㨀倀爀漀砀礀䄀挀琀椀漀渀 䄀挀琀椀漀渀吀礀瀀攀㬀਀਀†  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †  䌀愀氀氀愀戀氀攀 ⨀开攀愀挀栀 㴀 䤀洀瀀䔀䈀漀搀礀㨀㨀洀开挀愀氀氀愀戀氀攀猀㬀਀†  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  †if( !_each->m_blocked ){
  †  †  †  †//member methods
  †  †  †  †if( _each->m_isMember ){
  †  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  †ProxyActor *_actor = static_cast<ProxyActor *>(_mem->m_obj);
  †  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  †(_actor->*_action)( arg0 );
  †  †  †  †}
  †  †  †  †//static methods
  †  †  †  †else{
  †  †  †  †  䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  †(*_action)( arg0 );
  †  †  †  †}
  †  †  †  紀਀†  †  †  †//fetch next
  †  †  †  开攀愀挀栀 㴀 开攀愀挀栀ⴀ㸀洀开渀攀砀琀㬀਀†  †  †  紀਀†  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀爀攀氀攀愀猀攀猀⠀⤀㬀਀†  †  †}
  †  紀㬀਀਀†  ⼀⼀㈀ 愀爀最甀洀攀渀琀猀਀†  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䄀爀最　Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㄀㸀਀†  挀氀愀猀猀 吀爀椀最最攀爀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 一甀氀氀吀礀瀀攀Ⰰ 一甀氀氀吀礀瀀攀਀†  †,NullType,NullType,NullType,NullType,NullType>
  †  㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀㸀 㸀笀਀            琀礀瀀攀搀攀昀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀㸀 㸀 䤀洀瀀䔀䈀漀搀礀㬀਀†  †__Constructor_Destructor public:
  †  †Trigger() : ImpEBody::_TriggerImpEBody(){}
  †  †~Trigger() {}

  †  瀀甀戀氀椀挀㨀਀†  †  瘀漀椀搀 琀爀椀最最攀爀猀⠀ 䄀爀最　 愀爀最　Ⰰ 䄀爀最㄀ 愀爀最㄀ ⤀笀਀†  †      琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀㬀਀                    琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀㸀㨀㨀倀爀漀砀礀䄀挀琀椀漀渀 䄀挀琀椀漀渀吀礀瀀攀㬀਀਀†  †  †ImpEBody::m_mutex.acquires();
  †  †  䌀愀氀氀愀戀氀攀 ⨀开攀愀挀栀 㴀 䤀洀瀀䔀䈀漀搀礀㨀㨀洀开挀愀氀氀愀戀氀攀猀㬀਀†  †  †while( _each != Nullptr ){
  †  †  †if( !_each->m_blocked ){
  †  †  †  ⼀⼀洀攀洀戀攀爀 洀攀琀栀漀搀猀਀†  †  †  †if( _each->m_isMember ){
  †  †  †  †MemberCallable *_mem = static_cast<MemberCallable *>(_each);
  †  †  †  †ProxyActor *_actor = static_cast<ProxyActor *>(_mem->m_obj);
  †  †  †  †MemeberActionType _action = *reinterpret_cast<MemeberActionType *>(& (_mem->m_callableBody) );
  †  †  †  †(_actor->*_action)( arg0, arg1 );
  †  †  †  紀਀†  †  †  †//static methods
  †  †  †  攀氀猀攀笀਀†  †  †  †  䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<ActionType*>(& (_each->m_callableBody) );
  †  †  †  †(*_action)( arg0, arg1 );
  †  †  †  紀਀†  †  †  紀਀†  †  †  ⼀⼀昀攀琀挀栀 渀攀砀琀਀†  †  †  开攀愀挀栀 㴀 开攀愀挀栀ⴀ㸀洀开渀攀砀琀㬀਀†  †  †}
  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀爀攀氀攀愀猀攀猀⠀⤀㬀਀†  †  紀਀†  †};

  †//3 arguments
  †template<typename Arg0, typename Arg1, typename Arg2>
  †class Trigger<Arg0, Arg1, Arg2, NullType
  †  Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  †: public _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2> >{
            typedef _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2> > ImpEBody;

  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  吀爀椀最最攀爀⠀⤀ 㨀  䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  縀吀爀椀最最攀爀⠀⤀ 笀紀਀†  †public:
  †  †void triggers( Arg0 arg0, Arg1 arg1, Arg2 arg2 ){
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2>::ProxyMemberAction MemeberActionType;
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2>::ProxyAction ActionType;

  †  †   䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each =  ImpEBody::m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀开愀挀琀漀爀ⴀ㸀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀ ⤀㬀਀†  †  †  †}
  †  †  †  ⼀⼀猀琀愀琀椀挀 洀攀琀栀漀搀猀਀†  †  †  †else{
  †  †  †  †ActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀ ⤀㬀਀†  †  †  †}
  †  †  †}
  †  †  †//fetch next
  †  †  †_each = _each->m_next;
  †  †  紀਀†  †  † ImpEBody::m_mutex.releases();
  †  †}
  †  紀㬀਀਀਀†  ⼀⼀†4 arguments
  †template<typename Arg0, typename Arg1, typename Arg2, typename Arg3>
  †class Trigger<Arg0, Arg1, Arg2, Arg3
  †  Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  †: public _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2, Arg3> >{
            typedef _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2,Arg3> > ImpEBody;
  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  吀爀椀最最攀爀⠀⤀ 㨀 䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  縀吀爀椀最最攀爀⠀⤀ 笀紀਀਀†  †public:
  †  †void triggers( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3 ){
  †  †    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3>::ProxyMemberAction MemeberActionType;
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3>::ProxyAction ActionType;

  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each = ImpEBody::m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀 㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀开愀挀琀漀爀ⴀ㸀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀ ⤀㬀਀†  †  †  †}
  †  †  †  ⼀⼀猀琀愀琀椀挀 洀攀琀栀漀搀猀਀†  †  †  †else{
  †  †  †  †ActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀ ⤀㬀਀†  †  †  †}
  †  †  †}
  †  †  †//fetch next
  †  †  †_each = _each->m_next;
  †  †  紀਀†  †  †ImpEBody::m_mutex.releases();
  †  †}
  †  紀㬀਀਀†  ⼀⼀†5 arguments
  †template<typename Arg0
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㄀਀†  †  †, typename Arg2
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㌀਀†  †  †, typename Arg4>
  †class Trigger<Arg0, Arg1, Arg2, Arg3
  †  Ⰰ䄀爀最㐀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  †: public _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2, Arg3,Arg4> >{
            typedef _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2,Arg3,Arg4> > ImpEBody;
  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  吀爀椀最最攀爀⠀⤀ 㨀 䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  縀吀爀椀最最攀爀⠀⤀ 笀紀਀਀†  †public:
  †  †void triggers( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4 ){
  †  †    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4>::ProxyMemberAction MemeberActionType;
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4>::ProxyAction ActionType;

  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each = ImpEBody::m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<MemeberActionType *>(& (_mem->m_callableBody) );
  †  †  †  †(_actor->*_action)( arg0, arg1, arg2, arg3, arg4 );
  †  †  †  紀਀†  †  †  †//static methods
  †  †  †  攀氀猀攀笀਀†  †  †  †  䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<ActionType *>(& (_each->m_callableBody) );
  †  †  †  †(*_action)( arg0, arg1, arg2, arg3, arg4 );
  †  †  †  紀਀†  †  †  紀਀†  †  †  ⼀⼀昀攀琀挀栀 渀攀砀琀਀†  †  †  开攀愀挀栀 㴀 开攀愀挀栀ⴀ㸀洀开渀攀砀琀㬀਀†  †  †}
  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀爀攀氀攀愀猀攀猀⠀⤀㬀਀†  †  紀਀†  †};

  †//  㘀 愀爀最甀洀攀渀琀猀਀†  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䄀爀最　਀†  †  †, typename Arg1
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㈀਀†  †  †, typename Arg3
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㐀਀†  †  †, typename Arg5>
  †class Trigger<Arg0, Arg1, Arg2, Arg3
  †  Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀Ⰰ䄀爀最㈀Ⰰ 䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ 䄀爀最㔀㸀 㸀笀਀†      琀礀瀀攀搀攀昀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀Ⰰ䄀爀最㈀Ⰰ 䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ 䄀爀最㔀㸀 㸀 䤀洀瀀䔀䈀漀搀礀㬀਀†  †__Constructor_Destructor public:
  †  †Trigger() : ImpEBody::_TriggerImpEBody(){}
  †  †~Trigger() {}

  †  瀀甀戀氀椀挀㨀਀†  †  瘀漀椀搀 琀爀椀最最攀爀猀⠀ 䄀爀最　 愀爀最　Ⰰ 䄀爀最㄀ 愀爀最㄀Ⰰ 䄀爀最㈀ 愀爀最㈀Ⰰ䄀爀最㌀ 愀爀最㌀Ⰰ䄀爀最㐀 愀爀最㐀Ⰰ䄀爀最㔀 愀爀最㔀 ⤀笀਀†  †      琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 䄀爀最㈀Ⰰ䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀㬀਀                    琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 䄀爀最㈀Ⰰ䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀㸀㨀㨀倀爀漀砀礀䄀挀琀椀漀渀 䄀挀琀椀漀渀吀礀瀀攀㬀਀਀†  †  †ImpEBody::m_mutex.acquires();
  †  †  䌀愀氀氀愀戀氀攀 ⨀开攀愀挀栀 㴀 䤀洀瀀䔀䈀漀搀礀㨀㨀洀开挀愀氀氀愀戀氀攀猀㬀਀†  †  †while( _each != Nullptr ){
  †  †  †if( !_each->m_blocked ){
  †  †  †  ⼀⼀洀攀洀戀攀爀 洀攀琀栀漀搀猀਀†  †  †  †if( _each->m_isMember ){
  †  †  †  †MemberCallable *_mem = static_cast<MemberCallable *>(_each);
  †  †  †  †ProxyActor *_actor = static_cast<ProxyActor *>(_mem->m_obj);
  †  †  †  †MemeberActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀开愀挀琀漀爀ⴀ㸀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀Ⰰ 愀爀最㐀Ⰰ 愀爀最㔀 ⤀㬀਀†  †  †  †}
  †  †  †  ⼀⼀猀琀愀琀椀挀 洀攀琀栀漀搀猀਀†  †  †  †else{
  †  †  †  †ActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀Ⰰ 愀爀最㐀Ⰰ 愀爀最㔀 ⤀㬀਀†  †  †  †}
  †  †  †}
  †  †  †//fetch next
  †  †  †_each = _each->m_next;
  †  †  紀਀†  †  †ImpEBody::m_mutex.releases();
  †  †}
  †  紀㬀਀਀†  ⼀⼀†7 arguments
  †template<typename Arg0
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㄀਀†  †  †, typename Arg2
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㌀਀†  †  †, typename Arg4
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㔀਀†  †  †, typename Arg6>
  †class Trigger<Arg0, Arg1, Arg2, Arg3
  †  Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀Ⰰ䄀爀最㘀Ⰰ一甀氀氀吀礀瀀攀Ⰰ一甀氀氀吀礀瀀攀㸀਀†  㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀Ⰰ䄀爀最㈀Ⰰ 䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ 䄀爀最㔀Ⰰ䄀爀最㘀㸀 㸀笀਀†       琀礀瀀攀搀攀昀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀Ⰰ䄀爀最㈀Ⰰ 䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ 䄀爀最㔀Ⰰ䄀爀最㘀㸀 㸀 䤀洀瀀䔀䈀漀搀礀㬀਀਀†  †__Constructor_Destructor public:
  †  †Trigger() : ImpEBody::_TriggerImpEBody(){}
  †  †~Trigger() {}

  †  瀀甀戀氀椀挀㨀਀†  †  瘀漀椀搀 琀爀椀最最攀爀猀⠀ 䄀爀最　 愀爀最　Ⰰ 䄀爀最㄀ 愀爀最㄀Ⰰ 䄀爀最㈀ 愀爀最㈀Ⰰ䄀爀最㌀ 愀爀最㌀Ⰰ䄀爀最㐀 愀爀最㐀Ⰰ䄀爀最㔀 愀爀最㔀Ⰰ䄀爀最㘀 愀爀最㘀 ⤀笀਀†  †      琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 䄀爀最㈀Ⰰ䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀Ⰰ䄀爀最㘀㸀㨀㨀倀爀漀砀礀䴀攀洀戀攀爀䄀挀琀椀漀渀 䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀㬀਀                    琀礀瀀攀搀攀昀 琀礀瀀攀渀愀洀攀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 䄀爀最㈀Ⰰ䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ䄀爀最㔀Ⰰ䄀爀最㘀㸀㨀㨀倀爀漀砀礀䄀挀琀椀漀渀 䄀挀琀椀漀渀吀礀瀀攀㬀਀਀†  †  †ImpEBody::m_mutex.acquires();
  †  †  䌀愀氀氀愀戀氀攀 ⨀开攀愀挀栀 㴀 䤀洀瀀䔀䈀漀搀礀㨀㨀洀开挀愀氀氀愀戀氀攀猀㬀਀†  †  †while( _each != Nullptr ){
  †  †  †if( !_each->m_blocked ){
  †  †  †  ⼀⼀洀攀洀戀攀爀 洀攀琀栀漀搀猀਀†  †  †  †if( _each->m_isMember ){
  †  †  †  †MemberCallable *_mem = static_cast<MemberCallable *>(_each);
  †  †  †  †ProxyActor *_actor = static_cast<ProxyActor *>(_mem->m_obj);
  †  †  †  †MemeberActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开洀攀洀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀开愀挀琀漀爀ⴀ㸀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀Ⰰ 愀爀最㐀Ⰰ 愀爀最㔀Ⰰ愀爀最㘀 ⤀㬀਀†  †  †  †}
  †  †  †  ⼀⼀猀琀愀琀椀挀 洀攀琀栀漀搀猀਀†  †  †  †else{
  †  †  †  †ActionType _action
  †  †  †  †  㴀 ⨀爀攀椀渀琀攀爀瀀爀攀琀开挀愀猀琀㰀䄀挀琀椀漀渀吀礀瀀攀 ⨀㸀⠀☀ ⠀开攀愀挀栀ⴀ㸀洀开挀愀氀氀愀戀氀攀䈀漀搀礀⤀ ⤀㬀਀†  †  †  †  ⠀⨀开愀挀琀椀漀渀⤀⠀ 愀爀最　Ⰰ 愀爀最㄀Ⰰ 愀爀最㈀Ⰰ 愀爀最㌀Ⰰ 愀爀最㐀Ⰰ 愀爀最㔀Ⰰ愀爀最㘀 ⤀㬀਀†  †  †  †}
  †  †  †}
  †  †  †//fetch next
  †  †  †_each = _each->m_next;
  †  †  紀਀†  †  †ImpEBody::m_mutex.releases();
  †  †}
  †  紀㬀਀਀†  ⼀⼀†8 arguments
  †template<typename Arg0
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㄀਀†  †  †, typename Arg2
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㌀਀†  †  †, typename Arg4
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㔀਀†  †  †, typename Arg6
  †  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㜀㸀਀†  挀氀愀猀猀 吀爀椀最最攀爀㰀䄀爀最　Ⰰ 䄀爀最㄀Ⰰ 䄀爀最㈀Ⰰ 䄀爀最㌀਀†  †,Arg4,Arg5,Arg6,Arg7,NullType>
  †: public _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2, Arg3,Arg4, Arg5,Arg6,Arg7> >{
  †    typedef _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2, Arg3,Arg4, Arg5,Arg6,Arg7> > ImpEBody;
  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  吀爀椀最最攀爀⠀⤀ 㨀 䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  縀吀爀椀最最攀爀⠀⤀ 笀紀਀਀†  †public:
  †  †void triggers( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5,Arg6 arg6,Arg7 arg7 ){
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7>::ProxyMemberAction MemeberActionType;
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7>::ProxyAction ActionType;

  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each = ImpEBody::m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<MemeberActionType *>(& (_mem->m_callableBody) );
  †  †  †  †(_actor->*_action)( arg0, arg1, arg2, arg3, arg4, arg5,arg6, arg7 );
  †  †  †  紀਀†  †  †  †//static methods
  †  †  †  攀氀猀攀笀਀†  †  †  †  䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<ActionType *>(& (_each->m_callableBody) );
  †  †  †  †(*_action)( arg0, arg1, arg2, arg3, arg4, arg5,arg6,arg7 );
  †  †  †  紀਀†  †  †  紀਀†  †  †  ⼀⼀昀攀琀挀栀 渀攀砀琀਀†  †  †  开攀愀挀栀 㴀 开攀愀挀栀ⴀ㸀洀开渀攀砀琀㬀਀†  †  †}
  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀爀攀氀攀愀猀攀猀⠀⤀㬀਀†  †  紀਀†  †};

  †//  㤀 愀爀最甀洀攀渀琀猀਀†  琀攀洀瀀氀愀琀攀㰀琀礀瀀攀渀愀洀攀 䄀爀最　਀†  †, typename Arg1
  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㈀਀†  †, typename Arg3
  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㐀਀†  †, typename Arg5
  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㘀਀†  †, typename Arg7
  †  Ⰰ 琀礀瀀攀渀愀洀攀 䄀爀最㠀㸀਀†  挀氀愀猀猀 吀爀椀最最攀爀 㨀 瀀甀戀氀椀挀 开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀㰀 吀爀椀最最攀爀吀爀愀椀琀㰀䄀爀最　Ⰰ䄀爀最㄀Ⰰ䄀爀最㈀Ⰰ 䄀爀最㌀Ⰰ䄀爀最㐀Ⰰ 䄀爀最㔀Ⰰ䄀爀最㘀Ⰰ䄀爀最㜀Ⰰ䄀爀最㠀㸀 㸀笀਀†  † typedef _TriggerImpEBody< TriggerTrait<Arg0,Arg1,Arg2, Arg3,Arg4, Arg5,Arg6,Arg7,Arg8> > ImpEBody;

  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  吀爀椀最最攀爀⠀⤀ 㨀 䤀洀瀀䔀䈀漀搀礀㨀㨀开吀爀椀最最攀爀䤀洀瀀䔀䈀漀搀礀⠀⤀笀紀਀†  †  縀吀爀椀最最攀爀⠀⤀ 笀紀਀†  †public:
  †  †void triggers( Arg0 arg0, Arg1 arg1, Arg2 arg2,Arg3 arg3,Arg4 arg4,Arg5 arg5,Arg6 arg6,Arg7 arg7,Arg8 arg8 ){
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8>::ProxyMemberAction MemeberActionType;
                    typedef typename TriggerTrait<Arg0, Arg1, Arg2,Arg3,Arg4,Arg5,Arg6,Arg7,Arg8>::ProxyAction ActionType;


  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀愀挀焀甀椀爀攀猀⠀⤀㬀਀†  †  †Callable *_each = ImpEBody::m_callables;
  †  †  眀栀椀氀攀⠀ 开攀愀挀栀 ℀㴀 一甀氀氀瀀琀爀 ⤀笀਀†  †  †  椀昀⠀ ℀开攀愀挀栀ⴀ㸀洀开戀氀漀挀欀攀搀 ⤀笀਀†  †  †  †//member methods
  †  †  †  椀昀⠀ 开攀愀挀栀ⴀ㸀洀开椀猀䴀攀洀戀攀爀 ⤀笀਀†  †  †  †  䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀开洀攀洀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀䴀攀洀戀攀爀䌀愀氀氀愀戀氀攀 ⨀㸀⠀开攀愀挀栀⤀㬀਀†  †  †  †  倀爀漀砀礀䄀挀琀漀爀 ⨀开愀挀琀漀爀 㴀 猀琀愀琀椀挀开挀愀猀琀㰀倀爀漀砀礀䄀挀琀漀爀 ⨀㸀⠀开洀攀洀ⴀ㸀洀开漀戀樀⤀㬀਀†  †  †  †  䴀攀洀攀戀攀爀䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<MemeberActionType *>(& (_mem->m_callableBody) );
  †  †  †  †(_actor->*_action)( arg0, arg1, arg2, arg3, arg4, arg5,arg6, arg7,arg8 );
  †  †  †  紀਀†  †  †  †//static methods
  †  †  †  攀氀猀攀笀਀†  †  †  †  䄀挀琀椀漀渀吀礀瀀攀 开愀挀琀椀漀渀਀†  †  †  †  †= *reinterpret_cast<ActionType *>(& (_each->m_callableBody) );
  †  †  †  †(*_action)( arg0, arg1, arg2, arg3, arg4, arg5,arg6,arg7,arg8 );
  †  †  †  紀਀†  †  †  紀਀†  †  †  ⼀⼀昀攀琀挀栀 渀攀砀琀਀†  †  †  开攀愀挀栀 㴀 开攀愀挀栀ⴀ㸀洀开渀攀砀琀㬀਀†  †  †}
  †  †  䤀洀瀀䔀䈀漀搀礀㨀㨀洀开洀甀琀攀砀⸀爀攀氀攀愀猀攀猀⠀⤀㬀਀†  †  紀਀†  †};

  †//macro def
  †#define TRIGGER_DEF(trigger_name,...)\
  †  吀爀椀最最攀爀㰀开开嘀䄀开䄀刀䜀匀开开㸀 琀爀椀最最攀爀开渀愀洀攀㬀਀†}//namespace Core
}//namespace Magna

#endif  ⼀⨀†TRIGGER_H  ⨀⼀�