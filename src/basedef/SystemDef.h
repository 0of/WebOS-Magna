#ifdef _MSC_VER
/** global extension macros */
#define  MAGNA_FORCEINLINE  开开昀漀爀挀攀椀渀氀椀渀攀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开一伀䤀一䰀䤀一䔀†__declspec( noinline )
#define MAGNA_NORETURN __declspec( noreturn )
#define MAGNA_X86  开䴀开䤀堀㠀㘀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开吀䠀䤀匀䌀䄀䰀䰀  开开琀栀椀猀挀愀氀氀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开䌀䐀䔀䌀䰀  开开挀搀攀挀氀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开一伀嘀吀䄀䈀䰀䔀 开开搀攀挀氀猀瀀攀挀⠀渀漀瘀琀愀戀氀攀⤀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开一伀吀䠀刀伀圀 开开搀攀挀氀猀瀀攀挀⠀渀漀琀栀爀漀眀⤀਀⼀⨀ 最氀漀戀愀氀 攀砀琀攀渀猀椀漀渀 洀愀挀爀漀猀†**/

/*  挀⬀⬀ ㄀㄀ 猀甀瀀瀀漀爀琀 挀栀攀挀欀†*/
#if _MSC_VER >= 1800

#ifndef Nullptr
#define Nullptr nullptr
#endif

#ifndef MAGNA_DELETE
#define MAGNA_DELETE  = delete
#endif  /*  MAGNA_DELETE    */

#elif _MSC_VER >= 1600

#ifndef MAGNA_DELETE
#define MAGNA_DELETE
#endif  /*  MAGNA_DELETE    */

#ifndef Nullptr
#define Nullptr nullptr
#endif

#else
#ifndef Nullptr
#define Nullptr (void *)(0)
#endif

#endif  ⼀⨀†_MSC_VER  ⨀⼀਀⌀攀氀椀昀 搀攀昀椀渀攀搀 开开䜀一唀䌀开开਀਀⼀⨀⨀ 最氀漀戀愀氀 攀砀琀攀渀猀椀漀渀 洀愀挀爀漀猀 ⨀⼀਀⌀搀攀昀椀渀攀  䴀䄀䜀一䄀开䘀伀刀䌀䔀䤀一䰀䤀一䔀†inline __attribute__((always_inline))
#define MAGNA_NOINLINE  开开愀琀琀爀椀戀甀琀攀开开⠀⠀ 渀漀椀渀氀椀渀攀 ⤀⤀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开堀㠀㘀†_X86_
#define MAGNA_NORETURN __attribute__((noreturn))
#define MAGNA_THISCALL
#define MAGNA_CDECL  __attribute__((cdecl))
#define MAGNA_NOVTABLE
#define MAGNA_NOTHROW __attribute__(( nothrow ))
//arm env
//#define MAGNA_ARM _ARM_

#ifndef Nullptr
#define Nullptr nullptr
#endif

#ifndef MAGNA_DELETE
#define MAGNA_DELETE = delete
#endif  /*  MAGNA_DELETE    */

#else

#ifndef Nullptr
#define Nullptr (void *)(0)
#endif

#ifndef MAGNA_DELETE
#define MAGNA_DELETE
#endif  /*  MAGNA_DELETE    */

