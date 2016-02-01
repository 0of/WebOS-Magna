#ifndef IMPLATOMICTYPE_H
#define IMPLATOMICTYPE_H

#include "../SystemDef.h"

#include "../CompilerTimeAssert.h"
#include "../StaticTypeTrait.h"

namespace Magna{

    template<typename _Byte_Type>
    class ByteAtomicImplementor{
    public:
#ifdef MAGNA_X86
        static inline void atomicInc( volatile _Byte_Type *atomicIntPtr ) {

#ifdef _MSC_VER
            __asm {
                    mov eax, atomicIntPtr
                    lock inc byte ptr[eax]
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "lock incb (%%eax)"
                :
            :"a" (atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline void atomicDec( volatile _Byte_Type *atomicIntPtr ) {
#ifdef _MSC_VER
            __asm {
                    mov eax, atomicIntPtr
                    lock dec byte ptr[eax]
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "lock decb (%%eax)"
                :
            :"a" (atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline void atomicWrite( volatile _Byte_Type *atomicIntPtr, _Byte_Type val ) {

#ifdef _MSC_VER
            __asm {
                    mov eax, atomicIntPtr
                    mov bl, val
                    lock xchg byte ptr[eax], bl
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "movb %1, %%bl \t\n"
                "lock xchgb %%bl,(%%eax)"
                :
            :"a"(atomicIntPtr),"m"(val)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline _Byte_Type atomicRead( volatile const _Byte_Type * atomicIntPtr ) {
            _Byte_Type ret_val = 0;
#ifdef _MSC_VER
            __asm {
                    xor bl, bl
                    mov eax, atomicIntPtr
                    lock xadd byte ptr[eax], bl
                    mov ret_val, bl
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "xor %%bl, %%bl \t\n"
                "lock xaddb %%bl, (%%eax) \t\n"
                "movl %%bl, %0\t\n"
                :"=m"(ret_val)
                :"a"(atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
            return ret_val;
        }

#endif  /*  MAGNA_X86  */
    };



    template<typename _DWord_Type>
    class DWordAtomicImplementor{
    public:
#ifdef MAGNA_X86
        static inline void atomicInc( volatile _DWord_Type *atomicIntPtr ) {

#ifdef _MSC_VER
            __asm {
                mov eax, atomicIntPtr
                    lock inc dword ptr[eax]
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "lock incl (%%eax)"
                :
            :"a" (atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline void atomicDec( volatile _DWord_Type *atomicIntPtr ) {
#ifdef _MSC_VER
            __asm {
                mov eax, atomicIntPtr
                    lock dec dword ptr[eax]
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "lock decl (%%eax)"
                :
            :"a" (atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline void atomicWrite( volatile _DWord_Type *atomicIntPtr, _DWord_Type val ) {

#ifdef _MSC_VER
            __asm {
                mov eax, atomicIntPtr
                    mov ebx, val
                    lock xchg dword ptr[eax], ebx
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "movl %1, %%ebx \t\n"
                "lock xchgl %%ebx,(%%eax)"
                :
            :"a"(atomicIntPtr),"m"(val)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
        }

        static inline _DWord_Type atomicRead( volatile const _DWord_Type * atomicIntPtr ) {
            _DWord_Type ret_val = 0;
#ifdef _MSC_VER
            __asm {
                xor ebx, ebx
                    mov eax, atomicIntPtr
                    lock xadd dword ptr[eax], ebx
                    mov ret_val, ebx
            }
#elif defined __GNUC__
            __asm__ __volatile__(
                "xor %%ebx, %%ebx \t\n"
                "lock xaddl %%ebx, (%%eax) \t\n"
                "movl %%ebx, %0\t\n"
                :"=m"(ret_val)
                :"a"(atomicIntPtr)
                );
#else
#error UNKNOW_COMPILE_ENV
#endif
            return ret_val;
        }

#endif  /*  MAGNA_X86  */
    };

    template<typename _Base_Type>
    class AtomicImplementor;

    template<> class BASEDEF_LIB_EXPORT AtomicImplementor< sint32 > : public DWordAtomicImplementor< sint32 >{};
    template<> class BASEDEF_LIB_EXPORT AtomicImplementor< uint32 > : public DWordAtomicImplementor< uint32 >{};

    template<> class BASEDEF_LIB_EXPORT AtomicImplementor< uint8 > : public ByteAtomicImplementor< uint8 >{};
    template<> class BASEDEF_LIB_EXPORT AtomicImplementor< sint8 > : public ByteAtomicImplementor< sint8 >{};
    template<> class BASEDEF_LIB_EXPORT AtomicImplementor< bool > : public ByteAtomicImplementor< bool >{};

}//Magna
#endif  /*  IMPLATOMICTYPE_H  */
