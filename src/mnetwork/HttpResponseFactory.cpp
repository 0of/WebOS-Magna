#include "HttpResponseFactory.h"

#include <regex>

namespace Magna{
  namespace Network{
    
    HttpResponseFactory &HttpResponseFactory::getHttpResponseFactory(){
      static HttpResponseFactory _factory;
      return _factory;
    }

    HttpResponseFactory::HttpResponseFactory(){

    }

    HttpResponseFactory::~HttpResponseFactory(){

    }

    HttpResponseMessage* HttpResponseFactory::produces(){
      HttpResponseMessage *_mess = new HttpResponseMessage;
      //clear buffer
      _mess->m_entityData.clear();
      _mess->m_entityData.str( "" );

      _mess->m_headerData.clear();
      _mess->m_headerData.str( "" );
      return _mess;
    }

    uint32  HttpResponseFactory::processMessageHeader( HttpResponseMessage*mess, void *d,  uint32 u, uint32 total){
      uint32 _process_num = 0;
      if( mess != Nullptr ){

        _process_num = u * total ;

        //extract the return code from header
        //another way to fetch this is using CURLINFO_RESPONSE_CODE
        //
        if( mess->m_retCode == HttpResponseMessage::ReturnCode_Invalid ){
          //read return code
          std::regex reg( "(HTTP|http)/\\d\.\\d\\s\\d{3}" );

          std::string _ret_info( reinterpret_cast<const assic_char *>(d) , _process_num );
          std::sregex_iterator _matched_iter(  _ret_info.begin(), _ret_info.end() , reg );

          if( _matched_iter != std::sregex_iterator() ){
            auto &_matched_str = _matched_iter->str();
            
            //ensure the size is higher than 3 (3 figures)
            if( _matched_str.size() > 3 ){
              auto &_ret_cod_in_str = _matched_str.substr(  _matched_str.size() - 3 );
              try{
                const auto&_code = stoul( _ret_cod_in_str );
                mess->m_retCode = static_cast< HttpResponseMessage::ReturnCode >(_code);
              }
              catch(const std::invalid_argument& _invalid_arg){
                //can not convert from invalid string
                abort();
              }
            }
          }
        }

        auto &_header_data_output = mess->m_headerData;

        _header_data_output.write( reinterpret_cast<const assic_char *>(d) , _process_num ) ;
      }
      return _process_num;
    }

    uint32 HttpResponseFactory::processMessageEntity( HttpResponseMessage*mess, void *d,  uint32 u, uint32 total){
      uint32 _process_num = 0;
      if( mess != Nullptr ){
        auto &_entity_data_output = mess->m_entityData;

        _process_num = u * total ;
        _entity_data_output.write( reinterpret_cast<const assic_char *>(d) , _process_num );
      }
      return _process_num;
    }

  }//namespace Network
}//namespace Magna