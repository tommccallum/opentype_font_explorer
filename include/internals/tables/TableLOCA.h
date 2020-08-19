#ifndef TABLE_LOCA_H
#define TABLE_LOCA_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    class TableLOCA : public AbstractTable {
    public:
        TableLOCA( TypeReader type_reader, bool use_long_offsets );
        bool use_long_offsets() const;
        OT_OFFSET16 get_offset16( OT_UINT16 glyph_index ) const;
        OT_UINT16 get_glyph_data_length16(OT_UINT16 glyph_index) const;
        OT_OFFSET32 get_offset32( OT_UINT16 glyph_index ) const;
        OT_UINT32 get_glyph_data_length32(OT_UINT16 glyph_index) const;
        size_t size() const;
        void print(std::ostream& out) const; // Override
    private:
        bool use_long_offsets_;
        std::vector<OT_OFFSET16> short_offsets_;
        std::vector<OT_OFFSET32> long_offsets_;
        void from_bytes( TypeReader& type_reader );

    };

}

#endif // TABLE_LOCA_H
