#ifndef DEFAULTDELETER_H
#define DEFAULTDELETER_H

namespace Magna{
    namespace Core{

        template<typename T>
        class DefaultDeleter{
            public:
                static void deletes( T *_raw_pointer ){
                    if( Nullptr != _raw_pointer ){
                        delete _raw_pointer;
                    }
                }
        };

        template<typename T>
        class DefaultDeleter<T[]>{
            public:
                static void deletes( T *_raw_pointer ){
                    if( Nullptr != _raw_pointer ){
                        delete [] _raw_pointer;
                    }
                }
        };

    }
}

#endif  /*  DEFAULTDELETER_H    */