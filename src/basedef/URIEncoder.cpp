#include "URIEncoder.h"

#include "URIParser_p.h"

namespace Magna{
    namespace Core{
        static unicode_char shared_hexTable[] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'A', L'B', L'C', L'D', L'E', L'F' };

        String URIEncoder::URIEncode( const String& _input_uri_string ){
            String _encoded_string;
            if( !_input_uri_string.empty() ){
                auto _utf8_string = _input_uri_string.toUTF8();
                const auto _utf8_size = _utf8_string.size();

                // reserved
                _encoded_string.reserve( _utf8_size + ( _utf8_size >> 2 ) + ( _utf8_size >> 4 ) );

                for( auto _each_iter = _utf8_string.begin(); _utf8_string.end() != _each_iter; ++_each_iter ){
                    uint8 _each_char_value = static_cast<uint8>( *_each_iter );

                    if( _each_char_value < 128 
                        && CharacterChecker::isUnencodedChar( static_cast<unicode_char>( _each_char_value ) ) ){
                        _encoded_string.push_back( static_cast<unicode_char>( _each_char_value ) );
                    } else{
                        _encoded_string.push_back( L'%' );

                        uint8 _high_bits = ( ( _each_char_value >> 4 ) & 0x0F );
                        uint8 _low_bits = ( _each_char_value & 0x0F );
                        _encoded_string.push_back( shared_hexTable[ _high_bits ] );
                        _encoded_string.push_back( shared_hexTable[ _low_bits ] );
                    }
                }
            }
            return _encoded_string;
        }

        String URIEncoder::dataEncode( const String& _input_uri_string ){
            String _encoded_string;
            if( !_input_uri_string.empty() ){
                auto _utf8_string = _input_uri_string.toUTF8();
                const auto _utf8_size = _utf8_string.size();

                // reserved
                _encoded_string.reserve( _utf8_size + ( _utf8_size >> 2 ) + ( _utf8_size >> 4 ) );

                for( auto _each_iter = _utf8_string.begin(); _utf8_string.end() != _each_iter; ++_each_iter ){
                    uint8 _each_char_value = static_cast<uint8>( *_each_iter );

                    _encoded_string.push_back( L'%' );

                    uint8 _high_bits = ( ( _each_char_value >> 4 ) & 0x0F );
                    uint8 _low_bits = ( _each_char_value & 0x0F );
                    _encoded_string.push_back( shared_hexTable[ _high_bits ] );
                    _encoded_string.push_back( shared_hexTable[ _low_bits ] );
                }
            }
            return _encoded_string;
        }
    }
}