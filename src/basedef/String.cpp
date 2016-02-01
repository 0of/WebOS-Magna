#include "String.h"

#include <locale>
#include <exception>
#include <stdexcept>
#ifdef _MSC_VER
#include <codecvt>
#elif defined __GNUC__
#include <ext/codecvt_specializations.h>
#else
#error UNKNOW_COMPILE_ENV
#endif

namespace Magna{
  namespace Core{

        String String::EmptyString = String();

    std::vector<String> String::split( const String& delimit ){
      std::vector<String> _ret_strings;
      size_t _last = 0;
      size_t _index= find_first_of( delimit, _last);
      while ( _index != std::string::npos ){
        _ret_strings.push_back( substr( _last, _index-_last ));
        _last = (++_index);
        _index= find_first_of( delimit, _last );
      }

      if (_index > _last ){
        _ret_strings.push_back( substr( _last, _index- _last ) );
      }
      return _ret_strings;
    }

    uint32 String::replaceAll( const String&from, const String&to ){
      uint32 _convert_num = 0;

      const auto& _from_size = from.size();
      const auto& _to_size = to.size();

      for(auto _each_found_pos = find(from, 0)
        ;  _each_found_pos != npos
        ; [&](){
        replace(_each_found_pos, _to_size, to );

        ++_convert_num;
        _each_found_pos = find( from,_each_found_pos + _from_size) ;
      } );

      return _convert_num;
    }

    std::string String::toString() const{
      std::string _ret_string;

      if( !empty() ){
        uint32 _convert_num = 0;

        const uint32 _str_size = (size() + 1) * ( sizeof( unicode_char ) / sizeof( assic_char ) );

        assic_char *_buffer = new assic_char[ _str_size ];

        setlocale(LC_CTYPE, "");

        _convert_num = wcstombs(_buffer, c_str(), (_str_size - ( sizeof( unicode_char ) / sizeof( assic_char )) )  );

        _ret_string = std::string( _buffer, _convert_num );

        delete [] _buffer;
      }

      return _ret_string;
    }

    String String::fromString( const std::string& str ){
      String _ret_string;
            if( !str.empty() ){
                 uint32 _convert_num = 0;
                 uint32 _mb_size = 0;
                //get the mulit-bytes size
                mbstate_t _mbstate;

                //init state
                ::mbrlen (Nullptr, 0, &_mbstate);

                _mb_size = ::mbrlen ( str.c_str(), str.size(), &_mbstate );
        unicode_char *_buffer = new unicode_char[ (_mb_size + 1) ];

        setlocale(LC_CTYPE, "");

                //convert
                _convert_num =  ::mbstowcs (_buffer, str.c_str(), _mb_size);

        _ret_string = String( _buffer, _convert_num );

        delete [] _buffer;
            }
      return _ret_string;
    }

        String String::fromUTF8( const std::string& utf8str){
            String _ret_string;
            if( !utf8str.empty() ){
#ifdef _MSC_VER
                std::wstring_convert<std::codecvt_utf8<unicode_char> > _utf8_convertor;

                _ret_string = String( _utf8_convertor.from_bytes(utf8str) );
#elif defined __GNUC__
                //at least the same capacity
                _ret_string.reserve( utf8str.size() );
                unicode_char _each_wchar = L' ';
                uint32  _each_wchar_bytes = 0;

                const auto *_utf8_src = utf8str.c_str();

                try{
                    for( auto _i = 0; utf8str.size() != _i ; ++_i ){
                        uint8 _each_plain_char_va = static_cast< decltype(_each_plain_char_va) >( *(_utf8_src + _i) );
                        if( _each_plain_char_va <= 0x7F ){
                            if( 0 == _each_wchar_bytes ){
                                _each_wchar = static_cast<decltype(_each_wchar)>( _each_plain_char_va );
                                _ret_string.push_back( _each_wchar );
                            } else{
                                throw std::runtime_error( "Conversion Occurs Error" );
                            }
                        } else if( _each_plain_char_va <= 0xBF ){
                            if( 0 != _each_wchar_bytes ){
                                _each_wchar = ((_each_wchar << 6)|(_each_plain_char_va & 0x3f));
                                if( 0 == --_each_wchar_bytes ){
                                    _ret_string.push_back( _each_wchar );
                                }
                            }  else{
                                throw std::runtime_error( "Conversion Occurs Error" );
                            }
                        } else if (_each_plain_char_va <= 0XDF){
                            _each_wchar_bytes = 1;
                            _each_wchar = _each_plain_char_va &0X1F;
                        } else if( _each_plain_char_va <=  0xEF) {
                            _each_wchar_bytes = 2;
                            _each_wchar = _each_plain_char_va &0X1F;
                        } else if (_each_plain_char_va <= 0xF7){
                            _each_wchar_bytes = 3;
                            _each_wchar = _each_plain_char_va & 0x07;
                        } else{
                            throw std::runtime_error( "Conversion Occurs Error" );
                        }
                    }
                    //append end sign
                    //_ret_string.push_back( L'\0' );
                } catch( const std::exception& _ex ){
                    printf( "Exception Caught: %s" , _ex.what() );
                   // _ret_string.push_back( L'\0' );
                }
#else
#error UNKNOW_COMPILE_ENV
#endif
            }
            return _ret_string;
        }

        std::string String::toUTF8() const{
            std::string _ret_string;
            if( !empty() ){
#ifdef _MSC_VER
                std::wstring_convert<std::codecvt_utf8<unicode_char> > _utf8_convertor;

                _ret_string = _utf8_convertor.to_bytes( *this );
#elif defined __GNUC__

                _ret_string.reserve( size() * ( sizeof(unicode_char) / sizeof( assic_char ) ));
                const auto *_src_wchar = c_str();

                try{
                    for (auto _i = 0; size() != _i ; ++_i ){
                        const auto&_each_wchar = *(_src_wchar + _i);
                        if( _each_wchar <= 0x7F ){
                            _ret_string.push_back( static_cast<assic_char>(_each_wchar) );
                        } else if( _each_wchar <= 0x7FF ){
                            _ret_string.push_back( 0xC0 | ((_each_wchar >> 6)& 0x1F) );
                            _ret_string.push_back( 0x80| (_each_wchar & 0x3F) );
                        } else if (_each_wchar <= 0xFFFF){
                            _ret_string.push_back(0xe0 | ((_each_wchar >> 12)& 0x0F));
                            _ret_string.push_back(0x80| ((_each_wchar >> 6) & 0x3F));
                            _ret_string.push_back(0x80| (_each_wchar & 0x3F));
                        } else if (_each_wchar <= 0x10FFFF ){
                            _ret_string.push_back(0xF0 | ((_each_wchar >> 18)& 0x07));
                            _ret_string.push_back(0x80| ((_each_wchar >> 12) & 0x3F));
                            _ret_string.push_back(0x80| ((_each_wchar >> 6) & 0x3F));
                            _ret_string.push_back(0x80| (_each_wchar & 0x3F));
                        } else{
                            throw std::runtime_error( "Conversion Occurs Error" );
                        }
                    }
                } catch( const std::exception& _ex ){
                    printf( "Exception Caught: %s", _ex.what() );
                }
#else
#error UNKNOW_COMPILE_ENV
#endif
            }
            return _ret_string;
        }

  }
}//namespace Magna
