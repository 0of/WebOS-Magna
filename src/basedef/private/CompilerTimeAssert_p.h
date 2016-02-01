#ifndef COMPILTERTIMEASSERT_P_H
#define COMPILTERTIMEASSERT_P_H

template<class Error_Message, bool User_Expression>
class CompilerTimeAssert{

};

template<class Error_Message>
class CompilerTimeAssert<Error_Message, true>;

//#ifndef __GUNG__
#ifdef _DEBUG
#define _ComilerTimeAssert(_expression,_error_message)  \
{class Error_##_error_message;\
  sizeof CompilerTimeAssert<Error_##_error_message,!_expression> ;}
#else
#define _ComilerTimeAssert(_expression,_error_message)
#endif  /*_DEBUG  */
//#else
/*  G++  */
//#ifdef _DEBUG
//#endif  /*  _DEBUG  */

//#endif  /*  __GUNG__  */

#endif  /* COMPILTERTIMEASSERT_P_H  */
