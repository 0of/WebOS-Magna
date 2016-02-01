#include "JSONReader.h"

#include "JSONObject.h"
#include "JSONArray.h"

#include <map>
#include <vector>
#include <stack>
#include <limits>
#include <cmath>
#include <algorithm>

namespace Magna{
  namespace Core{

    namespace Private{

      class _JSONReader{
      public:

        enum ReadMessageType{
          ReadMessage_OK,
          ReadMessage_NullData,
          ReadMessage_CorruptedDocument,
          ReadMessage_InternalError,
          ReadMessage_UnknownCharacter,
          ReadMessage_InvalidUTF8Code,
          ReadMessage_InvalidStringFormat,  //    
          ReadMessage_InvalidConstant,
          ReadMessage_InvalidNumberFormat,
          ReadMessage_ExceedMaxPrecision,
          ReadMessage_NumberTooLarge
        };

      public:
        _JSONReader();
        ~_JSONReader();

      public:
        JSONValue reads( const unicode_char * _data, const uint32 _size);

        inline const unicode_char nextChar() {
          unicode_char _ret_char = L'';
          if( m_alreadyReadLength < m_totalLength ){
            _ret_char = *++m_at;
            ++m_alreadyReadLength;
          }
          return _ret_char;
        }

        inline const unicode_char currentChar() {
          unicode_char _ret_char = L'';
          if( m_alreadyReadLength < m_totalLength ){
            _ret_char = *m_at;
          }
          return _ret_char;
        }

        inline void rollbackToPrevious( uint32 rollbackLen ) {
          if( m_alreadyReadLength - rollbackLen > 0 ){
            m_alreadyReadLength -= rollbackLen;
            m_at -= rollbackLen;
          }
        }

        inline bool isEnd() const{
          return m_alreadyReadLength >= m_totalLength;
        }

        inline bool isOK() const{
          return m_readMessageType == ReadMessage_OK;
        }

        void clear();

      public:
        const unicode_char * m_at;
        uint32 m_alreadyReadLength;
        uint32 m_totalLength;

        String m_readMessage;
        ReadMessageType m_readMessageType;
      };

      class _JSONReadBehaviour{
      public:
        virtual ~_JSONReadBehaviour() {}
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) = 0;
      };

      class _JSONReadObjectBehaviour : public _JSONReadBehaviour{
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) ;
      };

