#include "Timer.h"

#include <cstdlib>
#include <cstring>
#include <map>
#include <random>

#ifdef MAGNA_WINDOWS
//win32
#include <Windows.h>
#elif defined MAGNA_GNU_LINUX
#include <signal.h>
#include <time.h>
#include <unistd.h>
#else
#error UNKNOW_COMPILE_ENV
#endif

#include "BaseTypes.h"
#include "SystemDef.h"
#include "SpinMutex.h"
using namespace Magna::Core;

namespace Magna{
  namespace Core{

        class Timer::PrivateData{
    public:
      PrivateData( Timer *binding )
        :m_binding( binding )
        ,m_interval( 1000 )
        ,m_timerId( 0 ){
#ifdef MAGNA_GNU_LINUX
                ::memset( &m_timer, 0, sizeof( timer_t ) );
#endif
      }

      ~PrivateData(){

      }

      uint32 m_interval;
      Timer *m_binding;
      TimerID m_timerId;
#ifdef MAGNA_GNU_LINUX
            //contains a timer instance
            timer_t m_timer;
#endif
    };

    class GlobalTimerManager{
    protected:
      GlobalTimerManager()
        :m_mutex()
        ,m_globalTimers(){

      }

      ~GlobalTimerManager(){

        for( auto _each = m_globalTimers.begin()
          ; _each != m_globalTimers.end()
          ; ++_each ){
#ifdef MAGNA_WINDOWS
          KillTimer( NULL, _each->first );
#elif defined MAGNA_GNU_LINUX
                    if( Nullptr != _each->second
                       && Nullptr != _each->second->m_data ){
                        auto *_data = _each->second->m_data ;
                        timer_delete( _data->m_timer );
                    }
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

      }

    public:
      static GlobalTimerManager shared_globalTimerManager;

      void requestTimer( Timer::PrivateData& );
      void killTimer( Timer::PrivateData& );

      void triggerTimeOut( const TimerID& );

      SpinMutex m_mutex;
      std::map<TimerID, Timer *> m_globalTimers;
    };

    GlobalTimerManager GlobalTimerManager::shared_globalTimerManager = GlobalTimerManager();

#ifdef MAGNA_WINDOWS
        VOID CALLBACK magna_timer_proc_callback(HWND, UINT, UINT_PTR id, DWORD){
      GlobalTimerManager::shared_globalTimerManager.triggerTimeOut( id );
    }
#elif defined MAGNA_GNU_LINUX
        void /* callbck */ magna_timer_proc_callback ( union sigval sig){
            GlobalTimerManager::shared_globalTimerManager.triggerTimeOut( sig.sival_int );
        }
#else
#error UNKNOW_COMPILE_ENV
#endif

    void GlobalTimerManager::requestTimer( Timer::PrivateData& t){
            bool _req_ok = false;
            m_mutex.acquires();
#ifdef MAGNA_WINDOWS
            t.m_timerId = SetTimer( NULL, 0, t.m_interval, magna_timer_proc_callback );
            if( 0 != t.m_timerId ){
                _req_ok = !false;
            }
#elif defined MAGNA_GNU_LINUX
            //create timer instance
             struct   sigevent   _sig_event;
             ::memset   (&_sig_event,   0,   sizeof   ( struct   sigevent ));

               //calculate the random tid
                std::random_device _dev_gen;

                std::mt19937 _base32_ram( _dev_gen() );

                TimerID _id = 0;

                //ensure id unique
                //enter critical section
                while( [&]() -> bool{ _id = _base32_ram()
                    ; return m_globalTimers.count( _id )  != 0; }() ){}

                t.m_timerId = _id;

              _sig_event.sigev_notify   =   SIGEV_THREAD;
              _sig_event.sigev_notify_function   =   magna_timer_proc_callback;
              _sig_event.sigev_value.sival_int   =   t.m_timerId;

            bool _create_ok = false;
            if   ( 0 == timer_create   ( CLOCK_REALTIME,   &_sig_event,   &t.m_timer ) ){
                _create_ok = !false;
            } else{
                //error gather
            }

            bool _settimer_ok = false;
            if( _create_ok ){
                struct   itimerspec   _timer_spec;
                ::memset( &_timer_spec, 0, sizeof(  struct   itimerspec ) );

                //_timer_spec.it_value.tv_sec   =   t.m_interval / 1000;
                //_timer_spec.it_value.tv_nsec   =   t.m_interval % 1000;
                _timer_spec.it_value.tv_sec   =  0;
                _timer_spec.it_value.tv_nsec   =  0;

                _timer_spec.it_interval.tv_sec   =   t.m_interval / 1000;
                _timer_spec.it_interval.tv_nsec   =   t.m_interval % 1000;

                if(  0 == timer_settime (t.m_timer,   TIMER_ABSTIME,   &_timer_spec,  Nullptr) ){
                    _settimer_ok = !false;
                }

                _req_ok = _req_ok || (_settimer_ok && _create_ok);
            }
#else
#error UNKNOW_COMPILE_ENV
#endif

            if( _req_ok ){
                m_globalTimers.emplace( std::make_pair( t.m_timerId, t.m_binding ) );
            }

      m_mutex.releases();
    }

    void GlobalTimerManager::killTimer( Timer::PrivateData& t ){
      m_mutex.acquires();
      auto _found = m_globalTimers.find( t.m_timerId );
      if( _found != m_globalTimers.end() ){
#ifdef MAGNA_WINDOWS
        KillTimer( NULL, t.m_timerId );
#elif defined MAGNA_GNU_LINUX
                timer_delete (t.m_timer);
                ::memset( &t.m_timer, 0, sizeof( timer_t ) );
#else
#error UNKNOW_COMPILE_ENV
#endif
        m_globalTimers.erase( _found );
        t.m_timerId = 0;
      }
      m_mutex.releases();
    }

    void GlobalTimerManager::triggerTimeOut( const TimerID& id){
      m_mutex.acquires();
      auto _found = m_globalTimers.find( id );
      if( _found != m_globalTimers.end() ){
        auto *timer = _found->second;
        if( timer != Nullptr ){
          timer->OnceTimeOut.triggers();
        }
      }
      m_mutex.releases();
    }

    Timer::Timer()
      :m_data( new PrivateData( this ) ){

    }

    Timer::~Timer(){
        if( Nullptr != m_data ){
            if( 0 != m_data->m_timerId ){
                    stop();
                }
                delete m_data;
        }
    }


    TimerID Timer::getTimerId() const{
      TimerID _ret_id = 0;
      if( m_data != Nullptr ){
        _ret_id = m_data->m_timerId;
      }
      return _ret_id;
    }

    uint32 Timer::getInterval() const{
      sint32 _ret_int = 0;
      if( m_data != Nullptr ){
        _ret_int = m_data->m_interval;
      }
      return _ret_int;
    }

    void Timer::setInterval( uint32 msec ){
      if( m_data != Nullptr ){
        m_data->m_interval = msec;
      }
    }

    void Timer::start(){
      if( m_data != Nullptr ){
        GlobalTimerManager::shared_globalTimerManager.requestTimer(*m_data);
      }
    }

    void Timer::start( uint32 msec ){
      if( m_data != Nullptr ){
        m_data->m_interval = msec;
        GlobalTimerManager::shared_globalTimerManager.requestTimer(*m_data);
      }
    }

    void Timer::stop(){
      if( m_data != Nullptr ){
        GlobalTimerManager::shared_globalTimerManager.killTimer(*m_data);
      }
    }

  }
}
