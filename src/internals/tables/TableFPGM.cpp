#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableFPGM.h"

namespace OpenType {

    TableFPGM::TableFPGM(TypeReader type_reader) :
        AbstractTable()
    {
        from_bytes( type_reader );
    }

    void TableFPGM::from_bytes( TypeReader& type_reader ) {
        control_values_ = type_reader.readUInt8Vector();
    }

    // @Override
    void TableFPGM::print(std::ostream& out) const {
        out << std::dec;
        out << "FPGM{";
        size_t n = control_values_.size();
        size_t ii=0;
        for( auto cv : control_values_ ) {
            out << int(cv) ;
            if ( ii < n-1 ) out << ",";
            ii++;
        }
        out << "}";
    }


}
