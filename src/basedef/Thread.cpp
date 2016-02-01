#pragma warning(disable:4101)

#include "Thread.h"
#include "AtomicType.h"
#include "BaseTypes.h"
#include "SharedPtr.h"

#include <cassert>
#include <cstring>
#include <stdexcept>

#include "ThreadManager.h"
#include "Thread_p.h"

namespace Magna{
    namespace Core{

        Runner::~Runner(){

        }

        Thread::Thread()
            :m_data(){

        }

        Thread::Thread( const String& _thread_name )
            :m_data( new PrivateData( _thread_name ) ){

        }

        Thread::Thread( UniquePtr<Runner> &&_runner, const String& _thread_name )
            :m_data( new PrivateData( std::move( _runner ), _thread_name ) ){

        }

        Thread::Thread( const Thread& thread )
            :m_data( thread.m_data ){

        }

        Thread::~Thread(){

        }

        bool Thread::isWaiting(){
            bool _is_waiting = false;
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                _is_waiting = m_data->m_isWaiting;
            PRIVATE_DATA_NOT_NULL_END
            return _is_waiting;
        }

        bool Thread::isFinished() const{
            bool _is_finished = !false;
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                _is_finished = m_data->m_isFinished;
            PRIVATE_DATA_NOT_NULL_END
            return _is_finished;
        }

        void Thread::setRunner( UniquePtr<Runner>&& runner ){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( !m_data->m_isFinished ){
                    m_data->m_runner = std::move( runner );
                }
            PRIVATE_DATA_NOT_NULL_END
        }

        WeakPtr<Runner> Thread::getRunner() const{
            WeakPtr<Runner> _weak_ptr;
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                _weak_ptr = m_data->m_runner.toWeakPtr();
            PRIVATE_DATA_NOT_NULL_END
            return _weak_ptr;
        }

        Thread Thread::getCurrentThread(){
            return ThreadManager::getThreadManager().getCurrentThread();
        }

        bool Thread::operator != ( const Thread& thread ){
            return !operator==( thread );
        }

        Thread &Thread::operator = ( const Thread& thread ){
            m_data = thread.m_data;
            return *this;
        }
  }//namespace Core
}//namespace Magna
