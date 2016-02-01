#ifndef EVENTDELEGATOR_H
#define EVENTDELEGATOR_H

#include "basegui_lib.h"

#include "basedef/SystemDef.h"
#include "basedef/BaseTypes.h"
#include "basedef/CompilerTimeAssert.h"
#include "basedef/IsBaseOf.h"
using namespace Magna::Core;

namespace Magna{
  namespace GUI{
    class NullDelegator{};

    template<
      typename BaseType
      , typename ParameterType = NullType
    >
    class Delegator;

    template<
      typename BaseType
    >
    class Delegator<BaseType, NullType>{
      typedef void(BaseType::*DelegatorType)();
      __Constructor_Destructor public:
      Delegator()
        :m_delegator( Nullptr ){

      }

      template<typename Binder>
      Delegator( void(Binder::*customizedDelegator )() )
        :m_delegator( Nullptr ) {
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )
        m_delegator = *reinterpret_cast<DelegatorType *>( &customizedDelegator );
      }

      Delegator( const Delegator<BaseType>& d )
        :m_delegator( d.m_delegator ){

      }

    public:
      template<typename Binder>
      void invoke( Binder&invoker ){
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

          if( m_delegator != Nullptr ){
            (invoker.*m_delegator)();
          }
      }

      template<typename Binder>
      void invoke( Binder*invoker ){
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

          if( invoker != Nullptr && m_delegator != Nullptr ){
            (invoker->*m_delegator)();
          }
      }

      __Overloaded_Methods public:
      template<typename Binder>
      Delegator<BaseType>&  operator = ( void(Binder::*customizedDelegator )() ){
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

        m_delegator = *reinterpret_cast<DelegatorType *>( &customizedDelegator );

        m_delegator = customizedDelegator;
        return *this;
      }

      bool operator == ( const NullDelegator& nullDelegator ){
        return m_delegator == Nullptr;
      }

      bool operator != ( const NullDelegator& nullDelegator ) {
        return m_delegator != Nullptr;
      }

      bool operator == ( const NullDelegator& nullDelegator ) const{
        return m_delegator == Nullptr;
      }

      bool operator != ( const NullDelegator& nullDelegator ) const {
        return m_delegator != Nullptr;
      }

      __Data_Field private:
      DelegatorType m_delegator;
    };

    template<
            typename BaseType
            , typename ParameterType
            >
    class BASEGUI_LIB_EXPORT Delegator{
      typedef void(BaseType::*DelegatorType)(ParameterType&);
    __Constructor_Destructor public:
      Delegator()
        :m_delegator( Nullptr ){

      }

      template<typename Binder, typename InputParameterType>
      Delegator( void(Binder::*customizedDelegator )(InputParameterType&) )
        :m_delegator( Nullptr ) {
        typedef IsBaseOf<InputParameterType, ParameterType> ParameterIsBaseOf;
        COMPILTER_TIME_ASSERT( ParameterIsBaseOf::isTrue, Parameter_Type_Error )

        m_delegator = *reinterpret_cast<DelegatorType *>( &customizedDelegator );
      }

      Delegator( const Delegator<BaseType, ParameterType>& d )
        :m_delegator( d.m_delegator ){

      }

    public:
      template<typename Binder>
      void invoke( Binder&invoker,  ParameterType& para ){
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

        if( m_delegator != Nullptr ){
          (invoker.*m_delegator)( para );
        }
      }

      template<typename Binder>
      void invoke( Binder*invoker,  ParameterType& para ){
        typedef IsBaseOf<Binder, BaseType> BinderIsBaseOfBaseType;
        COMPILTER_TIME_ASSERT( BinderIsBaseOfBaseType::isTrue, Invoker_Type_Error )

        if( invoker != Nullptr && m_delegator != Nullptr ){
          (invoker->*m_delegator)( para );
        }
      }

    __Overloaded_Methods public:
      template<typename Binder>
      Delegator<BaseType, ParameterType>&  operator = ( void(Binder::*customizedDelegator )(ParameterType&) ){
        typedef IsBaseOf<Binder, ParameterType> ParameterIsBaseOf;
        COMPILTER_TIME_ASSERT( ParameterIsBaseOf::isTrue, Parameter_Type_Error )

        m_delegator = *reinterpret_cast<DelegatorType *>( &customizedDelegator );

        m_delegator = customizedDelegator;
        return *this;
      }

      bool operator == ( const NullDelegator& nullDelegator ){
        return m_delegator == Nullptr;
      }

      bool operator != ( const NullDelegator& nullDelegator ) {
        return m_delegator != Nullptr;
      }

      bool operator == ( const NullDelegator& nullDelegator ) const{
        return m_delegator == Nullptr;
      }

      bool operator != ( const NullDelegator& nullDelegator ) const {
        return m_delegator != Nullptr;
      }

    __Data_Field private:
      DelegatorType m_delegator;
    };
  }//namespace GUI
}//namespace Magna

#endif  /*  EVENTDELEGATOR_H  */
