#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TablePOST.h"

namespace OpenType {

    TablePOST::TablePOST(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        italic_angle_(0),
        underline_position_(0),
        underline_thickness_(0),
        is_fixed_pitch_(0),
        min_mem_type_42_(0),
        max_mem_type_42_(0),
        min_mem_type_1_(0),
        max_mem_type_1_(0),
        num_glyphs_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TablePOST::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readFixed();
        italic_angle_ = type_reader.readFixed();
        underline_position_ = type_reader.readFWORD();
        underline_thickness_ = type_reader.readFWORD();
        is_fixed_pitch_ = type_reader.readUInt32();
        min_mem_type_42_ = type_reader.readUInt32();
        max_mem_type_42_ = type_reader.readUInt32();
        min_mem_type_1_ = type_reader.readUInt32();
        max_mem_type_1_ = type_reader.readUInt32();

        if ( version_ == (int32_t)(0x00020000L) ||
             version_ == (int32_t)(0x00025000L)
            ) {
            num_glyphs_ = type_reader.readUInt16();
            if ( version_ == (int32_t)(0x00020000L) ) {
                for( size_t ii=0; ii < num_glyphs_; ii++ ) {
                    glyph_name_index_.push_back( type_reader.readUInt16() );
                }
                while ( !type_reader.eof() ) {
                    names_.push_back( type_reader.readPascalString() );
                }
            } else if ( version_ == (int32_t)(0x00025000L) ) {
                for( size_t ii=0; ii < num_glyphs_; ii++ ) {
                    offset_.push_back( type_reader.readInt8() );
                }
            }
        }
    }

    // @Override
    void TablePOST::print(std::ostream& out) const {
        out << std::dec;
        out << "POST{";
        out << version_ << ",";
        out << italic_angle_ << ",";
        out << underline_position_ << ",";
        out << underline_thickness_ << ",";
        out << is_fixed_pitch_ << ",";
        out << min_mem_type_42_ << ",";
        out << max_mem_type_42_ << ",";
        out << min_mem_type_1_ << ",";
        out << max_mem_type_1_ << ",";
        // end of version 1 / 3

        // version 2.0
        out << "V2/2.5{";
        out << num_glyphs_ << ",(";
        size_t ii=0;
        for( auto x : glyph_name_index_) {
            out << x;
            if ( ii < glyph_name_index_.size() - 1 ) out << ",";
            ii++;
        }
        out << "),(";
        ii=0;
        for( auto x : names_) {
            out << x;
            if ( ii < names_.size() - 1 ) out << ",";
            ii++;
        }
        out << "),(";
        ii=0;
        for( auto x : offset_) {
            out << x;
            if ( ii < offset_.size() - 1 ) out << ",";
            ii++;
        }
        out << ")";
        out << "}"; // end of version 2/2.5 section

        out << "}";
    }

}
