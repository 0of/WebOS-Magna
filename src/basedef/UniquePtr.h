#ifndef UNIQUEPTR_H
#define UNIQUEPTR_H

#include "BasePtr.h"
#include "SharedPtr.h"
#include "WeakPtr.h"

namespace Magna{
    namespace Core{

        template<typename _Pointer_Type, typename _Deleter = DefaultDeleter<_Pointer_Type> >
        class UniquePtr : public _CountedReferenceBasePtr<_Pointer_Type, _Deleter>{
            typedef UniquePtr<_Pointer_Type, _Deleter> _Self_Type;
            typedef typename PointerTypeTrait<_Pointer_Type>::_Type _Given_Pointer_Type;
            typedef _CountedReferenceBasePtr<_Pointer_Type, _Deleter> _Base_Type;

            __Constructor_Destructor public:
                UniquePtr()
                    : _Base_Type(){}

                UniquePtr( _Given_Pointer_Type * _given_pointer )
                     : _Base_Type( _given_pointer ){}

                UniquePtr( _Self_Type && _move_ptr )
                     : _Base_Type( std::move( _move_ptr ) ){}

                ~UniquePtr(){
                    if( Nullptr != _Base_Type::m_rawPtr ){
                        _Deleter::deletes( _Base_Type::m_rawPtr );
                    }
                }

            __To_Methods public:
                SharedPtr<_Pointer_Type, _Deleter> toSharedPtr(){
                    LOCK_GUARD( m_selfLocker )
                    SharedPtr<_Pointer_Type, _Deleter> _shared_ptr( _Base_Type::m_rawPtr );
                    _Base_Type::clear();
                    return _shared_ptr;
                }

                WeakPtr<_Pointer_Type, _Deleter> toWeakPtr(){
                    {
                        LOCK_GUARD( m_selfLocker )
                        if( Nullptr != _Base_Type::m_rawPtr ){
                            _Base_Type::init();
                        }
                    }
                    return WeakPtr<_Pointer_Type, _Deleter>( *this );
                }

            __Overloaded_Methods public:
                inline const _Given_Pointer_Type * operator -> () const { return _Base_Type::m_rawPtr; }
                inline _Given_Pointer_Type * operator -> () { return _Base_Type::m_rawPtr; }
                inline _Given_Pointer_Type &operator * (){ return *_Base_Type::m_rawPtr; }
                inline const _Given_Pointer_Type &operator * () const { return *_Base_Type::m_rawPtr; }

                UniquePtr& operator = ( _Self_Type && _move_ptr ){
                    {
                        LOCK_GUARD( _move_ptr.m_selfLocker )
                        {
                            LOCK_GUARD( m_selfLocker )
                            _Base_Type::operator = ( std::move( _move_ptr ) );
                        }
                    }
                    return *this;
                }

            private:
                UniquePtr( const _Self_Type& ) MAGNA_DELETE ;
                _Self_Type& operator = ( const _Self_Type& ) MAGNA_DELETE ;
        };
    }
}

#endif  /*  UNIQUEPTR_H */