#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/SignatureBlockFormat1.h"
#include "internals/TypeReader.h"
#include "internals/FontReader.h"

namespace OpenType {

    SignatureBlockFormat1::SignatureBlockFormat1( TypeReader type_reader) :
        reserved1_(0), reserved2_(0), length_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void SignatureBlockFormat1::from_bytes( TypeReader& type_reader ) {
        reserved1_ = type_reader.readUInt16();
        reserved2_ = type_reader.readUInt16();

        // both of these should be set to zero
        // @see https://docs.microsoft.com/en-gb/typography/opentype/spec/dsig
        assert( reserved1_ == 0x0 );
        assert( reserved2_ == 0x0 );

        length_ = type_reader.readUInt32();

        signature_ = type_reader.readCharVector();
        assert( signature_.size() == length_ );
    }

    std::ostream& operator<<( std::ostream& out, const SignatureBlockFormat1& table ) {
        out << "SignatureBlockFormat1{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.reserved1_ << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << table.reserved2_ << ",";
        out << std::dec << table.length_;
        out << "}";
        return out;
    }
}
