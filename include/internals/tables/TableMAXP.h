#ifndef TABLE_MAXP_H
#define TABLE_MAXP_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"
#include "internals/FixedPointMath.h"

namespace OpenType {

    class TypeReader;

    class TableMAXP : public AbstractTable {
    public:
        TableMAXP( TypeReader type_reader );
        OT_UINT16 get_num_glyphs() const;
        OT_UINT16 get_max_points() const;
        OT_UINT16 get_max_contours() const;
        OT_UINT16 get_max_size_of_instructions() const;

        void print(std::ostream& out) const; // Override
    private:
        OT_FIXED version_;
        OT_UINT16 num_glyphs_;
        // end of version 0.5
        OT_UINT16 max_points_;
        OT_UINT16 max_contours_;
        OT_UINT16 max_composite_points_;
        OT_UINT16 max_composite_contours_;
        OT_UINT16 max_zones_;
        OT_UINT16 max_twilight_points_;
        OT_UINT16 max_storage_;
        OT_UINT16 max_function_defs_;
        OT_UINT16 max_instruction_defs_;
        OT_UINT16 max_stack_elements_;
        OT_UINT16 max_size_of_instructions_;
        OT_UINT16 max_component_elements_;
        OT_UINT16 max_component_depth_;
        void from_bytes( TypeReader& type_reader );

    };

}

#endif // TABLE_MAXP_H
