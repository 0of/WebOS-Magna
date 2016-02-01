#ifndef URIBUILDER_H
#define URIBUILDER_H

#include "Uncopyable.h"
#include "URI.h"

namespace Magna{
    namespace Core{

        class URIBuilder;

        template<typename InputType>
        class URIInputActionDelegator{
        public:
            typedef URI&( URI:: *URIInputAction )(const InputType&);
        public:
            URIInputActionDelegator( URIInputAction action )
                :m_action( action ){}
            URIInputActionDelegator( const URIInputActionDelegator<InputType>& delegator )
                :m_action( delegator.m_action ){}
            ~URIInputActionDelegator(){}
            void actBy( URIBuilder& _actor, const InputType& _param ){
                *(_actor.m_action)( _param );
            }
        private:
            URIInputAction m_action;
        };

        template<typename InputType>
        class URIInputActionPair{
        public:
            URIInputActionPair( URIBuilder& actor, URIInputActionDelegator<InputType> delegator )
                :m_action( action )
                ,m_actor( actor ){}
            ~URIInputActionPair(){}
            URIBuilder& operator << ( const InputType& input_alue ){
                m_action.actBy( m_actor, input_alue );
                return m_actor;
            }
        private:
            URIInputActionDelegator<InputType> m_action;
            URIBuilder& m_actor;
        };

        //!     for URI builder
        class URIBuilder : Uncopyable{
            public:
                static URIInputActionDelegator<String> _URIString;
                static URIInputActionDelegator<String> _Host;
                static URIInputActionDelegator<String> _Scheme;
                static URIInputActionDelegator<String> _Username;
                static URIInputActionDelegator<String> _Password;
                static URIInputActionDelegator<String> _Fragment;
                static URIInputActionDelegator<std::pair<String, String> > _Query;
                static URIInputActionDelegator<std::pair<String, String> > _UserInfo;
                static URIInputActionDelegator<uint16> _Port;

            __Constructor_Destructor public:
                URIBuilder();
                ~URIBuilder();

            __Checker public:
                bool isValid() const;

            public:
                URI builds() const;

            __Setter public:
                URIBuilder& setPort( uint16 port );
                URIBuilder& setScheme( const String& Scheme );
                URIBuilder& setUserInfo( const String& name, const String& password );
                URIBuilder& setUsername( const String& name );
                URIBuilder& setPassword( const String& password );

                URIBuilder& setHost( const String& host );
                URIBuilder& setPath( const String& path );
                URIBuilder& setFragment( const String& fragment );

            public:
                URIBuilder& appendQueryParameter( const std::pair<String, String>& param );
                URIBuilder& appendQueryParameters( const std::map<String, String>& params );

            __Getter public:
                inline uint16 getPort() const { return static_cast<uint16>( m_port ); }
                inline String getScheme() const { return m_scheme; }
                inline String getHost() const { return m_host; }
                inline String getPath() const { return m_path; }
                inline String getFragment() const { return m_fragment; }
                inline std::pair<String, String> getUserInfo() const { return m_userInfo; }
                inline const std::map<String, String>& getQueries() const { return m_queries; }

            __Overloaded_Methods public:
                //!     builder
                // for adding string value
                template<typename InputValueType>
                URIInputActionPair<InputValueType> operator << ( const URIInputActionDelegator<InputValueType>& value ){
                    return URIInputActionPair<InputValueType>( *this, value );
                }

            __Data_Field private:
                uint32 m_port;
                String m_scheme;
                String m_host;
                String m_path;
                String m_fragment;

                std::pair<String, String> m_userInfo;
                std::map<String, String> m_queries;
        };
    }
}

#endif  /*  URIBUILDER_H    */