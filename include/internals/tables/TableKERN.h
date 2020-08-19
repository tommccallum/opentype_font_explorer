#ifndef TABLE_KERN_H
#define TABLE_KERN_H

#include <vector>
#include <iostream>
#include <memory>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"
#include "internals/FixedPointMath.h"

namespace OpenType {

    class TypeReader;

    class TableKERN : public AbstractTable {
    public:
        struct KerningPair {
            OT_UINT16 left;
            OT_UINT16 right;
            OT_FWORD value;
        };

        struct Format0 {
            OT_UINT16 num_pairs;
            OT_UINT16 search_range;
            OT_UINT16 entry_selector;
            OT_UINT16 range_shift;
            std::vector<KerningPair> kerning_pairs;
        };

        struct ClassTable {
            OT_UINT16 first_glyph;
            OT_UINT16 num_glyphs;
            std::vector<OT_UINT16> class_values; // of size num_glyph
        };

        struct Format2 {
            OT_UINT16 row_width;
            OT_OFFSET16 left_class_table_offset;
            OT_OFFSET16 right_class_table_offset;
            OT_OFFSET16 array_offset;
            // completed when read in
            ClassTable left_class_table;
            ClassTable right_class_table;
            std::vector<OT_FWORD> kerning_values;
        };

        struct KernSubtable {
            OT_UINT16 version;
            OT_UINT16 length;
            OT_UINT16 coverage;

            // this is rather yucky
            std::unique_ptr<Format0> format0;
            std::unique_ptr<Format2> format2;
        };

        TableKERN( TypeReader type_reader );
        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_UINT16 num_tables_;
        std::vector<KernSubtable> subtables_;

        void from_bytes( TypeReader& type_reader );
        OT_UINT8 table_format( OT_UINT16 coverage ) const;
        bool is_override( OT_UINT16 coverage ) const;
        bool is_cross_stream( OT_UINT16 coverage ) const;
        bool is_minimum(OT_UINT16 coverage) const;
        bool is_vertical(OT_UINT16 coverage)  const;
        bool is_horizontal(OT_UINT16 coverage) const;
        ClassTable load_class_table( TypeReader type_reader, OT_OFFSET16 offset ) ;
        Format2* load_format2( TypeReader type_reader );
        Format0* load_format0( TypeReader type_reader );

    };

}

#endif // TABLE_KERN_H
