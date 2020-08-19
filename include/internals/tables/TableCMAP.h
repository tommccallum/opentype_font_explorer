#ifndef TABLE_CMAP_H
#define TABLE_CMAP_H

#include <vector>
#include <iostream>
#include "internals/InternalTypes.h"
#include "internals/AbstractTable.h"

namespace OpenType {
    class TypeReader;

    class TableCMAP : public AbstractTable {
    public:
        // there are many formats that this table can take
        // all related structures are held within this class.
        // We select based on the platform_id matching to
        // our enums in OpenType.h

        // code to identify which format structure we are using
        enum PlatformEncodingFormat {
                PLATFORM_ENCODING_FORMAT_NONE=-1,
                PLATFORM_ENCODING_FORMAT_0=0,
                PLATFORM_ENCODING_FORMAT_2=2,
                PLATFORM_ENCODING_FORMAT_4=4,
                PLATFORM_ENCODING_FORMAT_8=8,
                PLATFORM_ENCODING_FORMAT_10=10,
                PLATFORM_ENCODING_FORMAT_12=12,
                PLATFORM_ENCODING_FORMAT_13=13,
                PLATFORM_ENCODING_FORMAT_14=14
        };

        // an empty base class
        struct AbstractPlatformEncodingFormat {
            virtual ~AbstractPlatformEncodingFormat();
        };

        struct EncodingRecord {
            OT_UINT16 platform_id;
            OT_UINT16 encoding_id;
            OT_OFFSET32 offset;
        };

        struct ByteEncodingFormat0 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 length;
            OT_UINT16 language;
            std::vector<char> glyph_ids; // map character codes to glyph index
        };

        struct SubHeader {
            OT_UINT16 first_code;
            OT_UINT16 entry_count;
            OT_INT16 id_delta;
            OT_UINT16 id_range_offset;
        };

        struct ByteEncodingFormat2 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 length;
            OT_UINT16 language;
            std::vector<OT_UINT16> sub_header_keys;//256
            std::vector<SubHeader> sub_headers;
            std::vector<OT_UINT16> glyph_ids; // map character codes to glyph index
        };

        struct ByteEncodingFormat4 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 length;
            OT_UINT16 language;
            OT_UINT16 seg_count_x2;
            OT_UINT16 search_range;
            OT_UINT16 entry_selector;
            OT_UINT16 range_shift;
            std::vector<OT_UINT16> end_codes;
            OT_UINT16 reserved_pad;
            std::vector<OT_UINT16> start_codes;
            std::vector<OT_INT16> id_deltas;
            std::vector<OT_UINT16> id_range_offsets;
            std::vector<OT_UINT16> glyph_ids;
        };

        struct ByteEncodingFormat6 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 length;
            OT_UINT16 language;
            OT_UINT16 first_code;
            OT_UINT16 entry_count;
            std::vector<OT_UINT16> glyph_ids;
        };

        struct SequentialMapGroup {
            OT_UINT32 start_char_code;
            OT_UINT32 end_char_code;
            OT_UINT32 start_glyph_id;
        };

        struct ByteEncodingFormat8 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 reserved;
            OT_UINT32 length;
            OT_UINT32 language;
            std::vector<OT_UINT8> is32; // 8192 long
            OT_UINT32 num_groups;
            std::vector<SequentialMapGroup> groups;
        };

        struct ByteEncodingFormat10 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 reserved;
            OT_UINT32 length;
            OT_UINT32 language;
            OT_UINT32 start_char_code;
            OT_UINT32 num_chars;
            std::vector<OT_UINT16> glyph_ids;
        };

        struct ByteEncodingFormat12 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 reserved;
            OT_UINT32 length;
            OT_UINT32 language;
            OT_UINT32 num_groups;
            std::vector<SequentialMapGroup> groups;
        };

        struct ConstantMapGroup {
            OT_UINT32 start_char_code;
            OT_UINT32 end_char_code;
            OT_UINT32 glyph_id;
        };

        struct ByteEncodingFormat13 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT16 reserved;
            OT_UINT32 length;
            OT_UINT32 language;
            OT_UINT32 num_groups;
            std::vector<ConstantMapGroup> groups;
        };

        struct VariationSelector {
            OT_UINT24 var_selector;
            OT_OFFSET32 default_uvs_offset;
            OT_OFFSET32 non_default_uvs_offset;
        };

        struct ByteEncodingFormat14 : public AbstractPlatformEncodingFormat {
            OT_UINT16 format;
            OT_UINT32 length;
            OT_UINT32 num_var_selector_records;
            std::vector<VariationSelector> var_selectors;
        };

        struct UnicodeRange {
            OT_UINT24 start_unicode_value;
            OT_UINT8 additional_count;
        };

        struct DefaultUVSTable {
            OT_UINT32 num_unicode_value_ranges;
            std::vector<UnicodeRange> ranges;
        };

        struct UVSMapping {
            OT_UINT24 start_unicode_value;
            OT_UINT16 glyph_id;
        };

        struct NonDefaultUVSTable {
            OT_UINT32 num_unicode_value_ranges;
            std::vector<UVSMapping> ranges;
        };

        // end of format structures


        TableCMAP( TypeReader type_reader );
        PlatformEncodingFormat get_format_type(size_t index);
        ByteEncodingFormat0* get_format_0(size_t index);
        ByteEncodingFormat2* get_format_2(size_t index);
        ByteEncodingFormat4* get_format_4(size_t index);
        ByteEncodingFormat8* get_format_8(size_t index);
        ByteEncodingFormat10* get_format_10(size_t index);
        ByteEncodingFormat12* get_format_12(size_t index);
        ByteEncodingFormat13* get_format_13(size_t index);
        ByteEncodingFormat14* get_format_14(size_t index);

        OT_UINT16 get_glyph_index(int encoding_index, int character_code);
        void print(std::ostream& out) const; // Override
    private:
        OT_UINT16 version_;
        OT_UINT16 num_tables_;
        std::vector<EncodingRecord> encoding_records_;

        // CMAP can be made up of multiple formats
        std::vector<PlatformEncodingFormat> format_types_;
        std::vector<std::unique_ptr<AbstractPlatformEncodingFormat>> formats_;

        void from_bytes( TypeReader& type_reader );
        void load_format( PlatformEncodingFormat format, TypeReader type_reader );
        void load_format0( TypeReader& type_reader );
        void load_format2( TypeReader& type_reader );
        void load_format4( TypeReader& type_reader );
        void load_format8( TypeReader& type_reader );
        void load_format10( TypeReader& type_reader );
        void load_format12( TypeReader& type_reader );
        void load_format13( TypeReader& type_reader );
        void load_format14( TypeReader& type_reader );

        OT_UINT16 format4_map_character_code( int index, int char_code );
    };
}
#endif // TABLE_CMAP_H
