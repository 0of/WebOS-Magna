#ifndef WEAKPTR_H
#define WEAKPTR_H

#include "basedef_lib.h"

#include "BasePtr.h"
#include "DefaultDeleter.h"
#include "LockGuard.h"

namespace Magna{
    namespace Core{

        //!    Weak pointer as a pointer tracker.
        /*
         *    \details 
         *      a weak pointer always can be used as a tracker of a pointer points to a block of memory which allocated in the heap.
         *      
         *      a weak pointer must be assigned by another SharedPtr or WeakPtr if the weak pointer enables the tracking behavior.
         *       The tracking behavior can be achieved by hasExpired() indicating whether the pointer has been deleted or not.
         *      
         *      you can call shares() to obtain a SharedPtr to access the pointer.
         *
         *      \em this class is thread safe.
         *
         *    \author  Magnus
         *    \version 1.0.0.1
         *    \date     2013/9/9
         */
        template<typename _Pointer_Type, typename _Deleter = DefaultDeleter<_Pointer_Type> >
        class BASEDEF_LIB_EXPORT WeakPtr : public _CountedReferenceBasePtr<_Pointer_Type, _Deleter>{

            typedef WeakPtr<_Pointer_Type, _Deleter> _Self_Type;
            typedef _CountedReferenceBasePtr<_Pointer_Type, _Deleter> _Base_Type;

            __Constructor_Destructor public:
                //!    Default constructor with null pointer and reference data
                WeakPtr() : _Base_Type(){}

                //!    Constructor with managed pointer
                /*
                 *      \praram _managed_ptr
                 *          managed pointer must be not a null pointer including raw pointer and reference counter values
                 *          the managed pointer can be SharedPtr,  initialized UniquePtr.
                 */
                explicit WeakPtr( const _CountedReferenceBasePtr<_Pointer_Type, _Deleter>& _managed_ptr )
                    : _Base_Type(){

                    LOCK_GUARD( _managed_ptr.getSelfLocker() )
                    if( !_managed_ptr.isNull() ){
                        _Base_Type::operator = ( _managed_ptr );
                        ++m_refData->m_weakRefCount;
                    }
                }

                WeakPtr( const _Self_Type& _weak_ptr )
                    : _Base_Type(){

                    LOCK_GUARD( _weak_ptr.m_selfLocker )
                    if( Nullptr != _weak_ptr.m_refData ){
                        _Base_Type::operator = ( _weak_ptr );
                        ++m_refData->m_weakRefCount;
                    }
                }

                ~WeakPtr(){
                    LOCK_GUARD( m_selfLocker )
                    weakDetaches();
                }

            public:
                SharedPtr<_Pointer_Type, _Deleter> shares(){
                    SharedPtr<_Pointer_Type, _Deleter> _shared_ptr;
                    {
                        LOCK_GUARD( m_selfLocker )
                        if( Nullptr != m_refData && 0 != m_refData->m_refCount.read() ){
                            //expired
                            ++m_refData->m_refCount;
                            _shared_ptr._Base_Type::operator = ( *this );
                        }
                    }
                    return _shared_ptr;
                }

                void reset(){
                    LOCK_GUARD( m_selfLocker )
                    weakDetaches();
                    _Base_Type::clear();
                }

            __Checker public:
                bool hasExpired() const{
                    bool _expired = false; 
                    {
                        LOCK_GUARD( m_selfLocker )
                        if( Nullptr != m_refData ){
                            _expired = 0 == m_refData->m_refCount.read();
                        }
                    }
                    return _expired;
                }

            __Overloaded_Methods public:
                _Self_Type & operator = ( const SharedPtr<_Pointer_Type, _Deleter>& _managed_shared_ptr ){
                    {
                        LOCK_GUARD( _managed_shared_ptr.m_selfLocker )
                        {
                            LOCK_GUARD( m_selfLocker )
                            //two tracking pointers shall not be the same 
                            if( _Base_Type::m_rawPtr != _managed_shared_ptr._Base_Type::m_rawPtr ){
                                weakDetaches();

                                //reference data pointer modified
                                _Base_Type::operator = ( _managed_shared_ptr );
                                weakAttaches();
                            }
                        }
                    }
                    return *this;
                }

                _Self_Type & operator = ( const _Self_Type& _weak_ptr ){
                    {
                        LOCK_GUARD( _weak_ptr.m_selfLocker )
                        {
                            LOCK_GUARD( m_selfLocker )
                            //two tracking pointers shall not be the same 
                            if( _Base_Type::m_rawPtr != _weak_ptr._Base_Type::m_rawPtr ){
                                //detaches
                                weakDetaches();

                                //reference data pointer modified
                                _Base_Type::operator = ( _weak_ptr );
                                weakAttaches();
                            }
                        }
                    }
                    return *this;
                }

            protected:
                inline void weakAttaches(){
                    if( Nullptr != m_refData ){
                        ++m_refData->m_weakRefCount;
                    }
                }

                inline void weakDetaches(){
                    if( Nullptr != m_refData ){
                        --m_refData->m_weakRefCount;
                        _Base_Type::disposeReferenceData();
                    }
                }
        };

    }
}

#endif  /*  WEAKPTR_H   */