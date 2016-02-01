#ifndef ATOMICTYPE_H
#define ATOMICTYPE_H

#include "basedef_lib.h"

#include "private/ImplAtomicType.h"

namespace Magna{
  namespace Core{

        template<typename _Type>
        class BASEDEF_LIB_EXPORT Atomic{
            typedef Atomic<_Type> _Self_Type;
            typedef AtomicImplementor<_Type> _Impl_Type;

            __Constructor_Destructor public:
                explicit Atomic( _Type init_val )
                    :m_atomicValue( init_val ){}
                Atomic( volatile const _Self_Type& atomic_init )
                    :m_atomicValue( atomic_init.read() ){}

                ~Atomic(){}

            public:
                _Type read() const volatile{
                    return _Impl_Type::atomicRead( &m_atomicValue );
                }

                void write( const _Type val ) volatile{
                    _Impl_Type::atomicWrite( &m_atomicValue, val );
                }

            __Overloaded_Methods public:
                _Self_Type volatile& operator ++() volatile{
                    _Impl_Type::atomicInc( &m_atomicValue );
                    return *this;
                }

                _Self_Type volatile& operator --() volatile{
                    _Impl_Type::atomicDec( &m_atomicValue );
                    return *this;
                }

                _Self_Type volatile& operator =( volatile const _Self_Type& atomic_value ) volatile{
                    _Type _read_value = atomic_value.read();
                    _Impl_Type::atomicWrite( &m_atomicValue, _read_value );
                    return *this;
                }

                //not locked the cmp instruction
                bool volatile operator == ( volatile const _Type& _cmp_value ) volatile{
                    return _cmp_value == m_atomicValue.read();
                }

                bool volatile operator != ( volatile const _Type& _cmp_value ) volatile{
                    return _cmp_value != m_atomicValue.read();
                }

            private:
                _Type m_atomicValue;
        };

        template<>
        class BASEDEF_LIB_EXPORT Atomic<bool>{
            typedef Atomic<bool> _Self_Type;
            typedef AtomicImplementor<bool> _Impl_Type;

            __Constructor_Destructor public:
                explicit Atomic( bool init_val )
                    :m_atomicValue( init_val ){}

                ~Atomic(){}

            __Overloaded_Methods public:
                operator bool () volatile const{
                    return _Impl_Type::atomicRead( &m_atomicValue );
                }

                _Self_Type volatile& operator = ( volatile const bool bool_value ) volatile{
                    _Impl_Type::atomicWrite( &m_atomicValue, bool_value );
                    return *this;
                }

                //not locked the cmp instruction
                bool volatile operator == ( volatile const _Self_Type& _cmp_value ) volatile{
                    return _cmp_value == _Impl_Type::atomicRead( &m_atomicValue );
                }

                bool volatile operator != ( volatile const _Self_Type& _cmp_value ) volatile{
                    return _cmp_value != _Impl_Type::atomicRead( &m_atomicValue );
                }

            private:
                bool m_atomicValue;
        };
        
        template<typename _Type>
        BASEDEF_LIB_EXPORT bool operator == ( const _Type& _cmp, const Atomic<_Type>& _atomic){
            return _cmp == _atomic.read();
        }

        template<typename _Type>
        BASEDEF_LIB_EXPORT bool operator != ( const _Type& _cmp, const Atomic<_Type>& _atomic){
            return _cmp != _atomic.read();
        }

        typedef Atomic<sint32> AtomicInt;
        typedef Atomic<bool> AtomicBool;
    }
}//namespace Magna

#endif  /*  ATOMICTYPE_H    */