/* global extension macros  ⨀⨀⼀਀਀਀⌀椀昀  开开䜀一唀䌀开开 㸀 㐀 簀簀 ⠀开开䜀唀一䌀开开 㴀㴀 㐀 尀਀†&& __MINOR__ > 6 )
#define AUTO auto
#else
#define AUTO
#endif // __VERSION__
#endif  ⼀⨀†__GUNG__  ⨀⼀਀਀⌀搀攀昀椀渀攀 开开䤀渀琀攀爀昀愀挀攀਀⌀搀攀昀椀渀攀 开开䄀戀猀琀爀愀挀琀攀搀਀⌀搀攀昀椀渀攀 开开䌀漀渀猀琀愀渀琀猀਀⌀搀攀昀椀渀攀 开开伀瘀攀爀氀漀愀搀攀搀开䴀攀琀栀漀搀猀਀⌀搀攀昀椀渀攀 开开伀瘀攀爀爀椀搀攀开䴀攀琀栀漀搀猀਀⌀搀攀昀椀渀攀 开开䠀椀最栀氀椀最栀琀开倀爀漀瀀攀爀琀礀਀⌀搀攀昀椀渀攀 开开䐀愀琀愀开䘀椀攀氀搀਀⌀搀攀昀椀渀攀  开开䐀攀昀椀渀椀琀椀漀渀猀਀⌀搀攀昀椀渀攀 开开匀琀愀琀椀挀开䴀攀琀栀漀搀猀਀⌀搀攀昀椀渀攀 开开䤀洀瀀氀攀洀攀渀琀攀搀开䴀攀琀栀漀搀猀਀⌀搀攀昀椀渀攀 开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀਀⌀搀攀昀椀渀攀 开开䜀攀渀攀爀愀氀椀稀攀猀਀⌀搀攀昀椀渀攀 开开刀攀愀氀椀稀攀猀਀⌀搀攀昀椀渀攀 开开匀攀琀琀攀爀਀⌀搀攀昀椀渀攀 开开䜀攀琀琀攀爀਀⌀搀攀昀椀渀攀 开开䌀栀攀挀欀攀爀਀⌀搀攀昀椀渀攀 开开䈀礀开䴀攀琀栀漀搀猀਀⌀搀攀昀椀渀攀 开开吀漀开䴀攀琀栀漀搀猀਀਀⌀椀昀渀搀攀昀  䴀䄀䜀一䄀开䴀䄀䜀䤀䌀开一唀䴀䈀䔀刀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开䴀䄀䜀䤀䌀开一唀䴀䈀䔀刀 㤀㈀㄀㌀਀⌀攀渀搀椀昀਀਀⌀椀昀渀搀攀昀 䴀䄀䜀一䄀开䌀伀一䌀䄀吀开਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开䌀伀一䌀䄀吀开⠀愀Ⰰ戀⤀ 愀⌀⌀戀਀⌀攀渀搀椀昀  ⼀⨀  䴀䄀䜀一䄀开䌀伀一䌀䄀吀开   ⨀⼀਀਀⼀⼀ 洀愀挀爀漀 挀漀渀挀愀琀攀渀愀琀攀਀⌀椀昀渀搀攀昀 䴀䄀䜀一䄀开䌀伀一䌀䄀吀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开䌀伀一䌀䄀吀⠀愀Ⰰ戀⤀ 䴀䄀䜀一䄀开䌀伀一䌀䄀吀开⠀愀Ⰰ戀⤀਀⌀攀渀搀椀昀  ⼀⨀  䴀䄀䜀一䄀开䌀伀一䌀䄀吀  ⨀⼀਀਀⌀椀昀渀搀攀昀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䈀䔀䜀䤀一਀⌀搀攀昀椀渀攀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䈀䔀䜀䤀一 椀昀⠀℀洀开搀愀琀愀⸀椀猀一甀氀氀⠀⤀⤀笀ഀ਀⌀攀渀搀椀昀  ⼀⨀  倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䈀䔀䜀䤀一 ⨀⼀ഀ਀ഀ਀⌀椀昀渀搀攀昀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䔀一䐀ഀ਀⌀搀攀昀椀渀攀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䔀一䐀 紀਀⌀攀渀搀椀昀  ⼀⨀  倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开一伀吀开一唀䰀䰀开䔀一䐀   ⨀⼀਀਀⌀椀昀渀搀攀昀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开䐀䔀䌀䰀਀⌀搀攀昀椀渀攀 倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开䐀䔀䌀䰀 挀氀愀猀猀 倀爀椀瘀愀琀攀䐀愀琀愀㬀 匀栀愀爀攀搀倀琀爀㰀倀爀椀瘀愀琀攀䐀愀琀愀㸀 洀开搀愀琀愀㬀਀⌀攀渀搀椀昀 ⼀⨀   倀刀䤀嘀䄀吀䔀开䐀䄀吀䄀开䐀䔀䌀䰀 ⨀⼀਀਀⼀⼀伀匀 ਀⌀椀昀搀攀昀 开开最渀甀开氀椀渀甀砀开开਀⌀椀昀渀搀攀昀  䴀䄀䜀一䄀开䜀一唀开䰀䤀一唀堀਀⌀搀攀昀椀渀攀 䴀䄀䜀一䄀开䜀一唀开䰀䤀一唀堀਀⌀攀渀搀椀昀਀਀⌀攀氀椀昀 搀攀昀椀渀攀搀 ⠀开开䄀倀倀䰀䔀开开⤀ 尀਀†  †  †&& (__MACH__)
#ifndef  MAGNA_MAC_OS
#define MAGNA_MAC_OS
#endif

#elif defined (__WINDOWS__) \
  †  †  †|| (_WIN32) \
  †  †  †|| (_WIN64)
#ifndef  MAGNA_WINDOWS
#define MAGNA_WINDOWS
#endif

#endif

// thread
#ifdef MAGNA_WINDOWS
#ifndef WIN_THREAD
#define WIN_THREAD      1
#endif  /*  WIN_THREAD  */
#elif defined MAGNA_GNU_LINUX
#ifndef POSIX_PTHREAD
#define POSIX_PTHREAD       1
#endif  /*  POSIX_PTHREAD   */
#elif defined MAGNA_MAC_OS
#ifndef POSIX_PTHREAD
#define POSIX_PTHREAD       1
#endif  /*  POSIX_PTHREAD   */
#else
#error Unknown OS
#endif
