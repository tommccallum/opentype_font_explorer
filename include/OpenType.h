#ifndef OPENTYPE_H
#define OPENTYPE_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "internals/InternalTypes.h"
#include "internals/WindowsLanguageIds.h"
#include "internals/MacintoshEncodingIds.h"
#include "internals/MacintoshLanguageIds.h"
#include "internals/NameIds.h"
#include "internals/FontReader.h"
#include "internals/TypeReader.h"
#include "internals/OffsetTable.h"
#include "internals/TableRecord.h"

// allows us to suppress argument unused message
#define UNUSED(expr) do { (void)(expr); } while (0)

namespace OpenType {

// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/name
enum PlatformID {
    PLATFORM_ID_UNICODE=0,
    PLATFORM_ID_MACINTOSH=1,
    PLATFORM_ID_ISO=2,
    PLATFORM_ID_WINDOWS=3,
    PLATFORM_ID_CUSTOM=4
};

// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/name
enum UnicodePlatformEncodingID {
    UNI_PLATFORM_EID_UNICODE_10_SEMANTICS=0,
    UNI_PLATFORM_EID_UNICODE_11_SEMANTICS=1,
    UNI_PLATFORM_EID_ISO_10464_SEMANTICS=2,
    UNI_PLATFORM_EID_UNICODE_20_BMP=3,
    UNI_PLATFORM_EID_UNICODE_20_CMAP=4,
    UNI_PLATFORM_EID_UNICODE_VAR=5,
    UNI_PLATFORM_EID_UNICODE_FULL=6
};

// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/name
enum WindowsPlatformEncodingID {
    WIN_PLATFORM_EID_SYMBOL=0,
    WIN_PLATFORM_EID_UNICODE_BMP=1,
    WIN_PLATFORM_EID_SHIFTJIS=2,
    WIN_PLATFORM_EID_PRC=3,
    WIN_PLATFORM_EID_BIG5=4,
    WIN_PLATFORM_EID_WANSUNG=5,
    WIN_PLATFORM_EID_JOHAB=6,
    WIN_PLATFORM_EID_RESERVED_1=7,
    WIN_PLATFORM_EID_RESERVED_2=8,
    WIN_PLATFORM_EID_RESERVED_3=9,
    WIN_PLATFORM_EID_UNICODE_FULL=10
};

enum IsoEncodingID {
    ISO_PLATFORM_EID_7BIT_ASCII=0,
    ISO_PLATFORM_EID_ISO_10646=1,
    ISO_PLATFORM_EID_ISO_8859_1=2
};

/*


// Table checksum calculation
// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/otff
OT_INT32 calculate_table_checksum( OT_UINT32 *table, OT_UINT32 length ) {
    OT_UINT32 sum = 0L;
    OT_UINT32* endptr = table + (( length + 3 ) & ~3) / sizeof( OT_UINT32 );
    while ( table < endptr )
        sum += *table++;
    return sum;
}

// Head table checksum calculation
// @see https://docs.microsoft.com/en-gb/typography/opentype/spec/otff
OT_INT32 calculate_head_table_checksum();

namespace OpenType {
class FontCollection {
private:
    TTCHeader header;
    std::vector<OffsetTable> offset_tables;
    std::vector<OpenTableTable> opentype_tables;
}

// version 2 TTCHeader which can be used with or without digital signature
class TTCHeader {
private:
    OT_TAG ttc_tag;
    OT_UINT16 major_version;
    OT_UINT16 minor_version;
    OT_UINT32 num_fonts;
    std::vector<OT_OFFSET32> offset_table
    OT_UINT32 dsig_tag;
    OT_UINT32 dsig_length;
    OT_UINT32 dsig_offset;
public:
    TTCHeader();
};

class Layout {
private:
    GlyphSubstitutionTable gsub;
    GlyphPositioningTable gpos;
    BaselineTable base;
    JustificationtTable jstf;
    GlyphDefinitionTable gdef;
};

class AxisValueMap {
public:
    F2DOT14 from_coordinate;
    F2DOT14 to_coordinate;
};

class SegmentMap {
public:
    OT_UINT16 position_map_count;
    std::vector<AxisValueMap> axis_value_maps
};

class AvarTable {
private:
    OT_UINT16 major_version;
    OT_UINT16 minor_version;
    OT_UINT16 reserved;
    OT_UINT16 axis_count;
    std::vector<SegmentMap> segment_maps; // length axisCount
};

//class CMapTable
*/

}

#endif // OPENTYPE_H
