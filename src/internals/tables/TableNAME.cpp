#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableNAME.h"
#include "OpenType.h"

namespace OpenType {


    // @todo This is almost correct although could do with some unicode tests
    // for UTF-8 and UTF-16 for reading from type_reader as some of it is
    // still garbled e.g. Copyright character and Greek letters (Language:0x408)

    TableNAME::TableNAME(TypeReader type_reader) :
        AbstractTable(),
        format_(0),
        count_(0),
        string_offset_(0),
        lang_tag_count_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableNAME::from_bytes( TypeReader& type_reader ) {
        format_ = type_reader.readUInt16();
        count_ = type_reader.readUInt16();
        string_offset_ = type_reader.readOffset16();
        for( int ii=0; ii < count_; ii++ ) {
            auto name_record = NameRecord{};
            name_record.platform_id = type_reader.readUInt16();
            name_record.encoding_id = type_reader.readUInt16();
            name_record.language_id = type_reader.readUInt16();
            name_record.name_id = type_reader.readUInt16();
            name_record.length = type_reader.readUInt16();
            name_record.offset = type_reader.readOffset16();
            name_records_.push_back( std::move(name_record) );
        }

        if ( format_ == 0x1 ) {
            lang_tag_count_ = type_reader.readUInt16();
            for( int ii=0; ii < lang_tag_count_; ii++ ) {
                auto lang_tag_record = LangTagRecord {};
                lang_tag_record.length = type_reader.readUInt16();
                lang_tag_record.offset = type_reader.readOffset16();
                lang_tag_records_.push_back( std::move( lang_tag_record) );
            }
        }

        // reads the names section into a single stream that makes it easy for us to offset
        TypeReader subreader = type_reader.get_byte_sequence( type_reader.get_position() );
        for( auto& name_record : name_records_ ) {
            // the name_record information can be used to work out how to
            // decode the strings
            // (1,0) and (3,1) are common
            switch( name_record.platform_id ) {
                case PLATFORM_ID_UNICODE:
                    throw std::runtime_error( "Platform and encoding not supported.");
                    break;
                case PLATFORM_ID_MACINTOSH:
                    switch( name_record.encoding_id ) {
                    case 0:
                        name_record.text = subreader.readStringUTF8( name_record.offset, name_record.length );
                        break;
                    default:
                        throw std::runtime_error( "Platform and encoding not supported.");
                    }
                    break;
                case PLATFORM_ID_ISO:
                    throw std::runtime_error( "Platform and encoding not supported.");
                    break;
                case PLATFORM_ID_WINDOWS:
                    switch ( name_record.encoding_id ) {
                    case WIN_PLATFORM_EID_SYMBOL:
                        name_record.text = subreader.readStringUTF16BF( name_record.offset, name_record.length );
                        break;
                    case WIN_PLATFORM_EID_UNICODE_BMP:
                        name_record.text = subreader.readStringUTF16BF( name_record.offset, name_record.length );
                        break;
                    default:
                        throw std::runtime_error( "Platform and encoding not supported.");
                    }
                    break;
                case PLATFORM_ID_CUSTOM:
                    throw std::runtime_error( "Platform and encoding not supported.");
                    break;
            }
        }

        if ( format_ == 0x1 ) {
            std::cout << "LANGUAGES" << std::endl;
            for( auto& lang_tag_record : lang_tag_records_ ) {
                lang_tag_record.text = subreader.readStringUTF16BF( lang_tag_record.offset, lang_tag_record.length );
                std::cout << lang_tag_record.text << std::endl;
            }
            // @todo find a font that has these language and figure out what to do with them.
        }
    }

    // @Override
    void TableNAME::print(std::ostream& out) const {
        out << "NAME{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << format_ << ",";
        out << std::dec;
        out << count_ << ",";
        out << string_offset_ << ",";
        for( auto nr : name_records_ ) {
            out << "{";
            out << nr.platform_id << "," << nr.encoding_id << ","
                << std::hex << "0x" << nr.language_id << std::dec <<
                "," << nr.name_id
                << "," << nr.length << "," << nr.offset << ",";
            out << "\"" << nr.text << "\"";
            out << "}";
        }
        out << lang_tag_count_ << ",";
        for( auto nr : lang_tag_records_ ) {
            out << "{";
            out << nr.length << "," << nr.offset << ",";
            out << "\"" << nr.text << "\"";
            out << "}";
        }
        out << "}";
    }

}
