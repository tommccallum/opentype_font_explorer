#ifndef TABLE_RECORD_H
#define TABLE_RECORD_H

#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"
#include "internals/TypeReader.h"

namespace OpenType {
    class FontReader;
    class OffsetTable;

    // forward declare table classes
    class TableDSIG;
    class TableLTSH;
    class TableOS2;
    class TableVDMX;
    class TableCMAP;
    class TableCVT;
    class TableFPGM;
    class TableMAXP;
    class TablePREP;
    class TableLOCA;
    class TableHEAD;
    class TablePOST;
    class TableNAME;
    class TableKERN;
    class TableGASP;
    class TableGLYF;
    class TableHHEA;
    class TableHMTX;
    class TableHDMX;

    class TableRecord {
    public:
        TableRecord();
        void from_bytes( FontReader& reader );
        void get_data( OffsetTable const & offsetTable );
        std::string get_tag() const;
        AbstractTable* get_table() const; // get common table

        // get a particular table
        // these are needed to dynamically cast to a specific table
        TableDSIG* get_dsig() const;
        TableLTSH* get_ltsh() const;
        TableOS2* get_os2() const;
        TableVDMX* get_vdmx() const;
        TableCMAP* get_cmap() const;
        TableCVT* get_cvt() const;
        TableFPGM* get_fpgm() const;
        TableMAXP* get_maxp() const;
        TablePREP* get_prep() const;
        TableLOCA* get_loca() const;
        TableHEAD* get_head() const;
        TablePOST* get_post() const;
        TableNAME* get_name() const;
        TableKERN* get_kern() const;
        TableGASP* get_gasp() const;
        TableGLYF* get_glyf() const;
        TableHMTX* get_hmtx() const;
        TableHHEA* get_hhea() const;
        TableHDMX* get_hdmx() const;

        friend std::ostream& operator<<( std::ostream& out, TableRecord const & table );
        friend std::ostream& operator<<( std::ostream& out, TableRecord const * table );

    private:
        struct TableRecordInfo {
            std::string      table_tag;
            OT_UINT32   checksum;
            OT_OFFSET32 offset;
            OT_UINT32   length;
        };
        TableRecordInfo info_;
        OT_UINT32 bof_offset_;
        OT_UINT32 calculated_checksum_;
        size_t calculated_length_;
        std::unique_ptr<AbstractTable> table_ptr_;
        TypeReader internal_bytes_reader;

        size_t get_info_size() {
            return sizeof(OT_TAG) + sizeof(OT_UINT32) + sizeof(OT_OFFSET32) + sizeof(OT_UINT32);
        }

        void read_table_data( const FontReader& reader);
    };
}

#endif // TABLE_RECORD_H
