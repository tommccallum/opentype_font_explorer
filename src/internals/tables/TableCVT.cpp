#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableCVT.h"

namespace OpenType {

    TableCVT::TableCVT(TypeReader type_reader) :
        AbstractTable()
    {
        from_bytes( type_reader );
    }

    void TableCVT::from_bytes( TypeReader& type_reader ) {
        control_values_ = type_reader.readFWordVector();
    }

    // @Override
    void TableCVT::print(std::ostream& out) const {
        out << std::dec;
        out << "CVT{";
        size_t n = control_values_.size();
        size_t ii=0;
        for( auto cv : control_values_ ) {
            out << cv ;
            if ( ii < n-1 ) out << ",";
            ii++;
        }
        out << "}";
        //out << std::endl;
    }


}
