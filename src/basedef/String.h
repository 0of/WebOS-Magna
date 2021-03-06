/*
 * This file is part of core library of Magna framework
 * 
 * Copyright (c) 2013 by Magnus
 */
#pragma warning(disable:4251)

#ifndef STRING_H
#define STRING_H

#include "basedef_lib.h"

#include <string>
#include <vector>
#include <sstream>

#include "SystemDef.h"
#include "BaseTypes.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀ഀ਀ഀ਀†  琀礀瀀攀搀攀昀 猀琀搀㨀㨀眀漀猀琀爀椀渀最猀琀爀攀愀洀 伀甀琀匀琀爀椀渀最匀琀爀攀愀洀㬀ഀ਀ഀ਀†  ⼀⨀℀†  尀戀爀椀攀昀ഀ਀†  †  䄀 猀琀爀椀渀最 挀氀愀猀猀⸀⁛坻♎㉼笰Ȁ†  ഀ਀†   ⨀⼀ഀ਀†  ⼀⨀℀†  尀搀攀琀愀椀氀猀ഀ਀†   ⨀†
  † *  †A STL wstring extension class.
  † *  †It extents several functionalities : split, find and replace,
  † *  †multi-bytes characters conversions.
  † *  †
  † *  †STL宽字符扩展类。
  † *  †扩展了一些功能：分割、查找替换、多字节字符串转换等。
  † *  †
  † *  †\author  䴀愀最渀甀猀ഀ਀†   ⨀†  尀瘀攀爀猀椀漀渀   ㄀⸀　⸀　⸀　ഀ਀†   ⨀†  尀搀愀琀攀†  ㈀　㄀㌀⼀㌀⼀㈀㄀ഀ਀†   ⨀⼀ഀ਀†
  †class BASEDEF_LIB_EXPORT String : public std::wstring{
            __Definitions public:
                static String EmptyString;

  †  开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀ഀ਀†  †  匀琀爀椀渀最⠀⤀ഀ਀†  †  †:std::wstring(){

  †  †}

  †  †String( const String& st )
  †  †  㨀猀琀搀㨀㨀眀猀琀爀椀渀最⠀ 猀琀 ⤀笀ഀ਀ഀ਀†  †  紀ഀ਀ഀ਀†  †  匀琀爀椀渀最⠀ 挀漀渀猀琀 猀琀搀㨀㨀眀猀琀爀椀渀最☀ 猀琀 ⤀ഀ਀†  †  †:std::wstring( st ){

  †  †}

  †  †String( const String& str, uint32 pos, uint32 len = std::wstring::npos )
  †  †  㨀猀琀搀㨀㨀眀猀琀爀椀渀最⠀ 猀琀爀Ⰰ 瀀漀猀Ⰰ 氀攀渀 ⤀笀ഀ਀ഀ਀†  †  紀ഀ਀ഀ਀†  †  匀琀爀椀渀最⠀ 挀漀渀猀琀 甀渀椀挀漀搀攀开挀栀愀爀 ⨀挀开猀琀爀椀渀最 ⤀ഀ਀†  †  †:std::wstring( c_string ){

  †  †}

  †  †String( const unicode_char *c_string , uint32 size )
  †  †  㨀猀琀搀㨀㨀眀猀琀爀椀渀最⠀ 挀开猀琀爀椀渀最Ⰰ 猀椀稀攀 ⤀笀ഀ਀ഀ਀†  †  紀ഀ਀ഀ਀†  †  匀琀爀椀渀最⠀ 甀椀渀琀㌀㈀ 猀椀稀攀Ⰰ 甀渀椀挀漀搀攀开挀栀愀爀 昀椀氀氀䌀栀愀爀 ⤀ഀ਀†  †  †:std::wstring( size, fillChar ){

  †  †}

  †  †~String(){

  †  †}

  †  瀀甀戀氀椀挀㨀ഀ਀†  †  ⼀⼀℀†  猀瀀氀椀琀 戀礀 搀攀氀椀洀椀琀 椀渀琀漀 猀攀瘀攀爀愀氀 猀甀戀猀琀爀椀渀最猀⸀ 尀湒ْ牛坻♎㉎㩙ᩎ⩛偛坻♎㈰Ȁഀ਀†  †  ⼀⨀℀†
  †  † *  †
  †  † *  †\code{.cpp}
  †  † *  †String delimit = L",";
  †  † *  †String split_string = L"abc,efgh,ijklo,,cd";
  †  † *  †const std::vector<String> &substrings = split_string.split( delimit );
  †  † *  †//the substrings would be: "abc"  "efgh"  "ijklo" "" "cd" 
  †  † *  †//5 substrings
  †  † *  † \endcode
  †       ⨀†  ഀ਀†  †   ⨀†  尀瀀愀爀愀洀 搀攀氀椀洀椀琀ഀ਀†  †   ⨀†  愀 搀攀氀椀洀椀琀⸀ഀ਀†  †   ⨀† ⁒ږ鑻☰Ȁഀ਀†  †   ⨀†  ഀ਀†  †   ⨀†  尀爀攀琀甀爀渀 愀 瘀攀挀琀漀爀 漀昀 猀甀戀猀琀爀椀渀最猀ഀ਀†  †   ⨀†  尀湢䁧†的子字符串。
  †  † */
  †  †std::vector<String> split( const String& delimit );

  †  †//!  †replace all the specific substring to other string. \n替换所朠⁾�驶葛偛坻♎㉎㩑癎홛坻♎㈀ഀ਀†  †  ⼀⨀℀†
  †  † *  †\param by
  †  † *  †when occurs the \a by , it'll will be replaced by \a to
  †  † *  †\n当遇到 \a by 时，都将被替换成 \a to
  †  † *  †
  †  † *  †\param to
  †  † *  †the string replace to
  †  † *  †\n替换成的字符串。
  †  † *
  †  † *  †\return the times the replacement occurs.
  †  † *  †\n替换发生的次数。
  †  † */
  †  †uint32 replaceAll( const String&by, const String& to);

  †  †//!  †convert wide string to multi-byte string. \n 由宽字符转换成多字节字符。
  †  †/*!  ഀ਀†  †   ⨀†  尀爀攀琀甀爀渀 洀甀氀琀椀ⴀ戀礀琀攀 猀琀搀 猀琀爀椀渀最⸀ഀ਀†  †   ⨀†  尀湙ᩛ垂舀猀琀搀㨀㨀猀琀爀椀渀杛坻♎㈰Ȁഀ਀†  †   ⨀⼀ഀ਀†  †  猀琀搀㨀㨀猀琀爀椀渀最 琀漀匀琀爀椀渀最⠀⤀ 挀漀渀猀琀㬀਀਀†  †  ⼀⼀℀†  挀漀渀瘀攀爀琀 眀椀搀攀 猀琀爀椀渀最 琀漀 唀吀䘀ⴀ㠀 洀甀氀琀椀ⴀ戀礀琀攀 猀琀爀椀渀最⸀ 尀渀⁵ㅛ뵛坻⚏汣扢က唀吀䘀ⴀ㡙ᩛ垂艛坻☰Ȁഀ਀†  †  ⼀⨀℀†
  †  † *  †\return multi-byte UTF-8 std string.
  †  † *  †\n多字节UTF-8 std::string字符串。
  †  † *  †
  †  † *  †\sa fromString( const std::string& )
  †  † */
  †  †std::string toUTF8() const;

  †  †//!  †convert UTF-8 multi-byte string to String
  †  †/*!  ഀ਀†  †   ⨀†  尀瀀愀爀愀洀 猀琀爀ഀ਀†  †   ⨀†  洀甀氀琀椀ⴀ戀礀琀攀 唀吀䘀ⴀ㠀 猀琀搀 猀琀爀椀渀最⸀ഀ਀†  †   ⨀†  尀湙ᩛ垂舀 唀吀䘀ⴀ㠀 猀琀搀㨀㨀猀琀爀椀渀最⁛坻♎㈰Ȁഀ਀†  †   ⨀†  ഀ਀†  †   ⨀†  尀爀攀琀甀爀渀 挀漀渀瘀攀爀琀攀搀 匀琀爀椀渀最⸀ഀ਀†  †   ⨀†  尀溏汣扔๶萀匀琀爀椀渀朰Ȁഀ਀†  †   ⨀⼀਀                猀琀愀琀椀挀 匀琀爀椀渀最 昀爀漀洀唀吀䘀㠀⠀ 挀漀渀猀琀 猀琀搀㨀㨀猀琀爀椀渀最☀ 猀琀爀⤀㬀ഀ਀ഀ਀†  †  ⼀⼀℀†  挀漀渀瘀攀爀琀 洀甀氀琀椀ⴀ戀礀琀攀 猀琀爀椀渀最 琀漀 匀琀爀椀渀最ഀ਀†  †  ⼀⨀℀†
  †  † *  †\param str
  †  † *  †multi-byte std string.
  †  † *  †\n多字节 std::string 字符串。
  †  † *  †
  †  † *  †\return converted String.
  †  † *  †\n转换后的String。
  †  † *  †
  †  † *  †\sa toString()
  †  † */
  †  †static String fromString( const std::string& str);
  †};

  紀ഀ਀紀⼀⼀渀愀洀攀猀瀀愀挀攀 䴀愀最渀愀ഀ਀ഀ਀⌀攀渀搀椀昀†/*  匀吀刀䤀一䜀开䠀†*/
