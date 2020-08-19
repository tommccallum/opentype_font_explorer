#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableKERN.h"

namespace OpenType {

    TableKERN::TableKERN(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_tables_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableKERN::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        num_tables_ = type_reader.readUInt16();

        for( int ii=0; ii < num_tables_; ii++ ) {
            auto kern_subtable = KernSubtable {};
            kern_subtable.version = type_reader.readUInt16(); // version of kern table
            kern_subtable.length = type_reader.readUInt16();
            kern_subtable.coverage = type_reader.readUInt16(); // type of info

            if ( table_format( kern_subtable.coverage ) == 0x0 ) {
                auto f0 = load_format0( type_reader.get_byte_sequence( type_reader.get_position(), kern_subtable.length ) );
                kern_subtable.format0.reset(f0);
            } else if ( table_format( kern_subtable.coverage ) == 0x2 ) {
                auto f2 = load_format2( type_reader.get_byte_sequence( type_reader.get_position(), kern_subtable.length ) );
                kern_subtable.format2.reset(f2);
            } else {
                throw std::runtime_error("invalid KERN subtable format");
            }
            subtables_.push_back( std::move(kern_subtable) );
        }
    }

    TableKERN::Format0* TableKERN::load_format0( TypeReader type_reader ) {
        auto f0 = new TableKERN::Format0 {};
        f0->num_pairs = type_reader.readUInt16();
        f0->search_range = type_reader.readUInt16();
        f0->entry_selector = type_reader.readUInt16();
        f0->range_shift = type_reader.readUInt16();

        for( int ii=0; ii < f0->num_pairs; ii++ ) {
            auto kp = KerningPair {};
            kp.left = type_reader.readUInt16();
            kp.right = type_reader.readUInt16();
            kp.value = type_reader.readFWORD();
            f0->kerning_pairs.push_back( kp );
        }
        return f0;
    }

    TableKERN::Format2* TableKERN::load_format2( TypeReader type_reader ) {
        auto f2 = new TableKERN::Format2 {};
        f2->row_width = type_reader.readUInt16();
        f2->left_class_table_offset = type_reader.readOffset16();
        f2->right_class_table_offset = type_reader.readOffset16();
        f2->array_offset = type_reader.readOffset16();

        auto class_table = load_class_table( type_reader.get_byte_sequence(f2->left_class_table_offset), f2->left_class_table_offset);
        f2->left_class_table = class_table;
        class_table = load_class_table( type_reader.get_byte_sequence(f2->right_class_table_offset), f2->right_class_table_offset);
        f2->right_class_table = class_table;

        TypeReader array_values = type_reader.get_byte_sequence( f2->array_offset, f2->left_class_table.num_glyphs * f2->right_class_table.num_glyphs );
        while( array_values.eof() == false ) {
            f2->kerning_values.push_back( array_values.readFWORD() );
        }
        return f2;
    }

    TableKERN::ClassTable TableKERN::load_class_table( TypeReader type_reader, OT_OFFSET16 offset ) {
        type_reader.seek( offset );
        auto class_table = TableKERN::ClassTable {};
        class_table.first_glyph = type_reader.readUInt16();
        class_table.num_glyphs = type_reader.readUInt16();

        for( int ii=0; ii < class_table.num_glyphs; ii++ ) {
            class_table.class_values.push_back( type_reader.readUInt16() );
        }
        return class_table;
    }

    /**
     * Is table has horizontal data
     * @param coverage [description]
     * @return TRUE if horizontal data, vertical otherwise
     */
    bool TableKERN::is_horizontal(OT_UINT16 coverage) const {
        return (coverage & 0x1) == 0x1;
    }

    bool TableKERN::is_vertical(OT_UINT16 coverage) const {
        return (coverage & 0x1) == 0x0;
    }

    /**
     * If this bit is set to 1, the table has minimum values. If set to 0, the table has kerning values.
     * @param coverage [description]
     */
    bool TableKERN::is_minimum(OT_UINT16 coverage) const {
        return (coverage & 0x2) == 0x2;
    }

    /**
     * If set to 1, kerning is perpendicular to the flow of the text.
     * @param coverage [description]
     */
    bool TableKERN::is_cross_stream( OT_UINT16 coverage ) const {
        return (coverage & 0x4) == 0x4;
    }

    /**
     * If this bit is set to 1 the value in this table should replace the value currently being accumulated.
     * @param coverage [description]
     */
    bool TableKERN::is_override( OT_UINT16 coverage ) const {
        return (coverage & 0x8) == 0x8;
    }

    /**
     * Format of the subtable. Only formats 0 and 2 have been defined.
     * Formats 1 and 3 through 255 are reserved for future use.
     * @param coverage [description]
     */
    OT_UINT8 TableKERN::table_format( OT_UINT16 coverage ) const {
        return coverage >> 8;
    }



    // @Override
    void TableKERN::print(std::ostream& out) const {
        out << "KERN{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << version_ << ",";
        out << std::dec << num_tables_ << ",";

        for( auto& kern : subtables_ ) {
            out << "0x" << std::setfill('0') << std::setw(8) << std::hex << kern.coverage << ",";
            out << std::dec;
            out << (is_horizontal(kern.coverage) == true ? "TRUE" : "FALSE" ) << ",";
            out << (is_minimum(kern.coverage) == true ? "TRUE" : "FALSE" ) << ",";
            out << (is_cross_stream(kern.coverage) == true ? "TRUE" : "FALSE" ) << ",";
            out << (is_override(kern.coverage) == true ? "TRUE" : "FALSE" ) << ",";
            out << "0x" << std::setfill('0') << std::setw(4) << std::hex << int(table_format(kern.coverage)) << ",";
            out << std::dec;

            if ( kern.format0 != nullptr ) {
                out << "FORMAT0{";
                out << kern.format0->num_pairs << ",";
                out << kern.format0->search_range << ",";
                out << kern.format0->entry_selector << ",";
                out << kern.format0->range_shift << ",";
                out << "{";
                for( auto kp : kern.format0->kerning_pairs ) {
                    out << "(";
                    out << kp.left << ",";
                    out << kp.right << ",";
                    out << kp.value;
                    out << ")";
                }
                out << "}}";
            }
            if ( kern.format2 != nullptr ) {
                out << "FORMAT2{";
                out << "@TODO";
                out << "}";
            }
        }
        out << "}";
        out << std::endl;
    }

}
