#include "Thread.h"
#include "Thread_p.h"

#ifdef MAGNA_WINDOWS
#include <Windows.h>
#include <process.h>

namespace Magna{
    namespace Core{

        // private data
        Thread::PrivateData::PrivateData( const String& _thread_name )
            :m_runner()
            ,m_threadName( _thread_name )
            ,m_isFinished( false )
            ,m_isWaiting( !false ){

        }

        Thread::PrivateData::PrivateData( UniquePtr<Runner> &&runner,  const String& _thread_name )
            :m_runner( std::move( runner ) )
            ,m_threadName( _thread_name )
            ,m_isFinished( false )
            ,m_isWaiting( !false ){

        }

        Thread::PrivateData::~PrivateData(){
            // exit if not finished 
            if( !m_isFinished ){
                Thread::exit( 3 );
            }
        }

        // exception code for VS_Debuger
#      define VS_DEBUGER_EXCEPTION_CODE 0x406D1388

        // thread info for SEH
        typedef struct tagTHREADNAME_INFO
        {
            DWORD dwType;
            LPCSTR szName;
            DWORD dwThreadID;
            DWORD dwFlags;
        } THREADNAME_INFO;

        // set the name of the thread
        VOID WINAPI SetThreadName(  LPCSTR szThreadName, CONST DWORD dwThreadID ){
            THREADNAME_INFO _info;
            ::memset( &_info, 0, sizeof( THREADNAME_INFO ) );

            _info.dwType = 0x1000;  // must be 0x1000
            _info.szName = szThreadName;    // NO check; can NOT contains another characters except ASSIC characters
            _info.dwThreadID = dwThreadID;

            __try{
                ::RaiseException( VS_DEBUGER_EXCEPTION_CODE
                    , 0
                    , sizeof( THREADNAME_INFO ) / sizeof( DWORD )
                    , reinterpret_cast<const ULONG_PTR *>( &_info ) );
            } __except( EXCEPTION_CONTINUE_EXECUTION )
            {}
        }

        class RunnerWrapper{
        public:
            static void doRun( UniquePtr<Runner>& runner );
        };

         void RunnerWrapper::doRun( UniquePtr<Runner>& runner ){
            // get runner to run
            __try{
                ( *runner )();
            } __except(EXCEPTION_EXECUTE_HANDLER){
                //### dispatch exception 
            }
         }

        // thread callback
         void MAGNA_CDECL _ThreadCallback( void * _param ){
                if( Nullptr != _param ){
                    auto _thread_instance = ( *static_cast<Thread *>( _param ) );

                    auto &_p_thread_data = ThreadAccessor::getThreadPrivateData( _thread_instance );
                    auto &_thread_data = *( _p_thread_data );

                    LOCK_GUARD( _p_thread_data.getSelfLocker() )
                    {
                        // update current thread name
                        auto _assic_thread_name = _thread_data.m_threadName.toString().c_str();
                        SetThreadName( _assic_thread_name, ::GetCurrentThreadId() );
                        ::SetThreadPriority( _thread_data.m_threadHandle, _thread_data.m_priority );    //
                        ULONG _stack_size = _thread_data.m_stackSize;
                        ::SetThreadStackGuarantee( &_stack_size );  //

                        RunnerWrapper::doRun( _thread_data.m_runner );
                        // switch state
                        _thread_data.m_isFinished = !false;
                    }
                }
        }

        void Thread::run(){
            if( !m_data.isNull() && !m_data->m_runner.isNull() ){
                // current thread must be locked
                HANDLE _thread_handle = reinterpret_cast<HANDLE>( _beginthread( _ThreadCallback
                                                                            , m_data->m_stackSize
                                                                            , this ) );
                if( Nullptr != _thread_handle ){

                }
            }
        }

        void Thread::syncRun(){
            if( !m_data.isNull() && !m_data->m_runner.isNull() ){
                // acquire the locker here in order to prevent deleting the data from other threads
                m_data.getSelfLocker().acquires();

                HANDLE _thread_handle = reinterpret_cast<HANDLE>( _beginthread( _ThreadCallback
                                                                            , m_data->m_stackSize
                                                                            , this ) );

                if( Nullptr != _thread_handle ){
                    ::WaitForSingleObject( _thread_handle, INFINITE );
                }
            }
        }

        void Thread::setThreadStackSize( uint32 _size ){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( !m_data->m_isFinished
                    && m_data->m_threadId == ::GetCurrentThreadId() ){    // must be current thread to call this
                    ULONG _stack_size = _size;
                    if( ::SetThreadStackGuarantee( &_stack_size ) ){
                        m_data->m_stackSize = _size;
                    }
                } else{
                    m_data->m_stackSize = _size;
                }
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::wait(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( m_data->m_threadId == ::GetCurrentThreadId()    // must be called within current thread
                    && !m_data->m_isWaiting ){
                    auto _wait_mutex = ::CreateMutex( Nullptr, FALSE, Nullptr );
                    if( Nullptr != _wait_mutex ){
                        m_data->m_waitMutex = _wait_mutex;
                        m_data->m_isWaiting = !false;
                        ::WaitForSingleObject( _wait_mutex, INFINITE );
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::cancelWait(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( m_data->m_threadId == ::GetCurrentThreadId()    // must be called within current thread
                    && m_data->m_isWaiting ){
                    if( ::ReleaseMutex( m_data->m_waitMutex ) ){
                        m_data->m_waitMutex = Nullptr;
                    }
                }
                PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::setPriority( uint32 _priority ){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( !m_data->m_isFinished ){
                    if( ::SetThreadPriority( m_data->m_threadHandle, _priority ) ){
                        m_data->m_priority = _priority;
                    }
                } else{
                    m_data->m_priority = _priority;
                }
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::terminate(){
            PRIVATE_DATA_NOT_NULL_BEGIN
                LOCK_GUARD( m_data.getSelfLocker() )
                if( m_data->m_threadId == ::GetCurrentThreadId() ){    // must be called within current thread
                    if( ::TerminateThread( m_data->m_threadHandle, 0 ) ){
                        m_data->m_isFinished = !false;
                    }
                }
            PRIVATE_DATA_NOT_NULL_END
        }

        void Thread::usleep( uint32 microsec ){
            ::Sleep( microsec / 1000 );
        }

        void Thread::sleep( uint32 ms ){
            ::Sleep( ms );
        }

        void Thread::exit( uint32 _exit_code ){
            Thread &_current_thread = Thread::getCurrentThread();
            if( !_current_thread.isNull() ){
                // notify the current thread and do the clean up
                _current_thread.m_data->m_isFinished = !false;
                _current_thread.m_data->m_threadId = 0;
                _current_thread.m_data->m_threadHandle = Nullptr;
                _current_thread.m_data->m_waitMutex = Nullptr;
            }

            ::ExitThread( _exit_code );
        }

        void Thread::yield(){
            ::Sleep( 0 );
        }

        bool Thread::operator == ( const Thread& _thread ){
            bool _is_equal = false;
            if( !m_data.isNull() && !_thread.m_data.isNull() ){
                LOCK_GUARD( _thread.m_data.getSelfLocker() )
                {
                    LOCK_GUARD( _thread.m_data.getSelfLocker() )
                    _is_equal = m_data->m_threadId == _thread.m_data->m_threadId;
                }
            }
            return _is_equal;
        }
    }
}


#endif