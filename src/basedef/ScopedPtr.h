#ifndef SCOPEDPTR_H
#define SCOPEDPTR_H

#include "basedef/Uncopyable.h"
#include "basedef/PointerTrait.h"
#include "basedef/DefaultDeleter.h"

namespace Magna{
    namespace Core{
        // 9/28
        template<typename _Pointer_Type, typename _Deleter = DefaultDeleter<_Pointer_Type> >
        class ScopedPtr : Uncopyable{
            typedef typename PointerTypeTrait<_Pointer_Type>::_Type _Given_Pointer_Type;
            typedef typename ScopedPtr<_Pointer_Type, _Deleter> _Self_Type;

            public:
                ScopedPtr( _Given_Pointer_Type *_raw_ptr )
                    :m_rawPtr( _raw_ptr ){}
                ~ScopedPtr(){
                    _Deleter::deletes( m_rawPtr );
                }

            private:
                ScopedPtr( const _Self_Type& );
                _Self_Type & operator = ( const _Self_Type& );

            public:
                inline _Given_Pointer_Type *operator -> (){
                    return m_rawPtr;
                }

                inline const _Given_Pointer_Type *operator -> () const{
                    return m_rawPtr;
                }

                inline _Given_Pointer_Type &operator * (){
                    return *m_rawPtr;
                }

                inline const _Given_Pointer_Type &operator * () const{
                    return *m_rawPtr;
                }

            __Data_Field private:
                _Given_Pointer_Type *m_rawPtr;
        };
    }
}

#endif  /*  SCOPEDPTR_H */