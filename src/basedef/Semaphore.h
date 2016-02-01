#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "basedef/Thread.h"
#include "basedef/AtomicType.h"

namespace Magna{
    namespace Core{
        // 9/28

        // initiation value is 0
        // semaphore value is lower than permits which means 
        // any other threads can acquire available semaphore.
        // if any threads want to acquire semaphore if value is ever higher than permits 
        // those threads would be waiting till any available semaphore has been released.
        template<uint32 _permits = 1>
        class BasicSemaphore{
           public:
               // default is binary semaphore
               // for basic semaphore no such fair preemption
               // \sa Semaphore
               BasicSemaphore()
                   :m_semaphoreValue( 0 ){}
               ~BasicSemaphore(){}

            public:
                //
                void acquires(){
                    ++m_semaphoreValue;
                    for( ; m_semaphoreValue.read() <= _permits; Thread::yield() ){}
                }

                void releases(){
                    if( m_semaphoreValue.read() > 0 ){
                        --m_semaphoreValue;
                    }
                }

                void acquires() const{
                    ++m_semaphoreValue;
                    for( ; m_semaphoreValue.read() <= _permits; Thread::yield() ){}
                }

                void releases() const{
                    if( m_semaphoreValue.read() > 0 ){
                        --m_semaphoreValue;
                    }
                }

                bool tryAcquire() const{
                    bool _tried_successfully = false;
                    ++m_semaphoreValue;
                    if( m_semaphoreValue.read() <= _permits ){
                        _tried_successfully = !false;
                    } else{
                        --m_semaphoreValue;
                    }
                    return _tried_successfully;
                }

                uint32 getWaitingNumber() const{
                    uint32 _waiting_number = 0;
                    auto _semaphore_value = m_semaphoreValue.read();
                    if( _semaphore_value > _permits ){
                        _waiting_number = _semaphore_value - _permits;
                    }
                    return _waiting_number;
                }

            private:
                mutable Atomic<uint32> m_semaphoreValue;
        };

    }
}

#endif  /*  SEMAPHORE_H */