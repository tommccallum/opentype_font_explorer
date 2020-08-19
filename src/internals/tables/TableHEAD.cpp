#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>
#include <chrono>
#include <ctime>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableHEAD.h"

namespace OpenType {

    TableHEAD::TableHEAD(TypeReader type_reader) :
        AbstractTable(),
        major_version_(0),
        minor_version_(0),
        font_revision_(0),
        check_sum_adjustment_(0),
        magic_number_(0),
        flags_(0),
        units_per_em_(0),
        created_(0),
        modified_(0),
        x_min_(0),
        y_min_(0),
        x_max_(0),
        y_max_(0),
        mac_style_(0),
        lowest_rec_ppem_(0),
        font_direction_hint_(0),
        index_to_loc_format_(TableHEAD::SHORT_OFFSETS),
        glyph_data_format_(0)
    {
        from_bytes( type_reader );
    }

    void TableHEAD::from_bytes( TypeReader& type_reader ) {
        major_version_ = type_reader.readUInt16();
        minor_version_ = type_reader.readUInt16();
        font_revision_ = type_reader.readFixed();
        check_sum_adjustment_ = type_reader.readUInt32();
        magic_number_ =  type_reader.readUInt32();
        assert( magic_number_ == 0x5F0F3CF5 );
        flags_ =  type_reader.readUInt16();
        units_per_em_ =  type_reader.readUInt16();
        created_ = type_reader.readLongDateTime();
        modified_ = type_reader.readLongDateTime();
        x_min_ = type_reader.readInt16();
        y_min_ = type_reader.readInt16();
        x_max_ = type_reader.readInt16();
        y_max_ = type_reader.readInt16();
        mac_style_ = type_reader.readUInt16();
        lowest_rec_ppem_ = type_reader.readUInt16();
        font_direction_hint_ = type_reader.readInt16();
        OT_UINT16 indexToLocFormat = type_reader.readInt16();
        if ( indexToLocFormat == 0x1 ) {
            index_to_loc_format_ = LONG_OFFSETS;
        } else {
            index_to_loc_format_ = SHORT_OFFSETS;
        }
        glyph_data_format_ = type_reader.readInt16();
    }

    TableHEAD::IndexToLocFormat TableHEAD::index_to_loc_format() {
        return index_to_loc_format_;
    }

    // @Override
    void TableHEAD::print(std::ostream& out) const {
        out << std::dec;
        out << "HEAD{";
        out << major_version_ << ",";
        out << minor_version_ << ",";
        out << font_revision_ << ",";
        out << check_sum_adjustment_ << ",";
        out << "0x" << std::hex << magic_number_ << std::dec << ",";
        out << flags_ << ",";
        out << units_per_em_ << ",";
        auto const tp_epoch = std::chrono::system_clock::time_point{};
        auto const tp_media_epoch = tp_epoch + std::chrono::seconds(-2082844800); // add seconds until 1904-01-01 00:00
        //auto const tp = std::chrono::time_point<std::chrono::system_clock>{};
        auto const tp_created = tp_media_epoch + std::chrono::seconds(created_);
        auto const tp_modified = tp_media_epoch + std::chrono::seconds(modified_);
        auto created_posix = std::chrono::system_clock::to_time_t(tp_created);
        out << std::put_time(std::localtime(&created_posix), "%Y-%m-%d %X") << ",";
        auto modified_posix = std::chrono::system_clock::to_time_t(tp_modified);
        out << std::put_time(std::localtime(&modified_posix), "%Y-%m-%d %X") << ",";
        out << x_min_ << ",";
        out << y_min_ << ",";
        out << x_max_ << ",";
        out << y_max_ << ",";
        out << mac_style_ << ",";
        out << lowest_rec_ppem_ << ",";
        out << font_direction_hint_ << ",";
        out << index_to_loc_format_ << ",";
        out << glyph_data_format_;
        out << "}";
    }


}
