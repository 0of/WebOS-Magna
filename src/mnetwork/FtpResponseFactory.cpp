#include "FtpResponseFactory.h"

namespace Magna{
  namespace Network{
    
    FtpResponseFactory::FtpResponseFactory(){

    }

    FtpResponseFactory::~FtpResponseFactory(){

    }

     FtpResponseFactory &FtpResponseFactory::getFtpResponseFactory(){
       static FtpResponseFactory _factory;
       return _factory;
     }

    FtpResponseMessage* FtpResponseFactory::produces(){
      return new FtpResponseMessage();
    }

    uint32 FtpResponseFactory::processMessageHeader( FtpResponseMessage*resp, void *d,  uint32 u, uint32 total ){

      uint32 _process_num = 0;
      if( resp != Nullptr ){

        _process_num = u * total ;

        //read return code

        auto &_header_data_output = resp->m_headerData;

        _header_data_output.write( reinterpret_cast<const assic_char *>(d) , _process_num ) ;
      }

      return _process_num;
    }

    uint32 FtpResponseFactory::processMessageContent( FtpResponseMessage*, void *,  uint32, uint32 ){
      return 0;
    }

  }//namespace Network
}//namespace Magna