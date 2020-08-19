#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/SignatureRecord.h"
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/SignatureBlockFormat1.h"

namespace OpenType {

    SignatureRecord::SignatureRecord() :
        format_(0), length_(0), offset_(0)
    {

    }

    // expects reader to be in correct position to read
    void SignatureRecord::from_bytes( TypeReader& type_reader ) {
        format_ = type_reader.readUInt32();
        length_ = type_reader.readUInt32();
        offset_ = type_reader.readOffset32();

        // typereader should have all the bytes for this table so we can index
        // directly into this
        TypeReader sig_block_reader = type_reader.get_byte_sequence( offset_, length_ );
        assert( sig_block_reader.size() == length_ );

        // currently only 1 format exists
        // if this were to change then we want to fail and report
        // @see https://docs.microsoft.com/en-gb/typography/opentype/spec/dsig

        // create new signature block with contains the PKCS#7 packets
        auto block = SignatureBlockFormat1( sig_block_reader );
        signatures_.push_back( std::move( block ) );
    }

    std::ostream& operator<<( std::ostream& out, const SignatureRecord& table ) {
        out << "SignatureRecord{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.format_ << ",";
        out << std::dec << table.length_ << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.offset_ ;
        out << "}";
        out << std::endl;
        for( auto signature : table.signatures_ ) {
            out << "            " << signature << std::endl;
        }
        return out;
    }
}
