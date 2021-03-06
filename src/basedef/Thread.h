#ifndef THREAD_H
#define THREAD_H

#include "basedef_lib.h"

#include "SystemDef.h"
#include "BaseTypes.h"
#include "UniquePtr.h"
#include "String.h"
#include "WeakPtr.h"
#include "Uncopyable.h"

namespace Magna{
  渀愀洀攀猀瀀愀挀攀 䌀漀爀攀笀਀        开开䤀渀琀攀爀昀愀挀攀 挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 䴀䄀䜀一䄀开一伀嘀吀䄀䈀䰀䔀 刀甀渀渀攀爀笀਀            瀀甀戀氀椀挀㨀਀                瘀椀爀琀甀愀氀 縀刀甀渀渀攀爀⠀⤀㬀  ⼀⼀ 挀氀攀愀渀 甀瀀਀                瘀椀爀琀甀愀氀 瘀漀椀搀 漀瀀攀爀愀琀漀爀 ⠀⤀ ⠀⤀ 㴀 　㬀਀        紀㬀਀਀        挀氀愀猀猀 䈀䄀匀䔀䐀䔀䘀开䰀䤀䈀开䔀堀倀伀刀吀 吀栀爀攀愀搀笀਀            昀爀椀攀渀搀 挀氀愀猀猀 吀栀爀攀愀搀䴀愀渀愀最攀爀㬀਀            昀爀椀攀渀搀 挀氀愀猀猀 吀栀爀攀愀搀䄀挀挀攀猀猀漀爀㬀਀            昀爀椀攀渀搀 挀氀愀猀猀 刀甀渀渀愀戀氀攀䴀攀猀猀愀最攀䰀漀漀瀀攀爀㬀਀਀            开开䌀漀渀猀琀爀甀挀琀漀爀开䐀攀猀琀爀甀挀琀漀爀 瀀甀戀氀椀挀㨀਀                ⼀⼀℀     䐀攀昀愀甀氀琀 挀漀渀猀琀爀甀挀琀漀爀਀                吀栀爀攀愀搀⠀⤀㬀਀਀                ⼀⼀℀     䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 琀栀爀攀愀搀 渀愀洀攀਀                攀砀瀀氀椀挀椀琀 吀栀爀攀愀搀⠀ 挀漀渀猀琀 匀琀爀椀渀最☀ 琀栀爀攀愀搀开渀愀洀攀 ⤀㬀਀਀                ⼀⼀℀     䌀漀渀猀琀爀甀挀琀漀爀 眀椀琀栀 爀甀渀渀攀爀 愀渀搀 琀栀爀攀愀搀 渀愀洀攀਀                攀砀瀀氀椀挀椀琀 吀栀爀攀愀搀⠀ 唀渀椀焀甀攀倀琀爀㰀刀甀渀渀攀爀㸀 ☀☀爀甀渀渀攀爀Ⰰ 挀漀渀猀琀 匀琀爀椀渀最☀ 琀栀爀攀愀搀开渀愀洀攀 㴀 匀琀爀椀渀最㨀㨀䔀洀瀀琀礀匀琀爀椀渀最 ⤀㬀਀                ਀                ⼀⼀℀     䄀猀猀椀最渀洀攀渀琀 挀漀渀猀琀爀甀挀琀漀爀਀                吀栀爀攀愀搀⠀ 挀漀渀猀琀 吀栀爀攀愀搀☀ 琀栀爀攀愀搀 ⤀㬀਀਀                ⼀⼀℀     䐀攀猀琀爀甀挀琀漀爀਀                縀吀栀爀攀愀搀⠀⤀㬀਀਀        瀀甀戀氀椀挀㨀਀            ⼀⼀℀     猀氀攀攀瀀 挀甀爀爀攀渀琀 琀栀爀攀愀搀 昀漀爀 洀椀挀爀漀猀攀挀漀渀搀猀਀            ⼀⨀℀਀             ⨀†    \param microsec
             *          the sleep time span in microseconds
             *      \attention
             *          In some platform, time-span is not precise enough, this could lead to sleep( microsec / 1000 )
             */
            static void usleep( uint32 microsec );

            //!     sleep current thread for milliseconds
            /*!
             *      尀瀀愀爀愀洀 洀猀਀             ⨀          琀栀攀 猀氀攀攀瀀 琀椀洀攀 猀瀀愀渀 椀渀 洀椀氀氀椀猀攀挀漀渀搀猀਀             ⨀⼀਀            猀琀愀琀椀挀 瘀漀椀搀 猀氀攀攀瀀⠀ 甀椀渀琀㌀㈀ 洀猀 ⤀㬀਀਀            ⼀⼀℀     攀砀椀琀 挀甀爀爀攀渀琀 琀栀爀攀愀搀 眀椀琀栀 攀砀椀琀 挀漀搀攀 ਀            ⼀⨀℀਀             ⨀      ਀             ⨀†    \param exit_code
             *          exit code 
             */
            static void exit( uint32 exit_code );

            //!     yield current thread 
            static void yield();

