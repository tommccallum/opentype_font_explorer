#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableHDMX.h"

namespace OpenType {

    TableHDMX::TableHDMX(TypeReader type_reader, OT_UINT16 num_glyphs) :
        AbstractTable(),
        version_(0),
        num_records_(0),
        size_device_record_(0),
        num_glyphs_(num_glyphs)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableHDMX::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        num_records_ = type_reader.readInt16();
        size_device_record_ = type_reader.readInt32();

        for( int ii=0; ii < num_records_; ii++ ) {
            auto device = DeviceRecord {};
            device.pixel_size = type_reader.readUInt8();
            device.max_width = type_reader.readUInt8();
            for( int jj=0; jj < num_glyphs_; jj++ ) {
                device.widths.push_back( type_reader.readUInt8() );
            }
            device_records_.push_back( std::move( device ) );
        }
    }

    // @Override
    void TableHDMX::print(std::ostream& out) const {
        out << "HDMX{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << version_ << ",";
        out << std::dec;
        out << num_records_ << ",";
        out << size_device_record_ << ",";
        out << "(";
        size_t ii=0;
        for( auto dev : device_records_ ) {
            out << "{" << int(dev.pixel_size) << "," << int(dev.max_width) << ",(";
            size_t jj=0;
            for( auto w : dev.widths ) {
                out << int(w);
                if ( jj < dev.widths.size() -1 ) out << ",";
            }
            out << ")";
            if ( ii < device_records_.size() - 1 ) out << ",";
        }
        out << ")";
        out << "}";
        out << std::endl;
    }

}
