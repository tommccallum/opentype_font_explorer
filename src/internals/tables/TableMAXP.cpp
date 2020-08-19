#include <iostream>
#include <iomanip>
#include <cassert>
#include <stdexcept>

#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableMAXP.h"

namespace OpenType {

    TableMAXP::TableMAXP(TypeReader type_reader) :
        AbstractTable(),
        version_(0),
        num_glyphs_(0),
        // end of version 0.5
        max_points_(0),
        max_contours_(0),
        max_composite_points_(0),
        max_composite_contours_(0),
        max_zones_(0),
        max_twilight_points_(0),
        max_storage_(0),
        max_function_defs_(0),
        max_instruction_defs_(0),
        max_stack_elements_(0),
        max_size_of_instructions_(0),
        max_component_elements_(0),
        max_component_depth_(0)
    {
        from_bytes( type_reader );
    }

    OT_UINT16 TableMAXP::get_num_glyphs() const {
        return num_glyphs_;
    }
    OT_UINT16 TableMAXP::get_max_points() const {
        return max_points_;
    }
    OT_UINT16 TableMAXP::get_max_contours() const {
        return max_contours_;
    }
    OT_UINT16 TableMAXP::get_max_size_of_instructions() const {
        return max_size_of_instructions_;
    }

    void TableMAXP::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readFixed();
        num_glyphs_ = type_reader.readUInt16();
        if ( version_ == 0x10000 ) {
            max_points_ = type_reader.readUInt16();
            max_contours_ = type_reader.readUInt16();
            max_composite_points_ = type_reader.readUInt16();
            max_composite_contours_ = type_reader.readUInt16();
            max_zones_ = type_reader.readUInt16();
            max_twilight_points_ = type_reader.readUInt16();
            max_storage_ = type_reader.readUInt16();
            max_function_defs_ = type_reader.readUInt16();
            max_instruction_defs_ = type_reader.readUInt16();
            max_stack_elements_ = type_reader.readUInt16();
            max_size_of_instructions_ = type_reader.readUInt16();
            max_component_elements_ = type_reader.readUInt16();
            max_component_depth_ = type_reader.readUInt16();
        }
    }

    // @Override
    void TableMAXP::print(std::ostream& out) const {
        out << std::dec;
        out << "MAXP{";
        out << "0x" << std::hex << version_ << ",";
        out << std::dec;
        out << num_glyphs_ << ",";
        out << max_points_ << ",";
        out << max_contours_ << ",";
        out << max_composite_points_ << ",";
        out << max_composite_contours_ << ",";
        out << max_zones_ << ",";
        out << max_twilight_points_ << ",";
        out << max_storage_ << ",";
        out << max_function_defs_ << ",";
        out << max_instruction_defs_ << ",";
        out << max_stack_elements_ << ",";
        out << max_size_of_instructions_ << ",";
        out << max_component_elements_ << ",";
        out << max_component_depth_ ;
        out << "}";
        //out << std::endl;
    }

}
