#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableCMAP.h"
#include "OpenType.h"

namespace OpenType {

    TableCMAP::AbstractPlatformEncodingFormat::~AbstractPlatformEncodingFormat() {

    }

    TableCMAP::TableCMAP(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_tables_(0)
    {
        from_bytes( type_reader );
    }

    TableCMAP::PlatformEncodingFormat TableCMAP::get_format_type(size_t index) {
        return format_types_[index];
    }
    TableCMAP::ByteEncodingFormat0* TableCMAP::get_format_0(size_t index) {
        return dynamic_cast<ByteEncodingFormat0*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat2* TableCMAP::get_format_2(size_t index) {
        return dynamic_cast<ByteEncodingFormat2*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat4* TableCMAP::get_format_4(size_t index) {
        return dynamic_cast<ByteEncodingFormat4*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat8* TableCMAP::get_format_8(size_t index) {
        return dynamic_cast<ByteEncodingFormat8*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat10* TableCMAP::get_format_10(size_t index) {
        return dynamic_cast<ByteEncodingFormat10*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat12* TableCMAP::get_format_12(size_t index) {
        return dynamic_cast<ByteEncodingFormat12*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat13* TableCMAP::get_format_13(size_t index) {
        return dynamic_cast<ByteEncodingFormat13*>(formats_[index].get());
    }
    TableCMAP::ByteEncodingFormat14* TableCMAP::get_format_14(size_t index) {
        return dynamic_cast<ByteEncodingFormat14*>(formats_[index].get());
    }

    // expects reader to be in correct position to read
    void TableCMAP::from_bytes( TypeReader& type_reader ) {
        PlatformEncodingFormat format = PLATFORM_ENCODING_FORMAT_NONE;
        version_ = type_reader.readUInt16();
        num_tables_ = type_reader.readUInt16();

        // read in all the encoding records
        for( size_t ii=0; ii < num_tables_; ii++ ) {
            auto encoding_record = EncodingRecord();
            encoding_record.platform_id = type_reader.readUInt16();
            encoding_record.encoding_id = type_reader.readUInt16();
            encoding_record.offset = type_reader.readOffset32();
            encoding_records_.push_back( std::move(encoding_record) );
        }

        // @see https://docs.microsoft.com/en-gb/typography/opentype/spec/CMAP#encoding-records-and-encodings
        for( auto encoding : encoding_records_ ) {
            // enum PlatformID {
            //     PLATFORM_ID_UNICODE=0,
            //     PLATFORM_ID_MACINTOSH=1,
            //     PLATFORM_ID_ISO=2,
            //     PLATFORM_ID_WINDOWS=3,
            //     PLATFORM_ID_CUSTOM=4
            // };
            switch( encoding.platform_id ) {
                case PLATFORM_ID_UNICODE:
                    // enum UnicodePlatformEncodingID {
                    //     UNI_PLATFORM_EID_UNICODE_10_SEMANTICS=0,
                    //     UNI_PLATFORM_EID_UNICODE_11_SEMANTICS=1,
                    //     UNI_PLATFORM_EID_ISO_10464_SEMANTICS=2,
                    //     UNI_PLATFORM_EID_UNICODE_20_BMP=3,
                    //     UNI_PLATFORM_EID_UNICODE_20_CMAP=4,
                    //     UNI_PLATFORM_EID_UNICODE_VAR=5,
                    //     UNI_PLATFORM_EID_UNICODE_FULL=6
                    // };
                    switch( encoding.encoding_id ) {
                        case UNI_PLATFORM_EID_UNICODE_VAR:
                            format = PLATFORM_ENCODING_FORMAT_14;
                            break;
                    }
                break;
                case PLATFORM_ID_MACINTOSH:
                    break;
                case PLATFORM_ID_ISO:
                    // none listed
                    break;
                case PLATFORM_ID_WINDOWS:
                    // enum WindowsPlatformEncodingID {
                    //     WIN_PLATFORM_EID_SYMBOL=0,
                    //     WIN_PLATFORM_EID_UNICODE_BMP=1,
                    //     WIN_PLATFORM_EID_SHIFTJIS=2,
                    //     WIN_PLATFORM_EID_PRC=3,
                    //     WIN_PLATFORM_EID_BIG5=4,
                    //     WIN_PLATFORM_EID_WANSUNG=5,
                    //     WIN_PLATFORM_EID_JOHAB=6,
                    //     WIN_PLATFORM_EID_RESERVED_1=7,
                    //     WIN_PLATFORM_EID_RESERVED_2=8,
                    //     WIN_PLATFORM_EID_RESERVED_3=9,
                    //     WIN_PLATFORM_EID_UNICODE_FULL=10
                    // };
                    // encoding_id == 1 then ByteEncodingFormat4
                    // encoding_id == 10 then ByteEncodingFormat12
                    switch ( encoding.encoding_id ) {
                        case WIN_PLATFORM_EID_UNICODE_BMP:
                            format = PLATFORM_ENCODING_FORMAT_4;
                            break;
                        case WIN_PLATFORM_EID_UNICODE_FULL:
                            format = PLATFORM_ENCODING_FORMAT_12;
                            break;
                    }
                    break;
                case PLATFORM_ID_CUSTOM:
                    // ignore for now
                    break;
            }

            // once the format has been decided THEN we load the format from
            // a single place
            load_format( format, type_reader.get_byte_sequence( encoding.offset ) );
        }

    }

    void TableCMAP::load_format( PlatformEncodingFormat format, TypeReader type_reader ) {
        switch( format ) {
        case PLATFORM_ENCODING_FORMAT_4:
            load_format4( type_reader );
            break;
        default:
            // add a null to keep us aligned with encoding records vector
            format_types_.push_back( PLATFORM_ENCODING_FORMAT_NONE );
            formats_.push_back( nullptr );
            // ignore the format and move on to the next one
            //throw std::runtime_error("Custom platform format not currently supported.");
        }
    }

    void TableCMAP::load_format0( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_0 );
        throw std::runtime_error("Custom platform format 0 not currently supported.");
    }

    void TableCMAP::load_format2( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_2 );
        throw std::runtime_error("Custom platform format 2 not currently supported.");
    }

    void TableCMAP::load_format4( TypeReader& type_reader ) {
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_4 );

        auto encoding = new ByteEncodingFormat4();
        encoding->format = type_reader.readUInt16();
        encoding->length = type_reader.readUInt16();
        encoding->language = type_reader.readUInt16();
        encoding->seg_count_x2 = type_reader.readUInt16();
        encoding->search_range = type_reader.readUInt16();
        encoding->entry_selector = type_reader.readUInt16();
        encoding->range_shift = type_reader.readUInt16();
        size_t seg_count= encoding->seg_count_x2 / 2;
        for( size_t ii=0; ii < seg_count; ii++ ) {
            encoding->end_codes.push_back( type_reader.readUInt16() );
        }
        encoding->reserved_pad = type_reader.readUInt16();
        for( size_t ii=0; ii < seg_count; ii++ ) {
            encoding->start_codes.push_back( type_reader.readUInt16() );
        }
        for( size_t ii=0; ii < seg_count; ii++ ) {
            encoding->id_deltas.push_back( type_reader.readInt16() );
        }
        for( size_t ii=0; ii < seg_count; ii++ ) {
            encoding->id_range_offsets.push_back( type_reader.readUInt16() );
        }
        // rest are UINT16
        encoding->glyph_ids = type_reader.readUInt16Vector();
    }



    /**
     * For ByteEncodingFormat4 map character code to a glyph index
     * @param index     index of the encoding to use
     * @param char_code the character code to get the glyph id for
     * @return the glyph index
     */
    OT_UINT16 TableCMAP::format4_map_character_code( int index, int char_code ) {
        ByteEncodingFormat4* encoding = get_format_4( index );
        size_t segment_index = 0;
        // search for first end_code that is greater than or equal to
        // the character code specified
        // @todo use a binary search here would be more efficient
        for( size_t ii=0; ii < encoding->end_codes.size(); ii++ ) {
            if ( encoding->end_codes[ii] >= char_code ) {
                segment_index = ii;
                break;
            }
        }
        // if our charater code is between [start,end]
        if ( encoding->start_codes[segment_index] <= char_code ) {
            // get the offset into glyph_ids array if the character_code
            // has a mapping
            OT_UINT16 range_offset = encoding->id_range_offsets[segment_index];
            if ( range_offset == 0  ) {
                // character code does not have an entry in glyph_ids array.
                // in this section the glyphs are located at a predefined offset
                // for all character codes in the segment so there is no need
                // for a lookup
                return char_code + encoding->id_deltas[segment_index];
            } else {
                // get where the glyphs for segment start in glyphs_id
                size_t offset = encoding->id_range_offsets[segment_index];
                // how far through this segment do we need to be
                size_t char_code_dt = char_code - encoding->start_codes[segment_index];
                size_t glyph_index = offset + char_code_dt;
                return encoding->glyph_ids[ glyph_index ];
            }
        }
        // map everything else to the missing glyph
        return 0;
    }

    OT_UINT16 TableCMAP::get_glyph_index(int encoding_index, int character_code) {
        PlatformEncodingFormat format = get_format_type( encoding_index );
        switch( format ) {
        case PLATFORM_ENCODING_FORMAT_4:
            return format4_map_character_code( encoding_index, character_code );
        default:
            // map to missing glyph by default
            return 0;
        }
    }

    void TableCMAP::load_format8( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_8 );
        throw std::runtime_error("Custom platform format 8 not currently supported.");
    }

    void TableCMAP::load_format10( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_10 );
        throw std::runtime_error("Custom platform format 10 not currently supported.");
    }

    void TableCMAP::load_format12( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_12 );
        throw std::runtime_error("Custom platform format 12 not currently supported.");
    }

    void TableCMAP::load_format13( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_13 );
        throw std::runtime_error("Custom platform format 13 not currently supported.");
    }

    void TableCMAP::load_format14( TypeReader& type_reader ) {
        UNUSED(type_reader);
        format_types_.push_back( PLATFORM_ENCODING_FORMAT_14 );
    }

    // @Override
    void TableCMAP::print(std::ostream& out) const {
        out << std::dec;
        out << "CMAP{";
        out << version_ << ",";
        out << num_tables_ << ",";

        size_t ii=0;
        for( auto record : encoding_records_ ) {
            out << "(";
            out << record.platform_id << ",";
            out << record.encoding_id << ",";
            out << record.offset << ",";
            out << format_types_[ii];
            out << ")";
            ii++;
        }
        out << "}";
    }

}
