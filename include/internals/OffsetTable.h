#ifndef OFFSET_TABLE_H
#define OFFSET_TABLE_H

#include <vector>
#include "internals/InternalTypes.h"

namespace OpenType {
    class FontReader;
    class TableRecord;

    class OffsetTable {
    public:
        OffsetTable();
        void from_bytes( FontReader& reader );
        OT_UINT32 get_sfnt_version() const;
        TableRecord & get_table( std::string const name ) const;
        bool exists_table(std::string const name) const;
        friend std::ostream& operator<<( std::ostream& out, const OffsetTable& table );
    private:
        struct OffsetInfo {
            // OpenType fonts that contain TrueType outlines should use the
            // value of 0x00010000 for the sfntVersion. OpenType fonts
            // containing CFF data (version 1 or 2)
            // should use 0x4F54544F ('OTTO', when re-interpreted as a Tag)
            // for sfntVersion.
            OT_UINT32 sfnt_version;
            OT_UINT16 num_tables; // number of tables contained
            OT_UINT16 search_range; // maximum power of 2 <= numTables x 16
            OT_UINT16 entry_selector; // log2(maximum power of 2 <= num_tables)
            OT_UINT16 range_shift; // numtables x 16 - searchRange
        };
        OffsetInfo info_;
        std::vector<std::unique_ptr<TableRecord>> table_records_;

        void read_table_records( FontReader& reader );

        size_t get_info_size() {
            return sizeof( OffsetInfo );
        }
    };
}

#endif // OFFSET_TABLE_H
