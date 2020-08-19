#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableLTSH.h"

namespace OpenType {

    TableLTSH::TableLTSH(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_glyphs_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableLTSH::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        num_glyphs_ = type_reader.readUInt16();
        // rest of this table block should be y_pels
        y_pels_ = type_reader.readCharVector();
        //assert( y_pels_.size() == num_glyphs_ );
    }

    // @Override
    void TableLTSH::print(std::ostream& out) const {
        out << "LTSH{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << version_ << ",";
        if ( num_glyphs_ == y_pels_.size() ) {
            out << std::dec << num_glyphs_ << " PASS" << ",";
        } else {
            out << std::dec << num_glyphs_ << " (" << y_pels_.size() << "),";
        }
        out << "ypel";
        for( auto y_pel : y_pels_ ) {
            out << ",";
            out << int(y_pel) ;
        }
        out << "}";
        out << std::endl;
    }

}
