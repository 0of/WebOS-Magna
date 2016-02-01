#ifdef MAGNA_GNU_LINUX

#include <pthread/pthread.h>

#include "Thread.h"
#include "Thread_p.h"

namespace Magna{
    namespace Core{

        void Thread::yield(){
            sched_yield();
        }

        void Thread::wait(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                m_data->m_isWaiting.write( 1 );
                pthread_mutex_lock( &( m_data->m_waitMutex ) );
                pthread_cond_wait( &( m_data->m_waitCond ), &( m_data->m_waitMutex ) );
                pthread_mutex_unlock( &( m_data->m_waitMutex ) );
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::cancelWait(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                pthread_cond_signal( &( m_data->m_waitCond ) );
                m_data->m_isWaiting.write( 0 );
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::terminate(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                pthread_cancel( m_data->m_threadId );
            PRIVATE_DATA_NOT_NULL_END
        }

        // thread call back
        void MAGNA_CDECL _ThreadCallback( void * _param ){
            //pthread_getname_np
        }

        void Thread::run(){
            if( !m_data.isNull() && !m_data->m_runner.isNull() ){
                auto _raw_runner = m_data->m_runner.operator ->();

                pthread_attr_t _attr;
                pthread_attr_init( &_attr );
                pthread_attr_setdetachstate( &_attr, PTHREAD_CREATE_DETACHED );

                //wait condition & wait mutex
                pthread_cond_init( &m_data->m_waitCond, Nullptr );
                pthread_mutex_init( &m_data->m_waitMutex, Nullptr );

                auto _ret_code = pthread_create( &(m_data->m_threadId), &_attr, _ThreadCallback, this );
                if( _ret_code == 0 ){
                    ThreadManager::getThreadManager().registerThread( *this );
                } else{

                }
                pthread_attr_destroy( &_attr );
            }
        }

    }
}

#endif  /*  MAGNA_GNU_LINUX */