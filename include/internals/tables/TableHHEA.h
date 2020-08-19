#ifndef TABLE_HHEA_H
#define TABLE_HHEA_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TableHHEA : public AbstractTable {
    public:
        TableHHEA( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
        OT_UINT16 get_number_of_h_metrics() const;
    private:
        OT_UINT16 major_version_;
        OT_UINT16 minor_version_;
        OT_FWORD ascender_;
        OT_FWORD descender_;
        OT_FWORD line_gap_;
        OT_UFWORD advance_width_max_;
        OT_FWORD min_left_side_bearing_;
        OT_FWORD min_right_side_bearing_;
        OT_FWORD x_max_extent_;
        OT_INT16 caret_slope_rise_;
        OT_INT16 caret_slope_run_;
        OT_INT16 caret_offset_;
        OT_INT16 reserved1_;
        OT_INT16 reserved2_;
        OT_INT16 reserved3_;
        OT_INT16 reserved4_;
        OT_INT16 metric_data_format_;
        OT_UINT16 number_of_h_metrics_;


        void from_bytes( TypeReader& type_reader );

    };
}

#endif // TABLE_HHEA_H
