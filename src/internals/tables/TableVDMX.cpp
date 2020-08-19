#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableVDMX.h"

namespace OpenType {

    TableVDMX::TableVDMX(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_vdmx_groups_(0),
        num_ratio_groups_(0)
    {
        from_bytes( type_reader );
    }

    void TableVDMX::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        num_vdmx_groups_ = type_reader.readUInt16();
        num_ratio_groups_ = type_reader.readUInt16();

        for( size_t ii=0; ii < num_ratio_groups_; ii++ ) {
            auto rr = RatioRange();
            rr.b_char_set = type_reader.readUInt8();
            rr.x_ratio = type_reader.readUInt8();
            rr.y_start_ratio = type_reader.readUInt8();
            rr.y_end_ratio = type_reader.readUInt8();
            ratio_ranges_.push_back( std::move( rr ) );
        }
        for( size_t ii=0; ii < num_ratio_groups_; ii++ ) {
            offsets_.push_back(type_reader.readOffset16());
        }

        // VDMX groups immediately follow this header so we should be on point
        // to continue reading the groups
        for( size_t ii =0; ii < num_vdmx_groups_; ii++ ) {
            auto group = VDMXGroup();
            group.height_records = type_reader.readUInt16();
            group.start_sz = type_reader.readUInt8();
            group.end_sz = type_reader.readUInt8();
            for( size_t jj=0; jj < group.height_records; jj++ ) {
                auto vtable = vTableRecord { type_reader.readUInt16(),
                                             type_reader.readInt16() ,
                                             type_reader.readInt16()  };
                group.vdmx_records.push_back( std::move(vtable) );
            }
            vdmx_groups_.push_back( std::move( group ) );
        }
    }

    // @Override
    void TableVDMX::print(std::ostream& out) const {
        out << std::dec << "VDMX{";
        out << version_ << ",";
        out << num_vdmx_groups_ << ",";
        out << num_ratio_groups_ << " ";

        for( auto rr : ratio_ranges_ ) {
            out << "(";
            out << int(rr.b_char_set) << ",";
            out << int(rr.x_ratio) << ",";
            out << int(rr.y_start_ratio) << ",";
            out << int(rr.y_end_ratio);
            out << ")";
        }

        out << "(";
        size_t ii=0;
        for( auto rr : offsets_ ) {
            out << int(rr);
            if ( ii < offsets_.size() - 1 ) {
                out << ",";
            }
            ii++;
        }
        out << ")";

        out << "}";
        out << std::endl;

        for( auto vdmx : vdmx_groups_ ) {
            out << "VMDXGroup{";
            out << vdmx.height_records << ",";
            out << int(vdmx.start_sz) << ",";
            out << int(vdmx.end_sz) << ",";
            out << "(";
            for( size_t ii =0; ii < vdmx.vdmx_records.size(); ii++ ) {
                out << "(" << vdmx.vdmx_records[ii].y_pel_height << "," << vdmx.vdmx_records[ii].y_max << "," << vdmx.vdmx_records[ii].y_min << ")";
                if ( ii < vdmx.vdmx_records.size()-1) out << ",";
            }
            out << ")";
            out << "}";
            out << std::endl;
        }

    }

}
