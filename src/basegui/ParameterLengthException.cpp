#include "ParameterLengthException.h"

namespace Magna{  
   namespace GUI{
     ParameterLengthException::ParameterLengthException()
       :std::logic_error("Parameter Length Error"){}

     ParameterLengthException::ParameterLengthException( const std::string& what )
       :std::logic_error( what ){}
   }//GUI
}//Magna
