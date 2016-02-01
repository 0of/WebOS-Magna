#ifndef HTTPREQUESTMESSAGE_H
#define HTTPREQUESTMESSAGE_H

#include "basedef/BaseTypes.h"
#include "basedef/SystemDef.h"
#include "basedef/String.h"
using namespace Magna::Core;

#include <map>

namespace Magna{
  namespace Network{
    
    typedef std::map<String,String> ParameterField;
    class HttpRequestMessage{
    
      __Constants public:
        enum Method{
          Method_GET
          ,Method_HEAD
          ,Method_POST
          ,Method_PUT
        };

      __Constructor_Destructor public:
        HttpRequestMessage();
        explicit HttpRequestMessage( const String& url, Method );
        HttpRequestMessage( const HttpRequestMessage& );
        ~HttpRequestMessage();

      __Setter public:
        void setHost( const String& );
        void setURLString( const String& );
        void setHeader( const String& );
        void setParameterField( const ParameterField& );
        void setMethod( const Method& );

      __Getter public:
        inline String getHeader() const{
          return m_headerString ;
        }

        String getHost() const;
    
        String getURLString() const{
          return m_URLString;
        }

        const ParameterField& getParameterField() const{
          return m_parameterField;
        }

        Method getMethod() const{
          return m_method;
        }

      __Checker public:
        bool isValid() const;

      __Overloaded_Methods public:
        HttpRequestMessage& operator =( const HttpRequestMessage& );

      __Data_Field private:
        String m_headerString;
        String m_URLString;
        ParameterField m_parameterField;
        Method m_method;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  HTTPREQUESTMESSAGE_H  */