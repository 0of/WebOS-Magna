#include "ThreadManager.h"

#include <random>
#include <algorithm>

#include "Thread_p.h"

namespace Magna{
    namespace Core{

        ThreadManager &ThreadManager::getThreadManager(){
            static ThreadManager _manager;
            return _manager;
        }


        ThreadManager::ThreadManager()
            :m_mutex()
            ,m_threads()
            ,m_mainThreadId( 0 ){

        }

        ThreadManager::~ThreadManager(){

        }

        void ThreadManager::initMainThread(){
#if WIN_THREAD
            const auto _self_id = ::GetCurrentThreadId();
#else POSIX_PTHREAD
            const pthread_t &_self_id = pthread_self();
#endif

            Thread _init_thread( L"main_thread" );

            _init_thread.m_data->m_threadId = _self_id;

            std::random_device _dev_gen;

            std::mt19937 _base32_ram( _dev_gen() );

            uint32 _id = 0;

            while( [&]() -> bool{ _id = _base32_ram()
                ; return  _id == 0; }() ){}

            m_threads.emplace( std::make_pair( _id, _init_thread) );
            m_mainThreadId = _id;
        }

        bool ThreadManager::isMainThread( const Thread& t){
            bool _ret_equ = false;
            if( !t.isNull() ){
                _ret_equ = (t.m_data->m_runningId == m_mainThreadId);
            }
            return _ret_equ;
        }

        void ThreadManager::registerThread( Thread& t){
            if( !t.m_data.isNull() ){
                m_mutex.acquires();

                std::random_device _dev_gen;

                std::mt19937 _base32_ram( _dev_gen() );

                uint32 _id = 0;

                while( [&]() -> bool{ _id = _base32_ram()
                    ; return  m_threads.count( _id )  != 0 || _id == 0; }() ){}

                m_threads.emplace( std::make_pair( _id, t) );
                t.m_data->m_runningId = _id;

                m_mutex.releases();
            }
        }

        void ThreadManager::unregisterThread( Thread& t){
            if( !t.m_data.isNull() && t.m_data->m_runningId != 0 ){
                m_mutex.acquires();

                auto _found = m_threads.find( t.m_data->m_runningId );
                if( _found != m_threads.end() ){

                    t.m_data->m_runningId = 0;

                    m_threads.erase( _found );
                }
                m_mutex.releases();
            }
        }

        Thread ThreadManager::getCurrentThread(){

            class ThreadComparer{
            public:
#if WIN_THREAD
            ThreadComparer( DWORD _cmp )
#else POSIX_PTHREAD
            ThreadComparer( pthread_t _cmp )
#endif
                    :m_cmp( _cmp ){

                }

                ~ThreadComparer(){

                }

                bool operator() ( const std::pair<uint32, Thread>& each ){
                    auto &_thread_data = each.second.m_data;
#if WIN_THREAD
                    return !_thread_data.isNull() && m_cmp == _thread_data->m_threadId;
#else POSIX_PTHREAD
                    return !_thread_data.isNull() && pthread_equal( m_cmp, _thread_data->m_threadId );
#endif
                }
#if WIN_THREAD
                    DWORD m_cmp;
#else POSIX_PTHREAD
                    pthread_t m_cmp;
#endif
            };

            bool hasOne = false;

            m_mutex.acquires();
#if WIN_THREAD
            auto _found = std::find_if( m_threads.begin(), m_threads.end(), ThreadComparer( ::GetCurrentThreadId() ) );
#else POSIX_PTHREAD
             auto _found = std::find_if( m_threads.begin(), m_threads.end(), ThreadComparer( pthread_self() ) );
#endif
            hasOne = (_found != m_threads.end() );
            m_mutex.releases();

            return hasOne ? _found->second : Thread();
        }

    }
}//namespace Magna
