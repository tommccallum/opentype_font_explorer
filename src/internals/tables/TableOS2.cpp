#include <iostream>
#include <iomanip>
#include <cassert>
#include "internals/TypeReader.h"
#include "internals/FontReader.h"
#include "internals/tables/TableOS2.h"

namespace OpenType {

    TableOS2::TableOS2(TypeReader type_reader) :
        AbstractTable(),
        version_(0), // 1-4
        x_avg_char_width_(0),
        us_weight_class_(0),
        us_width_class_(0),
        fs_type_(0),
        y_subscript_x_size_(0),
        y_subscript_y_size_(0),
        y_subscript_x_offset_(0),
        y_subscript_y_offset_(0),
        y_superscript_x_size_(0),
        y_superscript_y_size_(0),
        y_superscript_x_offset_(0),
        y_superscript_y_offset_(0),
        y_strikeout_size_(0),
        y_strikeout_position_(0),
        s_family_class_(0),
        ul_unicode_range_1_(0),
        ul_unicode_range_2_(0),
        ul_unicode_range_3_(0),
        ul_unicode_range_4_(0),
        ach_vend_id_(""), // 4 bytes (TAG)
        fs_selection_(0),
        us_first_char_index_(0),
        us_last_char_index_(0),
        // end of version 0 (Macintosh)
        s_typo_ascender_(0),
        s_typo_descender_(0),
        s_typo_line_gap_(0),
        us_win_ascent_(0),
        us_win_descent_(0),
        // end of version 0 (Windows)
        ul_code_page_range_1_(0),
        ul_code_page_range_2_(0),
        // end of version 1,2,3
        sx_height_(0),
        s_cap_height_(0),
        us_default_char_(0),
        us_break_char_(0),
        us_max_context_(0),
        // end of version 4
        us_lower_optical_point_size_(0),
        us_upper_optical_point_size_(0)
        // end of version 5
    {
        from_bytes( type_reader );
    }

    // expects reader to be in correct position to read
    void TableOS2::from_bytes( TypeReader& type_reader ) {
        version_ = type_reader.readUInt16();
        x_avg_char_width_ = type_reader.readInt16();
        us_weight_class_ = type_reader.readUInt16();
        us_width_class_ = type_reader.readUInt16();
        fs_type_ = type_reader.readUInt16();
        y_subscript_x_size_ = type_reader.readInt16();
        y_subscript_y_size_ = type_reader.readInt16();
        y_subscript_x_offset_ = type_reader.readInt16();
        y_subscript_y_offset_ = type_reader.readInt16();
        y_superscript_x_size_ = type_reader.readInt16();
        y_superscript_y_size_ = type_reader.readInt16();
        y_superscript_x_offset_ = type_reader.readInt16();
        y_superscript_y_offset_ = type_reader.readInt16();
        y_strikeout_size_ = type_reader.readInt16();
        y_strikeout_position_ = type_reader.readInt16();
        s_family_class_ = type_reader.readInt16();

        // read 10 char/bytes
        panose_ = type_reader.readChar(10);

        ul_unicode_range_1_ = type_reader.readUInt32();
        ul_unicode_range_2_ = type_reader.readUInt32();
        ul_unicode_range_3_ = type_reader.readUInt32();
        ul_unicode_range_4_ = type_reader.readUInt32();
        ach_vend_id_ = type_reader.readTag(), // 4 bytes (TAG)
        fs_selection_ = type_reader.readUInt16();
        us_first_char_index_ = type_reader.readUInt16();
        us_last_char_index_ = type_reader.readUInt16();
        // end of version 0 (Macintosh)
        s_typo_ascender_ = type_reader.readInt16();
        s_typo_descender_ = type_reader.readInt16();
        s_typo_line_gap_ = type_reader.readInt16();
        us_win_ascent_ = type_reader.readUInt16();
        us_win_descent_ = type_reader.readUInt16();
        // end of version 0 (Windows)
        if ( version_ > 0 ) {
            ul_code_page_range_1_ = type_reader.readUInt32();
            ul_code_page_range_2_ = type_reader.readUInt32();
            // end of version 1,2,3
        }
        if ( version_ > 3 ) {
            sx_height_ = type_reader.readInt16();
            s_cap_height_ = type_reader.readInt16();
            us_default_char_ = type_reader.readInt16();
            us_break_char_ = type_reader.readInt16();
            us_max_context_ = type_reader.readInt16();
            // end of version 4
        }
        if ( version_ > 4 ) {
            us_lower_optical_point_size_ = type_reader.readInt16();
            us_upper_optical_point_size_ = type_reader.readInt16();
            // end of version 5
        }
    }

