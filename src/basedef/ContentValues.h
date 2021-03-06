/*
  * This file is part of core library of Magna framework
  * 
  * Copyright (c) 2013 by Magnus
  */
#ifndef CONTENTVALUES_H
#define CONTENTVALUES_H

#include "BaseTypes.h"
#include "Message.h"
#include "UnionVariant.h"

#include "ContentValues_p.h"

//STL
#include "string"

namespace Magna{  ਀† namespace Core{
  † 
  †template<typename Key, typename Value>
  †class Pair{
  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀†  †
  †  †Pair( const Key& input_key, const Value& val )  㨀 洀开欀攀礀⠀椀渀瀀甀琀开欀攀礀⤀Ⰰ 洀开瘀愀氀甀攀⠀ 瘀愀氀 ⤀笀紀਀†  †  縀倀愀椀爀⠀⤀㬀਀਀†  †__Getter public:
  †  †inline const Key & getKey() const { return m_key ;}
  †  †inline  Key & getKey() { return m_key ;}

  †  †inline const Value & getValue() const { return m_value ;}
  †  †inline Value & getValue(){ return m_value ;}

  †  开开䐀愀琀愀开䘀椀攀氀搀 瀀爀椀瘀愀琀攀㨀਀†  †  䬀攀礀 洀开欀攀礀㬀਀†  †  嘀愀氀甀攀 洀开瘀愀氀甀攀㬀਀†  紀㬀਀†  ਀†  琀礀瀀攀搀攀昀 倀愀椀爀㰀猀琀搀㨀㨀猀琀爀椀渀最Ⰰ唀渀椀漀渀嘀愀爀椀愀渀琀㸀 匀琀爀椀渀最嘀愀爀椀愀渀琀倀愀椀爀㬀਀†  琀礀瀀攀搀攀昀 倀愀椀爀㰀猀椀渀琀㌀㈀Ⰰ唀渀椀漀渀嘀愀爀椀愀渀琀㸀 䤀渀琀嘀愀爀椀愀渀琀倀愀椀爀㬀਀†  ਀਀†   挀氀愀猀猀 䌀漀渀琀攀渀琀嘀愀氀甀攀猀 㨀 瀀甀戀氀椀挀 䴀攀猀猀愀最攀਀†  †  †  †  †, PrivateContentValues{
  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀†  †  䌀漀渀琀攀渀琀嘀愀氀甀攀猀⠀ 挀漀渀猀琀 匀琀爀椀渀最嘀愀爀椀愀渀琀倀愀椀爀☀ 瀀愀椀爀 ⤀਀†  †  †:PrivateContentValues( pair.getKey() , pair.getValue() ){}
  †  †~ContentValues(){}
  †  ਀†  † __Setter public:
  †  † void puts(const StringVariantPair& pair){
  †  †  开椀渀猀攀爀琀⠀ 瀀愀椀爀⸀最攀琀䬀攀礀⠀⤀Ⰰ 瀀愀椀爀⸀最攀琀嘀愀氀甀攀⠀⤀ ⤀㬀਀†  †   紀਀†  † __Getter public:
  †  † UnionVariant get( const std::string& key ){
  †  †  爀攀琀甀爀渀 开昀椀渀搀⠀欀攀礀⤀㬀਀†  †   紀਀†   紀㬀਀† }//Core
}//Magna
#endif  ⼀⨀†CONTENTVALUES_H  ⨀