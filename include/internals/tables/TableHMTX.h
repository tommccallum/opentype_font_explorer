#ifndef TABLE_HMTX_H
#define TABLE_HMTX_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;
    class TableMAXP;
    class TableHHEA;

    // class name matches the tag of the table
    class TableHMTX : public AbstractTable {
    public:
        struct LongHorMetric {
                OT_UINT16 advance_width;
                OT_INT16 lsb;
        };

        TableHMTX( TypeReader type_reader, TableHHEA* hhea, TableMAXP* maxp );

        void print(std::ostream& out) const; // Override
    private:
        std::vector<LongHorMetric> h_metrics_;
        std::vector<OT_INT16> left_side_bearings_;
        OT_UINT16 number_of_h_metrics_; // from hhea
        OT_UINT16 num_glyphs_; // from maxp
        void from_bytes( TypeReader& type_reader );
    };
}

#endif // TABLE_HMTX_H
