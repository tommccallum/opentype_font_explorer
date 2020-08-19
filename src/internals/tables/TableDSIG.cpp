#include <iostream>
#include <iomanip>
#include "internals/SignatureRecord.h"
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableDSIG.h"

namespace OpenType {

    TableDSIG::TableDSIG(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_signatures_(0),
        flags_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableDSIG::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt32();
        num_signatures_ = type_reader.readUInt16();
        flags_ = type_reader.readUInt16();

        // read in signature blocks
        for( size_t ii = 0; ii < num_signatures_; ii++ ) {
            auto signature = SignatureRecord();
            signature.from_bytes( type_reader );
            signature_records_.push_back( std::move( signature) );
        }
    }

    // @Override
    void TableDSIG::print(std::ostream& out) const {
        out << "DSIG{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << version_ << ",";
        if ( num_signatures_ == signature_records_.size() ) {
            out << std::dec << num_signatures_ << " PASS" << ",";
        } else {
            out << std::dec << num_signatures_ << " (" << signature_records_.size() << "),";
        }
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << flags_;
        out << "}";
        out << std::endl;
        size_t ii = 0;
        for( auto signature : signature_records_ ) {
            out << "      " << "[" << ii << "] " ;
            out << signature << std::endl;
            ii++;
        }
    }


}
