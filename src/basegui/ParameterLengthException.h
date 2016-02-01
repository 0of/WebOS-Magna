#ifndef PARAMETERLENGTHEXCEPTION_H
#define PARAMETERLENGTHEXCEPTION_H

#include <string>
#include <stdexcept>

namespace Magna{  
   namespace GUI{
     class ParameterLengthException : public std::logic_error{
      public:
        ParameterLengthException();
        explicit ParameterLengthException( const std::string& what );
        virtual ~ParameterLengthException(){}
     };
   }//GUI
}//Magna
#endif  /*  PARAMETERLENGTHEXCEPTION_H  */
