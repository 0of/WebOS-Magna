#ifndef BASEPTR_H
#define BASEPTR_H

#include "IsBaseOf.h"
#include "CompilerTimeAssert.h"

#include "LockGuard.h"
#include "PointerTrait.h"
#include "DefaultDeleter.h"
#include "SpinMutex.h"
#include "AtomicType.h"

namespace Magna{
  namespace Core{

        template<typename _Pointer_Type, typename _Deleter = DefaultDeleter<_Pointer_Type> >
        class _CountedReferenceBasePtr {

            template<typename _Pointer_Type_, typename _Deleter_>
            friend class _CountedReferenceBasePtr;

            protected:
                typedef typename PointerTypeTrait<_Pointer_Type>::_Type _Given_Pointer_Type;

            protected:
                struct CountedReferenceData{
                    CountedReferenceData()
                        :m_refCount( 0 )
                        ,m_weakRefCount( 0 ){}
                    ~CountedReferenceData(){}
                    Atomic<uint32> m_refCount;
                    Atomic<uint32> m_weakRefCount;
                };

            __Constructor_Destructor protected:
                _CountedReferenceBasePtr()
                    :m_refData( Nullptr )
                    ,m_rawPtr( Nullptr )
                    ,m_selfLocker(){}

                _CountedReferenceBasePtr( _Given_Pointer_Type *_raw_ptr )
                    :m_refData( Nullptr )
                    ,m_rawPtr( _raw_ptr )
                    ,m_selfLocker(){}

                _CountedReferenceBasePtr( _CountedReferenceBasePtr<_Pointer_Type, _Deleter> &&_moved_ptr )
                    :m_refData( _moved_ptr.m_refData )
                    ,m_rawPtr( _moved_ptr.m_rawPtr )
                    ,m_selfLocker(){
                    _moved_ptr.clear();
                }

                ~_CountedReferenceBasePtr(){

                }

            __Checker public:
                inline bool isNull() const {
                    return Nullptr == m_rawPtr || Nullptr == m_refData;
                }

            __Getter public:
                inline SpinMutex &getSelfLocker(){
                    return m_selfLocker;
                }

                inline const SpinMutex &getSelfLocker() const{
                    return m_selfLocker;
                }

            __Overloaded_Methods public:
                inline bool operator == ( const _CountedReferenceBasePtr<_Pointer_Type>& ptr ) const{
                    return m_rawPtr == ptr.m_rawPtr;
                }

                inline bool operator != ( const _CountedReferenceBasePtr<_Pointer_Type>& ptr ) const{
                    return m_rawPtr != ptr.m_rawPtr;
                }

            protected:
                //refData shall never be null when call this
                inline void dispose(){
                    // when shared reference count goes to zero,
                    // pointer shall be deleted
                    if( 0 == m_refData->m_refCount.read() ){
                        _Deleter::deletes( m_rawPtr );
                        m_rawPtr = Nullptr;

                        //weak ref is zero, then clear up ref data
                        if( 0 == m_refData->m_weakRefCount.read() ){
                            delete m_refData;
                            m_refData = Nullptr;
                        }
                    }
                }

                inline void disposeReferenceData(){
                    // when weak reference count goes to zero,
                    // which means don't need the pointer tracker
                    // the reference data shall be deleted
                    if( 0 == m_refData->m_refCount.read() //shared ref must be zero
                        && 0 == m_refData->m_weakRefCount.read() ){
                        delete m_refData;
                        m_refData = Nullptr;
                    }
                }

                inline void init(){
                    m_refData = new ( CountedReferenceData );
                }

                inline void clear(){
                    m_rawPtr = Nullptr;
                    m_refData = Nullptr;
                }

            __Overloaded_Methods protected:
                MAGNA_FORCEINLINE _CountedReferenceBasePtr & operator = ( const _CountedReferenceBasePtr<_Pointer_Type, _Deleter>& ptr ){
                    m_rawPtr = ptr.m_rawPtr;
                    m_refData = ptr.m_refData;
                    return *this;
                }

                MAGNA_FORCEINLINE _CountedReferenceBasePtr & operator = ( _CountedReferenceBasePtr<_Pointer_Type, _Deleter>&& ptr ){
                    m_rawPtr = ptr.m_rawPtr;
                    m_refData = ptr.m_refData;
                    ptr.m_rawPtr = Nullptr;
                    ptr.m_refData = Nullptr;
                    return *this;
                }

            __Data_Field protected:
                _Given_Pointer_Type *m_rawPtr;

                // to avoid under the multi-thread circumstance, user uses the pointer
                // as a pointer or a reference( i.e. SharedPtr<T>* or SharedPtr<T>& ) not an instance
                // which may result some devastating situations, I add a self locker which can
                // ensure every single pointer instance self access atomicity. 
                // For example, a pointer reference would assign to
                // a new pointer whereas in anther thread this pointer reference would be assigned by
                // another pointer, and this situation will result if reference data has been deleted 
                // when another thread access the reference data (access violation).
                SpinMutex m_selfLocker;
                CountedReferenceData *m_refData;

            private:
                _CountedReferenceBasePtr( const _CountedReferenceBasePtr<_Pointer_Type, _Deleter>& ptr );
        };

    }
}//namespace Magna

#endif  /*  BASEPTR_H   */