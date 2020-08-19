#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableHHEA.h"

namespace OpenType {

    TableHHEA::TableHHEA(TypeReader type_reader) :
        AbstractTable(),
        major_version_(0),
        minor_version_(0),
        ascender_(0),
        descender_(0),
        line_gap_(0),
        advance_width_max_(0),
        min_left_side_bearing_(0),
        min_right_side_bearing_(0),
        x_max_extent_(0),
        caret_slope_rise_(0),
        caret_slope_run_(0),
        caret_offset_(0),
        reserved1_(0),
        reserved2_(0),
        reserved3_(0),
        reserved4_(0),
        metric_data_format_(0),
        number_of_h_metrics_(0)
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableHHEA::from_bytes( TypeReader& type_reader ) {
        major_version_= type_reader.readUInt16();
        minor_version_= type_reader.readUInt16();
        ascender_= type_reader.readFWORD();
        descender_= type_reader.readFWORD();
        line_gap_= type_reader.readFWORD();
        advance_width_max_= type_reader.readUFWORD();
        min_left_side_bearing_= type_reader.readFWORD();
        min_right_side_bearing_= type_reader.readFWORD();
        x_max_extent_= type_reader.readFWORD();
        caret_slope_rise_= type_reader.readInt16();
        caret_slope_run_= type_reader.readInt16();
        caret_offset_= type_reader.readInt16();
        reserved1_= type_reader.readInt16();
        reserved2_= type_reader.readInt16();
        reserved3_= type_reader.readInt16();
        reserved4_= type_reader.readInt16();
        metric_data_format_= type_reader.readInt16();
        number_of_h_metrics_= type_reader.readUInt16();
    }

    OT_UINT16 TableHHEA::get_number_of_h_metrics() const {
        return number_of_h_metrics_;
    }

    // @Override
    void TableHHEA::print(std::ostream& out) const {
        out << "HHEA{";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << major_version_ << ",";
        out << "0x" << std::setfill('0') << std::setw(8) << std::hex << minor_version_ << ",";
        out << std::dec;
        out << ascender_ << ",";
        out << descender_ << ",";
        out << line_gap_ << ",";
        out << advance_width_max_ << ",";
        out << min_left_side_bearing_ << ",";
        out << min_right_side_bearing_ << ",";
        out << x_max_extent_ << ",";
        out << caret_slope_rise_ << ",";
        out << caret_slope_run_ << ",";
        out << caret_offset_ << ",";
        out << reserved1_ << ",";
        out << reserved2_ << ",";
        out << reserved3_ << ",";
        out << reserved4_ << ",";
        out << metric_data_format_ << ",";
        out << number_of_h_metrics_ ;
        out << "}";
        out << std::endl;
    }

}
