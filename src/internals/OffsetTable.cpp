#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include <sstream>

#include "internals/EnumTable.h"
#include "internals/OffsetTable.h"
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/TableRecord.h"
#include "internals/tables/TableHEAD.h"

namespace OpenType {

    OffsetTable::OffsetTable() {

    }

    void OffsetTable::from_bytes( FontReader& reader ) {
        auto type_reader = TypeReader( reader.get_bytes( 0, get_info_size() ) );
        info_.sfnt_version = type_reader.readUInt32();
        info_.num_tables = type_reader.readUInt16();
        info_.search_range = type_reader.readUInt16();
        info_.entry_selector = type_reader.readUInt16();
        info_.range_shift = type_reader.readUInt16();

        // read all the table records as well as we are in the right place
        read_table_records( reader );
    }

    OT_UINT32 OffsetTable::get_sfnt_version() const {
        return info_.sfnt_version;
    }

    void OffsetTable::read_table_records( FontReader& reader ) {
        // first we have to look for HEAD table which gives us some
        // variables we need for the other tables
        for(size_t ii=0; ii < info_.num_tables; ii++ ) {
            auto table_record = std::make_unique<TableRecord>();
            table_record->from_bytes( reader );
            table_records_.push_back( std::move(table_record) );
        }

        assert( exists_table(HEAD) );
        assert( exists_table(MAXP) && exists_table(LOCA) );

        // first we get the full header which gives us a number of
        // variables we need later on
        get_table(HEAD).get_data( *this );

        // then we want to get all tables that are not dependent on
        // any others
        for( auto& tr : table_records_ ) { // tr is a unique_ptr reference
            std::string table_name = tr->get_tag();
            if ( table_name != GLYF &&
                 table_name != HMTX &&
                 table_name != HDMX ) {
                tr->get_data( *this );
            }
        }
        // glyf is dependent on MAXP and LOCA
        get_table(GLYF).get_data( *this );
        // htmx is dependent on a variety on MAXP and hhea tables
        get_table(HMTX).get_data( *this );
        // hmdx is dependent on MAXP for num_glyphs
        get_table(HDMX).get_data( *this );
    }

    bool OffsetTable::exists_table(std::string const name) const {
        for( auto& table : table_records_ ) {
            if ( table->get_tag() == name ) {
                return true;
            }
        }
        return false;
    }

    TableRecord & OffsetTable::get_table(std::string const name) const {
        for( auto& table : table_records_ ) {
            if ( table->get_tag() == name ) {
                return *(table.get());
            }
        }
        std::stringstream ss;
        ss << name << " table not found";
        throw std::runtime_error(ss.str());
    }

    std::ostream& operator<<( std::ostream& out, const OffsetTable& table ) {
        out << "OffsetTable{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.sfnt_version << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.num_tables << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.search_range << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.entry_selector << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.range_shift << ",";
        out << table.table_records_.size();
        out << "}\n";

        for( auto& tr : table.table_records_ ) {
            out << *(tr.get()) << std::endl;
        }
        return out;
    }
}
