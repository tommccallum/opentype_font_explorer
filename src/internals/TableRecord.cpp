#include <iostream>
#include <iomanip>
#include <memory>
#include <cassert>
#include "internals/EnumTable.h"
#include "internals/OffsetTable.h"
#include "internals/TableRecord.h"
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/EnumTable.h"
#include "internals/tables/TableDSIG.h"
#include "internals/tables/TableLTSH.h"
#include "internals/tables/TableOS2.h"
#include "internals/tables/TableVDMX.h"
#include "internals/tables/TableCMAP.h"
#include "internals/tables/TableCVT.h"
#include "internals/tables/TableFPGM.h"
#include "internals/tables/TableMAXP.h"
#include "internals/tables/TablePREP.h"
#include "internals/tables/TableLOCA.h"
#include "internals/tables/TableHEAD.h"
#include "internals/tables/TablePOST.h"
#include "internals/tables/TableNAME.h"
#include "internals/tables/TableKERN.h"
#include "internals/tables/TableGASP.h"
#include "internals/tables/TableGLYF.h"
#include "internals/tables/TableHHEA.h"
#include "internals/tables/TableHMTX.h"
#include "internals/tables/TableHDMX.h"

namespace OpenType {

    TableRecord::TableRecord() :
        calculated_checksum_(0) {

    }

    // expects reader to be in correct position to read
    void TableRecord::from_bytes( FontReader& reader ) {
        bof_offset_ = reader.get_position(); // save where this TableRecord begins
        auto type_reader = TypeReader( reader.get_bytes( get_info_size() ) );
        info_.table_tag = type_reader.readTag();
        info_.checksum = type_reader.readUInt32();
        info_.offset = type_reader.readOffset32();
        info_.length = type_reader.readUInt32();

        read_table_data( reader );
    }

    std::string TableRecord::get_tag() const {
        return info_.table_tag;
    }

    void TableRecord::read_table_data( FontReader const & reader) {
        internal_bytes_reader = TypeReader( reader.get_byte_sequence( info_.offset, info_.length ) );
        internal_bytes_reader.pad();
        calculated_length_ = internal_bytes_reader.size() - internal_bytes_reader.get_padding_size();
        calculated_checksum_ = internal_bytes_reader.get_checksum();
    }

    void TableRecord::get_data( const OffsetTable& offsetTable) {
        if ( info_.table_tag == DSIG ) {
            table_ptr_ = std::make_unique<TableDSIG>( internal_bytes_reader );
        } else if ( info_.table_tag == LTSH ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableLTSH>( internal_bytes_reader );
        } else if ( info_.table_tag == OS2 ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableOS2>( internal_bytes_reader );
        } else if ( info_.table_tag == VDMX ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableVDMX>( internal_bytes_reader );
        } else if ( info_.table_tag == CMAP ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableCMAP>( internal_bytes_reader );
        } else if ( info_.table_tag == CVT ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableCVT>( internal_bytes_reader );
        } else if ( info_.table_tag == FPGM ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableFPGM>( internal_bytes_reader );
        } else if ( info_.table_tag == GASP ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableGASP>( internal_bytes_reader );
        } else if ( info_.table_tag == MAXP ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableMAXP>( internal_bytes_reader );
        } else if ( info_.table_tag == PREP ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TablePREP>( internal_bytes_reader );
        } else if ( info_.table_tag == LOCA ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableLOCA>( internal_bytes_reader, offsetTable.get_table(HEAD).get_head()->index_to_loc_format() == TableHEAD::LONG_OFFSETS );
        } else if ( info_.table_tag == HEAD ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableHEAD>( internal_bytes_reader );
        } else if ( info_.table_tag == POST ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TablePOST>( internal_bytes_reader );
        } else if ( info_.table_tag == NAME ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableNAME>( internal_bytes_reader );
        } else if ( info_.table_tag == KERN ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableKERN>( internal_bytes_reader );
        } else if ( info_.table_tag == GLYF ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableGLYF>( internal_bytes_reader,
                            offsetTable.get_table(MAXP).get_maxp(),
                            offsetTable.get_table(LOCA).get_loca() );
        } else if ( info_.table_tag == HHEA ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableHHEA>( internal_bytes_reader );
        } else if ( info_.table_tag == HMTX ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableHMTX>( internal_bytes_reader,
                                        offsetTable.get_table(HHEA).get_hhea(),
                                        offsetTable.get_table(MAXP).get_maxp() );
        } else if ( info_.table_tag == HDMX ) {
            internal_bytes_reader.remove_padding();
            table_ptr_ = std::make_unique<TableHDMX>( internal_bytes_reader,
                                        offsetTable.get_table(MAXP).get_maxp()->get_num_glyphs()
                                        );
        }
    }

    AbstractTable* TableRecord::get_table() const {
        return table_ptr_.get();
    }

    TableDSIG* TableRecord::get_dsig() const {
        return dynamic_cast<TableDSIG*>(table_ptr_.get());
    };

    TableLTSH* TableRecord::get_ltsh() const {
        return dynamic_cast<TableLTSH*>(table_ptr_.get());
    };

    TableOS2* TableRecord::get_os2() const {
        return dynamic_cast<TableOS2*>(table_ptr_.get());
    };

