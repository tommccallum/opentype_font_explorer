#ifndef TABLE_HEAD_H
#define TABLE_HEAD_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"
#include "internals/FixedPointMath.h"

namespace OpenType {

    class TypeReader;

    class TableHEAD : public AbstractTable {
    public:

        enum IndexToLocFormat {
            SHORT_OFFSETS=0x0,
            LONG_OFFSETS=0x1
        };

        TableHEAD( TypeReader type_reader );
        IndexToLocFormat index_to_loc_format();
        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 major_version_;
        OT_UINT16 minor_version_;
        OT_FIXED font_revision_;
        OT_UINT32 check_sum_adjustment_;
        OT_UINT32 magic_number_;
        OT_UINT16 flags_;
        OT_UINT16 units_per_em_;
        OT_LONGDATETIME created_;
        OT_LONGDATETIME modified_;
        OT_INT16 x_min_;
        OT_INT16 y_min_;
        OT_INT16 x_max_;
        OT_INT16 y_max_;
        OT_UINT16 mac_style_;
        OT_UINT16 lowest_rec_ppem_;
        OT_INT16 font_direction_hint_;
        IndexToLocFormat index_to_loc_format_;
        OT_INT16 glyph_data_format_;

        void from_bytes( TypeReader& type_reader );
    };

}

#endif // TABLE_HEAD_H
