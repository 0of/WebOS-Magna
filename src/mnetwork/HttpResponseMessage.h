#ifndef HTTPRESPONSEMESSAGE_H
#define HTTPRESPONSEMESSAGE_H

#include <sstream>

namespace Magna{
  namespace Network{
    
    class HttpResponseMessage{
      friend class HttpResponseFactory;

    public:
      enum ReturnCode{
        ReturnCode_Invalid = 0

        ,ReturnCode_Continue = 100

        ,ReturnCode_Ok = 200
        ,ReturnCode_Created = 201
        ,ReturnCode_Accepted = 202
        ,ReturnCode_NonAuthoritativeInfo = 203
        ,ReturnCode_NoContent = 204

        ,ReturnCode_MultipleChoices = 300
        ,ReturnCode_MovedPermanently = 301
        ,ReturnCode_Found = 302
        ,ReturnCode_SeeOther = 303
        ,ReturnCode_NotModified = 304

        ,ReturnCode_BadRequest = 400
        ,ReturnCode_Unauthorized = 401
        ,ReturnCode_PaymentRequired = 402
        ,ReturnCode_Forbidden = 403
        ,ReturnCode_NotFound = 404

        ,ReturnCode_InternalServerError = 500
        ,ReturnCode_NotImplemented = 501
        ,ReturnCode_BadGateway = 502
        ,ReturnCode_ServiceUnavailable = 503
        ,ReturnCode_GatewayTimeout = 504
      };

    protected:
      HttpResponseMessage()
        :m_entityData()
        ,m_retCode(ReturnCode_Invalid)
        ,m_headerData(){

      }

    public:
      ~HttpResponseMessage(){

      }

    public:
      inline const std::stringstream &getEntityData() const{
        return m_entityData;
      }

      inline ReturnCode getReturnCode() const{
        return m_retCode;
      }

      inline const std::stringstream &getHeaderData() const{
        return m_headerData;
      }

    private:
      //entity
      std::stringstream m_entityData;
      //return code
      ReturnCode m_retCode;
      //header
      std::stringstream m_headerData;
    };

  }//namespace Network
}//namespace Magna

#endif  /*  HTTPRESPONSEMESSAGE_H  */