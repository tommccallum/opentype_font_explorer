#ifndef TABLE_POST_H
#define TABLE_POST_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TablePOST : public AbstractTable {
    public:
        TablePOST( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
    private:
        OT_FIXED version_;
        OT_FIXED italic_angle_;
        OT_FWORD underline_position_;
        OT_FWORD underline_thickness_;
        OT_UINT32 is_fixed_pitch_;
        OT_UINT32 min_mem_type_42_;
        OT_UINT32 max_mem_type_42_;
        OT_UINT32 min_mem_type_1_;
        OT_UINT32 max_mem_type_1_;
        // end of version 1 / 3

        // version 2.0
        OT_UINT16 num_glyphs_;
        // the index here indexes into names_ if you substract 258
        // from the number stored i.e.
        // names_[ glyph_name_index_[some_index] - 258 ]
        // if < 258 then get glyph name from standard order.
        std::vector<OT_UINT16> glyph_name_index_;
        std::vector<std::string> names_;
        // end version 2.0

        // version 2.5
        // uses num_glyphs_
        std::vector<OT_INT8> offset_;

        void from_bytes( TypeReader& type_reader );
        bool is_supported_version();
    };
}

#endif // TABLE_POST_H
