#include "JSONReader.h"

#include "JSONObject.h"
#include "JSONArray.h"

#include <map>
#include <vector>
#include <stack>
#include <limits>
#include <cmath>

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
        };

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
        inline bool isEnd() const{
          return m_alreadyReadLength >= m_totalLength;
        }
      public:
        const unicode_char * m_at;
        uint32 m_alreadyReadLength;
        uint32 m_totalLength;

        std::stack<JSONValue> m_valueStack;

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
      };

      //parse array
      class _JSONReadArrayBehaviour : public _JSONReadBehaviour{
      public:
        virtual JSONValue doRead( _JSONReader& _reader ) ;
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
      };
    }

    //_implementations
    namespace Private{

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
            if( _read_value.isJSONArray() || _read_value.isJSONObject() ){
              _value = _read_value;
              //ok
            } else{
              m_readMessage = L"JSON Document Must Be Started With An Object or An Array";
              m_readMessageType = ReadMessage_CorruptedDocument;
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

          while( L'}' != _each_char && L'\0' != _each_char ){

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
                      _object[ _pair_string ] = _pair_value;
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

            } else if( L',' == _each_char ){
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
        while( !_reader.isEnd() && !_reached_string_end ){
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
                  }

                  parsedChar <<= 4;
                }
                _string.push_back(parsedChar);
              } else{
                _reader.m_readMessage = L"The Length of UTF-8 Code Must be 4";
                _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidStringFormat;
              }
                   }
            default:
              _reader.m_readMessage = L"Invalid Escaped Character:\\" + _each_char;
              _reader.m_readMessageType = _JSONReader::ReadMessage_InvalidStringFormat;
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

      JSONValue _JSONReadNumberBehaviour::doRead( _JSONReader& _reader ) {
        //can be a float or an integer
        bool _has_decimal_point = false;
        bool _is_minus = false;
        bool _has_factor_sign = false;
        bool _is_factor_minus = false;
        bool _is_scientific_notation = false;
        bool _is_valid = !false;

        sint32 _integer_value = 0;

        uint32 _after_decimal_point_count = 0; 
        double _decimal_value = 0.0;
        uint32 _factor_value = 0;

        sint64 _calculated_value = 0;

        uint32 _read_length = 0;


        unicode_char _each_char = (*_reader.m_at);
        do{
          if( _read_length == 0 ){

            if( _each_char == L'-' ){
              _is_minus = !false;
            } else if(_each_char > L'0' && _each_char <= L'9'){
              _integer_value = _each_char - L'0';
            } else{
              _is_valid = false;
            }

          } else{  //not the first symbol
            if( _each_char > L'0' && _each_char <= L'9' ){

              auto _numeric_value = _each_char - L'0';
              if(  _is_scientific_notation ){  //decode integer
                _calculated_value = _factor_value * 10 + _numeric_value;
                if( _calculated_value > std::numeric_limits<sint32>::max() ){
                  //error
                } else{
                  _factor_value = static_cast<sint32>(_calculated_value);
                }
              } else if( _has_decimal_point ){  //decode double
                _after_decimal_point_count ++;
                auto _after_decimal_point_value = static_cast<double>(_numeric_value) / std::pow(10.0, static_cast<double>(_after_decimal_point_count));

                _decimal_value += _after_decimal_point_value;    
    
              } else {
                _calculated_value = _integer_value * 10 + _numeric_value;
                if( _calculated_value > std::numeric_limits<sint32>::max() ){
                  //error
                } else{
                  _integer_value = static_cast<sint32>(_calculated_value);
                }
              }
            } else {
              switch( _each_char ){
              case L'.':
                if( !_has_decimal_point ){
                  _has_decimal_point = !false;
                } else{
                  _is_valid = false;
                  //error
                } break;

              case L'e':
              case L'E':
                if( !_is_scientific_notation ){
                  _is_scientific_notation = !false;
                } else{
                  _is_valid = false;
                  //error
                }break;

              case L'+':
                if( _is_scientific_notation && !_has_factor_sign){
                  _has_factor_sign = !false;
                }else{
                  _is_valid = false;
                  //error
                }break;

              case L'-':
                if( _is_scientific_notation && !_has_factor_sign ){
                  _has_factor_sign = !false;
                  _is_factor_minus = !false;
                }else{
                  _is_valid = false;
                  //error
                }break;

              default:
                _is_valid = false;
                break;
              }
            }
          }

          ++_read_length;            
          _each_char = _reader.nextChar();

        }while( !_reader.isEnd() && _is_valid);

        JSONValue _value;
        //parse to real or integer value
        if( _is_valid ){

          //double
          if( _has_decimal_point ){
            auto &&_double_value = _is_minus ? -(static_cast<double>(_integer_value) + _decimal_value)
              : (static_cast<double>(_integer_value) + _decimal_value);
            _value = JSONValue( _double_value );
          } else if( _is_scientific_notation ){



          } else{  //normal integer
            _value = JSONValue( _is_minus ? -_integer_value : _integer_value );
          }

          if( !_value.isNull() ){

          }
        }
        return _value;
      }

      JSONValue _JSONReadArrayBehaviour::doRead( _JSONReader& _reader ) {
        JSONArray _array;
        //JSONValue _value;
        auto &_mapper = _JSONReadBehaviourMapper::getBehaviourMapper();

        auto _each_char = _reader.nextChar();

        while( L']' != _each_char && L'\0' != _each_char ){
          //separator
          if( L',' == _each_char ){
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

      _JSONReadBehaviourMapper& _JSONReadBehaviourMapper::getBehaviourMapper(){
        static _JSONReadBehaviourMapper _mapper;
        return _mapper;
      }

      _JSONReadBehaviourMapper::_JSONReadBehaviourMapper()
        :BehaviourMapper()
        ,m_readStringBehaviour( new _JSONReadStringBehaviour )
        ,m_readObjectBehaviour( new _JSONReadObjectBehaviour )
        ,m_readArrayBehaviour( new _JSONReadArrayBehaviour )
        ,m_readNumberBehaviour( new _JSONReadNumberBehaviour ){

        //mappers init
        emplace( std::make_pair( L'{', m_readObjectBehaviour ) );
        emplace( std::make_pair( L'[', m_readArrayBehaviour ) );
        emplace( std::make_pair( L'\"', m_readStringBehaviour ) );

        emplace( std::make_pair( L'-', m_readNumberBehaviour ) );
        unicode_char _start_num_in_char = L'0';
        for( auto _counter = 0; 10 != _counter; ++_counter, ++_start_num_in_char ){
          emplace( std::make_pair( _start_num_in_char , m_readNumberBehaviour ) );
        }
      
      }

      _JSONReadBehaviourMapper::~_JSONReadBehaviourMapper(){
        clear();
        delete m_readStringBehaviour;
        delete m_readObjectBehaviour;
        delete m_readArrayBehaviour;
        delete m_readNumberBehaviour;
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

    JSONReader::JSONReader( std::wifstream& stream )
      :m_rootValue()
      ,m_errorMessage(){
      
      readFromFileStream(stream);
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
      std::wifstream _stream;
      _stream.open( filePath, std::fstream::in );
      return readFromFileStream(_stream);
    }

    bool JSONReader::readFromFileStream( std::wifstream& stream ){
      bool _is_ok = false;
      if( stream.is_open() ){
        std::wstringbuf _buffer;
        stream.get( _buffer );

        if( stream.good() && 0 != stream.gcount() ){
          String _json_strings = _buffer.str();

          //read
          Private::_JSONReader _reader;
          auto && _json_value = _reader.reads( _json_strings.c_str(), _json_strings.size() );
          if( _json_value.isValid() ){
            _is_ok = !false;         
          } else{
            m_errorMessage = _reader.m_readMessage;
          }

        } else{
          m_errorMessage = L"File Buffer Corrupted!";
        }
      } else{
        m_errorMessage = L"JSON File Not Open!";
      }
      return _is_ok;
    }

    bool JSONReader::readFromString( String::const_iterator start, String::const_iterator end ){
      bool _is_ok = false;
      if( start < end ){
        const uint32 _range_length = (end - start);
        Private::_JSONReader _reader;
        auto && _json_value = _reader.reads( start.operator->(), _range_length );
        if( _json_value.isValid() ){
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