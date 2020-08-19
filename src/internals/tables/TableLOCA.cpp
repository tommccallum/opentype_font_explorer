#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableLOCA.h"

namespace OpenType {

    TableLOCA::TableLOCA(TypeReader type_reader, bool use_long_offsets ) :
        AbstractTable(),
        use_long_offsets_(use_long_offsets)
    {
        from_bytes( type_reader );
    }

    bool TableLOCA::use_long_offsets() const {
        return use_long_offsets_;
    }

    OT_OFFSET16 TableLOCA::get_offset16( OT_UINT16 glyph_index ) const {
        return short_offsets_[glyph_index];
    }
    OT_UINT16 TableLOCA::get_glyph_data_length16(OT_UINT16 glyph_index) const {
        assert( glyph_index < short_offsets_.size()-1 );
        return short_offsets_[ glyph_index+1 ] - short_offsets_[ glyph_index ];
    }
    OT_OFFSET32 TableLOCA::get_offset32( OT_UINT16 glyph_index ) const {
        return long_offsets_[glyph_index];
    }
    OT_UINT32 TableLOCA::get_glyph_data_length32(OT_UINT16 glyph_index) const {
        assert( glyph_index < long_offsets_.size()-1 );
        return long_offsets_[ glyph_index+1 ] - long_offsets_[ glyph_index ];
    }

    size_t TableLOCA::size() const {
        if ( use_long_offsets() ) {
            return long_offsets_.size();
        } else {
            return short_offsets_.size();
        }
    }
    void TableLOCA::from_bytes( TypeReader& type_reader ) {
        if ( use_long_offsets_ ) {
            long_offsets_ = type_reader.readOffset32Vector();
        } else {
            short_offsets_ = type_reader.readOffset16Vector();
        }

    }

    // @Override
    void TableLOCA::print(std::ostream& out) const {
        out << std::dec;
        out << "LOCA(" << (use_long_offsets_ == false ? "SHORT" : "LONG") << ","
                        << short_offsets_.size() << ","
                        << long_offsets_.size() << "){";
        if ( use_long_offsets_) {
            size_t n = long_offsets_.size();
            size_t ii=0;
            for( auto cv : long_offsets_ ) {
                out << int(cv) ;
                if ( ii < n-1 ) out << ",";
                ii++;
            }
        } else {
            size_t n = short_offsets_.size();
            size_t ii=0;
            for( auto cv : short_offsets_ ) {
                out << int(cv) ;
                if ( ii < n-1 ) out << ",";
                ii++;
            }
        }
        out << "}";
        //out << std::endl;
    }

}