    TableVDMX* TableRecord::get_vdmx() const {
        return dynamic_cast<TableVDMX*>(table_ptr_.get());
    };

    TableCMAP* TableRecord::get_cmap() const {
        return dynamic_cast<TableCMAP*>(table_ptr_.get());
    };

    TableCVT* TableRecord::get_cvt() const {
        return dynamic_cast<TableCVT*>(table_ptr_.get());
    };

    TableFPGM* TableRecord::get_fpgm() const {
        return dynamic_cast<TableFPGM*>(table_ptr_.get());
    };

    TableMAXP* TableRecord::get_maxp() const {
        return dynamic_cast<TableMAXP*>(table_ptr_.get());
    };

    TablePREP* TableRecord::get_prep() const {
        return dynamic_cast<TablePREP*>(table_ptr_.get());
    };

    TableLOCA* TableRecord::get_loca() const {
        return dynamic_cast<TableLOCA*>(table_ptr_.get());
    };

    TableHEAD* TableRecord::get_head() const {
        return dynamic_cast<TableHEAD*>(table_ptr_.get());
    };

    TablePOST* TableRecord::get_post() const {
        return dynamic_cast<TablePOST*>(table_ptr_.get());
    };

    TableNAME* TableRecord::get_name() const {
        return dynamic_cast<TableNAME*>(table_ptr_.get());
    };

    TableKERN* TableRecord::get_kern() const {
        return dynamic_cast<TableKERN*>(table_ptr_.get());
    };

    TableGASP* TableRecord::get_gasp() const {
        return dynamic_cast<TableGASP*>(table_ptr_.get());
    };

    TableGLYF* TableRecord::get_glyf() const {
        return dynamic_cast<TableGLYF*>(table_ptr_.get());
    };

    TableHHEA* TableRecord::get_hhea() const {
        return dynamic_cast<TableHHEA*>(table_ptr_.get());
    };

    TableHMTX* TableRecord::get_hmtx() const {
        return dynamic_cast<TableHMTX*>(table_ptr_.get());
    };

    TableHDMX* TableRecord::get_hdmx() const {
        return dynamic_cast<TableHDMX*>(table_ptr_.get());
    };

    std::ostream& operator<<( std::ostream& out, TableRecord const & table ) {
        out << "  " << "TableRecord{";
        out << table.info_.table_tag << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.checksum;
        if ( table.info_.checksum == table.calculated_checksum_ ) {
            out << " PASS,";
        } else {
            out << " (" << std::dec << table.info_.checksum << "/" << table.calculated_checksum_ << " " << table.calculated_checksum_ % 4 << "),";
        }
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.offset << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.info_.length << std::dec << "(" << table.info_.length << ")";
        if ( table.info_.length == table.calculated_length_ ) {
            out << " PASS";
        } else {
            out << " (" << std::dec << table.info_.length << "/" << table.calculated_length_ << ")";
        }
        out << "}";

        if ( table.table_ptr_ ) {
            out << std::endl;
            out << table.table_ptr_.get() << std::endl;
            // if ( table.info_.table_tag == DSIG ) {
            //     out << "    " << table.get_dsig() << std::endl;
            // } else if ( table.info_.table_tag == LTSH ) {
            //     out << "    " << table.get_ltsh() << std::endl;
            // } else if ( table.info_.table_tag == OS2 ) {
            //     out << "    " << table.get_os2() << std::endl;
            // } else if ( table.info_.table_tag == VDMX ) {
            //     out << "    " << table.get_vdmx() << std::endl;
            // } else if ( table.info_.table_tag == CMAP ) {
            //     out << "    " << table.get_cmap() << std::endl;
            // } else if ( table.info_.table_tag == CVT ) {
            //     out << "    " << table.get_cvt() << std::endl;
            // } else if ( table.info_.table_tag == FPGM ) {
            //     out << "    " << table.get_fpgm() << std::endl;
            // } else if ( table.info_.table_tag == MAXP ) {
            //     out << "    " << table.get_maxp() << std::endl;
            // } else if ( table.info_.table_tag == PREP ) {
            //     out << "    " << table.get_prep() << std::endl;
            // } else if ( table.info_.table_tag == LOCA ) {
            //     out << "    " << table.get_loca() << std::endl;
            // } else if ( table.info_.table_tag == HEAD ) {
            //     out << "    " << table.get_head() << std::endl;
            // } else if ( table.info_.table_tag == POST ) {
            //     out << "    " << table.get_post() << std::endl;
            // } else if ( table.info_.table_tag == NAME ) {
            //     out << "    " << table.get_name() << std::endl;
            // } else if ( table.info_.table_tag == KERN ) {
            //     out << "    " << table.get_kern() << std::endl;
            // } else if ( table.info_.table_tag == GASP ) {
            //     out << "    " << table.get_gasp() << std::endl;
            // } else if ( table.info_.table_tag == GLYF ) {
            //     out << "    " << table.get_glyf() << std::endl;
            // } else if ( table.info_.table_tag == HHEA ) {
            //     out << "    " << table.get_glyf() << std::endl;
            // } else {
            //     out << "    " << "Table format not recognised." << std::endl;
            // }
        }
        return out;
    }

    std::ostream& operator<<( std::ostream& out, TableRecord const * table ) {
        out << *table;
        return out;
    }
}
