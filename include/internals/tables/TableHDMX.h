#ifndef TABLE_HDMX_H
#define TABLE_HDMX_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TableHDMX : public AbstractTable {
    public:
        struct DeviceRecord {
            OT_UINT8 pixel_size;
            OT_UINT8 max_width;
            std::vector<OT_UINT8> widths;
        };

        TableHDMX( TypeReader type_reader, OT_UINT16 num_glyphs );

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_INT16 num_records_;
        OT_INT32 size_device_record_;
        std::vector<DeviceRecord> device_records_;
        OT_UINT16 num_glyphs_; // from maxp

        // vertical pel height at which the glyph can be assumed to
        // scale linearly, on a per glyph basis
        std::vector<char> y_pels_;

        void from_bytes( TypeReader& type_reader );

    };
}

#endif // TABLE_HDMX_H