            //!     get the current thread 
            /*!
             *      尀爀攀琀甀爀渀 挀甀爀爀攀渀琀 琀栀爀攀愀搀 椀渀猀琀愀渀挀攀਀             ⨀      尀愀琀琀攀渀琀椀漀渀 椀昀 琀栀攀 琀栀爀攀愀搀 椀猀 渀漀琀 挀爀攀愀琀攀搀 戀礀 吀栀爀攀愀搀Ⰰ 琀栀攀 爀甀渀渀攀爀 椀猀 愀氀眀愀礀猀 渀甀氀氀਀             ⨀⼀਀            猀琀愀琀椀挀 吀栀爀攀愀搀 最攀琀䌀甀爀爀攀渀琀吀栀爀攀愀搀⠀⤀㬀਀਀        瀀甀戀氀椀挀㨀਀            ⼀⼀℀     琀攀爀洀椀渀愀琀攀 琀栀攀 琀栀爀攀愀搀਀            ⼀⨀℀਀             ⨀      一伀吀 爀攀挀漀洀洀攀渀搀 琀漀 挀愀氀氀 琀栀椀猀 琀漀 攀渀搀 愀 琀栀爀攀愀搀⸀਀             ⨀      䤀渀 最爀愀挀攀昀甀氀 眀愀礀Ⰰ 琀漀 攀渀搀 愀 琀栀爀攀愀搀 椀猀 甀猀甀愀氀氀礀 戀礀 瀀漀猀琀椀渀最 愀 攀渀搀 洀攀猀猀愀最攀 琀漀 椀琀 愀渀搀 眀愀椀琀 琀椀氀氀 椀琀猀 ਀             ⨀      爀甀渀渀攀爀 最漀攀猀 昀椀渀椀猀栀攀搀 愀渀搀 搀漀 琀栀攀 挀氀攀愀渀甀瀀 瀀爀漀挀攀猀猀⸀਀             ⨀†    \warning calling this may have no chance to do some cleanup in Windows.
             */
            void terminate();

            //!     wait the thread
            
            void wait();
            void cancelWait();

            //!     runs the thread procedure.
            /*!
             *      爀甀渀猀 琀栀攀 琀栀爀攀愀搀 瀀爀漀挀攀搀甀爀攀 椀渀 搀攀琀愀挀栀攀搀 猀琀愀琀攀Ⰰ 眀栀椀挀栀 洀攀愀渀猀 眀漀渀✀琀 戀氀漀挀欀 琀栀攀 ਀             ⨀      挀愀氀氀椀渀最 琀栀爀攀愀搀 愀渀搀 眀栀攀渀 琀栀爀攀愀搀 猀攀琀琀椀渀最猀 挀漀渀昀椀最甀爀愀琀椀漀渀猀 搀漀渀攀Ⰰ 琀栀攀 洀攀琀栀漀搀 眀漀甀氀搀 椀渀猀琀愀渀琀氀礀 爀攀琀甀爀渀⸀਀             ⨀⼀਀            瘀漀椀搀 爀甀渀⠀⤀㬀਀਀            ⼀⼀℀     猀礀渀挀栀爀漀渀漀甀猀氀礀 爀甀渀猀 琀栀攀 琀栀爀攀愀搀 瀀爀漀挀攀搀甀爀攀⸀਀            ⼀⨀℀਀             ⨀†    calling this method would be block the caller thread till the runner goes to the end.
             */
            void syncRun();

        __Checker public:
            bool isFinished() const;
            bool isWaiting();

            inline bool isNull() const { return m_data.isNull(); }

        __Setter public:
            //!    set the runner.
            /*!
             *      尀瀀愀爀愀洀 爀甀渀渀攀爀਀             ⨀          愀渀 爀椀最栀琀ⴀ爀攀昀攀爀攀渀挀攀 唀渀椀焀甀攀倀琀爀㰀刀甀渀渀攀爀㸀 椀渀猀琀愀渀挀攀⸀਀             ⨀⼀਀            瘀漀椀搀 猀攀琀刀甀渀渀攀爀⠀ 唀渀椀焀甀攀倀琀爀㰀刀甀渀渀攀爀㸀☀☀ 爀甀渀渀攀爀 ⤀㬀਀਀            瘀漀椀搀 猀攀琀吀栀爀攀愀搀匀琀愀挀欀匀椀稀攀⠀ 甀椀渀琀㌀㈀ 猀琀愀挀欀开猀椀稀攀 ⤀㬀਀਀            瘀漀椀搀 猀攀琀倀爀椀漀爀椀琀礀⠀ 甀椀渀琀㌀㈀ 瀀爀椀漀爀椀琀礀 ⤀㬀਀਀        开开䜀攀琀琀攀爀 瀀甀戀氀椀挀㨀਀            ⼀⼀℀     最攀琀 琀栀攀 爀甀渀渀攀爀਀            ⼀⨀℀਀             ⨀†    \return returns the WeakPtr of the runner which can be used as 
             *          runner identifier.
             */
            WeakPtr<Runner> getRunner() const;

            //!     get the thread priority in uint32 form.
            uint32 getPriority();

        __Overloaded_Methods public:
            bool operator == ( const Thread& thread );
            bool operator != ( const Thread& thread );

            Thread &operator = ( const Thread& thread );

        __Data_Field private:
            PRIVATE_DATA_DECL
        };
    }//namespace Core
}//namespace Magna

#endif  ⼀⨀†THREAD_H  ⨀⼀