    // @Override
    void TableOS2::print(std::ostream& out) const {
        out << "OS2{" << std::endl;
        out << std::dec;
        out << "Version: " << version_ << std::endl;
        out << "xAvgCharWidth: " <<  x_avg_char_width_ << std::endl;
        out << "usWeightClass: " << us_weight_class_ << std::endl;
        out << "usWidthClass: " << us_width_class_ << std::endl;
        out << "fsType: "<< fs_type_ << std::endl;
        out << "ySubscript(x,y)Size: " << y_subscript_x_size_ << ",";
        out << y_subscript_y_size_ << std::endl;
        out << "ySubscript(x,y)Offset: " << y_subscript_x_offset_ << ",";
        out << y_subscript_y_offset_ << std::endl;
        out << "ySuperscript(x,y)Size: " << y_superscript_x_size_ << ",";
        out << y_superscript_y_size_ << std::endl;
        out << "ySuperscript(x,y)Offset: " << y_superscript_x_offset_ << ",";
        out << y_superscript_y_offset_ << std::endl;

        out << "yStrikeoutSize: " << y_strikeout_size_ << std::endl;
        out << "yStrikeoutPosition: " << y_strikeout_position_ << std::endl;
        out << "sFamilyClass: " << s_family_class_ << std::endl;

        out << "panose: ";
        size_t ii = 0;
        for( auto ch : panose_ ) {
            out << int(ch);
            if ( ii < 9 ) out << ",";
            ii++;
        }
        out << std::endl;

        out << "ulUnicodeRange(1-4): " << ul_unicode_range_1_ << ",";
        out << ul_unicode_range_2_ << ",";
        out << ul_unicode_range_3_ << ",";
        out << ul_unicode_range_4_ << std::endl;

        out << "achVendId: " << ach_vend_id_ << std::endl;

        out << "fsSelection: " << fs_selection_ << std::endl;
        out << "us(First/Last)CharIndex: " << us_first_char_index_ << ",";
        out << us_last_char_index_ << std::endl;
        // end of version 0 (Macintosh)
        out << "sTypo(A/Desc)scender: " << s_typo_ascender_ << ",";
        out << s_typo_descender_ << std::endl;

        out << "sTypoLineGap: " << s_typo_line_gap_ << std::endl;
        out << "usWin(A/De)scent: " <<  us_win_ascent_ << ",";
        out << us_win_descent_ << std::endl;
        // end of version 0 (Windows)

        out << "ulCodePageRange(1/2): " << ul_code_page_range_1_ << ",";
        out << ul_code_page_range_2_ << std::endl;
        // end of version 1,2,3

        out << "sxHeight: " << sx_height_ << std::endl;
        out << "sCapHeight: " << s_cap_height_ << std::endl;
        out << "usDefaultChar: " << us_default_char_ << std::endl;
        out << "usBreakChar: " << us_break_char_ << std::endl;
        out << "usMaxContext: " << us_max_context_ << std::endl;
        // end of version 4

        out << "us(Lower/Upper)OpticalPointSize: " << us_lower_optical_point_size_ << ",";
        out << us_upper_optical_point_size_ << std::endl;
        // end of version 5

        out << "}";
        out << std::endl;
    }

}
