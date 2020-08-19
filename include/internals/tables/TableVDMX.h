#ifndef TABLE_VDMX_H
#define TABLE_VDMX_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TableVDMX : public AbstractTable {
    public:
        struct RatioRange {
            OT_UINT8 b_char_set;
            OT_UINT8 x_ratio;
            OT_UINT8 y_start_ratio;
            OT_UINT8 y_end_ratio;
        };

        struct vTableRecord {
            OT_UINT16 y_pel_height;
            OT_INT16 y_max;
            OT_INT16 y_min;
        };

        struct VDMXGroup {
            OT_UINT16 height_records;
            OT_UINT8 start_sz;
            OT_UINT8 end_sz;
            std::vector<vTableRecord> vdmx_records;
        };

        TableVDMX( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_UINT16 num_vdmx_groups_;
        OT_UINT16 num_ratio_groups_;
        std::vector<RatioRange> ratio_ranges_;
        std::vector<OT_OFFSET16> offsets_;
        std::vector<VDMXGroup> vdmx_groups_;
        void from_bytes( TypeReader& type_reader );
    };
}

#endif // TABLE_VDMX_H