      class _JSONReadStringBehaviour : public _JSONReadBehaviour{
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) ;
      };

      //parse number
      class _JSONReadNumberBehaviour : public _JSONReadBehaviour{
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) ;

      private:
        struct _Number{
          _Number() 
            :m_hasDecimalPoint( false )
            ,m_isExpMinus( false )
            ,m_isMinus( false )
            ,m_isScientificNotaion( false )
            ,m_integerString()
            ,m_decimalString()
            ,m_expString(){

          }

          ~_Number(){

          }
        
          bool m_hasDecimalPoint;
          bool m_isExpMinus;
          bool m_isMinus;
          bool m_isScientificNotaion;

          String m_integerString;
          String m_decimalString;
          String m_expString;
        } ;

        bool _doReadNumberProperty( _JSONReader&_reader, _Number &_out );

        double _doReadScientificNotation( _JSONReader&_reader, const _Number& _number_properties );
      };

      //parse array
      class _JSONReadArrayBehaviour : public _JSONReadBehaviour{
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) ;
      };

      //parse constants
      class _JSONReadConstantBehaviour : public _JSONReadBehaviour{
      public:
        typedef JSONValue (*GenerateValueExtAction)();

        _JSONReadConstantBehaviour( const unicode_char * matcher, const uint32 len, GenerateValueExtAction action);
        virtual ~_JSONReadConstantBehaviour();
        virtual JSONValue doRead( _JSONReader& _reader );

      public:
        static JSONValue generateNullValue();
        static JSONValue generateTrueValue();
        static JSONValue generateFalseValue();

      private:
        const unicode_char *m_matcher;
        const uint32 m_length;
        GenerateValueExtAction m_generateAction;
      };

      typedef std::map< unicode_char, _JSONReadBehaviour *> BehaviourMapper;

      class _JSONReadBehaviourMapper : public BehaviourMapper{
      public:
        static _JSONReadBehaviourMapper& getBehaviourMapper();

      private:
        _JSONReadBehaviourMapper();
        ~_JSONReadBehaviourMapper();

      public:
        inline _JSONReadStringBehaviour * getReadStringBehaviour() const{
          return m_readStringBehaviour;
        }

      private:
        _JSONReadStringBehaviour *m_readStringBehaviour;
        _JSONReadObjectBehaviour *m_readObjectBehaviour;
        _JSONReadArrayBehaviour *m_readArrayBehaviour;
        _JSONReadNumberBehaviour *m_readNumberBehaviour;
        _JSONReadConstantBehaviour *m_readNullConstantBehaviour;
        _JSONReadConstantBehaviour *m_readTrueConstantBehaviour;
        _JSONReadConstantBehaviour *m_readFalseConstantBehaviour;
      };


    }

    //_implementations
    namespace Private{
  
      _JSONReader::_JSONReader()
        :m_at( Nullptr )
        ,m_alreadyReadLength( 0 )
        ,m_totalLength( 0 )
        ,m_readMessage()
        ,m_readMessageType( ReadMessage_OK ){

      }

      _JSONReader::~_JSONReader(){

      }

      void _JSONReader::clear(){
        m_at = Nullptr;
        m_alreadyReadLength = 0;
        m_totalLength = 0;
        m_readMessage = String();
        m_readMessageType = ReadMessage_OK;
      }

      JSONValue _JSONReader::reads( const unicode_char * _data, const uint32 _size){
        JSONValue _value;
        if( Nullptr != _data && _size > 0 ){
          //clear up
          m_at = _data;
          m_alreadyReadLength = 0;
          m_totalLength = _size;
          
          //read the first char
          auto &_mapper = _JSONReadBehaviourMapper::getBehaviourMapper();

          auto _first_char = *m_at;
          auto _found_behaviour = _mapper.find( _first_char );
          if( _mapper.end() != _found_behaviour ){
            JSONValue _read_value = _found_behaviour->second->doRead( *this );

            if( _read_value.isValid() ){
              if( ( _read_value.isJSONArray() || _read_value.isJSONObject() ) ){
                _value = _read_value;
                //ok
              } else{
                m_readMessage = L"JSON Document Must Be Started With An Object or An Array";
                m_readMessageType = ReadMessage_CorruptedDocument;
              }
            }
            
          } else{
            m_readMessage = L"Unknown Character :" + _first_char;
            m_readMessageType = ReadMessage_UnknownCharacter;
          }

        } else{
          m_readMessageType = ReadMessage_NullData;
          m_readMessage = L"Read Null Data";
        }
        return _value;
      }

      //when read { a sign of reading an object
      JSONValue _JSONReadObjectBehaviour::doRead( _JSONReader& _reader ) {
        JSONObject _object;

        auto &_mapper = _JSONReadBehaviourMapper::getBehaviourMapper();
        auto &&_read_string_behaviour = _mapper.getReadStringBehaviour();

        if( Nullptr != _read_string_behaviour ){
          
          //read string first
          auto _each_char = _reader.nextChar();
          //the end which means a null object

          while( L'}' != _each_char && !_reader.isEnd() 
            && _JSONReader::ReadMessage_OK == _reader.m_readMessageType ){

            if( L'\"' == _each_char ){  //read string
              auto && _string_JSON_value = _read_string_behaviour->doRead( _reader );
              String _pair_string;

              //ok to read value
              if( _string_JSON_value.isValid() && _string_JSON_value.asString( _pair_string ) ){
                //pass over ':'
                _each_char = _reader.nextChar();
                if( _each_char == L':' ){
                  //read next value
                  auto _found = _mapper.find( _reader.nextChar() );
                  if( _mapper.end() != _found && Nullptr != _found->second){
                    auto&& _pair_value = _found->second->doRead( _reader );
                    if( _pair_value.isValid() ){
                      //make pair
                      _object.emplace( _pair_string, _pair_value);
                      _each_char = _reader.nextChar();
                    } else{
                      break;
                      //stop and dispatch error 
                    }
                  } else{
                    _reader.m_readMessage = L"Unknown Character :" + _each_char;
                    _reader.m_readMessageType = _JSONReader::ReadMessage_UnknownCharacter;
                  }
                } else{
                  _reader.m_readMessage = L"Unknown Character :" + _each_char;
                  _reader.m_readMessageType = _JSONReader::ReadMessage_UnknownCharacter;
                }//read value
                
              }  //read string ok

            } else if( L',' == _each_char || L' ' == _each_char 
              || L'\t' == _each_char || L'\n' == _each_char ){
              _each_char = _reader.nextChar();
            } else{
              _reader.m_readMessage = L"Unknown Character :" + _each_char;
              _reader.m_readMessageType = _JSONReader::ReadMessage_UnknownCharacter;
            }
          }
        } else{
          _reader.m_readMessage = L"Internal Error";
          _reader.m_readMessageType = _JSONReader::ReadMessage_InternalError;
        }

        JSONValue _value;
        if( _JSONReader::ReadMessage_OK == _reader.m_readMessageType ){
          _value = JSONValue( _object );
        } else{
          //process the error or exit
        }

        return _value;
      }

      JSONValue _JSONReadStringBehaviour::doRead( _JSONReader& _reader ) {
        String _string;
        
        bool _reached_string_end = false;
        bool _has_escape = false;

        unicode_char _each_char = L'';
        while( !_reader.isEnd() && !_reached_string_end 
          && _reader.m_readMessageType == _JSONReader::ReadMessage_OK ){
          _each_char = _reader.nextChar();

          if( _has_escape ){
            switch( _each_char ){
            case L'"': _string.push_back( L'"' ); break;
            case L'\\': _string.push_back( L'\\' ); break;
            case L'b': _string.push_back( L'\b' ); break;
            case L'f': _string.push_back( L'\f' ); break;
            case L'n': _string.push_back( L'\n' ); break;
            case L'r': _string.push_back( L'\r' ); break;
            case L't': _string.push_back( L'\t' ); break;
            case L'u': {
              //unicode
              //e.g. \u057a must be 4 hex digits 
              // ! it'll modify the value of the reader object
              if( _reader.m_totalLength - _reader.m_alreadyReadLength > 4 ){          
                unicode_char parsedChar = L'\0';
                for( auto _i = 0; 4 != _i;  ++_i ){
                  _each_char = *++_reader.m_at;
                  if ( _each_char >= L'0'  &&  _each_char <= L'9' )
                    parsedChar |= (_each_char - '0');
                  else if ( _each_char >= L'a'  &&  _each_char <= L'f' )
                    parsedChar |= (_each_char - L'a' + 10);
                  else if ( _each_char >= L'A'  &&  _each_char <= L'F' )
                    parsedChar |= (_each_char - L'A' + 10);
                  else{
                    _reader.m_readMessage = L"Invalid UTF-8 Code:" + _each_char;
                    _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidUTF8Code;
                    break;
                  }

                  parsedChar <<= 4;
                }
                _string.push_back(parsedChar);
              } else{
                _reader.m_readMessage = L"The Length of UTF-8 Code Must be 4";
                _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidStringFormat;
              }
            } break;
            default:
              _reader.m_readMessage = L"Invalid Escaped Character:\\" + _each_char;
              _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidStringFormat;
              break;
            }
          } else{
            if( L'"' == _each_char ) {
              _reached_string_end = !false;
            } else if( L'\\' == _each_char ){
              _has_escape = !false;
            } else{
              _string.push_back( _each_char );
            }
          }
        }

        JSONValue _value;
        if( _JSONReader::ReadMessage_OK == _reader.m_readMessageType ){
          _value = JSONValue( _string );
        } else{
          //process the error or exit
        }

        return _value;
      }

      bool _JSONReadNumberBehaviour::_doReadNumberProperty( _JSONReader&_reader, _Number &_number ){
        unicode_char _each_char = _reader.currentChar();
        uint32 _read_len = 0;

        bool _reached_the_end = false;
        while( !_reader.isEnd() && _reader.m_readMessageType == _JSONReader::ReadMessage_OK && !_reached_the_end ){
          if( _each_char >= L'0' && _each_char <= L'9' ){
            if( _number.m_isScientificNotaion ){
              _number.m_expString.push_back( _each_char );
            } else if( _number.m_hasDecimalPoint ){
              _number.m_decimalString.push_back( _each_char );  
            } else{
              _number.m_integerString.push_back( _each_char );
            }
            //zero parsing
          } else{  
            switch( _each_char ){
              case L'.':
                if( !_number.m_hasDecimalPoint ){
                  //not the first one
                  if( !_number.m_integerString.empty() ){
                    _number.m_hasDecimalPoint = !false;
                  } else{
                    _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidNumberFormat;
                    _reader.m_readMessage = L"Decimal point can NOT be the first symbol.";
                  }
                } else{
                  _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidNumberFormat;
                  _reader.m_readMessage = L"Contains more than one '.' decimal point.";
                } break;

              case L'e':
              case L'E':
                if( !_number.m_integerString.empty() && !_number.m_isScientificNotaion ){
                  _number.m_isScientificNotaion = !false;
                } else{
                  _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidNumberFormat;
                  _reader.m_readMessage = L"Contains more than one 'E' symbol.";
                } break;

              case L'+':
                if( !_number.m_isScientificNotaion || !_number.m_expString.empty() ){
                  _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidNumberFormat;
                  _reader.m_readMessage = L"Invalid '+' symbol.";
                } break;

              case L'-':
                if( _number.m_integerString.empty() ){
                  _number.m_isMinus = !false;
                } else if( _number.m_expString.empty() ){
                  _number.m_isExpMinus = !false;
                } else{
                  _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidNumberFormat;
                  _reader.m_readMessage = L"Invalid '-' symbol.";
                } break;
              
              default:
                _reached_the_end = !false;
                break;
            }
          }
          //read next
          if( !_reached_the_end ){
            _each_char = _reader.nextChar();
            ++_read_len;
          }          
        }
        //roll back
        _reader.rollbackToPrevious( 1 );
        return _reader.m_readMessageType == _JSONReader::ReadMessage_OK;
      }

      //
      template<uint8>
      struct _NumberTrait;

      template<>
      struct _NumberTrait<std::numeric_limits<sint32>::digits>{
        static const String sharedMaxBoundary;
      };

      template<>
      struct _NumberTrait<std::numeric_limits<uint32>::digits>{
        static const String sharedMaxBoundary;
      };

      template<>
      struct _NumberTrait<std::numeric_limits<double>::digits>{
        static const String sharedMaxBoundary;
      };

      //positive max
      template<>
      struct _NumberTrait<std::numeric_limits<double>::digits + 1>{
        static const String sharedMaxBoundary;
      };

      //positive min
      template<>
      struct _NumberTrait<std::numeric_limits<double>::digits + 2>{
        static const String sharedMaxBoundary;
      };

      const String _NumberTrait<31>::sharedMaxBoundary = String( L"2147483647" );
      const String _NumberTrait<std::numeric_limits<uint32>::digits>::sharedMaxBoundary = String( L"2147483647" );
      const String _NumberTrait<std::numeric_limits<double>::digits>::sharedMaxBoundary = String( L"4503599627370495" );

      const String _NumberTrait<std::numeric_limits<double>::digits + 1>::sharedMaxBoundary = String( L"1797693134862315" );
      const String _NumberTrait<std::numeric_limits<double>::digits + 2>::sharedMaxBoundary = String( L"4940656458412465" );
      //
      template<typename _Number_Trait>
      class _NumberBoundaryChecker{
      public:
        static bool _doCheck( const String& numberString ){
          bool _is_within_boundary = !false;
          if( numberString.size() == _Number_Trait::sharedMaxBoundary.size() ){
            for( auto _index = 0; numberString.size() != _index; ++_index ){
              if( numberString[_index] > _Number_Trait::sharedMaxBoundary[_index] ){
                _is_within_boundary = false;
              } 
              break;
            }
          } else if ( numberString.size() > _Number_Trait::sharedMaxBoundary.size() ){
            _is_within_boundary = false;
          }
          return _is_within_boundary;
        }
      };

      template<typename _Result_Type, uint8 _Bytes_Num>
      class _NumberGenerator{
      public:
        static _Result_Type _doGenerate( _JSONReader& _reader, const String& _number_string ){      
          //clear up 
          _Result_Type _out_result = 0;

          if( _NumberBoundaryChecker<_NumberTrait<_Bytes_Num> >::_doCheck( _number_string ) ){
            
            for( auto _each_num_iter = _number_string.begin()
              ; _number_string.end() != _each_num_iter
              ; ++_each_num_iter){
                _out_result = _out_result * 10 + (*_each_num_iter - L'0');
            }
          } else{
            _reader.m_readMessageType = _JSONReader::ReadMessage_NumberTooLarge;
            _reader.m_readMessage = L"Number Is Too Large.";
          }
          return _out_result;
        }
      };

      template<uint8 _Bytes_Num>
      class _NumberGenerator<double, _Bytes_Num>{
      public:
        static double _doGenerate( _JSONReader& _reader, const String& _interger_string, const String& _decimal_string ){      
          String _double_string = _interger_string + _decimal_string;
          uint64 _uint64_value = 0;
          double _out_result = 0.0;

          if( _NumberBoundaryChecker<_NumberTrait<_Bytes_Num> >::_doCheck( _double_string ) ){

            for( auto _each_num_iter = _double_string.begin()
              ; _double_string.end() != _each_num_iter
              ; ++_each_num_iter){
              _uint64_value = _uint64_value * 10 + (*_each_num_iter - L'0');
            }

            _out_result = static_cast<double>( _uint64_value ) 
              / std::pow(10.0, static_cast<double>( _decimal_string.size() ) ); 

          } else{
            _reader.m_readMessageType = _JSONReader::ReadMessage_ExceedMaxPrecision;
            _reader.m_readMessage = L"Exceeds Double Precision.";
          }
          return _out_result;
        }
      };

      
      double _JSONReadNumberBehaviour::_doReadScientificNotation( _JSONReader&_reader, const _Number& _number_properties ){
        double _double_value = 0.0;
        uint16 _exp_integer = 0;

        typedef _NumberGenerator<decltype(_double_value), std::numeric_limits<decltype(_double_value)>::digits + 1> _DoubleDigitSciMax_Generator;
        typedef _NumberGenerator<decltype(_double_value), std::numeric_limits<decltype(_double_value)>::digits + 2> _DoubleDigitSciMin_Generator;

        //parse exp 
        const auto& _exp_string = _number_properties.m_expString;
        if( _number_properties.m_expString.size() <= 3 ){

          for( auto _each_num_iter = _exp_string.begin()
            ; _exp_string.end() != _each_num_iter
            ; ++_each_num_iter){
            _exp_integer = _exp_integer * 10 + (*_each_num_iter - L'0'); 
          }

          auto _integer_size = _number_properties.m_integerString.size() == 1?
            0 : _number_properties.m_integerString.size();
          if( _number_properties.m_isExpMinus ){
            //if the exp is minus, exp can reach at 324 digits 
            if( _integer_size - _exp_integer <= 324 ){//ok
              _double_value = _number_properties.m_isMinus ? 
                -1.0 * _DoubleDigitSciMin_Generator::_doGenerate( _reader, _number_properties.m_integerString, _number_properties.m_decimalString )
                : _DoubleDigitSciMax_Generator::_doGenerate( _reader, _number_properties.m_integerString, _number_properties.m_decimalString );

              if( _reader.m_readMessageType == _JSONReader::ReadMessage_OK ){
                _double_value /= std::pow( 10.0, static_cast<double>(_exp_integer) );
              }

            } else{
              // too small
              _reader.m_readMessageType = _JSONReader::ReadMessage_ExceedMaxPrecision;
              _reader.m_readMessage = L"Exponent Is Too Small Which Results Loss Data.";
            }
          } else{  //exp is positive
            if( _exp_integer +  _integer_size <= 308 ){
              _double_value = _number_properties.m_isMinus ? 
                -1.0 * _DoubleDigitSciMax_Generator::_doGenerate( _reader, _number_properties.m_integerString, _number_properties.m_decimalString )
                : _DoubleDigitSciMin_Generator::_doGenerate( _reader, _number_properties.m_integerString, _number_properties.m_decimalString );

              if( _reader.m_readMessageType == _JSONReader::ReadMessage_OK ){
                _double_value *= std::pow( 10.0, static_cast<double>(_exp_integer) );
              } 

            } else{
              _reader.m_readMessageType = _JSONReader::ReadMessage_NumberTooLarge;
              _reader.m_readMessage = L"Exponent Is Too Large Which Data Can NOT Be Represented.";
            }
          }
        } else{
          if( _number_properties.m_isExpMinus ){
            _reader.m_readMessageType = _JSONReader::ReadMessage_ExceedMaxPrecision;
            _reader.m_readMessage = L"Exponent Is Too Small Which Results Loss Data.";
          } else{
            _reader.m_readMessageType = _JSONReader::ReadMessage_NumberTooLarge;
            _reader.m_readMessage = L"Exponent Is Too Large Which Data Can NOT Be Represented.";
          }
        }
        return _double_value;
      }

      JSONValue _JSONReadNumberBehaviour::doRead( _JSONReader& _reader ) {      
        JSONValue _value;
        
        _Number _number_properties;
        if( _doReadNumberProperty( _reader, _number_properties ) ){
          //trim integer zero
          auto _trim_index = 0;
          if( _number_properties.m_integerString.size() > 1 ){
            for( ; _number_properties.m_integerString.size() != _trim_index; ++_trim_index ){
              if( _number_properties.m_integerString.at( _trim_index ) != L'0' ){
                break;
              }
            }
          }
          _number_properties.m_integerString = _number_properties.m_integerString.substr( _trim_index );

          //scientific notation
          if( _number_properties.m_isScientificNotaion ){  // a scientific double value
            auto _double_value = _doReadScientificNotation( _reader, _number_properties );
            if( _reader.isOK() ){
              _value = JSONValue( _double_value );
            }
          } else if( _number_properties.m_hasDecimalPoint ){  // a fixed double value
            typedef _NumberGenerator<double, std::numeric_limits<double>::digits> _DoubleDigit53_Generator;

            auto _double_value = _DoubleDigit53_Generator::_doGenerate( _reader, _number_properties.m_integerString, _number_properties.m_decimalString );
            if( _reader.isOK() ){
              if( _number_properties.m_isMinus ){
                _double_value *= -1.0;
              }
              _value = JSONValue( _double_value );
            }
          } else{  // a integer or unsigned integer
            if( _number_properties.m_isMinus ){  // a integer
              typedef _NumberGenerator<sint32, std::numeric_limits<sint32>::digits> _Sint32_Generator;

              auto _integer_value = _Sint32_Generator::_doGenerate( _reader, _number_properties.m_integerString );
              if( _reader.isOK() ){
                if( _number_properties.m_isMinus ){
                  _integer_value *= -1;
                }
                _value = JSONValue( _integer_value );
              }
            } else{  // a unsigned integer
              typedef _NumberGenerator<uint32, std::numeric_limits<uint32>::digits> _Uint32_Generator;
              auto _integer_value = _Uint32_Generator::_doGenerate( _reader, _number_properties.m_integerString );
              if( _reader.isOK() ){
                if( _number_properties.m_isMinus ){
                  _integer_value *= -1;
                }
                _value = JSONValue( _integer_value );
              }
            }
          }
        }
        return _value;
      }

      JSONValue _JSONReadArrayBehaviour::doRead( _JSONReader& _reader ) {
        JSONArray _array;
        //JSONValue _value;
        auto &_mapper = _JSONReadBehaviourMapper::getBehaviourMapper();

        auto _each_char = _reader.nextChar();

        while( L']' != _each_char && !_reader.isEnd() ){
          //separator
          if( L',' == _each_char || L'\t' == _each_char
            || L' ' == _each_char || L'\n' == _each_char ){
            _each_char = _reader.nextChar();
          } else{
            auto _found = _mapper.find( _each_char );
            if( _mapper.end() != _found && Nullptr != _found->second){
              auto&& _pair_value = _found->second->doRead( _reader );
              if( _pair_value.isValid() ){
                _array.appendValue( _pair_value );
                _each_char = _reader.nextChar();
              } else{
                break;
                //stop and dispatch error
              }
            } else{
              _reader.m_readMessage = L"Unknown Character :" + _each_char;
              _reader.m_readMessageType = _JSONReader::ReadMessage_UnknownCharacter;
            }
          }
        }
        JSONValue _value;
        if( _JSONReader::ReadMessage_OK == _reader.m_readMessageType ){
          _value = JSONValue( _array );
        } else{
          //process the error or exit
        }

        return _value;
      }

      _JSONReadConstantBehaviour::_JSONReadConstantBehaviour( const unicode_char* matcher, const uint32 len, GenerateValueExtAction action)
        :m_matcher( matcher )
        ,m_length( len )
        ,m_generateAction( action ){

      }

      _JSONReadConstantBehaviour::~_JSONReadConstantBehaviour(){

      }

      JSONValue _JSONReadConstantBehaviour::generateNullValue(){
        return JSONValue( Nullptr );
      }
      JSONValue _JSONReadConstantBehaviour::generateTrueValue(){
        return JSONValue( !false );
      }
      JSONValue _JSONReadConstantBehaviour::generateFalseValue(){
        return JSONValue( false );
      }

      JSONValue _JSONReadConstantBehaviour::doRead( _JSONReader& _reader ){
        JSONValue _value;
        auto &&_can_read_length = (_reader.m_totalLength - _reader.m_alreadyReadLength);
      
        if( _can_read_length > m_length ){
          String _constant_string;

          for( auto _counter = 0; m_length != _counter; ++_counter ){
            _constant_string.push_back( _reader.nextChar() );
          }
          //whether matches
          std::transform( _constant_string.begin(), _constant_string.end(), _constant_string.begin(), ::tolower );      
          
          auto _found_index = _constant_string.find( m_matcher );
          if( String::npos != _found_index ){
            if( Nullptr != m_generateAction ){
              _value = (*m_generateAction)();
            } else{
              _reader.m_readMessage = L"Generate JSON Value Error";
              _reader.m_readMessageType = _JSONReader::ReadMessage_InternalError;
            }        
          } else{
            _reader.m_readMessage = L"Invalid Constant";
            _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidConstant;
          }
        } else{
          _reader.m_readMessage = L"Invalid Constant 'null'";
          _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidConstant;
        }
        return _value;
      }

      _JSONReadBehaviourMapper& _JSONReadBehaviourMapper::getBehaviourMapper(){
        static _JSONReadBehaviourMapper _mapper;
        return _mapper;
      }

      _JSONReadBehaviourMapper::_JSONReadBehaviourMapper()
        :BehaviourMapper()
        ,m_readStringBehaviour( new _JSONReadStringBehaviour )
        ,m_readObjectBehaviour( new _JSONReadObjectBehaviour )
        ,m_readArrayBehaviour( new _JSONReadArrayBehaviour )
        ,m_readNumberBehaviour( new _JSONReadNumberBehaviour )
        ,m_readNullConstantBehaviour( new _JSONReadConstantBehaviour( L"ull", 3, &_JSONReadConstantBehaviour::generateNullValue ) )
        ,m_readTrueConstantBehaviour( new _JSONReadConstantBehaviour( L"rue", 3, &_JSONReadConstantBehaviour::generateTrueValue ) )
        ,m_readFalseConstantBehaviour( new _JSONReadConstantBehaviour( L"alse", 4, &_JSONReadConstantBehaviour::generateFalseValue ) ) {

        //mappers init
        emplace( std::make_pair( L'{', m_readObjectBehaviour ) );
        emplace( std::make_pair( L'[', m_readArrayBehaviour ) );
        emplace( std::make_pair( L'\"', m_readStringBehaviour ) );

        emplace( std::make_pair( L'-', m_readNumberBehaviour ) );
        unicode_char _start_num_in_char = L'0';
        for( auto _counter = 0; 10 != _counter; ++_counter, ++_start_num_in_char ){
          emplace( std::make_pair( _start_num_in_char , m_readNumberBehaviour ) );
        }
      
        emplace( std::make_pair( L'n', m_readNullConstantBehaviour ) );
        emplace( std::make_pair( L'N', m_readNullConstantBehaviour ) );
        emplace( std::make_pair( L't', m_readTrueConstantBehaviour ) );
        emplace( std::make_pair( L'T', m_readTrueConstantBehaviour ) );
        emplace( std::make_pair( L'f', m_readFalseConstantBehaviour ) );
        emplace( std::make_pair( L'F', m_readFalseConstantBehaviour ) );
      }

      _JSONReadBehaviourMapper::~_JSONReadBehaviourMapper(){
        clear();
        delete m_readStringBehaviour;
        delete m_readObjectBehaviour;
        delete m_readArrayBehaviour;
        delete m_readNumberBehaviour;
        delete m_readNullConstantBehaviour;
        delete m_readTrueConstantBehaviour;
        delete m_readFalseConstantBehaviour;
      }

    }


    JSONReader::JSONReader()
      :m_rootValue()
      ,m_errorMessage(){

    }

    JSONReader::~JSONReader(){

    }

    JSONReader::JSONReader( const String& filePath )
      :m_rootValue()
      ,m_errorMessage(){

      readFromFile( filePath );
    }

    JSONReader::JSONReader( std::wistream& stream )
      :m_rootValue()
      ,m_errorMessage(){
      
      readFromStream(stream);
    }

    JSONReader::JSONReader( String::const_iterator start, String::const_iterator end )
      :m_rootValue()
      ,m_errorMessage(){

      readFromString(start, end);
    }

    JSONReader::JSONReader( const unicode_char* data, const uint32 size)
      :m_rootValue()
      ,m_errorMessage(){

      readFromString(data, size);
    }

    bool JSONReader::readFromFile( const String& filePath ){
      bool _is_ok = false;
      std::wifstream _stream;
      _stream.imbue( std::locale( "" ) );
      _stream.open( filePath, std::fstream::in );
      if(  _stream.is_open() ){
        _is_ok = readFromStream( _stream );
      } else{
        m_errorMessage = L"JSON File Not Open!";
      }
      return _is_ok;
    }

    bool JSONReader::readFromStream( std::wistream& stream ){
      bool _is_ok = false;

      std::wstringbuf _buffer;
      stream.get( _buffer );

      if( stream.good() && 0 != stream.gcount() ){
        String _json_strings = _buffer.str();

        //read
        Private::_JSONReader _reader;
        m_rootValue = _reader.reads( _json_strings.c_str(), _json_strings.size() );
        if( m_rootValue.isValid() ){
          _is_ok = !false;         
        } else{
          m_errorMessage = _reader.m_readMessage;
        }

      } else{
        m_errorMessage = L"File Buffer Corrupted!";
      }  
      return _is_ok;
    }

    bool JSONReader::readFromString( String::const_iterator start, String::const_iterator end ){
      bool _is_ok = false;
      if( start < end ){
        const uint32 _range_length = (end - start);
        Private::_JSONReader _reader;
        m_rootValue = _reader.reads( start.operator->(), _range_length );
        if( m_rootValue.isValid() ){
          _is_ok = !false;
        } else{
          m_errorMessage = _reader.m_readMessage;
        }
      } else{
        m_errorMessage = L"Given String Buffer Error!";
      }
      return _is_ok;
    }

    bool JSONReader::readFromString( const unicode_char* data, const uint32 size ){
      bool _is_ok = false;
      Private::_JSONReader _reader;
      m_rootValue = _reader.reads( data, size );
      if( m_rootValue.isValid() ){
        _is_ok = !false;
      } else{
        m_errorMessage = _reader.m_readMessage;
      }
      return _is_ok;
    }
  }
}//namespace Magna