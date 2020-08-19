#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TablePREP.h"

namespace OpenType {

    TablePREP::TablePREP(TypeReader type_reader) :
        AbstractTable()
    {
        from_bytes( type_reader );
    }

    void TablePREP::from_bytes( TypeReader& type_reader ) {
        control_values_ = type_reader.readUInt8Vector();
    }

    // @Override
    void TablePREP::print(std::ostream& out) const {
        out << std::dec;
        out << "PREP{";
        size_t n = control_values_.size();
        size_t ii=0;
        for( auto cv : control_values_ ) {
            out << int(cv) ;
            if ( ii < n-1 ) out << ",";
            ii++;
        }
        out << "}";
        //out << std::endl;
    }

}
