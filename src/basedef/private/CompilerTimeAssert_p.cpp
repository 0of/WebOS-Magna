#include "CompilerTimeAssert_p.h"

template<class Error_Message>
class CompilerTimeAssert<Error_Message, false>{
private:
  Error_Message Error_Message_Has_Been_Listed;
};




