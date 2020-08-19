#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableGASP.h"

namespace OpenType {

    TableGASP::TableGASP(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_ranges_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableGASP::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        num_ranges_ = type_reader.readUInt16();

        for( int ii=0; ii < num_ranges_; ii++ ) {
            auto gasp_range = GaspRange {};
            gasp_range.range_max_ppem = type_reader.readUInt16();
            gasp_range.range_gasp_behaviour = type_reader.readUInt16();
            ranges_.push_back( gasp_range );
        }
    }

    // @Override
    void TableGASP::print(std::ostream& out) const {
        out << "GASP{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << version_ << ",";
        out << std::dec;
        out << num_ranges_ << ",";
        for( auto gr : ranges_ ) {
            out << "(" << gr.range_max_ppem << "," <<
                gr.range_gasp_behaviour << ")";
        }
        out << "}";
        out << std::endl;
    }
}
