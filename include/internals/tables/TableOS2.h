#ifndef TABLE_OS2_H
#define TABLE_OS2_H

#include <iostream>
#include <vector>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {

    class TypeReader;

    // class name matches the tag of the table
    class TableOS2 : public AbstractTable {
    public:
        TableOS2( TypeReader type_reader );

        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_; // 1-4
        OT_INT16 x_avg_char_width_;
        OT_UINT16 us_weight_class_;
        OT_UINT16 us_width_class_;
        OT_UINT16 fs_type_;
        OT_INT16 y_subscript_x_size_;
        OT_INT16 y_subscript_y_size_;
        OT_INT16 y_subscript_x_offset_;
        OT_INT16 y_subscript_y_offset_;
        OT_INT16 y_superscript_x_size_;
        OT_INT16 y_superscript_y_size_;
        OT_INT16 y_superscript_x_offset_;
        OT_INT16 y_superscript_y_offset_;
        OT_INT16 y_strikeout_size_;
        OT_INT16 y_strikeout_position_;
        OT_INT16 s_family_class_;
        std::vector<char> panose_; // 10 bytes
        OT_UINT32 ul_unicode_range_1_;
        OT_UINT32 ul_unicode_range_2_;
        OT_UINT32 ul_unicode_range_3_;
        OT_UINT32 ul_unicode_range_4_;
        std::string ach_vend_id_; // 4 bytes (TAG)
        OT_UINT16 fs_selection_;
        OT_UINT16 us_first_char_index_;
        OT_UINT16 us_last_char_index_;
        // end of version 0 (Macintosh)
        OT_INT16 s_typo_ascender_;
        OT_INT16 s_typo_descender_;
        OT_INT16 s_typo_line_gap_;
        OT_UINT16 us_win_ascent_;
        OT_UINT16 us_win_descent_;
        // end of version 0 (Windows)
        OT_UINT32 ul_code_page_range_1_;
        OT_UINT32 ul_code_page_range_2_;
        // end of version 1,2,3
        OT_INT16 sx_height_;
        OT_INT16 s_cap_height_;
        OT_INT16 us_default_char_;
        OT_INT16 us_break_char_;
        OT_INT16 us_max_context_;
        // end of version 4
        OT_INT16 us_lower_optical_point_size_;
        OT_INT16 us_upper_optical_point_size_;
        // end of version 5



        void from_bytes( TypeReader& type_reader );

    };
}

#endif // TABLE_OS2_H
