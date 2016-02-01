#ifndef LOCKGUIDE_H
#define LOCKGUIDE_H

#include "Uncopyable.h"

namespace Magna{
  namespace Core{

        template<typename _Locker_Type>
        class LockGuard : Uncopyable{
            public:
                LockGuard( _Locker_Type& locker )
                    :m_locker( locker ){
                    m_locker.acquires();
                }

                ~LockGuard(){
                    m_locker.releases();
                }

            private:
                //local only
                void* operator new( size_t );
                void operator delete( void * );

            private:
                _Locker_Type& m_locker;
        };

#       ifndef LOCK_GUARD
#       define LOCK_GUARD(locker) LockGuard< decltype( locker ) > MAGNA_CONCAT(_local_locker, __LINE__)( locker );
#       endif
    }
}//namespace Magna

#endif  /*  LOCKGUIDE_H */